# Event Type System

## Overview

The Datadog Java Profiler uses two distinct type systems for event identification:
- **`EventType`** enum (from upstream async-profiler)
- **`ASGCT_CallFrameType`** (BCI_* constants)

This document explains the relationship between these systems and how Datadog's implementation differs from upstream async-profiler.

## Type Definitions

### EventType Enum

Defined in `ddprof-lib/src/main/cpp/event.h`:

```cpp
enum EventType {
    PERF_SAMPLE,           // 0
    EXECUTION_SAMPLE,      // 1
    WALL_CLOCK_SAMPLE,     // 2
    MALLOC_SAMPLE,         // 3
    INSTRUMENTED_METHOD,   // 4
    METHOD_TRACE,          // 5
    ALLOC_SAMPLE,          // 6
    ALLOC_OUTSIDE_TLAB,    // 7
    LIVE_OBJECT,           // 8
    LOCK_SAMPLE,           // 9
    PARK_SAMPLE,           // 10
    PROFILING_WINDOW,      // 11
    USER_EVENT,            // 12
};
```

### ASGCT_CallFrameType (BCI_* Constants)

Defined in `ddprof-lib/src/main/cpp/vmEntry.h`:

```cpp
enum ASGCT_CallFrameType {
    BCI_CPU = 0,                  // cpu time
    BCI_WALL = -10,               // wall time
    BCI_NATIVE_FRAME = -11,       // native function name (char*)
    BCI_ALLOC = -12,              // name of the allocated class
    BCI_ALLOC_OUTSIDE_TLAB = -13, // name of the class allocated outside TLAB
    BCI_LIVENESS = -14,           // name of the allocated class
    BCI_LOCK = -15,               // class name of the locked object
    BCI_PARK = -16,               // class name of the park() blocker
    BCI_THREAD_ID = -17,          // method_id designates a thread
    BCI_ERROR = -18,              // method_id is an error string
};
```

## Upstream vs Datadog Implementation

### Upstream async-profiler

Uses `EventType` consistently throughout:

- **Function signature** (cpp/profiler.h:213):
  ```cpp
  u64 recordSample(void* ucontext, u64 counter, EventType event_type, Event* event);
  ```

- **Event-to-frame-type conversion** when building call traces:
  ```cpp
  // Convert EventType to BCI_* frame type
  jint frame_type = BCI_ALLOC - (event_type - ALLOC_SAMPLE);
  ```

- **Type-safe comparisons**:
  ```cpp
  if (event_type <= MALLOC_SAMPLE) { ... }
  if (event_type >= ALLOC_SAMPLE && event_type <= ALLOC_OUTSIDE_TLAB) { ... }
  ```

### Datadog Implementation

Uses BCI_* values directly as event identifiers:

- **Modified function signature** (ddprof-lib/src/main/cpp/profiler.h:247-248):
  ```cpp
  void recordSample(void *ucontext, u64 weight, int tid, jint event_type,
                    u64 call_trace_id, Event *event);
  ```

- **Direct BCI_* comparisons**:
  ```cpp
  if (event_type == BCI_CPU && _cpu_engine == &perf_events) { ... }
  if (event_type == BCI_CPU || event_type == BCI_WALL) { ... }
  ```

- **Call sites pass BCI_* values**:
  ```cpp
  Profiler::instance()->recordSample(ucontext, _interval, tid, BCI_CPU, 0, &event);
  Profiler::instance()->recordSample(ucontext, last_sample, tid, BCI_WALL, call_trace_id, &event);
  ```

## Type Conversion

### The Problem

Datadog's `StackWalker::walkVM()` (inherited from upstream) expects `EventType` but receives BCI_* values. Previously, this used an unsafe cast:

```cpp
// Old approach - undefined behavior for negative BCI_* values
static_cast<EventType>(event_type)
```

This cast is technically undefined behavior because:
- BCI_WALL = -10 is not a valid EventType enum value (0-12)
- Casting negative integers to enums with only positive values is undefined in C++
- It worked by accident because numeric comparisons still functioned

### The Solution

A conversion function maps BCI_* values to appropriate EventType values:

```cpp
inline EventType eventTypeFromBCI(jint bci_type) {
    switch (bci_type) {
        case BCI_CPU:                return EXECUTION_SAMPLE;
        case BCI_WALL:               return WALL_CLOCK_SAMPLE;
        case BCI_ALLOC:              return ALLOC_SAMPLE;
        case BCI_ALLOC_OUTSIDE_TLAB: return ALLOC_OUTSIDE_TLAB;
        case BCI_LIVENESS:           return LIVE_OBJECT;
        case BCI_LOCK:               return LOCK_SAMPLE;
        case BCI_PARK:               return PARK_SAMPLE;
        default:                     return EXECUTION_SAMPLE;
    }
}
```

Usage in profiler.cpp:

```cpp
num_frames += ddprof::StackWalker::walkVM(ucontext, frames + num_frames,
                                          max_remaining, _features,
                                          eventTypeFromBCI(event_type), &truncated);
```

## Type Mapping

| BCI_* Constant | Value | EventType | Value | Notes |
|----------------|-------|-----------|-------|-------|
| BCI_CPU | 0 | EXECUTION_SAMPLE | 1 | CPU samples (perf/itimer) |
| BCI_WALL | -10 | WALL_CLOCK_SAMPLE | 2 | Wall clock samples |
| BCI_ALLOC | -12 | ALLOC_SAMPLE | 6 | TLAB allocations |
| BCI_ALLOC_OUTSIDE_TLAB | -13 | ALLOC_OUTSIDE_TLAB | 7 | Non-TLAB allocations |
| BCI_LIVENESS | -14 | LIVE_OBJECT | 8 | Live heap objects |
| BCI_LOCK | -15 | LOCK_SAMPLE | 9 | Monitor contention |
| BCI_PARK | -16 | PARK_SAMPLE | 10 | Thread park events |

## Key Files

### Type Definitions
- `ddprof-lib/src/main/cpp/event.h` - EventType enum
- `ddprof-lib/src/main/cpp/vmEntry.h` - ASGCT_CallFrameType (BCI_* constants)

### Conversion Function
- `ddprof-lib/src/main/cpp/profiler.h:61-96` - eventTypeFromBCI() implementation

### Usage Sites
- `ddprof-lib/src/main/cpp/profiler.cpp:716,719` - StackWalker::walkVM() calls
- `ddprof-lib/src/main/cpp/profiler.cpp:690,717` - BCI_* comparisons
- `ddprof-lib/src/main/cpp/flightRecorder.cpp:1620-1642` - Event recording switch

### Call Sites (BCI_* sources)
- `ddprof-lib/src/main/cpp/itimer.cpp:55` - BCI_CPU
- `ddprof-lib/src/main/cpp/ctimer_linux.cpp:171` - BCI_CPU
- `ddprof-lib/src/main/cpp/perfEvents_linux.cpp:749` - BCI_CPU
- `ddprof-lib/src/main/cpp/wallClock.cpp:105` - BCI_WALL

## Why Two Type Systems?

### Historical Context

1. **Upstream design**: async-profiler uses EventType for event categorization and converts to BCI_* frame types only when building call traces.

2. **Datadog divergence**: Datadog's fork uses BCI_* values as the primary event identifiers throughout the codebase.

### Rationale

Using BCI_* values directly has advantages:
- **Frame type alignment**: BCI_* values are already frame types, eliminating conversion steps
- **Semantic clarity**: BCI_CPU, BCI_WALL are more descriptive than numeric EventType values
- **Simpler call sites**: Event sources directly specify the frame type they produce

However, it creates the conversion requirement when calling upstream code that expects EventType.

## Best Practices

### When Adding New Event Types

1. **Choose the identifier**: Use BCI_* constant for the event type identifier
2. **Update conversion function**: Add mapping in eventTypeFromBCI()
3. **Update FlightRecorder**: Add case to recordEvent() switch statement
4. **Add call sites**: Pass BCI_* value to recordSample()

### Code Review Checklist

- [ ] All event_type comparisons use symbolic names (BCI_CPU, not 0)
- [ ] No raw static_cast<EventType> on event_type parameters
- [ ] New BCI_* values have eventTypeFromBCI() mappings
- [ ] FlightRecorder::recordEvent() handles the new event type
- [ ] Call sites pass correct BCI_* constant

## Future Considerations

### Option 1: Align with Upstream
Convert back to using EventType throughout Datadog's code:
- **Pros**: Type safety, upstream compatibility
- **Cons**: Large refactoring, frame type conversion overhead

### Option 2: Maintain Current Design
Keep using BCI_* with conversion function:
- **Pros**: Minimal changes, semantically clear
- **Cons**: Type system mismatch persists

### Option 3: Diverge Further
Fork StackWalker to accept BCI_* directly:
- **Pros**: Eliminates conversion, full type consistency
- **Cons**: Maintenance burden, harder to merge upstream changes

## Conclusion

The eventTypeFromBCI() conversion function provides a clean bridge between Datadog's BCI_*-based event identification and upstream's EventType-based stack walking logic. This approach:

- Eliminates undefined behavior from raw casts
- Documents the intentional type system divergence
- Maintains compatibility with upstream StackWalker code
- Preserves the semantic benefits of BCI_* identifiers

When working with event types, always use the conversion function when calling code that expects EventType, and use BCI_* constants directly in Datadog-specific code.
