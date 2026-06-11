#!/usr/bin/env bash
# Post aggregated reliability + chaos test results as a single PR comment.
#
# Reads REASON_* variables written to build.env by the reliability/chaos jobs
# and emits a ✅/❌ matrix with failure <details> blocks.
#
# Required env:
#   DDPROF_COMMIT_BRANCH  – branch name used to locate the open PR
#   CI_JOB_TOKEN          – used to clone benchmarking-platform if needed
# Optional env:
#   CI_PIPELINE_URL

set -euo pipefail

REPO="DataDog/java-profiler"

# Skip for main / unset branches
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

# ── Collect failures from REASON_* env vars ────────────────────────────────────
rel_fail=0; rel_failures=""
chaos_fail=0; chaos_failures=""

for key in $(compgen -v | grep -E '^REASON_.*X(jit|memory)$' | sort); do
  reason="${!key}"
  label="${key#REASON_}"
  rel_fail=$((rel_fail + 1))
  detail=$(printf '%s' "${reason//\`/}" | tr ';' '\n')
  rel_failures="${rel_failures}
<details><summary>❌ ${label//_/ }</summary>

\`\`\`
${detail}
\`\`\`

</details>"
done

for key in $(compgen -v | grep -E '^REASON_.*Xchaos$' | sort); do
  reason="${!key}"
  label="${key#REASON_}"
  chaos_fail=$((chaos_fail + 1))
  detail=$(printf '%s' "${reason//\`/}" | tr ';' '\n')
  chaos_failures="${chaos_failures}
<details><summary>❌ chaos: ${label//_/ }</summary>

\`\`\`
${detail}
\`\`\`

</details>"
done

# ── Assemble comment ────────────────────────────────────────────────────────────
total_fail=$((rel_fail + chaos_fail))
if [ "${total_fail}" -gt 0 ]; then
  overall="❌ **${total_fail} failure(s) detected**"
else
  overall="✅ **All reliability & chaos checks passed**"
fi

COMMENT_BODY="## Reliability & Chaos Results

${overall}  Pipeline: ${CI_PIPELINE_URL:-}
${rel_failures}${chaos_failures}"

echo "${COMMENT_BODY}" | pr-commenter \
  --for-repo="${REPO}" \
  --for-pr="${DDPROF_COMMIT_BRANCH}" \
  --header="Reliability & Chaos" \
  --on-duplicate=replace
