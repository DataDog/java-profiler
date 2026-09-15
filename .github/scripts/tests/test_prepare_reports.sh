#!/usr/bin/env bash
# Hermetic checks for prepare_reports.sh's artifact staging.
#
# The one thing that must never happen quietly: shipping a test-reports
# artifact with no JUnit XML in it, which is what made every failed job render
# "No detailed failure information available".
set -uo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)
SCRIPT="$ROOT/.github/scripts/prepare_reports.sh"
TESTS=0
TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT

pass() { TESTS=$((TESTS + 1)); echo "  ok: $1"; }
fail() { echo "FAIL: $1" >&2; exit 1; }

write_xml() {
  mkdir -p "$1"
  cat > "$1/TEST-com.dd.Some.xml" <<'EOS'
<?xml version="1.0" encoding="UTF-8"?>
<testsuite name="com.dd.Some" tests="1" failures="0">
  <testcase name="passes()" classname="com.dd.Some"/>
</testsuite>
EOS
}

echo "== prepare_reports.sh stages JUnit XML =="

# snapshot() creates attempt-<n> with mkdir -p *before* the copy that may fail,
# so an empty or partial snapshot must still fall back to build/test-results.
CASE="$TEMP_DIR/case-empty-snapshot"
mkdir -p "$CASE/flake-evidence/attempt-1" "$CASE/build/logs"
write_xml "$CASE/ddprof-test/build/test-results/testDebug"
( cd "$CASE" && "$SCRIPT" >/dev/null 2>&1 )
[ -n "$(find "$CASE/test-reports" -name 'TEST-*.xml' 2>/dev/null | head -1)" ] \
  || fail "an empty attempt-* snapshot must still ship build/test-results, found none in test-reports"
pass "an empty snapshot falls back to build/test-results"

# With real evidence in flake-evidence there is nothing to fall back to: the
# snapshot already holds what build/test-results holds.
CASE="$TEMP_DIR/case-real-snapshot"
mkdir -p "$CASE/build/logs"
write_xml "$CASE/flake-evidence/attempt-1"
write_xml "$CASE/ddprof-test/build/test-results/testDebug"
( cd "$CASE" && "$SCRIPT" >/dev/null 2>&1 )
[ -n "$(find "$CASE/test-reports" -name 'TEST-*.xml' 2>/dev/null | head -1)" ] \
  || fail "a populated snapshot must still reach the artifact"
pass "a populated snapshot is shipped as-is"

echo
echo "All $TESTS prepare-reports tests passed."
