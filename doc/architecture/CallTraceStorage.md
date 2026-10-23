# CallTraceStorage Triple-Buffer Architecture

## Overview

`CallTraceStorage` (`ddprof-lib/src/main/cpp/callTraceStorage.{h,cpp}`) stores
deduplicated call traces. Signal handlers and JNI paths write traces with
`put()`; the JFR writer drains them with `processTraces()`. The storage keeps
three `CallTraceHashTable` instances and rotates them by swapping pointers, so
a drain never copies trace data and never blocks a writer.

Each trace gets a 64-bit ID made of the table's 32-bit instance ID and a 32-bit
slot index. The ID is stable for the life of the trace, including when a
liveness checker carries the trace over to later JFR chunks.

## Design Principles

1. **Signal-handler-safe writes**: `put()` uses only atomics and a
   [`RefCountGuard`](RefCountGuard.md); it never takes a lock or calls `malloc`.
2. **Unique trace IDs**: `(instance_id << 32) | (slot_base + slot)`; a table
   gets a fresh instance ID every time it retires from the active role.
3. **Continuity**: traces reported live by a liveness checker survive into the
   next cycle with their original IDs.
4. **Zero-copy rotation**: tables change role by pointer swaps.
5. **Safe reclamation**: a table's memory is freed only after the guards on it
   have drained.

## Buffer Roles

```
┌─────────────┐    ┌─────────────┐    ┌─────────────┐
│   ACTIVE    │    │   STANDBY   │    │   SCRATCH   │
│             │    │             │    │             │
│ New traces  │    │ Preserved   │    │ Previous    │
│ from put()  │    │ traces from │    │ active,     │
│             │    │ last cycle  │    │ cleared     │
└─────────────┘    └─────────────┘    └─────────────┘
```

- **ACTIVE** (`_active_storage`): the only table `put()` writes to.
- **STANDBY** (`_standby_storage`): holds the traces preserved by the previous
  `processTraces()`. No writer touches it.
- **SCRATCH** (`_scratch_storage`): empty at the start of `processTraces()`;
  receives the traces preserved during this cycle and becomes the next STANDBY.

## Rotation (`processTraces()`)

With tables `A` (active), `B` (standby) and `C` (scratch):

```
before:  ACTIVE = A   STANDBY = B   SCRATCH = C
after:   ACTIVE = B   STANDBY = C   SCRATCH = A
```

The steps, as implemented:

1. **Liveness**: under a shared `_liveness_lock`, every registered
   `LivenessChecker` adds the IDs of live traces to `_preserve_set_buffer`.
2. **Collect STANDBY (`B`)** into `_traces_buffer`. Each trace whose ID is in
   the preserve set is copied into `C` with `putWithExistingId()`.
3. **Reset `B`** with `clearTableOnly()`. Its chunks are detached, not freed:
   `_traces_buffer` still points into them.
4. **Swap** inside a `CriticalSection`: `_active_storage = B`,
   `_scratch_storage = A`, `_standby_storage = C`. New `put()` calls now go to
   `B`.
5. **Drain `A`**: `RefCountGuard::waitForRefCountToClear(A)` waits for any
   `put()` still holding a guard on it.
6. **Collect `A`** into `_traces_buffer`, again copying preserved traces into
   `C`.
7. **Re-number `A`**: `A->setInstanceId(getNextInstanceId())`.
8. **Process**: add the dropped-trace sentinel to `_traces_buffer` and call the
   `processor` callback.
9. **Free `B`'s old chunks** (`LinearAllocator::freeChunks()`).
10. **Clear `A`**: `clear()` if the drain in step 5 succeeded; otherwise
    `clearAfterFailedDrain()`, which resets the table and leaks its chunks
    instead of freeing memory a stalled `put()` might still write.

`B` becomes ACTIVE with the instance ID it received when it last retired from
ACTIVE (or at construction), so IDs never repeat across tenures.
`processTraces()` must not run concurrently with itself.

## `put()`

```cpp
u64 CallTraceStorage::put(int num_frames, ASGCT_CallFrame* frames,
                          bool truncated, u64 weight) {
    CallTraceHashTable* active = __atomic_load_n(&_active_storage, __ATOMIC_ACQUIRE);
    if (active == nullptr) return DROPPED_TRACE_ID;

    RefCountGuard guard(active);
    if (!guard.isActive()) return DROPPED_TRACE_ID;   // no free guard slot

    // Re-check after the guard is published (SEQ_CST, see RefCountGuard.md):
    // if the table was swapped out meanwhile, drop the sample rather than
    // touch a table that may be draining.
    if (__atomic_load_n(&_active_storage, __ATOMIC_SEQ_CST) != active)
        return DROPPED_TRACE_ID;

    return active->put(num_frames, frames, truncated, weight);
}
```

(Simplified from the source; each drop increments `CALLTRACE_STORAGE_DROPPED`.)

The guard protocol, the drain, and their memory-ordering arguments are described
in [RefCountGuard](RefCountGuard.md).

## Reclamation Rules

- `processTraces()` tolerates concurrent `put()`. A table is reclaimed only after
  it has been swapped out of `_active_storage`, which `put()` re-checks after
  taking its guard, and after the drain on it succeeds. If that drain times out,
  the table is still collected (the chunk needs its traces) but then reset with
  its chunks leaked, without draining a second time.
- `clear()` resets the *active* and standby tables in place. `_active_storage`
  does not change, so a `put()` that starts after the drain passes its re-check
  and could write into chunks being freed: `clear()` requires `put()` to be
  excluded.
- The destructor requires `put()` to be stopped. `put()` loads `_active_storage`
  before it takes its guard, so a `put()` still in flight could find the
  `CallTraceStorage` object itself freed; the table-level drains only cover a
  straggler that already holds a guard.

Today `Profiler` excludes `put()` from `processTraces()` and `clear()`, and never
destroys its `CallTraceStorage`: every `put()` runs under one of the stripe
locks, and every `processTraces()` / `clear()` caller (`FlightRecorder::stop()` /
`dump()` via `rotateDictsAndRun()`, and `Profiler::start()`) holds `lockAll()`,
which the dump needs anyway for the per-stripe JFR buffers. The drains therefore
find no guard on the table. If a drain does time out, debug builds abort and
release builds leak instead of freeing memory a `put()` may still be writing
(`clearTableOnly()` leaks the detached chunks, the destructor leaks the table).

`_generation_counter` is initialized but not read anywhere; ABA safety comes from
the guard plus the pointer re-check in `put()`, not from a generation check.

## Pre-allocated Buffers

`processTraces()` reuses two member collections instead of allocating per call:
`_traces_buffer` (`CallTraceSet`, pre-sized for 2048 traces) and
`_preserve_set_buffer` (`CallTraceIdSet`, pre-sized for 1024 IDs). Both use
`CountingAllocator`, so their memory is reported under `NM_CALLTRACE`.

## Liveness Preservation

```cpp
typedef std::function<void(CallTraceIdSet&)> LivenessChecker;
```

Checkers are registered with `registerLivenessChecker()` (exposed as
`Profiler::registerLivenessChecker()`) and removed with
`clearLivenessCheckers()`. The live-heap tracker (`livenessTracker.cpp`)
registers one that adds the trace IDs of tracked allocations that are still
live, so their stacks are written again in later chunks.

A preserved trace is reinserted by ID (`putWithExistingId()`), not by stack
hash, so identical stacks from different tenures keep their distinct IDs. The
preserving table is always cleared before it becomes ACTIVE again, so ID keys
never mix with `put()`'s stack-hash keys.

## 64-Bit Trace IDs

```
┌──────────────────────────────┬──────────────────────────────────────┐
│     Upper 32 bits            │          Lower 32 bits               │
│   Instance ID                │       slot_base + slot               │
└──────────────────────────────┴──────────────────────────────────────┘
```

- **Instance ID**: from the global `_next_instance_id` counter (starts at 1,
  incremented with `__atomic_fetch_add`). Each table gets one at construction
  and a new one in step 7 every time it retires from ACTIVE.
- **`slot_base + slot`**: a `CallTraceHashTable` grows by chaining a new
  `LongHashTable` of double capacity; each generation's `slot_base` is the sum of
  the previous capacities, so slot IDs stay unique across generations of one
  tenure. Expansion is skipped (`CALLTRACE_STORAGE_EXPANSION_SKIPPED`) if it would
  push `slot_base + slot` past 2^32 or if the doubled table would not fit in one
  allocator chunk; the table keeps working at a higher load factor until the next
  rotation resets it.

### Reserved IDs

| ID | Meaning |
|----|---------|
| `DROPPED_TRACE_ID = 1` | Sample dropped (no guard slot, storage swapped, allocation failed). A static `<dropped>` trace is added to every `processTraces()` output. |
| `OVERFLOW_TRACE_ID = 0x7fffffffffffffff` | Hash-table probe exhausted. A `storage_overflow` trace is collected when the table overflowed. |

Real IDs have an instance ID ≥ 1 in the upper half, so they cannot equal
`DROPPED_TRACE_ID`.

## Benchmarks

`ddprof-stresstest/src/jmh/java/com/datadoghq/profiler/stresstest/scenarios/throughput/`
contains whole-profiler throughput benchmarks (signal handlers, stack walking,
`CallTraceStorage`, JFR):

- `ProfilerThroughputQuickBenchmark` — short smoke set (1/8/32 threads, churn, burst)
- `ProfilerThroughputFullBenchmark` — baseline scaling, 1 to 64 threads
- `ProfilerThroughputThreadChurnBenchmark` — short-lived thread churn
- `ProfilerThroughputSlotExhaustionBenchmark` — burst/wave/sustained thread creation (500–4000 threads)

Run through Gradle (`-PjmhInclude` is a JMH include regex; fork, iteration and
time settings are fixed in `ddprof-stresstest/build.gradle.kts`):

```bash
./gradlew :ddprof-stresstest:jmh -PjmhInclude=ProfilerThroughputQuickBenchmark
```

Or run the JMH jar directly, which accepts standard JMH options and the
`WhiteboxProfiler` for profiler counters:

```bash
./gradlew :ddprof-stresstest:jmhJar
java -jar ddprof-stresstest/build/libs/stresstests.jar \
  -prof com.datadoghq.profiler.stresstest.WhiteboxProfiler \
  -f 1 -wi 1 -i 2 \
  ProfilerThroughputQuickBenchmark
```

`./gradlew :ddprof-stresstest:runStressTests` runs the jar with
`-prof com.datadoghq.profiler.stresstest.WhiteboxProfiler counters.*`; the
`counters.*` include selects the `scenarios.counters` benchmarks, not the
throughput ones above.
