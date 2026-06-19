/*
 * Copyright The async-profiler authors
 * Copyright 2024, 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cassert>
#include "profiler.h"
#include "asyncSampleMutex.h"
#include "mallocTracer.h"
#include "nativeSocketSampler.h"
#include "nativeSocketInterposer.h"
#include "context.h"
#include "guards.h"
#include "common.h"
#include "counters.h"
#include "ctimer.h"
#include "dwarf.h"
#include "flightRecorder.h"
#include "itimer.h"
#include "hotspot/vmStructs.inline.h"
#include "hotspot/hotspotSupport.h"
#include "j9/j9Support.h"
#include "j9/j9WallClock.h"
#include "jvmSupport.h"
#include "jvmThread.h"
#include "libraryPatcher.h"
#include "objectSampler.h"
#include "os.h"
#include "perfEvents.h"
#include "safeAccess.h"
#include "stackFrame.h"
#include "stackWalker.h"
#include "symbols.h"
#include "taskBlockRecorder.h"
#include "thread.h"
#include "tsc.h"
#include "utils.h"
#include "wallClock.h"
#include "wallClockCounters.h"
#include "frames.h"

#include <algorithm>
#include <dlfcn.h>
#include <fstream>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>

// The instance is not deleted on purpose, since profiler structures
// can be still accessed concurrently during VM termination
Profiler *const Profiler::_instance = new Profiler();
volatile bool Profiler::_signals_initialized = false;
volatile bool Profiler::_need_JDK_8313796_workaround = true;

static void (*orig_segvHandler)(int signo, siginfo_t *siginfo, void *ucontext);
static void (*orig_busHandler)(int signo, siginfo_t *siginfo, void *ucontext);

static Engine noop_engine;
static MallocTracer malloc_tracer;
static PerfEvents perf_events;
static WallClockASGCT wall_asgct_engine;
static WallClockJvmti wall_jvmti_engine;
static J9WallClock j9_engine;
static ITimer itimer;
static ITimerJvmti itimer_jvmti;
static CTimer ctimer;
static CTimerJvmti ctimer_jvmti;

void *Profiler::taskBlockDrainLoop(void *arg) {
  Profiler *self = static_cast<Profiler *>(arg);

  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGPROF);
  sigaddset(&mask, SIGVTALRM);
  pthread_sigmask(SIG_BLOCK, &mask, nullptr);

  while (self->_task_block_drain_running.load(std::memory_order_acquire)) {
    self->drainTaskBlockQueue(true);
    OS::sleepWhile(1000000ULL, self->_task_block_drain_running);
  }
  self->drainTaskBlockQueue(true);
  return nullptr;
}

void Profiler::startTaskBlockDrain() {
  if (!_wall_precheck) {
    return;
  }
  if (_task_block_drain_running.load(std::memory_order_acquire)) {
    return;
  }

  _task_block_queue.discardAll();
  _task_block_generation.fetch_add(1, std::memory_order_acq_rel);
  _task_block_drain_running.store(true, std::memory_order_release);
  if (pthread_create(&_task_block_drain_thread, nullptr, taskBlockDrainLoop,
                     this) != 0) {
    _task_block_drain_running.store(false, std::memory_order_release);
    Log::warn("Unable to start TaskBlock drain thread");
    return;
  }
  if (VM::nativeMonitorEventsAvailable() &&
      !VM::setNativeMonitorEventsEnabled(true)) {
    stopTaskBlockDrain();
  }
}

void Profiler::stopTaskBlockDrain() {
  if (!_task_block_drain_running.load(std::memory_order_acquire)) {
    return;
  }
  if (VM::nativeMonitorEventsAvailable()) {
    VM::setNativeMonitorEventsEnabled(false);
  }
  if (!_task_block_drain_running.exchange(false, std::memory_order_acq_rel)) {
    return;
  }
  pthread_kill(_task_block_drain_thread, WAKEUP_SIGNAL);
  pthread_join(_task_block_drain_thread, nullptr);
  drainTaskBlockQueue(true);
}

void Profiler::drainTaskBlockQueue(bool record) {
  QueuedTaskBlockEvent queued;
  u64 generation = _task_block_generation.load(std::memory_order_acquire);
  while (_task_block_queue.tryPop(queued)) {
    if (record && queued.generation == generation) {
      if (recordTaskBlockLive(queued.tid, &queued.event)) {
        Counters::increment(TASK_BLOCK_EMITTED);
      } else {
        Counters::increment(TASK_BLOCK_RECORD_FAILED);
      }
    }
  }
}

void Profiler::onThreadStart(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread) {
  ProfiledThread::initCurrentThread();
  ProfiledThread *current = ProfiledThread::current();
  current->setJavaThread(true);
  int tid = current->tid();
  if (_thread_filter.enabled()) {
    int slot_id = _thread_filter.registerThread();
    current->setFilterSlotId(slot_id);
    _thread_filter.resetSlotRunState(slot_id);
    _thread_filter.remove(slot_id);  // Remove from filtering initially
  }
  if (thread != NULL) {
    updateThreadName(jvmti, jni, thread, true);
  }

  _cpu_engine->registerThread(tid);
  _wall_engine->registerThread(tid);
}

void Profiler::onThreadEnd(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread) {
  ProfiledThread *current = ProfiledThread::currentSignalSafe();
  int tid = -1;
  
  if (current != nullptr) {
    // ProfiledThread is alive - do full cleanup and use efficient tid access
    int slot_id = current->filterSlotId();
    tid = current->tid();
    
    if (_thread_filter.enabled()) {
      _thread_filter.unregisterThread(slot_id);
      current->setFilterSlotId(-1);
    }

    updateThreadName(jvmti, jni, thread, false);
    // Block profiling signals around engine unregistration + TLS release to
    // close the window where a wall-clock/CPU signal could sample a
    // partially-torn-down thread (PROF-14674).
    {
      SignalBlocker blocker;
      _cpu_engine->unregisterThread(tid);
      _wall_engine->unregisterThread(tid);
      ProfiledThread::release();
    }
    return;
  }

  // ProfiledThread already cleaned up - try to get tid from JVMTI as fallback
  tid = JVMThread::nativeThreadId(jni, thread);
  if (tid < 0) {
    // No ProfiledThread AND can't get tid from JVMTI - nothing we can do
    return;
  }

  updateThreadName(jvmti, jni, thread, false);
  _cpu_engine->unregisterThread(tid);
  _wall_engine->unregisterThread(tid);
}

int Profiler::registerThread(int tid) {
  return _instance->_cpu_engine->registerThread(tid) |
         _instance->_wall_engine->registerThread(tid);
}
#ifdef UNIT_TEST
static std::atomic<int> g_test_last_unregistered_tid{-1};

int Profiler::lastUnregisteredTidForTest() {
    return g_test_last_unregistered_tid.load(std::memory_order_relaxed);
}
void Profiler::resetUnregisterObservableForTest() {
    g_test_last_unregistered_tid.store(-1, std::memory_order_relaxed);
}
#endif

void Profiler::unregisterThread(int tid) {
#ifdef UNIT_TEST
    // In gtest, _cpu_engine/_wall_engine are null (profiler not started).
    // Record the tid so integration tests can verify the call happened without
    // crashing on the null engine dereference.  This bypasses the real engine
    // unregister path entirely, so that path is covered only by JVM-level tests,
    // not by these gtests.  UNIT_TEST is defined solely for the gtest binaries
    // (see GtestTaskBuilder); the shipped library never compiles this branch.
    g_test_last_unregistered_tid.store(tid, std::memory_order_relaxed);
    return;
#endif
  _instance->_cpu_engine->unregisterThread(tid);
  _instance->_wall_engine->unregisterThread(tid);
}

const char *Profiler::asgctError(int code) {
  switch (code) {
  case ticks_no_Java_frame:
  case ticks_unknown_not_Java:
    // Not in Java context at all; this is not an error
    return NULL;
  case ticks_thread_exit:
    // The last Java frame has been popped off, only native frames left
    return NULL;
  case ticks_GC_active:
    return "GC_active";
  case ticks_unknown_Java:
    return "unknown_Java";
  case ticks_not_walkable_Java:
    return "not_walkable_Java";
  case ticks_not_walkable_not_Java:
    return "not_walkable_not_Java";
  case ticks_deopt:
    return "deoptimization";
  case ticks_safepoint:
    return "safepoint";
  case ticks_skipped:
    return "skipped";
  case ticks_unknown_state:
    // Zing sometimes returns it
    return "unknown_state";
  default:
    // Should not happen
    return "unexpected_state";
  }
}

inline u32 Profiler::getLockIndex(int tid) {
  u32 lock_index = tid;
  lock_index ^= lock_index >> 8;
  lock_index ^= lock_index >> 4;
  return lock_index % CONCURRENCY_LEVEL;
}

void Profiler::mangle(const char *name, char *buf, size_t size) {
  char *buf_end = buf + size;
  strcpy(buf, "_ZN");
  buf += 3;

  const char *c;
  while ((c = strstr(name, "::")) != NULL && buf + (c - name) + 4 < buf_end) {
    int n = snprintf(buf, buf_end - buf, "%d", (int)(c - name));
    if (n < 0 || n >= buf_end - buf) {
      if (n < 0) {
        Log::debug("Error in snprintf.");
      }
      goto end;
    }
    buf += n;
    memcpy(buf, name, c - name);
    buf += c - name;
    name = c + 2;
  }
  if (buf < buf_end) {
    snprintf(buf, buf_end - buf, "%d%sE*", (int)strlen(name), name);
  }

end:
  buf_end[-1] = '\0';
}

const void *Profiler::resolveSymbol(const char *name) {
  char mangled_name[256];
  if (strstr(name, "::") != NULL) {
    mangle(name, mangled_name, sizeof(mangled_name));
    name = mangled_name;
  }

  size_t len = strlen(name);
  const CodeCacheArray& native_libs = _libs->native_libs();
  int native_lib_count = native_libs.count();
  if (len > 0 && name[len - 1] == '*') {
    for (int i = 0; i < native_lib_count; i++) {
      CodeCache *lib = native_libs[i];
      if (lib != NULL) {
        const void *address = lib->findSymbolByPrefix(name, len - 1);
        if (address != NULL) {
          return address;
        }
      }
    }
  } else {
    for (int i = 0; i < native_lib_count; i++) {
      CodeCache *lib = native_libs[i];
      if (lib != NULL) {
        const void *address = lib->findSymbol(name);
        if (address != NULL) {
          return address;
        }
      }
    }
  }

  return NULL;
}

// For BCI_NATIVE_FRAME, library index is encoded ahead of the symbol name
const char *Profiler::getLibraryName(const char *native_symbol) {
  short lib_index = NativeFunc::libIndex(native_symbol);
  const CodeCacheArray& native_libs = _libs->native_libs();
  if (lib_index >= 0 && lib_index < native_libs.count()) {
    CodeCache *lib = native_libs[lib_index];
    if (lib != NULL) {
      const char *s = lib->name();
      if (s != NULL) {
        const char *p = strrchr(s, '/');
        return p != NULL ? p + 1 : s;
      }
    }
  }
  return NULL;
}

const char *Profiler::findNativeMethod(const void *address) {
  CodeCache *lib = _libs->findLibraryByAddress(address);
  const char *name = NULL;
  if (lib != NULL) {
    lib->binarySearch(address, &name);
  }
  return name;
}

int Profiler::getNativeTrace(void *ucontext, ASGCT_CallFrame *frames,
                             int event_type, int tid, StackContext *java_ctx,
                             bool *truncated, int lock_index) {
  if (_cstack == CSTACK_NO ||
      (event_type == BCI_ALLOC || event_type == BCI_ALLOC_OUTSIDE_TLAB) ||
      (event_type != BCI_CPU && event_type != BCI_WALL &&
       _cstack == CSTACK_DEFAULT)) {
    return 0;
  }
  int max_depth = min(_max_stack_depth, MAX_NATIVE_FRAMES);
  const void *callchain[max_depth + 1]; // we can read one frame past when trying to figure out whether the result is truncated
  int native_frames = 0;

  if (event_type == BCI_CPU && _cpu_engine == &perf_events) {
    native_frames +=
        PerfEvents::walkKernel(tid, callchain + native_frames,
                               max_depth - native_frames, java_ctx);
  }
  if (_cstack >= CSTACK_VM) {
    return 0;
  } else if (_cstack == CSTACK_DWARF) {
    native_frames += StackWalker::walkDwarf(ucontext, callchain + native_frames,
                                            max_depth - native_frames,
                                            java_ctx, truncated);
  } else {
    native_frames += StackWalker::walkFP(ucontext, callchain + native_frames,
                                         max_depth - native_frames,
                                         java_ctx, truncated);
  }

  return convertNativeTrace(native_frames, callchain, frames, lock_index);
}

/**
 * Populates an ASGCT_CallFrame with remote symbolication data.
 *
 * Packs pc_offset, mark, and lib_index into the jmethodID field for deferred
 * symbol resolution during JFR serialization. This approach defers expensive
 * symbol lookups to post-processing while still capturing marks needed for
 * correct stack walk termination.
 *
 * @param frame The ASGCT_CallFrame to populate
 * @param pc The program counter address
 * @param lib The CodeCache library containing build-ID information
 * @param mark The mark value (0 for regular frames, non-zero for JVM internals)
 */
void Profiler::populateRemoteFrame(ASGCT_CallFrame* frame, uintptr_t pc, CodeCache* lib, char mark) {
  uintptr_t pc_offset = pc - (uintptr_t)lib->imageBase();
  uint32_t lib_index = (uint32_t)lib->libIndex();

  unsigned long packed = RemoteFramePacker::pack(pc_offset, mark, lib_index);

  TEST_LOG("populateRemoteFrame: lib=%s, build_id=%s, pc=0x%lx, pc_offset=0x%lx, mark=%d, lib_index=%u, packed=0x%zx",
           lib->name(), lib->buildId(), pc, pc_offset, (int)mark, lib_index, packed);

  frame->bci = BCI_NATIVE_FRAME_REMOTE;
  frame->packed_remote_frame = packed;

  // Track remote symbolication usage
  Counters::increment(REMOTE_SYMBOLICATION_FRAMES);
}

/**
 * Resolve native frame for upstream StackWalker (called from signal handler).
 * Returns resolution decision without writing to ASGCT_CallFrame.
 *
 * For remote symbolication with build-ID:
 * - Does symbol resolution to check marks (O(log n) binarySearch + O(1) mark check)
 * - Packs mark + lib_index + pc_offset into method_id field
 * - Returns is_marked=true if mark indicates termination (MARK_INTERPRETER, etc.)
 *
 * For traditional symbolication:
 * - Does symbol resolution via binarySearch() on the found library
 * - Checks marks after symbol resolution (same O(log n) + O(1) cost)
 * - If no symbol found but PC is in a known library, packs as
 *   BCI_NATIVE_FRAME_REMOTE for library-relative rendering ([lib+0xoffset])
 */
Profiler::NativeFrameResolution Profiler::resolveNativeFrameForWalkVM(uintptr_t pc, int lock_index) {
  CodeCache* lib = _libs->findLibraryByAddress((void*)pc);

  if (_remote_symbolication && lib != nullptr && lib->hasBuildId()) {
    // Get symbol name and check mark
    const char *method_name = nullptr;
    lib->binarySearch((void*)pc, &method_name);
    char mark = (method_name != nullptr) ? NativeFunc::read_mark(method_name) : 0;

    if (mark != 0) {
      return {nullptr, BCI_NATIVE_FRAME, true};  // Marked - stop processing
    }

    // Pack remote symbolication data using utility struct
    uintptr_t pc_offset = pc - (uintptr_t)lib->imageBase();
    uint32_t lib_index = (uint32_t)lib->libIndex();
    unsigned long packed = RemoteFramePacker::pack(pc_offset, mark, lib_index);

    return NativeFrameResolution(packed, BCI_NATIVE_FRAME_REMOTE, false);
  }

  // Traditional symbol resolution
  const char *method_name = nullptr;
  if (lib != nullptr) {
    lib->binarySearch((void*)pc, &method_name);
  }
  if (method_name != nullptr && NativeFunc::is_marked(method_name)) {
    return NativeFrameResolution(nullptr, BCI_NATIVE_FRAME, true);
  }

  // No symbol but known library: pack for library-relative identification.
  // Reuses BCI_NATIVE_FRAME_REMOTE encoding; resolveMethod() in flightRecorder.cpp
  // distinguishes remote vs local rendering via hasBuildId() && isRemoteSymbolication().
  if (method_name == nullptr && lib != nullptr) {
    uintptr_t pc_offset = pc - (uintptr_t)lib->imageBase();
    uint32_t lib_index = (uint32_t)lib->libIndex();
    unsigned long packed = RemoteFramePacker::pack(pc_offset, 0, lib_index);
    return NativeFrameResolution(packed, BCI_NATIVE_FRAME_REMOTE, false);
  }

  return NativeFrameResolution(method_name, BCI_NATIVE_FRAME, false);
}

/**
 * Converts a native callchain to ASGCT_CallFrame array.
 *
 * For libraries with build-IDs, uses remote symbolication (deferred resolution).
 * For libraries without build-IDs, performs traditional symbol resolution.
 *
 * In both cases, performs symbol resolution via binarySearch() to check for
 * marked frames (JVM internals) that should terminate the stack walk.
 */
int Profiler::convertNativeTrace(int native_frames, const void **callchain,
                                 ASGCT_CallFrame *frames, int lock_index) {
  int depth = 0;
  void* prev_identifier = NULL;  // Can be jmethodID or frame pointer for remote

  for (int i = 0; i < native_frames; i++) {
    uintptr_t pc = (uintptr_t)callchain[i];

    // Try remote symbolication first if enabled
    if (_remote_symbolication) {
      CodeCache* lib = _libs->findLibraryByAddress((void*)pc);
      if (lib != nullptr && lib->hasBuildId()) {
        // Check for marked frames via symbol resolution
        // binarySearch() returns symbol name, then we check mark (O(1))
        const char *method_name = nullptr;
        lib->binarySearch((void*)pc, &method_name);
        char mark = (method_name != nullptr) ? NativeFunc::read_mark(method_name) : 0;

        if (mark != 0) {
          // Terminate scan at marked frame
          return depth;
        }

        // Populate remote frame inline - no allocation needed!
        // Pass the mark we already retrieved to avoid duplicate binarySearch
        populateRemoteFrame(&frames[depth], pc, lib, mark);

        // Use frame address as identifier for duplicate detection
        void* current_identifier = (void*)&frames[depth];
        if (current_identifier != prev_identifier || _cstack != CSTACK_LBR) {
          prev_identifier = current_identifier;
          depth++;
        }
        continue;
      }
    }

    // Fallback: Traditional symbol resolution
    const char *method_name = findNativeMethod((void*)pc);
    if (method_name != nullptr && NativeFunc::is_marked(method_name)) {
      // Terminate scan at marked frame
      return depth;
    }

    // Store standard frame
    jmethodID current_method = (jmethodID)method_name;
    if (current_method == prev_identifier && _cstack == CSTACK_LBR) {
      prev_identifier = NULL;
    } else if (current_method != NULL) {
      frames[depth].bci = BCI_NATIVE_FRAME;
      frames[depth].method_id = current_method;
      prev_identifier = current_method;
      depth++;
    }
  }

  return depth;
}

u64 Profiler::recordJVMTISample(u64 counter, int tid, jthread thread, jint event_type, Event *event, bool deferred) {
  // Protect JVMTI sampling operations to prevent signal handler interference
  CriticalSection cs;
  atomicIncRelaxed(_total_samples);

  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    // Too many concurrent signals already
    atomicIncRelaxed(_failures[-ticks_skipped]);

    return 0;
  }
  u64 call_trace_id = 0;
  if (!_omit_stacktraces) {
    // Defensive: the buffer slot can be observed as nullptr in pathological
    // start sequences (e.g. a calloc failure path in Profiler::start before
    // engines are enabled). Drop the sample rather than dereferencing.
    CallTraceBuffer *buf = _calltrace_buffer[lock_index];
    if (buf == nullptr) {
      atomicIncRelaxed(_failures[-ticks_skipped]);
      _locks[lock_index].unlock();
      return 0;
    }
#ifdef COUNTERS
    u64 startTime = TSC::ticks();
#endif // COUNTERS
    ASGCT_CallFrame *frames = buf->_asgct_frames;
    jvmtiFrameInfo *jvmti_frames = buf->_jvmti_frames;

    int num_frames = 0;

    if (VM::jvmti()->GetStackTrace(thread, 0, _max_stack_depth, jvmti_frames, &num_frames) == JVMTI_ERROR_NONE && num_frames > 0) {
      // Convert to AsyncGetCallTrace format.
      // Note: jvmti_frames and frames may overlap.
      for (int i = 0; i < num_frames; i++) {
        jint bci = jvmti_frames[i].location;
        jmethodID mid = jvmti_frames[i].method;
        frames[i].method_id = mid;
        frames[i].bci = bci;
        // see https://github.com/async-profiler/async-profiler/pull/1090
        LP64_ONLY(frames[i].padding = 0;)
      }
      // On JDK 21+, GetStackTrace on a virtual thread returns only the VT's
      // logical stack; it stops at the continuation boundary and never includes
      // carrier-thread frames.  Without a synthetic root the trace appears
      // truncated to the UI backend, which attributes it to "Missing Frames".
      // Detect the VT case via JavaThread::_cont_entry being non-null on the
      // carrier.  This field is in gHotSpotVMStructs on all JDK 21+ builds so
      // isCarryingVirtualThread() works regardless of JDK version.  Append a
      // synthetic "JVM Continuation" root frame to mark the boundary
      // explicitly, matching the behaviour of walkVM without carrier_frames.
      if (VM::isHotspot() && VM::hotspot_version() >= 21 &&
          num_frames < _max_stack_depth) {
        VMThread* carrier = VMThread::current();
        if (carrier != nullptr && carrier->isCarryingVirtualThread()) {
          frames[num_frames].bci = BCI_NATIVE_FRAME;
          frames[num_frames].method_id = (jmethodID) "JVM Continuation";
          LP64_ONLY(frames[num_frames].padding = 0;)
          num_frames++;
        }
      }
    }

    call_trace_id = _call_trace_storage.put(num_frames, frames, false, counter);
#ifdef COUNTERS
    u64 duration = TSC::ticks() - startTime;
    if (duration > 0) {
      Counters::increment(UNWINDING_TIME_JVMTI, duration);
    }
#endif // COUNTERS
  }
  if (!deferred) {
    setWallSampleIdIfNeeded(event_type, event);
    _jfr.recordEvent(lock_index, tid, call_trace_id, event_type, event);
  }

  _locks[lock_index].unlock();
  return call_trace_id;
}

void Profiler::recordDeferredSample(int tid, u64 call_trace_id, jint event_type, Event *event) {
  atomicIncRelaxed(_total_samples);

  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    // Too many concurrent signals already
    atomicIncRelaxed(_failures[-ticks_skipped]);
    return;
  }

  setWallSampleIdIfNeeded(event_type, event);
  _jfr.recordEvent(lock_index, tid, call_trace_id, event_type, event);

  _locks[lock_index].unlock();
}

bool Profiler::recordSample(void *ucontext, u64 counter, int tid,
                            jint event_type, u64 call_trace_id, Event *event,
                            u64 *recorded_call_trace_id) {
  atomicIncRelaxed(_total_samples);

  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    // Too many concurrent signals already
    atomicIncRelaxed(_failures[-ticks_skipped]);

    if (event_type == BCI_CPU && _cpu_engine == &perf_events) {
      // Need to reset PerfEvents ring buffer, even though we discard the
      // collected trace
      PerfEvents::resetBuffer(tid);
    }
    return false;
  }

  bool truncated = false;
  // in lightweight mode we're just sampling the the context associated with the
  // passage of CPU or wall time, we use the same event definitions but we
  // record a null stacktrace we can skip the unwind if we've got a
  // call_trace_id determined to be reusable at a higher level

  if (!_omit_stacktraces && call_trace_id == 0) {
#ifdef COUNTERS
    u64 startTime = TSC::ticks();
#endif // COUNTERS
    ASGCT_CallFrame *frames = _calltrace_buffer[lock_index]->_asgct_frames;

    int num_frames = 0;

    StackContext java_ctx = {0};
    ASGCT_CallFrame *native_stop = frames + num_frames;
    num_frames += getNativeTrace(ucontext, native_stop, event_type, tid,
                                 &java_ctx, &truncated, lock_index);
    assert(num_frames >= 0);

    int max_remaining = _max_stack_depth - num_frames;
    if (max_remaining > 0) {
      StackWalkRequest request = {event_type, lock_index, ucontext, frames + num_frames, max_remaining, &java_ctx, &truncated};
      num_frames += JVMSupport::walkJavaStack(request);
    }
  
    assert(num_frames >= 0);
    if (num_frames == 0) {
      num_frames += makeFrame(frames + num_frames, BCI_ERROR, "no_Java_frame");
    }

    call_trace_id =
        _call_trace_storage.put(num_frames, frames, truncated, counter);
    ProfiledThread *thread = ProfiledThread::currentSignalSafe();
    if (thread != nullptr) {
      thread->recordCallTraceId(call_trace_id);
    }
#ifdef COUNTERS
    u64 duration = TSC::ticks() - startTime;
    if (duration > 0) {
      Counters::increment(UNWINDING_TIME_ASYNC, duration);
    }
#endif // COUNTERS
  }
  setWallSampleIdIfNeeded(event_type, event);
  if (event_type == BCI_WALL) {
    static_cast<ExecutionEvent *>(event)->_call_trace_id = call_trace_id;
  }
  bool recorded = _jfr.recordEvent(lock_index, tid, call_trace_id, event_type, event);
  if (recorded && recorded_call_trace_id != nullptr) {
    *recorded_call_trace_id = call_trace_id;
  }

  _locks[lock_index].unlock();
  return recorded;
}

bool Profiler::recordSampleDelegated(void *ucontext, u64 weight, int tid,
                                     jint event_type, Event *event) {
  if (!VM::canRequestStackTrace()) {
    return false;
  }

  // Reserve the correlation ID up-front so we can pass the same value to the
  // JVM (as user_data) and to our own event.
  u64 correlation_id = atomicIncRelaxed(_sample_seq);

  Counters::increment(JVMTI_STACKS_REQUESTED);
  jvmtiError rc = VM::requestStackTrace(ucontext, (jlong)correlation_id);
  if (rc != JVMTI_ERROR_NONE) {
    if (rc == JVMTI_ERROR_WRONG_PHASE) {
      Counters::increment(JVMTI_STACKS_FAILED_WRONG_PHASE);
    } else {
      Counters::increment(JVMTI_STACKS_FAILED_OTHER);
    }
    return false;
  }

  atomicIncRelaxed(_total_samples);
  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    atomicIncRelaxed(_failures[-ticks_skipped]);
    Counters::increment(JVMTI_STACKS_DROPPED_LOCK);
    // The JVM-side stack trace request is already in flight; we just drop our
    // sample event. The dangling StackTraceRequest entry in the JVM recording
    // will simply have no matching datadog event, which is harmless.
    return false;
  }

  setWallSampleIdIfNeeded(event_type, event);
  if (event_type == BCI_WALL) {
    static_cast<ExecutionEvent *>(event)->_correlation_id = correlation_id;
  }
  bool recorded =
      _jfr.recordEventDelegated(lock_index, tid, correlation_id, event_type, event);
  _locks[lock_index].unlock();
  return recorded;
}

void Profiler::recordWallClockEpoch(int tid, WallClockEpochEvent *event) {
  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    return;
  }
  _jfr.wallClockEpoch(lock_index, event);
  _locks[lock_index].unlock();
}

void Profiler::recordTraceRoot(int tid, TraceRootEvent *event) {
  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    return;
  }
  _jfr.recordTraceRoot(lock_index, tid, event);
  _locks[lock_index].unlock();
}

void Profiler::recordQueueTime(int tid, QueueTimeEvent *event) {
  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    return;
  }
  _jfr.recordQueueTime(lock_index, tid, event);
  _locks[lock_index].unlock();
}

bool Profiler::recordTaskBlockLive(int tid, TaskBlockEvent *event) {
  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    return false;
  }
  bool recorded = _jfr.recordTaskBlock(lock_index, tid, event);
  _locks[lock_index].unlock();
  return recorded;
}

bool Profiler::recordTaskBlockAsync(int tid, TaskBlockEvent *event) {
  if (!_task_block_drain_running.load(std::memory_order_acquire)) {
    Counters::increment(TASK_BLOCK_QUEUE_DROPPED);
    return false;
  }

  QueuedTaskBlockEvent queued;
  queued.tid = tid;
  queued.generation = _task_block_generation.load(std::memory_order_acquire);
  queued.event = *event;
  if (!_task_block_queue.tryPush(queued)) {
    Counters::increment(TASK_BLOCK_QUEUE_DROPPED);
    return false;
  }
  return true;
}

void Profiler::recordExternalSample(u64 weight, int tid, int num_frames,
                                    ASGCT_CallFrame *frames, bool truncated,
                                    jint event_type, Event *event) {
  // Protect external sampling operations to prevent signal handler interference
  CriticalSection cs;
  atomicIncRelaxed(_total_samples);

  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    atomicIncRelaxed(_failures[-ticks_skipped]);
    return;
  }

  CallTraceBuffer *buf = _calltrace_buffer[lock_index];
  if (buf == nullptr) {
    atomicIncRelaxed(_failures[-ticks_skipped]);
    _locks[lock_index].unlock();
    return;
  }
  // External samplers (like ObjectSampler) provide standard frames only
  ASGCT_CallFrame *extended_frames = buf->_asgct_frames;
  for (int i = 0; i < num_frames; i++) {
    extended_frames[i] = frames[i];
  }

  u64 call_trace_id =
      _call_trace_storage.put(num_frames, extended_frames, truncated, weight);
  setWallSampleIdIfNeeded(event_type, event);
  _jfr.recordEvent(lock_index, tid, call_trace_id, event_type, event);

  _locks[lock_index].unlock();
}

void Profiler::writeLog(LogLevel level, const char *message) {
  _jfr.recordLog(level, message, strlen(message));
}

void Profiler::writeLog(LogLevel level, const char *message, size_t len) {
  _jfr.recordLog(level, message, len);
}

void Profiler::writeDatadogProfilerSetting(int tid, int length,
                                           const char *name, const char *value,
                                           const char *unit) {
  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    return;
  }
  _jfr.recordDatadogSetting(lock_index, length, name, value, unit);
  _locks[lock_index].unlock();
}

void Profiler::writeHeapUsage(long value, bool live) {
  int tid = ProfiledThread::currentTid();
  if (tid < 0) {
    return;
  }
  u32 lock_index = getLockIndex(tid);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    return;
  }
  _jfr.recordHeapUsage(lock_index, value, live);
  _locks[lock_index].unlock();
}

void Profiler::prewarmUnwinder() {
#ifdef __linux__
  // J9 on aarch64 (and other JVMs) lazily loads libgcc_s.so.1 from its DWARF
  // unwinder during stack walks. When that happens inside a signal handler
  // frame, our dlopen_hook fires from signal context and tries to refresh the
  // library list — Mutex::lock and malloc on a signal stack.  By forcing the
  // load here, before any signal handler is installed, subsequent calls find
  // libgcc_s already mapped and the lazy-load path never runs.
  //
  // The handle is intentionally leaked: keeping the refcount > 0 prevents the
  // library from being unmapped for the remainder of the process lifetime.
  //
  // SONAME note: "libgcc_s.so.1" is hardcoded deliberately. Referencing
  // _Unwind_Backtrace from C++ would normally let the linker resolve the
  // SONAME implicitly, but our release build uses -static-libgcc
  // (ConfigurationPresets.kt: "-static-libgcc"), which embeds the unwinder
  // into libjavaProfiler.so and removes libgcc_s.so from our NEEDED entries
  // — so a symbol reference would not trigger the shared-library load.
  // dlopen by SONAME is the only mechanism that works under static-libgcc.
  // libgcc_s.so.1 has been the stable SONAME since 2002; a bump would
  // constitute a glibc/GCC C++ ABI break and is treated as a fixed contract.
  (void)dlopen("libgcc_s.so.1", RTLD_LAZY | RTLD_GLOBAL);
#endif
}

void *Profiler::dlopen_hook(const char *filename, int flags) {
  void *result = dlopen(filename, flags);

  if (result != NULL) {
    if (!isInTrackedSignalContext()) {
      // Either confirmed non-signal context, or no ProfiledThread on this
      // thread (uninstrumented JVM internals — VM Thread, JIT, GC).  We
      // prefer synchronous refresh for the null-PT case too because (a)
      // those threads call dlopen synchronously during normal JVM
      // operation, and (b) wasmtime's broken sigaction patching depends
      // on switchLibraryTrap running its work inline (the original reason
      // for the trap).  The residual risk — an uninstrumented thread
      // calling dlopen from inside a foreign signal handler — is small:
      // prewarmUnwinder() closes the known libgcc_s lazy-load case, and
      // mainstream JVM signal handlers are AS-safe by design.
      Libraries::instance()->refresh();
    } else {
      // Confirmed signal context (one of our SignalHandlerScopes is on
      // the stack).  refresh() must NOT run here — parseLibraries
      // acquires a Mutex and calls malloc, both AS-unsafe.  Mark the
      // library set dirty; the Libraries refresher thread picks it up
      // within REFRESH_INTERVAL_NS (500 ms).
      Libraries::instance()->markDirty();
    }
  }

  return result;
}

const char* Profiler::cstack() const {
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

void Profiler::switchLibraryTrap(bool enable) {
  if (_dlopen_entry == NULL) {
    return;  // Not initialized yet, nothing to do
  }
  void *impl = enable ? (void *)dlopen_hook : (void *)dlopen;
  __atomic_store_n(_dlopen_entry, impl, __ATOMIC_RELEASE);
}

void Profiler::enableEngines() {
  _cpu_engine->enableEvents(true);
  _wall_engine->enableEvents(true);
}

void Profiler::disableEngines() {
  _cpu_engine->enableEvents(false);
  _wall_engine->enableEvents(false);
}

void Profiler::segvHandler(int signo, siginfo_t *siginfo, void *ucontext) {
  // J9 installs a SIGSEGV handler that uses siglongjmp() to recover from
  // null-pointer-check faults during normal Java execution.  When we chain to
  // it, that longjmp unwinds past our stack frame and skips the RAII
  // destructor, permanently leaking depth on the thread.  Release the guard
  // before chaining so depth is correct whether the chained handler returns
  // or longjmps.
  //
  // Sanitizer-coverage note: this also means depth == 0 inside the chained
  // handler, so DEBUG_ASSERT_NOT_IN_SIGNAL() will NOT fire for AS-unsafe
  // code reachable from a chained handler that returns normally.  This is
  // the lesser of two evils — leaking depth on longjmp would silently
  // break the production deferred-refresh gate, while the sanitizer gap
  // is bounded to third-party signal handler code we don't own.
  SIGNAL_HANDLER_GUARD();
  if (crashHandlerInternal(signo, siginfo, ucontext)) {
    return;  // Handled — destructor decrements depth
  }
  SIGNAL_HANDLER_GUARD_RELEASE();
  // Not handled, chain to next handler (may longjmp; never return through us)
  SigAction chain = OS::getSegvChainTarget();
  if (chain != nullptr) {
    chain(signo, siginfo, ucontext);
  } else if (orig_segvHandler != nullptr) {
    orig_segvHandler(signo, siginfo, ucontext);
  }
}

void Profiler::busHandler(int signo, siginfo_t *siginfo, void *ucontext) {
  // See segvHandler: release before chaining in case the chained handler
  // longjmps through us.
  SIGNAL_HANDLER_GUARD();
  if (crashHandlerInternal(signo, siginfo, ucontext)) {
    return;  // Handled — destructor decrements depth
  }
  SIGNAL_HANDLER_GUARD_RELEASE();
  // Not handled, chain to next handler
  SigAction chain = OS::getBusChainTarget();
  if (chain != nullptr) {
    chain(signo, siginfo, ucontext);
  } else if (orig_busHandler != nullptr) {
    orig_busHandler(signo, siginfo, ucontext);
  }
}

// Returns: 0 = not handled (chain to next handler), non-zero = handled
int Profiler::crashHandlerInternal(int signo, siginfo_t *siginfo, void *ucontext) {
  ProfiledThread* thrd = ProfiledThread::currentSignalSafe();

  // First, try to handle safefetch - this doesn't need TLS or any protection
  // because it directly checks the PC and modifies ucontext to skip the fault.
  // This must be checked first before any reentrancy checks.
  if (SafeAccess::handle_safefetch(signo, ucontext)) {
    return 1;  // handled
  }

  // Reentrancy protection: use TLS-based tracking if available.
  // If TLS is not available, we can only safely handle faults that we can
  // prove are from our protected code paths (checked via sameStack heuristic
  // in HotspotSupport::checkFault). For anything else, we must chain immediately
  // to avoid claiming faults that aren't ours.
  bool have_tls_protection = false;
  if (thrd != nullptr) {
    if (!thrd->enterCrashHandler()) {
      // we are already in a crash handler; don't recurse!
      return 0;  // not handled, safe to chain
    }
    have_tls_protection = true;
  }
  // If thrd == nullptr, we proceed but with limited handling capability.
  // Only HotspotSupport::checkFault (which has its own sameStack fallback)
  // and the JDK-8313796 workaround can safely handle faults without TLS.

  StackFrame frame(ucontext);
  uintptr_t pc = frame.pc();

  uintptr_t fault_address = (uintptr_t)siginfo->si_addr;
  if (pc == fault_address) {
    // it is 'pc' that is causing the fault; can not access it safely
    if (have_tls_protection) {
      thrd->exitCrashHandler();
    }
    return 0;  // not handled, safe to chain
  }

  if (WX_MEMORY && Trap::isFaultInstruction(pc)) {
    if (have_tls_protection) {
      thrd->exitCrashHandler();
    }
    return 1;  // handled
  }

  if (VM::isHotspot()) {
    // the following checks require vmstructs and therefore HotSpot

    // HotspotSupport::checkFault has its own fallback for when TLS is unavailable:
    // it uses sameStack() heuristic to check if we're in a protected stack walk.
    // If the fault is from our protected walk, it will longjmp and never return.
    // If it returns, the fault wasn't from our code.
    HotspotSupport::checkFault(thrd);

    // Workaround for JDK-8313796 if needed. Setting cstack=dwarf also helps
    if (_need_JDK_8313796_workaround &&
        VMStructs::isInterpretedFrameValidFunc((const void *)pc) &&
        frame.skipFaultInstruction()) {
      if (have_tls_protection) {
        thrd->exitCrashHandler();
      }
      return 1;  // handled
    }
  }

  if (have_tls_protection) {
    thrd->exitCrashHandler();
  }
  return 0;  // not handled, safe to chain
}

void Profiler::setupSignalHandlers() {
  // Do not re-run the signal setup (run only when VM has not been loaded yet)
  if (__sync_bool_compare_and_swap(&_signals_initialized, false, true)) {
      if (VM::isHotspot() || VM::isOpenJ9()) {
        // HotSpot and J9 tolerate interposed SIGSEGV/SIGBUS handler; other JVMs probably not
        // IMPORTANT: protectSignalHandlers must be called BEFORE replaceSigsegvHandler so that
        // the original (JVM's) handlers are saved before we install ours. This way, when we
        // intercept other libraries' sigaction calls and return oldact, we return the JVM's
        // handler (not ours), preventing infinite chaining loops.
        OS::protectSignalHandlers(segvHandler, busHandler);
        orig_segvHandler = OS::replaceSigsegvHandler(segvHandler);
        orig_busHandler = OS::replaceSigbusHandler(busHandler);
        // Patch sigaction GOT in libraries with broken signal handlers (already loaded)
        LibraryPatcher::patch_sigaction();
      }
  }
}


/**
 * Update thread name for the given thread
 */
void Profiler::updateThreadName(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                                bool self) {
  JitWriteProtection jit(true); // workaround for JDK-8262896
  jvmtiThreadInfo thread_info;
  int native_thread_id = -1;

  if (self) {
    // if updating the current thread, use the native thread id from the
    // ProfilerThread, it is faster and safer.
    native_thread_id = ProfiledThread::currentTid();
    assert(native_thread_id != -1);
  } else {
    native_thread_id = JVMThread::nativeThreadId(jni, thread);
    if (jni->ExceptionCheck()) {
      jni->ExceptionClear();
    }
  }

  if (native_thread_id >= 0 &&
    jvmti->GetThreadInfo(thread, &thread_info) == 0) {
    jlong java_thread_id = JVMThread::javaThreadId(jni, thread);
    _thread_info.set(native_thread_id, thread_info.name, java_thread_id);
    jvmti->Deallocate((unsigned char *)thread_info.name);
  }
}

void Profiler::updateJavaThreadNames() {
  jvmtiEnv *jvmti = VM::jvmti();
  jint thread_count;
  jthread *thread_objects;
  if (jvmti->GetAllThreads(&thread_count, &thread_objects) != 0) {
    return;
  }

  JNIEnv *jni = VM::jni();
  for (int i = 0; i < thread_count; i++) {
    if (thread_objects[i] == nullptr) {
      continue;
    }
    updateThreadName(jvmti, jni, thread_objects[i]);
    jni->DeleteLocalRef(thread_objects[i]);
  }

  jvmti->Deallocate((unsigned char *)thread_objects);
}

void Profiler::updateNativeThreadNames(bool defer_initializing) {
  ThreadList *thread_list = OS::listThreads();
  constexpr size_t buffer_size = 64;
  char name_buf[buffer_size];  // Stack-allocated buffer

  // A freshly cloned thread inherits the creating thread's comm until it sets
  // its own name; for the threads we want here that creator is typically the
  // main thread, so the inherited name is the process name. When deferring, we
  // skip recording it and let a later pass capture the final name.
  char proc_name[buffer_size];
  bool have_proc_name =
      defer_initializing && OS::threadName(OS::processId(), proc_name, buffer_size);

  while (thread_list->hasNext()) {
    int tid = thread_list->next();
    _thread_info.updateThreadName(
        tid, [&](int tid) -> std::string {
          if (OS::threadName(tid, name_buf, buffer_size)) {
            // Skip a thread still showing the inherited process name: it is
            // probably mid-initialization. Recording it would latch a
            // provisional name (updateThreadName is first-writer-wins).
            if (have_proc_name && strcmp(name_buf, proc_name) == 0) {
              return std::string();
            }
            // name_buf is NUL-terminated by OS::threadName; let
            // std::string find the length rather than storing the
            // full 64-byte buffer (NUL + trailing garbage).
            return std::string(name_buf);
          }
          return std::string();
        });
  }

  delete thread_list;
}

Engine *Profiler::selectCpuEngine(Arguments &args) {
  if (args._cpu < 0 &&
      (args._event == NULL || strcmp(args._event, EVENT_NOOP) == 0)) {
    return &noop_engine;
  } else if (args._cpu >= 0 || strcmp(args._event, EVENT_CPU) == 0) {
    if (VM::isOpenJ9()) {
      if (!J9Support::shouldUseAsgct() || !J9Support::can_use_ASGCT()) {
        if (!J9Support::is_jvmti_jmethodid_safe()) {
          LOG_WARN("Safe jmethodID access is not available on this JVM. Using "
                    "CPU profiler on your own risk. Use -XX:+KeepJNIIDs=true JVM "
                    "flag to make access to jmethodIDs safe, if your JVM supports it");
        }
        TEST_LOG("J9[cpu]=jvmti");
        return &j9_engine;
      }
      TEST_LOG("J9[cpu]=asgct");
    }
    // Prefer the JVMTI JFR-delegated engine when the HotSpot extension is
    // available and the user opted into jvmtistacks.  On Linux, CTimerJvmti
    // uses per-thread CPU timers.  On other platforms (e.g. macOS) it is not
    // supported, so fall back to ITimerJvmti which uses setitimer(ITIMER_PROF).
    if (args._jvmtistacks) {
      if (!ctimer_jvmti.check(args)) {
        TEST_LOG("HS[cpu]=ctimer_jvmti");
        return &ctimer_jvmti;
      }
      if (!itimer_jvmti.check(args)) {
        TEST_LOG("HS[cpu]=itimer_jvmti");
        return &itimer_jvmti;
      }
      Log::warn("jvmtistacks requested but no JVMTI CPU engine is available; falling back to ASGCT");
    }
    return !ctimer.check(args)
               ? (Engine *)&ctimer
               : (!perf_events.check(args) ? (Engine *)&perf_events
                                           : (Engine *)&itimer);
  } else if (strcmp(args._event, EVENT_WALL) == 0) {
    return &noop_engine;
  } else if (strcmp(args._event, EVENT_ITIMER) == 0) {
    return &itimer;
  } else if (strcmp(args._event, EVENT_CTIMER) == 0) {
    return &ctimer;
  } else {
    return &perf_events;
  }
}

Engine *Profiler::selectWallEngine(Arguments &args) {
  if (args._wall < 0 &&
      (args._event == NULL || strcmp(args._event, EVENT_WALL) != 0)) {
    return &noop_engine;
  }
  if (VM::isOpenJ9()) {
    if (args._wallclock_sampler == JVMTI || !J9Support::shouldUseAsgct() || !J9Support::can_use_ASGCT()) {
      if (!J9Support::is_jvmti_jmethodid_safe()) {
        LOG_WARN("Safe jmethodID access is not available on this JVM. Using "
                  "wallclock profiler on your own risk. Use -XX:+KeepJNIIDs=true JVM "
                  "flag to make access to jmethodIDs safe, if your JVM supports it");
      }
      j9_engine.sampleIdleThreads();
      TEST_LOG("J9[wall]=jvmti");
      return (Engine *)&j9_engine;
    } else {
      TEST_LOG("J9[wall]=asgct");
      return (Engine *)&wall_asgct_engine;
    }
  }
  // jvmtistacks overrides _wallclock_sampler when the HotSpot extension is available.
  if (args._jvmtistacks && VM::canRequestStackTrace()) {
    TEST_LOG("HS[wall]=jvmti");
    return (Engine *)&wall_jvmti_engine;
  }
  switch (args._wallclock_sampler) {
        case JVMTI:
            fprintf(stderr, "[ddprof] [WARN] JVMTI wallclock is not available on this JVM, fallback to ASGCT wallclock\n");
            [[fallthrough]];
        case ASGCT:
        default:
            return (Engine*)&wall_asgct_engine;
    }
}

Engine *Profiler::selectAllocEngine(Arguments &args) {
  if (VM::canSampleObjects()) {
    return static_cast<Engine *>(ObjectSampler::instance());
  } else {
    Log::info("Not enabling the alloc profiler, SampledObjectAlloc is not "
              "supported on this JVM");
    return &noop_engine;
  }
}

Error Profiler::checkJvmCapabilities() {
  if (!JVMThread::isInitialized()) {
    return Error("Could not find JVMThread bridge. Unsupported JVM?");
  }

  if (!JVMThread::hasJavaThreadId()) {
    return Error("Could not find Thread ID field. Unsupported JVM?");
  }

  if (VM::isUseAdaptiveGCBoundarySet()) {
    return Error(
        "The user has explicitly set -XX:+UseAdaptiveGCBoundary so the "
        "profiler has been disabled to avoid the risk of crashing.");
  }

  if (_dlopen_entry == NULL) {
    CodeCache *lib = _libs->findJvmLibrary("libj9prt");
    if (lib == NULL || (_dlopen_entry = lib->findImport(im_dlopen)) == NULL) {
      return Error("Could not set dlopen hook. Unsupported JVM?");
    }
  }

  if (!VMStructs::libjvm()->hasDebugSymbols() && !VM::isOpenJ9()) {
    Log::warn("Install JVM debug symbols to improve profile accuracy");
  }

  return Error::OK;
}

void Profiler::check_JDK_8313796_workaround() {
  int java_version = VM::java_version();
  int java_update_version = VM::java_update_version();

  // JDK-8313796 has been fixed in JDK 22 and backported to
  // JDK versions 11.0.21, 17.0.9 and 21.0.1
  bool fixed_version = java_version >= 22 ||
                         (java_version == 11 && java_update_version >= 21) ||
                         (java_version == 17 && java_update_version >= 9) ||
                         (java_version == 21 && java_update_version >= 1);
    _need_JDK_8313796_workaround = !fixed_version;
}


Error Profiler::start(Arguments &args, bool reset) {
  MutexLocker ml(_state_lock);
  if (state() > IDLE) {
    return Error("Profiler already started");
  }

  // Force libgcc_s to load now (idempotent dlopen) so the JVM's DWARF
  // unwinder cannot lazy-load it later from signal context.
  prewarmUnwinder();

  Error error = checkJvmCapabilities();
  if (error) {
    return error;
  }

  _omit_stacktraces = args._lightweight;
  _remote_symbolication = args._remote_symbolication;
  _libs->setRemoteSymbolication(_remote_symbolication);
  _wall_precheck = args._wall_precheck;
  _event_mask =
      ((args._event != NULL && strcmp(args._event, EVENT_NOOP) != 0) ? EM_CPU
                                                                     : 0) |
      (args._cpu >= 0 ? EM_CPU : 0) | (args._wall >= 0 ? EM_WALL : 0) |
      (args._record_allocations || args._record_liveness || args._gc_generations
           ? EM_ALLOC
           : 0) |
      (args._nativemem >= 0 ? EM_NATIVEMEM : 0) |
      (args._nativesocket ? EM_NATIVESOCKET : 0);

  if (_event_mask == 0) {
    return Error("No profiling events specified");
  }

  // Commit _features before the reset block so any signal-handler code that
  // reads _features.* observes the correct enabled state once profiling
  // engines start.
  _features = args._features;
  if (VM::hotspot_version() < 8) {
      _features.java_anchor = 0;
      _features.gc_traces = 0;
  }
  if (!VMStructs::hasClassNames()) {
      _features.vtable_target = 0;
  }
  if (!VMStructs::hasCompilerStructs()) {
      _features.comp_task = 0;
  }

  if (reset || _start_time == 0) {
    // Reset counters. _sample_seq is intentionally not reset: it is a
    // monotonically increasing uniqueness generator for correlation IDs and
    // must not repeat values across recording sessions.
    _total_samples = 0;
    memset(_failures, 0, sizeof(_failures));

    // Reset dictionaries. StringDictionary::clearAll() manages its own
    // synchronisation (RefCountGuard drain). The exclusive _class_map_lock
    // additionally fences out shared-lock readers introduced by #527
    // (deferred vtable receiver resolution) so they cannot observe a
    // half-cleared class map.
    {
      ExclusiveLockGuard guard(&_class_map_lock);
      _class_map.clearAll();
    }
    _string_label_map.clearAll();
    _context_value_map.clearAll();

    // Reset call trace storage
    if (!_omit_stacktraces) {
      lockAll();
      _call_trace_storage.clear();
      unlockAll();
    }
    Counters::reset();
    WallClockCounters::reset();

    // Reset thread names and IDs
    _thread_info.clearAll();
  }

  // (Re-)allocate calltrace buffers
  if (_max_stack_depth != args._jstackdepth) {
    _max_stack_depth = args._jstackdepth;
    size_t nelem = _max_stack_depth + RESERVED_FRAMES;

    for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
      // Allocate the replacement before touching the slot so a calloc failure
      // does not leave the slot pointing at freed memory.
      CallTraceBuffer *fresh =
          (CallTraceBuffer*)calloc(nelem, sizeof(CallTraceBuffer));
      if (fresh == NULL) {
        _max_stack_depth = 0;
        return Error("Not enough memory to allocate stack trace buffers (try "
                     "smaller jstackdepth)");
      }
      // Swap under the per-shard lock: all readers (recordJVMTISample,
      // recordExternalSample) acquire this lock via tryLock before reading
      // _calltrace_buffer, so no reader can observe a freed pointer mid-replacement.
      _locks[i].lock();
      CallTraceBuffer *prev = _calltrace_buffer[i];
      _calltrace_buffer[i] = fresh;
      _locks[i].unlock();
      free(prev);
    }
  }

  // Remote symbolication is now inline in ASGCT_CallFrame
  // No separate pool allocation needed!

  _safe_mode = args._safe_mode;
  if (VM::hotspot_version() < 8 || VM::isZing()) {
    _safe_mode |= GC_TRACES | LAST_JAVA_PC;
  }

  // TODO: Current way of setting filter is weird with the recent changes
  _thread_filter.init(args._filter ? args._filter : "0");
  
  // Minor optim: Register the current thread (start thread won't be called)
  if (_thread_filter.enabled()) {
    _thread_filter.clearActive();
    ProfiledThread *current = ProfiledThread::current();
    assert(current != nullptr);
    int slot_id = current->filterSlotId();
    if (slot_id < 0) {
      slot_id = _thread_filter.registerThread();
      current->setFilterSlotId(slot_id);
    }
    _thread_filter.remove(slot_id);  // Remove from filtering initially (matches onThreadStart behavior)
  }

  _cpu_engine = selectCpuEngine(args);
  _wall_engine = selectWallEngine(args);
  _cstack = args._cstack;
  if (_cstack == CSTACK_DEFAULT) {
    if (VMStructs::hasStackStructs() && OS::isLinux()) {
      _cstack = CSTACK_VM;
    } else if (DWARF_SUPPORTED) {
      _cstack = CSTACK_DWARF;
    }
  }
  if (_cstack == CSTACK_DWARF && !DWARF_SUPPORTED) {
    _cstack = CSTACK_NO;
    Log::warn("DWARF unwinding is not supported on this platform. Defaulting "
              "to no native call stack unwinding.");
  } else if (_cstack == CSTACK_LBR && _cpu_engine != &perf_events) {
    _cstack = CSTACK_NO;
    Log::warn("Branch stack is supported only with PMU events");
  } else if (_cstack == CSTACK_VM) {
    if (!VMStructs::hasStackStructs()) {
      _cstack = DWARF_SUPPORTED ? CSTACK_DWARF : CSTACK_NO;
      Log::error("VMStructs stack walking is not supported on this JVM/platform, defaulting to the default native call stack unwinding mode.");
    }
  }

  LibraryPatcher::initialize();

  // Kernel symbols are useful only for perf_events without --all-user
  _libs->updateSymbols(_cpu_engine == &perf_events && (args._ring & RING_KERNEL));

  // Extract build-ids for remote symbolication if enabled
  if (_remote_symbolication) {
    _libs->updateBuildIds();
  }

  enableEngines();

  // Refresher must be running before the trap fires: dlopen_hook's
  // signal-context branch only marks dirty and relies on the refresher
  // to call refresh() within REFRESH_INTERVAL_NS (500 ms).
  _libs->startRefresher();

  // Always enable library trap to catch wasmtime loading and patch its broken sigaction
  switchLibraryTrap(true);

  JfrMetadata::reset();
  JfrMetadata::initialize(args._context_attributes);
  _num_context_attributes = args._context_attributes.size();
  error = _jfr.start(args, reset);
  if (error) {
    disableEngines();
    switchLibraryTrap(false);
    _libs->stopRefresher();
    return error;
  }
  initializeTaskBlockDurationThreshold();
  startTaskBlockDrain();
  if ((_event_mask & EM_WALL) && args._wall_precheck) {
    Error native_io_error = NativeSocketInterposer::instance()->start();
    if (native_io_error) {
      Log::warn("%s", native_io_error.message());
    }
  }

  int activated = 0;
  if ((_event_mask & EM_CPU) && _cpu_engine != &noop_engine) {
    error = _cpu_engine->start(args);
    if (error) {
      Log::warn("%s", error.message());
      error = Error::OK; // recoverable
    } else {
      activated |= EM_CPU;
    }
  }
  if ((_event_mask & EM_WALL) && _wall_engine != &noop_engine) {
    error = _wall_engine->start(args);
    if (error) {
      Log::warn("%s", error.message());
      error = Error::OK; // recoverable
    } else {
      activated |= EM_WALL;
    }
  }
  if (_event_mask & EM_ALLOC) {
    _alloc_engine = selectAllocEngine(args);
    if (_alloc_engine != &noop_engine) {
      error = _alloc_engine->start(args);
      if (error) {
        Log::warn("%s", error.message());
        error = Error::OK; // recoverable
      } else {
        activated |= EM_ALLOC;
      }
    }
  }
  if (_event_mask & EM_NATIVEMEM) {
    error = malloc_tracer.start(args);
    if (error) {
      Log::warn("%s", error.message());
      if (_event_mask == EM_NATIVEMEM) {
        // nativemem is the only requested mode: propagate the real error
        disableEngines();
        NativeSocketInterposer::instance()->stop();
        switchLibraryTrap(false);
        _libs->stopRefresher();
        stopTaskBlockDrain();
        lockAll();
        _jfr.stop();
        unlockAll();
        return error;
      }
      error = Error::OK; // recoverable when other modes are also active
    } else {
      activated |= EM_NATIVEMEM;
    }
  }
  if (_event_mask & EM_NATIVESOCKET) {
    error = NativeSocketSampler::instance()->start(args);
    if (error) {
      Log::warn("%s", error.message());
      error = Error::OK; // recoverable
    } else {
      activated |= EM_NATIVESOCKET;
    }
  }

  if (activated) {
    switchThreadEvents(JVMTI_ENABLE);

    // Initialize this thread
    // Note: passing all nullptrs results in not able to resolve the thread name here.
    //      However, the thread name will be updated later in updateJavaThreadNames().
    // TODO: find a better way to resolve the thread name.
    onThreadStart(nullptr, nullptr, nullptr);

    _state.store(RUNNING, std::memory_order_release);
    _start_time = time(NULL);
    __atomic_add_fetch(&_epoch, 1, __ATOMIC_RELAXED);
    return Error::OK;
  }
  // no engine was activated; perform cleanup
  disableEngines();
  NativeSocketInterposer::instance()->stop();
  switchLibraryTrap(false);
  _libs->stopRefresher();
  stopTaskBlockDrain();

  lockAll();
  _jfr.stop();
  unlockAll();

  return Error(
      "Neither CPU, wallclock nor allocation profiling could be started");
}

Error Profiler::stop() {
  MutexLocker ml(_state_lock);
  if (state() != RUNNING) {
    return Error("Profiler is not active");
  }

  disableEngines();

  if (_event_mask & EM_ALLOC)
    _alloc_engine->stop();
  if (_event_mask & EM_NATIVEMEM)
    malloc_tracer.stop();
  // Stop the refresher BEFORE socket unpatch: the refresher calls
  // install_socket_hooks() which re-reads _socket_active before acquiring the
  // patch lock.  If the refresher runs concurrently with unpatch_socket_functions()
  // it can see _socket_active=true, wait for the lock, then re-patch PLT slots
  // that unpatch just restored.  Stopping the refresher here closes that window.
  _libs->stopRefresher();
  if (_event_mask & EM_NATIVESOCKET)
    NativeSocketSampler::instance()->stop();
  if (_event_mask & EM_WALL)
    _wall_engine->stop();
  if (_event_mask & EM_CPU)
    _cpu_engine->stop();

  NativeSocketInterposer::instance()->stop();
  switchLibraryTrap(false);
  switchThreadEvents(JVMTI_DISABLE);
  Libraries::instance()->refresh();
  updateJavaThreadNames();
  updateNativeThreadNames();
  stopTaskBlockDrain();

  // If jvmtistacks delegation was used this recording, surface likely
  // misconfigurations. The JVM returns WRONG_PHASE when JFR is not recording
  // and NOT_AVAILABLE when JFR is recording but the StackTraceRequest event is
  // disabled. If the request was accepted the JVM will have written the
  // stack trace, so no warning is needed.
  if (VM::canRequestStackTrace()) {
    long long requested =
        Counters::getCounter(JVMTI_STACKS_REQUESTED);
    long long wrong_phase =
        Counters::getCounter(JVMTI_STACKS_FAILED_WRONG_PHASE);
    long long other =
        Counters::getCounter(JVMTI_STACKS_FAILED_OTHER);
    long long dropped_lock =
        Counters::getCounter(JVMTI_STACKS_DROPPED_LOCK);
    if (requested > 0 && wrong_phase * 2 >= requested) {
      fprintf(stderr,
              "[java-profiler] jvmtistacks: %lld of %lld stack-trace requests "
              "were rejected with WRONG_PHASE, so no async stack traces were "
              "emitted by the JVM. Start JFR (e.g. "
              "-XX:StartFlightRecording=...) before or as the profiler starts.\n",
              wrong_phase, requested);
    } else if (requested > 0 && other * 2 >= requested) {
      fprintf(stderr,
              "[java-profiler] jvmtistacks: %lld of %lld stack-trace requests "
              "were rejected with NOT_AVAILABLE. The jdk.StackTraceRequest event "
              "is likely disabled; enable it in the JFR configuration, e.g. "
              "-XX:StartFlightRecording=...,+jdk.StackTraceRequest#enabled=true.\n",
              other, requested);
    }
    if (dropped_lock > 0) {
      fprintf(stderr,
              "[java-profiler] jvmtistacks: %lld of %lld stack-trace requests "
              "were dropped due to lock contention; the corresponding "
              "jdk.StackTraceRequest events will have no matching profiler event.\n",
              dropped_lock, requested);
    }
  }

  // writing these out before stopping the JFR recording allows to report the
  // correct counts in the recording
  _thread_info.reportCounters();

  rotateDictsAndRun([&]{ _jfr.stop(); });

  // Unpatch libraries AFTER JFR serialization completes
  // Remote symbolication RemoteFrameInfo structs contain pointers to build-ID strings
  // owned by library metadata, so we must keep library patches active until after serialization
  LibraryPatcher::unpatch_libraries();

  _state.store(IDLE, std::memory_order_release);
  return Error::OK;
}

Error Profiler::check(Arguments &args) {
  MutexLocker ml(_state_lock);
  if (state() > IDLE) {
    return Error("Profiler already started");
  }

  Error error = checkJvmCapabilities();

  if (!error && (args._event != NULL || args._cpu >= 0)) {
    _cpu_engine = selectCpuEngine(args);
    error = _cpu_engine->check(args);
  }
  if (!error && args._wall >= 0) {
    _wall_engine = selectWallEngine(args);
    error = _wall_engine->check(args);
  }
  if (!error && args._memory >= 0) {
    _alloc_engine = selectAllocEngine(args);
    error = _alloc_engine->check(args);
  }
  if (!error && args._nativemem >= 0) {
    error = malloc_tracer.check(args);
  }
  if (!error && args._nativesocket) {
    error = NativeSocketSampler::instance()->check(args);
  }
  if (!error) {
    if (args._cstack == CSTACK_DWARF && !DWARF_SUPPORTED) {
      return Error("DWARF unwinding is not supported on this platform");
    } else if (args._cstack == CSTACK_LBR && _cpu_engine != &perf_events) {
      return Error("Branch stack is supported only with PMU events");
    } else if (_cstack >= CSTACK_VM && !(VMStructs::hasStackStructs() && OS::isLinux())) {
      return Error(
          "VMStructs stack walking is not supported on this JVM/platform");
    }
  }

  return error;
}

Error Profiler::dump(const char *path, const int length) {
  MutexLocker ml(_state_lock);
  State cur_state = state();
  if (cur_state != IDLE && cur_state != RUNNING) {
    return Error("Profiler has not started");
  }

  if (cur_state == RUNNING) {
    std::set<int> thread_ids;
    // flush the liveness tracker instance and note all the threads referenced
    // by the live objects
    LivenessTracker::instance()->flush(thread_ids);

    Libraries::instance()->refresh();
    updateJavaThreadNames();
    updateNativeThreadNames();

    const CodeCacheArray& native_libs = _libs->native_libs();
    Counters::set(CODECACHE_NATIVE_COUNT, native_libs.count());
    Counters::set(CODECACHE_NATIVE_SIZE_BYTES, native_libs.memoryUsage());
    Counters::set(CODECACHE_RUNTIME_STUBS_SIZE_BYTES,
                  native_libs.memoryUsage());

    Error err = Error::OK;
    // rotateDictsAndRun rotates the dictionaries, takes lockAll() around the
    // dump (fences ASGCT/JNI writers to CallTraceStorage), then clearStandby()s
    // the rotated buffers.  StringDictionary's RefCountGuard protocol handles
    // its own writer/reader coordination; #527's classMapSharedGuard readers
    // (deferred vtable receiver resolution) are coordinated through
    // _class_map_lock.
    rotateDictsAndRun([&]{
      err = _jfr.dump(path, length);
      __atomic_add_fetch(&_epoch, 1, __ATOMIC_SEQ_CST);
    });

    _thread_info.clearAll(thread_ids);
    _thread_info.reportCounters();

    // reset unwinding counters
    Counters::set(UNWINDING_TIME_ASYNC, 0);
    Counters::set(UNWINDING_TIME_JVMTI, 0);

    return err;
  }

  return Error::OK;
}

void Profiler::lockAll() {
  for (int i = 0; i < CONCURRENCY_LEVEL; i++)
    _locks[i].lock();
}

void Profiler::unlockAll() {
  for (int i = 0; i < CONCURRENCY_LEVEL; i++)
    _locks[i].unlock();
}

void Profiler::switchThreadEvents(jvmtiEventMode mode) {
  if (_thread_events_state != mode) {
    jvmtiEnv *jvmti = VM::jvmti();
    jvmti->SetEventNotificationMode(mode, JVMTI_EVENT_THREAD_START, NULL);
    jvmti->SetEventNotificationMode(mode, JVMTI_EVENT_THREAD_END, NULL);
    _thread_events_state = mode;
  }
}

Error Profiler::runInternal(Arguments &args, std::ostream &out) {
  switch (args._action) {
  case ACTION_START:
  case ACTION_RESUME: {
    Error error = start(args, args._action == ACTION_START);
    if (error) {
      return error;
    }
    out << "Profiling started\n";
    break;
  }
  case ACTION_STOP: {
    Error error = stop();
    if (error) {
      return error;
    }
    break;
  }

  case ACTION_CHECK: {
    Error error = check(args);
    if (error) {
      return error;
    }
    out << "OK\n";
    break;
  }
  case ACTION_STATUS: {
    MutexLocker ml(_state_lock);
    if (state() == RUNNING) {
      out << "Profiling is running for " << uptime() << " seconds\n";
    } else {
      out << "Profiler is not active\n";
    }
    break;
  }
  case ACTION_LIST: {
    out << "Basic events:" << std::endl;
    out << "  " << EVENT_CPU << std::endl;
    out << "  " << EVENT_ALLOC << std::endl;
    out << "  " << EVENT_WALL << std::endl;
    out << "  " << EVENT_ITIMER << std::endl;

    out << "Java method calls:\n";
    out << "  ClassName.methodName\n";

    if (perf_events.check(args)) {
      out << "Perf events:\n";
      // The first perf event is "cpu" which is already printed
      for (int event_id = 1;; event_id++) {
        const char *event_name = PerfEvents::getEventName(event_id);
        if (event_name == NULL)
          break;
        out << "  " << event_name << "\n";
      }
    }
    break;
  }
  case ACTION_VERSION:
    out << PROFILER_VERSION;
    out.flush();
    break;
  default:
    break;
  }
  return Error::OK;
}

Error Profiler::run(Arguments &args) { return runInternal(args, std::cout); }

Error Profiler::restart(Arguments &args) {
  MutexLocker ml(_state_lock);

  Error error = stop();
  if (error) {
    return error;
  }

  return Error::OK;
}

void Profiler::shutdown(Arguments &args) {
  MutexLocker ml(_state_lock);

  // The last chance to dump profile before VM terminates
  if (state() == RUNNING) {
    args._action = ACTION_STOP;
    Error error = run(args);
    if (error) {
      Log::error("%s", error.message());
    }
  }

  _state.store(TERMINATED, std::memory_order_release);
}

int Profiler::lookupClass(const char *key, size_t length) {
  // StringDictionary::lookup() is internally thread-safe via _accepting +
  // RefCountGuard; no external lock required (unlike the old Dictionary).
  u32 id = _class_map.lookup(key, length);
  return id != 0 ? static_cast<int>(id) : -1;
}

int Profiler::status(char* status, int max_len) {
  return snprintf(status, max_len,
    "== Java-Profiler Status ===\n"
    " Running          : %s\n"
    " CPU Engine       : %s\n"
    " WallClock Engine : %s\n"
    " Allocations      : %s\n",
    state() == RUNNING ? "true" : "false",
    _cpu_engine != nullptr ? _cpu_engine->name() : "None",
    _wall_engine != nullptr ? _wall_engine->name() : "None",
    _alloc_engine != nullptr ? _alloc_engine->name() : "None");
}
