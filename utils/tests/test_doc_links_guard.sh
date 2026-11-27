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
mkdir -p "$TEMP_REPO/doc"
printf 'paren doc\n' > "$TEMP_REPO/note(1).md"
git -C "$TEMP_REPO" add note\(1\).md 2>/dev/null || git -C "$TEMP_REPO" add "note(1).md"

# --- Claude Code adapter: JSON payload on stdin, exit 2 blocks, 0 allows ---
claude() {
  local payload=$1
  printf '%s' "$payload" | CLAUDE_PROJECT_DIR="$ROOT" python3 "$ROOT/.claude/hooks/doc-links-guard.py"
}
# Same adapter against the throwaway repo: CLAUDE_PROJECT_DIR must name it, or the
# hook's outside-the-checkout guard returns 0 before any checking happens.
claude_repo() {
  local payload=$1
  printf '%s' "$payload" | CLAUDE_PROJECT_DIR="$TEMP_REPO" python3 "$ROOT/.claude/hooks/doc-links-guard.py"
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
expect "claude: non-string write content is allowed" 0 "" \
  claude '{"tool_name":"Write","tool_input":{"file_path":"'"$ROOT"'/README.md","content":123}}'
# A bare `..` target must not reach git as an out-of-repository pathspec: that exits 2
# and the guards would allow the whole write, including the unrelated broken link.
expect "claude: bare parent target does not disable the guard" 2 "broken link" \
  claude_repo '{"tool_name":"Write","tool_input":{"file_path":"'"$TEMP_REPO"'/parent-links.md","content":"[parent](..) [bad](missing.md)\n"}}'
# The incoming document exists prospectively: a self-link in a new file must not block.
expect "claude: self-link in a new file is allowed" 0 "" \
  claude_repo '{"tool_name":"Write","tool_input":{"file_path":"'"$TEMP_REPO"'/fresh.md","content":"[section](fresh.md#sec)\n"}}'
# Code spans delimited by two backticks are code, not links.
expect "claude: double-backtick code span is not a link" 0 "" \
  claude_repo '{"tool_name":"Write","tool_input":{"file_path":"'"$TEMP_REPO"'/spans.md","content":"``[skip](Nope2.md)``\n"}}'
# Nested parentheses in a destination: a tracked target resolves, an absent one is caught.
expect "claude: nested-paren destination resolves a tracked file" 0 "" \
  claude_repo '{"tool_name":"Write","tool_input":{"file_path":"'"$TEMP_REPO"'/notes.md","content":"[x](note(1).md)\n"}}'
expect "claude: nested-paren destination catches a missing file" 2 "broken link" \
  claude_repo '{"tool_name":"Write","tool_input":{"file_path":"'"$TEMP_REPO"'/notes.md","content":"[x](absent((1)).md)\n"}}'

# Edit that inserts a link INSIDE an existing fenced code block of the file being
# edited: the resulting document keeps the fence, so the link is inside code and the
# write must not be blocked (fragment-only checking false-blocks this).
expect "claude: edit inside an existing fenced block is allowed" 0 "" \
  claude_repo '{"tool_name":"Edit","tool_input":{"file_path":"'"$TEMP_REPO"'/guide.md","old_string":"print(1)","new_string":"print(1)\n# see [x](docs/absent.md)"}}'
# A fragment that only opens a fence (the file already closes it) must not be reported
# as an unclosed fence by fragment-only checking.
expect "claude: edit whose fragment is balanced by the file is allowed" 0 "" \
  claude_repo '{"tool_name":"Edit","tool_input":{"file_path":"'"$TEMP_REPO"'/guide.md","old_string":"print(1)","new_string":"```python\nprint(1)"}}'

# Claude Code's Edit replaces every occurrence under replace_all: the guard must
# reconstruct that result, or a broken link introduced by a later occurrence (here:
# the one outside the fence) escapes the check.
printf '```python\nprint(1)\n```\nprint(1)\n' > "$TEMP_REPO/dup.md"
expect "claude: edit replace_all introducing a broken link outside the fence is blocked" 2 "broken link" \
  claude_repo '{"tool_name":"Edit","tool_input":{"file_path":"'"$TEMP_REPO"'/dup.md","old_string":"print(1)","new_string":"[x](docs/absent.md)","replace_all":true}}'

# A write that FIXES a known-broken link must not be blocked by a stale KNOWN_BROKEN entry.
expect "claude: fixing a known-broken link is allowed" 0 "" \
  env CLAUDE_PROJECT_DIR="$TEMP_REPO" bash -c "printf '%s' '{\"tool_name\":\"Write\",\"tool_input\":{\"file_path\":\"$TEMP_REPO/test-validation/README.md\",\"content\":\"[fixed](README.md)\\n\"}}' | python3 '$ROOT/.claude/hooks/doc-links-guard.py'"

# A cwd outside any git checkout: the failed root lookup must fail open (exit 0), and
# must not feed git's empty output to realpath.
expect "claude: write from a non-repo cwd is allowed" 0 "" \
  env CLAUDE_PROJECT_DIR="$TEMP_DIR/nonrepo" bash -c "mkdir -p $TEMP_DIR/nonrepo && printf '%s' '{\"tool_name\":\"Write\",\"tool_input\":{\"file_path\":\"$TEMP_DIR/nonrepo/x.md\",\"content\":\"[x](absent.md)\\n\"}}' | python3 '$ROOT/.claude/hooks/doc-links-guard.py'"

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
  ? { path: "@" + path, edits: [{ oldText, newText: content }] }
  : field === "atpath"
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
  # A session whose cwd is a subdirectory still checks writes into the repository: the
  # checker is resolved from the repository root, not from ctx.cwd.
  expect "pi: write from a subdirectory cwd is checked against the repo" 2 "broken link" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$TEMP_REPO/doc" write "$TEMP_REPO/sub-guide.md" '[x](docs/absent.md)' content
  expect "pi: @-prefixed edit path is normalized" 2 "broken link" \
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
    "$ROOT/.pi/extensions/doc-links-guard.ts" "$TEMP_REPO" edit "$TEMP_REPO/guide.md" '[x](docs/absent.md)' atpath '[real](fenced-real.md)' 
else
  echo "SKIP: pi doc-links-guard cases (node with --experimental-strip-types not found)"
fi

echo "$TESTS tests, $FAILED failed"
[ "$FAILED" -eq 0 ]
