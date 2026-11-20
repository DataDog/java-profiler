#! /bin/bash
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
# Hermetic checks for .gitlab/scripts/run-gtest-quarantine.sh: the --attempt
# exit-code aggregation (first signal death 128+N wins over any earlier plain
# failure; find failure vs clean zero match) and the RETRY_ON_NO_TEST_FAILURES
# guard (exported for asan only).
# Run with: bash .gitlab/scripts/tests/test_run_gtest_quarantine.sh

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
# Overridable so the behavior under test can be mutation-checked against
# this suite (the same hook pattern check_abi_floor_test.sh's CHECKER uses).
SCRIPT_UNDER_TEST="${SCRIPT_UNDER_TEST:-${HERE}/../run-gtest-quarantine.sh}"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT
STDERR_FILE="${WORK}/stderr.out"

fail() { echo "FAIL: $*"; FAILED=1; }
pass() { echo "PASS: $*"; }

# Fresh fake repo tree per case: the script under test derives REPO_ROOT
# from its own BASH_SOURCE and cd's there, so it must be copied, never run
# in place.
setup_tree() {
  rm -rf "${WORK}/repo"
  mkdir -p "${WORK}/repo/.gitlab/scripts"
  cp "${SCRIPT_UNDER_TEST}" "${WORK}/repo/.gitlab/scripts/run-gtest-quarantine.sh"
}

# Fake gtest binary in the real build layout: the directory carries the
# <config>_<target> prefix, the binary the plain test name. With xml=1 the
# fake writes the JUnit XML a completing binary leaves behind -- a failing
# binary with XML is a plain failure, without XML it is an abort (the marker
# path).
make_bin() {
  local name="$1" rc="$2" xml="${3:-}"
  mkdir -p "${WORK}/repo/ddprof-lib/build/bin/gtest/release_${name}_ut"
  # Single-quoted format: $xml_out must reach the generated script unexpanded.
  # The fake HONORS --gtest_output=xml:<path> (writes exactly where the
  # runner tells it), so a renamed or dropped runner argument fails the
  # suite instead of silently decoupling the evidence.
  # shellcheck disable=SC2016
  printf '#!/usr/bin/env bash
xml_out=""
for a in "$@"; do
  case "$a" in --gtest_output=xml:*) xml_out="${a#--gtest_output=xml:}" ;; esac
done
if [ -n "%s" ] && [ -n "$xml_out" ]; then
  cat > "$xml_out" <<XMLEOF
<?xml version="1.0" encoding="UTF-8"?>
<testsuites tests="1" failures="%s">
  <testsuite name="FakeSuite" tests="1" failures="%s">
    <testcase name="fails" classname="FakeSuite" status="run">%s</testcase>
  </testsuite>
</testsuites>
XMLEOF
fi
exit %s
' "${xml}" "$([ "${rc}" -ne 0 ] && echo 1 || echo 0)" "$([ "${rc}" -ne 0 ] && echo 1 || echo 0)" "$([ "${rc}" -ne 0 ] && echo '<failure message="boom" type="AssertionFailed"/>' || echo '')" "${rc}" \
    > "${WORK}/repo/ddprof-lib/build/bin/gtest/release_${name}_ut/${name}"
  chmod +x "${WORK}/repo/ddprof-lib/build/bin/gtest/release_${name}_ut/${name}"
}

# Stub retry wrapper: records the exported flag and the cell argument; UNSET
# is the observable form of "not exported" (the real wrapper's default-0
# contract makes an empty value indistinguishable from an unset one).
setup_retry_stub() {
  mkdir -p "${WORK}/repo/.github/scripts"
  cat > "${WORK}/repo/.github/scripts/run_tests_with_retry.sh" <<'STUB'
#!/usr/bin/env bash
echo "RETRY=${RETRY_ON_NO_TEST_FAILURES-UNSET}"
echo "CELL=${3-}"
STUB
  chmod +x "${WORK}/repo/.github/scripts/run_tests_with_retry.sh"
}

# Runs the copied script in the fake tree; fills OUT, RC, and STDERR_FILE.
# $1 = SANITIZER_LC, $2 = extra argument ("" or --attempt).
run_case() {
  local cfg="$1" extra="${2:-}" args=()
  [ -n "${extra}" ] && args=("${extra}")
  OUT=$( cd "${WORK}/repo" && \
    env -u RETRY_ON_NO_TEST_FAILURES SANITIZER_LC="${cfg}" GTEST_ARCH=amd64 \
      bash .gitlab/scripts/run-gtest-quarantine.sh "${args[@]+"${args[@]}"}" \
      2> "${STDERR_FILE}" )
  RC=$?
}

# Runs the copied script with one variable unset; fills OUT, RC, STDERR_FILE.
# $1 = name of the variable to unset (SANITIZER_LC or GTEST_ARCH).
run_case_missing_var() {
  local a filtered=()
  for a in SANITIZER_LC=asan GTEST_ARCH=amd64; do
    [ "${a%%=*}" = "${1}" ] && continue
    filtered+=("${a}")
  done
  OUT=$( cd "${WORK}/repo" && \
    env -u RETRY_ON_NO_TEST_FAILURES -u "${1}" \
      env "${filtered[@]}" \
      bash .gitlab/scripts/run-gtest-quarantine.sh \
      2> "${STDERR_FILE}" )
  RC=$?
}

assert_rc() {
  local expected="$1" label="$2"
  if [ "${RC}" -eq "${expected}" ]; then
    pass "${label}: exit ${RC}"
  else
    fail "${label}: expected exit ${expected}, got ${RC} (stderr: $(cat "${STDERR_FILE}"))"
  fi
}

# T1 — a signal death beats a later plain failure (mutation killer for
# the dropped-guard / always-overwrite mutations of the aggregation guard).
# The plain failure writes XML; the signal death leaves none.
setup_tree
make_bin release_alpha 130
make_bin release_beta 1 xml
run_case release --attempt
assert_rc 130 "T1 signal rc wins over later plain failure"

# T2 — an earlier plain failure must NOT mask a later signal death
# (bug-fix pin: the pre-fix script kept the first failure's rc, 1).
setup_tree
make_bin release_alpha 1 xml
make_bin release_beta 130
run_case release --attempt
assert_rc 130 "T2 signal rc outranks earlier plain failure"

# T3 — a fully passing suite exits 0 (the precedence rule must not fire
# on passes).
setup_tree
make_bin release_alpha 0 xml
make_bin release_beta 0 xml
run_case release --attempt
assert_rc 0 "T3 passing suite exits 0"

# T9 — a sanitizer abort (exit 66, no signal) after another binary's
# quarantined failure must surface the ABORTED marker and win the exit:
# without it the classifier sees only quarantined XML and excuses the job.
setup_tree
make_bin release_alpha 1 xml
make_bin release_beta 66
run_case release --attempt
assert_rc 66 "T9 sanitizer abort wins over earlier plain failure"
if grep -q "ABORTED: release_beta exited 66 without producing test results" <<< "${OUT}"; then
  pass "T9 output carries the ABORTED marker"
else
  fail "T9: output missing the ABORTED marker, got: ${OUT}"
fi

# T10 — an ASan-style abort (exit 1, no signal) is indistinguishable from a
# plain failure by exit code alone; the ABORTED marker is the only evidence.
setup_tree
make_bin release_alpha 1 xml
make_bin release_beta 1
run_case release --attempt
assert_rc 1 "T10 abort exit 1 propagates"
if grep -q "ABORTED: release_beta exited 1 without producing test results" <<< "${OUT}"; then
  pass "T10 output carries the ABORTED marker"
else
  fail "T10: output missing the ABORTED marker, got: ${OUT}"
fi

# T4 — a failed find is a build problem: exit 2 with a stderr message
# naming the path (bug-fix pin: the pre-fix script exited 1 via the
# generic zero-match path).
setup_tree
run_case release --attempt
assert_rc 2 "T4 find failure exits 2"
if grep -q "find over ddprof-lib/build/bin/gtest failed" "${STDERR_FILE}"; then
  pass "T4 stderr names the build problem"
else
  fail "T4: stderr missing 'find over ddprof-lib/build/bin/gtest failed'"
fi

# T5 — a clean zero match stays a runner problem: exit 1 and the
# byte-identical one-line stdout message. Only an asan_-prefixed directory
# exists, so the release selector has nothing to anchor on.
setup_tree
mkdir -p "${WORK}/repo/ddprof-lib/build/bin/gtest/asan_other_ut"
printf '#!/usr/bin/env bash\nexit 0\n' > "${WORK}/repo/ddprof-lib/build/bin/gtest/asan_other_ut/other"
chmod +x "${WORK}/repo/ddprof-lib/build/bin/gtest/asan_other_ut/other"
run_case release --attempt
assert_rc 1 "T5 clean zero match exits 1"
EXPECTED_MSG="no gtest binaries matching /release_ under ddprof-lib/build/bin/gtest; the build produced nothing runnable"
if [ "${OUT}" = "${EXPECTED_MSG}" ]; then
  pass "T5 zero-match message byte-identical"
else
  fail "T5: stdout '${OUT}' != expected message"
fi

# T11 — the tsan cell runs with TSAN_OPTIONS=halt_on_error=1: TSan's default
# (halt_on_error=0, exitcode=66) lets gtest finish and write a passing XML
# before exiting 66 at shutdown, which neither the ABORTED marker nor the
# >128 check would catch. The fake binary only halts without XML when the
# runner exported the flag; its stdout names the value it received.
setup_tree
mkdir -p "${WORK}/repo/ddprof-lib/build/bin/gtest/tsan_racy_ut"
cat > "${WORK}/repo/ddprof-lib/build/bin/gtest/tsan_racy_ut/tsan_racy_ut" <<'FAKE'
#!/usr/bin/env bash
echo "TSAN_OPTIONS=${TSAN_OPTIONS-UNSET}"
exit 66
FAKE
chmod +x "${WORK}/repo/ddprof-lib/build/bin/gtest/tsan_racy_ut/tsan_racy_ut"
run_case tsan --attempt
assert_rc 66 "T11 tsan race halt propagates exit 66"
if grep -q "ABORTED: tsan_racy_ut exited 66 without producing test results" <<< "${OUT}"; then
  pass "T11 tsan race halt carries the ABORTED marker"
else
  fail "T11: output missing the ABORTED marker, got: ${OUT}"
fi
if grep -q "TSAN_OPTIONS=.*halt_on_error=1" <<< "${OUT}"; then
  pass "T11 runner exports TSAN_OPTIONS=halt_on_error=1"
else
  fail "T11: binary did not receive halt_on_error=1, got: ${OUT}"
fi

# T12 — a stale TEST-*.xml from a reused workspace must not defeat the
# ABORTED detection: the attempt clears the results dir before running, so
# a planted XML disappears and the aborting binary is still marked.
setup_tree
make_bin release_alpha 66
mkdir -p "${WORK}/repo/ddprof-lib/build/test-results/gtest/release"
printf '<testsuites><testsuite name="Ghost"><testcase name="ghost" classname="Ghost"/></testsuite></testsuites>' \
  > "${WORK}/repo/ddprof-lib/build/test-results/gtest/release/TEST-release_alpha.xml"
run_case release --attempt
assert_rc 66 "T12 aborting binary keeps its exit code"
if grep -q "ABORTED: release_alpha exited 66 without producing test results" <<< "${OUT}"; then
  pass "T12 planted stale XML does not defeat the ABORTED marker"
else
  fail "T12: stale XML suppressed the ABORTED marker, got: ${OUT}"
fi

# T13 — rc 128 is a plain failure, not a signal death: flake_report.py's
# cut-short check is strict >128, so the boundary must match exactly.
setup_tree
make_bin release_alpha 128 xml
run_case release --attempt
assert_rc 128 "T13 rc 128 stays a plain failure"
if grep -q "ABORTED" <<< "${OUT}"; then
  fail "T13: rc 128 must not produce the ABORTED marker, got: ${OUT}"
else
  pass "T13 rc 128 produces no ABORTED marker"
fi

# T14 — a SANITIZER_LC outside the known set is rejected before the value
# reaches the rm -rf path (the guard doubles as the injection guard).
setup_tree
OUT=$( cd "${WORK}/repo" && \
  env SANITIZER_LC="../oops" GTEST_ARCH=amd64 \
    bash .gitlab/scripts/run-gtest-quarantine.sh 2> "${STDERR_FILE}" )
RC=$?
assert_rc 1 "T14 unknown SANITIZER_LC exits 1"
if grep -q "must be one of: asan, tsan, release" "${STDERR_FILE}"; then
  pass "T14 stderr names the allowed values"
else
  fail "T14: stderr missing the allowed-values message, got: $(cat "${STDERR_FILE}")"
fi
if [ -d "${WORK}/repo/oops" ]; then
  fail "T14: the unvalidated value reached the filesystem"
else
  pass "T14 the rejected value never touches the results path"
fi

# T18 — a miswired GTEST_ARCH (e.g. the runner tag's arm64) must fail loudly:
# the cell string it would build matches no quarantine entry and mutes
# nothing silently.
OUT=$( cd "${WORK}/repo" && \
  env SANITIZER_LC=asan GTEST_ARCH=arm64 \
    bash .gitlab/scripts/run-gtest-quarantine.sh 2> "${STDERR_FILE}" )
RC=$?
assert_rc 1 "T18 GTEST_ARCH=arm64 exits 1"
if grep -q "must be one of: amd64, aarch64" "${STDERR_FILE}"; then
  pass "T18 stderr names the allowed arch spellings"
else
  fail "T18: stderr missing the arch message, got: $(cat "${STDERR_FILE}")"
fi

# T15 — the selector must anchor on the config directory: a "release_helper"
# binary parked in an asan_other directory must not be swept into the
# release cell. (The counterpart — an unprefixed binary inside a release_*
# directory being dropped — is the same selector, anchored in the other
# direction.)
setup_tree
mkdir -p "${WORK}/repo/ddprof-lib/build/bin/gtest/asan_other"
printf '#!/usr/bin/env bash\nexit 1\n' > "${WORK}/repo/ddprof-lib/build/bin/gtest/asan_other/release_helper"
chmod +x "${WORK}/repo/ddprof-lib/build/bin/gtest/asan_other/release_helper"
make_bin release_real 0 xml
run_case release --attempt
assert_rc 0 "T15 release cell runs only its own config's binaries"
if grep -q "release_helper" <<< "${OUT}"; then
  fail "T15: the stray asan-tree binary was selected, got: ${OUT}"
else
  pass "T15 the stray asan-tree binary was not selected"
fi

# T16 — a failed mkdir after the rm -rf must fail the attempt (exit 3): gtest
# cannot write its XML when the directory is missing yet still runs and can
# exit 0, so an unchecked mkdir yields a green-looking empty-evidence run.
# Point the results tree at a path whose parent is a regular file.
setup_tree
mkdir -p "${WORK}/repo/ddprof-lib/build/test-results"
printf 'not a directory' > "${WORK}/repo/ddprof-lib/build/test-results/gtest"
run_case release --attempt
assert_rc 3 "T16 mkdir failure exits 3"
if grep -q "cannot create" "${STDERR_FILE}"; then
  pass "T16 stderr names the failed mkdir"
else
  fail "T16: stderr missing the mkdir failure message, got: $(cat "${STDERR_FILE}")"
fi

# T17 — a binary that exits 0 WITHOUT its XML is evidence loss, not a pass:
# the runner must emit the ABORTED marker and fail the attempt (rc 1), so the
# cut-short gate can fire instead of a green run with empty evidence.
setup_tree
make_bin release_alpha 0
run_case release --attempt
assert_rc 1 "T17 exit-0-without-XML fails the attempt"
if grep -q "ABORTED: release_alpha exited 0 without producing test results" <<< "${OUT}"; then
  pass "T17 output carries the ABORTED marker"
else
  fail "T17: output missing the ABORTED marker, got: ${OUT}"
fi

# T6 — the retry-flag guard exports RETRY_ON_NO_TEST_FAILURES=1 for the
# asan cell only (ASan init aborting before any test runs); flipping the
# config comparison fails this case. The stub records the exported value.
setup_tree
setup_retry_stub
for cfg in asan tsan release; do
  case "${cfg}" in
    asan) expected="RETRY=1" ;;
    *)    expected="RETRY=UNSET" ;;
  esac
  run_case "${cfg}"
  assert_rc 0 "T6 ${cfg} wrapper propagates stub rc"
  if [ "${OUT%%$'\n'*}" = "${expected}" ]; then
    pass "T6 ${cfg}: RETRY_ON_NO_TEST_FAILURES exported as expected"
  else
    fail "T6 ${cfg}: expected '${expected}', got '${OUT}'"
  fi
done

# T7 — the wrapper must receive the exact cell string; dropping either
# variable from the construction (or swapping the axes) fails this case.
for cfg in asan tsan release; do
  run_case "${cfg}"
  if grep -q "CELL=glibc-${cfg}-amd64" <<< "${OUT}"; then
    pass "T7 ${cfg}: wrapper called with cell glibc-${cfg}-amd64"
  else
    fail "T7 ${cfg}: expected cell glibc-${cfg}-amd64 in stub output, got: ${OUT}"
  fi
done

# T8 — unset SANITIZER_LC or GTEST_ARCH fails the invocation instead of
# building a truncated cell name (dropping the guard would call the wrapper
# with cell 'glibc-asan-' or 'glibc--amd64').
for var in SANITIZER_LC GTEST_ARCH; do
  run_case_missing_var "${var}"
  assert_rc 1 "T8 unset ${var} exits 1"
  if grep -q "SANITIZER_LC and GTEST_ARCH must both be set" "${STDERR_FILE}"; then
    pass "T8 unset ${var}: stderr names the missing variables"
  else
    fail "T8 unset ${var}: stderr missing the guard message, got: $(cat "${STDERR_FILE}")"
  fi
done

if [ "${FAILED}" -eq 0 ]; then
  echo "test_run_gtest_quarantine: all tests passed"
fi
exit "${FAILED}"
