#!/bin/bash

set -euo pipefail

# run-integration-test.sh - Simplified integration tests for profiler
#
# This script runs self-contained integration tests without building dd-trace-java.
# It tests the patched dd-java-agent with both profiler-only and tracer+profiler scenarios.
#
# Expected environment variables:
# - LIBC_VARIANT: glibc or musl
# - ARCH: x64 or arm64
# - JVM_TYPE: hotspot or openj9
# - JAVA_VERSION: 8, 11, 17, 21, 25
#
# Optional:
# - CI_PROJECT_DIR: Project root (auto-detected if not set)
# - JAVA_HOME: Java installation (must be set)
# - TEST_DURATION: Test duration in seconds (default: 30)

# ========================================
# Configuration
# ========================================

# Use CI_PROJECT_DIR if available, otherwise calculate from script location
if [ -n "${CI_PROJECT_DIR:-}" ]; then
  PROJECT_ROOT="${CI_PROJECT_DIR}"
else
  HERE=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
  PROJECT_ROOT="${HERE}/../.."
fi

# Test configuration
TEST_DURATION="${TEST_DURATION:-60}"
TEST_THREADS=4
CPU_ITERATIONS=10000
ALLOC_RATE=1000

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

function log_info() {
  echo -e "${GREEN}[INFO]${NC} $*"
}

function log_warn() {
  echo -e "${YELLOW}[WARN]${NC} $*"
}

function log_error() {
  echo -e "${RED}[ERROR]${NC} $*"
}

# ========================================
# Validate Environment
# ========================================
echo "=== Integration Test Configuration ==="
echo "LIBC_VARIANT=${LIBC_VARIANT:-<not set>}"
echo "ARCH=${ARCH:-<not set>}"
echo "JVM_TYPE=${JVM_TYPE:-<not set>}"
echo "JAVA_VERSION=${JAVA_VERSION:-<not set>}"
echo "JAVA_HOME=${JAVA_HOME:-<not set>}"
echo "TEST_DURATION=${TEST_DURATION}"
echo ""

# Validate required variables
if [ -z "${LIBC_VARIANT:-}" ] || [ -z "${ARCH:-}" ] || [ -z "${JVM_TYPE:-}" ] || [ -z "${JAVA_VERSION:-}" ]; then
  log_error "Missing required environment variables"
  log_error "Required: LIBC_VARIANT, ARCH, JVM_TYPE, JAVA_VERSION"
  exit 1
fi

# Validate JAVA_HOME
if [ -z "${JAVA_HOME:-}" ]; then
  log_error "JAVA_HOME not set"
  exit 1
fi

if [ ! -x "${JAVA_HOME}/bin/java" ]; then
  log_error "Java not found at: ${JAVA_HOME}/bin/java"
  exit 1
fi

if [ ! -x "${JAVA_HOME}/bin/javac" ]; then
  log_error "javac not found at: ${JAVA_HOME}/bin/javac"
  exit 1
fi

# ========================================
# System Diagnostics Functions
# ========================================

collect_system_metrics() {
  local phase="$1"  # start|mid|end
  local output="${RESULTS_DIR}/diagnostics/system-metrics-${phase}.json"

  mkdir -p "${RESULTS_DIR}/diagnostics"

  # Collect metrics
  local cpu_count=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo "1")
  local cpu_quota=$(cat /sys/fs/cgroup/cpu/cpu.cfs_quota_us 2>/dev/null || echo "-1")
  local cpu_period=$(cat /sys/fs/cgroup/cpu/cpu.cfs_period_us 2>/dev/null || echo "-1")
  local load_avg=$(uptime | awk -F'load average:' '{print $2}' | xargs)
  local container=$(test -f /.dockerenv && echo "true" || echo "false")

  # Parse throttling stats
  local throttle_stats=$(cat /sys/fs/cgroup/cpu/cpu.stat 2>/dev/null || echo "")
  local nr_periods=$(echo "$throttle_stats" | grep nr_periods | awk '{print $2}')
  local nr_throttled=$(echo "$throttle_stats" | grep nr_throttled | awk '{print $2}')
  local throttled_time=$(echo "$throttle_stats" | grep throttled_time | awk '{print $2}')

  # Calculate throttle percentage
  local throttle_pct=0
  if [ -n "$nr_periods" ] && [ "$nr_periods" -gt 0 ] && [ "$cpu_period" -gt 0 ]; then
    throttle_pct=$(awk "BEGIN {printf \"%.2f\", ($throttled_time / ($nr_periods * $cpu_period)) * 100}")
  fi

  # Write JSON
  cat > "$output" <<EOF
{
  "timestamp": "$(date -Iseconds 2>/dev/null || date +%Y-%m-%dT%H:%M:%S%z)",
  "phase": "$phase",
  "cpu_count": $cpu_count,
  "cpu_quota": $cpu_quota,
  "cpu_period": $cpu_period,
  "load_average": "$load_avg",
  "container": $container,
  "throttling": {
    "nr_periods": ${nr_periods:-0},
    "nr_throttled": ${nr_throttled:-0},
    "throttled_time_ns": ${throttled_time:-0},
    "percentage": $throttle_pct
  }
}
EOF

  log_info "System metrics collected ($phase): CPU=$cpu_count, Throttled=${throttle_pct}%"
}

start_cpu_monitor() {
  # Background process sampling CPU count every 5s
  local monitor_file="${RESULTS_DIR}/diagnostics/cpu-timeline.log"
  mkdir -p "${RESULTS_DIR}/diagnostics"

  (
    while true; do
      local cpu_now=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo "1")
      echo "$(date +%s) $cpu_now" >> "$monitor_file"
      sleep 5
    done
  ) &

  echo $! > "${RESULTS_DIR}/diagnostics/monitor.pid"
  log_info "CPU monitor started (PID: $!)"
}

stop_cpu_monitor() {
  local pid_file="${RESULTS_DIR}/diagnostics/monitor.pid"
  if [ -f "$pid_file" ]; then
    local monitor_pid=$(cat "$pid_file")
    kill "$monitor_pid" 2>/dev/null || true
    rm "$pid_file"
    log_info "CPU monitor stopped"
  fi
}

generate_diagnostics_summary() {
  local output="${RESULTS_DIR}/diagnostics/summary.txt"

  # Analyze CPU timeline for changes
  local cpu_changes=$(awk '{print $2}' "${RESULTS_DIR}/diagnostics/cpu-timeline.log" | sort -u | wc -l)
  local cpu_min=$(awk '{print $2}' "${RESULTS_DIR}/diagnostics/cpu-timeline.log" | sort -n | head -1)
  local cpu_max=$(awk '{print $2}' "${RESULTS_DIR}/diagnostics/cpu-timeline.log" | sort -n | tail -1)

  # Extract throttling from end metrics
  local throttle_pct=$(grep '"percentage"' "${RESULTS_DIR}/diagnostics/system-metrics-end.json" | awk -F': ' '{print $2}' | tr -d ',')

  cat > "$output" <<EOF
=== System Diagnostics Summary ===
CPU Range: ${cpu_min} - ${cpu_max} cores
CPU Changes: ${cpu_changes} unique values
Throttling: ${throttle_pct}%
Container: $(grep '"container"' "${RESULTS_DIR}/diagnostics/system-metrics-start.json" | awk -F': ' '{print $2}' | tr -d ',')
EOF

  log_info "Diagnostics summary generated"
}

# Create results directory
RESULTS_DIR="${PROJECT_ROOT}/integration-test-results/${LIBC_VARIANT}-${ARCH}-${JVM_TYPE}-jdk${JAVA_VERSION}"
mkdir -p "${RESULTS_DIR}"

log_info "Results directory: ${RESULTS_DIR}"
log_info "Java version:"
"${JAVA_HOME}/bin/java" -version 2>&1 | head -3

# ========================================
# Install Prerequisites
# ========================================
echo ""
log_info "Installing prerequisites (jbang for JFR validation)..."

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
if [ -f "${SCRIPT_DIR}/install-prerequisites.sh" ]; then
  source "${SCRIPT_DIR}/install-prerequisites.sh"
else
  log_warn "install-prerequisites.sh not found, skipping"
fi

# Ensure jbang is in PATH
export PATH="$HOME/.jbang/bin:$PATH"

# Verify jbang is available
if ! command -v jbang &> /dev/null; then
  log_error "jbang not found after installation"
  log_error "JFR validation will not work"
  exit 1
fi

log_info "jbang version: $(jbang version 2>&1 | head -1)"

# ========================================
# Artifact Collection on Exit
# ========================================
function collect_artifacts() {
  log_info "Collecting artifacts..."

  # Copy JFR recordings from dump directories
  find /tmp -type d -name 'jfr-*' -exec sh -c 'cp "$0"/*.jfr "${1}/" 2>/dev/null || true' {} "${RESULTS_DIR}" \; 2>/dev/null || true

  # Copy agent logs
  find /tmp -maxdepth 1 -name '*-agent.log' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true

  # Copy HotSpot JVM crash dumps
  find /tmp -maxdepth 1 -name 'hs_err*' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true
  find . -maxdepth 1 -name 'hs_err*' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true

  # Copy OpenJ9 crash dumps
  find /tmp -maxdepth 1 -name 'javacore*.txt' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true
  find /tmp -maxdepth 1 -name 'Snap*.trc' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true
  find /tmp -maxdepth 1 -name 'jitdump*' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true
  find /tmp -maxdepth 1 -name 'core.*' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true
  find . -maxdepth 1 -name 'javacore*.txt' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true
  find . -maxdepth 1 -name 'Snap*.trc' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true

  # Copy validation reports
  find /tmp/jfr-validation -name '*.log' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true

  # Copy any test output logs
  find /tmp -maxdepth 1 -name 'test-*.log' -exec cp {} "${RESULTS_DIR}/" \; 2>/dev/null || true

  log_info "Artifacts collected to: ${RESULTS_DIR}"
}

trap collect_artifacts EXIT

# ========================================
# Calculate Threshold Multiplier
# ========================================
# Base multiplier is 1.0, adjusted for platform and JVM type

THRESHOLD_MULTIPLIER=1.0

# Platform adjustments
case "${ARCH}-${LIBC_VARIANT}" in
  x64-glibc)
    PLATFORM_MULT=1.0
    ;;
  x64-musl)
    PLATFORM_MULT=1.0
    ;;
  arm64-glibc)
    PLATFORM_MULT=0.8
    ;;
  arm64-musl)
    PLATFORM_MULT=0.8
    ;;
  *)
    log_warn "Unknown platform: ${ARCH}-${LIBC_VARIANT}, using default multiplier"
    PLATFORM_MULT=1.0
    ;;
esac

# JVM type adjustments
case "${JVM_TYPE}" in
  hotspot)
    JVM_MULT=1.0
    ;;
  openj9)
    JVM_MULT=0.5  # OpenJ9 typically produces fewer samples
    ;;
  *)
    log_warn "Unknown JVM type: ${JVM_TYPE}, using default multiplier"
    JVM_MULT=1.0
    ;;
esac

# Extra adjustment for musl libc (Docker-on-runner with significant overhead)
LIBC_MULT=1.0
if [ "${LIBC_VARIANT}" = "musl" ]; then
  LIBC_MULT=0.25
fi

# Calculate final multiplier
THRESHOLD_MULTIPLIER=$(awk "BEGIN {print ${PLATFORM_MULT} * ${JVM_MULT} * ${LIBC_MULT}}")

log_info "Threshold multiplier: ${THRESHOLD_MULTIPLIER} (platform=${PLATFORM_MULT}, jvm=${JVM_MULT}, libc=${LIBC_MULT})"

# ========================================
# Find Patched Agent
# ========================================
log_info "Locating patched dd-java-agent..."

PATCHED_AGENT="${PROJECT_ROOT}/dd-java-agent-patched.jar"

if [ ! -f "${PATCHED_AGENT}" ]; then
  log_error "Patched agent not found: ${PATCHED_AGENT}"
  log_error "Expected artifact from prepare-patched-agent job"
  exit 1
fi

log_info "Patched agent: ${PATCHED_AGENT}"
log_info "Agent size: $(du -h "${PATCHED_AGENT}" | cut -f1)"

# Verify ddprof is actually in the patched agent
log_info "Verifying ddprof presence in patched agent..."
NATIVE_LIBS=$(unzip -l "${PATCHED_AGENT}" | grep -c "shared/META-INF/native-libs/.*\.so$" || echo "0")
CLASSDATA=$(unzip -l "${PATCHED_AGENT}" | grep -c "shared/.*\.classdata$" || echo "0")
log_info "  - Native libraries: ${NATIVE_LIBS}"
log_info "  - Classdata files: ${CLASSDATA}"

if [ "${NATIVE_LIBS}" -eq 0 ]; then
  log_error "No ddprof native libraries found in patched agent!"
  log_error "Patching may have failed"
  exit 1
fi

# ========================================
# Compile Test Application
# ========================================
log_info "Compiling test application..."

TEST_APP_SRC="${PROJECT_ROOT}/test-apps/ProfilerTestApp.java"
TEST_APP_DIR="/tmp/test-app-$$"

if [ ! -f "${TEST_APP_SRC}" ]; then
  log_error "Test app not found: ${TEST_APP_SRC}"
  exit 1
fi

mkdir -p "${TEST_APP_DIR}"
cp "${TEST_APP_SRC}" "${TEST_APP_DIR}/"

cd "${TEST_APP_DIR}"

if ! "${JAVA_HOME}/bin/javac" ProfilerTestApp.java 2>&1; then
  log_error "Test app compilation failed"
  exit 1
fi

log_info "✓ Test application compiled successfully"

# ========================================
# Run Scenario 1: Profiler-Only
# ========================================
echo ""
echo "========================================"
echo "  Scenario 1: Profiler-Only"
echo "========================================"
echo ""

SCENARIO1_JFR_DIR="/tmp/jfr-profiler-only-${LIBC_VARIANT}-${ARCH}-${JVM_TYPE}-jdk${JAVA_VERSION}"
SCENARIO1_LOG="/tmp/profiler-only-agent.log"

mkdir -p "${SCENARIO1_JFR_DIR}"

# Collect system metrics at test start
collect_system_metrics "start"
start_cpu_monitor

log_info "Running profiler-only test (${TEST_DURATION}s)..."
log_info "JFR dump directory: ${SCENARIO1_JFR_DIR}"
log_info "Log output: ${SCENARIO1_LOG}"

# Log Java version details for debugging allocation profiling
log_info "Java version details:"
"${JAVA_HOME}/bin/java" -XshowSettings:properties -version 2>&1 | grep -E "java\.(version|vendor|runtime|vm)" || true
echo ""

# Run test with profiler-only configuration
"${JAVA_HOME}/bin/java" \
  -javaagent:"${PATCHED_AGENT}" \
  -Ddd.profiling.enabled=true \
  -Ddd.profiling.ddprof.enabled=true \
  -Ddd.trace.enabled=false \
  -Ddd.profiling.start-delay=0 \
  -Ddd.profiling.start-force-first=true \
  -Ddd.profiling.upload.period=10 \
  -Ddd.profiling.debug.dump_path="${SCENARIO1_JFR_DIR}" \
  -Ddd.service.name=profiler-integration-test \
  -Ddd.trace.startup.logs=true \
  -Ddatadog.slf4j.simpleLogger.defaultLogLevel=debug \
  -cp . ProfilerTestApp \
    --duration "${TEST_DURATION}" \
    --threads "${TEST_THREADS}" \
    --cpu-iterations "${CPU_ITERATIONS}" \
    --alloc-rate "${ALLOC_RATE}" \
  > "${SCENARIO1_LOG}" 2>&1

# Show agent startup logs
log_info "Agent startup log (first 100 lines):"
head -100 "${SCENARIO1_LOG}"

log_info "✓ Profiler-only test completed"

# Collect mid-test system metrics
collect_system_metrics "mid"

# Find the JFR recording (profiler writes continuously)
log_info "Locating JFR recording in ${SCENARIO1_JFR_DIR}..."

SCENARIO1_JFR=$(find "${SCENARIO1_JFR_DIR}" -name "*.jfr" -print -quit)

if [ -z "${SCENARIO1_JFR}" ] || [ ! -f "${SCENARIO1_JFR}" ]; then
  log_error "JFR recording not found in: ${SCENARIO1_JFR_DIR}"
  ls -la "${SCENARIO1_JFR_DIR}" || true
  exit 1
fi

log_info "Found JFR recording: ${SCENARIO1_JFR}"

JFR_SIZE=$(stat -f%z "${SCENARIO1_JFR}" 2>/dev/null || stat -c%s "${SCENARIO1_JFR}" 2>/dev/null)
log_info "JFR recording size: ${JFR_SIZE} bytes"

if [ "${JFR_SIZE}" -lt 1024 ]; then
  log_error "JFR recording is too small (< 1KB)"
  exit 1
fi

# Run JFR validation with conformance checking
VALIDATION_LOG="/tmp/jfr-validation/profiler-only-${LIBC_VARIANT}-${ARCH}-${JVM_TYPE}-jdk${JAVA_VERSION}.log"
mkdir -p /tmp/jfr-validation

log_info "Running conformance-based JFR validation..."

# Use conformance wrapper with explicit configuration flags
# Since we're using the patched agent with ddprof, ddprof is enabled by default
set +e
"${PROJECT_ROOT}/test-validation/validate-jfr-conformance.sh" \
  "${SCENARIO1_JFR}" \
  --ddprof-enabled=true \
  --tracer-enabled=false \
  --test-duration="${TEST_DURATION}" \
  --arch="${ARCH}" \
  --libc="${LIBC_VARIANT}" \
  --jvm-type="${JVM_TYPE}" \
  --output="${VALIDATION_LOG}"

VALIDATION_EXIT=$?
set -e

# Show validation output and check exit code
if [ ${VALIDATION_EXIT} -ne 0 ]; then
  echo ""
  log_error "=========================================="
  log_error "  PROFILER-ONLY VALIDATION FAILED"
  log_error "  Exit code: ${VALIDATION_EXIT}"
  log_error "=========================================="
  log_error ""

  if [ -f "${VALIDATION_LOG}" ]; then
    log_error "Validation output:"
    cat "${VALIDATION_LOG}"
  else
    log_error "Validation log file not found: ${VALIDATION_LOG}"
  fi

  exit 1
fi

log_info "✓ Profiler-only validation PASSED"

# Copy validation log to results directory for artifact collection
CONFIG_NAME="${LIBC_VARIANT}-${ARCH}-${JVM_TYPE}-jdk${JAVA_VERSION}"
if [ -f "${VALIDATION_LOG}" ]; then
  cp "${VALIDATION_LOG}" "${RESULTS_DIR}/profiler-only-${CONFIG_NAME}.log"
  log_info "Copied validation log to ${RESULTS_DIR}/profiler-only-${CONFIG_NAME}.log"
fi

# ========================================
# Run Scenario 2: Tracer+Profiler
# ========================================
echo ""
echo "========================================"
echo "  Scenario 2: Tracer+Profiler"
echo "========================================"
echo ""

SCENARIO2_JFR_DIR="/tmp/jfr-tracer-profiler-${LIBC_VARIANT}-${ARCH}-${JVM_TYPE}-jdk${JAVA_VERSION}"
SCENARIO2_LOG="/tmp/tracer-profiler-agent.log"

mkdir -p "${SCENARIO2_JFR_DIR}"

log_info "Running tracer+profiler test (${TEST_DURATION}s)..."
log_info "JFR dump directory: ${SCENARIO2_JFR_DIR}"
log_info "Log output: ${SCENARIO2_LOG}"

# Run test with tracer+profiler configuration
"${JAVA_HOME}/bin/java" \
  -javaagent:"${PATCHED_AGENT}" \
  -Ddd.profiling.enabled=true \
  -Ddd.profiling.ddprof.enabled=true \
  -Ddd.trace.enabled=true \
  -Ddd.profiling.start-delay=0 \
  -Ddd.profiling.start-force-first=true \
  -Ddd.profiling.upload.period=10 \
  -Ddd.profiling.debug.dump_path="${SCENARIO2_JFR_DIR}" \
  -Ddd.service.name=profiler-integration-test \
  -Ddd.trace.startup.logs=true \
  -Ddatadog.slf4j.simpleLogger.defaultLogLevel=debug \
  -cp . ProfilerTestApp \
    --duration "${TEST_DURATION}" \
    --threads "${TEST_THREADS}" \
    --cpu-iterations "${CPU_ITERATIONS}" \
    --alloc-rate "${ALLOC_RATE}" \
  > "${SCENARIO2_LOG}" 2>&1

log_info "✓ Tracer+profiler test completed"

# Find the JFR recording (profiler writes continuously)
log_info "Locating JFR recording in ${SCENARIO2_JFR_DIR}..."

SCENARIO2_JFR=$(find "${SCENARIO2_JFR_DIR}" -name "*.jfr" -print -quit)

if [ -z "${SCENARIO2_JFR}" ] || [ ! -f "${SCENARIO2_JFR}" ]; then
  log_error "JFR recording not found in: ${SCENARIO2_JFR_DIR}"
  ls -la "${SCENARIO2_JFR_DIR}" || true
  exit 1
fi

log_info "Found JFR recording: ${SCENARIO2_JFR}"

JFR_SIZE=$(stat -f%z "${SCENARIO2_JFR}" 2>/dev/null || stat -c%s "${SCENARIO2_JFR}" 2>/dev/null)
log_info "JFR recording size: ${JFR_SIZE} bytes"

if [ "${JFR_SIZE}" -lt 1024 ]; then
  log_error "JFR recording is too small (< 1KB)"
  exit 1
fi

# Run JFR validation with conformance checking
VALIDATION_LOG="/tmp/jfr-validation/tracer-profiler-${LIBC_VARIANT}-${ARCH}-${JVM_TYPE}-jdk${JAVA_VERSION}.log"
mkdir -p /tmp/jfr-validation

log_info "Running conformance-based JFR validation..."

# Use conformance wrapper with tracer enabled
set +e
"${PROJECT_ROOT}/test-validation/validate-jfr-conformance.sh" \
  "${SCENARIO2_JFR}" \
  --ddprof-enabled=true \
  --tracer-enabled=true \
  --test-duration="${TEST_DURATION}" \
  --arch="${ARCH}" \
  --libc="${LIBC_VARIANT}" \
  --jvm-type="${JVM_TYPE}" \
  --output="${VALIDATION_LOG}"

VALIDATION_EXIT=$?
set -e

# Show validation output and check exit code
if [ ${VALIDATION_EXIT} -ne 0 ]; then
  echo ""
  log_error "=========================================="
  log_error "  TRACER+PROFILER VALIDATION FAILED"
  log_error "  Exit code: ${VALIDATION_EXIT}"
  log_error "=========================================="
  log_error ""

  if [ -f "${VALIDATION_LOG}" ]; then
    log_error "Validation output:"
    cat "${VALIDATION_LOG}"
  else
    log_error "Validation log file not found: ${VALIDATION_LOG}"
  fi

  exit 1
fi

log_info "✓ Tracer+profiler validation PASSED"

# Copy validation log to results directory for artifact collection
if [ -f "${VALIDATION_LOG}" ]; then
  cp "${VALIDATION_LOG}" "${RESULTS_DIR}/tracer-profiler-${CONFIG_NAME}.log"
  log_info "Copied validation log to ${RESULTS_DIR}/tracer-profiler-${CONFIG_NAME}.log"
fi

# Collect final system metrics and generate summary
collect_system_metrics "end"
stop_cpu_monitor
generate_diagnostics_summary

# ========================================
# Cleanup
# ========================================
cd "${PROJECT_ROOT}"
rm -rf "${TEST_APP_DIR}"

# ========================================
# Summary
# ========================================
echo ""
echo "========================================"
echo "  Integration Tests Summary"
echo "========================================"
echo ""
log_info "Platform: ${LIBC_VARIANT}-${ARCH}"
log_info "JVM: ${JVM_TYPE} JDK${JAVA_VERSION}"
log_info "✓ Scenario 1: Profiler-Only - PASSED"
log_info "✓ Scenario 2: Tracer+Profiler - PASSED"
log_info ""
log_info "All integration tests PASSED"
log_info "Results saved to: ${RESULTS_DIR}"
echo ""
