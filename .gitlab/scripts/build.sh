#! /bin/bash

set -eo pipefail  # exit on any failure, including mid-pipeline
set -x

if [ ! -z "${CANCELLED:-}" ]; then
  exit 0
fi

if [ -z "$TARGET" ]; then
  echo "Expecting the TARGET variable to be set"
  exit 1
fi

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
REPO_ROOT=$( cd "${HERE}/../.." && pwd )

if [ -z "${JAVA_HOME}" ]; then
  # workaround for CI when JAVA_HOME is not properly defined
  export JAVA_HOME=~/.sdkman/candidates/java/current
fi

echo "Using Java @ ${JAVA_HOME}"

source .gitlab/scripts/includes.sh

# Remove any zero-byte or corrupt JARs from the Gradle cache (can result from partial downloads)
find .gradle -name "*.jar" -size 0 -delete 2>/dev/null || true

function onexit {
  mkdir -p "${REPO_ROOT}/test/${TARGET}/reports"
  mkdir -p "${REPO_ROOT}/test/${TARGET}/logs"
  mv "${REPO_ROOT}/ddprof-test/build/reports" "${REPO_ROOT}/test/${TARGET}/" 2>/dev/null || true
  mv /tmp/*.jfr "${REPO_ROOT}/test/${TARGET}/logs" 2>/dev/null || true
  mv /tmp/*.json "${REPO_ROOT}/test/${TARGET}/logs" 2>/dev/null || true
  mv /tmp/*.txt "${REPO_ROOT}/test/${TARGET}/logs" 2>/dev/null || true
  find . -name 'hs_err*' | xargs -I {} cp {} "${REPO_ROOT}/test/${TARGET}/logs" 2>/dev/null || true
}

trap onexit EXIT

set -x
./gradlew -Pddprof_version="$(get_version)" -Pskip-cpp-tests :ddprof-lib:assembleReleaseJar --build-cache --stacktrace --info --no-watch-fs --no-daemon

mkdir -p "${REPO_ROOT}/libs"
cp -r "${REPO_ROOT}/ddprof-lib/build/native/release/META-INF/native-libs/"* "${REPO_ROOT}/libs/"
