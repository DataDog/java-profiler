#!/usr/bin/env bash
# Post aggregated benchmark results as a single PR comment.
#
# Handles two report types found under REPORTS_DIR (default: reports/):
#   - comparison-baseline-vs-candidate_*.md  (perf comparison benchmarks)
#   - result_${BENCHMARK}_${JDK}_${LIBRARY}.json  (reliability benchmarks)
#
# Required env:
#   DDPROF_COMMIT_BRANCH  – branch name used to locate the open PR
# Optional env:
#   CI_PIPELINE_URL, DDPROF_COMMIT_SHA

set -euo pipefail

REPORTS_DIR="${1:-reports}"
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# --- Perf comparison reports (markdown, one per benchmark cell) ---
SECTIONS=""
for md in "${REPORTS_DIR}"/comparison-baseline-vs-candidate_*.md; do
  [ -f "${md}" ] || continue
  label=$(basename "${md}" .md | sed 's/comparison-baseline-vs-candidate_//')
  SECTIONS="${SECTIONS}
<details><summary>${label}</summary>

$(cat "${md}")

</details>
"
done

# --- Reliability reports (JSON, one per benchmark×JDK×library) ---
RELIABILITY_TABLE=$(python3 - "${REPORTS_DIR}" <<'PYEOF'
import json, sys, glob, collections

reports_dir = sys.argv[1]
results = collections.defaultdict(dict)

for path in sorted(glob.glob(f"{reports_dir}/result_*.json")):
    try:
        with open(path) as f:
            r = json.load(f)
        key = (r["benchmark"], r["jdk"])
        results[key][r["library"]] = r
    except Exception:
        continue

if not results:
    sys.exit(0)

def fmt_avg(r):
    icon = "💥" if r.get("crashed") else "✅"
    avg = r.get("avg_ms", 0)
    cnt = r.get("run_count", 0)
    return f"{icon} {avg} ms ({cnt} iters)"

def fmt_delta(latest, dev):
    la, da = latest.get("avg_ms", 0), dev.get("avg_ms", 0)
    if not la or not da:
        return "—"
    pct = (da - la) / la * 100
    # positive = dev is slower (potential regression)
    arrow = "🔴 +" if pct > 2 else ("🟢 " if pct < -2 else "")
    return f"{arrow}{pct:+.1f}%"

def fmt_uploads(r):
    return str(r.get("upload_count", 0))

def fmt_issues(r):
    e = r.get("error_count", 0)
    w = r.get("warn_count", 0)
    if e == 0 and w == 0:
        return "—"
    parts = []
    if e: parts.append(f"E:{e}")
    if w: parts.append(f"W:{w}")
    return "⚠️ " + " ".join(parts)

lines = [
    "### Reliability Benchmarks",
    "",
    "| Benchmark | JDK | Latest | Dev | Δ% (dev vs latest) | Uploads L/D | Issues L/D |",
    "|-----------|-----|--------|-----|-------------------|-------------|------------|",
]
for (bench, jdk) in sorted(results.keys()):
    libs = results[(bench, jdk)]
    latest = libs.get("latest", {})
    dev    = libs.get("dev", {})

    col_latest  = fmt_avg(latest)  if latest else "—"
    col_dev     = fmt_avg(dev)     if dev    else "—"
    col_delta   = fmt_delta(latest, dev) if (latest and dev) else "—"
    col_uploads = f"{fmt_uploads(latest)} / {fmt_uploads(dev)}"
    col_issues  = f"{fmt_issues(latest)} / {fmt_issues(dev)}"

    lines.append(f"| {bench} | {jdk} | {col_latest} | {col_dev} | {col_delta} | {col_uploads} | {col_issues} |")

print("\n".join(lines))
PYEOF
) || true

[ -n "${RELIABILITY_TABLE}" ] && SECTIONS="${SECTIONS}
${RELIABILITY_TABLE}
"

if [ -z "${SECTIONS}" ]; then
  echo "No benchmark reports found under ${REPORTS_DIR} — skipping comment"
  exit 0
fi

BODY_FILE=$(mktemp)
trap 'rm -f "${BODY_FILE}"' EXIT
cat > "${BODY_FILE}" <<EOF
## Benchmark Results

Pipeline: ${CI_PIPELINE_URL:-}  Commit: \`${DDPROF_COMMIT_SHA:-unknown}\`

${SECTIONS}
EOF

"${HERE}/../scripts/upsert-github-pr-comment.sh" \
  "benchmark-results" "${DDPROF_COMMIT_BRANCH:-}" "${BODY_FILE}"
