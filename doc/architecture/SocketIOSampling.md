# Socket I/O Sampling Design

## Overview

This document describes the adaptive sampling mechanism for Socket I/O profiling in the Datadog Java Profiler. The design ensures statistically representative data collection while maintaining controlled overhead and predictable event emission rates.

## Motivation

High-throughput applications using Netty can generate 100,000+ socket I/O operations per minute. Capturing every operation with full stacktraces would:
- Overwhelm the profiler backend with events
- Add significant overhead via `getcontext()` and stack walking
- Produce unmanageably large JFR files

The sampling mechanism addresses these concerns while preserving statistical accuracy.

## Design Goals

1. **Bounded Event Rate**: Maintain ~6,000 sampled events per minute (configurable)
2. **Statistical Representativeness**: Samples should accurately represent the full workload
3. **Outlier Coverage**: Always capture slow operations (>300ms by default)
4. **Low Overhead**: Avoid expensive operations for skipped events
5. **Adaptive Control**: Automatically adjust to varying workload characteristics

## Sampling Strategy

### Two-Tier Approach

The implementation uses **stratified sampling** with two populations:

#### 1. Outlier Population (Census)
- **Threshold**: Operations with duration ≥ 300ms (configurable)
- **Sampling Rate**: 100% (complete census)
- **Weight**: 1.0 (no upscaling needed)
- **Rationale**: Slow operations are critical for performance diagnosis and rare enough to capture all

#### 2. Normal Operation Population (Exponential Sampling)
- **Sampling**: Duration-based exponential distribution
- **Weight**: Calculated per-sample for unbiased estimation
- **Rate Control**: PID controller adjusts sampling interval to maintain target event rate

## Exponential Duration-Based Sampling

### Mechanism

Following the approach used in JVMTI heap sampling ([JEP 331](https://openjdk.org/jeps/331)) and similar to [heapprofd](https://perfetto.dev/docs/design-docs/heapprofd-sampling):

1. **Draw Skip Duration**: Sample from exponential distribution with mean = `sampling_interval_ns`
   ```
   duration_to_skip = exponential_dist(λ = 1/interval)
   ```

2. **Accumulate Duration**: For each operation, subtract its duration from the skip budget:
   ```
   duration_until_next_sample -= operation_duration
   ```

3. **Sample on Threshold**: When accumulated duration crosses zero, capture the event

4. **Reset**: Draw new skip duration and repeat

### Statistical Properties

- **Unbiased**: Longer operations have proportionally higher sampling probability
- **Poisson Process**: Inter-sample durations follow exponential distribution
- **No Bias**: Avoids periodic sampling artifacts

### Weight Calculation

Each sampled normal operation receives a weight to correct for sampling bias:

```cpp
weight = 1.0 / (1.0 - exp(-duration / sampling_interval))
```

This formula ensures that:
- Short operations (duration << interval) get higher weights (less likely to be sampled)
- Long operations (duration >> interval) get weights close to 1.0 (almost always sampled)
- The expected value equals the true population

## Adaptive Rate Control

### PID Controller

A PID (Proportional-Integral-Derivative) controller dynamically adjusts `sampling_interval_ns` to maintain the target event rate:

```cpp
PidController(
    target = 100 events/sec,  // ~6k/min default
    Kp = 31,   // Proportional gain - react quickly to bursts
    Ki = 511,  // Integral gain - focus on long-term rate
    Kd = 3     // Derivative gain - handle abrupt changes
)
```

### Feedback Loop

Every 1 second (or every `target_samples_per_window` events):

1. **Measure**: Count events emitted in time window
2. **Compare**: Calculate error = target - actual
3. **Adjust**:
   - If too many events → increase `sampling_interval_ns` (skip more)
   - If too few events → decrease `sampling_interval_ns` (sample more)

### Behavior Under Different Workloads

| Workload Scenario | System Response |
|-------------------|-----------------|
| High-frequency fast I/O | Interval increases → sample less frequently |
| Low-frequency I/O | Interval decreases to configured minimum |
| Many outliers (>300ms) | Outliers counted toward rate limit → interval increases for normals |
| Bursty traffic | PID dampens oscillations via integral/derivative terms |

## Per-Thread State

Each thread maintains independent sampling state:

```cpp
struct ThreadSamplingState {
    int64_t duration_until_next_sample;  // Current skip budget (ns)
    std::mt19937_64 rng;                 // Random number generator
    std::exponential_distribution<double> exp_dist;  // Distribution
};
```

**Thread-local state advantages**:
- No cross-thread synchronization for sampling decisions
- Each thread's I/O is sampled independently
- Natural load balancing across threads

## Data Upscaling and Analysis

### Backend Calculation

To reconstruct full population statistics from samples:

```python
# Separate populations
outliers = [s for s in samples if s.is_outlier]
normals = [s for s in samples if not s.is_outlier]

# Outliers: exact count (weight=1)
outlier_count = len(outliers)
outlier_total_duration = sum(s.duration for s in outliers)
outlier_total_bytes = sum(s.bytes for s in outliers)

# Normals: upscale by weight
normal_estimated_count = sum(s.weight for s in normals)
normal_estimated_duration = sum(s.duration * s.weight for s in normals)
normal_estimated_bytes = sum(s.bytes * s.weight for s in normals)

# Combined totals
total_ops = outlier_count + normal_estimated_count
total_duration = outlier_total_duration + normal_estimated_duration
total_bytes = outlier_total_bytes + normal_estimated_bytes

# Per-operation statistics
for operation in ['read', 'write', 'epoll_wait', ...]:
    op_samples = [s for s in samples if s.operation == operation]
    estimated_count = sum(s.weight for s in op_samples)
    estimated_duration = sum(s.duration * s.weight for s in op_samples)
```

### Stacktrace Analysis

Stacktraces are weighted contributions:

```python
# Build flame graph with weighted samples
for sample in samples:
    for frame in sample.stacktrace:
        frame_contribution[frame] += sample.weight

# Each stack frame's contribution is proportional to actual I/O time
```

## Event Schema

### SocketIOEvent Structure

```cpp
typedef struct SocketIOEvent {
    u64 _start;                // start time in TSC ticks
    u64 _end;                  // end time in TSC ticks
    const char* _operation;    // operation name (read/write/epoll_wait/etc.)
    long _bytes;               // bytes transferred (-1 if N/A)
    float _weight;             // sampling weight for upscaling
    bool _is_outlier;          // true if always-sampled outlier
} SocketIOEvent;
```

### JFR Metadata

```cpp
event("datadog.SocketIO")
    << field("startTime", T_LONG, "Start Time", F_TIME_TICKS)
    << field("duration", T_LONG, "Duration", F_DURATION_TICKS)
    << field("eventThread", T_THREAD, "Event Thread", F_CPOOL)
    << field("stackTrace", T_STACK_TRACE, "Stack Trace", F_CPOOL)
    << field("operation", T_STRING, "Operation")
    << field("bytesTransferred", T_LONG, "Bytes Transferred")
    << field("weight", T_FLOAT, "Sample weight")
    << field("isOutlier", T_BOOLEAN, "Captured as outlier")
```

## Configuration Parameters

| Parameter | Default | Description |
|-----------|---------|-------------|
| `socket_io_enabled` | false | Enable Socket I/O profiling |
| `socket_io_outlier_threshold` | 300ms | Always capture ops slower than this |
| `socket_io_target_rate` | 100/sec | Target sampled events per second |
| `socket_io_min_interval` | 10ms | Minimum sampling interval (prevents over-sampling) |
| `socket_io_disable_rate_limiting` | false | Sample all events (testing only) |

## Performance Characteristics

### Overhead Per Operation

| Operation Type | Stack Capture | Weight Calc | Total Overhead |
|----------------|---------------|-------------|----------------|
| Skipped normal op | None | ~5ns (counter decrement) | ~5ns |
| Sampled normal op | getcontext() + stack walk | ~50ns | ~5-20μs |
| Outlier op | getcontext() + stack walk | None | ~5-20μs |

### Memory Usage

- **Thread-local state**: ~64 bytes per thread
- **Global state**: ~128 bytes (counters, config)
- **Event data**: ~200 bytes per sampled event in JFR buffer

### Sampling Examples

**Scenario 1: High-throughput service**
- Real ops: 100,000/min (1,667/sec)
- Target rate: 6,000/min (100/sec)
- Effective sampling: ~1 in 17 operations
- Outliers (>300ms): 10/min → all captured
- Normal samples: ~90/min → upscaled

**Scenario 2: Low-throughput service**
- Real ops: 1,000/min (17/sec)
- Target rate: 6,000/min (100/sec)
- Effective sampling: All operations captured (rate limiter backs off)
- Weight: 1.0 for all events

## Comparison to Allocation Profiling

Both Socket I/O and Allocation profiling use similar sampling strategies:

| Aspect | Allocation Profiling | Socket I/O Profiling |
|--------|---------------------|---------------------|
| **Sampling Variable** | Bytes allocated | Duration (nanoseconds) |
| **Distribution** | Exponential (JVMTI-provided) | Exponential (manual) |
| **Skip Calculation** | Per-thread cumulative bytes | Per-thread cumulative duration |
| **Weight Formula** | `1/(1-e^(-size/interval))` | `1/(1-e^(-duration/interval))` |
| **Rate Control** | PID adjusts interval | PID adjusts interval |
| **Target Rate** | ~6k/min | ~6k/min |
| **Special Handling** | Large allocations more likely | Outliers always captured |

## Implementation Notes

### Thread Safety

- **Atomic counters**: `_sampled_event_count`, `_sampling_interval_ns`
- **Thread-local state**: No synchronization for sampling decisions
- **PID update**: CAS (compare-and-swap) ensures single updater

### Numerical Stability

- **Weight calculation**: Guards against division by zero when `interval=0`
- **Skip budget**: Multiple draws if budget deeply negative (long outlier case)
- **Interval clamping**: Bounded between configured min and 1 second max

### Integration Points

1. **Hooks**: Socket functions call `SocketTracer::recordSocketOp()`
2. **Profiler**: `recordSample()` captures stacktrace with `skip_frames=2`
3. **JFR**: `Recording::recordSocketIO()` serializes event with weight/outlier flag
4. **Startup**: `Profiler::start()` initializes `SocketTracer` with config

## Future Enhancements

### Possible Improvements

1. **Byte-based sampling**: Additionally sample based on cumulative bytes (hybrid duration+bytes)
2. **Per-operation thresholds**: Different outlier thresholds for read vs write vs epoll_wait
3. **Adaptive outlier threshold**: Dynamically adjust based on p99 latency
4. **Separate rate limits**: Independent targets for outliers vs normals
5. **Time-of-day awareness**: Adjust sampling during known traffic patterns

### Alternative Approaches Considered

1. **Fixed 1-in-N sampling**: Simpler but not statistically representative
2. **Time-based sampling**: Per-thread rate limiting (loses correlation with workload)
3. **Reservoir sampling**: Fixed sample size per window (loses temporal information)

## References

- [JEP 331: Low-Overhead Heap Profiling](https://openjdk.org/jeps/331) - JVMTI heap sampling design
- [heapprofd: Sampling for Memory Profiles](https://perfetto.dev/docs/design-docs/heapprofd-sampling) - Exponential distribution approach
- [Inverse Transform Sampling](https://stephens999.github.io/fiveMinuteStats/inverse_transform_sampling.html) - Statistical foundation
- PID Controller implementation: `ddprof-lib/src/main/cpp/pidController.{h,cpp}`
- ObjectSampler implementation: `ddprof-lib/src/main/cpp/objectSampler.{h,cpp}`

## Authors

- Design: Jason Feng (Datadog), with assistance from Claude (Anthropic)
- Date: 2026-03-09
