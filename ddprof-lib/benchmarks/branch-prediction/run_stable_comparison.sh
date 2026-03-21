#!/bin/bash
# Run multiple comparison iterations for statistical confidence
# Attempts to reduce system noise for more stable results

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
COMPARE_SCRIPT="${SCRIPT_DIR}/compare_branch_prediction.sh"
ITERATIONS="${1:-3}"
BENCHMARK="${2:-akka-uct}"

# Color output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

log_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

# System tuning recommendations
log_info "=== System Performance Tuning Recommendations ==="
echo ""
log_warn "For more stable results, consider:"
echo "  1. Set CPU governor to 'performance':"
echo "     sudo cpupower frequency-set -g performance"
echo ""
echo "  2. Disable turbo boost (reduces thermal variance):"
echo "     echo 1 | sudo tee /sys/devices/system/cpu/intel_pmu/allow_tsx_force_abort"
echo ""
echo "  3. Pin to specific CPUs (if using taskset with the benchmark)"
echo ""
echo "  4. Ensure system is idle (no background jobs)"
echo ""
read -p "Press Enter to continue or Ctrl-C to abort..."
echo ""

log_info "Running ${ITERATIONS} iterations of benchmark: ${BENCHMARK}"
echo ""

# Run iterations
for i in $(seq 1 ${ITERATIONS}); do
    log_info "=== Iteration $i/${ITERATIONS} ==="

    # Wait a bit between iterations to let system settle
    if [ $i -gt 1 ]; then
        log_info "Waiting 10 seconds for system to settle..."
        sleep 10
    fi

    # Run comparison
    "${COMPARE_SCRIPT}" "${BENCHMARK}"

    # Save results
    if [ -d perf_results ]; then
        mkdir -p "perf_results_run_${i}"
        cp -r perf_results/* "perf_results_run_${i}/"
        log_info "Results saved to perf_results_run_${i}/"
    fi

    echo ""
done

log_info "=== All iterations complete ==="
log_info "Results saved in perf_results_run_*/ directories"
log_info ""
log_info "To analyze variance, compare the stat.txt files across runs"
