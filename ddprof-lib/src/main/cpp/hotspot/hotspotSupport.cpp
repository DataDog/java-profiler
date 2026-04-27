/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstdlib>
#include <setjmp.h>
#include "asyncSampleMutex.h"
#include "hotspot/classloader.inline.h"
#include "hotspot/hotspotSupport.h"
#include "hotspot/jitCodeCache.h"
#include "hotspot/vmStructs.inline.h"
#include "jvmSupport.h"
#include "profiler.h"
#include "stackWalker.inline.h"
#include "frames.h"

using StackWalkValidation::inDeadZone;
using StackWalkValidation::aligned;
using StackWalkValidation::MAX_FRAME_SIZE;
using StackWalkValidation::sameStack;

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
    return NULL;
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
        default:
            // For unknown or invalid BCI types, default to EXECUTION_SAMPLE
            // This maintains backward compatibility and prevents undefined behavior
            return EXECUTION_SAMPLE;
    }
}

static void fillFrameTypes(ASGCT_CallFrame *frames, int num_frames, VMNMethod *nmethod) {
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

static inline void fillFrame(ASGCT_CallFrame& frame, FrameTypeId type, int bci, const VMMethod* method) {
    frame.bci = FrameType::encode(type, bci);
    frame.method = static_cast<const void*>(method);
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
    HotspotStackFrame frame(ucontext);
    uintptr_t bottom = (uintptr_t)&frame + MAX_WALK_SIZE;

    Profiler* profiler = Profiler::instance();
    int bcp_offset = InterpreterFrame::bcp_offset();

    jmp_buf crash_protection_ctx;
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
    void* saved_exception = vm_thread != NULL ? vm_thread->exception() : NULL;

    // Should be preserved across setjmp/longjmp
    volatile int depth = 0;
    int actual_max_depth = truncated ? max_depth + 1 : max_depth;
    bool fp_chain_fallback = false;
    int fp_chain_depth = 0;

    ProfiledThread* profiled_thread = ProfiledThread::currentSignalSafe();

    VMJavaFrameAnchor* anchor = NULL;
    if (vm_thread != NULL) {
        anchor = vm_thread->anchor();
        if (anchor == NULL) {
            Counters::increment(WALKVM_ANCHOR_NULL);
        }
        vm_thread->exception() = &crash_protection_ctx;
        if (profiled_thread != nullptr) {
            profiled_thread->setCrashProtectionActive(true);
        }
        if (setjmp(crash_protection_ctx) != 0) {
            if (profiled_thread != nullptr) {
                profiled_thread->setCrashProtectionActive(false);
            }
            vm_thread->exception() = saved_exception;
            if (depth < max_depth) {
                fillFrame(frames[depth++], BCI_ERROR, "break_not_walkable");
            }
            return depth;
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

    // Show extended frame types and stub frames for execution-type events
    bool details = event_type <= MALLOC_SAMPLE || features.mixed;

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
        // setjmp crash protection in walkVM (checkFault -> longjmp).
        uintptr_t carrier_fp = *(uintptr_t*)entry_fp;
        const void* carrier_pc = ((const void**)entry_fp)[FRAME_PC_SLOT];
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
            // Without vm_thread, crash protection via setjmp/longjmp cannot work
            // (checkFault() needs vm_thread->exception() to longjmp). Any memory dereference in interpreter
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
                    VMMethod* method = VMMethod::cast(((void**)fp)[InterpreterFrame::method_offset]);
                    if (method != nullptr) {
                        jmethodID method_id = getMethodId(method);
    //                    assert(method_id != nullptr || VMClassLoader::isLoadedByBootstrapClassLoader(method));
                        if (method_id != NULL || VMClassLoader::isLoadedByBootstrapClassLoader(method)) {
                            Counters::increment(WALKVM_JAVA_FRAME_OK);
                            const char* bytecode_start = method->bytecode();
                            const char* bcp = ((const char**)fp)[bcp_offset];
                            int bci = bytecode_start == NULL || bcp < bytecode_start ? 0 : bcp - bytecode_start;
                            if (method_id != nullptr) {
                                fillFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id);
                            } else {
                                fillFrame(frames[depth++], FRAME_INTERPRETED_METHOD, bci, method);
                            }
                            sp = ((uintptr_t*)fp)[InterpreterFrame::sender_sp_offset];
                            pc = stripPointer(((void**)fp)[FRAME_PC_SLOT]);
                            fp = *(uintptr_t*)fp;
                            continue;
                        }
                    }
                }

                if (depth == 0) {
                    VMMethod* method = (VMMethod*)frame.method();
                    jmethodID method_id = getMethodId(method);
//                    assert(method_id != nullptr || VMClassLoader::isLoadedByBootstrapClassLoader(method));
                    if (method_id != NULL || VMClassLoader::isLoadedByBootstrapClassLoader(method)) {
                        Counters::increment(WALKVM_JAVA_FRAME_OK);
                        if (method_id != nullptr) {
                            fillFrame(frames[depth++], FRAME_INTERPRETED, 0, method_id);
                        } else {
                            fillFrame(frames[depth++], FRAME_INTERPRETED_METHOD, 0, method);
                        }
                        if (is_plausible_interpreter_frame) {
                            pc = stripPointer(((void**)fp)[FRAME_PC_SLOT]);
                            sp = frame.senderSP();
                            fp = *(uintptr_t*)fp;
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
                fillFrame(frames[depth++], type, 0, nm->method()->id());

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
                            fillFrame(frames[depth++], type, scope.bci(), scope.method()->id());
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
                        VMSymbol* symbol = VMKlass::fromOop(receiver)->name();
                        u32 class_id = profiler->classMap()->lookup(symbol->body(), symbol->length());
                        fillFrame(frames[depth++], BCI_ALLOC, class_id);
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
            }
        } else {
            // Resolve native frame (may use remote symbolication if enabled)
            Profiler::NativeFrameResolution resolution = profiler->resolveNativeFrameForWalkVM((uintptr_t)pc, lock_index);
            if (resolution.is_marked) {
                // This is a marked C++ interpreter frame, terminate scan
                break;
            }
            const char* method_name = resolution.method_name;
            int frame_bci = resolution.bci;
            char mark;
            if (frame_bci != BCI_NATIVE_FRAME_REMOTE && method_name != NULL && (mark = NativeFunc::read_mark(method_name)) != 0) {
                if (mark == MARK_ASYNC_PROFILER && event_type == MALLOC_SAMPLE) {
                    // Skip all internal frames above malloc_hook functions, leave the hook itself
                    depth = 0;
                } else if (mark == MARK_COMPILER_ENTRY && features.comp_task && vm_thread != NULL) {
                    // Insert current compile task as a pseudo Java frame
                    VMMethod* method = vm_thread->compiledMethod();
                    jmethodID method_id = method != NULL ? method->id() : NULL;
                    if (method_id != NULL) {
                        fillFrame(frames[depth++], FRAME_JIT_COMPILED, 0, method_id);
                    }
                } else if (mark == MARK_THREAD_ENTRY) {
                    // Thread entry point detected via pre-computed mark - this is the root frame
                    // No need for expensive symbol resolution, just stop unwinding
                    Counters::increment(THREAD_ENTRY_MARK_DETECTIONS);
                    break;
                }
            } else if (method_name == NULL && details && !anchor_recovery_used
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
                        VMMethod* method = ((VMMethod**)recovery_fp)[InterpreterFrame::method_offset];
                        jmethodID method_id = getMethodId(method);
                        if (method_id != NULL) {
                            anchor = NULL;
                            prev_native_pc = NULL;
                            if (depth > 0 && depth + 1 < actual_max_depth) {
                                fillFrame(frames[depth++], BCI_ERROR, "[skipped frames]");
                            }
                            Counters::increment(WALKVM_JAVA_FRAME_OK);
                            const char* bytecode_start = method->bytecode();
                            const char* bcp = ((const char**)recovery_fp)[bcp_offset];
                            int bci = bytecode_start == NULL || bcp < bytecode_start ? 0 : bcp - bytecode_start;
                            fillFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id);

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
            if (method_id != NULL) {
                Counters::increment(WALKVM_ANCHOR_FALLBACK);
                Counters::increment(WALKVM_JAVA_FRAME_OK);
                anchor = NULL;
                while (depth > 0 && frames[depth - 1].method_id == NULL) depth--;
                if (depth < actual_max_depth) {
                    const char* bytecode_start = method->bytecode();
                    const char* bcp = ((const char**)anchor_fp)[bcp_offset];
                    int bci = bytecode_start == NULL || bcp < bytecode_start ? 0 : bcp - bytecode_start;
                    fillFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id);
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
    if (profiled_thread != nullptr) {
        profiled_thread->setCrashProtectionActive(false);
    }
    if (vm_thread != NULL) {
        vm_thread->exception() = saved_exception;
    }

    // Drop unknown leaf frame - it provides no useful information and breaks
    // aggregation by lumping unrelated samples under a single "unknown" entry
    depth = StackWalkValidation::dropUnknownLeaf(frames, depth);

    if (depth == 0) {
        Counters::increment(WALKVM_DEPTH_ZERO);
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

    return depth;
}

void HotspotSupport::checkFault(ProfiledThread* thrd) {
    if (!JVMThread::isInitialized()) {
        // JVM has not been loaded or has not been initialized yet
        return;
    }

    VMThread* vm_thread = VMThread::current();
    if (vm_thread == NULL || !vm_thread->isThreadAccessible()) {
        return;
    }

    // Prefer the semantic crash protection flag (reliable regardless of stack frame sizes).
    // Fall back to sameStack heuristic when ProfiledThread TLS is unavailable (e.g. during
    // early init or in crash recovery tests). sameStack uses a fixed 8KB threshold which
    // can fail with ASAN-inflated frames, but the crashProtectionActive path handles that.
    bool protected_walk = (thrd != nullptr && thrd->isCrashProtectionActive())
                       || sameStack(vm_thread->exception(), &vm_thread);
    if (!protected_walk) {
        return;
    }

    if (thrd != nullptr) {
        thrd->resetCrashHandler();
    }
    longjmp(*(jmp_buf*)vm_thread->exception(), 1);
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
  VM::_asyncGetCallTrace(&trace, max_depth, ucontext);

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
        VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
      }
    } else if (VMStructs::hasMethodStructs()) {
      VMNMethod *nmethod = CodeHeap::findNMethod((const void *)frame.pc());
      if (nmethod != NULL && nmethod->isNMethod() && nmethod->isAlive()) {
        VMMethod *method = nmethod->method();
        if (method != NULL) {
          jmethodID method_id = method->id();
          if (method_id != NULL) {
            max_depth -= makeFrame(trace.frames++, 0, method_id);
          }
          if (!(safe_mode & POP_METHOD) && frame.unwindCompiled(nmethod) &&
              isAddressInCode((const void *)frame.pc())) {
            VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
          }
          if ((safe_mode & PROBE_SP) && trace.num_frames < 0) {
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
        if (cstack != CSTACK_NO) {
          max_depth -=
              makeFrame(trace.frames++, BCI_NATIVE_FRAME, nmethod->name());
        }
        if (!(safe_mode & POP_STUB) &&
            frame.unwindStub(NULL, nmethod->name()) &&
            isAddressInCode((const void *)frame.pc())) {
          VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
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
        VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
      } else if (libs->findLibraryByAddress(pc) != NULL) {
        VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
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
        VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
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

  int java_frames = 0;
  if (features.mixed) {
    java_frames = walkVM(ucontext, frames, max_depth, features, eventTypeFromBCI(request.event_type), lock_index, truncated);
  } else if (request.event_type == BCI_CPU || request.event_type == BCI_WALL || request.event_type == BCI_NATIVE_MALLOC) {
    if (cstack >= CSTACK_VM) {
        java_frames = walkVM(ucontext, frames, max_depth, features, eventTypeFromBCI(request.event_type), lock_index, truncated);
    } else {
        // Async events
        AsyncSampleMutex mutex(ProfiledThread::currentSignalSafe());
        if (mutex.acquired()) {
            java_frames = getJavaTraceAsync(ucontext, frames, max_depth, java_ctx, truncated);
            if (java_frames > 0 && java_ctx->pc != NULL && VMStructs::hasMethodStructs()) {
                VMNMethod* nmethod = CodeHeap::findNMethod(java_ctx->pc);
                if (nmethod != NULL) {
                    fillFrameTypes(frames, java_frames, nmethod);
                }
            }
        }
        // ASGCT stops at the continuation boundary for virtual threads (JDK 21+).
        // Append a synthetic root frame so the UI does not show "Missing Frames".
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

constexpr const char* LAMBDA_PREFIX = "Ljava/lang/invoke/LambdaForm$";
constexpr const char* FFM_PREFIX = "Ljdk/internal/foreign/abi/";
// constexpr const size_t LAMBDA_PREFIX_LEN = strlen(LAMBDA_PREFIX);
static bool isLambdaClass(const char* signature) {
    return strncmp(signature, LAMBDA_PREFIX, strlen(LAMBDA_PREFIX)) == 0 ||
           strstr(signature, "$$Lambda.") != nullptr ||
           strstr(signature, "$$Lambda$") != nullptr ||
           strstr(signature, ".lambda$") != nullptr ||
           strncmp(signature, FFM_PREFIX, strlen(FFM_PREFIX)) == 0;
}

bool HotspotSupport::loadMethodIDsImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass) {

    patchClassLoaderData(jni, klass);

    jobject cl;
    // Hotpsot only: loaded by bootstrap class loader, which is never unloaded,
    // we use Method instead.
    if (jvmti->GetClassLoader(klass, &cl) == JVMTI_ERROR_NONE && cl == nullptr) {
        char* signature_ptr;
        jvmti->GetClassSignature(klass, &signature_ptr, nullptr);
//        TEST_LOG("processing bootstrap class %s", signature_ptr);
        // Lambda classes can be unloaded, exlcude them
        if (!isLambdaClass(signature_ptr)) {
//            TEST_LOG("Skipping  class %s",signature_ptr);
            return false;
        } else {
//            TEST_LOG("Lambda class: %s", signature_ptr);
        }
    } else if (cl != nullptr) {
        char* signature_ptr;
        jvmti->GetClassSignature(klass, &signature_ptr, nullptr);
//        TEST_LOG("processing none bootstrap class %s", signature_ptr);
    }

    return JVMSupport::loadMethodIDsImpl(jvmti, jni, klass);
}

void JNICALL HotspotSupport::NativeMethodBind(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                                         jmethodID method, void *address,
                                         void **new_address_ptr) {
    VMStructs::NativeMethodBind(jvmti, jni, thread, method, address, new_address_ptr);
}

