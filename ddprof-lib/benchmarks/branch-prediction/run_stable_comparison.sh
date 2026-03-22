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

# System tuning recommendations (non-interactive)
if [ -t 0 ]; then
    # Only show interactive prompt if stdin is a terminal
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
else
    # Non-interactive mode (nohup, background, etc.)
    log_info "Running in non-interactive mode (nohup/background)"
    log_warn "For best results, ensure system tuning is applied before running"
fi

log_info "Running ${ITERATIONS} iterations of benchmark: ${BENCHMARK}"
echo ""

# Build once before all iterations
log_info "Building baseline and optimized versions (one-time setup)..."
"${COMPARE_SCRIPT}" "${BENCHMARK}" --build-only
echo ""

# Run iterations
for i in $(seq 1 ${ITERATIONS}); do
    log_info "=== Iteration $i/${ITERATIONS} ==="

    # Wait a bit between iterations to let system settle
    if [ $i -gt 1 ]; then
        log_info "Waiting 10 seconds for system to settle..."
        sleep 10
    fi

    # Run comparison (skip build)
    "${COMPARE_SCRIPT}" "${BENCHMARK}" --skip-build

    # Save results (only stat.txt files to save disk space)
    if [ -d perf_results ]; then
        mkdir -p "perf_results_run_${i}"
        cp perf_results/*_stat.txt "perf_results_run_${i}/" 2>/dev/null || true
        log_info "Results saved to perf_results_run_${i}/"
        # Clean up perf_results to save disk space
        rm -rf perf_results
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

    # Calculate standard deviation (handle edge cases)
    local baseline_stddev="0"
    local optimized_stddev="0"

    if [ ${n} -gt 1 ]; then
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

        # Use max(0, variance) to handle floating point errors
        if [ ${baseline_var_sum} -gt 0 ]; then
            baseline_stddev=$(echo "scale=2; sqrt(${baseline_var_sum} / ${n})" | bc 2>/dev/null || echo "0")
        fi
        if [ ${optimized_var_sum} -gt 0 ]; then
            optimized_stddev=$(echo "scale=2; sqrt(${optimized_var_sum} / ${n})" | bc 2>/dev/null || echo "0")
        fi
    fi

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
    baseline_file="perf_results_run_${i}/baseline_stat.txt"
    optimized_file="perf_results_run_${i}/optimized_stat.txt"

    if [ -f "${baseline_file}" ] && [ -f "${optimized_file}" ]; then
        b_instr=$(extract_metric "${baseline_file}" "instructions")
        b_cycles=$(extract_metric "${baseline_file}" "cycles")
        o_instr=$(extract_metric "${optimized_file}" "instructions")
        o_cycles=$(extract_metric "${optimized_file}" "cycles")

        if [ -n "${b_instr}" ] && [ -n "${b_cycles}" ] && [ "${b_cycles}" -gt 0 ]; then
            b_ipc=$(echo "scale=6; ${b_instr} / ${b_cycles}" | bc)
            baseline_ipc_values+=("${b_ipc}")
        fi

        if [ -n "${o_instr}" ] && [ -n "${o_cycles}" ] && [ "${o_cycles}" -gt 0 ]; then
            o_ipc=$(echo "scale=6; ${o_instr} / ${o_cycles}" | bc)
            optimized_ipc_values+=("${o_ipc}")
        fi
    fi
done

if [ ${#baseline_ipc_values[@]} -gt 0 ]; then
    # Calculate mean IPC
    baseline_ipc_sum=0
    optimized_ipc_sum=0
    for val in "${baseline_ipc_values[@]}"; do
        baseline_ipc_sum=$(echo "${baseline_ipc_sum} + ${val}" | bc)
    done
    for val in "${optimized_ipc_values[@]}"; do
        optimized_ipc_sum=$(echo "${optimized_ipc_sum} + ${val}" | bc)
    done

    n=${#baseline_ipc_values[@]}
    baseline_ipc_mean=$(echo "scale=6; ${baseline_ipc_sum} / ${n}" | bc)
    optimized_ipc_mean=$(echo "scale=6; ${optimized_ipc_sum} / ${n}" | bc)

    # Calculate standard deviation (handle edge cases)
    baseline_ipc_stddev="0.000000"
    optimized_ipc_stddev="0.000000"

    if [ ${n} -gt 1 ]; then
        baseline_ipc_var_sum=0
        optimized_ipc_var_sum=0
        for val in "${baseline_ipc_values[@]}"; do
            diff=$(echo "${val} - ${baseline_ipc_mean}" | bc)
            sq=$(echo "${diff} * ${diff}" | bc)
            baseline_ipc_var_sum=$(echo "${baseline_ipc_var_sum} + ${sq}" | bc)
        done
        for val in "${optimized_ipc_values[@]}"; do
            diff=$(echo "${val} - ${optimized_ipc_mean}" | bc)
            sq=$(echo "${diff} * ${diff}" | bc)
            optimized_ipc_var_sum=$(echo "${optimized_ipc_var_sum} + ${sq}" | bc)
        done

        # Check if variance is positive before taking sqrt
        is_positive=$(echo "${baseline_ipc_var_sum} > 0" | bc)
        if [ "${is_positive}" -eq 1 ]; then
            baseline_ipc_stddev=$(echo "scale=6; sqrt(${baseline_ipc_var_sum} / ${n})" | bc 2>/dev/null || echo "0.000000")
        fi
        is_positive=$(echo "${optimized_ipc_var_sum} > 0" | bc)
        if [ "${is_positive}" -eq 1 ]; then
            optimized_ipc_stddev=$(echo "scale=6; sqrt(${optimized_ipc_var_sum} / ${n})" | bc 2>/dev/null || echo "0.000000")
        fi
    fi

    # Calculate change
    ipc_change=$(echo "scale=2; (${optimized_ipc_mean} - ${baseline_ipc_mean}) * 100 / ${baseline_ipc_mean}" | bc)

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

# Generate human-readable summary file
SUMMARY_FILE="benchmark_summary_$(date +%Y%m%d_%H%M%S).txt"
log_info ""
log_info "Generating summary report: ${SUMMARY_FILE}"

cat > "${SUMMARY_FILE}" << EOF
================================================================================
Branch Prediction Benchmark Summary
================================================================================
Generated: $(date)
Benchmark: ${BENCHMARK}
Iterations: ${ITERATIONS}
Baseline branch: main
Optimized branch: jb/likely

================================================================================
Statistical Analysis Results
================================================================================

Metric                    | Baseline (mean ± σ)                | Optimized (mean ± σ)               | Change
--------------------------|------------------------------------|------------------------------------|----------
EOF

# Append the statistics table to file
{
calc_stats "Branch misses" "branch-misses"
calc_stats "L1 icache misses" "L1-icache-load-misses"
calc_stats "Instructions" "instructions"
calc_stats "Cycles" "cycles"

# Re-calculate IPC for file output
if [ ${#baseline_ipc_values[@]} -gt 0 ]; then
    echo "--------------------------|------------------------------------|------------------------------------|----------"
    printf "%-25s | %20s ± %10s | %20s ± %10s | %8s%%\n" \
           "IPC (insn/cycle)" \
           "$(printf "%.3f" ${baseline_ipc_mean})" "$(printf "%.6f" ${baseline_ipc_stddev})" \
           "$(printf "%.3f" ${optimized_ipc_mean})" "$(printf "%.6f" ${optimized_ipc_stddev})" \
           "${ipc_change}"
fi
} >> "${SUMMARY_FILE}"

cat >> "${SUMMARY_FILE}" << EOF

================================================================================
Interpretation
================================================================================
- Negative change % = improvement (fewer misses/cycles)
- Positive IPC change % = improvement (more instructions per cycle)
- Standard deviation (σ) indicates measurement stability

================================================================================
Individual Run Data
================================================================================

EOF

# Append individual run data
for i in $(seq 1 ${ITERATIONS}); do
    echo "--- Iteration $i ---" >> "${SUMMARY_FILE}"
    if [ -f "perf_results_run_${i}/baseline_stat.txt" ]; then
        echo "Baseline:" >> "${SUMMARY_FILE}"
        grep -E "(branch-misses|L1-icache-load-misses|instructions|cycles)" "perf_results_run_${i}/baseline_stat.txt" >> "${SUMMARY_FILE}" 2>/dev/null || echo "  No data" >> "${SUMMARY_FILE}"
    fi
    if [ -f "perf_results_run_${i}/optimized_stat.txt" ]; then
        echo "Optimized:" >> "${SUMMARY_FILE}"
        grep -E "(branch-misses|L1-icache-load-misses|instructions|cycles)" "perf_results_run_${i}/optimized_stat.txt" >> "${SUMMARY_FILE}" 2>/dev/null || echo "  No data" >> "${SUMMARY_FILE}"
    fi
    echo "" >> "${SUMMARY_FILE}"
done

cat >> "${SUMMARY_FILE}" << EOF
================================================================================
End of Report
================================================================================
EOF

log_info "Summary saved to: ${SUMMARY_FILE}"
