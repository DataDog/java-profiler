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

# Throwaway repo with a git-tracked scaffold; the guard adapters run the checker copy
# inside it, so --check-file resolves targets against THIS repo, not $ROOT.
TEMP_REPO="$TEMP_DIR/repo"
mkdir -p "$TEMP_REPO/utils" "$TEMP_REPO/.git"
cp "$ROOT/utils/check-doc-links.py" "$TEMP_REPO/utils/"
git -C "$TEMP_REPO" init -q
mkdir -p "$TEMP_REPO/test-validation"
printf '[known-broken](../gone.md)\n' > "$TEMP_REPO/test-validation/README.md"
printf '```python\nprint(1)\n```\n[real](fenced-real.md)\n' > "$TEMP_REPO/guide.md"
printf 'target\n' > "$TEMP_REPO/fenced-real.md"
git -C "$TEMP_REPO" add -A
# Created after `add -A`: tracked by the worktree, not by git — the untracked-but-
# not-ignored half of the --check-file target universe.
printf 'u\n' > "$TEMP_REPO/untracked.md"

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
  claude '{"tool_name":"Edit","tool_input":{"file_path":"'"$ROOT"'/README.md","old_string":"Google Test","new_string":"[x](docs/absent.md)"}}'
expect "claude: multiedit with broken link is blocked" 2 "broken link" \
  claude '{"tool_name":"MultiEdit","tool_input":{"file_path":"'"$ROOT"'/README.md","edits":[{"old_string":"Google Test","new_string":"[x](docs/absent.md)"}]}}'
expect "claude: non-markdown write is not checked" 0 "" \
  claude '{"tool_name":"Write","tool_input":{"file_path":"'"$ROOT"'/x.txt","content":"[x](docs/absent.md)"}}'
expect "claude: .markdown write is checked" 2 "broken link" \
  claude '{"tool_name":"Write","tool_input":{"file_path":"'"$ROOT"'/x.markdown","content":"[x](docs/absent.md)"}}'
expect "claude: write outside the checkout is not checked" 0 "" \
  claude '{"tool_name":"Write","tool_input":{"file_path":"/tmp/elsewhere/README.md","content":"[x](docs/absent.md)"}}'
expect "claude: malformed payload is allowed" 0 "" \
  claude 'not-json'

# Edit that inserts a link INSIDE an existing fenced code block of the file being
# edited: the resulting document keeps the fence, so the link is inside code and the
# write must not be blocked (fragment-only checking false-blocks this).
expect "claude: edit inside an existing fenced block is allowed" 0 "" \
  claude '{"tool_name":"Edit","tool_input":{"file_path":"'"$TEMP_REPO"'/guide.md","old_string":"print(1)","new_string":"print(1)\n# see [x](docs/absent.md)"}}'
# A fragment that only opens a fence (the file already closes it) must not be reported
# as an unclosed fence by fragment-only checking.
expect "claude: edit whose fragment is balanced by the file is allowed" 0 "" \
  claude '{"tool_name":"Edit","tool_input":{"file_path":"'"$TEMP_REPO"'/guide.md","old_string":"print(1)","new_string":"```python\nprint(1)"}}'

# A write that FIXES a known-broken link must not be blocked by a stale KNOWN_BROKEN entry.
expect "claude: fixing a known-broken link is allowed" 0 "" \
  env CLAUDE_PROJECT_DIR="$TEMP_REPO" bash -c "printf '%s' '{\"tool_name\":\"Write\",\"tool_input\":{\"file_path\":\"$TEMP_REPO/test-validation/README.md\",\"content\":\"[fixed](README.md)\\n\"}}' | python3 '$ROOT/.claude/hooks/doc-links-guard.py'"

# --check-file target resolution in the throwaway repo: a tracked target, a directory
# holding a tracked file, and an untracked-but-not-ignored file all resolve.
expect "claude: write targeting an untracked file is allowed" 0 "" \
  env CLAUDE_PROJECT_DIR="$TEMP_REPO" bash -c "printf '%s' '{\"tool_name\":\"Write\",\"tool_input\":{\"file_path\":\"$TEMP_REPO/notes.md\",\"content\":\"[x](untracked.md)\\n\"}}' | python3 '$ROOT/.claude/hooks/doc-links-guard.py'"

# --- pi adapter: tool_call handler, block returns {block:true} ---
if node --experimental-strip-types --no-warnings -e '' >/dev/null 2>&1; then
  cat > "$TEMP_DIR/pi-driver.mjs" <<'JS'
const [ext, cwd, toolName, path, content, field, oldText] = process.argv.slice(2);
const mod = await import(ext);
let handler;
mod.default({ on: (name, fn) => { if (name === "tool_call") handler = fn; } });
const input = field === "edits"
  ? { path, edits: [{ oldText, newText: content }] }
  : field === "newText"
  ? { path, oldText, newText: content }
  : { path, content };
const result = await handler({ toolName, input }, { cwd });
if (result?.block) { console.error(result.reason); process.exit(2); }
JS
  expect "pi: write with broken link is blocked" 2 "broken link" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" write "$ROOT/README.md" '[x](docs/absent.md)' content
  expect "pi: edit edits[]-shaped with broken link is blocked (real pi edit tool shape)" 2 "broken link" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$TEMP_REPO" edit "$TEMP_REPO/guide.md" '[x](docs/absent.md)' edits '[real](fenced-real.md)'
  expect "pi: edit newText with broken link is blocked" 2 "broken link" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$TEMP_REPO" edit "$TEMP_REPO/guide.md" '[x](docs/absent.md)' newText '[real](fenced-real.md)'
  expect "pi: write with resolvable link is allowed" 0 "" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" write "$ROOT/README.md" '[x](doc/README.md)' content
  expect "pi: non-markdown write is not checked" 0 "" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" write "$ROOT/x.txt" '[x](docs/absent.md)' content
  expect "pi: .markdown write is checked" 2 "broken link" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" write "$ROOT/x.markdown" '[x](docs/absent.md)' content
  expect "pi: write outside the checkout is not checked" 0 "" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$ROOT" write /tmp/elsewhere/README.md '[x](docs/absent.md)' content
  expect "pi: edit inside an existing fenced block is allowed" 0 "" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$TEMP_REPO" edit "$TEMP_REPO/guide.md" 'print(1)
# see [x](docs/absent.md)' edits 'print(1)'
  expect "pi: write targeting a tracked file is allowed" 0 "" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$TEMP_REPO" write "$TEMP_REPO/notes.md" '[x](fenced-real.md)' content
  expect "pi: write targeting a directory holding a tracked file is allowed" 0 "" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$TEMP_REPO" write "$TEMP_REPO/notes.md" '[x](utils)' content
  expect "pi: write targeting an untracked-but-not-ignored file is allowed" 0 "" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$TEMP_REPO" write "$TEMP_REPO/notes.md" '[x](untracked.md)' content
else
  echo "SKIP: pi doc-links-guard cases (node with --experimental-strip-types not found)"
fi

echo "$TESTS tests, $FAILED failed"
[ "$FAILED" -eq 0 ]
