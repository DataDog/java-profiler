/*
 * Copyright 2016 Andrei Pangin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include <fstream>
#include <set>
#include <dlfcn.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "profiler.h"
#include "perfEvents.h"
#include "objectSampler.h"
#include "wallClock.h"
#include "j9Ext.h"
#include "j9ObjectSampler.h"
#include "j9WallClock.h"
#include "itimer.h"
#include "dwarf.h"
#include "flightRecorder.h"
#include "os.h"
#include "safeAccess.h"
#include "stackFrame.h"
#include "stackWalker.h"
#include "symbols.h"
#include "thread.h"
#include "vmStructs.h"
#include "context.h"
#include "counters.h"


// The instance is not deleted on purpose, since profiler structures
// can be still accessed concurrently during VM termination
Profiler* const Profiler::_instance = new Profiler();

static void (*orig_segvHandler)(int signo, siginfo_t* siginfo, void* ucontext);

static Engine noop_engine;
static PerfEvents perf_events;
// static AllocTracer alloc_tracer;
// static J9ObjectSampler j9_object_sampler;
static WallClock wall_engine;
static J9WallClock j9_engine;
static ITimer itimer;


// Stack recovery techniques used to workaround AsyncGetCallTrace flaws.
// Can be disabled with 'safemode' option.
enum StackRecovery {
    UNKNOWN_JAVA  = (1 << 0),
    POP_STUB      = (1 << 1),
    POP_METHOD    = (1 << 2),
    UNWIND_NATIVE = (1 << 3),
    LAST_JAVA_PC  = (1 << 4),
    GC_TRACES     = (1 << 5),
};


static inline int makeFrame(ASGCT_CallFrame* frames, jint type, jmethodID id) {
    frames[0].bci = type;
    frames[0].method_id = id;
    return 1;
}

static inline int makeFrame(ASGCT_CallFrame* frames, jint type, uintptr_t id) {
    return makeFrame(frames, type, (jmethodID)id);
}

static inline int makeFrame(ASGCT_CallFrame* frames, jint type, const char* id) {
    return makeFrame(frames, type, (jmethodID)id);
}


void Profiler::addJavaMethod(const void* address, int length, jmethodID method) {
    CodeHeap::updateBounds(address, (const char*)address + length);
}

void Profiler::addRuntimeStub(const void* address, int length, const char* name) {
    _stubs_lock.lock();
    _runtime_stubs.add(address, length, name, true);
    _stubs_lock.unlock();

    if (strcmp(name, "call_stub") == 0) {
        _call_stub_begin = address;
        _call_stub_end = (const char*) address + length;
    }

    CodeHeap::updateBounds(address, (const char*)address + length);
}

void Profiler::onThreadStart(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread) {
    ProfiledThread::initCurrentThread();

    int tid = ProfiledThread::currentTid();
    if (_thread_filter.enabled()) {
        _thread_filter.remove(tid);
    }
    updateThreadName(jvmti, jni, thread);

    _cpu_engine->registerThread(tid);
    _wall_engine->registerThread(tid);
}

void Profiler::onThreadEnd(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread) {
    int tid = ProfiledThread::currentTid();
    if (_thread_filter.enabled()) {
        _thread_filter.remove(tid);
    }
    updateThreadName(jvmti, jni, thread);

    _cpu_engine->unregisterThread(tid);
    // unregister here because JNI callers generally don't know about thread exits
    _wall_engine->unregisterThread(tid);
    ProfiledThread::release();
}

int Profiler::registerThread(int tid) {
    return _instance->_cpu_engine->registerThread(tid) |
            _instance->_wall_engine->registerThread(tid);
}
void Profiler::unregisterThread(int tid) {
    _instance->_cpu_engine->unregisterThread(tid);
    _instance->_wall_engine->unregisterThread(tid);
}

const char* Profiler::asgctError(int code) {
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

void Profiler::updateSymbols(bool kernel_symbols) {
    Symbols::parseLibraries(&_native_libs, kernel_symbols);
}

void Profiler::mangle(const char* name, char* buf, size_t size) {
    char* buf_end = buf + size;
    strcpy(buf, "_ZN");
    buf += 3;

    const char* c;
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

const void* Profiler::resolveSymbol(const char* name) {
    char mangled_name[256];
    if (strstr(name, "::") != NULL) {
        mangle(name, mangled_name, sizeof(mangled_name));
        name = mangled_name;
    }

    size_t len = strlen(name);
    int native_lib_count = _native_libs.count();
    if (len > 0 && name[len - 1] == '*') {
        for (int i = 0; i < native_lib_count; i++) {
            const void* address = _native_libs[i]->findSymbolByPrefix(name, len - 1);
            if (address != NULL) {
                return address;
            }
        }
    } else {
        for (int i = 0; i < native_lib_count; i++) {
            const void* address = _native_libs[i]->findSymbol(name);
            if (address != NULL) {
                return address;
            }
        }
    }

    return NULL;
}

// For BCI_NATIVE_FRAME, library index is encoded ahead of the symbol name
const char* Profiler::getLibraryName(const char* native_symbol) {
    short lib_index = NativeFunc::libIndex(native_symbol);
    if (lib_index >= 0 && lib_index < _native_libs.count()) {
        const char* s = _native_libs[lib_index]->name();
        if (s != NULL) {
            const char* p = strrchr(s, '/');
            return p != NULL ? p + 1 : s;
        }
    }
    return NULL;
}

CodeCache* Profiler::findJvmLibrary(const char* lib_name) {
    return VM::isOpenJ9() ? findLibraryByName(lib_name) : VMStructs::libjvm();
}

CodeCache* Profiler::findLibraryByName(const char* lib_name) {
    const size_t lib_name_len = strlen(lib_name);
    const int native_lib_count = _native_libs.count();
    for (int i = 0; i < native_lib_count; i++) {
        const char* s = _native_libs[i]->name();
        if (s != NULL) {
            const char* p = strrchr(s, '/');
            if (p != NULL && strncmp(p + 1, lib_name, lib_name_len) == 0) {
                return _native_libs[i];
            }
        }
    }
    return NULL;
}

CodeCache* Profiler::findLibraryByAddress(const void* address) {
    const int native_lib_count = _native_libs.count();
    for (int i = 0; i < native_lib_count; i++) {
        if (_native_libs[i]->contains(address)) {
            return _native_libs[i];
        }
    }
    return NULL;
}

const char* Profiler::findNativeMethod(const void* address) {
    CodeCache* lib = findLibraryByAddress(address);
    return lib == NULL ? NULL : lib->binarySearch(address);
}

bool Profiler::isAddressInCode(uintptr_t addr) {
    const void* pc = (const void*)addr;
    if (CodeHeap::contains(pc)) {
        return CodeHeap::findNMethod(pc) != NULL && !(pc >= _call_stub_begin && pc < _call_stub_end);
    } else {
        return findLibraryByAddress(pc) != NULL;
    }
}

int Profiler::getNativeTrace(void* ucontext, ASGCT_CallFrame* frames, int event_type, int tid, StackContext* java_ctx, bool *truncated) {
    if (_cstack == CSTACK_NO
        || (event_type == BCI_ALLOC || event_type == BCI_ALLOC_OUTSIDE_TLAB)
        || (event_type != BCI_CPU && event_type != BCI_WALL && _cstack == CSTACK_DEFAULT)) {
        return 0;
    }
    const void* callchain[MAX_NATIVE_FRAMES];
    int native_frames = 0;

    if (event_type == BCI_CPU && _cpu_engine == &perf_events) {
        native_frames += PerfEvents::walkKernel(tid, callchain + native_frames, MAX_NATIVE_FRAMES - native_frames, java_ctx);
    }
    if (_cstack == CSTACK_DWARF) {
        native_frames += StackWalker::walkDwarf(ucontext, callchain + native_frames, MAX_NATIVE_FRAMES - native_frames, java_ctx, truncated);
    } else {
        native_frames += StackWalker::walkFP(ucontext, callchain + native_frames, MAX_NATIVE_FRAMES - native_frames, java_ctx, truncated);
    }

    return convertNativeTrace(native_frames, callchain, frames);
}

int Profiler::convertNativeTrace(int native_frames, const void** callchain, ASGCT_CallFrame* frames) {
    int depth = 0;
    jmethodID prev_method = NULL;

    for (int i = 0; i < native_frames; i++) {
        const char* current_method_name = findNativeMethod(callchain[i]);
        if (current_method_name != NULL && NativeFunc::isMarked(current_method_name)) {
            // This is C++ interpreter frame, this and later frames should be reported
            // as Java frames returned by AGCT. Terminate the scan here.
            return depth;
        }

        jmethodID current_method = (jmethodID)current_method_name;
        if (current_method == prev_method && _cstack == CSTACK_LBR) {
            // Skip duplicates in LBR stack, where branch_stack[N].from == branch_stack[N+1].to
            prev_method = NULL;
        } else {
            frames[depth].bci = BCI_NATIVE_FRAME;
            frames[depth].method_id = prev_method = current_method;
            depth++;
        }
    }

    return depth;
}

int Profiler::getJavaTraceAsync(void* ucontext, ASGCT_CallFrame* frames, int max_depth, StackContext* java_ctx, bool *truncated) {
    // Workaround for JDK-8132510: it's not safe to call GetEnv() inside a signal handler
    // since JDK 9, so we do it only for threads already registered in ThreadLocalStorage
    VMThread* vm_thread = VMThread::current();
    if (vm_thread == NULL) {
        return 0;
    }

    JNIEnv* jni = VM::jni();
    if (jni == NULL) {
        // Not a Java thread
        return 0;
    }

    StackFrame frame(ucontext);
    uintptr_t saved_pc, saved_sp, saved_fp;
    if (ucontext != NULL) {
        saved_pc = frame.pc();
        saved_sp = frame.sp();
        saved_fp = frame.fp();

        if (!VMStructs::isSafeToWalk(saved_pc)) {
            frames->bci = BCI_NATIVE_FRAME;
            CodeBlob* codeBlob = VMStructs::libjvm()->find((const void*) saved_pc);
            if (codeBlob) {
                frames->method_id = (jmethodID) codeBlob->_name;
            } else {
                frames->method_id = (jmethodID) "unknown_unwalkable";
            }
            return 1;
        }
    } else {
        return 0;
    }

    int state = vm_thread->state();
    // from OpenJDK https://github.com/openjdk/jdk/blob/7455bb23c1d18224e48e91aae4f11fe114d04fab/src/hotspot/share/utilities/globalDefinitions.hpp#L1030
    /*
    enum JavaThreadState {
        _thread_uninitialized     =  0, // should never happen (missing initialization)
        _thread_new               =  2, // just starting up, i.e., in process of being initialized
        _thread_new_trans         =  3, // corresponding transition state (not used, included for completeness)
        _thread_in_native         =  4, // running in native code
        _thread_in_native_trans   =  5, // corresponding transition state
        _thread_in_vm             =  6, // running in VM
        _thread_in_vm_trans       =  7, // corresponding transition state
        _thread_in_Java           =  8, // running in Java or in stub code
        _thread_in_Java_trans     =  9, // corresponding transition state (not used, included for completeness)
        _thread_blocked           = 10, // blocked in vm
        _thread_blocked_trans     = 11, // corresponding transition state
        _thread_max_state         = 12  // maximum thread state+1 - used for statistics allocation
    };
     */
    bool in_java = (state == 8 || state == 9);
    if (in_java && java_ctx->sp) {
        // skip ahead to the Java frames before calling AGCT
        frame.restore((uintptr_t)java_ctx->pc, java_ctx->sp, java_ctx->fp);
    }
    // do not attempt to unwind
    bool in_native = (state == 4 || state == 5);
    if (in_native) {
        if (java_ctx->sp) {
            // skip ahead to the Java frames before calling AGCT
            frame.restore((uintptr_t)java_ctx->pc, java_ctx->sp, java_ctx->fp);
        } else {
            // we've tried to unwind some native code without frame pointers,
            // and we don't know where the top Java frame is, so we don't want to call AGCT
            return 0;
        }
    }

    JitWriteProtection jit(false);
    ASGCT_CallTrace trace = {jni, 0, frames};
    VM::_asyncGetCallTrace(&trace, max_depth, ucontext);

    if (trace.num_frames > 0) {
        frame.restore(saved_pc, saved_sp, saved_fp);
        return trace.num_frames;
    }

    if ((trace.num_frames == ticks_unknown_Java || trace.num_frames == ticks_not_walkable_Java) && !(_safe_mode & UNKNOWN_JAVA) && ucontext != NULL) {
        CodeBlob* stub = NULL;
        _stubs_lock.lockShared();
        if (_runtime_stubs.contains((const void*) frame.pc())) {
            stub = _runtime_stubs.find((const void*) frame.pc());
        }
        _stubs_lock.unlockShared();

        if (stub != NULL) {
            if (_cstack != CSTACK_NO) {
                max_depth -= makeFrame(trace.frames++, BCI_NATIVE_FRAME, stub->_name);
            }
            if (!(_safe_mode & POP_STUB) && frame.popStub((instruction_t*)stub->_start, stub->_name)
                    && isAddressInCode(frame.pc() -= ADJUST_RET)) {
                VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
            }
        } else if (VMStructs::hasMethodStructs()) {
            NMethod* nmethod = CodeHeap::findNMethod((const void*)frame.pc());
            if (nmethod != NULL && nmethod->isNMethod() && nmethod->isAlive()) {
                VMMethod* method = nmethod->method();
                if (method != NULL) {
                    jmethodID method_id = method->constMethod()->id();
                    if (method_id != NULL) {
                        max_depth -= makeFrame(trace.frames++, 0, method_id);
                    }
                    if (!(_safe_mode & POP_METHOD) && frame.popMethod((instruction_t*)nmethod->entry())
                            && isAddressInCode(frame.pc() -= ADJUST_RET)) {
                        VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
                    }
                }
            } else if (nmethod != NULL) {
                if (_cstack != CSTACK_NO) {
                    max_depth -= makeFrame(trace.frames++, BCI_NATIVE_FRAME, nmethod->name());
                }
                if (!(_safe_mode & POP_STUB) && frame.popStub(NULL, nmethod->name())
                        && isAddressInCode(frame.pc() -= ADJUST_RET)) {
                    VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
                }
            }
        }
    } else if (trace.num_frames == ticks_unknown_not_Java && !(_safe_mode & LAST_JAVA_PC)) {
        uintptr_t& sp = vm_thread->lastJavaSP();
        uintptr_t& pc = vm_thread->lastJavaPC();
        if (sp != 0 && pc == 0) {
            // We have the last Java frame anchor, but it is not marked as walkable.
            // Make it walkable here
            pc = ((uintptr_t*)sp)[-1];

            NMethod* m = CodeHeap::findNMethod((const void*)pc);
            if (m != NULL) {
                // AGCT fails if the last Java frame is a Runtime Stub with an invalid _frame_complete_offset.
                // In this case we patch _frame_complete_offset manually
                if (!m->isNMethod() && m->frameSize() > 0 && m->frameCompleteOffset() == -1) {
                    m->setFrameCompleteOffset(0);
                }
                VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
            } else if (findLibraryByAddress((const void*)pc) != NULL) {
                VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
            }

            pc = 0;
        }
    } else if (trace.num_frames == ticks_not_walkable_not_Java && !(_safe_mode & LAST_JAVA_PC)) {
        uintptr_t& sp = vm_thread->lastJavaSP();
        uintptr_t& pc = vm_thread->lastJavaPC();
        if (sp != 0 && pc != 0) {
            // Similar to the above: last Java frame is set,
            // but points to a Runtime Stub with an invalid _frame_complete_offset
            NMethod* m = CodeHeap::findNMethod((const void*)pc);
            if (m != NULL && !m->isNMethod() && m->frameSize() > 0 && m->frameCompleteOffset() == -1) {
                m->setFrameCompleteOffset(0);
                VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
            }
        }
    } else if (trace.num_frames == ticks_GC_active && !(_safe_mode & GC_TRACES)) {
        if (vm_thread->lastJavaSP() == 0) {
            // Do not add 'GC_active' for threads with no Java frames, e.g. Compiler threads
            frame.restore(saved_pc, saved_sp, saved_fp);
            return 0;
        }
    }

    frame.restore(saved_pc, saved_sp, saved_fp);

    if (trace.num_frames > 0) {
        return trace.num_frames + (trace.frames - frames);
    }

    const char* err_string = asgctError(trace.num_frames);
    if (err_string == NULL) {
        // No Java stack, because thread is not in Java context
        return 0;
    }

    atomicInc(_failures[-trace.num_frames]);
    trace.frames->bci = BCI_ERROR;
    trace.frames->method_id = (jmethodID)err_string;
    return trace.frames - frames + 1;
}

int Profiler::getJavaTraceJvmti(jvmtiFrameInfo* jvmti_frames, ASGCT_CallFrame* frames, int start_depth, int max_depth) {
    int num_frames;
    if (VM::jvmti()->GetStackTrace(NULL, start_depth, _max_stack_depth, jvmti_frames, &num_frames) == 0 && num_frames > 0) {
        return convertFrames(jvmti_frames, frames, num_frames);
    }
    return 0;
}

int Profiler::getJavaTraceInternal(jvmtiFrameInfo* jvmti_frames, ASGCT_CallFrame* frames, int max_depth) {
    // We cannot call pure JVM TI here, because it assumes _thread_in_native state,
    // but allocation events happen in _thread_in_vm state,
    // see https://github.com/jvm-profiling-tools/java-profiler/issues/64
    JNIEnv* jni = VM::jni();
    if (jni == NULL) {
        return 0;
    }

    JitWriteProtection jit(false);
    VMThread* vm_thread = VMThread::fromEnv(jni);
    int num_frames;
    if (VMStructs::_get_stack_trace(NULL, vm_thread, 0, max_depth, jvmti_frames, &num_frames) == 0 && num_frames > 0) {
        return convertFrames(jvmti_frames, frames, num_frames);
    }
    return 0;
}

inline int Profiler::convertFrames(jvmtiFrameInfo* jvmti_frames, ASGCT_CallFrame* frames, int num_frames) {
    // Convert to AsyncGetCallTrace format.
    // Note: jvmti_frames and frames may overlap.
    for (int i = 0; i < num_frames; i++) {
        jint bci = jvmti_frames[i].location;
        frames[i].method_id = jvmti_frames[i].method;
        frames[i].bci = bci;
    }
    return num_frames;
}

void Profiler::fillFrameTypes(ASGCT_CallFrame* frames, int num_frames, NMethod* nmethod) {
    if (nmethod->isNMethod() && nmethod->isAlive()) {
        VMMethod* method = nmethod->method();
        if (method == NULL) {
            return;
        }

        jmethodID current_method_id = method->constMethod()->id();
        if (current_method_id == NULL) {
            return;
        }

        // Mark current_method as COMPILED and frames above current_method as INLINED
        for (int i = 0; i < num_frames; i++) {
            if (frames[i].method_id == NULL || frames[i].bci <= BCI_NATIVE_FRAME) {
                break;
            }
            if (frames[i].method_id == current_method_id) {
                int level = nmethod->level();
                frames[i].bci = FrameType::encode(level >= 1 && level <= 3 ? FRAME_C1_COMPILED : FRAME_JIT_COMPILED, frames[i].bci);
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

void Profiler::recordExternalSample(u64 counter, int tid, jvmtiFrameInfo *jvmti_frames, jint num_jvmti_frames, bool truncated, jint event_type, Event* event) {
    atomicInc(_total_samples);

    u32 lock_index = getLockIndex(tid);
    if (!_locks[lock_index].tryLock() &&
        !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
        !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock())
    {
        // Too many concurrent signals already
        atomicInc(_failures[-ticks_skipped]);

        if (event_type == BCI_CPU && _cpu_engine == &perf_events) {
            // Need to reset PerfEvents ring buffer, even though we discard the collected trace
            PerfEvents::resetBuffer(tid);
        }
        return;
    }
    u32 call_trace_id = 0;
    if (!_omit_stacktraces) {
        ASGCT_CallFrame *frames = _calltrace_buffer[lock_index]->_asgct_frames;

        int num_frames = 0;
        if (!_jfr.active() && BCI_ALLOC >= event_type && event_type >= BCI_PARK && event->_id) {
            num_frames = makeFrame(frames, event_type, event->_id);
        }

        num_frames += convertFrames(jvmti_frames, frames + num_frames, num_jvmti_frames);

        call_trace_id = _call_trace_storage.put(num_frames, frames, truncated, counter);
    }
    _jfr.recordEvent(lock_index, tid, call_trace_id, event_type, event, counter);

    _locks[lock_index].unlock();
}

void Profiler::recordSample(void* ucontext, u64 counter, int tid, jint event_type, Event* event) {
    atomicInc(_total_samples);

    u32 lock_index = getLockIndex(tid);
    if (!_locks[lock_index].tryLock() &&
        !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
        !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock())
    {
        // Too many concurrent signals already
        atomicInc(_failures[-ticks_skipped]);

        if (event_type == BCI_CPU && _cpu_engine == &perf_events) {
            // Need to reset PerfEvents ring buffer, even though we discard the collected trace
            PerfEvents::resetBuffer(tid);
        }
        return;
    }

    bool truncated = false;
    // in lightweight mode we're just sampling the the context associated with the passage of CPU or wall time,
    // we use the same event definitions but we record a null stacktrace
    u32 call_trace_id = 0;
    if (!_omit_stacktraces) {
        ASGCT_CallFrame *frames = _calltrace_buffer[lock_index]->_asgct_frames;
        jvmtiFrameInfo *jvmti_frames = _calltrace_buffer[lock_index]->_jvmti_frames;

        int num_frames = 0;

        StackContext java_ctx = {0};
        ASGCT_CallFrame *native_stop = frames + num_frames;
        num_frames += getNativeTrace(ucontext, native_stop, event_type, tid, &java_ctx, &truncated);

        if (event_type == BCI_CPU || event_type == BCI_WALL) {
            // Async events
            int java_frames = getJavaTraceAsync(ucontext, frames + num_frames, _max_stack_depth, &java_ctx, &truncated);
            if (java_frames > 0 && java_ctx.pc != NULL) {
                NMethod *nmethod = CodeHeap::findNMethod(java_ctx.pc);
                if (nmethod != NULL) {
                    fillFrameTypes(frames + num_frames, java_frames, nmethod);
                }
            }
            num_frames += java_frames;
        } else if (event_type >= BCI_ALLOC_OUTSIDE_TLAB && VMStructs::_get_stack_trace != NULL) {
            // Object allocation in HotSpot happens at known places where it is safe to call JVM TI,
            // but not directly, since the thread is in_vm rather than in_native
            num_frames += getJavaTraceInternal(jvmti_frames + num_frames, frames + num_frames, _max_stack_depth);
        } else if (event_type >= BCI_ALLOC_OUTSIDE_TLAB && !VM::isOpenJ9()) {
            num_frames += getJavaTraceAsync(ucontext, frames + num_frames, _max_stack_depth, &java_ctx, &truncated);
        } else {
            // Lock events can safely call synchronous JVM TI stack walker.
            num_frames += getJavaTraceJvmti(jvmti_frames + num_frames, frames + num_frames, 0, _max_stack_depth);
        }

        if (num_frames == 0) {
            num_frames += makeFrame(frames + num_frames, BCI_ERROR, "no_Java_frame");
        }

        call_trace_id = _call_trace_storage.put(num_frames, frames, truncated, counter);
    }
    _jfr.recordEvent(lock_index, tid, call_trace_id, event_type, event, counter);

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

void Profiler::recordExternalSample(u64 counter, int tid, int num_frames, ASGCT_CallFrame* frames, bool truncated, jint event_type, Event* event) {
    atomicInc(_total_samples);

    u32 call_trace_id = _call_trace_storage.put(num_frames, frames, truncated, counter);

    u32 lock_index = getLockIndex(tid);
    if (!_locks[lock_index].tryLock() &&
        !_locks[lock_index = (lock_index + 1) % CONCURRENCY_LEVEL].tryLock() &&
        !_locks[lock_index = (lock_index + 2) % CONCURRENCY_LEVEL].tryLock())
    {
        // Too many concurrent signals already
        atomicInc(_failures[-ticks_skipped]);
        return;
    }

    _jfr.recordEvent(lock_index, tid, call_trace_id, event_type, event, counter);

    _locks[lock_index].unlock();
}

void Profiler::writeLog(LogLevel level, const char* message) {
    _jfr.recordLog(level, message, strlen(message));
}

void Profiler::writeLog(LogLevel level, const char* message, size_t len) {
    _jfr.recordLog(level, message, len);
}

void Profiler::writeDatadogProfilerSetting(int tid, int length, const char* name, const char* value, const char* unit) {
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

void* Profiler::dlopen_hook(const char* filename, int flags) {
    void* result = dlopen(filename, flags);
    if (result != NULL) {
        instance()->updateSymbols(false);
    }
    return result;
}

void Profiler::switchLibraryTrap(bool enable) {
    void* impl = enable ? (void*)dlopen_hook : (void*)dlopen;
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

void Profiler::segvHandler(int signo, siginfo_t* siginfo, void* ucontext) {
    StackFrame frame(ucontext);

    uintptr_t length = SafeAccess::skipFaultInstruction(frame.pc());
    if (length > 0) {
        // Skip the fault instruction, as if it successfully loaded NULL
        frame.pc() += length;
        frame.retval() = 0;
        return;
    }

    if (WX_MEMORY && Trap::isFaultInstruction(frame.pc())) {
        return;
    }

    orig_segvHandler(signo, siginfo, ucontext);
}

void Profiler::setupSignalHandlers() {
    if (VM::java_version() > 0) {
        // HotSpot tolerates interposed SIGSEGV/SIGBUS handler; other JVMs probably not
        orig_segvHandler = OS::replaceCrashHandler(segvHandler);
    }
}

void Profiler::setThreadInfo(int tid, const char* name, jlong java_thread_id) {
    MutexLocker ml(_thread_names_lock);
    _thread_names[tid] = name;
    _thread_ids[tid] = java_thread_id;
}

void Profiler::updateThreadName(jvmtiEnv* jvmti, JNIEnv* jni, jthread thread) {
    JitWriteProtection jit(true);  // workaround for JDK-8262896
    jvmtiThreadInfo thread_info;
    int native_thread_id = VMThread::nativeThreadId(jni, thread);
    if (native_thread_id >= 0 && jvmti->GetThreadInfo(thread, &thread_info) == 0) {
        jlong java_thread_id = VMThread::javaThreadId(jni, thread);
        setThreadInfo(native_thread_id, thread_info.name, java_thread_id);
        jvmti->Deallocate((unsigned char*)thread_info.name);
    }
}

void Profiler::updateJavaThreadNames() {
    jvmtiEnv* jvmti = VM::jvmti();
    jint thread_count;
    jthread* thread_objects;
    if (jvmti->GetAllThreads(&thread_count, &thread_objects) != 0) {
        return;
    }

    JNIEnv* jni = VM::jni();
    for (int i = 0; i < thread_count; i++) {
        updateThreadName(jvmti, jni, thread_objects[i]);
    }

    jvmti->Deallocate((unsigned char*)thread_objects);
}

void Profiler::updateNativeThreadNames() {
    ThreadList* thread_list = OS::listThreads();
    char name_buf[64];

    for (int tid; (tid = thread_list->next()) != -1; ) {
        MutexLocker ml(_thread_names_lock);
        std::map<int, std::string>::iterator it = _thread_names.lower_bound(tid);
        if (it == _thread_names.end() || it->first != tid) {
            if (OS::threadName(tid, name_buf, sizeof(name_buf))) {
                _thread_names.insert(it, std::map<int, std::string>::value_type(tid, name_buf));
            }
        }
    }

    delete thread_list;
}

Engine* Profiler::selectCpuEngine(Arguments& args) {
    if (args._cpu < 0 && (args._event == NULL || strcmp(args._event, EVENT_NOOP) == 0)) {
        return &noop_engine;
    } else if (args._cpu >= 0 || strcmp(args._event, EVENT_CPU) == 0) {
        if (VM::isOpenJ9() && !J9Ext::can_use_ASGCT()) {
            // signal based samplers are unstable on J9 before 8.0.362, 11.0.18 and 17.0.6
            return (Engine*)&j9_engine;
        }
        return !perf_events.check(args) ? (Engine*)&perf_events : &itimer;
    } else if (strcmp(args._event, EVENT_WALL) == 0) {
        return (Engine*)&noop_engine;
    } else if (strcmp(args._event, EVENT_ITIMER) == 0) {
        return &itimer;
    } else {
        return &perf_events;
    }
}

Engine* Profiler::selectWallEngine(Arguments& args) {
    if (args._wall < 0 && (args._event == NULL || strcmp(args._event, EVENT_WALL) != 0)) {
        return &noop_engine;
    }
    if (VM::isOpenJ9() && !J9Ext::can_use_ASGCT()) {
        j9_engine.sampleIdleThreads();
        return (Engine*)&j9_engine;
    }
    return (Engine*)&wall_engine;
}

Engine* Profiler::selectAllocEngine(Arguments& args) {
    if (VM::canSampleObjects()) {
        return static_cast<Engine*>(ObjectSampler::instance());
    } else {
        Log::info("Not enabling the alloc profiler, SampledObjectAlloc is not supported on this JVM");
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

    if (_dlopen_entry == NULL) {
        CodeCache* lib = findJvmLibrary("libj9prt");
        if (lib == NULL || (_dlopen_entry = lib->findGlobalOffsetEntry((void*)dlopen)) == NULL) {
            return Error("Could not set dlopen hook. Unsupported JVM?");
        }
    }

    if (!VMStructs::hasDebugSymbols() && !VM::isOpenJ9()) {
        Log::warn("Install JVM debug symbols to improve profile accuracy");
    }

    return Error::OK;
}

Error Profiler::start(Arguments& args, bool reset) {
    MutexLocker ml(_state_lock);
    if (_state > IDLE) {
        return Error("Profiler already started");
    }

    Error error = checkJvmCapabilities();
    if (error) {
        return error;
    }

    ProfiledThread::initExistingThreads();
    _omit_stacktraces = args._lightweight;
    _event_mask = ((args._event != NULL && strcmp(args._event, EVENT_NOOP) != 0) ? EM_CPU : 0) |
                  (args._cpu >= 0 ? EM_CPU : 0) |
                  (args._wall >= 0 ? EM_WALL : 0) |
                  (args._memory >= 0 ? EM_ALLOC : 0);
    if (_event_mask == 0) {
        return Error("No profiling events specified");
    }

    if (reset || _start_time == 0) {
        // Reset counters
        _total_samples = 0;
        memset(_failures, 0, sizeof(_failures));

        // Reset dictionaries and bitmaps
        // Reset class map under lock because ObjectSampler may try to use it while it is being cleaned up
        _class_map_lock.lock();
        _class_map.clear();
        _class_map_lock.unlock();

        // Reset call trace storage
        if (!_omit_stacktraces) {
            lockAll();
            _call_trace_storage.clear();
            unlockAll();
        }

        // Reset thread names and IDs
        MutexLocker ml(_thread_names_lock);
        _thread_names.clear();
        _thread_ids.clear();
    }

    // (Re-)allocate calltrace buffers
    if (_max_stack_depth != args._jstackdepth) {
        _max_stack_depth = args._jstackdepth;
        size_t buffer_size = (_max_stack_depth + MAX_NATIVE_FRAMES + RESERVED_FRAMES) * sizeof(CallTraceBuffer);

        for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
            free(_calltrace_buffer[i]);
            _calltrace_buffer[i] = (CallTraceBuffer*)malloc(buffer_size);
            if (_calltrace_buffer[i] == NULL) {
                _max_stack_depth = 0;
                return Error("Not enough memory to allocate stack trace buffers (try smaller jstackdepth)");
            }
        }
    }

    _safe_mode = args._safe_mode;
    if (VM::java_version() < 8 || VM::isZing()) {
        _safe_mode |= GC_TRACES | LAST_JAVA_PC;
    }

    _thread_filter.init(args._filter);

    _cpu_engine = selectCpuEngine(args);
    _wall_engine = selectWallEngine(args);
    _cstack = args._cstack;
    if (_cstack == CSTACK_DWARF && !DWARF_SUPPORTED) {
        return Error("DWARF unwinding is not supported on this platform");
    } else if (_cstack == CSTACK_LBR && _cpu_engine != &perf_events) {
        return Error("Branch stack is supported only with PMU events");
    }

    // Kernel symbols are useful only for perf_events without --all-user
    updateSymbols(_cpu_engine == &perf_events && (args._ring & RING_KERNEL));

    enableEngines();

    switchLibraryTrap(_cstack == CSTACK_DWARF);

    JfrMetadata::initialize(args._context_attributes);
    _num_context_attributes = args._context_attributes.size();
    error = _jfr.start(args, reset);
    if (error) {
        disableEngines();
        switchLibraryTrap(false);
        return error;
    }

    int activated = 0;
    if (_event_mask & EM_CPU) {
        error = _cpu_engine->start(args);
        if (error) {
            Log::warn("%s", error.message());
            error = Error::OK; // recoverable
        } else {
            activated |= EM_CPU;
        }
    }
    if (_event_mask & EM_WALL) {
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
        error = _alloc_engine->start(args);
        if (error) {
            Log::warn("%s", error.message());
            error = Error::OK; // recoverable
        } else {
            activated |= EM_ALLOC;
        }
    }

    if (activated) {
        switchThreadEvents(JVMTI_ENABLE);

        _state = RUNNING;
        _start_time = time(NULL);
        _epoch++;

        return Error::OK;
    }
    // no engine was activated; perform cleanup
    disableEngines();
    switchLibraryTrap(false);

    lockAll();
    _jfr.stop();
    unlockAll();

    return Error("Neither CPU, wallclock nor allocation profiling could be started");
}

Error Profiler::stop() {
    MutexLocker ml(_state_lock);
    if (_state != RUNNING) {
        return Error("Profiler is not active");
    }

    disableEngines();

    if (_event_mask & EM_ALLOC) _alloc_engine->stop();
    if (_event_mask & EM_WALL) _wall_engine->stop();
    if (_event_mask & EM_CPU) _cpu_engine->stop();

    switchLibraryTrap(false);
    switchThreadEvents(JVMTI_DISABLE);
    updateJavaThreadNames();
    updateNativeThreadNames();

    // Acquire all spinlocks to avoid race with remaining signals
    lockAll();
    _jfr.stop();
    unlockAll();

    Counters::set(THREAD_IDS_COUNT, _thread_ids.size());
    Counters::set(THREAD_NAMES_COUNT, _thread_names.size());

    _state = IDLE;
    return Error::OK;
}

Error Profiler::check(Arguments& args) {
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

Error Profiler::dump(const char* path, const int length) {
    MutexLocker ml(_state_lock);
    if (_state != IDLE && _state != RUNNING) {
        return Error("Profiler has not started");
    }

    if (_state == RUNNING) {
        std::set<int> thread_ids;
        // flush the liveness tracker instance and note all the threads referenced by the live objects
        LivenessTracker::instance()->flush(thread_ids);

        updateJavaThreadNames();
        updateNativeThreadNames();
        
        lockAll();
        Error err = _jfr.dump(path, length);
        
        // Reset calltrace storage
        if (!_omit_stacktraces) {
            _call_trace_storage.clear();
        }
        unlockAll();
        // Reset classmap
        _class_map_lock.lock();
        _class_map.clear();
        _class_map_lock.unlock();

        // // Reset thread names and IDs
        MutexLocker ml(_thread_names_lock);
        if (thread_ids.empty()) {
            // take the fast path
            _thread_names.clear();
            _thread_ids.clear();
        } else {
            // we need to honor the thread referenced from th liveness tracker
            std::map<int, std::string>::iterator name_itr = _thread_names.begin();
            while (name_itr != _thread_names.end()) {
                if (thread_ids.find(name_itr->first) != thread_ids.end()) {
                    name_itr = _thread_names.erase(name_itr);
                } else {
                    ++name_itr;
                }
            }
            std::map<int, jlong>::iterator id_itr = _thread_ids.begin();
            while (id_itr != _thread_ids.end()) {
                if (thread_ids.find(name_itr->first) != thread_ids.end()) {
                    id_itr = _thread_ids.erase(id_itr);
                } else {
                    ++id_itr;
                }
            }
        }

        Counters::set(THREAD_IDS_COUNT, _thread_ids.size());
        Counters::set(THREAD_NAMES_COUNT, _thread_names.size());

        return err;
    }

    return Error::OK;
}

void Profiler::lockAll() {
    for (int i = 0; i < CONCURRENCY_LEVEL; i++) _locks[i].lock();
}

void Profiler::unlockAll() {
    for (int i = 0; i < CONCURRENCY_LEVEL; i++) _locks[i].unlock();
}

void Profiler::switchThreadEvents(jvmtiEventMode mode) {
    if (_thread_events_state != mode) {
        jvmtiEnv* jvmti = VM::jvmti();
        jvmti->SetEventNotificationMode(mode, JVMTI_EVENT_THREAD_START, NULL);
        jvmti->SetEventNotificationMode(mode, JVMTI_EVENT_THREAD_END, NULL);
        _thread_events_state = mode;
    }
}

Error Profiler::runInternal(Arguments& args, std::ostream& out) {
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
            // Fall through
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
                for (int event_id = 1; ; event_id++) {
                    const char* event_name = PerfEvents::getEventName(event_id);
                    if (event_name == NULL) break;
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

Error Profiler::run(Arguments& args) {
    return runInternal(args, std::cout);
}

Error Profiler::restart(Arguments& args) {
    MutexLocker ml(_state_lock);

    Error error = stop();
    if (error) {
        return error;
    }

    return Error::OK;
}

void Profiler::shutdown(Arguments& args) {
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

int Profiler::lookupClass(const char* key, size_t length) {
    if (_class_map_lock.tryLockShared()) {
        int ret = _class_map.lookup(key, length);
        _class_map_lock.unlockShared();
        return ret;
    }
    // unable to lookup the class
    return -1;
}
