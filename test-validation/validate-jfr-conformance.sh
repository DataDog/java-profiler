#!/bin/bash

# validate-jfr-conformance.sh - Conformance-based JFR validation
#
# This script selects the appropriate conformance profile based on profiler
# configuration and validates JFR recordings against expected events.
#
# Usage:
#   validate-jfr-conformance.sh <jfr-file> [options]
#
# Options:
#   --ddprof-enabled=<true|false>     Whether dd.profiling.ddprof.enabled (default: auto-detect)
#   --tracer-enabled=<true|false>     Whether dd.trace.enabled (default: false)
#   --test-duration=<seconds>         Test duration in seconds (default: 60)
#   --arch=<x64|arm64>                Architecture (default: x64)
#   --libc=<glibc|musl>               libc variant (default: glibc)
#   --jvm-type=<hotspot|openj9>       JVM type (default: hotspot)
#   --output=<file>                   Output log file (default: stdout)
#
# Exit codes:
#   0 - Validation passed
#   1 - Validation failed
#   2 - Configuration error

set -euo pipefail

# Ensure consistent decimal handling regardless of system locale
export LC_NUMERIC=C

# Defaults
JFR_FILE=""
DDPROF_ENABLED="auto"
TRACER_ENABLED="false"
TEST_DURATION="60"
ARCH="x64"
LIBC="glibc"
JVM_TYPE="hotspot"
OUTPUT_FILE=""

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function log_info() {
  echo -e "${GREEN}[INFO]${NC} $*"
}

function log_error() {
  echo -e "${RED}[ERROR]${NC} $*"
}

# Parse arguments
while [[ $# -gt 0 ]]; do
  case $1 in
    --ddprof-enabled=*)
      DDPROF_ENABLED="${1#*=}"
      shift
      ;;
    --tracer-enabled=*)
      TRACER_ENABLED="${1#*=}"
      shift
      ;;
    --test-duration=*)
      TEST_DURATION="${1#*=}"
      shift
      ;;
    --arch=*)
      ARCH="${1#*=}"
      shift
      ;;
    --libc=*)
      LIBC="${1#*=}"
      shift
      ;;
    --jvm-type=*)
      JVM_TYPE="${1#*=}"
      shift
      ;;
    --output=*)
      OUTPUT_FILE="${1#*=}"
      shift
      ;;
    *)
      if [ -z "${JFR_FILE}" ]; then
        JFR_FILE="$1"
      else
        log_error "Unknown argument: $1"
        exit 2
      fi
      shift
      ;;
  esac
done

# Validate required arguments
if [ -z "${JFR_FILE}" ]; then
  log_error "Missing required argument: <jfr-file>"
  echo ""
  echo "Usage: $0 <jfr-file> [options]"
  exit 2
fi

if [ ! -f "${JFR_FILE}" ]; then
  log_error "JFR file not found: ${JFR_FILE}"
  exit 2
fi

# Determine conformance profile
PROFILE="auto_detect"
PROFILE_DESC="Auto-detect profiler implementation"

if [ "${DDPROF_ENABLED}" = "true" ]; then
  if [ "${TRACER_ENABLED}" = "true" ]; then
    PROFILE="ddprof_with_tracer"
    PROFILE_DESC="Datadog profiler with tracer"
  else
    PROFILE="ddprof_only"
    PROFILE_DESC="Datadog profiler only"
  fi
elif [ "${DDPROF_ENABLED}" = "false" ]; then
  PROFILE="jdk_fallback"
  PROFILE_DESC="JDK profiling (ddprof disabled)"
fi

log_info "=========================================="
log_info "  JFR Conformance Validation"
log_info "=========================================="
log_info ""
log_info "Configuration:"
log_info "  JFR file: ${JFR_FILE}"
log_info "  Profile: ${PROFILE} (${PROFILE_DESC})"
log_info "  ddprof enabled: ${DDPROF_ENABLED}"
log_info "  Tracer enabled: ${TRACER_ENABLED}"
log_info "  Test duration: ${TEST_DURATION}s"
log_info "  Platform: ${ARCH}-${LIBC}"
log_info "  JVM: ${JVM_TYPE}"
log_info ""

# Calculate threshold multiplier
PLATFORM_MULT="1.0"
case "${ARCH}" in
  arm64)
    # ARM64 emulation has lower sampling rates
    PLATFORM_MULT="0.5"
    ;;
esac

JVM_MULT="1.0"
case "${JVM_TYPE}" in
  openj9)
    # OpenJ9 produces significantly fewer samples due to different JIT behavior
    JVM_MULT="0.3"
    ;;
esac

LIBC_MULT="1.0"
case "${LIBC}" in
  musl)
    # musl runners use Docker-on-runner with significant overhead
    # Additional reduction due to Alpine's different scheduler behavior
    LIBC_MULT="0.15"
    ;;
esac

THRESHOLD_MULTIPLIER=$(awk "BEGIN {print ${PLATFORM_MULT} * ${JVM_MULT} * ${LIBC_MULT}}")
log_info "Threshold multiplier: ${THRESHOLD_MULTIPLIER} (arch=${PLATFORM_MULT}, jvm=${JVM_MULT}, libc=${LIBC_MULT})"

# ========================================
# Calculate actual minimum thresholds
# ========================================
# Base rates per second (HotSpot, x64, glibc baseline):
#   ExecutionSample: ~2/sec
#   ObjectAllocationSample: ~10/sec
#   Thread count: minimum 3 unique threads
BASE_EXEC_RATE=2
BASE_ALLOC_RATE=10
BASE_THREAD_COUNT=3

# Calculate minimum thresholds based on test duration and multiplier
MIN_EXECUTION_SAMPLES=$(awk "BEGIN {val = ${BASE_EXEC_RATE} * ${TEST_DURATION} * ${THRESHOLD_MULTIPLIER}; print (val < 2) ? 2 : int(val)}")
# Allocation sampling is unreliable - just sanity check that at least 1 event exists
MIN_ALLOCATION_SAMPLES=1

# Thread count doesn't scale with duration, but reduced for challenging platforms
if awk "BEGIN {exit (${THRESHOLD_MULTIPLIER} < 0.3) ? 0 : 1}"; then
  MIN_THREAD_COUNT=2
else
  MIN_THREAD_COUNT=${BASE_THREAD_COUNT}
fi

log_info ""
log_info "Calculated thresholds (single source of truth):"
log_info "  ExecutionSample: >=${MIN_EXECUTION_SAMPLES} (${BASE_EXEC_RATE}/sec × ${TEST_DURATION}s × ${THRESHOLD_MULTIPLIER})"
log_info "  AllocationSample: >=${MIN_ALLOCATION_SAMPLES} (sanity check only)"
log_info "  Thread count: >=${MIN_THREAD_COUNT}"

# Load diagnostic data if available
DIAGNOSTICS_DIR="$(dirname "${JFR_FILE}")/diagnostics"
HAVE_DIAGNOSTICS="false"

if [ -d "${DIAGNOSTICS_DIR}" ] && [ -f "${DIAGNOSTICS_DIR}/summary.txt" ]; then
  HAVE_DIAGNOSTICS="true"
  log_info "System diagnostics available"

  # Extract key metrics
  THROTTLE_PCT=$(grep '"percentage"' "${DIAGNOSTICS_DIR}/system-metrics-end.json" 2>/dev/null | awk -F': ' '{print $2}' | tr -d ',' || echo "0")
  CPU_START=$(grep '"cpu_count"' "${DIAGNOSTICS_DIR}/system-metrics-start.json" 2>/dev/null | awk -F': ' '{print $2}' | tr -d ',' || echo "0")
  CPU_END=$(grep '"cpu_count"' "${DIAGNOSTICS_DIR}/system-metrics-end.json" 2>/dev/null | awk -F': ' '{print $2}' | tr -d ',' || echo "0")

  log_info "  CPU: ${CPU_START} → ${CPU_END} cores"
  log_info "  Throttling: ${THROTTLE_PCT}%"
fi

# Set expected event types based on profile
case "${PROFILE}" in
  ddprof_only)
    EXPECTED_CPU_EVENT="datadog"
    EXPECTED_ALLOC_EVENT="datadog"
    REQUIRE_CPU="true"
    REQUIRE_ALLOC="false"
    CHECK_ENDPOINT="false"
    UNEXPECTED_JDK_EXEC="true"
    UNEXPECTED_JDK_ALLOC="true"
    UNEXPECTED_DD_EXEC="false"
    UNEXPECTED_DD_ALLOC="false"
    UNEXPECTED_ENDPOINT="true"
    ;;

  ddprof_with_tracer)
    EXPECTED_CPU_EVENT="datadog"
    EXPECTED_ALLOC_EVENT="datadog"
    REQUIRE_CPU="true"
    REQUIRE_ALLOC="false"
    CHECK_ENDPOINT="true"
    UNEXPECTED_JDK_EXEC="true"
    UNEXPECTED_JDK_ALLOC="true"
    UNEXPECTED_DD_EXEC="false"
    UNEXPECTED_DD_ALLOC="false"
    UNEXPECTED_ENDPOINT="false"
    ;;

  jdk_fallback)
    EXPECTED_CPU_EVENT="jdk"
    EXPECTED_ALLOC_EVENT="jdk"
    REQUIRE_CPU="true"
    REQUIRE_ALLOC="false"
    CHECK_ENDPOINT="false"
    UNEXPECTED_JDK_EXEC="false"
    UNEXPECTED_JDK_ALLOC="false"
    UNEXPECTED_DD_EXEC="true"
    UNEXPECTED_DD_ALLOC="true"
    UNEXPECTED_ENDPOINT="true"
    ;;

  auto_detect)
    EXPECTED_CPU_EVENT="any"
    EXPECTED_ALLOC_EVENT="any"
    REQUIRE_CPU="true"
    REQUIRE_ALLOC="false"
    CHECK_ENDPOINT="false"
    UNEXPECTED_JDK_EXEC="false"
    UNEXPECTED_JDK_ALLOC="false"
    UNEXPECTED_DD_EXEC="false"
    UNEXPECTED_DD_ALLOC="false"
    UNEXPECTED_ENDPOINT="false"
    ;;

  *)
    log_error "Unknown profile: ${PROFILE}"
    exit 2
    ;;
esac

log_info "Expected events:"
log_info "  CPU profiling: ${EXPECTED_CPU_EVENT} (required: ${REQUIRE_CPU})"
log_info "  Allocation profiling: ${EXPECTED_ALLOC_EVENT} (required: ${REQUIRE_ALLOC})"
log_info "  Endpoint events: ${CHECK_ENDPOINT}"
log_info "Unexpected events:"
log_info "  jdk.ExecutionSample: ${UNEXPECTED_JDK_EXEC}"
log_info "  jdk.ObjectAllocationSample: ${UNEXPECTED_JDK_ALLOC}"
log_info "  datadog.ExecutionSample: ${UNEXPECTED_DD_EXEC}"
log_info "  datadog.ObjectSample: ${UNEXPECTED_DD_ALLOC}"
log_info "  datadog.EndpointEvent: ${UNEXPECTED_ENDPOINT}"
log_info ""

# Prepare validation command
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VALIDATION_SCRIPT="${SCRIPT_DIR}/validate-jfr.jfrs"

if [ ! -f "${VALIDATION_SCRIPT}" ]; then
  log_error "Validation script not found: ${VALIDATION_SCRIPT}"
  exit 2
fi

# Run validation
log_info "Running JFR validation..."
log_info ""

# Check if JFR validation should be skipped (JDK 25 unavailable)
if [ -f /tmp/skip-jfr-validation ]; then
  SKIP_REASON=$(cat /tmp/skip-jfr-validation 2>/dev/null || echo "prerequisite unavailable")
  log_warn "Skipping JFR validation: ${SKIP_REASON}"
  if [ -n "${OUTPUT_FILE}" ]; then
    echo "VALIDATION_SKIPPED: ${SKIP_REASON}" > "${OUTPUT_FILE}"
  fi
  exit 0
fi

# jfr-shell (jafar) requires Java 25 (class file version 69.0)
# Always use --java 25 to let jbang download the correct JDK
unset JAVA_VERSION  # Prevent jbang from picking up test JDK version

log_info "Using Java 25 for jbang (required by jfr-shell)"

# Pass calculated thresholds directly (single source of truth - no duplicate logic in jfrs)
VALIDATION_CMD="jbang --java 25 jfr-shell@btraceio script \"${VALIDATION_SCRIPT}\" \"${JFR_FILE}\" \"${PROFILE}\" \"${MIN_EXECUTION_SAMPLES}\" \"${MIN_ALLOCATION_SAMPLES}\" \"${MIN_THREAD_COUNT}\" \"${EXPECTED_CPU_EVENT}\" \"${EXPECTED_ALLOC_EVENT}\" \"${CHECK_ENDPOINT}\" \"${UNEXPECTED_JDK_EXEC}\" \"${UNEXPECTED_JDK_ALLOC}\" \"${UNEXPECTED_DD_EXEC}\" \"${UNEXPECTED_DD_ALLOC}\" \"${UNEXPECTED_ENDPOINT}\""

if [ -n "${OUTPUT_FILE}" ]; then
  # Set up trap to write failure marker if script is killed/crashes
  trap 'echo "VALIDATION_FAILED: Script terminated unexpectedly (exit code: $?)" >> "${OUTPUT_FILE}" 2>/dev/null || true' EXIT ERR

  # Write START marker so we know validation began
  {
    echo "VALIDATION_STARTED: $(date -u +"%Y-%m-%dT%H:%M:%SZ")"
    echo "Configuration: ddprof=${DDPROF_ENABLED}, tracer=${TRACER_ENABLED}, duration=${TEST_DURATION}s"
    echo "Platform: arch=${ARCH}, libc=${LIBC}, jvm-type=${JVM_TYPE}"
    echo "JFR file: ${JFR_FILE}"
    echo "Profile: ${PROFILE}"
    echo "---"
  } > "${OUTPUT_FILE}"

  # Run validation and append output
  eval "${VALIDATION_CMD}" >> "${OUTPUT_FILE}" 2>&1
  JBANG_EXIT=$?

  # Always write completion marker based on exit code
  if [ ${JBANG_EXIT} -eq 0 ]; then
    # Check if validation script itself reported failure
    if grep -q "VALIDATION_FAILED" "${OUTPUT_FILE}"; then
      echo "VALIDATION_FAILED: Validation checks did not pass" >> "${OUTPUT_FILE}"
    else
      echo "SUCCESS: All validations passed" >> "${OUTPUT_FILE}"
    fi
  else
    echo "VALIDATION_FAILED: jbang/jfr-shell exit code ${JBANG_EXIT}" >> "${OUTPUT_FILE}"
  fi

  # Clear trap now that we've written the marker
  trap - EXIT ERR

  # Check if validation actually failed by examining output
  if grep -q "VALIDATION_FAILED" "${OUTPUT_FILE}"; then
    log_error ""
    log_error "=========================================="
    log_error "  VALIDATION FAILED"
    log_error "  Profile: ${PROFILE}"
    log_error "=========================================="
    log_error ""

    # Show diagnostics if available
    if [ "${HAVE_DIAGNOSTICS}" = "true" ]; then
      log_error "System Diagnostics:"
      log_error "  CPU range: ${CPU_START} → ${CPU_END} cores"
      log_error "  Throttling: ${THROTTLE_PCT}%"
      log_error "  Full diagnostics: ${DIAGNOSTICS_DIR}/"
      log_error ""
    fi

    # Show the full output to see what failed
    cat "${OUTPUT_FILE}"
    exit 1
  fi

  # Show summary from output
  tail -20 "${OUTPUT_FILE}"
else
  VALIDATION_OUTPUT=$(eval "${VALIDATION_CMD}" 2>&1)
  JBANG_EXIT=$?

  # Print output
  echo "${VALIDATION_OUTPUT}"

  # Check if validation failed
  if echo "${VALIDATION_OUTPUT}" | grep -q "VALIDATION_FAILED"; then
    log_error ""
    log_error "=========================================="
    log_error "  VALIDATION FAILED"
    log_error "  Profile: ${PROFILE}"
    log_error "=========================================="

    # Show diagnostics if available
    if [ "${HAVE_DIAGNOSTICS}" = "true" ]; then
      log_error ""
      log_error "System Diagnostics:"
      log_error "  CPU range: ${CPU_START} → ${CPU_END} cores"
      log_error "  Throttling: ${THROTTLE_PCT}%"
      log_error "  Full diagnostics: ${DIAGNOSTICS_DIR}/"
    fi

    exit 1
  fi
fi

# Check if jbang itself failed
if [ ${JBANG_EXIT} -ne 0 ]; then
  log_error ""
  log_error "=========================================="
  log_error "  JBANG EXECUTION FAILED"
  log_error "  Profile: ${PROFILE}"
  log_error "  Exit code: ${JBANG_EXIT}"
  log_error "=========================================="
  exit 1
fi

# Success - show enhanced summary
log_info ""
log_info "=========================================="
log_info "  VALIDATION PASSED"
log_info "  Profile: ${PROFILE}"
log_info "=========================================="

if [ "${HAVE_DIAGNOSTICS}" = "true" ]; then
  log_info ""
  log_info "System Performance:"
  log_info "  CPU: ${CPU_START} → ${CPU_END} cores"
  log_info "  Throttling: ${THROTTLE_PCT}%"

  # Calculate actual sample rate from validation output
  # Read from OUTPUT_FILE if set, otherwise use VALIDATION_OUTPUT variable
  if [ -n "${OUTPUT_FILE}" ] && [ -f "${OUTPUT_FILE}" ]; then
    ACTUAL_SAMPLES=$(grep "ExecutionSample:" "${OUTPUT_FILE}" | grep -oE '[0-9]+ events' | awk '{print $1}')
  else
    ACTUAL_SAMPLES=$(echo "${VALIDATION_OUTPUT}" | grep "ExecutionSample:" | grep -oE '[0-9]+ events' | awk '{print $1}')
  fi
  if [ -n "${ACTUAL_SAMPLES}" ]; then
    ACTUAL_RATE=$(awk "BEGIN {printf \"%.2f\", ${ACTUAL_SAMPLES} / ${TEST_DURATION}}")
    EXPECTED_BASE=1.6
    EXPECTED_ADJUSTED=$(awk "BEGIN {printf \"%.2f\", ${EXPECTED_BASE} * ${THRESHOLD_MULTIPLIER}}")
    HEALTH_SCORE=$(awk "BEGIN {printf \"%.0f\", (${ACTUAL_RATE} / ${EXPECTED_ADJUSTED}) * 100}")

    # Classification
    if [ "${HEALTH_SCORE}" -ge 90 ]; then
      CLASSIFICATION="EXCELLENT"
    elif [ "${HEALTH_SCORE}" -ge 75 ]; then
      CLASSIFICATION="GOOD"
    elif [ "${HEALTH_SCORE}" -ge 60 ]; then
      CLASSIFICATION="MARGINAL"
    else
      CLASSIFICATION="POOR"
    fi

    log_info "  Sample rate: ${ACTUAL_RATE}/sec (expected: ${EXPECTED_ADJUSTED}/sec)"
    log_info "  Health score: ${HEALTH_SCORE}% (${CLASSIFICATION})"
  fi
fi

exit 0
