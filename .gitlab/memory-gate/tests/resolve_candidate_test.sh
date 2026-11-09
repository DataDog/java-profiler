#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.
#
# Tests for .gitlab/memory-gate/resolve-candidate.sh on sample snapshot metadata.
# Run with: bash .gitlab/memory-gate/tests/resolve_candidate_test.sh
set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT="${HERE}/../resolve-candidate.sh"
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
FAILED=0

pass() { echo "PASS: $1"; }
fail() { echo "FAIL: $1"; FAILED=1; }

# Sample maven-metadata.xml: two builds, the newer one listed last, each with a
# debug and a sources classifier besides the main jar.
metadata() {
  cat <<EOF
<metadata><versioning><snapshotVersions>
<snapshotVersion><classifier>debug</classifier><extension>jar</extension><value>$1-20261108.090000-1</value></snapshotVersion>
<snapshotVersion><extension>jar</extension><value>$1-20261108.090000-1</value></snapshotVersion>
<snapshotVersion><classifier>debug</classifier><extension>jar</extension><value>$1-20261109.101500-2</value></snapshotVersion>
<snapshotVersion><extension>jar</extension><value>$1-20261109.101500-2</value></snapshotVersion>
<snapshotVersion><extension>pom</extension><value>$1-20261109.101500-2</value></snapshotVersion>
<snapshotVersion><classifier>sources</classifier><extension>jar</extension><value>$1-20261109.101500-2</value></snapshotVersion>
</snapshotVersions></versioning></metadata>
EOF
}

echo "com.datadoghq:ddprof:1.54.0-my_branch-SNAPSHOT" > "$TMP/version.txt"
metadata 1.54.0-my_branch > "$TMP/metadata.xml"
if bash "$SCRIPT" "$TMP/version.txt" "$TMP/out.env" "$TMP/metadata.xml" >/dev/null &&
   [ "$(cat "$TMP/out.env")" = "MEMORY_GATE_CANDIDATE=snapshot:1.54.0-my_branch-20261109.101500-2" ]; then
  pass "pins the newest timestamped main-jar build"
else
  fail "pins the newest timestamped main-jar build (got: $(cat "$TMP/out.env" 2>/dev/null))"
fi

echo "com.datadoghq:ddprof:1.54.0" > "$TMP/release.txt"
if bash "$SCRIPT" "$TMP/release.txt" "$TMP/release.env" "$TMP/metadata.xml" 2>/dev/null; then
  fail "rejects a release version"
else
  pass "rejects a release version"
fi

metadata 1.54.0-other_branch > "$TMP/other.xml"
if bash "$SCRIPT" "$TMP/version.txt" "$TMP/other.env" "$TMP/other.xml" 2>/dev/null; then
  fail "rejects metadata of another version"
else
  pass "rejects metadata of another version"
fi

echo "<metadata><versioning><snapshotVersions></snapshotVersions></versioning></metadata>" > "$TMP/empty.xml"
if bash "$SCRIPT" "$TMP/version.txt" "$TMP/empty.env" "$TMP/empty.xml" 2>/dev/null; then
  fail "rejects metadata without a main jar"
else
  pass "rejects metadata without a main jar"
fi

exit $FAILED
