#!/usr/bin/env bash
# Upsert a comment on the java-profiler GitHub PR for the current branch.
#
# Posts (or replaces) a single marker-tagged comment using a short-lived GitHub
# token obtained via dd-octo-sts. No pr-commenter / benchmarking-platform clone
# is required — only dd-octo-sts (present in dd-octo-sts-ci-base) plus curl/jq.
#
# Usage:
#   upsert-github-pr-comment.sh <comment-id> <branch> <body-file>
#
#   comment-id : unique slug used as an HTML marker to find/replace the comment
#   branch     : head branch name used to locate the open PR
#   body-file  : path to a file holding the markdown comment body
#
# Requires in CI: dd-octo-sts CLI + DDOCTOSTS_ID_TOKEN id_token, curl, jq.
# Token policy async-profiler-build.ci grants issues:write + pull_requests:read.

set -euo pipefail

COMMENT_ID="${1:?comment-id required}"
BRANCH="${2:?branch required}"
BODY_FILE="${3:?body-file required}"
REPO="DataDog/java-profiler"
API="https://api.github.com/repos/${REPO}"

log() { echo "[upsert-pr-comment] $*" >&2; }

# gh_api <method> <url> [data] — performs a GitHub API call, capturing both the
# response body and HTTP status. On HTTP >= 400 it logs the status and body
# (turning opaque "curl 403" failures into actionable diagnostics) and returns 1.
# On success the response body is written to stdout.
gh_api() {
  local method="$1" url="$2" data="${3:-}"
  local args=(-sS -X "${method}"
    -H "Authorization: Bearer ${TOKEN}"
    -H "Accept: application/vnd.github+json"
    -H "X-GitHub-Api-Version: 2022-11-28"
    -H "User-Agent: java-profiler-ci"
    -w $'\n%{http_code}')
  [ -n "${data}" ] && args+=(-d "${data}")
  local resp status body
  resp=$(curl "${args[@]}" "${url}") || { log "curl failed for ${method} ${url}"; return 1; }
  status="${resp##*$'\n'}"
  body="${resp%$'\n'*}"
  if [ "${status}" -ge 400 ]; then
    log "GitHub API ${method} ${url} -> HTTP ${status}"
    log "Response: ${body}"
    return 1
  fi
  printf '%s' "${body}"
}

if [ -z "${BRANCH}" ] || [ "${BRANCH}" = "main" ] || [ "${BRANCH}" = "master" ]; then
  log "Skipping PR comment for branch: ${BRANCH:-<unset>}"
  exit 0
fi
if [ ! -s "${BODY_FILE}" ]; then
  log "Empty body file (${BODY_FILE}) — nothing to post"
  exit 0
fi

# 1. Obtain a GitHub token via dd-octo-sts (no stored secrets). Trim whitespace
#    and validate the format, mirroring publish-gh-pages.sh — a token polluted
#    with log noise/newlines produces a malformed header and a GitHub 403.
TOKEN=$(dd-octo-sts token --scope "${REPO}" --policy async-profiler-build.ci 2>/tmp/octo-sts.err || true)
TOKEN="${TOKEN//[$'\t\r\n ']/}"
if [ -z "${TOKEN}" ]; then
  log "Failed to obtain GitHub token via dd-octo-sts — skipping comment"
  [ -s /tmp/octo-sts.err ] && log "dd-octo-sts: $(head -3 /tmp/octo-sts.err)"
  exit 0
fi
if [[ ! "${TOKEN}" =~ ^(ghs_|ghp_|github_pat_|v1\.|[A-Za-z0-9_-]+\.[A-Za-z0-9_-]+\.) ]]; then
  log "dd-octo-sts returned an unexpected token format (first 8 chars: ${TOKEN:0:8}) — skipping"
  exit 0
fi

# 2. Resolve the open PR for this branch.
PR=$(gh_api GET "${API}/pulls?head=DataDog:${BRANCH}&state=open&per_page=1" | jq -r '.[0].number // empty')
if [ -z "${PR}" ]; then
  log "No open PR found for branch ${BRANCH} — skipping comment"
  exit 0
fi

# 3. Prepend a stable marker and build the JSON payload safely.
MARKER="<!-- ${COMMENT_ID} -->"
BODY="${MARKER}"$'\n'"$(cat "${BODY_FILE}")"
PAYLOAD=$(jq -n --arg body "${BODY}" '{body: $body}')

# 4. Find an existing marker comment and PATCH it, otherwise POST a new one.
CID=$(gh_api GET "${API}/issues/${PR}/comments?per_page=100" \
        | jq -r --arg m "${MARKER}" '.[] | select(.body | contains($m)) | .id' | head -n1)

if [ -n "${CID}" ]; then
  gh_api PATCH "${API}/issues/comments/${CID}" "${PAYLOAD}" >/dev/null
  log "Updated comment ${CID} on PR #${PR}"
else
  gh_api POST "${API}/issues/${PR}/comments" "${PAYLOAD}" >/dev/null
  log "Created comment on PR #${PR}"
fi
