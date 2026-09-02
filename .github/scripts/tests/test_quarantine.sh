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

write_list "$LIST" "$(entry a.B.c PROF-1 "$(day_offset 30)" '*arm64*')"

result=$(printf 'a.B.c\n' | python3 "$SCRIPTS/quarantine.py" --list "$LIST" match --cell "glibc-17-debug-arm64")
echo "$result" | grep -q '"quarantined": \["a.B.c"\]' \
  || fail "expected a.B.c quarantined on an arm64 cell, got: $result"
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
pass "a list that cannot be read fails the job instead of passing silently"
# A malformed line is skipped rather than fatal, so the flake is still caught;
# either way the job must be red.
echo "$output" | grep -q "Flaky test\|Could not classify" \
  || fail "expected the flake or the classifier failure to be reported, got: $output"
pass "the reason for the red is reported"

echo
echo "All $TESTS quarantine tests passed."
