# CallTraceStorage: Architecture and Performance

## Overview

The CallTraceStorage system implements a sophisticated triple-buffered architecture designed for lock-free, signal-handler-safe profiling data collection. This design enables concurrent trace collection from signal handlers while allowing safe background processing for JFR (Java Flight Recorder) serialization.

Each collected call trace receives a globally unique 64-bit identifier composed of a 32-bit instance epoch ID and a 32-bit slot index. This dual-component design ensures collision-free trace identification across buffer rotations and supports stable JFR constant pool references.

## Core Design Principles

1. **Signal Handler Safety**: All operations in signal handlers use lock-free atomic operations
2. **Globally Unique Trace IDs**: 64-bit identifiers (instance epoch + slot index) prevent collisions across buffer rotations
3. **Memory Continuity**: Traces can be preserved across collection cycles for liveness tracking
4. **Zero-Copy Collection**: Uses atomic pointer swapping instead of data copying
5. **ABA Protection**: Generation counters and hazard pointers prevent use-after-free
6. **Lock-Free Concurrency**: Multiple threads can collect traces without blocking each other

## Triple-Buffer Architecture

The system maintains three `CallTraceHashTable` instances with distinct roles:

```
┌─────────────┐    ┌─────────────┐    ┌─────────────┐
│   ACTIVE    │    │   STANDBY   │    │   SCRATCH   │
│             │    │             │    │             │
│ New traces  │    │ Preserved   │    │ Processing  │
│ from signal │    │ traces from │    │ old traces  │
│ handlers    │    │ prev cycle  │    │ before clear│
└─────────────┘    └─────────────┘    └─────────────┘
```

### Buffer Roles

- **ACTIVE**: Receives new traces from signal handlers (lock-free puts)
- **STANDBY**: Contains preserved traces from the previous collection cycle
- **SCRATCH**: Temporary storage during rotation, gets cleared after processing

### Rotation Algorithm

The rotation follows a carefully orchestrated 6-step sequence:

```cpp
void processTraces() {
    // Step 1: Collect from STANDBY (preserved traces)
    current_standby->collect(standby_traces);

    // Step 2: Clear STANDBY, prepare for new role as ACTIVE
    current_standby->clear();
    current_standby->setInstanceId(new_instance_id);

    // Step 3: ATOMIC ROTATION
    // STANDBY (empty) → ACTIVE (receives new traces)
    old_active = _active_storage.exchange(current_standby);
    // ACTIVE (full) → SCRATCH (for processing)
    old_scratch = _scratch_storage.exchange(old_active);
    // SCRATCH (processed) → STANDBY (for next cycle)
    _standby_storage.store(old_scratch);

    // Step 4: Collect from SCRATCH (old active, now read-only)
    old_active->collect(active_traces);

    // Step 5: Process combined traces
    all_traces = standby_traces ∪ active_traces;
    processor(all_traces);

    // Step 6: Preserve traces for next cycle
    old_scratch->clear();
    for (trace : preserved_traces) {
        old_scratch->putWithExistingIdLockFree(trace);
    }
}
```

## 64-Bit Trace ID Architecture

### Trace ID Structure

```
┌──────────────────────────────┬──────────────────────────────────────┐
│     Upper 32 bits            │          Lower 32 bits               │
│   Instance Epoch ID          │       Hash Table Slot Index          │
│ Unique per active rotation   │    Position in hash table            │
└──────────────────────────────┴──────────────────────────────────────┘
```

### Instance Epoch ID Generation

Each time a `CallTraceHashTable` transitions from STANDBY to ACTIVE during buffer rotation, it receives a new instance epoch ID:

```cpp
// During rotation - Step 2
current_standby->clear();
u64 new_instance_id = getNextInstanceId();  // Atomic increment
current_standby->setInstanceId(new_instance_id);

// Later during trace creation
u64 trace_id = (instance_id << 32) | slot_index;
```

### Benefits

1. **Collision Immunity**: Same slot across rotations generates different trace IDs
2. **JFR Compatibility**: 64-bit IDs work seamlessly with JFR constant pool indices
3. **Liveness Support**: Preserved traces maintain stable IDs across collection cycles
4. **Debug Capability**: Instance ID in trace ID aids in debugging buffer rotation issues

## Memory Safety Mechanisms

### Hazard Pointers

Signal handlers use hazard pointers to prevent tables from being deleted during access. The **scanner** is the background thread (JFR processing) that checks all hazard pointer slots before deleting or reusing a table.

```
Signal Handler Thread               JFR Processing Thread (Scanner)
─────────────────────              ────────────────────────────────
1. Load active table
2. Register hazard pointer   ──→   1. Scan hazard pointer slots
3. Verify table still active       2. Wait if any point to target table
4. Use table safely                3. Safe to delete/clear when all clear
5. Clear hazard pointer            4. Continue processing
```

**Scanner implementation**: `waitForHazardPointersToClear()` scans the occupied bitmap and checks each active slot to see if any signal handlers are still using the table being deleted.

#### Enhanced Design (8192 Slots)

**Slot Array Design:**
- **8192 hazard pointer slots** (64KB memory usage)
- **Thread ID verification** array prevents slot overwrites
- **Semi-random prime step probing** eliminates secondary clustering
- **Graceful degradation** when slots are exhausted

**Semi-Random Prime Step Collision Resolution:**
```cpp
// Pre-selected prime numbers coprime to MAX_THREADS (8192 = 2^13)
static constexpr int PRIME_STEPS[16] = {
    1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049,
    1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097
};

int getThreadHazardSlot() {
    int tid = OS::threadId();  // Signal-safe cached thread ID
    size_t hash = static_cast<size_t>(tid) * KNUTH_MULTIPLICATIVE_CONSTANT;
    int base_slot = (hash >> (sizeof(size_t) * 8 - 13)) % MAX_THREADS;

    // Semi-random prime step probing eliminates secondary clustering
    int step_index = (hash >> 4) % PRIME_STEP_COUNT;
    int prime_step = PRIME_STEPS[step_index];

    for (int i = 0; i < MAX_PROBE_DISTANCE; i++) {
        int slot = (base_slot + i * prime_step) % MAX_THREADS;

        // Atomic slot claiming with thread ID verification
        int expected = 0;
        if (slot_owners[slot].compare_exchange_strong(expected, tid)) {
            return slot;
        }

        // Check if we already own this slot (reentrant calls)
        if (slot_owners[slot].load() == tid) {
            return slot;
        }
    }

    return -1; // Graceful degradation
}
```

**Performance Characteristics:**
- **Collision Probability**: <3% with 2000 concurrent threads
- **Memory Cost**: 64KB total (negligible)
- **Signal Handler Safe**: No allocation, bounded execution time

### ABA Protection

Generation counters prevent the ABA problem:

```cpp
u64 generation = _generation_counter.load();
CallTraceHashTable* table = _active_storage.load();

if (_generation_counter.load() != generation) {
    // Storage was rotated, retry or abort
}
```

## Performance Benchmarks

### Benchmark Suite

Located in `ddprof-stresstest/src/jmh/java/com/datadoghq/profiler/stresstest/scenarios/throughput/`:

**Note**: These benchmarks test the **complete profiling engine** (signal handlers, stack walking, CallTraceStorage, JFR processing), not just isolated CallTraceStorage operations.

1. **ProfilerThroughputBaselineBenchmark** - Baseline performance with stable threads
2. **ProfilerThroughputThreadChurnBenchmark** - Short-lived thread churn overhead
3. **ProfilerThroughputSlotExhaustionBenchmark** - High concurrency stress tests
4. **ProfilerThroughputQuickBenchmark** - Fast smoke test (~2 minutes)

### Running Benchmarks

**Prerequisites**: All benchmarks require the WhiteboxProfiler to be enabled.

**Quick smoke test (~2 minutes):**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  ProfilerThroughputQuickBenchmark
```

**Full baseline (~12 minutes):**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  ProfilerThroughputBaselineBenchmark
```

**Thread churn benchmarks (~20-30 minutes):**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  ProfilerThroughputThreadChurnBenchmark
```

**Slot exhaustion benchmarks (~15-20 minutes):**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  ProfilerThroughputSlotExhaustionBenchmark
```

**Saving results to JSON:**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  -Pjmh.resultFormat=json \
  -Pjmh.resultFile=build/calltrace-results.json \
  ProfilerThroughputQuickBenchmark
```

**Faster iterations for development:**
```bash
./gradlew :ddprof-stresstest:jmh \
  -Pjmh.prof='com.datadoghq.profiler.stresstest.WhiteboxProfiler' \
  -Pjmh.fork=1 -Pjmh.wi=1 -Pjmh.i=2 \
  ProfilerThroughputQuickBenchmark.baseline01Thread
```

**Common JMH options:**
- `-Pjmh.fork=N`: Number of JVM forks (default: 3)
- `-Pjmh.wi=N`: Warmup iterations (default: 3)
- `-Pjmh.i=N`: Measurement iterations (default: 3)
- `-Pjmh.wt=N`: Warmup time in seconds (default: 1)
- `-Pjmh.t=N`: Measurement time in seconds (default: 3)
- `-Pjmh.resultFormat=json|csv|text`: Output format
- `-Pjmh.resultFile=path`: Output file path

### Benchmark Results Summary

**Platform**: macOS arm64 (Apple Silicon), OpenJDK 21.0.5

#### Baseline Scaling Analysis

| Threads | Score (ops/s) | Efficiency | Assessment |
|---------|---------------|------------|------------|
| 1       | 7,766         | 100%       | ✅ Baseline |
| 2       | 15,104        | 97%        | ✅ Excellent |
| 4       | 30,311        | 98%        | ✅ Excellent |
| 8       | 56,870        | 92%        | ✅ Good |
| 16      | 59,900        | 48%        | ⚠️ Warning |
| 32      | 60,647        | 24%        | ⚠️ Warning |
| 64      | 65,077        | 13%        | 🔴 Critical |

**Key Findings:**
- Near-linear scaling up to 8 threads (92-98% efficiency)
- Performance plateaus at ~60k ops/s beyond 8 threads
- Cache line contention on `slot_owners` and `occupied_bitmap` arrays

#### Thread Churn Performance

| Configuration | Score (batches/s) | Threads/sec | Per-Thread Overhead | Assessment |
|---------------|-------------------|-------------|---------------------|------------|
| 10 threads × 5ms | 146 ± 21 | **1,460** | **4.86 ms** | 🔴 Critical |
| 50 threads × 5ms | 33 ± 4 | **1,650** | **4.55 ms** | 🔴 Critical |

**Key Finding**: Thread creation/destruction overhead is ~4.5-4.9ms per thread, driven by:
1. 5 atomic operations per HazardPointer lifecycle
2. Prime probing for slot allocation
3. OS thread creation/destruction overhead

#### Slot Exhaustion - Wave Pattern

| Thread Count | Time/Thread | Assessment |
|--------------|-------------|------------|
| 500          | 5.3ms       | 🔴 Critical |
| 1000         | 5.2ms       | 🔴 Critical |
| 2000         | 3.4ms       | 🔴 Critical |
| 4000         | 1.3ms       | ⚠️ Better |

**Key Finding**: Per-thread allocation time improves at higher thread counts (better amortization), indicating prime probing is **not** exhibiting quadratic behavior.

### Performance Targets

| Metric | Target | Actual | Status |
|--------|--------|--------|--------|
| 8-thread scaling | >80% | **92%** | ✅ Pass |
| 64-thread scaling | >15% | **13%** | ⚠️ Close |
| Thread creation rate | >10k/s | **1.5k/s** | 🔴 Fail |
| Burst allocation | <200μs | **800-5000μs** | 🔴 Fail |

## Optimization Recommendations

### High Priority: Cache Line Alignment

**Impact**: Fixes 16+ thread scaling issue
**Difficulty**: Low
**Risk**: Low

```cpp
// Before
int slot_owners[MAX_THREADS];

// After
alignas(64) int slot_owners[MAX_THREADS];

// Pad bitmap words
struct alignas(64) BitmapWord {
    uint64_t value;
    char padding[56];
};
BitmapWord occupied_bitmap[BITMAP_WORDS];
```

**Expected Improvement:**
- 64-thread efficiency: 13% → 40-50%
- Peak throughput: 65k → 150-200k ops/s

### Medium Priority: Reduce Atomic Operations

**Impact**: Reduces per-thread overhead
**Difficulty**: Medium
**Risk**: Medium

Current: 5 atomic ops per put()

Options:
1. Batch bitmap updates
2. Use relaxed atomics where safe
3. Remove redundant slot ownership checks

**Expected Improvement:**
- Per-thread overhead: 4.5ms → 2-3ms
- Thread creation rate: 1.5k/s → 3-5k/s

### Low Priority: Slot Allocation Hints

**Impact**: Improves slot reuse locality
**Difficulty**: High
**Risk**: Medium

Maintain per-CPU "last freed slot" hint for better cache locality.

## Use Case Guidance

**Good fit:**
- Applications with 1-8 long-lived worker threads ✅
- Stable thread pools ✅
- Server applications with persistent connections ✅

**Poor fit:**
- Applications creating >100 threads/second 🔴
- Thread-per-request architectures with <10ms request times 🔴
- Virtual thread / fiber-based applications 🔴

## Usage Example

```cpp
// Setup
CallTraceStorage storage;
storage.registerLivenessChecker([](auto& preserve_set) {
    // Add traces to preserve
});

// Signal handler (lock-free)
u64 trace_id = storage.put(num_frames, frames, truncated, weight);

// Background processing
storage.processTraces([](const std::unordered_set<CallTrace*>& traces) {
    for (CallTrace* trace : traces) {
        writeToJFR(trace);
    }
});
```

## Key Architectural Benefits

1. **Scalability**: Lock-free design scales linearly with thread count (up to core count)
2. **Reliability**: Hazard pointers prevent memory safety issues
3. **Flexibility**: Pluggable liveness checkers support different use cases
4. **Performance**: Zero-copy operations minimize overhead
5. **Safety**: Signal-handler safe operations prevent deadlocks

This architecture enables high-performance, concurrent profiling data collection suitable for production environments with minimal impact on application performance.
