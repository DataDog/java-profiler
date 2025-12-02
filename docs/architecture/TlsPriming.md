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

## Configuration

TLS priming for native threads can be controlled via environment variable or JVM system property:

| Setting | Values | Default | Description |
|---------|--------|---------|-------------|
| `DD_PROFILER_TLS_WATCHER` | `0`, `1` | `1` (enabled) | Controls the filesystem watcher for native thread TLS priming |

**Environment Variable:**
```bash
# Disable native thread TLS priming (Java threads still primed via JVMTI)
export DD_PROFILER_TLS_WATCHER=0

# Enable native thread TLS priming (default)
export DD_PROFILER_TLS_WATCHER=1
```

**JVM System Property** (useful for JMH forked JVMs):
```bash
java -DDD_PROFILER_TLS_WATCHER=0 ...
```

**When to Disable:**
- Throughput-sensitive benchmarks where the per-thread overhead of the watcher matters
- Environments where only Java threads need profiling (no native threads of interest)

**Note:** Disabling the watcher only affects native threads created after profiling starts. Java threads are always primed via JVMTI callbacks regardless of this setting.

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

### 4. Java Thread Tracking and Filtering

To prevent wasteful signal sending to Java threads (which are already initialized via JVMTI), the system uses a lock-free atomic bitset to track Java thread IDs.

#### Lock-Free Bitset Design with Double-Hashing

The bitset uses a reusable `LockFreeBitset` template class from `lockFree.h` that implements double-hashing to minimize false positives:

```cpp
// Cache-line padded atomic words to prevent false sharing
constexpr size_t CACHE_LINE_SIZE = 64;

template<typename T>
struct alignas(CACHE_LINE_SIZE) PaddedAtomic {
  std::atomic<T> value;
  // Padding is automatic due to alignas - ensures 64-byte alignment
};

// LockFreeBitset with double-hashing for minimal false positives
// Interleaved layout: [word1_0, word2_0, word1_1, word2_1, ...] for L1 cache locality
template<size_t NumBits>
class LockFreeBitset {
  // Single contiguous interleaved array - for <=16384 bits it fits entirely in L1 cache (32 KB)
  PaddedAtomic<uint64_t> _words[NUM_WORDS * 2];
  // ...
};

// Java thread tracking bitset
constexpr size_t JAVA_THREAD_BITSET_SIZE = 16384;
static LockFreeBitset<JAVA_THREAD_BITSET_SIZE> _java_thread_bitset;
```

**Double-Hashing Strategy:**

The bitset uses two independent hash functions. A key is considered "set" only if BOTH corresponding bits are set:

```cpp
// Hash 1: Knuth multiplicative hash (uses lower bits via modulo)
static size_t hashKey1(size_t key) {
  return (key * KNUTH_MULTIPLICATIVE_CONSTANT) % NumBits;
}

// Hash 2: Different constant with upper bits extraction for independence
static size_t hashKey2(size_t key) {
  size_t product = key * HASH2_CONSTANT;
  return (product >> 32) % NumBits;  // Upper bits for independence
}

bool test(size_t key) const {
  return testInArray(_words1, hashKey1(key)) && testInArray(_words2, hashKey2(key));
}
```

**Key Design Features:**

1. **Double-Hashing**: Two independent hash functions reduce false positive probability from p to p²
2. **Knuth Multiplicative Hashing**: Primary hash uses `0x9e3779b97f4a7c15ULL` for excellent distribution
3. **Upper Bits Extraction**: Secondary hash uses upper 32 bits for true independence from primary
4. **False Positive Minimization**: With M threads, P(false positive) ≈ (M/16384)²
   - 100 threads → 0.003%
   - 500 threads → 0.09%
   - 1000 threads → 0.37%
5. **Cache-Line Padding**: Each atomic word on separate cache line prevents false sharing
6. **Memory Overhead**: 32 KB (256 words × 2 arrays × 64 bytes/cache-line, fits in L1 cache)
7. **Interleaved Layout**: Arrays stored as [word1_0, word2_0, word1_1, word2_1, ...] for cache locality
8. **Lock-Free Operations**: All operations use atomic fetch_or/fetch_and for thread safety
9. **Reusable Design**: `LockFreeBitset` is a generic template in `lockFree.h`

#### Registration and Lookup

The `LockFreeBitset` class provides a simple API that handles the double-hashing internally:

```cpp
void ProfiledThread::registerJavaThread(int tid) {
  // Sets bits in both arrays using both hash functions
  _java_thread_bitset.set(static_cast<size_t>(tid));
}

bool ProfiledThread::isLikelyJavaThread(int tid) {
  // Returns true only if BOTH bits (from both hash functions) are set
  return _java_thread_bitset.test(static_cast<size_t>(tid));
}

void ProfiledThread::unregisterJavaThread(int tid) {
  // Clears bits in both arrays using both hash functions
  _java_thread_bitset.clear(static_cast<size_t>(tid));
}
```

**Internal Implementation (in LockFreeBitset):**

```cpp
void set(size_t key) {
  setInArray(_words1, hashKey1(key));  // Set bit in first array
  setInArray(_words2, hashKey2(key));  // Set bit in second array
}

bool test(size_t key) const {
  // Both bits must be set for a positive result
  return testInArray(_words1, hashKey1(key)) && testInArray(_words2, hashKey2(key));
}

void clear(size_t key) {
  clearInArray(_words1, hashKey1(key));  // Clear bit in first array
  clearInArray(_words2, hashKey2(key));  // Clear bit in second array
}
```

#### Memory Ordering Guarantees

- **`memory_order_release` on writes**: Ensures all writes before registration are visible to readers
- **`memory_order_acquire` on reads**: Ensures visibility of writes that happened before registration
- **Race Condition Handling**: 20ms delay in watcher between inotify event and bitset check eliminates most races

#### Integration with Thread Watcher

```cpp
// In watcher loop (os_linux_dd.cpp:298-310)
if (event->mask & (IN_CREATE | IN_MOVED_TO)) {
  // Small delay (20ms) to allow JVMTI ThreadStart callback to register Java threads
  // This virtually eliminates the race condition between thread creation and JVMTI callback
  struct timespec delay = {0, 20000000}; // 20ms
  nanosleep(&delay, nullptr);

  // Skip sending signal to likely Java threads
  if (!ProfiledThread::isLikelyJavaThread(tid) && g_on_new_thread) {
    g_on_new_thread(tid);
  }
} else if (event->mask & (IN_DELETE | IN_MOVED_FROM)) {
  if (g_on_dead_thread) g_on_dead_thread(tid);
}
```

**Performance Impact:**

- **Before Optimization**: All threads receive TLS priming signal (Java + native)
- **After Optimization**: Only native threads receive signal (typical: 1-5% of threads)
- **Overhead Reduction**: ~95% fewer signal sends for typical Java workloads
- **Memory Cost**: 32 KB (fits in L1 cache, acceptable for 95% performance win)

**Trade-offs:**

- **False Positives**: Double-hashing minimizes false positives to ~0.003-0.37% depending on thread count
- **Memory**: 32 KB overhead (fits entirely in L1 cache)
- **Complexity**: Reusable `LockFreeBitset` class encapsulates double-hashing logic

**Important Context on False Positives:**

Even with the small probability of false positives, this system represents a significant improvement over the previous state. Before TLS priming was implemented, native threads created after profiling started were **completely invisible** to the profiler—they could not be sampled at all because their TLS was never initialized.

With the current implementation:
- The vast majority of native threads (99.6-99.997%) are correctly primed and profiled
- Only a tiny fraction might be skipped due to false positives in the Java thread filter
- This is dramatically better than 100% of late-created native threads being invisible

The false positive rate is a minor imperfection in an otherwise complete solution to native thread visibility.

### 5. Linux-Specific Implementation

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

### 5. Signal Handler with Java Thread Filtering

The signal handler and watcher use both a bitset filter and VMThread check to prevent unnecessary signal delivery and double-initialization:

**Two-Layer Filtering:**

1. **Watcher-Level Filter** (os_linux_dd.cpp):
```cpp
// In watcher loop - filter BEFORE sending signal
if (event->mask & (IN_CREATE | IN_MOVED_TO)) {
  struct timespec delay = {0, 20000000}; // 20ms delay
  nanosleep(&delay, nullptr);

  // Skip sending signal to likely Java threads
  if (!ProfiledThread::isLikelyJavaThread(tid) && g_on_new_thread) {
    g_on_new_thread(tid);  // Only signal if NOT Java thread
  }
}
```

2. **Handler-Level Check** (thread.cpp):
```cpp
void simpleTlsSignalHandler(int signo) {
    // Quick check: if TLS already set, return immediately
    if (pthread_getspecific(_tls_key) != nullptr) {
        return;
    }

    // Only prime threads that are not Java threads
    // Java threads are handled by JVMTI ThreadStart events
    if (VMThread::current() == nullptr) {
        initCurrentThreadWithBuffer();
    }
}
```

**Filtering Flow:**

```
New Thread Created
    │
    ├─ inotify detects /proc/self/task/{tid}
    │
    ├─ Watcher waits 20ms (JVMTI registration time)
    │
    ├─ Check: ProfiledThread::isLikelyJavaThread(tid)?
    │      │
    │      ├─ YES → Skip signal (optimization)
    │      │
    │      └─ NO  → Send RT signal
    │              │
    │              ├─ Signal arrives
    │              │
    │              ├─ Check: pthread_getspecific() != NULL?
    │              │      │
    │              │      ├─ YES → Early return (already initialized)
    │              │      │
    │              │      └─ NO  → Check VMThread::current()
    │              │              │
    │              │              ├─ NULL → Native thread
    │              │              │      │
    │              │              │      └─ initCurrentThreadWithBuffer()
    │              │              │
    │              │              └─ NOT NULL → Java thread
    │              │                     │
    │              │                     └─ Do nothing
    │              │
    │              └─ TLS initialized (if needed)
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

Java threads get initialized via JVMTI callback and registered in the bitset:

```cpp
void Profiler::onThreadStart(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread) {
    // Initialize TLS and register as Java thread
    ProfiledThread::initCurrentThread();
    ProfiledThread *current = ProfiledThread::getOrCreate();

    // Register with profiling engines
    _cpu_engine->registerThread(current->tid());
    _wall_engine->registerThread(current->tid());
}

// Inside ProfiledThread::initCurrentThread() (thread.cpp:67-83):
void ProfiledThread::initCurrentThread() {
    initTLSKey();

    if (pthread_getspecific(_tls_key) != NULL) {
        return; // Already initialized
    }

    int tid = OS::threadId();
    ProfiledThread *tls = ProfiledThread::forTid(tid);
    pthread_setspecific(_tls_key, (const void *)tls);

    // Register this thread as a Java thread for TLS priming optimization
    ProfiledThread::registerJavaThread(tid);
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
         │      ├─ Registers TID in bitset: registerJavaThread(tid)
         │      │
         │      └─ TLS now initialized with dedicated allocation
         │
         ├─ Later: filesystem watcher detects thread (Linux only)
         │
         ├─ Watcher waits 20ms
         │
         ├─ Checks: isLikelyJavaThread(tid)?
         │      │
         │      └─ YES → Bitset returns true (registered above)
         │              │
         │              └─ Skip signal send (optimization)
         │
         └─ No signal sent, no handler invocation needed
```

**Key Distinction: Two Separate Initialization Strategies**

1. **JVMTI/pthread hook Path** (`init via current()`):
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

Java threads are managed via JVMTI/pthread hook callbacks (safe context), so they can use `new` operator. Native threads have no interception point, so they must use pre-allocated buffer slots claimed via async-signal-safe operations.

## Platform-Specific Behavior

### Linux (Full TLS Priming)

**Capabilities:**
- ✅ RT signal handler installation
- ✅ Thread enumeration via `/proc/self/task`
- ✅ Per-thread signaling via `tgkill()`
- ✅ Filesystem watching with inotify
- ✅ Thread count via `/proc/self/status`

### macOS (Limited TLS Priming)

**Limitations:**
- ❌ No RT signals (SIGRTMIN/SIGRTMAX unavailable)
- ❌ No `/proc` filesystem
- ❌ No inotify equivalent
- ✅ JVMTI ThreadStart still works for Java threads

## Performance Characteristics

### Memory Overhead

```
Buffer Size: 256 slots
Per-Slot: sizeof(ProfiledThread) ≈ 128 bytes
Total: 256 * 128 = 32 KB

Free Slot Stack: 256 * sizeof(int) = 1 KB

Java Thread Bitset (Double-Hashed LockFreeBitset):
- 16384 bits per array → 256 words per array (16384 / 64 bits per word)
- 2 arrays (double-hashing) → 512 total words
- Interleaved layout: [word1_0, word2_0, word1_1, word2_1, ...] for L1 cache locality
- Cache-line padding: 512 words × 64 bytes = 32 KB
Total Bitset: 32 KB (fits entirely in L1 cache)

Total Memory: ~65 KB (buffer + free stack + bitset)
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

**LockFreeBitset Tests** (`test_lockFreeBitset.cpp`):
- **BasicSetAndTest**: Set/test single key
- **ClearOperation**: Verify clear removes key
- **RawBitOperations**: Test direct bit manipulation without hashing
- **MultipleKeys**: Set multiple keys, verify all marked
- **ClearAll**: Verify clearAll resets entire bitset
- **Idempotency**: Multiple set/clear calls
- **EdgeCases**: Test key 0, large keys, word boundaries
- **ConcurrentAccess**: 8 threads setting 100 keys each (lock-free correctness)
- **MemoryOrdering**: Writer/reader threads verify acquire/release semantics
- **ReducedFalsePositives**: Verify double-hashing reduces false positives compared to single hash
- **MultipleKeysIntegrity**: Verify partial clear doesn't affect other keys

**Java Thread Bitset Tests** (`test_javaThreadBitset.cpp`):
- **BasicRegistrationAndLookup**: Register/unregister single TID
- **Unregistration**: Verify unregister clears bit
- **MultipleThreads**: Register 5 TIDs, verify all marked
- **KnuthHashDistribution**: Verify basic Knuth hashing registration/unregistration
- **RealisticThreadIds**: Test 50 sequential TIDs with Knuth distribution
- **ConcurrentAccess**: 10 threads registering 100 TIDs each (lock-free correctness)
- **EdgeCases**: Test TID 0, negative TIDs, large TIDs
- **Idempotency**: Multiple register/unregister calls
- **MemoryOrdering**: Writer/reader threads verify acquire/release semantics

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
4. **Memory Trade-off**: ~65 KB total overhead (32 KB bitset fits in L1 cache)
5. **Scalability**: Lock-free operations scale with thread count
6. **Reliability**: Handles race conditions without corruption
7. **Performance Optimization**: Java thread bitset reduces signal overhead by ~95%
8. **False Sharing Prevention**: Cache-line padding ensures atomic operations don't contend
9. **Double-Hashing**: Reduces false positive probability from p to p², making false positives effectively non-issue
10. **Reusable Components**: `LockFreeBitset` template class can be used for other purposes

## Future Enhancements

### Potential Improvements

1. **Dynamic Buffer Sizing**: Grow buffer if 256 slots exhausted
2. **macOS Native Support**: Explore kqueue for thread monitoring
3. **Metrics**: Track slot utilization and initialization latency
4. **Proactive Priming**: Prime threads during profiler start
5. **Buffer Compaction**: Defragment free slots periodically

### Known Limitations

1. **Fixed Buffer Size**: 256 slots may be insufficient for extreme workloads
2. **macOS Gap**: Native threads not pre-initialized (no bitset optimization)
3. **Watcher Latency**: ~1-10 μs delay between thread start and priming
4. **Signal Exhaustion**: RT signals limited (typically 32 available)
5. **Bitset False Positives**: Double-hashing reduces false positives to ~0.003-0.37% (effectively non-issue)
6. **Bitset Memory**: 32 KB overhead (fits in L1 cache, justified by near-zero false positives)

## Summary

This architecture provides a robust, platform-aware solution to the TLS initialization problem with intelligent Java thread filtering:

- **Signal Safety**: Eliminates malloc/locks in signal handlers
- **Performance**: 95% reduction in unnecessary signals via bitset filtering
- **Reliability**: Lock-free operations with proper memory ordering
- **False Positive Minimization**: Double-hashing reduces false positives to ~0.003-0.37%
- **Memory Trade-off**: ~65 KB total overhead (32 KB bitset fits entirely in L1 cache)
- **Testing**: Comprehensive unit tests including concurrent access, memory ordering, and double-hash effectiveness

The double-hashed bitset optimization is a critical enhancement that prevents wasteful signal delivery to Java threads while ensuring native threads are not incorrectly skipped due to hash collisions. The reusable `LockFreeBitset` class in `lockFree.h` encapsulates this functionality and can be used for other concurrent membership tracking needs.
