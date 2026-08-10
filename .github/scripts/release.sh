#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc

# Create a release tag (and release branch for minor/major) from the current
# HEAD. Version is computed from git tags — no file modifications, no bump PRs.
#
# Usage:
#   release.sh <TYPE> [--dry-run]
#
# TYPE: MINOR | MAJOR | PATCH | RETAG
#
# Branch rules:
#   MINOR/MAJOR: must be run from 'main'
#   PATCH/RETAG: must be run from 'release/X.Y._'

TYPE=$1
DRYRUN=""

# Parse remaining args for --dry-run
shift
while [ $# -gt 0 ]; do
  case "$1" in
    --dry-run) DRYRUN="--dry-run"; shift ;;
    *) echo "ERROR: unknown argument: $1" >&2; exit 1 ;;
  esac
done

BRANCH=$(git branch --show-current)
SOURCE_SHA=$(git rev-parse HEAD)
RELEASE_BRANCH=
RELEASE_VERSION=

# --- RETAG: re-point an existing tag at the current HEAD ---------------------
# Unchanged from the previous flow. Use when a partial release (tag created,
# but no Maven artifacts / no final GitHub release) needs additional commits.
if [ "$TYPE" == "RETAG" ]; then
  if [[ ! $BRANCH =~ ^release\/[0-9]+\.[0-9]+\._$ ]] && [ -z "$DRYRUN" ]; then
    echo "Retag can only be performed from a 'release/*' branch."
    exit 1
  fi

  # Compute the current release version for this branch
  RELEASE_VERSION=$(utils/compute-version.sh --release --patch)
  TAG_NAME="v_${RELEASE_VERSION}"

  if ! git rev-parse "$TAG_NAME" >/dev/null 2>&1; then
    echo "::error::Tag $TAG_NAME does not exist. Use a normal release to create a new tag."
    exit 1
  fi

  # Refuse to retag if the GitHub release is already public
  if command -v gh >/dev/null 2>&1 && [ -z "$DRYRUN" ]; then
    IS_DRAFT=$(gh release view "$TAG_NAME" --json isDraft --jq '.isDraft' 2>/dev/null || echo "not-found")
    if [ "$IS_DRAFT" == "false" ]; then
      echo "::error::GitHub release $TAG_NAME is already public. Retagging is not allowed."
      exit 1
    fi
  fi

  if [ -z "$DRYRUN" ]; then
    git tag -f -a "$TAG_NAME" -m "Release v_${RELEASE_VERSION} (retag) from ${BRANCH}"
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
  echo "Retagged Version: $RELEASE_VERSION"
  echo "Tag: $TAG_NAME -> $(git rev-parse HEAD)"
  echo "========================================================"
  if [ -n "${GITHUB_OUTPUT:-}" ]; then
    {
      echo "base_branch=$BRANCH"
      echo "source_sha=$SOURCE_SHA"
      echo "release_version=$RELEASE_VERSION"
      echo "release_branch=$BRANCH"
    } >> "$GITHUB_OUTPUT"
  fi
  exit 0
fi

# --- Validate branch and compute release version -----------------------------

if [ "$TYPE" == "PATCH" ]; then
  if [[ ! $BRANCH =~ ^release\/[0-9]+\.[0-9]+\._$ ]] && [ -z "$DRYRUN" ]; then
    echo "Patch release can be created only for 'release/*' branch."
    exit 1
  fi
  RELEASE_VERSION=$(utils/compute-version.sh --release --patch)
  RELEASE_BRANCH="release/${RELEASE_VERSION%.*}._"
elif [ "$TYPE" == "MINOR" ]; then
  if [ "$BRANCH" != "main" ] && [ -z "$DRYRUN" ]; then
    echo "Minor release can be performed only from 'main' branch."
    exit 1
  fi
  RELEASE_VERSION=$(utils/compute-version.sh --release --minor)
  RELEASE_BRANCH="release/${RELEASE_VERSION%.*}._"
elif [ "$TYPE" == "MAJOR" ]; then
  if [ "$BRANCH" != "main" ] && [ -z "$DRYRUN" ]; then
    echo "Major release can be performed only from 'main' branch."
    exit 1
  fi
  RELEASE_VERSION=$(utils/compute-version.sh --release --major)
  RELEASE_BRANCH="release/${RELEASE_VERSION%.*}._"
else
  echo "ERROR: Invalid release type: $TYPE (expected MINOR, MAJOR, PATCH, or RETAG)" >&2
  exit 1
fi

# --- Check tag doesn't already exist ----------------------------------------

TAG_NAME="v_${RELEASE_VERSION}"
if git rev-parse "$TAG_NAME" >/dev/null 2>&1; then
  if [ -z "$DRYRUN" ]; then
    echo "::error::Tag $TAG_NAME already exists"
    exit 1
  else
    echo "[DRY-RUN] Tag $TAG_NAME exists (would fail)"
    exit 1
  fi
fi

# --- Create annotated tag ---------------------------------------------------

lowercase_type=$(tr '[:upper:]' '[:lower:]' <<<"$TYPE")
tag_message="Release v_${RELEASE_VERSION} (${lowercase_type}) from ${BRANCH}"

if [ -z "$DRYRUN" ]; then
  git tag -a "$TAG_NAME" -m "$tag_message"
  echo "✓ Created annotated tag: $TAG_NAME"
else
  echo "[DRY-RUN] Would create tag: $TAG_NAME"
  echo "[DRY-RUN] Message: $tag_message"
fi

# --- Create release branch (minor/major only) -------------------------------

if [ "$TYPE" != "PATCH" ]; then
  if [ -z "$DRYRUN" ]; then
    git branch "$RELEASE_BRANCH" "$SOURCE_SHA"
    echo "✓ Created release branch: $RELEASE_BRANCH"
  else
    echo "[DRY-RUN] Would create branch: $RELEASE_BRANCH"
  fi
fi

# --- Push -------------------------------------------------------------------

if [ -z "$DRYRUN" ]; then
  if [ "$TYPE" == "PATCH" ]; then
    git push origin "$TAG_NAME"
  else
    git push --atomic origin "$TAG_NAME" "$RELEASE_BRANCH"
  fi
  echo "✓ Pushed tag $TAG_NAME"
  if [ "$TYPE" != "PATCH" ]; then
    echo "✓ Pushed branch $RELEASE_BRANCH"
  fi
else
  if [ "$TYPE" == "PATCH" ]; then
    echo "[DRY-RUN] Would push tag $TAG_NAME"
  else
    echo "[DRY-RUN] Would push tag $TAG_NAME and branch $RELEASE_BRANCH"
  fi
fi

# --- Output -----------------------------------------------------------------

if [ -n "${GITHUB_OUTPUT:-}" ]; then
  {
    echo "base_branch=$BRANCH"
    echo "source_sha=$SOURCE_SHA"
    echo "release_version=$RELEASE_VERSION"
    echo "release_branch=$RELEASE_BRANCH"
  } >> "$GITHUB_OUTPUT"
fi

echo "==================== RELEASE SUMMARY ===================="
echo "Release Type: $TYPE"
echo "Released Version: $RELEASE_VERSION"
echo "Release Branch: $RELEASE_BRANCH"
echo "Tag: $TAG_NAME"
if [ -z "$DRYRUN" ]; then
  echo "Tag Message: $(git tag -l "$TAG_NAME" -n1 --format='%(contents:subject)')"
fi
echo "=========================================================="
