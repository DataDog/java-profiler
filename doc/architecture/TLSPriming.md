# TLS Priming Architecture

## Overview

The TLS (Thread-Local Storage) Priming system ensures that thread-local profiling data structures are initialized before signal handlers access them. This prevents allocation and initialization from occurring within async-signal-unsafe contexts (signal handlers), eliminating potential deadlocks and crashes.

The system uses JVMTI callbacks for Java threads to initialize thread-local storage. Native threads will be initialized through future lib patching mechanisms (the previous filesystem-based monitoring approach has been removed due to performance concerns).

## Core Design Principles

1. **Signal Handler Safety**: Never allocate or initialize TLS within signal handlers
2. **JVMTI-Based Initialization**: Java threads initialized via JVMTI callbacks
3. **Lock-Free Buffer Management**: Use GCC atomic builtins instead of `std::atomic`
4. **Graceful Degradation**: Handle slot exhaustion without crashing
5. **Platform Specificity**: TLS priming supported on Linux, simplified approach on macOS

## Problem Statement

### The TLS Initialization Race

Profiling signal handlers (SIGPROF, SIGALRM) fire asynchronously and need to access thread-local data:

```
Thread Timeline:
──────────────────────────────────────────────────────────────────
Thread Start
    │
    ├─ SIGPROF arrives ← Signal handler fires
    │      │
    │      └─ Needs ProfiledThread* → TLS not initialized!
    │            │
    │            └─ malloc() in signal handler → DEADLOCK or CRASH
    │
    └─ Normal TLS initialization (too late)
```

**Without TLS Priming:**
- Signal arrives before TLS init
- Handler calls `pthread_getspecific()` → returns NULL
- Attempts lazy allocation → calls malloc()
- **CRASH**: malloc is not async-signal-safe

**With TLS Priming:**
- TLS initialized before profiling starts
- Signal arrives → TLS already exists
- Handler accesses existing data → safe

## Architecture Components

### 1. Buffer-Based TLS Management

The system uses a pre-allocated array of `ProfiledThread` objects shared across all threads:

```
┌────────────────────────────────────────────────────────────┐
│              ProfiledThread Buffer (256 slots)             │
├────────────────────────────────────────────────────────────┤
│ Slot 0: ProfiledThread                                     │
│ Slot 1: ProfiledThread ← Thread A's TLS points here       │
│ Slot 2: ProfiledThread                                     │
│ Slot 3: ProfiledThread ← Thread B's TLS points here       │
│   ...                                                       │
│ Slot 255: ProfiledThread                                   │
└────────────────────────────────────────────────────────────┘
         ↑                    ↑
         │                    │
    Thread A TLS          Thread B TLS
   (pthread_key)        (pthread_key)
```

**Key Design Decisions:**

- **Pre-allocation**: All `ProfiledThread` objects allocated during profiler startup
- **Slot Reuse**: Free slot stack enables efficient slot recycling when threads die
- **No Signal Allocation**: Signal handlers only claim existing slots, never allocate
- **Bounded Size**: 256 slots handles typical production workloads

### 2. Lock-Free Slot Management

Uses GCC atomic builtins (not `std::atomic`) for async-signal-safety:

```cpp
// Static storage (NOT std::atomic - signal-safe requirement)
static volatile int _running_buffer_pos = 0;   // Next slot to allocate
static volatile int _free_stack_top = -1;      // Top of free slot stack
static int* _free_slots = nullptr;             // Stack of recycled slots

// Slot allocation (can be called from signal handler)
int pos = -1;

// Try to reuse freed slot first
pos = popFreeSlot();  // Lock-free CAS-based pop

if (pos == -1) {
    // No free slots, allocate new one
    pos = __atomic_fetch_add(&_running_buffer_pos, 1, __ATOMIC_RELAXED);
}
```

**Lock-Free Stack Operations:**

```cpp
int popFreeSlot() {
    int current_top, new_top;
    do {
        current_top = __atomic_load_n(&_free_stack_top, __ATOMIC_ACQUIRE);
        if (current_top == -1) return -1; // Stack empty

        new_top = _free_slots[current_top];
    } while (!__atomic_compare_exchange_n(&_free_stack_top, &current_top, new_top,
                                          true, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE));
    return current_top;
}

void pushFreeSlot(int slot_index) {
    int current_top;
    do {
        current_top = __atomic_load_n(&_free_stack_top, __ATOMIC_ACQUIRE);
        _free_slots[slot_index] = current_top;
    } while (!__atomic_compare_exchange_n(&_free_stack_top, &current_top, slot_index,
                                          true, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE));
}
```

**Why GCC Builtins Instead of `std::atomic`:**

1. `std::atomic` is **not guaranteed async-signal-safe** (may use mutexes)
2. GCC `__atomic_*` builtins are **guaranteed lock-free** for aligned types
3. Signal handlers require strict async-signal-safety guarantees

### 3. JVMTI-Based Initialization

The system initializes Java threads via JVMTI callbacks:

```
┌──────────────────────────────────────────────────────────────┐
│                   Thread Lifecycle                            │
├──────────────────────────────────────────────────────────────┤
│                                                               │
│  Java Thread Created                                          │
│          │                                                     │
│          ├─ JVMTI ThreadStart                                │
│          │      │                                             │
│          │      └─ initCurrentThread()                       │
│          │              │                                     │
│          │              └─ TLS Initialized                   │
│          │                                                     │
│          │           ProfiledThread* set via                 │
│          │           pthread_setspecific()                   │
│          │                                                     │
│          └─ Signal handlers safe                             │
│                                                               │
│  Note: Native threads currently use lazy initialization       │
│        Future lib patching will address native thread         │
│        initialization before signal handlers access TLS      │
│                                                               │
└──────────────────────────────────────────────────────────────┘
```

### 4. Linux-Specific Implementation

#### RT Signal Handler Installation

Linux uses real-time signals for TLS priming:

```cpp
int installTlsPrimeSignalHandler(SigHandler handler, int signal_offset) {
    int signal_num = SIGRTMIN + signal_offset;

    if (signal_num > SIGRTMAX) {
        return -1; // No available RT signal
    }

    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(signal_num, &sa, NULL) != 0) {
        return -1; // Installation failed
    }

    return signal_num;
}
```

**RT Signal Benefits:**
- Queued delivery (won't lose signals)
- Multiple available (SIGRTMIN to SIGRTMAX)
- Separate from profiling signals (SIGPROF, SIGALRM)

**Note:** The filesystem-based thread monitoring with inotify has been removed due to performance concerns. Future implementations will use lib patching for native thread TLS initialization.

### 5. Signal Handler Implementation

The signal handler infrastructure remains in place for potential future use:

```cpp
void simpleTlsSignalHandler(int signo) {
    // Only prime threads that are not Java threads
    // Java threads are handled by JVMTI ThreadStart events
    if (VMThread::current() == nullptr) {
        initCurrentThreadWithBuffer();
    }
}
```

**Note:** With the removal of filesystem-based thread monitoring, this signal handler is currently not actively used. It remains available for future lib patching implementations that may signal threads explicitly.

### 6. JVMTI Integration

Java threads get initialized via JVMTI callback:

```cpp
void Profiler::onThreadStart(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread) {
    ProfiledThread::initCurrentThread();
    ProfiledThread *current = ProfiledThread::current();

    // Register with profiling engines
    _cpu_engine->registerThread(current->tid());
    _wall_engine->registerThread(current->tid());
}
```

**JVMTI Lifecycle:**

```
JVMTI ThreadStart fires
         │
         ├─ Executes INSIDE new Java thread
         │
         ├─ initCurrentThread()
         │      │
         │      ├─ Allocates NEW ProfiledThread via forTid(tid)
         │      │    │
         │      │    └─ Uses 'new' operator (NOT from buffer)
         │      │
         │      ├─ Sets pthread_setspecific(_tls_key, new_instance)
         │      │
         │      └─ TLS now initialized with dedicated allocation
         │
         └─ Thread ready for profiling
```

**Key Characteristics:**

1. **JVMTI Path** (`initCurrentThread()`):
   - Used for: New Java threads created after profiler starts
   - Allocation: `ProfiledThread::forTid(tid)` → uses `new` operator
   - Not from buffer: Java threads get dedicated allocations
   - Safe context: Called from JVMTI callback (not signal handler)

2. **Native Threads:**
   - Currently use lazy initialization (may allocate in signal handler)
   - Future lib patching will enable pre-initialization of native threads
   - Buffer-based priming infrastructure remains available for future use

## Platform-Specific Behavior

### Linux (TLS Priming)

**Capabilities:**
- ✅ RT signal handler installation
- ✅ Thread enumeration via `/proc/self/task`
- ✅ Per-thread signaling via `tgkill()`
- ✅ Thread count via `/proc/self/status`
- ✅ JVMTI ThreadStart for Java threads

**Implementation:**
```cpp
bool OS::isTlsPrimingAvailable() {
    return true; // TLS priming supported on Linux
}
```

**Current Behavior:**
- Java threads: Fully initialized via JVMTI callbacks
- Native threads: Use lazy initialization (awaiting lib patching implementation)

### macOS (Limited TLS Priming)

**Limitations:**
- ❌ No RT signals (SIGRTMIN/SIGRTMAX unavailable)
- ❌ No `/proc` filesystem
- ✅ JVMTI ThreadStart still works for Java threads

**Implementation:**
```cpp
bool OS::isTlsPrimingAvailable() {
    return false; // TLS priming not available on macOS
}
```

**macOS Behavior:**
- Java threads: Initialized via JVMTI (works normally)
- Native threads: Lazy initialization on first signal (may allocate in handler)
- Acceptable tradeoff: macOS profiling is primarily for development

## Performance Characteristics

### Memory Overhead

```
Buffer Size: 256 slots
Per-Slot: sizeof(ProfiledThread) ≈ 128 bytes
Total: 256 * 128 = 32 KB

Free Slot Stack: 256 * sizeof(int) = 1 KB

Total Memory: ~33 KB (negligible)
```

### Initialization Cost

**Java Thread (JVMTI Path):**
- 1 atomic fetch-add or CAS-based pop
- 1 pthread_setspecific call
- **Total: ~100-200 CPU cycles**

**Native Thread:**
- Currently uses lazy initialization
- Future lib patching will provide pre-initialization with minimal overhead

## Signal Safety Guarantees

### Async-Signal-Safe Operations

The TLS priming system only uses operations guaranteed async-signal-safe:

```cpp
// ✅ SAFE in signal handlers:
__atomic_fetch_add()           // GCC builtin, lock-free
__atomic_load_n()              // GCC builtin, lock-free
__atomic_compare_exchange_n()  // GCC builtin, lock-free
pthread_getspecific()          // POSIX async-signal-safe
OS::threadId()                 // Cached, no syscall
VMThread::current()            // TLS read, signal-safe

// ❌ UNSAFE in signal handlers (avoided):
malloc()                       // Not signal-safe
pthread_mutex_lock()           // Not signal-safe
std::atomic<>::load()          // May use mutexes (not guaranteed)
```

### Race Condition Handling

**Double-Initialization Race:**

```
Thread A: JVMTI ThreadStart          Thread B: Watcher detects thread
    │                                         │
    ├─ Claims slot 42                        │
    │                                         │
    ├─ pthread_setspecific()                 ├─ Sends signal
    │                                         │
    │                                    Signal arrives
    │                                         │
    │                                         ├─ pthread_getspecific()
    │                                         │
    │                                         └─ Returns != NULL
    │                                              │
    │                                              └─ Early return (no-op)
```

**Result:** Wasted signal but no corruption. Slot remains correctly assigned.

**Concurrent Slot Claims:**

```
Thread A (Java, JVMTI)          Thread B (Native, Signal)
    │                                   │
    ├─ popFreeSlot()                    ├─ popFreeSlot()
    │      │                            │      │
    │      └─ CAS on _free_stack_top    │      └─ CAS on _free_stack_top
    │              │                    │              │
    │              └─ One succeeds      └──────────────┘
    │                                                 │
    │                                                 └─ Other retries or allocates new
```

**Result:** Lock-free CAS ensures only one thread claims each slot.

## Lifecycle Management

### Startup Sequence

```cpp
// 1. Profiler initialization
Profiler::start() {
    // 2. Initialize TLS infrastructure (if priming available)
    ProfiledThread::initExistingThreads();
}

// 3. Install signal handler and prepare buffer
void initExistingThreads() {
    // Install RT signal handler (Linux only)
    g_tls_prime_signal = OS::installTlsPrimeSignalHandler(
        simpleTlsSignalHandler, 4);

    // Prepare buffer for future use
    prepareBuffer(256);
}
```

### Shutdown Sequence

```cpp
void cleanupTlsPriming() {
    // 1. Uninstall signal handler
    OS::uninstallTlsPrimeSignalHandler(g_tls_prime_signal);

    // 2. Note: Don't clean buffer (threads may still be using it)
    //    Buffer cleaned up on process exit
}
```

## Testing Strategy

### Unit Tests

**Signal Handler Installation** (`test_tlsPriming.cpp`):
- Verifies RT signal allocation
- Checks signal number range (SIGRTMIN to SIGRTMAX)
- Platform-specific expectations

**Thread Enumeration** (`test_tlsPriming.cpp`):
- Enumerates current threads
- Validates TID values
- Ensures at least 1 thread found

**Signal Delivery** (`test_tlsPriming.cpp`):
- Installs handler
- Signals thread
- Verifies TLS modification
- Confirms signal delivery

### Integration Tests

**ProfiledThread Tests:**
- Buffer allocation
- Slot reuse
- Concurrent initialization
- Thread isolation
- JVMTI vs buffer-based initialization

## Key Architectural Benefits

1. **Crash Prevention**: Eliminates malloc() in signal handlers for Java threads
2. **Deadlock Avoidance**: No locks in signal handler paths
3. **Platform Optimization**: JVMTI-based initialization on both Linux and macOS
4. **Efficient Memory**: Small fixed overhead (33 KB)
5. **Scalability**: Lock-free operations scale with thread count
6. **Reliability**: Handles race conditions without corruption

## Future Enhancements

### Planned Improvements

1. **Lib Patching for Native Threads**: Replace filesystem monitoring with library patching to pre-initialize native threads
2. **Dynamic Buffer Sizing**: Grow buffer if 256 slots exhausted
3. **Metrics**: Track slot utilization and initialization latency
4. **Buffer Compaction**: Defragment free slots periodically

### Known Limitations

1. **Native Thread Gap**: Native threads currently use lazy initialization (awaiting lib patching)
2. **Fixed Buffer Size**: 256 slots may be insufficient for extreme workloads (unlikely for native threads)
3. **macOS Gap**: Native threads not pre-initialized
4. **Signal Exhaustion**: RT signals limited (typically 32 available, unlikely to happen)

### Recent Changes

**Removed Filesystem Monitoring (2025):**
- Filesystem-based thread monitoring via inotify has been removed due to performance concerns
- The thread directory watcher caused overhead in production environments
- Future implementations will use lib patching instead for native thread initialization

This architecture provides a robust, platform-aware solution to the TLS initialization problem for Java threads, ensuring signal handlers can safely access thread-local data without risk of deadlock or crash. Native thread support will be enhanced through future lib patching implementations.
