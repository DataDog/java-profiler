#!/bin/bash

# post-pr-comment.sh - Post integration test results as PR comment
#
# Usage: post-pr-comment.sh <results-dir>
#
# Posts a formatted comment to the java-profiler PR with:
# - Pass/fail summary with badges
# - Test matrix results
# - Link to full dashboard
# - Failure details if any
#
# Requires:
# - DDPROF_COMMIT_BRANCH: Branch name to find PR
# - CI_PIPELINE_URL: Link to pipeline
# - dd-octo-sts CLI (for GitHub token exchange, via upsert-github-pr-comment.sh)

set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Colors for logging
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

log_info() { echo -e "${GREEN}[INFO]${NC} $*" >&2; }
log_warn() { echo -e "${YELLOW}[WARN]${NC} $*" >&2; }
log_error() { echo -e "${RED}[ERROR]${NC} $*" >&2; }

RESULTS_DIR="${1:-integration-test-results}"

# Dashboard URL (GitHub Pages)
DASHBOARD_URL="https://datadog.github.io/java-profiler/integration/"

# The matrix this run is expected to cover. Declared once: it drives both the
# completeness check and the table rendering below, so the two cannot drift.
PLATFORMS=(
  glibc-x64-hotspot glibc-x64-openj9 glibc-arm64-hotspot glibc-arm64-openj9
  musl-x64-hotspot musl-x64-openj9 musl-arm64-hotspot musl-arm64-openj9
)
JDKS=(8 11 17 21 25)
EXPECTED=$(( ${#PLATFORMS[@]} * ${#JDKS[@]} ))

log_info "Collecting results for branch: ${DDPROF_COMMIT_BRANCH:-<unset>}"

# Collect test results
log_info "Collecting test results from ${RESULTS_DIR}..."

declare -A RESULTS
TOTAL_PASS=0
TOTAL_FAIL=0
FAILURES=""

for config_dir in "${RESULTS_DIR}"/*; do
  [ -d "${config_dir}" ] || continue
  config_name=$(basename "${config_dir}")

  # Check validation logs for pass/fail
  s1_status="unknown"
  s2_status="unknown"

  # Scenario 1: profiler-only
  s1_log="${config_dir}/profiler-only-${config_name}.log"
  if [ -f "${s1_log}" ]; then
    if grep -q "SUCCESS:" "${s1_log}" 2>/dev/null; then
      s1_status="pass"
    elif grep -q "VALIDATION_FAILED" "${s1_log}" 2>/dev/null; then
      s1_status="fail"
    fi
  fi

  # Scenario 2: tracer+profiler
  s2_log="${config_dir}/tracer-profiler-${config_name}.log"
  if [ -f "${s2_log}" ]; then
    if grep -q "SUCCESS:" "${s2_log}" 2>/dev/null; then
      s2_status="pass"
    elif grep -q "VALIDATION_FAILED" "${s2_log}" 2>/dev/null; then
      s2_status="fail"
    fi
  fi

  # Determine overall status for this config
  if [ "${s1_status}" = "pass" ] && [ "${s2_status}" = "pass" ]; then
    RESULTS["${config_name}"]="pass"
    TOTAL_PASS=$((TOTAL_PASS + 1))
  elif [ "${s1_status}" = "fail" ] || [ "${s2_status}" = "fail" ]; then
    RESULTS["${config_name}"]="fail"
    TOTAL_FAIL=$((TOTAL_FAIL + 1))
    # Collect failure details
    FAILURES="${FAILURES}\n<details><summary>${config_name}</summary>\n\n"
    if [ "${s1_status}" = "fail" ] && [ -f "${s1_log}" ]; then
      FAILURES="${FAILURES}**Profiler-only:**\n\`\`\`\n$(tail -20 "${s1_log}")\n\`\`\`\n"
    fi
    if [ "${s2_status}" = "fail" ] && [ -f "${s2_log}" ]; then
      FAILURES="${FAILURES}**Tracer+profiler:**\n\`\`\`\n$(tail -20 "${s2_log}")\n\`\`\`\n"
    fi
    FAILURES="${FAILURES}</details>\n"
  else
    RESULTS["${config_name}"]="unknown"
  fi
done

TOTAL=$((TOTAL_PASS + TOTAL_FAIL))

# A configuration that produced no readable validation log is not a pass. Its
# job may have timed out, lost its runner, or failed in setup before writing
# one, which leaves its artifact directory empty -- or absent entirely, in
# which case the collection loop above never sees it. Walk the expected matrix
# so both shapes are caught, and gate on them: without this, 39 passes and one
# timed-out cell reports success.
TOTAL_INCOMPLETE=0
INCOMPLETE_CONFIGS=""
for platform in "${PLATFORMS[@]}"; do
  for jdk in "${JDKS[@]}"; do
    config="${platform}-jdk${jdk}"
    case "${RESULTS[${config}]:-missing}" in
      pass|fail) ;;
      *)
        TOTAL_INCOMPLETE=$((TOTAL_INCOMPLETE + 1))
        INCOMPLETE_CONFIGS="${INCOMPLETE_CONFIGS} ${config}"
        ;;
    esac
  done
done

# Determine overall status
if [ "${TOTAL_FAIL}" -gt 0 ] || [ "${TOTAL_INCOMPLETE}" -gt 0 ]; then
  OVERALL_STATUS="failure"
  STATUS_EMOJI=":x:"
  STATUS_TEXT="FAILED"
elif [ "${TOTAL_PASS}" -gt 0 ]; then
  OVERALL_STATUS="success"
  STATUS_EMOJI=":white_check_mark:"
  STATUS_TEXT="PASSED"
else
  # No results at all usually means the test matrix never ran (setup/prerequisite
  # failure) rather than a clean run — treat it as a failure so it isn't silently
  # swallowed.
  OVERALL_STATUS="failure"
  STATUS_EMOJI=":rotating_light:"
  STATUS_TEXT="COULD NOT RUN"
fi

log_info "Results: ${TOTAL_PASS} passed, ${TOTAL_FAIL} failed, ${TOTAL_INCOMPLETE} without a result, out of ${EXPECTED} expected configurations"
if [ -n "${INCOMPLETE_CONFIGS}" ]; then
  log_warn "No validation log for:${INCOMPLETE_CONFIGS}"
fi

# Build the comment body
DDPROF_SHA="${DDPROF_COMMIT_SHA:-$(cat ddprof-commit-sha.txt 2>/dev/null || echo unknown)}"

if [ "${OVERALL_STATUS}" = "success" ]; then
  # Every expected configuration passed - keep it short
  COMMENT_BODY=":white_check_mark: **All ${TOTAL_PASS} integration tests passed**

:bar_chart: [Dashboard](${DASHBOARD_URL}) · :construction_worker: [Pipeline](${CI_PIPELINE_URL:-}) · :package: \`${DDPROF_SHA:0:8}\`"
elif [ "${TOTAL}" -eq 0 ]; then
  # No results produced at all - the test matrix itself never ran (e.g. a setup
  # or prerequisite failure), not a clean pass/fail outcome.
  COMMENT_BODY=":rotating_light: **Integration tests could not run — no results were produced**

The test matrix in \`${RESULTS_DIR}\` is empty. This usually means a setup step
(prerequisite installation, JDK provisioning, etc.) failed before any test could run.

:construction_worker: [Pipeline](${CI_PIPELINE_URL:-}) · :package: \`${DDPROF_SHA:0:8}\`"
else
  # Some failures or unknowns - show full matrix
  COMMENT_BODY="${STATUS_EMOJI} **${TOTAL_PASS}** passed, **${TOTAL_FAIL}** failed out of **${TOTAL}** configurations

### Test Matrix

| Platform | JDK 8 | JDK 11 | JDK 17 | JDK 21 | JDK 25 |
|----------|-------|--------|--------|--------|--------|"

  # Build matrix rows
  for platform in "${PLATFORMS[@]}"; do
    row="| ${platform} |"
    for jdk in "${JDKS[@]}"; do
      config="${platform}-jdk${jdk}"
      status="${RESULTS[${config}]:-unknown}"
      case "${status}" in
        pass) row="${row} :white_check_mark: |" ;;
        fail) row="${row} :x: |" ;;
        *) row="${row} :grey_question: |" ;;
      esac
    done
    COMMENT_BODY="${COMMENT_BODY}
${row}"
  done

  # Call out configurations that produced no result at all: a grey cell is not
  # a pass, and the reason is not in any validation log.
  if [ -n "${INCOMPLETE_CONFIGS}" ]; then
    COMMENT_BODY="${COMMENT_BODY}

### No result produced
These configurations wrote no validation log, so their outcome is unknown and
they are counted as failures. The job usually timed out or failed during setup;
see its log in the pipeline.
"
    for config in ${INCOMPLETE_CONFIGS}; do
      COMMENT_BODY="${COMMENT_BODY}
- \`${config}\`"
    done
  fi

  # Add failure details if any
  if [ -n "${FAILURES}" ]; then
    COMMENT_BODY="${COMMENT_BODY}

### Failure Details
$(echo -e "${FAILURES}")"
  fi

  # Add links
  COMMENT_BODY="${COMMENT_BODY}

### Links
- :bar_chart: [Full Dashboard](${DASHBOARD_URL})
- :construction_worker: [Pipeline](${CI_PIPELINE_URL:-})
- :package: Commit: \`${DDPROF_SHA}\`"
fi

# Post comment via dd-octo-sts (upsert-github-pr-comment.sh handles missing
# branch/PR/token gracefully, so a comment-posting problem never masks the
# actual test outcome below).
BODY_FILE=$(mktemp)
trap 'rm -f "${BODY_FILE}"' EXIT
echo "${COMMENT_BODY}" > "${BODY_FILE}"
if ! "${HERE}/../scripts/upsert-github-pr-comment.sh" \
    "dd-trace-integration-results" "${DDPROF_COMMIT_BRANCH:-}" "${BODY_FILE}"; then
  log_error "Failed to post PR comment (transport failure) — continuing; only the test outcome below determines pipeline status"
fi

# Exit with failure if tests failed (makes pipeline fail)
if [ "${OVERALL_STATUS}" = "failure" ]; then
  if [ "${TOTAL_FAIL}" -gt 0 ]; then
    log_error "${TOTAL_FAIL} integration test(s) failed - marking pipeline as failed"
  fi
  if [ "${TOTAL_INCOMPLETE}" -gt 0 ]; then
    log_error "${TOTAL_INCOMPLETE} configuration(s) produced no result - marking pipeline as failed"
  fi
  exit 1
fi

exit 0
