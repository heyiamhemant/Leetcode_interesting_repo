import yaml
from pathlib import Path

CONFIG_DIR = Path(__file__).resolve().parent

_config: dict | None = None
_watchlist: dict | None = None
_etf_tickers: set[str] | None = None


def get_config() -> dict:
    global _config
    if _config is None:
        with open(CONFIG_DIR / "strategy_params.yaml") as f:
            _config = yaml.safe_load(f)
    return _config


def get_watchlist_raw() -> dict:
    global _watchlist
    if _watchlist is None:
        with open(CONFIG_DIR / "watchlist.yaml") as f:
            _watchlist = yaml.safe_load(f)
    return _watchlist


def get_etf_tickers() -> set[str]:
    """Return the set of tickers listed under the 'etfs' key in watchlist.yaml."""
    global _etf_tickers
    if _etf_tickers is None:
        raw = get_watchlist_raw()
        _etf_tickers = set()
        for group_tickers in raw.get("etfs", {}).values():
            _etf_tickers.update(group_tickers)
    return _etf_tickers


def reload_config() -> dict:
    """Force re-read from disk. Useful for tests."""
    global _config, _watchlist, _etf_tickers
    _config = None
    _watchlist = None
    _etf_tickers = None
    return get_config()
