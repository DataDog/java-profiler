#!/bin/bash

# generate-report.sh - Generate full integration test report in Markdown
#
# Usage: generate-report.sh <results-dir> [output-file]
#
# Generates a comprehensive Markdown report including:
# - Test configuration
# - Both scenario results (profiler-only, tracer+profiler)
# - System diagnostics (CPU, throttling)
# - Health scores and sample rates

set -euo pipefail

RESULTS_DIR="${1:-}"
OUTPUT_FILE="${2:-}"

if [ -z "${RESULTS_DIR}" ]; then
  echo "Usage: $0 <results-dir> [output-file]" >&2
  exit 1
fi

if [ ! -d "${RESULTS_DIR}" ]; then
  echo "Error: Results directory not found: ${RESULTS_DIR}" >&2
  exit 1
fi

# Extract config from directory name (e.g., glibc-x64-hotspot-jdk17)
CONFIG_NAME=$(basename "${RESULTS_DIR}")
IFS='-' read -r LIBC ARCH JVM_TYPE JDK_VERSION <<< "${CONFIG_NAME}"

# Get timestamp
TIMESTAMP=$(date -Iseconds 2>/dev/null || date +%Y-%m-%dT%H:%M:%S%z)
DATE_HUMAN=$(date "+%Y-%m-%d %H:%M:%S %Z" 2>/dev/null || date)

# Parse diagnostic data
DIAGNOSTICS_DIR="${RESULTS_DIR}/diagnostics"
CPU_START="N/A"
CPU_END="N/A"
THROTTLE_PCT="N/A"
CONTAINER="N/A"

if [ -d "${DIAGNOSTICS_DIR}" ]; then
  if [ -f "${DIAGNOSTICS_DIR}/system-metrics-start.json" ]; then
    CPU_START=$(grep '"cpu_count"' "${DIAGNOSTICS_DIR}/system-metrics-start.json" | awk -F': ' '{print $2}' | tr -d ',' || echo "N/A")
    CONTAINER=$(grep '"container"' "${DIAGNOSTICS_DIR}/system-metrics-start.json" | awk -F': ' '{print $2}' | tr -d ',' || echo "N/A")
  fi
  if [ -f "${DIAGNOSTICS_DIR}/system-metrics-end.json" ]; then
    CPU_END=$(grep '"cpu_count"' "${DIAGNOSTICS_DIR}/system-metrics-end.json" | awk -F': ' '{print $2}' | tr -d ',' || echo "N/A")
    THROTTLE_PCT=$(grep '"percentage"' "${DIAGNOSTICS_DIR}/system-metrics-end.json" | awk -F': ' '{print $2}' | tr -d ',' || echo "N/A")
  elif [ -f "${DIAGNOSTICS_DIR}/system-metrics-mid.json" ]; then
    CPU_END=$(grep '"cpu_count"' "${DIAGNOSTICS_DIR}/system-metrics-mid.json" | awk -F': ' '{print $2}' | tr -d ',' || echo "N/A")
    THROTTLE_PCT=$(grep '"percentage"' "${DIAGNOSTICS_DIR}/system-metrics-mid.json" | awk -F': ' '{print $2}' | tr -d ',' || echo "N/A")
  fi
fi

# Parse scenario 1 (profiler-only) results
S1_STATUS="N/A"
S1_SAMPLES="N/A"
S1_THREADS="N/A"
S1_ALLOC="N/A"
S1_LOG="${RESULTS_DIR}/profiler-only-${CONFIG_NAME}.log"

if [ -f "${S1_LOG}" ]; then
  if grep -q "SUCCESS: All validations passed" "${S1_LOG}"; then
    S1_STATUS="PASS"
  elif grep -q "VALIDATION_FAILED" "${S1_LOG}"; then
    S1_STATUS="FAIL"
  fi
  S1_SAMPLES=$(grep "ExecutionSample:" "${S1_LOG}" | grep -oE '[0-9]+ events' | awk '{print $1}' | head -1 || echo "N/A")
  S1_THREADS=$(grep "Thread diversity:" "${S1_LOG}" | grep -oE '[0-9]+ threads' | awk '{print $1}' | head -1 || echo "N/A")
  S1_ALLOC=$(grep "Allocation samples:" "${S1_LOG}" | grep -oE '[0-9]+ events' | awk '{print $1}' | head -1 || echo "N/A")
fi

# Parse scenario 2 (tracer+profiler) results
S2_STATUS="N/A"
S2_SAMPLES="N/A"
S2_THREADS="N/A"
S2_ALLOC="N/A"
S2_LOG="${RESULTS_DIR}/tracer-profiler-${CONFIG_NAME}.log"

if [ -f "${S2_LOG}" ]; then
  if grep -q "SUCCESS: All validations passed" "${S2_LOG}"; then
    S2_STATUS="PASS"
  elif grep -q "VALIDATION_FAILED" "${S2_LOG}"; then
    S2_STATUS="FAIL"
  fi
  S2_SAMPLES=$(grep "ExecutionSample:" "${S2_LOG}" | grep -oE '[0-9]+ events' | awk '{print $1}' | head -1 || echo "N/A")
  S2_THREADS=$(grep "Thread diversity:" "${S2_LOG}" | grep -oE '[0-9]+ threads' | awk '{print $1}' | head -1 || echo "N/A")
  S2_ALLOC=$(grep "Allocation samples:" "${S2_LOG}" | grep -oE '[0-9]+ events' | awk '{print $1}' | head -1 || echo "N/A")
fi

# Calculate overall status
OVERALL_STATUS="PASS"
if [ "${S1_STATUS}" = "FAIL" ] || [ "${S2_STATUS}" = "FAIL" ]; then
  OVERALL_STATUS="FAIL"
fi

# Calculate health scores (samples/sec compared to expected 1.6/sec baseline)
TEST_DURATION=60  # Default test duration (see run-integration-test.sh)
S1_RATE="N/A"
S1_HEALTH="N/A"
S2_RATE="N/A"
S2_HEALTH="N/A"

if [ "${S1_SAMPLES}" != "N/A" ] && [ -n "${S1_SAMPLES}" ]; then
  S1_RATE=$(awk "BEGIN {printf \"%.2f\", ${S1_SAMPLES} / ${TEST_DURATION}}")
  S1_HEALTH=$(awk "BEGIN {printf \"%.0f\", (${S1_RATE} / 1.6) * 100}")
fi

if [ "${S2_SAMPLES}" != "N/A" ] && [ -n "${S2_SAMPLES}" ]; then
  S2_RATE=$(awk "BEGIN {printf \"%.2f\", ${S2_SAMPLES} / ${TEST_DURATION}}")
  S2_HEALTH=$(awk "BEGIN {printf \"%.0f\", (${S2_RATE} / 1.6) * 100}")
fi

# Status emoji
status_emoji() {
  case "$1" in
    PASS) echo "✅" ;;
    FAIL) echo "❌" ;;
    *) echo "⚠️" ;;
  esac
}

# Generate Markdown report
generate_report() {
  cat <<EOF
## ${CONFIG_NAME} - $(status_emoji "${OVERALL_STATUS}") ${OVERALL_STATUS}

**Date:** ${DATE_HUMAN}

### Configuration
| Setting | Value |
|---------|-------|
| Platform | ${LIBC}-${ARCH} |
| JVM | ${JVM_TYPE} |
| Java | ${JDK_VERSION} |
| Container | ${CONTAINER} |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | ${CPU_START} |
| CPU Cores (end) | ${CPU_END} |
| Throttling | ${THROTTLE_PCT}% |

### Test Results

#### Scenario 1: Profiler-Only $(status_emoji "${S1_STATUS}")
| Metric | Value |
|--------|-------|
| Status | ${S1_STATUS} |
| CPU Samples | ${S1_SAMPLES} |
| Sample Rate | ${S1_RATE}/sec |
| Health Score | ${S1_HEALTH}% |
| Threads | ${S1_THREADS} |
| Allocations | ${S1_ALLOC} |

#### Scenario 2: Tracer+Profiler $(status_emoji "${S2_STATUS}")
| Metric | Value |
|--------|-------|
| Status | ${S2_STATUS} |
| CPU Samples | ${S2_SAMPLES} |
| Sample Rate | ${S2_RATE}/sec |
| Health Score | ${S2_HEALTH}% |
| Threads | ${S2_THREADS} |
| Allocations | ${S2_ALLOC} |

EOF

  # Add CPU timeline if available
  if [ -f "${DIAGNOSTICS_DIR}/cpu-timeline.log" ]; then
    local cpu_values=$(awk '{print $2}' "${DIAGNOSTICS_DIR}/cpu-timeline.log" | sort -u | wc -l)
    local cpu_min=$(awk '{print $2}' "${DIAGNOSTICS_DIR}/cpu-timeline.log" | sort -n | head -1)
    local cpu_max=$(awk '{print $2}' "${DIAGNOSTICS_DIR}/cpu-timeline.log" | sort -n | tail -1)

    cat <<EOF
<details>
<summary>CPU Timeline (${cpu_values} unique values: ${cpu_min}-${cpu_max} cores)</summary>

\`\`\`
$(head -20 "${DIAGNOSTICS_DIR}/cpu-timeline.log")
\`\`\`
</details>

EOF
  fi

  echo "---"
  echo ""
}

# Output report
if [ -n "${OUTPUT_FILE}" ]; then
  generate_report > "${OUTPUT_FILE}"
  echo "Report generated: ${OUTPUT_FILE}"
else
  generate_report
fi
