#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# Tests for the doc-links write guard adapters: .claude/hooks/doc-links-guard.py (Claude
# Code PreToolUse) and .pi/extensions/doc-links-guard.ts (pi tool_call), both running
# utils/check-doc-links.py --check-file. Cases run in a throwaway repo with a bare origin;
# global git config is ignored. Needs Node.js 22.6+ (--experimental-strip-types) for the pi
# cases; the Claude cases run without Node. Run with: bash utils/tests/test_doc_links_guard.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
ROOT=$(cd "$SCRIPT_DIR/../.." && pwd)
TESTS=0
FAILED=0
export GIT_CONFIG_GLOBAL=/dev/null GIT_CONFIG_NOSYSTEM=1

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

# --- Claude Code adapter: JSON payload on stdin, exit 2 blocks, 0 allows ---
claude() {
  local payload=$1
  printf '%s' "$payload" | CLAUDE_PROJECT_DIR="$ROOT" python3 "$ROOT/.claude/hooks/doc-links-guard.py"
}

expect "claude: write with broken link is blocked" 2 "broken link" \
  claude '{"tool_name":"Write","tool_input":{"file_path":"'"$ROOT"'/README.md","content":"[x](docs/absent.md)\n"}}'
expect "claude: write with resolvable link is allowed" 0 "" \
  claude '{"tool_name":"Write","tool_input":{"file_path":"'"$ROOT"'/README.md","content":"[x](doc/README.md)\n"}}'
expect "claude: edit new_string with broken link is blocked" 2 "broken link" \
  claude '{"tool_name":"Edit","tool_input":{"file_path":"'"$ROOT"'/README.md","old_string":"a","new_string":"[x](docs/absent.md)"}}'
expect "claude: multiedit with broken link is blocked" 2 "broken link" \
  claude '{"tool_name":"MultiEdit","tool_input":{"file_path":"'"$ROOT"'/README.md","edits":[{"old_string":"a","new_string":"[x](docs/absent.md)"}]}}'
expect "claude: non-markdown write is not checked" 0 "" \
  claude '{"tool_name":"Write","tool_input":{"file_path":"'"$ROOT"'/x.txt","content":"[x](docs/absent.md)"}}'
expect "claude: write outside the checkout is not checked" 0 "" \
  claude '{"tool_name":"Write","tool_input":{"file_path":"/tmp/elsewhere/README.md","content":"[x](docs/absent.md)"}}'
expect "claude: malformed payload is allowed" 0 "" \
  claude 'not-json'

# A write that FIXES a known-broken link must not be blocked by a stale KNOWN_BROKEN entry.
mkdir -p "$TEMP_DIR/repo/utils" "$TEMP_DIR/repo/.git"
cp "$ROOT/utils/check-doc-links.py" "$TEMP_DIR/repo/utils/"
git -C "$TEMP_DIR/repo" init -q
printf '[known-broken](gone.md)\n' > "$TEMP_DIR/repo/test-validation-README-scaffold"
mkdir -p "$TEMP_DIR/repo/test-validation"
printf '[known-broken](../gone.md)\n' > "$TEMP_DIR/repo/test-validation/README.md"
git -C "$TEMP_DIR/repo" add -A
expect "claude: fixing a known-broken link is allowed" 0 "" \
  env CLAUDE_PROJECT_DIR="$TEMP_DIR/repo" bash -c "printf '%s' '{\"tool_name\":\"Write\",\"tool_input\":{\"file_path\":\"$TEMP_DIR/repo/test-validation/README.md\",\"content\":\"[fixed](README.md)\\n\"}}' | python3 '$ROOT/.claude/hooks/doc-links-guard.py'"

# --- pi adapter: tool_call handler, block returns {block:true} ---
if node --experimental-strip-types --no-warnings -e '' >/dev/null 2>&1; then
  cat > "$TEMP_DIR/pi-driver.mjs" <<'JS'
const [ext, cwd, toolName, path, content, field] = process.argv.slice(2);
const mod = await import(ext);
let handler;
mod.default({ on: (name, fn) => { if (name === "tool_call") handler = fn; } });
const input = field === "edits"
  ? { path, edits: [{ oldText: "old", newText: content }] }
  : field === "newText"
  ? { path, newText: content }
  : { path, content };
const result = await handler({ toolName, input }, { cwd });
if (result?.block) { console.error(result.reason); process.exit(2); }
JS
  expect "pi: write with broken link is blocked" 2 "broken link" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" write "$ROOT/README.md" '[x](docs/absent.md)' content
  expect "pi: edit edits[]-shaped with broken link is blocked (real pi edit tool shape)" 2 "broken link" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" edit "$ROOT/README.md" '[x](docs/absent.md)' edits
  expect "pi: edit newText with broken link is blocked" 2 "broken link" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" edit "$ROOT/README.md" '[x](docs/absent.md)' newText
  expect "pi: write with resolvable link is allowed" 0 "" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" write "$ROOT/README.md" '[x](doc/README.md)' content
  expect "pi: non-markdown write is not checked" 0 "" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" write "$ROOT/x.txt" '[x](docs/absent.md)' content
  expect "pi: write outside the checkout is not checked" 0 "" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" write /tmp/elsewhere/README.md '[x](docs/absent.md)' content
else
  echo "SKIP: pi doc-links-guard cases (node with --experimental-strip-types not found)"
fi

echo "$TESTS tests, $FAILED failed"
[ "$FAILED" -eq 0 ]
