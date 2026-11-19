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
case "${JAVA_VERSION}-${ARCH}" in
  8-x64)
    SEMERU_TAG=jdk-8.0.512.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_x64_linux_8.0.512.0.tar.gz
    ;;
  8-arm64)
    SEMERU_TAG=jdk-8.0.512.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_aarch64_linux_8.0.512.0.tar.gz
    ;;
  11-x64)
    SEMERU_TAG=jdk-11.0.33.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_x64_linux_11.0.33.0.tar.gz
    ;;
  11-arm64)
    SEMERU_TAG=jdk-11.0.33.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_aarch64_linux_11.0.33.0.tar.gz
    ;;
  17-x64)
    SEMERU_TAG=jdk-17.0.21.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_x64_linux_17.0.21.0.tar.gz
    ;;
  17-arm64)
    SEMERU_TAG=jdk-17.0.21.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_aarch64_linux_17.0.21.0.tar.gz
    ;;
  21-x64)
    SEMERU_TAG=jdk-21.0.13.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_x64_linux_21.0.13.0.tar.gz
    ;;
  21-arm64)
    SEMERU_TAG=jdk-21.0.13.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_aarch64_linux_21.0.13.0.tar.gz
    ;;
  25-x64)
    SEMERU_TAG=jdk-25.0.5.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_x64_linux_25.0.5.0.tar.gz
    ;;
  25-arm64)
    SEMERU_TAG=jdk-25.0.5.0
    SEMERU_ARCHIVE=ibm-semeru-open-jdk_aarch64_linux_25.0.5.0.tar.gz
    ;;
esac

export JAVA_HOME="${1:?installation root required}/openj9-${JAVA_VERSION}"
DOWNLOAD_URL="https://github.com/ibmruntimes/semeru${JAVA_VERSION}-binaries/releases/download/${SEMERU_TAG}/${SEMERU_ARCHIVE}"
mkdir -p "${JAVA_HOME}"
curl --fail --location --retry 3 --retry-delay 5 "${DOWNLOAD_URL}" \
  | tar xzf - -C "${JAVA_HOME}" --strip-components=1

if [ ! -x "${JAVA_HOME}/bin/java" ] || [ ! -x "${JAVA_HOME}/bin/javac" ]; then
  echo "ERROR: Semeru archive does not contain an executable JDK at ${JAVA_HOME}" >&2
  exit 1
fi
