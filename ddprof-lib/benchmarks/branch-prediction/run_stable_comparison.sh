#!/bin/bash
# Run multiple comparison iterations for statistical confidence
# Attempts to reduce system noise for more stable results

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
COMPARE_SCRIPT="${SCRIPT_DIR}/compare_branch_prediction.sh"
ITERATIONS="${1:-3}"
BENCHMARK="${2:-akka-uct}"

# Change to script directory to ensure perf_results/ is in the right place
cd "${SCRIPT_DIR}"

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

# Statistical analysis
log_info "=== Statistical Analysis ==="
echo ""

# Extract metric from a stat file
extract_metric() {
    local file="$1"
    local pattern="$2"
    local value=$(grep "$pattern" "$file" | awk '{print $1}' | head -1)
    # Return empty if value contains < (like <not counted>)
    if [[ "$value" =~ \< ]]; then
        echo ""
    else
        echo "$value" | tr -d ','
    fi
}

# Calculate statistics for a metric
calc_stats() {
    local metric_name="$1"
    local pattern="$2"
    local baseline_values=()
    local optimized_values=()

    # Collect all values
    for i in $(seq 1 ${ITERATIONS}); do
        local baseline_file="perf_results_run_${i}/baseline_stat.txt"
        local optimized_file="perf_results_run_${i}/optimized_stat.txt"

        if [ -f "${baseline_file}" ] && [ -f "${optimized_file}" ]; then
            local bval=$(extract_metric "${baseline_file}" "${pattern}")
            local oval=$(extract_metric "${optimized_file}" "${pattern}")

            if [ -n "${bval}" ] && [ -n "${oval}" ]; then
                baseline_values+=("${bval}")
                optimized_values+=("${oval}")
            fi
        fi
    done

    if [ ${#baseline_values[@]} -eq 0 ]; then
        echo "${metric_name}: No data"
        return
    fi

    # Calculate mean
    local baseline_sum=0
    local optimized_sum=0
    for val in "${baseline_values[@]}"; do
        baseline_sum=$((baseline_sum + val))
    done
    for val in "${optimized_values[@]}"; do
        optimized_sum=$((optimized_sum + val))
    done

    local n=${#baseline_values[@]}
    local baseline_mean=$((baseline_sum / n))
    local optimized_mean=$((optimized_sum / n))

    # Calculate standard deviation
    local baseline_var_sum=0
    local optimized_var_sum=0
    for val in "${baseline_values[@]}"; do
        local diff=$((val - baseline_mean))
        baseline_var_sum=$((baseline_var_sum + diff * diff))
    done
    for val in "${optimized_values[@]}"; do
        local diff=$((val - optimized_mean))
        optimized_var_sum=$((optimized_var_sum + diff * diff))
    done

    local baseline_stddev=$(echo "scale=2; sqrt(${baseline_var_sum} / ${n})" | bc)
    local optimized_stddev=$(echo "scale=2; sqrt(${optimized_var_sum} / ${n})" | bc)

    # Calculate change
    local change=$(echo "scale=2; (${optimized_mean} - ${baseline_mean}) * 100 / ${baseline_mean}" | bc)

    # Format output with thousand separators
    local baseline_formatted=$(printf "%'d" ${baseline_mean})
    local optimized_formatted=$(printf "%'d" ${optimized_mean})

    printf "%-25s | %20s ± %10s | %20s ± %10s | %8s%%\n" \
           "${metric_name}" \
           "${baseline_formatted}" "${baseline_stddev}" \
           "${optimized_formatted}" "${optimized_stddev}" \
           "${change}"
}

echo "Metric                    | Baseline (mean ± σ)                | Optimized (mean ± σ)               | Change"
echo "--------------------------|------------------------------------|------------------------------------|----------"

calc_stats "Branch misses" "branch-misses"
calc_stats "L1 icache misses" "L1-icache-load-misses"
calc_stats "Instructions" "instructions"
calc_stats "Cycles" "cycles"

# Calculate IPC statistics
baseline_ipc_values=()
optimized_ipc_values=()

for i in $(seq 1 ${ITERATIONS}); do
    local baseline_file="perf_results_run_${i}/baseline_stat.txt"
    local optimized_file="perf_results_run_${i}/optimized_stat.txt"

    if [ -f "${baseline_file}" ] && [ -f "${optimized_file}" ]; then
        local b_instr=$(extract_metric "${baseline_file}" "instructions")
        local b_cycles=$(extract_metric "${baseline_file}" "cycles")
        local o_instr=$(extract_metric "${optimized_file}" "instructions")
        local o_cycles=$(extract_metric "${optimized_file}" "cycles")

        if [ -n "${b_instr}" ] && [ -n "${b_cycles}" ] && [ "${b_cycles}" -gt 0 ]; then
            local b_ipc=$(echo "scale=6; ${b_instr} / ${b_cycles}" | bc)
            baseline_ipc_values+=("${b_ipc}")
        fi

        if [ -n "${o_instr}" ] && [ -n "${o_cycles}" ] && [ "${o_cycles}" -gt 0 ]; then
            local o_ipc=$(echo "scale=6; ${o_instr} / ${o_cycles}" | bc)
            optimized_ipc_values+=("${o_ipc}")
        fi
    fi
done

if [ ${#baseline_ipc_values[@]} -gt 0 ]; then
    # Calculate mean IPC
    local baseline_ipc_sum=0
    local optimized_ipc_sum=0
    for val in "${baseline_ipc_values[@]}"; do
        baseline_ipc_sum=$(echo "${baseline_ipc_sum} + ${val}" | bc)
    done
    for val in "${optimized_ipc_values[@]}"; do
        optimized_ipc_sum=$(echo "${optimized_ipc_sum} + ${val}" | bc)
    done

    local n=${#baseline_ipc_values[@]}
    local baseline_ipc_mean=$(echo "scale=6; ${baseline_ipc_sum} / ${n}" | bc)
    local optimized_ipc_mean=$(echo "scale=6; ${optimized_ipc_sum} / ${n}" | bc)

    # Calculate standard deviation
    local baseline_ipc_var_sum=0
    local optimized_ipc_var_sum=0
    for val in "${baseline_ipc_values[@]}"; do
        local diff=$(echo "${val} - ${baseline_ipc_mean}" | bc)
        local sq=$(echo "${diff} * ${diff}" | bc)
        baseline_ipc_var_sum=$(echo "${baseline_ipc_var_sum} + ${sq}" | bc)
    done
    for val in "${optimized_ipc_values[@]}"; do
        local diff=$(echo "${val} - ${optimized_ipc_mean}" | bc)
        local sq=$(echo "${diff} * ${diff}" | bc)
        optimized_ipc_var_sum=$(echo "${optimized_ipc_var_sum} + ${sq}" | bc)
    done

    local baseline_ipc_stddev=$(echo "scale=6; sqrt(${baseline_ipc_var_sum} / ${n})" | bc)
    local optimized_ipc_stddev=$(echo "scale=6; sqrt(${optimized_ipc_var_sum} / ${n})" | bc)

    # Calculate change
    local ipc_change=$(echo "scale=2; (${optimized_ipc_mean} - ${baseline_ipc_mean}) * 100 / ${baseline_ipc_mean}" | bc)

    echo "--------------------------|------------------------------------|------------------------------------|----------"
    printf "%-25s | %20s ± %10s | %20s ± %10s | %8s%%\n" \
           "IPC (insn/cycle)" \
           "$(printf "%.3f" ${baseline_ipc_mean})" "$(printf "%.6f" ${baseline_ipc_stddev})" \
           "$(printf "%.3f" ${optimized_ipc_mean})" "$(printf "%.6f" ${optimized_ipc_stddev})" \
           "${ipc_change}"
fi

echo ""
log_info "n=${ITERATIONS} iterations"
log_info "Negative change % indicates improvement (fewer misses/cycles)"
log_info "Positive IPC change % indicates improvement (more instructions per cycle)"
log_info ""
log_info "Individual run results in perf_results_run_*/ directories"
