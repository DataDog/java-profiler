#!/usr/bin/env bash

set -x

TYPE=$1
DRYRUN=$2

BRANCH=$(git branch --show-current)
RELEASE_BRANCH=

BASE=$(./gradlew printVersion -Psnapshot=false | grep 'Version:' | cut -f2 -d' ')
# BASE == 0.0.1

if [ "$TYPE" == "MINOR" ] || [ "$TYPE" == "MAJOR" ]; then
  if [ "$BRANCH" != "main" ]; then
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
  git tag -f v_$BASE
fi

if [ "$TYPE" == "PATCH" ]; then
  if [[ ! $BRANCH =~ ^release\/[0-9]+\.[0-9]+\._$ ]]; then
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
  git push $DRYRUN --set-upstream origin $RELEASE_BRANCH
  git checkout $BRANCH
else
  git tag -f v_$BASE
fi

if [ "$TYPE" == "MAJOR" ] || [ "$TYPE" == "MINOR" ]; then
  ./gradlew incrementVersion --versionIncrementType=MINOR
else
  ./gradlew incrementVersion --versionIncrementType=PATCH
fi

CANDIDATE=$(./gradlew printVersion -Psnapshot=false | grep 'Version:' | cut -f2 -d' ')

git add build.gradle
git commit -m "[Automated] Bump dev version to ${CANDIDATE}"

git push $DRYRUN --set-upstream origin $BRANCH
git push $DRYRUN --tags