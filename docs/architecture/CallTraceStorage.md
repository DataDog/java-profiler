# CallTraceStorage Triple-Buffer Architecture

## Overview

The CallTraceStorage system implements a sophisticated triple-buffered architecture designed for lock-free, signal-handler-safe profiling data collection. This design enables concurrent trace collection from signal handlers while allowing safe background processing for JFR (Java Flight Recorder) serialization.

Each collected call trace receives a globally unique 64-bit identifier composed of a 32-bit instance epoch ID and a 32-bit slot index. This dual-component design ensures collision-free trace identification across buffer rotations and supports stable JFR constant pool references.

## Core Design Principles

1. **Signal Handler Safety**: All operations in signal handlers use lock-free atomic operations
2. **Globally Unique Trace IDs**: 64-bit identifiers (instance epoch + slot index) prevent collisions across buffer rotations
3. **Memory Continuity**: Traces can be preserved across collection cycles for liveness tracking
4. **Zero-Copy Collection**: Uses atomic pointer swapping instead of data copying
5. **ABA Protection**: Generation counters and RefCountGuard prevent use-after-free
6. **Lock-Free Concurrency**: Multiple threads can collect traces without blocking each other

## Triple-Buffer States

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

## Triple-Buffer Rotation Algorithm

The rotation follows a carefully orchestrated 6-step sequence:

### Phase Diagram

```
BEFORE ROTATION:
┌─────────────────────────────────────────────────────────────┐
│ Thread A (Signal Handler)    │    Thread B (JFR Processing) │
├─────────────────────────────────────────────────────────────┤
│                              │                              │
│ put() → ACTIVE               │    processTraces()           │
│       ↓                      │            ↓                 │
│ [New Traces]                 │    Step 1: Collect STANDBY   │
│                              │    Step 2: Clear STANDBY     │
│                              │    Step 3: ATOMIC SWAP       │
└─────────────────────────────────────────────────────────────┘

DURING ROTATION (Atomic Swap):
┌─────────────────────────────────────────────────────────────┐
│  OLD STATE        │    ATOMIC SWAP    │    NEW STATE        │
├─────────────────────────────────────────────────────────────┤
│ ACTIVE   = A      │                   │  ACTIVE   = B       │
│ STANDBY  = B      │ ──── SWAP ────→   │  STANDBY  = C       │
│ SCRATCH  = C      │                   │  SCRATCH  = A       │
└─────────────────────────────────────────────────────────────┘

AFTER ROTATION:
┌────────────────────────────────────────────────────────────┐
│ put() → NEW ACTIVE (B)      │    Step 4: Collect SCRATCH   │
│                             │    Step 5: Process All       │
│ [Safe to continue]          │    Step 6: Preserve & Clear  │
└────────────────────────────────────────────────────────────┘
```

### Detailed Steps

```cpp
void processTraces() {
    // PHASE 1: Liveness Analysis
    // Determine which traces need preservation

    // PHASE 2: Collection Sequence

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

## Memory Safety Mechanisms

The profiler uses thread-local reference counting (RefCountGuard) as the primary memory reclamation mechanism. This provides lock-free, signal-handler-safe protection against use-after-free bugs during concurrent table access and rotation.

> **Historical Note**: Earlier versions used hazard pointers with bitmap optimization for slot scanning. However, the bitmap-pointer split-update approach had a race condition: the bitmap bit and pointer store were separate atomic operations, creating a window where the scanner could observe an inconsistent state. RefCountGuard eliminates this issue via the pointer-first protocol, where the count field acts as a single atomic activation barrier. Benchmarking confirmed equivalent performance (within 0.25% noise) while providing provably correct memory reclamation. The hazard pointer implementation was removed in favor of the simpler, more correct RefCountGuard approach.

### ABA Protection

Generation counters prevent the ABA problem during concurrent access:

```cpp
// Each storage operation includes generation check
u64 generation = _generation_counter.load();
CallTraceHashTable* table = _active_storage.load();

if (_generation_counter.load() != generation) {
    // Storage was rotated, retry or abort
}
```

### Thread-Local Reference Counting (RefCountGuard)

**Production Implementation**: The profiler uses thread-local reference counting via `RefCountGuard` as the primary memory reclamation mechanism. This approach provides superior correctness guarantees compared to hazard pointers while maintaining equivalent performance.

#### Architecture

RefCountGuard implements a **cache-aligned, thread-local reference counting scheme** where each thread has a dedicated slot containing:
- Reference count (4 bytes): Number of active guards protecting the table
- Active table pointer (8 bytes): Which table is currently being protected
- Padding (52 bytes): Ensures full cache line alignment (64 bytes total)

**Memory Layout:**
```
┌──────────────────────────────────────────────────────────────────┐
│                      RefCountSlot (64 bytes)                     │
├──────────────┬──────────────┬─────────────────────────────────────┤
│ count (4B)   │ padding (4B) │ active_table* (8B) │ padding (48B) │
│ volatile     │              │                    │               │
└──────────────┴──────────────┴────────────────────┴───────────────┘
```

**Global Array:**
```cpp
static RefCountSlot refcount_slots[8192];  // 8192 × 64 bytes = 512 KB
static int slot_owners[8192];              // Thread ID ownership tracking
```

#### The Pointer-First Protocol

The correctness of RefCountGuard relies on a **strict ordering protocol** that eliminates race conditions:

**Constructor (Activation):**
```cpp
RefCountGuard::RefCountGuard(CallTraceHashTable* resource) {
    _my_slot = getThreadRefCountSlot();  // Get thread-local slot

    // CRITICAL ORDERING: Store pointer FIRST, then increment count
    // Step 1: Store pointer with release semantics
    __atomic_store_n(&refcount_slots[_my_slot].active_table,
                     resource, __ATOMIC_RELEASE);

    // Step 2: Increment count with release semantics
    __atomic_fetch_add(&refcount_slots[_my_slot].count,
                       1, __ATOMIC_RELEASE);
}
```

**Destructor (Deactivation):**
```cpp
RefCountGuard::~RefCountGuard() {
    // CRITICAL ORDERING: Decrement count FIRST, then clear pointer
    // Step 1: Decrement count with release semantics
    __atomic_fetch_sub(&refcount_slots[_my_slot].count,
                       1, __ATOMIC_RELEASE);

    // Step 2: Clear pointer with release semantics
    __atomic_store_n(&refcount_slots[_my_slot].active_table,
                     nullptr, __ATOMIC_RELEASE);
}
```

**Scanner (Reclamation Check):**
```cpp
void RefCountGuard::waitForRefCountToClear(CallTraceHashTable* table) {
    for (int i = 0; i < MAX_THREADS; ++i) {
        // CRITICAL: Check count FIRST (pointer-first protocol)
        uint32_t count = __atomic_load_n(&refcount_slots[i].count,
                                          __ATOMIC_ACQUIRE);
        if (count == 0) continue;  // Slot inactive, skip

        // Count > 0: slot is active, check which table it protects
        CallTraceHashTable* table =
            __atomic_load_n(&refcount_slots[i].active_table,
                            __ATOMIC_ACQUIRE);
        if (table == table_to_delete) {
            return false;  // Still protected, cannot reclaim
        }
    }
    return true;  // Safe to reclaim
}
```

#### Why This Protocol Is Correct

The pointer-first protocol **provably eliminates race conditions** through careful ordering:

**Scenario 1: Scanner observes during activation (between steps 1 and 2)**
```
Thread T1 (Constructor):
  Step 1: store pointer → refcount_slots[S].active_table = P  ✓ DONE
  [PREEMPTION - Scanner runs here]
  Step 2: increment count → refcount_slots[S].count = 1       PENDING

Scanner Thread:
  Load count = __atomic_load(&refcount_slots[S].count)
  → Observes count = 0 (step 2 not yet executed)
  → Treats slot S as INACTIVE
  → Skips this slot

Result: SAFE
  - Scanner skips the slot (treats as inactive)
  - Thread T1 hasn't "activated" protection yet
  - No false sense of protection
```

**Scenario 2: Scanner observes after activation (after step 2)**
```
Thread T1 (Constructor):
  Step 1: store pointer → refcount_slots[S].active_table = P  ✓ DONE
  Step 2: increment count → refcount_slots[S].count = 1       ✓ DONE

Scanner Thread:
  Load count = __atomic_load(&refcount_slots[S].count)
  → Observes count = 1 (step 2 completed)
  → Treats slot S as ACTIVE
  → Loads pointer = __atomic_load(&refcount_slots[S].active_table)
  → Observes pointer P (step 1 happened-before step 2 via release semantics)

Result: SAFE
  - Scanner sees active slot
  - Pointer is guaranteed visible due to release-acquire ordering
  - Table P is correctly protected
```

**Scenario 3: Scanner observes during deactivation (between steps 1 and 2)**
```
Thread T1 (Destructor):
  Step 1: decrement count → refcount_slots[S].count = 0       ✓ DONE
  [PREEMPTION - Scanner runs here]
  Step 2: clear pointer → refcount_slots[S].active_table = nullptr  PENDING

Scanner Thread:
  Load count = __atomic_load(&refcount_slots[S].count)
  → Observes count = 0 (step 1 completed)
  → Treats slot S as INACTIVE
  → Skips this slot

Result: SAFE
  - Scanner treats slot as inactive (count = 0)
  - Doesn't load the pointer at all
  - Safe to reclaim (no protection claimed)
```

**Key Invariant**: The count field acts as a **single atomic activation barrier**. The scanner checks count first:
- `count == 0` → slot inactive (safe to skip, regardless of pointer value)
- `count > 0` → slot active (pointer is guaranteed visible via release-acquire)

There is **no window** where the scanner can observe inconsistent state that leads to **use-after-free** bugs.

#### Trace Drop Window and Revalidation

There is a narrow window during guard construction where traces may be dropped, but use-after-free is **impossible**:

**The Scenario:**
```
Thread T1 (signal handler):
  active = _active_storage.load();              // Step 1: Load TableA
  RefCountGuard guard(active);                  // Step 2: Constructor starts
      store pointer → slot[S].active_table = TableA;
      ⚠️ PREEMPTION - count still 0!

Thread T2 (scanner):
  old = exchange(_active_storage, nullptr);     // Nullifies storage
  waitForRefCountToClear(TableA);               // Scans all slots
      for slot[S]: count=0 → skip               // Sees inactive
      return;                                   // All clear!
  delete TableA;                                // Table deleted

Thread T1 resumes:
      increment count → slot[S].count = 1;      // Too late!

  // ⚡ CRITICAL REVALIDATION CHECK:
  original_active = _active_storage.load();     // Reads nullptr!
  if (original_active != active) {              // TRUE (nullptr != TableA)
      return DROPPED_TRACE_ID;                  // ✅ SAFE - never touches table
  }
  // active->put() is NEVER REACHED ✅
```

**Why This Is Safe:**

1. **Revalidation Always Happens**: After guard construction completes, we **always** re-check `_active_storage` before using the table pointer
2. **Memory Ordering Guarantees Visibility**: ACQUIRE/RELEASE semantics ensure the revalidation sees the scanner's nullification
3. **No Use-After-Free**: We return `DROPPED_TRACE_ID` and never dereference the deleted table
4. **Acceptable Tradeoff**: Traces arriving during this tiny window (~10-100ns) are dropped, which is acceptable under contention

**Key Insight**: The scanner can complete on its **first iteration** if all slots have `count=0`. This is by design - we trade this narrow trace-drop window for the simplicity of a two-state protocol (inactive/active) rather than a more complex three-state protocol (inactive/pending/active).

#### Why Hazard Pointers Had a Race Condition

The original hazard pointer implementation had a **bitmap-pointer atomicity gap**:

```cpp
// Hazard Pointer Constructor (FLAWED)
HazardPointer::HazardPointer(CallTraceHashTable* resource) {
    // Step 1: Store pointer
    global_hazard_list[_my_slot].pointer = resource;

    // Step 2: Set bitmap bit (SEPARATE ATOMIC OPERATION)
    set_bitmap_bit(_my_slot);
}

// Scanner (VULNERABLE)
void waitForHazardPointersToClear(CallTraceHashTable* table) {
    // Step 1: Load bitmap
    uint64_t bitmap_word = occupied_bitmap[word_index];
    if (bitmap_word == 0) return;  // No occupied slots

    // Step 2: Check pointers in occupied slots
    for (each bit set in bitmap_word) {
        void* ptr = global_hazard_list[slot].pointer;
        if (ptr == table) return false;  // Still protected
    }
}
```

**Race Condition Window:**
```
Thread T1 (Hazard Constructor):
  Step 1: store pointer → global_hazard_list[S].pointer = P   ✓ DONE
  [PREEMPTION - Scanner runs here]
  Step 2: set bitmap bit → occupied_bitmap[W] |= (1 << B)      PENDING

Scanner Thread:
  Load bitmap = occupied_bitmap[W]
  → Observes bit B is NOT SET (step 2 not executed)
  → Skips slot S entirely (not in bitmap)
  → Concludes table P is not protected

Result: UNSAFE
  - Scanner falsely believes no thread is protecting table P
  - May delete/reuse table P
  - Thread T1 will access freed memory after step 2
  - Use-after-free bug
```

**Why the bitmap approach fails**: The bitmap and pointer are **two separate memory locations** that cannot be updated atomically together. A thread preemption or cache coherency delay between the two operations creates a window where:
1. Pointer is stored (protection intended)
2. Bitmap bit not yet set (protection not visible to scanner)
3. Scanner sees unset bitmap bit → incorrectly assumes no protection → deletes table
4. Thread resumes and uses freed memory → crash

**RefCountGuard fixes this** by making the count field serve as **both** the "occupied" indicator and the activation barrier, eliminating the two-location race.

#### Slot Allocation

RefCountGuard reuses the proven slot allocation strategy from hazard pointers:

```cpp
int RefCountGuard::getThreadRefCountSlot() {
    int tid = OS::threadId();  // Signal-safe cached thread ID
    size_t hash = static_cast<size_t>(tid) * 0x9E3779B97F4A7C15ULL;
    int base_slot = (hash >> 51) % MAX_THREADS;  // Upper 13 bits

    // Semi-random prime step probing
    int step_index = (hash >> 4) % 16;
    int prime_step = PRIME_STEPS[step_index];  // e.g., 1009, 1013, etc.

    for (int i = 0; i < MAX_PROBE_DISTANCE; i++) {
        int slot = (base_slot + i * prime_step) % MAX_THREADS;

        int expected = 0;
        if (__atomic_compare_exchange_n(&slot_owners[slot], &expected, tid,
                                        false, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
            return slot;  // Successfully claimed
        }

        if (__atomic_load_n(&slot_owners[slot], __ATOMIC_ACQUIRE) == tid) {
            return slot;  // Already owned (reentrant)
        }
    }

    return -1;  // Slot exhaustion - graceful degradation
}
```

#### Performance Characteristics

**Memory Cost:**
- 512 KB for refcount slots (8192 × 64 bytes)
- 32 KB for slot owners (8192 × 4 bytes)
- **Total: 544 KB** (8 KB less than hazard pointers due to no bitmap)

**Hot Path Cost:**
- Constructor: 2 atomic stores (pointer + count increment)
- Destructor: 2 atomic stores (count decrement + pointer clear)
- No bitmap operations required

**Benchmark Results (vs Hazard Pointers):**

| Workload | HazardPointer | RefCountGuard | Difference |
|----------|---------------|---------------|------------|
| 1 thread baseline | 6,139.0 ops/s | 6,134.7 ops/s | -0.07% |
| 8 threads baseline | 49,039.2 ops/s | 49,034.1 ops/s | -0.01% |
| 32 threads baseline | 95,902.9 ops/s | 95,690.1 ops/s | -0.22% |
| 10 threads churn | 176.2 ops/s | 175.9 ops/s | -0.16% |
| 50 threads churn | 46.6 ops/s | 46.5 ops/s | -0.09% |

**Statistical Analysis:**
- All differences fall within measurement noise (< 0.25%)
- Confidence intervals overlap significantly (91% for single-thread, 79% for 8-thread)
- No meaningful performance difference across all tested scenarios

**Conclusion**: RefCountGuard provides **equivalent performance** to hazard pointers while offering **provably correct** memory reclamation through the pointer-first protocol.

#### Signal Handler Safety

RefCountGuard is fully signal-handler-safe:
- **No malloc/free**: Uses pre-allocated global array
- **No blocking**: Only uses GCC atomic builtins
- **Bounded execution**: Maximum 32 probing attempts for slot allocation
- **Reentrant-safe**: Thread ID verification prevents slot conflicts
- **OS integration**: Uses `OS::threadId()` which caches the thread ID

#### Usage in Signal Handlers

```cpp
u64 CallTraceStorage::put(int num_frames, ASGCT_CallFrame* frames,
                          bool truncated, u64 weight) {
    // Protect active table with thread-local reference counting
    RefCountGuard guard(_active_storage);
    if (!guard.isActive()) {
        return DROPPED_TRACE_ID;  // Slot exhaustion - graceful degradation
    }

    // Safe to use _active_storage - guard prevents reclamation
    CallTraceHashTable* table = _active_storage;
    return table->put(num_frames, frames, truncated, weight);

    // Guard destructor automatically releases protection
}
```

#### Scanner Integration

The JFR processing thread (scanner) waits for all reference counts to clear before reclaiming a table:

```cpp
void CallTraceStorage::processTraces(...) {
    // ... rotation logic ...

    // Wait for all signal handlers to finish with old active table
    RefCountGuard::waitForRefCountToClear(old_active_table);

    // Safe to clear and reuse the table
    old_active_table->clear();
}
```

**Scanner Performance:**
- Linear scan of 8192 slots: ~10-20 microseconds on modern CPUs
- Early exit optimization: stops on first active reference
- Amortized cost: negligible compared to JFR serialization (milliseconds)

#### Comparison Summary

| Aspect | HazardPointer | RefCountGuard | Winner |
|--------|---------------|---------------|--------|
| **Correctness** | Race condition in bitmap-pointer gap | Provably race-free (pointer-first protocol) | ✅ RefCountGuard |
| **Performance** | ~6,139 ops/s (1T), ~96K ops/s (32T) | ~6,135 ops/s (1T), ~96K ops/s (32T) | ⚖️ Tie |
| **Memory** | 520 KB (array + bitmap) | 512 KB (array only) | ✅ RefCountGuard |
| **Complexity** | Bitmap + pointer synchronization | Single count field as barrier | ✅ RefCountGuard |
| **Signal Safety** | Yes | Yes | ⚖️ Tie |
| **Graceful Degradation** | Yes | Yes | ⚖️ Tie |

**Production Status**: RefCountGuard is the **production implementation** due to superior correctness properties with zero performance cost.

## Thread-Local Collections

Each thread maintains pre-allocated collections to avoid malloc/free in hot paths:

```
Thread A                     Thread B                     Thread N
────────                     ────────                     ────────
ThreadLocalCollections       ThreadLocalCollections       ThreadLocalCollections
├─ traces_buffer            ├─ traces_buffer             ├─ traces_buffer
├─ standby_traces           ├─ standby_traces            ├─ standby_traces
├─ active_traces            ├─ active_traces             ├─ active_traces
├─ preserve_set             ├─ preserve_set              ├─ preserve_set
└─ traces_to_preserve       └─ traces_to_preserve        └─ traces_to_preserve
```

## Liveness Preservation

The system supports pluggable liveness checkers to determine which traces to preserve:

```cpp
// Liveness checker interface
typedef std::function<void(std::unordered_set<u64>&)> LivenessChecker;

// Example: JFR constant pool preservation
registerLivenessChecker([](std::unordered_set<u64>& preserve_set) {
    // Add trace IDs that appear in active JFR recordings
    preserve_set.insert(active_jfr_traces.begin(), active_jfr_traces.end());
});
```

## 64-Bit Trace ID Architecture

The system uses a sophisticated 64-bit trace ID scheme that combines collision avoidance with instance tracking to ensure globally unique, stable trace identifiers across buffer rotations.

### Trace ID Structure

```
┌─────────────────────────────────────────────────────────────────────┐
│                        64-bit Trace ID                              │
├──────────────────────────────┬──────────────────────────────────────┤
│     Upper 32 bits            │          Lower 32 bits               │
│   Instance Epoch ID          │       Hash Table Slot Index          │
│                              │                                      │
│ Unique per active rotation   │    Position in hash table            │
│ Prevents collision across    │    (0 to capacity-1)                 │
│ buffer swaps                 │                                      │
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

### Collision Prevention Across Rotations

The instance epoch prevents trace ID collisions when the same hash table slot is reused across different active periods:

```
Timeline Example:
─────────────────────────────────────────────────────────────────────

Rotation 1: Instance ID = 0x00000001
┌─────────────────┐
│ ACTIVE Table A  │ Slot 100 → Trace ID: 0x0000000100000064
│ Instance: 001   │ Slot 200 → Trace ID: 0x00000001000000C8
└─────────────────┘

Rotation 2: Instance ID = 0x00000002
┌─────────────────┐
│ ACTIVE Table A  │ Slot 100 → Trace ID: 0x0000000200000064
│ Instance: 002   │ Slot 200 → Trace ID: 0x00000002000000C8
│ (same table,    │
│  different ID)  │
└─────────────────┘
```

### JFR Constant Pool Stability

The trace ID scheme provides crucial benefits for JFR serialization:

1. **Stable References**: Trace IDs remain consistent during the active period
2. **Unique Across Cycles**: Even if the same slot is reused, the trace ID differs
3. **Collision Avoidance**: 32-bit instance space prevents ID conflicts
4. **Liveness Tracking**: Preserved traces maintain their original IDs

### Implementation Details

```cpp
class CallTraceHashTable {
    std::atomic<u64> _instance_id;  // Set when becoming active

    u64 put(int num_frames, ASGCT_CallFrame* frames, bool truncated, u64 weight) {
        // ... hash table logic ...

        // Generate unique trace ID
        u64 instance_id = _instance_id.load(std::memory_order_acquire);
        u64 trace_id = (instance_id << 32) | slot;

        CallTrace* trace = storeCallTrace(num_frames, frames, truncated, trace_id);
        return trace->trace_id;
    }
};
```

### Instance ID Generation

```cpp
class CallTraceStorage {
    static std::atomic<u64> _next_instance_id;  // Global counter

    static u64 getNextInstanceId() {
        return _next_instance_id.fetch_add(1, std::memory_order_relaxed);
    }

    void processTraces() {
        // During rotation - assign new instance ID
        u64 new_instance_id = getNextInstanceId();
        current_standby->setInstanceId(new_instance_id);

        // Atomic swap: standby becomes new active with fresh instance ID
        _active_storage.exchange(current_standby, std::memory_order_acq_rel);
    }
};
```

### Reserved ID Space

The system reserves trace IDs with upper 32 bits = 0 for special purposes:

```cpp
// Reserved for dropped samples (contention/allocation failures)
static const u64 DROPPED_TRACE_ID = 1ULL;

// Real trace IDs always have instance_id >= 1
// Format: (instance_id << 32) | slot where instance_id starts from 1
// This guarantees no collision with reserved IDs
```

### Benefits of This Architecture

1. **Collision Immunity**: Same slot across rotations generates different trace IDs
2. **JFR Compatibility**: 64-bit IDs work seamlessly with JFR constant pool indices
3. **Liveness Support**: Preserved traces maintain stable IDs across collection cycles
4. **Debug Capability**: Instance ID in trace ID aids in debugging buffer rotation issues
5. **Scalability**: 32-bit instance space supports ~4 billion rotations before wraparound

This trace ID design ensures that each call trace has a globally unique, stable identifier that survives the complex buffer rotation lifecycle while providing essential metadata about its origin and timing.

## Performance Characteristics

### Lock-Free Operations
- **put()**: O(1) average, lock-free with RefCountGuard protection
- **processTraces()**: Lock-free table swapping, O(n) collection where n = trace count

### Memory Efficiency
- **Zero-Copy Rotation**: Only atomic pointer swaps, no data copying
- **Pre-allocated Collections**: Thread-local collections prevent malloc/free cycles
- **Trace Deduplication**: Hash tables prevent duplicate trace storage

### Concurrency Benefits
- **Signal Handler Safe**: No blocking operations in signal context
- **Multi-threaded Collection**: Multiple threads can process traces concurrently
- **Contention-Free**: Atomic operations eliminate lock contention

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
1. RefCountGuard lifecycle atomic operations (pointer stores and count updates)
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
    // Serialize to JFR format
    for (CallTrace* trace : traces) {
        writeToJFR(trace);
    }
});
```

## Key Architectural Benefits

1. **Scalability**: Lock-free design scales linearly with thread count (up to core count)
2. **Reliability**: RefCountGuard prevents memory safety issues through provably correct reclamation
3. **Flexibility**: Pluggable liveness checkers support different use cases
4. **Performance**: Zero-copy operations minimize overhead
5. **Safety**: Signal-handler safe operations prevent deadlocks

This architecture enables high-performance, concurrent profiling data collection suitable for production environments with minimal impact on application performance.
