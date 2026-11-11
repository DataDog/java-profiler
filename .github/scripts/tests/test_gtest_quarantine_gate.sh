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

# --- 6c. an <error> element counts as a failure, not a pass -----------------
# rc 0 is what makes this pin real: with a failing rc the rc-fallback loop
# would gate a mutant that ignores <error> elements, and the test could not
# tell error-parsing from the fallback.
d="$TEMP_DIR/errorel"; setup_evidence "$d"
printf '<?xml version="1.0"?>\n<testsuites><testsuite name="S"><testcase name="t" classname="S"><error message="segv"/></testcase></testsuite></testsuites>\n' > "$d/TEST-err_ut.xml"
echo 0 > "$d/rc/err_ut"
run_gate "$d" "$CELL" "$TEMP_DIR/unquarantined/list.txt" \
  && fail "an <error> element was not counted as a failure" || true
pass "<error> element counts as a failure"

# --- 6d. a passing binary with an unreadable report is not gated ------------
# Pins the rc-decides contract: the report only ever removes the excuse.
d="$TEMP_DIR/passunreadable"; setup_evidence "$d"
printf '<?xml version="1.0"?><testsuites><testsuite name="X">' > "$d/TEST-ok_ut.xml"
echo 0 > "$d/rc/ok_ut"
run_gate "$d" "$CELL" "$ROOT/ddprof-test/quarantine.txt" \
  || fail "a passing binary with an unreadable report gated"
grep -q "passed but wrote no readable report" "$TEMP_DIR/out.txt" \
  || fail "pass-through branch not reported"
pass "passing binary with unreadable report passes with a notice"

# --- 6e. an unreadable report on a failing binary is counted exactly once ---
# Pins the dedup guard: the xml loop and the rc loop must not both gate it.
d="$TEMP_DIR/dedup"; setup_evidence "$d"
printf '<?xml version="1.0"?><testsuites><testsuite name="X">' > "$d/TEST-baz_ut.xml"
echo 1 > "$d/rc/baz_ut"
run_gate "$d" "$CELL" "$ROOT/ddprof-test/quarantine.txt" \
  && fail "an unreadable report on a failing binary did not gate" || true
count=$(grep -c "wrote no readable report" "$TEMP_DIR/out.txt")
[ "$count" -eq 1 ] || fail "unreadable report gated $count times, expected 1"
[ -z "$(grep 'without naming a failing test' "$TEMP_DIR/out.txt")" ] \
  || fail "rc loop double-counted a binary the xml loop already gated"
pass "unreadable report counted exactly once (no rc-loop double gate)"

# --- 6f. a binary that dies before writing any report gates -----------------
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

# --- 9. runner smoke: rc propagation through run-gtests.sh ------------------
# Hermetic staging of the repo layout the runner expects; a stub binary stands
# in for gtest and honours --gtest_output=xml:<path>. This is the test that
# fails if the runner stops recording real exit codes (writing a constant 0
# would make a crashed binary's rc file read 0 and the gate would pass).
STAGE=$(mktemp -d)
mkdir -p "$STAGE/.gitlab/scripts" "$STAGE/.github/scripts" \
  "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut" "$STAGE/ddprof-test"
cp "$ROOT/.gitlab/scripts/run-gtests.sh" \
   "$ROOT/.gitlab/scripts/gtest_quarantine_gate.py" "$STAGE/.gitlab/scripts/"
cp "$ROOT/.github/scripts/quarantine.py" "$STAGE/.github/scripts/"
# The staged list covers both arches: the real entry scopes glibc-gtest-*-amd64
# (only amd64 cells have failed so far), but the smoke runs on whatever arch
# the dev machine has, so the runner's derived cell must still match.
cat > "$STAGE/ddprof-test/quarantine.txt" <<'EOF'
NativeThreadNameRaceTest.threadDyingBetweenScansIsNeverNamed | PROF-16577 | 2026-11-11 | 2099-01-01 | glibc-gtest-* | fixture
EOF
make_stub() { # make_stub <exit-code> <testname> [message]
  # $1/$2/$3 expand at creation time (the unquoted heredoc bakes the literals
  # into the stub); the stub itself only ever receives --gtest_output=xml:<path>.
  cat > "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut" <<STUB
#!/bin/sh
out=""
for a in "\$@"; do case "\$a" in *=xml:*) out="\${a#*=xml:}";; esac; done
printf '<?xml version="1.0"?>\n<testsuites><testsuite name="NativeThreadNameRaceTest"><testcase name="${2:-threadDyingBetweenScansIsNeverNamed}" classname="NativeThreadNameRaceTest"><failure message="${3:-boom}"/></testcase></testsuite></testsuites>\n' > "\$out"
exit ${1}
STUB
  chmod +x "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut"
}
# macOS/BSD find lacks -executable; CI runners are Linux/GNU, the shim only
# exists so this hermetic test can run on a dev Mac. It TRANSLATES the token
# to the BSD-equivalent -perm -u+x rather than dropping it, so both the
# runner's executable filter and its non-executable guard keep their
# semantics during the smoke.
mkdir "$STAGE/shim"
cat > "$STAGE/shim/find" <<'EOF'
#!/bin/sh
args=""
for a in "$@"; do
  if [ "$a" = "-executable" ]; then
    args="$args -perm -u+x"
  else
    args="$args $a"
  fi
done
exec /usr/bin/find $args
EOF
chmod +x "$STAGE/shim/find"

# A failure the staged list does not name gates on any cell (the stub reports
# a different test than the quarantined one).
make_stub 1 someOtherTest
( cd "$STAGE" && PATH="$STAGE/shim:$PATH" bash .gitlab/scripts/run-gtests.sh release ) > "$TEMP_DIR/runner.txt" 2>&1 \
  && fail "runner smoke: an un-quarantined failure passed the gate"
grep -q "not quarantined" "$TEMP_DIR/runner.txt" || fail "runner smoke: gate output missing"
pass "runner propagates a failing binary's exit code to the gate"

make_stub 1 threadDyingBetweenScansIsNeverNamed "expected equal"
( cd "$STAGE" && PATH="$STAGE/shim:$PATH" bash .gitlab/scripts/run-gtests.sh release ) > "$TEMP_DIR/runner2.txt" 2>&1 \
  || { cat "$TEMP_DIR/runner2.txt" >&2; fail "runner smoke: the quarantined failure gated anyway"; }
grep -q "excused by quarantine" "$TEMP_DIR/runner2.txt" || fail "runner smoke: no excuse line"
pass "runner + gate excuse the quarantined failure end to end"

# A stub that exits non-zero and writes NO report is the case that pins real
# rc recording: with rc files written as constant 0, the rc loop would never
# gate it and this smoke would pass on the mutant.
make_crash_stub() {
  cat > "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut" <<'STUB'
#!/bin/sh
exit 1
STUB
  chmod +x "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut"
}
make_crash_stub
( cd "$STAGE" && PATH="$STAGE/shim:$PATH" bash .gitlab/scripts/run-gtests.sh release ) > "$TEMP_DIR/runner3.txt" 2>&1 \
  && fail "runner smoke: a binary that crashed without a report passed"
grep -q "without naming a failing test" "$TEMP_DIR/runner3.txt" \
  || fail "runner smoke: crash-without-report not gated"
pass "runner records real exit codes: a crashed binary gates"

# A matching but non-executable binary must abort the run, not be silently
# skipped (which would read as a complete passing suite).
mv "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut" \
   "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut.bak"
cp "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut.bak" \
   "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut"
chmod -x "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut"
chmod +x "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut.bak"
mv "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut.bak" \
   "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut2"
chmod +x "$STAGE/ddprof-lib/build/bin/gtest/release_stub_ut/stub_ut2"
( cd "$STAGE" && PATH="$STAGE/shim:$PATH" bash .gitlab/scripts/run-gtests.sh release ) > "$TEMP_DIR/runner4.txt" 2>&1 \
  && fail "runner smoke: a non-executable matching binary was silently skipped"
grep -q "not executable" "$TEMP_DIR/runner4.txt" \
  || fail "runner smoke: non-executable guard did not report"
pass "runner refuses to run a subset when a matching binary is not executable"
rm -rf "$STAGE"
