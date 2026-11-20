#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc

# Select the release-train candidate: the newest certified commit that the
# release train has not released yet.
#
# Usage:
#   pick-release-candidate.sh
#
# A certified commit qualifies only when the newest v_* release tag's commit
# is a strict ancestor of it. This guarantees the train never releases twice
# from the same certified commit and never releases a commit older than the
# last release.
#
# Output on stdout: the candidate commit SHA (exit 0), or "none: <reason>"
# (exit 10). Any other failure exits non-zero.

NOTES_REF="refs/notes/certification"

git fetch origin "$NOTES_REF:$NOTES_REF" 2>/dev/null || true

# Certified commits, newest (by commit date) first.
CERTIFIED=$(git notes --ref=certification list 2>/dev/null | awk '{print $2}' | sort -u || true)
if [ -z "$CERTIFIED" ]; then
  echo "none: no certified commits"
  exit 10
fi

NEWEST_CERTIFIED=$(for sha in $CERTIFIED; do
  git show -s --format='%ct %H' "$sha" 2>/dev/null || true
done | sort -rn | awk 'NR==1 {print $2}')
if [ -z "$NEWEST_CERTIFIED" ]; then
  echo "none: certification notes point at unknown commits"
  exit 10
fi

# Newest release tag, ordered like compute-version.sh orders versions.
TAG=$(git tag --list 'v_*' | sed 's/^v_//' | sort -t. -k1,1n -k2,2n -k3,3n | tail -1)
if [ -n "$TAG" ]; then
  TAG_COMMIT=$(git rev-parse --verify --quiet "v_${TAG}^{commit}" || true)
  if [ -z "$TAG_COMMIT" ]; then
    echo "ERROR: tag v_${TAG} does not resolve to a commit" >&2
    exit 1
  fi

  if [ "$NEWEST_CERTIFIED" == "$TAG_COMMIT" ]; then
    echo "none: newest certified commit $NEWEST_CERTIFIED is already released (v_${TAG})"
    exit 10
  fi

  if ! git merge-base --is-ancestor "$TAG_COMMIT" "$NEWEST_CERTIFIED"; then
    echo "none: newest certified commit $NEWEST_CERTIFIED predates the last release v_${TAG}"
    exit 10
  fi
fi

echo "$NEWEST_CERTIFIED"
