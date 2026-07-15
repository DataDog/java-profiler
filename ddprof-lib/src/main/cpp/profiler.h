/*
 * Copyright The async-profiler authors
 * Copyright 2025, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _PROFILER_H
#define _PROFILER_H

#include "arch.h"
#include "arguments.h"
#include "callTraceStorage.h"
#include "codeCache.h"
#include "common.h"
#include "dictionary.h"
#include "stringDictionary.h"
#include "engine.h"
#include "event.h"
#include "flightRecorder.h"
#include "guards.h"
#include "libraries.h"
#include "log.h"
#include "mutex.h"
#include "objectSampler.h"
#include "spinLock.h"
#include "threadLocalData.h"
#include "threadFilter.h"
#include "threadInfo.h"
#include "trap.h"
#include "vmEntry.h"
#include <atomic>
#include <iostream>
#include <map>
#include <time.h>

// avoid linking against newer symbols here for wide compatibility
#ifdef __GLIBC__
#ifdef __aarch64__
__asm__(".symver log,log@GLIBC_2.17");
__asm__(".symver exp,exp@GLIBC_2.17");
#endif
#endif

// A "hook-prefixed" sample (malloc, socket I/O, ...) is one whose native
// callchain starts inside the profiler's own PLT/libc hook and must be
// trimmed up to the MARK_JAVA_PROFILER boundary frame before symbolication.
// Single source of truth for that predicate across both BCI_* (FP/DWARF path)
// and EventType (walkVM path) representations.
inline bool isHookPrefixedSample(jint bci) {
  return bci == BCI_NATIVE_MALLOC || bci == BCI_NATIVE_SOCKET;
}

inline bool isHookPrefixedSample(EventType event_type) {
  return event_type == MALLOC_SAMPLE || event_type == SOCKET_SAMPLE;
}

#ifdef DEBUG
#include <signal.h>
static const char* force_stackwalk_crash_env = getenv("DDPROF_FORCE_STACKWALK_CRASH");
#endif

const int MAX_NATIVE_FRAMES = 128;
const int RESERVED_FRAMES   = 10;  // for synthetic frames

union CallTraceBuffer {
  ASGCT_CallFrame _asgct_frames[1];
  jvmtiFrameInfo _jvmti_frames[1];
};

class FrameName;
class StackContext;
class VM;

enum State { NEW, IDLE, RUNNING, TERMINATED, ERROR };

// Aligned to satisfy SpinLock member alignment requirement (64 bytes)
// Required because this class contains the _locks[] SpinLock array.
class alignas(alignof(SpinLock)) Profiler {
  friend VM;
  friend class ProfilerTestAccessor;

private:
  // signal handlers
  static volatile bool _signals_initialized;

  // JDK_8313796 workaround for unfixed versions
  static volatile bool _need_JDK_8313796_workaround;

  Mutex _state_lock;
  std::atomic<State> _state;
  // class unload hook
  Trap _class_unload_hook_trap;
  typedef void (*NotifyClassUnloadedFunc)(void *);
  NotifyClassUnloadedFunc _notify_class_unloaded_func;
  // --

  // Caps the number of distinct class names _class_map will ever hold.
  // rotate()/clearStandby() carry the full accumulated set forward on every
  // JFR chunk (only clearAll() on profiler restart truly resets it), so
  // without a cap a workload with unbounded distinct-class churn (e.g. heavy
  // dynamic class generation) grows this dictionary for the lifetime of the
  // process. 256K distinct classes is far beyond any real application's
  // class count.
  static const int MAX_CLASS_MAP_SIZE = 1 << 18;

  ThreadInfo _thread_info;
  StringDictionary _class_map{1};
  StringDictionary _string_label_map{2};
  StringDictionary _context_value_map{3};
  // Set when a fresh start resets _context_value_map (clearAll), reassigning encodings. Consumed by
  // the Java layer to drop its process-wide ContextValueCache so no stale encoding is reused. See
  // JavaProfiler.execute / ContextValueCache.
  std::atomic<bool> _context_value_dict_reset{false};
  ThreadFilter _thread_filter;
  CallTraceStorage _call_trace_storage;
  FlightRecorder _jfr;
  Engine *_cpu_engine;
  Engine *_wall_engine = NULL;
  Engine *_alloc_engine;
  int _event_mask;

  time_t _start_time;
  time_t _stop_time;
  u32 _epoch;
  WaitableMutex _timer_lock;
  void *_timer_id;

  volatile u64 _total_samples;
  // On a separate cache line: incremented from every signal handler via
  // recordSampleDelegated; must not share a line with _failures (written by
  // ASGCT paths) or _total_samples (written by every recording path).
  alignas(DEFAULT_CACHE_LINE_SIZE) volatile u64 _sample_seq;
  alignas(DEFAULT_CACHE_LINE_SIZE) u64 _failures[ASGCT_FAILURE_TYPES];
  bool _wall_precheck = false;
  std::atomic<bool> _task_block_enabled{false};
  std::atomic<bool> _task_block_rotation{false};
  std::atomic<u64> _task_block_inflight{0};

  SpinLock _class_map_lock;
  SpinLock _locks[CONCURRENCY_LEVEL];
  CallTraceBuffer *_calltrace_buffer[CONCURRENCY_LEVEL];
  int _max_stack_depth;
  StackWalkFeatures _features;
  int _safe_mode;
  CStack _cstack;

  volatile jvmtiEventMode _thread_events_state;

  Libraries* _libs;
  u32 _num_context_attributes;
  bool _omit_stacktraces;
  bool _remote_symbolication;  // Enable remote symbolication for native frames

  // dlopen() hook support
  void **_dlopen_entry;
  static void *dlopen_hook(const char *filename, int flags);
  void switchLibraryTrap(bool enable);
  static void prewarmUnwinder();

  void disableEngines();

  void onThreadStart(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread);
  void onThreadEnd(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread);

  u32 getLockIndex(int tid);
  int getNativeTrace(void *ucontext, ASGCT_CallFrame *frames, int event_type,
                     int tid, StackContext *java_ctx, bool *truncated, int lock_index);
  void updateThreadName(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                        bool self = false);
  void updateJavaThreadNames();
  // Publish the native-symbol (CodeCache) memory counters and NativeMem gauge
  // from the current library set. Called before each JFR chunk is finalized
  // (dump and stop) so the emitted counters reflect the latest libraries.
  void updateNativeLibMemStats();
  void mangle(const char *name, char *buf, size_t size);

  Engine *selectCpuEngine(Arguments &args);
  Engine *selectWallEngine(Arguments &args);
  Engine *selectAllocEngine(Arguments &args);
  Error checkJvmCapabilities();

  void lockAll();
  void unlockAll();
  void beginTaskBlockRotation();
  void endTaskBlockRotation();

  // Rotate all three dictionaries, then run jfr_op under lockAll().
  //
  // rotate() is self-contained: it uses _accepting + RefCountGuard to drain
  // concurrent JNI readers, and SignalBlocker prevents profiling signals on
  // this thread from inserting into old_active between Phase 1 and Phase 2.
  // No external lock is required for rotation.
  //
  // lockAll() wraps jfr_op only — to gate call-trace writers (signal handlers
  // and JNI paths that write to CallTraceStorage) from racing with the dump.
  // Dictionary writers that bypass lockAll() (e.g. recordTrace0) are handled
  // by the dictionary's own RefCountGuard protocol, not by lockAll().
  template<typename F>
  void rotateDictsAndRun(F jfr_op) {
    SignalBlocker blocker;
    _class_map.rotate();
    _string_label_map.rotate();
    _context_value_map.rotate();
    lockAll();
    jfr_op();
    unlockAll();
    _class_map.clearStandby();
    _string_label_map.clearStandby();
    _context_value_map.clearStandby();
  }

  static int crashHandlerInternal(int signo, siginfo_t *siginfo, void *ucontext);
  static void check_JDK_8313796_workaround();

  static Profiler *const _instance;

  inline State state() const {
    return _state.load(std::memory_order_relaxed);
  }

public:
  Profiler()
      : _state_lock(), _state(State::NEW), _class_unload_hook_trap(2),
        _notify_class_unloaded_func(NULL), _thread_info(), _class_map(1),
        _string_label_map(2), _context_value_map(3), _thread_filter(),
        _call_trace_storage(), _jfr(), _cpu_engine(NULL), _wall_engine(NULL),
        _alloc_engine(NULL), _event_mask(0),
        _start_time(0), _stop_time(0), _epoch(0), _timer_id(NULL),
        _total_samples(0), _sample_seq(0), _failures(), _class_map_lock(),
        _max_stack_depth(0), _features(), _safe_mode(0), _cstack(CSTACK_NO),
        _thread_events_state(JVMTI_DISABLE), _libs(Libraries::instance()),
        _num_context_attributes(0), _omit_stacktraces(false),
        _remote_symbolication(false), _dlopen_entry(NULL) {

    for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
      _calltrace_buffer[i] = NULL;
    }
  }

  static inline Profiler *instance() {
    return _instance;
  }

  // Resolve names of native (non-Java) threads from /proc. Idempotent and
  // allocation-light (no-op for already-named tids), so it is safe to call
  // periodically from the Libraries refresher thread to capture transient
  // compiler/GC threads before they exit. Must NOT be called from a signal
  // handler: thread enumeration uses opendir/readdir/malloc.
  //
  // When defer_initializing is true (periodic refresher), a thread whose comm
  // still equals the process's own (inherited) name is skipped: it is most
  // likely still initializing and has not yet set its final pthread name.
  // Recording it now would latch that provisional name permanently
  // (ThreadInfo::updateThreadName is first-writer-wins). A later scan, or the
  // dump-time pass (which passes false), records the final name instead.
  void updateNativeThreadNames(bool defer_initializing = false);

  inline void incFailure(int type) {
    if (type < ASGCT_FAILURE_TYPES) {
      atomicIncRelaxed(_failures[type]);
    }
  }

  int status(char* status, int max_len);
  static const char *asgctError(int code);

  
  inline int safe_mode() const {
    return _safe_mode;
  }

  inline const Libraries* libraries() const {
    return _libs;
  }

  inline CStack cstackMode() const {
    return _cstack;
  }

  inline const StackWalkFeatures& stackWalkFeatures() const {
    return _features;
  }

  inline bool isRunning() {
    return _state.load(std::memory_order_acquire) == RUNNING;
  }

  u64 total_samples() { return _total_samples; }
  int max_stack_depth() { return _max_stack_depth; }
  time_t uptime() { return time(NULL) - _start_time; }
  Engine *cpuEngine() { return _cpu_engine; }
  Engine *wallEngine() { return _wall_engine; }

  StringDictionary *classMap() { return &_class_map; }
  // Same cap lookupClass() enforces for sample-time inserts; dump-time
  // insertions (Lookup::_classes->lookupDuringDump in flightRecorder.cpp)
  // must use this too so _class_map cannot grow past it via that path.
  static int maxClassMapSize() { return MAX_CLASS_MAP_SIZE; }
  SharedLockGuard classMapSharedGuard() { return SharedLockGuard(&_class_map_lock); }
  StringDictionary *stringLabelMap() { return &_string_label_map; }
  StringDictionary *contextValueMap() { return &_context_value_map; }
  // Atomically reads and clears the "context value dictionary was reset" flag (see the member).
  bool consumeContextValueDictReset() {
    return _context_value_dict_reset.exchange(false, std::memory_order_acq_rel);
  }
  u32 numContextAttributes() { return _num_context_attributes; }
  ThreadFilter *threadFilter() { return &_thread_filter; }

  const char* cstack() const;
  int lookupClass(const char *key, size_t length);
  void processCallTraces(std::function<void(const std::unordered_set<CallTrace*>&)> processor) {
    if (!_omit_stacktraces) {
      _call_trace_storage.processTraces(processor);
    } else {
      // If stack traces are omitted, call processor with empty set
      static std::unordered_set<CallTrace*> empty_traces;
      processor(empty_traces);
    }
  }
  
  void registerLivenessChecker(LivenessChecker checker) {
    _call_trace_storage.registerLivenessChecker(checker);
  }

  inline u32 recordingEpoch() {
    // no thread reordering constraints
    return __atomic_load_n(&_epoch, __ATOMIC_RELAXED);
  }

  Error init();
  Error run(Arguments &args);
  Error runInternal(Arguments &args, std::ostream &out);
  Error restart(Arguments &args);
  void shutdown(Arguments &args);
  Error check(Arguments &args);
  Error start(Arguments &args, bool reset);
  Error stop();
  Error dump(const char *path, const int length);
  Error checkState();
  void logStats();
  void switchThreadEvents(jvmtiEventMode mode);

  /**
   * Remote symbolication packed data layout (BCI_NATIVE_FRAME_REMOTE):
   *
   * When remote symbolication is enabled and a library has a build-ID, we defer
   * full symbol resolution to post-processing and pack essential data into the
   * 64-bit jmethodID field:
   *
   *   Bits 0-43:   pc_offset (44 bits, 16 TB range)
   *   Bits 44-46:  mark (3 bits, 0-7 values)
   *   Bits 47-61:  lib_index (15 bits, 32K libraries)
   *.  Bits 62-63:  reserved
   *
   * Mark values identify JVM-internal frames the caller must dispatch on;
   * they don't all mean "terminate the walk":
   *   0 = no mark (regular native frame)
   *   MARK_VM_RUNTIME = 1      -- terminates the scan
   *   MARK_INTERPRETER = 2     -- terminates the scan
   *   MARK_COMPILER_ENTRY = 3  -- inserts a pseudo JIT-compile-task frame, then resumes unwinding
   *   MARK_JAVA_PROFILER = 4  -- resets depth and resumes unwinding above the hook boundary
   *
   * During stack walking, we perform symbol resolution (binarySearch) to check
   * marks and pack the mark value for later use. The performance is O(log n) for
   * binarySearch + O(1) for mark extraction, same as traditional symbolication
   * but simpler than maintaining a separate marked ranges index.
   */
  struct RemoteFramePacker {
    static const int PC_OFFSET_BITS = 44;
    static const int MARK_BITS = 3;
    static const int LIB_INDEX_BITS = 15;

    static const unsigned long PC_OFFSET_MASK = (1ULL << PC_OFFSET_BITS) - 1;  // 0xFFFFFFFFFFF (44 bits)
    static const unsigned long MARK_MASK = (1ULL << MARK_BITS) - 1;             // 0x7 (3 bits)
    static const unsigned long LIB_INDEX_MASK = (1ULL << LIB_INDEX_BITS) - 1;   // 0x7FFF (15 bits)

    /**
     * Pack remote symbolication data into a 64-bit jmethodID.
     * Layout: pc_offset (44 bits) | mark (3 bits) | lib_index (15 bits)
     */
    static inline unsigned long pack(uintptr_t pc_offset, char mark, uint32_t lib_index) {
      return (unsigned long)(
        (pc_offset & PC_OFFSET_MASK) |                                             // Bits 0-43
        (((unsigned long)mark & MARK_MASK) << PC_OFFSET_BITS) |                        // Bits 44-46
        (((unsigned long)lib_index & LIB_INDEX_MASK) << (PC_OFFSET_BITS + MARK_BITS))  // Bits 47-62
      );
    }

    /**
     * Unpack pc_offset from packed data.
     */
    static inline uintptr_t unpackPcOffset(unsigned long packed) {
      return (uintptr_t)(packed & PC_OFFSET_MASK);
    }

    /**
     * Unpack mark from packed data.
     */
    static inline char unpackMark(unsigned long packed) {
      return (char)((packed >> PC_OFFSET_BITS) & MARK_MASK);
    }

    /**
     * Unpack lib_index from packed data.
     */
    static inline uint32_t unpackLibIndex(unsigned long packed) {
      return (uint32_t)((packed >> (PC_OFFSET_BITS + MARK_BITS)) & LIB_INDEX_MASK);
    }
  };

  // Result of resolving a native frame for symbolication
  struct NativeFrameResolution {
    union {
      unsigned long packed_remote_frame;  // Packed remote frame data (pc_offset|mark|lib_index)
      const char* method_name;            // Resolved method name
    };
    int bci;                            // BCI_NATIVE_FRAME_REMOTE or BCI_NATIVE_FRAME
    char mark;                         // Value domain: 0 (unmarked) or one of the Mark
                                        // enum constants (codeCache.h), currently 1-5.
                                        // Kept as char rather than Mark since it is
                                        // packed into RemoteFramePacker's 3-bit field.
    // True if this frame carries a JVM-internal mark; caller must inspect
    // `mark` to decide whether to terminate the walk or dispatch/resume
    // (see the Mark values table above resolveNativeFrameForWalkVM).
    bool is_marked() const { return mark != 0; }
    NativeFrameResolution(const char* name, int bci_type, char mark_value = 0)
      : method_name(name), bci(bci_type), mark(mark_value) {}
    NativeFrameResolution(unsigned long packed, int bci_type, char mark_value = 0)
      : packed_remote_frame(packed), bci(bci_type), mark(mark_value) {}
  };

  void populateRemoteFrame(ASGCT_CallFrame* frame, uintptr_t pc, CodeCache* lib, char mark);
  NativeFrameResolution resolveNativeFrameForWalkVM(uintptr_t pc, int lock_index);
  int convertNativeTrace(int native_frames, const void **callchain,
                         ASGCT_CallFrame *frames, int lock_index,
                         bool skip_hook_prefix);
  bool recordSample(void *ucontext, u64 weight, int tid, jint event_type,
                    u64 call_trace_id, Event *event,
                    u64 *recorded_call_trace_id = nullptr);
  // Delegated sample path: stack-walking is performed by the HotSpot JFR
  // RequestStackTrace extension (the JVM emits the stack trace into its own
  // JFR recording). We only emit the CPU/wall sample event with no
  // stack-trace reference, tagged by the correlation ID we passed to
  // RequestStackTrace as user_data.
  bool recordSampleDelegated(void *ucontext, u64 weight, int tid,
                             jint event_type, Event *event);
  u64 recordJVMTISample(u64 weight, int tid, jthread thread, jint event_type, Event *event, bool deferred);
  void recordDeferredSample(int tid, u64 call_trace_id, jint event_type, Event *event);
  void recordExternalSample(u64 weight, int tid, int num_frames,
                            ASGCT_CallFrame *frames, bool truncated,
                            jint event_type, Event *event);
  void recordWallClockEpoch(int tid, WallClockEpochEvent *event);
  void recordTraceRoot(int tid, TraceRootEvent *event);
  void recordQueueTime(int tid, QueueTimeEvent *event);
  enum class TaskBlockRecordResult {
    RECORDED,
    STACK_CAPTURE_FAILED,
    RECORD_FAILED,
  };
  TaskBlockRecordResult recordTaskBlock(int tid, jthread thread,
                                        int start_depth,
                                        TaskBlockEvent *event);
#ifdef UNIT_TEST
  using TaskBlockRecordOverride = TaskBlockRecordResult (*)(
      int tid, jthread thread, int start_depth, TaskBlockEvent *event);
  static void setTaskBlockRecordOverrideForTest(
      TaskBlockRecordOverride override);
#endif
  bool tryEnterTaskBlockActivity();
  void leaveTaskBlockActivity();
  void waitForTaskBlockRotation();
  bool taskBlockEnabled() const {
    return _task_block_enabled.load(std::memory_order_acquire);
  }
  void writeLog(LogLevel level, const char *message);
  void writeLog(LogLevel level, const char *message, size_t len);
  void writeDatadogProfilerSetting(int tid, int length, const char *name,
                                   const char *value, const char *unit);
  void writeHeapUsage(long value, bool live);
  int eventMask() const { return _event_mask; }
  bool isRemoteSymbolication() const { return _remote_symbolication; }

  const void *resolveSymbol(const char *name);
  const char *getLibraryName(const char *native_symbol);
  const char *findNativeMethod(const void *address);

  static void segvHandler(int signo, siginfo_t *siginfo, void *ucontext);
  static void busHandler(int signo, siginfo_t *siginfo, void *ucontext);
  static void setupSignalHandlers();

  static int registerThread(int tid);
  static void unregisterThread(int tid);

#ifdef UNIT_TEST
  void beginTaskBlockRotationForTest() { beginTaskBlockRotation(); }
  void endTaskBlockRotationForTest() { endTaskBlockRotation(); }
  bool taskBlockRotationActiveForTest() const {
    return _task_block_rotation.load(std::memory_order_acquire);
  }
  int taskBlockInflightForTest() const {
    return _task_block_inflight.load(std::memory_order_acquire);
  }

  // Returns the tid most recently passed to unregisterThread(), or -1 if it
  // has never been called (or since the last resetUnregisterObservableForTest).
  // Used by integration tests to assert that cleanup_unregister wired
  // Profiler::unregisterThread correctly without needing live engine instances.
  static int  lastUnregisteredTidForTest();
  static void resetUnregisterObservableForTest();

  // Reads back the name recorded for a tid in _thread_info, or an empty string
  // if none was recorded. Lets integration tests observe the result of
  // updateNativeThreadNames() (notably the defer_initializing skip) without
  // exposing the private _thread_info. Compiled only into gtest binaries.
  std::string threadNameForTest(int tid) {
    std::pair<std::shared_ptr<std::string>, u64> info = _thread_info.get(tid);
    return info.first != nullptr ? *info.first : std::string();
  }
#endif


  static void JNICALL ThreadStart(jvmtiEnv *jvmti, JNIEnv *jni,
                                  jthread thread) {
    instance()->onThreadStart(jvmti, jni, thread);
  }

  static void JNICALL ThreadEnd(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread) {
    instance()->onThreadEnd(jvmti, jni, thread);
  }

  // Keep backward compatibility with the upstream async-profiler
  inline CodeCache* findLibraryByAddress(const void *address) {
  #ifdef DEBUG
    // we need this code to simulate segfault during stackwalking
    // this is a safe place to do it since this wrapper is used solely from the 'vm' stackwalker implementation
    if (force_stackwalk_crash_env) {
      TEST_LOG("FORCE_SIGSEGV");
      raise(SIGSEGV);
    }
  #endif
    return Libraries::instance()->findLibraryByAddress(address);
  }

  friend class Recording;
};

#endif // _PROFILER_H
