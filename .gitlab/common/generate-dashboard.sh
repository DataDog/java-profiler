#!/bin/bash

# generate-dashboard.sh - Generate main index.md dashboard from history data
#
# Usage: generate-dashboard.sh [work-dir]
#
# Reads _data/{integration,benchmarks,reliability}.json and generates index.md
# with quick status table and recent runs across all test types.
#
# Pure bash/jq implementation - no Python required

set -euo pipefail

WORK_DIR="${1:-.}"
TIMESTAMP=$(date -u +"%Y-%m-%d %H:%M UTC")

# Check if jq is available
if ! command -v jq >/dev/null 2>&1; then
  echo "Error: jq is required for JSON parsing" >&2
  exit 1
fi

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

# Generate the dashboard markdown
{
cat <<EOF_HEADER
---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** ${TIMESTAMP}

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
EOF_HEADER

# Quick status for each test type
for test_type in integration benchmarks reliability; do
  # Capitalize first letter
  display_name="$(echo "${test_type:0:1}" | tr '[:lower:]' '[:upper:]')${test_type:1}"
  history_file="${WORK_DIR}/_data/${test_type}.json"

  if [ -f "$history_file" ] && [ -s "$history_file" ]; then
    # Get latest run (first in array)
    latest=$(jq -r '.runs[0] // empty' "$history_file" 2>/dev/null)

    if [ -n "$latest" ]; then
      status=$(echo "$latest" | jq -r '.status // "unknown"')
      status_symbol=$(status_emoji "$status")
      branch=$(echo "$latest" | jq -r '.ddprof_branch // "unknown"')
      pr_info=$(echo "$latest" | jq -c '.ddprof_pr // null')
      pipeline=$(echo "$latest" | jq -c '.pipeline // null')

      pr_link=$(format_pr_link "$pr_info")
      pipeline_link=$(format_pipeline_link "$pipeline")

      echo "| [$display_name]($test_type/) | $pipeline_link | $status_symbol | $branch | $pr_link |"
    else
      echo "| [$display_name]($test_type/) | - | - | - | - |"
    fi
  else
    echo "| [$display_name]($test_type/) | - | - | - | - |"
  fi
done

cat <<'EOF_TEST_TYPES'

---

## Test Types

### Integration Tests
dd-trace-java compatibility tests verifying profiler works correctly with the Datadog tracer.
Tests run on every main branch build across multiple JDK versions and platforms.

### Benchmarks
Performance regression testing using Renaissance benchmark suite.
Compares profiler overhead against baseline (no profiling).

### Reliability Tests
Long-running stability tests checking for memory leaks and crashes.
Tests multiple allocator configurations (gmalloc, tcmalloc, jemalloc).

---

## Recent Runs (All Types)

| Date | Type | Pipeline | Branch | PR | Status |
|------|------|----------|--------|-----|--------|
EOF_TEST_TYPES

# Collect all runs from all types (last 5 from each) into a single JSON array
tmpfile=$(mktemp)
trap "rm -f $tmpfile" EXIT

# Build array by merging runs from all test types
all_runs="[]"
for test_type in integration benchmarks reliability; do
  history_file="${WORK_DIR}/_data/${test_type}.json"

  if [ -f "$history_file" ] && [ -s "$history_file" ]; then
    # Get last 5 runs, add type field, merge into all_runs
    runs=$(jq --arg type "$test_type" \
       '.runs[:5] | map(. + {_type: $type})' \
       "$history_file" 2>/dev/null || echo "[]")

    all_runs=$(echo "$all_runs" "$runs" | jq -s 'add')
  fi
done

echo "$all_runs" > "$tmpfile"

# Sort by timestamp descending, take 15 most recent
if [ "$(jq 'length' "$tmpfile" 2>/dev/null || echo 0)" -gt 0 ]; then
  jq -c 'sort_by(.timestamp) | reverse | .[:15] | .[]' "$tmpfile" 2>/dev/null | \
  while IFS= read -r run; do
    date=$(echo "$run" | jq -r '(.timestamp // "")[:10]')
    type_val=$(echo "$run" | jq -r '._type // "unknown"')
    type_name="$(echo "${type_val:0:1}" | tr '[:lower:]' '[:upper:]')${type_val:1}"
    status=$(echo "$run" | jq -r '.status // "unknown"')
    status_symbol=$(status_emoji "$status")
    branch=$(echo "$run" | jq -r '.ddprof_branch // "unknown"')
    pr_info=$(echo "$run" | jq -c '.ddprof_pr // null')
    pipeline=$(echo "$run" | jq -c '.pipeline // null')

    pr_link=$(format_pr_link "$pr_info")
    pipeline_link=$(format_pipeline_link "$pipeline")

    echo "| $date | $type_name | $pipeline_link | $branch | $pr_link | $status_symbol |"
  done
else
  echo "| - | - | - | - | - | - |"
fi

cat <<'EOF_FOOTER'

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
EOF_FOOTER

} > "${WORK_DIR}/index.md"

echo "Generated ${WORK_DIR}/index.md"
