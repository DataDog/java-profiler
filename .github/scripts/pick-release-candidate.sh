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

# A missing notes ref on origin is normal (first certification); any other
# fetch failure must fail loudly — a stale or absent local ref would make the
# train skip a release that should run. '+' allows non-fast-forward notes
# updates, which are routine for git notes.
if ! git fetch origin "+$NOTES_REF:$NOTES_REF" 2>/dev/null; then
  # ls-remote exit 2 means the ref is absent on origin (normal before the
  # first certification); any other status is a transport failure and must
  # fail loudly, else the candidate choice runs against a stale ref.
  LS_RC=0
  git ls-remote --exit-code origin "$NOTES_REF" >/dev/null 2>&1 || LS_RC=$?
  if [ "$LS_RC" -eq 2 ]; then
    echo "No certification notes on origin yet" >&2
  else
    echo "ERROR: failed to fetch $NOTES_REF from origin (ls-remote rc=$LS_RC)" >&2
    exit 1
  fi
fi

# Certified commits known to this clone.
CERTIFIED=$(git notes --ref=certification list 2>/dev/null | awk '{print $2}' | sort -u || true)
if [ -z "$CERTIFIED" ]; then
  echo "none: no certified commits"
  exit 10
fi

# Newest certified commit by history position on main, not by committer
# date: rebases and cherry-picks make dates unreliable, and same-second
# commits make date ties arbitrary. The first certified commit in
# rev-list --first-parent --topo-order of origin/main is the tip-most
# MAINLINE one: without --first-parent a certified commit sitting on a
# merged side branch would sort ahead of the mainline tip that actually
# carries it. Certified commits unreachable from origin/main cannot be
# candidates.
CERT_LIST=$(mktemp)
printf '%s\n' "$CERTIFIED" > "$CERT_LIST"
if ! git rev-parse --verify --quiet origin/main >/dev/null; then
  echo "ERROR: origin/main is not available" >&2
  exit 1
fi
# First certified commit on main's first-parent line (--first-parent:
# side branches of merge commits are not mainline history). rev-list
# writes to a file so its failure aborts under set -e instead of silently
# feeding awk an empty stream; awk exits 0 on both match and no-match, so
# the empty case falls through to the guard below.
MAIN_ORDER=$(mktemp)
git rev-list origin/main --first-parent --topo-order > "$MAIN_ORDER"
NEWEST_CERTIFIED=$(awk 'NR==FNR { want[$1] = 1; next } $1 in want { print; exit }' \
  "$CERT_LIST" "$MAIN_ORDER")
rm -f "$CERT_LIST" "$MAIN_ORDER"
if [ -z "$NEWEST_CERTIFIED" ]; then
  echo "none: no certified commit is reachable from origin/main"
  exit 10
fi

# Newest release tag whose commit is on main (a maintenance-branch patch
# tag is newer by version but does not gate the mainline train). Ordered
# with the same version sort compute-version.sh uses.
TAG=""
TAG_COMMIT=""
for t in $(git tag --list 'v_*' | sed 's/^v_//' | sort -t. -k1,1n -k2,2n -k3,3n | awk '{a[NR]=$0} END {for (i=NR; i>=1; i--) print a[i]}'); do
  c=$(git rev-parse --verify --quiet "v_${t}^{commit}" || true)
  if [ -n "$c" ] && git merge-base --is-ancestor "$c" origin/main; then
    TAG="$t"
    TAG_COMMIT="$c"
    break
  fi
done
if [ -n "$TAG" ]; then
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
