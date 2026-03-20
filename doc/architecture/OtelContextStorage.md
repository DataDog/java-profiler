# OTEL-Compatible Context Storage Architecture

## Overview

The OTEL Context Storage system extends the profiler's existing Thread-Local Storage (TLS) context mechanism with an alternative storage mode compliant with [OTEP #4947](https://github.com/open-telemetry/opentelemetry-specification/pull/4947). This enables external profilers (like the OTel eBPF profiler) to discover and read tracing context from the Java profiler via a standard TLS pointer.

The system uses a feature-flagged approach where the storage mode is selected at profiler startup:
- **profiler mode** (default): Uses the existing TLS-based storage with checksum validation (`context_tls_v1`)
- **otel mode**: Uses an OTEP #4947 TLS pointer (`custom_labels_current_set_v2`) discoverable via ELF `dynsym`

## Core Design Principles

1. **OTEP Compliance**: TLS pointer and record layout match the OTEP #4947 specification
2. **External Discoverability**: `custom_labels_current_set_v2` symbol exported in `dynsym`
3. **Signal Handler Safety**: Record pointer cached in `ProfiledThread` — signal handlers never access TLS directly
4. **Unified API**: `ContextApi` abstracts storage mode from callers
5. **Backward Compatibility**: Default behavior unchanged, OTEL mode is opt-in

## Architecture Overview

### High-Level Component Diagram

```
┌─────────────────────────────────────────────────────────────────────────┐
│                           Java Layer                                     │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  JavaProfiler.execute("start,cpu=1ms,ctxstorage=otel,...")             │
│         │                                                               │
│         ▼                                                               │
│  ThreadContext.put(localRootSpanId, spanId, traceIdHigh, traceIdLow)    │
│         │                                                               │
│         ▼                                                               │
│  JNI: setContext0(localRootSpanId, spanId, traceIdHigh, traceIdLow)    │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                          Native Layer                                    │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ContextApi (Unified Interface)                                         │
│    │                                                                    │
│    ├─ initialize(args)    → Select mode based on ctxstorage option      │
│    ├─ setFull(lrs, span, trHi, trLo) → Write full context              │
│    ├─ get(spanId, rootSpanId) → Read from appropriate storage           │
│    ├─ setAttribute(idx, val)  → Write custom attribute                  │
│    └─ clear()                 → Clear current thread's context          │
│         │                                                               │
│         ├─────────────────────────┬─────────────────────────────────────┤
│         ▼                         ▼                                     │
│  ┌─────────────────────┐   ┌─────────────────────────────────────────┐  │
│  │  PROFILER Mode      │   │  OTEL Mode (OTEP #4947)                │  │
│  │  (TLS Storage)      │   │  (TLS Pointer Storage)                 │  │
│  │                     │   │                                         │  │
│  │  Context struct     │   │  custom_labels_current_set_v2 (TLS ptr)│  │
│  │  ├─ spanId          │   │  → OtelThreadContextRecord (640 bytes) │  │
│  │  ├─ rootSpanId      │   │       ├─ trace_id[16]                  │  │
│  │  ├─ checksum        │   │       ├─ span_id[8]                    │  │
│  │  └─ tags[10]        │   │       ├─ valid, _reserved              │  │
│  │                     │   │       ├─ attrs_data_size                │  │
│  │  Torn-read safety:  │   │       └─ attrs_data[612]               │  │
│  │  Checksum protocol  │   │                                         │  │
│  └─────────────────────┘   │  Torn-read safety: pointer-swapping    │  │
│                            │                                         │  │
│                            │  Discovery: ELF dynsym table            │  │
│                            └─────────────────────────────────────────┘  │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                     External Profiler (OTel eBPF)                       │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  1. Scan libjavaProfiler.so dynsym for custom_labels_current_set_v2    │
│  2. Record TLS offset                                                   │
│  3. For each thread: resolve TSD base + TLS offset                     │
│  4. Read pointer → if non-NULL, read header + attrs_data               │
│  5. Check valid == 1 → extract trace_id and span_id                    │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
```

## OTEP #4947 Thread Local Context Record

### Record Layout (640 bytes, packed)

```
┌─────────────────────────────────────────────────────────────────────────┐
│                OtelThreadContextRecord (640 bytes)                      │
├─────────┬──────┬────────────────┬───────────────────────────────────────┤
│  Offset │ Size │ Field          │ Description                           │
├─────────┼──────┼────────────────┼───────────────────────────────────────┤
│  0x00   │ 16   │ trace_id       │ uint8[16] — W3C 128-bit trace ID     │
│  0x10   │ 8    │ span_id        │ uint8[8] — 64-bit span ID            │
│  0x18   │ 1    │ valid          │ 1 = record ready for reading          │
│  0x19   │ 1    │ _reserved      │ Alignment padding                    │
│  0x1A   │ 2    │ attrs_data_size│ Number of valid bytes in attrs_data   │
│  0x1C   │ 612  │ attrs_data     │ Encoded key/value attribute pairs     │
└─────────┴──────┴────────────────┴───────────────────────────────────────┘

Each attribute in attrs_data:
  key_index: uint8  — index into process context's attribute_key_map
  length:    uint8  — length of value string (max 255)
  value:     uint8[length] — UTF-8 value bytes
```

### Byte Encoding

Datadog uses u64 for trace/span IDs. OTEP uses byte arrays. Conversion uses big-endian (W3C trace context):

- `trace_id[0..7]` ← trace_id_high (upper 64 bits)
- `trace_id[8..15]` ← trace_id_low (lower 64 bits, maps to rootSpanId)
- `span_id[0..7]` ← span_id

## Publication Protocol (OTEP #4947)

### Writer (application thread — JNI setContext0)

```cpp
// 1. Detach — external readers see no record during construction
custom_labels_current_set_v2 = nullptr;  // release barrier

// 2. Invalidate — signal handler readers (via cached pointer) see invalid record
record->valid = 0;  // release barrier

// 3. Populate record fields
u64ToBytes(trace_id_high, record->trace_id);
u64ToBytes(trace_id_low, record->trace_id + 8);
u64ToBytes(span_id, record->span_id);
record->attrs_data_size = 0;

// 4. Mark record valid
record->valid = 1;  // release barrier

// 5. Attach — publish completed record
custom_labels_current_set_v2 = record;  // release barrier
```

### Context Detachment

```cpp
custom_labels_current_set_v2 = nullptr;  // release barrier
```

### Reader (signal handler — via ProfiledThread)

```cpp
// Signal handlers NEVER access custom_labels_current_set_v2 directly
// (TLS lazy init can deadlock in musl's allocator)
OtelThreadContextRecord* record = profiledThread->getOtelContextRecord();
if (record != nullptr && record->valid == 1) {
    // Read trace_id and span_id from record
}
```

## Signal Safety

The critical constraint: signal handlers must never access `custom_labels_current_set_v2` directly. The pattern mirrors the existing `context_tls_v1` approach:

1. First non-signal-handler `ContextApi::set()` initializes TLS (with `SignalBlocker` to prevent musl deadlock)
2. Record pointer is cached in `ProfiledThread::_otel_ctx_record`
3. Signal handlers read via `ProfiledThread::getOtelContextRecord()`

### Record Lifecycle

- Allocated once per thread on first `ContextApi::set()` in OTEL mode
- Never freed until thread exits (ProfiledThread cleanup)
- Reused across span activations (no allocation in hot path)
- One record per thread (only one active span per thread)

## API Reference

### ContextApi (Unified Interface)

```cpp
class ContextApi {
public:
    static void initialize(const Arguments& args);
    static void shutdown();
    static ContextStorageMode getMode();

    static void set(u64 span_id, u64 root_span_id);           // Profiler mode only
    static void setFull(u64 lrs, u64 span, u64 trHi, u64 trLo); // Both modes
    static bool get(u64& span_id, u64& root_span_id);
    static void clear();
    static bool setAttribute(uint8_t key_index, const char* value, uint8_t value_len);
    static void registerAttributeKeys(const char** keys, int count);
};
```

### OtelContexts (OTEL-Specific Implementation)

```cpp
class OtelContexts {
public:
    static void initialize();
    static void shutdown();

    static void set(u64 trace_id_high, u64 trace_id_low, u64 span_id);
    static bool get(u64& trace_id_high, u64& trace_id_low, u64& span_id);
    static bool setAttribute(uint8_t key_index, const char* value, uint8_t value_len);
    static void clear();
};
```

## Configuration

| Option | Values | Default | Description |
|--------|--------|---------|-------------|
| `ctxstorage` | `profiler`, `otel` | `profiler` | Context storage mode |

### Usage Examples

```bash
# Default (profiler mode)
java -agentpath:libjavaProfiler.so=start,cpu=1ms,jfr,file=profile.jfr ...

# OTEL mode
java -agentpath:libjavaProfiler.so=start,cpu=1ms,ctxstorage=otel,jfr,file=profile.jfr ...
```

## Platform Support

| Platform | Profiler Mode | OTEL Mode | Notes |
|----------|---------------|-----------|-------|
| Linux x64 | Y | Y | Full support |
| Linux arm64 | Y | Y | Full support |
| Linux (musl) | Y | Y | Full support |
| macOS arm64 | Y | Y | Full support |
| macOS x64 | Y | Y | Full support |

## Performance Characteristics

| Operation | Profiler Mode | OTEL Mode | Notes |
|-----------|---------------|-----------|-------|
| Context write | ~10-20ns | ~15-25ns | OTEL: pointer-swap + byte conversion |
| Context read (signal handler) | ~5-10ns | ~5-10ns | Both use cached pointer / sidecar |
| Tag read (signal handler) | O(1) array | O(1) array | Sidecar caches Dictionary encodings |
| Memory overhead | ~64 bytes/thread | ~640 bytes + sidecar/thread | OTEL record + tag encoding sidecar |

## File Structure

```
ddprof-lib/src/main/cpp/
├── context.h              # Existing TLS context (profiler mode)
├── context.cpp
├── context_api.h          # Unified context abstraction
├── context_api.cpp
├── otel_context.h         # OTEP #4947 TLS pointer implementation
├── otel_context.cpp
├── otel_process_ctx.h     # OTEP #4719 process context (C library)
├── otel_process_ctx.cpp
├── thread.h               # ProfiledThread with tag encoding sidecar
├── arguments.h            # ctxstorage option
├── arguments.cpp
├── profiler.cpp           # ContextApi initialization
├── javaApi.cpp            # JNI routing through ContextApi
└── flightRecorder.cpp     # writeCurrentContext reads sidecar

ddprof-lib/src/main/java/com/datadoghq/profiler/
├── ThreadContext.java     # isOtelMode(), mode-aware getters
├── OTelContext.java       # Process context API

ddprof-test/src/test/java/com/datadoghq/profiler/context/
└── OtelContextStorageModeTest.java  # OTEL mode tests
```

## Future Considerations

1. **Process Context (OTEP #4719)**: Implemented — `thread_ctx_config` with `schema_version` and `attribute_key_map` is published via `ContextApi::registerAttributeKeys()`.

2. **Custom Attributes**: Implemented — `attrs_data` supports variable-length key/value pairs per the OTEP specification. `ThreadContext.setContextAttribute()` writes to OTEP record in OTEL mode, falls back to `registerConstant` + `Context.tags[]` in profiler mode.

3. **Cross-thread reads**: TLS cannot be accessed from another thread in-process. Signal handlers read their own thread's context via `ProfiledThread`'s cached record pointer.
