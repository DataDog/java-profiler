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
# The token authenticates gh API calls but not the plain git push from the
# temp clone; wire it in as a git credential helper.
gh auth setup-git --hostname github.com >/dev/null

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
# A downgrade means a maintenance-line release while dd-trace-java already
# pins a newer mainline version; downgrading the pin is impossible, and the
# release itself published fine, so this is a skip, not a failure.
if [ "$(printf '%s\n%s\n' "$OLD_VERSION" "$VERSION" | sort -t. -k1,1n -k2,2n -k3,3n | head -1)" == "$VERSION" ]; then
  echo "dd-trace-java already pins newer ddprof ${OLD_VERSION}; skipping ${VERSION}"
  exit 0
fi

git checkout -B "$BRANCH"

# The .bak suffix form is the only sed -i variant that is identical on GNU
# and BSD; the backups are removed right after the verification greps.
sed -i.bak "s/^ddprof = \"${OLD_VERSION}\"/ddprof = \"${VERSION}\"/" "$TOML"
if ! grep -q "^ddprof = \"${VERSION}\"" "$TOML"; then
  echo "ERROR: failed to update $TOML" >&2
  exit 1
fi
rm -f "$TOML.bak"

if [ -f "$LOCK" ]; then
  sed -i.bak "s/^com\.datadoghq:ddprof:${OLD_VERSION}=/com.datadoghq:ddprof:${VERSION}=/" "$LOCK"
  if ! grep -q "^com\.datadoghq:ddprof:${VERSION}=" "$LOCK"; then
    echo "ERROR: failed to update $LOCK" >&2
    exit 1
  fi
  rm -f "$LOCK.bak"
fi

# An open PR from a previous run means the bump is already tracked; a lookup
# failure must abort — treating it as "no PR" could delete an existing PR's
# head branch in the recreate fallback below.
EXISTING=$(gh pr list --head "$BRANCH" --state open --json number --jq '.[0].number // empty')
if [ -n "$EXISTING" ]; then
  echo "Open bump PR already exists: #$EXISTING"
  exit 0
fi

git config user.email "java-profiler@datadoghq.com"
git config user.name "Datadog Java Profiler"
git add "$TOML"
[ -f "$LOCK" ] && git add "$LOCK"
git commit -m "Bump java-profiler (ddprof) to ${VERSION}"
# The branch is bot-owned and version-scoped. Push plainly first; only a
# non-fast-forward reject (a stale branch from a closed previous run)
# recreates it, so a concurrent PR on the branch is not deleted by accident
# and a delete failure is not hidden.
if ! git push origin "$BRANCH" 2>"$WORK_DIR/push.err"; then
  if grep -qE 'non-fast-forward|fetch first' "$WORK_DIR/push.err"; then
    git push origin :"$BRANCH" || { echo "ERROR: failed to recreate $BRANCH" >&2; exit 1; }
    git push origin "$BRANCH" || { echo "ERROR: failed to push recreated $BRANCH" >&2; exit 1; }
  else
    cat "$WORK_DIR/push.err" >&2
    exit 1
  fi
fi

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
