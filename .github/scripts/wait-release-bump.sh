#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

set -euo pipefail

REPO=""
PR_NUMBER=""
EXPECTED_HEAD_SHA=""
POLL_ATTEMPTS=${RELEASE_BUMP_POLL_ATTEMPTS:-120}
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
    *) die "unknown argument: $1" ;;
  esac
done

[ -n "$REPO" ] && [ -n "$PR_NUMBER" ] && [ -n "$EXPECTED_HEAD_SHA" ] ||
  die "--repo, --pr-number, and --expected-head-sha are required"
[[ "$PR_NUMBER" =~ ^[0-9]+$ ]] || die "invalid PR number"
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

for ((attempt = 1; attempt <= POLL_ATTEMPTS; attempt++)); do
  PR=$(read_pr)
  verify_head "$PR"
  if [ "$(jq -r '.merged_at // ""' <<<"$PR")" = "" ] &&
     [ "$(jq -er '.state' <<<"$PR")" != "open" ]; then
    die "PR closed without merging"
  fi

  if gh api --paginate "repos/$REPO/pulls/$PR_NUMBER/reviews?per_page=100" \
      --slurp --jq \
      "add | any(.user.login == \"dd-octo-sts[bot]\" and .state == \"APPROVED\" and .commit_id == \"$EXPECTED_HEAD_SHA\")" |
      grep -qx true; then
    APPROVED=true
    break
  fi
  sleep "$POLL_SECONDS"
done

[ "${APPROVED:-false}" = "true" ] ||
  die "timed out waiting for the exact-SHA STS approval"

CHECKS_VISIBLE=false
for ((attempt = 1; attempt <= POLL_ATTEMPTS; attempt++)); do
  CHECK_COUNT=$(gh pr checks "$PR_NUMBER" --repo "$REPO" --required \
    --json name --jq 'length' 2>/dev/null || true)
  if [[ "$CHECK_COUNT" =~ ^[1-9][0-9]*$ ]]; then
    CHECKS_VISIBLE=true
    break
  fi
  PR=$(read_pr)
  verify_head "$PR"
  sleep "$POLL_SECONDS"
done
[ "$CHECKS_VISIBLE" = "true" ] ||
  die "timed out waiting for required checks to be registered"

gh pr checks "$PR_NUMBER" --repo "$REPO" --required --watch --fail-fast

PR=$(read_pr)
verify_head "$PR"

for ((attempt = 1; attempt <= POLL_ATTEMPTS; attempt++)); do
  if [ "$(jq -r '.merged_at // ""' <<<"$PR")" != "" ]; then
    echo "Release bump PR #$PR_NUMBER is merged at $EXPECTED_HEAD_SHA"
    exit 0
  fi
  [ "$(jq -er '.state' <<<"$PR")" = "open" ] ||
    die "PR closed without merging"
  sleep "$POLL_SECONDS"
  PR=$(read_pr)
  verify_head "$PR"
done

die "required checks passed, but exact-SHA auto-merge did not complete"
