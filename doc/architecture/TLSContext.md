# Thread-Local Context Architecture

## Overview

The Thread-Local Context (TLS Context) system provides a high-performance,
signal-handler-safe mechanism for capturing distributed tracing context
(trace IDs, span IDs, and custom attributes) during
profiling events. It enables the profiler to correlate performance samples
with active traces.

The system uses OTEL profiling signal conventions
([OTEP #4947](https://github.com/open-telemetry/oteps/pull/4947)) as its
sole context storage format. Java code writes tracing context into
thread-local `DirectByteBuffer`s mapped to native structs. Two consumer
paths read this context concurrently:

1. **DD signal handler (SIGPROF)** — reads integer tag encodings and
   root-span ID from the sidecar buffer, and span ID from the OTEL record
   (ignores trace ID)
2. **External OTEP-compliant profilers** — discover the
   `otel_thread_ctx_v1` TLS symbol via ELF dynsym and read
   the `OtelThreadContextRecord` directly.

All writes from Java are zero-JNI on the hot path (cache-hit case),
using `DirectByteBuffer` with explicit memory ordering. A detach/attach
publication protocol ensures readers see either a complete old record or
a complete new record, never a torn intermediate state.

For benchmark data, see
[ThreadContext Benchmark Report](../performance/reports/thread-context-benchmark-2026-03-21.md).

## Core Design Principles

1. **Zero-Copy Shared Memory** — Java writes to `DirectByteBuffer`s
   mapped to native `ProfiledThread` fields; no data copying between
   Java and native heaps.
2. **Signal Handler Safety** — all signal-handler reads use lock-free
   atomic loads with acquire semantics; no allocation, no locks, no
   syscalls.
3. **Detach/Attach Publication Protocol** — the `valid` flag is cleared
   before mutation and set after, with `storeFence` barriers between
   steps. The TLS pointer is set permanently at thread init.
4. **Two-Phase Attribute Registration** — string attribute values are
   registered in the native Dictionary once via JNI; subsequent uses
   are zero-JNI ByteBuffer writes from a per-thread encoding cache.
5. **Platform Independence** — correct on both strong (x86/TSO) and
   weak (ARM) memory models via explicit `storeFence` / volatile write
   barriers.
6. **Low Overhead** — typical span lifecycle write ~30 ns, sidecar
   encoding read ~2 ns (no syscalls, no locks).

## Architecture

### High-Level Data Flow

```
┌─────────────────────────────────────────────────────────────────────┐
│                       Application Thread                            │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  Tracer calls ThreadContext.put(lrs, spanId, trHi, trLo)            │
│         │                                                           │
│         ▼                                                           │
│  ┌───────────────────────────────────────────────────────────────┐  │
│  │  setContextDirect()                                           │  │
│  │  1. detach()  — valid ← 0, storeFence                         │  │
│  │  2. ctxBuffer.putLong(traceIdOffset, reverseBytes(trHi))      │  │
│  │     ctxBuffer.putLong(traceIdOffset+8, reverseBytes(trLo))    │  │
│  │     ctxBuffer.putLong(spanIdOffset, reverseBytes(spanId))     │  │
│  │  3. tag_encodings[0..9] ← 0                                   │  │
│  │     attrs_data_size ← LRS_ENTRY_SIZE (keeps fixed LRS at [0]) │  │
│  │  4. ctxBuffer.putLong(lrsOffset, lrs)                         │  │
│  │     writeLrsHex(lrs) — update fixed LRS entry in attrs_data   │  │
│  │  5. attach() — storeFence, valid ← 1                          │  │
│  └───────────────────────────────────────────────────────────────┘  │
│         │                                                           │
│         ▼                                                           │
│  ┌──────────────────────────────────────────────────────────────┐   │
│  │ Unified ctxBuffer (688B, single DirectByteBuffer)            │   │
│  │ ┌──────────────────────┐  ┌───────────────────────────┐      │   │
│  │ │ OtelThreadContextRec │  │ tag_encodings[10] (u32)   │      │   │
│  │ │   trace_id[16]  (BE) │  │ local_root_span_id  (u64) │      │   │
│  │ │   span_id[8]    (BE) │  └───────────────────────────┘      │   │
│  │ │   valid          (u8)│    offsets 640..688 in ctxBuffer    │   │
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
│    ├─ ThreadLocal<ThreadContext> tlsContextStorage                   │
│    ├─ initializeContextTLS0(long[] metadata) → ByteBuffer (688B)     │
│    └─ registerConstant0(String value) → int encoding                 │
│                                                                      │
│  ThreadContext (per thread)                                          │
│    ├─ ctxBuffer  (688B DirectByteBuffer — record + sidecar contiguous)│
│    ├─ put(lrs, spanId, trHi, trLo)  → setContextDirect()             │
│    ├─ setContextAttribute(keyIdx, value) → setContextAttributeDirect │
│    ├─ snapshot(byte[], int) / restore(byte[], int)  ← nested scopes  │
│    └─ Per-thread caches:                                             │
│         └─ attrCache[CACHE_SIZE]: String → {int encoding, byte[] utf8}│
│                                                                      │
│  BufferWriter (memory ordering abstraction)                          │
│    ├─ BufferWriter8  (Java 8:  Unsafe)                               │
│    │    ├─ putOrderedLong / putOrderedInt                            │
│    │    └─ storeFence → Unsafe.storeFence()                          │
│    └─ BufferWriter9  (Java 9+: VarHandle)                            │
│         ├─ setRelease                                                │
│         └─ storeFence → VarHandle.storeStoreFence()                  │
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

The sidecar fields are exposed to Java as a single `DirectByteBuffer`.
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
Java-side mutation:

1. **SIGPROF signal handler** — interrupts the writing thread
   mid-sequence, runs on the same thread.
2. **External OTEP profiler** — reads from a different thread via the
   `otel_thread_ctx_v1` TLS pointer.

Both must see either a complete old state or a complete new state, never
a partially-written record.

### Protocol

```
Java writer timeline:
──────────────────────────────────────────────────────────────────
Time 0:  detach()
           ctxBuffer.put(validOffset, 0)           ← mark invalid
           storeFence()                            ← drain store buffer

Time 1:  Mutate record fields
           ctxBuffer.putLong(traceIdOffset, ...)
           ctxBuffer.putLong(spanIdOffset, ...)
           tag_encodings[0..9] ← 0                 ← zero tag encodings (offsets 640..680)
           attrs_data_size ← LRS_ENTRY_SIZE        ← keep only fixed LRS entry at attrs_data[0]
           ctxBuffer.putLong(lrsOffset, lrs)       ← update LRS at offset 680
           writeLrsHex(lrs)                        ← update LRS hex entry in attrs_data

         ⚡ SIGPROF may arrive here — handler sees valid=0, skips record

Time 2:  attach()
           storeFence()                            ← ensure writes visible
           ctxBuffer.put(validOffset, 1)           ← mark valid
──────────────────────────────────────────────────────────────────
```

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

The acquire fence pairs with the writer's `storeFence` + `valid=1`
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
  concern. The JIT compiler can still reorder stores arbitrarily, so a compiler
  barrier is required.
- The **external OTEP profiler** (e.g. eBPF using scheduler events) attaches a
  `sched_switch` tracepoint that fires on the same CPU that was executing the
  thread. The Linux scheduler acquires `rq_lock` before the tracepoint fires,
  which includes a full hardware memory barrier (`smp_mb__before_spinlock` on
  ARM). By the time the eBPF probe runs, all prior user-space stores from that
  thread are globally visible — including any stores ordered by `DMB ISHST`.

In both cases `storeFence` serves as a compiler barrier that prevents the JIT
from sinking record field writes past the `valid=1` store. On ARM it also emits
`DMB ISHST`, which is required to order field writes before `valid=1` at the
hardware level — this is not a mere side effect.

### Barrier Taxonomy

| Operation | Java 8 | Java 9+ | ARM | x86 |
|-----------|--------|---------|-----|-----|
| `storeFence` | `Unsafe.storeFence` | `VarHandle.storeStoreFence` | DMB ISHST (~2 ns) | compiler barrier (free) |

On x86, `storeFence` is a compiler-only barrier (TSO guarantees hardware
store ordering for free; Java 9+ `VarHandle.storeStoreFence` emits no
hardware instruction on x86). On ARM it compiles to `DMB ISHST` (~2 ns).

### Why storeFence, Not fullFence

The detach/attach protocol only requires store-store ordering — all
operations on the hot path are writes. There are no load-dependent
ordering requirements on the writer side. `storeFence` (~2 ns on ARM)
is sufficient; a full fence (~50 ns on ARM) would be wasteful.

## Initialization

### Per-Thread TLS Setup

When a thread first accesses its `ThreadContext` via the `ThreadLocal`:

```java
// JavaProfiler.initializeThreadContext()
long[] metadata = new long[6];
ByteBuffer buffer = initializeContextTLS0(metadata);
return new ThreadContext(buffer, metadata);
```

The native `initializeContextTLS0` (in `javaApi.cpp`):

1. Gets the calling thread's `ProfiledThread` (creates one if needed).
2. Sets `otel_thread_ctx_v1` permanently to the thread's
   `OtelThreadContextRecord` (triggering TLS slot init on musl).
3. Fills the `metadata` array with absolute offsets into the unified
   buffer (computed via `offsetof` for record fields; `OTEL_MAX_RECORD_SIZE
   + DD_TAGS_CAPACITY*sizeof(u32) = 680` for the LRS offset), so Java code
   writes to the correct positions regardless of struct packing changes.
4. Creates a single `DirectByteBuffer` spanning the contiguous 688-byte
   region: `_otel_ctx_record` (640 B) followed immediately by
   `_otel_tag_encodings` (40 B) and `_otel_local_root_span_id` (8 B).
   Contiguity is enforced by `alignas(8)` on `_otel_ctx_record` plus
   `sizeof(OtelThreadContextRecord)` being a multiple of 8.
5. Returns the single buffer.

This is the only JNI call in the initialization path. After this, all
hot-path operations are pure Java ByteBuffer writes into offset regions
of the one buffer.

### Signal-Safe TLS Access

Signal handlers cannot call `initializeContextTLS0` (it may allocate). The
read path uses a pre-initialized pointer:

```cpp
// ProfiledThread::currentSignalSafe() — no allocation, no TLS lazy init
ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
if (thrd == nullptr || !thrd->isContextInitialized()) {
    return false;  // emit zeros
}
```

## Two-Phase Attribute Registration

String attributes are set via `ThreadContext.setContextAttribute(keyIndex, value)`.
The hot path avoids JNI by splitting the work into two phases:

### Phase 1: Registration (cache miss)

On the first call with a new string value:

```java
encoding = registerConstant0(value);  // JNI → Dictionary lookup
utf8 = value.getBytes(UTF_8);        // one allocation, cached
attrCacheEncodings[slot] = encoding;
attrCacheBytes[slot] = utf8;
attrCacheKeys[slot] = value;          // cache is per-thread; no fence needed
```

`registerConstant0` crosses JNI once to register the value in the
native `Dictionary` and returns an integer encoding.

### Phase 2: Cached Write (cache hit, zero JNI)

On subsequent calls with the same string:

```java
if (value.equals(attrCacheKeys[slot])) {
    encoding = attrCacheEncodings[slot];  // int read
    utf8 = attrCacheBytes[slot];          // ref read
}
// Both sidecar and OTEP attrs_data are written inside the detach/attach window
// so a signal handler never sees a new sidecar encoding alongside old attrs_data.
detach();
ctxBuffer.putInt(TAG_ENCODINGS_OFFSET + keyIndex * 4, encoding);
replaceOtepAttribute(otepKeyIndex, utf8);
attach();
```

The cache is a 256-slot direct-mapped structure keyed by
`value.hashCode() & 0xFF`. Collisions evict the old entry (benign —
causes a redundant `registerConstant0` call). In production web
applications with 5–50 unique attribute values, the hit rate is
effectively 100%.

## Signal Handler Read Path

`Recording::writeCurrentContext()` executes in the SIGPROF handler and
reads context in bounded time (~15 ns) with no allocation:

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

## Performance

### Write Path Costs (arm64, Java 25)

| Operation | ns/op | Path |
|-----------|------:|------|
| `clearContext` | 5.0 | detach + zero fields |
| `setContextFull` | 11.1 | detach + 3 putLong + attach |
| `setAttrCacheHit` | 10.7 | cache lookup + sidecar write + detach/attach |
| `spanLifecycle` | 30.4 | `setContextFull` + `setAttrCacheHit` |

### Multi-Threaded Scaling

| Benchmark | 1 thread | 2 threads | 4 threads |
|-----------|----------|-----------|-----------|
| `setContextFull` | 11.1 ns | 11.1 ns | 11.7 ns |
| `spanLifecycle` | 30.4 ns | 30.7 ns | 32.2 ns |

No false sharing: each thread's `OtelThreadContextRecord` and sidecar
are embedded in its own heap-allocated `ProfiledThread`.

### Instrumentation Budget

At ~35 ns per span (`spanLifecycle` 30.4 ns + `clearContext` 5.0 ns), a single thread
can sustain ~28 million span transitions per second. For a web
application at 100K requests/second, this is <0.004% of CPU time.

Full benchmark data and analysis:
[thread-context-benchmark-2026-03-21.md](../performance/reports/thread-context-benchmark-2026-03-21.md)

## Testing

### Integration Tests (Java)

`ddprof-test/src/test/java/com/datadoghq/profiler/context/OtelContextStorageModeTest.java`:

- **testOtelStorageModeContext** — context round-trips correctly with JFR running.
- **testOtelModeCustomAttributes** — verifies attribute TLV encoding in
  `attrs_data` via `setContextAttribute`.
- **testOtelModeAttributeOverflow** — overflow of `attrs_data` is handled
  gracefully (returns false, no crash).
- **testSequentialContextUpdates** — repeated writes with varying values,
  `Long.MAX_VALUE` round-trip, and `clearContext` resetting both IDs to zero.
- **testThreadIsolation** — concurrent writes from multiple threads,
  validating thread-local isolation.
- **testSpanTransitionClearsAttributes** — direct span-to-span transition
  without `clearContext` does not leak custom attributes from the previous span.

`ddprof-test/src/test/java/com/datadoghq/profiler/wallclock/ContextWallClockTest.java`:

- **test** — validates context propagation through wall-clock profiling
  samples and JFR event correlation across cstack modes.

`ddprof-test/src/test/java/com/datadoghq/profiler/context/TagContextTest.java`:

- **test** — validates integer tag/attribute context propagation through
  profiling samples.

### JMH Benchmarks

`ddprof-stresstest/src/jmh/java/com/datadoghq/profiler/stresstest/scenarios/throughput/ThreadContextBenchmark.java`:

- Single-threaded: `setContextFull`, `setAttrCacheHit`, `spanLifecycle`,
  `clearContext`, `getContext`.
- Multi-threaded: `setContextFull_2t/4t`, `spanLifecycle_2t/4t` —
  `@Threads(2)` and `@Threads(4)` variants to verify linear scaling
  (absence of false sharing).

## OTEP References

- [OTEP #4947 — Profiling Signal Conventions](https://github.com/open-telemetry/oteps/pull/4947):
  Defines the `otel_thread_ctx_v1` TLS symbol, the
  `OtelThreadContextRecord` struct layout, and the publication protocol
  (valid flag + TLS pointer atomics).
- [OpenTelemetry Profiling SIG](https://github.com/open-telemetry/opentelemetry-specification/tree/main/specification/profiles):
  Broader context for profiling signal integration in the OTel
  ecosystem.
