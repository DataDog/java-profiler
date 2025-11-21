# TLS Priming Architecture

## Overview

The TLS (Thread-Local Storage) Priming system ensures that thread-local profiling data structures are initialized before signal handlers access them. This prevents allocation and initialization from occurring within async-signal-unsafe contexts (signal handlers), eliminating potential deadlocks and crashes.

The system uses a dual-path initialization strategy combining JVMTI callbacks for Java threads and filesystem-based monitoring for native threads, with careful deduplication to prevent double-initialization overhead.

## Core Design Principles

1. **Signal Handler Safety**: Never allocate or initialize TLS within signal handlers
2. **Dual-Path Coverage**: JVMTI for Java threads, filesystem watching for native threads
3. **Deduplication**: Prevent wasteful double-initialization
4. **Lock-Free Buffer Management**: Use GCC atomic builtins instead of `std::atomic`
5. **Graceful Degradation**: Handle slot exhaustion without crashing
6. **Platform Specificity**: Linux gets full priming, macOS gets simplified approach

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

### 3. Dual-Path Initialization

The system uses two complementary initialization paths:

```
┌──────────────────────────────────────────────────────────────┐
│                   Thread Lifecycle                            │
├──────────────────────────────────────────────────────────────┤
│                                                               │
│  Java Thread Created                  Native Thread Created  │
│          │                                     │              │
│          ├─ JVMTI ThreadStart                │              │
│          │      │                              │              │
│          │      └─ initCurrentThread()        │              │
│          │              │                      │              │
│          │              │               ┌──────┘              │
│          │              │               │                     │
│          │              │        /proc/self/task watcher     │
│          │              │               │                     │
│          │              │       detects new thread           │
│          │              │               │                     │
│          │              │      sends RT signal               │
│          │              │               │                     │
│          │              │       simpleTlsSignalHandler()     │
│          │              │               │                     │
│          │              │      checks: VMThread::current()   │
│          │              │               │                     │
│          │              │        NULL? (native thread)       │
│          │              │               │                     │
│          │              │      initCurrentThreadWithBuffer() │
│          │              │               │                     │
│          └──────────────┴───────────────┘                     │
│                         │                                     │
│                 TLS Initialized                               │
│                         │                                     │
│           ProfiledThread* set via pthread_setspecific()      │
│                         │                                     │
│                Signal handlers safe                           │
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

#### Filesystem Watching with inotify

Monitors `/proc/self/task` for new threads:

```cpp
bool startThreadDirectoryWatcher(
    const std::function<void(int)>& on_new_thread,
    const std::function<void(int)>& on_dead_thread)
{
    int inotify_fd = inotify_init1(IN_CLOEXEC | IN_NONBLOCK);
    if (inotify_fd == -1) return false;

    int watch_fd = inotify_add_watch(inotify_fd, "/proc/self/task",
                                     IN_CREATE | IN_DELETE |
                                     IN_MOVED_FROM | IN_MOVED_TO);
    if (watch_fd == -1) {
        close(inotify_fd);
        return false;
    }

    // Create watcher thread
    pthread_create(&g_watcher_thread, nullptr, threadDirectoryWatcherLoop, nullptr);

    return true;
}
```

**Watcher Thread Loop:**

```cpp
void* threadDirectoryWatcherLoop(void* arg) {
    char buffer[4096];
    fd_set readfds;
    struct timeval timeout;

    while (g_watcher_running.load()) {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int ret = select(fd + 1, &readfds, nullptr, nullptr, &timeout);
        if (ret <= 0) continue;

        ssize_t len = read(fd, buffer, sizeof(buffer));

        // Parse inotify events
        for (ssize_t i = 0; i < len;) {
            struct inotify_event *event = (struct inotify_event *)(buffer + i);

            if (event->len > 0 && event->name[0] >= '1' && event->name[0] <= '9') {
                int tid = atoi(event->name);

                if (event->mask & (IN_CREATE | IN_MOVED_TO)) {
                    if (g_on_new_thread) g_on_new_thread(tid);
                } else if (event->mask & (IN_DELETE | IN_MOVED_FROM)) {
                    if (g_on_dead_thread) g_on_dead_thread(tid);
                }
            }

            i += sizeof(struct inotify_event) + event->len;
        }
    }

    return nullptr;
}
```

**New Thread Detection Flow:**

```
New Native Thread Started
         │
         ├─ /proc/self/task/{tid} directory created
         │
         ├─ inotify fires IN_CREATE event
         │
         ├─ Watcher thread parses event
         │
         ├─ Extracts TID from directory name
         │
         ├─ Sends RT signal to TID
         │
         ├─ simpleTlsSignalHandler() executes
         │
         ├─ Checks: VMThread::current() == nullptr?
         │
         └─ Yes → initCurrentThreadWithBuffer()
```

### 5. Signal Handler with Deduplication

The signal handler prevents double-initialization for Java threads:

```cpp
void simpleTlsSignalHandler(int signo) {
    // Only prime threads that are not Java threads
    // Java threads are handled by JVMTI ThreadStart events
    if (VMThread::current() == nullptr) {
        initCurrentThreadWithBuffer();
    }
}
```

**Deduplication Logic:**

```
Signal arrives on Java thread:
    │
    ├─ VMThread::current() → returns JavaThread*
    │
    └─ Handler does nothing (already initialized by JVMTI)

Signal arrives on native thread:
    │
    ├─ VMThread::current() → returns nullptr
    │
    └─ Handler calls initCurrentThreadWithBuffer()
```

**Additional Safety Check:**

```cpp
void initCurrentThreadWithBuffer() {
    // Early check - if already initialized, return immediately
    if (pthread_getspecific(_tls_key) != NULL) {
        return;
    }

    // ... claim slot and initialize ...
}
```

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
         ├─ Later: filesystem watcher detects thread (Linux only)
         │
         ├─ Sends RT signal to thread
         │
         ├─ simpleTlsSignalHandler() fires
         │
         ├─ VMThread::current() != nullptr (Java thread)
         │
         └─ Handler exits without action (already initialized)
```

**Key Distinction: Two Separate Initialization Strategies**

1. **JVMTI Path** (`initCurrentThread()`):
   - Used for: New Java threads created after profiler starts
   - Allocation: `ProfiledThread::forTid(tid)` → uses `new` operator
   - Not from buffer: Java threads get dedicated allocations
   - Safe context: Called from JVMTI callback (not signal handler)

2. **Signal Priming Path** (`initCurrentThreadWithBuffer()`):
   - Used for: Native threads and existing Java threads at startup
   - Allocation: Claims pre-allocated buffer slot
   - Signal-safe: No malloc, just atomic slot claim
   - Buffer reuse: Slots recycled when threads die

**Why Two Strategies?**

Java threads are managed via JVMTI callbacks (safe context), so they can use `new` operator. Native threads have no interception point, so they must use pre-allocated buffer slots claimed via async-signal-safe operations.

## Platform-Specific Behavior

### Linux (Full TLS Priming)

**Capabilities:**
- ✅ RT signal handler installation
- ✅ Thread enumeration via `/proc/self/task`
- ✅ Per-thread signaling via `tgkill()`
- ✅ Filesystem watching with inotify
- ✅ Thread count via `/proc/self/status`

**Implementation:**
```cpp
bool OS::isTlsPrimingAvailable() {
    return true; // Full support on Linux
}
```

### macOS (Limited TLS Priming)

**Limitations:**
- ❌ No RT signals (SIGRTMIN/SIGRTMAX unavailable)
- ❌ No `/proc` filesystem
- ❌ No inotify equivalent
- ✅ JVMTI ThreadStart still works for Java threads

**Implementation:**
```cpp
bool OS::isTlsPrimingAvailable() {
    return false; // Filesystem watching unavailable
}

// JVMTI still initializes Java threads
void initCurrentThread() {
    if (OS::isTlsPrimingAvailable()) {
        initCurrentThreadWithBuffer();  // Not called on macOS
    }
    // Java threads still work via JVMTI
}
```

**macOS Behavior:**
- Java threads: Initialized via JVMTI (works normally)
- Native threads: Lazy initialization on first signal (may allocate in handler)
- Acceptable tradeoff: macOS profiling is less critical for production

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

**Native Thread (Signal Path):**
- Signal delivery latency: ~1-10 μs
- Handler execution: ~100-200 cycles
- **Total: ~1-10 μs per thread**

### Watcher Thread Overhead

```
Idle State:
- select() with 1-second timeout
- ~0% CPU usage

Active State (new threads):
- inotify read + parse: ~1-5 μs per event
- Signal send: ~1-5 μs per thread
- **Total: ~2-10 μs per new thread**
```

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
    // 2. Initialize existing threads (if priming available)
    ProfiledThread::initExistingThreads();
}

// 3. Install signal handler and start watcher
void initExistingThreads() {
    // Install RT signal handler (Linux only)
    g_tls_prime_signal = OS::installTlsPrimeSignalHandler(
        simpleTlsSignalHandler, 4);

    // Prepare buffer
    prepareBuffer(256);

    // Start filesystem watcher (Linux only)
    OS::startThreadDirectoryWatcher(
        [](int tid) { OS::signalThread(tid, g_tls_prime_signal); },
        [](int tid) { /* thread death - no-op */ }
    );
}
```

### Shutdown Sequence

```cpp
void cleanupTlsPriming() {
    // 1. Stop watcher thread
    OS::stopThreadDirectoryWatcher();  // Joins watcher thread

    // 2. Uninstall signal handler
    OS::uninstallTlsPrimeSignalHandler(g_tls_prime_signal);

    // 3. Note: Don't clean buffer (threads may still be using it)
    //    Buffer cleaned up on process exit
}
```

## Testing Strategy

### Unit Tests

**Signal Handler Installation** (`test_tlsPriming.cpp:38-57`):
- Verifies RT signal allocation
- Checks signal number range (SIGRTMIN to SIGRTMAX)
- Platform-specific expectations

**Thread Enumeration** (`test_tlsPriming.cpp:59-74`):
- Enumerates current threads
- Validates TID values
- Ensures at least 1 thread found

**Signal Delivery** (`test_tlsPriming.cpp:84-123`):
- Installs handler
- Signals thread
- Verifies TLS modification
- Confirms signal delivery

**Filesystem Watcher** (`test_tlsPriming.cpp:125-162`):
- Starts watcher
- Creates short-lived thread
- Detects thread creation/destruction
- Validates cleanup

### Integration Tests

**ProfiledThread Tests:**
- Buffer allocation
- Slot reuse
- Concurrent initialization
- Thread isolation

## Key Architectural Benefits

1. **Crash Prevention**: Eliminates malloc() in signal handlers
2. **Deadlock Avoidance**: No locks in signal handler paths
3. **Platform Optimization**: Full support on Linux, graceful degradation on macOS
4. **Efficient Memory**: Small fixed overhead (33 KB)
5. **Scalability**: Lock-free operations scale with thread count
6. **Reliability**: Handles race conditions without corruption

## Future Enhancements

### Potential Improvements

1. **Dynamic Buffer Sizing**: Grow buffer if 256 slots exhausted
2. **macOS Native Support**: Explore kqueue for thread monitoring
3. **Metrics**: Track slot utilization and initialization latency
4. **Proactive Priming**: Prime threads during profiler start
5. **Buffer Compaction**: Defragment free slots periodically

### Known Limitations

1. **Fixed Buffer Size**: 256 slots may be insufficient for extreme workloads
2. **macOS Gap**: Native threads not pre-initialized
3. **Watcher Latency**: ~1-10 μs delay between thread start and priming
4. **Signal Exhaustion**: RT signals limited (typically 32 available)

This architecture provides a robust, platform-aware solution to the TLS initialization problem, ensuring signal handlers can safely access thread-local data without risk of deadlock or crash.
