"""IRCTC Tatkal booking automation (Selenium).

Workflow:
  1. Loads config.json with credentials, journey, passengers, payment.
  2. Opens IRCTC, logs in (you solve login CAPTCHA manually).
  3. Waits until ~30s before Tatkal window opens (10:00 AC, 11:00 non-AC).
  4. Searches the train, selects class+Tatkal quota, clicks Book Now.
  5. Auto-fills the passenger form, contact and payment (UPI) options.
  6. Pauses for you to solve the booking CAPTCHA + complete UPI on phone.

Disclaimer: For personal use only. Respect IRCTC Terms of Service.
Element locators may break when IRCTC updates the UI; adjust selectors
in the constants section below if needed.
"""

from __future__ import annotations

import argparse
import json
import sys
import time
from dataclasses import dataclass
from datetime import datetime, timedelta
from pathlib import Path
from typing import Any

from selenium import webdriver
from selenium.common.exceptions import (
    NoSuchElementException,
    TimeoutException,
)
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support import expected_conditions as ec
from selenium.webdriver.support.ui import WebDriverWait
from webdriver_manager.chrome import ChromeDriverManager


IRCTC_URL = "https://www.irctc.co.in/nget/train-search"
TATKAL_AC_TIME = "10:00:00"
TATKAL_NON_AC_TIME = "11:00:00"

QUOTA_LABELS = {
    "GENERAL": "GENERAL",
    "GN": "GENERAL",
    "TATKAL": "TATKAL",
    "TQ": "TATKAL",
    "PT": "PREMIUM TATKAL",
    "LD": "LADIES",
    "SS": "LOWER BERTH/SR.CITIZEN",
}


@dataclass
class Config:
    raw: dict[str, Any]

    @classmethod
    def load(cls, path: Path) -> "Config":
        with path.open("r", encoding="utf-8") as f:
            return cls(raw=json.load(f))

    def get(self, *keys: str) -> Any:
        node: Any = self.raw
        for k in keys:
            node = node[k]
        return node


def build_driver(headless: bool, page_load_timeout: int) -> webdriver.Chrome:
    opts = Options()
    if headless:
        opts.add_argument("--headless=new")
    opts.add_argument("--disable-blink-features=AutomationControlled")
    opts.add_argument("--start-maximized")
    opts.add_experimental_option("excludeSwitches", ["enable-automation"])
    opts.add_experimental_option("useAutomationExtension", False)
    driver = webdriver.Chrome(
        service=Service(ChromeDriverManager().install()), options=opts
    )
    driver.set_page_load_timeout(page_load_timeout)
    driver.execute_cdp_cmd(
        "Page.addScriptToEvaluateOnNewDocument",
        {"source": "Object.defineProperty(navigator,'webdriver',{get:()=>undefined})"},
    )
    return driver


def pause_for_user(prompt: str) -> None:
    print(f"\n>>> ACTION REQUIRED: {prompt}")
    input(">>> Press ENTER once done... ")


def login(driver: webdriver.Chrome, wait: WebDriverWait, cfg: Config) -> None:
    driver.get(IRCTC_URL)
    login_btn = wait.until(
        ec.element_to_be_clickable((By.XPATH, "//a[normalize-space()='LOGIN']"))
    )
    login_btn.click()

    user_in = wait.until(
        ec.presence_of_element_located(
            (By.XPATH, "//input[@formcontrolname='userid']")
        )
    )
    user_in.send_keys(cfg.get("credentials", "username"))
    driver.find_element(
        By.XPATH, "//input[@formcontrolname='password']"
    ).send_keys(cfg.get("credentials", "password"))

    pause_for_user("Solve the login CAPTCHA, then click SIGN IN.")
    wait.until(ec.presence_of_element_located((By.ID, "origin")))
    print("[ok] Logged in.")


def wait_until_window(open_time: str, buffer_seconds: int) -> None:
    target = datetime.strptime(open_time, "%H:%M:%S").time()
    today = datetime.now().date()
    target_dt = datetime.combine(today, target) - timedelta(seconds=buffer_seconds)
    if datetime.now() >= target_dt:
        print("[info] Tatkal window already open or near, proceeding immediately.")
        return
    while datetime.now() < target_dt:
        remaining = (target_dt - datetime.now()).total_seconds()
        print(f"[wait] {remaining:0.1f}s until Tatkal window...", end="\r")
        time.sleep(min(remaining, 5))
    print("\n[ok] Buffer reached. Starting search.")


def fill_station(driver: webdriver.Chrome, field_id: str, station_code: str) -> None:
    el = driver.find_element(By.ID, field_id)
    el.click()
    el.send_keys(Keys.CONTROL, "a")
    el.send_keys(station_code)
    time.sleep(1)
    el.send_keys(Keys.ARROW_DOWN, Keys.ENTER)


def resolve_quota_label(quota_code: str) -> str:
    label = QUOTA_LABELS.get(quota_code.upper())
    if not label:
        raise ValueError(
            f"Unknown quota '{quota_code}'. Use one of: {sorted(QUOTA_LABELS)}"
        )
    return label


def search_train(driver: webdriver.Chrome, wait: WebDriverWait, cfg: Config) -> None:
    fill_station(driver, "origin", cfg.get("journey", "from_station"))
    fill_station(driver, "destination", cfg.get("journey", "to_station"))

    date_in = driver.find_element(By.XPATH, "//p-calendar//input")
    date_in.click()
    date_in.send_keys(Keys.CONTROL, "a")
    date_in.send_keys(cfg.get("journey", "journey_date"))
    date_in.send_keys(Keys.ESCAPE)

    quota_label = resolve_quota_label(cfg.get("journey", "quota"))
    quota_dd = driver.find_element(
        By.XPATH, "//p-dropdown[@formcontrolname='journeyQuota']"
    )
    quota_dd.click()
    quota_opt = wait.until(
        ec.element_to_be_clickable(
            (By.XPATH, f"//li//span[normalize-space()='{quota_label}']")
        )
    )
    quota_opt.click()
    print(f"[ok] Quota set to {quota_label}.")

    driver.find_element(
        By.XPATH, "//button[normalize-space()='Search']"
    ).click()
    print("[ok] Train search submitted.")


def select_train_and_class(
    driver: webdriver.Chrome, wait: WebDriverWait, cfg: Config
) -> None:
    train_no = cfg.get("journey", "train_number")
    cls = cfg.get("journey", "class")
    train_card = wait.until(
        ec.presence_of_element_located(
            (By.XPATH, f"//div[contains(@class,'train-list')]//strong[contains(.,'{train_no}')]/ancestor::div[contains(@class,'bull-back')]")
        )
    )
    class_btn = train_card.find_element(
        By.XPATH, f".//div[contains(@class,'pre-avl')]//strong[normalize-space()='{cls}']/ancestor::div[contains(@class,'pre-avl')]"
    )
    class_btn.click()

    book_btn = wait.until(
        ec.element_to_be_clickable(
            (By.XPATH, "//button[contains(.,'Book Now')]")
        )
    )
    book_btn.click()
    print("[ok] Book Now clicked.")


def fill_passengers(
    driver: webdriver.Chrome, wait: WebDriverWait, cfg: Config
) -> None:
    passengers = cfg.get("passengers")
    wait.until(
        ec.presence_of_element_located(
            (By.XPATH, "//input[@placeholder='Passenger Name']")
        )
    )
    for idx, p in enumerate(passengers):
        if idx > 0:
            driver.find_element(
                By.XPATH, "//a[normalize-space()='+ Add Passenger']"
            ).click()
            time.sleep(0.4)
        name_inputs = driver.find_elements(
            By.XPATH, "//input[@placeholder='Passenger Name']"
        )
        age_inputs = driver.find_elements(
            By.XPATH, "//input[@placeholder='Age']"
        )
        gender_dd = driver.find_elements(
            By.XPATH, "//select[@formcontrolname='passengerGender']"
        )
        berth_dd = driver.find_elements(
            By.XPATH, "//select[@formcontrolname='passengerBerthChoice']"
        )

        name_inputs[idx].send_keys(p["name"])
        age_inputs[idx].send_keys(str(p["age"]))
        _select_by_value(gender_dd[idx], p["gender"])
        if berth_dd and idx < len(berth_dd):
            _select_by_value(berth_dd[idx], p.get("berth", ""))

    mobile_in = driver.find_elements(
        By.XPATH, "//input[@formcontrolname='mobile']"
    )
    if mobile_in:
        mobile_in[0].clear()
        mobile_in[0].send_keys(cfg.get("contact", "mobile"))

    print("[ok] Passenger details filled.")


def _select_by_value(select_el: Any, value: str) -> None:
    from selenium.webdriver.support.ui import Select

    if not value:
        return
    try:
        Select(select_el).select_by_value(value)
    except Exception:
        try:
            Select(select_el).select_by_visible_text(value)
        except Exception:
            pass


def select_payment_upi(driver: webdriver.Chrome, wait: WebDriverWait) -> None:
    pause_for_user(
        "Solve the booking-page CAPTCHA and click 'Continue' to reach the "
        "payment page."
    )
    bhim_radio = wait.until(
        ec.element_to_be_clickable(
            (By.XPATH, "//label[contains(.,'BHIM/UPI/USSD')]")
        )
    )
    bhim_radio.click()
    pay_btn = wait.until(
        ec.element_to_be_clickable(
            (By.XPATH, "//button[contains(.,'Pay & Book')]")
        )
    )
    pay_btn.click()
    print("[ok] Payment submitted. Approve the UPI request on your phone.")


def run(cfg: Config, quota_override: str | None = None) -> int:
    if quota_override:
        cfg.raw["journey"]["quota"] = quota_override
    quota_label = resolve_quota_label(cfg.get("journey", "quota"))
    is_tatkal = quota_label in {"TATKAL", "PREMIUM TATKAL"}
    print(f"[info] Booking mode: {quota_label}")

    driver = build_driver(
        headless=cfg.get("browser", "headless"),
        page_load_timeout=cfg.get("browser", "page_load_timeout_seconds"),
    )
    driver.implicitly_wait(cfg.get("browser", "implicit_wait_seconds"))
    wait = WebDriverWait(driver, 30)
    try:
        login(driver, wait, cfg)
        if is_tatkal:
            open_time = (
                TATKAL_AC_TIME
                if cfg.get("schedule", "is_ac_class")
                else TATKAL_NON_AC_TIME
            )
            wait_until_window(
                open_time, cfg.get("schedule", "start_buffer_seconds")
            )
        else:
            print("[info] Non-Tatkal quota: proceeding without window wait.")
        search_train(driver, wait, cfg)
        select_train_and_class(driver, wait, cfg)
        fill_passengers(driver, wait, cfg)
        select_payment_upi(driver, wait)
        pause_for_user("Booking flow handed off. Verify and close browser.")
        return 0
    except (TimeoutException, NoSuchElementException) as e:
        print(f"[error] Selector failed: {e}", file=sys.stderr)
        pause_for_user("Inspect the page and continue manually if possible.")
        return 1
    finally:
        driver.quit()


def main() -> int:
    parser = argparse.ArgumentParser(description="IRCTC Tatkal automation")
    parser.add_argument(
        "--config",
        type=Path,
        default=Path(__file__).parent / "config.json",
        help="Path to config.json",
    )
    parser.add_argument(
        "--quota",
        choices=sorted({k for k in QUOTA_LABELS}),
        help="Override journey.quota (e.g., GENERAL, TATKAL, PT).",
    )
    args = parser.parse_args()
    if not args.config.exists():
        print(
            f"[error] Config not found: {args.config}. "
            f"Copy config.example.json to config.json first.",
            file=sys.stderr,
        )
        return 2
    return run(Config.load(args.config), quota_override=args.quota)


if __name__ == "__main__":
    sys.exit(main())
