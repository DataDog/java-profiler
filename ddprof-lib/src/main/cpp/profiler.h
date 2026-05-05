/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
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
#include "engine.h"
#include "event.h"
#include "flightRecorder.h"
#include "libraries.h"
#include "log.h"
#include "mutex.h"
#include "objectSampler.h"
#include "spinLock.h"
#include "thread.h"
#include "threadFilter.h"
#include "threadInfo.h"
#include "trap.h"
#include "vmEntry.h"
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

enum State { NEW, IDLE, RUNNING, TERMINATED };

// Aligned to satisfy SpinLock member alignment requirement (64 bytes)  
// Required because this class contains multiple SpinLock members:
// _class_map_lock and _locks[]
class alignas(alignof(SpinLock)) Profiler {
  friend VM;

private:
  // signal handlers
  static volatile bool _signals_initialized;

  // JDK_8313796 workaround for unfixed versions
  static volatile bool _need_JDK_8313796_workaround;

  Mutex _state_lock;
  State _state;
  // class unload hook
  Trap _class_unload_hook_trap;
  typedef void (*NotifyClassUnloadedFunc)(void *);
  NotifyClassUnloadedFunc _notify_class_unloaded_func;
  // --

  ThreadInfo _thread_info;
  Dictionary _class_map;
  Dictionary _string_label_map;
  Dictionary _context_value_map;
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
  alignas(DEFAULT_CACHE_LINE_SIZE) volatile u64 _sample_seq;
  u64 _failures[ASGCT_FAILURE_TYPES];

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

  void enableEngines();
  void disableEngines();

  void onThreadStart(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread);
  void onThreadEnd(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread);

  u32 getLockIndex(int tid);
  int getNativeTrace(void *ucontext, ASGCT_CallFrame *frames, int event_type,
                     int tid, StackContext *java_ctx, bool *truncated, int lock_index);
  void updateThreadName(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                        bool self = false);
  void updateJavaThreadNames();
  void updateNativeThreadNames();
  void mangle(const char *name, char *buf, size_t size);

  Engine *selectCpuEngine(Arguments &args);
  Engine *selectWallEngine(Arguments &args);
  Engine *selectAllocEngine(Arguments &args);
  Error checkJvmCapabilities();

  void lockAll();
  void unlockAll();

  static int crashHandlerInternal(int signo, siginfo_t *siginfo, void *ucontext);
  static void check_JDK_8313796_workaround();

  static Profiler *const _instance;

public:
  Profiler()
      : _state_lock(), _state(NEW), _class_unload_hook_trap(2),
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

  u64 total_samples() { return _total_samples; }
  int max_stack_depth() { return _max_stack_depth; }
  time_t uptime() { return time(NULL) - _start_time; }
  Engine *cpuEngine() { return _cpu_engine; }
  Engine *wallEngine() { return _wall_engine; }

  Dictionary *classMap() { return &_class_map; }
  Dictionary *stringLabelMap() { return &_string_label_map; }
  Dictionary *contextValueMap() { return &_context_value_map; }
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

  Error run(Arguments &args);
  Error runInternal(Arguments &args, std::ostream &out);
  Error restart(Arguments &args);
  void shutdown(Arguments &args);
  Error check(Arguments &args);
  Error start(Arguments &args, bool reset);
  Error stop();
  Error flushJfr();
  Error dump(const char *path, const int length);
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
   * Mark values indicate JVM internal frames that should terminate stack walks:
   *   0 = no mark (regular native frame)
   *   MARK_VM_RUNTIME = 1
   *   MARK_INTERPRETER = 2
   *   MARK_COMPILER_ENTRY = 3
   *   MARK_ASYNC_PROFILER = 4
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
    bool is_marked;                     // true if this is a marked C++ interpreter frame (stop processing)
    NativeFrameResolution(const char* name, int bci_type, bool marked)
      : method_name(name), bci(bci_type), is_marked(marked) {}
    NativeFrameResolution(unsigned long packed, int bci_type, bool marked)
      : packed_remote_frame(packed), bci(bci_type), is_marked(marked) {}
  };

  void populateRemoteFrame(ASGCT_CallFrame* frame, uintptr_t pc, CodeCache* lib, char mark);
  NativeFrameResolution resolveNativeFrameForWalkVM(uintptr_t pc, int lock_index);
  int convertNativeTrace(int native_frames, const void **callchain,
                         ASGCT_CallFrame *frames, int lock_index);
  void recordSample(void *ucontext, u64 weight, int tid, jint event_type,
                    u64 call_trace_id, Event *event);
  // Delegated sample path: stack-walking is performed by the HotSpot JFR
  // RequestStackTrace extension (the JVM emits the stack trace into its own
  // JFR recording). We only emit the CPU/wall sample event with no
  // stack-trace reference, tagged by the correlation ID we passed to
  // RequestStackTrace as user_data. Returns true if the request was accepted
  // by the JVM (JVMTI_ERROR_NONE) and the sample event was recorded, false
  // otherwise; on false the caller may fall back to a direct walk.
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
