#!/usr/bin/env bash
# Post aggregated benchmark comparison results as a single PR comment.
#
# Expects all per-cell comparison-baseline-vs-candidate_*.md reports to be
# present under REPORTS_DIR (default: reports/).
#
# Required env:
#   DDPROF_COMMIT_BRANCH  – branch name used to locate the open PR
#   CI_JOB_TOKEN          – used to clone benchmarking-platform if needed
# Optional env:
#   CI_PIPELINE_URL, DDPROF_COMMIT_SHA

set -euo pipefail

REPORTS_DIR="${1:-reports}"
REPO="DataDog/java-profiler"

# Skip for main / unset branches (no PR to comment on)
if [ -z "${DDPROF_COMMIT_BRANCH:-}" ] || \
   [ "${DDPROF_COMMIT_BRANCH}" = "main" ] || \
   [ "${DDPROF_COMMIT_BRANCH}" = "master" ]; then
  echo "Skipping PR comment for branch: ${DDPROF_COMMIT_BRANCH:-<unset>}"
  exit 0
fi

# Acquire pr-commenter from benchmarking-platform if not already on PATH
if ! command -v pr-commenter >/dev/null 2>&1; then
  PLATFORM_DIR=$(mktemp -d)
  trap "rm -rf ${PLATFORM_DIR}" EXIT
  git -c url."https://gitlab-ci-token:${CI_JOB_TOKEN}@gitlab.ddbuild.io/DataDog/".insteadOf="https://github.com/DataDog/" \
    clone --depth 1 --branch dd-trace-go https://github.com/DataDog/benchmarking-platform "${PLATFORM_DIR}"
  export PATH="${PLATFORM_DIR}/tools:${PATH}"
fi

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

COMMENT_BODY="## Benchmark Results

Pipeline: ${CI_PIPELINE_URL:-}  Commit: \`${DDPROF_COMMIT_SHA:-unknown}\`

${SECTIONS}"

echo "${COMMENT_BODY}" | pr-commenter \
  --for-repo="${REPO}" \
  --for-pr="${DDPROF_COMMIT_BRANCH}" \
  --header="Benchmarks" \
  --on-duplicate=replace
