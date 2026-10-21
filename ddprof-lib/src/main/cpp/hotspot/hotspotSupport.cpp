/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <atomic>
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
#include "dwarfStep.inline.h"
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
    // callerPC/callerSP/callerFP describe whichever frame evaluates them --
    // they are __builtin_return_address/__builtin_frame_address underneath --
    // so they have to be read here, in the function whose caller the walk is
    // meant to start from. Moving them into a helper seeds the walk one frame
    // too deep wherever that helper is not inlined, which is precisely the
    // debug and sanitizer builds: the walk then burns a profiler frame before
    // reaching the MARK_JAVA_PROFILER boundary, and a shallow malloc/socket
    // sample can run out of depth before it gets there. Keep them inline.
    if (ucontext == NULL) {
        return walkVM(&empty_ucontext, frames, max_depth, features, event_type,
                      callerPC(), CALLER_PC_IS_RETURN_ADDRESS,
                      (uintptr_t)callerSP(), (uintptr_t)callerFP(), lock_index, truncated);
    }
    HotspotStackFrame frame(ucontext);
    return walkVM(ucontext, frames, max_depth, features, event_type,
                  (const void*)frame.pc(), /*pc_is_return_address=*/false,
                  frame.sp(), frame.fp(), lock_index, truncated);
}

__attribute__((no_sanitize("address"))) int HotspotSupport::walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                        StackWalkFeatures features, EventType event_type,
                        const void* entry_pc, bool pc_is_return_address,
                        uintptr_t sp, uintptr_t fp, int lock_index, bool* truncated) {

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
    // JVMThread::current() asserts its thread-local key is live, which only a
    // JVM attach sets up. Only the Java-frame paths below need a VMThread --
    // the native walk does not -- so ask whether one exists rather than
    // requiring it. With a JVM attached this is always true and nothing
    // changes; without one, the walk degrades to the NULL handling every use
    // below already has, and WALKVM_NO_VMTHREAD still records that it did.
    VMThread* vm_thread = JVMThread::isInitialized() ? VMThread::current() : nullptr;
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

    // The walking pc and whether it came out of a return-address slot travel
    // together, so a newly added pc source has to say which it is instead of
    // inheriting whatever the previous frame happened to set. Range-based
    // lookups -- findLibraryByAddress, findFrameDesc, the DW_REG_PLT
    // stub-offset test -- go through attribution(), otherwise a call that is
    // the last instruction of its caller selects whatever follows the caller.
    // Exact-address consumers (isContReturnBarrier, isContEntryReturnPc,
    // isEntryFrame), the DW_PC_OFFSET arithmetic and the no-progress guard
    // read raw().
    WalkPc walk_pc;
    walk_pc.setSeed(entry_pc, pc_is_return_address);

    // The previous frame's pc, kept for the MARK_THREAD_ENTRY check, with the
    // same distinction attached.
    WalkPc prev_native_walk_pc;
    bool have_prev_native_pc = false;

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
        // Read out of the carrier frame's saved-pc slot.
        walk_pc.setReturnAddress(carrier_pc);
        return true;
    };

    unwind_loop:

    // Walk until the bottom of the stack or until the first Java frame
    while (depth < actual_max_depth) {
        if (CodeHeap::contains(walk_pc.raw())) {
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
            have_prev_native_pc = false; // we are in JVM code, no previous 'native' PC
            // Both continuation boundary PCs are JVM stubs whose findNMethod()
            // returns NULL; detect them by exact-PC match before the nmethod
            // dispatch below.
            // cont_returnBarrier: bottom thawed frame returns here when frozen
            //   frames remain in the StackChunk (blocking/remounted VT).
            // cont_entry_return_pc: bottom thawed frame returns here when the
            //   continuation is fully thawed (CPU-bound VT, never yielded).
            if (!CONT_UNWIND_DISABLED && VMStructs::isContReturnBarrier(walk_pc.raw())) {
                Counters::increment(WALKVM_CONT_BARRIER_HIT);
                if (walkThroughContinuation(false)) continue;
                break;
            }
            if (!CONT_UNWIND_DISABLED && VMStructs::isContEntryReturnPc(walk_pc.raw())) {
                Counters::increment(WALKVM_ENTER_SPECIAL_HIT);
                if (walkThroughContinuation(true)) continue;
                break;
            }
            VMNMethod* nm = CodeHeap::findNMethod(walk_pc.raw());
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
                const void* anchor_pc = walk_pc.raw();
                if (anchor->getFrame(anchor_pc, sp, fp)) {
                    // getFrame() redirects pc to lastJavaPC(), a return address.
                    walk_pc.setReturnAddress(anchor_pc);
                    if (!nm->contains(walk_pc.raw())) {
                        anchor = NULL;
                        continue;  // NMethod has changed as a result of correction
                    }
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
                        walk_pc.setReturnAddress(stripPointer(((void**)fp)[FRAME_PC_SLOT]));
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
                            walk_pc.setReturnAddress(stripPointer(((void**)fp_addr)[FRAME_PC_SLOT]));
                            sp = frame.senderSP();
                            fp = *fp_addr;
                        } else {
                            walk_pc.setReturnAddress(stripPointer(SafeAccess::load((void**)sp)));
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

                if (nm->isFrameCompleteAt(walk_pc.raw())) {
                    const void* epilogue_pc = walk_pc.raw();
                    if (depth == 1 && frame.unwindEpilogue(nm, (uintptr_t&)epilogue_pc, sp, fp)) {
                        walk_pc.setReturnAddress(epilogue_pc);
                        continue;
                    }

                    int scope_offset = nm->findScopeOffset(walk_pc.raw());
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
                    frame.adjustSP(nm->entry(), walk_pc.raw(), sp);

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
                    // Saved return address of the caller frame.
                    walk_pc.setReturnAddress(((const void**)sp)[-FRAME_PC_SLOT]);
                    continue;
                } else {
                    const void* prologue_pc = walk_pc.raw();
                    if (frame.unwindPrologue(nm, (uintptr_t&)prologue_pc, sp, fp)) {
                        walk_pc.setReturnAddress(prologue_pc);
                        continue;
                    }
                }

                Counters::increment(WALKVM_BREAK_COMPILED);
                fillFrame(frames[depth++], BCI_ERROR, "break_compiled");
                break;
            } else if (nm->isEntryFrame(walk_pc.raw()) && !features.mixed) {
                VMJavaFrameAnchor* next_anchor = VMJavaFrameAnchor::fromEntryFrame(fp);
                if (next_anchor == NULL) {
                    fillFrame(frames[depth++], BCI_ERROR, "break_entry_frame");
                    break;
                }
                uintptr_t prev_sp = sp;
                const void* entry_frame_pc = walk_pc.raw();
                if (!next_anchor->getFrame(entry_frame_pc, sp, fp)) {
                    // End of Java stack
                    break;
                }
                // getFrame() redirects pc to lastJavaPC(), a return address.
                walk_pc.setReturnAddress(entry_frame_pc);
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

                // One shared-lock acquisition returns the stub view plus the
                // precomputed aarch64 unwind info (null on x64): the signal
                // handler still takes _stubs_lock exactly once.
                const void* start;
                const char* name;
                const StubUnwindInfo* stub_info = nullptr;
#ifdef __aarch64__
                if (!JitCodeCache::findRuntimeStubInfo(walk_pc.raw(), &start, &name, &stub_info)) {
                    start = nm->code();
                    name = nm->name();
                }
#else
                CodeBlob* stub = JitCodeCache::findRuntimeStub(walk_pc.raw());
                start = stub != NULL ? stub->_start : nm->code();
                name = stub != NULL ? stub->_name : nm->name();
#endif

                if (details) {
                    fillFrame(frames[depth++], BCI_NATIVE_FRAME, name);
                }

                const void* stub_pc = walk_pc.raw();
                if (frame.unwindStub((instruction_t*)start, name, (uintptr_t&)stub_pc, sp, fp, stub_info)) {
                    walk_pc.setReturnAddress(stub_pc);
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
                    // Saved return address of the caller frame.
                    walk_pc.setReturnAddress(((const void**)sp)[-FRAME_PC_SLOT]);
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
            Profiler::NativeFrameResolution resolution = profiler->resolveNativeFrameForWalkVM((uintptr_t)walk_pc.raw(), walk_pc.isReturnAddress(), lock_index);
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
                       && profiler->findLibraryByAddress(walk_pc.attribution()) == NULL) {
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
                            have_prev_native_pc = false;
                            if (depth > 0 && depth + 1 < actual_max_depth) {
                                fillFrame(frames[depth++], BCI_ERROR, "[skipped frames]");
                            }
                            Counters::increment(WALKVM_JAVA_FRAME_OK);
                            const char* bytecode_start = method->bytecode();
                            const char* bcp = ((const char**)recovery_fp)[bcp_offset];
                            int bci = bytecode_start == NULL || bcp < bytecode_start ? 0 : bcp - bytecode_start;
                            HotspotSupport::fillJavaFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id, method);
                            sp = ((uintptr_t*)recovery_fp)[InterpreterFrame::sender_sp_offset];
                            walk_pc.setReturnAddress(stripPointer(((void**)recovery_fp)[FRAME_PC_SLOT]));
                            fp = *(uintptr_t*)recovery_fp;
                            continue;
                        }
                    }

                    // Fallback: redirect via recovery SP/FP/PC
                    sp = recovery_sp;
                    fp = recovery_fp;
                    // lastJavaPC() records where the Java frame resumes, i.e. a
                    // return address; so is the sp[-1] slot read just below.
                    walk_pc.setReturnAddress(recovery_pc);
                    if (walk_pc.raw() != NULL && !CodeHeap::contains(walk_pc.raw())
                            && sp != 0 && aligned(sp) && sp < bottom) {
                        walk_pc.setReturnAddress(((const void**)sp)[-1]);
                    }
                    if (sp != 0 && walk_pc.raw() != NULL) {
                        anchor = NULL;
                        if (sp >= bottom || !aligned(sp)) {
                            Counters::increment(WALKVM_ANCHOR_INLINE_BAD_SP);
                            fillFrame(frames[depth++], BCI_ERROR, "break_no_anchor");
                            break;
                        }
                        have_prev_native_pc = false;
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
                if (have_prev_native_pc) {
                    Profiler::NativeFrameResolution prev_resolution = profiler->resolveNativeFrameForWalkVM(
                        (uintptr_t)prev_native_walk_pc.raw(), prev_native_walk_pc.isReturnAddress(), lock_index);
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
        // Snapshotted before the step rather than mid-way through it as the
        // inlined copy used to: nothing between here and that point mutates
        // walk_pc, and a stop leaves the loop, so the only reader -- the
        // MARK_THREAD_ENTRY check on the next iteration -- sees the same value.
        prev_native_walk_pc = walk_pc;
        have_prev_native_pc = true;

        if (!advanceDwarfFrame(walk_pc, sp, fp, bottom, depth, frame,
                               profiler)) {
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
                    walk_pc.setReturnAddress(stripPointer(((void**)anchor_fp)[FRAME_PC_SLOT]));
                    fp = *(uintptr_t*)anchor_fp;
                    if (sp != 0 && sp < bottom && aligned(sp)) {
                        goto unwind_loop;
                    }
                }
            }
        }
        // Fallback: redirect via anchor frame and sp[-1]
        const void* fallback_pc = walk_pc.raw();
        if (anchor != NULL && anchor->getFrame(fallback_pc, sp, fp)) {
            // Both the anchor's lastJavaPC() and the sp[-1] slot are return addresses.
            walk_pc.setReturnAddress(fallback_pc);
            if (!CodeHeap::contains(walk_pc.raw()) && sp != 0 && aligned(sp) && sp < bottom) {
                walk_pc.setReturnAddress(((const void**)sp)[-1]);
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
                                bool *truncated, HotspotStackFrame::RegisterSnapshot& ctx_snapshot) {
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
  // ctx_snapshot (passed in by the caller) snapshotted pc/sp/fp before this
  // function starts feeding them to HotSpot's own AsyncGetCallTrace below (it
  // mutates them in place via frame.restore() / frame.unwindStub() /
  // frame.unwindCompiled() to try alternate frames), so they can be put back
  // once AGCT is done. It's the same instance withUcontextFaultRecovery()
  // restores on a recovered fault -- see its own comment -- which is also why
  // any JavaThread anchor mutation below must be recorded on it via
  // saveJavaAnchor() rather than tracked locally. None of this function's own
  // return paths need to call ctx_snapshot.restore() themselves: it's a local
  // of withUcontextFaultRecovery, and RegisterSnapshot's destructor
  // unconditionally restores on scope exit -- covering every return here,
  // the same way it covers a recovered fault.
  if (ucontext != NULL) {
    if (JitCodeCache::isCallStub((const void *)ctx_snapshot.pc())) {
       // call_stub is unsafe to walk
      frames->bci = BCI_ERROR;
      frames->method_id = (jmethodID) "call_stub";
      return 1;
    }

    if (!VMStructs::isSafeToWalk(ctx_snapshot.pc())) {
      frames->bci = BCI_NATIVE_FRAME;
      CodeBlob *codeBlob =
          VMStructs::libjvm()->findBlobByAddress((const void *)ctx_snapshot.pc());
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
    // skip ahead to the Java frames before calling AGCT.
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

  // AsyncGetCallTrace writes to ASGCT_CallFrame array
  ASGCT_CallTrace trace = {jni, 0, frames};
  JVMSupport::jvmAsyncGetCallTrace(&trace, max_depth, ucontext);

  if (trace.num_frames > 0) {
    return trace.num_frames;
  }

  int safe_mode = Profiler::instance()->safe_mode();
  CStack cstack = Profiler::instance()->cstackMode();
  
  if ((trace.num_frames == ticks_unknown_Java ||
       trace.num_frames == ticks_not_walkable_Java) &&
      !(safe_mode & UNKNOWN_JAVA) && ucontext != NULL) {
    const void* stub_start;
    const char* stub_name;
    const StubUnwindInfo* stub_info = nullptr;
#ifdef __aarch64__
    if (JitCodeCache::findRuntimeStubInfo((const void *)frame.pc(), &stub_start, &stub_name, &stub_info)) {
#else
    CodeBlob *stub = JitCodeCache::findRuntimeStub((const void *)frame.pc());
    if (stub != NULL) {
      stub_start = stub->_start;
      stub_name = stub->_name;
#endif
      if (cstack != CSTACK_NO) {
        max_depth -= makeFrame(trace.frames++, BCI_NATIVE_FRAME, stub_name);
      }
      if (!(safe_mode & POP_STUB) &&
          frame.unwindStub((instruction_t *)stub_start, stub_name, stub_info) &&
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
              frame.sp() = frame.sp() + sizeof(void*);
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
    if (anchor == NULL) {
      return 0;
    }
    uintptr_t sp = anchor->lastJavaSP();
    const void* pc = anchor->lastJavaPC();
    if (sp != 0 && pc == NULL) {
      // We have the last Java frame anchor, but it is not marked as walkable.
      // Make it walkable here.
      // sp comes straight from the anchor with no validation; fault-inject it
      // so the unguarded dereference below exercises the sigsetjmp/siglongjmp
      // recovery path installed by the caller (withUcontextFaultRecovery) instead of only
      // ever running against a known-good sp.
      pc = *(const void**)INJECT_FAULT_ADDRESS_UNLIKELY((const void**)sp - 1);
      ctx_snapshot.saveJavaAnchor(anchor, NULL);
      anchor->setLastJavaPC<false /* plain store */>(pc);

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
    }
  } else if (trace.num_frames == ticks_not_walkable_not_Java &&
             !(safe_mode & LAST_JAVA_PC)) {
    VMJavaFrameAnchor* anchor = vm_thread->anchor();
    if (anchor == NULL) {
      return 0;
    }
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
      return 0;
    }
  }

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

int HotspotSupport::asyncJavaTraceWithPostProcessing(void* ucontext, ASGCT_CallFrame* frames,
                                                      int max_depth, StackContext* java_ctx,
                                                      bool* truncated, ProfiledThread* prof_thread) {
  // getJavaTraceAsync() dereferences VMThread/anchor state directly, calls
  // into HotSpot's own AsyncGetCallTrace, and mutates the real ucontext's
  // pc/sp/fp (and, via saveJavaAnchor(), the JavaThread anchor) in place
  // while doing so, with no crash protection of its own. withUcontextFaultRecovery()
  // installs a jmp ctx around just that path, so a SIGSEGV there (except
  // inside HotSpot's own AsyncGetCallTrace call) is caught by
  // Profiler::checkFault() and recovered instead of crashing the process --
  // see its own comment for why it also restores the ucontext.
  // Both guards deliberately outlive withUcontextFaultRecovery(): a recovered
  // siglongjmp bypasses destructors for objects in its callback.  Keeping the
  // JIT protection guard here ensures macOS arm64 restores the sampled
  // thread's W^X state when this function returns from the recovery branch.
  // WxRestoreOnRecoveryTest pins this guard layout on macOS arm64.
  AsyncSampleMutex mutex(prof_thread);
  if (!mutex.acquired()) {
    return 0;
  }
  JitWriteProtection jit(false);
  volatile int partial = 0;
  return withUcontextFaultRecovery(ucontext, prof_thread, truncated, partial, [&](HotspotStackFrame::RegisterSnapshot& ctx_snapshot) {
      partial = getJavaTraceAsync(ucontext, frames, max_depth, java_ctx, truncated, ctx_snapshot);
      if (partial > 0 && java_ctx->pc != NULL && VMStructs::hasMethodStructs()) {
          VMNMethod* nmethod = CodeHeap::findNMethod(java_ctx->pc);
          if (nmethod != NULL) {
              fillFrameTypes(frames, partial, nmethod);
          }
      }
      if (partial > 0 && VM::hotspot_version() >= 21 && partial < max_depth) {
          VMThread* carrier = VMThread::current();
          if (carrier != nullptr && carrier->isCarryingVirtualThread()) {
              frames[partial].bci = BCI_NATIVE_FRAME;
              frames[partial].method_id = (jmethodID) "JVM Continuation";
              LP64_ONLY(frames[partial].padding = 0;)
              partial++;
          }
      }
  });
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

  ProfiledThread* prof_thread = ProfiledThread::acquireCurrent();
  if (prof_thread == nullptr) {
    Counters::increment(SAMPLES_DROPPED_THREAD_LOCAL);
    return 0;
  }

  // walkVM() mutates none of the real ucontext's pc/sp/fp -- it unwinds
  // through its own local pc/sp/fp copies -- and installs its own
  // sigsetjmp/siglongjmp crash protection (chained with any pre-existing jmp
  // ctx, see the comment in walkVM), so a fault during it is caught by
  // walkVM's own recovery branch, never propagated here. It's dispatched
  // directly, with no withUcontextFaultRecovery() wrapper: constructing that
  // wrapper's RegisterSnapshot would be pure overhead on this path -- pc/sp/fp
  // reads into uc_mcontext with nothing to ever restore. asyncJavaTraceWithPostProcessing()
  // (see its own comment) is the getJavaTraceAsync() counterpart, wrapped
  // because that path does mutate the ucontext with no crash protection of
  // its own.
  //
  // isHookPrefixedSample()/BCI_CPU/BCI_WALL samples share the exact same
  // walkVM-vs-async dispatch, just gated on different event types, so they're
  // collapsed into one branch here rather than duplicated per event type.
  if (features.mixed) {
    return walkVM(ucontext, frames, max_depth, features, eventTypeFromBCI(request.event_type), lock_index, truncated);
  }
  if (isHookPrefixedSample(request.event_type) || request.event_type == BCI_CPU || request.event_type == BCI_WALL) {
    if (cstack >= CSTACK_VM) {
      return walkVM(ucontext, frames, max_depth, features, eventTypeFromBCI(request.event_type), lock_index, truncated);
    }
    return asyncJavaTraceWithPostProcessing(ucontext, frames, max_depth, java_ctx, truncated, prof_thread);
  }
  return 0;
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

// ClassLoaderData of the boot, platform and application class loaders; see
// HotspotSupport::isPermanentLoaderData().
enum { PERMANENT_BOOT, PERMANENT_PLATFORM, PERMANENT_APPLICATION, PERMANENT_COUNT };
static std::atomic<const void*> PERMANENT_LOADER_DATA[PERMANENT_COUNT];

static bool permanentLoaderDataComplete() {
    return PERMANENT_LOADER_DATA[PERMANENT_APPLICATION].load(std::memory_order_acquire) != nullptr &&
           (JAVA_PLATFORM_CLASSLOADER == nullptr ||  // JDK 8
            PERMANENT_LOADER_DATA[PERMANENT_PLATFORM].load(std::memory_order_acquire) != nullptr);
}

// fromJavaClass() needs java.lang.Class's klass field, part of hasClassNames().
static bool canReadLoaderData() {
    return VMStructs::class_loader_data_offset() >= 0 && VMStructs::hasClassNames();
}

const void* HotspotSupport::classLoaderDataOf(JNIEnv* jni, jclass klass) {
    if (!canReadLoaderData()) {
        return nullptr;
    }
    VMKlass* vmklass = VMKlass::fromJavaClass(jni, klass);
    // As in readMethod(): the field's value, not a typed VMClassLoaderData*.
    return vmklass != nullptr
               ? *(const void* const*)((const char*)vmklass + VMStructs::class_loader_data_offset())
               : nullptr;
}

void HotspotSupport::initPermanentLoaderData(jvmtiEnv* jvmti, JNIEnv* jni) {
    if (!canReadLoaderData()) {
        return;
    }
    initClassloaderInfo(jni);
    if (PERMANENT_LOADER_DATA[PERMANENT_BOOT].load(std::memory_order_acquire) == nullptr) {
        jclass object_class = jni->FindClass("java/lang/Object");
        if (object_class != nullptr) {
            PERMANENT_LOADER_DATA[PERMANENT_BOOT].store(classLoaderDataOf(jni, object_class),
                                                        std::memory_order_release);
            jni->DeleteLocalRef(object_class);
        } else {
            jni->ExceptionClear();
        }
    }
    if (permanentLoaderDataComplete()) {
        return;
    }
    jint count = 0;
    jclass* classes = nullptr;
    if (jvmti->GetLoadedClasses(&count, &classes) != JVMTI_ERROR_NONE) {
        return;
    }
    for (int i = 0; i < count; i++) {
        if (!permanentLoaderDataComplete()) {
            notePermanentLoaderData(jvmti, jni, classes[i]);
        }
        jni->DeleteLocalRef(classes[i]);
    }
    jvmti->Deallocate((unsigned char*)classes);
}

void HotspotSupport::notePermanentLoaderData(jvmtiEnv* jvmti, JNIEnv* jni, jclass klass) {
    if (!canReadLoaderData() || permanentLoaderDataComplete()) {
        return;
    }
    jobject cl = nullptr;
    if (jvmti->GetClassLoader(klass, &cl) != JVMTI_ERROR_NONE || cl == nullptr) {
        return;  // the boot loader's is taken from java.lang.Object
    }
    int slot = jni->IsSameObject(cl, JAVA_APPLICATION_CLASSLOADER) ? PERMANENT_APPLICATION
             : JAVA_PLATFORM_CLASSLOADER != nullptr &&
               jni->IsSameObject(cl, JAVA_PLATFORM_CLASSLOADER) ? PERMANENT_PLATFORM
             : PERMANENT_COUNT;
    jni->DeleteLocalRef(cl);
    if (slot == PERMANENT_COUNT ||
        PERMANENT_LOADER_DATA[slot].load(std::memory_order_acquire) != nullptr) {
        return;
    }
    // A hidden or VM-anonymous class has a ClassLoaderData of its own, not
    // its loader's.
    char* signature = nullptr;
    if (jvmti->GetClassSignature(klass, &signature, nullptr) != JVMTI_ERROR_NONE) {
        return;
    }
    bool hidden = isHiddenClassBySignature(signature) || isLambdaClass(signature);
    jvmti->Deallocate((unsigned char*)signature);
    if (!hidden && !isHiddenClass(jvmti, klass)) {
        PERMANENT_LOADER_DATA[slot].store(classLoaderDataOf(jni, klass), std::memory_order_release);
    }
}

#ifdef UNIT_TEST
void HotspotSupport::setPermanentLoaderDataForTest(const void* class_loader_data) {
    PERMANENT_LOADER_DATA[PERMANENT_BOOT].store(class_loader_data, std::memory_order_release);
}
#endif

bool HotspotSupport::isPermanentLoaderData(const void* class_loader_data) {
    if (class_loader_data == nullptr) {
        return false;
    }
    for (int i = 0; i < PERMANENT_COUNT; i++) {
        if (PERMANENT_LOADER_DATA[i].load(std::memory_order_acquire) == class_loader_data) {
            return true;
        }
    }
    return false;
}

bool HotspotSupport::loadMethodIDsIfNeededImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass, bool load_all) {
    notePermanentLoaderData(jvmti, jni, klass);
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

ResolvedMethod::ResolvedMethod() :
  _long_method_name(nullptr),
  _long_method_signature(nullptr),
  _long_klass_name(nullptr),
  _line_number_table(nullptr),
  _line_number_table_size(0),
  _is_thread_run(false),
  _class_loader_data(nullptr) {
  _method_name[0] = '\0';
  _method_signature[0] = '\0';
  _klass_name[0] = '\0';
}

void ResolvedMethod::release() {
  // Must be idempotent: resolve()'s fault-recovery path calls this explicitly
  // (siglongjmp bypasses ~ResolvedMethod()), and the destructor runs it again
  // on the same object later. Nulling out each pointer after freeing makes
  // the second call a no-op instead of a double free.
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
  if (_line_number_table != nullptr) {
    free(_line_number_table);
    _line_number_table = nullptr;
  }
  _line_number_table_size = 0;
}

bool ResolvedMethod::setName(char* short_name, char* volatile& long_name, size_t short_limit, VMSymbol* sym) {
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

bool ResolvedMethod::setMethodName(VMSymbol* sym) {
  return setName(_method_name, _long_method_name, MAX_METHOD_NAME_LEN, sym);
}

bool ResolvedMethod::setMethodSignature(VMSymbol* sym) {
  return setName(_method_signature, _long_method_signature, MAX_SIGNATURE_LEN, sym);
}

bool ResolvedMethod::setKlassName(VMSymbol* sym) {
  return setName(_klass_name, _long_klass_name, MAX_KLASS_NAME_LEN, sym);
}

// Compares a Symbol's contents with `expected` without touching the Symbol
// memory through libc (a fault inside memcmp() would have a pc outside this
// library and could not be recovered).
static bool symbolEquals(VMSymbol* sym, const char* expected, size_t expected_len) {
  static constexpr size_t MAX_COMPARE_LEN = 64;
  assert(expected_len <= MAX_COMPARE_LEN);
  if (sym == nullptr || sym->length() != expected_len) {
    return false;
  }
  char buf[MAX_COMPARE_LEN];
  return SafeAccess::safeCopy(buf, sym->body(), expected_len) &&
         memcmp(buf, expected, expected_len) == 0;
}

// Whether `klass` is java.lang.Thread or one of its subclasses, by walking
// the Klass::_super chain. Unknown (no _super offset) is reported as false.
static bool isThreadSubclass(VMKlass* klass) {
  static const char THREAD_CLASS[] = "java/lang/Thread";
  // Real hierarchies are far shallower; the cap only guards against a cycle
  // in stale metadata.
  static constexpr int MAX_DEPTH = 64;
  for (int depth = 0; klass != nullptr && depth < MAX_DEPTH; depth++) {
    if (symbolEquals(klass->name(), THREAD_CLASS, sizeof(THREAD_CLASS) - 1)) {
      return true;
    }
    klass = klass->super_or_null();
  }
  return false;
}

// Decodes the method's compressed line number table into a malloc'd
// jvmtiLineNumberEntry array, the same shape JVMTI GetLineNumberTable()
// produces. Returns false only if the table is present but implausible (a
// bci outside the bytecode or too many entries), i.e. the metadata is stale;
// a method without a table returns true with no table attached.
static bool readLineNumberTable(VMConstMethod* const_method,
                                jvmtiLineNumberEntry* volatile& table, volatile int& table_size) {
  const unsigned char* compressed = const_method->compressedLineNumberTable();
  if (compressed == nullptr) {
    return true;
  }
  int code_size = const_method->codeSize();

  // Pass 1: validate and count, so the second pass can fill an exactly-sized
  // buffer. Every bci must index the bytecode (JVMS 4.7.12).
  int count = 0;
  VMLineNumberStream counter(compressed);
  while (counter.readPair()) {
    if (counter.bci() < 0 || counter.bci() >= code_size ||
        ++count > ResolvedMethod::MAX_LINE_NUMBER_TABLE_ENTRIES) {
      return false;
    }
  }
  if (count == 0) {
    return true;
  }

  jvmtiLineNumberEntry* entries = (jvmtiLineNumberEntry*)malloc((size_t)count * sizeof(jvmtiLineNumberEntry));
  if (entries == nullptr) {
    return true;  // keep the names; the frame just has no line numbers
  }
  // Owned by the ResolvedMethod from here on, so a fault in pass 2 still frees it.
  table = entries;

  VMLineNumberStream reader(compressed);
  for (int i = 0; i < count; i++) {
    if (!reader.readPair()) {
      return false;   // stream changed under us between the passes
    }
    entries[i].start_location = (jlocation)reader.bci();
    entries[i].line_number = (jint)reader.line();
  }
  table_size = count;
  return true;
}

// The raw HotSpot metadata walk. MUST run with a jmp ctx installed: every step
// is a raw *(void**)(this + offset) whose target may have been freed by GC or
// class unloading since the sample was taken. Contains no JNI and no JVMTI, so
// the whole protected region stays inside this library, where
// Profiler::checkFault() can recover. Allocations it makes are owned by
// `result` as soon as they are made, so resolve()'s landing pad can free them.
bool HotspotSupport::readMethod(const void* method, ResolvedMethod* result) {
  VMMethod* vm_method = VMMethod::cast_or_null(method);
  if (vm_method == nullptr) {
    return false;
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

  if (!result->setMethodName(name_sym) || !result->setMethodSignature(sig_sym) || !result->setKlassName(klass_sym)) {
    Counters::increment(METHOD_RESOLVE_SYMBOL_UNREADABLE);
    return false;
  }

  if (strcmp(result->methodName(), "run") == 0 && strcmp(result->methodSignature(), "()V") == 0) {
    result->_is_thread_run = isThreadSubclass(klass);
  }
  if (VMStructs::class_loader_data_offset() >= 0) {
    // Only ever compared, never dereferenced: read the field rather than go
    // through classLoaderData(), whose typed cast needs ClassLoaderData's
    // size from the JVM's exported types.
    result->_class_loader_data =
        *(const void* const*)((const char*)klass + VMStructs::class_loader_data_offset());
  }

  if (!readLineNumberTable(const_method, result->_line_number_table, result->_line_number_table_size)) {
    Counters::increment(LINE_NUMBER_TABLE_UNREADABLE);
    return false;
  }
  return true;
}

bool HotspotSupport::resolve(const void* method, ResolvedMethod& result) {
  assert(VM::isHotspot());
  NO_INJECTION_ASSERT(method != nullptr);
  // fillJavaFrame stores the sentinel without the raw flag, so this should
  // never reach the raw-pointer resolve path. Report it as unresolved so the
  // dump thread serializes it as the shared unknown method.
  if ((jmethodID)method == JMETHODID_NOT_WALKABLE) {
    return false;
  }

  // The Method* was captured at sample time; GC or class unloading may have
  // freed the metadata since, so every dereference below can fault. Install a
  // landing pad and report the method as unresolved instead of taking the JVM
  // down mid-dump -- false is already a first-class result for our caller
  // (Lookup::fillMethod serializes it as the shared unknown method).
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
    return false;
  }

  bool resolved = false;
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
      // siglongjmp bypasses ~ResolvedMethod() and skips the cleanup below;
      // free whatever was allocated before the fault.
      result.release();
      Counters::increment(METHOD_RESOLVE_FAULT_RECOVERED);
      return false;
    }
    jmp_scope.install(&crash_protection_ctx);

    resolved = readMethod(method, &result);
  }

  if (!resolved) {
    result.release();
  }
  return resolved;
}
