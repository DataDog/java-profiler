#!/bin/bash
# Compare branch prediction performance between baseline and optimized builds
# This script helps measure the impact of likely/unlikely hints

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="${SCRIPT_DIR}/../../.."
TEST_SCRIPT="${SCRIPT_DIR}/test_branch_prediction_perf.sh"

# Color output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
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

    log_info "=== Branch Prediction Comparison Test ==="
    log_info "This will test baseline (main) vs optimized (jb/likely) branches"
    log_info "Benchmark: ${benchmark}"
    echo ""

    if [ ! -f "${TEST_SCRIPT}" ]; then
        log_warn "Test script not found at ${TEST_SCRIPT}"
        exit 1
    fi

    # Current branch (should be jb/likely)
    local current_branch=$(git branch --show-current)
    log_info "Current branch: ${current_branch}"

    if [ "${current_branch}" != "jb/likely" ]; then
        log_warn "You are not on jb/likely branch. Switch to it first?"
        read -p "Continue anyway? (y/N) " -n 1 -r
        echo
        if [[ ! $REPLY =~ ^[Yy]$ ]]; then
            exit 1
        fi
    fi

    # Test optimized version (current branch)
    log_step "1/4: Building optimized version (${current_branch})..."
    cd "${REPO_ROOT}"
    ./gradlew ddprof-lib:build -x test
    cd - > /dev/null

    log_step "2/4: Testing optimized version..."
    "${TEST_SCRIPT}" "${benchmark}" "optimized"

    # Switch to main and test baseline
    log_step "3/4: Switching to main branch and building baseline..."
    cd "${REPO_ROOT}"
    git stash push -m "Temporary stash for perf comparison"
    git checkout main
    ./gradlew ddprof-lib:build -x test
    cd - > /dev/null

    log_step "4/4: Testing baseline version..."
    "${TEST_SCRIPT}" "${benchmark}" "baseline"

    # Switch back
    log_info "Switching back to ${current_branch}..."
    cd "${REPO_ROOT}"
    git checkout "${current_branch}"
    git stash pop || true
    cd - > /dev/null

    # Compare results
    echo ""
    compare_results \
        "${SCRIPT_DIR}/perf_results/baseline_stat.txt" \
        "${SCRIPT_DIR}/perf_results/optimized_stat.txt"

    log_info "=== Comparison Complete ==="
    log_info "Detailed results in perf_results/ directory"
    log_info ""
    log_info "To view detailed perf reports:"
    log_info "  perf report -i perf_results/baseline_record.data --dsos=libjavaProfiler.so"
    log_info "  perf report -i perf_results/optimized_record.data --dsos=libjavaProfiler.so"
}

if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo "Usage: $0 [benchmark]"
    echo ""
    echo "Compares branch prediction performance between main and jb/likely branches"
    echo ""
    echo "Arguments:"
    echo "  benchmark   Renaissance benchmark to use (default: akka-uct)"
    echo ""
    echo "Examples:"
    echo "  $0                # Compare using akka-uct"
    echo "  $0 finagle-chirper # Compare using finagle-chirper"
    exit 0
fi

main "$@"
