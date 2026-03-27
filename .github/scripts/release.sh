#!/usr/bin/env bash

set -x
set -e

TYPE=$1
DRYRUN=$2

BRANCH=$(git branch --show-current)
RELEASE_BRANCH=

BASE=$(./gradlew printVersion -Psnapshot=false | grep 'Version:' | cut -f2 -d' ')
# BASE == 0.0.1

create_annotated_tag() {
  local version=$1
  local type=$2
  local branch=$3

  local tag_name="v_${version}"
  local tag_message="Release v_${version} (${type,,}) from ${branch}"

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
  create_annotated_tag "$BASE" "$TYPE" "$BRANCH"
fi

if [ "$TYPE" == "PATCH" ]; then
  if [[ ! $BRANCH =~ ^release\/[0-9]+\.[0-9]+\._$ ]] && [ -z "$DRYRUN" ]; then
    echo "Patch release can be created only for 'release/*' branch."
    exit 1
  fi
  RELEASE_BRANCH="release/${BASE%.*}._"
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
  exit 0
fi

if [ "$BRANCH" != "$RELEASE_BRANCH" ]; then
  git checkout -b $RELEASE_BRANCH
  if ! git diff --quiet; then
    git add build.gradle.kts
    git commit -m "[Automated] Release ${BASE}"
  fi
  git push $DRYRUN --atomic --set-upstream origin $RELEASE_BRANCH
  git checkout $BRANCH
fi

if [ "$TYPE" == "MAJOR" ] || [ "$TYPE" == "MINOR" ]; then
  ./gradlew incrementVersion --versionIncrementType=MINOR
else
  ./gradlew incrementVersion --versionIncrementType=PATCH
fi

CANDIDATE=$(./gradlew printVersion -Psnapshot=false | grep 'Version:' | cut -f2 -d' ')

git add build.gradle.kts
git commit -m "[Automated] Bump dev version to ${CANDIDATE}"

git push $DRYRUN --atomic --set-upstream origin $BRANCH
git push $DRYRUN --atomic --tags

echo "==================== RELEASE SUMMARY ===================="
echo "Release Type: $TYPE"
echo "Released Version: $BASE"
echo "Next Dev Version: $CANDIDATE"
echo "Release Branch: $RELEASE_BRANCH"
echo "Tag: v_$BASE"
if [ -z "$DRYRUN" ]; then
  echo "Tag Message: $(git tag -l v_$BASE -n1 --format='%(contents:subject)')"
fi
echo "=========================================================="
