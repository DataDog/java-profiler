#!/bin/bash

# check-stack-top.sh - Decide whether benchmarks should run for this branch.
#
# A branch is the top of its PR stack when no other open PR uses it as base
# branch. Stacked PRs chain head -> base (PR_n's base is PR_{n-1}'s head
# branch), so an open PR with base == <this branch> means this branch sits
# below another PR in the stack. Benchmarks only run for the top of a stack:
# intermediate commits get no BP pipeline.
#
# Usage: check-stack-top.sh [branch]
#   branch defaults to $CI_COMMIT_BRANCH.
# Output: exactly one line "RUN_BENCHMARKS=true" or "RUN_BENCHMARKS=false" on
# stdout (diagnostics go to stderr).
#
# Fail-open: on any API/auth/parsing error the decision is RUN_BENCHMARKS=true
# so a GitHub outage can never silently disable benchmark coverage.
#
# Authentication mirrors .gitlab/common/lookup-pr.sh: Octo-STS token when
# available, GITHUB_TOKEN fallback, anonymous as last resort. The token is
# passed to curl via a header file, never as a command-line argument (argv is
# world-readable on shared runners via /proc/*/cmdline).

set -uo pipefail

BRANCH="${1:-${CI_COMMIT_BRANCH:-}}"
REPO="DataDog/java-profiler"

debug() { echo "[DEBUG] $*" >&2; }

result() {
  echo "RUN_BENCHMARKS=$1"
  debug "decision: RUN_BENCHMARKS=$1 ($2)"
  exit 0
}

# main/master are the stack root: open PRs target them as base by
# definition, so the base-branch query below would always report "not top".
if [ -z "${BRANCH}" ] || [ "${BRANCH}" = "main" ] || [ "${BRANCH}" = "master" ]; then
  result "true" "branch is ${BRANCH:-<empty>}"
fi

# Authentication: pre-existing GITHUB_TOKEN env var, refreshed via dd-octo-sts
# when available (same scheme as lookup-pr.sh)
GITHUB_TOKEN="${GITHUB_TOKEN:-}"
if command -v dd-octo-sts >/dev/null 2>&1 && [ -n "${DDOCTOSTS_ID_TOKEN:-}" ]; then
  debug "Attempting to get token via Octo-STS..."
  if TOKEN_OUTPUT=$(dd-octo-sts token --scope "${REPO}" --policy async-profiler-build.ci 2>/tmp/dd-octo-sts-stack-top-error.log) && [ -n "${TOKEN_OUTPUT}" ]; then
    GITHUB_TOKEN="${TOKEN_OUTPUT}"
    debug "Got GitHub token via Octo-STS"
  else
    debug "Failed to get token via Octo-STS, falling back"
  fi
fi
# Normalize: strip CR/LF/outer whitespace and reject values that are not a
# bare token — a multi-line or decorated value would be interpolated into an
# HTTP header (injected headers or guaranteed auth failure).
GITHUB_TOKEN=$(printf '%s' "${GITHUB_TOKEN}" | tr -d '\r\n' | sed 's/^[[:space:]]*//; s/[[:space:]]*$//')
if [ -n "${GITHUB_TOKEN}" ] && ! printf '%s' "${GITHUB_TOKEN}" | grep -qE '^[A-Za-z0-9_.=-]+$'; then
  debug "Token has unexpected shape — ignoring it"
  GITHUB_TOKEN=""
fi

# URL-encode the branch name (/ -> %2F, etc.) - same approach as lookup-pr.sh
url_encode() {
  local string="$1"
  if command -v jq >/dev/null 2>&1; then
    printf '%s' "$string" | jq -sRr @uri
  else
    # % must be encoded first so the encodings added below are not re-encoded
    printf '%s' "$string" | sed 's/%/%25/g; s|/|%2F|g; s/ /%20/g; s/#/%23/g; s/+/%2B/g; s/&/%26/g; s/?/%3F/g; s/=/%3D/g; s/:/%3A/g; s/;/%3B/g; s/@/%40/g'
  fi
}

ENCODED_BRANCH=$(url_encode "${BRANCH}")
API_URL="https://api.github.com/repos/${REPO}/pulls?state=open&base=${ENCODED_BRANCH}&per_page=1"
debug "API URL: ${API_URL}"

# Pass the credential out-of-band: curl reads the header from a 0600 temp file
# instead of receiving it as a world-readable argv element.
AUTH_HEADER_FILE=""
cleanup() { [ -n "${AUTH_HEADER_FILE}" ] && rm -f "${AUTH_HEADER_FILE}"; }
trap cleanup EXIT
if [ -n "${GITHUB_TOKEN}" ]; then
  AUTH_HEADER_FILE=$(mktemp "${TMPDIR:-/tmp}/sphinx-stack-top-hdr.XXXXXX")
  chmod 600 "${AUTH_HEADER_FILE}"
  printf 'Authorization: token %s\n' "${GITHUB_TOKEN}" > "${AUTH_HEADER_FILE}"
  debug "Using authenticated request (header via file)"
else
  debug "Using anonymous request (may be rate limited)"
fi

BODY_FILE=$(mktemp "${TMPDIR:-/tmp}/sphinx-stack-top-body.XXXXXX")
HTTP_CODE=$(curl -s -o "${BODY_FILE}" -w '%{http_code}' --max-time 10 \
  ${AUTH_HEADER_FILE:+-H "@${AUTH_HEADER_FILE}"} \
  -H "Accept: application/vnd.github+json" \
  "${API_URL}" 2>/dev/null)
CURL_EXIT=$?
response=$(cat "${BODY_FILE}" 2>/dev/null)
rm -f "${BODY_FILE}"

if [ "${CURL_EXIT}" -ne 0 ]; then
  result "true" "curl failed with exit ${CURL_EXIT} (fail-open)"
fi
if [ "${HTTP_CODE}" != "200" ]; then
  # HTTP 403 with a JSON error object is the anonymous rate-limit response;
  # surfacing the code here makes that failure observable instead of silent.
  result "true" "GitHub API returned HTTP ${HTTP_CODE} (fail-open)"
fi

debug "API response length: ${#response} chars"
debug "API response preview: ${response:0:200}"

if ! command -v jq >/dev/null 2>&1; then
  result "true" "jq not available (fail-open)"
fi

if ! echo "${response}" | jq -e 'type == "array"' >/dev/null 2>&1; then
  result "true" "response is not a JSON array (API error, fail-open)"
fi

STACKED_ON_TOP=$(echo "${response}" | jq 'length')
if [ "${STACKED_ON_TOP}" -gt 0 ]; then
  result "false" "${STACKED_ON_TOP} open PR(s) use ${BRANCH} as base branch"
fi

result "true" "no open PR stacks on ${BRANCH}"
