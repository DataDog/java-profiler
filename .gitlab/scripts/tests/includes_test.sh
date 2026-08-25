#! /bin/bash
# Minimal, dependency-free unit tests for .gitlab/scripts/includes.sh helpers.
# Run with: bash .gitlab/scripts/tests/includes_test.sh

set -eo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source "${HERE}/../includes.sh"

FAILED=0

assert_true() {
  local desc="$1"
  shift
  if "$@"; then
    echo "PASS: ${desc}"
  else
    echo "FAIL: ${desc} — expected success"
    FAILED=1
  fi
}

assert_false() {
  local desc="$1"
  shift
  if "$@"; then
    echo "FAIL: ${desc} — expected failure"
    FAILED=1
  else
    echo "PASS: ${desc}"
  fi
}

# A freshly published snapshot version differs from the pre-publish baseline
# and must be accepted.
assert_true "differing candidate is accepted as new" \
  is_new_snapshot_version "20260101.120000-5" "20260101.100000-3"

# The metadata still pointing at the pre-publish baseline is stale and must
# be rejected — this is the guard the retry loop in deploy.sh relies on.
assert_false "candidate matching baseline is rejected as stale" \
  is_new_snapshot_version "20260101.100000-3" "20260101.100000-3"

# An empty candidate (metadata not resolvable yet) must be rejected
# regardless of the baseline.
assert_false "empty candidate is rejected" \
  is_new_snapshot_version "" "20260101.100000-3"

# An empty baseline (no prior publish) plus any non-empty candidate must be
# accepted.
assert_true "non-empty candidate with empty baseline is accepted" \
  is_new_snapshot_version "20260101.120000-5" ""

exit "${FAILED}"
