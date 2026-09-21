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

echo "== quarantine.find_entry (the rule the gating decision actually uses) =="

write_list "$LIST" "$(entry a.B.c PROF-1 "$(day_offset 30)" '*aarch64*')"

result=$(python3 -c "
import sys; sys.path.insert(0, '$SCRIPTS')
import quarantine
entries = quarantine.load('$LIST')
print('hit' if quarantine.find_entry(entries, 'a.B.c', 'glibc-17-debug-aarch64') else 'miss')
")
[ "$result" = "hit" ] || fail "expected a.B.c quarantined on an aarch64 cell, got: $result"
pass "a cell glob matches the cells it names"

result=$(python3 -c "
import sys; sys.path.insert(0, '$SCRIPTS')
import quarantine
entries = quarantine.load('$LIST')
print('hit' if quarantine.find_entry(entries, 'a.B.c', 'glibc-17-debug-amd64') else 'miss')
")
[ "$result" = "miss" ] || fail "expected a.B.c gating (not quarantined) on an amd64 cell, got: $result"
pass "a cell glob does not match other cells"

write_list "$LIST" "$(entry 'a.B.*' PROF-1 "$(day_offset 30)")"
result=$(python3 -c "
import sys; sys.path.insert(0, '$SCRIPTS')
import quarantine
entries = quarantine.load('$LIST')
tests = ['a.B.c', 'a.B.d', 'a.C.e']
gating = [t for t in tests if quarantine.find_entry(entries, t, 'any') is None]
print(','.join(gating))
")
[ "$result" = "a.C.e" ] || fail "expected only a.C.e to gate under a class wildcard, got: $result"
pass "a class wildcard covers that class only"

# validate-quarantine only runs from ci.yml, but find_entry() is the function
# every workflow's flake_report.py invocation actually calls -- nightly.yml
# and release-validated.yml reuse the retry/quarantine machinery without ever
# running validate-quarantine, so an expired entry must stop matching here
# too, not just be caught by the separate CLI check above.
write_list "$LIST" "$(entry a.B.c PROF-1 "$(day_offset -1)")"
result=$(python3 -c "
import sys; sys.path.insert(0, '$SCRIPTS')
import quarantine
entries = quarantine.load('$LIST')
print('hit' if quarantine.find_entry(entries, 'a.B.c', 'any') else 'miss')
")
[ "$result" = "miss" ] || fail "expected an expired entry to gate rather than match, got: $result"
pass "find_entry() treats an expired entry as absent, not as a hit"

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

# A clean run on the first attempt must exit 0 and report nothing gating.
# Every other case in this section starts from a failure; without this one, a
# regression that made a clean run report a gating failure would leave every
# other assertion here passing.
CASE="$TEMP_DIR/case-green"
mkdir -p "$CASE"
cat > "$CASE/suite.sh" <<EOS
#!/usr/bin/env bash
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
$(declare -f write_pass_xml)
write_pass_xml "\$OUT" "com.dd.SteadyTest" "alwaysPasses"
exit 0
EOS
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt"
set +e
(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh >/dev/null 2>&1)
rc=$?
set -e
[ "$rc" -eq 0 ] || fail "a suite that passes on the first attempt must exit 0 (got exit $rc)"
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['gating_count'] == 0 and d['failure_count'] == 0, d
assert not d['flaky'] and not d['persistent'] and not d['unclassified'], d
" "$CASE/ci-outcome/glibc-17-debug-amd64.json" || fail "a clean run was not reported as clean"
pass "a suite that passes on the first attempt is green and reports no failures"

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

# Regression: a failure aggregated from an EARLIER attempt must never rescue a
# FINAL attempt that failed for a reason naming no test at all (here: nothing
# that prints "Execution failed for task", so the non_test_task_failures grep
# alone would miss it). Attempt 1 fails a named, quarantined test; attempt 2
# aborts before writing any JUnit XML, the way a docker or JVM-init failure
# would. The job must stay red even though every named failure is quarantined.
CASE="$TEMP_DIR/case-final-attempt-no-tests"
mkdir -p "$CASE"
cat > "$CASE/suite.sh" <<EOS
#!/usr/bin/env bash
n=\$(( \$(cat .n 2>/dev/null || echo 0) + 1 )); echo \$n > .n
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
if [ "\$n" -eq 1 ]; then
$(declare -f write_failure_xml)
  write_failure_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails" "got 2 samples, wanted 50"
  exit 1
fi
rm -rf "\$OUT"
echo "docker: Error response from daemon: OCI runtime create failed"
exit 1
EOS
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
set +e
output=$(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "a final attempt that named no test must not be excused by an earlier attempt's quarantined failure (got exit $rc)"
pass "a final attempt naming no test is never excused by an earlier attempt's quarantine hit"

# Regression: a final attempt that crashes part-way through still writes JUnit
# XML for the tests it got to, and those all passed -- so it names no failure
# of its own and every aggregated failure is quarantined. Gradle blames the
# abort on the test task itself, so the non-test-task check cannot see it
# either. Only the attempt's own non-zero exit distinguishes this from the
# ordinary flaky-then-passed case, and it must stay red.
CASE="$TEMP_DIR/case-final-attempt-crashed-mid-run"
mkdir -p "$CASE"
cat > "$CASE/suite.sh" <<EOS
#!/usr/bin/env bash
n=\$(( \$(cat .n 2>/dev/null || echo 0) + 1 )); echo \$n > .n
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
$(declare -f write_failure_xml)
$(declare -f write_pass_xml)
if [ "\$n" -eq 1 ]; then
  write_failure_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails" "got 2 samples, wanted 50"
  exit 1
fi
write_pass_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails"
echo "# A fatal error has been detected by the Java Runtime Environment: SIGSEGV"
echo "Execution failed for task ':ddprof-test:test'."
echo "> Process 'Gradle Test Executor 3' finished with non-zero exit value 134"
exit 134
EOS
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
set +e
output=$(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "a final attempt that crashed after recording only passes must not be excused by quarantine (got exit $rc)"
pass "a final attempt that crashed mid-run is not read as a quarantined pass"

# The counterpart: the same shape without the crash is the ordinary
# flaky-then-passed case a quarantine entry exists to excuse, and must be
# green. Without this the guard above could be satisfied by gating everything.
CASE="$TEMP_DIR/case-quarantined-flake-recovers"
mkdir -p "$CASE"
cat > "$CASE/suite.sh" <<EOS
#!/usr/bin/env bash
n=\$(( \$(cat .n 2>/dev/null || echo 0) + 1 )); echo \$n > .n
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
$(declare -f write_failure_xml)
$(declare -f write_pass_xml)
if [ "\$n" -eq 1 ]; then
  write_failure_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails" "got 2 samples, wanted 50"
  exit 1
fi
write_pass_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails"
exit 0
EOS
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
set +e
output=$(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -eq 0 ] || fail "a quarantined flake that passed on retry must stay green (got exit $rc): $output"
pass "a quarantined flake that recovers on a clean retry is still excused"

# A final attempt can name only quarantined failures and still exit non-zero
# -- a JVM abort partway through, after writing XML for the one test it
# reached. The tests it never got to are missing from the XML, not passing;
# a quarantined name or two must not paper over that crash.
CASE="$TEMP_DIR/case-final-attempt-quarantined-failure-plus-crash"
mkdir -p "$CASE"
cat > "$CASE/suite.sh" <<EOS
#!/usr/bin/env bash
n=\$(( \$(cat .n 2>/dev/null || echo 0) + 1 )); echo \$n > .n
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
$(declare -f write_failure_xml)
write_failure_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails" "got 2 samples, wanted 50"
if [ "\$n" -gt 1 ]; then
  echo "# A fatal error has been detected by the Java Runtime Environment: SIGSEGV"
  echo "Execution failed for task ':ddprof-test:test'."
  echo "> Process 'Gradle Test Executor 3' finished with non-zero exit value 134"
  exit 134
fi
exit 1
EOS
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
set +e
output=$(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "a final attempt that crashed after naming only a quarantined failure must not be excused (got exit $rc)"
pass "a final attempt naming a quarantined failure is still gated if it also crashed"

# ...but only when the evidence it rests on is complete. Docker writes the
# JUnit XML as root; if this user cannot take ownership of it, the snapshot is
# partial, and a partial snapshot is indistinguishable from an attempt whose
# missing tests all passed. make_results_readable() must report that rather
# than fail open, and the run must go red.
CASE="$TEMP_DIR/case-unreadable-results"
mkdir -p "$CASE/stub-bin"
cat > "$CASE/stub-bin/find" <<'EOS'
#!/usr/bin/env bash
for a in "$@"; do
  if [ "$a" = "-user" ]; then echo "/root-owned/TEST-Foo.xml"; exit 0; fi
done
exec /usr/bin/find "$@"
EOS
cat > "$CASE/stub-bin/sudo" <<'EOS'
#!/usr/bin/env bash
exit 1
EOS
chmod +x "$CASE/stub-bin/find" "$CASE/stub-bin/sudo"
cat > "$CASE/suite.sh" <<EOS
#!/usr/bin/env bash
n=\$(( \$(cat .n 2>/dev/null || echo 0) + 1 )); echo \$n > .n
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
$(declare -f write_failure_xml)
$(declare -f write_pass_xml)
if [ "\$n" -eq 1 ]; then
  write_failure_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails" "got 2 samples, wanted 50"
  exit 1
fi
write_pass_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails"
exit 0
EOS
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
set +e
output=$(cd "$CASE" && PATH="$CASE/stub-bin:$PATH" "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "results that could not be made readable must not be excused by quarantine (got exit $rc)"
echo "$output" | grep -q "suspect" \
  || fail "expected the suspect evidence to be named as the reason, got: $output"
pass "evidence that could not be made readable is never excused by the quarantine list"

# A `cp -r` that fails partway through RESULTS_DIR must poison the evidence
# the same way an unreadable results directory does above -- even when the
# one failure it *did* manage to copy is quarantined, the files it could not
# copy are missing from this attempt's snapshot, not passing. Stubbed like
# the find/sudo cases above rather than chmod'd, since a root-run CI job
# would not actually be denied read access by chmod.
CASE="$TEMP_DIR/case-partial-snapshot-copy"
mkdir -p "$CASE/stub-bin"
cat > "$CASE/stub-bin/cp" <<'EOS'
#!/usr/bin/env bash
exit 1
EOS
chmod +x "$CASE/stub-bin/cp"
cat > "$CASE/suite.sh" <<EOS
#!/usr/bin/env bash
n=\$(( \$(cat .n 2>/dev/null || echo 0) + 1 )); echo \$n > .n
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
$(declare -f write_failure_xml)
write_failure_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails" "got 2 samples, wanted 50"
exit 1
EOS
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
set +e
output=$(cd "$CASE" && PATH="$CASE/stub-bin:$PATH" "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "a failed snapshot copy must not be excused even though the named failure is quarantined (got exit $rc)"
echo "$output" | grep -q "Could not snapshot" \
  || fail "expected the lost evidence to be reported, got: $output"
pass "a failed snapshot copy leaves nothing to excuse, so the command's own failure stands"

# Suspect evidence is a reason to distrust a quarantine excuse, not a failure
# of its own. A suite that passed has nothing to excuse, so an unreadable
# results tree must not turn its exit 0 into a red job.
CASE="$TEMP_DIR/case-suspect-evidence-all-passed"
mkdir -p "$CASE/stub-bin"
cat > "$CASE/stub-bin/find" <<'EOS'
#!/usr/bin/env bash
for a in "$@"; do
  if [ "$a" = "-user" ]; then echo "/root-owned/TEST-Foo.xml"; exit 0; fi
done
exec /usr/bin/find "$@"
EOS
cat > "$CASE/stub-bin/sudo" <<'EOS'
#!/usr/bin/env bash
exit 1
EOS
chmod +x "$CASE/stub-bin/find" "$CASE/stub-bin/sudo"
cat > "$CASE/suite.sh" <<EOS
#!/usr/bin/env bash
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
$(declare -f write_pass_xml)
write_pass_xml "\$OUT" "com.dd.SteadyTest" "alwaysPasses"
exit 0
EOS
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt"
set +e
output=$(cd "$CASE" && PATH="$CASE/stub-bin:$PATH" "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -eq 0 ] || fail "suspect evidence must not fail a run in which every test passed (got exit $rc): $output"
pass "suspect evidence does not redden a run with nothing to excuse"

# A test missing from the retry never re-ran, so it is not evidence of a flake.
CASE="$TEMP_DIR/case-absent-is-not-passed"
mkdir -p "$CASE/flake-evidence/attempt-1" "$CASE/flake-evidence/attempt-2"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.GoneTest" "vanishes" "boom"
write_pass_xml "$CASE/flake-evidence/attempt-2" "com.dd.OtherTest" "unrelated"
write_list "$CASE/list.txt"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 2 --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert not d['flaky'], 'a test absent from the retry must not be called flaky: %r' % d['flaky']
assert len(d['persistent']) == 1, d
" "$CASE/out.json" || fail "absence from a later attempt was treated as a pass"
pass "a test missing from the retry is not mistaken for a flake"

# A <testcase> missing name or classname cannot be attributed to any real
# test; it must be skipped rather than counted as a failure or crashing the
# classifier, while a properly-identified failure alongside it still counts.
CASE="$TEMP_DIR/case-unnamed-testcase"
mkdir -p "$CASE/flake-evidence/attempt-1"
cat > "$CASE/flake-evidence/attempt-1/TEST-com.dd.Weird.xml" <<'EOS'
<?xml version="1.0" encoding="UTF-8"?>
<testsuite name="com.dd.Weird" tests="2" failures="2">
  <testcase classname="com.dd.Weird">
    <failure message="no name attribute" type="AssertionError"/>
  </testcase>
  <testcase name="realFailure" classname="com.dd.Weird">
    <failure message="boom" type="AssertionError"/>
  </testcase>
</testsuite>
EOS
write_list "$CASE/list.txt"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 1 --out "$CASE/out.json" >/dev/null 2>&1 \
  || fail "a testcase with no name attribute must not crash the classifier"
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['failure_count'] == 1, d
assert d['unclassified'] and d['unclassified'][0]['test'] == 'com.dd.Weird.realFailure', d
" "$CASE/out.json" || fail "the unnamed testcase was not ignored, or the real failure was missed"
pass "a testcase with no name attribute is ignored, not mistaken for a failure"

# A stray attempt-* directory must not abort classification, and attempt-1
# must still be read as the (only, and so final) real attempt.
CASE="$TEMP_DIR/case-stray-attempt"
mkdir -p "$CASE/flake-evidence/attempt-tmp"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.WobblyTest" "sometimesFails" "boom"
write_list "$CASE/list.txt"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 1 --out "$CASE/out.json" >/dev/null 2>&1 \
  || fail "a non-numeric attempt directory must be ignored, not fatal"
pass "a stray attempt directory is ignored"
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['attempts'] == 1, d
assert d['unclassified'] and d['unclassified'][0]['test'] == 'com.dd.WobblyTest.sometimesFails', d
" "$CASE/out.json" || fail "attempt-1 was not read back despite the stray attempt-tmp"
pass "attempt-1 is still read as evidence while the stray directory is skipped"

# The ordinary quarantine case, and the one the exit-code guard must not eat:
# a quarantined test fails on the final attempt, so Gradle exits non-zero
# *because of that very test*. No test passed --final-attempt-exit-code before,
# so it defaulted to None and this shape went untested while the guard gated
# every one of them.
CASE="$TEMP_DIR/case-quarantined-failure-exit-nonzero"
mkdir -p "$CASE/flake-evidence/attempt-1"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.WobblyTest" "sometimesFails" "boom"
cat > "$CASE/attempt.log" <<'EOS'
> Task :ddprof-test:testDebug FAILED
Execution failed for task ':ddprof-test:testDebug'.
> There were failing tests.
EOS
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 1 --attempt-log "$CASE/attempt.log" \
  --final-attempt-exit-code 1 --test-task-pattern test \
  --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['gates'] is False, 'a quarantined test failing on the final attempt must not gate: %r' % d['gate_reason']
assert len(d['quarantined']) == 1, d
" "$CASE/out.json" || fail "the non-zero exit caused by the quarantined test's own failure was read as a crash"
pass "a quarantined failure still excuses the non-zero exit it caused"

# The shape the guard exists for: the same all-quarantined failure list, but
# Gradle reports the test JVM died, so tests it never reached are absent from
# the XML rather than passing.
CASE="$TEMP_DIR/case-quarantined-but-cut-short"
mkdir -p "$CASE/flake-evidence/attempt-1"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.WobblyTest" "sometimesFails" "boom"
cat > "$CASE/attempt.log" <<'EOS'
> Task :ddprof-test:testDebug FAILED
Process 'Gradle Test Executor 1' finished with non-zero exit value 134
EOS
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 1 --attempt-log "$CASE/attempt.log" \
  --final-attempt-exit-code 1 --test-task-pattern test \
  --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['gates'] is True, 'a cut-short final attempt must gate even with every named failure quarantined: %r' % d['gate_reason']
assert d['final_attempt_cut_short'], d
" "$CASE/out.json" || fail "a dead test JVM was excused by the quarantine list"
pass "a cut-short final attempt gates despite its failures being quarantined"

# musl runs ProfilerTestRunner through a plain Exec task, not Gradle's native
# Test task: Gradle prints the exact same "finished with non-zero exit value"
# line whenever that process exits non-zero for *any* reason, including an
# ordinary single-test failure -- not just a genuine crash. That line must not
# gate a quarantined musl failure the way it correctly does for glibc above.
CASE="$TEMP_DIR/case-quarantined-musl-exec-task-nonzero-exit"
mkdir -p "$CASE/flake-evidence/attempt-1"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.WobblyTest" "sometimesFails" "boom"
cat > "$CASE/attempt.log" <<'EOS'
> Task :ddprof-test:testDebug FAILED
Process 'command '/usr/bin/java'' finished with non-zero exit value 1
EOS
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "musl-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 1 --attempt-log "$CASE/attempt.log" \
  --final-attempt-exit-code 1 --test-task-pattern test \
  --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['gates'] is False, 'a musl Exec task exit-value line must not read as cut-short: %r' % d['gate_reason']
assert not d['final_attempt_cut_short'], d
" "$CASE/out.json" || fail "an ordinary musl test failure's Exec-task exit line was read as a crash"
pass "musl's Exec-task exit-value line does not gate a quarantined failure"

# The one musl signal that must still gate: a genuine crash banner, present
# regardless of libc.
CASE="$TEMP_DIR/case-quarantined-musl-real-crash"
mkdir -p "$CASE/flake-evidence/attempt-1"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.WobblyTest" "sometimesFails" "boom"
cat > "$CASE/attempt.log" <<'EOS'
> Task :ddprof-test:testDebug FAILED
# A fatal error has been detected by the Java Runtime Environment:
# hs_err_pid12345.log
EOS
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "musl-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 1 --attempt-log "$CASE/attempt.log" \
  --final-attempt-exit-code 1 --test-task-pattern test \
  --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['gates'] is True, 'a real crash banner must still gate on musl: %r' % d['gate_reason']
assert d['final_attempt_cut_short'], d
" "$CASE/out.json" || fail "a genuine musl crash was excused by the quarantine list"
pass "a genuine crash banner still gates a quarantined musl failure"

# Same intent, without the log saying so: the final attempt reached fewer tests
# than an earlier one managed, so it stopped early.
CASE="$TEMP_DIR/case-quarantined-but-short-run"
mkdir -p "$CASE/flake-evidence/attempt-1" "$CASE/flake-evidence/attempt-2"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.WobblyTest" "sometimesFails" "boom"
write_pass_xml "$CASE/flake-evidence/attempt-1" "com.dd.OtherTest" "stable"
write_failure_xml "$CASE/flake-evidence/attempt-2" "com.dd.WobblyTest" "sometimesFails" "boom"
cat > "$CASE/attempt.log" <<'EOS'
> Task :ddprof-test:testDebug FAILED
Execution failed for task ':ddprof-test:testDebug'.
EOS
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 2 --attempt-log "$CASE/attempt.log" \
  --final-attempt-exit-code 1 --test-task-pattern test \
  --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['gates'] is True, 'a final attempt that reached fewer tests must gate: %r' % d['gate_reason']
assert d['final_attempt_observed_shortfall'], d
" "$CASE/out.json" || fail "a final attempt that stopped early was excused by the quarantine list"
pass "a final attempt reaching fewer tests than an earlier one gates"

# Gradle writes a JUnit 5 @Test method as name="method()", so the id built from
# the report is Class.method() while an entry is written Class.method. Without
# normalisation covers() (exact equality) matches nothing and the quarantine
# silently excuses nothing, with validate still reporting the list as valid.
CASE="$TEMP_DIR/case-method-parens"
mkdir -p "$CASE/flake-evidence/attempt-1"
cat > "$CASE/flake-evidence/attempt-1/TEST-com.dd.WobblyTest.xml" <<'EOS'
<?xml version="1.0" encoding="UTF-8"?>
<testsuite name="com.dd.WobblyTest" tests="1" failures="1">
  <testcase name="sometimesFails()" classname="com.dd.WobblyTest" time="0.1">
    <failure message="boom" type="AssertionError"/>
  </testcase>
</testsuite>
EOS
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 1 --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert len(d['quarantined']) == 1, 'an entry written as documented must match the id JUnit produces: %r' % d
assert d['quarantined'][0]['test'] == 'com.dd.WobblyTest.sometimesFails()', d
assert d['gates'] is False, d['gate_reason']
" "$CASE/out.json" || fail "the documented <class>.<method> form did not match Gradle's method() id"
pass "an entry written without parentheses matches JUnit's method() id"

# The paste-ready proposal must be precise for such a method, not widened to
# the whole class: the parens are the only unsafe characters and covers()
# normalises them away.
CASE="$TEMP_DIR/case-proposal-parens"
python3 -c "
import sys
sys.path.insert(0, '$SCRIPTS')
import flake_summary
got = flake_summary.sanitize_quarantine_test_pattern('com.dd.WobblyTest.sometimesFails()')
assert got == 'com.dd.WobblyTest.sometimesFails', got
idx = flake_summary.sanitize_quarantine_test_pattern('com.dd.WobblyTest.[1]')
assert idx == 'com.dd.WobblyTest.*', idx
" || fail "the proposal for a method() id was not the documented form, or an indexed invocation was not widened class-wide"
pass "a method() id proposes the documented form; an indexed invocation proposes the class"

# The other-task guard, asserted on the verdict rather than on stdout: the
# previous check grepped for a task name the fixture echoes itself, which
# filter_gradle_log.py passes through verbatim, so deleting the guard left the
# test green. Exit 0 from the fixture isolates this from the exit-code branch.
CASE="$TEMP_DIR/case-other-task-guard"
mkdir -p "$CASE/flake-evidence/attempt-1"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.WobblyTest" "sometimesFails" "boom"
cat > "$CASE/attempt.log" <<'EOS'
> Task :ddprof-lib:verifyNative FAILED
Execution failed for task ':ddprof-lib:verifyNative'.
EOS
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 1 --attempt-log "$CASE/attempt.log" \
  --final-attempt-exit-code 0 --test-task-pattern ":ddprof-test:test" \
  --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['gates'] is True, 'a non-test task failure must gate even with every test quarantined: %r' % d['gate_reason']
assert 'the build also failed in' in (d['gate_reason'] or ''), d['gate_reason']
assert d['other_task_failures'] == [':ddprof-lib:verifyNative'], d['other_task_failures']
" "$CASE/out.json" || fail "the non-test-task guard did not gate, or did not name the task"
pass "a build failure outside the test task is never excused by the list"

# b-12, hermetically: suspect evidence with no failure recorded has nothing to
# excuse, so the classifier must hold no opinion and let the command's own exit
# code stand.
CASE="$TEMP_DIR/case-suspect-no-failures"
mkdir -p "$CASE/flake-evidence/attempt-1"
write_pass_xml "$CASE/flake-evidence/attempt-1" "com.dd.SteadyTest" "alwaysPasses"
write_list "$CASE/list.txt"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 1 --evidence-suspect --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert d['gates'] is None, 'suspect evidence with no failure must not gate: %r' % d['gate_reason']
" "$CASE/out.json" || fail "suspect evidence gated a run in which nothing failed"
pass "suspect evidence holds no opinion when there is no failure to excuse"

# s-22: a single attempt cannot tell flaky from broken, so the failure must not
# also appear as persistent -- that label asserts a measurement never made.
CASE="$TEMP_DIR/case-single-attempt-not-persistent"
mkdir -p "$CASE/flake-evidence/attempt-1"
write_failure_xml "$CASE/flake-evidence/attempt-1" "com.dd.SlowTest" "onlyRunOnce" "boom"
write_list "$CASE/list.txt"
python3 "$SCRIPTS/flake_report.py" --list "$CASE/list.txt" report \
  --cell "glibc-17-debug-amd64-slow" --evidence-dir "$CASE/flake-evidence" \
  --final-attempt 1 --out "$CASE/out.json" >/dev/null 2>&1
python3 -c "
import json,sys
d = json.load(open(sys.argv[1]))
assert not d['persistent'], 'a single-attempt failure must not be labelled persistent: %r' % d['persistent']
assert len(d['unclassified']) == 1, d
" "$CASE/out.json" || fail "a single-attempt failure was labelled broken rather than unclassified"
pass "a single-attempt failure is unclassified, not persistent"

# s-19, through the renderer: the WIDENED marker has to reach the rendered
# proposal, not merely exist as a helper.
python3 -c "
import sys
sys.path.insert(0, '$SCRIPTS')
from flake_summary import render_proposals
out = '\n'.join(render_proposals({'com.dd.WobblyTest.[1]': {'message': 'boom', 'cells': ['glibc-17-debug-amd64']}}))
assert 'WIDENED' in out, 'the rendered proposal does not mark the widening:\n' + out
assert 'com.dd.WobblyTest.*' in out, out
" || fail "a class-wide proposal was rendered without its WIDENED marker"
pass "the rendered proposal carries the WIDENED marker"

# g-14: no command at all must fail loudly rather than record a green cell that
# ran nothing.
CASE="$TEMP_DIR/case-no-command"
mkdir -p "$CASE"
write_list "$CASE/list.txt"
set +e
output=$(cd "$CASE" && "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "an empty command list must not exit 0 (got $rc): $output"
echo "$output" | grep -q "no command given" \
  || fail "expected an explicit error about the missing command, got: $output"
pass "an empty command list fails loudly instead of passing without running a test"

# s-9: a destination that cannot be cleared makes cp merge stale evidence into
# this attempt's, which is how a persistent failure acquires a flaky label.
CASE="$TEMP_DIR/case-dest-clear-fails"
mkdir -p "$CASE/stub-bin"
cat > "$CASE/stub-bin/rm" <<'EOS'
#!/usr/bin/env bash
for a in "$@"; do
  case "$a" in *flake-evidence/attempt-*) exit 1 ;; esac
done
exec /bin/rm "$@"
EOS
chmod +x "$CASE/stub-bin/rm"
cat > "$CASE/suite.sh" <<EOS
#!/usr/bin/env bash
OUT=ddprof-test/build/test-results/testDebug
mkdir -p "\$OUT"
$(declare -f write_failure_xml)
write_failure_xml "\$OUT" "com.dd.WobblyTest" "sometimesFails" "boom"
exit 1
EOS
chmod +x "$CASE/suite.sh"
write_list "$CASE/list.txt" "$(entry com.dd.WobblyTest.sometimesFails PROF-1 "$(day_offset 30)")"
set +e
output=$(cd "$CASE" && PATH="$CASE/stub-bin:$PATH" "$SCRIPTS/run_tests_with_retry.sh" --list list.txt "glibc-17-debug-amd64" -- ./suite.sh 2>&1)
rc=$?
set -e
[ "$rc" -ne 0 ] || fail "evidence that may be merged with an earlier attempt's must not be excused (got exit $rc): $output"
echo "$output" | grep -q "merged with an earlier attempt" \
  || fail "expected the merged-evidence warning, got: $output"
pass "a destination that cannot be cleared poisons the evidence rather than being excused"

echo "== quarantine.py fails closed =="

# An unreadable review_by must stop excusing rather than excuse forever:
# parse() accepts a blank or non-date value, and validate() only runs in PR CI.
for bad in "" "not-a-date" "2026-13-45"; do
  python3 -c "
import sys
sys.path.insert(0, '$SCRIPTS')
import quarantine
entry = {'test': 'a.B.c', 'ticket': 'PROF-1', 'added': '2026-01-01',
         'review_by': '$bad', 'cells': [], '_line': 1}
assert quarantine.is_expired(entry), 'review_by %r must count as expired' % '$bad'
assert quarantine.find_entry([entry], 'a.B.c', 'glibc-17-debug-amd64') is None, \
    'an entry with an unreadable review_by must not excuse anything'
" || fail "an unreadable review_by (${bad:-<blank>}) was treated as never expiring"
done
pass "an unreadable review_by counts as expired, not as eternal"

# A trailing '.*' covers one class's methods, as documented -- not a package.
python3 -c "
import sys
sys.path.insert(0, '$SCRIPTS')
import quarantine
pkg = {'test': 'com.datadoghq.profiler.*'}
assert not quarantine.covers(pkg, 'com.datadoghq.profiler.cpu.CpuTest.sampling'), \
    'a package-level pattern must not quarantine a whole subtree'
cls = {'test': 'com.datadoghq.profiler.cpu.CpuTest.*'}
assert quarantine.covers(cls, 'com.datadoghq.profiler.cpu.CpuTest.sampling')
assert quarantine.covers(cls, 'com.datadoghq.profiler.cpu.CpuTest.sampling()')
assert not quarantine.covers(cls, 'com.datadoghq.profiler.cpu.CpuTest.Inner.sampling')
" || fail "a trailing '.*' is not scoped to one class's methods"
pass "a trailing '.*' covers one class's methods, not a package"

write_list "$LIST" "$(entry 'com.datadoghq.profiler.*' PROF-1 "$(day_offset 30)")"
if python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null 2>&1; then
  fail "a package-level '.*' pattern should be rejected"
fi
pass "a package-level '.*' pattern is rejected"

write_list "$LIST" "$(entry '.*' PROF-1 "$(day_offset 30)")"
if python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null 2>&1; then
  fail "a bare '.*' pattern should be rejected"
fi
pass "a bare '.*' pattern is rejected"

# cells_overlap() fails closed for a glob matching nothing synthetic, so a JDK
# variant missing from the synthetic universe makes disjoint entries look like
# duplicates.
write_list "$LIST" \
  "$(entry a.B.c PROF-1 "$(day_offset 30)" '*17-j9*')" \
  "$(entry a.B.c PROF-2 "$(day_offset 30)" '*21-graal*')"
python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null 2>&1 \
  || fail "two entries on genuinely disjoint JDK variants must validate"
pass "disjoint JDK-variant cells are not mistaken for duplicates"

echo "== cells_glob narrows on every axis =="

python3 -c "
import sys
sys.path.insert(0, '$SCRIPTS')
import fnmatch
from flake_summary import cells_glob
# One cell: every axis is shared, so nothing else may match.
g = cells_glob(['glibc-8-j9-debug-amd64'])[0]
assert fnmatch.fnmatch('glibc-8-j9-debug-amd64', g), g
assert not fnmatch.fnmatch('glibc-17-debug-amd64', g), 'JDK axis not narrowed: %s' % g
# Differing only in JDK: that field opens up, the rest stays put.
g = cells_glob(['glibc-8-debug-amd64', 'glibc-17-debug-amd64'])[0]
assert fnmatch.fnmatch('glibc-8-debug-amd64', g) and fnmatch.fnmatch('glibc-17-debug-amd64', g), g
assert not fnmatch.fnmatch('musl-8-debug-amd64', g), 'libc axis not narrowed: %s' % g
assert not fnmatch.fnmatch('glibc-8-release-amd64', g), 'config axis not narrowed: %s' % g
assert not fnmatch.fnmatch('glibc-8-debug-aarch64', g), 'arch axis not narrowed: %s' % g
assert not fnmatch.fnmatch('glibc-8-debug-amd64-slow', g), 'suite suffix not narrowed: %s' % g
" || fail "cells_glob does not narrow on the JDK or the slow/regular axis"
pass "a proposal excludes cells differing only in JDK or in the slow suffix"

# A JDK variant like "17-j9" gives its cell one more "-"-separated field than
# a plain "17" cell, so cells_glob() can't merge the two into one glob and
# returns None. render_proposals() must not turn that into the empty `cells`
# column applies_to() reads as "no globs means everywhere" -- it must fall
# back to listing the exact cells observed.
python3 -c "
import sys
sys.path.insert(0, '$SCRIPTS')
from flake_summary import render_proposals, cells_glob
cells = ['glibc-17-debug-amd64', 'glibc-17-j9-debug-amd64']
assert cells_glob(cells) is None, 'fixture no longer exercises the None case'
out = '\n'.join(render_proposals({'com.dd.WobblyTest.sometimesFails': {'message': 'boom', 'cells': cells}}))
line = [l for l in out.splitlines() if l.startswith('com.dd.WobblyTest.sometimesFails')][0]
cells_field = line.split('|')[4].strip()
assert cells_field != '-', 'unglobbable cells rendered as the global-quarantine sentinel: ' + line
assert set(cells_field.split(',')) == set(cells), line
" || fail "a proposal for mixed-width cells silently quarantined the test everywhere"
pass "a proposal for cells with no computable glob lists them literally instead of everywhere"

echo "== a widened proposal says so =="

python3 -c "
import sys
sys.path.insert(0, '$SCRIPTS')
from flake_summary import widened_note, sanitize_quarantine_test_pattern
idx = 'com.dd.WobblyTest.[1]'
pat = sanitize_quarantine_test_pattern(idx)
assert pat == 'com.dd.WobblyTest.*', pat
note = widened_note(idx, pat)
assert note and 'WIDENED' in note and idx in note, note
exact = 'com.dd.WobblyTest.sometimesFails()'
assert widened_note(exact, sanitize_quarantine_test_pattern(exact)) is None
" || fail "a class-wide proposal for an inexpressible id carries no warning"
pass "a proposal widened to the class is marked as widened"

echo "== validate rejects unmatchable test patterns =="

write_list "$LIST" "$(entry 'com.dd.WobblyTest.sometimesFails()' PROF-1 "$(day_offset 30)")"
if python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null 2>&1; then
  fail "a test field carrying JUnit's parentheses should be rejected"
fi
pass "a test pattern written with parentheses is rejected"

write_list "$LIST" "$(entry 'com.dd.WobblyTest.[1]' PROF-1 "$(day_offset 30)")"
if python3 "$SCRIPTS/quarantine.py" --list "$LIST" validate >/dev/null 2>&1; then
  fail "a test field naming an invocation index should be rejected"
fi
pass "a test pattern naming an invocation index is rejected"

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
{"cell": "glibc-17-debug-aarch64", "attempts": 2, "attempts_run": 2,
 "flaky": [{"test": "com.dd.WobblyTest.sometimesFails", "failed_attempts": [1],
            "message": "got 2 | wanted 50",
            "flaky": true, "quarantined": false, "ticket": null}],
 "persistent": [], "quarantined": [], "gating_count": 1, "failure_count": 1,
 "final_attempt_ran": true, "final_attempt_gating_count": 0,
 "final_attempt_failure_count": 0, "other_task_failures": [],
 "gates": true, "gate_reason": "1 un-quarantined failure(s)"}
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

echo "== flake_summary.cells_glob =="

# Every glob cells_glob() proposes must actually fnmatch the cells it was
# derived from -- a glob built with axes in the wrong order (or missing an
# axis real cells vary on, like config) looks plausible but can never match,
# silently proposing a quarantine entry that quarantines nothing.
python3 -c "
import fnmatch, sys
sys.path.insert(0, '$SCRIPTS')
import flake_summary as fs

cases = [
    ['glibc-17-debug-amd64', 'glibc-21-debug-amd64'],
    ['musl-17-release-aarch64', 'musl-11-release-aarch64'],
    ['glibc-17-debug-amd64-slow'],
    ['glibc-17-asan-amd64', 'musl-17-asan-amd64'],
]
for cells in cases:
    globs = fs.cells_glob(cells) or []
    for cell in cells:
        assert any(fnmatch.fnmatch(cell, g) for g in globs), (
            'cells_glob(%r) = %r does not match %r' % (cells, globs, cell))
print('ok')
" | grep -q '^ok$' || fail "a cells_glob() proposal did not fnmatch the cells it was derived from"
pass "every cells_glob() proposal fnmatches the cells it was derived from"

echo
echo "All $TESTS quarantine tests passed."
