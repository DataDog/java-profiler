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
class VMNMethod;
class StackContext;
class VM;

enum State { NEW, IDLE, RUNNING, TERMINATED };

/**
 * Converts a BCI_* frame type value to the corresponding EventType enum value.
 *
 * This conversion is necessary because Datadog's implementation uses BCI_* values
 * (from ASGCT_CallFrameType) directly as event type identifiers, while upstream
 * StackWalker::walkVM() expects EventType enum values for its logic.
 *
 * BCI_* values are special frame types with negative values (except BCI_CPU=0)
 * that indicate non-standard frame information in call traces. EventType values
 * are positive enum indices used for event categorization in the upstream code.
 *
 * @param bci_type A BCI_* value (e.g., BCI_CPU, BCI_WALL, BCI_ALLOC)
 * @return The corresponding EventType enum value
 */
inline EventType eventTypeFromBCI(jint bci_type) {
    switch (bci_type) {
        case BCI_CPU:
            return EXECUTION_SAMPLE;  // CPU samples map to execution samples
        case BCI_WALL:
            return WALL_CLOCK_SAMPLE;
        case BCI_ALLOC:
            return ALLOC_SAMPLE;
        case BCI_ALLOC_OUTSIDE_TLAB:
            return ALLOC_OUTSIDE_TLAB;
        case BCI_LIVENESS:
            return LIVE_OBJECT;
        case BCI_LOCK:
            return LOCK_SAMPLE;
        case BCI_PARK:
            return PARK_SAMPLE;
        default:
            // For unknown or invalid BCI types, default to EXECUTION_SAMPLE
            // This maintains backward compatibility and prevents undefined behavior
            return EXECUTION_SAMPLE;
    }
}

// Aligned to satisfy SpinLock member alignment requirement (64 bytes)  
// Required because this class contains multiple SpinLock members:
// _class_map_lock, _locks[], and _stubs_lock
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
  SpinLock _stubs_lock;
  CodeCache _runtime_stubs;
  const void *_call_stub_begin;
  const void *_call_stub_end;
  u32 _num_context_attributes;
  bool _omit_stacktraces;
  bool _remote_symbolication;  // Enable remote symbolication for native frames

  // dlopen() hook support
  void **_dlopen_entry;
  static void *dlopen_hook(const char *filename, int flags);
  void switchLibraryTrap(bool enable);

  void enableEngines();
  void disableEngines();

  void addJavaMethod(const void *address, int length, jmethodID method);
  void addRuntimeStub(const void *address, int length, const char *name);

  void onThreadStart(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread);
  void onThreadEnd(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread);

  const char *asgctError(int code);
  u32 getLockIndex(int tid);
  bool isAddressInCode(uintptr_t addr);
  int getNativeTrace(void *ucontext, ASGCT_CallFrame *frames, int event_type,
                     int tid, StackContext *java_ctx, bool *truncated, int lock_index);
  int getJavaTraceAsync(void *ucontext, ASGCT_CallFrame *frames, int max_depth,
                        StackContext *java_ctx, bool *truncated);
  void fillFrameTypes(ASGCT_CallFrame *frames, int num_frames,
                      VMNMethod *nmethod);
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

  static bool crashHandler(int signo, siginfo_t *siginfo, void *ucontext);
  static void check_JDK_8313796_workaround();

  static Profiler *const _instance;

public:
  Profiler()
      : _state(NEW), _class_unload_hook_trap(2),
        _notify_class_unloaded_func(NULL), _thread_filter(), _call_trace_storage(), _jfr(),
        _start_time(0), _epoch(0), _timer_id(NULL),
        _max_stack_depth(0), _safe_mode(0), _thread_events_state(JVMTI_DISABLE),
        _libs(Libraries::instance()), _stubs_lock(), _runtime_stubs("[stubs]"),
        _call_stub_begin(NULL), _call_stub_end(NULL), _dlopen_entry(NULL),
        _num_context_attributes(0), _class_map(1), _string_label_map(2),
        _context_value_map(3), _cpu_engine(), _alloc_engine(), _event_mask(0),
        _stop_time(), _total_samples(0), _failures(), _cstack(CSTACK_NO),
        _omit_stacktraces(false) {

    for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
      _calltrace_buffer[i] = NULL;
    }
  }

  static Profiler *instance() {
    return _instance;
  }

  int status(char* status, int max_len);

  const char* cstack() {
    switch (_cstack) {
      case CSTACK_DEFAULT: return "default";
      case CSTACK_NO: return "no";
      case CSTACK_FP: return "fp";
      case CSTACK_DWARF: return "dwarf";
      case CSTACK_LBR: return "lbr";
      case CSTACK_VM: {
        return _features.mixed ? "vmx" : "vm";
      }
      default: return "default";
    }
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
     * Layout: pc_offset (44 bits) | mark (3 bits) | lib_index (17 bits)
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

  const void *resolveSymbol(const char *name);
  const char *getLibraryName(const char *native_symbol);
  const char *findNativeMethod(const void *address);
  CodeBlob *findRuntimeStub(const void *address);
  bool isAddressInCode(const void *pc, bool include_stubs = true);

  static void segvHandler(int signo, siginfo_t *siginfo, void *ucontext);
  static void busHandler(int signo, siginfo_t *siginfo, void *ucontext);
  static void setupSignalHandlers();

  static int registerThread(int tid);
  static void unregisterThread(int tid);

  // CompiledMethodLoad is also needed to enable DebugNonSafepoints info by
  // default
  static void JNICALL CompiledMethodLoad(jvmtiEnv *jvmti, jmethodID method,
                                         jint code_size, const void *code_addr,
                                         jint map_length,
                                         const jvmtiAddrLocationMap *map,
                                         const void *compile_info) {
    instance()->addJavaMethod(code_addr, code_size, method);
  }

  static void JNICALL DynamicCodeGenerated(jvmtiEnv *jvmti, const char *name,
                                           const void *address, jint length) {
    instance()->addRuntimeStub(address, length, name);
  }

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
