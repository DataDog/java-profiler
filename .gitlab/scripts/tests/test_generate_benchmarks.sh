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
# child pipeline contents) and STACK_INVOKED (whether the stub ran).
RUN_N=0
run_generator() {
  local desc="$1"; shift
  local dir log
  dir=$(setup_sandbox)
  RUN_N=$((RUN_N + 1))
  log="$WORK/stack_log.$RUN_N"
  : > "$log"
  if [ -n "${GC_CANCELLED+x}" ]; then
    RESULT=$(cd "$dir" && env CANCELLED="$GC_CANCELLED" STACK_LOG="$log" "$@" \
      "$BASH_BIN" "$SCRIPT_FILE" 2>/dev/null)
  else
    RESULT=$(cd "$dir" && env -u CANCELLED STACK_LOG="$log" "$@" \
      "$BASH_BIN" "$SCRIPT_FILE" 2>/dev/null)
  fi
  CHILD=$(cat "$dir/generated-benchmarks.yml" 2>/dev/null || true)
  STACK_INVOKED=$(cat "$log" 2>/dev/null || true)
}

expect_result() {
  local desc="$1" expected="$2" actual
  # the decision contract is the single RUN_BENCHMARKS= line on stdout
  actual=$(printf '%s\n' "$RESULT" | sed -n 's/^RUN_BENCHMARKS=//p' | head -1)
  if [ "$actual" = "$expected" ]; then
    pass "$desc"
  else
    fail "$desc — expected RUN_BENCHMARKS=$expected, got '${RESULT}'"
  fi
}

expect_child() {
  local desc="$1" kind="$2"
  case "$kind" in
    noop)
      if printf '%s' "$CHILD" | grep -q 'skip-benchmarks:'; then
        pass "$desc"
      else
        fail "$desc — expected the noop child, got: ${CHILD:0:80}"
      fi
      ;;
    real)
      if [ "$CHILD" = "real-child-pipeline" ]; then
        pass "$desc"
      else
        fail "$desc — expected the real child pipeline, got: ${CHILD:0:80}"
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

if [ "$FAILED" -ne 0 ]; then
  echo "test_generate_benchmarks: FAILED"
  exit 1
fi
echo "test_generate_benchmarks: all passed"
