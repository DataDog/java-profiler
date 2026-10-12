#!/usr/bin/env python3
"""Renders sweep-refchains-budgets.sh's CSV into a self-contained HTML report
with one line chart per metric (param value on x, metric on y). No external
JS/CSS dependencies - everything (SVG chart bodies, tooltip behavior) is
inlined so the report opens standalone from the sweep's temp working dir.
"""
import argparse
import csv
import html
import sys

ACCENT = "#2a78d6"  # dataviz palette categorical slot 1 ("blue") - single series, no legend needed
GRID = "#dedcd3"
TEXT_PRIMARY = "#0b0b0b"
TEXT_SECONDARY = "#52514e"
SURFACE = "#fcfcfb"

CHARTS = [
    ("entries_per_sec", "Throughput", "entries/sec", False),
    ("avg_round_ms", "Avg round latency", "ms", False),
    ("max_round_ms", "Max round latency", "ms", False),
    ("stw_total_s", "Total STW stop time", "s", False),
    ("stw_max_s", "Longest single STW pause", "s", False),
    ("heap_growth_mb", "Heap growth", "MB", True),
    ("peak_rss_kb", "Peak RSS", "KB", False),
]

CHART_W, CHART_H = 640, 260
MARGIN_L, MARGIN_R, MARGIN_T, MARGIN_B = 56, 24, 20, 32


def fnum(s):
    try:
        return float(s)
    except (TypeError, ValueError):
        # Coercing an unparsable CSV cell to 0.0 lets the chart render
        # instead of crashing, but a silent 0.0 looks like a real
        # measurement - flag it so a malformed sweep row doesn't masquerade
        # as a genuine zero data point.
        print(f"warning: could not parse {s!r} as a number, using 0.0", file=sys.stderr)
        return 0.0


def render_chart(rows, field, title, unit):
    xs = [fnum(r["param_value"]) for r in rows]
    ys = [fnum(r[field]) for r in rows]
    plot_w = CHART_W - MARGIN_L - MARGIN_R
    plot_h = CHART_H - MARGIN_T - MARGIN_B

    # Budget-style sweep values are usually log-spaced (1000, 10000, 100000, ...).
    # A linear x-scale collapses all but the top value into the left few
    # pixels, so switch to log scale whenever the sweep spans more than a
    # decade and every value is positive.
    use_log_x = min(xs) > 0 and (max(xs) / min(xs) >= 10)
    x_min, x_max = min(xs), max(xs)
    y_min, y_max = min(0.0, min(ys)), max(ys) if ys else 1.0
    if y_max == y_min:
        y_max = y_min + 1.0
    if x_max == x_min:
        x_max = x_min + 1.0

    def px(x):
        if use_log_x:
            import math
            lo, hi, v = math.log10(x_min), math.log10(x_max), math.log10(x)
            return MARGIN_L + (v - lo) / (hi - lo) * plot_w
        return MARGIN_L + (x - x_min) / (x_max - x_min) * plot_w

    def py(y):
        return MARGIN_T + plot_h - (y - y_min) / (y_max - y_min) * plot_h

    points = [(px(x), py(y)) for x, y in zip(xs, ys)]
    path_d = "M " + " L ".join(f"{x:.1f},{y:.1f}" for x, y in points)

    # 4 recessive horizontal gridlines with y-axis value labels.
    gridlines = []
    for i in range(5):
        gy = MARGIN_T + plot_h * i / 4
        gval = y_max - (y_max - y_min) * i / 4
        gridlines.append(
            f'<line x1="{MARGIN_L}" y1="{gy:.1f}" x2="{CHART_W - MARGIN_R}" y2="{gy:.1f}" '
            f'stroke="{GRID}" stroke-width="1"/>'
            f'<text x="{MARGIN_L - 8}" y="{gy:.1f}" text-anchor="end" dominant-baseline="middle" '
            f'font-size="11" fill="{TEXT_SECONDARY}">{gval:.3g}</text>'
        )

    x_labels = []
    for x, r in zip(xs, rows):
        x_labels.append(
            f'<text x="{px(x):.1f}" y="{CHART_H - MARGIN_B + 18}" text-anchor="middle" '
            f'font-size="11" fill="{TEXT_SECONDARY}">{r["param_value"]}</text>'
        )

    markers = []
    for i, ((x, y), r) in enumerate(zip(points, rows)):
        val = fnum(r[field])
        markers.append(
            f'<circle class="pt" cx="{x:.1f}" cy="{y:.1f}" r="4" fill="{ACCENT}" '
            f'data-value="{val:g} {html.escape(unit)}" data-x="{html.escape(r["param_value"])}"/>'
        )

    x_scale_note = (
        f'<text x="{CHART_W - MARGIN_R}" y="{MARGIN_T - 6}" text-anchor="end" '
        f'font-size="10" fill="{TEXT_SECONDARY}">x: log scale</text>'
        if use_log_x else ""
    )

    svg = f'''
<svg viewBox="0 0 {CHART_W} {CHART_H}" width="{CHART_W}" height="{CHART_H}" class="chart-svg">
  {"".join(gridlines)}
  <path d="{path_d}" fill="none" stroke="{ACCENT}" stroke-width="2" stroke-linecap="round"/>
  {"".join(markers)}
  {"".join(x_labels)}
  {x_scale_note}
</svg>'''
    return svg


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("csv_path")
    ap.add_argument("html_path")
    ap.add_argument("--param", default="budget")
    ap.add_argument("--jdk", default="")
    ap.add_argument("--gc", default="")
    ap.add_argument("--duration", default="")
    args = ap.parse_args()

    with open(args.csv_path, newline="") as f:
        rows = list(csv.DictReader(f))

    chart_sections = []
    for field, title, unit, higher_is_worse in CHARTS:
        note = "higher is worse" if higher_is_worse else ""
        svg = render_chart(rows, field, title, unit)
        chart_sections.append(f"""
<section class="card">
  <h2>{html.escape(title)} <span class="unit">({html.escape(unit)}{', ' + note if note else ''})</span></h2>
  <div class="chart-wrap">{svg}</div>
</section>""")

    table_rows = "\n".join(
        "<tr>" + "".join(f"<td>{html.escape(r[k])}</td>" for k in r) + "</tr>" for r in rows
    )
    table_header = "".join(f"<th>{html.escape(k)}</th>" for k in rows[0]) if rows else ""

    out = f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>reference-chains budget sweep — {html.escape(args.param)}</title>
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
  .meta {{ color: var(--text-secondary); font-size: 13px; margin-bottom: 24px; }}
  .grid {{ display: grid; grid-template-columns: repeat(2, minmax(320px, 1fr)); gap: 16px; }}
  .card {{
    border: 1px solid var(--grid);
    border-radius: 8px;
    padding: 16px;
    background: #fff;
  }}
  .card h2 {{ font-size: 14px; margin: 0 0 8px; font-weight: 600; }}
  .unit {{ color: var(--text-secondary); font-weight: 400; }}
  .chart-wrap {{ position: relative; }}
  .chart-svg {{ width: 100%; height: auto; overflow: visible; }}
  .pt {{ cursor: pointer; }}
  .pt:hover {{ r: 6; }}
  table {{ border-collapse: collapse; margin-top: 32px; font-size: 12px; width: 100%; }}
  th, td {{ border: 1px solid var(--grid); padding: 4px 8px; text-align: right; }}
  th {{ background: #f4f3ef; text-align: right; }}
  #tooltip {{
    position: fixed;
    pointer-events: none;
    background: #1a1a19;
    color: #fff;
    font-size: 12px;
    padding: 4px 8px;
    border-radius: 4px;
    display: none;
    z-index: 10;
  }}
</style>
</head>
<body>
<h1>reference-chains budget sweep — <code>{html.escape(args.param)}</code></h1>
<div class="meta">JDK: {html.escape(args.jdk)} &nbsp;|&nbsp; GC: {html.escape(args.gc)} &nbsp;|&nbsp; duration/point: {html.escape(str(args.duration))}s &nbsp;|&nbsp; x-axis: {html.escape(args.param)} value</div>
<div class="grid">
{"".join(chart_sections)}
</div>
<table>
<thead><tr>{table_header}</tr></thead>
<tbody>
{table_rows}
</tbody>
</table>
<div id="tooltip"></div>
<script>
  const tooltip = document.getElementById('tooltip');
  document.querySelectorAll('.pt').forEach(pt => {{
    pt.addEventListener('mousemove', e => {{
      tooltip.style.display = 'block';
      tooltip.style.left = (e.clientX + 12) + 'px';
      tooltip.style.top = (e.clientY + 12) + 'px';
      tooltip.textContent = pt.dataset.x + ': ' + pt.dataset.value;
    }});
    pt.addEventListener('mouseleave', () => {{ tooltip.style.display = 'none'; }});
  }});
</script>
</body>
</html>"""

    with open(args.html_path, "w") as f:
        f.write(out)


if __name__ == "__main__":
    main()
