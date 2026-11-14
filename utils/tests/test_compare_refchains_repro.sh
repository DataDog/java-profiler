#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

# Hermetic tests for utils/compare-refchains-repro.sh's handling of failed
# variants. The compare script is copied next to a stub run-refchains-repro.sh
# whose exit status / [metrics] output is controlled per variant.
# Run with: bash utils/tests/test_compare_refchains_repro.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
COMPARE="$SCRIPT_DIR/../compare-refchains-repro.sh"
TESTS=0
FAILED=0

TEMP_DIR=$(mktemp -d)
COMPARE_WORKDIRS=()
cleanup() {
  rm -rf "$TEMP_DIR"
  local d
  for d in ${COMPARE_WORKDIRS[@]+"${COMPARE_WORKDIRS[@]}"}; do
    rm -rf "$d"
  done
}
trap cleanup EXIT

pass() {
  TESTS=$((TESTS + 1))
}

fail() {
  TESTS=$((TESTS + 1))
  FAILED=$((FAILED + 1))
  echo "FAIL: $*" >&2
}

expect_eq() {
  if [ "$2" = "$3" ]; then pass; else fail "$1: expected '$3', got '$2'"; fi
}

expect_contains() {
  case "$2" in
    *"$3"*) pass ;;
    *) fail "$1: expected to contain '$3', got '$2'" ;;
  esac
}

expect_not_contains() {
  case "$2" in
    *"$3"*) fail "$1: should not contain '$3'" ;;
    *) pass ;;
  esac
}

HERE_DIR="$TEMP_DIR/here"
mkdir -p "$HERE_DIR"
cp "$COMPARE" "$HERE_DIR/compare-refchains-repro.sh"
chmod +x "$HERE_DIR/compare-refchains-repro.sh"

cat > "$HERE_DIR/run-refchains-repro.sh" <<'EOF'
#!/usr/bin/env bash
set -euo pipefail
if [ "${REFCHAINS_ENABLED:-}" = "${STUB_FAIL_ENABLED:-}" ]; then
  echo "stub: simulated JVM startup failure"
  exit 3
fi
if [ "${REFCHAINS_ENABLED:-}" = "${STUB_NOMETRICS_ENABLED:-}" ]; then
  echo "stub: finished without metrics"
  exit 0
fi
echo "[metrics] wallSeconds=1.0 entriesPerSec=100.0 avgRoundMs=1.0 maxRoundMs=2.0 heapGrowthMb=3"
exit 0
EOF
chmod +x "$HERE_DIR/run-refchains-repro.sh"

# run_compare <bash binary> [env=val ...] - sets RC, OUT, ERR, WD, REPORT_TEXT
run_compare() {
  local bash_bin=$1
  shift
  RC=0
  # STUB_* default to a value REFCHAINS_ENABLED never takes.
  env STUB_FAIL_ENABLED=never STUB_NOMETRICS_ENABLED=never "$@" \
    "$bash_bin" "$HERE_DIR/compare-refchains-repro.sh" 1 \
    > "$TEMP_DIR/compare.out" 2> "$TEMP_DIR/compare.err" || RC=$?
  OUT=$(cat "$TEMP_DIR/compare.out")
  ERR=$(cat "$TEMP_DIR/compare.err")
  WD=$(sed -n 's/^Working directory: //p' "$TEMP_DIR/compare.out")
  REPORT_TEXT=""
  if [ -n "$WD" ]; then
    COMPARE_WORKDIRS+=("$WD")
    if [ -f "$WD/report.md" ]; then
      REPORT_TEXT=$(cat "$WD/report.md")
    fi
  fi
}

run_suite() {
  local bash_bin=$1 tag=$2

  # --- T3.1 both succeed -------------------------------------------------------
  run_compare "$bash_bin"
  expect_eq "$tag T3.1 rc" "$RC" "0"
  expect_contains "$tag T3.1 table" "$REPORT_TEXT" "| metric |"
  expect_contains "$tag T3.1 answers" "$REPORT_TEXT" "## Answers"
  expect_not_contains "$tag T3.1 not invalid" "$REPORT_TEXT" "INVALID"

  # --- T3.2 "on" exits non-zero -------------------------------------------------
  run_compare "$bash_bin" STUB_FAIL_ENABLED=true
  expect_eq "$tag T3.2 rc" "$RC" "1"
  expect_contains "$tag T3.2 variant fail" "$ERR" "FAIL: variant 'on' exited with status 3"
  expect_contains "$tag T3.2 aborted" "$ERR" "FAIL: comparison aborted"
  expect_contains "$tag T3.2 report invalid" "$REPORT_TEXT" "INVALID"
  expect_contains "$tag T3.2 report names on" "$REPORT_TEXT" "on(exit=3)"
  expect_not_contains "$tag T3.2 no answers" "$REPORT_TEXT" "## Answers"
  expect_not_contains "$tag T3.2 no results" "$OUT" "===================== results"
  if [ -n "$WD" ] && [ -f "$WD/off.stdout.log" ]; then pass; else fail "$tag T3.2: off variant did not run"; fi

  # --- T3.3 "off" prints no metrics -------------------------------------------
  run_compare "$bash_bin" STUB_NOMETRICS_ENABLED=false
  expect_eq "$tag T3.3 rc" "$RC" "1"
  expect_contains "$tag T3.3 report names off" "$REPORT_TEXT" "off(no-metrics)"
  expect_not_contains "$tag T3.3 no answers" "$REPORT_TEXT" "## Answers"

  # --- T3.4 both fail ------------------------------------------------------------
  run_compare "$bash_bin" STUB_FAIL_ENABLED=true STUB_NOMETRICS_ENABLED=false
  expect_eq "$tag T3.4 rc" "$RC" "1"
  expect_contains "$tag T3.4 report names on" "$REPORT_TEXT" "on(exit=3)"
  expect_contains "$tag T3.4 report names off" "$REPORT_TEXT" "off(no-metrics)"
}

run_suite bash "bash"

# --- T3.5 bash 3.2 --------------------------------------------------------------
if [ -x /bin/bash ] && case "$(/bin/bash --version 2>/dev/null)" in *"version 3."*) true ;; *) false ;; esac; then
  run_suite /bin/bash "bash3.2"
else
  echo "SKIP: T3.5 (bash 3.2 unavailable)"
fi

echo "$TESTS checks, $FAILED failed"
if [ "$FAILED" -gt 0 ]; then
  exit 1
fi
