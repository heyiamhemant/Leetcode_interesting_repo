# IRCTC Tatkal Booking Automation

Selenium-based helper that pre-fills login, search, passenger and payment
screens so you only have to solve the CAPTCHA and approve the UPI request.

## Setup

```bash
cd tatkal_booking
python3 -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt
cp config.example.json config.json
# edit config.json with your details
```

## Run

### Option A — Web UI (recommended)

```bash
python web_app.py
# open http://127.0.0.1:5000
```

Fill the form, add passengers, then click **Start GENERAL** or **Start TATKAL**.
Logs stream live in the page; **Stop** sends SIGINT to the running booking
process. **Save config only** writes `config.json` without launching.

### Option B — CLI

```bash
python tatkal_book.py --config config.json            # uses journey.quota from config
python tatkal_book.py --quota GENERAL                 # try general booking first
python tatkal_book.py --quota TATKAL                  # then re-run for Tatkal window
```

The `--quota` flag overrides `journey.quota`. For non-Tatkal quotas the
script skips the 10:00/11:00 window wait and books immediately.

The script will:

1. Open Chrome and load IRCTC.
2. Pre-fill username/password — you solve the login CAPTCHA, press ENTER in terminal.
3. Wait until ~30s before Tatkal opens (10:00 AC, 11:00 non-AC).
4. Search train, pick class + Tatkal quota, click **Book Now**.
5. Auto-fill all passengers and contact mobile.
6. Pause for booking-page CAPTCHA, then auto-select **BHIM/UPI** and click **Pay & Book**.
7. Approve the collect-request on your UPI app.

## Config keys

| Key                              | Notes                                     |
| -------------------------------- | ----------------------------------------- |
| `journey.from_station` / `to_station` | Station codes (e.g., `NDLS`, `BCT`)  |
| `journey.journey_date`           | Format `dd/mm/yyyy`                       |
| `journey.class`                  | `SL`, `3A`, `2A`, `1A`, `CC`, `2S`, etc.  |
| `journey.quota`                  | `GENERAL`, `TATKAL`, `PT`, `LD`, `SS`     |
| `passengers[].berth`             | `LB`, `MB`, `UB`, `SL`, `SU`, `WS`, `""`  |
| `payment.upi_id`                 | Your UPI VPA                              |
| `schedule.is_ac_class`           | `true` for AC (10:00 IST), else `false`   |
| `schedule.start_buffer_seconds`  | How early to be ready before the window   |
| `browser.headless`               | Keep `false` — CAPTCHAs need the browser  |

## Notes / disclaimers

- Personal use only. Respect IRCTC's Terms of Service and rate limits.
- IRCTC frequently changes the UI; if a step fails, update the XPath
  constants in `tatkal_book.py`.
- The script never solves CAPTCHAs for you — that would violate ToS.
