#!/usr/bin/env python3
"""Renders sweep-refchains-all.sh's combined (knob,param_value,<metrics>) CSV
into a single self-contained HTML report: one tab per knob, one Chart.js line
chart per metric within each tab. Chart.js is vendored under utils/vendor and
inlined directly into the report so it opens standalone, offline, from the
sweep's temp working directory (no CDN dependency at view time).
"""
import argparse
import csv
import html
import json
import os

ACCENT = "#2a78d6"  # dataviz palette categorical slot 1 ("blue") - one series per chart, no legend needed
GRID = "#dedcd3"
TEXT_PRIMARY = "#0b0b0b"
TEXT_SECONDARY = "#52514e"
SURFACE = "#fcfcfb"

HERE = os.path.dirname(os.path.abspath(__file__))
CHARTJS_PATH = os.path.join(HERE, "vendor", "chart.umd.min.js")

METRICS = [
    ("time_to_first_chain_s", "Time to first reference chain", "s", True),
    ("chain_count", "Reference chains found", "count", False),
    ("abandoned_count", "Searches abandoned", "count", True),
    ("entries_per_sec", "Throughput", "entries/sec", False),
    ("avg_round_ms", "Avg round latency", "ms", True),
    ("max_round_ms", "Max round latency", "ms", True),
    ("stw_total_s", "Total STW stop time", "s", True),
    ("stw_max_s", "Longest single STW pause", "s", True),
    ("heap_growth_mb", "Heap growth", "MB", True),
    ("peak_rss_kb", "Peak RSS", "KB", True),
]

# time_to_first_chain_s uses -1 as a sentinel for "no chain found within the
# run's duration" (see refchains-jfr-metrics.py) - never plot that as a
# real value, and never let it participate in the min/max Y bounds.
NOT_FOUND_SENTINEL = -1.0

KNOB_LABELS = {
    "budget": "budget",
    "firstpassbudget": "firstpassbudget",
    "pausetarget": "pausetarget",
    "painbudget": "painbudget",
}


def fnum(s):
    try:
        return float(s)
    except (TypeError, ValueError):
        return 0.0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("csv_path")
    ap.add_argument("html_path")
    ap.add_argument("--jdk", default="")
    ap.add_argument("--gc", default="")
    ap.add_argument("--duration", default="")
    args = ap.parse_args()

    with open(args.csv_path, newline="") as f:
        rows = list(csv.DictReader(f))

    knobs = []
    for r in rows:
        if r["knob"] not in knobs:
            knobs.append(r["knob"])

    with open(CHARTJS_PATH) as f:
        chartjs_src = f.read()

    tabs_nav = []
    tabs_content = []
    chart_configs = []  # list of (canvas_id, config_dict)

    for ti, knob in enumerate(knobs):
        knob_rows = [r for r in rows if r["knob"] == knob]
        active = "active" if ti == 0 else ""
        tabs_nav.append(
            f'<button class="tab-btn {active}" data-tab="tab-{knob}">{KNOB_LABELS.get(knob, knob)}</button>'
        )

        xs_raw = [r["param_value"] for r in knob_rows]
        xs_num = [fnum(v) for v in xs_raw]
        use_log = min(xs_num) > 0 and (max(xs_num) / min(xs_num) >= 10)

        cards = []
        for field, title, unit, higher_is_worse in METRICS:
            canvas_id = f"chart-{knob}-{field}"
            raw_ys = [fnum(r[field]) for r in knob_rows]
            if field == "time_to_first_chain_s":
                not_found = sum(1 for y in raw_ys if y == NOT_FOUND_SENTINEL)
                ys = [None if y == NOT_FOUND_SENTINEL else y for y in raw_ys]
                badge = (
                    f'<span class="badge">{not_found}/{len(raw_ys)} runs never found a chain</span>'
                    if not_found else ""
                )
            else:
                ys = raw_ys
                badge = ""
            note = "higher is worse" if higher_is_worse else ""
            cards.append(f'''
<section class="card">
  <h2>{title} <span class="unit">({unit}{', ' + note if note else ''})</span> {badge}</h2>
  <div class="chart-wrap"><canvas id="{canvas_id}"></canvas></div>
</section>''')

            config = {
                "type": "line",
                "data": {
                    "labels": xs_raw,
                    "datasets": [{
                        "label": title,
                        "data": ys,
                        "borderColor": ACCENT,
                        "backgroundColor": ACCENT,
                        "borderWidth": 2,
                        "pointRadius": 4,
                        "pointHoverRadius": 6,
                        "tension": 0,
                        "fill": False,
                        "spanGaps": False,
                    }],
                },
                "options": {
                    "responsive": True,
                    "maintainAspectRatio": False,
                    "plugins": {
                        "legend": {"display": False},
                        "tooltip": {
                            "callbacks": {},
                            "backgroundColor": "#1a1a19",
                            "titleColor": "#ffffff",
                            "bodyColor": "#ffffff",
                        },
                    },
                    "scales": {
                        "x": {
                            "type": "logarithmic" if use_log else "linear",
                            "title": {"display": True, "text": f"{KNOB_LABELS.get(knob, knob)}" + (" (log scale)" if use_log else "")},
                            "grid": {"color": GRID},
                            "ticks": {"color": TEXT_SECONDARY},
                        },
                        "y": {
                            "title": {"display": True, "text": unit},
                            "grid": {"color": GRID},
                            "ticks": {"color": TEXT_SECONDARY},
                            "beginAtZero": True,
                        },
                    },
                },
            }
            chart_configs.append((canvas_id, config, xs_num if use_log else None))

        tabs_content.append(f'''
<div class="tab-pane {active}" id="tab-{knob}">
  <div class="grid">{"".join(cards)}</div>
</div>''')

    table_header = "".join(f"<th>{html.escape(str(k))}</th>" for k in rows[0]) if rows else ""
    table_rows = "\n".join(
        "<tr>" + "".join(f"<td>{html.escape(str(r[k]))}</td>" for k in r) + "</tr>" for r in rows
    )

    # Chart.js logarithmic scale needs numeric x values, not category labels -
    # use a scatter-with-lines dataset (x/y pairs) instead of the labels array
    # for any knob using log scale, since category+log axis isn't supported.
    js_chart_inits = []
    for canvas_id, config, xs_num in chart_configs:
        if xs_num is not None:
            ys = config["data"]["datasets"][0]["data"]
            config["data"]["datasets"][0]["data"] = [{"x": x, "y": y} for x, y in zip(xs_num, ys)]
            del config["data"]["labels"]
        js_chart_inits.append(
            f'new Chart(document.getElementById("{canvas_id}"), {json.dumps(config)});'
        )

    out = f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>reference-chains OFAT budget-knob sweep</title>
<style>
  :root {{
    color-scheme: light;
    --surface-1: {SURFACE};
    --text-primary: {TEXT_PRIMARY};
    --text-secondary: {TEXT_SECONDARY};
    --grid: {GRID};
  }}
  body {{
    background: var(--surface-1);
    color: var(--text-primary);
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Helvetica, Arial, sans-serif;
    margin: 0;
    padding: 32px;
  }}
  h1 {{ font-size: 20px; margin: 0 0 4px; }}
  .meta {{ color: var(--text-secondary); font-size: 13px; margin-bottom: 20px; }}
  .tabs {{ display: flex; gap: 4px; border-bottom: 1px solid var(--grid); margin-bottom: 20px; }}
  .tab-btn {{
    border: none; background: none; padding: 10px 16px; font-size: 13px;
    font-weight: 600; color: var(--text-secondary); cursor: pointer;
    border-bottom: 2px solid transparent; margin-bottom: -1px;
  }}
  .tab-btn.active {{ color: {ACCENT}; border-bottom-color: {ACCENT}; }}
  .tab-pane {{ display: none; }}
  .tab-pane.active {{ display: block; }}
  .grid {{ display: grid; grid-template-columns: repeat(2, minmax(340px, 1fr)); gap: 16px; }}
  .card {{ border: 1px solid var(--grid); border-radius: 8px; padding: 16px; background: #fff; }}
  .card h2 {{ font-size: 14px; margin: 0 0 8px; font-weight: 600; }}
  .unit {{ color: var(--text-secondary); font-weight: 400; }}
  .badge {{
    display: inline-block; font-size: 10px; font-weight: 600; color: #8a5a00;
    background: #fdf0d5; border-radius: 4px; padding: 1px 6px; margin-left: 4px;
  }}
  .chart-wrap {{ position: relative; height: 260px; }}
  table {{ border-collapse: collapse; margin-top: 32px; font-size: 12px; width: 100%; }}
  th, td {{ border: 1px solid var(--grid); padding: 4px 8px; text-align: right; }}
  th {{ background: #f4f3ef; }}
  details {{ margin-top: 32px; }}
  summary {{ cursor: pointer; font-size: 13px; color: var(--text-secondary); }}
</style>
</head>
<body>
<h1>reference-chains OFAT budget-knob sweep</h1>
<div class="meta">JDK: {html.escape(str(args.jdk))} &nbsp;|&nbsp; GC: {html.escape(str(args.gc))} &nbsp;|&nbsp; duration/point: {html.escape(str(args.duration))}s &nbsp;|&nbsp; one-factor-at-a-time: each knob swept independently, others left at their built-in defaults</div>
<div class="tabs">{"".join(tabs_nav)}</div>
{"".join(tabs_content)}
<details>
  <summary>Raw data ({len(rows)} runs)</summary>
  <table>
    <thead><tr>{table_header}</tr></thead>
    <tbody>{table_rows}</tbody>
  </table>
</details>
<script>{chartjs_src}</script>
<script>
  document.querySelectorAll('.tab-btn').forEach(btn => {{
    btn.addEventListener('click', () => {{
      document.querySelectorAll('.tab-btn').forEach(b => b.classList.remove('active'));
      document.querySelectorAll('.tab-pane').forEach(p => p.classList.remove('active'));
      btn.classList.add('active');
      document.getElementById(btn.dataset.tab).classList.add('active');
    }});
  }});
  {"".join(js_chart_inits)}
</script>
</body>
</html>"""

    with open(args.html_path, "w") as f:
        f.write(out)


if __name__ == "__main__":
    main()
