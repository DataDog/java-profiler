#!/bin/bash

# lookup-pr.sh - Find GitHub PR for a java-profiler branch
#
# Usage: lookup-pr.sh <branch-name>
# Output: JSON with PR info {"number": N, "url": "...", "title": "..."} or {}
#
# Authentication:
#   - In CI: Uses Octo-STS with java-profiler-build-read policy
#   - Fallback: GITHUB_TOKEN env var or unauthenticated (public repo)
#
# Falls back gracefully if API fails or no PR found.

set -euo pipefail

BRANCH="${1:-}"
REPO="DataDog/java-profiler"

# Debug logging to stderr (doesn't affect JSON output on stdout)
debug() { echo "[DEBUG] $*" >&2; }

debug "Looking for PR in ${REPO} with head branch: ${BRANCH}"

# Skip lookup for main/master branches (never have PRs)
if [ -z "${BRANCH}" ] || [ "${BRANCH}" = "main" ] || [ "${BRANCH}" = "master" ]; then
  debug "Skipping lookup for main/master branch"
  echo "{}"
  exit 0
fi

# Obtain GitHub token via dd-octo-sts if available
GITHUB_TOKEN=""
if command -v dd-octo-sts >/dev/null 2>&1 && [ -n "${DDOCTOSTS_ID_TOKEN:-}" ]; then
  debug "Attempting to get token via Octo-STS..."
  TOKEN_OUTPUT=$(dd-octo-sts token --scope DataDog/java-profiler --policy async-profiler-build.ci 2>/tmp/dd-octo-sts-lookup-error.log)
  TOKEN_EXIT_CODE=$?

  if [ $TOKEN_EXIT_CODE -eq 0 ] && [ -n "${TOKEN_OUTPUT}" ]; then
    GITHUB_TOKEN="${TOKEN_OUTPUT}"
    debug "Got GitHub token via Octo-STS"
  else
    debug "Failed to get token via Octo-STS (exit code: ${TOKEN_EXIT_CODE})"
    if [ -s /tmp/dd-octo-sts-lookup-error.log ]; then
      debug "dd-octo-sts error: $(cat /tmp/dd-octo-sts-lookup-error.log | head -5)"
    fi
  fi
else
  debug "Octo-STS not available (dd-octo-sts: $(command -v dd-octo-sts 2>/dev/null || echo 'not found'), DDOCTOSTS_ID_TOKEN: ${DDOCTOSTS_ID_TOKEN:+set})"
fi

# URL-encode the branch name (/ -> %2F, etc.)
# Use jq if available, otherwise use sed for common cases
url_encode() {
  local string="$1"
  if command -v jq >/dev/null 2>&1; then
    printf '%s' "$string" | jq -sRr @uri
  else
    # Fallback: encode common special characters with sed
    printf '%s' "$string" | sed 's|/|%2F|g; s| |%20|g; s|#|%23|g'
  fi
}

ENCODED_BRANCH=$(url_encode "${BRANCH}")
API_URL="https://api.github.com/repos/${REPO}/pulls?head=DataDog:${ENCODED_BRANCH}&state=all&per_page=1"
debug "API URL: ${API_URL}"

if [ -n "${GITHUB_TOKEN}" ]; then
  debug "Using authenticated request"
  response=$(curl -s --max-time 10 \
    -H "Authorization: token ${GITHUB_TOKEN}" \
    -H "Accept: application/vnd.github+json" \
    "${API_URL}" 2>/dev/null) || {
    debug "curl failed"
    echo "{}"
    exit 0
  }
else
  # Anonymous access for public repos (60 req/hour limit)
  debug "Using anonymous request (may be rate limited)"
  response=$(curl -s --max-time 10 \
    -H "Accept: application/vnd.github+json" \
    "${API_URL}" 2>/dev/null) || {
    debug "curl failed"
    echo "{}"
    exit 0
  }
fi

debug "API response length: ${#response} chars"
debug "API response preview: ${response:0:200}"

# Parse JSON response - use jq if available
if command -v jq >/dev/null 2>&1; then
  # Check if response is a non-empty array
  if ! echo "${response}" | jq -e 'if type == "array" and length > 0 then true else false end' >/dev/null 2>&1; then
    debug "Response is not a valid JSON array with items (might be error response or empty)"
    echo "{}"
    exit 0
  fi

  debug "Found valid PR response"

  # Extract PR info
  echo "${response}" | jq -c '.[0] | {number: .number, url: .html_url, title: .title}'
else
  # Fallback: use grep/sed for basic JSON extraction (less reliable but works without jq)
  debug "jq not available, using fallback JSON parsing"

  # Check if it looks like a non-empty array
  if ! echo "${response}" | grep -q '^\[{'; then
    debug "Response doesn't look like a JSON array with items"
    echo "{}"
    exit 0
  fi

  debug "Found valid PR response (basic check)"

  # Extract fields using grep/sed (fragile but works for simple cases)
  pr_number=$(echo "${response}" | grep -o '"number":[0-9]*' | head -1 | sed 's/"number"://')
  pr_url=$(echo "${response}" | grep -o '"html_url":"[^"]*"' | head -1 | sed 's/"html_url":"//; s/"$//')
  pr_title=$(echo "${response}" | grep -o '"title":"[^"]*"' | head -1 | sed 's/"title":"//; s/"$//')

  if [ -n "${pr_number}" ]; then
    echo "{\"number\":${pr_number},\"url\":\"${pr_url}\",\"title\":\"${pr_title}\"}"
  else
    echo "{}"
  fi
fi
