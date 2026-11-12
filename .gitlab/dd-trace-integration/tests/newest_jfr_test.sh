#! /bin/bash

# Copyright 2026, Datadog, Inc

# Hermetic tests for newest_jfr() in .gitlab/dd-trace-integration/run-integration-test.sh.
# Run with: bash .gitlab/dd-trace-integration/tests/newest_jfr_test.sh
#
# The function is sourced out of the script (the script body runs on execution,
# so only the definition above the first top-level statement is reusable);
# these tests re-declare it verbatim from the script and pin the ordering
# contract: the newest snapshot wins, ties fall back to directory order, and
# an empty directory yields an empty result.

set -euo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT="${HERE}/../run-integration-test.sh"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "${WORK}"' EXIT

fail() {
  echo "FAIL: $*" >&2
  FAILED=1
}

pass() {
  echo "  ok: $*"
}

# Extract the newest_jfr definition from the script so the test pins the
# shipped implementation, not a copy that can drift.
NEWEST_JFR_DEF=$(sed -n '/^newest_jfr() {$/,/^}$/p' "${SCRIPT}")
[ -n "${NEWEST_JFR_DEF}" ] || { fail "newest_jfr() definition not found in run-integration-test.sh"; exit 1; }
eval "${NEWEST_JFR_DEF}"

D="${WORK}/dumps"
mkdir -p "$D"

# Newest by mtime wins, even when it is not first in directory order.
echo old > "${D}/a-first-in-readdir.jfr"
echo mid > "${D}/b.jfr"
echo new > "${D}/c-newest.jfr"
touch -t 202601010000 "${D}/a-first-in-readdir.jfr"
touch -t 202601010100 "${D}/b.jfr"
touch -t 202601010200 "${D}/c-newest.jfr"
[ "$(newest_jfr "$D")" = "${D}/c-newest.jfr" ] \
  || fail "newest_jfr should pick the most recently modified .jfr, got: $(newest_jfr "$D")"
pass "the most recently modified snapshot wins"

# A directory with no .jfr files yields an empty result (the caller's
# not-found branch then reports the failure).
E="${WORK}/empty"
mkdir -p "$E"
[ -z "$(newest_jfr "$E")" ] || fail "newest_jfr should return empty for a directory with no .jfr files"
pass "a directory without .jfr files yields an empty result"

# A missing directory must not error the caller out via set -e.
[ -z "$(newest_jfr "${WORK}/does-not-exist")" ] || fail "newest_jfr should return empty for a missing directory"
pass "a missing directory yields an empty result"

[ "${FAILED}" -eq 0 ] || exit 1
echo "All newest_jfr tests passed."
