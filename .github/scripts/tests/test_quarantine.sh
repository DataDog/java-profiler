#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc

# Hermetic tests for the flaky-test quarantine machinery.
# Run with: .github/scripts/tests/test_quarantine.sh
#
# The gating decision here is the one that can let a real defect through, and
# the retry path only executes when something has already failed -- which is to
# say, never on a green CI run. So it is exercised against fixtures instead.

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)
SCRIPTS="$ROOT/.github/scripts"
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

today() { python3 -c 'import datetime; print(datetime.date.today())'; }
day_offset() { python3 -c "import datetime,sys; print(datetime.date.today()+datetime.timedelta(days=int(sys.argv[1])))" "$1"; }

write_list() {
  # write_list <path> [entry line...]
  local path="$1"; shift
  printf '# test | ticket | added | review_by | cells | reason\n' > "$path"
  local line
  for line in "$@"; do
    printf '%s\n' "$line" >> "$path"
  done
}

entry() {
  # entry <test> <ticket> <review_by> [cells]
  printf '%s | %s | %s | %s | %s | flaky under test\n' \
    "$1" "$2" "$(today)" "$3" "${4:--}"
}

# Writes a JUnit XML report naming one failed test.
write_failure_xml() {
  # write_failure_xml <dir> <class> <method> <message>
  mkdir -p "$1"
  cat > "$1/TEST-$2.xml" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<testsuite name="$2" tests="1" failures="1">
  <testcase name="$3" classname="$2">
    <failure message="$4" type="AssertionError"/>
  </testcase>
</testsuite>
EOF
}

write_pass_xml() {
  mkdir -p "$1"
  cat > "$1/TEST-$2.xml" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<testsuite name="$2" tests="1" failures="0">
  <testcase name="$3" classname="$2"/>
</testsuite>
EOF
}

echo "== quarantine.py validate =="

LIST="$TEMP_DIR/list.txt"

write_list "$LIST"
python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null \
  || fail "empty list should be valid"
pass "an empty list is valid"

write_list "$LIST" "$(entry a.B.c PROF-1 "$(day_offset 30)")"
python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null \
  || fail "a complete, unexpired entry should be valid"
pass "a complete entry is valid"

write_list "$LIST" "a.B.c |  | $(today) | $(day_offset 30) | - | no ticket"
if python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null 2>&1; then
  fail "an entry with no ticket should be rejected"
fi
pass "an entry with no ticket is rejected"

write_list "$LIST" "$(entry a.B.c JIRA-1 "$(day_offset 30)")"
if python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null 2>&1; then
  fail "a ticket outside the PROF project should be rejected"
fi
pass "a non-PROF ticket is rejected"

write_list "$LIST" "$(entry a.B.c PROF-1 "$(day_offset -1)")"
if python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null 2>&1; then
  fail "an entry past review_by should be rejected"
fi
pass "an expired entry is rejected"

write_list "$LIST" "$(entry a.B.c PROF-1 "$(day_offset 30)")" "$(entry a.B.c PROF-2 "$(day_offset 30)")"
if python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null 2>&1; then
  fail "the same test listed twice should be rejected"
fi
pass "a duplicate entry is rejected"

# The list that ships in the repo must itself be valid, or CI is lying.
python3 "$SCRIPTS/quarantine.py" --list "$ROOT/ddprof-test/quarantine.txt" validate >/dev/null \
  || fail "the committed quarantine list is invalid"
pass "the committed quarantine list is valid"

echo "== quarantine.py match =="

write_list "$LIST" "$(entry a.B.c PROF-1 "$(day_offset 30)" '*aarch64*')"

result=$(printf 'a.B.c\n' | python3 "$SCRIPTS/quarantine.py" --list "$LIST" match --cell "glibc-17-debug-aarch64")
echo "$result" | grep -q '"quarantined": \["a.B.c"\]' \
  || fail "expected a.B.c quarantined on an aarch64 cell, got: $result"
pass "a cell glob matches the cells it names"

result=$(printf 'a.B.c\n' | python3 "$SCRIPTS/quarantine.py" --list "$LIST" match --cell "glibc-17-debug-amd64")
echo "$result" | grep -q '"gating": \["a.B.c"\]' \
  || fail "expected a.B.c gating on an amd64 cell, got: $result"
pass "a cell glob does not match other cells"

write_list "$LIST" "$(entry 'a.B.*' PROF-1 "$(day_offset 30)")"
result=$(printf 'a.B.c\na.B.d\na.C.e\n' | python3 "$SCRIPTS/quarantine.py" --list "$LIST" match --cell "any")
echo "$result" | grep -q '"gating": \["a.C.e"\]' \
  || fail "expected only a.C.e to gate under a class wildcard, got: $result"
pass "a class wildcard covers that class only"

echo "== gating: run_tests_with_retry.sh =="

# A suite that fails one test on the first attempt and passes on the second.
make_flaky_suite() {
  local dir="$1"
  mkdir -p "$dir"
  cat > "$dir/suite.sh" <<EOS
#!/usr/bin/env bash
n=\$(( \$(cat .n 2>/dev/null || echo 0) + 1 )); echo \$n > .n
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
if [ "\$n" -eq 1 ]; then
$(declare -f write_failure_xml)
  write_failure_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails" "got 2 samples, wanted 50"
  exit 1
fi
$(declare -f write_pass_xml)
write_pass_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails"
exit 0
EOS
  chmod +x "$dir/suite.sh"
}

# Not quarantined: passing on the retry must not rescue the job.
CASE="$TEMP_DIR/case-gating"
make_flaky_suite "$CASE"
write_list "$CASE/list.txt"
set +e
(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh >/dev/null 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "an un-quarantined flaky test must fail the job (got exit $rc)"
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['gating_count'] == 1, d
assert d['flaky'][0]['test'] == 'com.dd.WobblyTest.sometimesFails', d
" "$CASE/ci-outcome/glibc-17-debug-amd64.json" || fail "flaky test not classified as gating"
pass "an un-quarantined flake fails the job and is recorded as flaky"

# Same suite, now quarantined: the job goes green and the failure is recorded.
CASE="$TEMP_DIR/case-quarantined"
make_flaky_suite "$CASE"
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
set +e
(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh >/dev/null 2>&1)
rc=$?
set -e
[ "$rc" -eq 0 ] || fail "a quarantined test must not fail the job (got exit $rc)"
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['gating_count'] == 0, d
assert d['quarantined'][0]['ticket'] == 'PROF-1', d
" "$CASE/ci-outcome/glibc-17-debug-amd64.json" || fail "quarantined failure not recorded"
pass "a quarantined failure keeps the job green and is still recorded"

# A build error names no test, so quarantine has nothing to say about it.
CASE="$TEMP_DIR/case-build-error"
mkdir -p "$CASE"
printf '#!/usr/bin/env bash\necho "error: cannot find symbol"\nexit 1\n' > "$CASE/suite.sh"
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt" "$(entry 'com.dd.WobblyTest.*' PROF-1 "$(day_offset 30)")"
set +e
(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh >/dev/null 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "a build error must fail the job regardless of the quarantine list"
pass "a failure naming no test is never excused by quarantine"

# Regression: an unreadable list once made flake_report.py exit non-zero, and a
# `|| true` turned that into a silent green on a suite whose first attempt had
# failed. A classifier that did not run must never be mistaken for a clean run.
CASE="$TEMP_DIR/case-broken-list"
make_flaky_suite "$CASE"
printf 'this line has too few fields\n' > "$CASE/list.txt"
set +e
output=$(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "a malformed list must not yield a green job (got exit $rc)"
pass "a list with a malformed line still fails the job"
# A malformed line is skipped rather than fatal, so here the flake is what
# gates. The classifier-failure path is a separate case below.
echo "$output" | grep -q "Flaky test" \
  || fail "expected the flake to be reported, got: $output"
pass "the reason for the red is reported"

# The guard above only bites when flake_report.py itself exits non-zero, which
# a merely malformed line does not do. Point --list at a directory so the
# classifier genuinely fails: the suite passes on its retry, so without the
# REPORT_STATUS guard this job would be green.
CASE="$TEMP_DIR/case-unreadable-list"
make_flaky_suite "$CASE"
mkdir -p "$CASE/list.txt"
set +e
output=$(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "a classifier that could not run must not yield a green job (got exit $rc)"
echo "$output" | grep -q "Could not classify results for" \
  || fail "expected the classifier failure to be named, got: $output"
pass "a classifier that cannot run fails the job rather than passing unexamined"

# Quarantine excuses the tests it names, never the build around them. A suite
# whose only named failure is quarantined but which also failed a non-test
# Gradle task must stay red.
CASE="$TEMP_DIR/case-quarantined-plus-build-failure"
mkdir -p "$CASE"
cat > "$CASE/suite.sh" <<EOS
#!/usr/bin/env bash
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
$(declare -f write_failure_xml)
write_failure_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails" "got 2 samples, wanted 50"
echo "> Task :ddprof-lib:verifyNative FAILED"
echo "Execution failed for task ':ddprof-lib:verifyNative'."
exit 1
EOS
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt" "$(entry 'com.dd.WobblyTest.*' PROF-1 "$(day_offset 30)")"
set +e
output=$(cd "$CASE" && MAX_ATTEMPTS=1 "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "a non-test task failure must not be excused by quarantine (got exit $rc)"
echo "$output" | grep -q "verifyNative" \
  || fail "expected the offending task to be named, got: $output"
pass "quarantine excuses the tests it names, not a build failure alongside them"

# A test missing from the retry never re-ran, so it is not evidence of a flake.
CASE="$TEMP_DIR/case-absent-is-not-passed"
mkdir -p "$CASE/flake-evidence/attempt-1" "$CASE/flake-evidence/attempt-2"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.GoneTest" "vanishes" "boom"
write_pass_xml "$CASE/flake-evidence/attempt-2" "com.dd.OtherTest" "unrelated"
write_list "$CASE/list.txt"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-status fail --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert not d['flaky'], 'a test absent from the retry must not be called flaky: %r' % d['flaky']
assert len(d['persistent']) == 1, d
" "$CASE/out.json" || fail "absence from a later attempt was treated as a pass"
pass "a test missing from the retry is not mistaken for a flake"

# A stray attempt-* directory must not abort classification.
CASE="$TEMP_DIR/case-stray-attempt"
mkdir -p "$CASE/flake-evidence/attempt-tmp"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.WobblyTest" "sometimesFails" "boom"
write_list "$CASE/list.txt"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-status fail --out "$CASE/out.json" >/dev/null 2>&1 \
  || fail "a non-numeric attempt directory must be ignored, not fatal"
pass "a stray attempt directory is ignored"

echo "== validate rejects unmatchable cell globs =="

write_list "$LIST" "$(entry a.B.c PROF-1 "$(day_offset 30)" '*arm64*')"
if python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null 2>&1; then
  fail "a cell glob naming an architecture CI never builds should be rejected"
fi
pass "an unmatchable cell glob is rejected"

write_list "$LIST" "$(entry a.B.c PROF-1 "$(day_offset 30)" '*aarch64*')"
python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null \
  || fail "a real cell glob should be accepted"
pass "a real cell glob is accepted"

if python3 "$SCRIPTS/quarantine.py" --list "$TEMP_DIR/does-not-exist.txt" validate >/dev/null 2>&1; then
  fail "validating a missing list should fail rather than report success"
fi
pass "a missing list fails validation instead of reporting zero problems"

# Two entries for one test are legitimate when they cover different cells.
write_list "$LIST" \
  "$(entry a.B.c PROF-1 "$(day_offset 30)" '*aarch64*')" \
  "$(entry a.B.c PROF-2 "$(day_offset 30)" '*amd64*')"
python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null \
  || fail "the same test on disjoint cells should be allowed"
pass "one test may have separate entries for separate cells"

echo "== flake_summary.py renders =="

CASE="$TEMP_DIR/case-summary"
mkdir -p "$CASE/outcomes"
cat > "$CASE/outcomes/glibc-17-debug-aarch64.json" <<'EOS'
{"cell": "glibc-17-debug-aarch64", "attempts": 2, "status": "fail",
 "flaky": [{"test": "com.dd.WobblyTest.sometimesFails", "failed_attempts": [1],
            "passed_attempts": [2], "message": "got 2 | wanted 50",
            "flaky": true, "quarantined": false, "ticket": null}],
 "persistent": [], "quarantined": [], "gating_count": 1, "failure_count": 1}
EOS
summary=$(python3 "$SCRIPTS/flake_summary.py" --dir "$CASE/outcomes") \
  || fail "flake_summary.py must render without error"
echo "$summary" | grep -q "sometimesFails" \
  || fail "expected the flaky test in the summary, got: $summary"
echo "$summary" | grep -q "PROF-XXXXX" \
  || fail "expected a paste-ready quarantine proposal, got: $summary"
echo "$summary" | grep -q 'got 2 \\| wanted 50' \
  || fail "expected the pipe in the message to be escaped, got: $summary"
pass "the PR summary renders the flaky table and a proposal"

echo
echo "All $TESTS quarantine tests passed."
