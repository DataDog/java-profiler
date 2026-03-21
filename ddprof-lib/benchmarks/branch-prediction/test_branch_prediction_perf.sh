#!/bin/bash
# Performance test script for branch prediction hints (likely/unlikely)
# Uses Renaissance benchmarks to generate realistic load

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="${SCRIPT_DIR}/../../.."
RENAISSANCE_VERSION="0.16.1"
RENAISSANCE_JAR="${SCRIPT_DIR}/renaissance-gpl-${RENAISSANCE_VERSION}.jar"
# Allow override for comparison testing
PROFILER_LIB="${PROFILER_LIB_OVERRIDE:-${REPO_ROOT}/ddprof-lib/build/lib/main/release/linux/x64/libjavaProfiler.so}"
DURATION=60  # seconds for perf measurement
WARMUP=30    # seconds to warmup before measurement

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

log_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Download Renaissance JAR if not present
download_renaissance() {
    if [ -f "${RENAISSANCE_JAR}" ]; then
        log_info "Renaissance JAR found at ${RENAISSANCE_JAR}"
        return 0
    fi

    log_info "Renaissance JAR not found, downloading version ${RENAISSANCE_VERSION}..."
    local url="https://github.com/renaissance-benchmarks/renaissance/releases/download/v${RENAISSANCE_VERSION}/renaissance-gpl-${RENAISSANCE_VERSION}.jar"

    if command -v curl &> /dev/null; then
        curl -L -o "${RENAISSANCE_JAR}" "${url}"
    elif command -v wget &> /dev/null; then
        wget -O "${RENAISSANCE_JAR}" "${url}"
    else
        log_error "Neither curl nor wget found. Please install one of them."
        exit 1
    fi

    if [ ! -f "${RENAISSANCE_JAR}" ]; then
        log_error "Failed to download Renaissance JAR"
        exit 1
    fi

    log_info "Successfully downloaded Renaissance JAR"
}

# Check prerequisites
check_prerequisites() {
    log_info "Checking prerequisites..."

    download_renaissance

    if ! command -v perf &> /dev/null; then
        log_error "perf not found. Please install linux-tools package."
        exit 1
    fi

    if [ ! -f "${PROFILER_LIB}" ]; then
        log_error "Profiler library not found at ${PROFILER_LIB}"
        log_info "Please build the profiler first: ./gradlew ddprof-lib:build"
        exit 1
    fi

    # Check perf permissions
    if [ "$(cat /proc/sys/kernel/perf_event_paranoid)" -gt 1 ]; then
        log_warn "perf_event_paranoid is restrictive. You may need to run:"
        log_warn "  sudo sysctl -w kernel.perf_event_paranoid=1"
        log_warn "  or run this script with sudo"
    fi
}

# Start Renaissance benchmark in background
start_benchmark() {
    local benchmark="${1:-akka-uct}"
    log_info "Starting Renaissance benchmark: ${benchmark}"

    # Disable DD Java agent injection to avoid conflicts
    # Run many iterations to keep benchmark running during perf measurement
    env -u JAVA_TOOL_OPTIONS \
    java -agentpath:"${PROFILER_LIB}=start,cpu,file=/tmp/test.jfr" \
         -Xmx2g \
         -Xms2g \
         -jar "${RENAISSANCE_JAR}" \
         "${benchmark}" \
         -r 9999 \
         &> /tmp/renaissance_${benchmark}.log &

    JAVA_PID=$!
    echo ${JAVA_PID} > /tmp/java_perf_test.pid

    log_info "Java process started with PID: ${JAVA_PID}"

    # Verify process started successfully
    sleep 2
    if ! kill -0 ${JAVA_PID} 2>/dev/null; then
        log_error "Java process ${JAVA_PID} died immediately. Check /tmp/renaissance_${benchmark}.log"
        exit 1
    fi

    log_info "Warming up for ${WARMUP} seconds..."
    sleep ${WARMUP}

    # Verify still running after warmup
    if ! kill -0 ${JAVA_PID} 2>/dev/null; then
        log_error "Java process ${JAVA_PID} died during warmup. Check /tmp/renaissance_${benchmark}.log"
        exit 1
    fi
}

# Run perf stat to collect branch prediction statistics
run_perf_stat() {
    local pid=$1
    local output_file="${2:-perf_stat_results.txt}"

    log_info "Running perf stat for ${DURATION} seconds..."

    perf stat -e branch-misses,branches \
              -e L1-icache-load-misses,L1-icache-loads \
              -e instructions,cycles \
              -e cache-misses,cache-references \
              -p ${pid} \
              -- sleep ${DURATION} \
              2>&1 | tee "${output_file}"

    log_info "perf stat results saved to ${output_file}"
}

# Run perf record for detailed analysis
run_perf_record() {
    local pid=$1
    local output_file="${2:-perf_record.data}"

    log_info "Running perf record for ${DURATION} seconds..."

    perf record -e L1-icache-load-misses,branch-misses \
                -g -F 999 \
                -p ${pid} \
                -o "${output_file}" \
                -- sleep ${DURATION}

    log_info "perf record data saved to ${output_file}"

    # Generate report focused on our library
    log_info "Generating perf report for libjavaProfiler.so..."
    perf report -i "${output_file}" \
                --dsos=libjavaProfiler.so \
                --stdio \
                > "${output_file%.data}_report.txt"

    log_info "Report saved to ${output_file%.data}_report.txt"
}

# Stop the benchmark
stop_benchmark() {
    if [ -f /tmp/java_perf_test.pid ]; then
        local pid=$(cat /tmp/java_perf_test.pid)
        log_info "Stopping Java process ${pid}..."
        kill ${pid} 2>/dev/null || true
        sleep 2
        kill -9 ${pid} 2>/dev/null || true
        rm -f /tmp/java_perf_test.pid
    fi
}

# Parse and display results
display_results() {
    local stat_file="$1"

    log_info "=== Performance Summary ==="

    if [ -f "${stat_file}" ]; then
        echo ""
        grep -E "(branch-misses|L1-icache-load-misses|instructions|cycles)" "${stat_file}" || true
        echo ""

        # Calculate branch miss rate if available
        local misses=$(grep "branch-misses" "${stat_file}" | awk '{print $1}' | tr -d ',')
        local total=$(grep -w "branches" "${stat_file}" | awk '{print $1}' | tr -d ',')

        if [ -n "${misses}" ] && [ -n "${total}" ] && [ "${total}" -gt 0 ]; then
            local rate=$(echo "scale=4; ${misses} * 100 / ${total}" | bc)
            log_info "Branch miss rate: ${rate}%"
        fi
    fi
}

# Cleanup on exit
cleanup() {
    log_info "Cleaning up..."
    stop_benchmark
}

trap cleanup EXIT

# Main test flow
main() {
    local benchmark="${1:-akka-uct}"
    local test_name="${2:-likely_test}"

    log_info "=== Branch Prediction Performance Test ==="
    log_info "Benchmark: ${benchmark}"
    log_info "Test name: ${test_name}"
    echo ""

    check_prerequisites

    # Create output directory
    mkdir -p perf_results
    cd perf_results

    # Start the benchmark
    start_benchmark "${benchmark}"

    # Run perf stat
    run_perf_stat ${JAVA_PID} "${test_name}_stat.txt"

    # Run perf record
    run_perf_record ${JAVA_PID} "${test_name}_record.data"

    # Display results
    display_results "${test_name}_stat.txt"

    # Stop benchmark
    stop_benchmark

    log_info "=== Test Complete ==="
    log_info "Results available in perf_results/ directory:"
    log_info "  - ${test_name}_stat.txt: Statistics summary"
    log_info "  - ${test_name}_record.data: Raw perf data"
    log_info "  - ${test_name}_record_report.txt: Detailed report"
    echo ""
    log_info "To view interactive report:"
    log_info "  perf report -i perf_results/${test_name}_record.data --dsos=libjavaProfiler.so"
}

# Show usage
usage() {
    echo "Usage: $0 [benchmark] [test_name]"
    echo ""
    echo "Arguments:"
    echo "  benchmark   Renaissance benchmark to run (default: akka-uct)"
    echo "  test_name   Name for output files (default: likely_test)"
    echo ""
    echo "Available benchmarks: akka-uct, finagle-chirper, fj-kmeans, future-genetic,"
    echo "                     movie-lens, neo4j-analytics, reactors, scala-kmeans, etc."
    echo ""
    echo "Examples:"
    echo "  $0                          # Run with defaults"
    echo "  $0 akka-uct baseline        # Run akka-uct, save as 'baseline'"
    echo "  $0 finagle-chirper likely   # Run finagle-chirper, save as 'likely'"
}

if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    usage
    exit 0
fi

main "$@"
