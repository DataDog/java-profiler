#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc

# Hermetic tests for the GitLab gtest quarantine gate.
# Run with: .github/scripts/tests/test_gtest_quarantine_gate.sh
#
# The gate decides which C++ test failures turn CI red, so every verdict
# branch is exercised against fixture evidence dirs, not real runs: an
# un-quarantined failure, a quarantined failure on a matching and a
# non-matching cell, an expired entry, a binary that died without naming a
# test, a missing report, and a clean pass.

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)
GATE="$ROOT/.gitlab/scripts/gtest_quarantine_gate.py"
TEMP_DIR=$(mktemp -d)
TESTS=0

cleanup() {
  rm -rf "$TEMP_DIR"
}
trap cleanup EXIT

fail() {
  echo "FAIL: $*" >&2
  exit 1
}

pass() {
  TESTS=$((TESTS + 1))
  echo "  ok: $*"
}

# write_xml <path> <classname> <testname> [failure-message]
write_xml() {
  local path="$1" classname="$2" testname="$3" msg="${4:-}"
  {
    printf '<?xml version="1.0" encoding="UTF-8"?>\n'
    printf '<testsuites tests="1" failures="0">\n'
    printf '  <testsuite name="%s" tests="1">\n' "$classname"
    printf '    <testcase name="%s" classname="%s" status="run">\n' "$testname" "$classname"
    if [ -n "$msg" ]; then
      printf '      <failure message="%s" type="AssertionFailure"/>\n' "$msg"
    fi
    printf '    </testcase>\n  </testsuite>\n</testsuites>\n'
  } > "$path"
}

# setup_evidence <dir> — one failed binary + one passing binary
setup_evidence() {
  local dir="$1"
  mkdir -p "${dir}/rc"
}

# run_gate <evidence-dir> <cell> <list-file>  -> gate's exit code
run_gate() {
  python3 "$GATE" --evidence "$1" --cell "$2" --list "$3" > "$TEMP_DIR/out.txt" 2>&1
}

CELL="glibc-gtest-release-amd64"

# --- 1. an un-quarantined failure gates -------------------------------------
d="$TEMP_DIR/unquarantined"; setup_evidence "$d"
# The repo's real list now quarantines this very test, so the fixture uses a
# list with an unrelated entry: the failure must gate against it.
cat > "$d/list.txt" <<'EOF'
SomeOtherSuite.someOtherTest | PROF-12345 | 2026-11-11 | 2099-01-01 | - | fixture
EOF
write_xml "$d/TEST-foo_ut.xml" NativeThreadNameRaceTest threadDyingBetweenScansIsNeverNamed "expected equal"
echo 1 > "$d/rc/foo_ut"
run_gate "$d" "$CELL" "$d/list.txt" \
  && fail "un-quarantined failure did not gate" || true
grep -q "not quarantined" "$TEMP_DIR/out.txt" || fail "gate output does not name the un-quarantined failure"
pass "un-quarantined failure gates and is named in the output"

# --- 2. a quarantined failure on a matching cell is excused -----------------
d="$TEMP_DIR/excused"; setup_evidence "$d"
cat > "$d/list.txt" <<'EOF'
NativeThreadNameRaceTest.threadDyingBetweenScansIsNeverNamed | PROF-16577 | 2026-11-11 | 2099-01-01 | glibc-gtest-*-amd64 | fixture
EOF
write_xml "$d/TEST-foo_ut.xml" NativeThreadNameRaceTest threadDyingBetweenScansIsNeverNamed "expected equal"
echo 1 > "$d/rc/foo_ut"
run_gate "$d" "$CELL" "$d/list.txt" \
  || fail "quarantined failure gated anyway"
grep -q "excused by quarantine" "$TEMP_DIR/out.txt" || fail "gate output does not report the excuse"
pass "quarantined failure on a matching cell is excused"

# --- 3. the same failure on a non-matching cell gates -----------------------
run_gate "$d" "glibc-gtest-release-aarch64" "$d/list.txt" \
  && fail "failure on a cell the entry does not cover did not gate" || true
pass "entry scoped to amd64 does not excuse an aarch64 cell"

# --- 4. an expired entry excuses nothing ------------------------------------
d="$TEMP_DIR/expired"; setup_evidence "$d"
cat > "$d/list.txt" <<'EOF'
NativeThreadNameRaceTest.threadDyingBetweenScansIsNeverNamed | PROF-16577 | 2026-01-01 | 2026-02-01 | - | fixture, long expired
EOF
write_xml "$d/TEST-foo_ut.xml" NativeThreadNameRaceTest threadDyingBetweenScansIsNeverNamed "expected equal"
echo 1 > "$d/rc/foo_ut"
run_gate "$d" "$CELL" "$d/list.txt" \
  && fail "an expired entry excused a failure" || true
pass "expired entry is treated as absent"

# --- 5. a binary that died without naming a test gates ----------------------
d="$TEMP_DIR/crash"; setup_evidence "$d"
write_xml "$d/TEST-bar_ut.xml" SomeSuite somePassingTest
echo 137 > "$d/rc/bar_ut"
echo 0 > "$d/rc/passing_ut"
run_gate "$d" "$CELL" "$ROOT/ddprof-test/quarantine.txt" \
  && fail "a non-zero exit with no named failure did not gate" || true
grep -q "without naming a failing test" "$TEMP_DIR/out.txt" || fail "gate output does not report the unnamed failure"
pass "non-zero exit with no named failure gates (the list excuses tests, not crashes)"

# --- 6. a missing or unparseable report on a failed binary gates ------------
d="$TEMP_DIR/truncated"; setup_evidence "$d"
printf '<?xml version="1.0"?><testsuites><testsuite name="X">' > "$d/TEST-baz_ut.xml"
echo 1 > "$d/rc/baz_ut"
run_gate "$d" "$CELL" "$ROOT/ddprof-test/quarantine.txt" \
  && fail "an unparseable report did not gate" || true
grep -q "no readable report" "$TEMP_DIR/out.txt" || fail "gate output does not report the unreadable report"
pass "unparseable report gates instead of reading as a pass"

# --- 6b. a binary that dies before writing any report gates -----------------
d="$TEMP_DIR/noreport"; setup_evidence "$d"
echo 139 > "$d/rc/baz_ut"
run_gate "$d" "$CELL" "$ROOT/ddprof-test/quarantine.txt" \
  && fail "a binary with no report at all did not gate" || true
grep -q "without naming a failing test" "$TEMP_DIR/out.txt" || fail "gate output does not report the missing report"
pass "missing report gates instead of reading as a pass"

# --- 7. a clean run passes ---------------------------------------------------
d="$TEMP_DIR/clean"; setup_evidence "$d"
write_xml "$d/TEST-ok_ut.xml" SomeSuite someTest
echo 0 > "$d/rc/ok_ut"
run_gate "$d" "$CELL" "$ROOT/ddprof-test/quarantine.txt" \
  || fail "a clean run gated"
pass "clean run passes"

# --- 8. an empty or missing list refuses to gate on nothing -----------------
d="$TEMP_DIR/nolist"; setup_evidence "$d"
write_xml "$d/TEST-ok_ut.xml" SomeSuite someTest
echo 0 > "$d/rc/ok_ut"
run_gate "$d" "$CELL" "$TEMP_DIR/does-not-exist.txt" \
  && fail "a missing quarantine list passed silently" || true
pass "missing quarantine list fails the job rather than gating on nothing"

echo "test_gtest_quarantine_gate: $TESTS ok"
