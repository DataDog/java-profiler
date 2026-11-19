#! /bin/bash
# Minimal, dependency-free unit tests for the CANCELLED/cancelled decision in
# generate-benchmarks-child-pipeline (.gitlab/benchmarks/.gitlab-ci.yml).
# Run with: bash .gitlab/scripts/tests/test_generate_benchmarks.sh
#
# The generator's script block is extracted from the YAML and executed in a
# sandbox with a stubbed check-stack-top.sh, so no network access and no
# GitLab runner are involved. Regression guard: a branch push without an open
# PR (CANCELLED=true from prepare:start) must produce the noop child pipeline
# — never the real one that benchmarks a snapshot deploy-artifact never
# published.

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
YAML="${HERE}/../../benchmarks/.gitlab-ci.yml"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT
# the extracted script is run with bash by absolute path, like
# test_check_stack_top.sh restricts its PATH
BASH_BIN=$(command -v bash)

fail() { echo "FAIL: $*"; FAILED=1; }
pass() { echo "PASS: $*"; }

# Extract the generator's script block (the `- |` literal under
# generate-benchmarks-child-pipeline's script:) as an executable bash snippet.
# Fails loudly if the YAML layout drifts, so the tests can never silently run
# a stale copy.
extract_script() {
  awk '
    /^generate-benchmarks-child-pipeline:/ { injob=1 }
    injob && /^  script:/ { inscript=1; next }
    inscript && /^    - \|$/ { inblock=1; next }
    inblock && /^      / { sub(/^      /, ""); print; next }
    inblock { exit }
  ' "$YAML"
}

SCRIPT_FILE="$WORK/generator-script.sh"
extract_script > "$SCRIPT_FILE"
if [ ! -s "$SCRIPT_FILE" ]; then
  echo "FAIL: could not extract the generator script block from $YAML"
  exit 1
fi

# Build the sandbox: stubbed check-stack-top.sh (appends "invoked" to
# $STACK_LOG, prints $FAKE_STACK_OUT) and a sentinel child pipeline file for
# the cp branch.
setup_sandbox() {
  local dir="$WORK/sandbox"
  rm -rf "$dir"
  mkdir -p "$dir/.gitlab/benchmarks"
  cat > "$dir/.gitlab/benchmarks/check-stack-top.sh" << 'STUB'
#! /bin/bash
echo "invoked" >> "$STACK_LOG"
# dash form: an explicitly empty FAKE_STACK_OUT must reach the generator
printf '%s\n' "${FAKE_STACK_OUT-RUN_BENCHMARKS=true}"
STUB
  chmod +x "$dir/.gitlab/benchmarks/check-stack-top.sh"
  printf 'real-child-pipeline\n' > "$dir/.gitlab/benchmarks/child.gitlab-ci.yml"
  echo "$dir"
}

# run_generator <desc> [KEY=VALUE env assignments...]
# GC_CANCELLED: set => run with CANCELLED=<value>; unset => run with CANCELLED
# removed from the environment. Leaves RESULT (stdout), CHILD (generated
# child pipeline contents), STACK_INVOKED and the generator diagnostics.
RUN_N=0
GENERATOR_STATUS=0
GENERATOR_STDERR=""
run_generator() {
  local desc="$1"; shift
  local dir log
  dir=$(setup_sandbox)
  RUN_N=$((RUN_N + 1))
  log="$WORK/stack_log.$RUN_N"
  GENERATOR_STDERR="$WORK/generator_stderr.$RUN_N"
  : > "$log"
  : > "$GENERATOR_STDERR"
  if [ -n "${GC_CANCELLED+x}" ]; then
    RESULT=$(cd "$dir" && env CANCELLED="$GC_CANCELLED" STACK_LOG="$log" "$@" \
      "$BASH_BIN" "$SCRIPT_FILE" 2>"$GENERATOR_STDERR")
  else
    RESULT=$(cd "$dir" && env -u CANCELLED STACK_LOG="$log" "$@" \
      "$BASH_BIN" "$SCRIPT_FILE" 2>"$GENERATOR_STDERR")
  fi
  GENERATOR_STATUS=$?
  CHILD=$(cat "$dir/generated-benchmarks.yml" 2>/dev/null || true)
  STACK_INVOKED=$(cat "$log" 2>/dev/null || true)
}

generator_diagnostics() {
  local stderr=""
  if [ -n "$GENERATOR_STDERR" ] && [ -f "$GENERATOR_STDERR" ]; then
    stderr=$(cat "$GENERATOR_STDERR")
  fi
  printf 'generator status: %s\nstdout:\n%s\nstderr:\n%s' \
    "$GENERATOR_STATUS" "$RESULT" "$stderr"
}

diagnostics_match() {
  local captured="$1" status="$2" stdout="$3" stderr="$4" expected
  expected=$(printf 'generator status: %s\nstdout:\n%s\nstderr:\n%s' "$status" "$stdout" "$stderr")
  [[ "$captured" == *"$expected" ]]
}

expect_result() {
  local desc="$1" expected="$2" actual count
  if [ "$GENERATOR_STATUS" -ne 0 ]; then
    fail "$desc — generator exited with status $GENERATOR_STATUS"$'\n'"$(generator_diagnostics)"
    return
  fi

  count=$(printf '%s\n' "$RESULT" | awk '/^RUN_BENCHMARKS=/{n++} END{print n+0}')
  if [ "$count" -ne 1 ]; then
    fail "$desc — expected exactly one RUN_BENCHMARKS= line, got $count"$'\n'"$(generator_diagnostics)"
    return
  fi

  actual=$(printf '%s\n' "$RESULT" | sed -n 's/^RUN_BENCHMARKS=//p')
  if [ "$actual" = "$expected" ]; then
    pass "$desc"
  else
    fail "$desc — expected RUN_BENCHMARKS=$expected"$'\n'"$(generator_diagnostics)"
  fi
}

expect_child() {
  local desc="$1" kind="$2"
  case "$kind" in
    noop)
      if printf '%s' "$CHILD" | grep -q 'skip-benchmarks:'; then
        pass "$desc"
      else
        fail "$desc — expected the noop child, got: ${CHILD:0:80}"$'\n'"$(generator_diagnostics)"
      fi
      ;;
    real)
      if [ "$CHILD" = "real-child-pipeline" ]; then
        pass "$desc"
      else
        fail "$desc — expected the real child pipeline, got: ${CHILD:0:80}"$'\n'"$(generator_diagnostics)"
      fi
      ;;
  esac
}

expect_stack_check() {
  local desc="$1" expected="$2" # yes|no
  if { [ "$expected" = "yes" ] && [ -n "$STACK_INVOKED" ]; } || \
     { [ "$expected" = "no" ] && [ -z "$STACK_INVOKED" ]; }; then
    pass "$desc"
  else
    fail "$desc — stack check invoked: ${STACK_INVOKED:+yes}${STACK_INVOKED:-no}"
  fi
}

assert_result_rejected_with_diagnostics() {
  local desc="$1" output="$2" status="$3" stderr="$4"
  local stderr_file="$WORK/assertion.stderr" captured
  printf '%s' "$stderr" > "$stderr_file"
  if captured=$(
    FAILED=0
    RESULT="$output"
    GENERATOR_STATUS="$status"
    GENERATOR_STDERR="$stderr_file"
    expect_result "$desc" true
    [ "$FAILED" -eq 1 ]
  ) 2>&1; then
    if diagnostics_match "$captured" "$status" "$output" "$stderr"; then
      pass "$desc rejects output and reports complete diagnostics"
    else
      fail "$desc did not report status, full stdout, and stderr"
    fi
  else
    fail "$desc was not rejected"
  fi
}

assert_run_generator_captures_exit_status() {
  local script="$WORK/nonzero-generator.sh" captured
  cat > "$script" << 'STUB'
printf '%s\n' 'RUN_BENCHMARKS=true'
printf '%s\n' 'nonzero-process-stderr' >&2
exit 17
STUB
  if captured=$(
    FAILED=0
    SCRIPT_FILE="$script"
    GC_CANCELLED=true
    run_generator "nonzero process exit"
    expect_result "nonzero process exit" true
    [ "$GENERATOR_STATUS" -eq 17 ] && [ "$FAILED" -eq 1 ]
  ) 2>&1; then
    if diagnostics_match "$captured" 17 'RUN_BENCHMARKS=true' 'nonzero-process-stderr'; then
      pass "run_generator captures nonzero exit status and diagnostics"
    else
      fail "run_generator did not report the nonzero process status and diagnostics"
    fi
  else
    fail "run_generator did not reject the nonzero process"
  fi
}

assert_child_rejected_with_diagnostics() {
  local stderr_file="$WORK/child-assertion.stderr" captured
  printf '%s' 'child-stderr-marker' > "$stderr_file"
  if captured=$(
    FAILED=0
    RESULT='child stdout marker'
    GENERATOR_STATUS=17
    GENERATOR_STDERR="$stderr_file"
    CHILD='unexpected child'
    expect_child 'controlled child failure' noop
    [ "$FAILED" -eq 1 ]
  ) 2>&1; then
    if diagnostics_match "$captured" 17 'child stdout marker' 'child-stderr-marker'; then
      pass "child failure reports status, full stdout, and stderr"
    else
      fail "child failure did not report complete generator diagnostics"
    fi
  else
    fail "controlled child assertion was not rejected"
  fi
}

# GC_CANCELLED is set and unset as plain statements, never as `VAR=x func`
# prefixes: whether such an assignment outlives the function is
# shell-version-dependent, so each case must control its own mode explicitly.

# CANCELLED=true (no open PR): noop child, stack check must not run
GC_CANCELLED=true
run_generator "cancelled"
expect_result "CANCELLED=true skips benchmarks" false
expect_child "CANCELLED=true emits the noop child" noop
expect_stack_check "CANCELLED=true never consults the stack check" no

# CANCELLED=false (web pipelines without the guard): follows the stack check
GC_CANCELLED=false
run_generator "cancelled-false" FAKE_STACK_OUT="RUN_BENCHMARKS=true"
expect_result "CANCELLED=false follows the stack check" true
expect_child "CANCELLED=false emits the real child" real
expect_stack_check "CANCELLED=false consults the stack check" yes

# CANCELLED unset (normal PR push): follows the stack check both ways
unset GC_CANCELLED
run_generator "stack-top" FAKE_STACK_OUT="RUN_BENCHMARKS=true"
expect_result "stack-top branch enables benchmarks" true
expect_child "stack-top branch emits the real child" real
expect_stack_check "stack-top decision consults the stack check" yes

run_generator "not-stack-top" FAKE_STACK_OUT="RUN_BENCHMARKS=false"
expect_result "not-stack-top branch skips benchmarks" false
expect_child "not-stack-top branch emits the noop child" noop
expect_stack_check "not-stack-top decision consults the stack check" yes

# unambiguous-parse fail-open: empty/garbled stack-check output must never
# skip benchmarks
run_generator "garbled" FAKE_STACK_OUT=""
expect_result "garbled stack-check output fails open" true
expect_child "garbled stack-check output emits the real child" real

# Exercise parser failures and diagnostics without altering the extracted
# generator scenarios above.
assert_result_rejected_with_diagnostics "missing contract line" \
  'generator stdout without a decision' 0 'missing-contract-stderr'
assert_result_rejected_with_diagnostics "duplicate contract lines" \
  $'RUN_BENCHMARKS=true\nRUN_BENCHMARKS=false' 0 'duplicate-contract-stderr'
assert_result_rejected_with_diagnostics "wrong contract value" \
  'RUN_BENCHMARKS=false' 0 'wrong-value-stderr'
assert_result_rejected_with_diagnostics "nonzero generator status" \
  'RUN_BENCHMARKS=true' 17 'nonzero-status-stderr'
assert_run_generator_captures_exit_status
assert_child_rejected_with_diagnostics

saved_script_file="$SCRIPT_FILE"
SCRIPT_FILE="$WORK/stream-separation-generator.sh"
cat > "$SCRIPT_FILE" << 'STUB'
printf '%s\n' 'RUN_BENCHMARKS=true'
printf '%s\n' 'stderr-only-marker' >&2
printf '%s\n' 'real-child-pipeline' > generated-benchmarks.yml
STUB
GC_CANCELLED=true
run_generator "stream-separation"
if [ "$RESULT" = 'RUN_BENCHMARKS=true' ] && \
   [ "$(cat "$GENERATOR_STDERR")" = 'stderr-only-marker' ]; then
  pass "generator stderr stays separate from contract stdout"
else
  fail "generator stderr contaminated stdout or was not captured"$'\n'"$(generator_diagnostics)"
fi
expect_result "controlled generator emits one contract line" true
SCRIPT_FILE="$saved_script_file"

if [ "$FAILED" -ne 0 ]; then
  echo "test_generate_benchmarks: FAILED"
  exit 1
fi
echo "test_generate_benchmarks: all passed"
