#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# Tests for utils/gradle-command-policy.py, the Claude Code hook
# .claude/hooks/require-gradle-wrapper.py and its Pi adapter, plus the agent
# configuration that must not grant or run gradlew directly. Hook cases run in a
# throwaway repo with a bare origin; global git config is ignored.
# Run with: bash utils/tests/test_gradle_hook.sh

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

BLOCK_MSG="build-and-summarize"

# --- utils/gradle-command-policy.py ---
policy() { printf '%s' "$1" | python3 -I "$ROOT/utils/gradle-command-policy.py"; }
for c in './gradlew build' 'gradlew build' '/abs/path/gradlew build' './gradlew.bat build' \
         './gradlew' 'cd x && ./gradlew build' 'true; ./gradlew build' 'true || ./gradlew build' \
         'ls | ./gradlew build' '(./gradlew build)' 'echo $(./gradlew -q properties)' \
         'bash -c "./gradlew build"' "sh -c './gradlew build'" 'sh gradlew tasks' \
         'FOO=1 ./gradlew build' 'env JAVA_HOME=/x ./gradlew build' 'timeout 60 ./gradlew test' \
         'nohup ./gradlew build' $'./gradlew \\\nbuild' './gradlew --stop && ./gradlew build' \
         './gradlew --stop build' $'ls\n./gradlew build' './gradlew --stop "build"' \
         "./gradlew --version 'build'" './gradlew build \' 'if ./gradlew test; then :; fi' \
         'while ./gradlew test; do :; done' 'until ./gradlew test; do :; done' \
         'if false; then :; elif ./gradlew test; then :; fi' 'env -u JAVA_TOOL_OPTIONS ./gradlew build' \
         '> /tmp/log ./gradlew build' '2>&1 ./gradlew build' 'nice -n 5 ./gradlew build' \
         '! ./gradlew build' 'bash -c "cd x; ./gradlew build"' 'xargs ./gradlew' \
         'cat x && ./gradlew build' 'bash -c "gradlew build; ls"'; do
  expect "policy denies: $c" 2 "$BLOCK_MSG" policy "$c"
done
for c in './.claude/commands/build-and-summarize buildDebug' './gradlew --stop' \
         './gradlew --version' './gradlew --stop 2>/dev/null' './gradlew --stop > /dev/null' \
         './gradlew --version >/dev/null' \
         $'./gradlew --stop \\\n' './gradlewx build' 'cat gradlew' \
         'git diff -- gradlew gradlew.bat' 'grep -n gradlew AGENTS.md' 'ls gradle/wrapper' '' \
         'echo "./gradlew build"' 'git commit -m "run ./gradlew build"' "bash -c './gradlew --stop'" \
         '`./gradlew --version`' 'find . -name gradlew' '/usr/bin/grep gradlew x' \
         'LC_ALL=C grep gradlew x'; do
  expect "policy allows: $c" 0 "" policy "$c"
done
expect "policy blocks a non-reader naming gradlew (accepted false positive)" 2 "$BLOCK_MSG" \
  policy 'mv gradlew gradlew.old'
expect "policy names the blocked command" 2 'Blocked `./gradlew build`' policy 'cd x && ./gradlew build'
expect "policy names a nested blocked command" 2 'Blocked `./gradlew build`' policy "sh -c './gradlew build'"

# --- agent configuration (no direct gradlew grant or call) ---
if python3 -c 'import json,sys; a=json.load(open(sys.argv[1]))["permissions"]["allow"]; sys.exit(any("gradlew" in r for r in a))' \
     "$ROOT/.claude/settings.json"; then pass; else fail "settings.json allows gradlew"; fi
for f in .claude/commands/jmh.md .claude/agents/jmh-benchmarks.md; do
  if grep -nE '\./gradlew|Bash\(gradlew' "$ROOT/$f"; then fail "$f grants or runs gradlew"; else pass; fi
done
HOOK_CMD=$(python3 -c 'import json,sys
for e in json.load(open(sys.argv[1]))["hooks"]["PreToolUse"]:
    for h in e["hooks"]:
        if e.get("matcher") == "Bash" and "require-gradle-wrapper.py" in h["command"]: print(h["command"])' \
  "$ROOT/.claude/settings.json")
if [ -n "$HOOK_CMD" ]; then pass; else fail "settings.json does not register the hook for Bash"; fi
mkdir -p "$TEMP_DIR/nohook"
expect "settings hook command allows everything when the hook file is missing" 0 "" \
  sh -c "echo '{\"tool_input\":{\"command\":\"./gradlew build\"}}' | CLAUDE_PROJECT_DIR=$TEMP_DIR/nohook sh -c '$HOOK_CMD'"

# --- .claude/hooks/require-gradle-wrapper.py ---
git init -q --bare "$TEMP_DIR/origin.git"
mkdir -p "$TEMP_DIR/repo" && cd "$TEMP_DIR/repo"
git init -q -b main
git config user.email t@example.com && git config user.name t
mkdir -p utils .claude/hooks .pi/extensions
cp "$ROOT/.claude/hooks/require-gradle-wrapper.py" .claude/hooks/
cp "$ROOT/.pi/extensions/require-gradle-wrapper.ts" .pi/extensions/
git add . && git commit -qm "hook without policy"
git remote add origin "$TEMP_DIR/origin.git" && git push -q origin main

hook() {
  python3 -I -c 'import json,sys; print(json.dumps({"cwd": sys.argv[2], "tool_input": {"command": sys.argv[1]}}))' \
    "$1" "${2:-$PWD}" | CLAUDE_PROJECT_DIR=$PWD python3 .claude/hooks/require-gradle-wrapper.py
}
expect "hook allows everything while origin/main lacks the policy" 0 "" hook "./gradlew build"

cp "$ROOT/utils/gradle-command-policy.py" utils/
git add utils && git commit -qm policy && git push -q origin main
expect "hook ignores bad payload" 0 "" sh -c 'echo nope | python3 .claude/hooks/require-gradle-wrapper.py'
expect "hook allows unrelated command" 0 "" hook "ls -la"
expect "hook denies direct gradlew" 2 "$BLOCK_MSG" hook "./gradlew build"
expect "hook allows gradlew --stop" 0 "" hook "./gradlew --stop"
mkdir -p "$TEMP_DIR/elsewhere" && (cd "$TEMP_DIR/elsewhere" && git init -q)
expect "hook ignores commands run in another repository" 0 "" hook "./gradlew build" "$TEMP_DIR/elsewhere"

# The checkout's policy may be untrusted: the hook must run origin/main's, unimported.
git checkout -qb feature
printf 'import sys\nopen("%s/pwned", "w").close()\nsys.exit(0)\n' "$TEMP_DIR" > utils/gradle-command-policy.py
cp utils/gradle-command-policy.py re.py
git add utils && git commit -qm tamper
expect "hook runs origin/main's policy, not the checkout's" 2 "$BLOCK_MSG" hook "./gradlew build"
if [ -e "$TEMP_DIR/pwned" ]; then fail "hook ran checkout code"; else pass; fi
rm -f re.py

# --- .pi/extensions/require-gradle-wrapper.ts (driven through a stub Pi API) ---
if node --experimental-strip-types --no-warnings -e '' >/dev/null 2>&1; then
  cat > "$TEMP_DIR/pi-driver.mjs" <<'EOF'
const [ext, cwd, toolName, command] = process.argv.slice(2);
const mod = await import(ext);
let handler;
mod.default({ on: (name, fn) => { if (name === "tool_call") handler = fn; } });
const result = await handler({ toolName, input: { command } }, { cwd });
if (result?.block) { console.error(result.reason); process.exit(2); }
EOF
  pi_hook() {
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
      "$PWD/.pi/extensions/require-gradle-wrapper.ts" "${3:-$PWD}" "$1" "$2"
  }
  expect "pi adapter ignores other tools" 0 "" pi_hook read "./gradlew build"
  expect "pi adapter allows unrelated bash" 0 "" pi_hook bash "ls -la"
  expect "pi adapter denies direct gradlew" 2 "$BLOCK_MSG" pi_hook bash "./gradlew build"
  expect "pi adapter allows a checkout without the hook" 0 "" pi_hook bash "./gradlew build" "$TEMP_DIR/nohook"
else
  echo "SKIP: pi adapter tests (node with --experimental-strip-types not found)"
fi

echo "$TESTS tests, $FAILED failed"
[ "$FAILED" -eq 0 ]
