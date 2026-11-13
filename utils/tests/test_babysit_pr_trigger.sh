#!/bin/bash
# Copyright 2026, Datadog, Inc.
# Hermetic tests for .claude/hooks/babysit-pr.py (the babysit-pr trigger) and its Pi
# adapter .pi/extensions/babysit-pr.ts. No gh stub is needed: the hook never calls gh,
# only git. Every branch the hook has gets a test; the adapter is driven through a stub
# Pi API like its siblings (test_review_marker.sh, test_knowledgebase_guard.sh).
set -u
FAILED=0
export PYTHONDONTWRITEBYTECODE=1 GIT_CONFIG_GLOBAL=/dev/null GIT_CONFIG_NOSYSTEM=1

TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT

pass() { TESTS=$((TESTS + 1)); }
fail() { TESTS=$((TESTS + 1)); FAILED=$((FAILED + 1)); echo "FAIL: $*" >&2; }
TESTS=0

HOOK="$TEMP_DIR/repo/.claude/hooks/babysit-pr.py"
mkdir -p "$TEMP_DIR/repo/.claude/hooks"
cp "$(dirname "$0")/../../.claude/hooks/babysit-pr.py" "$HOOK"

git -C "$TEMP_DIR/repo" init -q
git -C "$TEMP_DIR/repo" -c user.email=t -c user.name=t commit -q --allow-empty -m init

# run_hook <command> <response-stdout> [<payload-cwd>] [<process-cwd>] -> exit status;
# stderr in OUT_ERR. Command and response travel base64-encoded through argv: a heredoc
# would collapse the backslash-newline of a continued command before the payload is
# built. The payload cwd and the hook process's cwd are passed separately so tests can
# pin which one the hook's checkout guard follows.
run_hook() {
  local cmd_b64 resp_b64 cwd="${3:-$TEMP_DIR/repo}" proc_cwd="${4:-${3:-$TEMP_DIR/repo}}"
  cmd_b64=$(printf '%s' "$1" | base64)
  resp_b64=$(printf '%s' "$2" | base64)
  OUT_ERR=$(python3 - "$TEMP_DIR/repo" "$cmd_b64" "$resp_b64" "$cwd" "$proc_cwd" <<'PYEOF'
import base64, json, os, subprocess, sys
repo, cmd_b64, resp_b64, cwd, proc_cwd = sys.argv[1:6]
payload = {"cwd": cwd, "tool_name": "Bash",
           "tool_input": {"command": base64.b64decode(cmd_b64).decode()},
           "tool_response": {"stdout": base64.b64decode(resp_b64).decode(),
                             "stderr": "", "interrupted": False}}
res = subprocess.run([sys.executable, os.path.join(repo, ".claude/hooks/babysit-pr.py")],
                     input=json.dumps(payload).encode(), cwd=proc_cwd,
                     stdout=subprocess.DEVNULL, stderr=subprocess.PIPE,
                     env={**os.environ, "CLAUDE_PROJECT_DIR": repo})
print(res.stderr.decode(errors="replace"))
sys.exit(res.returncode)
PYEOF
)
  return $?
}

# 1. A successful `gh pr create` naming a protected-repo PR URL triggers (exit 2).
run_hook "gh pr create --draft -F pr-body.md" "https://github.com/datadog/java-profiler/pull/1234"
if [ $? -eq 2 ] && grep -q "babysit-pr" <<<"$OUT_ERR" && grep -q "#1234" <<<"$OUT_ERR"; then
  pass
else
  fail "protected create with URL should exit 2 naming the skill and PR (got: $OUT_ERR)"
fi

# 2. A create in another repository does not trigger.
run_hook "gh -R other/repo pr create --draft" "https://github.com/other/repo/pull/7"
if [ $? -eq 0 ]; then pass; else fail "foreign-repo create should exit 0 (got: $OUT_ERR)"; fi

# 3. A create whose response holds no URL (failed, --web) does not trigger.
run_hook "gh pr create --draft -F pr-body.md" "gh: Not Found (HTTP 404)"
if [ $? -eq 0 ]; then pass; else fail "failed create should exit 0 (got: $OUT_ERR)"; fi

# 4. `gh pr view` printing a URL does not trigger.
run_hook "gh pr view --json url" '{"url":"https://github.com/datadog/java-profiler/pull/1234"}'
if [ $? -eq 0 ]; then pass; else fail "pr view with URL should exit 0 (got: $OUT_ERR)"; fi

# 5. `gh pr ready` printing a URL does not trigger.
run_hook "gh pr ready 1234" "https://github.com/datadog/java-profiler/pull/1234"
if [ $? -eq 0 ]; then pass; else fail "pr ready with URL should exit 0 (got: $OUT_ERR)"; fi

# 6. A command in another checkout — a real second git repository whose common dir
#    differs from the project's — does not trigger. This exercises the distinct-
#    common-dir comparison, not just the not-a-checkout shortcut.
git -C "$TEMP_DIR/other" init -q 2>/dev/null || mkdir -p "$TEMP_DIR/other"
git -C "$TEMP_DIR/other" init -q
git -C "$TEMP_DIR/other" -c user.email=t -c user.name=t commit -q --allow-empty -m init
run_hook "gh pr create --draft" "https://github.com/datadog/java-profiler/pull/1234" "$TEMP_DIR/other"
if [ $? -eq 0 ]; then pass; else fail "other-checkout create should exit 0 (got: $OUT_ERR)"; fi

# 7. A backslash-continued create still triggers: the payload must carry a raw
#    backslash-newline for the hook's continuation-join to collapse.
run_hook 'gh pr \
  create --draft -F pr-body.md' "https://github.com/datadog/java-profiler/pull/9"
if [ $? -eq 2 ]; then pass; else fail "backslash-continued create should exit 2 (got: $OUT_ERR)"; fi

# 8. A quoted false-positive cost is accepted and pinned: raw text matching triggers on
#    a command that only mentions `gh pr create`.
run_hook "echo 'gh pr create'" "https://github.com/datadog/java-profiler/pull/1234"
if [ $? -eq 2 ]; then pass; else fail "quoted mention should still trigger, pinning the documented cost (got: $OUT_ERR)"; fi

# 9. The last protected bare-URL line is the one named; a trailing foreign bare URL
#    does not hide the protected create.
run_hook "gh pr create --draft -F pr-body.md" "https://github.com/datadog/java-profiler/pull/1
https://github.com/other/repo/pull/7"
if [ $? -eq 2 ] && grep -q "#1" <<<"$OUT_ERR"; then pass; else fail "last protected bare URL should be named (got: $OUT_ERR)"; fi

# 10. A compound command where the create failed and only `gh pr view` printed a URL
#     (embedded in JSON, not a bare line) does not trigger: the URL is never bound to
#     a create that did not happen.
run_hook "gh pr create --draft -F pr-body.md; gh pr view 12 --json url" '{"url":"https://github.com/datadog/java-profiler/pull/12"}'
if [ $? -eq 0 ]; then pass; else fail "JSON-embedded URL after failed create should exit 0 (got: $OUT_ERR)"; fi

# 11. A URL is matched case-insensitively: removing the .lower() comparison would
#     silently drop this trigger.
run_hook "gh pr create --draft -F pr-body.md" "https://github.com/Datadog/Java-Profiler/pull/77"
if [ $? -eq 2 ] && grep -q "#77" <<<"$OUT_ERR"; then pass; else fail "uppercase repo URL should trigger naming #77 (got: $OUT_ERR)"; fi

# 12. Malformed JSON on stdin fails open: exit 0, no traceback — pinning the
#     fail-open guard (deleting it would crash the hook on any malformed payload).
OUT_ERR=$(cd "$TEMP_DIR/repo" && printf 'not json' | CLAUDE_PROJECT_DIR="$TEMP_DIR/repo" python3 "$HOOK" 2>&1 >/dev/null)
HOOK_RC=$?
if [ "$HOOK_RC" -eq 0 ] && ! grep -q "Traceback" <<<"$OUT_ERR"; then
  pass
else
  fail "malformed JSON should fail open with exit 0 and no traceback (rc=$HOOK_RC, got: $OUT_ERR)"
fi

# 13. A structurally malformed but valid-JSON payload (tool_input null) also fails
#     open: no traceback, exit 0.
OUT_ERR=$(cd "$TEMP_DIR/repo" && printf '{"tool_input":null,"tool_response":{}}' | CLAUDE_PROJECT_DIR="$TEMP_DIR/repo" python3 "$HOOK" 2>&1 >/dev/null)
HOOK_RC=$?
if [ "$HOOK_RC" -eq 0 ] && ! grep -q "Traceback" <<<"$OUT_ERR"; then
  pass
else
  fail "null tool_input should fail open with exit 0 and no traceback (rc=$HOOK_RC, got: $OUT_ERR)"
fi

# 14. A valid-JSON non-object payload also fails open: no traceback, exit 0.
OUT_ERR=$(cd "$TEMP_DIR/repo" && printf '[]' | CLAUDE_PROJECT_DIR="$TEMP_DIR/repo" python3 "$HOOK" 2>&1 >/dev/null)
HOOK_RC=$?
if [ "$HOOK_RC" -eq 0 ] && ! grep -q "Traceback" <<<"$OUT_ERR"; then
  pass
else
  fail "non-object payload should fail open with exit 0 and no traceback (rc=$HOOK_RC, got: $OUT_ERR)"
fi

# 15. The checkout guard follows the payload's cwd, not the hook process's cwd: a
#     payload naming the other repository but a process running inside the project's
#     checkout must not trigger. Removing the payload-cwd fallback (always using
#     os.getcwd()) makes this case trigger and kills this test.
run_hook "gh pr create --draft" "https://github.com/datadog/java-profiler/pull/1234" \
  "$TEMP_DIR/other" "$TEMP_DIR/repo"
if [ $? -eq 0 ]; then pass; else fail "payload cwd in another checkout should exit 0 (got: $OUT_ERR)"; fi

# 16. A payload cwd that is not a git checkout at all fails closed without a crash:
#     `top` is None, and dropping the `top and` guard would resolve the common dir
#     against the process cwd (the project checkout) and trigger.
mkdir -p "$TEMP_DIR/plain"
run_hook "gh pr create --draft" "https://github.com/datadog/java-profiler/pull/1234" \
  "$TEMP_DIR/plain" "$TEMP_DIR/repo"
if [ $? -eq 0 ]; then pass; else fail "non-git payload cwd should exit 0 (got: $OUT_ERR)"; fi

# --- .pi/extensions/babysit-pr.ts (driven through a stub Pi API) ---
if node --experimental-strip-types --no-warnings -e "" >/dev/null 2>&1; then
  cat > "$TEMP_DIR/pi-driver.mjs" <<'EOF'
const [ext, cwd, toolName, command, response] = process.argv.slice(2);
const mod = await import(ext);
let handler;
mod.default({ on: (name, fn) => { if (name === "tool_result") handler = fn; } });
const content = response ? [{ type: "text", text: response }] : [];
const result = await handler(
  { toolName, input: command === undefined ? {} : { command }, content, isError: false },
  { cwd });
const appended = result?.content?.length > content.length
  ? result.content[result.content.length - 1].text : "";
process.stdout.write(appended);
process.exit(appended ? 2 : 0);
EOF
  pi_hook() {
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
      "$PWD/.pi/extensions/babysit-pr.ts" "${4:-$TEMP_DIR/repo}" "$1" "$2" "$3"
  }
  expect() { # expect <name> <rc> <grep-pattern> <args to pi_hook...>
    local name="$1" want_rc="$2" pattern="$3"; shift 3
    local out rc
    out=$(pi_hook "$@"); rc=$?
    if [ "$rc" -eq "$want_rc" ] && { [ -z "$pattern" ] || grep -q "$pattern" <<<"$out"; }; then
      pass
    else
      fail "$name: want rc=$want_rc grep='$pattern', got rc=$rc out='$out'"
    fi
  }
  expect "pi adapter ignores other tools" 0 "" read "gh pr create" ""
  expect "pi adapter ignores unrelated bash (pre-filter skips the spawn)" 0 "" bash "ls -la" ""
  expect "pi adapter skips non-create gh commands" 0 "" bash "gh pr checks 1" ""
  expect "pi adapter skips a checkout without the hook" 0 "" bash "gh pr create" "" "$TEMP_DIR/nogit"
  expect "pi adapter tolerates an empty event" 0 "" bash "" ""
  expect "pi adapter appends the trigger for a create" 2 "babysit-pr" \
    bash "gh pr create --draft -F pr-body.md" "https://github.com/datadog/java-profiler/pull/1234"
  expect "pi adapter appends nothing when the hook stays silent" 0 "" \
    bash "gh pr create --draft -F pr-body.md" "gh: Not Found (HTTP 404)"
else
  echo "SKIP: pi adapter tests (node with --experimental-strip-types not found)"
fi

echo "$0: $TESTS tests, $FAILED failed"
exit $((FAILED > 0))
