#!/bin/bash

# generate-run-json.sh - Generate run JSON for integration tests
#
# Usage: generate-run-json.sh [results-dir] [--verbose]
#
# Parses all test configuration directories and outputs a JSON object
# suitable for update-history.sh. Reads CI environment variables for metadata.
#
# Pure bash implementation - no Python required

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="${SCRIPT_DIR}/../.."

# Parse arguments
VERBOSE=false
RESULTS_BASE=""
for arg in "$@"; do
  case "$arg" in
    --verbose)
      VERBOSE=true
      ;;
    *)
      RESULTS_BASE="$arg"
      ;;
  esac
done

# Default results base if not provided
RESULTS_BASE="${RESULTS_BASE:-${PROJECT_ROOT}/integration-test-results}"

# Read metadata from environment or defaults
TIMESTAMP=$(date -u +"%Y-%m-%dT%H:%M:%SZ")
PIPELINE_ID="${CI_PIPELINE_ID:-0}"
PIPELINE_URL="${CI_PIPELINE_URL:-#}"
DDPROF_BRANCH="${DDPROF_COMMIT_BRANCH:-main}"
DDPROF_SHA="${DDPROF_COMMIT_SHA:-$(cat "${PROJECT_ROOT}/ddprof-commit-sha.txt" 2>/dev/null || echo unknown)}"

# Read version from version.txt if available
LIB_VERSION="unknown"
if [ -f "${PROJECT_ROOT}/version.txt" ]; then
  LIB_VERSION=$(awk -F: '{print $NF}' "${PROJECT_ROOT}/version.txt" | tr -d ' ')
fi

# Lookup PR for branch
PR_JSON="{}"
if [ -x "${SCRIPT_DIR}/../common/lookup-pr.sh" ]; then
  PR_JSON=$("${SCRIPT_DIR}/../common/lookup-pr.sh" "${DDPROF_BRANCH}" 2>/dev/null) || PR_JSON="{}"
fi

# Parse validation log for status
parse_validation_log() {
  local log_path="$1"

  if [ ! -f "$log_path" ]; then
    [ "$VERBOSE" = "true" ] && echo "[DEBUG] Log not found: $log_path" >&2
    echo "missing"
    return
  fi

  if grep -q "SUCCESS: All validations passed" "$log_path" 2>/dev/null; then
    [ "$VERBOSE" = "true" ] && echo "[DEBUG] ✓ PASSED: $log_path" >&2
    echo "passed"
  elif grep -q "VALIDATION_FAILED" "$log_path" 2>/dev/null; then
    [ "$VERBOSE" = "true" ] && echo "[DEBUG] ✗ FAILED: $log_path" >&2
    echo "failed"
  else
    # Log exists but has no status markers - this is the problem!
    echo "[WARN] Log missing markers: $log_path" >&2
    if [ "$VERBOSE" = "true" ]; then
      echo "[DEBUG] Log preview (first 10 lines):" >&2
      head -10 "$log_path" >&2
      echo "[DEBUG] Log preview (last 10 lines):" >&2
      tail -10 "$log_path" >&2
    fi
    echo "unknown"
  fi
}

# Initialize counters
total_jobs=0
passed_jobs=0
failed_jobs=0
total_scenarios=0
passed_scenarios=0
failed_scenarios=0
unknown_scenarios=0
failed_configs=""

# Parse test results if directory exists
if [ -d "${RESULTS_BASE}" ]; then
  for config_dir in "${RESULTS_BASE}"/*; do
    [ -d "$config_dir" ] || continue

    config_name=$(basename "$config_dir")
    [ "$VERBOSE" = "true" ] && echo "[DEBUG] Processing config: $config_name" >&2

    # Skip history directory
    [ "$config_name" = "history" ] && continue

    # Skip if no log files
    [ -z "$(ls "$config_dir"/*.log 2>/dev/null)" ] && continue

    total_jobs=$((total_jobs + 1))

    # Check profiler-only scenario
    s1_log="${config_dir}/profiler-only-${config_name}.log"
    s1_status=$(parse_validation_log "$s1_log")

    # Check tracer+profiler scenario
    s2_log="${config_dir}/tracer-profiler-${config_name}.log"
    s2_status=$(parse_validation_log "$s2_log")

    # Count scenarios
    for status in "$s1_status" "$s2_status"; do
      if [ "$status" != "missing" ]; then
        total_scenarios=$((total_scenarios + 1))
        if [ "$status" = "passed" ]; then
          passed_scenarios=$((passed_scenarios + 1))
        elif [ "$status" = "failed" ]; then
          failed_scenarios=$((failed_scenarios + 1))
        elif [ "$status" = "unknown" ]; then
          unknown_scenarios=$((unknown_scenarios + 1))
        fi
      fi
    done

    # Determine job status
    if [ "$s1_status" = "passed" ] && [ "$s2_status" = "passed" ]; then
      passed_jobs=$((passed_jobs + 1))
    else
      failed_jobs=$((failed_jobs + 1))
      failed_configs="${failed_configs}${failed_configs:+, }\"${config_name}\""
    fi
  done
fi

# Report diagnostic summary to stderr
if [ $unknown_scenarios -gt 0 ]; then
  echo "" >&2
  echo "[ERROR] ================================================" >&2
  echo "[ERROR] Found $unknown_scenarios scenario(s) with logs but NO status markers!" >&2
  echo "[ERROR] ================================================" >&2
  echo "[ERROR]" >&2
  echo "[ERROR] This means validation logs exist but don't contain:" >&2
  echo "[ERROR]   - 'SUCCESS: All validations passed'" >&2
  echo "[ERROR]   - 'VALIDATION_FAILED'" >&2
  echo "[ERROR]" >&2
  echo "[ERROR] Likely causes:" >&2
  echo "[ERROR]   1. Validation script crashed before completion" >&2
  echo "[ERROR]   2. jbang/jfr-shell failed to run" >&2
  echo "[ERROR]   3. Process killed/timeout before markers written" >&2
  echo "[ERROR]" >&2
  echo "[ERROR] Check the logs above for '[WARN] Log missing markers:'" >&2
  echo "[ERROR] ================================================" >&2
  echo "" >&2
fi

if [ "$VERBOSE" = "true" ]; then
  echo "[DEBUG] Counters: total_jobs=$total_jobs, passed_jobs=$passed_jobs, failed_jobs=$failed_jobs" >&2
  echo "[DEBUG] Scenarios: total=$total_scenarios, passed=$passed_scenarios, failed=$failed_scenarios, unknown=$unknown_scenarios" >&2
  echo "[INFO] Parsing summary:" >&2
  echo "[INFO]   Total configs found: $total_jobs" >&2
  echo "[INFO]   Total scenarios: $total_scenarios" >&2
  echo "[INFO]   Passed: $passed_scenarios" >&2
  echo "[INFO]   Failed: $failed_scenarios" >&2
  echo "[INFO]   Unknown: $unknown_scenarios" >&2
  echo "" >&2
fi

# Determine overall status
if [ $failed_jobs -eq 0 ] && [ $total_jobs -gt 0 ]; then
  status="passed"
elif [ $passed_jobs -eq 0 ] && [ $total_jobs -gt 0 ]; then
  status="failed"
elif [ $total_jobs -eq 0 ]; then
  status="unknown"
else
  status="partial"
fi

# Extract PR number if available
pr_field="null"
if command -v jq >/dev/null 2>&1; then
  pr_number=$(echo "$PR_JSON" | jq -r '.number // empty' 2>/dev/null || echo "")
  if [ -n "$pr_number" ]; then
    pr_field="$PR_JSON"
  fi
else
  # Fallback: simple grep for number field
  if echo "$PR_JSON" | grep -q '"number"'; then
    pr_field="$PR_JSON"
  fi
fi

# Generate JSON (without jq dependency for maximum compatibility)
cat <<EOF
{
  "id": "$PIPELINE_ID",
  "timestamp": "$TIMESTAMP",
  "ddprof_branch": "$DDPROF_BRANCH",
  "ddprof_sha": "$DDPROF_SHA",
  "ddprof_pr": $pr_field,
  "pipeline": {
    "id": "$PIPELINE_ID",
    "url": "$PIPELINE_URL"
  },
  "lib_version": "$LIB_VERSION",
  "status": "$status",
  "summary": {
    "total_jobs": $total_jobs,
    "passed_jobs": $passed_jobs,
    "failed_jobs": $failed_jobs,
    "total_scenarios": $total_scenarios,
    "passed_scenarios": $passed_scenarios,
    "failed_scenarios": $failed_scenarios,
    "unknown_scenarios": $unknown_scenarios,
    "failed_configs": [$failed_configs]
  }
}
EOF
