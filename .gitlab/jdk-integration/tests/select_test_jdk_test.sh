#! /bin/bash
# Minimal, dependency-free unit tests for .gitlab/jdk-integration/select_test_jdk.sh.
# Run with: bash .gitlab/jdk-integration/tests/select_test_jdk_test.sh
#
# The selector is exercised against fake /usr/lib/jvm-style trees built in a
# temp dir, so no real JDK and no image access is needed.

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT_UNDER_TEST="${HERE}/../select_test_jdk.sh"

FAILED=0
WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT

fail() { echo "FAIL: $*"; FAILED=1; }
pass() { echo "PASS: $*"; }

# Builds a fake JDK home: only an executable bin/java is needed — the selector
# locates JDKs by that file and never runs java itself.
make_jdk() {
  local home="$1"
  mkdir -p "${home}/bin"
  printf '#!/bin/sh\n' > "${home}/bin/java"
  chmod +x "${home}/bin/java"
}

# A single JDK under the root is selected unconditionally.
make_jdk "${WORK}/root/jdk-21.0.5"
out=$("$SCRIPT_UNDER_TEST" "${WORK}/root" 2>&1)
rc=$?
if [ "${rc}" -eq 0 ] && [ "${out}" = "${WORK}/root/jdk-21.0.5" ]; then
  pass "single JDK is selected"
else
  fail "single JDK is selected (rc=${rc}, out=${out})"
fi

# With several JDKs, the one whose path carries JDK_VERSION wins.
make_jdk "${WORK}/root2/jdk-11.0.28"
make_jdk "${WORK}/root2/jdk-25.0.1"
out=$(JDK_VERSION=25.0.1 "$SCRIPT_UNDER_TEST" "${WORK}/root2" 2>&1)
rc=$?
if [ "${rc}" -eq 0 ] && [ "${out}" = "${WORK}/root2/jdk-25.0.1" ]; then
  pass "JDK_VERSION match wins among several JDKs"
else
  fail "JDK_VERSION match wins among several JDKs (rc=${rc}, out=${out})"
fi

# Non-executable bin/java (e.g. a half-installed JVM) is not a candidate.
rm -f "${WORK}/root2/jdk-25.0.1/bin/java"
out=$(JDK_VERSION=25.0.1 "$SCRIPT_UNDER_TEST" "${WORK}/root2" 2>&1)
rc=$?
if [ "${rc}" -eq 0 ] && [ "${out}" = "${WORK}/root2/jdk-11.0.28" ]; then
  pass "non-executable bin/java is skipped, sole remaining JDK selected"
else
  fail "non-executable bin/java is skipped (rc=${rc}, out=${out})"
fi

# Several JDKs with no JDK_VERSION match must fail loudly instead of
# silently testing the wrong JDK — this is the guard the CI job relies on.
make_jdk "${WORK}/root2/jdk-25.0.1"
out=$(JDK_VERSION=17 "$SCRIPT_UNDER_TEST" "${WORK}/root2" 2>&1)
rc=$?
if [ "${rc}" -ne 0 ]; then
  pass "no JDK_VERSION match among several JDKs fails"
else
  fail "no JDK_VERSION match among several JDKs fails (out=${out})"
fi

# Several JDKs with JDK_VERSION unset must fail too: the job always sets it,
# but an empty value must never silently pick an arbitrary candidate.
out=$("$SCRIPT_UNDER_TEST" "${WORK}/root2" 2>&1)
rc=$?
if [ "${rc}" -ne 0 ]; then
  pass "several JDKs with JDK_VERSION unset fail"
else
  fail "several JDKs with JDK_VERSION unset fail (out=${out})"
fi

# An empty root (no JDK at all) fails rather than printing an empty home.
mkdir -p "${WORK}/empty"
out=$("$SCRIPT_UNDER_TEST" "${WORK}/empty" 2>&1)
rc=$?
if [ "${rc}" -ne 0 ]; then
  pass "empty search root fails"
else
  fail "empty search root fails (out=${out})"
fi

# Wiring of the CI job: the selector result must be exported as
# JAVA_TEST_HOME (the variable PlatformUtils.testJavaHome() reads), the dead
# TEST_JAVA_HOME spelling must stay out, and the job must echo both resolved
# JVM versions so the selected JDK is visible in the job log.
YML="${HERE}/../.gitlab-ci.yml"
if grep -q 'export JAVA_TEST_HOME="\$(\.gitlab/jdk-integration/select_test_jdk\.sh)"' "${YML}"; then
  pass "job exports JAVA_TEST_HOME from the selector"
else
  fail "job exports JAVA_TEST_HOME from the selector"
fi
if grep -q 'TEST_JAVA_HOME' "${YML}"; then
  fail "dead TEST_JAVA_HOME variable removed from the job"
else
  pass "dead TEST_JAVA_HOME variable removed from the job"
fi
if grep -q '"\${JAVA_TEST_HOME}/bin/java" -version' "${YML}"; then
  pass "job logs the test JVM version"
else
  fail "job logs the test JVM version"
fi
if grep -q 'export JAVA_HOME=/root/.sdkman/candidates/java/21.0.3-tem' "${YML}"; then
  pass "build JDK (Gradle) is a 17+ sdkman install"
else
  fail "build JDK (Gradle) is a 17+ sdkman install"
fi

exit "${FAILED}"
