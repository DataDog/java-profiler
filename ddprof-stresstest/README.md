# ddprof-stresstest - Performance Benchmarking Suite

## Overview

This module contains JMH-based performance benchmarks for the Java Profiler. The benchmarks are organized into two main categories:

- **Throughput Benchmarks** (`scenarios.throughput`): Measure raw performance and scalability
- **Counter Benchmarks** (`scenarios.counters`): Measure feature-specific behavior with profiler metrics

## Prerequisites

### Running Benchmarks

All benchmarks require the WhiteboxProfiler to be enabled, which starts/stops the profiler between iterations and collects internal metrics.

### Basic JMH Commands

**Run all benchmarks:**
```bash
./gradlew :ddprof-stresstest:jmh
```

**Run specific benchmark class:**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  CallTraceStorageQuickBenchmark
```

**Run specific benchmark method:**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  CallTraceStorageBaselineBenchmark.baseline01Thread
```

### Common Options

- `-Pjmh.fork=N`: Number of JVM forks (default: 3)
- `-Pjmh.wi=N`: Warmup iterations (default: 3-5)
- `-Pjmh.i=N`: Measurement iterations (default: 3-5)
- `-Pjmh.wt=N`: Warmup time in seconds (default: 1-2)
- `-Pjmh.t=N`: Measurement time in seconds (default: 3-5)
- `-Pjmh.resultFormat=json|csv|text`: Output format
- `-Pjmh.resultFile=path`: Output file path
- `-Pjmh.prof='profiler'`: JMH profiler to use

### Fast Iterations for Development

```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  -Pjmh.fork=1 -Pjmh.wi=1 -Pjmh.i=2 \
  YourBenchmark
```

## Throughput Benchmarks

Located in `scenarios.throughput.*`

### Profiler Throughput Benchmarks

Measure end-to-end profiling engine performance including signal handlers, stack walking, CallTraceStorage operations, and JFR processing under various thread lifecycle patterns.

**Quick smoke test (~2 minutes):**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  ProfilerThroughputQuickBenchmark
```

**Baseline scaling (~12 minutes):**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  ProfilerThroughputBaselineBenchmark
```

**Thread churn (~20-30 minutes):**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  ProfilerThroughputThreadChurnBenchmark
```

**Slot exhaustion (~15-20 minutes):**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  ProfilerThroughputSlotExhaustionBenchmark
```

**Documentation**: See `doc/architecture/CallTraceStorage.md` for detailed CallTraceStorage architecture, benchmark results analysis, and optimization recommendations.

### ThreadContext Benchmarks

Compare performance of JNI-based native vs DirectByteBuffer-based Java implementations for thread context storage.

```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  ThreadContextBenchmark
```

Tests various thread counts to measure both single-threaded overhead and multi-threaded contention.

### ThreadFilter Benchmarks

Measure thread filtering performance and overhead.

```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  scenarios.throughput.ThreadFilterBenchmark
```

## Counter Benchmarks

Located in `scenarios.counters.*`

These benchmarks focus on measuring specific profiler features with metric collection enabled.

### TracedParallelWork

Measures profiler behavior under parallel work with distributed tracing context propagation.

```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  TracedParallelWork
```

**Parameters:**
- `tagCardinality`: Number of unique tag values (10, 100, 1000)
- `command`: Profiler configuration with attributes

### DumpRecording

Measures overhead of JFR recording dump operations.

```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  DumpRecording
```

### GraphMutation / GraphState

Measures profiler performance with complex object graph mutations.

```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  GraphMutation
```

### NanoTime

Measures timing overhead and profiler impact on high-frequency time measurements.

```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  NanoTime
```

### CapturingLambdas

Measures profiler impact on lambda capture and invocation performance.

```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  CapturingLambdas
```

### ThreadFilter (Counters)

Thread filtering with counter metrics collection.

```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  scenarios.counters.ThreadFilterBenchmark
```

## Saving Results

### JSON Output
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  -Pjmh.resultFormat=json \
  -Pjmh.resultFile=build/benchmark-results.json \
  YourBenchmark
```

### CSV Output
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.resultFormat=csv \
  -Pjmh.resultFile=build/benchmark-results.csv \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  YourBenchmark
```

## Customizing Parameters

Override benchmark parameters:
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  -Pjmh.p='command=cpu=50us,wall=50us' \
  YourBenchmark
```

## Troubleshooting

### "No benchmarks matched the filter"
Use simple class names, not regex patterns:
- ❌ Wrong: `-Pjmh.includes='.*CallTrace.*'`
- ✅ Right: `CallTraceStorageQuickBenchmark`

### Benchmark takes too long
Use reduced iterations:
```bash
-Pjmh.fork=1 -Pjmh.wi=1 -Pjmh.i=1
```

### Profiler fails to start
Verify profiler library loads:
```bash
./gradlew :ddprof-test:testdebug -Ptests=JavaProfilerTest.testGetInstance
```

**Note**: The `-Ptests` property works uniformly across all platforms with config-specific test tasks.

### Out of memory errors
- Reduce concurrent thread counts
- Use smaller parameter values
- Increase JVM heap: `-Pjmh.jvmArgs='-Xmx4g'`

## CI Integration

For CI environments with reduced iterations:
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  -Pjmh.fork=1 -Pjmh.wi=2 -Pjmh.i=3 \
  -Pjmh.resultFormat=json \
  -Pjmh.resultFile=build/ci-results.json \
  CallTraceStorageQuickBenchmark
```

## Project Structure

```
ddprof-stresstest/
├── README.md                           # This file
├── src/jmh/java/
│   └── com/datadoghq/profiler/stresstest/
│       ├── Configuration.java          # Base benchmark configuration
│       ├── WhiteboxProfiler.java       # Custom JMH profiler
│       └── scenarios/
│           ├── throughput/             # Raw performance benchmarks
│           │   ├── ProfilerThroughput* # End-to-end profiling engine suite
│           │   ├── ThreadContext*      # ThreadContext benchmarks
│           │   └── ThreadFilter*       # ThreadFilter benchmarks
│           └── counters/               # Feature-specific benchmarks
│               ├── TracedParallelWork  # Distributed tracing overhead
│               ├── DumpRecording       # JFR dump overhead
│               ├── GraphMutation       # Object graph mutations
│               ├── NanoTime            # Timing overhead
│               ├── CapturingLambdas    # Lambda performance
│               └── ThreadFilter*       # Thread filtering with counters
```

## Documentation

- **CallTraceStorage Architecture**: `doc/architecture/CallTraceStorage.md` - Detailed triple-buffer architecture, benchmark results, and optimization guide
- **Main README**: `README.md` (project root) - General project overview
- **Build Configuration**: `CLAUDE.md` - Build system and development guidelines

## Contributing

When adding new benchmarks:

1. Place in appropriate category (`throughput` or `counters`)
2. Extend `Configuration.java` for common setup
3. Use `WhiteboxProfiler` for profiler metric collection
4. Document in this README with:
   - Purpose
   - Example command
   - Key parameters
5. Add detailed analysis to `doc/` if architectural (like CallTraceStorage)

## Performance Targets

Benchmarks help establish and validate:

- **Scalability**: Linear scaling up to core count
- **Overhead**: <5% impact on application performance
- **Throughput**: Millions of samples per second
- **Latency**: <1μs per profiling operation
- **Memory**: Bounded memory usage under load

Run benchmarks before and after changes to validate performance regressions.
