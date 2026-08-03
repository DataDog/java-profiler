#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

set -euo pipefail

REPO=""
PR_NUMBER=""
EXPECTED_HEAD_SHA=""
CHECK_NAMES=()
POLL_ATTEMPTS=${RELEASE_BUMP_POLL_ATTEMPTS:-360}
POLL_SECONDS=${RELEASE_BUMP_POLL_SECONDS:-5}

die() {
  echo "release-bump completion failed: $*" >&2
  exit 1
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --repo) REPO=${2:-}; shift 2 ;;
    --pr-number) PR_NUMBER=${2:-}; shift 2 ;;
    --expected-head-sha) EXPECTED_HEAD_SHA=${2:-}; shift 2 ;;
    --check) CHECK_NAMES+=("${2:-}"); shift 2 ;;
    *) die "unknown argument: $1" ;;
  esac
done

if [ -z "$REPO" ] || [ -z "$PR_NUMBER" ] || [ -z "$EXPECTED_HEAD_SHA" ]; then
  die "--repo, --pr-number, and --expected-head-sha are required"
fi
[[ "$PR_NUMBER" =~ ^[0-9]+$ ]] || die "invalid PR number"
[ "${#CHECK_NAMES[@]}" -gt 0 ] || die "at least one --check is required"
for check_name in "${CHECK_NAMES[@]}"; do
  [ -n "$check_name" ] || die "check names must not be empty"
done
[[ "$POLL_ATTEMPTS" =~ ^[1-9][0-9]*$ ]] || die "invalid poll attempts"
[[ "$POLL_SECONDS" =~ ^[0-9]+$ ]] || die "invalid poll interval"

read_pr() {
  gh api "repos/$REPO/pulls/$PR_NUMBER"
}

verify_head() {
  local pr=$1
  [ "$(jq -er '.head.sha' <<<"$pr")" = "$EXPECTED_HEAD_SHA" ] ||
    die "PR head changed from the validated release bump"
}

verify_open() {
  local pr=$1
  [ "$(jq -er '.state' <<<"$pr")" = "open" ] ||
    die "PR closed before approval, checks, and gated merge completed"
}

for ((attempt = 1; attempt <= POLL_ATTEMPTS; attempt++)); do
  PR=$(read_pr)
  verify_head "$PR"
  verify_open "$PR"

  if gh api --paginate "repos/$REPO/pulls/$PR_NUMBER/reviews?per_page=100" \
      --slurp |
      jq -e --arg expected_head_sha "$EXPECTED_HEAD_SHA" \
        'add | any(.user.login == "dd-octo-sts[bot]" and .state == "APPROVED" and .commit_id == $expected_head_sha)' \
        >/dev/null; then
    APPROVED=true
    break
  fi
  sleep "$POLL_SECONDS"
done

[ "${APPROVED:-false}" = "true" ] ||
  die "timed out waiting for the exact-SHA STS approval"

for ((attempt = 1; attempt <= POLL_ATTEMPTS; attempt++)); do
  PR=$(read_pr)
  verify_head "$PR"
  verify_open "$PR"

  CHECKS=$(gh pr checks "$PR_NUMBER" --repo "$REPO" \
    --json name,state 2>/dev/null || true)
  ALL_CHECKS_PASSED=true
  for check_name in "${CHECK_NAMES[@]}"; do
    CHECK_STATE=$(jq -r --arg name "$check_name" \
      '[.[] | select(.name == $name) | .state] | if length == 1 then .[0] else "" end' \
      <<<"${CHECKS:-[]}")
    if [ "$CHECK_STATE" = "SUCCESS" ]; then
      continue
    fi
    case "$CHECK_STATE" in
      ""|PENDING|QUEUED|IN_PROGRESS|WAITING|REQUESTED)
        ALL_CHECKS_PASSED=false
        ;;
      *)
        die "selected check $check_name completed with state $CHECK_STATE"
        ;;
    esac
  done
  if [ "$ALL_CHECKS_PASSED" = "true" ]; then
    break
  fi
  sleep "$POLL_SECONDS"
done
[ "${ALL_CHECKS_PASSED:-false}" = "true" ] ||
  die "timed out waiting for selected checks to pass"

PR=$(read_pr)
verify_head "$PR"
verify_open "$PR"

gh pr merge "$PR_NUMBER" --repo "$REPO" --squash \
  --match-head-commit "$EXPECTED_HEAD_SHA"

for ((attempt = 1; attempt <= POLL_ATTEMPTS; attempt++)); do
  PR=$(read_pr)
  verify_head "$PR"
  if [ "$(jq -r '.merged_at // ""' <<<"$PR")" != "" ]; then
    echo "Release bump PR #$PR_NUMBER is merged at $EXPECTED_HEAD_SHA"
    exit 0
  fi
  [ "$(jq -er '.state' <<<"$PR")" = "open" ] ||
    die "PR closed without merging"
  sleep "$POLL_SECONDS"
done

die "approval and selected checks passed, but exact-SHA merge did not complete"
