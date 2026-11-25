#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# Tests for .pi/extensions/permissions-floor.ts, the Pi adapter of the permissions
# floor in .claude/settings.json. Cases run in a throwaway repo with a bare origin;
# global git config is ignored. Needs Node.js 22.6+ (--experimental-strip-types).
# Run with: bash utils/tests/test_pi_permissions_floor.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
ROOT=$(cd "$SCRIPT_DIR/../.." && pwd)
TESTS=0
FAILED=0
export GIT_CONFIG_GLOBAL=/dev/null GIT_CONFIG_NOSYSTEM=1

if ! node --experimental-strip-types --no-warnings -e '' >/dev/null 2>&1; then
  echo "SKIP: pi permissions-floor tests (node with --experimental-strip-types not found)"
  exit 0
fi

TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT

pass() { TESTS=$((TESTS + 1)); }
fail() { TESTS=$((TESTS + 1)); FAILED=$((FAILED + 1)); echo "FAIL: $*" >&2; }

# expect <name> <expected-exit> <output-substring-or-empty> <command...>
expect() {
  local name=$1 want=$2 needle=$3; shift 3
  local rc=0
  "$@" >"$TEMP_DIR/out" 2>"$TEMP_DIR/err" || rc=$?
  if [ "$rc" -ne "$want" ]; then
    fail "$name: exit $rc, want $want ($(cat "$TEMP_DIR/err"))"
  elif [ -n "$needle" ] && ! cat "$TEMP_DIR/out" "$TEMP_DIR/err" | grep -qF -- "$needle"; then
    fail "$name: output lacks '$needle': $(cat "$TEMP_DIR/out" "$TEMP_DIR/err")"
  else
    pass
  fi
}

cat > "$TEMP_DIR/pi-driver.mjs" <<'JS'
const [ext, cwd, toolName, command] = process.argv.slice(2);
const mod = await import(ext);
let handler;
mod.default({ on: (name, fn) => { if (name === "tool_call") handler = fn; } });
const result = await handler({ toolName, input: { command } }, { cwd });
if (result?.block) { console.error(result.reason); process.exit(2); }
JS
EXT="$ROOT/.pi/extensions/permissions-floor.ts"
pi_hook() { node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" "$EXT" "${3:-$TEMP_DIR/repo}" "$1" "$2"; }

git init -q --bare "$TEMP_DIR/origin.git"
mkdir -p "$TEMP_DIR/repo/.claude" "$TEMP_DIR/nofloor" && cd "$TEMP_DIR/repo"
git init -q -b main
git config user.email t@example.com && git config user.name t
cp "$ROOT/.claude/settings.json" .claude/settings.json
git add .claude/settings.json && git commit -q -m floor
git remote add origin "$TEMP_DIR/origin.git" && git push -q origin main && git fetch -q origin

BLOCK_MSG="denies Bash("
for c in 'rm -rf build' 'rm' 'sudo ls' 'cd x && rm -f y' 'true; rm y' 'ls | sudo tee f' \
         'FOO=1 rm y' '(rm y)' 'echo $(rm y)' 'echo `rm y`' $'ls\nrm y' 'false || rm y'; do
  expect "floor denies: $c" 2 "$BLOCK_MSG" pi_hook bash "$c"
done
for c in 'ls -la' 'rmdir x' 'grep rm file' 'git rm --cached f' 'echo sudo' 'sudoedit f' ''; do
  expect "floor allows: $c" 0 "" pi_hook bash "$c"
done
expect "floor ignores other tools" 0 "" pi_hook read "rm -rf build"
expect "floor names the blocked segment" 2 'Blocked `rm -f y`' pi_hook bash 'cd x && rm -f y'

# The checkout's settings never widen or narrow the floor: origin/main's apply.
python3 - <<'PY'
import json
p = ".claude/settings.json"
with open(p) as fh:
    d = json.load(fh)
d["permissions"]["deny"] = ["Bash(ls:*)"]
with open(p, "w") as fh:
    json.dump(d, fh)
PY
expect "floor ignores a checkout that drops rm" 2 "$BLOCK_MSG" pi_hook bash 'rm y'
expect "floor ignores a checkout that adds ls" 0 "" pi_hook bash 'ls'
expect "floor allows everything outside a checkout with origin/main" 0 "" pi_hook bash 'rm y' "$TEMP_DIR/nofloor"

# A failed floor read is never cached: once origin/main becomes readable, the floor
# applies in the same cwd whose earlier read failed. A transient git error must
# disable the floor for one call, not for the session.
mkdir -p "$TEMP_DIR/nofetch/.claude" && cd "$TEMP_DIR/nofetch"
git init -q -b main
git config user.email t@example.com && git config user.name t
cp "$ROOT/.claude/settings.json" .claude/settings.json
git add .claude/settings.json && git commit -q -m floor
git remote add origin "$TEMP_DIR/origin.git"
expect "floor allows while origin/main is unfetched" 0 "" pi_hook bash 'rm y' "$TEMP_DIR/nofetch"
git fetch -q origin
expect "floor denies once origin/main is fetched" 2 "$BLOCK_MSG" pi_hook bash 'rm y' "$TEMP_DIR/nofetch"

echo "$TESTS tests, $FAILED failed"
[ "$FAILED" -eq 0 ]
