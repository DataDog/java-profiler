#! /bin/bash
# Minimal, dependency-free unit tests for the summary that
# .gitlab/dd-trace-integration/post-pr-comment.sh posts.
# Run with: bash .gitlab/dd-trace-integration/tests/post_pr_comment_test.sh
#
# The script reads a results directory and renders a comment; these tests build
# that directory, capture the rendered body through COMMENT_BODY_FILE, and
# assert on the headline counts and the exit status. Posting is left to fail on
# its own (no token in a test environment), which the script already tolerates.

set -eo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT="${HERE}/../post-pr-comment.sh"

# The matrix the script expects, mirrored here so a test can build a full one.
PLATFORMS=(
  glibc-x64-hotspot glibc-x64-openj9 glibc-arm64-hotspot glibc-arm64-openj9
  musl-x64-hotspot musl-x64-openj9 musl-arm64-hotspot musl-arm64-openj9
)
JDKS=(8 11 17 21 25)

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "${WORK}"' EXIT

# The gate reads the list through QUARANTINE_LIST; each run points at an empty
# list unless a test builds its own.
: > "${WORK}/empty-quarantine.txt"

# Freeze the clock for this suite and every child script: the fixtures below
# pin added 2026-11-12 and review_by 2027-02-10, so a real wall-clock read
# past that date would expire them; keep FROZEN_DATE strictly between the two.
FROZEN_DATE="2026-11-13"
date() {
  if [ "$#" -eq 1 ] && [ "$1" = '+%Y-%m-%d' ]; then
    printf '%s\n' "${FROZEN_DATE}"
  else
    command date "$@"
  fi
}
export -f date
export FROZEN_DATE

TODAY="$(TZ=UTC date '+%Y-%m-%d')"

# The freeze must reach both this shell and the child gate process; a silent
# re-read of the real clock would fail the suite only months later.
if [ "${TODAY}" != "${FROZEN_DATE}" ] \
   || [ "$(bash -c 'TZ=UTC date "+%Y-%m-%d"')" != "${FROZEN_DATE}" ]; then
  echo "FAIL: clock freeze not in effect (parent and child must both see ${FROZEN_DATE})"
  exit 1
fi

# Writes one config directory whose two validation logs say pass or fail.
write_config() {
  local dir="$1" config="$2" outcome="$3"
  local marker="SUCCESS:"
  [ "${outcome}" = "fail" ] && marker="VALIDATION_FAILED"
  mkdir -p "${dir}/${config}"
  echo "${marker} whatever" > "${dir}/${config}/profiler-only-${config}.log"
  echo "${marker} whatever" > "${dir}/${config}/tracer-profiler-${config}.log"
}

# Per-scenario variant: outcome per scenario is pass, fail, or omit (no log
# at all - a lost job that wrote only one validation log).
write_cell() {
  local dir="$1" config="$2" s1="$3" s2="$4" scenario outcome marker
  mkdir -p "${dir}/${config}"
  for scenario in profiler-only tracer-profiler; do
    if [ "${scenario}" = "profiler-only" ]; then outcome="${s1}"; else outcome="${s2}"; fi
    [ "${outcome}" = "omit" ] && continue
    marker="SUCCESS:"
    [ "${outcome}" = "fail" ] && marker="VALIDATION_FAILED"
    echo "${marker} whatever" > "${dir}/${config}/${scenario}-${config}.log"
  done
}

# Appends a quarantine entry to a list file; empty ticket keeps the field so
# the validator's format still applies when a test wants one.
add_quarantine() {
  local file="$1" id="$2" ticket="$3" review_by="$4" reason="${5:-flake}"
  echo "${id} | ${ticket} | 2026-11-12 | ${review_by} | ${reason}" >> "${file}"
}

# Builds a full expected matrix, then applies per-config overrides:
#   omit:<config>  -> the directory is absent entirely (a lost/timed-out job)
#   fail:<config>  -> the logs report a validation failure
build_matrix() {
  local dir="$1"; shift
  local -a omit=() failing=()
  local spec
  for spec in "$@"; do
    case "${spec}" in
      omit:*) omit+=("${spec#omit:}") ;;
      fail:*) failing+=("${spec#fail:}") ;;
    esac
  done
  mkdir -p "${dir}"
  local platform jdk config skip f
  for platform in "${PLATFORMS[@]}"; do
    for jdk in "${JDKS[@]}"; do
      config="${platform}-jdk${jdk}"
      skip=0
      for f in "${omit[@]:-}"; do [ "${f}" = "${config}" ] && skip=1; done
      [ "${skip}" -eq 1 ] && continue
      local outcome="pass"
      for f in "${failing[@]:-}"; do [ "${f}" = "${config}" ] && outcome="fail"; done
      write_config "${dir}" "${config}" "${outcome}"
    done
  done
}

# Runs the script over a results dir, keeping the rendered body and exit code.
# The optional second argument is a quarantine list to inject.
run_script() {
  local dir="$1" qfile="${2:-${WORK}/empty-quarantine.txt}"
  BODY="${WORK}/body.md"
  : > "${BODY}"
  SCRIPT_EXIT=0
  QUARANTINE_LIST="${qfile}" COMMENT_BODY_FILE="${BODY}" "${BASH}" "${SCRIPT}" "${dir}" > "${WORK}/log.txt" 2>&1 || SCRIPT_EXIT=$?
}

assert_body_contains() {
  local desc="$1" needle="$2"
  if grep -qF -- "${needle}" "${BODY}"; then
    echo "PASS: ${desc}"
  else
    echo "FAIL: ${desc} — body does not contain '${needle}'"
    sed 's/^/      /' "${BODY}" | head -12
    FAILED=1
  fi
}

assert_body_lacks() {
  local desc="$1" needle="$2"
  if [ ! -s "${BODY}" ]; then
    echo "FAIL: ${desc} — no comment body was rendered, so the absence proves nothing"
    FAILED=1
    return
  fi
  if grep -qF -- "${needle}" "${BODY}"; then
    echo "FAIL: ${desc} — body unexpectedly contains '${needle}'"
    sed 's/^/      /' "${BODY}" | head -12
    FAILED=1
  else
    echo "PASS: ${desc}"
  fi
}

assert_exit() {
  local desc="$1" expected="$2"
  if [ "${SCRIPT_EXIT}" -eq "${expected}" ]; then
    echo "PASS: ${desc}"
  else
    echo "FAIL: ${desc} — expected exit ${expected}, got ${SCRIPT_EXIT}"
    sed 's/^/      /' "${WORK}/log.txt" | tail -8
    FAILED=1
  fi
}

# --- a complete, passing matrix ---

build_matrix "${WORK}/all-pass"
run_script "${WORK}/all-pass"
assert_exit "a complete passing matrix exits 0" 0
assert_body_contains "it reports every configuration as passed" "All 40 integration tests passed"

# --- one cell produced no result at all: the case this gating exists for ---
#
# The headline has to account for it. Reporting "39 passed, 0 failed out of 39"
# while failing the pipeline tells a reviewer the opposite of what happened.

build_matrix "${WORK}/one-missing" "omit:musl-arm64-openj9-jdk25"
run_script "${WORK}/one-missing"
assert_exit "a missing cell fails the pipeline" 1
assert_body_contains "the headline counts the passes" "**39** passed"
assert_body_contains "the headline counts zero failures" "**0** failed"
assert_body_contains "the headline counts the cell with no result" "**1** without a result"
assert_body_contains "the headline denominator is the expected matrix" "out of **40** expected configurations"
assert_body_contains "the missing cell is named" "musl-arm64-openj9-jdk25"

# --- an ordinary validation failure keeps the headline terse ---

build_matrix "${WORK}/one-fail" "fail:glibc-x64-hotspot-jdk11"
run_script "${WORK}/one-fail"
assert_exit "a validation failure fails the pipeline" 1
assert_body_contains "the headline counts the failure" "**1** failed"
assert_body_contains "the denominator is still the expected matrix" "out of **40** expected configurations"
assert_body_lacks "no incomplete clause when nothing is missing" "without a result"

# --- nothing ran at all ---

mkdir -p "${WORK}/empty"
run_script "${WORK}/empty"
assert_exit "an empty results directory fails the pipeline" 1
assert_body_contains "an empty matrix says the tests could not run" "no results were produced"

# --- a quarantined scenario failure does not gate ---
#
# One scenario fails with an unexpired matching entry: the cell renders as
# quarantined, the comment names ticket and expiry, and the job exits 0.

build_matrix "${WORK}/one-quarantined" "fail:glibc-x64-openj9-jdk25"
# Only the profiler-only scenario fails (and is quarantined); the cell's
# tracer-profiler scenario passes.
write_cell "${WORK}/one-quarantined" "glibc-x64-openj9-jdk25" fail pass
Q="${WORK}/q1.txt"
: > "${Q}"
add_quarantine "${Q}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "2027-02-10" "VALIDATION_FAILED on patch verification, 1 in ~5 runs"
run_script "${WORK}/one-quarantined" "${Q}"
assert_exit "a quarantined scenario failure exits 0" 0
assert_body_contains "the quarantined cell is counted in the headline" "**1** quarantined"
assert_body_contains "the headline keeps the expected denominator" "out of **40** expected configurations"
assert_body_lacks "the terse all-pass line is not used when something failed" "All 39 integration tests passed"
assert_body_contains "the quarantined cell is marked in the matrix" ":shield:"
assert_body_contains "the quarantined entry names the ticket" "PROF-16618"
assert_body_contains "the quarantined entry names the review date" "review_by 2027-02-10"
assert_body_contains "the quarantined entry names the scenario" "glibc-x64-openj9-jdk25/profiler-only"

# --- the free-text reason renders verbatim, escapes and all ---
#
# A reason carrying backslash sequences (a Windows path, a literal \c) must
# reach the comment unchanged: no escape expansion, no truncation of the
# sections that follow.

Q_ESC="${WORK}/q-esc.txt"
: > "${Q_ESC}"
add_quarantine "${Q_ESC}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "2027-02-10" 'path C:\temp logged, exit \c code'
run_script "${WORK}/one-quarantined" "${Q_ESC}"
assert_exit "a reason with backslash escapes does not change gating" 0
assert_body_contains "the reason text is rendered verbatim" 'path C:\temp logged, exit \c code'
assert_body_contains "a backslash-heavy reason does not truncate the sections after it" "### Links"

# --- one cell with both scenarios quarantined: one shield, two bullets ---

Q_BOTH="${WORK}/q-both.txt"
: > "${Q_BOTH}"
add_quarantine "${Q_BOTH}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "2027-02-10" "flake A"
add_quarantine "${Q_BOTH}" "glibc-x64-openj9-jdk25/tracer-profiler" "PROF-16618" "2027-02-10" "flake B"
build_matrix "${WORK}/both-quarantined" "fail:glibc-x64-openj9-jdk25"
run_script "${WORK}/both-quarantined" "${Q_BOTH}"
assert_exit "a cell with both scenarios quarantined exits 0" 0
assert_body_contains "the quarantined section header is present" "### Quarantined failures"
assert_body_contains "the fully quarantined cell is counted once" "**1** quarantined"
assert_body_lacks "the cell is not counted as failed" "**1** failed"
# The needle quotes the comment's literal backticks; they are data, not substitution.
# shellcheck disable=SC2016
assert_body_contains "the first scenario bullet is listed" '`glibc-x64-openj9-jdk25/profiler-only` — PROF-16618, review_by 2027-02-10, flake A'
# shellcheck disable=SC2016
assert_body_contains "the second scenario bullet is listed" '`glibc-x64-openj9-jdk25/tracer-profiler` — PROF-16618, review_by 2027-02-10, flake B'
EXPECTED_HEADER="| Platform |$(printf ' JDK %s |' "${JDKS[@]}")"
assert_body_contains "the matrix header is generated from the JDK list" "${EXPECTED_HEADER}"

# --- the same flake on the other scenario still gates ---

build_matrix "${WORK}/other-scenario" "fail:glibc-x64-openj9-jdk25"
write_cell "${WORK}/other-scenario" "glibc-x64-openj9-jdk25" pass fail
run_script "${WORK}/other-scenario" "${Q}"
assert_exit "a non-quarantined scenario failure still fails the pipeline" 1
assert_body_contains "the gating failure is marked in the matrix" ":x:"
assert_body_contains "the failure details name the failing scenario" "**Tracer+profiler:**"
assert_body_lacks "a quarantined scenario of a gating cell is not reported as excused" "### Quarantined failures"

# --- a quarantined scenario sharing a cell with a plain failure keeps its details ---
#
# Both scenarios fail: the cell gates (:x:, failure details) and the
# quarantined scenario's ticket, expiry, and reason still reach the comment.

build_matrix "${WORK}/mixed-cell" "fail:glibc-x64-openj9-jdk25"
write_cell "${WORK}/mixed-cell" "glibc-x64-openj9-jdk25" fail fail
run_script "${WORK}/mixed-cell" "${Q}"
assert_exit "a quarantined failure next to a plain failure still gates" 1
assert_body_contains "the mixed gating cell is marked in the matrix" ":x:"
assert_body_contains "the quarantined details survive the plain failure" "### Quarantined failures"
# shellcheck disable=SC2016
assert_body_contains "the quarantined entry is still listed" '`glibc-x64-openj9-jdk25/profiler-only` — PROF-16618, review_by 2027-02-10'
assert_body_contains "the plain failure details are still reported" "### Failure Details"

# --- an expired entry never excuses a failure ---

Q_EXPIRED="${WORK}/q-expired.txt"
: > "${Q_EXPIRED}"
add_quarantine "${Q_EXPIRED}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "2020-01-01" "stale entry"
run_script "${WORK}/one-quarantined" "${Q_EXPIRED}"
assert_exit "an expired quarantine gates again" 1
assert_body_contains "an expired quarantine renders the cell as failed" ":x:"
assert_body_lacks "an expired quarantine is not rendered as quarantined" ":shield:"

# --- a review_by equal to today is expired: the failure gates again ---

Q_DUE_TODAY="${WORK}/q-due-today.txt"
: > "${Q_DUE_TODAY}"
add_quarantine "${Q_DUE_TODAY}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "${TODAY}" "due today"
run_script "${WORK}/one-quarantined" "${Q_DUE_TODAY}"
assert_exit "a review_by equal to today gates again" 1
assert_body_contains "a due-today quarantine renders the cell as failed" ":x:"
assert_body_lacks "a due-today quarantine is not rendered as quarantined" ":shield:"
assert_body_lacks "a due-today quarantine has no quarantined-failures section" "### Quarantined failures"

# --- a quarantined scenario must not mask the other scenario's missing log ---
Q2="${WORK}/q2.txt"
: > "${Q2}"
add_quarantine "${Q2}" "musl-arm64-openj9-jdk25/profiler-only" "PROF-16618" "2027-02-10" "flake"
build_matrix "${WORK}/quarantined-plus-unknown" "fail:musl-arm64-openj9-jdk25"
rm "${WORK}/quarantined-plus-unknown/musl-arm64-openj9-jdk25/tracer-profiler-musl-arm64-openj9-jdk25.log"
run_script "${WORK}/quarantined-plus-unknown" "${Q2}"
assert_exit "a quarantined failure next to a missing log still fails the pipeline" 1
assert_body_contains "the missing log is still reported" "**1** without a result"
assert_body_contains "the quarantined details survive the missing log" "### Quarantined failures"
assert_body_contains "the quarantined entry survives the missing log" "PROF-16618"

# --- quarantine details survive an all-incomplete matrix ---
#
# Every job lost its logs except one cell's quarantined profiler-only log.
# TOTAL stays 0 (an unknown cell is not a quarantined result), but the
# observed quarantined failure must still render instead of the
# "no results were produced" branch; the pipeline still gates.
Q_ALLINC="${WORK}/q-all-incomplete.txt"
: > "${Q_ALLINC}"
add_quarantine "${Q_ALLINC}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "2027-02-10" "flake"
mkdir -p "${WORK}/all-incomplete/glibc-x64-openj9-jdk25"
echo "VALIDATION_FAILED whatever" > "${WORK}/all-incomplete/glibc-x64-openj9-jdk25/profiler-only-glibc-x64-openj9-jdk25.log"
run_script "${WORK}/all-incomplete" "${Q_ALLINC}"
assert_exit "an all-incomplete matrix with a quarantined failure still gates" 1
assert_body_lacks "the no-results branch is not taken over quarantine details" "no results were produced"
assert_body_contains "the quarantined section renders on an all-incomplete matrix" "### Quarantined failures"
assert_body_contains "the quarantine ticket renders on an all-incomplete matrix" "PROF-16618"

# --- a glob entry quarantines every cell it matches, and only those ---

Q4="${WORK}/q4.txt"
: > "${Q4}"
add_quarantine "${Q4}" "glibc-x64-openj9-*/profiler-only" "PROF-16618" "2027-02-10" "same flake on both jdk versions"
build_matrix "${WORK}/wildcard" "fail:glibc-x64-openj9-jdk25"
write_cell "${WORK}/wildcard" "glibc-x64-openj9-jdk25" fail pass
write_cell "${WORK}/wildcard" "glibc-x64-openj9-jdk11" pass fail
run_script "${WORK}/wildcard" "${Q4}"
assert_exit "the glob-matched cell does not gate, the unlisted failing one does" 1
assert_body_contains "the matched cell renders as quarantined" ":shield:"
assert_body_contains "the unlisted failing cell still renders as failed" ":x:"
assert_body_contains "exactly one cell is quarantined" "**1** quarantined"

# --- the gate fails closed on a list it cannot read ---

Q5="${WORK}/q5.txt"
echo "glibc-x64-openj9-jdk25profiler-only | PROF-16618 | 2026-11-12 | 2027-02-10 | malformed id" >> "${Q5}"
run_script "${WORK}/one-quarantined" "${Q5}"
assert_exit "a malformed entry never excuses a failure" 1

run_script "${WORK}/one-quarantined" "${WORK}/no-such-list.txt"
assert_exit "a missing list file never excuses a failure" 1

# --- a sub-5-field line fails closed in the gate ---

Q_SHORT="${WORK}/q-short.txt"
echo "glibc-x64-openj9-jdk25/profiler-only | PROF-16618 | 2026-11-12 | 2027-02-10" >> "${Q_SHORT}"
run_script "${WORK}/one-quarantined" "${Q_SHORT}"
assert_exit "a sub-5-field entry never excuses a failure" 1
assert_body_lacks "a sub-5-field entry is not rendered as quarantined" ":shield:"

# --- a quarantined scenario that passes renders as an ordinary pass ---

Q3="${WORK}/q3.txt"
: > "${Q3}"
add_quarantine "${Q3}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "2027-02-10" "flake that got fixed"
run_script "${WORK}/all-pass" "${Q3}"
assert_exit "a quarantined-but-passing scenario still exits 0" 0
assert_body_contains "the quarantine does not colour a passing scenario" "All 40 integration tests passed"

# --- quarantined bullets render on separate lines ---

build_matrix "${WORK}/two-quarantined" "fail:glibc-x64-openj9-jdk25" "fail:musl-arm64-openj9-jdk25"
write_cell "${WORK}/two-quarantined" "glibc-x64-openj9-jdk25" fail pass
write_cell "${WORK}/two-quarantined" "musl-arm64-openj9-jdk25" fail pass
Q6="${WORK}/q6.txt"
: > "${Q6}"
add_quarantine "${Q6}" "glibc-x64-openj9-jdk25/profiler-only" "PROF-16618" "2027-02-10" "flake one"
add_quarantine "${Q6}" "musl-arm64-openj9-jdk25/profiler-only" "PROF-16014" "2027-02-10" "flake two"
run_script "${WORK}/two-quarantined" "${Q6}"
assert_exit "two quarantined cells exit 0" 0
assert_body_contains "the first quarantined entry is named" "glibc-x64-openj9-jdk25/profiler-only"
assert_body_contains "the second quarantined entry is named" "musl-arm64-openj9-jdk25/profiler-only"
if grep -qF -- '\n' "${BODY}"; then
  printf '%s\n' "FAIL: quarantined bullets must not contain a literal \\n escape"
  sed 's/^/      /' "${BODY}" | head -12
  FAILED=1
else
  echo "PASS: quarantined bullets contain no literal escape sequence"
fi
if [ "$(grep -c '^- `' "${BODY}")" -eq 2 ]; then
  echo "PASS: both quarantined entries render as separate bullet lines"
else
  echo "FAIL: expected 2 quarantined bullet lines, got $(grep -c '^- `' "${BODY}" || true)"
  sed 's/^/      /' "${BODY}" | head -12
  FAILED=1
fi

exit "${FAILED}"
