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

if [ -z "$TEST_JDK" ]; then
  echo "Expecting the TEST_JDK variable to be set (Adoptium major version, e.g. 8, 11, 17, 21)"
  exit 1
fi

# Release, not Debug: build:x64 (.gitlab/scripts/build.sh) only ever produces
# and ships the release-config libjavaProfiler.so -- that's the actual
# shipped artifact this job exists to exercise. testDebug would set
# ddprof_test.config=debug while the loaded library was in fact built
# release, so debug-only assertions (e.g. JVMAccessTest's [TEST::INFO] log
# lines, only compiled into debug builds) would fail outright instead of
# correctly assumeTrue-skipping.
TEST_CONFIG="${TEST_CONFIG:-Release}"

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
REPO_ROOT=$( cd "${HERE}/../.." && pwd )

if [ -z "${JAVA_HOME}" ]; then
  # workaround for CI when JAVA_HOME is not properly defined
  export JAVA_HOME=~/.sdkman/candidates/java/current
fi

echo "Using Java (build) @ ${JAVA_HOME}"

# Fetch the JDK under test independently of the JDK running Gradle: the
# profiler-test Gradle plugin runs the test JVM from JAVA_TEST_HOME when it
# is set, so this is the only way to exercise multiple JDKs without needing
# a Gradle version that runs on each of them.
JDK_CACHE_DIR="${REPO_ROOT}/.jdk-cache/${TEST_JDK}"
if [ ! -x "${JDK_CACHE_DIR}/bin/java" ]; then
  rm -rf "${JDK_CACHE_DIR}"
  mkdir -p "${JDK_CACHE_DIR}"
  curl -sL "https://api.adoptium.net/v3/binary/latest/${TEST_JDK}/ga/linux/x64/jdk/hotspot/normal/eclipse" \
    -o /tmp/test-jdk.tar.gz
  tar -xzf /tmp/test-jdk.tar.gz -C "${JDK_CACHE_DIR}" --strip-components=1
  rm -f /tmp/test-jdk.tar.gz
fi
export JAVA_TEST_HOME="${JDK_CACHE_DIR}"
echo "Using Java (test) @ ${JAVA_TEST_HOME}"
"${JAVA_TEST_HOME}/bin/java" -version

source .gitlab/scripts/includes.sh

function onexit {
  local out_dir="${REPO_ROOT}/functional/${TARGET}/jdk${TEST_JDK}"
  mkdir -p "${out_dir}/reports"
  mkdir -p "${out_dir}/logs"
  mv "${REPO_ROOT}/ddprof-test/build/reports" "${out_dir}/" 2>/dev/null || true
  mv /tmp/*.jfr "${out_dir}/logs" 2>/dev/null || true
  mv /tmp/*.json "${out_dir}/logs" 2>/dev/null || true
  mv /tmp/*.txt "${out_dir}/logs" 2>/dev/null || true
  find . -name 'hs_err*' | xargs -I {} cp {} "${out_dir}/logs" 2>/dev/null || true
}

trap onexit EXIT

GRADLE_EXTRA_ARGS=()
if [ -n "${TESTS_FILTER:-}" ]; then
  GRADLE_EXTRA_ARGS+=("-Ptests=${TESTS_FILTER}")
fi

./gradlew -Pddprof_version="$(get_version)" -Pskip-native=ddprof-lib,malloc-shim -Pwith-libs="$(pwd)/libs" -PCI \
  -PtestMaxHeap=1536m "${GRADLE_EXTRA_ARGS[@]}" \
  ":ddprof-test:test${TEST_CONFIG}" --max-workers=1 --build-cache --stacktrace --info --no-watch-fs --no-daemon
