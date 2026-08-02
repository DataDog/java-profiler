#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

set -x
set -euo pipefail

TYPE=$1
DRYRUN=${2:-}

git_push() {
  if [ -n "$DRYRUN" ]; then
    git push "$DRYRUN" "$@"
  else
    git push "$@"
  fi
}

BRANCH=$(git branch --show-current)
SOURCE_SHA=$(git rev-parse HEAD)
RELEASE_BRANCH=

BASE=$(./gradlew printVersion -Psnapshot=false | grep 'Version:' | cut -f2 -d' ')
# BASE == 0.0.1

# Refuse to tag a version whose post-release bump PR never merged: the
# branch's build.gradle.kts still shows an already-tagged version, so
# proceeding would either re-tag it (rejected below) or silently skip
# release creation while still looking like a successful run.
check_not_stuck() {
  local base=$1
  local branch=$2

  if [ -n "$DRYRUN" ]; then
    return 0
  fi

  if ! git show-ref --verify --quiet "refs/tags/v_${base}"; then
    return 0
  fi

  echo "::error::${branch} is stuck at version ${base}, which is already tagged (v_${base})."
  echo "::error::The automated post-release version-bump PR for this branch was never merged."
  local stuck_pr
  stuck_pr=$(gh pr list --state open --base "$branch" --json headRefName,url \
    --jq '[.[] | select(.headRefName | startswith("automated/bump-"))][0].url' 2>/dev/null || true)
  if [ -n "$stuck_pr" ]; then
    echo "::error::Merge the pending bump PR first, then retry: $stuck_pr"
  else
    echo "::error::No pending bump PR was found. Bump ${branch}'s version manually and merge it before retrying the release."
  fi
  exit 1
}

create_annotated_tag() {
  local version=$1
  local type=$2
  local branch=$3

  local tag_name="v_${version}"
  local lowercase_type
  lowercase_type=$(tr '[:upper:]' '[:lower:]' <<<"$type")
  local tag_message="Release v_${version} (${lowercase_type}) from ${branch}"

  # Check if tag exists
  if git rev-parse "$tag_name" >/dev/null 2>&1; then
    if [ -z "$DRYRUN" ]; then
      echo "::error::Tag $tag_name already exists"
      exit 1
    else
      echo "[DRY-RUN] Tag $tag_name exists (would fail)"
      return
    fi
  fi

  if [ -z "$DRYRUN" ]; then
    git tag -a "$tag_name" -m "$tag_message"
    echo "✓ Created annotated tag: $tag_name"
  else
    echo "[DRY-RUN] Would create tag: $tag_name"
    echo "[DRY-RUN] Message: $tag_message"
  fi
}

if [ "$TYPE" == "MINOR" ] || [ "$TYPE" == "MAJOR" ]; then
  if [ "$BRANCH" != "main" ] && [ -z "$DRYRUN" ]; then
    echo "Major or minor release can be performed only from 'main' branch."
    exit 1
  fi
  if [ "$TYPE" == "MAJOR" ]; then
    # 0.1.0 -> 1.0.0
    ./gradlew incrementVersion --versionIncrementType=MAJOR
    BASE=$(./gradlew printVersion -Psnapshot=false | grep 'Version:' | cut -f2 -d' ')
    # BASE == 1.0.0
  fi
  RELEASE_BRANCH="release/${BASE%.*}._"
  check_not_stuck "$BASE" "$BRANCH"
  if [ "$TYPE" == "MINOR" ]; then
    create_annotated_tag "$BASE" "$TYPE" "$BRANCH"
  fi
fi

if [ "$TYPE" == "PATCH" ]; then
  if [[ ! $BRANCH =~ ^release\/[0-9]+\.[0-9]+\._$ ]] && [ -z "$DRYRUN" ]; then
    echo "Patch release can be created only for 'release/*' branch."
    exit 1
  fi
  RELEASE_BRANCH="release/${BASE%.*}._"
  check_not_stuck "$BASE" "$BRANCH"
  create_annotated_tag "$BASE" "$TYPE" "$BRANCH"
fi

# RETAG: re-point an existing tag at the current HEAD of a release branch.
# Use when a partial release (tag + branch created, but no Maven artifacts and
# no final GitHub release yet) needs additional commits (e.g. a cherry-picked fix).
if [ "$TYPE" == "RETAG" ]; then
  if [[ ! $BRANCH =~ ^release\/[0-9]+\.[0-9]+\._$ ]] && [ -z "$DRYRUN" ]; then
    echo "Retag can only be performed from a 'release/*' branch."
    exit 1
  fi
  TAG_NAME="v_${BASE}"
  if ! git rev-parse "$TAG_NAME" >/dev/null 2>&1; then
    echo "::error::Tag $TAG_NAME does not exist. Use a normal release to create a new tag."
    exit 1
  fi

  # Refuse to retag if the GitHub release is already public
  if command -v gh >/dev/null 2>&1; then
    IS_DRAFT=$(gh release view "$TAG_NAME" --json isDraft --jq '.isDraft' 2>/dev/null || echo "not-found")
    if [ "$IS_DRAFT" == "false" ]; then
      echo "::error::GitHub release $TAG_NAME is already public. Retagging is not allowed."
      exit 1
    fi
  fi

  if [ -z "$DRYRUN" ]; then
    git tag -f -a "$TAG_NAME" -m "Release v_${BASE} (retag) from ${BRANCH}"
    git push --force-with-lease origin "$BRANCH"
    git push origin :"$TAG_NAME"
    git push origin "$TAG_NAME"
  else
    echo "[DRY-RUN] Would force-move tag $TAG_NAME to $(git rev-parse HEAD)"
    echo "[DRY-RUN] Would push $BRANCH with --force-with-lease"
    echo "[DRY-RUN] Would delete and re-push remote tag $TAG_NAME"
  fi

  echo "==================== RETAG SUMMARY ===================="
  echo "Release Branch: $BRANCH"
  echo "Retagged Version: $BASE"
  echo "Tag: $TAG_NAME -> $(git rev-parse HEAD)"
  echo "========================================================"
  if [ -n "${GITHUB_OUTPUT:-}" ]; then
    {
      echo "base_branch=$BRANCH"
      echo "source_sha=$SOURCE_SHA"
      echo "release_version=$BASE"
      echo "release_branch=$BRANCH"
    } >> "$GITHUB_OUTPUT"
  fi
  exit 0
fi

if [ "$BRANCH" != "$RELEASE_BRANCH" ]; then
  git checkout -b "$RELEASE_BRANCH"
  if ! git diff --quiet; then
    git add build.gradle.kts
    git commit -m "[Automated] Release ${BASE}"
  fi
  if [ "$TYPE" == "MAJOR" ]; then
    create_annotated_tag "$BASE" "$TYPE" "$BRANCH"
  fi
  git_push --atomic --set-upstream origin "$RELEASE_BRANCH"
  git checkout "$BRANCH"
fi

if [ "$TYPE" == "MAJOR" ]; then
  # The release commit stays on release/X.0._. Main moves directly from the
  # previous development version to X.1.0 through the validated bump PR.
  ./gradlew incrementVersion --versionIncrementType=MAJOR
  ./gradlew incrementVersion --versionIncrementType=MINOR
elif [ "$TYPE" == "MINOR" ]; then
  ./gradlew incrementVersion --versionIncrementType=MINOR
else
  ./gradlew incrementVersion --versionIncrementType=PATCH
fi

CANDIDATE=$(./gradlew printVersion -Psnapshot=false | grep 'Version:' | cut -f2 -d' ')

FINAL_BUMP_MESSAGE="[Automated] Bump dev version to ${CANDIDATE}"
git add build.gradle.kts
# GITHUB_TOKEN-created pull_request.opened events do not start other workflows.
# Open the PR from this temporary commit, then amend and push the canonical
# commit through SSH so GitHub emits a normal pull_request.synchronize event.
git commit -m "[Automated] Prepare dev version bump to ${CANDIDATE}"

if [ -z "$DRYRUN" ]; then
  : "${GITHUB_REPOSITORY:?GITHUB_REPOSITORY is required}"
  : "${GITHUB_TOKEN:?GITHUB_TOKEN is required}"
  : "${BUMP_LABEL_TOKEN:?BUMP_LABEL_TOKEN is required}"
  BUMP_BRANCH="automated/bump-${CANDIDATE//./-}"
  git checkout -b "$BUMP_BRANCH"
  git push --force-with-lease --set-upstream origin "$BUMP_BRANCH"
  INITIAL_BUMP_SHA=$(git rev-parse HEAD)

  if ! BUMP_PR_JSON=$(GH_TOKEN="$GITHUB_TOKEN" gh api --method POST \
      "repos/$GITHUB_REPOSITORY/pulls" \
      -f title="$FINAL_BUMP_MESSAGE" \
      -f head="$BUMP_BRANCH" \
      -f base="$BRANCH" \
      -f body="Automated post-release development version bump for v_$BASE."); then
    echo "::error::Unable to create the release bump PR with GITHUB_TOKEN."
    echo "::error::Verify that Actions is allowed to create and approve pull requests in repository settings."
    exit 1
  fi
  BUMP_PR_NUMBER=$(jq -er '.number' <<<"$BUMP_PR_JSON")
  BUMP_PR_URL=$(jq -er '.html_url' <<<"$BUMP_PR_JSON")

  git commit --amend -m "$FINAL_BUMP_MESSAGE"
  BUMP_HEAD_SHA=$(git rev-parse HEAD)
  [ "$BUMP_HEAD_SHA" != "$INITIAL_BUMP_SHA" ] || {
    echo "::error::Amending the bump commit did not change its SHA"
    exit 1
  }
  git push \
    --force-with-lease="refs/heads/$BUMP_BRANCH:$INITIAL_BUMP_SHA" \
    origin "$BUMP_BRANCH:$BUMP_BRANCH"

  # Validate every remotely visible commit before publishing the release tag,
  # which triggers artifact publication. Major preflight additionally proves
  # that the still-local annotated tag identifies the remote release commit.
  if [ "$TYPE" == "MAJOR" ]; then
    ./.github/scripts/validate-release-bump.sh \
      --repo "${GITHUB_REPOSITORY:?GITHUB_REPOSITORY is required}" \
      --branch \
      --base "$BRANCH" \
      --head "$BUMP_BRANCH" \
      --source-sha "$SOURCE_SHA" \
      --expected-head-sha "$BUMP_HEAD_SHA" \
      --local-release-tag "v_$BASE"
  else
    ./.github/scripts/validate-release-bump.sh \
      --repo "${GITHUB_REPOSITORY:?GITHUB_REPOSITORY is required}" \
      --branch \
      --base "$BRANCH" \
      --head "$BUMP_BRANCH" \
      --source-sha "$SOURCE_SHA" \
      --expected-head-sha "$BUMP_HEAD_SHA"
  fi
  git push --atomic --tags

  # The STS identity is deliberately distinct from github-actions[bot], which
  # created the PR. Its label event starts the trusted approval workflow.
  GH_TOKEN="$BUMP_LABEL_TOKEN" gh api --method POST \
    "repos/$GITHUB_REPOSITORY/issues/$BUMP_PR_NUMBER/labels" \
    -f 'labels[]=trivial' >/dev/null
  GH_TOKEN="$GITHUB_TOKEN" gh pr merge "$BUMP_PR_NUMBER" \
    --repo "$GITHUB_REPOSITORY" \
    --auto \
    --squash \
    --match-head-commit "$BUMP_HEAD_SHA"
  echo "✓ Version bump PR opened and queued for exact-SHA auto-merge: $BUMP_PR_URL"
else
  BUMP_BRANCH="automated/bump-${CANDIDATE//./-}"
  BUMP_HEAD_SHA=$(git rev-parse HEAD)
  BUMP_PR_NUMBER=
  BUMP_PR_URL=
  git_push --atomic --set-upstream origin "$BRANCH"
  git_push --atomic --tags
fi

if [ -n "${GITHUB_OUTPUT:-}" ]; then
  {
    echo "base_branch=$BRANCH"
    echo "source_sha=$SOURCE_SHA"
    echo "release_version=$BASE"
    echo "next_version=$CANDIDATE"
    echo "release_branch=$RELEASE_BRANCH"
    echo "bump_branch=$BUMP_BRANCH"
    echo "bump_head_sha=$BUMP_HEAD_SHA"
    echo "bump_pr_number=$BUMP_PR_NUMBER"
    echo "bump_pr_url=$BUMP_PR_URL"
  } >> "$GITHUB_OUTPUT"
fi

echo "==================== RELEASE SUMMARY ===================="
echo "Release Type: $TYPE"
echo "Released Version: $BASE"
echo "Next Dev Version: $CANDIDATE"
echo "Release Branch: $RELEASE_BRANCH"
echo "Tag: v_$BASE"
if [ -z "$DRYRUN" ]; then
  echo "Tag Message: $(git tag -l "v_$BASE" -n1 --format='%(contents:subject)')"
fi
echo "=========================================================="
