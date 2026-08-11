#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

# Compute the profiler version from git tags.
#
# Usage:
#   utils/compute-version.sh [--release] [--major|--minor|--patch]
#                             [--branch-suffix <branch>]
#
# Without --release: prints the snapshot version for HEAD.
# With --release: prints the release version (no -SNAPSHOT suffix).
#
# Version rules:
#   main              → most recent tag v_X.Y.Z → X.(Y+1).0-SNAPSHOT
#   release/X.Y._     → most recent tag v_X.Y.Z → X.Y.(Z+1)-SNAPSHOT
#   other branches    → same bump as main + -<branch>-SNAPSHOT suffix
#   tag commit        → X.Y.Z (no bump)
#
# Exit 1 if no version tags are reachable from HEAD.

set -euo pipefail

# Resolve repo root by walking up from CWD (no git command needed, so
# this works even when git's "dubious ownership" check would block
# git rev-parse --show-toplevel in CI containers).
REPO_ROOT="."
dir="$(pwd)"
while [ "$dir" != "/" ] && [ ! -d "$dir/.git" ]; do
  dir=$(dirname "$dir")
done
if [ -d "$dir/.git" ]; then
  REPO_ROOT="$dir"
fi
# Use -c safe.directory for all git commands so they work regardless of
# ownership (CI containers may have a different owner than the runner user).
# This does NOT modify global git config.
GIT="git -c safe.directory=$REPO_ROOT"

RELEASE=false
BUMP_TYPE=""
BRANCH_SUFFIX=""

usage() {
  cat <<EOF
Usage: $0 [--release] [--major|--minor|--patch] [--branch-suffix <branch>]

Options:
  --release              Print the release version (strip -SNAPSHOT)
  --major                Major bump (implies --release)
  --minor                Minor bump (implies --release)
  --patch                Patch bump (implies --release)
  --branch-suffix <branch>  Append -<branch>-SNAPSHOT for non-main branches
  --help                 Show this help
EOF
}

while [ $# -gt 0 ]; do
  case "$1" in
    --release) RELEASE=true; shift ;;
    --major) RELEASE=true; BUMP_TYPE="major"; shift ;;
    --minor) RELEASE=true; BUMP_TYPE="minor"; shift ;;
    --patch) RELEASE=true; BUMP_TYPE="patch"; shift ;;
    --branch-suffix) BRANCH_SUFFIX="${2:-}"; shift 2 ;;
    --help) usage; exit 0 ;;
    *) echo "ERROR: unknown argument: $1" >&2; usage >&2; exit 1 ;;
  esac
done

# --- Detect tag build (short-circuit) ---------------------------------------

if [[ "${CI_COMMIT_TAG:-}" =~ ^v_([0-9]+\.[0-9]+\.[0-9]+)$ ]]; then
  echo "${BASH_REMATCH[1]}"
  exit 0
fi

# GitHub Actions tag push: GITHUB_REF_TYPE=tag, GITHUB_REF_NAME=v_X.Y.Z
if [ "${GITHUB_REF_TYPE:-}" = "tag" ] && [[ "${GITHUB_REF_NAME:-}" =~ ^v_([0-9]+\.[0-9]+\.[0-9]+)$ ]]; then
  echo "${BASH_REMATCH[1]}"
  exit 0
fi

# --- Find most recent reachable tag -----------------------------------------

# Disable pipefail/errexit for git commands that may fail in unusual
# CI environments (detached HEAD, shallow clones, etc.)
set +e
latest_tag=$($GIT -C "$REPO_ROOT" tag --merged HEAD --list 'v_*' 2>/dev/null | sed 's/^v_//' | sort -V | tail -1)

# Fallback: if --merged fails (e.g. detached HEAD in some CI environments),
# use all tags sorted by version — the most recent one is almost certainly
# reachable from HEAD in practice.
if [ -z "$latest_tag" ]; then
  latest_tag=$($GIT -C "$REPO_ROOT" tag --list 'v_*' 2>/dev/null | sed 's/^v_//' | sort -V | tail -1)
fi
set -e

if [ -z "$latest_tag" ]; then
  echo "ERROR: no version tags (v_*) reachable from HEAD" >&2
  exit 1
fi

IFS=. read -r major minor patch <<<"$latest_tag"

# --- Detect current branch --------------------------------------------------

branch=""
if [ -n "${CI_COMMIT_BRANCH:-}" ]; then
  branch="$CI_COMMIT_BRANCH"
elif [ -n "${GITHUB_REF_NAME:-}" ] && [ "${GITHUB_REF_TYPE:-}" != "tag" ]; then
  branch="$GITHUB_REF_NAME"
else
  branch=$($GIT -C "$REPO_ROOT" rev-parse --abbrev-ref HEAD 2>/dev/null || echo "")
fi

# --- Determine bump type -----------------------------------------------------

is_release_branch=false
if [[ "$branch" =~ ^release/([0-9]+)\.([0-9]+)\._$ ]]; then
  is_release_branch=true
fi

if [ -z "$BUMP_TYPE" ]; then
  if [ "$is_release_branch" = "true" ]; then
    BUMP_TYPE="patch"
  else
    BUMP_TYPE="minor"
  fi
fi

# --- Apply bump with rollover ------------------------------------------------

case "$BUMP_TYPE" in
  major)
    major=$((major + 1))
    minor=0
    patch=0
    ;;
  minor)
    if [ "$minor" -ge 99 ]; then
      major=$((major + 1))
      minor=0
    else
      minor=$((minor + 1))
    fi
    patch=0
    ;;
  patch)
    if [ "$patch" -ge 99 ]; then
      if [ "$minor" -ge 99 ]; then
        major=$((major + 1))
        minor=0
      else
        minor=$((minor + 1))
      fi
      patch=0
    else
      patch=$((patch + 1))
    fi
    ;;
  *)
    echo "ERROR: unknown bump type: $BUMP_TYPE" >&2
    exit 1
    ;;
esac

version="$major.$minor.$patch"

# --- Assemble version string -------------------------------------------------

if [ "$RELEASE" = "true" ]; then
  echo "$version"
else
  if [ -n "$BRANCH_SUFFIX" ] && [ "$branch" != "main" ] && [ "$is_release_branch" = "false" ]; then
    sanitized_branch=$(echo "$BRANCH_SUFFIX" | tr '/' '_')
    echo "${version}-${sanitized_branch}-SNAPSHOT"
  else
    echo "${version}-SNAPSHOT"
  fi
fi
