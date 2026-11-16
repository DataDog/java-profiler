#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.
set -euo pipefail

if ! settings=$("${JAVA_HOME:?JAVA_HOME required}/bin/java" -XshowSettings:properties -version 2>&1); then
  printf '%s\n' "${settings}" >&2
  echo "ERROR: Could not query integration JVM identity" >&2
  exit 1
fi
printf '%s\n' "${settings}"

vm_name=$(printf '%s\n' "${settings}" | sed -n 's/^[[:space:]]*java\.vm\.name = //p')
java_version=$(printf '%s\n' "${settings}" | sed -n 's/^[[:space:]]*java\.version = //p')
case "${JVM_TYPE:?JVM_TYPE required}:${vm_name}" in
  openj9:*OpenJ9*|hotspot:*HotSpot*|hotspot:*OpenJDK*) ;;
  *) echo "ERROR: JVM identity mismatch: expected ${JVM_TYPE}, java.vm.name=${vm_name:-<missing>}" >&2; exit 1 ;;
esac

case "${JAVA_VERSION:?JAVA_VERSION required}:${java_version}" in
  8:1.8.*) ;;
  "${JAVA_VERSION}:${JAVA_VERSION}."*) ;;
  *) echo "ERROR: JDK version mismatch: expected ${JAVA_VERSION}, java.version=${java_version:-<missing>}" >&2; exit 1 ;;
esac

echo "Verified integration JVM: JVM_TYPE=${JVM_TYPE} JAVA_VERSION=${JAVA_VERSION} java.vm.name=${vm_name} java.version=${java_version}"
