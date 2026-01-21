/*
 * Copyright The async-profiler authors
 * Copyright 2024, 2025 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "profiler.h"
#include "asyncSampleMutex.h"
#include "context.h"
#include "criticalSection.h"
#include "common.h"
#include "counters.h"
#include "ctimer.h"
#include "dwarf_dd.h"
#include "flightRecorder.h"
#include "itimer.h"
#include "j9Ext.h"
#include "j9WallClock.h"
#include "libraryPatcher.h"
#include "objectSampler.h"
#include "os.h"
#include "perfEvents.h"
#include "safeAccess.h"
#include "stackFrame.h"
#include "stackWalker_dd.h"
#include "symbols.h"
#include "thread.h"
#include "tsc_dd.h"
#include "vmStructs_dd.h"
#include "wallClock.h"
#include <algorithm>
#include <dlfcn.h>
#include <fstream>
#include <memory>
#include <set>
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

static void (*orig_trapHandler)(int signo, siginfo_t *siginfo, void *ucontext);
static void (*orig_segvHandler)(int signo, siginfo_t *siginfo, void *ucontext);
static void (*orig_busHandler)(int signo, siginfo_t *siginfo, void *ucontext);

static Engine noop_engine;
static PerfEvents perf_events;
static WallClockASGCT wall_asgct_engine;
static WallClockJVMTI wall_jvmti_engine;
static J9WallClock j9_engine;
static ITimer itimer;
static CTimer ctimer;

// Stack recovery techniques used to workaround AsyncGetCallTrace flaws.
// Can be disabled with 'safemode' option.
enum StackRecovery {
  UNKNOWN_JAVA = (1 << 0),
  POP_STUB = (1 << 1),
  POP_METHOD = (1 << 2),
  UNWIND_NATIVE = (1 << 3),
  LAST_JAVA_PC = (1 << 4),
  GC_TRACES = (1 << 5),
  PROBE_SP = 0x100,
};

static inline int makeFrame(ASGCT_CallFrame *frames, jint type, jmethodID id) {
  frames[0].bci = type;
  frames[0].method_id = id;
  return 1;
}

static inline int makeFrame(ASGCT_CallFrame *frames, jint type, uintptr_t id) {
  return makeFrame(frames, type, (jmethodID)id);
}

static inline int makeFrame(ASGCT_CallFrame *frames, jint type,
                            const char *id) {
  return makeFrame(frames, type, (jmethodID)id);
}

void Profiler::addJavaMethod(const void *address, int length,
                             jmethodID method) {
  CodeHeap::updateBounds(address, (const char *)address + length);
}

void Profiler::addRuntimeStub(const void *address, int length,
                              const char *name) {
  _stubs_lock.lock();
  _runtime_stubs.add(address, length, name, true);
  _stubs_lock.unlock();

  if (strcmp(name, "call_stub") == 0) {
    _call_stub_begin = address;
    _call_stub_end = (const char *)address + length;
  }

  CodeHeap::updateBounds(address, (const char *)address + length);
}

void Profiler::onThreadStart(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread) {
  ProfiledThread::initCurrentThread();
  ProfiledThread *current = ProfiledThread::current();
  int tid = current->tid();
  if (_thread_filter.enabled()) {
    int slot_id = _thread_filter.registerThread();
    current->setFilterSlotId(slot_id);
    _thread_filter.remove(slot_id);  // Remove from filtering initially
  }
  updateThreadName(jvmti, jni, thread, true);

  _cpu_engine->registerThread(tid);
  _wall_engine->registerThread(tid);
}

void Profiler::onThreadEnd(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread) {
  ProfiledThread *current = ProfiledThread::current();
  int tid = -1;
  
  if (current != nullptr) {
    // ProfiledThread is alive - do full cleanup and use efficient tid access
    int slot_id = current->filterSlotId();
    tid = current->tid();
    
    if (_thread_filter.enabled()) {
      _thread_filter.unregisterThread(slot_id);
      current->setFilterSlotId(-1);
    }
    
    ProfiledThread::release();
  } else {
    // ProfiledThread already cleaned up - try to get tid from JVMTI as fallback
    tid = VMThread::nativeThreadId(jni, thread);
    if (tid < 0) {
      // No ProfiledThread AND can't get tid from JVMTI - nothing we can do
      return;
    }
  }
  
  // These can run if we have a valid tid
  updateThreadName(jvmti, jni, thread, false);  // false = not self
  _cpu_engine->unregisterThread(tid);
  _wall_engine->unregisterThread(tid);
}

int Profiler::registerThread(int tid) {
  return _instance->_cpu_engine->registerThread(tid) |
         _instance->_wall_engine->registerThread(tid);
}
void Profiler::unregisterThread(int tid) {
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
      const void *address = native_libs[i]->findSymbolByPrefix(name, len - 1);
      if (address != NULL) {
        return address;
      }
    }
  } else {
    for (int i = 0; i < native_lib_count; i++) {
      const void *address = native_libs[i]->findSymbol(name);
      if (address != NULL) {
        return address;
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
    const char *s = native_libs[lib_index]->name();
    if (s != NULL) {
      const char *p = strrchr(s, '/');
      return p != NULL ? p + 1 : s;
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

CodeBlob *Profiler::findRuntimeStub(const void *address) {
  return _runtime_stubs.findBlobByAddress(address);
}

bool Profiler::isAddressInCode(const void *pc, bool include_stubs) {
  if (CodeHeap::contains(pc)) {
    return CodeHeap::findNMethod(pc) != NULL &&
           (include_stubs || !(pc >= _call_stub_begin && pc < _call_stub_end));
  } else {
    return _libs->findLibraryByAddress(pc) != NULL;
  }
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
    native_frames += ddprof::StackWalker::walkDwarf(ucontext, callchain + native_frames,
                                            max_depth - native_frames,
                                            java_ctx, truncated);
  } else {
    native_frames += ddprof::StackWalker::walkFP(ucontext, callchain + native_frames,
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

  jmethodID packed = RemoteFramePacker::pack(pc_offset, mark, lib_index);

  TEST_LOG("populateRemoteFrame: lib=%s, build_id=%s, pc=0x%lx, pc_offset=0x%lx, mark=%d, lib_index=%u, packed=0x%lx",
           lib->name(), lib->buildId(), pc, pc_offset, (int)mark, lib_index, (uintptr_t)packed);

  frame->bci = BCI_NATIVE_FRAME_REMOTE;
  frame->method_id = packed;

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
 * - Does full symbol resolution via findNativeMethod()
 * - Checks marks after symbol resolution (same O(log n) + O(1) cost)
 */
Profiler::NativeFrameResolution Profiler::resolveNativeFrameForWalkVM(uintptr_t pc, int lock_index) {
  if (_remote_symbolication) {
    CodeCache* lib = _libs->findLibraryByAddress((void*)pc);
    if (lib != nullptr && lib->hasBuildId()) {
      // Get symbol name and check mark
      const char *method_name = nullptr;
      lib->binarySearch((void*)pc, &method_name);
      char mark = (method_name != nullptr) ? NativeFunc::mark(method_name) : 0;

      if (mark != 0) {
        return {nullptr, BCI_NATIVE_FRAME, true};  // Marked - stop processing
      }

      // Pack remote symbolication data using utility struct
      uintptr_t pc_offset = pc - (uintptr_t)lib->imageBase();
      uint32_t lib_index = (uint32_t)lib->libIndex();
      jmethodID packed = RemoteFramePacker::pack(pc_offset, mark, lib_index);

      TEST_LOG("resolveNativeFrameForWalkVM: lib=%s, build_id=%s, pc=0x%lx, pc_offset=0x%lx, mark=%d, lib_index=%u, packed=0x%lx",
               lib->name(), lib->buildId(), pc, pc_offset, (int)mark, lib_index, (uintptr_t)packed);

      return {packed, BCI_NATIVE_FRAME_REMOTE, false};
    }
  }

  // Fallback: Traditional symbol resolution
  const char *method_name = findNativeMethod((void*)pc);
  if (method_name != nullptr && NativeFunc::isMarked(method_name)) {
    return {nullptr, BCI_NATIVE_FRAME, true};
  }

  return {(jmethodID)method_name, BCI_NATIVE_FRAME, false};
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
        char mark = (method_name != nullptr) ? NativeFunc::mark(method_name) : 0;

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
    if (method_name != nullptr && NativeFunc::isMarked(method_name)) {
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

int Profiler::getJavaTraceAsync(void *ucontext, ASGCT_CallFrame *frames,
                                int max_depth, StackContext *java_ctx,
                                bool *truncated) {
  // Workaround for JDK-8132510: it's not safe to call GetEnv() inside a signal
  // handler since JDK 9, so we do it only for threads already registered in
  // ThreadLocalStorage
  ddprof::VMThread *vm_thread = ddprof::VMThread::current();
  if (vm_thread == NULL) {
    Counters::increment(AGCT_NOT_REGISTERED_IN_TLS);
    return 0;
  }

  JNIEnv *jni = VM::jni();
  if (jni == NULL) {
    // Not a Java thread
    Counters::increment(AGCT_NOT_JAVA);
    return 0;
  }

  StackFrame frame(ucontext);
  uintptr_t saved_pc, saved_sp, saved_fp;
  if (ucontext != NULL) {
    saved_pc = frame.pc();
    saved_sp = frame.sp();
    saved_fp = frame.fp();

    if (saved_pc >= (uintptr_t)_call_stub_begin &&
        saved_pc < (uintptr_t)_call_stub_end) {
      // call_stub is unsafe to walk
      frames->bci = BCI_ERROR;
      frames->method_id = (jmethodID) "call_stub";
      return 1;
    }

    if (!ddprof::VMStructs::isSafeToWalk(saved_pc)) {
      frames->bci = BCI_NATIVE_FRAME;
      CodeBlob *codeBlob =
          VMStructs::libjvm()->findBlobByAddress((const void *)saved_pc);
      if (codeBlob) {
        frames->method_id = (jmethodID)codeBlob->_name;
      } else {
        frames->method_id = (jmethodID) "unknown_unwalkable";
      }
      return 1;
    }
  } else {
    return 0;
  }

  int state = vm_thread->state();
  // from OpenJDK
  // https://github.com/openjdk/jdk/blob/7455bb23c1d18224e48e91aae4f11fe114d04fab/src/hotspot/share/utilities/globalDefinitions.hpp#L1030
  /*
  enum JavaThreadState {
      _thread_uninitialized     =  0, // should never happen (missing
  initialization) _thread_new               =  2, // just starting up, i.e., in
  process of being initialized _thread_new_trans         =  3, // corresponding
  transition state (not used, included for completeness) _thread_in_native =  4,
  // running in native code _thread_in_native_trans   =  5, // corresponding
  transition state _thread_in_vm             =  6, // running in VM
      _thread_in_vm_trans       =  7, // corresponding transition state
      _thread_in_Java           =  8, // running in Java or in stub code
      _thread_in_Java_trans     =  9, // corresponding transition state (not
  used, included for completeness) _thread_blocked           = 10, // blocked in
  vm _thread_blocked_trans     = 11, // corresponding transition state
      _thread_max_state         = 12  // maximum thread state+1 - used for
  statistics allocation
  };
   */
  bool in_java = (state == 8 || state == 9);
  if (in_java && java_ctx->sp != 0) {
    // skip ahead to the Java frames before calling AGCT
    frame.restore((uintptr_t)java_ctx->pc, java_ctx->sp, java_ctx->fp);
  } else if (state != 0 && (vm_thread->anchor() == nullptr || vm_thread->anchor()->lastJavaSP() == 0)) {
    // we haven't found the top Java frame ourselves, and the lastJavaSP wasn't
    // recorded either when not in the Java state, lastJava ucontext will be
    // used by AGCT
    Counters::increment(AGCT_NATIVE_NO_JAVA_CONTEXT);
    return 0;
  }
  bool blocked_in_vm = (state == 10 || state == 11);
  // avoid unwinding during deoptimization
  if (blocked_in_vm && vm_thread->osThreadState() == OSThreadState::RUNNABLE) {
    Counters::increment(AGCT_BLOCKED_IN_VM);
    return 0;
  }

  JitWriteProtection jit(false);
  // AsyncGetCallTrace writes to ASGCT_CallFrame array
  ASGCT_CallTrace trace = {jni, 0, frames};
  VM::_asyncGetCallTrace(&trace, max_depth, ucontext);

  if (trace.num_frames > 0) {
    frame.restore(saved_pc, saved_sp, saved_fp);
    return trace.num_frames;
  }

  if ((trace.num_frames == ticks_unknown_Java ||
       trace.num_frames == ticks_not_walkable_Java) &&
      !(_safe_mode & UNKNOWN_JAVA) && ucontext != NULL) {
    CodeBlob *stub = NULL;
    _stubs_lock.lockShared();
    if (_runtime_stubs.contains((const void *)frame.pc())) {
      stub = findRuntimeStub((const void *)frame.pc());
    }
    _stubs_lock.unlockShared();

    if (stub != NULL) {
      if (_cstack != CSTACK_NO) {
        max_depth -= makeFrame(trace.frames++, BCI_NATIVE_FRAME, stub->_name);
      }
      if (!(_safe_mode & POP_STUB) &&
          frame.unwindStub((instruction_t *)stub->_start, stub->_name) &&
          isAddressInCode((const void *)frame.pc())) {
        VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
      }
    } else if (VMStructs::hasMethodStructs()) {
      NMethod *nmethod = CodeHeap::findNMethod((const void *)frame.pc());
      if (nmethod != NULL && nmethod->isNMethod() && nmethod->isAlive()) {
        VMMethod *method = nmethod->method();
        if (method != NULL) {
          jmethodID method_id = method->id();
          if (method_id != NULL) {
            max_depth -= makeFrame(trace.frames++, 0, method_id);
          }
          if (!(_safe_mode & POP_METHOD) && frame.unwindCompiled(nmethod) &&
              isAddressInCode((const void *)frame.pc())) {
            VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
          }
          if ((_safe_mode & PROBE_SP) && trace.num_frames < 0) {
            if (method_id != NULL) {
              trace.frames--;
            }
            for (int i = 0; trace.num_frames < 0 && i < PROBE_SP_LIMIT; i++) {
              frame.sp() += sizeof(void*);
              VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
            }
          }
        }
      } else if (nmethod != NULL) {
        if (_cstack != CSTACK_NO) {
          max_depth -=
              makeFrame(trace.frames++, BCI_NATIVE_FRAME, nmethod->name());
        }
        if (!(_safe_mode & POP_STUB) &&
            frame.unwindStub(NULL, nmethod->name()) &&
            isAddressInCode((const void *)frame.pc())) {
          VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
        }
      }
    }
  } else if (trace.num_frames == ticks_unknown_not_Java &&
             !(_safe_mode & LAST_JAVA_PC)) {
    JavaFrameAnchor* anchor = vm_thread->anchor();
    uintptr_t sp = anchor->lastJavaSP();
    const void* pc = anchor->lastJavaPC();
    if (sp != 0 && pc == NULL) {
      // We have the last Java frame anchor, but it is not marked as walkable.
      // Make it walkable here
      pc = ((const void**)sp)[-1];
      anchor->setLastJavaPC(pc);

      NMethod *m = CodeHeap::findNMethod(pc);
      if (m != NULL) {
        // AGCT fails if the last Java frame is a Runtime Stub with an invalid
        // _frame_complete_offset. In this case we patch _frame_complete_offset
        // manually
        if (!m->isNMethod() && m->frameSize() > 0 &&
            m->frameCompleteOffset() == -1) {
          m->setFrameCompleteOffset(0);
        }
        VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
      } else if (_libs->findLibraryByAddress(pc) != NULL) {
        VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
      }

      anchor->setLastJavaPC(nullptr);
    }
  } else if (trace.num_frames == ticks_not_walkable_not_Java &&
             !(_safe_mode & LAST_JAVA_PC)) {
    JavaFrameAnchor* anchor = vm_thread->anchor();
    uintptr_t sp = anchor->lastJavaSP();
    const void* pc = anchor->lastJavaPC();
    if (sp != 0 && pc != NULL) {
      // Similar to the above: last Java frame is set,
      // but points to a Runtime Stub with an invalid _frame_complete_offset
      NMethod *m = CodeHeap::findNMethod(pc);
      if (m != NULL && !m->isNMethod() && m->frameSize() > 0 &&
          m->frameCompleteOffset() == -1) {
        m->setFrameCompleteOffset(0);
        VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
      }
    }
  } else if (trace.num_frames == ticks_GC_active && !(_safe_mode & GC_TRACES)) {
    if (vm_thread->anchor()->lastJavaSP() == 0) {
      // Do not add 'GC_active' for threads with no Java frames, e.g. Compiler
      // threads
      frame.restore(saved_pc, saved_sp, saved_fp);
      return 0;
    }
  }

  frame.restore(saved_pc, saved_sp, saved_fp);

  if (trace.num_frames > 0) {
    return trace.num_frames + (trace.frames - frames);
  }

  const char *err_string = asgctError(trace.num_frames);
  if (err_string == NULL) {
    // No Java stack, because thread is not in Java context
    return 0;
  }

  atomicIncRelaxed(_failures[-trace.num_frames]);
  trace.frames->bci = BCI_ERROR;
  trace.frames->method_id = (jmethodID)err_string;
  return trace.frames - frames + 1;
}

void Profiler::fillFrameTypes(ASGCT_CallFrame *frames, int num_frames,
                              NMethod *nmethod) {
  if (nmethod->isNMethod() && nmethod->isAlive()) {
    VMMethod *method = nmethod->method();
    if (method == NULL) {
      return;
    }

    jmethodID current_method_id = method->id();
    if (current_method_id == NULL) {
      return;
    }

    // Mark current_method as COMPILED and frames above current_method as
    // INLINED
    for (int i = 0; i < num_frames; i++) {
      if (frames[i].method_id == NULL || frames[i].bci <= BCI_NATIVE_FRAME) {
        break;
      }
      if (frames[i].method_id == current_method_id) {
        int level = nmethod->level();
        frames[i].bci = FrameType::encode(
            level >= 1 && level <= 3 ? FRAME_C1_COMPILED : FRAME_JIT_COMPILED,
            frames[i].bci);
        for (int j = 0; j < i; j++) {
          frames[j].bci = FrameType::encode(FRAME_INLINED, frames[j].bci);
        }
        break;
      }
    }
  } else if (nmethod->isInterpreter()) {
    // Mark the first Java frame as INTERPRETED
    for (int i = 0; i < num_frames; i++) {
      if (frames[i].bci > BCI_NATIVE_FRAME) {
        frames[i].bci = FrameType::encode(FRAME_INTERPRETED, frames[i].bci);
        break;
      }
    }
  }
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
    u64 startTime = TSC::ticks();
    ASGCT_CallFrame *frames = _calltrace_buffer[lock_index]->_asgct_frames;
    jvmtiFrameInfo *jvmti_frames = _calltrace_buffer[lock_index]->_jvmti_frames;

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
    }

    call_trace_id = _call_trace_storage.put(num_frames, frames, false, counter);
    u64 duration = TSC::ticks() - startTime;
    if (duration > 0) {
      Counters::increment(UNWINDING_TIME_JVMTI, duration); // increment the JVMTI specific counter
    }
  }
  if (!deferred) {
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

  _jfr.recordEvent(lock_index, tid, call_trace_id, event_type, event);

  _locks[lock_index].unlock();
}

void Profiler::recordSample(void *ucontext, u64 counter, int tid,
                            jint event_type, u64 call_trace_id, Event *event) {
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
    return;
  }

  bool truncated = false;
  // in lightweight mode we're just sampling the the context associated with the
  // passage of CPU or wall time, we use the same event definitions but we
  // record a null stacktrace we can skip the unwind if we've got a
  // call_trace_id determined to be reusable at a higher level

  if (!_omit_stacktraces && call_trace_id == 0) {
    u64 startTime = TSC::ticks();
    ASGCT_CallFrame *frames = _calltrace_buffer[lock_index]->_asgct_frames;

    int num_frames = 0;

    StackContext java_ctx = {0};
    ASGCT_CallFrame *native_stop = frames + num_frames;
    num_frames += getNativeTrace(ucontext, native_stop, event_type, tid,
                                 &java_ctx, &truncated, lock_index);
    if (num_frames < _max_stack_depth) {
      int max_remaining = _max_stack_depth - num_frames;
      if (_features.mixed) {
        int vm_start = num_frames;
        int vm_frames = ddprof::StackWalker::walkVM(ucontext, frames + vm_start, max_remaining, _features, eventTypeFromBCI(event_type), &truncated, lock_index);
        num_frames += vm_frames;
      } else if (event_type == BCI_CPU || event_type == BCI_WALL) {
        if (_cstack >= CSTACK_VM) {
          int vm_start = num_frames;
          int vm_frames = ddprof::StackWalker::walkVM(ucontext, frames + vm_start, max_remaining, _features, eventTypeFromBCI(event_type), &truncated, lock_index);
          num_frames += vm_frames;
        } else {
          // Async events
          AsyncSampleMutex mutex(ProfiledThread::currentSignalSafe());
          int java_frames = 0;
          if (mutex.acquired()) {
            java_frames = getJavaTraceAsync(ucontext, frames + num_frames, max_remaining, &java_ctx, &truncated);
            if (java_frames > 0 && java_ctx.pc != NULL && VMStructs::hasMethodStructs()) {
              NMethod* nmethod = CodeHeap::findNMethod(java_ctx.pc);
              if (nmethod != NULL) {
                fillFrameTypes(frames + num_frames, java_frames, nmethod);
              }
            }
          }
          num_frames += java_frames;
        }
      }
    }
    if (num_frames == 0) {
      num_frames += makeFrame(frames + num_frames, BCI_ERROR, "no_Java_frame");
    }

    call_trace_id =
        _call_trace_storage.put(num_frames, frames, truncated, counter);
    ProfiledThread *thread = ProfiledThread::currentSignalSafe();
    if (thread != nullptr) {
      thread->recordCallTraceId(call_trace_id);
    }
    u64 duration = TSC::ticks() - startTime;
    if (duration > 0) {
      Counters::increment(UNWINDING_TIME_ASYNC, duration); // increment the async specific counter
    }
  }
  _jfr.recordEvent(lock_index, tid, call_trace_id, event_type, event);

  _locks[lock_index].unlock();
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

void Profiler::recordExternalSample(u64 weight, int tid, int num_frames,
                                    ASGCT_CallFrame *frames, bool truncated,
                                    jint event_type, Event *event) {
  // Protect external sampling operations to prevent signal handler interference
  CriticalSection cs;
  atomicIncRelaxed(_total_samples);

  // Convert ASGCT_CallFrame to ASGCT_CallFrame
  // External samplers (like ObjectSampler) provide standard frames only
  u32 lock_index = getLockIndex(tid);
  ASGCT_CallFrame *extended_frames = _calltrace_buffer[lock_index]->_asgct_frames;
  for (int i = 0; i < num_frames; i++) {
    extended_frames[i] = frames[i];
  }

  u64 call_trace_id =
      _call_trace_storage.put(num_frames, extended_frames, truncated, weight);
  if (!_locks[lock_index].tryLock() &&
      !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
      !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock()) {
    // Too many concurrent signals already
    atomicIncRelaxed(_failures[-ticks_skipped]);
    return;
  }

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

void *Profiler::dlopen_hook(const char *filename, int flags) {
  void *result = dlopen(filename, flags);
  if (result != NULL) {
    // Static function of Profiler -> can not use the instance variable _libs
    // Since Libraries is a singleton, this does not matter
    Libraries::instance()->updateSymbols(false);
    // Extract build-ids for newly loaded libraries if remote symbolication is enabled
    Profiler* profiler = instance();
    if (profiler != nullptr && profiler->_remote_symbolication) {
      Libraries::instance()->updateBuildIds();
    }
  }
  return result;
}

void Profiler::switchLibraryTrap(bool enable) {
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
  if (!crashHandler(signo, siginfo, ucontext)) {
    orig_segvHandler(signo, siginfo, ucontext);
  }
}

void Profiler::busHandler(int signo, siginfo_t *siginfo, void *ucontext) {
  if (!crashHandler(signo, siginfo, ucontext)) {
    orig_busHandler(signo, siginfo, ucontext);
  }
}

bool Profiler::crashHandler(int signo, siginfo_t *siginfo, void *ucontext) {
  ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
  if (thrd != nullptr && !thrd->enterCrashHandler()) {
    // we are already in a crash handler; don't recurse!
    return false;
  }

  if (SafeAccess::handle_safefetch(signo, ucontext)) {
    if (thrd != nullptr) {
      thrd->exitCrashHandler();
    }
    return true;
  }

  uintptr_t fault_address = (uintptr_t)siginfo->si_addr;
  StackFrame frame(ucontext);
  uintptr_t pc = frame.pc();
  if (pc == fault_address) {
    // it is 'pc' that is causing the fault; can not access it safely
    if (thrd != nullptr) {
      thrd->exitCrashHandler();
    }
    return false;
  }

  if (WX_MEMORY && Trap::isFaultInstruction(pc)) {
    if (thrd != nullptr) {
      thrd->exitCrashHandler();
    }
    return true;
  }

  if (VM::isHotspot()) {
    // the following checks require vmstructs and therefore HotSpot

    ddprof::StackWalker::checkFault(thrd);

    // Workaround for JDK-8313796 if needed. Setting cstack=dwarf also helps
    if (_need_JDK_8313796_workaround &&
        VMStructs::isInterpretedFrameValidFunc((const void *)pc) &&
        frame.skipFaultInstruction()) {
      if (thrd != nullptr) {
        thrd->exitCrashHandler();
      }
      return true;
    }
  }

  if (thrd != nullptr) {
    thrd->exitCrashHandler();
  }
  return false;
}

void Profiler::setupSignalHandlers() {
  // do not re-run the signal setup (run only when VM has not been loaded yet)
  if (__sync_bool_compare_and_swap(&_signals_initialized, false, true)) {
      if (VM::isHotspot() || VM::isOpenJ9()) {
        // HotSpot and J9 tolerate interposed SIGSEGV/SIGBUS handler; other JVMs
        // probably not
        orig_segvHandler = OS::replaceSigsegvHandler(segvHandler);
        orig_busHandler = OS::replaceSigbusHandler(busHandler);
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
  int native_thread_id = VMThread::nativeThreadId(jni, thread);
  if (native_thread_id < 0 && self) {
    // if updating the current thread, use the native thread id from the
    // ProfilerThread
    native_thread_id = ProfiledThread::currentTid();
  }
  if (native_thread_id >= 0 &&
      jvmti->GetThreadInfo(thread, &thread_info) == 0) {
    jlong java_thread_id = VMThread::javaThreadId(jni, thread);
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
    updateThreadName(jvmti, jni, thread_objects[i]);
    jni->DeleteLocalRef(thread_objects[i]);
  }

  jvmti->Deallocate((unsigned char *)thread_objects);
}

void Profiler::updateNativeThreadNames() {
    ThreadList *thread_list = OS::listThreads();
    constexpr size_t buffer_size = 64;
    char name_buf[buffer_size];  // Stack-allocated buffer

    while (thread_list->hasNext()) { 
        int tid = thread_list->next(); 
        _thread_info.updateThreadName(
                tid, [&](int tid) -> std::string {
                    if (OS::threadName(tid, name_buf, buffer_size)) {
                        return std::string(name_buf, buffer_size);
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
      if (!J9Ext::shouldUseAsgct() || !J9Ext::can_use_ASGCT()) {
        if (!J9Ext::is_jvmti_jmethodid_safe()) {
          fprintf(stderr, "[ddprof] [WARN] Safe jmethodID access is not available on this JVM. Using "
                    "CPU profiler on your own risk. Use -XX:+KeepJNIIDs=true JVM "
                    "flag to make access to jmethodIDs safe, if your JVM supports it\n");
        }
        TEST_LOG("J9[cpu]=jvmti");
        return &j9_engine;
      }
      TEST_LOG("J9[cpu]=asgct");
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
    if (args._wallclock_sampler == JVMTI || !J9Ext::shouldUseAsgct() || !J9Ext::can_use_ASGCT()) {
      if (!J9Ext::is_jvmti_jmethodid_safe()) {
        fprintf(stderr, "[ddprof] [WARN] Safe jmethodID access is not available on this JVM. Using "
                  "wallclock profiler on your own risk. Use -XX:+KeepJNIIDs=true JVM "
                  "flag to make access to jmethodIDs safe, if your JVM supports it\n");
      }
      j9_engine.sampleIdleThreads();
      TEST_LOG("J9[wall]=jvmti");
      return (Engine *)&j9_engine;
    } else {
      TEST_LOG("J9[wall]=asgct");
      return (Engine *)&wall_asgct_engine;
    }
  }
  switch (args._wallclock_sampler) {
        case JVMTI:
            return (Engine*)&wall_jvmti_engine;
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
  if (!VMStructs::hasJavaThreadId()) {
    return Error("Could not find Thread ID field. Unsupported JVM?");
  }

  if (VMThread::key() < 0) {
    return Error("Could not find VMThread bridge. Unsupported JVM?");
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
  if (_state > IDLE) {
    return Error("Profiler already started");
  }

  Error error = checkJvmCapabilities();
  if (error) {
    return error;
  }

  ProfiledThread::initExistingThreads();
  
  // Validate TLS priming for signal-based profiling safety
  if (ProfiledThread::wasTlsPrimingAttempted() && !ProfiledThread::isTlsPrimingAvailable()) {
    _omit_stacktraces = args._lightweight;
    _remote_symbolication = args._remote_symbolication;
    _event_mask =
        ((args._event != NULL && strcmp(args._event, EVENT_NOOP) != 0) ? EM_CPU
                                                                       : 0) |
        (args._cpu >= 0 ? EM_CPU : 0) | (args._wall >= 0 ? EM_WALL : 0) |
        (args._record_allocations || args._record_liveness || args._gc_generations
             ? EM_ALLOC
             : 0);
    
    // Check if signal-based profiling is requested without TLS priming
    if (_event_mask & (EM_CPU | EM_WALL)) {
      return Error("CRITICAL: Signal-based profiling (CPU/Wall) requested but TLS priming failed. "
                   "This would cause crashes in signal handlers due to unsafe TLS allocation. "
                   "Profiling disabled for safety. Check system RT signal availability.");
    }
    
    // Allow allocation profiling since it doesn't use signals
    if (_event_mask == EM_ALLOC) {
      writeLog(LOG_WARN, "TLS priming failed but continuing with allocation-only profiling (no signals)", 92);
    }
  } else {
    _omit_stacktraces = args._lightweight;
    _remote_symbolication = args._remote_symbolication;
    _event_mask =
        ((args._event != NULL && strcmp(args._event, EVENT_NOOP) != 0) ? EM_CPU
                                                                       : 0) |
        (args._cpu >= 0 ? EM_CPU : 0) | (args._wall >= 0 ? EM_WALL : 0) |
        (args._record_allocations || args._record_liveness || args._gc_generations
             ? EM_ALLOC
             : 0);
  }
  
  if (_event_mask == 0) {
    return Error("No profiling events specified");
  }

  if (reset || _start_time == 0) {
    // Reset counters
    _total_samples = 0;
    memset(_failures, 0, sizeof(_failures));

    // Reset dictionaries and bitmaps
    // Reset class map under lock because ObjectSampler may try to use it while
    // it is being cleaned up
    _class_map_lock.lock();
    _class_map.clear();
    _class_map_lock.unlock();

    // Reset call trace storage
    if (!_omit_stacktraces) {
      lockAll();
      _call_trace_storage.clear();
      unlockAll();
    }
    Counters::reset();

    // Reset thread names and IDs
    _thread_info.clearAll();
  }

  // (Re-)allocate calltrace buffers
  if (_max_stack_depth != args._jstackdepth) {
    _max_stack_depth = args._jstackdepth;
    size_t nelem = _max_stack_depth + RESERVED_FRAMES;

    for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
      free(_calltrace_buffer[i]);
      _calltrace_buffer[i] = (CallTraceBuffer*)calloc(nelem, sizeof(CallTraceBuffer));
      if (_calltrace_buffer[i] == NULL) {
        _max_stack_depth = 0;
        return Error("Not enough memory to allocate stack trace buffers (try "
                     "smaller jstackdepth)");
      }
    }
  }

  // Remote symbolication is now inline in ASGCT_CallFrame
  // No separate pool allocation needed!

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
  _safe_mode = args._safe_mode;
  if (VM::hotspot_version() < 8 || VM::isZing()) {
    _safe_mode |= GC_TRACES | LAST_JAVA_PC;
  }

  // TODO: Current way of setting filter is weird with the recent changes
  _thread_filter.init(args._filter ? args._filter : "0");
  
  // Minor optim: Register the current thread (start thread won't be called)
  if (_thread_filter.enabled()) {
    ProfiledThread *current = ProfiledThread::current();
    if (current != nullptr) {
      int slot_id = _thread_filter.registerThread();
      current->setFilterSlotId(slot_id);
      _thread_filter.remove(slot_id);  // Remove from filtering initially (matches onThreadStart behavior)
    }
  }

  _cpu_engine = selectCpuEngine(args);
  _wall_engine = selectWallEngine(args);
  _cstack = args._cstack;
  if (_cstack == CSTACK_DWARF && !DWARF_SUPPORTED) {
    _cstack = CSTACK_NO;
    Log::warn("DWARF unwinding is not supported on this platform. Defaulting "
              "to no native call stack unwinding.");
  } else if (_cstack == CSTACK_LBR && _cpu_engine != &perf_events) {
    _cstack = CSTACK_NO;
    Log::warn("Branch stack is supported only with PMU events");
  } else if (_cstack == CSTACK_VM) {
    if (!VMStructs::hasStackStructs()) {
      return Error(
          "VMStructs stack walking is not supported on this JVM/platform");
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

  switchLibraryTrap(_cstack == CSTACK_DWARF || _remote_symbolication);

  JfrMetadata::initialize(args._context_attributes);
  _num_context_attributes = args._context_attributes.size();
  error = _jfr.start(args, reset);
  if (error) {
    disableEngines();
    switchLibraryTrap(false);
    return error;
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

  if (activated) {
    switchThreadEvents(JVMTI_ENABLE);

    _state = RUNNING;
    _start_time = time(NULL);
    __atomic_add_fetch(&_epoch, 1, __ATOMIC_RELAXED);

    return Error::OK;
  }
  // no engine was activated; perform cleanup
  disableEngines();
  switchLibraryTrap(false);

  lockAll();
  _jfr.stop();
  unlockAll();

  return Error(
      "Neither CPU, wallclock nor allocation profiling could be started");
}

Error Profiler::stop() {
  MutexLocker ml(_state_lock);
  if (_state != RUNNING) {
    return Error("Profiler is not active");
  }

  disableEngines();

  if (_event_mask & EM_ALLOC)
    _alloc_engine->stop();
  if (_event_mask & EM_WALL)
    _wall_engine->stop();
  if (_event_mask & EM_CPU)
    _cpu_engine->stop();

  switchLibraryTrap(false);
  switchThreadEvents(JVMTI_DISABLE);
  updateJavaThreadNames();
  updateNativeThreadNames();

  // writing these out before stopping the JFR recording allows to report the
  // correct counts in the recording
  _thread_info.reportCounters();

  // Clean up TLS priming infrastructure (watcher thread and signal handler)
  ProfiledThread::cleanupTlsPriming();

  // Acquire all spinlocks to avoid race with remaining signals
  lockAll();
  _jfr.stop();  // JFR serialization must complete before unpatching libraries
  unlockAll();

  // Unpatch libraries AFTER JFR serialization completes
  // Remote symbolication RemoteFrameInfo structs contain pointers to build-ID strings
  // owned by library metadata, so we must keep library patches active until after serialization
  LibraryPatcher::unpatch_libraries();

  _state = IDLE;
  return Error::OK;
}

Error Profiler::check(Arguments &args) {
  MutexLocker ml(_state_lock);
  if (_state > IDLE) {
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

Error Profiler::flushJfr() {
  MutexLocker ml(_state_lock);
  if (_state != RUNNING) {
    return Error("Profiler is not active");
  }

  updateJavaThreadNames();
  updateNativeThreadNames();

  lockAll();
  _jfr.flush();
  unlockAll();

  return Error::OK;
}

Error Profiler::dump(const char *path, const int length) {
  MutexLocker ml(_state_lock);
  if (_state != IDLE && _state != RUNNING) {
    return Error("Profiler has not started");
  }

  if (_state == RUNNING) {
    std::set<int> thread_ids;
    // flush the liveness tracker instance and note all the threads referenced
    // by the live objects
    LivenessTracker::instance()->flush(thread_ids);

    updateJavaThreadNames();
    updateNativeThreadNames();

    const CodeCacheArray& native_libs = _libs->native_libs();
    Counters::set(CODECACHE_NATIVE_COUNT, native_libs.count());
    Counters::set(CODECACHE_NATIVE_SIZE_BYTES, native_libs.memoryUsage());
    Counters::set(CODECACHE_RUNTIME_STUBS_SIZE_BYTES,
                  native_libs.memoryUsage());

    lockAll();
    Error err = _jfr.dump(path, length);
    __atomic_add_fetch(&_epoch, 1, __ATOMIC_SEQ_CST);

    // Note: No need to clear call trace storage here - the double buffering system
    // in processTraces() already handles clearing old traces while preserving
    // traces referenced by surviving LivenessTracker objects
    unlockAll();
    // Reset classmap
    _class_map_lock.lock();
    _class_map.clear();
    _class_map_lock.unlock();

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
    if (_state == RUNNING) {
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
  if (_state == RUNNING) {
    args._action = ACTION_STOP;
    Error error = run(args);
    if (error) {
      Log::error("%s", error.message());
    }
  }

  _state = TERMINATED;
}

int Profiler::lookupClass(const char *key, size_t length) {
  if (_class_map_lock.tryLockShared()) {
    int ret = _class_map.lookup(key, length);
    _class_map_lock.unlockShared();
    return ret;
  }
  // unable to lookup the class
  return -1;
}

int Profiler::status(char* status, int max_len) {
  return snprintf(status, max_len,
    "== Java-Profiler Status ===\n"
    " Running          : %s\n"
    " CPU Engine       : %s\n"
    " WallClock Engine : %s\n"
    " Allocations      : %s\n",
    _state == RUNNING ? "true" : "false",
    _cpu_engine != nullptr ? _cpu_engine->name() : "None",
    _wall_engine != nullptr ? _wall_engine->name() : "None",
    _alloc_engine != nullptr ? _alloc_engine->name() : "None");
}
