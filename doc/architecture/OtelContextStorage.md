# OTEL-Compatible Context Storage Architecture

## Overview

The OTEL Context Storage system extends the profiler's existing Thread-Local Storage (TLS) context mechanism with an alternative storage mode that is compatible with the OpenTelemetry (OTEL) profiling proposal. This enables external profilers (like DDProf) to discover and read tracing context from the Java profiler without requiring direct integration.

The system uses a feature-flagged approach where the storage mode is selected at profiler startup:
- **profiler mode** (default): Uses the existing TLS-based storage with checksum validation
- **otel mode**: Uses an OTEL-compatible ring buffer storage discoverable via `/proc/<pid>/maps`

## Core Design Principles

1. **Feature-Flagged Storage**: Storage mode selected at startup, not runtime switchable
2. **External Discoverability**: OTEL buffer is discoverable by external profilers via named mmap regions
3. **Signal Handler Safety**: Both modes support safe reads from signal handlers
4. **Unified API**: `ContextApi` abstracts storage mode from callers
5. **Backward Compatibility**: Default behavior unchanged, OTEL mode is opt-in
6. **Platform Awareness**: OTEL mode fully supported on Linux, graceful fallback elsewhere

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
│  ThreadContext.put(spanId, rootSpanId)                                  │
│         │                                                               │
│         ▼                                                               │
│  JNI: setContext0(spanId, rootSpanId)                                   │
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
│    ├─ initialize(args)  → Select mode based on ctxstorage option        │
│    ├─ set(spanId, rootSpanId)  → Route to appropriate storage           │
│    ├─ get(spanId, rootSpanId)  → Read from appropriate storage          │
│    └─ getByTid(tid, ...)       → Read by thread ID (OTEL mode only)     │
│         │                                                               │
│         ├─────────────────────────┬─────────────────────────────────────┤
│         ▼                         ▼                                     │
│  ┌─────────────────────┐   ┌─────────────────────────────────────────┐  │
│  │  PROFILER Mode      │   │  OTEL Mode                              │  │
│  │  (TLS Storage)      │   │  (Ring Buffer Storage)                  │  │
│  │                     │   │                                         │  │
│  │  Context struct     │   │  OtelContextBuffer (mmap)               │  │
│  │  ├─ spanId          │   │  ├─ Header (magic, version, capacity)   │  │
│  │  ├─ rootSpanId      │   │  └─ Slots[capacity]                     │  │
│  │  ├─ checksum        │   │       ├─ trace_id_high                  │  │
│  │  └─ tags[10]        │   │       ├─ trace_id_low                   │  │
│  │                     │   │       ├─ span_id                        │  │
│  │  Torn-read safety:  │   │       └─ in_use flag                    │  │
│  │  Checksum protocol  │   │                                         │  │
│  └─────────────────────┘   │  Torn-read safety: in_use flag          │  │
│                            │                                         │  │
│                            │  Discovery: /proc/<pid>/maps            │  │
│                            │  → [anon:DD_OTEL_CTX]                   │  │
│                            └─────────────────────────────────────────┘  │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                       External Profiler (DDProf)                         │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  1. Parse /proc/<pid>/maps                                              │
│  2. Find region named [anon:DD_OTEL_CTX]                                │
│  3. Validate header (magic=0x4F54454C, version=1)                       │
│  4. Read slot by TID: buffer->slots[tid % capacity]                     │
│  5. Check in_use flag for torn-read safety                              │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
```

### Storage Mode Selection Flow

```
┌─────────────────────────────────────────────────────────────────────────┐
│                     Profiler Startup                                     │
└─────────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
                    ┌───────────────────────────────┐
                    │  Parse ctxstorage option      │
                    │  (default: profiler)          │
                    └───────────────────────────────┘
                                    │
                    ┌───────────────┴───────────────┐
                    ▼                               ▼
        ┌───────────────────┐           ┌───────────────────┐
        │ ctxstorage=profiler│          │ ctxstorage=otel   │
        └───────────────────┘           └───────────────────┘
                    │                               │
                    ▼                               ▼
        ┌───────────────────┐           ┌───────────────────┐
        │ Use existing TLS  │           │ Create mmap buffer│
        │ (no extra init)   │           │ with prctl naming │
        └───────────────────┘           └───────────────────┘
                    │                               │
                    │                   ┌───────────┴───────────┐
                    │                   ▼                       ▼
                    │       ┌───────────────────┐   ┌───────────────────┐
                    │       │ mmap succeeded    │   │ mmap failed       │
                    │       └───────────────────┘   └───────────────────┘
                    │                   │                       │
                    │                   ▼                       ▼
                    │       ┌───────────────────┐   ┌───────────────────┐
                    │       │ OTEL mode active  │   │ Fallback to       │
                    │       └───────────────────┘   │ profiler mode     │
                    │                               └───────────────────┘
                    │                               │
                    └───────────────┬───────────────┘
                                    ▼
                    ┌───────────────────────────────┐
                    │  ContextApi ready for use     │
                    └───────────────────────────────┘
```

## OTEL Ring Buffer Design

### Memory Layout

The OTEL buffer is a contiguous mmap region with a header followed by slot array:

```
┌─────────────────────────────────────────────────────────────────────────┐
│                        OtelContextBuffer Layout                          │
├─────────────────────────────────────────────────────────────────────────┤
│  Offset    │ Size   │ Field         │ Description                       │
├────────────┼────────┼───────────────┼───────────────────────────────────┤
│  0x00      │ 4      │ magic         │ 0x4F54454C ("OTEL" in ASCII)      │
│  0x04      │ 4      │ version       │ Protocol version (currently 1)    │
│  0x08      │ 4      │ capacity      │ Number of slots                   │
│  0x0C      │ 4      │ slot_size     │ sizeof(OtelContextSlot) = 32      │
│  0x10      │ 16     │ reserved      │ Future use (padding to 32 bytes)  │
├────────────┼────────┼───────────────┼───────────────────────────────────┤
│  0x20      │ 32     │ slots[0]      │ First context slot                │
│  0x40      │ 32     │ slots[1]      │ Second context slot               │
│  ...       │ ...    │ ...           │ ...                               │
│  N*32+0x20 │ 32     │ slots[N-1]    │ Last context slot                 │
└─────────────────────────────────────────────────────────────────────────┘

Total size: 32 (header) + 32 * capacity bytes
Default capacity: 65536 slots = 2MB + 32 bytes
```

### Slot Structure

Each slot is 32 bytes, aligned to prevent false sharing between adjacent slots:

```
┌─────────────────────────────────────────────────────────────────────────┐
│                      OtelContextSlot (32 bytes)                          │
├─────────────────────────────────────────────────────────────────────────┤
│  Offset │ Size │ Field          │ Description                           │
├─────────┼──────┼────────────────┼───────────────────────────────────────┤
│  0x00   │ 8    │ trace_id_high  │ Upper 64 bits of 128-bit trace ID     │
│  0x08   │ 8    │ trace_id_low   │ Lower 64 bits (maps to rootSpanId)    │
│  0x10   │ 8    │ span_id        │ 64-bit span ID                        │
│  0x18   │ 1    │ in_use         │ 1 = write in progress, 0 = valid      │
│  0x19   │ 7    │ padding        │ Alignment to 32 bytes                 │
└─────────────────────────────────────────────────────────────────────────┘
```

### TID-to-Slot Mapping

Slots are indexed by thread ID using simple modulo hashing:

```cpp
slot_index = tid % capacity
slot_ptr = &buffer->slots[slot_index]
```

**Collision Handling**: With 65536 slots, TID collisions are rare. When they occur:
- Two threads with `tid1 % 65536 == tid2 % 65536` share a slot
- The `in_use` flag prevents torn reads but context may be from either thread
- This is acceptable for profiling (low probability, bounded impact)

## Torn-Read Protection

### OTEL Mode: in_use Flag Protocol

The `in_use` flag provides torn-read safety using acquire/release semantics:

**Writer (application thread):**
```cpp
void OtelContexts::set(u64 trace_id_high, u64 trace_id_low, u64 span_id) {
    OtelContextSlot* slot = getSlot(OS::threadId());

    // 1. Mark write in progress (release semantics)
    __atomic_store_n(&slot->in_use, 1, __ATOMIC_RELEASE);

    // 2. Write data fields (relaxed - ordering from in_use barriers)
    __atomic_store_n(&slot->trace_id_high, trace_id_high, __ATOMIC_RELAXED);
    __atomic_store_n(&slot->trace_id_low, trace_id_low, __ATOMIC_RELAXED);
    __atomic_store_n(&slot->span_id, span_id, __ATOMIC_RELAXED);

    // 3. Mark write complete (release semantics)
    __atomic_store_n(&slot->in_use, 0, __ATOMIC_RELEASE);
}
```

**Reader (signal handler or external profiler):**
```cpp
bool OtelContexts::getByTid(int tid, u64& trace_high, u64& trace_low, u64& span) {
    OtelContextSlot* slot = getSlot(tid);

    // 1. Check if write in progress (acquire semantics)
    if (__atomic_load_n(&slot->in_use, __ATOMIC_ACQUIRE)) {
        return false;  // Write in progress, skip this sample
    }

    // 2. Read data fields (relaxed - ordering from in_use acquire)
    trace_high = __atomic_load_n(&slot->trace_id_high, __ATOMIC_RELAXED);
    trace_low = __atomic_load_n(&slot->trace_id_low, __ATOMIC_RELAXED);
    span = __atomic_load_n(&slot->span_id, __ATOMIC_RELAXED);

    // 3. Double-check (acquire semantics)
    if (__atomic_load_n(&slot->in_use, __ATOMIC_ACQUIRE)) {
        return false;  // Write started during read, discard
    }

    return true;
}
```

### Profiler Mode: Checksum Protocol

The existing TLS mode uses a checksum for torn-read detection (see TLSContext.md for details):

```cpp
// Writer
__atomic_store_n(&ctx.checksum, 0ULL, __ATOMIC_RELEASE);  // Invalidate
__atomic_store_n(&ctx.spanId, span_id, __ATOMIC_RELAXED);
__atomic_store_n(&ctx.rootSpanId, root_span_id, __ATOMIC_RELAXED);
__atomic_store_n(&ctx.checksum, computed_checksum, __ATOMIC_RELEASE);

// Reader
u64 checksum1 = __atomic_load_n(&ctx.checksum, __ATOMIC_ACQUIRE);
u64 span = __atomic_load_n(&ctx.spanId, __ATOMIC_RELAXED);
u64 root = __atomic_load_n(&ctx.rootSpanId, __ATOMIC_RELAXED);
bool valid = (checksum1 != 0) && (checksum1 == Contexts::checksum(span, root));
```

## External Discovery Mechanism

### Linux: Named Anonymous Mappings

On Linux 5.17+, the mmap region is named using `prctl(PR_SET_VMA_ANON_NAME)`:

```cpp
bool OtelContexts::initialize(size_t capacity) {
    size_t size = sizeof(OtelContextHeader) + capacity * sizeof(OtelContextSlot);

    // Create anonymous mapping
    void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE,
                     MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    // Name the region for discovery (Linux 5.17+ with CONFIG_ANON_VMA_NAME)
    prctl(PR_SET_VMA, PR_SET_VMA_ANON_NAME, ptr, size, "DD_OTEL_CTX");

    // Initialize header
    buffer->magic = 0x4F54454C;  // "OTEL"
    buffer->version = 1;
    buffer->capacity = capacity;
    buffer->slot_size = sizeof(OtelContextSlot);

    return true;
}
```

**External profiler discovery:**
```bash
# Find the OTEL context buffer in target process
grep "DD_OTEL_CTX" /proc/<pid>/maps
# Output: 7f1234560000-7f1234760000 rw-p 00000000 00:00 0 [anon:DD_OTEL_CTX]
```

### Fallback: Magic Number Scanning

If `prctl` naming is unavailable (older kernels, Docker/LinuxKit), external profilers can scan anonymous regions for the magic number:

```cpp
// External profiler pseudocode
for (region in parse_proc_maps(pid)) {
    if (region.is_anonymous && region.is_rw) {
        u32 magic = read_u32(region.start);
        if (magic == 0x4F54454C) {  // "OTEL"
            // Validate header
            OtelContextHeader* hdr = (OtelContextHeader*)region.start;
            if (hdr->version == 1 && hdr->slot_size == 32) {
                // Found valid OTEL context buffer
            }
        }
    }
}
```

## API Reference

### ContextApi (Unified Interface)

```cpp
// context_api.h

enum ContextStorageMode {
    CTX_STORAGE_PROFILER = 0,  // TLS-based storage (default)
    CTX_STORAGE_OTEL = 1       // OTEL ring buffer storage
};

class ContextApi {
public:
    // Lifecycle (single-threaded, called from Profiler::start/stop)
    static bool initialize(const Arguments& args);
    static void shutdown();
    static bool isInitialized();
    static ContextStorageMode getMode();

    // Context operations (thread-safe, signal-safe)
    static void set(u64 span_id, u64 root_span_id);
    static void setOtel(u64 trace_id_high, u64 trace_id_low, u64 span_id);
    static bool get(u64& span_id, u64& root_span_id);
    static bool getByTid(int tid, u64& span_id, u64& root_span_id);
    static void clear();
};
```

### OtelContexts (OTEL-Specific Implementation)

```cpp
// otel_context.h

class OtelContexts {
public:
    // Lifecycle
    static bool initialize(size_t capacity = 65536);
    static void shutdown();
    static bool isInitialized();

    // Context operations
    static void set(u64 trace_id_high, u64 trace_id_low, u64 span_id);
    static bool get(u64& trace_id_high, u64& trace_id_low, u64& span_id);
    static bool getByTid(int tid, u64& trace_id_high, u64& trace_id_low, u64& span_id);
};
```

### Java API

```java
// ThreadContext.java

public class ThreadContext {
    // Set context (routes through ContextApi)
    public long put(long spanId, long rootSpanId);

    // Get context (mode-aware)
    public long getSpanId();
    public long getRootSpanId();

    // Check storage mode
    public static boolean isOtelMode();
}
```

## Configuration

### Profiler Options

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

```java
// Programmatic API
JavaProfiler profiler = JavaProfiler.getInstance();
profiler.execute("start,cpu=1ms,ctxstorage=otel,jfr,file=profile.jfr");

// Check mode
if (ThreadContext.isOtelMode()) {
    System.out.println("OTEL context storage active");
}
```

## Platform Support

| Platform | Profiler Mode | OTEL Mode | Notes |
|----------|---------------|-----------|-------|
| Linux x64 | ✓ | ✓ | Full support |
| Linux arm64 | ✓ | ✓ | Full support |
| Linux (musl) | ✓ | ✓ | Full support |
| macOS arm64 | ✓ | ✓* | *mmap naming unavailable |
| macOS x64 | ✓ | ✓* | *mmap naming unavailable |

**Note**: On macOS, OTEL mode works but the mmap region cannot be named. External profilers must use magic number scanning for discovery.

## Performance Characteristics

| Operation | Profiler Mode | OTEL Mode | Notes |
|-----------|---------------|-----------|-------|
| Context write | ~10-20ns | ~15-25ns | OTEL slightly slower (TID lookup) |
| Context read (own thread) | ~5-10ns | ~10-15ns | OTEL has slot lookup overhead |
| Context read (by TID) | N/A | ~10-15ns | Only available in OTEL mode |
| Memory overhead | ~64 bytes/thread | ~2MB fixed | OTEL uses fixed-size buffer |

## File Structure

```
ddprof-lib/src/main/cpp/
├── context.h              # Existing TLS context (profiler mode)
├── context.cpp
├── context_api.h          # NEW: Unified context abstraction
├── context_api.cpp
├── otel_context.h         # NEW: OTEL ring buffer implementation
├── otel_context.cpp
├── arguments.h            # Modified: ctxstorage option
├── arguments.cpp
├── profiler.cpp           # Modified: ContextApi initialization
├── javaApi.cpp            # Modified: JNI routing through ContextApi
└── wallClock.cpp          # Modified: Uses ContextApi

ddprof-lib/src/main/java/com/datadoghq/profiler/
├── ThreadContext.java     # Modified: isOtelMode(), mode-aware getters

ddprof-test/src/test/java/com/datadoghq/profiler/context/
└── OtelContextStorageModeTest.java  # NEW: OTEL mode tests
```

## Future Considerations

1. **Full 128-bit Trace ID**: Currently `trace_id_high` is unused (set to 0). Future integration with OTEL tracers may populate the full 128-bit trace ID.

2. **Tags Support in OTEL Mode**: The current OTEL mode does not support custom tags. This could be added by extending the slot structure.

3. **Shared Buffer Discovery**: The named mmap region could be made `MAP_SHARED` to allow in-process discovery without `/proc` parsing.

4. **Dynamic Capacity**: Currently capacity is fixed at initialization. Dynamic resizing could be added for long-running applications with many threads.
