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

if [ -z "${BRANCH}" ] || [ "${BRANCH}" = "main" ] || [ "${BRANCH}" = "master" ]; then
  log "Skipping PR comment for branch: ${BRANCH:-<unset>}"
  exit 0
fi
if [ ! -s "${BODY_FILE}" ]; then
  log "Empty body file (${BODY_FILE}) — nothing to post"
  exit 0
fi

# 1. Obtain a GitHub token via dd-octo-sts (no stored secrets).
TOKEN=$(dd-octo-sts token --scope "${REPO}" --policy async-profiler-build.ci 2>/dev/null || true)
if [ -z "${TOKEN}" ]; then
  log "Failed to obtain GitHub token via dd-octo-sts — skipping comment"
  exit 0
fi
AUTH=(-H "Authorization: Bearer ${TOKEN}" -H "Accept: application/vnd.github+json")

# 2. Resolve the open PR for this branch.
PR=$(curl -fsS "${AUTH[@]}" "${API}/pulls?head=DataDog:${BRANCH}&state=open&per_page=1" \
       | jq -r '.[0].number // empty')
if [ -z "${PR}" ]; then
  log "No open PR found for branch ${BRANCH} — skipping comment"
  exit 0
fi

# 3. Prepend a stable marker and build the JSON payload safely.
MARKER="<!-- ${COMMENT_ID} -->"
BODY="${MARKER}"$'\n'"$(cat "${BODY_FILE}")"
PAYLOAD=$(jq -n --arg body "${BODY}" '{body: $body}')

# 4. Find an existing marker comment and PATCH it, otherwise POST a new one.
CID=$(curl -fsS "${AUTH[@]}" "${API}/issues/${PR}/comments?per_page=100" \
        | jq -r --arg m "${MARKER}" '.[] | select(.body | contains($m)) | .id' | head -n1)

if [ -n "${CID}" ]; then
  curl -fsS -X PATCH "${AUTH[@]}" "${API}/issues/comments/${CID}" -d "${PAYLOAD}" >/dev/null
  log "Updated comment ${CID} on PR #${PR}"
else
  curl -fsS -X POST "${AUTH[@]}" "${API}/issues/${PR}/comments" -d "${PAYLOAD}" >/dev/null
  log "Created comment on PR #${PR}"
fi
