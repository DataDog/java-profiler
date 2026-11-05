#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# Tests for utils/knowledgebase-write-policy.py, the Claude Code hook
# .claude/hooks/protect-knowledgebase.py, its Pi adapter and its settings.json wiring.
# Hook cases run in a throwaway repo with a bare origin; global git config is ignored.
# Run with: bash utils/tests/test_knowledgebase_guard.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
ROOT=$(cd "$SCRIPT_DIR/../.." && pwd)
TESTS=0
FAILED=0
export PYTHONDONTWRITEBYTECODE=1 GIT_CONFIG_GLOBAL=/dev/null GIT_CONFIG_NOSYSTEM=1

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

BLOCK_MSG="written only by the cairn skills"

# --- utils/knowledgebase-write-policy.py ---
policy() { printf '%s' "$1" | python3 -I "$ROOT/utils/knowledgebase-write-policy.py"; }
for p in .knowledgebase/memories/x.md .knowledgebase .knowledgebase/.cairn \
         src/../.knowledgebase/memories/x.md ./.knowledgebase/x; do
  expect "policy denies: $p" 2 "$BLOCK_MSG" policy "$p"
done
for p in src/x.cpp .knowledgebase-notes/x.md docs/.knowledgebase.md memories/x.md ''; do
  expect "policy allows: $p" 0 "" policy "$p"
done
expect "policy names the blocked path" 2 'Blocked write to `.knowledgebase/memories/x.md`' \
  policy .knowledgebase/memories/x.md

# --- settings.json wiring ---
HOOK_CMD=$(python3 -c 'import json,sys
for e in json.load(open(sys.argv[1]))["hooks"]["PreToolUse"]:
    tools = set(e.get("matcher", "").split("|"))
    for h in e["hooks"]:
        if {"Edit", "Write", "NotebookEdit"} <= tools and "protect-knowledgebase.py" in h["command"]:
            print(h["command"])' "$ROOT/.claude/settings.json")
if [ -n "$HOOK_CMD" ]; then pass; else fail "settings.json does not register the hook for Edit/Write/NotebookEdit"; fi
mkdir -p "$TEMP_DIR/nohook"
expect "settings hook command allows everything when the hook file is missing" 0 "" \
  sh -c "echo '{\"tool_input\":{\"file_path\":\".knowledgebase/x.md\"}}' | CLAUDE_PROJECT_DIR=$TEMP_DIR/nohook sh -c '$HOOK_CMD'"

# --- .claude/hooks/protect-knowledgebase.py ---
git init -q --bare "$TEMP_DIR/origin.git"
REPO="$TEMP_DIR/repo"
mkdir -p "$REPO" && cd "$REPO"
git init -q -b main
git config user.email t@example.com && git config user.name t
mkdir -p utils .claude/hooks .pi/extensions .knowledgebase/memories src
cp "$ROOT/.claude/hooks/protect-knowledgebase.py" .claude/hooks/
cp "$ROOT/.pi/extensions/protect-knowledgebase.ts" .pi/extensions/
echo m > .knowledgebase/memories/m.md && echo s > src/a.cpp
git add . && git commit -qm "hook without policy"
git remote add origin "$TEMP_DIR/origin.git" && git push -q origin main

# hook <tool> <path> [cwd] [field]
hook() {
  python3 -I -c 'import json,sys; print(json.dumps({"tool_name": sys.argv[1], "cwd": sys.argv[3],
                                                     "tool_input": {sys.argv[4]: sys.argv[2]}}))' \
    "$1" "$2" "${3:-$PWD}" "${4:-file_path}" | CLAUDE_PROJECT_DIR=$REPO python3 "$REPO/.claude/hooks/protect-knowledgebase.py"
}
expect "hook allows everything while origin/main lacks the policy" 0 "" \
  hook Edit "$REPO/.knowledgebase/memories/m.md"

cp "$ROOT/utils/knowledgebase-write-policy.py" utils/
git add utils && git commit -qm policy && git push -q origin main
expect "hook ignores bad payload" 0 "" sh -c "echo nope | python3 $REPO/.claude/hooks/protect-knowledgebase.py"
expect "hook ignores a payload without a path" 0 "" hook Edit "" "$REPO" command
expect "hook denies Edit of a memory" 2 "$BLOCK_MSG" hook Edit "$REPO/.knowledgebase/memories/m.md"
expect "hook denies Write of a new memory" 2 "$BLOCK_MSG" hook Write "$REPO/.knowledgebase/memories/new.md"
expect "hook denies Write into a new subdirectory" 2 "$BLOCK_MSG" hook Write "$REPO/.knowledgebase/new/dir/x.md"
expect "hook denies NotebookEdit by notebook_path" 2 "$BLOCK_MSG" \
  hook NotebookEdit "$REPO/.knowledgebase/n.ipynb" "$REPO" notebook_path
expect "hook denies a path relative to the cwd" 2 "$BLOCK_MSG" hook Edit .knowledgebase/memories/m.md "$REPO"
expect "hook denies a path through .." 2 "$BLOCK_MSG" hook Edit ../.knowledgebase/memories/m.md "$REPO/src"
ln -s .knowledgebase kb && ln -s ../.knowledgebase/memories/m.md src/link.md
expect "hook denies a path through a symlinked directory" 2 "$BLOCK_MSG" hook Edit "$REPO/kb/memories/m.md"
expect "hook denies a symlink to a memory" 2 "$BLOCK_MSG" hook Edit "$REPO/src/link.md"
rm kb src/link.md
expect "hook allows a write elsewhere" 0 "" hook Edit "$REPO/src/a.cpp"
expect "hook allows a name that only resembles the directory" 0 "" hook Write "$REPO/src/.knowledgebase-notes.md"
# A separate clone is another repository even with the policy on its origin/main.
git clone -q "$TEMP_DIR/origin.git" "$TEMP_DIR/elsewhere"
expect "hook ignores another repository's knowledgebase" 0 "" \
  hook Edit "$TEMP_DIR/elsewhere/.knowledgebase/memories/m.md"
expect "hook ignores a path outside any checkout" 0 "" hook Write /nonexistent/.knowledgebase/x.md
git worktree add -q "$TEMP_DIR/wt" HEAD
expect "hook denies the knowledgebase of another worktree of this repo" 2 "$BLOCK_MSG" \
  hook Edit "$TEMP_DIR/wt/.knowledgebase/memories/m.md"

# The checkout's policy may be untrusted: the hook must run origin/main's, unimported.
git checkout -qb feature
printf 'import sys\nopen("%s/pwned", "w").close()\nsys.exit(0)\n' "$TEMP_DIR" > utils/knowledgebase-write-policy.py
cp utils/knowledgebase-write-policy.py posixpath.py
git add utils && git commit -qm tamper
expect "hook runs origin/main's policy, not the checkout's" 2 "$BLOCK_MSG" \
  hook Edit "$REPO/.knowledgebase/memories/m.md"
if [ -e "$TEMP_DIR/pwned" ]; then fail "hook ran checkout code"; else pass; fi
rm -f posixpath.py

# --- .pi/extensions/protect-knowledgebase.ts (driven through a stub Pi API) ---
if node --experimental-strip-types --no-warnings -e '' >/dev/null 2>&1; then
  cat > "$TEMP_DIR/pi-driver.mjs" <<'EOF'
const [ext, cwd, toolName, path] = process.argv.slice(2);
const mod = await import(ext);
let handler;
mod.default({ on: (name, fn) => { if (name === "tool_call") handler = fn; } });
const result = await handler({ toolName, input: { path, command: path } }, { cwd });
if (result?.block) { console.error(result.reason); process.exit(2); }
EOF
  pi_hook() {
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
      "$REPO/.pi/extensions/protect-knowledgebase.ts" "${3:-$REPO}" "$1" "$2"
  }
  expect "pi adapter ignores other tools" 0 "" pi_hook bash ".knowledgebase/memories/m.md"
  expect "pi adapter denies edit of a memory" 2 "$BLOCK_MSG" pi_hook edit ".knowledgebase/memories/m.md"
  expect "pi adapter denies write of a memory" 2 "$BLOCK_MSG" pi_hook write ".knowledgebase/memories/new.md"
  expect "pi adapter allows a write elsewhere" 0 "" pi_hook write "src/a.cpp"
  expect "pi adapter allows a checkout without the hook" 0 "" \
    pi_hook edit ".knowledgebase/memories/m.md" "$TEMP_DIR/nohook"
else
  echo "SKIP: pi adapter tests (node with --experimental-strip-types not found)"
fi

echo "$TESTS tests, $FAILED failed"
[ "$FAILED" -eq 0 ]
