import json
import sys
import threading
from datetime import datetime
from pathlib import Path

_THIS_DIR = Path(__file__).resolve().parent
_PROJECT_DIR = _THIS_DIR.parent
if str(_PROJECT_DIR) not in sys.path:
    sys.path.insert(0, str(_PROJECT_DIR))

from flask import Flask, render_template, request, jsonify, redirect, url_for

app = Flask(
    __name__,
    template_folder=str(_THIS_DIR / "templates"),
    static_folder=str(_THIS_DIR / "static"),
)
app.secret_key = "swing-trader-local-only"

DATA_DIR = _PROJECT_DIR / "data"

_scan_lock = threading.Lock()
_scan_state = {"running": False, "progress": "", "result": None, "error": None}


@app.route("/")
def dashboard():
    from journal.tracker import get_open_positions, get_all_trades
    from analysis.macro import detect_regime

    positions = get_open_positions()
    trades = get_all_trades()
    closed = [t for t in trades if t.get("exit_date")]

    from config.loader import get_config
    capital = get_config()["capital"]["total"]

    total_deployed = sum(p["position_usd"] for p in positions)
    total_pnl = sum(t.get("pnl", 0) or 0 for t in closed)
    wins = sum(1 for t in closed if (t.get("pnl") or 0) > 0)
    win_rate = (wins / len(closed) * 100) if closed else 0

    try:
        regime = detect_regime()
    except Exception:
        regime = {"regime": "unknown", "allocation_pct": 1.0, "tilt": "N/A", "signals": {}}

    latest_decision = _load_latest_decision()

    return render_template(
        "dashboard.html",
        regime=regime,
        positions=positions,
        total_deployed=total_deployed,
        cash=capital - total_deployed,
        total_pnl=total_pnl,
        win_rate=win_rate,
        total_trades=len(closed),
        open_count=len(positions),
        latest_decision=latest_decision,
    )


@app.route("/scan", methods=["GET"])
def scan_page():
    latest = _load_latest_decision()
    return render_template("scan.html", decision=latest, scan_state=_scan_state)


@app.route("/api/scan/start", methods=["POST"])
def api_scan_start():
    with _scan_lock:
        if _scan_state["running"]:
            return jsonify({"status": "already_running"})
        _scan_state["running"] = True
        _scan_state["progress"] = "Gathering market data..."
        _scan_state["result"] = None
        _scan_state["error"] = None

    thread = threading.Thread(target=_run_scan_background, daemon=True)
    thread.start()
    return jsonify({"status": "started"})


@app.route("/api/scan/status", methods=["GET"])
def api_scan_status():
    return jsonify(_scan_state)


@app.route("/api/scan/prompt", methods=["GET"])
def api_scan_prompt():
    """Serve the pending prompt text so the UI can copy it directly."""
    prompt_path = DATA_DIR / "pending_prompt.txt"
    if prompt_path.exists():
        return jsonify({"status": "ok", "prompt": prompt_path.read_text(encoding="utf-8")})
    return jsonify({"status": "error", "message": "No pending prompt found."}), 404


@app.route("/api/scan/load-response", methods=["POST"])
def api_load_response():
    """Load a manually-saved claude_response.json."""
    from agent.runner import load_manual_response
    decision = load_manual_response()
    if decision:
        _save_latest_decision(decision)
        return jsonify({"status": "ok", "decision": decision})
    return jsonify({"status": "error", "message": "No response file found at data/claude_response.json"}), 404


@app.route("/api/scan/upload-response", methods=["POST"])
def api_upload_response():
    """Accept pasted JSON response from the browser."""
    try:
        data = request.get_json()
        response_text = data.get("response", "")
        decision = json.loads(response_text)
        resp_path = DATA_DIR / "claude_response.json"
        resp_path.write_text(json.dumps(decision, indent=2), encoding="utf-8")
        _save_latest_decision(decision)
        return jsonify({"status": "ok", "decision": decision})
    except (json.JSONDecodeError, Exception) as e:
        return jsonify({"status": "error", "message": str(e)}), 400


@app.route("/portfolio")
def portfolio_page():
    from journal.tracker import get_open_positions
    positions = get_open_positions()
    from config.loader import get_config
    capital = get_config()["capital"]["total"]
    total = sum(p["position_usd"] for p in positions)
    return render_template("portfolio.html", positions=positions, total_deployed=total, cash=capital - total)


@app.route("/journal")
def journal_page():
    from journal.tracker import get_all_trades
    trades = get_all_trades()
    return render_template("journal.html", trades=trades)


@app.route("/review")
def review_page():
    from journal.reviewer import compute_quarterly_review, current_quarter
    quarter = request.args.get("quarter") or current_quarter()
    review = compute_quarterly_review(quarter)
    return render_template("review.html", review=review, quarter=quarter)


@app.route("/api/log-entry", methods=["POST"])
def api_log_entry():
    from journal.tracker import log_entry
    data = request.get_json()
    try:
        price = float(data["price"])
        shares = float(data["shares"])
        trade_id = log_entry(
            ticker=data["ticker"].upper(),
            price=price,
            shares=shares,
            position_usd=price * shares,
            stop_loss=float(data["stop_loss"]),
            target=float(data["target"]),
            notes=data.get("notes", ""),
        )
        return jsonify({"status": "ok", "trade_id": trade_id})
    except (KeyError, ValueError) as e:
        return jsonify({"status": "error", "message": str(e)}), 400


@app.route("/api/log-exit", methods=["POST"])
def api_log_exit():
    from journal.tracker import log_exit
    data = request.get_json()
    try:
        result = log_exit(
            ticker=data["ticker"].upper(),
            price=float(data["price"]),
            reason=data.get("reason", "manual"),
            notes=data.get("notes", ""),
        )
        if result:
            return jsonify({"status": "ok", "result": result})
        return jsonify({"status": "error", "message": f"No open position for {data['ticker']}"}), 404
    except (KeyError, ValueError) as e:
        return jsonify({"status": "error", "message": str(e)}), 400


@app.route("/api/log-all-entries", methods=["POST"])
def api_log_all_entries():
    """Bulk log all picks from the latest decision."""
    from journal.tracker import log_entry
    decision = _load_latest_decision()
    if not decision or not decision.get("picks"):
        return jsonify({"status": "error", "message": "No decision loaded"}), 400

    logged = []
    for p in decision["picks"]:
        if p.get("action", "BUY").upper() != "BUY":
            continue
        price = p.get("entry_price", 0)
        size = p.get("position_usd", 0)
        shares = round(size / price, 6) if price > 0 else 0
        tid = log_entry(
            ticker=p["ticker"],
            price=price,
            shares=shares,
            position_usd=size,
            stop_loss=p.get("stop_loss", 0),
            target=p.get("target", 0),
            scores={
                "composite": None,
                "technical": None,
                "fundamental": None,
            },
            regime=decision.get("regime_assessment", "")[:50],
            sector="",
            notes=f"Conviction: {p.get('conviction', 'N/A')}",
        )
        logged.append({"ticker": p["ticker"], "trade_id": tid})

    return jsonify({"status": "ok", "logged": logged})


def _run_scan_background():
    try:
        from agent.briefing import build_briefing, briefing_to_text
        from agent.prompts import build_scan_prompt

        def on_progress(msg):
            _scan_state["progress"] = msg

        briefing = build_briefing(verbose=False, progress_cb=on_progress)
        meta = briefing.get("metadata", {})
        _scan_state["progress"] = (
            f"Analyzed {meta.get('stocks_analyzed', '?')} of {meta.get('total_universe', '?')} stocks. "
            f"Top {meta.get('top_n_shown', '?')} sent to Claude. Building prompt..."
        )

        briefing_text = briefing_to_text(briefing)
        prompt = build_scan_prompt(briefing_text)

        prompt_path = DATA_DIR / "pending_prompt.txt"
        prompt_path.write_text(prompt, encoding="utf-8")

        _scan_state["progress"] = "Trying Claude API..."
        from agent.runner import invoke_claude
        decision = invoke_claude(prompt)

        if decision.get("status") == "manual_required":
            _scan_state["progress"] = "Prompt saved. Paste Claude's response to continue."
            _scan_state["result"] = {"status": "manual_required", "briefing_summary": {
                "total_stocks": briefing.get("top_n_sent_to_claude", briefing.get("all_stocks_count", "?")),
                "regime": briefing["macro"]["regime"],
                "tilt": briefing["macro"]["tilt"],
            }}
        else:
            _save_latest_decision(decision)
            _scan_state["result"] = decision
            _scan_state["progress"] = "Scan complete."

    except Exception as e:
        _scan_state["error"] = str(e)
        _scan_state["progress"] = f"Error: {e}"
    finally:
        with _scan_lock:
            _scan_state["running"] = False


def _load_latest_decision() -> dict | None:
    path = DATA_DIR / "latest_decision.json"
    if path.exists():
        try:
            return json.loads(path.read_text(encoding="utf-8"))
        except Exception:
            pass
    return None


def _save_latest_decision(decision: dict):
    path = DATA_DIR / "latest_decision.json"
    path.write_text(json.dumps(decision, indent=2), encoding="utf-8")


if __name__ == "__main__":
    app.run(debug=True, port=5000)
