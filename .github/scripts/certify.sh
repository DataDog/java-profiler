#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc

# Mark a commit as release-certified by attaching a git note on the
# 'certification' notes ref and pushing it to origin.
#
# Usage:
#   certify.sh <commit-sha> --run-url <url> [--suite <text>]
#
# The note body is a single-line JSON object with the commit, timestamp,
# workflow run URL and the certification suite summary. Re-running on an
# already-certified commit is a no-op (exit 0).

NOTES_REF="refs/notes/certification"

usage() {
  echo "Usage: $0 <commit-sha> --run-url <url> [--suite <text>]" >&2
  exit 2
}

SHA=""
RUN_URL=""
SUITE="nightly certification"

while [ $# -gt 0 ]; do
  case "$1" in
    --run-url) RUN_URL="$2"; shift 2 ;;
    --suite) SUITE="$2"; shift 2 ;;
    -h|--help) usage ;;
    -*) echo "ERROR: unknown option: $1" >&2; exit 2 ;;
    *) SHA="$1"; shift ;;
  esac
done

if [ -z "$SHA" ]; then
  usage
fi

if ! git rev-parse --verify --quiet "$SHA^{commit}" >/dev/null; then
  echo "ERROR: not a commit: $SHA" >&2
  exit 1
fi
SHA=$(git rev-parse "$SHA^{commit}")

# '+' allows non-fast-forward notes updates, which are routine for git notes.
# A missing notes ref on origin is normal (first certification); any other
# fetch failure must fail loudly, else the already-certified check runs
# against a stale ref.
if ! git fetch origin "+$NOTES_REF:$NOTES_REF" 2>/dev/null; then
  if git ls-remote --exit-code origin "$NOTES_REF" >/dev/null 2>&1; then
    echo "ERROR: failed to fetch $NOTES_REF from origin" >&2
    exit 1
  fi
  echo "No certification notes on origin yet"
fi

if git notes --ref=certification list 2>/dev/null | awk '{print $2}' | grep -qx "$SHA"; then
  echo "Commit $SHA is already certified; nothing to do"
  exit 0
fi

CERTIFIED_AT=$(date -u +%Y-%m-%dT%H:%M:%SZ)
NOTE="{\"commit\":\"$SHA\",\"certified_at\":\"$CERTIFIED_AT\",\"run_url\":\"$RUN_URL\",\"suite\":\"$SUITE\"}"

git notes --ref=certification add -f -m "$NOTE" "$SHA"
git push origin "$NOTES_REF"

echo "Certified $SHA"
echo "$NOTE"
