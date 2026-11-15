#! /bin/bash
# Minimal, dependency-free unit tests for .gitlab/scripts/check-abi-floor.sh.
# Run with: bash .gitlab/scripts/tests/check_abi_floor_test.sh
#
# The checker reads the artifact through $OBJDUMP, so these tests supply a stub
# that prints canned output. That keeps them runnable without a compiler or a
# real shared object, and lets them cover cases a real artifact cannot easily
# produce (a lost -static-libstdc++, an unreadable file).

# The run_* helpers are invoked indirectly, as arguments to the assert_*
# helpers, which shellcheck cannot see.
# shellcheck disable=SC2329

set -eo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
# Overridable so the checker's guards can be mutation-checked against this suite.
CHECKER="${CHECKER:-${HERE}/../check-abi-floor.sh}"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "${WORK}"' EXIT

# A stub objdump: -T prints ${FAKE_DYNSYM}, -p prints ${FAKE_HEADERS}.
cat > "${WORK}/objdump" <<'STUB'
#! /bin/bash
# FAKE_FAIL makes the stub behave like an objdump that cannot read the file.
[ -n "${FAKE_FAIL}" ] && exit 1
case "$1" in
  -T) cat "${FAKE_DYNSYM}" ;;
  -p) cat "${FAKE_HEADERS}" ;;
  *)  exit 1 ;;
esac
STUB
chmod +x "${WORK}/objdump"

: > "${WORK}/libjavaProfiler.so"

# The NEEDED set of a correctly linked release artifact, as measured on the
# shipped x86_64 library.
cat > "${WORK}/headers-good" <<'EOF'
Dynamic Section:
  NEEDED               libdl.so.2
  NEEDED               libpthread.so.0
  NEEDED               librt.so.1
  NEEDED               libm.so.6
  NEEDED               libc.so.6
  NEEDED               ld-linux-x86-64.so.2
EOF

# The same, plus the dependency a lost -static-libstdc++ would introduce.
cat > "${WORK}/headers-libstdcxx" <<'EOF'
Dynamic Section:
  NEEDED               libstdc++.so.6
  NEEDED               libm.so.6
  NEEDED               libc.so.6
  NEEDED               ld-linux-x86-64.so.2
EOF

: > "${WORK}/headers-empty"

# Undefined references in objdump -T form. The weak-binding column on the
# getentropy line is deliberate: it shifts the fields to its right, which is
# why the checker matches trailing fields instead of fixed columns.
cat > "${WORK}/dynsym-217" <<'EOF'
0000000000000000      DF *UND*	0000000000000000  GLIBC_2.2.5 memcpy
0000000000000000      DF *UND*	0000000000000000  GLIBC_2.17 clock_gettime
0000000000000000      DF *UND*	0000000000000000  GLIBC_2.3 dlopen
EOF

cat > "${WORK}/dynsym-227" <<'EOF'
0000000000000000      DF *UND*	0000000000000000  GLIBC_2.2.5 memcpy
0000000000000000      DF *UND*	0000000000000000  GLIBC_2.27 expf
EOF

cat > "${WORK}/dynsym-225-227" <<'EOF'
0000000000000000      DF *UND*	0000000000000000  GLIBC_2.2.5 memcpy
0000000000000000  w   DF *UND*	0000000000000000  GLIBC_2.25 getentropy
0000000000000000      DF *UND*	0000000000000000  GLIBC_2.27 expf
EOF

# What a .symver-pinned artifact looks like: objdump parenthesises a binding to
# a non-default version, so both the pinned symbol and anything else bound
# off-default appear in brackets. Reading only the bare form reports this file
# as having no versioned references at all.
cat > "${WORK}/dynsym-pinned" <<'EOF'
0000000000000000      DF *UND*	0000000000000000  GLIBC_2.2.5 memcpy
0000000000000000      DF *UND*	0000000000000000 (GLIBC_2.17) expf
0000000000000000  w   DF *UND*	0000000000000000 (GLIBC_2.25) getentropy
EOF

# The same artifact once the above-floor symbol is gone.
cat > "${WORK}/dynsym-pinned-clean" <<'EOF'
0000000000000000      DF *UND*	0000000000000000  GLIBC_2.2.5 memcpy
0000000000000000      DF *UND*	0000000000000000 (GLIBC_2.17) expf
EOF

# A musl artifact, or an objdump that could not read the file: no versioned
# glibc references at all.
: > "${WORK}/dynsym-empty"

run_checker() {
  local dynsym="$1" headers="$2" floor="$3"
  FAKE_DYNSYM="${WORK}/${dynsym}" FAKE_HEADERS="${WORK}/${headers}" \
    OBJDUMP="${WORK}/objdump" \
    "${CHECKER}" "${WORK}/libjavaProfiler.so" "${floor}" > "${WORK}/out" 2>&1
}

# Invokes the checker with arguments verbatim, for the argument-handling cases.
run_raw() {
  env FAKE_DYNSYM="${WORK}/dynsym-217" FAKE_HEADERS="${WORK}/headers-good" \
      OBJDUMP="${WORK}/objdump" "${CHECKER}" "$@" > "${WORK}/out" 2>&1
}

# Asserts an exact exit status, to keep a usage error distinguishable from a
# contract violation.
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

# Runs the checker with a `sort` that ignores -V, as a version-unaware sort
# would. Shadowing it on PATH is enough: the checker calls sort unqualified.
run_with_lexical_sort() {
  local floor="$1"
  mkdir -p "${WORK}/lexbin"
  cat > "${WORK}/lexbin/sort" <<'LEXSORT'
#! /bin/bash
args=()
for a in "$@"; do
  [ "$a" = "-V" ] || args+=("$a")
done
exec /usr/bin/sort "${args[@]}"
LEXSORT
  chmod +x "${WORK}/lexbin/sort"
  FAKE_DYNSYM="${WORK}/dynsym-217" FAKE_HEADERS="${WORK}/headers-good" \
    OBJDUMP="${WORK}/objdump" PATH="${WORK}/lexbin:${PATH}" \
    "${CHECKER}" "${WORK}/libjavaProfiler.so" "${floor}" > "${WORK}/out" 2>&1
}

# Simulates an objdump that cannot read the artifact at all.
run_unreadable() {
  local floor="$1"
  FAKE_FAIL=1 OBJDUMP="${WORK}/objdump" \
    "${CHECKER}" "${WORK}/libjavaProfiler.so" "${floor}" > "${WORK}/out" 2>&1
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
  if grep -qF "${needle}" "${WORK}/out"; then
    echo "PASS: ${desc}"
  else
    echo "FAIL: ${desc} — output does not mention '${needle}'"
    sed 's/^/      /' "${WORK}/out"
    FAILED=1
  fi
}

# --- the glibc symbol floor ---

# An artifact below the floor is fine; the floor is a ceiling on what may be
# required, not an exact match.
assert_pass "requirement below the floor is accepted" \
  run_checker dynsym-217 headers-good 2.28

# Requiring exactly the floor is the expected steady state.
assert_pass "requirement equal to the floor is accepted" \
  run_checker dynsym-227 headers-good 2.27

assert_fail "requirement above the floor is rejected" \
  run_checker dynsym-225-227 headers-good 2.17
# The whole point of the guard is naming what to fix, so the message must carry
# the offending symbols rather than only the version.
assert_output_contains "rejection names the offending symbol" "expf@GLIBC_2.27"
assert_output_contains "rejection names every offending symbol" "getentropy@GLIBC_2.25"

# Version ordering: GLIBC_2.2.5 must compare below GLIBC_2.17, which a lexical
# sort gets backwards. Both directions are checked, because a reversed
# comparison passes one of them by accident.
assert_pass "2.2.5 does not read as higher than a 2.17 floor" \
  run_checker dynsym-217 headers-good 2.17
assert_fail "2.17 reads as higher than a 2.2.5 floor" \
  run_checker dynsym-217 headers-good 2.2.5
assert_output_contains "the 2.17 symbol is named, not the 2.2.5 one" "clock_gettime@GLIBC_2.17"

# Parenthesised versions are what the shipped artifact actually contains once
# expf is pinned, so they must parse like bare ones. Checked in both
# directions: that the pinned symbol is not mistaken for unversioned, and that
# a parenthesised symbol above the floor is still caught.
assert_pass "a pinned artifact at the floor is accepted" \
  run_checker dynsym-pinned-clean headers-good 2.17
assert_fail "a parenthesised version above the floor is rejected" \
  run_checker dynsym-pinned headers-good 2.17
assert_output_contains "the parenthesised offender is named" "getentropy@GLIBC_2.25"
assert_output_contains "the parenthesised max is reported" "GLIBC_2.25"

# An empty symbol list means the file could not be read or is not a glibc
# build. Reporting a pass there would make the guard silently inoperative,
# which is worse than no guard at all.
assert_fail "no versioned glibc symbols is an error, not a pass" \
  run_checker dynsym-empty headers-good 2.28
assert_output_contains "the empty-symbol-list error explains itself" \
  "references no versioned glibc symbols"

# An objdump that cannot read the file must say so, rather than being reported
# as an empty-and-therefore-clean artifact.
assert_fail "an unreadable artifact is rejected" \
  run_unreadable 2.28
assert_output_contains "the unreadable-artifact error names the cause" "failed on"

# A `sort` without version ordering (busybox, say) must stop the check rather
# than silently inverting every comparison it makes.
assert_fail "a sort without version ordering is refused" \
  run_with_lexical_sort 2.28
assert_output_contains "the sort error explains the cause" "does not order versions"

# --- the runtime dependency allowlist ---

assert_fail "a libstdc++ dependency is rejected" \
  run_checker dynsym-217 headers-libstdcxx 2.28
assert_output_contains "rejection names the unexpected library" "libstdc++.so.6"

assert_fail "no NEEDED entries is an error, not a pass" \
  run_checker dynsym-217 headers-empty 2.28

# --- argument handling ---

assert_fail "a missing shared object is rejected" \
  run_raw "${WORK}/does-not-exist.so" 2.28
assert_output_contains "the missing-file error names the path" "no such file"

assert_exit_code "a missing floor argument exits with the usage status" 2 \
  run_raw "${WORK}/libjavaProfiler.so"
assert_output_contains "the usage error prints usage" "usage:"

exit "${FAILED}"
