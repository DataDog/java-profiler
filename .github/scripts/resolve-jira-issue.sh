#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc.

# Resolve the open Jira issue whose summary matches exactly, then add a
# comment that says why. The counterpart of file-jira-issue.sh
# --on-duplicate skip for alerts that clear on their own.
#
# Environment: as file-jira-issue.sh (ATLASSIAN_BASE_URL, ATLASSIAN_USER_EMAIL,
# ATLASSIAN_API_TOKEN, optional JIRA_PROJECT, default PROF).
#
# Usage:
#   resolve-jira-issue.sh --summary <text> --comment-file <path>
#
# Prints the key of the matching open issue, or nothing when none matches.
# Exit codes: 0 resolved (a failed comment only warns) or nothing to do,
# 1 lookup failure, 2 usage, 3 credentials missing, 4 no transition to a done
# status (left untouched), 5 the transition lookup or call failed.

usage() {
  echo "Usage: $0 --summary <text> --comment-file <path>" >&2
  exit 2
}

SUMMARY=""
COMMENT_FILE=""

while [ $# -gt 0 ]; do
  case "$1" in
    --summary) SUMMARY="$2"; shift 2 ;;
    --comment-file) COMMENT_FILE="$2"; shift 2 ;;
    -h|--help) usage ;;
    *) echo "ERROR: unknown argument: $1" >&2; usage ;;
  esac
done

if [ -z "$SUMMARY" ] || [ -z "$COMMENT_FILE" ]; then
  usage
fi
if [ ! -f "$COMMENT_FILE" ]; then
  echo "ERROR: comment file not found: $COMMENT_FILE" >&2
  exit 2
fi
for var in ATLASSIAN_BASE_URL ATLASSIAN_USER_EMAIL ATLASSIAN_API_TOKEN; do
  if [ -z "${!var:-}" ]; then
    echo "WARNING: $var is not set; cannot resolve a Jira issue" >&2
    exit 3
  fi
done

PROJECT="${JIRA_PROJECT:-PROF}"
BASE="${ATLASSIAN_BASE_URL%/}"
AUTH="$ATLASSIAN_USER_EMAIL:$ATLASSIAN_API_TOKEN"
API="$BASE/rest/api/3"

# jira <exit code> <curl args...>: maps a curl failure to the given code;
# curl's own exit codes overlap the ones above.
jira() {
  local code=$1
  shift
  curl -fsS -u "$AUTH" -H 'Content-Type: application/json' "$@" || {
    echo "ERROR: Jira API call failed: ${*: -1}" >&2
    exit "$code"
  }
}

# The exact-phrase JQL of file-jira-issue.sh --on-duplicate skip, so this
# finds the issue that script dedupes onto. Phrase JQL also matches longer
# summaries, so the hits are post-filtered below to an exact summary.
JQL_SUMMARY=$(jq -rn --arg s "$SUMMARY" '$s | gsub("\\\\"; "\\\\\\\\") | gsub("\""; "\\\\\"")')
JQL="project = $PROJECT AND summary ~ \"\\\"$JQL_SUMMARY\\\"\" AND resolution = Unresolved AND statusCategory != Done"
SEARCH=$(jira 1 -X POST --data "$(jq -n --arg jql "$JQL" \
  '{jql: $jql, maxResults: 10, fields: ["key", "summary"]}')" "$API/search/jql")

# Closing the first phrase hit could transition an unrelated open ticket
# whose summary merely contains the phrase, so resolve only an exact,
# case-insensitive summary match and leave the rest untouched.
EXISTING_KEY=$(jq -r --arg s "$SUMMARY" '
  [.issues[] | select((.fields.summary // "") | ascii_downcase == ($s | ascii_downcase))][0].key // empty' <<<"$SEARCH")
if [ -z "$EXISTING_KEY" ] && [ "$(jq '.issues | length' <<<"$SEARCH")" != 0 ]; then
  echo "WARNING: Jira phrase search matched issues but none with the exact summary '$SUMMARY'; not resolving" >&2
  exit 0
fi

if [ -z "$EXISTING_KEY" ]; then
  exit 0
fi
echo "$EXISTING_KEY"

# Transition before commenting, so an issue that cannot be closed does not
# collect the same comment every run. Names differ between workflows; prefer
# Done/Resolve/Close over other done statuses such as Won't Do.
TRANSITION_ID=$(jira 5 "$API/issue/$EXISTING_KEY/transitions" | jq -r '
  [.transitions[] | select(.to.statusCategory.key == "done")] |
  ((map(select((.name // "") | test("^(done|resolve|close)"; "i"))) + .)[0].id) // empty')
if [ -z "$TRANSITION_ID" ]; then
  echo "WARNING: $EXISTING_KEY has no transition to a done status; left open" >&2
  exit 4
fi

jira 5 -X POST --data "$(jq -n --arg id "$TRANSITION_ID" '{transition: {id: $id}}')" \
  "$API/issue/$EXISTING_KEY/transitions" >/dev/null
COMMENT_PAYLOAD=$(jq -n --rawfile body "$COMMENT_FILE" \
  '{body: {type: "doc", version: 1, content: [{type: "paragraph", content: [{type: "text", text: $body}]}]}}')
# The issue is already closed here; a failed comment must not report it open.
curl -fsS -u "$AUTH" -H 'Content-Type: application/json' -X POST --data "$COMMENT_PAYLOAD" \
  "$API/issue/$EXISTING_KEY/comment" >/dev/null ||
  echo "WARNING: $EXISTING_KEY resolved, but the comment failed" >&2
