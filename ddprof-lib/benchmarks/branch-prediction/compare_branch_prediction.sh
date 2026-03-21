#!/bin/bash
# Compare branch prediction performance between baseline and optimized builds
# This script helps measure the impact of likely/unlikely hints

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="${SCRIPT_DIR}/../../.."

# Color output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

log_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

log_step() {
    echo -e "${BLUE}[STEP]${NC} $1"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Cleanup worktrees on exit
cleanup() {
    log_info "Cleaning up worktrees..."
    cd "${REPO_ROOT}"

    if [ -n "${BASELINE_WORKTREE}" ] && [ -d "${BASELINE_WORKTREE}" ]; then
        git worktree remove -f "${BASELINE_WORKTREE}" 2>/dev/null || true
    fi

    # Only cleanup optimized worktree if it's not the current repo
    if [ -n "${OPTIMIZED_WORKTREE}" ] && [ "${OPTIMIZED_WORKTREE}" != "${REPO_ROOT}" ] && [ -d "${OPTIMIZED_WORKTREE}" ]; then
        git worktree remove -f "${OPTIMIZED_WORKTREE}" 2>/dev/null || true
    fi
}

trap cleanup EXIT

# Compare two perf stat results
compare_results() {
    local baseline="$1"
    local optimized="$2"

    log_info "=== Performance Comparison ==="
    echo ""

    # Extract metrics
    extract_metric() {
        local file="$1"
        local pattern="$2"
        grep "$pattern" "$file" | awk '{print $1}' | tr -d ',' | head -1
    }

    # Branch misses
    local baseline_br_miss=$(extract_metric "$baseline" "branch-misses")
    local optimized_br_miss=$(extract_metric "$optimized" "branch-misses")

    # L1 icache misses
    local baseline_l1_miss=$(extract_metric "$baseline" "L1-icache-load-misses")
    local optimized_l1_miss=$(extract_metric "$optimized" "L1-icache-load-misses")

    # Instructions
    local baseline_instr=$(extract_metric "$baseline" "instructions")
    local optimized_instr=$(extract_metric "$optimized" "instructions")

    echo "Metric                    | Baseline        | Optimized       | Change"
    echo "--------------------------|-----------------|-----------------|------------------"

    if [ -n "$baseline_br_miss" ] && [ -n "$optimized_br_miss" ]; then
        local change=$(echo "scale=2; ($optimized_br_miss - $baseline_br_miss) * 100 / $baseline_br_miss" | bc)
        printf "Branch misses             | %15s | %15s | %s%%\n" \
               "$(printf '%0s' $baseline_br_miss | sed 's/\(.\{3\}\)/\1,/g' | sed 's/,$//')" \
               "$(printf '%0s' $optimized_br_miss | sed 's/\(.\{3\}\)/\1,/g' | sed 's/,$//')" \
               "$change"
    fi

    if [ -n "$baseline_l1_miss" ] && [ -n "$optimized_l1_miss" ]; then
        local change=$(echo "scale=2; ($optimized_l1_miss - $baseline_l1_miss) * 100 / $baseline_l1_miss" | bc)
        printf "L1 icache misses          | %15s | %15s | %s%%\n" \
               "$(printf '%0s' $baseline_l1_miss | sed 's/\(.\{3\}\)/\1,/g' | sed 's/,$//')" \
               "$(printf '%0s' $optimized_l1_miss | sed 's/\(.\{3\}\)/\1,/g' | sed 's/,$//')" \
               "$change"
    fi

    if [ -n "$baseline_instr" ] && [ -n "$optimized_instr" ]; then
        local change=$(echo "scale=2; ($optimized_instr - $baseline_instr) * 100 / $baseline_instr" | bc)
        printf "Instructions              | %15s | %15s | %s%%\n" \
               "$(printf '%0s' $baseline_instr | sed 's/\(.\{3\}\)/\1,/g' | sed 's/,$//')" \
               "$(printf '%0s' $optimized_instr | sed 's/\(.\{3\}\)/\1,/g' | sed 's/,$//')" \
               "$change"
    fi

    echo ""
    log_info "Negative change % indicates improvement (fewer misses)"
}

main() {
    local benchmark="${1:-akka-uct}"
    local baseline_branch="${2:-main}"
    local optimized_branch="${3:-jb/likely}"

    log_info "=== Branch Prediction Comparison Test ==="
    log_info "Baseline branch: ${baseline_branch}"
    log_info "Optimized branch: ${optimized_branch}"
    log_info "Benchmark: ${benchmark}"
    echo ""

    cd "${REPO_ROOT}"

    # Get current branch
    local current_branch=$(git branch --show-current)

    # Create worktrees for both branches
    BASELINE_WORKTREE="${REPO_ROOT}/../java-profiler-baseline-$$"
    OPTIMIZED_WORKTREE="${REPO_ROOT}/../java-profiler-optimized-$$"

    log_step "1/6: Creating worktree for baseline (${baseline_branch})..."
    git worktree add "${BASELINE_WORKTREE}" "${baseline_branch}"

    log_step "2/6: Creating worktree for optimized (${optimized_branch})..."
    # If we're already on the optimized branch, use current worktree
    if [ "${current_branch}" = "${optimized_branch}" ]; then
        log_info "Already on ${optimized_branch}, using current worktree"
        OPTIMIZED_WORKTREE="${REPO_ROOT}"
    else
        git worktree add "${OPTIMIZED_WORKTREE}" "${optimized_branch}"
    fi

    # Build baseline
    log_step "3/6: Building baseline version..."
    cd "${BASELINE_WORKTREE}"
    ./gradlew ddprof-lib:build -x test

    # Build optimized
    log_step "4/6: Building optimized version..."
    cd "${OPTIMIZED_WORKTREE}"
    ./gradlew ddprof-lib:build -x test

    # Test baseline
    log_step "5/6: Testing baseline version..."
    local baseline_test_script="${OPTIMIZED_WORKTREE}/ddprof-lib/benchmarks/branch-prediction/test_branch_prediction_perf.sh"

    if [ ! -f "${baseline_test_script}" ]; then
        log_error "Test script not found at ${baseline_test_script}"
        log_error "Benchmark scripts may not exist on ${optimized_branch} branch"
        exit 1
    fi

    # Run tests from optimized worktree but with baseline library
    cd "${OPTIMIZED_WORKTREE}/ddprof-lib/benchmarks/branch-prediction"

    # Temporarily override PROFILER_LIB for baseline test
    PROFILER_LIB_OVERRIDE="${BASELINE_WORKTREE}/ddprof-lib/build/lib/main/release/linux/x64/libjavaProfiler.so" \
    "${baseline_test_script}" "${benchmark}" "baseline"

    # Test optimized
    log_step "6/6: Testing optimized version..."
    "${baseline_test_script}" "${benchmark}" "optimized"

    # Compare results
    echo ""
    compare_results \
        "${OPTIMIZED_WORKTREE}/ddprof-lib/benchmarks/branch-prediction/perf_results/baseline_stat.txt" \
        "${OPTIMIZED_WORKTREE}/ddprof-lib/benchmarks/branch-prediction/perf_results/optimized_stat.txt"

    log_info "=== Comparison Complete ==="
    log_info "Detailed results in ${OPTIMIZED_WORKTREE}/ddprof-lib/benchmarks/branch-prediction/perf_results/"
    log_info ""
    log_info "To view detailed perf reports:"
    log_info "  cd ${OPTIMIZED_WORKTREE}/ddprof-lib/benchmarks/branch-prediction/perf_results"
    log_info "  perf report -i baseline_record.data --dsos=libjavaProfiler.so"
    log_info "  perf report -i optimized_record.data --dsos=libjavaProfiler.so"
}

if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo "Usage: $0 [benchmark] [baseline_branch] [optimized_branch]"
    echo ""
    echo "Compares branch prediction performance between two branches using git worktrees"
    echo ""
    echo "Arguments:"
    echo "  benchmark         Renaissance benchmark to use (default: akka-uct)"
    echo "  baseline_branch   Baseline branch (default: main)"
    echo "  optimized_branch  Optimized branch (default: jb/likely)"
    echo ""
    echo "Examples:"
    echo "  $0                           # Compare main vs jb/likely using akka-uct"
    echo "  $0 finagle-chirper           # Compare using finagle-chirper"
    echo "  $0 akka-uct main jb/likely   # Explicit branch names"
    exit 0
fi

main "$@"
