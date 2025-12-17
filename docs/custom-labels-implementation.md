# Custom Labels Implementation

## Overview

This document describes the implementation of custom labels support in the Datadog Java Profiler, compliant with the Custom Label ABI v1 specification (see `custom-labels-v1.md`).

The implementation provides a thread-local label storage mechanism that allows external profilers to read label key-value pairs from interrupted threads without requiring synchronization.

## Design Goals

1. **ABI Compliance**: Expose `custom_labels_labelset_t` structure via thread-local storage
2. **Zero Dynamic Allocation**: Pre-allocated fixed-size buffers to avoid malloc in hot paths
3. **Performance**: Minimize overhead in label set/get operations
4. **Signal Safety**: Safe to read from signal handlers (profiler sampling)
5. **Integration**: Support both trace context (spanId/rootSpanId) and custom labels

## Memory Layout

The implementation uses a single pre-allocated buffer per thread with the following structure:

```
Total size: 4184 bytes

┌─────────────────────────────────────────────────────────────┐
│ Header: custom_labels_labelset_t (24 bytes)                 │
│   - storage (8 bytes): pointer to label array               │
│   - count (8 bytes): current number of active labels        │
│   - capacity (8 bytes): maximum labels (constant: 10)       │
├─────────────────────────────────────────────────────────────┤
│ Label Array: 10 × custom_labels_label_t (320 bytes)         │
│   Label 0:                                                   │
│     - key.len (8 bytes)                                      │
│     - key.buf (8 bytes): pointer to label 0's key buffer    │
│     - value.len (8 bytes)                                    │
│     - value.buf (8 bytes): pointer to label 0's value buffer│
│   Label 1: (same structure)                                 │
│   ...                                                        │
│   Label 9: (same structure)                                 │
├─────────────────────────────────────────────────────────────┤
│ String Buffers: 10 × (128 + 256) bytes (3840 bytes)         │
│   Label 0:                                                   │
│     - key buffer (128 bytes, fixed size)                    │
│     - value buffer (256 bytes, fixed size)                  │
│   Label 1:                                                   │
│     - key buffer (128 bytes, fixed size)                    │
│     - value buffer (256 bytes, fixed size)                  │
│   ...                                                        │
│   Label 9:                                                   │
│     - key buffer (128 bytes, fixed size)                    │
│     - value buffer (256 bytes, fixed size)                  │
└─────────────────────────────────────────────────────────────┘
```

### Offset Calculations

- **Header**: bytes 0-23
- **Label array start**: byte 24
- **Label N metadata**: byte 24 + (N × 32)
- **String buffers start**: byte 344 (24 + 320)
- **Label N key buffer**: byte 344 + (N × 384)
- **Label N value buffer**: byte 344 + (N × 384) + 128

## Constraints

### Hard Limits

- **Maximum labels**: 10 per thread
- **Maximum key length**: 128 bytes (UTF-8 encoded)
- **Maximum value length**: 256 bytes (UTF-8 encoded)
- **Strings exceeding limits**: Truncated without error

### Special Labels

Labels at index 0 and 1 are reserved for trace context:

- **Label 0**: `span-id` → current span ID (formatted as decimal long)
- **Label 1**: `root-span-id` → root span ID (formatted as decimal long)

These are automatically populated when `ThreadContext.put(spanId, rootSpanId)` is called.

## Architecture

### Native Layer (C++)

**Thread-Local Storage**:
```c++
// Exported symbol for ABI compliance
DLLEXPORT thread_local custom_labels_labelset_t* custom_labels_current_set;

// ABI version indicator
DLLEXPORT const uint32_t custom_labels_abi_version = 1;
```

**Initialization**:
- `Contexts::initializeContextTls()` allocates and initializes the 4184-byte buffer
- Pre-populates label 0 and 1 with keys "span-id" and "root-span-id"
- Sets all label value pointers to NULL initially (absent values)
- Stores the address in ProfiledThread for signal-safe access

**Label Operations**:
- `setLabel(key, value)`: Native function that:
  1. Searches for existing key in labels 2-9 (linear scan)
  2. If found, updates value in-place
  3. If not found and space available, adds new label
  4. Copies strings to fixed buffers (truncates if needed)
  5. Updates pointers and count atomically

### Java Layer

**ThreadContext.java**:
```java
// Simplified API - no more ByteBuffer manipulation
public class ThreadContext {
    // Set trace context (updates labels 0 and 1)
    public void put(long spanId, long rootSpanId);

    // Set custom label (uses labels 2-9)
    public void setLabel(String key, String value);

    // Remove custom label by key
    public void removeLabel(String key);

    // Clear all custom labels (preserves span-id/root-span-id)
    public void clearLabels();
}
```

**ContextSetter.java**:
```java
// Updated to use string-based API
public class ContextSetter {
    public boolean setContextValue(String key, String value) {
        profiler.getThreadContext().setLabel(key, value);
        return true;
    }
}
```

## API Usage

### Setting Trace Context

```java
JavaProfiler profiler = JavaProfiler.getInstance();
profiler.setContext(12345L, 67890L);
// Results in:
// - Label 0: key="span-id", value="12345"
// - Label 1: key="root-span-id", value="67890"
```

### Setting Custom Labels

```java
ContextSetter setter = new ContextSetter(profiler, Arrays.asList("user.id", "request.type"));
setter.setContextValue("user.id", "alice");
setter.setContextValue("request.type", "api");
// Results in:
// - Label 2: key="user.id", value="alice"
// - Label 3: key="request.type", value="api"
```

### Reading Labels (External Profiler)

External profilers can read the thread-local `custom_labels_current_set` pointer:

1. Locate the symbol in the process memory
2. Read the TLS descriptor to get thread-specific instance
3. Follow the `storage` pointer to read label array
4. For each label, check if `key.buf` is non-null
5. Read key/value strings using `buf` pointers and `len` fields

## Performance Considerations

### Hot Path Optimizations

1. **No Dynamic Allocation**: All buffers pre-allocated at thread initialization
2. **Fixed-Size Buffers**: Pointer arithmetic instead of dynamic arrays
3. **Linear Scan**: With only 10 labels max, linear search is faster than hash lookup
4. **In-Place Updates**: Reusing existing label slots when keys match
5. **JNI-Only**: Label operations delegate directly to native code (Java 17+)

### Trade-offs

- **Memory Usage**: 4184 bytes per thread (acceptable for thread-local data)
- **Label Capacity**: Limited to 10 labels (sufficient for trace context + custom tags)
- **String Length**: Truncation instead of error handling (performance over safety)

## Signal Safety

The implementation is signal-safe for **reading**:

- No malloc/free during label reads
- No locks required for reads
- Atomic pointer updates for label modifications
- ProfiledThread stores context pointer to avoid TLS lazy initialization in signal handlers

**Note**: Label **writes** are not signal-safe and should only occur in normal execution context.

## ABI Compliance

### Exported Symbols

1. **`custom_labels_abi_version`**: 4-byte constant with value `1`
2. **`custom_labels_current_set`**: Thread-local pointer to `custom_labels_labelset_t`

### TLS Model

Uses `__thread` attribute with appropriate TLS model:
- **x86-64**: `-ftls-model=global-dynamic -mtls-dialect=gnu2`
- **aarch64**: `-ftls-model=global-dynamic -mtls-dialect=desc`

### Structure Layout

Exactly matches the ABI specification:

```c
typedef struct {
    size_t len;
    const unsigned char *buf;
} custom_labels_string_t;

typedef struct {
    custom_labels_string_t key;
    custom_labels_string_t value;
} custom_labels_label_t;

typedef struct {
    custom_labels_label_t *storage;
    size_t count;
    size_t capacity;
} custom_labels_labelset_t;
```

## Migration from Previous Implementation

### Removed Features

1. **Checksum field**: No longer needed with string-based labels
2. **ByteBuffer direct manipulation**: All operations via JNI
3. **Integer encoding**: Labels use strings directly instead of constant pool IDs
4. **Offset-based API**: `putCustom(offset, value)` replaced with `setLabel(key, value)`

### API Changes

| Old API | New API |
|---------|---------|
| `ThreadContext.put(spanId, rootSpanId)` | Same (internally sets labels 0-1) |
| `ThreadContext.putCustom(offset, value)` | `ThreadContext.setLabel(key, value)` |
| `ContextSetter.setContextValue(attribute, value)` | Same (uses setLabel internally) |
| `profiler.registerConstant(key)` | Removed (no more constant pool) |

## Testing Considerations

### Unit Tests

1. **Label CRUD**: Set, update, remove labels
2. **Truncation**: Verify strings exceeding limits are truncated
3. **Capacity**: Verify behavior when exceeding 10 labels
4. **Reserved Labels**: Verify span-id/root-span-id handling
5. **Thread Isolation**: Verify labels are thread-local

### Integration Tests

1. **ABI Compliance**: External tool reads labels via TLS
2. **Profiler Integration**: Verify labels appear in JFR output
3. **Performance**: Benchmark label set/get operations
4. **Concurrency**: Multiple threads setting labels concurrently

## Future Considerations

### Potential Enhancements

1. **Dynamic Capacity**: Support configuration of max labels
2. **Error Reporting**: Return codes for truncation/capacity exceeded
3. **Label Enumeration**: Java API to list current labels
4. **Metrics**: Track label usage statistics

### Backward Compatibility

The new implementation breaks binary compatibility with code using the old offset-based API. Applications must update to use the string-based API.

## References

- [Custom Label ABI v1 Specification](custom-labels-v1.md)
- [ELF Handling For Thread-Local Storage](https://www.akkadia.org/drepper/tls.pdf)
- Context implementation: `ddprof-lib/src/main/cpp/context.{h,cpp}`
- Java API: `ddprof-lib/src/main/java/com/datadoghq/profiler/ThreadContext.java`
