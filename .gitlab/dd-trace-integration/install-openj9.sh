#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.
# Source with an installation root to export the selected Semeru JAVA_HOME.
set -euo pipefail

if [ "${LIBC_VARIANT}" != glibc ]; then
  echo "ERROR: OpenJ9 integration requires glibc; no OpenJ9 musl runtime is configured" >&2
  exit 1
fi

case "${ARCH}" in
  x64) JDK_ARCH=x64 ;;
  arm64) JDK_ARCH=aarch64 ;;
  *) echo "ERROR: Unsupported OpenJ9 architecture: ${ARCH}" >&2; exit 1 ;;
esac

case "${JAVA_VERSION}" in
  8) SEMERU_VERSION=8.0.512.0 ;;
  11) SEMERU_VERSION=11.0.33.0 ;;
  17) SEMERU_VERSION=17.0.21.0 ;;
  21) SEMERU_VERSION=21.0.13.0 ;;
  25) SEMERU_VERSION=25.0.5.0 ;;
  *) echo "ERROR: Unsupported OpenJ9 JDK version: ${JAVA_VERSION}" >&2; exit 1 ;;
esac

export JAVA_HOME="${1:?installation root required}/openj9-${JAVA_VERSION}"
DOWNLOAD_URL="https://github.com/ibmruntimes/semeru${JAVA_VERSION}-binaries/releases/download/jdk-${SEMERU_VERSION}/ibm-semeru-open-jdk_${JDK_ARCH}_linux_${SEMERU_VERSION}.tar.gz"
mkdir -p "${JAVA_HOME}"
curl --fail --location --retry 3 --retry-delay 5 "${DOWNLOAD_URL}" \
  | tar xzf - -C "${JAVA_HOME}" --strip-components=1

if [ ! -x "${JAVA_HOME}/bin/java" ] || [ ! -x "${JAVA_HOME}/bin/javac" ]; then
  echo "ERROR: Semeru archive does not contain an executable JDK at ${JAVA_HOME}" >&2
  exit 1
fi
