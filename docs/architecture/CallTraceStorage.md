# CallTraceStorage Triple-Buffer Architecture

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

### Hazard Pointers

Signal handlers use hazard pointers to prevent tables from being deleted during access:

```
Signal Handler Thread               JFR Processing Thread
─────────────────────              ──────────────────────
1. Load active table          
2. Register hazard pointer   ──→   1. Check hazard pointers
3. Verify table still active       2. Wait if hazards exist
4. Use table safely                3. Safe to delete/clear
5. Clear hazard pointer            4. Continue processing
```

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
- **put()**: O(1) average, lock-free with hazard pointer protection
- **processTraces()**: Lock-free table swapping, O(n) collection where n = trace count

### Memory Efficiency
- **Zero-Copy Rotation**: Only atomic pointer swaps, no data copying
- **Pre-allocated Collections**: Thread-local collections prevent malloc/free cycles
- **Trace Deduplication**: Hash tables prevent duplicate trace storage

### Concurrency Benefits
- **Signal Handler Safe**: No blocking operations in signal context
- **Multi-threaded Collection**: Multiple threads can process traces concurrently
- **Contention-Free**: Atomic operations eliminate lock contention

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

1. **Scalability**: Lock-free design scales linearly with thread count
2. **Reliability**: Hazard pointers prevent memory safety issues
3. **Flexibility**: Pluggable liveness checkers support different use cases  
4. **Performance**: Zero-copy operations minimize overhead
5. **Safety**: Signal-handler safe operations prevent deadlocks

This architecture enables high-performance, concurrent profiling data collection suitable for production environments with minimal impact on application performance.