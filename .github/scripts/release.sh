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
fi

if [ "$BRANCH" != "$RELEASE_BRANCH" ]; then
  git checkout -b $RELEASE_BRANCH
  if ! git diff --quiet; then
    git add build.gradle
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

git add build.gradle
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
