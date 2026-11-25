#! /bin/bash

# Copyright 2026, Datadog, Inc

# Hermetic tests for newest_jfr() in .gitlab/dd-trace-integration/run-integration-test.sh.
# Run with: bash .gitlab/dd-trace-integration/tests/newest_jfr_test.sh
#
# newest_jfr is extracted with sed and eval'd: the script body runs on execution.
# Pinned: newest snapshot wins (subdirectories included); an empty or missing
# directory yields an empty result without failing a set -e caller.

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

# A missing directory must not error the caller out via set -e + pipefail.
[ -z "$(newest_jfr "${WORK}/does-not-exist")" ] || fail "newest_jfr should return empty for a missing directory"
# A fresh bash process: errexit is ignored inside a substitution on the left
# of ||, so the check must run where set -e is in force.
REACHED=$(bash -c 'set -euo pipefail; eval "$1"; x=$(newest_jfr "$2"); echo reached' \
          _ "${NEWEST_JFR_DEF}" "${WORK}/does-not-exist" 2>/dev/null || true)
[ "${REACHED}" = "reached" ] || fail "newest_jfr must not abort a set -e caller on a missing directory"
pass "a missing directory yields an empty result and does not abort a set -e caller"

# Snapshots in a subdirectory are found, and the newest across levels wins.
N="${WORK}/nested"
mkdir -p "${N}/sub"
echo old > "${N}/top.jfr"
echo new > "${N}/sub/deep.jfr"
touch -t 202601010000 "${N}/top.jfr"
touch -t 202601010100 "${N}/sub/deep.jfr"
[ "$(newest_jfr "$N")" = "${N}/sub/deep.jfr" ] \
  || fail "newest_jfr should search subdirectories, got: $(newest_jfr "$N")"
pass "a snapshot in a subdirectory is found"

# A newer non-.jfr file must not win: the -name filter selects snapshots only.
F="${WORK}/filtered"
mkdir -p "${F}"
echo jfr > "${F}/recording.jfr"
echo txt > "${F}/newer.log"
touch -t 202601010000 "${F}/recording.jfr"
touch -t 202601010900 "${F}/newer.log"
[ "$(newest_jfr "$F")" = "${F}/recording.jfr" ] \
  || fail "newest_jfr should ignore newer non-.jfr files, got: $(newest_jfr "$F")"
pass "a newer non-.jfr file is ignored"

# A newer directory named *.jfr must not win: only regular files count.
D2="${WORK}/dirjfr"
mkdir -p "${D2}/plain" "${D2}/fake.jfr"
echo jfr > "${D2}/plain/recording.jfr"
touch -t 202601010000 "${D2}/plain/recording.jfr"
touch -t 202601011000 "${D2}/fake.jfr"
[ "$(newest_jfr "$D2")" = "${D2}/plain/recording.jfr" ] \
  || fail "newest_jfr should ignore directories named *.jfr, got: $(newest_jfr "$D2")"
pass "a directory named *.jfr is ignored"

# The scenario call sites must keep selecting through newest_jfr and keep
# guarding the empty result: a regression that switches a scenario to
# directory order or drops the not-found branch must fail here.
for call in SCENARIO1_JFR SCENARIO2_JFR; do
  grep -qF "${call}=\$(newest_jfr " "${SCRIPT}" \
    || fail "${call} must be selected through newest_jfr in run-integration-test.sh"
  grep -qF "if [ -z \"\${${call}}\" ] || [ ! -f \"\${${call}}\" ]" "${SCRIPT}" \
    || fail "${call} must keep its empty-or-missing guard in run-integration-test.sh"
done
pass "both scenario call sites select through newest_jfr with the not-found guard"

[ "${FAILED}" -eq 0 ] || exit 1
echo "All newest_jfr tests passed."
