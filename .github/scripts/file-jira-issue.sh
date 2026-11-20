#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc

# File a Jira issue, or update the existing open one when a duplicate is
# already tracked.
#
# Environment:
#   ATLASSIAN_BASE_URL    e.g. https://datadoghq.atlassian.net (required)
#   ATLASSIAN_USER_EMAIL  account email for the API token (required)
#   ATLASSIAN_API_TOKEN   API token (required)
#   JIRA_PROJECT          project key, default PROF
#
# Usage:
#   file-jira-issue.sh --summary <text> --body-file <path> [--priority <name>]
#                      [--label <label> ...]
#
# Dedupe: when an unresolved issue in the project already has the exact
# summary, a dedupe comment is added to it instead of creating a new issue.
# Prints the created/updated issue key on stdout.

usage() {
  echo "Usage: $0 --summary <text> --body-file <path> [--priority <name>] [--label <label> ...]" >&2
  exit 2
}

SUMMARY=""
BODY_FILE=""
PRIORITY="High"
LABELS=()

while [ $# -gt 0 ]; do
  case "$1" in
    --summary) SUMMARY="$2"; shift 2 ;;
    --body-file) BODY_FILE="$2"; shift 2 ;;
    --priority) PRIORITY="$2"; shift 2 ;;
    --label) LABELS+=("$2"); shift 2 ;;
    -h|--help) usage ;;
    *) echo "ERROR: unknown argument: $1" >&2; usage ;;
  esac
done

if [ -z "$SUMMARY" ] || [ -z "$BODY_FILE" ]; then
  usage
fi
if [ ! -f "$BODY_FILE" ]; then
  echo "ERROR: body file not found: $BODY_FILE" >&2
  exit 1
fi
for var in ATLASSIAN_BASE_URL ATLASSIAN_USER_EMAIL ATLASSIAN_API_TOKEN; do
  if [ -z "${!var:-}" ]; then
    echo "WARNING: $var is not set; cannot file a Jira issue" >&2
    exit 3
  fi
done

PROJECT="${JIRA_PROJECT:-PROF}"
BASE="${ATLASSIAN_BASE_URL%/}"
AUTH="$ATLASSIAN_USER_EMAIL:$ATLASSIAN_API_TOKEN"
API="$BASE/rest/api/3"

# Escaped exact-match JQL for the dedupe lookup; summary text is plain ASCII
# produced by the callers (no quotes), but escape anyway.
JQL_SUMMARY=$(jq -rn --arg s "$SUMMARY" '$s | gsub("\\\\"; "\\\\\\\\") | gsub("\""; "\\\\\"")')
JQL="project = $PROJECT AND summary ~ \"$JQL_SUMMARY\" AND resolution = Unresolved"
EXISTING_KEY=$(curl -fsS -u "$AUTH" -H 'Content-Type: application/json' \
  --get --data-urlencode "jql=$JQL" --data 'maxResults=1&fields=key' \
  "$API/search" | jq -r '.issues[0].key // empty') || EXISTING_KEY=""

BODY=$(cat "$BODY_FILE")

if [ -n "$EXISTING_KEY" ]; then
  COMMENT_PAYLOAD=$(jq -n --arg body "$BODY" \
    '{body: [{type: "paragraph", content: [{type: "text", text: ("Recurring failure. Details:\n\n" + $body)}]}]}')
  curl -fsS -u "$AUTH" -H 'Content-Type: application/json' \
    -X POST --data "$COMMENT_PAYLOAD" "$API/issue/$EXISTING_KEY/comment" >/dev/null
  echo "$EXISTING_KEY"
  exit 0
fi

# ADF document: the body file holds plain text; blank lines split paragraphs.
ADF_DOC=$(jq -n --arg body "$BODY" '
  [$body | split("\n\n")[] | {type: "paragraph", content: [{type: "text", text: .}]}] |
  {type: "doc", version: 1, content: .}')

ISSUE_PAYLOAD=$(jq -n --arg project "$PROJECT" --arg summary "$SUMMARY" --arg priority "$PRIORITY" \
  --argjson doc "$ADF_DOC" --argjson labels "$(printf '%s\n' "${LABELS[@]:-}" | jq -R . | jq -s 'map(select(length > 0))')" '
  {fields: {
    project: {key: $project},
    summary: $summary,
    description: $doc,
    issuetype: {name: "Task"},
    priority: {name: $priority},
    labels: $labels
  }}')

ISSUE_KEY=$(curl -fsS -u "$AUTH" -H 'Content-Type: application/json' \
  -X POST --data "$ISSUE_PAYLOAD" "$API/issue" | jq -r '.key')

echo "$ISSUE_KEY"
