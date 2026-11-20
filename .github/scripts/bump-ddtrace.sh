#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc

# Bump the ddprof dependency in DataDog/dd-trace-java and open a draft PR.
#
# Environment:
#   DDTRACE_GH_TOKEN  token with contents:write + pull_requests:write on
#                     DataDog/dd-trace-java (required)
#
# Usage:
#   bump-ddtrace.sh <new-version> [release-notes-url]
#
# The change is exactly two files: gradle/libs.versions.toml (the ddprof
# version.ref) and dd-java-agent/ddprof-lib/gradle.lockfile. Skips (exit 0)
# when an open PR from a previous run already bumps to this version.

if [ $# -lt 1 ]; then
  echo "Usage: $0 <new-version> [release-notes-url]" >&2
  exit 2
fi

VERSION="$1"
NOTES_URL="${2:-https://github.com/DataDog/java-profiler/releases/tag/v_${VERSION}}"
REPO="DataDog/dd-trace-java"
BRANCH="ddprof/bump-${VERSION}"

if [ -z "${DDTRACE_GH_TOKEN:-}" ]; then
  echo "WARNING: DDTRACE_GH_TOKEN is not set; skipping dd-trace-java bump" >&2
  exit 3
fi

export GH_TOKEN="$DDTRACE_GH_TOKEN"
export GH_REPO="$REPO"

WORK_DIR=$(mktemp -d)
trap 'rm -rf "$WORK_DIR"' EXIT

gh repo clone "$REPO" "$WORK_DIR/repo" -- --depth 1 --no-tags
cd "$WORK_DIR/repo"

TOML="gradle/libs.versions.toml"
LOCK="dd-java-agent/ddprof-lib/gradle.lockfile"

OLD_VERSION=$(awk -F '"' '/^ddprof = / {print $2; exit}' "$TOML")
if [ -z "$OLD_VERSION" ]; then
  echo "ERROR: no ddprof version entry found in $TOML" >&2
  exit 1
fi
if [ "$OLD_VERSION" == "$VERSION" ]; then
  echo "dd-trace-java already pins ddprof ${VERSION}; nothing to do"
  exit 0
fi

git checkout -B "$BRANCH"

sed -i "0,/^ddprof = \"${OLD_VERSION}\"/s//ddprof = \"${VERSION}\"/" "$TOML"
if ! grep -q "^ddprof = \"${VERSION}\"" "$TOML"; then
  echo "ERROR: failed to update $TOML" >&2
  exit 1
fi

if [ -f "$LOCK" ]; then
  sed -i "s/^com\.datadoghq:ddprof:${OLD_VERSION}=/com.datadoghq:ddprof:${VERSION}=/" "$LOCK"
  if ! grep -q "^com\.datadoghq:ddprof:${VERSION}=" "$LOCK"; then
    echo "ERROR: failed to update $LOCK" >&2
    exit 1
  fi
fi

EXISTING=$(gh pr list --head "$BRANCH" --state open --json number --jq '.[0].number' || true)
if [ -n "$EXISTING" ]; then
  echo "Open bump PR already exists: #$EXISTING"
  exit 0
fi

git config user.email "java-profiler@datadoghq.com"
git config user.name "Datadog Java Profiler"
git add "$TOML" "$LOCK"
git commit -m "Bump java-profiler (ddprof) to ${VERSION}"
# A remote branch from a closed/failed previous run would reject a plain
# push as non-fast-forward; the branch is bot-owned and version-scoped, so
# recreate it.
git push origin :"$BRANCH" 2>/dev/null || true
git push origin "$BRANCH"

PR_BODY=$(cat <<EOF
# What Does This Do

Bumps java-profiler (ddprof) from ${OLD_VERSION} to ${VERSION} and updates the dependency lockfile.

Automated bump by the java-profiler release train, opened after the release
artifacts were published. See the
[release notes](${NOTES_URL}) for the changes introduced since ${OLD_VERSION}.
Refine this description before merging if a curated summary of notable
changes is needed.
EOF
)

PR_URL=$(gh pr create --draft --title "Bump java-profiler (ddprof) to ${VERSION}" \
  --body "$PR_BODY" --label "type: bug fix" --label "comp: profiling" --label "tag: ai generated")

echo "Opened $PR_URL"
