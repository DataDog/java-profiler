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

# Writes one config directory whose two validation logs say pass or fail.
write_config() {
  local dir="$1" config="$2" outcome="$3"
  local marker="SUCCESS:"
  [ "${outcome}" = "fail" ] && marker="VALIDATION_FAILED"
  mkdir -p "${dir}/${config}"
  echo "${marker} whatever" > "${dir}/${config}/profiler-only-${config}.log"
  echo "${marker} whatever" > "${dir}/${config}/tracer-profiler-${config}.log"
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
run_script() {
  local dir="$1"
  BODY="${WORK}/body.md"
  : > "${BODY}"
  SCRIPT_EXIT=0
  COMMENT_BODY_FILE="${BODY}" "${BASH}" "${SCRIPT}" "${dir}" > "${WORK}/log.txt" 2>&1 || SCRIPT_EXIT=$?
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

exit "${FAILED}"
