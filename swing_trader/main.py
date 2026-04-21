#!/usr/bin/env python3
"""
Swing Trading Signal System — CLI Entry Point

Usage:
    python main.py scan              Full market scan → Claude picks stocks
    python main.py scan --from-response   Load a manually-saved Claude response
    python main.py portfolio         Show open positions
    python main.py journal           Show all trades
    python main.py review [QUARTER]  Quarterly performance review
    python main.py rebalance         Quarterly rebalance via Claude
    python main.py log-entry ...     Log a trade entry
    python main.py log-exit ...      Log a trade exit
    python main.py check             Check open positions for exit signals
    python main.py daemon            Run daily scans on a schedule
"""

import argparse
import json
import os
import sys
from pathlib import Path

# Auto-activate the bundled venv if it exists and we're not already in it
_THIS_DIR = Path(__file__).resolve().parent
_VENV_SITE = _THIS_DIR / ".venv" / "lib"
if _VENV_SITE.exists() and "swing_trader/.venv" not in (sys.prefix or ""):
    import subprocess
    python = str(_THIS_DIR / ".venv" / "bin" / "python3")
    if os.path.isfile(python):
        os.execv(python, [python] + sys.argv)

# Ensure swing_trader/ is on sys.path so absolute imports work
if str(_THIS_DIR) not in sys.path:
    sys.path.insert(0, str(_THIS_DIR))

from rich.console import Console
from rich.panel import Panel
from rich.text import Text
from rich import box

console = Console()

PROJECT_ROOT = _THIS_DIR


def cmd_scan(args):
    from agent.briefing import build_briefing, briefing_to_text
    from agent.prompts import build_scan_prompt
    from agent.runner import invoke_claude, load_manual_response
    from output.signals import display_regime

    if args.from_response:
        console.print("[cyan]Loading saved Claude response...[/cyan]")
        decision = load_manual_response()
        if not decision:
            console.print("[red]No response file found at data/claude_response.json[/red]")
            return
    else:
        console.print("[cyan]Gathering market data...[/cyan]")

        def _cli_progress(msg: str):
            console.print(f"  [dim]{msg}[/dim]")

        briefing = build_briefing(verbose=args.verbose, progress_cb=_cli_progress)

        display_regime(briefing["macro_raw"])

        meta = briefing.get("metadata", {})
        console.print(
            f"\n[cyan]Scanned {meta.get('total_universe', '?')} tickers, "
            f"{meta.get('stocks_analyzed', '?')} valid. "
            f"Top {meta.get('top_n_shown', '?')} sent to Claude...[/cyan]\n"
        )

        briefing_text = briefing_to_text(briefing)
        prompt = build_scan_prompt(briefing_text)
        decision = invoke_claude(prompt)

    if decision.get("status") == "manual_required":
        console.print(Panel(
            decision["message"],
            title="Manual Step Required",
            border_style="yellow",
        ))
        return

    if decision.get("status") == "parse_error":
        console.print(f"[red]Failed to parse Claude's response:[/red]")
        console.print(decision.get("raw_response", "")[:500])
        return

    _display_claude_decision(decision)

    # Save signals JSON
    out_path = PROJECT_ROOT / "data" / "latest_decision.json"
    out_path.write_text(json.dumps(decision, indent=2), encoding="utf-8")
    console.print(f"\n[dim]Decision saved to {out_path}[/dim]")

    # Send notifications
    from output.notify import notify_decision
    notify_decision(decision)


def cmd_rebalance(args):
    from agent.briefing import build_briefing, briefing_to_text
    from agent.prompts import build_review_prompt
    from agent.runner import invoke_claude
    from journal.tracker import get_open_positions
    from journal.reviewer import compute_quarterly_review

    console.print("[cyan]Gathering data for quarterly rebalance...[/cyan]")
    briefing = build_briefing(verbose=args.verbose)
    briefing_text = briefing_to_text(briefing)

    positions = get_open_positions()
    review = compute_quarterly_review()

    prompt = build_review_prompt(briefing_text, review, positions)
    decision = invoke_claude(prompt)

    if decision.get("status") == "manual_required":
        console.print(Panel(decision["message"], title="Manual Step Required", border_style="yellow"))
        return

    _display_claude_decision(decision)


def cmd_check(args):
    from agent.briefing import analyze_single_stock
    from agent.prompts import build_exit_check_prompt
    from agent.runner import invoke_claude
    from journal.tracker import get_open_positions
    from data.fetcher import ticker_to_sector
    from analysis.macro import detect_regime, compute_macro_score

    positions = get_open_positions()
    if not positions:
        console.print("[dim]No open positions to check.[/dim]")
        return

    sector_map = ticker_to_sector()
    regime = detect_regime()
    macro_score = compute_macro_score(regime)
    for pos in positions:
        console.print(f"\n[cyan]Checking {pos['ticker']}...[/cyan]")
        stock_data = analyze_single_stock(pos["ticker"], sector_map, macro_score, False)
        if not stock_data:
            console.print(f"  [yellow]Could not fetch data for {pos['ticker']}[/yellow]")
            continue

        current = {
            "price": stock_data["price"],
            "rsi": stock_data["indicators"].get("rsi"),
            "macd_hist": stock_data["indicators"].get("macd_hist"),
            "adx": stock_data["indicators"].get("adx"),
            "vol_ratio": stock_data["indicators"].get("vol_ratio"),
        }

        prompt = build_exit_check_prompt(pos, current)
        result = invoke_claude(prompt)

        action = result.get("action", "HOLD")
        color = {"HOLD": "green", "SELL": "red", "ADJUST": "yellow"}.get(action, "white")
        console.print(f"  [{color}]{action}[/{color}]: {result.get('reasoning', 'No reasoning')}")

        if result.get("new_stop"):
            console.print(f"  New stop: ${result['new_stop']}")
        if result.get("new_target"):
            console.print(f"  New target: ${result['new_target']}")


def cmd_portfolio(args):
    from journal.tracker import get_open_positions
    from output.signals import display_open_positions

    positions = get_open_positions()
    display_open_positions(positions)

    if positions:
        from config.loader import get_config
        capital = get_config()["capital"]["total"]
        total = sum(p["position_usd"] for p in positions)
        console.print(f"\nTotal deployed: [bold]${total:.2f}[/bold]")
        console.print(f"Cash remaining: [bold]${capital - total:.2f}[/bold]")


def cmd_journal(args):
    from journal.tracker import get_all_trades
    from output.signals import display_journal

    trades = get_all_trades()
    display_journal(trades)


def cmd_review(args):
    from journal.reviewer import compute_quarterly_review, current_quarter
    from output.signals import display_review

    quarter = args.quarter or current_quarter()
    review = compute_quarterly_review(quarter)
    display_review(review)


def cmd_log_entry(args):
    from journal.tracker import log_entry

    trade_id = log_entry(
        ticker=args.ticker.upper(),
        price=args.price,
        shares=args.shares,
        position_usd=args.price * args.shares,
        stop_loss=args.stop,
        target=args.target,
        notes=args.notes or "",
    )
    console.print(f"[green]Logged entry #{trade_id}: {args.ticker.upper()} @ ${args.price}[/green]")


def cmd_log_exit(args):
    from journal.tracker import log_exit

    result = log_exit(
        ticker=args.ticker.upper(),
        price=args.price,
        reason=args.reason,
        notes=args.notes or "",
    )
    if result:
        color = "green" if result["pnl"] >= 0 else "red"
        console.print(
            f"[{color}]Closed {result['ticker']}: "
            f"${result['entry_price']} -> ${result['exit_price']} "
            f"= ${result['pnl']:+.2f} ({result['pnl_pct']:+.1f}%)[/{color}]"
        )
    else:
        console.print(f"[red]No open position found for {args.ticker.upper()}[/red]")


def cmd_daemon(args):
    import schedule
    import time

    console.print("[cyan]Starting daily scan daemon...[/cyan]")
    console.print("Will scan at 16:05 ET (after market close) on weekdays.\n")

    def run_scan():
        console.print(f"\n[bold]Running scheduled scan...[/bold]")
        scan_args = argparse.Namespace(verbose=False, from_response=False)
        cmd_scan(scan_args)

    schedule.every().monday.at("16:05").do(run_scan)
    schedule.every().tuesday.at("16:05").do(run_scan)
    schedule.every().wednesday.at("16:05").do(run_scan)
    schedule.every().thursday.at("16:05").do(run_scan)
    schedule.every().friday.at("16:05").do(run_scan)

    while True:
        schedule.run_pending()
        time.sleep(60)


def _display_claude_decision(decision: dict):
    """Render Claude's trading decision to the console."""
    # Summary
    if decision.get("analysis_summary"):
        console.print(Panel(
            decision["analysis_summary"],
            title="Claude's Market Analysis",
            border_style="cyan",
        ))

    if decision.get("regime_assessment"):
        console.print(f"\n[bold]Regime Assessment:[/bold] {decision['regime_assessment']}\n")

    # Picks
    picks = decision.get("picks", [])
    if picks:
        console.print(f"\n[bold green]Claude's Picks ({len(picks)} positions)[/bold green]\n")

        for i, p in enumerate(picks, 1):
            action = p.get("action", "BUY")
            action_color = {"BUY": "green", "SELL": "red", "HOLD": "cyan"}.get(action, "white")
            conv = p.get("conviction", "-")
            conv_color = {"HIGH": "green", "MEDIUM": "yellow", "LOW": "red"}.get(conv, "dim")

            ticker = p.get("ticker", "?")
            entry = p.get("entry_price", 0)
            stop = p.get("stop_loss", 0)
            target = p.get("target", 0)
            size = p.get("position_usd", 0)
            rr = p.get("risk_reward_ratio", 0)
            risk_pct = ((entry - stop) / entry * 100) if entry > 0 else 0
            reward_pct = ((target - entry) / entry * 100) if entry > 0 else 0

            header = (
                f"[bold]{i}. [{action_color}]{action}[/{action_color}] "
                f"{ticker}[/bold]  [{conv_color}]{conv}[/{conv_color}] conviction"
            )
            numbers = (
                f"  Entry: [bold]${entry:.2f}[/bold]  |  "
                f"Stop: [red]${stop:.2f} ({risk_pct:.1f}%)[/red]  |  "
                f"Target: [green]${target:.2f} ({reward_pct:.1f}%)[/green]  |  "
                f"R:R: [bold]{rr:.1f}[/bold]  |  "
                f"Size: ${size:.0f}"
            )
            reasoning = p.get("reasoning", "")

            console.print(header)
            console.print(numbers)
            console.print(f"  [dim]{reasoning}[/dim]\n")

    # Allocation
    alloc = decision.get("portfolio_allocation", {})
    if alloc:
        console.print(
            f"\n[bold]Allocation:[/bold] ${alloc.get('total_deployed', 0):.0f} deployed, "
            f"${alloc.get('cash_reserve', 0):.0f} cash"
        )
        if alloc.get("rationale"):
            console.print(f"  Rationale: {alloc['rationale']}")

    # Watchlist notes
    notes = decision.get("watchlist_notes", [])
    if notes:
        console.print("\n[bold yellow]Watchlist Notes:[/bold yellow]")
        for n in notes:
            console.print(f"  {n.get('ticker', '?')}: {n.get('note', '')}")

    # Risk warnings
    warnings = decision.get("risk_warnings", [])
    if warnings:
        console.print("\n[bold red]Risk Warnings:[/bold red]")
        for w in warnings:
            console.print(f"  ! {w}")

    # Next review triggers
    triggers = decision.get("next_review_triggers", [])
    if triggers:
        console.print("\n[bold]Review Triggers:[/bold]")
        for t in triggers:
            console.print(f"  -> {t}")


def main():
    parser = argparse.ArgumentParser(
        description="Swing Trading Signal System powered by Claude",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    sub = parser.add_subparsers(dest="command")

    # scan
    p_scan = sub.add_parser("scan", help="Full market scan — Claude picks stocks")
    p_scan.add_argument("--verbose", "-v", action="store_true")
    p_scan.add_argument("--from-response", action="store_true", help="Load saved Claude response")
    p_scan.set_defaults(func=cmd_scan)

    # rebalance
    p_rebal = sub.add_parser("rebalance", help="Quarterly rebalance via Claude")
    p_rebal.add_argument("--verbose", "-v", action="store_true")
    p_rebal.set_defaults(func=cmd_rebalance)

    # check
    p_check = sub.add_parser("check", help="Check open positions for exit signals")
    p_check.set_defaults(func=cmd_check)

    # portfolio
    p_port = sub.add_parser("portfolio", help="Show open positions")
    p_port.set_defaults(func=cmd_portfolio)

    # journal
    p_jour = sub.add_parser("journal", help="Show trade journal")
    p_jour.set_defaults(func=cmd_journal)

    # review
    p_rev = sub.add_parser("review", help="Quarterly performance review")
    p_rev.add_argument("quarter", nargs="?", help="Quarter (e.g. 2026Q2)")
    p_rev.set_defaults(func=cmd_review)

    # log-entry
    p_entry = sub.add_parser("log-entry", help="Log a trade entry")
    p_entry.add_argument("--ticker", required=True)
    p_entry.add_argument("--price", type=float, required=True)
    p_entry.add_argument("--shares", type=float, required=True)
    p_entry.add_argument("--stop", type=float, required=True)
    p_entry.add_argument("--target", type=float, required=True)
    p_entry.add_argument("--notes", default="")
    p_entry.set_defaults(func=cmd_log_entry)

    # log-exit
    p_exit = sub.add_parser("log-exit", help="Log a trade exit")
    p_exit.add_argument("--ticker", required=True)
    p_exit.add_argument("--price", type=float, required=True)
    p_exit.add_argument("--reason", default="manual", choices=["target", "stop", "manual", "rebalance"])
    p_exit.add_argument("--notes", default="")
    p_exit.set_defaults(func=cmd_log_exit)

    # daemon
    p_daemon = sub.add_parser("daemon", help="Run daily scans on schedule")
    p_daemon.set_defaults(func=cmd_daemon)

    args = parser.parse_args()
    if not args.command:
        parser.print_help()
        return

    args.func(args)


if __name__ == "__main__":
    main()
