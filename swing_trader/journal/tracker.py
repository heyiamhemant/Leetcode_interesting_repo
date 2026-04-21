import sqlite3
import json
from datetime import datetime
from pathlib import Path

DB_PATH = Path(__file__).parent.parent / "data" / "swing_trader.db"

_JOURNAL_SCHEMA = """
CREATE TABLE IF NOT EXISTS trades (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    ticker TEXT NOT NULL,
    entry_date TEXT NOT NULL,
    entry_price REAL NOT NULL,
    shares REAL NOT NULL,
    position_usd REAL NOT NULL,
    stop_loss REAL,
    target REAL,
    composite_score REAL,
    technical_score REAL,
    fundamental_score REAL,
    macro_regime TEXT,
    sector TEXT,
    exit_date TEXT,
    exit_price REAL,
    exit_reason TEXT,
    pnl REAL,
    pnl_pct REAL,
    notes TEXT,
    created_at TEXT DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS portfolio_snapshots (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    snapshot_date TEXT NOT NULL,
    regime TEXT,
    total_value REAL,
    cash REAL,
    positions TEXT,
    created_at TEXT DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS quarterly_reviews (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    quarter TEXT NOT NULL,
    start_value REAL,
    end_value REAL,
    total_pnl REAL,
    total_pnl_pct REAL,
    win_rate REAL,
    avg_rr REAL,
    total_trades INTEGER,
    winning_trades INTEGER,
    losing_trades INTEGER,
    best_trade TEXT,
    worst_trade TEXT,
    spy_return_pct REAL,
    alpha REAL,
    notes TEXT,
    created_at TEXT DEFAULT CURRENT_TIMESTAMP
);
"""


def _get_conn() -> sqlite3.Connection:
    conn = sqlite3.connect(str(DB_PATH), timeout=10)
    conn.row_factory = sqlite3.Row
    conn.execute("PRAGMA journal_mode=WAL")
    conn.execute("PRAGMA busy_timeout=5000")
    conn.executescript(_JOURNAL_SCHEMA)
    return conn


def log_entry(
    ticker: str,
    price: float,
    shares: float,
    position_usd: float,
    stop_loss: float,
    target: float,
    scores: dict | None = None,
    regime: str = "",
    sector: str = "",
    notes: str = "",
) -> int:
    conn = _get_conn()
    scores = scores or {}
    cur = conn.execute(
        """INSERT INTO trades
        (ticker, entry_date, entry_price, shares, position_usd, stop_loss, target,
         composite_score, technical_score, fundamental_score, macro_regime, sector, notes)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)""",
        (
            ticker,
            datetime.now().strftime("%Y-%m-%d"),
            price,
            shares,
            position_usd,
            stop_loss,
            target,
            scores.get("composite"),
            scores.get("technical"),
            scores.get("fundamental"),
            regime,
            sector,
            notes,
        ),
    )
    conn.commit()
    trade_id = cur.lastrowid
    conn.close()
    return trade_id


def log_exit(
    ticker: str,
    price: float,
    reason: str = "manual",
    notes: str = "",
) -> dict | None:
    conn = _get_conn()
    row = conn.execute(
        "SELECT * FROM trades WHERE ticker=? AND exit_date IS NULL ORDER BY entry_date DESC LIMIT 1",
        (ticker,),
    ).fetchone()

    if row is None:
        conn.close()
        return None

    pnl = (price - row["entry_price"]) * row["shares"]
    pnl_pct = ((price - row["entry_price"]) / row["entry_price"]) * 100

    conn.execute(
        """UPDATE trades SET exit_date=?, exit_price=?, exit_reason=?, pnl=?, pnl_pct=?,
        notes=CASE WHEN notes IS NOT NULL AND notes != '' THEN notes || ' | ' || ? ELSE ? END
        WHERE id=?""",
        (
            datetime.now().strftime("%Y-%m-%d"),
            price,
            reason,
            round(pnl, 2),
            round(pnl_pct, 2),
            notes,
            notes,
            row["id"],
        ),
    )
    conn.commit()
    conn.close()

    return {
        "trade_id": row["id"],
        "ticker": ticker,
        "entry_price": row["entry_price"],
        "exit_price": price,
        "pnl": round(pnl, 2),
        "pnl_pct": round(pnl_pct, 2),
        "reason": reason,
    }


def get_open_positions() -> list[dict]:
    conn = _get_conn()
    rows = conn.execute(
        "SELECT * FROM trades WHERE exit_date IS NULL ORDER BY entry_date"
    ).fetchall()
    conn.close()
    return [dict(r) for r in rows]


def get_closed_trades(quarter: str | None = None) -> list[dict]:
    conn = _get_conn()
    if quarter:
        year, q = quarter.split("Q")
        q_num = int(q)
        start_month = (q_num - 1) * 3 + 1
        end_month = start_month + 2
        start_date = f"{year}-{start_month:02d}-01"
        end_date = f"{year}-{end_month:02d}-31"
        rows = conn.execute(
            "SELECT * FROM trades WHERE exit_date IS NOT NULL AND exit_date >= ? AND exit_date <= ? ORDER BY exit_date",
            (start_date, end_date),
        ).fetchall()
    else:
        rows = conn.execute(
            "SELECT * FROM trades WHERE exit_date IS NOT NULL ORDER BY exit_date"
        ).fetchall()
    conn.close()
    return [dict(r) for r in rows]


def get_all_trades() -> list[dict]:
    conn = _get_conn()
    rows = conn.execute("SELECT * FROM trades ORDER BY entry_date").fetchall()
    conn.close()
    return [dict(r) for r in rows]


def save_quarterly_review(review: dict) -> None:
    """Persist a quarterly review to the quarterly_reviews table."""
    if review.get("total_trades", 0) == 0:
        return
    conn = _get_conn()
    conn.execute(
        """INSERT OR REPLACE INTO quarterly_reviews
        (quarter, total_pnl, total_pnl_pct, win_rate, avg_rr,
         total_trades, winning_trades, losing_trades, best_trade, worst_trade,
         spy_return_pct, alpha, notes)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)""",
        (
            review["quarter"],
            review.get("total_pnl"),
            review.get("total_pnl_pct"),
            review.get("win_rate"),
            review.get("avg_rr"),
            review.get("total_trades"),
            review.get("winning_trades"),
            review.get("losing_trades"),
            review.get("best_trade"),
            review.get("worst_trade"),
            review.get("spy_return_pct"),
            review.get("alpha"),
            json.dumps(review.get("improvement_hints", [])),
        ),
    )
    conn.commit()
    conn.close()


def save_portfolio_snapshot(regime: str, total_value: float, cash: float, positions: list[dict]) -> None:
    conn = _get_conn()
    conn.execute(
        "INSERT INTO portfolio_snapshots (snapshot_date, regime, total_value, cash, positions) VALUES (?, ?, ?, ?, ?)",
        (datetime.now().strftime("%Y-%m-%d"), regime, total_value, cash, json.dumps(positions)),
    )
    conn.commit()
    conn.close()
