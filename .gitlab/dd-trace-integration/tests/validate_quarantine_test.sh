#! /bin/bash
# Minimal, dependency-free unit tests for validate-quarantine.sh, the CI
# validator of .gitlab/dd-trace-integration/quarantine.txt.
# Run with: bash .gitlab/dd-trace-integration/tests/validate_quarantine_test.sh
#
# Each case builds a list in a temp dir, points the validator at it through
# QUARANTINE_LIST, and asserts on the exit status and the reported problem.

set -eo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT="${HERE}/../validate-quarantine.sh"
LIB="${HERE}/../quarantine-lib.sh"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "${WORK}"' EXIT

# A date N days from today, pure bash, via the lib's day serials — the tests
# must not depend on GNU vs BSD date extensions. The source path is computed
# at runtime, so shellcheck cannot follow it.
# shellcheck disable=SC1090,SC1091
. "${LIB}"

days_to_date() {
  local serial="$1" y=1970 m d
  while :; do
    local ydays=365
    if [ $((y % 4)) -eq 0 ] && { [ $((y % 100)) -ne 0 ] || [ $((y % 400)) -eq 0 ]; }; then
      ydays=366
    fi
    [ "${serial}" -ge "${ydays}" ] || break
    serial=$((serial - ydays))
    y=$((y + 1))
  done
  local -a mdays=(31 28 31 30 31 30 31 31 30 31 30 31)
  if [ $((y % 4)) -eq 0 ] && { [ $((y % 100)) -ne 0 ] || [ $((y % 400)) -eq 0 ]; }; then
    mdays[1]=29
  fi
  for d in "${mdays[@]}"; do
    [ "${serial}" -ge "${d}" ] || break
    serial=$((serial - d))
    m=$((m + 1))
  done
  printf '%04d-%02d-%02d' "${y}" "$((m + 1))" "$((serial + 1))"
}

TODAY=$(quarantine_today)
TODAY_SERIAL=$(quarantine_days_since_epoch "${TODAY}")
FUTURE=$(days_to_date $((TODAY_SERIAL + 90)))
FAR_FUTURE=$(days_to_date $((TODAY_SERIAL + 200)))
PAST=$(days_to_date $((TODAY_SERIAL - 10)))
MAX_DAY=$(days_to_date $((TODAY_SERIAL + QUARANTINE_MAX_REVIEW_DAYS)))
MAX_DAY_PLUS_1=$(days_to_date $((TODAY_SERIAL + QUARANTINE_MAX_REVIEW_DAYS + 1)))

# Runs the validator on a list file, keeping stderr and the exit code.
run_validator() {
  local list="$1"
  VALIDATOR_EXIT=0
  OUT=$(QUARANTINE_LIST="${list}" "${BASH}" "${SCRIPT}" 2>&1) || VALIDATOR_EXIT=$?
}

assert_exit() {
  local desc="$1" expected="$2"
  if [ "${VALIDATOR_EXIT}" -eq "${expected}" ]; then
    echo "PASS: ${desc}"
  else
    echo "FAIL: ${desc} — expected exit ${expected}, got ${VALIDATOR_EXIT}"
    printf '%s\n' "${OUT}" | sed 's/^/      /' | head -8
    FAILED=1
  fi
}

assert_out_contains() {
  local desc="$1" needle="$2"
  if printf '%s' "${OUT}" | grep -qF -- "${needle}"; then
    echo "PASS: ${desc}"
  else
    echo "FAIL: ${desc} — output does not contain '${needle}'"
    printf '%s\n' "${OUT}" | sed 's/^/      /' | head -8
    FAILED=1
  fi
}

assert_eq() {
  local desc="$1" actual="$2" expected="$3"
  if [ "${actual}" = "${expected}" ]; then
    echo "PASS: ${desc}"
  else
    echo "FAIL: ${desc} — expected '${expected}', got '${actual}'"
    FAILED=1
  fi
}

new_list() {
  local name="$1"
  : > "${WORK}/${name}.txt"
  printf '%s/%s.txt' "${WORK}" "${name}"
}

add() {
  local list="$1" id="$2" ticket="$3" added="$4" review_by="$5" reason="${6:-flake, 1 in ~5 runs}"
  echo "${id} | ${ticket} | ${added} | ${review_by} | ${reason}" >> "${list}"
}

# --- quarantine_days_since_epoch: absolute pinned values ---
#
# The leap-year adjustment must be pinned to absolute values; round-tripping
# through days_to_date() stays self-consistent with a mutated lib and would
# detect nothing.
assert_eq "1970-01-01 is epoch day 0" "$(quarantine_days_since_epoch 1970-01-01)" "0"
assert_eq "2000-03-01 is epoch day 11017 (leap year, adjustment taken)" "$(quarantine_days_since_epoch 2000-03-01)" "11017"
assert_eq "2000-02-28 is epoch day 11015 (no adjustment before March)" "$(quarantine_days_since_epoch 2000-02-28)" "11015"
assert_eq "2100-03-01 is epoch day 47541 (century not divisible by 400)" "$(quarantine_days_since_epoch 2100-03-01)" "47541"
assert_eq "1900-03-01 is epoch day -25508 (pre-epoch, century not div by 400)" "$(quarantine_days_since_epoch 1900-03-01)" "-25508"
assert_eq "2029-04-15 is epoch day 21654 (leap day of 2028 counted)" "$(quarantine_days_since_epoch 2029-04-15)" "21654"
D_FEB29="$(quarantine_days_since_epoch 2024-02-29)"
D_MAR1="$(quarantine_days_since_epoch 2024-03-01)"
assert_eq "2024-02-29 and 2024-03-01 are exactly one day apart" "$((D_MAR1 - D_FEB29))" "1"

# --- leap-year validity shares the same predicate ---

valid_of() {
  if quarantine_date_valid "$1"; then echo 0; else echo 1; fi
}
assert_eq "2024-02-29 is a valid date" "$(valid_of 2024-02-29)" "0"
assert_eq "2000-02-29 is a valid date" "$(valid_of 2000-02-29)" "0"
assert_eq "2023-02-29 is invalid (common year)" "$(valid_of 2023-02-29)" "1"
assert_eq "2100-02-29 is invalid (century, not div by 400)" "$(valid_of 2100-02-29)" "1"
assert_eq "1900-02-29 is invalid (century, not div by 400)" "$(valid_of 1900-02-29)" "1"

# --- a well-formed list validates ---

L=$(new_list valid)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "${TODAY}" "${FUTURE}"
add "${L}" "musl-*-hotspot-jdk21/tracer-profiler" "PROF-16014" "2026-11-12" "${FUTURE}" "startup timeout on musl"
run_validator "${L}"
assert_exit "a valid list exits 0" 0
assert_out_contains "the summary counts the entries" "2 quarantined scenario(s), all valid"

# --- an empty (header-only) list validates: the mechanism starts inert ---

L=$(new_list empty)
echo "# just a header" > "${L}"
run_validator "${L}"
assert_exit "an empty list exits 0" 0
assert_out_contains "the empty list reports zero entries" "0 quarantined scenario(s), all valid"

# --- a missing list fails ---

run_validator "${WORK}/does-not-exist.txt"
assert_exit "a missing list fails" 1
assert_out_contains "the missing list is named" "does not exist"

# --- format errors ---

L=$(new_list fields)
echo "glibc-x64-openj9-jdk25/profiler-only | PROF-16618 | ${TODAY} | ${FUTURE}" >> "${L}"
run_validator "${L}"
assert_exit "a four-field line fails" 1
assert_out_contains "the four-field error reports the field count" "expected 5 '|'-separated fields, found 4"

L=$(new_list piped-reason)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "${TODAY}" "${FUTURE}" "flake | retries ok"
run_validator "${L}"
assert_exit "a reason containing a pipe stays legal" 0

L=$(new_list id-shape)
echo "glibc-x64-openj9-jdk25 | PROF-16618 | ${TODAY} | ${FUTURE} | flake" >> "${L}"
run_validator "${L}"
assert_exit "an id without a scenario fails" 1
assert_out_contains "the id error names the expected shape" "not <cell-glob>/<scenario>"

# --- ticket discipline: no ticket, no quarantine ---

L=$(new_list no-ticket)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "" "${TODAY}" "${FUTURE}"
run_validator "${L}"
assert_exit "an empty ticket fails" 1
assert_out_contains "the empty-ticket error is actionable" "field 'ticket' is empty"

L=$(new_list bad-ticket)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-abc" "${TODAY}" "${FUTURE}"
run_validator "${L}"
assert_exit "a malformed ticket fails" 1
assert_out_contains "the malformed-ticket error names the value" "PROF-abc"

# --- review dates: expiry fails, renewal is a decision ---

L=$(new_list expired)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "${PAST}" "${PAST}"
run_validator "${L}"
assert_exit "an expired review_by fails" 1
assert_out_contains "the expired error tells how to fix it" "delete this line, or renew review_by"

L=$(new_list due-today)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "${TODAY}" "${TODAY}"
run_validator "${L}"
assert_exit "a review_by equal to today fails (CI fails on and after this date)" 1
assert_out_contains "the due-today error tells how to fix it" "delete this line, or renew review_by"

L=$(new_list far-future)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "${TODAY}" "${FAR_FUTURE}"
run_validator "${L}"
assert_exit "a review_by more than 120 days out fails" 1
assert_out_contains "the far-future error names the window" "not a review date"

L=$(new_list max-window)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "${TODAY}" "${MAX_DAY}"
run_validator "${L}"
assert_exit "a review_by exactly QUARANTINE_MAX_REVIEW_DAYS days out validates" 0

L=$(new_list max-window-plus-1)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "${TODAY}" "${MAX_DAY_PLUS_1}"
run_validator "${L}"
assert_exit "a review_by one day past the window fails" 1
assert_out_contains "the over-window error names the window" "not a review date"

L=$(new_list bad-date)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "2026-02-30" "${FUTURE}"
run_validator "${L}"
assert_exit "an impossible calendar date fails" 1
assert_out_contains "the impossible-date error names the field" "added '2026-02-30'"

# --- scenario tokens ---

L=$(new_list bad-scenario)
add "${L}" "glibc-x64-openj9-jdk25/tracer+profiler" "PROF-16618" "${TODAY}" "${FUTURE}"
run_validator "${L}"
assert_exit "the ticket prose's 'tracer+profiler' token is rejected" 1
assert_out_contains "the scenario error names both accepted tokens" "profiler-only tracer-profiler"

# --- cell globs must match the known matrix ---

L=$(new_list bad-glob)
add "${L}" "glibc-x64-foo-jdk99/profiler-only" "PROF-16618" "${TODAY}" "${FUTURE}"
run_validator "${L}"
assert_exit "a glob matching no known cell fails" 1
assert_out_contains "the glob error explains the cell shape" "matches no known matrix cell"

L=$(new_list runner-tag-glob)
add "${L}" "glibc-*/profiler-only" "PROF-16618" "${TODAY}" "${FUTURE}"
run_validator "${L}"
assert_exit "a wide but real glob validates" 0

# --- shadowing: duplicates and overlaps never validate ---

L=$(new_list duplicate)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "${TODAY}" "${FUTURE}"
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-99999" "${TODAY}" "${FUTURE}"
run_validator "${L}"
assert_exit "an exact duplicate id fails" 1
assert_out_contains "the duplicate error names the first line" "already quarantined on line 1"

L=$(new_list overlap)
add "${L}" "*-openj9-jdk25/profiler-only" "PROF-16618" "${TODAY}" "${FUTURE}"
add "${L}" "glibc-x64-openj9-jdk25/tracer-profiler" "PROF-16618" "${TODAY}" "${FUTURE}"
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16014" "${TODAY}" "${FUTURE}"
run_validator "${L}"
assert_exit "overlapping globs for one scenario fail" 1
assert_out_contains "the overlap error names both entries" "overlaps"

# --- different scenarios on the same cell do not overlap ---

L=$(new_list both-scenarios)
add "${L}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "${TODAY}" "${FUTURE}"
add "${L}" "glibc-x64-openj9-jdk25/tracer-profiler" "PROF-16618" "${TODAY}" "${FUTURE}"
run_validator "${L}"
assert_exit "the two scenarios of one cell can be quarantined independently" 0

exit "${FAILED}"
