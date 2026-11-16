#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# Tests for .pi/extensions/native-agents.ts, driven through a stub Pi API in a throwaway
# repo. Needs Node.js 22.6 or newer (--experimental-strip-types); older versions skip.
# Run with: bash utils/tests/test_native_agents_pi.sh

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

if ! node --experimental-strip-types --no-warnings -e '' >/dev/null 2>&1; then
  echo "SKIP: pi native-agents tests (node with --experimental-strip-types not found)"
  exit 0
fi

# The driver replays events against one extension instance and prints one line per
# tool_result: "inject <first item kept> <instructions text present> <structuredContent kept>",
# or "none" when the handler leaves the result alone. A step "rm:<path>" deletes a file,
# and "cd:<dir>" changes the cwd that later events pass.
cat > "$TEMP_DIR/driver.mjs" <<'EOF'
const [ext, cwd0, ...steps] = process.argv.slice(2);
const mod = await import(ext);
const handlers = {};
mod.default({ on: (name, fn) => { handlers[name] = fn; } });
const out = [];
let cwd = cwd0;
for (const step of steps) {
  const [ev, tool, path] = step.split(":");
  if (ev === "rm") { (await import("node:fs")).rmSync(tool); continue; }
  if (ev === "cd") { cwd = tool; continue; }
  if (ev !== "tool_result") { await handlers[ev]({ type: ev }, { cwd }); continue; }
  const content = [{ type: "text", text: "ORIGINAL" }];
  const structuredContent = { kept: true };
  const r = await handlers.tool_result({ type: ev, toolName: tool, input: { path, command: path },
    content, structuredContent, isError: false }, { cwd });
  if (!r) { out.push("none"); continue; }
  const text = r.content.slice(1).map((c) => c.text).join("");
  out.push(["inject", r.content[0].text === "ORIGINAL", text.includes("NATIVE-RULES-TOKEN"),
    r.structuredContent === structuredContent].join(" "));
}
console.log(out.join(","));
EOF

REPO="$TEMP_DIR/repo"
mkdir -p "$REPO/.pi/extensions" "$REPO/ddprof-lib/src/main/cpp" "$REPO/ddprof-lib/src/test/fuzz" \
  "$REPO/ddprof-lib/src/main/java" "$REPO/malloc-shim/src"
git -C "$REPO" init -q
cp "$ROOT/.pi/extensions/native-agents.ts" "$REPO/.pi/extensions/"
cp "$ROOT/.pi/native-agents.json" "$REPO/.pi/"
INSTRUCTIONS=$(python3 -c 'import json,sys; print(json.load(open(sys.argv[1]))["instructions"])' "$REPO/.pi/native-agents.json")
echo "NATIVE-RULES-TOKEN" > "$REPO/$INSTRUCTIONS"

HIT="inject true true true"
# check <name> <expected lines, comma-separated> <cwd> <steps...>
check() {
  local name=$1 want=$2 cwd=$3; shift 3
  local got rc=0
  got=$(node --experimental-strip-types --no-warnings "$TEMP_DIR/driver.mjs" \
    "$REPO/.pi/extensions/native-agents.ts" "$cwd" "$@" 2>&1) || rc=$?
  if [ "$rc" -ne 0 ] || [ "$got" != "$want" ]; then
    fail "$name: got '$got' (exit $rc), want '$want'"
  else
    pass
  fi
}

check "first read below a covered dir injects; the second does not" "$HIT,none" "$REPO" \
  tool_result:read:ddprof-lib/src/main/cpp/profiler.cpp tool_result:read:ddprof-lib/src/main/cpp/profiler.h
check "session_compact re-arms the injection" "$HIT,none,$HIT" "$REPO" \
  tool_result:read:ddprof-lib/src/main/cpp/a.cpp tool_result:edit:ddprof-lib/src/main/cpp/a.cpp \
  session_compact tool_result:read:ddprof-lib/src/main/cpp/a.cpp
check "session_start re-arms the injection" "$HIT,$HIT" "$REPO" \
  tool_result:read:ddprof-lib/src/main/cpp/a.cpp session_start tool_result:read:ddprof-lib/src/main/cpp/a.cpp
check "write of a new file in another covered dir" "$HIT" "$REPO" \
  tool_result:write:ddprof-lib/src/test/fuzz/new_fuzzer.cpp
check "edit with Pi's @ prefix" "$HIT" "$REPO" tool_result:edit:@malloc-shim/src/shim.c
check "relative path from a subdirectory" "$HIT" "$REPO/ddprof-lib/src/main/java" \
  tool_result:read:../cpp/a.cpp
check "absolute path" "$HIT" "$REPO" tool_result:read:"$REPO/ddprof-lib/src/main/cpp/a.cpp"
check "a file outside the covered dirs does not use up the injection" "none,$HIT" "$REPO" \
  tool_result:read:ddprof-lib/src/main/java/A.java tool_result:read:ddprof-lib/src/main/cpp/a.cpp
check "a directory name that only starts like a covered dir" "none" "$REPO" \
  tool_result:read:ddprof-lib/src/main/cppx/a.cpp
check "the covered dir itself is not below it" "none" "$REPO" tool_result:read:ddprof-lib/src/main/cpp
check "a path outside the checkout" "none" "$REPO" \
  tool_result:read:../other/ddprof-lib/src/main/cpp/a.cpp
check "bash and grep are not covered" "none,none" "$REPO" \
  tool_result:bash:ddprof-lib/src/main/cpp/a.cpp tool_result:grep:ddprof-lib/src/main/cpp/a.cpp
check "empty path" "none" "$REPO" tool_result:read:
HOME="$TEMP_DIR" check "~ expands to HOME" "$HIT" "$REPO" tool_result:read:"~/repo/ddprof-lib/src/main/cpp/a.cpp"

LIST="$REPO/.pi/native-agents.json"
check "the list is read once per session" "none,$HIT" "$REPO" \
  tool_result:read:ddprof-lib/src/main/java/A.java rm:"$LIST" tool_result:read:ddprof-lib/src/main/cpp/a.cpp
cp "$ROOT/.pi/native-agents.json" "$LIST"
check "session_start drops the cached list" "none,none" "$REPO" \
  tool_result:read:ddprof-lib/src/main/java/A.java rm:"$LIST" session_start \
  tool_result:read:ddprof-lib/src/main/cpp/a.cpp
cp "$ROOT/.pi/native-agents.json" "$LIST"
check "the cache is per cwd" "none,none" "$REPO" \
  tool_result:read:ddprof-lib/src/main/java/A.java rm:"$LIST" cd:"$REPO/ddprof-lib/src/main/java" \
  tool_result:read:../cpp/a.cpp
cp "$ROOT/.pi/native-agents.json" "$LIST"

mv "$REPO/$INSTRUCTIONS" "$TEMP_DIR/instructions.bak"
check "missing instruction file" "none" "$REPO" tool_result:read:ddprof-lib/src/main/cpp/a.cpp
mv "$TEMP_DIR/instructions.bak" "$REPO/$INSTRUCTIONS"
mv "$REPO/.pi/native-agents.json" "$TEMP_DIR/list.bak"
check "missing directory list" "none" "$REPO" tool_result:read:ddprof-lib/src/main/cpp/a.cpp
mv "$TEMP_DIR/list.bak" "$REPO/.pi/native-agents.json"
mkdir -p "$TEMP_DIR/nogit/ddprof-lib/src/main/cpp" "$TEMP_DIR/nogit/.pi"
cp "$REPO/.pi/native-agents.json" "$TEMP_DIR/nogit/.pi/"
cp "$REPO/$INSTRUCTIONS" "$TEMP_DIR/nogit/$INSTRUCTIONS"
check "outside a git checkout, paths are relative to the cwd" "$HIT" "$TEMP_DIR/nogit" \
  tool_result:read:ddprof-lib/src/main/cpp/a.cpp

echo "$TESTS tests, $FAILED failed"
[ "$FAILED" -eq 0 ]
