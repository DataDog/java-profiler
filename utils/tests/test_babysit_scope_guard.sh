#!/bin/bash
# Copyright 2026, Datadog, Inc.
# Hermetic tests for utils/babysit-scope-guard.py (the babysit scope layer of the
# pre-push gate). Every branch of the guard gets a case; pushes run in a temp repo.
set -u
FAILED=0
export PYTHONDONTWRITEBYTECODE=1 GIT_CONFIG_GLOBAL=/dev/null GIT_CONFIG_NOSYSTEM=1

TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT

pass() { TESTS=$((TESTS + 1)); }
fail() { TESTS=$((TESTS + 1)); FAILED=$((FAILED + 1)); echo "FAIL: $*" >&2; }
TESTS=0

GUARD="$TEMP_DIR/repo/utils/babysit-scope-guard.py"
mkdir -p "$TEMP_DIR/repo/utils"
cp "$(dirname "$0")/../../utils/babysit-scope-guard.py" "$GUARD"

R="$TEMP_DIR/repo"
git -C "$R" init -q
git -C "$R" -c user.email=t -c user.name=t commit -q --allow-empty -m base
BASE=$(git -C "$R" rev-parse HEAD)

# make_repo <branch>: a fix commit touching one allowed file, a remote branch tip
make_fix() { # <path> <branch>
  mkdir -p "$R/$(dirname "$1")"
  echo x > "$R/$1"
  git -C "$R" add "$1"
  git -C "$R" -c user.email=t -c user.name=t commit -q -m "fix $1"
  git -C "$R" branch -f "$2" HEAD
}

make_fix "ddprof-lib/src/main/cpp/a.cpp" fix
FIX=$(git -C "$R" rev-parse HEAD)
git -C "$R" update-ref refs/remotes/origin/main "$BASE"

# marker <json> — write a babysit marker for PR 1001
marker() { mkdir -p "$R/build"; printf '%s' "$1" > "$R/build/babysit-pr-1001.json"; }

# run_guard <branch> <local-sha> <remote-sha> -> exit status
run_guard() {
  ( cd "$R" && python3 "$GUARD" --branch "$1" --local-sha "$2" --remote-sha "$3" \
    >/dev/null 2>&1 )
}

# 1. No marker at all: a human push is never restricted.
rm -f "$R/build/babysit-pr-1001.json"
run_guard fix "$FIX" "$BASE"
if [ $? -eq 0 ]; then pass; else fail "no marker should allow the push"; fi

# 2. A stopped marker (run over) does not gate.
marker '{"pr":1001,"branch":"fix","status":"stopped","scope":["ddprof-lib/src/main/cpp/a.cpp"]}'
run_guard fix "$FIX" "$BASE"
if [ $? -eq 0 ]; then pass; else fail "stopped marker should allow the push"; fi

# 3. A running marker for a different branch does not gate this push.
marker '{"pr":1001,"branch":"other","status":"running","scope":[]}'
run_guard fix "$FIX" "$BASE"
if [ $? -eq 0 ]; then pass; else fail "other-branch marker should allow the push"; fi

# 4. Old-format marker (no branch field) cannot match: transition fail-open.
marker '{"pr":1001,"status":"running"}'
run_guard fix "$FIX" "$BASE"
if [ $? -eq 0 ]; then pass; else fail "old-format marker should allow the push"; fi

# 5. Running marker, declared scope, allowed file: the push goes through.
marker '{"pr":1001,"branch":"fix","status":"running","scope":["ddprof-lib/src/main/cpp/a.cpp"]}'
run_guard fix "$FIX" "$BASE"
if [ $? -eq 0 ]; then pass; else fail "in-scope in-allowlist push should be allowed"; fi

# 6. Allowed file but not declared: rejected.
marker '{"pr":1001,"branch":"fix","status":"running","scope":[]}'
run_guard fix "$FIX" "$BASE"
if [ $? -eq 1 ]; then pass; else fail "undeclared file should be rejected"; fi

# 7. Declared but outside the allowlist (the worker-editing-meta-files case): rejected
#    even though the marker declares it — the allowlist is not the worker's to widen.
marker '{"pr":1001,"branch":"fix","status":"running","scope":[".agents/skills/babysit-pr/SKILL.md"]}'
mkdir -p "$R/.agents/skills/babysit-pr"
echo y > "$R/.agents/skills/babysit-pr/SKILL.md"
git -C "$R" add .agents
git -C "$R" -c user.email=t -c user.name=t commit -q -m "edit skill"
META=$(git -C "$R" rev-parse HEAD)
run_guard fix "$META" "$FIX"
if [ $? -eq 1 ]; then pass; else fail "out-of-allowlist file should be rejected even when declared"; fi

# 8. Missing scope array on a running marker: rejected (fail closed for babysit pushes).
marker '{"pr":1001,"branch":"fix","status":"running"}'
run_guard fix "$FIX" "$BASE"
if [ $? -eq 1 ]; then pass; else fail "running marker without scope should be rejected"; fi

# 9. Unreadable marker JSON: rejected.
marker 'not json'
run_guard fix "$FIX" "$BASE"
if [ $? -eq 1 ]; then pass; else fail "unreadable marker should be rejected"; fi

# 10. A git failure (unknown remote sha) fails closed, not open.
marker '{"pr":1001,"branch":"fix","status":"running","scope":["ddprof-lib/src/main/cpp/a.cpp"]}'
run_guard fix "$FIX" "0000000000000000000000000000000000000bad"
if [ $? -eq 1 ]; then pass; else fail "git failure should fail closed"; fi

# 11. Branch creation (all-zero remote sha) falls back to the origin/main merge-base
#     and enforces the same rules on the full delta.
marker '{"pr":1001,"branch":"new","status":"running","scope":["ddprof-lib/src/main/cpp/a.cpp"]}'
git -C "$R" checkout -q -b new "$FIX"
run_guard new "$FIX" "0000000000000000000000000000000000000000"
if [ $? -eq 0 ]; then pass; else fail "branch-creation delta in scope should be allowed"; fi
marker '{"pr":1001,"branch":"new","status":"running","scope":[]}'
run_guard new "$FIX" "0000000000000000000000000000000000000000"
if [ $? -eq 1 ]; then pass; else fail "branch-creation delta without declared scope should be rejected"; fi

echo "$0: $TESTS tests, $FAILED failed"
exit $((FAILED > 0))
