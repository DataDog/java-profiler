# Branch Prediction Performance Testing

This guide explains how to measure the performance impact of branch prediction hints (likely/unlikely) using `perf` and Renaissance benchmarks.

## Prerequisites

1. **Renaissance benchmarks JAR** - Will be automatically downloaded to this directory if not present
   - Version 0.16.1 will be downloaded from: https://github.com/renaissance-benchmarks/renaissance/releases
   - Manual download is not required

2. **perf tool** - Install if not present:
   ```bash
   # For AWS EC2 instances:
   sudo apt-get install linux-tools-$(uname -r) linux-tools-aws

   # For generic Ubuntu/Debian:
   sudo apt-get install linux-tools-common linux-tools-generic linux-tools-$(uname -r)
   ```

3. **perf permissions** - Allow non-root perf access:
   ```bash
   sudo sysctl -w kernel.perf_event_paranoid=1
   ```

## Quick Start

### Option 1: Single Test Run

Test the current build:

```bash
./test_branch_prediction_perf.sh [benchmark] [test_name]
```

Examples:
```bash
# Test with default benchmark (akka-uct)
./test_branch_prediction_perf.sh

# Test with specific benchmark
./test_branch_prediction_perf.sh finagle-chirper optimized

# Test another benchmark
./test_branch_prediction_perf.sh scala-kmeans baseline
```

### Option 2: Automated Comparison (Recommended)

Compare main branch (baseline) vs jb/likely branch (optimized):

```bash
./compare_branch_prediction.sh [benchmark]
```

This will:
1. Build and test the optimized version (jb/likely)
2. Switch to main and build baseline
3. Test baseline version
4. Switch back to jb/likely
5. Display comparison table

## Understanding the Output

### perf stat Metrics

The test collects these key metrics:

- **branch-misses**: Number of mispredicted branches
  - Lower is better
  - Likely/unlikely hints should reduce this

- **L1-icache-load-misses**: L1 instruction cache misses
  - Lower is better
  - Better code layout can improve this

- **instructions**: Total instructions executed
  - Should be similar between runs

- **cycles**: Total CPU cycles
  - Lower is better overall

### Output Files

All results are saved to `perf_results/`:

- `{test_name}_stat.txt`: Summary statistics
- `{test_name}_record.data`: Raw perf recording
- `{test_name}_record_report.txt`: Detailed report filtered to libjavaProfiler.so

## Detailed Analysis

### View Interactive Report

```bash
perf report -i perf_results/optimized_record.data --dsos=libjavaProfiler.so
```

This shows hotspots and call graphs for the profiler library.

### Compare Specific Functions

```bash
# Baseline
perf report -i perf_results/baseline_record.data \
    --dsos=libjavaProfiler.so \
    --stdio | grep -A 10 "functionName"

# Optimized
perf report -i perf_results/optimized_record.data \
    --dsos=libjavaProfiler.so \
    --stdio | grep -A 10 "functionName"
```

### Manual perf Commands (as in PR description)

If you want to run perf manually:

```bash
# Start Renaissance benchmark
java -agentpath:ddprof-lib/build/lib/main/release/linux/x64/libjavaProfiler.so \
     -jar ~/renaissance-gpl-0.16.1.jar \
     akka-uct -r 9999 &
PID=$!

# Collect statistics for 60 seconds
perf stat -e branch-misses,L1-icache-load-misses,instructions \
  -p ${PID} -- sleep 60

# Record detailed data
perf record -e L1-icache-load-misses -g -p ${PID} -- sleep 60

# View report
perf report --dsos=libjavaProfiler.so
```

## Recommended Benchmarks

These Renaissance benchmarks work well for profiler testing:

- **akka-uct** (default): Actor-based workload, good CPU usage
- **finagle-chirper**: High concurrency, network-like patterns
- **scala-kmeans**: CPU-intensive computation
- **future-genetic**: Async/future-heavy workload

## Interpreting Results

### What to Look For

1. **Branch Miss Reduction**:
   - A reduction in branch-misses indicates better prediction
   - Even 1-2% improvement is meaningful at scale

2. **I-cache Impact**:
   - L1-icache-load-misses changes indicate code layout effects
   - May increase slightly if code size grows

3. **Overall Performance**:
   - Check cycles and instructions
   - IPC (instructions per cycle) = instructions / cycles
   - Higher IPC is better

### Expected Impact

Branch prediction hints typically provide:
- 1-5% reduction in branch misses for hot paths
- Minimal impact on total instruction count
- Slight improvement in overall cycles (if hints are correct)

## Troubleshooting

### Permission Denied

```bash
sudo sysctl -w kernel.perf_event_paranoid=1
```

Or run the script with sudo (not recommended).

### Renaissance JAR Not Found

The script will automatically download it. If automatic download fails:
- Check your internet connection
- Download manually from: https://github.com/renaissance-benchmarks/renaissance/releases
- Place in the same directory as the test scripts

### Profiler Library Not Built

```bash
./gradlew ddprof-lib:build
```

### High Variance in Results

- Increase test duration in the script (default: 60s)
- Ensure system is idle (no other heavy processes)
- Run multiple iterations and average results
- Pin CPU affinity for more stable results

## Advanced Usage

### Multiple Runs for Statistical Confidence

```bash
for i in {1..5}; do
    ./test_branch_prediction_perf.sh akka-uct "run_$i"
done
```

Then average the results.

### Different Perf Events

Edit the script to add more events:

```bash
perf stat -e branch-misses,branches,branch-load-misses \
          -e L1-dcache-load-misses,L1-dcache-loads \
          -e LLC-load-misses,LLC-loads \
          -e cpu-cycles,instructions \
          ...
```

See available events: `perf list`

### Flame Graphs

Generate flame graphs for visual analysis:

```bash
perf record -F 999 -g -p ${PID} -- sleep 60
perf script | stackcollapse-perf.pl | flamegraph.pl > flamegraph.svg
```

Requires: https://github.com/brendangregg/FlameGraph
