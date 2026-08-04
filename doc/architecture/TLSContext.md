# Thread-Local Context Architecture

## Overview

The Thread-Local Context (TLS Context) system provides a high-performance,
signal-handler-safe mechanism for capturing distributed tracing context
(trace IDs, span IDs, and custom attributes) during
profiling events. It enables the profiler to correlate performance samples
with active traces.

The system uses OTEL profiling signal conventions
([OTEP #4947](https://github.com/open-telemetry/oteps/pull/4947)) as its
sole context storage format. Java code writes tracing context through a
small set of native JNI primitives (`setTraceContext`/`clearTraceContext`/
`setContextValue`/`clearContextValue`) that resolve the current carrier's
`OtelThreadContextRecord` and mutate it directly — there is no cached
per-thread Java-side buffer. Two consumer paths read this context
concurrently:

1. **DD signal handler (SIGPROF)** — reads integer tag encodings and
   root-span ID from the sidecar buffer, and span ID from the OTEL record
   (ignores trace ID)
2. **External OTEP-compliant profilers** — discover the
   `otel_thread_ctx_v1` TLS symbol via ELF dynsym and read
   the `OtelThreadContextRecord` directly.

Each write resolves the current carrier's record inside a single JNI call —
race-free by construction under virtual-thread migration, since a JNI native
frame pins a mounted virtual thread to its carrier for the call's duration.
A detach/attach publication protocol ensures readers see either a complete
old record or a complete new record, never a torn intermediate state.

## Core Design Principles

1. **Signal Handler Safety** — all signal-handler reads use lock-free
   atomic loads with acquire semantics; no allocation, no locks, no
   syscalls.
2. **Detach/Attach Publication Protocol** — the `valid` flag is cleared
   before mutation and set after, with release fences between steps. The
   TLS pointer is set permanently at thread init.
3. **Two-Phase Attribute Registration** — string attribute values are
   registered in the native Dictionary once via JNI (`ContextValueCache`);
   subsequent uses of the same value reuse the cached encoding.
4. **Platform Independence** — correct on both strong (x86/TSO) and
   weak (ARM) memory models via explicit release fences.
5. **Low Overhead** — one JNI call per context operation; no cached buffer
   to invalidate or reattach across thread migration.

## Architecture

### High-Level Data Flow

```
┌─────────────────────────────────────────────────────────────────────┐
│                       Application Thread                            │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  Tracer calls JavaProfiler.setTraceContext(lrs, spanId, trHi, trLo, │
│                                             slot0, v0, slot1, v1)    │
│         │                                                           │
│         ▼                                                           │
│  ┌───────────────────────────────────────────────────────────────┐  │
│  │  setTraceContext0() (single JNI call)                        │  │
│  │  1. detach()  — valid ← 0, release fence                      │  │
│  │  2. record->trace_id/span_id ← big-endian encode              │  │
│  │  3. tag_encodings[0..9] ← 0                                   │  │
│  │     attrs_data_size ← LRS_ENTRY_SIZE (keeps fixed LRS at [0]) │  │
│  │  4. sidecar local_root_span_id ← lrs; write LRS hex entry     │  │
│  │  5. write slot0/slot1 activation attributes (if any)          │  │
│  │  6. attach() — release fence, valid ← 1                       │  │
│  └───────────────────────────────────────────────────────────────┘  │
│         │                                                           │
│         ▼                                                           │
│  ┌──────────────────────────────────────────────────────────────┐   │
│  │ ProfiledThread (native, per-thread heap allocation)          │   │
│  │ ┌──────────────────────┐  ┌───────────────────────────┐      │   │
│  │ │ OtelThreadContextRec │  │ tag_encodings[10] (u32)   │      │   │
│  │ │   trace_id[16]  (BE) │  │ local_root_span_id  (u64) │      │   │
│  │ │   span_id[8]    (BE) │  └───────────────────────────┘      │   │
│  │ │   valid          (u8)│    contiguous sidecar region        │   │
│  │ │   reserved       (u8)│                                     │   │
│  │ │   attrs_data_size(u16)│   ┌──────────────────────────────┐ │   │
│  │ │   attrs_data[612]    │   │ TLS pointer (8B)             │ │   │
│  │ └──────────────────────┘   │ otel_thread_ctx_v1           │ │   │
│  │   offsets 0..640           │ (thread_local, DLLEXPORT)    │ │   │
│  └──────────────────────────────────────────────────────────────┘   │
│         ▲                    ▲                                      │
│         │                    │                                      │
│  DD signal handler     External OTEP                                │
│  reads span_id         profiler reads                               │
│  from record           full record via                              │
│                        TLS symbol                                   │
└─────────────────────────────────────────────────────────────────────┘
```

### Component Architecture

```
┌──────────────────────────────────────────────────────────────────────┐
│                          Java Layer                                  │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│  JavaProfiler                                                        │
│    ├─ setTraceContext(lrs, spanId, trHi, trLo, slot0, v0, slot1, v1) │
│    ├─ clearTraceContext()                                           │
│    ├─ setContextValue(slot, value) / clearContextValue(slot)        │
│    └─ contextValueCache: ContextValueCache                          │
│                                                                      │
│  ContextValueCache (process-wide, shared across every carrier /     │
│                      virtual thread — no per-thread instance)       │
│    ├─ resolve(value) → {encoding, utf8}                             │
│    ├─ direct-mapped table keyed by value.hashCode() & 0xFF          │
│    └─ registerConstant0(String value) → int encoding (JNI)          │
└──────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                         Native Layer                                │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  ProfiledThread (per thread, heap-allocated)                        │
│    ├─ OtelThreadContextRecord _otel_ctx_record                      │
│    ├─ alignas(8) u32 _otel_tag_encodings[DD_TAGS_CAPACITY]          │
│    ├─ u64 _otel_local_root_span_id                                  │
│    └─ bool _otel_ctx_initialized                                    │
│                                                                     │
│  otel_thread_ctx_v1 (thread_local, DLLEXPORT)                       │
│    └─ OTEP #4947 TLS pointer for external profiler discovery        │
│                                                                     │
│  Recording::writeCurrentContext(Buffer*)  (signal handler)           │
│    ├─ ContextApi::get(spanId, rootSpanId)                           │
│    │    └─ acquire load of valid flag, big-endian decode of span_id │
│    └─ thrd->getOtelTagEncoding(i) for each attribute                │
└─────────────────────────────────────────────────────────────────────┘
```

## Memory Layout

### OtelThreadContextRecord

The OTEP #4947 record is a packed struct embedded in each `ProfiledThread`:

```
Offset  Size   Field             Description
──────────────────────────────────────────────────────────────────
0x00    16     trace_id          128-bit W3C trace ID (big-endian)
0x10     8     span_id           64-bit span ID (big-endian)
0x18     1     valid             1 = record is consistent, 0 = in-progress
0x19     1     _reserved         Reserved (must be 0)
0x1A     2     attrs_data_size   Size of attrs_data in bytes (LE uint16)
0x1C   612     attrs_data        TLV-encoded key/value attribute entries
──────────────────────────────────────────────────────────────────
Total: 640 bytes (OTEL_MAX_RECORD_SIZE)
```

### Sidecar Buffer

The sidecar is a contiguous, 8-byte-aligned region in `ProfiledThread`
that the DD signal handler reads directly:

```
Offset  Size   Field                     Description
──────────────────────────────────────────────────────────────────
0x00    40     _otel_tag_encodings[10]   Dictionary encoding per attribute (u32)
0x28     8     _otel_local_root_span_id  Local root span ID (u64)
──────────────────────────────────────────────────────────────────
Total: 48 bytes
```

Tag encodings are integer IDs from the profiler's `Dictionary` constant
pool — the signal handler writes them directly into JFR events without
any string lookup.

### attrs_data TLV Encoding

Each entry in `attrs_data` is encoded as:

```
┌──────────────┬──────────────┬───────────────────────┐
│ key_index(1) │ value_len(1) │ value_utf8[value_len] │
└──────────────┴──────────────┴───────────────────────┘
```

- `key_index` 0 is reserved for the local root span ID (16-char zero-padded lowercase hex string, always fixed at attrs_data[0..17]).
- `key_index` 1..N correspond to user-registered attributes offset by 1.

## The Detach/Attach Publication Protocol

### Problem

Two concurrent readers may observe the record at any point during a
native-side mutation:

1. **SIGPROF signal handler** — interrupts the writing thread
   mid-sequence, runs on the same thread.
2. **External OTEP profiler** — reads from a different thread via the
   `otel_thread_ctx_v1` TLS pointer.

Both must see either a complete old state or a complete new state, never
a partially-written record.

### Protocol

```
Native writer timeline (setTraceContext0 / setContextValue0):
──────────────────────────────────────────────────────────────────
Time 0:  detach()
           record->valid ← 0                        ← mark invalid
           release fence                             ← drain store buffer

Time 1:  Mutate record fields
           record->trace_id / span_id ← big-endian encode
           tag_encodings[0..9] ← 0                  ← zero tag encodings (setTraceContext0 only)
           attrs_data_size ← LRS_ENTRY_SIZE          ← keep only fixed LRS entry at attrs_data[0]
           sidecar local_root_span_id ← lrs          ← update LRS sidecar field
           writeLrsHex(lrs)                          ← update LRS hex entry in attrs_data

         ⚡ SIGPROF may arrive here — handler sees valid=0, skips record

Time 2:  attach()
           release fence                             ← ensure writes visible
           record->valid ← 1                         ← mark valid
──────────────────────────────────────────────────────────────────
```

`clearContextValue0` is the one exception: it preserves whatever `valid`
value it found (removing a single attribute must not resurrect a record
that a preceding `clearTraceContext0()` intentionally left detached).

### Reader: DD Signal Handler

```cpp
// flightRecorder.cpp — Recording::writeCurrentContext()
void Recording::writeCurrentContext(Buffer *buf) {
    u64 spanId = 0, rootSpanId = 0;
    bool hasContext = ContextApi::get(spanId, rootSpanId);  // acquire-loads valid flag
    buf->putVar64(spanId);
    buf->putVar64(rootSpanId);

    size_t numAttrs = Profiler::instance()->numContextAttributes();
    ProfiledThread* thrd = hasContext ? ProfiledThread::currentSignalSafe() : nullptr;
    for (size_t i = 0; i < numAttrs; i++) {
        buf->putVar32(thrd != nullptr ? thrd->getOtelTagEncoding(i) : 0);
    }
}
```

`ContextApi::get()` performs (context_api.cpp):

```cpp
OtelThreadContextRecord* record = thrd->getOtelContextRecord();
if (__atomic_load_n(&record->valid, __ATOMIC_ACQUIRE) != 1) {
    return false;  // record is being mutated — emit zeros
}
u64 val = 0;
for (int i = 0; i < 8; i++) { val = (val << 8) | record->span_id[i]; }
span_id = val;
```

The acquire fence pairs with the writer's release fence + `valid=1`
sequence, ensuring all record field writes are visible if `valid` reads
as 1.

### Reader: External OTEP Profiler

External profilers follow the OTEP #4947 protocol:

1. Discover `otel_thread_ctx_v1` via ELF `dlsym`.
2. Read the `OtelThreadContextRecord*` pointer. The pointer is set
   permanently at thread init; detach/attach never modify it. It is nulled
   on thread exit to prevent use-after-recycle — check for null before
   dereferencing.
3. Check `valid == 1`. If not, the record is being updated — skip.
4. Read `trace_id`, `span_id`, `attrs_data` from the record.

## Memory Ordering

### Why Barriers Are Needed

Both consumers need to see field writes ordered before `valid=1`, but for
different reasons:

- The **signal handler** runs on the same thread as the writer. The CPU presents
  its own stores in program order, so CPU store-buffer reordering is not a
  concern. The compiler can still reorder stores arbitrarily, so a compiler
  barrier is required.
- The **external OTEP profiler** (e.g. eBPF using scheduler events) attaches a
  `sched_switch` tracepoint that fires on the same CPU that was executing the
  thread. The Linux scheduler acquires `rq_lock` before the tracepoint fires,
  which includes a full hardware memory barrier (`smp_mb__before_spinlock` on
  ARM). By the time the eBPF probe runs, all prior user-space stores from that
  thread are globally visible.

In both cases the release fence prevents the compiler from sinking record
field writes past the `valid=1` store, and on ARM emits the hardware barrier
required to order field writes before `valid=1`.

## Initialization

### Self-Initializing on First Write

There is no separate TLS-initialization call. The first `setTraceContext0`
or `setContextValue0` on a thread that hasn't written context before:

1. Gets the calling thread's `ProfiledThread` (creates one if needed).
2. Sets `otel_thread_ctx_v1` permanently to the thread's
   `OtelThreadContextRecord` (triggering TLS slot init on musl).
3. Marks the thread's context initialized, so `ContextApi::get()` and the
   wall-clock sampler's precheck start considering the record.

A thread that only ever calls the all-native write API is therefore fully
visible to both the DD signal handler and external OTEP readers from its
very first write — no priming call is needed.

### Signal-Safe TLS Access

Signal handlers never call the write primitives (they may allocate on the
Dictionary-registration path). The read path uses a pre-initialized
pointer:

```cpp
// ProfiledThread::currentSignalSafe() — no allocation, no TLS lazy init
ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
if (thrd == nullptr || !thrd->isContextInitialized()) {
    return false;  // emit zeros
}
```

## Two-Phase Attribute Registration

String attributes are set via `JavaProfiler.setContextValue(slot, value)`
(or as activation attributes via `setTraceContext`). Registration is split
into two phases so that repeated values avoid a JNI call:

### Phase 1: Registration (cache miss)

On the first call with a new string value, `ContextValueCache.resolve`
crosses JNI once via `registerConstant0` to register the value in the
native Dictionary and cache the resulting `{encoding, utf8}` pair,
keyed by `value.hashCode() & 0xFF`.

### Phase 2: Cached Resolution (cache hit)

On subsequent calls with the same string, `ContextValueCache.resolve`
returns the cached `{encoding, utf8}` pair with no JNI call; the caller
still crosses JNI once to write the value into the current record (there
is no per-thread cached buffer to write into directly). Collisions in the
256-slot direct-mapped cache evict the old entry (benign — causes a
redundant `registerConstant0` call on the next use of the evicted value).
In production web applications with 5–50 unique attribute values, the hit
rate is effectively 100%.

## Signal Handler Read Path

`Recording::writeCurrentContext()` executes in the SIGPROF handler and
reads context in bounded time with no allocation:

1. `ContextApi::get(spanId, rootSpanId)`:
   - `ProfiledThread::currentSignalSafe()` — cached pointer, no TLS
     lazy init.
   - `__atomic_load_n(&record->valid, __ATOMIC_ACQUIRE)` — if 0, emit
     zeros (record is being mutated).
   - Read `span_id` from `OtelThreadContextRecord`.
   - Read `_otel_local_root_span_id` from sidecar.
2. For each registered attribute:
   - `thrd->getOtelTagEncoding(i)` — direct u32 read from sidecar.
   - Only read when `hasContext` is true; emits 0 otherwise, so tag
     encodings are never emitted alongside a zero span ID.

No dictionary lookup, no string comparison, no allocation. The
encodings written to JFR events are resolved later during JFR parsing.

## Testing

### Integration Tests (Java)

`ddprof-test/src/test/java/com/datadoghq/profiler/context/AllNativeContextTest.java`:

- Verifies `setTraceContext`/`clearTraceContext`/`setContextValue`/
  `clearContextValue` round-trip correctly, using package-private
  `JavaProfiler.test*` accessors (read via reflection) as the read oracle —
  each wraps a native primitive that reads the current thread's
  `OtelThreadContextRecord` directly, with no cached buffer involved.
- Covers span-transition attribute reset, attribute TLV encoding/overflow,
  and thread isolation.

`ddprof-test/src/test/java/com/datadoghq/profiler/context/AllNativeContextSamplingTest.java`:

- Regression test that the all-native write path self-initializes OTEL TLS
  on first write — a thread that never calls anything but the all-native
  API must still be visible to the wall-clock sampler.

`ddprof-test/src/test/java/com/datadoghq/profiler/wallclock/ContextWallClockTest.java`:

- Validates context propagation through wall-clock profiling
  samples and JFR event correlation across cstack modes.

`ddprof-test/src/test/java/com/datadoghq/profiler/ContextValueCacheTest.java`:

- Validates `ContextValueCache` resolution, hash-collision eviction,
  oversized-value rejection, and `clear()` semantics directly.

### JMH Benchmarks

`ddprof-stresstest/src/jmh/java/com/datadoghq/profiler/stresstest/scenarios/throughput/ContextCombinedBenchmark.java`:

- Perf-guard for the full per-scope activate+deactivate cycle
  (`setTraceContext`+`clearTraceContext`) as dd-trace-java drives it, on
  both platform and mounted virtual threads.

## OTEP References

- [OTEP #4947 — Profiling Signal Conventions](https://github.com/open-telemetry/oteps/pull/4947):
  Defines the `otel_thread_ctx_v1` TLS symbol, the
  `OtelThreadContextRecord` struct layout, and the publication protocol
  (valid flag + TLS pointer atomics).
- [OpenTelemetry Profiling SIG](https://github.com/open-telemetry/opentelemetry-specification/tree/main/specification/profiles):
  Broader context for profiling signal integration in the OTel
  ecosystem.
