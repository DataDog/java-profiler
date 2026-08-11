#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

# Hermetic unit tests for utils/compute-version.sh.
# Run with: bash utils/tests/test_compute_version.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
COMPUTE_VERSION="$SCRIPT_DIR/../compute-version.sh"
TESTS=0
FAILED=0

TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT

pass() {
  TESTS=$((TESTS + 1))
}

fail() {
  TESTS=$((TESTS + 1))
  FAILED=$((FAILED + 1))
  echo "FAIL: $*" >&2
}

# Run compute-version.sh in the given repo dir with the given env vars.
# Usage: run_in <repo_dir> [env=val ...] -- <args...>
run_in() {
  local repo_dir=$1
  shift
  local env_args=()
  while [ "$1" != "--" ]; do
    env_args+=("$1")
    shift
  done
  shift  # skip --
  (cd "$repo_dir" && env "${env_args[@]}" "$COMPUTE_VERSION" "$@")
}

# Create a fresh git repo with the given tags on the given branches.
# Usage: setup_repo -> echoes repo dir
setup_repo() {
  local repo="$TEMP_DIR/repo-$RANDOM"
  git init --quiet "$repo"
  git -C "$repo" config user.name "Test"
  git -C "$repo" config user.email "test@test.invalid"
  git -C "$repo" config commit.gpgsign false
  git -C "$repo" config tag.gpgsign false
  echo "$repo"
}

# Commit a dummy file in the repo
commit() {
  local repo=$1
  local msg=${2:-commit}
  echo "$msg" > "$repo/file.txt"
  git -C "$repo" add file.txt
  git -C "$repo" commit --quiet -m "$msg"
}

tag() {
  local repo=$1
  local tagname=$2
  git -C "$repo" tag -a "$tagname" -m "Release $tagname"
}

# --- Test 1: No tags → exit 1 ------------------------------------------------

repo=$(setup_repo)
commit "$repo" "initial"
if run_in "$repo" -- 2>/dev/null; then
  fail "no tags should exit 1"
else
  pass
fi

# --- Test 2: Tag on HEAD, main, no flag → snapshot ---------------------------

repo=$(setup_repo)
commit "$repo" "initial"
git -C "$repo" checkout -b main 2>/dev/null || git -C "$repo" branch -m main
tag "$repo" "v_1.48.0"
result=$(run_in "$repo" CI_COMMIT_BRANCH=main --)
[ "$result" = "1.49.0-SNAPSHOT" ] || fail "expected 1.49.0-SNAPSHOT, got '$result'"
pass

# --- Test 3: --release --minor → release version -----------------------------

result=$(run_in "$repo" CI_COMMIT_BRANCH=main -- --release --minor)
[ "$result" = "1.49.0" ] || fail "expected 1.49.0, got '$result'"
pass

# --- Test 4: --release --major → major bump ----------------------------------

result=$(run_in "$repo" CI_COMMIT_BRANCH=main -- --release --major)
[ "$result" = "2.0.0" ] || fail "expected 2.0.0, got '$result'"
pass

# --- Test 5: --release --patch on release branch ----------------------------

repo2=$(setup_repo)
commit "$repo2" "initial"
git -C "$repo2" checkout -b "release/1.48._" 2>/dev/null || git -C "$repo2" branch -m "release/1.48._"
tag "$repo2" "v_1.48.0"
result=$(run_in "$repo2" CI_COMMIT_BRANCH="release/1.48._" -- --release --patch)
[ "$result" = "1.48.1" ] || fail "expected 1.48.1, got '$result'"
pass

# --- Test 6: Release branch patch bump (snapshot) ----------------------------

repo3=$(setup_repo)
commit "$repo3" "initial"
git -C "$repo3" checkout -b "release/1.48._" 2>/dev/null || git -C "$repo3" branch -m "release/1.48._"
tag "$repo3" "v_1.48.2"
result=$(run_in "$repo3" CI_COMMIT_BRANCH="release/1.48._" --)
[ "$result" = "1.48.3-SNAPSHOT" ] || fail "expected 1.48.3-SNAPSHOT, got '$result'"
pass

# --- Test 7: First patch on new release branch -------------------------------

repo4=$(setup_repo)
commit "$repo4" "initial"
git -C "$repo4" checkout -b "release/1.50._" 2>/dev/null || git -C "$repo4" branch -m "release/1.50._"
tag "$repo4" "v_1.50.0"
result=$(run_in "$repo4" CI_COMMIT_BRANCH="release/1.50._" --)
[ "$result" = "1.50.1-SNAPSHOT" ] || fail "expected 1.50.1-SNAPSHOT, got '$result'"
pass

# --- Test 8: Feature branch suffix ------------------------------------------

repo5=$(setup_repo)
commit "$repo5" "initial"
git -C "$repo5" checkout -b main 2>/dev/null || git -C "$repo5" branch -m main
tag "$repo5" "v_1.49.0"
git -C "$repo5" checkout -b "feat/foo"
result=$(run_in "$repo5" CI_COMMIT_BRANCH="feat/foo" -- --branch-suffix "feat/foo")
[ "$result" = "1.50.0-feat_foo-SNAPSHOT" ] || fail "expected 1.50.0-feat_foo-SNAPSHOT, got '$result'"
pass

# --- Test 9: Minor rollover (1.99.0 → 2.0.0) ---------------------------------

repo6=$(setup_repo)
commit "$repo6" "initial"
git -C "$repo6" checkout -b main 2>/dev/null || git -C "$repo6" branch -m main
tag "$repo6" "v_1.99.0"
result=$(run_in "$repo6" CI_COMMIT_BRANCH=main --)
[ "$result" = "2.0.0-SNAPSHOT" ] || fail "expected 2.0.0-SNAPSHOT, got '$result'"
pass

# --- Test 10: Patch rollover (1.48.99 → 1.49.0) ------------------------------

repo7=$(setup_repo)
commit "$repo7" "initial"
git -C "$repo7" checkout -b "release/1.48._" 2>/dev/null || git -C "$repo7" branch -m "release/1.48._"
tag "$repo7" "v_1.48.99"
result=$(run_in "$repo7" CI_COMMIT_BRANCH="release/1.48._" --)
[ "$result" = "1.49.0-SNAPSHOT" ] || fail "expected 1.49.0-SNAPSHOT, got '$result'"
pass

# --- Test 11: Multiple tags, highest wins ------------------------------------

repo8=$(setup_repo)
commit "$repo8" "initial"
git -C "$repo8" checkout -b main 2>/dev/null || git -C "$repo8" branch -m main
tag "$repo8" "v_1.48.0"
commit "$repo8" "second"
tag "$repo8" "v_1.48.2"
commit "$repo8" "third"
tag "$repo8" "v_1.50.0"
result=$(run_in "$repo8" CI_COMMIT_BRANCH=main --)
[ "$result" = "1.51.0-SNAPSHOT" ] || fail "expected 1.51.0-SNAPSHOT, got '$result'"
pass

# --- Test 12: Tag not reachable from HEAD is ignored -------------------------

repo9=$(setup_repo)
commit "$repo9" "initial"
git -C "$repo9" checkout -b main 2>/dev/null || git -C "$repo9" branch -m main
tag "$repo9" "v_1.48.0"
# Create a divergent branch with a higher tag
git -C "$repo9" checkout -b other
commit "$repo9" "other"
tag "$repo9" "v_1.99.0"
git -C "$repo9" checkout main
result=$(run_in "$repo9" CI_COMMIT_BRANCH=main --)
[ "$result" = "1.49.0-SNAPSHOT" ] || fail "expected 1.49.0-SNAPSHOT (unreachable tag ignored), got '$result'"
pass

# --- Test 13: CI_COMMIT_TAG short-circuit -----------------------------------

repo10=$(setup_repo)
commit "$repo10" "initial"
git -C "$repo10" checkout -b main 2>/dev/null || git -C "$repo10" branch -m main
tag "$repo10" "v_1.48.3"
result=$(run_in "$repo10" CI_COMMIT_TAG="v_1.48.3" --)
[ "$result" = "1.48.3" ] || fail "expected 1.48.3 (tag short-circuit), got '$result'"
pass

# --- Test 14: Sort correctness (v_1.10.0 > v_1.9.0) --------------------------

repo11=$(setup_repo)
commit "$repo11" "initial"
git -C "$repo11" checkout -b main 2>/dev/null || git -C "$repo11" branch -m main
tag "$repo11" "v_1.9.0"
commit "$repo11" "second"
tag "$repo11" "v_1.10.0"
result=$(run_in "$repo11" CI_COMMIT_BRANCH=main --)
[ "$result" = "1.11.0-SNAPSHOT" ] || fail "expected 1.11.0-SNAPSHOT (version sort), got '$result'"
pass

# --- Test 15: --release without explicit bump on main → minor ----------------

result=$(run_in "$repo" CI_COMMIT_BRANCH=main -- --release)
[ "$result" = "1.49.0" ] || fail "expected 1.49.0, got '$result'"
pass

# --- Test 16: --release without explicit bump on release branch → patch ------

result=$(run_in "$repo2" CI_COMMIT_BRANCH="release/1.48._" -- --release)
[ "$result" = "1.48.1" ] || fail "expected 1.48.1, got '$result'"
pass

# --- Test 17: GITHUB_REF_NAME detection --------------------------------------

repo12=$(setup_repo)
commit "$repo12" "initial"
git -C "$repo12" checkout -b main 2>/dev/null || git -C "$repo12" branch -m main
tag "$repo12" "v_1.48.0"
result=$(run_in "$repo12" GITHUB_REF_NAME=main GITHUB_REF_TYPE=branch --)
[ "$result" = "1.49.0-SNAPSHOT" ] || fail "expected 1.49.0-SNAPSHOT (GITHUB_REF_NAME), got '$result'"
pass

# --- Test 18: Release branch does not get branch suffix ----------------------

repo13=$(setup_repo)
commit "$repo13" "initial"
git -C "$repo13" checkout -b "release/1.48._" 2>/dev/null || git -C "$repo13" branch -m "release/1.48._"
tag "$repo13" "v_1.48.0"
result=$(run_in "$repo13" CI_COMMIT_BRANCH="release/1.48._" -- --branch-suffix "release/1.48._")
[ "$result" = "1.48.1-SNAPSHOT" ] || fail "expected 1.48.1-SNAPSHOT (no suffix for release branch), got '$result'"
pass

# --- Test 19: Release branch ignores tags from other series -----------------
# If v_1.49.0 is merged into release/1.48._, it should NOT be used
repo14=$(setup_repo)
commit "$repo14" "initial"
git -C "$repo14" checkout -b "release/1.48._" 2>/dev/null || git -C "$repo14" branch -m "release/1.48._"
tag "$repo14" "v_1.48.2"
# Create a commit with a higher-series tag merged in
commit "$repo14" "merge mainline"
tag "$repo14" "v_1.49.0"
result=$(run_in "$repo14" CI_COMMIT_BRANCH="release/1.48._" --)
[ "$result" = "1.48.3-SNAPSHOT" ] || fail "expected 1.48.3-SNAPSHOT (series filter), got '$result'"
pass

# --- Summary -----------------------------------------------------------------

if [ "$FAILED" -gt 0 ]; then
  echo "FAIL: $FAILED/$TESTS test groups failed" >&2
  exit 1
fi
echo "PASS: $TESTS test groups"
