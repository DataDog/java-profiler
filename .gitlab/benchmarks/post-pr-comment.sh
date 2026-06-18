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

lines = [
    "### Reliability Benchmarks",
    "",
    "| Benchmark | JDK | Latest | Dev |",
    "|-----------|-----|--------|-----|",
]
for (bench, jdk) in sorted(results.keys()):
    libs = results[(bench, jdk)]

    def fmt(lib):
        if lib not in libs:
            return "—"
        r = libs[lib]
        icon = "💥" if r.get("crashed") else "✅"
        avg = r.get("avg_ms", 0)
        cnt = r.get("run_count", 0)
        return f"{icon} {avg} ms ({cnt} iters)"

    lines.append(f"| {bench} | {jdk} | {fmt('latest')} | {fmt('dev')} |")

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
