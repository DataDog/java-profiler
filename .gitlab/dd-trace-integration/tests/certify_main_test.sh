#! /bin/bash
# Minimal, dependency-free unit tests for .gitlab/dd-trace-integration/certify-main.sh.
# Run with: bash .gitlab/dd-trace-integration/tests/certify_main_test.sh
#
# The job must fail closed on incomplete results and must always validate the
# checked-in quarantine list: QUARANTINE_LIST is a test hook in
# validate-quarantine.sh and post-pr-comment.sh, so a project- or group-level
# CI/CD variable with that name would reach genuine push pipelines and let it
# quarantine every failing cell. certify-main.sh therefore unsets it before
# calling the gate scripts.

set -eo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT="${HERE}/../certify-main.sh"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "${WORK}"' EXIT

# The injected content is a malformed entry on purpose: whatever the injected
# list contains, the validator's report must name the checked-in path, never
# this file.
: > "${WORK}/attacker-quarantine.txt"
printf '%s\n' 'glibc-*-jdk25/profiler-only' > "${WORK}/attacker-quarantine.txt"

SHA=$(git -C "$HERE" rev-parse HEAD)
printf '%s\n' "${SHA}" > "${WORK}/ddprof-commit-sha.txt"

# The job runs with the pipeline workdir as its cwd: the prepared-SHA artifact
# and the results directory are read relative to it, so the sandbox must be
# the cwd while certify-main.sh still resolves its own scripts via BASH_SOURCE.
cd "${WORK}"

# Freeze the clock like the sibling suites, but to UTC today, not a fixed date:
# production validates against TZ=UTC, and the live checked-in list is
# validated against it, so a fixed date would start failing once a real
# entry's review_by falls behind it.
FROZEN_DATE="$(TZ=UTC command date '+%Y-%m-%d')"
date() {
  if [ "$#" -eq 1 ] && [ "$1" = '+%Y-%m-%d' ]; then
    printf '%s\n' "${FROZEN_DATE}"
  else
    command date "$@"
  fi
}
export -f date
export FROZEN_DATE

expect_fail() {
  local label="$1"
  shift
  if "$@" > "${WORK}/stdout.log" 2> "${WORK}/stderr.log"; then
    echo "FAIL: ${label}: expected nonzero exit, got success"
    FAILED=1
    return 0
  fi
  return 0
}

assert_output() {
  local label="$1" needle="$2"
  shift 2
  if ! grep -qF -- "${needle}" "$@"; then
    echo "FAIL: ${label}: output does not contain '${needle}'"
    cat "$@"
    FAILED=1
  fi
}

# Empty results directory: the run must fail closed.
mkdir -p "${WORK}/integration-test-results"

expect_fail "incomplete results fail closed" \
  env CI_PIPELINE_SOURCE=push CI_COMMIT_BRANCH=main CI_COMMIT_SHA="${SHA}" \
      QUARANTINE_LIST="${WORK}/attacker-quarantine.txt" \
  bash "${SCRIPT}"
assert_output "the checked-in list is validated, not the override" \
  "/quarantine.txt" "${WORK}/stdout.log" "${WORK}/stderr.log"
if grep -qF "attacker-quarantine.txt" "${WORK}/stdout.log" "${WORK}/stderr.log"; then
  echo "FAIL: attacker-supplied QUARANTINE_LIST reached the gate scripts"
  FAILED=1
fi

# The precondition guards stay intact: a spoofed non-push pipeline fails.
expect_fail "non-push pipeline source fails closed" \
  env CI_PIPELINE_SOURCE=web CI_COMMIT_BRANCH=main CI_COMMIT_SHA="${SHA}" \
      QUARANTINE_LIST="${WORK}/attacker-quarantine.txt" \
  bash "${SCRIPT}"
assert_output "non-push source is rejected" \
  "requires a main push pipeline" "${WORK}/stderr.log"

if [ "${FAILED}" -ne 0 ]; then
  echo "certify_main_test.sh: FAILED"
  exit 1
fi
echo "certify_main_test.sh: OK"
