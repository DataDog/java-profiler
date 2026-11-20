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
  # Same body-capture diagnostics as the integration-test JDK download: an egress
  # failure surfaces as a short non-gzip body that tar rejects and the pipe loses.
  TEST_JDK_URL="https://api.adoptium.net/v3/binary/latest/${TEST_JDK}/ga/linux/x64/jdk/hotspot/normal/eclipse"
  dump_test_jdk_body() {
    ls -l "$1" || true
    sha256sum "$1" || true
    head -c 256 "$1" | od -c | head -20 || true
  }
  save_test_jdk_body() {
    if [ "$(wc -c < "$1")" -le 1048576 ]; then
      cp "$1" "$2" || true
    else
      echo "failure body larger than 1MB, not saved"
    fi
  }
  MAX_RETRIES=3
  for attempt in $(seq 1 $MAX_RETRIES); do
    rm -rf "${JDK_CACHE_DIR}"
    mkdir -p "${JDK_CACHE_DIR}"
    TEST_JDK_TARBALL=$(mktemp /tmp/test-jdk.XXXXXXXX) || exit 1
    CURL_STATUS=0
    CURL_META=$(curl -sL -o "${TEST_JDK_TARBALL}" \
      -w 'http_code=%{http_code} effective_url=%{url_effective} redirects=%{num_redirects} size=%{size_download}' \
      "${TEST_JDK_URL}") || CURL_STATUS=$?
    echo "TEST_JDK ${TEST_JDK} download attempt ${attempt}/${MAX_RETRIES}: curl exit=${CURL_STATUS} ${CURL_META}"
    # A 4xx is deterministic: dump the body and stop instead of burning retries.
    HTTP_CODE=${CURL_META%% *}
    HTTP_CODE=${HTTP_CODE#http_code=}
    if [ "${HTTP_CODE:-0}" -ge 400 ] 2>/dev/null && [ "${HTTP_CODE:-0}" -lt 500 ]; then
      echo "TEST_JDK ${TEST_JDK} download failed with HTTP ${HTTP_CODE}:"
      dump_test_jdk_body "${TEST_JDK_TARBALL}"
      save_test_jdk_body "${TEST_JDK_TARBALL}" /tmp/test-jdk-failed.bin
      rm -f "${TEST_JDK_TARBALL}"
      exit 1
    fi
    if [ "${CURL_STATUS}" -eq 0 ] && tar -xzf "${TEST_JDK_TARBALL}" -C "${JDK_CACHE_DIR}" --strip-components=1 && [ -n "$(ls -A "${JDK_CACHE_DIR}")" ]; then
      rm -f "${TEST_JDK_TARBALL}"
      break
    fi
    echo "TEST_JDK ${TEST_JDK} download attempt ${attempt} produced a non-tar or empty body:"
    dump_test_jdk_body "${TEST_JDK_TARBALL}"
    save_test_jdk_body "${TEST_JDK_TARBALL}" /tmp/test-jdk-failed.bin
    if [ "$attempt" -eq 1 ]; then
      echo "TEST_JDK ${TEST_JDK} download probe (${TEST_JDK_URL}):"
      curl -sIL --max-redirs 5 "${TEST_JDK_URL}" 2>&1 | head -100 || true
    fi
    rm -f "${TEST_JDK_TARBALL}"
    [ $attempt -lt $MAX_RETRIES ] && sleep 10 || exit 1
  done
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

# "el7", not "glibc": this runtime (container, kernel, network stack) is a
# different environment than the GitHub Actions glibc/Ubuntu matrix and can
# fail the same test for unrelated reasons, so it needs its own cell token
# (quarantine.py's KNOWN_LIBCS) -- sharing "glibc" would let an entry meant to
# excuse one silently excuse the other.
CELL="el7-${TEST_JDK}-$(printf '%s' "${TEST_CONFIG}" | tr '[:upper:]' '[:lower:]')-amd64"

# Default to no retry: a flaky-vs-broken retry means a full second suite run,
# and this runner has already OOMKilled the container outright at the default
# 2 attempts (see PR #805). Overridable via the job's own variables.
export MAX_ATTEMPTS="${MAX_ATTEMPTS:-1}"

# Compile build-logic inside the Gradle process: the default Kotlin compile
# daemon (~660MB RSS) otherwise stays resident through the whole test run in
# this memory-limited pod. Not set globally -- under CodeQL's Kotlin extractor
# an in-process compile thrashes Gradle's default 512m heap.
.github/scripts/run_tests_with_retry.sh "${CELL}" -- \
  ./gradlew -Pddprof_version="$(get_version)" -Pskip-native=ddprof-lib,malloc-shim -Pwith-libs="$(pwd)/libs" -PCI \
  -PtestMaxHeap=1536m -Pkotlin.compiler.execution.strategy=in-process \
  ":ddprof-test:test${TEST_CONFIG}" --max-workers=1 --build-cache --stacktrace --info --no-watch-fs --no-daemon
