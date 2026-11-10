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

# Fake gtest binary: basename MUST start with release_ or the script's
# grep "/${SANITIZER_LC}_" selector silently drops it.
make_bin() {
  local name="$1" rc="$2"
  mkdir -p "${WORK}/repo/ddprof-lib/build/bin/gtest/release"
  printf '#!/usr/bin/env bash\nexit %s\n' "${rc}" \
    > "${WORK}/repo/ddprof-lib/build/bin/gtest/release/${name}"
  chmod +x "${WORK}/repo/ddprof-lib/build/bin/gtest/release/${name}"
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

# T1 — first signal death beats a later plain failure (mutation killer for
# the dropped-guard / always-overwrite mutations of the aggregation guard).
setup_tree
make_bin release_alpha 130
make_bin release_beta 1
run_case release --attempt
assert_rc 130 "T1 signal rc wins over later plain failure"

# T2 — an earlier plain failure must NOT mask a later signal death
# (bug-fix pin: the pre-fix script kept the first failure's rc, 1).
setup_tree
make_bin release_alpha 1
make_bin release_beta 130
run_case release --attempt
assert_rc 130 "T2 signal rc outranks earlier plain failure"

# T3 — a fully passing suite exits 0 (the precedence rule must not fire
# on passes).
setup_tree
make_bin release_alpha 0
make_bin release_beta 0
run_case release --attempt
assert_rc 0 "T3 passing suite exits 0"

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
# byte-identical one-line stdout message.
setup_tree
make_bin other_beta 0
run_case release --attempt
assert_rc 1 "T5 clean zero match exits 1"
EXPECTED_MSG="no gtest binaries matching /release_ under ddprof-lib/build/bin/gtest; the build produced nothing runnable"
if [ "${OUT}" = "${EXPECTED_MSG}" ]; then
  pass "T5 zero-match message byte-identical"
else
  fail "T5: stdout '${OUT}' != expected message"
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
