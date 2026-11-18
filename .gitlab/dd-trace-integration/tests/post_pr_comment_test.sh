#! /bin/bash
# Copyright 2026, Datadog, Inc.
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
  musl-x64-hotspot musl-arm64-hotspot
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
assert_body_contains "it reports every configuration as passed" "All 30 integration tests passed"

assert_body_contains "the skipped configurations are counted separately" "**10 not applicable (not scheduled)**"
assert_body_contains "the reason names the upstream runtime constraint" "OpenJ9 requires glibc; upstream publishes no musl runtime."

# Missing applicable cells still gate, even on musl.

build_matrix "${WORK}/one-missing" "omit:musl-arm64-hotspot-jdk25"
run_script "${WORK}/one-missing"
assert_exit "a missing cell fails the pipeline" 1
assert_body_contains "the headline counts the passes" "**29** passed"
assert_body_contains "the headline counts zero failures" "**0** failed"
assert_body_contains "the headline counts the cell with no result" "**1** without a result"
assert_body_contains "the headline denominator is the expected matrix" "out of **30** expected configurations"
assert_body_contains "the missing cell is named" "musl-arm64-hotspot-jdk25"

# --- an ordinary validation failure keeps the headline terse ---

build_matrix "${WORK}/one-fail" "fail:glibc-x64-hotspot-jdk11"
run_script "${WORK}/one-fail"
assert_exit "a validation failure fails the pipeline" 1
assert_body_contains "the headline counts the failure" "**1** failed"
assert_body_contains "the denominator is still the expected matrix" "out of **30** expected configurations"
assert_body_lacks "no incomplete clause when nothing is missing" "without a result"
assert_body_contains "the failure summary still separates not-applicable cells" "**10 not applicable (not scheduled)**"
for arch in x64 arm64; do
  assert_body_contains "${arch} musl/OpenJ9 row is entirely N/A" "| musl-${arch}-openj9 | N/A | N/A | N/A | N/A | N/A |"
done

# Old not-applicable artifacts count as neither coverage nor failures.
for outcome in pass fail; do
  build_matrix "${WORK}/stale-${outcome}"
  for arch in x64 arm64; do
    for jdk in "${JDKS[@]}"; do
      write_config "${WORK}/stale-${outcome}" "musl-${arch}-openj9-jdk${jdk}" "${outcome}"
    done
  done
  run_script "${WORK}/stale-${outcome}"
  assert_exit "stale N/A ${outcome} logs do not gate" 0
  assert_body_contains "stale N/A ${outcome} logs are not counted as coverage" "All 30 integration tests passed"
  assert_body_contains "stale N/A ${outcome} logs stay not applicable" "**10 not applicable (not scheduled)**"
done

# Both sides of the applicability boundary retain failure and completeness gates.
for config in glibc-x64-openj9-jdk8 musl-x64-hotspot-jdk8; do
  build_matrix "${WORK}/missing-${config}" "omit:${config}"
  run_script "${WORK}/missing-${config}"
  assert_exit "missing ${config} still fails" 1
  assert_body_contains "missing ${config} is named" "${config}"
  assert_body_contains "missing ${config} is counted" "**1** without a result"
  build_matrix "${WORK}/failed-${config}" "fail:${config}"
  run_script "${WORK}/failed-${config}"
  assert_exit "failed ${config} still fails" 1
  assert_body_contains "failed ${config} is counted" "**1** failed"
done

build_matrix "${WORK}/unreadable"
config=glibc-arm64-openj9-jdk21
rm "${WORK}/unreadable/${config}"/*.log
run_script "${WORK}/unreadable"
assert_exit "a present directory with no logs still fails" 1
assert_body_contains "a present directory with no logs is named" "${config}"
assert_body_contains "a present directory with no logs is incomplete" "**1** without a result"

mkdir -p "${WORK}/only-not-applicable"
for arch in x64 arm64; do
  for jdk in "${JDKS[@]}"; do
    write_config "${WORK}/only-not-applicable" "musl-${arch}-openj9-jdk${jdk}" pass
  done
done
run_script "${WORK}/only-not-applicable"
assert_exit "only N/A artifacts cannot count as a passing run" 1
assert_body_contains "only N/A artifacts leave applicable configurations without results" "No applicable configuration"
assert_body_contains "only N/A artifacts retain the not-scheduled count" "**10 not applicable (not scheduled)**"

# --- nothing ran at all ---

mkdir -p "${WORK}/empty"
run_script "${WORK}/empty"
assert_exit "an empty results directory fails the pipeline" 1
assert_body_contains "an empty matrix says the tests could not run" "no results were produced"
assert_body_contains "an empty matrix still names the N/A reason" "OpenJ9 requires glibc; upstream publishes no musl runtime."

exit "${FAILED}"
