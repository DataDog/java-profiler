#!/usr/bin/env bash
# Post aggregated benchmark comparison results as a single PR comment.
#
# Expects all per-cell comparison-baseline-vs-candidate_*.md reports to be
# present under REPORTS_DIR (default: reports/).
#
# Required env:
#   DDPROF_COMMIT_BRANCH  – branch name used to locate the open PR
# Optional env:
#   CI_PIPELINE_URL, DDPROF_COMMIT_SHA

set -euo pipefail

REPORTS_DIR="${1:-reports}"
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Aggregate all per-cell reports into a single comment body
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
