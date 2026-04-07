#!/bin/bash

# update-history.sh - Update JSON history file with new run, keeping last N entries
#
# Usage: update-history.sh <test-type> <new-run-json-file> [work-dir]
#
# test-type: integration|benchmarks|reliability
# new-run-json-file: Path to file containing new run JSON
# work-dir: Directory containing _data/ (default: current directory)
#
# Updates _data/{test-type}.json, prepending new run and keeping last MAX_HISTORY entries.
#
# Pure bash/jq implementation - no Python required

set -euo pipefail

TEST_TYPE="${1:-}"
NEW_RUN_FILE="${2:-}"
WORK_DIR="${3:-.}"
MAX_HISTORY="${MAX_HISTORY:-10}"

if [ -z "${TEST_TYPE}" ] || [ -z "${NEW_RUN_FILE}" ]; then
  echo "Usage: update-history.sh <test-type> <new-run-json-file> [work-dir]" >&2
  exit 1
fi

if [ ! -f "${NEW_RUN_FILE}" ]; then
  echo "Error: New run JSON file not found: ${NEW_RUN_FILE}" >&2
  exit 1
fi

HISTORY_FILE="${WORK_DIR}/_data/${TEST_TYPE}.json"

# Ensure _data directory exists
mkdir -p "${WORK_DIR}/_data"

# Initialize history file if it doesn't exist
if [ ! -f "${HISTORY_FILE}" ]; then
  echo '{"runs":[]}' > "${HISTORY_FILE}"
fi

# Check if jq is available
if ! command -v jq >/dev/null 2>&1; then
  echo "Error: jq is required for JSON manipulation" >&2
  echo "Install with: apt-get install jq (Debian/Ubuntu) or apk add jq (Alpine)" >&2
  exit 1
fi

# Read new run JSON
NEW_RUN_JSON=$(cat "${NEW_RUN_FILE}")

# Validate JSON
if ! echo "$NEW_RUN_JSON" | jq empty 2>/dev/null; then
  echo "Error: Invalid JSON in ${NEW_RUN_FILE}" >&2
  exit 1
fi

# Update history using jq:
# 1. Read existing history (or start with empty {"runs":[]})
# 2. Parse new run from variable
# 3. Prepend new run to .runs array
# 4. Keep only last MAX_HISTORY entries
jq --argjson newrun "$NEW_RUN_JSON" \
   --argjson maxhistory "$MAX_HISTORY" \
   '.runs = ([$newrun] + .runs) | .runs = .runs[:$maxhistory]' \
   "${HISTORY_FILE}" > "${HISTORY_FILE}.tmp"

# Atomic move
mv "${HISTORY_FILE}.tmp" "${HISTORY_FILE}"

# Report success
RUN_COUNT=$(jq '.runs | length' "${HISTORY_FILE}")
echo "Updated ${HISTORY_FILE}: now has ${RUN_COUNT} run(s)"
