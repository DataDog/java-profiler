#! /bin/sh

set -e

uname -a

export KEEP_JFRS=true
export TEST_COMMIT="${1}"
export TEST_CONFIGURATION="${2}"
export LIBRARY="musl"
export CONFIG="${3}"
export JAVA_HOME="${4}"
export JAVA_TEST_HOME="${5}"

export PATH="${JAVA_HOME}/bin":${PATH}

# due to env hell in GHA containers, we need to re-do the logic from Extract Versions here
JAVA_VERSION=$("${JAVA_TEST_HOME}/bin/java" -version 2>&1 | awk -F '"' '/version/ {
  split($2, v, "[._]");
  if (v[1] == "1") {
    # Java 8 or older: Include major, minor, and update
    printf "%s.%s.%s\n", v[2], v[3], v[4]
  } else {
    # Java 9 or newer: Major, minor, and patch
    printf "%s.%s.%s\n", v[1], v[2], v[3]
  }
}')
export JAVA_VERSION

apk update && apk add curl moreutils wget hexdump linux-headers bash make g++ clang git cppcheck jq cmake gtest-dev gmock tar >/dev/null

./gradlew -PCI -PkeepJFRs :ddprof-test:test${CONFIG} --no-daemon --parallel --build-cache --no-watch-fs