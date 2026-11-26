#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.
# Source with an installation root to export the selected Semeru JAVA_HOME.
set -euo pipefail

if [ "${LIBC_VARIANT}" != glibc ]; then
  echo "ERROR: OpenJ9 integration requires glibc; no OpenJ9 musl runtime is configured" >&2
  exit 1
fi

case "${ARCH}" in
  x64|arm64) ;;
  *) echo "ERROR: Unsupported OpenJ9 architecture: ${ARCH}" >&2; exit 1 ;;
esac

case "${JAVA_VERSION}" in
  8|11|17|21|25) ;;
  *) echo "ERROR: Unsupported OpenJ9 JDK version: ${JAVA_VERSION}" >&2; exit 1 ;;
esac

# Tags and archive names are separate upstream identifiers, not a version template.
# Digests are upstream's <archive>.sha256.txt for that exact release asset.
case "${JAVA_VERSION}-${ARCH}" in
  8-x64)
    SEMERU_TAG=jdk-8.0.512.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_x64_linux_8.0.512.0.tar.gz
    SEMERU_SHA256=bd45587130f56feb746056e30d1fa1ebe5dd0ef44ec7b496e8aa072201981f8e
    ;;
  8-arm64)
    SEMERU_TAG=jdk-8.0.512.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_aarch64_linux_8.0.512.0.tar.gz
    SEMERU_SHA256=2090ee80f0a05889c62dae44c0479687bff9ad606ead0e367cde496c9ffcadb2
    ;;
  11-x64)
    SEMERU_TAG=jdk-11.0.33.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_x64_linux_11.0.33.0.tar.gz
    SEMERU_SHA256=dc4c3d88a1e2d64152e5c14109b5fbf35a1654d45b92b3419a2325c91ab15013
    ;;
  11-arm64)
    SEMERU_TAG=jdk-11.0.33.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_aarch64_linux_11.0.33.0.tar.gz
    SEMERU_SHA256=25947aef6c52a1ada2f53d73d8e71ee2e79398977f2f6f46e9f95886a917b085
    ;;
  17-x64)
    SEMERU_TAG=jdk-17.0.21.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_x64_linux_17.0.21.0.tar.gz
    SEMERU_SHA256=854268feba1ebddcad42cf97915b3c48e44a543bbbe8f43e587a722921a16c42
    ;;
  17-arm64)
    SEMERU_TAG=jdk-17.0.21.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_aarch64_linux_17.0.21.0.tar.gz
    SEMERU_SHA256=9e92ab55b5088d6f8f9170b4f4e70baff7d39416e454583306e6b576c2262e67
    ;;
  21-x64)
    SEMERU_TAG=jdk-21.0.13.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_x64_linux_21.0.13.0.tar.gz
    SEMERU_SHA256=0c92b61ea02efe73a7b6d346f1d8324efd50fe1fb848bf3a031a577dc1181d45
    ;;
  21-arm64)
    SEMERU_TAG=jdk-21.0.13.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_aarch64_linux_21.0.13.0.tar.gz
    SEMERU_SHA256=c8730b3746f3c2e5eb5ce7cc4415d4b86260cf7e9b12de469607c0c9c3c32dfb
    ;;
  25-x64)
    SEMERU_TAG=jdk-25.0.5.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_x64_linux_25.0.5.0.tar.gz
    SEMERU_SHA256=cb52686cd841bb76b55b66dabcbf890a303169158aa4bb10fa61040bf462f9b1
    ;;
  25-arm64)
    SEMERU_TAG=jdk-25.0.5.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_aarch64_linux_25.0.5.0.tar.gz
    SEMERU_SHA256=0d011789093c1e5e4da6843a8f40947a36c2f0af0199e6be64590d279e37e7cc
    ;;
esac

export JAVA_HOME="${1:?installation root required}/openj9-${JAVA_VERSION}"
DOWNLOAD_URL="https://github.com/ibmruntimes/semeru${JAVA_VERSION}-binaries/releases/download/${SEMERU_TAG}/${SEMERU_ARCHIVE}"
mkdir -p "${JAVA_HOME}"
# Every retry happens in this loop, so each attempt starts from a truncated file and
# all attempts share one deadline: a stall or slow trickle cannot use up the job timeout.
# The subshell keeps the trap and exits out of the caller.
(
  archive=$(mktemp)
  trap 'rm -f "${archive}"' EXIT
  attempts=5
  # Overridable only so the regression tests can reach the deadline branch.
  budget=${SEMERU_DOWNLOAD_BUDGET_SECONDS:-300}
  deadline=$((SECONDS + budget))
  for attempt in $(seq 1 "${attempts}"); do
    remaining=$((deadline - SECONDS))
    if [ "${remaining}" -le 0 ]; then
      echo "ERROR: Semeru download did not finish within ${budget} s: ${DOWNLOAD_URL}" >&2
      exit 1
    fi
    curl_status=0
    # Under 100 KiB/s for 30 s aborts the attempt, so a stall is retried within the budget.
    http_code=$(curl --location --silent --show-error --connect-timeout 30 \
      --speed-limit 102400 --speed-time 30 --max-time "${remaining}" \
      --output "${archive}" --write-out '%{http_code}' "${DOWNLOAD_URL}") || curl_status=$?
    if [ "${curl_status}" -ne 0 ]; then
      echo "WARN: Semeru download attempt ${attempt}/${attempts} failed with curl exit ${curl_status}: ${DOWNLOAD_URL}" >&2
    elif [ "${http_code}" != 200 ]; then
      case "${http_code}" in
        408|429|5??) echo "WARN: Semeru download attempt ${attempt}/${attempts} got HTTP ${http_code}: ${DOWNLOAD_URL}" >&2 ;;
        *) echo "ERROR: Semeru download failed with HTTP ${http_code}: ${DOWNLOAD_URL}" >&2; exit 1 ;;
      esac
    elif tar tzf "${archive}" > /dev/null 2>&1; then
      # A valid archive with the wrong digest is not a transient egress error: fail without retrying.
      if ! printf '%s  %s\n' "${SEMERU_SHA256}" "${archive}" | sha256sum -c --status -; then
        echo "ERROR: Semeru archive SHA-256 does not match the pinned ${SEMERU_SHA256}: ${DOWNLOAD_URL}" >&2
        exit 1
      fi
      tar xzf "${archive}" -C "${JAVA_HOME}" --strip-components=1
      exit 0
    else
      echo "WARN: Semeru download attempt ${attempt}/${attempts} is not a gzip tar archive: ${DOWNLOAD_URL}" >&2
    fi
    [ "${attempt}" -eq "${attempts}" ] || sleep 5
  done
  echo "ERROR: Could not download a valid Semeru archive after ${attempts} attempts: ${DOWNLOAD_URL}" >&2
  exit 1
)

if [ ! -x "${JAVA_HOME}/bin/java" ] || [ ! -x "${JAVA_HOME}/bin/javac" ]; then
  echo "ERROR: Semeru archive does not contain an executable JDK at ${JAVA_HOME}" >&2
  exit 1
fi
