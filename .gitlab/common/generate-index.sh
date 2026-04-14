#!/bin/bash

# generate-index.sh - Generate test type index page with expandable details
#
# Usage: generate-index.sh <test-type> [work-dir]
#
# test-type: integration|benchmarks|reliability
# Reads _data/{test-type}.json and generates {test-type}/index.md
#
# Pure bash/jq implementation - no Python required

set -euo pipefail

TEST_TYPE="${1:-}"
WORK_DIR="${2:-.}"

if [ -z "${TEST_TYPE}" ]; then
  echo "Usage: generate-index.sh <test-type> [work-dir]" >&2
  exit 1
fi

# Check if jq is available
if ! command -v jq >/dev/null 2>&1; then
  echo "Error: jq is required for JSON parsing" >&2
  exit 1
fi

# Ensure output directory exists
mkdir -p "${WORK_DIR}/${TEST_TYPE}"

# Helper functions
status_emoji() {
  case "$1" in
    passed) echo "✅" ;;
    failed) echo "❌" ;;
    partial) echo "⚠️" ;;
    *) echo "❓" ;;
  esac
}

format_pr_link() {
  local pr_json="$1"
  if [ "$pr_json" != "null" ] && [ -n "$pr_json" ]; then
    local number=$(echo "$pr_json" | jq -r '.number // empty')
    local url=$(echo "$pr_json" | jq -r '.url // empty')
    if [ -n "$number" ]; then
      echo "[#${number}](${url})"
      return
    fi
  fi
  echo "-"
}

format_pipeline_link() {
  local pipeline_json="$1"
  if [ "$pipeline_json" != "null" ]; then
    local id=$(echo "$pipeline_json" | jq -r '.id // empty')
    local url=$(echo "$pipeline_json" | jq -r '.url // "#"')
    if [ -n "$id" ]; then
      echo "[#${id}](${url})"
      return
    fi
  fi
  echo "-"
}

# Test type metadata
case "$TEST_TYPE" in
  integration)
    TITLE="DD-Trace Integration Test History"
    DESCRIPTION="Tests dd-trace-java compatibility with ddprof across multiple JDK versions and platforms."
    ;;
  benchmarks)
    TITLE="Benchmark Test History"
    DESCRIPTION="Performance regression testing using Renaissance benchmark suite."
    ;;
  reliability)
    TITLE="Reliability Test History"
    DESCRIPTION="Long-running stability tests for memory leaks and crashes."
    ;;
  *)
    # Capitalize first letter
    cap_type="$(echo "${TEST_TYPE:0:1}" | tr '[:lower:]' '[:upper:]')${TEST_TYPE:1}"
    TITLE="${cap_type} Test History"
    DESCRIPTION=""
    ;;
esac

# Generate the index page
{
cat <<EOF_HEADER
---
layout: default
title: ${TITLE}
---

# ${TITLE}

[← Back to Dashboard](../)

${DESCRIPTION}

## Last 10 Runs

EOF_HEADER

# Load history
history_file="${WORK_DIR}/_data/${TEST_TYPE}.json"

if [ -f "$history_file" ] && [ -s "$history_file" ]; then
  runs=$(jq -c '.runs[]' "$history_file" 2>/dev/null || echo "")

  if [ -z "$runs" ]; then
    echo "*No test runs recorded yet.*"
  else
    echo "$runs" | while IFS= read -r run; do
      timestamp=$(echo "$run" | jq -r '.timestamp // ""')
      date_str="${timestamp:0:16}"
      date_str="${date_str/T/ }"
      [ -z "$date_str" ] && date_str="Unknown"

      status=$(echo "$run" | jq -r '.status // "unknown"')
      status_symbol=$(status_emoji "$status")
      branch=$(echo "$run" | jq -r '.ddprof_branch // "unknown"')
      version=$(echo "$run" | jq -r '.lib_version // "unknown"')
      sha=$(echo "$run" | jq -r '.ddprof_sha // "unknown"')
      sha="${sha:0:8}"

      pr_info=$(echo "$run" | jq -c '.ddprof_pr // null')
      pipeline=$(echo "$run" | jq -c '.pipeline // null')

      pr_link=$(format_pr_link "$pr_info")
      pipeline_link=$(format_pipeline_link "$pipeline")

      # PR text for summary line
      pr_text=""
      if [ "$pr_info" != "null" ]; then
        pr_num=$(echo "$pr_info" | jq -r '.number // empty')
        if [ -n "$pr_num" ]; then
          pr_text=" | PR $pr_link"
        fi
      fi

      # Print expandable details
      cat <<EOF_RUN
<details markdown="1">
<summary>
<strong>${date_str}</strong> | ${status_symbol} | ${branch}${pr_text} | Pipeline ${pipeline_link}
</summary>

**Version:** ${version}
**Commit:** ${sha}

EOF_RUN

      # Summary table based on test type
      summary=$(echo "$run" | jq -c '.summary // {}')

      case "$TEST_TYPE" in
        integration)
          total_jobs=$(echo "$summary" | jq -r '.total_jobs // "N/A"')
          passed_jobs=$(echo "$summary" | jq -r '.passed_jobs // "N/A"')
          failed_jobs=$(echo "$summary" | jq -r '.failed_jobs // "N/A"')

          echo "| Metric | Value |"
          echo "|--------|-------|"
          echo "| Jobs | $total_jobs |"
          echo "| Passed | $passed_jobs |"
          echo "| Failed | $failed_jobs |"

          # Failed configs
          failed_configs=$(echo "$summary" | jq -r '.failed_configs // [] | join(", ")')
          if [ -n "$failed_configs" ] && [ "$failed_configs" != "" ]; then
            echo ""
            echo "**Failed Configs:** $failed_configs"
          fi
          ;;

        benchmarks)
          architectures=$(echo "$summary" | jq -r '.architectures // "N/A"')
          modes_tested=$(echo "$summary" | jq -r '.modes_tested // "N/A"')
          regression=$(echo "$summary" | jq -r '.regression_detected // false')
          regression_text=$([ "$regression" = "true" ] && echo "Yes" || echo "No")

          echo "| Metric | Value |"
          echo "|--------|-------|"
          echo "| Architectures | $architectures |"
          echo "| Modes | $modes_tested |"
          echo "| Regression | $regression_text |"

          # Regression details
          regression_details=$(echo "$summary" | jq -r '.regression_details // [] | .[:5] | .[]' 2>/dev/null)
          if [ -n "$regression_details" ]; then
            echo ""
            echo "**Regressions:**"
            echo "$regression_details" | while read -r detail; do
              echo "- $detail"
            done
          fi
          ;;

        reliability)
          total_configs=$(echo "$summary" | jq -r '.total_configs // "N/A"')
          passed=$(echo "$summary" | jq -r '.passed // "N/A"')
          failed=$(echo "$summary" | jq -r '.failed // "N/A"')

          echo "| Metric | Value |"
          echo "|--------|-------|"
          echo "| Configs | $total_configs |"
          echo "| Passed | $passed |"
          echo "| Failed | $failed |"

          # Failures
          failures=$(echo "$summary" | jq -r '.failures // [] | .[:5] | .[]' 2>/dev/null)
          if [ -n "$failures" ]; then
            echo ""
            echo "**Failures:**"
            echo "$failures" | while read -r failure; do
              echo "- $failure"
            done
          fi
          ;;
      esac

      echo ""
      echo "</details>"
      echo ""
    done
  fi
else
  echo "*No test runs recorded yet.*"
fi

cat <<'EOF_FOOTER'

---

[← Back to Dashboard](../) | [View git history](https://github.com/DataDog/java-profiler/commits/gh-pages)
EOF_FOOTER

} > "${WORK_DIR}/${TEST_TYPE}/index.md"

echo "Generated ${WORK_DIR}/${TEST_TYPE}/index.md"
