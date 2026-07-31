#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

set -euo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
REPO=""
BASE=""
HEAD=""
SOURCE_SHA=""
EXPECTED_HEAD_SHA=""
RUN_ID=""
LABEL="trivial"
APPROVER="dd-octo-sts[bot]"

usage() {
  cat <<EOF
Usage: $0 --repo OWNER/REPO --base BRANCH --head BRANCH \\
  --source-sha SHA --head-sha SHA --run-id ID

Creates or resumes the human-authored post-release version-bump PR, waits for
approval of the exact validated commit, and squash-merges only that commit.
It never enables queued auto-merge and never bypasses branch protection.
EOF
}

die() {
  echo "ERROR: $*" >&2
  exit 1
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --repo) REPO=${2:-}; shift 2 ;;
    --base) BASE=${2:-}; shift 2 ;;
    --head) HEAD=${2:-}; shift 2 ;;
    --source-sha) SOURCE_SHA=${2:-}; shift 2 ;;
    --head-sha) EXPECTED_HEAD_SHA=${2:-}; shift 2 ;;
    --run-id) RUN_ID=${2:-}; shift 2 ;;
    --help) usage; exit 0 ;;
    *) die "Unknown argument: $1" ;;
  esac
done

if [ -z "$REPO" ] || [ -z "$BASE" ] || [ -z "$HEAD" ] ||
   [ -z "$SOURCE_SHA" ] || [ -z "$EXPECTED_HEAD_SHA" ] || [ -z "$RUN_ID" ]; then
  die "All arguments are required; use --help for details"
fi

[[ "$SOURCE_SHA" =~ ^[0-9a-f]{40}$ ]] || die "Invalid source SHA"
[[ "$EXPECTED_HEAD_SHA" =~ ^[0-9a-f]{40}$ ]] || die "Invalid head SHA"
[[ "$RUN_ID" =~ ^[0-9]+$ ]] || die "Invalid workflow run ID"

command -v gh >/dev/null || die "GitHub CLI (gh) is required"
PERMISSION=$(gh repo view "$REPO" --json viewerPermission --jq '.viewerPermission')
case "$PERMISSION" in
  WRITE|MAINTAIN|ADMIN) ;;
  *) die "The authenticated user needs write, maintain, or admin access to $REPO" ;;
esac

"$ROOT/.github/scripts/validate-release-bump.sh" \
  --repo "$REPO" \
  --branch \
  --base "$BASE" \
  --head "$HEAD" \
  --source-sha "$SOURCE_SHA" \
  --expected-head-sha "$EXPECTED_HEAD_SHA"

VERSION=${HEAD#automated/bump-}
VERSION=${VERSION//-/.}
TITLE="[Automated] Bump dev version to $VERSION"
BODY="Automated version bump after release workflow run https://github.com/$REPO/actions/runs/$RUN_ID.

Validated source: \`$SOURCE_SHA\`
Validated bump: \`$EXPECTED_HEAD_SHA\`"

PR_DATA=$(gh pr list --repo "$REPO" --state all --base "$BASE" --head "$HEAD" \
  --json number,state,isDraft,mergedAt,headRefOid,title --limit 10)
MATCH_COUNT=$(jq --arg sha "$EXPECTED_HEAD_SHA" \
  '[.[] | select(.headRefOid == $sha)] | length' <<<"$PR_DATA")
[ "$MATCH_COUNT" -le 1 ] || die "Multiple PRs refer to the expected bump commit"
TOTAL_COUNT=$(jq 'length' <<<"$PR_DATA")
[ "$TOTAL_COUNT" -eq "$MATCH_COUNT" ] ||
  die "A PR already exists for $HEAD at a different commit; refusing recovery"

if [ "$MATCH_COUNT" -eq 1 ]; then
  PR_NUMBER=$(jq -r --arg sha "$EXPECTED_HEAD_SHA" \
    '.[] | select(.headRefOid == $sha) | .number' <<<"$PR_DATA")
  PR_STATE=$(jq -r --arg sha "$EXPECTED_HEAD_SHA" \
    '.[] | select(.headRefOid == $sha) | .state' <<<"$PR_DATA")
  MERGED_AT=$(jq -r --arg sha "$EXPECTED_HEAD_SHA" \
    '.[] | select(.headRefOid == $sha) | .mergedAt // empty' <<<"$PR_DATA")
  [ -z "$MERGED_AT" ] || {
    echo "Release bump PR #$PR_NUMBER was already merged."
    exit 0
  }
  [ "$PR_STATE" = "OPEN" ] || die "Matching PR #$PR_NUMBER is closed without merge"
else
  PR_URL=$(gh pr create --repo "$REPO" --base "$BASE" --head "$HEAD" \
    --title "$TITLE" --body "$BODY")
  PR_NUMBER=${PR_URL##*/}
fi

CURRENT=$(gh pr view "$PR_NUMBER" --repo "$REPO" \
  --json state,isDraft,headRefOid,title)
[ "$(jq -r '.state' <<<"$CURRENT")" = "OPEN" ] || die "PR #$PR_NUMBER is not open"
[ "$(jq -r '.isDraft' <<<"$CURRENT")" = "false" ] || die "PR #$PR_NUMBER is a draft"
[ "$(jq -r '.headRefOid' <<<"$CURRENT")" = "$EXPECTED_HEAD_SHA" ] ||
  die "PR head changed before labeling"
[ "$(jq -r '.title' <<<"$CURRENT")" = "$TITLE" ] ||
  die "PR title differs from the validated title"

has_exact_approval() {
  gh api --paginate "repos/$REPO/pulls/$PR_NUMBER/reviews?per_page=100" --slurp \
    --jq "add | any(.user.login == \"$APPROVER\" and .state == \"APPROVED\" and .commit_id == \"$EXPECTED_HEAD_SHA\")"
}

if [ "$(has_exact_approval)" != "true" ]; then
  EXISTING_LABEL=$(gh pr view "$PR_NUMBER" --repo "$REPO" --json labels \
    --jq ".labels | any(.name == \"$LABEL\")")
  if [ "$EXISTING_LABEL" = "true" ]; then
    gh pr edit "$PR_NUMBER" --repo "$REPO" --remove-label "$LABEL"
  fi
  gh pr edit "$PR_NUMBER" --repo "$REPO" --add-label "$LABEL"
fi

echo "Waiting for $APPROVER to approve commit $EXPECTED_HEAD_SHA..."
for _ in $(seq 1 30); do
  CURRENT_SHA=$(gh pr view "$PR_NUMBER" --repo "$REPO" --json headRefOid \
    --jq '.headRefOid')
  [ "$CURRENT_SHA" = "$EXPECTED_HEAD_SHA" ] ||
    die "PR head changed while waiting for approval"
  if [ "$(has_exact_approval)" = "true" ]; then
    break
  fi
  sleep 10
done
[ "$(has_exact_approval)" = "true" ] ||
  die "Timed out waiting for exact bot approval. Resume with the same command."

echo "Waiting for required checks and merge readiness..."
gh pr checks "$PR_NUMBER" --repo "$REPO" --required --watch --fail-fast
for _ in $(seq 1 30); do
  CURRENT=$(gh pr view "$PR_NUMBER" --repo "$REPO" \
    --json headRefOid,mergeStateStatus)
  [ "$(jq -r '.headRefOid' <<<"$CURRENT")" = "$EXPECTED_HEAD_SHA" ] ||
    die "PR head changed while waiting for merge readiness"
  if [ "$(jq -r '.mergeStateStatus' <<<"$CURRENT")" = "CLEAN" ]; then
    break
  fi
  sleep 10
done
[ "$(gh pr view "$PR_NUMBER" --repo "$REPO" --json mergeStateStatus \
  --jq '.mergeStateStatus')" = "CLEAN" ] ||
  die "PR is not merge-ready. Resume with the same command."

gh pr merge "$PR_NUMBER" --repo "$REPO" --squash \
  --match-head-commit "$EXPECTED_HEAD_SHA"
[ -n "$(gh pr view "$PR_NUMBER" --repo "$REPO" --json mergedAt --jq '.mergedAt // empty')" ] ||
  die "GitHub did not report PR #$PR_NUMBER as merged"

echo "Release bump PR #$PR_NUMBER merged at exactly $EXPECTED_HEAD_SHA."
