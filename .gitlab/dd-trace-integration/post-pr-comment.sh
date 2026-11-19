#!/bin/bash
# Copyright 2026, Datadog, Inc.

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
#
# Reads the integration quarantine list (.gitlab/dd-trace-integration/quarantine.txt,
# see quarantine-lib.sh for the format). A quarantined scenario's validation
# failure is rendered as quarantined and does not turn this job red; every
# other failure path still does. QUARANTINE_LIST overrides the list path (the
# unit tests use this to inject temporary lists).

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

# shellcheck disable=SC1091  # source path is computed at runtime
. "${HERE}/quarantine-lib.sh"

QUARANTINE_LIST="${QUARANTINE_LIST:-$(quarantine_default_list)}"
quarantine_load "${QUARANTINE_LIST}"

# Dashboard URL (GitHub Pages)
DASHBOARD_URL="https://datadog.github.io/java-profiler/integration/"

# The matrix comes from quarantine-lib.sh, which also validates quarantine cell
# globs against the same set. Not-applicable platforms stay visible in the table
# but are excluded from completeness and pass/fail counts (EXPECTED is counted below).
PLATFORMS=("${QUARANTINE_PLATFORMS[@]}")
JDKS=("${QUARANTINE_JDKS[@]}")
NOT_APPLICABLE_REASON="OpenJ9 requires glibc; upstream publishes no musl runtime."

is_not_applicable() {
  case "$1" in
    musl-x64-openj9|musl-arm64-openj9) return 0 ;;
    *) return 1 ;;
  esac
}

log_info "Collecting results for branch: ${DDPROF_COMMIT_BRANCH:-<unset>}"

# Collect test results
log_info "Collecting test results from ${RESULTS_DIR}..."

# Config -> status map, kept as parallel indexed arrays: macOS /bin/bash is
# 3.2, which has no associative arrays (no 'declare -A').
RESULT_CONFIGS=()
RESULT_STATUSES=()

# Records (or overwrites) the status of <config>.
result_set() {
  local i
  if [ "${#RESULT_CONFIGS[@]}" -eq 0 ]; then
    RESULT_CONFIGS+=("$1")
    RESULT_STATUSES+=("$2")
    return 0
  fi
  for i in "${!RESULT_CONFIGS[@]}"; do
    if [ "${RESULT_CONFIGS[${i}]}" = "$1" ]; then
      RESULT_STATUSES[i]="$2"
      return 0
    fi
  done
  RESULT_CONFIGS+=("$1")
  RESULT_STATUSES+=("$2")
}

# Prints the status recorded for <config>, or nothing when none was recorded.
result_get() {
  local i
  if [ "${#RESULT_CONFIGS[@]}" -eq 0 ]; then
    return 0
  fi
  for i in "${!RESULT_CONFIGS[@]}"; do
    if [ "${RESULT_CONFIGS[${i}]}" = "$1" ]; then
      printf '%s' "${RESULT_STATUSES[${i}]}"
      return 0
    fi
  done
}

TOTAL_PASS=0
TOTAL_FAIL=0
TOTAL_QUARANTINED=0
FAILURES=""
QUARANTINED_ENTRIES=""

# Downgrades a plain validation failure to "quarantined" when an unexpired
# entry covers this cell and scenario; an expired entry never matches, so the
# failure gates again. Quarantine details collect into QUAR_CFG_ENTRIES with
# real newlines - never escape sequences - so the free-text reason cannot be
# mangled by any later expansion; the comment body appends the block verbatim.
scenario_status() {
  local config="$1" scenario="$2" status="$3"
  local q
  if [ "${status}" = "fail" ] && q=$(quarantine_find "${config}" "${scenario}"); then
    QUAR_CFG_ENTRIES+="- \`${config}/${scenario}\` — ${QUARANTINE_TICKETS[${q}]}, review_by ${QUARANTINE_REVIEW_BY[${q}]}, ${QUARANTINE_REASONS[${q}]}"$'\n'
    SCENARIO_STATUS_OUT="quarantined"
  else
    SCENARIO_STATUS_OUT="${status}"
  fi
}

for config_dir in "${RESULTS_DIR}"/*; do
  [ -d "${config_dir}" ] || continue
  config_name=$(basename "${config_dir}")
  # Stale artifacts must not turn a not-scheduled combination into test coverage.
  if is_not_applicable "${config_name%-jdk*}"; then
    continue
  fi

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

  QUAR_CFG_ENTRIES=""
  scenario_status "${config_name}" "profiler-only" "${s1_status}"
  s1_status="${SCENARIO_STATUS_OUT}"
  scenario_status "${config_name}" "tracer-profiler" "${s2_status}"
  s2_status="${SCENARIO_STATUS_OUT}"

  # Cell status, in order: a plain failure gates even next to a quarantined
  # or unreadable scenario, and a quarantined scenario never masks the
  # other scenario's missing log (the fail/unknown ordering is load-bearing).
  if [ "${s1_status}" = "fail" ] || [ "${s2_status}" = "fail" ]; then
    result_set "${config_name}" "fail"
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
  elif [ "${s1_status}" = "unknown" ] || [ "${s2_status}" = "unknown" ]; then
    result_set "${config_name}" "unknown"
  elif [ "${s1_status}" = "quarantined" ] || [ "${s2_status}" = "quarantined" ]; then
    result_set "${config_name}" "quarantined"
    TOTAL_QUARANTINED=$((TOTAL_QUARANTINED + 1))
  else
    result_set "${config_name}" "pass"
    TOTAL_PASS=$((TOTAL_PASS + 1))
  fi
  # Quarantined details are reported whatever the cell's gating outcome; the
  # cell still gates. QUAR_CFG_ENTRIES is empty unless a failing scenario
  # matched an unexpired entry, so pass cells append nothing; unknown and
  # gating cells append the matched scenario's bullet.
  QUARANTINED_ENTRIES+="${QUAR_CFG_ENTRIES}"
done

# Quarantined scenarios are observed results too: a run whose only outcomes
# are quarantined (every cell otherwise incomplete, so TOTAL is 0) must still
# render its quarantine details, not the "no results were produced" branch.
TOTAL=$((TOTAL_PASS + TOTAL_FAIL + TOTAL_QUARANTINED))

# Missing or unreadable logs for applicable cells must fail, including when
# setup failure leaves no artifact directory for the collection loop to see.
EXPECTED=0
TOTAL_NOT_APPLICABLE=0
TOTAL_INCOMPLETE=0
INCOMPLETE_CONFIGS=""
for platform in "${PLATFORMS[@]}"; do
  for jdk in "${JDKS[@]}"; do
    config="${platform}-jdk${jdk}"
    if is_not_applicable "${platform}"; then
      result_set "${config}" "not-applicable"
      TOTAL_NOT_APPLICABLE=$((TOTAL_NOT_APPLICABLE + 1))
      continue
    fi
    EXPECTED=$((EXPECTED + 1))
    # No recorded status (empty) falls through to the incomplete branch, like
    # the old "missing" sentinel did.
    case "$(result_get "${config}")" in
      pass|fail|quarantined) ;;
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
elif [ "${TOTAL}" -gt 0 ]; then
  OVERALL_STATUS="success"
  STATUS_EMOJI=":white_check_mark:"
else
  # No results at all usually means the test matrix never ran (setup/prerequisite
  # failure) rather than a clean run — treat it as a failure so it isn't silently
  # swallowed.
  OVERALL_STATUS="failure"
  STATUS_EMOJI=":rotating_light:"
fi

log_info "Results: ${TOTAL_PASS} passed, ${TOTAL_FAIL} failed, ${TOTAL_QUARANTINED} quarantined, ${TOTAL_INCOMPLETE} without a result, out of ${EXPECTED} expected configurations; ${TOTAL_NOT_APPLICABLE} not applicable (not scheduled)"
if [ -n "${INCOMPLETE_CONFIGS}" ]; then
  log_warn "No validation log for:${INCOMPLETE_CONFIGS}"
fi
if [ "${TOTAL_QUARANTINED}" -gt 0 ]; then
  log_warn "${TOTAL_QUARANTINED} quarantined cell(s) do not gate this run (see ${QUARANTINE_LIST})"
fi

# Build the comment body
DDPROF_SHA="${DDPROF_COMMIT_SHA:-$(cat ddprof-commit-sha.txt 2>/dev/null || echo unknown)}"

# The matrix header is derived from the same JDKS list that builds the rows
# and drives EXPECTED, so a JDK-list edit cannot mislabel the posted comment.
JDK_HEADER="| Platform |"
JDK_SEPARATOR="|----------|"
for jdk in "${JDKS[@]}"; do
  JDK_HEADER="${JDK_HEADER} JDK ${jdk} |"
  JDK_SEPARATOR="${JDK_SEPARATOR}--------|"
done

if [ "${OVERALL_STATUS}" = "success" ] && [ "${TOTAL_QUARANTINED}" -eq 0 ]; then
  # Every expected configuration passed - keep it short
  COMMENT_BODY=":white_check_mark: **All ${TOTAL_PASS} integration tests passed**

:bar_chart: [Dashboard](${DASHBOARD_URL}) · :construction_worker: [Pipeline](${CI_PIPELINE_URL:-}) · :package: \`${DDPROF_SHA:0:8}\`"
elif [ "${TOTAL}" -eq 0 ] && [ -z "${QUARANTINED_ENTRIES}" ]; then
  # Nothing was observed at all - no pass, fail, or quarantined scenario - so
  # the test matrix itself never ran (e.g. a setup or prerequisite failure),
  # not a clean pass/fail outcome.
  COMMENT_BODY=":rotating_light: **Integration tests could not run — no results were produced**

No applicable configuration in \`${RESULTS_DIR}\` produced a pass/fail result.
Check the pipeline logs for setup or validation failures.

:construction_worker: [Pipeline](${CI_PIPELINE_URL:-}) · :package: \`${DDPROF_SHA:0:8}\`"
else
  # Some failures, unknowns or quarantined results - show full matrix
  # Use the applicable matrix denominator so missing results cannot shrink it.
  HEADLINE="${STATUS_EMOJI} **${TOTAL_PASS}** passed, **${TOTAL_FAIL}** failed"
  if [ "${TOTAL_QUARANTINED}" -gt 0 ]; then
    HEADLINE="${HEADLINE}, **${TOTAL_QUARANTINED}** quarantined"
  fi
  if [ "${TOTAL_INCOMPLETE}" -gt 0 ]; then
    HEADLINE="${HEADLINE}, **${TOTAL_INCOMPLETE}** without a result"
  fi
  HEADLINE="${HEADLINE} out of **${EXPECTED}** expected configurations"

  COMMENT_BODY="${HEADLINE}

### Test Matrix

${JDK_HEADER}
${JDK_SEPARATOR}"

  # Build matrix rows
  for platform in "${PLATFORMS[@]}"; do
    row="| ${platform} |"
    for jdk in "${JDKS[@]}"; do
      config="${platform}-jdk${jdk}"
      status="$(result_get "${config}")"
      case "${status}" in
        pass) row="${row} :white_check_mark: |" ;;
        fail) row="${row} :x: |" ;;
        not-applicable) row="${row} N/A |" ;;
        quarantined) row="${row} :shield: |" ;;
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

  # Quarantined scenario failures: reported, with ticket and expiry, but not
  # gating; on a green run this section is the quarantine's only visibility.
  if [ -n "${QUARANTINED_ENTRIES}" ]; then
    COMMENT_BODY="${COMMENT_BODY}

### Quarantined failures
These scenarios failed and are quarantined in \`.gitlab/dd-trace-integration/quarantine.txt\`.
A quarantined scenario does not turn this pipeline red by itself; a cell still
gates when its other scenario fails or produced no result. Each quarantine
expires on its review_by date; the intended exit is a fix and a deleted line.
"
    COMMENT_BODY="${COMMENT_BODY}${QUARANTINED_ENTRIES}"
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

COMMENT_BODY="${COMMENT_BODY}

**${TOTAL_NOT_APPLICABLE} not applicable (not scheduled)**: musl/OpenJ9 on x64 and arm64. ${NOT_APPLICABLE_REASON}"

# Post comment via dd-octo-sts (upsert-github-pr-comment.sh handles missing
# branch/PR/token gracefully, so a comment-posting problem never masks the
# actual test outcome below).
# COMMENT_BODY_FILE lets a caller keep the rendered body instead of a temp file
# it never sees; the unit tests assert on it.
if [ -n "${COMMENT_BODY_FILE:-}" ]; then
  BODY_FILE="${COMMENT_BODY_FILE}"
else
  BODY_FILE=$(mktemp)
  trap 'rm -f "${BODY_FILE}"' EXIT
fi
echo "${COMMENT_BODY}" > "${BODY_FILE}"
if ! "${HERE}/../scripts/upsert-github-pr-comment.sh" \
    "dd-trace-integration-results" "${DDPROF_COMMIT_BRANCH:-}" "${BODY_FILE}"; then
  log_error "Failed to post PR comment (transport failure) — continuing; only the test outcome below determines pipeline status"
fi

# Exit with failure if tests failed (makes pipeline fail). Quarantined
# scenario failures are not in TOTAL_FAIL, so they do not gate; every other
# failure path does.
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
