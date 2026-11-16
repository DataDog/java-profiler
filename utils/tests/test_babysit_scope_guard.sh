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

# 9. Unreadable marker JSON: skipped with a warning — an unrelated corrupt file must not
#    block a push with no other marker (never restrict humans).
marker 'not json'
run_guard fix "$FIX" "$BASE"
if [ $? -eq 0 ]; then pass; else fail "unreadable marker should be skipped, not block"; fi

# 9a. Unreadable marker plus a valid running marker later in glob order: the valid one
#     still gates (the early-return bug is gone).
printf 'not json' > "$R/build/babysit-pr-0999.json"
marker '{"pr":1001,"branch":"fix","status":"running","scope":[]}'
run_guard fix "$FIX" "$BASE"
if [ $? -eq 1 ]; then pass; else fail "valid marker after corrupt one should still gate"; fi
marker '{"pr":1001,"branch":"fix","status":"running","scope":["ddprof-lib/src/main/cpp/a.cpp"]}'
run_guard fix "$FIX" "$BASE"
if [ $? -eq 0 ]; then pass; else fail "valid marker after corrupt one should allow in-scope"; fi
rm -f "$R/build/babysit-pr-0999.json"

# 9b. A stale marker (mtime beyond the 26h age-out) does not gate — a dead run must not
#     block pushes on its branch forever, including human ones.
marker '{"pr":1001,"branch":"fix","status":"running","scope":[]}'
python3 -c 'import os,sys; os.utime(sys.argv[1], (0, 0))' "$R/build/babysit-pr-1001.json"
run_guard fix "$FIX" "$BASE"
if [ $? -eq 0 ]; then pass; else fail "stale marker should be ignored (dead run)"; fi

# 9c. A fresh marker (mtime now) still gates.
touch "$R/build/babysit-pr-1001.json"
run_guard fix "$FIX" "$BASE"
if [ $? -eq 1 ]; then pass; else fail "fresh running marker with empty scope should still gate"; fi

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

# --- .githooks/pre-push wiring (local-branch keying) — distinct local and remote
# branch names through the real hook; a stub origin/main provides the trusted
# review-marker (exit 0) and the real scope guard, as the hook's trusted_source does.
H="$TEMP_DIR/hookrepo"
mkdir -p "$H"
git -C "$H" init -q
git -C "$H" -c user.email=t -c user.name=t commit -q --allow-empty -m base
mkdir -p "$H/ddprof-lib/src/main/cpp" "$H/utils" "$H/.githooks" "$H/build"
echo x > "$H/ddprof-lib/src/main/cpp/a.cpp"
git -C "$H" add ddprof-lib
# A stub origin/main carrying a no-op review marker and the real guard.
printf '#!/usr/bin/env python3\nimport sys\nsys.exit(0)\n' > "$H/utils/review-marker.py"
cp "$(dirname "$0")/../../utils/babysit-scope-guard.py" "$H/utils/"
git -C "$H" add utils
git -C "$H" -c user.email=t -c user.name=t commit -q -m gates
git -C "$H" update-ref refs/remotes/origin/main HEAD
HB=$(git -C "$H" rev-parse HEAD)
git -C "$H" checkout -q -b fix HEAD
echo y >> "$H/ddprof-lib/src/main/cpp/a.cpp"
git -C "$H" -c user.email=t -c user.name=t commit -q -am fixwork
HFX=$(git -C "$H" rev-parse HEAD)
cp "$(dirname "$0")/../../.githooks/pre-push" "$H/.githooks/"

# 12. The hook gates on the LOCAL branch: pushing local fix -> remote other with a
# running marker for fix (empty scope) is rejected; reverting the wiring to the remote
# name would pass and fail this case.
printf '%s' '{"pr":1001,"branch":"fix","status":"running","scope":[]}' > "$H/build/babysit-pr-1001.json"
OUT=$( (cd "$H" && printf 'refs/heads/fix %s refs/heads/other %s\n' "$HFX" "$HB" | python3 .githooks/pre-push) 2>&1 )
if [ $? -eq 1 ] && grep -q "never declared" <<<"$OUT"; then pass; else fail "hook should gate on the local branch (got: $OUT)"; fi

# 13. Control: a marker for the remote name only (other) does not gate a fix push.
printf '%s' '{"pr":1001,"branch":"other","status":"running","scope":[]}' > "$H/build/babysit-pr-1001.json"
OUT=$( (cd "$H" && printf 'refs/heads/fix %s refs/heads/other %s\n' "$HFX" "$HB" | python3 .githooks/pre-push) 2>&1 )
if [ $? -eq 0 ]; then pass; else fail "marker keyed on the remote name should not gate a local-branch push (got: $OUT)"; fi

echo "$0: $TESTS tests, $FAILED failed"
exit $((FAILED > 0))