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
#                      [--label <label> ...] [--component <name> ...]
#                      [--on-duplicate comment|skip] [--status-file <path>]
#
# Labels need no setup: Jira creates a label the first time an issue uses it.
# --on-duplicate skip leaves an existing open issue untouched (no comment),
# ignores issues in a done status, and dedupes only onto an issue whose
# summary equals the requested one (case-insensitive); it files nothing when
# the dedupe lookup fails or cannot be verified, and files new when the search
# matches only longer summaries. --status-file receives "created" or "existing".
#
# Dedupe: when an unresolved issue in the project already matches the
# summary as an exact phrase (unquoted JQL '~' is OR term matching, so any
# shared word would match another commit's ticket), a dedupe comment is
# added to it instead of creating a new issue. Without skip, a failed dedupe
# lookup only warns: a duplicate ticket beats a lost failure report.
# Prints the created/updated issue key on stdout.

usage() {
  echo "Usage: $0 --summary <text> --body-file <path> [--priority <name>] [--label <label> ...]" \
    "[--component <name> ...] [--on-duplicate comment|skip] [--status-file <path>]" >&2
  exit 2
}

SUMMARY=""
BODY_FILE=""
PRIORITY="High"
LABELS=()
COMPONENTS=()
ON_DUPLICATE="comment"
STATUS_FILE=""

while [ $# -gt 0 ]; do
  case "$1" in
    --summary) SUMMARY="$2"; shift 2 ;;
    --body-file) BODY_FILE="$2"; shift 2 ;;
    --priority) PRIORITY="$2"; shift 2 ;;
    --label) LABELS+=("$2"); shift 2 ;;
    --component) COMPONENTS+=("$2"); shift 2 ;;
    --on-duplicate) ON_DUPLICATE="$2"; shift 2 ;;
    --status-file) STATUS_FILE="$2"; shift 2 ;;
    -h|--help) usage ;;
    *) echo "ERROR: unknown argument: $1" >&2; usage ;;
  esac
done

if [ -z "$SUMMARY" ] || [ -z "$BODY_FILE" ]; then
  usage
fi
case "$ON_DUPLICATE" in
  comment|skip) ;;
  *) echo "ERROR: --on-duplicate must be comment or skip: $ON_DUPLICATE" >&2; usage ;;
esac
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

# Escaped JQL for the dedupe lookup; summary text is plain ASCII produced by
# the callers (no quotes), but escape anyway. The /search endpoint is retired;
# /search/jql takes a POST body and may return issues or issueKeys.
JQL_SUMMARY=$(jq -rn --arg s "$SUMMARY" '$s | gsub("\\\\"; "\\\\\\\\") | gsub("\""; "\\\\\"")')
# Exact-phrase match the whole summary: in JQL '~' the outer quotes only
# delimit the operand — unescaped, the words match in any order (OR terms),
# and the shared fixed words would let one commit's failure dedupe onto
# another commit's ticket. The phrase form needs escaped quotes INSIDE the
# operand; quotes in the summary arrive pre-escaped by JQL_SUMMARY and stay
# JQL escapes.
JQL="project = $PROJECT AND summary ~ \"\\\"$JQL_SUMMARY\\\"\" AND resolution = Unresolved"
# resolve-jira-issue.sh can close an alert into a done status that leaves the
# resolution unset; skip must not mistake it for open and drop a new alert.
if [ "$ON_DUPLICATE" = "skip" ]; then
  JQL="$JQL AND statusCategory != Done"
fi
# Every Jira request is bounded (--max-time 60): a stalled Jira server
# must fail fast instead of eating the caller's job timeout.
if [ "$ON_DUPLICATE" = "skip" ]; then
  # skip must not dedupe onto a ticket whose summary merely contains the
  # phrase, so it post-filters to an exact, case-insensitive summary match.
  # Anything it cannot verify is not a proven duplicate: a failed lookup or an
  # unsummarized response files nothing, matched-but-not-exact files new.
  SEARCH=$(curl -fsS --connect-timeout 15 --max-time 60 -u "$AUTH" -H 'Content-Type: application/json' \
    -X POST --data "$(jq -n --arg jql "$JQL" '{jql: $jql, maxResults: 100, fields: ["key", "summary"]}')" \
    "$API/search/jql") || {
    echo "ERROR: dedupe lookup failed; not filing a possible duplicate" >&2
    exit 1
  }
  jq -e 'type == "object"' >/dev/null <<<"$SEARCH" || {
    echo "ERROR: dedupe lookup returned an unexpected response; not filing a possible duplicate" >&2
    exit 1
  }
  EXISTING_KEY=$(jq -r --arg s "$SUMMARY" '
    [.issues[]? | select((.fields.summary // "") | ascii_downcase == ($s | ascii_downcase))][0].key // empty' <<<"$SEARCH")
  if [ -z "$EXISTING_KEY" ]; then
    if [ "$(jq '[.issues[]?] | length' <<<"$SEARCH")" != 0 ]; then
      echo "NOTICE: dedupe search matched issues but none with the exact summary; filing a new issue" >&2
    elif [ "$(jq '.issueKeys | type == "array" and length > 0' <<<"$SEARCH")" = true ]; then
      echo "ERROR: dedupe lookup returned issue keys without summaries; not filing a possible duplicate" >&2
      exit 1
    fi
  fi
else
  EXISTING_KEY=$(curl -fsS --connect-timeout 15 --max-time 60 -u "$AUTH" -H 'Content-Type: application/json' \
    -X POST --data "$(jq -n --arg jql "$JQL" '{jql: $jql, maxResults: 1, fields: ["key"]}')" \
    "$API/search/jql" | jq -r '.issues[0].key // .issueKeys[0] // empty') || {
    echo "WARNING: dedupe lookup failed; creating a new issue" >&2
    EXISTING_KEY=""
  }
fi

BODY=$(cat "$BODY_FILE")

if [ -n "$EXISTING_KEY" ]; then
  if [ -n "$STATUS_FILE" ]; then
    echo existing > "$STATUS_FILE"
  fi
  if [ "$ON_DUPLICATE" = "skip" ]; then
    echo "$EXISTING_KEY"
    exit 0
  fi
  COMMENT_PAYLOAD=$(jq -n --arg body "$BODY" \
    '{body: {type: "doc", version: 1, content: [{type: "paragraph", content: [{type: "text", text: ("Recurring failure. Details:\n\n" + $body)}]}]}}')
  curl -fsS --connect-timeout 15 --max-time 60 -u "$AUTH" -H 'Content-Type: application/json' \
    -X POST --data "$COMMENT_PAYLOAD" "$API/issue/$EXISTING_KEY/comment" >/dev/null
  echo "$EXISTING_KEY"
  exit 0
fi

# ADF document: the body file holds plain text; blank lines split paragraphs.
ADF_DOC=$(jq -n --arg body "$BODY" '
  [$body | split("\n\n")[] | {type: "paragraph", content: [{type: "text", text: .}]}] |
  {type: "doc", version: 1, content: .}')

ISSUE_PAYLOAD=$(jq -n --arg project "$PROJECT" --arg summary "$SUMMARY" --arg priority "$PRIORITY" \
  --argjson doc "$ADF_DOC" --argjson labels "$(printf '%s\n' "${LABELS[@]:-}" | jq -R . | jq -s 'map(select(length > 0))')" \
  --argjson components "$(printf '%s\n' "${COMPONENTS[@]:-}" | jq -R . | jq -s 'map(select(length > 0) | {name: .})')" '
  {fields: ({
    project: {key: $project},
    summary: $summary,
    description: $doc,
    issuetype: {name: "Task"},
    priority: {name: $priority},
    labels: $labels
  } + (if ($components | length) > 0 then {components: $components} else {} end))}')

ISSUE_KEY=$(curl -fsS --connect-timeout 15 --max-time 60 -u "$AUTH" -H 'Content-Type: application/json' \
  -X POST --data "$ISSUE_PAYLOAD" "$API/issue" | jq -r '.key')

if [ -n "$STATUS_FILE" ]; then
  echo created > "$STATUS_FILE"
fi
echo "$ISSUE_KEY"
