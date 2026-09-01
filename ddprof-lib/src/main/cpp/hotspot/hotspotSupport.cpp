/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <climits>
#include <cstdlib>
#include "asyncSampleMutex.h"
#include "faultInjection.h"
#include "frames.h"
#include "guards.h"
#include "hotspot/hotspotSupport.h"
#include "hotspot/jitCodeCache.h"
#include "hotspot/vmStructs.inline.h"
#include "jvmSupport.inline.h"
#include "jvmThread.h"
#include "profiler.h"
#include "stackWalker.inline.h"
#include "threadLocal.h"
#include "threadLocalData.inline.h"

using StackWalkValidation::inDeadZone;
using StackWalkValidation::aligned;
using StackWalkValidation::MAX_FRAME_SIZE;

// Initialize once, they survive on profiler restart
static jobject JAVA_PLATFORM_CLASSLOADER = nullptr;
static jobject JAVA_APPLICATION_CLASSLOADER = nullptr;

void HotspotSupport::initClassloaderInfo(JNIEnv* jni) {
    if (JAVA_APPLICATION_CLASSLOADER != nullptr &&
        (JAVA_PLATFORM_CLASSLOADER != nullptr || VM::hotspot_version() == 8)) {
        return;
    }

    jclass classLoaderClass = jni->FindClass("java/lang/ClassLoader");
    if (classLoaderClass == nullptr) {
        jni->ExceptionClear();
        return;
    }

    jmethodID getSysLoaderMethod = jni->GetStaticMethodID(classLoaderClass,
                                                          "getSystemClassLoader",
                                                          "()Ljava/lang/ClassLoader;");
    if (getSysLoaderMethod == nullptr) {
        jni->ExceptionClear();
    }

    jmethodID getPlatformLoaderMethod = jni->GetStaticMethodID(classLoaderClass,
                                                          "getPlatformClassLoader",
                                                          "()Ljava/lang/ClassLoader;");
    // JDK8 does not have platform class loader
    if (getPlatformLoaderMethod == nullptr) {
        jni->ExceptionClear();
    }

    if (getSysLoaderMethod != nullptr) {
        jobject ret = jni->CallStaticObjectMethod(classLoaderClass, getSysLoaderMethod);
        if (ret != nullptr) {
            JAVA_APPLICATION_CLASSLOADER = jni->NewGlobalRef(ret);
            jni->DeleteLocalRef(ret);
        }
    }

    if (getPlatformLoaderMethod != nullptr) {
        jobject ret = jni->CallStaticObjectMethod(classLoaderClass, getPlatformLoaderMethod);
        if (ret != nullptr) {
            JAVA_PLATFORM_CLASSLOADER = jni->NewGlobalRef(ret);
            jni->DeleteLocalRef(ret);
        }
    }

    if (jni->ExceptionCheck()) {
        jni->ExceptionClear();
    }

    jni->DeleteLocalRef(classLoaderClass);
}

static bool isAddressInCode(const void *pc, bool include_stubs = true) {
  if (CodeHeap::contains(pc)) {
    return CodeHeap::findNMethod(pc) != NULL &&
           (include_stubs || !JitCodeCache::isCallStub(pc));
  } else {
    return Profiler::instance()->libraries()->findLibraryByAddress(pc) != NULL;
  }
}

static jmethodID getMethodId(VMMethod* method) {
    if (!inDeadZone(method) && aligned((uintptr_t)method)
            && SafeAccess::isReadableRange(method, VMMethod::type_size())) {
        return method->validatedId();
    }
    return JMETHODID_NOT_WALKABLE;
}

/**
 * Converts a BCI_* frame type value to the corresponding EventType enum value.
 *
 * This conversion is necessary because Datadog's implementation uses BCI_* values
 * (from ASGCT_CallFrameType) directly as event type identifiers, while upstream
 * HotspotSupport::walkVM() expects EventType enum values for its logic.
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
        case BCI_NATIVE_MALLOC:
            return MALLOC_SAMPLE;
        case BCI_NATIVE_SOCKET:
            return SOCKET_SAMPLE;
        default:
            // For unknown or invalid BCI types, default to EXECUTION_SAMPLE
            // This maintains backward compatibility and prevents undefined behavior
            return EXECUTION_SAMPLE;
    }
}

static bool hasTheSameMethod(ASGCT_CallFrame& frame, jmethodID method_id, const VMMethod* method) {
    if (FrameType::isRawPointer(frame.bci)) {
        return frame.method == method;
    } else {
        return frame.method_id == method_id;
    }
}

static void fillFrameTypes(ASGCT_CallFrame *frames, int num_frames, VMNMethod *nmethod) {
  if (nmethod->isNMethod() && nmethod->isAlive()) {
    VMMethod *method = nmethod->method();
    if (method == NULL) {
      return;
    }

    jmethodID current_method_id = method->id();
    if (!isValidJMethodID(current_method_id)) {
      return;
    }

    // Mark current_method as COMPILED and frames above current_method as
    // INLINED
    for (int i = 0; i < num_frames; i++) {
      // method_id == nullptr, also means method == nullptr
      if (frames[i].method_id == NULL || frames[i].bci <= BCI_NATIVE_FRAME) {
        break;
      }
      if (hasTheSameMethod(frames[i], current_method_id, method)) {
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

// Fill the frame with raw method pointer
static void fillFrameRaw(ASGCT_CallFrame& frame, FrameTypeId type, int bci, const VMMethod* method) {
    NO_INJECTION_ASSERT(method != nullptr);
    frame.bci = FrameType::encode(type, bci, true /*raw method pointer*/);
    frame.method = static_cast<const void*>(method);
}

void HotspotSupport::fillJavaFrame(ASGCT_CallFrame& frame, FrameTypeId type, int bci,
                                   jmethodID method_id, const VMMethod* method) {
    if (method_id == JMETHODID_NOT_WALKABLE) {
        // The Method* failed validation while walking (bad pointer chain or
        // faulted load). Preserve only the sentinel; retaining the Method*
        // would defer a dereference of invalid metadata until the dump thread
        // resolves the frame.
        fillFrame(frame, type, bci, method_id);
    } else if (method_id != nullptr) {
        fillFrame(frame, type, bci, method_id);
    } else if (!Profiler::instance()->forceJmethodID()) {
        // fjmethodid=false: the user opted into the raw Method* path. nullptr
        // means no jmethodID is available — either the klass was deliberately
        // not primed (ids == NULL) or the cache was shrunk by a redefine
        // (num >= len). In both cases the raw Method* is the designed
        // resolution path; the deferred-dereference race at dump time is
        // inherent to this mode.
        NO_INJECTION_ASSERT(method != nullptr);
        fillFrameRaw(frame, type, bci, method);
    } else {
        // fjmethodid=true: all jmethodIDs should be preloaded, so nullptr is
        // unexpected — a transient invalidation window or a missed preload.
        // Use the sentinel rather than deferring a raw Method* dereference to
        // the dump thread, where the metadata may have been reclaimed.
        fillFrame(frame, type, bci, JMETHODID_NOT_WALKABLE);
    }
}

static ucontext_t empty_ucontext{};

#ifdef NDEBUG
static const bool CONT_UNWIND_DISABLED = false;
#else
// DEBUG-only: when set, both continuation-unwind detection branches
// (cont_entry_return_pc for fully-thawed VTs, cont_returnBarrier for VTs
// with frozen frames) are skipped, reproducing pre-fix behaviour.
// Used by negative integration tests to verify that carrier frames are not
// visible and walk-error sentinels do appear without the fix.
// NOTE: the env var is evaluated once at library load time; it must be set
// in the environment before the profiler agent is attached.
static const bool CONT_UNWIND_DISABLED = (std::getenv("DDPROF_DISABLE_CONT_UNWIND") != nullptr);
#endif

__attribute__((no_sanitize("address"))) int HotspotSupport::walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                        StackWalkFeatures features, EventType event_type, int lock_index, bool* truncated) {
    if (ucontext == NULL) {
        return walkVM(&empty_ucontext, frames, max_depth, features, event_type,
                      callerPC(), (uintptr_t)callerSP(), (uintptr_t)callerFP(), lock_index, truncated);
    } else {
        HotspotStackFrame frame(ucontext);
        return walkVM(ucontext, frames, max_depth, features, event_type,
                      (const void*)frame.pc(), frame.sp(), frame.fp(), lock_index, truncated);
    }
}

__attribute__((no_sanitize("address"))) int HotspotSupport::walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                        StackWalkFeatures features, EventType event_type,
                        const void* pc, uintptr_t sp, uintptr_t fp, int lock_index, bool* truncated) {

    // VMStructs is only available for hotspot JVM 
    assert(VM::isHotspot());

    ProfiledThread* prof_thread = ProfiledThread::acquireCurrent();
    if (prof_thread == nullptr) {
        Counters::increment(SAMPLES_DROPPED_THREAD_LOCAL);
        return 0;
    }
    
    // reset=false: the buffer only needs clearing after a failure was actually
    // recorded into it (done below, right after merging into UnwindStats), not
    // on every walk — clear() memsets ~288 KiB and this runs on the hot sample
    // path in DEBUG/ASan/TSan builds.
    DEBUG_ONLY(UnwindFailures* unwindFailures = prof_thread->unwindFailures(false);)

    HotspotStackFrame frame(ucontext);
    uintptr_t bottom = (uintptr_t)&frame + MAX_WALK_SIZE;

    Profiler* profiler = Profiler::instance();
    int bcp_offset = InterpreterFrame::bcp_offset();


    sigjmp_buf crash_protection_ctx;
    // Chaining sigjmp_buf
    // A non-signal-based-sampler can be interrupted by signal based sampler,
    // then we end up with multiple HotspotSupport::walkVM() calls on stack,
    // each one sets up sigjmp_buf, they need to be chained to jump back to
    // correct location.
    JmpCtxScope jmp_scope(prof_thread);
    // Should be preserved across sigsetjmp/siglongjmp
    volatile int depth = 0;
    int actual_max_depth = truncated ? max_depth + 1 : max_depth;

    if (sigsetjmp(crash_protection_ctx, 1) != 0) {
        // checkFault() does a siglongjmp from inside segvHandler, bypassing
        // segvHandler's SignalHandlerScope destructor.  Compensate.
        SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
        jmp_scope.restore();
        if (depth < max_depth) {
            fillFrame(frames[depth++], BCI_ERROR, "break_not_walkable");
        }
#ifdef DEBUG
        if (unwindFailures) {
            UnwindStats::recordFailures(unwindFailures);
            unwindFailures->clear();
        }
#endif // DEBUG
        return depth;
    }

    jmp_scope.install(&crash_protection_ctx);
    VMThread* vm_thread = VMThread::current();
    if (vm_thread != NULL && !vm_thread->isThreadAccessible()) {
        Counters::increment(WALKVM_THREAD_INACCESSIBLE);
        vm_thread = NULL;
    }
    if (vm_thread == NULL) {
        Counters::increment(WALKVM_NO_VMTHREAD);
    } else {
        Counters::increment(WALKVM_VMTHREAD_OK);
    }

    bool fp_chain_fallback = false;
    int fp_chain_depth = 0;

    VMJavaFrameAnchor* anchor = NULL;
    if (vm_thread != NULL) {
        anchor = vm_thread->anchor();
        if (anchor == NULL) {
            Counters::increment(WALKVM_ANCHOR_NULL);
        }
    }

    const void* prev_native_pc = NULL;

    // Last ContinuationEntry crossed; advanced via parent() for nested continuations.
    VMContinuationEntry* cont_entry = nullptr;

    // Saved anchor data — preserved across anchor consumption so inline
    // recovery can redirect even after the anchor pointer has been set to NULL.
    // Recovery is one-shot: once attempted, we do not retry to avoid
    // ping-ponging between CodeHeap and unmapped native regions.
    const void* saved_anchor_pc = NULL;
    uintptr_t saved_anchor_sp = 0;
    uintptr_t saved_anchor_fp = 0;
    bool anchor_recovery_used = false;

    // Set once the MARK_JAVA_PROFILER hook boundary is found for a
    // malloc/socket sample — mirrors skip_hook_prefix/skipping in
    // Profiler::convertNativeTrace so the same "boundary never found"
    // condition is observable from walkVM.
    bool hook_boundary_found = false;

    // Show extended frame types and stub frames for execution-type events
    bool details = event_type <= SOCKET_SAMPLE || features.mixed;

    if (details && vm_thread != NULL && VMThread::isJavaThread(vm_thread)) {
        anchor = vm_thread->anchor();
    }

    static const char* CONT_ROOT_FRAME = "JVM Continuation";

    // Advances through a continuation boundary to the carrier frame.
    // Without carrier_frames (default, cstack=vm): always stops with a "JVM Continuation"
    // synthetic root frame — VT frames are complete, carrier internals are noise.
    // With carrier_frames (cstack=vmx): attempts to walk through; failures emit BCI_ERROR
    // so the sample is truthfully marked truncated.
    // Walks cont_entry->parent() on repeated calls to handle nested continuations
    // (_parent not triggered by standard single-level VTs today, but required
    // once any runtime layers continuations on top of VTs).
    //
    // all_frames_thawed: true when the bottom VT frame's return PC is
    //         cont_entry_return_pc (all VT frames are thawed — CPU-bound VT),
    //         false when it is cont_returnBarrier (frozen frames remain in the
    //         StackChunk — VT parked and just remounted).
    //         Needed to derive entry_fp on JDK 21-26 where ContinuationEntry
    //         type size is absent from vmStructs and contEntry() returns nullptr.
    //
    // Returns true to continue the walk, false to break.
    auto walkThroughContinuation = [&](bool all_frames_thawed) -> bool {
        if (depth >= actual_max_depth) return false;
        if (!features.carrier_frames) {
            fillFrame(frames[depth++], BCI_NATIVE_FRAME, CONT_ROOT_FRAME);
            return false;
        }

        uintptr_t entry_fp;

        if (VMContinuationEntry::type_size() > 0) {
            // ContinuationEntry is known via vmStructs (JDK 27+, added by
            // JDK-8378985).  Walk the linked list of entries for nested-
            // continuation support and derive the enterSpecial frame FP from
            // the struct layout (entry + type_size).
            cont_entry = (cont_entry != nullptr) ? cont_entry->parent() : vm_thread->contEntry();
            if (cont_entry == nullptr) {
                Counters::increment(WALKVM_CONT_ENTRY_NULL);
                fillFrame(frames[depth++], BCI_ERROR, "break_cont_entry_null");
                return false;
            }
            entry_fp = cont_entry->entryFP();
        } else {
            // ContinuationEntry absent from vmStructs (JDK 21-26).
            // Derive the enterSpecial frame FP from the current fp:
            //   all frames thawed (pc == cont_entry_return_pc): fp IS the
            //     enterSpecial frame FP.
            //   frozen frames remain (pc == cont_returnBarrier): the saved
            //     caller FP at *fp leads to the enterSpecial frame on the
            //     carrier stack.
            // Nested continuation tracking is unavailable without type_size().
            entry_fp = all_frames_thawed ? fp : (uintptr_t)SafeAccess::load((void**)fp);
        }

        if (!StackWalkValidation::isValidFP(entry_fp)) {
            fillFrame(frames[depth++], BCI_ERROR, "break_cont_entry_fp");
            return false;
        }
        // entry_fp has been range-checked by isValidFP above; any remaining
        // SIGSEGV from a stale/concurrently-freed pointer is caught by the
        // sigsetjmp crash protection in walkVM (checkFault -> siglongjmp).
        uintptr_t* carrier_fp_addr = (uintptr_t*)INJECT_FAULT_ADDRESS_UNLIKELY(entry_fp);
        uintptr_t carrier_fp = *carrier_fp_addr;
        const void* carrier_pc = ((const void**)carrier_fp_addr)[FRAME_PC_SLOT];
        uintptr_t carrier_sp = entry_fp + (FRAME_PC_SLOT + 1) * sizeof(void*);
        if (!StackWalkValidation::isValidFP(carrier_fp) ||
            StackWalkValidation::inDeadZone(carrier_pc) ||
            !StackWalkValidation::isValidSP(carrier_sp, sp, bottom)) {
            fillFrame(frames[depth++], BCI_ERROR, "break_cont_carrier_sp");
            return false;
        }
        sp = carrier_sp;
        fp = carrier_fp;
        pc = carrier_pc;
        return true;
    };

    unwind_loop:

    // Walk until the bottom of the stack or until the first Java frame
    while (depth < actual_max_depth) {
        if (CodeHeap::contains(pc)) {
            Counters::increment(WALKVM_HIT_CODEHEAP);
            if (fp_chain_fallback) {
                Counters::increment(WALKVM_FP_CHAIN_REACHED_CODEHEAP);
                fp_chain_fallback = false;
                fp_chain_depth = 0;
            }
            // If we're in JVM-generated code but don't have a VMThread, we cannot safely
            // walk the Java stack because crash protection is not set up.
            //
            // This can occur during JNI attach/detach transitions: when a thread detaches,
            // pthread_setspecific() clears the VMThread TLS, but if a profiling signal arrives
            // while PC is still in JVM stubs (JavaCalls, method entry/exit), we see CodeHeap
            // code without VMThread context.
            //
            // Without vm_thread, crash protection via sigsetjmp/siglongjmp cannot work
            // (checkFault() needs vm_thread->exception() to siglongjmp). Any memory dereference in interpreter
            // frame handling or NMethod validation would crash the process with unrecoverable SEGV.
            //
            // The missing VMThread is a timing issue during thread lifecycle.
            if (vm_thread == NULL) {
                Counters::increment(WALKVM_CODEH_NO_VM);
                fillFrame(frames[depth++], BCI_ERROR, "break_no_vmthread");
                break;
            }
            prev_native_pc = NULL; // we are in JVM code, no previous 'native' PC
            // Both continuation boundary PCs are JVM stubs whose findNMethod()
            // returns NULL; detect them by exact-PC match before the nmethod
            // dispatch below.
            // cont_returnBarrier: bottom thawed frame returns here when frozen
            //   frames remain in the StackChunk (blocking/remounted VT).
            // cont_entry_return_pc: bottom thawed frame returns here when the
            //   continuation is fully thawed (CPU-bound VT, never yielded).
            if (!CONT_UNWIND_DISABLED && VMStructs::isContReturnBarrier(pc)) {
                Counters::increment(WALKVM_CONT_BARRIER_HIT);
                if (walkThroughContinuation(false)) continue;
                break;
            }
            if (!CONT_UNWIND_DISABLED && VMStructs::isContEntryReturnPc(pc)) {
                Counters::increment(WALKVM_ENTER_SPECIAL_HIT);
                if (walkThroughContinuation(true)) continue;
                break;
            }
            VMNMethod* nm = CodeHeap::findNMethod(pc);
            if (nm == NULL) {
                // On JDK 21+ builds, the continuation entry PC may be absent
                // from vmStructs OR resolved but pointing to the wrong address
                // (some distributions expose the symbol at the wrong address, so
                // the exact-PC check above never fires).  Attempt a fully-thawed
                // continuation walk whenever we see an unknown nmethod after
                // collecting Java frames.  walkThroughContinuation validates the
                // fp chain and emits BCI_ERROR cleanly on mismatch, so false
                // positives are safe.
                if (!CONT_UNWIND_DISABLED
                        && features.carrier_frames
                        && VM::hotspot_version() >= 21
                        && depth > 0
                        && vm_thread != NULL && vm_thread->isCarryingVirtualThread()) {
                    Counters::increment(WALKVM_CONT_SPECULATIVE_HIT);
                    if (walkThroughContinuation(true)) continue;
                    break;
                }
                if (anchor == NULL) {
                    // Add an error frame only if we cannot recover
                    fillFrame(frames[depth++], BCI_ERROR, "unknown_nmethod");
                }
                break;
            }

            // Always prefer JavaFrameAnchor when it is available,
            // since it provides reliable SP and FP.
            // Do not treat the topmost stub as Java frame.
            // Exception: when VT carrier-frame unwinding is active, skip the anchor
            // redirect — it can bypass the continuation boundary by jumping directly
            // into carrier frames, causing walkThroughContinuation to never fire.
            // The continuation mechanism finds carrier frames on its own.
            bool anchor_eligible = anchor != NULL && (depth > 0 || !nm->isStub());
            bool cont_unwind_active = features.carrier_frames && !CONT_UNWIND_DISABLED
                && vm_thread != NULL && vm_thread->isCarryingVirtualThread();
            if (anchor_eligible && !cont_unwind_active) {
                Counters::increment(WALKVM_ANCHOR_CONSUMED);
                // Preserve anchor data before consumption — getFrame() is read-only
                // but we set anchor=NULL below, losing the pointer for later recovery.
                if (saved_anchor_sp == 0) {
                    saved_anchor_pc = anchor->lastJavaPC();
                    saved_anchor_sp = anchor->lastJavaSP();
                    saved_anchor_fp = anchor->lastJavaFP();
                }
                if (anchor->getFrame(pc, sp, fp) && !nm->contains(pc)) {
                    anchor = NULL;
                    continue;  // NMethod has changed as a result of correction
                }
                anchor = NULL;
            } else if (anchor_eligible && cont_unwind_active) {
                // Clear the anchor without redirecting so it doesn't corrupt fp
                // for the continuation boundary walk.
                anchor = NULL;
            }

            if (nm->isInterpreter()) {
                if (vm_thread != NULL && vm_thread->inDeopt()) {
                    fillFrame(frames[depth++], BCI_ERROR, "break_deopt");
                    break;
                }

                bool is_plausible_interpreter_frame = StackWalkValidation::isPlausibleInterpreterFrame(fp, sp, bcp_offset);
                if (is_plausible_interpreter_frame) {
                    VMMethod* method = ((VMMethod**)INJECT_FAULT_ADDRESS_UNLIKELY(fp))[InterpreterFrame::method_offset];
                    jmethodID method_id = getMethodId(method);
                    if (method_id != JMETHODID_NOT_WALKABLE) {
                        Counters::increment(WALKVM_JAVA_FRAME_OK);
                        const char* bytecode_start = method->bytecode();
                        const char* bcp = ((const char**)fp)[bcp_offset];
                        int bci = bytecode_start == NULL || bcp < bytecode_start ? 0 : bcp - bytecode_start;
                        HotspotSupport::fillJavaFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id, method);
                        sp = ((uintptr_t*)fp)[InterpreterFrame::sender_sp_offset];
                        pc = stripPointer(((void**)fp)[FRAME_PC_SLOT]);
                        fp = *(uintptr_t*)INJECT_FAULT_ADDRESS_UNLIKELY(fp);
                        continue;
                    }
                }

                if (depth == 0) {
                    VMMethod* method = (VMMethod*)frame.method();
                    jmethodID method_id = getMethodId(method);
                    if (method_id != JMETHODID_NOT_WALKABLE) {
                        Counters::increment(WALKVM_JAVA_FRAME_OK);
                        HotspotSupport::fillJavaFrame(frames[depth++], FRAME_INTERPRETED, 0, method_id, method);
                        if (is_plausible_interpreter_frame) {
                            uintptr_t* fp_addr = (uintptr_t*)INJECT_FAULT_ADDRESS_UNLIKELY(fp);
                            pc = stripPointer(((void**)fp_addr)[FRAME_PC_SLOT]);
                            sp = frame.senderSP();
                            fp = *fp_addr;
                        } else {
                            pc = stripPointer(SafeAccess::load((void**)sp));
                            sp = frame.senderSP();
                        }
                        continue;
                    }
                }

                Counters::increment(WALKVM_BREAK_INTERPRETED);
                fillFrame(frames[depth++], BCI_ERROR, "break_interpreted");
                break;
            } else if (nm->isNMethod()) {
                // enterSpecial is a generated native nmethod that acts as the
                // continuation entry stub on JDK 27+. It has no JavaCallWrapper, so
                // isEntryFrame() will not fire for it. Detect it by identity
                // and navigate to the carrier thread via ContinuationEntry.
                if (!CONT_UNWIND_DISABLED && nm == VMStructs::enterSpecialNMethod()) {
                    Counters::increment(WALKVM_ENTER_SPECIAL_HIT);
                    if (walkThroughContinuation(true)) continue;
                    break;
                }
                // Check if deoptimization is in progress before walking compiled frames
                if (vm_thread != NULL && vm_thread->inDeopt()) {
                    fillFrame(frames[depth++], BCI_ERROR, "break_deopt_compiled");
                    break;
                }

                Counters::increment(WALKVM_JAVA_FRAME_OK);
                int level = nm->level();
                FrameTypeId type = details && level >= 1 && level <= 3 ? FRAME_C1_COMPILED : FRAME_JIT_COMPILED;

                VMMethod* method = nm->method();
                jmethodID method_id = method->id();
                HotspotSupport::fillJavaFrame(frames[depth++], type, 0, method_id, method);

                if (nm->isFrameCompleteAt(pc)) {
                    if (depth == 1 && frame.unwindEpilogue(nm, (uintptr_t&)pc, sp, fp)) {
                        continue;
                    }

                    int scope_offset = nm->findScopeOffset(pc);
                    if (scope_offset > 0) {
                        depth--;
                        ScopeDesc scope(nm);
                        do {
                            scope_offset = scope.decode(scope_offset);
                            if (details) {
                                type = scope_offset > 0 ? FRAME_INLINED :
                                       level >= 1 && level <= 3 ? FRAME_C1_COMPILED : FRAME_JIT_COMPILED;
                            }
                            VMMethod* method = scope.method();
                            jmethodID method_id = method->id();
                            HotspotSupport::fillJavaFrame(frames[depth++], type, scope.bci(), method_id, method);
                        } while (scope_offset > 0 && depth < max_depth);
                    }

                    // Handle situations when sp is temporarily changed in the compiled code
                    frame.adjustSP(nm->entry(), pc, sp);

                    // Validate NMethod metadata before using frameSize()
                    int frame_size = nm->frameSize();
                    if (frame_size <= 0 || frame_size > MAX_FRAME_SIZE_WORDS) {
                        fillFrame(frames[depth++], BCI_ERROR, "break_invalid_framesize");
                        break;
                    }

                    sp += frame_size * sizeof(void*);

                    // Verify alignment before dereferencing sp as pointer (secondary defense)
                    if (!aligned(sp)) {
                        fillFrame(frames[depth++], BCI_ERROR, "break_misaligned_sp");
                        break;
                    }
                    sp = (uintptr_t)INJECT_FAULT_ADDRESS_UNLIKELY(sp);
                    fp = ((uintptr_t*)sp)[-FRAME_PC_SLOT - 1];
                    pc = ((const void**)sp)[-FRAME_PC_SLOT];
                    continue;
                } else if (frame.unwindPrologue(nm, (uintptr_t&)pc, sp, fp)) {
                    continue;
                }

                Counters::increment(WALKVM_BREAK_COMPILED);
                fillFrame(frames[depth++], BCI_ERROR, "break_compiled");
                break;
            } else if (nm->isEntryFrame(pc) && !features.mixed) {
                VMJavaFrameAnchor* next_anchor = VMJavaFrameAnchor::fromEntryFrame(fp);
                if (next_anchor == NULL) {
                    fillFrame(frames[depth++], BCI_ERROR, "break_entry_frame");
                    break;
                }
                uintptr_t prev_sp = sp;
                if (!next_anchor->getFrame(pc, sp, fp)) {
                    // End of Java stack
                    break;
                }
                if (sp < prev_sp || sp >= bottom || !aligned(sp)) {
                    fillFrame(frames[depth++], BCI_ERROR, "break_entry_frame");
                    break;
                }
                continue;
            } else {
                if (features.vtable_target && nm->isVTableStub() && depth == 0) {
                    uintptr_t receiver = frame.jarg0();
                    if (receiver != 0) {
                        VMKlass* klass = VMKlass::fromOop(receiver);
                        VMSymbol* symbol = klass != nullptr ? klass->name() : nullptr;
                        // Store the raw VMSymbol* in the frame's method_id
                        // slot. BCI_VTABLE_RECEIVER (vmEntry.h) repurposes
                        // method_id for this pointer — same precedent as
                        // BCI_NATIVE_FRAME storing const char* and
                        // BCI_NATIVE_FRAME_REMOTE storing a packed blob.
                        // Resolution happens at dump time via SafeAccess so
                        // a concurrent class-unload + Symbol free cannot
                        // crash the dump thread (see Lookup::resolveVTableReceiver).
                        if (symbol != nullptr) {
                            fillFrame(frames[depth++], BCI_VTABLE_RECEIVER, (void*)symbol);
                        }
                    }
                }

                CodeBlob* stub = JitCodeCache::findRuntimeStub(pc);
                const void* start = stub != NULL ? stub->_start : nm->code();
                const char* name = stub != NULL ? stub->_name : nm->name();

                if (details) {
                    fillFrame(frames[depth++], BCI_NATIVE_FRAME, name);
                }

                if (frame.unwindStub((instruction_t*)start, name, (uintptr_t&)pc, sp, fp)) {
                    continue;
                }

                if (depth > 0 && nm->frameSize() > 0) {
                    Counters::increment(WALKVM_STUB_FRAMESIZE_FALLBACK);
                    // Validate NMethod metadata before using frameSize()
                    int frame_size = nm->frameSize();
                    if (frame_size <= 0 || frame_size > MAX_FRAME_SIZE_WORDS) {
                        fillFrame(frames[depth++], BCI_ERROR, "break_invalid_framesize");
                        break;
                    }

                    sp += frame_size * sizeof(void*);

                    // Verify alignment before dereferencing sp as pointer (secondary defense)
                    if (!aligned(sp)) {
                        fillFrame(frames[depth++], BCI_ERROR, "break_misaligned_sp");
                        break;
                    }

                    fp = ((uintptr_t*)sp)[-FRAME_PC_SLOT - 1];
                    pc = ((const void**)sp)[-FRAME_PC_SLOT];
                    continue;
                }

#ifdef DEBUG
                if (unwindFailures) {
                    unwindFailures->record(UNWIND_FAILURE_STUB, name);
                }
#endif // DEBUG
                // Unconditional (not DEBUG-only): previously this path fell through with
                // pc/sp/depth all unchanged, re-entering the enclosing
                // `while (depth < actual_max_depth)` in the same state -- an infinite loop
                // whenever a runtime-stub frame can't be unwound and the frameSize()
                // fallback above isn't available. Terminate the walk explicitly instead.
                fillFrame(frames[depth++], BCI_ERROR, "break_unwind_stub_failed");
                break;
            }
        } else {
            // Resolve native frame (may use remote symbolication if enabled)
            Profiler::NativeFrameResolution resolution = profiler->resolveNativeFrameForWalkVM((uintptr_t)pc, lock_index);
            if (resolution.is_marked()) {
                if (resolution.mark == MARK_JAVA_PROFILER &&
                    isHookPrefixedSample(event_type)) {
                    // Discard frames captured above the malloc/socket hook boundary,
                    // excluding the hook's own frame, and resume from the real
                    // caller above it — mirrors the FP/DWARF skip-prefix logic in
                    // Profiler::convertNativeTrace.
                    hook_boundary_found = true;
                    depth = 0;
                } else if (resolution.mark == MARK_COMPILER_ENTRY && features.comp_task && vm_thread != NULL) {
                    // Insert current compile task as a pseudo Java frame
                    VMMethod* method = vm_thread->compiledMethod();
                    if (method != nullptr) {
                        jmethodID method_id = method->id();
                        if (method_id != JMETHODID_NOT_WALKABLE) {
                            HotspotSupport::fillJavaFrame(frames[depth++], FRAME_JIT_COMPILED, 0, method_id, method);
                        }
                    }
                } else if (resolution.mark == MARK_THREAD_ENTRY) {
                    // Thread entry point detected via pre-computed mark - this is the root frame
                    Counters::increment(THREAD_ENTRY_MARK_DETECTIONS);
                    break;
                } else {
                    // Other marks (VM runtime / interpreter) terminate the scan.
                    break;
                }
                goto dwarf_unwind;
            }
            const char* method_name = resolution.method_name;
            int frame_bci = resolution.bci;
            if (method_name == NULL && details && !anchor_recovery_used
                       && profiler->findLibraryByAddress(pc) == NULL) {
                // Try anchor recovery — prefer live anchor, fall back to saved data
                anchor_recovery_used = true;
                const void* recovery_pc = NULL;
                uintptr_t recovery_sp = 0;
                uintptr_t recovery_fp = 0;
                bool have_anchor_data = false;

                if (anchor) {
                    Counters::increment(WALKVM_ANCHOR_USED_INLINE);
                    recovery_fp = anchor->lastJavaFP();
                    recovery_sp = anchor->lastJavaSP();
                    recovery_pc = anchor->lastJavaPC();
                    have_anchor_data = true;
                } else if (saved_anchor_sp != 0) {
                    Counters::increment(WALKVM_SAVED_ANCHOR_USED);
                    recovery_fp = saved_anchor_fp;
                    recovery_sp = saved_anchor_sp;
                    recovery_pc = saved_anchor_pc;
                    have_anchor_data = true;
                    // Clear saved data after use — one-shot recovery
                    saved_anchor_sp = 0;
                } else {
                    Counters::increment(WALKVM_ANCHOR_INLINE_NO_ANCHOR);
                }

                if (have_anchor_data) {
                    // Try to read the Java method directly from the anchor's FP,
                    // treating it as an interpreter frame.
                    // In HotSpot, lastJavaFP is non-zero only for interpreter frames;
                    // compiled frames record FP=0 in the anchor.
                    if (StackWalkValidation::isPlausibleInterpreterFrame(recovery_fp, recovery_sp, bcp_offset)) {
                        VMMethod* method = ((VMMethod**)INJECT_FAULT_ADDRESS_UNLIKELY(recovery_fp))[InterpreterFrame::method_offset];
                        jmethodID method_id = getMethodId(method);
                        if (method_id != JMETHODID_NOT_WALKABLE) {
                            anchor = NULL;
                            prev_native_pc = NULL;
                            if (depth > 0 && depth + 1 < actual_max_depth) {
                                fillFrame(frames[depth++], BCI_ERROR, "[skipped frames]");
                            }
                            Counters::increment(WALKVM_JAVA_FRAME_OK);
                            const char* bytecode_start = method->bytecode();
                            const char* bcp = ((const char**)recovery_fp)[bcp_offset];
                            int bci = bytecode_start == NULL || bcp < bytecode_start ? 0 : bcp - bytecode_start;
                            HotspotSupport::fillJavaFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id, method);
                            sp = ((uintptr_t*)recovery_fp)[InterpreterFrame::sender_sp_offset];
                            pc = stripPointer(((void**)recovery_fp)[FRAME_PC_SLOT]);
                            fp = *(uintptr_t*)recovery_fp;
                            continue;
                        }
                    }

                    // Fallback: redirect via recovery SP/FP/PC
                    sp = recovery_sp;
                    fp = recovery_fp;
                    pc = recovery_pc;
                    if (pc != NULL && !CodeHeap::contains(pc) && sp != 0 && aligned(sp) && sp < bottom) {
                        pc = ((const void**)sp)[-1];
                    }
                    if (sp != 0 && pc != NULL) {
                        anchor = NULL;
                        if (sp >= bottom || !aligned(sp)) {
                            Counters::increment(WALKVM_ANCHOR_INLINE_BAD_SP);
                            fillFrame(frames[depth++], BCI_ERROR, "break_no_anchor");
                            break;
                        }
                        prev_native_pc = NULL;
                        if (depth > 0) {
                            fillFrame(frames[depth++], BCI_ERROR, "[skipped frames]");
                        }
                        continue;
                    }
                    Counters::increment(WALKVM_ANCHOR_INLINE_NO_SP);
                }
                // Check previous frame for thread entry points (Rust, libc/pthread)
                // Only check marks for traditionally-resolved frames; packed remote
                // frames store an integer in the method_name union, not a valid pointer.
                if (prev_native_pc != NULL) {
                    Profiler::NativeFrameResolution prev_resolution = profiler->resolveNativeFrameForWalkVM((uintptr_t)prev_native_pc, lock_index);
                    if (prev_resolution.bci != BCI_NATIVE_FRAME_REMOTE) {
                        const char* prev_method_name = prev_resolution.method_name;
                        if (prev_method_name != NULL) {
                            char prev_mark = NativeFunc::read_mark(prev_method_name);
                            if (prev_mark == MARK_THREAD_ENTRY) {
                                Counters::increment(THREAD_ENTRY_MARK_DETECTIONS);
                                break;
                            }
                        }
                    }
                }
                // Fall through to DWARF section — when findLibraryByAddress(pc)
                // returns NULL, default_frame uses FP-chain walking (DW_REG_FP)
                // which can bridge symbol-less gaps in libjvm.so.
                Counters::increment(WALKVM_FP_CHAIN_ATTEMPT);
                fp_chain_fallback = true;
                if (++fp_chain_depth > actual_max_depth) {
                    break;
                }
                goto dwarf_unwind;
            }
            fillFrame(frames[depth++], frame_bci, (void*)method_name);
        }

        dwarf_unwind:
        uintptr_t prev_sp = sp;
        CodeCache* cc = profiler->findLibraryByAddress(pc);
        FrameDesc f = cc != NULL ? cc->findFrameDesc(pc) : FrameDesc::fallback_default_frame();

        u8 cfa_reg = (u8)f.cfa;
        int cfa_off = f.cfa >> 8;

        // If DWARF is invalid, we cannot continue unwinding reliably
        // Thread entry points are detected earlier via MARK_THREAD_ENTRY
        if (cfa_reg == DW_REG_INVALID || cfa_reg > DW_REG_PLT) {
            break;
        }

        if (cfa_reg == DW_REG_SP) {
            sp = sp + cfa_off;
        } else if (cfa_reg == DW_REG_FP) {
            // Sanity-check FP before deriving CFA from it. A corrupted FP can produce a
            // phantom CFA and cause the walk to record spurious frames before breaking.
            // We cannot check fp < sp here because on aarch64 the frame pointer is set
            // to SP at function entry, which is typically less than the previous CFA.
            if (fp >= bottom || !aligned(fp)) {
                break;
            }
            sp = fp + cfa_off;
        } else if (cfa_reg == DW_REG_PLT) {
            sp += ((uintptr_t)pc & 15) >= 11 ? cfa_off * 2 : cfa_off;
        }

        // Check if the next frame is below on the current stack
        if (sp < prev_sp || sp >= prev_sp + MAX_FRAME_SIZE || sp >= bottom) {
            break;
        }

        // Stack pointer must be word aligned
        if (!aligned(sp)) {
            break;
        }

        // store the previous pc before unwinding
        prev_native_pc = pc;
        if (f.fp_off & DW_PC_OFFSET) {
            pc = (const char*)pc + (f.fp_off >> 1);
        } else {
            if (f.fp_off != DW_SAME_FP && f.fp_off < MAX_FRAME_SIZE && f.fp_off > -MAX_FRAME_SIZE) {
                fp = (uintptr_t)SafeAccess::load((void**)(sp + f.fp_off));
            }

            if (EMPTY_FRAME_SIZE > 0 || f.pc_off != DW_LINK_REGISTER) {
                // Verify alignment before dereferencing sp + offset
                uintptr_t pc_addr = sp + f.pc_off;
                if (!aligned(pc_addr)) {
                    break;
                }
                pc = stripPointer(SafeAccess::load((void**)pc_addr));
            } else if (depth == 1) {
                pc = (const void*)frame.link();
            } else {
                break;
            }

            if (EMPTY_FRAME_SIZE == 0 && cfa_off == 0 && f.fp_off != DW_SAME_FP) {
                // AArch64 default_frame
                sp = defaultSenderSP(sp, fp);
                if (sp < prev_sp || sp >= bottom || !aligned(sp)) {
                    break;
                }
            }
        }

        if (inDeadZone(pc) || (pc == prev_native_pc && sp == prev_sp)) {
            break;
        }
    }

    // If we did not meet Java frame but current thread has JavaFrameAnchor set,
    // try to read the interpreter frame directly from the anchor's FP.
    // In HotSpot, lastJavaFP != 0 reliably indicates an interpreter frame.
    if (anchor != NULL) {
        uintptr_t anchor_fp = anchor->lastJavaFP();
        uintptr_t anchor_sp = anchor->lastJavaSP();
        if (anchor_sp == 0) {
            Counters::increment(WALKVM_ANCHOR_NOT_IN_JAVA);
            goto done;
        }
        if (StackWalkValidation::isPlausibleInterpreterFrame(anchor_fp, anchor_sp, bcp_offset)) {
            VMMethod* method = ((VMMethod**)anchor_fp)[InterpreterFrame::method_offset];
            jmethodID method_id = getMethodId(method);
            if (method_id != JMETHODID_NOT_WALKABLE) {
                Counters::increment(WALKVM_ANCHOR_FALLBACK);
                Counters::increment(WALKVM_JAVA_FRAME_OK);
                anchor = NULL;
                while (depth > 0 && frames[depth - 1].method_id == NULL) depth--;
                if (depth < actual_max_depth) {
                    const char* bytecode_start = method->bytecode();
                    const char* bcp = ((const char**)anchor_fp)[bcp_offset];
                    int bci = bytecode_start == NULL || bcp < bytecode_start ? 0 : bcp - bytecode_start;
                    HotspotSupport::fillJavaFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id, method);
                    sp = ((uintptr_t*)anchor_fp)[InterpreterFrame::sender_sp_offset];
                    pc = stripPointer(((void**)anchor_fp)[FRAME_PC_SLOT]);
                    fp = *(uintptr_t*)anchor_fp;
                    if (sp != 0 && sp < bottom && aligned(sp)) {
                        goto unwind_loop;
                    }
                }
            }
        }
        // Fallback: redirect via anchor frame and sp[-1]
        if (anchor != NULL && anchor->getFrame(pc, sp, fp)) {
            if (!CodeHeap::contains(pc) && sp != 0 && aligned(sp) && sp < bottom) {
                pc = ((const void**)sp)[-1];
            }
            Counters::increment(WALKVM_ANCHOR_FALLBACK);
            anchor = NULL;
            while (depth > 0 && frames[depth - 1].method_id == NULL) depth--;
            if (sp != 0 && sp < bottom && aligned(sp)) {
                goto unwind_loop;
            }
        } else if (anchor != NULL) {
            Counters::increment(WALKVM_ANCHOR_FALLBACK_FAIL);
        }
    }

    done:
    jmp_scope.restore();

    // Drop unknown leaf frame - it provides no useful information and breaks
    // aggregation by lumping unrelated samples under a single "unknown" entry
    depth = StackWalkValidation::dropUnknownLeaf(frames, depth);

    if (depth == 0) {
        Counters::increment(WALKVM_DEPTH_ZERO);
    }

    if (isHookPrefixedSample(event_type) && !hook_boundary_found) {
        // The malloc/socket hook boundary was never found in this walk;
        // mirrors Profiler::convertNativeTrace's NATIVE_TRACE_HOOK_PREFIX_NOT_FOUND.
        Counters::increment(NATIVE_TRACE_HOOK_PREFIX_NOT_FOUND);
    }

    if (truncated) {
        if (depth > max_depth) {
            *truncated = true;
            depth = max_depth;
        } else if (depth > 0) {
            if (frames[depth - 1].bci == BCI_ERROR) {
                // root frame is error; best guess is that the trace is truncated
                *truncated = true;
            }
        }
    }

#ifdef DEBUG
    if (unwindFailures && !unwindFailures->empty()) {
        UnwindStats::recordFailures(unwindFailures);
        unwindFailures->clear();
    }
#endif // DEBUG

    return depth;
}

int HotspotSupport::getJavaTraceAsync(void *ucontext, ASGCT_CallFrame *frames,
                                int max_depth, StackContext *java_ctx,
                                bool *truncated) {
  // Workaround for JDK-8132510: it's not safe to call GetEnv() inside a signal
  // handler since JDK 9, so we do it only for threads already registered in
  // ThreadLocalStorage
  VMThread *vm_thread = VMThread::current();
  if (vm_thread == NULL || !vm_thread->isThreadAccessible()) {
    Counters::increment(AGCT_NOT_REGISTERED_IN_TLS);
    return 0;
  }

  JNIEnv *jni = VM::jni();
  if (jni == NULL) {
    // Not a Java thread
    Counters::increment(AGCT_NOT_JAVA);
    return 0;
  }

  HotspotStackFrame frame(ucontext);
  uintptr_t saved_pc = 0, saved_sp = 0, saved_fp = 0;
  if (ucontext != NULL) {
    saved_pc = frame.pc();
    saved_sp = frame.sp();
    saved_fp = frame.fp();

    if (JitCodeCache::isCallStub((const void *)saved_pc)) {
       // call_stub is unsafe to walk
      frames->bci = BCI_ERROR;
      frames->method_id = (jmethodID) "call_stub";
      return 1;
    }

    if (!VMStructs::isSafeToWalk(saved_pc)) {
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
  }
  // Ported from upstream async-profiler (Profiler::getJavaTraceAsync in
  // src/profiler.cpp): when ucontext is NULL — as it is for malloc hooks,
  // which run outside any signal context — skip the PC-dependent pre-checks
  // and fall through to ASGCT. ASGCT then resolves the top Java frame from
  // JavaThread::last_Java_sp / last_Java_pc, which the JVM populates on every
  // Java → native transition.

  JVMJavaThreadState state = vm_thread->state();
  bool in_java = (state == _thread_in_Java || state == _thread_in_Java_trans);
  if (in_java && java_ctx->sp != 0) {
    // skip ahead to the Java frames before calling AGCT
    frame.restore((uintptr_t)java_ctx->pc, java_ctx->sp, java_ctx->fp);
  } else if (state != _thread_uninitialized) {
    VMJavaFrameAnchor* a = vm_thread->anchor();
    if (a == nullptr || a->lastJavaSP() == 0) {
      // we haven't found the top Java frame ourselves, and the lastJavaSP wasn't
      // recorded either when not in the Java state, lastJava ucontext will be
      // used by AGCT
      Counters::increment(AGCT_NATIVE_NO_JAVA_CONTEXT);
      return 0;
    }
  }
  bool blocked_in_vm = (state == _thread_blocked || state == _thread_blocked_trans);
  // avoid unwinding during deoptimization
  if (blocked_in_vm && vm_thread->osThreadState() == OSThreadState::RUNNABLE) {
    Counters::increment(AGCT_BLOCKED_IN_VM);
    return 0;
  }

  JitWriteProtection jit(false);
  // AsyncGetCallTrace writes to ASGCT_CallFrame array
  ASGCT_CallTrace trace = {jni, 0, frames};
  JVMSupport::jvmAsyncGetCallTrace(&trace, max_depth, ucontext);

  if (trace.num_frames > 0) {
    frame.restore(saved_pc, saved_sp, saved_fp);
    return trace.num_frames;
  }

  int safe_mode = Profiler::instance()->safe_mode();
  CStack cstack = Profiler::instance()->cstackMode();
  
  if ((trace.num_frames == ticks_unknown_Java ||
       trace.num_frames == ticks_not_walkable_Java) &&
      !(safe_mode & UNKNOWN_JAVA) && ucontext != NULL) {
    CodeBlob *stub = JitCodeCache::findRuntimeStub((const void *)frame.pc());
    if (stub != NULL) {
      if (cstack != CSTACK_NO) {
        max_depth -= makeFrame(trace.frames++, BCI_NATIVE_FRAME, stub->_name);
      }
      if (!(safe_mode & POP_STUB) &&
          frame.unwindStub((instruction_t *)stub->_start, stub->_name) &&
          isAddressInCode((const void *)frame.pc())) {
        JVMSupport::jvmAsyncGetCallTrace(&trace, max_depth, ucontext);
      }
    } else if (VMStructs::hasMethodStructs()) {
      VMNMethod *nmethod = CodeHeap::findNMethod((const void *)frame.pc());
      if (nmethod != NULL && nmethod->isNMethod() && nmethod->isAlive()) {
        VMMethod *method = nmethod->method();
        if (method != NULL) {
          jmethodID method_id = method->id();
          if (isValidJMethodID(method_id)) {
            max_depth -= makeFrame(trace.frames++, 0, method_id);
          }
          if (!(safe_mode & POP_METHOD) && frame.unwindCompiled(nmethod) &&
              isAddressInCode((const void *)frame.pc())) {
            JVMSupport::jvmAsyncGetCallTrace(&trace, max_depth, ucontext);
          }
          if ((safe_mode & PROBE_SP) && trace.num_frames < 0) {
            if (isValidJMethodID(method_id)) {
              trace.frames--;
            }
            for (int i = 0; trace.num_frames < 0 && i < PROBE_SP_LIMIT; i++) {
              frame.sp() += sizeof(void*);
              JVMSupport::jvmAsyncGetCallTrace(&trace, max_depth, ucontext);
            }
          }
        }
      } else if (nmethod != NULL) {
        if (cstack != CSTACK_NO) {
          max_depth -=
              makeFrame(trace.frames++, BCI_NATIVE_FRAME, nmethod->name());
        }
        if (!(safe_mode & POP_STUB) &&
            frame.unwindStub(NULL, nmethod->name()) &&
            isAddressInCode((const void *)frame.pc())) {
          JVMSupport::jvmAsyncGetCallTrace(&trace, max_depth, ucontext);
        }
      }
    }
  } else if (trace.num_frames == ticks_unknown_not_Java &&
             !(safe_mode & LAST_JAVA_PC)) {
    VMJavaFrameAnchor* anchor = vm_thread->anchor();
    if (anchor == NULL) return 0;
    uintptr_t sp = anchor->lastJavaSP();
    const void* pc = anchor->lastJavaPC();
    if (sp != 0 && pc == NULL) {
      // We have the last Java frame anchor, but it is not marked as walkable.
      // Make it walkable here
      pc = ((const void**)sp)[-1];
      anchor->setLastJavaPC(pc);

      VMNMethod *m = CodeHeap::findNMethod(pc);
      const Libraries* libs = Profiler::instance()->libraries();

      if (m != NULL) {
        // AGCT fails if the last Java frame is a Runtime Stub with an invalid
        // _frame_complete_offset. In this case we patch _frame_complete_offset
        // manually
        if (!m->isNMethod() && m->frameSize() > 0 &&
            m->frameCompleteOffset() == -1) {
          m->setFrameCompleteOffset(0);
        }
        JVMSupport::jvmAsyncGetCallTrace(&trace, max_depth, ucontext);
      } else if (libs->findLibraryByAddress(pc) != NULL) {
        JVMSupport::jvmAsyncGetCallTrace(&trace, max_depth, ucontext);
      }

      anchor->setLastJavaPC(nullptr);
    }
  } else if (trace.num_frames == ticks_not_walkable_not_Java &&
             !(safe_mode & LAST_JAVA_PC)) {
    VMJavaFrameAnchor* anchor = vm_thread->anchor();
    if (anchor == NULL) return 0;
    uintptr_t sp = anchor->lastJavaSP();
    const void* pc = anchor->lastJavaPC();
    if (sp != 0 && pc != NULL) {
      // Similar to the above: last Java frame is set,
      // but points to a Runtime Stub with an invalid _frame_complete_offset
      VMNMethod *m = CodeHeap::findNMethod(pc);
      if (m != NULL && !m->isNMethod() && m->frameSize() > 0 &&
          m->frameCompleteOffset() == -1) {
        m->setFrameCompleteOffset(0);
        JVMSupport::jvmAsyncGetCallTrace(&trace, max_depth, ucontext);
      }
    }
  } else if (trace.num_frames == ticks_GC_active && !(safe_mode & GC_TRACES)) {
    VMJavaFrameAnchor* anchor = vm_thread->anchor();
    if (anchor == NULL || anchor->lastJavaSP() == 0) {
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

  const char *err_string = Profiler::asgctError(trace.num_frames);
  if (err_string == NULL) {
    // No Java stack, because thread is not in Java context
    return 0;
  }

  Profiler::instance()->incFailure(-trace.num_frames);
  trace.frames->bci = BCI_ERROR;
  trace.frames->method_id = (jmethodID)err_string;
  return trace.frames - frames + 1;
}

int HotspotSupport::walkJavaStack(StackWalkRequest& request) {
  CStack cstack = Profiler::instance()->cstackMode();
  StackWalkFeatures features = Profiler::instance()->stackWalkFeatures();
  void* ucontext = request.ucontext;
  ASGCT_CallFrame* frames = request.frames;
  int max_depth = request.max_depth;
  StackContext* java_ctx = request.java_ctx;
  bool* truncated = request.truncated;
  u32 lock_index = request.lock_index;

  volatile int java_frames = 0;
  // walkVM() installs its own sigsetjmp/siglongjmp crash protection (chained
  // with any pre-existing jmp ctx, see the comment in walkVM), but the
  // getJavaTraceAsync() path below runs without one: it dereferences
  // VMThread/anchor state directly and calls into HotSpot's own
  // AsyncGetCallTrace. Install a jmp ctx here too, so a SIGSEGV anywhere in
  // walkJavaStack, except HotSpot's AsyncGetCallTrace call, is caught by
  // Profiler::checkFault() and siglongjmp'd back here instead of crashing the process.
  ProfiledThread* prof_thread = ProfiledThread::acquireCurrent();
  if (prof_thread == nullptr) {
    Counters::increment(SAMPLES_DROPPED_THREAD_LOCAL);
    return 0;
  }
  const bool prev_unwinding_java = prof_thread->is_unwinding_Java();
  sigjmp_buf crash_protection_ctx;
  JmpCtxScope jmp_scope(prof_thread);

  if (sigsetjmp(crash_protection_ctx, 1) != 0) {
    // checkFault() does a siglongjmp from inside segvHandler, bypassing
    // segvHandler's SignalHandlerScope destructor. Compensate.
    SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
    jmp_scope.restore();
    // A recovered siglongjmp bypasses AsyncSampleMutex destructors, so restore
    // the per-thread guard to its pre-walk value.
    prof_thread->set_unwinding_Java(prev_unwinding_java);
    if (truncated) {
      *truncated = true;
    }
    return java_frames;
  }
  jmp_scope.install(&crash_protection_ctx);

  if (features.mixed) {
    java_frames = walkVM(ucontext, frames, max_depth, features, eventTypeFromBCI(request.event_type), lock_index, truncated);
  } else if (isHookPrefixedSample(request.event_type)) {
    if (cstack >= CSTACK_VM) {
      java_frames = walkVM(ucontext, frames, max_depth, features, eventTypeFromBCI(request.event_type), lock_index, truncated);
    } else {
        AsyncSampleMutex mutex(ProfiledThread::current());
        if (mutex.acquired()) {
            java_frames = getJavaTraceAsync(ucontext, frames, max_depth, java_ctx, truncated);
            if (java_frames > 0 && java_ctx->pc != NULL && VMStructs::hasMethodStructs()) {
                VMNMethod* nmethod = CodeHeap::findNMethod(java_ctx->pc);
                if (nmethod != NULL) {
                    fillFrameTypes(frames, java_frames, nmethod);
                }
            }
        }
        if (java_frames > 0 && VM::hotspot_version() >= 21 && java_frames < max_depth) {
            VMThread* carrier = VMThread::current();
            if (carrier != nullptr && carrier->isCarryingVirtualThread()) {
                frames[java_frames].bci = BCI_NATIVE_FRAME;
                frames[java_frames].method_id = (jmethodID) "JVM Continuation";
                LP64_ONLY(frames[java_frames].padding = 0;)
                java_frames++;
            }
        }
    }
  } else if (request.event_type == BCI_CPU || request.event_type == BCI_WALL) {
    if (cstack >= CSTACK_VM) {
        java_frames = walkVM(ucontext, frames, max_depth, features, eventTypeFromBCI(request.event_type), lock_index, truncated);
    } else {
        AsyncSampleMutex mutex(ProfiledThread::current());
        if (mutex.acquired()) {
            java_frames = getJavaTraceAsync(ucontext, frames, max_depth, java_ctx, truncated);
            if (java_frames > 0 && java_ctx->pc != NULL && VMStructs::hasMethodStructs()) {
                VMNMethod* nmethod = CodeHeap::findNMethod(java_ctx->pc);
                if (nmethod != NULL) {
                    fillFrameTypes(frames, java_frames, nmethod);
                }
            }
        }
        if (java_frames > 0 && VM::hotspot_version() >= 21 && java_frames < max_depth) {
            VMThread* carrier = VMThread::current();
            if (carrier != nullptr && carrier->isCarryingVirtualThread()) {
                frames[java_frames].bci = BCI_NATIVE_FRAME;
                frames[java_frames].method_id = (jmethodID) "JVM Continuation";
                LP64_ONLY(frames[java_frames].padding = 0;)
                java_frames++;
            }
        }
    }
  }

  return java_frames;
}

static void patchClassLoaderData(JNIEnv* jni, jclass klass) {
  bool needs_patch = VM::hotspot_version() == 8;
  if (needs_patch) {
    // Workaround for JVM bug https://bugs.openjdk.org/browse/JDK-8062116
    // Preallocate space for jmethodIDs at the beginning of the list (rather than at the end)
    // This is relevant only for JDK 8 - later versions do not have this bug
    if (VMStructs::hasClassLoaderData()) {
      VMKlass *vmklass = VMKlass::fromJavaClass(jni, klass);
      int method_count = vmklass->methodCount();
      if (method_count > 0) {
        VMClassLoaderData *cld = vmklass->classLoaderData();
        cld->lock();
        for (int i = 0; i < method_count; i += MethodList::SIZE) {
          *cld->methodList() = new MethodList(*cld->methodList());
        }
        cld->unlock();
      }
    }
  }
}

constexpr const char LAMBDA_PREFIX[] = "Ljava/lang/invoke/LambdaForm$";
constexpr const size_t LAMBDA_PREFIX_LEN = sizeof(LAMBDA_PREFIX) - 1;

constexpr const char FFM_PREFIX[] = "Ljdk/internal/foreign/abi/";
constexpr const size_t FFM_PREFIX_LEN = sizeof(FFM_PREFIX) - 1;

constexpr const char* LAMBDA_FORMS[] = {"$$Lambda.", "$$Lambda$", ".lambda$"};

static bool isLambdaClass(const char* signature) {
    if (strncmp(signature, LAMBDA_PREFIX, LAMBDA_PREFIX_LEN) == 0 ||
        strncmp(signature, FFM_PREFIX, FFM_PREFIX_LEN) == 0) {
        return true;
    }

    size_t count = sizeof(LAMBDA_FORMS) / sizeof(LAMBDA_FORMS[0]);
    for (size_t index = 0; index < count; index++) {
        if (strstr(signature, LAMBDA_FORMS[index]) != nullptr) {
            return true;
        }
    }
    return false;
}

static bool isSystemClassLoader(JNIEnv* jni, jobject cl) {
    return cl == nullptr ||                         // bootstrap class loader
           jni->IsSameObject(cl, JAVA_PLATFORM_CLASSLOADER) ||       // platform class loader
           jni->IsSameObject(cl, JAVA_APPLICATION_CLASSLOADER);      // application class loader (system class loader)
}

static bool isHiddenClass(jvmtiEnv *jvmti, jclass clazz) {
    jint modifiers = 0;
    if (jvmti->GetClassModifiers(clazz, &modifiers) == JVMTI_ERROR_NONE &&
        JVMSupport::isHidden(modifiers)) {
        return true;
    }
    return false;
}

// Access flags do not reliably mark HotSpot hidden classes: there is no
// class-level hidden bit and a Lookup.defineHiddenClass class need not be
// synthetic. Hidden/anonymous classes carry a VM-injected "/0x..." name
// suffix (see Lookup::getPackage); '/' is illegal in a normal binary class
// name, so this reliably identifies the unloadable classes we must keep on
// the jmethodID path.
static bool isHiddenClassBySignature(const char* signature) {
    const char* slash = strrchr(signature, '/');
    return slash != nullptr && slash[1] >= '0' && slash[1] <= '9';
}

bool HotspotSupport::loadMethodIDsIfNeededImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass, bool load_all) {
    if (!load_all) {
        jobject cl = nullptr;
        // Hidden/lambda classes can be unloaded, fallback to use jmethodIDs, so preload them.
        if (!isHiddenClass(jvmti, klass) &&
            jvmti->GetClassLoader(klass, &cl) == JVMTI_ERROR_NONE &&
            isSystemClassLoader(jni, cl)) {
            char* signature_ptr = nullptr;
            if (jvmti->GetClassSignature(klass, &signature_ptr, nullptr) == JVMTI_ERROR_NONE) {
                // Lambda classes, even loaded by bootstrap class loader, can be unloaded,
                // fallback to jmethodID
                if (!isLambdaClass(signature_ptr) && !isHiddenClassBySignature(signature_ptr)) {
                    if (cl != nullptr) {
                        jni->DeleteLocalRef(cl);
                    }
                    jvmti->Deallocate((unsigned char*)signature_ptr);
                    return false;
                }
            }
            if (signature_ptr != nullptr) {
                jvmti->Deallocate((unsigned char*)signature_ptr);
            }
        }
        if (cl != nullptr) {
            jni->DeleteLocalRef(cl);
        }
    }
    patchClassLoaderData(jni, klass);
    return JVMSupport::loadMethodIDsImpl(jvmti, jni, klass);
}

// The three names resolve() needs, owned by resolve()'s frame. Each name has
// a fixed-size inline buffer for the common case, with a malloc'd fallback
// (up to MAX_SYMBOL_LEN) for names that don't fit -- see release() for why
// that fallback needs explicit cleanup on the crash-recovery path.
class ResolvedNames {
  // Hard ceiling for the malloc fallback in setImpl(), independent of which
  // field is being resolved. Not a JVM/class-file limit (Symbol::length() is
  // a u2, so up to 65535 is legal) -- a name that would already have been rejected
  // as too long for those fields' fixed buffers doesn't get an unbounded
  // allocation just because it went through the malloc path instead.
  static constexpr size_t MAX_SYMBOL_LEN = 64 * 1024;

  // Fixed-size fast-path buffers for the common case, sized generously above
  // the realistic common-case length for each field (see the per-field
  // comments below) but deliberately not so generous that the malloc
  // fallback in setImpl() never engages -- these caps are meant to be hit
  // occasionally so that path stays exercised.
  // HotSpot's Symbol length field is a u2, so the VM permits up to 65535 bytes.
  // A name/descriptor that overflows its fixed buffer falls back to malloc
  // (see ResolvedNames::setImpl), up to MAX_SYMBOL_LEN below; beyond that it is
  // rejected and the frame serializes as "unknown" -- METHOD_RESOLVE_SYMBOL_UNREADABLE
  // makes that visible if it bites. Unlike the old stack-only design, the malloc
  // fallback means this is no longer a leak-proof region: siglongjmp out of
  // resolve() bypasses ~ResolvedNames(), so the fault-recovery path must call
  // ResolvedNames::release() explicitly (see resolve()) to free any buffer
  // allocated before the fault.
  static constexpr size_t MAX_KLASS_NAME_LEN  = 1024;  // internal names; realistically < 256
  static constexpr size_t MAX_METHOD_NAME_LEN =  512;  // realistically < 64
  // A descriptor can in principle exceed this (255 argument *slots*, each able to
  // carry an arbitrarily long L...; type name), so this cap is a fidelity choice,
  // not a proof: over-cap descriptors serialize as "unknown" rather than being
  // truncated. METHOD_RESOLVE_SYMBOL_UNREADABLE makes it visible if that bites.
  static constexpr size_t MAX_SIGNATURE_LEN   = 1024;

  private:
  // volatile: resolve() mutates these (via setMethodName/setMethodSignature/
  // setKlassName, called through readMethodNames()) between sigsetjmp() and a
  // possible siglongjmp() out of a fault, then release() reads them back at
  // the landing pad to decide what to free. Per the setjmp/longjmp rules
  // (C11 7.13.2.1p3, inherited by C++), a non-volatile automatic local
  // modified in that window has an indeterminate value after longjmp;
  // volatile is what makes release()'s reads on the recovery path defined.
  char* volatile _long_method_name;
  char* volatile _long_method_signature;
  char* volatile _long_klass_name;

  char _method_name[MAX_METHOD_NAME_LEN];
  char _method_signature[MAX_SIGNATURE_LEN];
  char _klass_name[MAX_KLASS_NAME_LEN];

  bool setImpl(char* short_name, char* volatile& long_name, size_t short_limit, VMSymbol* sym);
public:
  // Non-copyable
  ResolvedNames(const ResolvedNames&) = delete;
  ResolvedNames& operator=(const ResolvedNames&) = delete;
 
  ResolvedNames();
  ~ResolvedNames();
  void release();

  bool setMethodName(VMSymbol* sym);
  bool setMethodSignature(VMSymbol* sym);
  bool setKlassName(VMSymbol* sym);

  const char* methodName() const {
    return _long_method_name != nullptr ? _long_method_name : _method_name;
  }

  const char* methodSignature() const {
    return _long_method_signature != nullptr ? _long_method_signature : _method_signature;
  }

  const char* klassName() const {
    return _long_klass_name != nullptr ? _long_klass_name : _klass_name;
  }
};

ResolvedNames::ResolvedNames() :
  _long_method_name(nullptr),
  _long_method_signature(nullptr),
  _long_klass_name(nullptr) {
}

ResolvedNames::~ResolvedNames() {
    release();
}

void ResolvedNames::release() {
  // Must be idempotent: resolve()'s fault-recovery path calls this explicitly
  // (siglongjmp bypasses ~ResolvedNames()), and then the destructor runs it
  // again on the same object when resolve() returns normally afterward.
  // Nulling out each pointer after freeing makes the second call a no-op
  // instead of a double free.
  if (_long_method_name != nullptr) {
    free(_long_method_name);
    _long_method_name = nullptr;
  }
  if (_long_method_signature != nullptr) {
    free(_long_method_signature);
    _long_method_signature = nullptr;
  }
  if (_long_klass_name != nullptr) {
    free(_long_klass_name);
    _long_klass_name = nullptr;
  }
}

bool ResolvedNames::setImpl(char* short_name, char* volatile& long_name, size_t short_limit, VMSymbol* sym) {
  unsigned len = sym->length();  // raw u2 deref; PC stays inside this library
  // A method name, descriptor or class name is never empty; 0 means the Symbol
  // slot has been recycled. `>=` leaves room for the NUL.
  if (len == 0 || len >= MAX_SYMBOL_LEN) {
    return false;
  }

  char* dest = short_name;
  if (len >= short_limit) {
    long_name = (char*)malloc(len + 1);
    if (long_name == nullptr) {
        return false;   // caller bumps METHOD_RESOLVE_SYMBOL_UNREADABLE
    }
    dest = long_name;
  }

  if (SafeAccess::safeCopy(dest, sym->body(), len)) {
    dest[len] = '\0';
    return true;
  } else {
    return false;
  }
}

bool ResolvedNames::setMethodName(VMSymbol* sym) {
  return setImpl(_method_name, _long_method_name, MAX_METHOD_NAME_LEN, sym);

}
bool ResolvedNames::setMethodSignature(VMSymbol* sym) {
  return setImpl(_method_signature, _long_method_signature, MAX_SIGNATURE_LEN, sym);
}

bool ResolvedNames::setKlassName(VMSymbol* sym) {
  return setImpl(_klass_name, _long_klass_name, MAX_KLASS_NAME_LEN, sym);
}


// PHASE 1 -- the raw HotSpot metadata walk. MUST run with a jmp ctx installed:
// every step is a raw *(void**)(this + offset) whose target may have been freed
// by GC or class unloading since the sample was taken. Deliberately contains no
// JNI and no JVMTI, so the whole protected region stays inside this library,
// where Profiler::checkFault() can actually recover. It can allocate, via
// ResolvedNames::setImpl()'s malloc fallback for over-sized names -- that
// allocation is self-contained (glibc malloc doesn't call back into JNI/JVMTI),
// but it does mean a fault after the allocation needs explicit freeing, since
// siglongjmp out of this scope bypasses ~ResolvedNames() (see resolve()).
//
// Returns false if the metadata is unusable. On success either *out_id holds an
// already-valid jmethodID (and `names` is untouched), or *out_id is null and
// `names` has been filled in for the JNI lookup the caller does afterwards.
static bool readMethodNames(const void* method, VMMethod** out_vm_method,
                            jmethodID* out_id, ResolvedNames* names) {
  *out_vm_method = nullptr;
  *out_id = nullptr;

  VMMethod* vm_method = VMMethod::cast_or_null(method);
  if (vm_method == nullptr) {
    return false;
  }
  *out_vm_method = vm_method;

  // May have been populated by following code or JMETHODID_NOT_WALKABLE
  jmethodID method_id = vm_method->validatedId();
  if (isValidJMethodID(method_id)) {
    *out_id = method_id;
    return true;
  }

  VMConstMethod* const_method = vm_method->constMethod_or_null();
  if (const_method == nullptr) {
    return false;
  }

  VMConstantPool* const_pool = const_method->constants_or_null();
  if (const_pool == nullptr) {
    return false;
  }

  VMSymbol* name_sym = const_method->name();
  VMSymbol* sig_sym = const_method->signature();
  VMKlass* klass = const_pool->holder_or_null();

  if (name_sym == nullptr || sig_sym == nullptr || klass == nullptr) {
    return false;
  }

  VMSymbol* klass_sym = klass->name();
  if (klass_sym == nullptr) {
    return false;
  }

  if (!names->setMethodName(name_sym) || !names->setMethodSignature(sig_sym) || !names->setKlassName(klass_sym)) {
    Counters::increment(METHOD_RESOLVE_SYMBOL_UNREADABLE);
    return false;
  }
  return true;
}

// PHASE 2 -- the JNI/JVMTI lookup, reading only the buffers phase 1 filled.
// MUST run with crash protection *off*. Two reasons, both about siglongjmp
// unwinding frames it must not:
//   - A fault inside libjvm.so is unrecoverable anyway (checkFault() only
//     recovers PCs inside this library), so a landing pad buys nothing here.
//   - FindClass() loads the class when it is not already loaded, which
//     synchronously runs our own JVMTI ClassPrepare callback ->
//     patchClassLoaderData(), which holds the JVM's ClassLoaderData mutex. That
//     code *is* in this library, so with a pad installed a fault there would
//     siglongjmp out of a JVMTI callback with a JVM lock held, an abandoned JNI
//     local frame and unbalanced safepoint state -- trading a crash for a
//     JVM-wide deadlock.
// vm_method->validatedId() below is safefetch-based, so it is safe unprotected.
//
// A plain, TU-local helper -- like readMethodNames() -- rather than a
// HotspotSupport member or friend: it never touches HotspotSupport's private
// state directly, so nothing about it, including ResolvedNames (a type
// defined entirely in this file with no header of its own), needs to be
// declared in hotspotSupport.h. The <clinit> fallback needs the private
// HotspotSupport::loadMethodIDsIfNeededImpl(), so resolve() -- which does
// have access, being a member -- passes it in as a plain function pointer
// instead of this function calling it directly.
//
// Returns a jmethodID valid for as long as the declaring class stays loaded
// (the same ownership/lifetime jmethodIDs always have in this codebase -- no
// release call is needed), or nullptr if the method could not be found via
// JNI/JVMTI.
static jmethodID lookupMethodIdViaJni(VMMethod* vm_method, const ResolvedNames& names,
                                       bool (*loadMethodIDsIfNeededImpl)(jvmtiEnv*, JNIEnv*, jclass, bool)) {
  jmethodID method_id = nullptr;
  const char* method_name = names.methodName();
  const char* method_signature = names.methodSignature();
  const char* klass_name = names.klassName();

  JNIEnv *jni = VM::jni();
  jclass clz = jni->FindClass(klass_name);
  if (clz == nullptr) {
    jni->ExceptionClear();
  } else {
    method_id = jni->GetMethodID(clz, method_name, method_signature);
    if (method_id == nullptr) {
      jni->ExceptionClear();
      method_id = jni->GetStaticMethodID(clz, method_name, method_signature);
      if (method_id == nullptr) {
        jni->ExceptionClear();
        // JNI GetMethodID/GetStaticMethodID cannot look up <clinit> because
        // the JVM intentionally hides class initializers from JNI callers.
        // Fall back to loadMethodIDsIfNeededImpl(), which covers all methods
        // including <clinit> and forces jmethodID slot allocation for them
        // (going through this helper, rather than calling GetClassMethods
        // directly, ensures the JDK-8062116 patchClassLoaderData() workaround
        // is applied here too, same as every other jmethodID-preload path).
        // After the call, re-read the ID directly from VM metadata.
        if (strcmp(method_name, "<clinit>") == 0) {
          jvmtiEnv* jvmti = VM::jvmti();
          if (jvmti != nullptr) {
            if (loadMethodIDsIfNeededImpl(jvmti, jni, clz, true /*load all*/)) {
              jmethodID validated = vm_method->validatedId();
              if (isValidJMethodID(validated)) {
                method_id = validated;
              }
            }
          }
        }
      }
    }
    jni->DeleteLocalRef(clz);
  }

  return method_id;
}

// This method only resolves methods that are loaded by system class loaders
jmethodID HotspotSupport::resolve(const void* method) {
  assert(VM::isHotspot());
  NO_INJECTION_ASSERT(method != nullptr);
  // fillJavaFrame stores the sentinel without the raw flag, so this should
  // never reach the raw-pointer resolve path. Map it to nullptr so the dump
  // thread serializes it as the shared unknown method.
  if ((jmethodID)method == JMETHODID_NOT_WALKABLE) {
    return nullptr;
  }

  // The Method* was captured at sample time; GC or class unloading may have
  // freed the metadata since, so every dereference below can fault. Install a
  // landing pad and report the method as unresolved instead of taking the JVM
  // down mid-dump -- nullptr is already a first-class result for our caller
  // (Lookup::resolveMethod serializes it as the shared unknown method).
  //
  // Runs on the JFR dump thread (Profiler::dump/stop), not in a signal handler.
  // acquireCurrent() rather than current() because JNI_OnUnload reaches
  // Profiler::stop() without priming TLS.
  ProfiledThread* prof_thread = ProfiledThread::acquireCurrent();
  if (prof_thread == nullptr) {
    // No landing pad available, so refuse to touch metadata that may be stale
    // rather than risk crashing. Reached only on an unprimed shutdown path or
    // when the thread-local pool is exhausted.
    Counters::increment(SAMPLES_DROPPED_THREAD_LOCAL);
    return nullptr;
  }

  ResolvedNames names;
  VMMethod* vm_method = nullptr;
  jmethodID existing_id = nullptr;
  bool walked = false;

  {
    sigjmp_buf crash_protection_ctx;
    // Chained via JmpCtxScope: the dump thread can be interrupted by a sampling
    // signal whose walkVM() installs its own context, so the previous landing
    // pad must be reinstated on every exit path from this frame.
    JmpCtxScope jmp_scope(prof_thread);
    // savemask must be 1: the siglongjmp originates inside segvHandler, where
    // the kernel has SIGSEGV blocked, so without restoring the saved mask the
    // signal would stay blocked and the next fault on this thread would be
    // fatal.
    if (sigsetjmp(crash_protection_ctx, 1) != 0) {
      // checkFault() does a siglongjmp from inside segvHandler, bypassing
      // segvHandler's SignalHandlerScope destructor. Compensate, then disarm
      // before touching anything that could fault again.
      SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
      jmp_scope.restore();
      // siglongjmp bypasses ~ResolvedNames(), so a name that was already
      // malloc'd (in setImpl()'s over-sized-name fallback) before the fault
      // would otherwise leak. release() is idempotent, so it's safe that the
      // destructor also runs it when resolve() returns below.
      names.release();
      Counters::increment(METHOD_RESOLVE_FAULT_RECOVERED);
      return nullptr;
    }
    jmp_scope.install(&crash_protection_ctx);

    walked = readMethodNames(method, &vm_method, &existing_id, &names);
  }
  // --- crash protection is off from here on; see lookupMethodIdViaJni() ---

  if (!walked) {
    return nullptr;
  }
  if (existing_id != nullptr) {
    return existing_id;
  }
  return lookupMethodIdViaJni(vm_method, names, &HotspotSupport::loadMethodIDsIfNeededImpl);
}
