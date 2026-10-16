#! /bin/bash
# Minimal, dependency-free unit tests for .gitlab/scripts/check-release-flags.sh.
# Run with: bash .gitlab/scripts/tests/check_release_flags_test.sh
#
# The checker reads the artifact through $NM/$STRINGS, so these tests supply
# stubs that print canned output. That keeps them runnable without a compiler
# or a real shared object built with -PenableFaultInjection / -PenableSamplerPerf.

# The run_* helpers are invoked indirectly, as arguments to the assert_*
# helpers, which shellcheck cannot see.
# shellcheck disable=SC2329

set -eo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
# Overridable so the checker's guards can be mutation-checked against this suite.
CHECKER="${CHECKER:-${HERE}/../check-release-flags.sh}"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "${WORK}"' EXIT

# A stub nm: prints ${FAKE_NM}. A stub strings: prints ${FAKE_STRINGS}.
cat > "${WORK}/nm" <<'STUB'
#! /bin/bash
[ -n "${FAKE_NM_FAIL}" ] && exit 1
cat "${FAKE_NM}"
STUB
chmod +x "${WORK}/nm"

cat > "${WORK}/strings" <<'STUB'
#! /bin/bash
[ -n "${FAKE_STRINGS_FAIL}" ] && exit 1
cat "${FAKE_STRINGS}"
STUB
chmod +x "${WORK}/strings"

: > "${WORK}/libjavaProfiler.so"

# A plain release build's symbol table: real symbols, none of the flag-only
# markers. SamplerPerf itself (unlike SamplerPerfProbe) always exists -- its
# disabled variant is what a build with neither flag ships -- so it belongs
# in the clean fixture, to prove the checker doesn't over-match on the name.
cat > "${WORK}/nm-clean" <<'EOF'
0000000000064500 T Agent_OnLoad
000000000006db10 t _ZN11SamplerPerf10primeClockEv
000000000006db20 t _ZN11SamplerPerf6reportEv
0000000000023000 t _ZN8Profiler4stopEv
EOF

# Mangled (Itanium) form, as plain nm -- not nm -C -- actually prints it.
cat > "${WORK}/nm-faultinj" <<'EOF'
0000000000064500 T Agent_OnLoad
000000000004b940 t _Z8crashNowv
000000000004b9b0 t _ZN8faultinj10shouldFireEyPKc
000000000004ba70 t _ZN8faultinj13poisonAddressEv
000000000004b950 t _ZN8faultinj4initEv
EOF

cat > "${WORK}/nm-samplerperf" <<'EOF'
0000000000064500 T Agent_OnLoad
000000000006db10 t _ZN11SamplerPerf10primeClockEv
000000000006db20 t _ZN11SamplerPerf6reportEv
0000000000019ff0 t _ZN16SamplerPerfProbeD2Ev
EOF

: > "${WORK}/nm-empty"

cat > "${WORK}/strings-clean" <<'EOF'
method_resolution_dropped_tls
metadata_tree_null_child
EOF

cat > "${WORK}/strings-faultinj" <<'EOF'
method_resolution_dropped_tls
faults_injected
EOF

cat > "${WORK}/strings-samplerperf" <<'EOF'
method_resolution_dropped_tls
sampler_ticks.cpu
sampler_count.cpu
EOF

run_checker() {
  local nm="$1" strings="$2"
  FAKE_NM="${WORK}/${nm}" FAKE_STRINGS="${WORK}/${strings}" \
    NM="${WORK}/nm" STRINGS="${WORK}/strings" \
    "${CHECKER}" "${WORK}/libjavaProfiler.so" > "${WORK}/out" 2>&1
}

# Invokes the checker with arguments verbatim, for the argument-handling cases.
run_raw() {
  env FAKE_NM="${WORK}/nm-clean" FAKE_STRINGS="${WORK}/strings-clean" \
      NM="${WORK}/nm" STRINGS="${WORK}/strings" "${CHECKER}" "$@" > "${WORK}/out" 2>&1
}

run_nm_unreadable() {
  FAKE_NM_FAIL=1 FAKE_STRINGS="${WORK}/strings-clean" \
    NM="${WORK}/nm" STRINGS="${WORK}/strings" \
    "${CHECKER}" "${WORK}/libjavaProfiler.so" > "${WORK}/out" 2>&1
}

assert_exit_code() {
  local desc="$1" expected="$2"; shift 2
  local actual=0
  "$@" || actual=$?
  if [ "${actual}" -eq "${expected}" ]; then
    echo "PASS: ${desc}"
  else
    echo "FAIL: ${desc} — expected exit ${expected}, got ${actual}"
    sed 's/^/      /' "${WORK}/out"
    FAILED=1
  fi
}

assert_pass() {
  local desc="$1"; shift
  if "$@"; then
    echo "PASS: ${desc}"
  else
    echo "FAIL: ${desc} — expected the check to pass"
    sed 's/^/      /' "${WORK}/out"
    FAILED=1
  fi
}

assert_fail() {
  local desc="$1"; shift
  if "$@"; then
    echo "FAIL: ${desc} — expected the check to fail"
    sed 's/^/      /' "${WORK}/out"
    FAILED=1
  else
    echo "PASS: ${desc}"
  fi
}

assert_output_contains() {
  local desc="$1" needle="$2"
  if grep -qF -- "${needle}" "${WORK}/out"; then
    echo "PASS: ${desc}"
  else
    echo "FAIL: ${desc} — output does not mention '${needle}'"
    sed 's/^/      /' "${WORK}/out"
    FAILED=1
  fi
}

# --- a clean release build ---

assert_pass "a build with neither flag is accepted" \
  run_checker nm-clean strings-clean

# --- -PenableFaultInjection markers ---

assert_fail "the faultinj:: namespace fails the check" \
  run_checker nm-faultinj strings-clean
assert_output_contains "the failure names the faultinj:: namespace" "faultinj:: namespace"
assert_output_contains "the failure names the offending flag" "-PenableFaultInjection"

assert_fail "the faults_injected counter string fails the check" \
  run_checker nm-clean strings-faultinj
assert_output_contains "the failure names the faults_injected counter" "faults_injected"

# --- -PenableSamplerPerf markers ---

assert_fail "the SamplerPerfProbe class fails the check" \
  run_checker nm-samplerperf strings-clean
assert_output_contains "the failure names the SamplerPerfProbe class" "SamplerPerfProbe"
assert_output_contains "the failure names the offending flag" "-PenableSamplerPerf"

assert_fail "the sampler_ticks./sampler_count. counter strings fail the check" \
  run_checker nm-clean strings-samplerperf
assert_output_contains "the failure names sampler_ticks" "sampler_ticks"
assert_output_contains "the failure names sampler_count" "sampler_count"

# --- symbol-table integrity ---

# An empty symbol table means the file could not be meaningfully read.
# Reporting a pass there would make the guard silently inoperative.
assert_fail "an empty symbol table is an error, not a pass" \
  run_checker nm-empty strings-clean
assert_output_contains "the empty-symtab error explains itself" \
  "found no symbols"

assert_fail "an nm that cannot read the file is rejected" \
  run_nm_unreadable
assert_output_contains "the unreadable-artifact error names the cause" "failed on"

# --- argument handling ---

assert_fail "a missing shared object is rejected" \
  run_raw "${WORK}/does-not-exist.so"
assert_output_contains "the missing-file error names the path" "no such file"

assert_exit_code "a missing shared-object argument exits with the usage status" 2 \
  run_raw

exit "${FAILED}"
