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

# Remove corrupt JARs from Gradle caches (non-ZIP content from failed/proxied downloads)
# JARs not starting with PK magic bytes are invalid and must be deleted before Gradle reads them
for cache_dir in .gradle ~/.gradle; do
  if [ -d "$cache_dir" ]; then
    find "$cache_dir" -name "*.jar" | while IFS= read -r jar; do
      magic=$(head -c 2 "$jar" 2>/dev/null | od -A n -t x1 | tr -d ' \n')
      if [ "$magic" != "504b" ]; then
        echo "WARN: removing corrupt JAR (magic=${magic:-empty}): $jar"
        rm -f "$jar"
      fi
    done
  fi
done

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
./gradlew -Pddprof_version="$(get_version)" -Pskip-cpp-tests :ddprof-lib:assembleReleaseJar --no-build-cache --stacktrace --info --no-watch-fs --no-daemon

mkdir -p "${REPO_ROOT}/libs"
cp -r "${REPO_ROOT}/ddprof-lib/build/native/release/META-INF/native-libs/"* "${REPO_ROOT}/libs/"
