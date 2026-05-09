"""Flask web UI for the IRCTC Tatkal/General booking script.

Run:
    python web_app.py
Then open http://127.0.0.1:5000 in your browser.

The form fills config.json and launches tatkal_book.py as a subprocess.
Live stdout/stderr is streamed to the browser via Server-Sent Events.
"""

from __future__ import annotations

import json
import os
import queue
import signal
import subprocess
import sys
import threading
from pathlib import Path
from typing import Any

from flask import Flask, Response, jsonify, render_template_string, request


BASE_DIR = Path(__file__).parent
CONFIG_PATH = BASE_DIR / "config.json"
SCRIPT_PATH = BASE_DIR / "tatkal_book.py"

app = Flask(__name__)


_log_queue: "queue.Queue[str]" = queue.Queue()
_proc: subprocess.Popen | None = None
_proc_lock = threading.Lock()


PAGE = """
<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8" />
<title>IRCTC Booking Console</title>
<style>
  :root { color-scheme: light dark; }
  body { font-family: -apple-system, system-ui, sans-serif; max-width: 960px; margin: 24px auto; padding: 0 16px; }
  h1 { margin-bottom: 4px; }
  fieldset { border: 1px solid #8884; border-radius: 8px; margin: 12px 0; padding: 12px 16px; }
  legend { font-weight: 600; padding: 0 6px; }
  label { display: block; font-size: 0.85rem; margin-top: 8px; }
  input, select { width: 100%; padding: 6px 8px; border: 1px solid #8886; border-radius: 6px; box-sizing: border-box; }
  .row { display: grid; grid-template-columns: repeat(auto-fit, minmax(180px, 1fr)); gap: 10px; }
  .pax { border: 1px dashed #8886; padding: 10px; border-radius: 6px; margin-top: 10px; position: relative; }
  .pax button.del { position: absolute; right: 8px; top: 8px; }
  button { cursor: pointer; padding: 8px 14px; border-radius: 6px; border: 1px solid #8886; background: #4a90e2; color: white; font-weight: 600; }
  button.secondary { background: transparent; color: inherit; }
  #log { background: #111; color: #0f0; font-family: ui-monospace, monospace; font-size: 12px; white-space: pre-wrap; padding: 12px; border-radius: 8px; height: 320px; overflow: auto; margin-top: 12px; }
  .actions { display: flex; gap: 8px; margin-top: 12px; }
</style>
</head>
<body>
  <h1>IRCTC Booking Console</h1>
  <p>Fill the form, choose <b>General</b> or <b>Tatkal</b>, and start. Logs stream below.</p>

  <form id="f">
    <fieldset><legend>Credentials</legend>
      <div class="row">
        <div><label>IRCTC Username</label><input name="username" required></div>
        <div><label>IRCTC Password</label><input type="password" name="password" required></div>
      </div>
    </fieldset>

    <fieldset><legend>Journey</legend>
      <div class="row">
        <div><label>From (code)</label><input name="from_station" placeholder="NDLS" required></div>
        <div><label>To (code)</label><input name="to_station" placeholder="BCT" required></div>
        <div><label>Date (dd/mm/yyyy)</label><input name="journey_date" placeholder="15/05/2026" required></div>
        <div><label>Class</label>
          <select name="class">
            <option>SL</option><option selected>3A</option><option>2A</option>
            <option>1A</option><option>CC</option><option>2S</option><option>EC</option>
          </select>
        </div>
        <div><label>Quota</label>
          <select name="quota">
            <option value="GENERAL" selected>GENERAL</option>
            <option value="TATKAL">TATKAL</option>
            <option value="PT">PREMIUM TATKAL</option>
            <option value="LD">LADIES</option>
            <option value="SS">LOWER BERTH/SR.CITIZEN</option>
          </select>
        </div>
        <div><label>Train number</label><input name="train_number" placeholder="12952" required></div>
        <div><label>Boarding station</label><input name="boarding_station" placeholder="NDLS"></div>
        <div><label>Is AC class? (Tatkal opens 10:00 vs 11:00)</label>
          <select name="is_ac_class"><option value="true" selected>Yes</option><option value="false">No</option></select>
        </div>
      </div>
    </fieldset>

    <fieldset><legend>Passengers</legend>
      <div id="pax-list"></div>
      <button type="button" class="secondary" onclick="addPax()">+ Add passenger</button>
    </fieldset>

    <fieldset><legend>Contact &amp; Payment</legend>
      <div class="row">
        <div><label>Mobile</label><input name="mobile" pattern="[0-9]{10}" required></div>
        <div><label>UPI VPA</label><input name="upi_id" placeholder="you@okicici"></div>
      </div>
    </fieldset>

    <fieldset><legend>Schedule / Browser</legend>
      <div class="row">
        <div><label>Start buffer (sec before window)</label><input name="start_buffer_seconds" type="number" value="30"></div>
        <div><label>Headless</label><select name="headless"><option value="false" selected>No</option><option value="true">Yes</option></select></div>
      </div>
    </fieldset>

    <div class="actions">
      <button type="button" onclick="start('GENERAL')">Start GENERAL</button>
      <button type="button" onclick="start('TATKAL')">Start TATKAL</button>
      <button type="button" class="secondary" onclick="stop()">Stop</button>
      <button type="button" class="secondary" onclick="saveOnly()">Save config only</button>
    </div>
  </form>

  <div id="log">Ready.\n</div>

<script>
function paxRow(i) {
  return `<div class="pax" data-i="${i}">
    <button class="del secondary" type="button" onclick="this.parentNode.remove()">Remove</button>
    <div class="row">
      <div><label>Name</label><input name="p_name" required></div>
      <div><label>Age</label><input name="p_age" type="number" min="1" max="125" required></div>
      <div><label>Gender</label><select name="p_gender"><option>M</option><option>F</option><option>T</option></select></div>
      <div><label>Berth</label><select name="p_berth">
        <option value="">No preference</option><option>LB</option><option>MB</option><option>UB</option><option>SL</option><option>SU</option><option>WS</option>
      </select></div>
      <div><label>Food</label><select name="p_food"><option value="">None</option><option value="V">Veg</option><option value="N">Non-veg</option></select></div>
      <div><label>Nationality</label><input name="p_nationality" value="IN"></div>
    </div>
  </div>`;
}
function addPax(){ const c=document.getElementById('pax-list'); c.insertAdjacentHTML('beforeend', paxRow(c.children.length)); }
addPax();

function collect(){
  const f=document.getElementById('f');
  const fd=new FormData(f);
  const passengers=[];
  document.querySelectorAll('.pax').forEach(p=>{
    passengers.push({
      name: p.querySelector('[name=p_name]').value,
      age: parseInt(p.querySelector('[name=p_age]').value,10),
      gender: p.querySelector('[name=p_gender]').value,
      berth: p.querySelector('[name=p_berth]').value,
      food: p.querySelector('[name=p_food]').value,
      nationality: p.querySelector('[name=p_nationality]').value || 'IN',
    });
  });
  return {
    credentials:{ username: fd.get('username'), password: fd.get('password') },
    journey:{
      from_station: fd.get('from_station').toUpperCase(),
      to_station: fd.get('to_station').toUpperCase(),
      journey_date: fd.get('journey_date'),
      class: fd.get('class'),
      quota: fd.get('quota'),
      train_number: fd.get('train_number'),
      boarding_station: (fd.get('boarding_station')||'').toUpperCase(),
    },
    passengers,
    contact:{ mobile: fd.get('mobile') },
    payment:{ method:'UPI', upi_id: fd.get('upi_id') || '' },
    schedule:{
      tatkal_open_time: '10:00:00',
      start_buffer_seconds: parseInt(fd.get('start_buffer_seconds')||'30',10),
      is_ac_class: fd.get('is_ac_class')==='true',
    },
    browser:{
      headless: fd.get('headless')==='true',
      implicit_wait_seconds: 5,
      page_load_timeout_seconds: 30,
    }
  };
}

const log=document.getElementById('log');
function append(t){ log.textContent+=t; log.scrollTop=log.scrollHeight; }

async function saveOnly(){
  const r=await fetch('/api/save',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(collect())});
  const j=await r.json(); append(`[save] ${j.status}\n`);
}
async function start(quota){
  const cfg=collect(); cfg.journey.quota=quota;
  const r=await fetch('/api/start',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({config:cfg, quota})});
  const j=await r.json(); append(`[start ${quota}] ${j.status}\n`);
}
async function stop(){
  const r=await fetch('/api/stop',{method:'POST'}); const j=await r.json(); append(`[stop] ${j.status}\n`);
}

const es=new EventSource('/api/logs');
es.onmessage=e=>append(e.data+'\n');
</script>
</body></html>
"""


@app.get("/")
def index() -> str:
    return render_template_string(PAGE)


@app.post("/api/save")
def api_save() -> Any:
    cfg = request.get_json(force=True)
    CONFIG_PATH.write_text(json.dumps(cfg, indent=2), encoding="utf-8")
    return jsonify(status=f"config written to {CONFIG_PATH.name}")


def _pump_output(proc: subprocess.Popen) -> None:
    assert proc.stdout is not None
    for line in iter(proc.stdout.readline, ""):
        _log_queue.put(line.rstrip("\n"))
    proc.stdout.close()
    rc = proc.wait()
    _log_queue.put(f"[process exited with code {rc}]")


@app.post("/api/start")
def api_start() -> Any:
    global _proc
    payload = request.get_json(force=True)
    cfg = payload["config"]
    quota = payload.get("quota") or cfg["journey"]["quota"]
    CONFIG_PATH.write_text(json.dumps(cfg, indent=2), encoding="utf-8")

    with _proc_lock:
        if _proc and _proc.poll() is None:
            return jsonify(status="already running"), 409
        env = {**os.environ, "PYTHONUNBUFFERED": "1"}
        _proc = subprocess.Popen(
            [
                sys.executable,
                str(SCRIPT_PATH),
                "--config",
                str(CONFIG_PATH),
                "--quota",
                quota,
            ],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            bufsize=1,
            env=env,
        )
        threading.Thread(target=_pump_output, args=(_proc,), daemon=True).start()
    return jsonify(status=f"launched pid={_proc.pid} quota={quota}")


@app.post("/api/stop")
def api_stop() -> Any:
    global _proc
    with _proc_lock:
        if not _proc or _proc.poll() is not None:
            return jsonify(status="not running")
        try:
            _proc.send_signal(signal.SIGINT)
            _proc.wait(timeout=5)
        except Exception:
            _proc.kill()
        return jsonify(status="stopped")


@app.get("/api/logs")
def api_logs() -> Response:
    def stream() -> Any:
        while True:
            try:
                line = _log_queue.get(timeout=15)
                yield f"data: {line}\n\n"
            except queue.Empty:
                yield ": keepalive\n\n"

    return Response(stream(), mimetype="text/event-stream")


if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=False, threaded=True)
