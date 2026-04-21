# Swing Trading Signal System

Claude-powered swing trading signal generator for US stocks/ETFs on Vested Finance.

Claude (opus) acts as the **full decision-maker** — it receives a complete data briefing
(technicals, fundamentals, macro regime) and returns specific stock picks with entry prices,
stop losses, targets, position sizes, and its reasoning.

## Setup

```bash
cd swing_trader
pip install -r requirements.txt
```

### Claude Access (pick one)

**Option A — Cursor Agent (preferred):**
Run commands from within the Cursor IDE. The system invokes Claude via Cursor's agent mode.

**Option B — Anthropic API:**
```bash
export ANTHROPIC_API_KEY="your_key_here"
```

**Option C — Manual:**
The system saves the prompt to `data/pending_prompt.txt`. Paste it into claude.ai,
save the JSON response to `data/claude_response.json`, then run with `--from-response`.

### Macro Data (optional)

For yield curve and VIX data from FRED:
```bash
export FRED_API_KEY="your_key_here"
```

## Usage

```bash
# Full market scan — Claude analyzes all stocks and picks a portfolio
python main.py scan

# Load a manually-saved Claude response
python main.py scan --from-response

# Quarterly rebalance — Claude reviews current positions + new data
python main.py rebalance

# Check open positions for exit signals
python main.py check

# View current portfolio
python main.py portfolio

# Log a trade entry
python main.py log-entry --ticker AAPL --price 185.50 --shares 0.54 --stop 170.60 --target 205.00

# Log a trade exit
python main.py log-exit --ticker AAPL --price 202.30 --reason target

# Quarterly performance review
python main.py review
python main.py review 2026Q2

# View full trade journal
python main.py journal

# Run as a daemon (daily scans at market close)
python main.py daemon
```

## How It Works

```
  watchlist.yaml ──> Data Fetcher (yfinance + FRED)
                           │
                    ┌──────┴──────┐
                    ▼             ▼
              Technical      Fundamental
              Analysis       Analysis
              (RSI, MACD,    (P/E, ROE,
               EMA, ADX...)   FCF, growth...)
                    │             │
                    └──────┬──────┘
                           ▼
                    Macro Regime Detector
                    (SPY trend, VIX, yield curve)
                           │
                           ▼
                   ┌───────────────┐
                   │ DATA BRIEFING │ ◄─── All scores, indicators, support/resistance
                   └───────┬───────┘
                           │
                           ▼
                   ┌───────────────┐
                   │   CLAUDE AI   │ ◄─── Analyzes briefing, picks stocks,
                   │  (opus model) │      sets stops/targets, explains reasoning
                   └───────┬───────┘
                           │
                           ▼
                    Display + Journal
```

## Strategy

- **Capital**: $1,000 across max 10 positions (fractional shares on Vested)
- **Rebalance**: Quarterly — Claude reviews and restructures
- **Analysis**: Quantitative data + Claude's qualitative judgment
- **Risk**: Every trade has a stop loss and target (min 1.5:1 R:R)
- **Universe**: ~50 curated US stocks/ETFs in `config/watchlist.yaml`
- **Journal**: SQLite-backed trade tracking with quarterly review metrics

## Configuration

- `config/watchlist.yaml` — Stock/ETF universe
- `config/strategy_params.yaml` — Technical/fundamental thresholds, risk parameters

## Quarterly Workflow

1. Run `python main.py review` — see last quarter's performance
2. Run `python main.py rebalance` — Claude sees current positions + new data + past performance
3. Claude suggests sells, holds, and new buys with reasoning
4. Execute trades on Vested Finance
5. Log entries/exits with `log-entry` and `log-exit`
