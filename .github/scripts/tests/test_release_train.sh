#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc

# Hermetic tests for the release-train certification flow:
#   .github/scripts/certify.sh            — note creation, idempotency
#   .github/scripts/pick-release-candidate.sh — candidate selection rules
# Run with: .github/scripts/tests/test_release_train.sh

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)
CERTIFY="$ROOT/.github/scripts/certify.sh"
PICK="$ROOT/.github/scripts/pick-release-candidate.sh"
TEMP_DIR=$(mktemp -d)
TESTS=0

# This suite must never mutate GitHub or any other network remote. Restrict Git
# to filesystem transports and shadow every network-capable command.
export GIT_ALLOW_PROTOCOL=file
NETWORK_GUARD_BIN="$TEMP_DIR/network-guard-bin"
mkdir "$NETWORK_GUARD_BIN"
for command in gh ssh scp curl wget; do
  printf '%s\n' \
    '#!/usr/bin/env bash' \
    "echo \"network command blocked by hermetic release train test: \${0##*/}\" >&2" \
    'exit 97' > "$NETWORK_GUARD_BIN/$command"
  chmod +x "$NETWORK_GUARD_BIN/$command"
done
PATH="$NETWORK_GUARD_BIN:$PATH"
export PATH

cleanup() {
  rm -rf "$TEMP_DIR"
}
trap cleanup EXIT

fail() {
  echo "FAIL: $*" >&2
  exit 1
}

pass() {
  TESTS=$((TESTS + 1))
}

assert_eq() {
  if [ "$1" != "$2" ]; then
    fail "$3: expected '$1', got '$2'"
  fi
  pass
}

assert_contains() {
  case "$1" in
    *"$2"*) pass ;;
    *) fail "$3: '$1' does not contain '$2'" ;;
  esac
}

# --- Fixture -----------------------------------------------------------------

ORIGIN="$TEMP_DIR/origin.git"
CLONE="$TEMP_DIR/clone"
git init -q --bare "$ORIGIN"
git init -q "$CLONE"
cd "$CLONE"
git config user.email "test@example.com"
git config user.name "Test"
git remote add origin "$ORIGIN"
git push -q origin HEAD:refs/heads/main 2>/dev/null || true
git checkout -q -b main

commit() {
  # commit <name>: creates a commit on main and pushes it
  echo "$1" >> file.txt
  git add file.txt
  git commit -qm "$1"
  git push -q origin main
  git rev-parse HEAD
}

# Runs pick-release-candidate.sh; writes its stdout to $TEMP_DIR/pick.out and
# its exit status to $TEMP_DIR/pick.rc. (Function must not assign globals from
# a command substitution subshell — that loses them under set -u.)
run_pick() {
  local rc=0
  ( set +e; "$PICK" 2>"$TEMP_DIR/pick.err" ) >"$TEMP_DIR/pick.out" || rc=$?
  echo "$rc" > "$TEMP_DIR/pick.rc"
}

# --- certify.sh --------------------------------------------------------------

C1=$(commit c1)

CONTENT=$(git fetch origin refs/notes/certification:refs/notes/certification 2>/dev/null; \
  "$CERTIFY" "$C1" --run-url "https://example/run/1" --suite "suite-a" 2>"$TEMP_DIR/certify.err") \
  && CERTIFY_RC=0 || CERTIFY_RC=$?
assert_eq "$CERTIFY_RC" "0" "certify.sh succeeds on first run"
assert_contains "$CONTENT" "$C1" "certify.sh output names the commit"
assert_contains "$CONTENT" "https://example/run/1" "certify.sh output carries the run URL"
assert_contains "$CONTENT" "suite-a" "certify.sh output carries the suite"

# The note is on origin and on the commit
git fetch origin refs/notes/certification:refs/notes/certification 2>/dev/null || true
NOTED=$(git notes --ref=certification list | awk '{print $2}' | head -1)
assert_eq "$NOTED" "$C1" "certify.sh pushes a note on the commit"

# Idempotent re-run: exit 0, exactly one note
"$CERTIFY" "$C1" --run-url "https://example/run/2" >/dev/null 2>>"$TEMP_DIR/certify.err" \
  && CERTIFY_RC2=0 || CERTIFY_RC2=$?
assert_eq "$CERTIFY_RC2" "0" "certify.sh re-run is a no-op success"
N_NOTES=$(git notes --ref=certification list | wc -l | tr -d ' ')
assert_eq "$N_NOTES" "1" "certify.sh re-run does not duplicate the note"

# Invalid commit fails
"$CERTIFY" deadbeefdeadbeefdeadbeefdeadbeefdeadbeef --run-url x >/dev/null 2>&1 \
  && fail "certify.sh must reject an unknown commit" || true
pass

# --- pick-release-candidate.sh -----------------------------------------------

# 1. Certified commit, no release tags yet -> candidate
run_pick
OUT=$(cat "$TEMP_DIR/pick.out")
PICK_RC=$(cat "$TEMP_DIR/pick.rc")
assert_eq "$PICK_RC" "0" "pick returns the certified commit"
assert_eq "$OUT" "$C1" "pick candidate is the certified commit"

# 2. No certified commits at all -> skip
git update-ref -d refs/notes/certification
git push -q origin :refs/notes/certification 2>/dev/null || true
run_pick
OUT=$(cat "$TEMP_DIR/pick.out")
PICK_RC=$(cat "$TEMP_DIR/pick.rc")
assert_eq "$PICK_RC" "10" "pick skips with no notes"
assert_contains "$OUT" "none:" "pick skip reason explains itself"

# 3. Newest certified commit released -> skip (never release twice from one
#    certified commit)
C2=$(commit c2)
"$CERTIFY" "$C2" --run-url "https://example/run/3" >/dev/null 2>&1
git tag -a v_1.53.0 -m "test" "$C2"
run_pick
OUT=$(cat "$TEMP_DIR/pick.out")
PICK_RC=$(cat "$TEMP_DIR/pick.rc")
assert_eq "$PICK_RC" "10" "pick skips when the newest certified commit is released"
assert_contains "$OUT" "already released" "pick names the released state"

# 4. Certified commit newer than the last release tag -> candidate
C3=$(commit c3)
"$CERTIFY" "$C3" --run-url "https://example/run/4" >/dev/null 2>&1
run_pick
OUT=$(cat "$TEMP_DIR/pick.out")
PICK_RC=$(cat "$TEMP_DIR/pick.rc")
assert_eq "$PICK_RC" "0" "pick returns a certified commit newer than the last tag"
assert_eq "$OUT" "$C3" "pick candidate is the newer certified commit"

# 5. Certified commit older than the last release tag (ancestor, unreleased)
#    -> skip: never release a commit older than the last release
git update-ref -d refs/notes/certification
git push -q origin :refs/notes/certification 2>/dev/null || true
"$CERTIFY" "$C1" --run-url "https://example/run/5" >/dev/null 2>&1
run_pick
OUT=$(cat "$TEMP_DIR/pick.out")
PICK_RC=$(cat "$TEMP_DIR/pick.rc")
assert_eq "$PICK_RC" "10" "pick skips a certified commit older than the last tag"
assert_contains "$OUT" "predates the last release" "pick explains the ancestor rule"

# 6. No release tags, certified commit exists -> candidate (fresh install)
git tag -d v_1.53.0 >/dev/null
run_pick
OUT=$(cat "$TEMP_DIR/pick.out")
PICK_RC=$(cat "$TEMP_DIR/pick.rc")
assert_eq "$PICK_RC" "0" "pick returns the certified commit when no tags exist"
assert_eq "$OUT" "$C1" "pick candidate without tags"

# 7. Several certified commits at once -> the tip-most one by history
#    position, not by committer date or SHA (guards the pipefail/SIGPIPE
#    failure mode of the rev-list|grep|head pipeline)
"$CERTIFY" "$C2" --run-url "https://example/run/6" >/dev/null 2>&1
"$CERTIFY" "$C3" --run-url "https://example/run/7" >/dev/null 2>&1
N_NOTES=$(git notes --ref=certification list | wc -l | tr -d ' ')
assert_eq "$N_NOTES" "3" "three certification notes accumulated"
run_pick
OUT=$(cat "$TEMP_DIR/pick.out")
PICK_RC=$(cat "$TEMP_DIR/pick.rc")
assert_eq "$PICK_RC" "0" "pick survives multiple certified commits"
assert_eq "$OUT" "$C3" "pick candidate is the tip-most certified commit"

echo "PASS: $TESTS assertions"
