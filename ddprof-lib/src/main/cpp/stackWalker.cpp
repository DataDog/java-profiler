/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include <setjmp.h>
#include "stackWalker.h"
#include "dwarf.h"
#include "profiler.h"
#include "safeAccess.h"
#include "stackFrame.h"
#include "symbols.h"
#include "vmStructs.inline.h"
#include "thread.h"


const uintptr_t MAX_WALK_SIZE = 0x100000;
const intptr_t MAX_FRAME_SIZE_WORDS = StackWalkValidation::MAX_FRAME_SIZE / sizeof(void*);  // 0x8000 = 32768 words

static ucontext_t empty_ucontext{};

// Use validation helpers from header (shared with tests)
using StackWalkValidation::inDeadZone;
using StackWalkValidation::aligned;
using StackWalkValidation::MAX_FRAME_SIZE;
using StackWalkValidation::SAME_STACK_DISTANCE;
using StackWalkValidation::sameStack;

// AArch64: on Linux, frame link is stored at the top of the frame,
// while on macOS, frame link is at the bottom.
static inline uintptr_t defaultSenderSP(uintptr_t sp, uintptr_t fp) {
#ifdef __APPLE__
    return sp + 2 * sizeof(void*);
#else
    return fp;
#endif
}

static inline void fillFrame(ASGCT_CallFrame& frame, ASGCT_CallFrameType type, const char* name) {
    frame.bci = type;
    frame.method_id = (jmethodID)name;
}

// Overload for RemoteFrameInfo* (passed as void* to support both char* and RemoteFrameInfo*)
static inline void fillFrame(ASGCT_CallFrame& frame, int bci, void* method_id_ptr) {
    frame.bci = bci;
    frame.method_id = (jmethodID)method_id_ptr;
}

static inline void fillFrame(ASGCT_CallFrame& frame, ASGCT_CallFrameType type, u32 class_id) {
    frame.bci = type;
    frame.method_id = (jmethodID)(uintptr_t)class_id;
}

static inline void fillFrame(ASGCT_CallFrame& frame, FrameTypeId type, int bci, jmethodID method) {
    frame.bci = FrameType::encode(type, bci);
    frame.method_id = method;
}

static jmethodID getMethodId(VMMethod* method) {
    if (!inDeadZone(method) && aligned((uintptr_t)method)
            && SafeAccess::isReadableRange(method, VMMethod::type_size())) {
        return method->validatedId();
    }
    return NULL;
}


int StackWalker::walkFP(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated) {
    const void* pc;
    uintptr_t fp;
    uintptr_t sp;
    uintptr_t bottom = (uintptr_t)&sp + MAX_WALK_SIZE;

    StackFrame frame(ucontext);
    if (ucontext == NULL) {
        pc = callerPC();
        fp = (uintptr_t)callerFP();
        sp = (uintptr_t)callerSP();
    } else {
        pc = (const void*)frame.pc();
        fp = frame.fp();
        sp = frame.sp();
    }

    int depth = 0;
    int actual_max_depth = truncated ? max_depth + 1 : max_depth;

    // Walk until the bottom of the stack or until the first Java frame
    while (depth < actual_max_depth) {
        if (CodeHeap::contains(pc) && !(depth == 0 && frame.unwindAtomicStub(pc)) &&
            VMThread::current() != nullptr) {  // If it is not a JVM thread, it cannot have Java frame
            java_ctx->set(pc, sp, fp);
            break;
        }

        callchain[depth++] = pc;

        // Check if the next frame is below on the current stack
        if (fp < sp || fp >= sp + MAX_FRAME_SIZE || fp >= bottom) {
            break;
        }

        // Frame pointer must be word aligned
        if (!aligned(fp)) {
            break;
        }

        pc = stripPointer(SafeAccess::load((void**)fp + FRAME_PC_SLOT));
        if (inDeadZone(pc)) {
            break;
        }

        sp = fp + (FRAME_PC_SLOT + 1) * sizeof(void*);
        fp = (uintptr_t)SafeAccess::load((void**)fp);
    }

    if (truncated && depth > max_depth) {
        *truncated = true;
        depth = max_depth;
    }

    return depth;
}

int StackWalker::walkDwarf(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated) {
    const void* pc;
    uintptr_t fp;
    uintptr_t sp;
    uintptr_t bottom = (uintptr_t)&sp + MAX_WALK_SIZE;

    StackFrame frame(ucontext);
    if (ucontext == NULL) {
        pc = callerPC();
        fp = (uintptr_t)callerFP();
        sp = (uintptr_t)callerSP();
    } else {
        pc = (const void*)frame.pc();
        fp = frame.fp();
        sp = frame.sp();
    }

    int depth = 0;
    Profiler* profiler = Profiler::instance();
    int actual_max_depth = truncated ? max_depth + 1 : max_depth;

    // Walk until the bottom of the stack or until the first Java frame
    while (depth < actual_max_depth) {
        if (CodeHeap::contains(pc) && !(depth == 0 && frame.unwindAtomicStub(pc)) &&
            VMThread::current() != nullptr) {  // If it is not a JVM thread, it cannot have Java frame
            // Don't dereference pc as it may point to unreadable memory
            // frame.adjustSP(page_start, pc, sp);
            java_ctx->set(pc, sp, fp);
            break;
        }

        callchain[depth++] = pc;

        uintptr_t prev_sp = sp;
        CodeCache* cc = profiler->findLibraryByAddress(pc);
        FrameDesc f = cc != NULL ? cc->findFrameDesc(pc) : FrameDesc::default_frame;

        u8 cfa_reg = (u8)f.cfa;
        int cfa_off = f.cfa >> 8;
        if (cfa_reg == DW_REG_SP) {
            sp = sp + cfa_off;
        } else if (cfa_reg == DW_REG_FP) {
            sp = fp + cfa_off;
        } else if (cfa_reg == DW_REG_PLT) {
            sp += ((uintptr_t)pc & 15) >= 11 ? cfa_off * 2 : cfa_off;
        } else {
            break;
        }

        // Check if the next frame is below on the current stack
        if (sp < prev_sp || sp >= prev_sp + MAX_FRAME_SIZE || sp >= bottom) {
            break;
        }

        // Stack pointer must be word aligned
        if (!aligned(sp)) {
            break;
        }

        const void* prev_pc = pc;
        if (f.fp_off & DW_PC_OFFSET) {
            pc = (const char*)pc + (f.fp_off >> 1);
        } else {
            if (f.fp_off != DW_SAME_FP && f.fp_off < MAX_FRAME_SIZE && f.fp_off > -MAX_FRAME_SIZE) {
                uintptr_t fp_addr = sp + f.fp_off;
                if (!aligned(fp_addr)) {
                    break;
                }
                fp = (uintptr_t)SafeAccess::load((void**)fp_addr);
            }

            if (EMPTY_FRAME_SIZE > 0 || f.pc_off != DW_LINK_REGISTER) {
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

        if (inDeadZone(pc) || (pc == prev_pc && sp == prev_sp)) {
            break;
        }
    }

    if (truncated && depth > max_depth) {
        *truncated = true;
        depth = max_depth;
    }

    return depth;
}

__attribute__((no_sanitize("address"))) int StackWalker::walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                        StackWalkFeatures features, EventType event_type, int lock_index, bool* truncated) {
    if (ucontext == NULL) {
        return walkVM(&empty_ucontext, frames, max_depth, features, event_type,
                      callerPC(), (uintptr_t)callerSP(), (uintptr_t)callerFP(), lock_index, truncated);
    } else {
        StackFrame frame(ucontext);
        return walkVM(ucontext, frames, max_depth, features, event_type,
                      (const void*)frame.pc(), frame.sp(), frame.fp(), lock_index, truncated);
    }
}

__attribute__((no_sanitize("address"))) int StackWalker::walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, VMJavaFrameAnchor* anchor, EventType event_type, int lock_index, bool* truncated) {
    uintptr_t sp = anchor->lastJavaSP();
    if (sp == 0) {
        return 0;
    }

    uintptr_t fp = anchor->lastJavaFP();
    if (fp == 0) {
        fp = sp;
    }

    const void* pc = anchor->lastJavaPC();
    if (pc == NULL || !CodeHeap::contains(pc)) {
        // lastJavaPC is NULL (thread not in Java→native transition) or points outside
        // the tracked CodeHeap range (e.g. interpreter/stub code in a separately mmap'd
        // region). Read the actual return address from the stack frame instead.
        if (!aligned(sp)) {
            return 0;
        }
        pc = ((const void**)sp)[-1];
    }

    StackWalkFeatures no_features{};
    return walkVM(ucontext, frames, max_depth, no_features, event_type, pc, sp, fp, lock_index, truncated);
}

__attribute__((no_sanitize("address"))) int StackWalker::walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                        StackWalkFeatures features, EventType event_type,
                        const void* pc, uintptr_t sp, uintptr_t fp, int lock_index, bool* truncated) {
    StackFrame frame(ucontext);
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

    // Saved anchor data — preserved across anchor consumption so inline
    // recovery can redirect even after the anchor pointer has been set to NULL.
    const void* saved_anchor_pc = NULL;
    uintptr_t saved_anchor_sp = 0;
    uintptr_t saved_anchor_fp = 0;

    // Show extended frame types and stub frames for execution-type events
    bool details = event_type <= MALLOC_SAMPLE || features.mixed;

    if (details && vm_thread != NULL && vm_thread->cachedIsJavaThread()) {
        anchor = vm_thread->anchor();
    }

    unwind_loop:

    // Walk until the bottom of the stack or until the first Java frame
    while (depth < actual_max_depth) {
        if (CodeHeap::contains(pc)) {
            Counters::increment(WALKVM_HIT_CODEHEAP);
            if (fp_chain_fallback) {
                Counters::increment(WALKVM_FP_CHAIN_REACHED_CODEHEAP);
                fp_chain_fallback = false;
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
            VMNMethod* nm = CodeHeap::findNMethod(pc);
            if (nm == NULL) {
                if (anchor == NULL) {
                    // Add an error frame only if we cannot recover
                    fillFrame(frames[depth++], BCI_ERROR, "unknown_nmethod");
                }
                break;
            }

            // Always prefer JavaFrameAnchor when it is available,
            // since it provides reliable SP and FP.
            // Do not treat the topmost stub as Java frame.
            if (anchor != NULL && (depth > 0 || !nm->isStub())) {
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
            }

            if (nm->isNMethod()) {
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
            } else if (nm->isInterpreter()) {
                if (vm_thread != NULL && vm_thread->inDeopt()) {
                    fillFrame(frames[depth++], BCI_ERROR, "break_deopt");
                    break;
                }

                bool is_plausible_interpreter_frame = StackWalkValidation::isPlausibleInterpreterFrame(fp, sp, bcp_offset);
                if (is_plausible_interpreter_frame) {
                    VMMethod* method = ((VMMethod**)fp)[InterpreterFrame::method_offset];
                    jmethodID method_id = getMethodId(method);
                    if (method_id != NULL) {
                        Counters::increment(WALKVM_JAVA_FRAME_OK);
                        const char* bytecode_start = method->bytecode();
                        const char* bcp = ((const char**)fp)[bcp_offset];
                        int bci = bytecode_start == NULL || bcp < bytecode_start ? 0 : bcp - bytecode_start;
                        fillFrame(frames[depth++], FRAME_INTERPRETED, bci, method_id);

                        sp = ((uintptr_t*)fp)[InterpreterFrame::sender_sp_offset];
                        pc = stripPointer(((void**)fp)[FRAME_PC_SLOT]);
                        fp = *(uintptr_t*)fp;
                        continue;
                    }
                }

                if (depth == 0) {
                    VMMethod* method = (VMMethod*)frame.method();
                    jmethodID method_id = getMethodId(method);
                    if (method_id != NULL) {
                        Counters::increment(WALKVM_JAVA_FRAME_OK);
                        fillFrame(frames[depth++], FRAME_INTERPRETED, 0, method_id);

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

                CodeBlob* stub = profiler->findRuntimeStub(pc);
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
            } else if (method_name == NULL && details && profiler->findLibraryByAddress(pc) == NULL) {
                // Try anchor recovery — prefer live anchor, fall back to saved data
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
                if (prev_native_pc != NULL) {
                    Profiler::NativeFrameResolution prev_resolution = profiler->resolveNativeFrameForWalkVM((uintptr_t)prev_native_pc, lock_index);
                    const char* prev_method_name = (const char*)prev_resolution.method_name;
                    if (prev_method_name != NULL) {
                        char prev_mark = NativeFunc::read_mark(prev_method_name);
                        if (prev_mark == MARK_THREAD_ENTRY) {
                            Counters::increment(THREAD_ENTRY_MARK_DETECTIONS);
                            break;
                        }
                    }
                }
                // Fall through to DWARF section — when findLibraryByAddress(pc)
                // returns NULL, default_frame uses FP-chain walking (DW_REG_FP)
                // which can bridge symbol-less gaps in libjvm.so.
                Counters::increment(WALKVM_FP_CHAIN_ATTEMPT);
                fp_chain_fallback = true;
                goto dwarf_unwind;
            }
            fillFrame(frames[depth++], frame_bci, (void*)method_name);
        }

        dwarf_unwind:
        uintptr_t prev_sp = sp;
        CodeCache* cc = profiler->findLibraryByAddress(pc);
        FrameDesc f = cc != NULL ? cc->findFrameDesc(pc) : FrameDesc::default_frame;

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
        if (anchor->getFrame(pc, sp, fp)) {
            if (!CodeHeap::contains(pc) && sp != 0 && aligned(sp) && sp < bottom) {
                pc = ((const void**)sp)[-1];
            }
            Counters::increment(WALKVM_ANCHOR_FALLBACK);
            anchor = NULL;
            while (depth > 0 && frames[depth - 1].method_id == NULL) depth--;
            if (sp != 0 && sp < bottom && aligned(sp)) {
                goto unwind_loop;
            }
        } else {
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

void StackWalker::checkFault(ProfiledThread* thrd) {
    if (VMThread::key() < 0) {
        // JVM has not been loaded or VMStructs have not been initialized yet
        return;
    }

    VMThread* vm_thread = VMThread::current();
    if (vm_thread != NULL && vm_thread->isThreadAccessible() && sameStack(vm_thread->exception(), &vm_thread)) {
        if (thrd) {
            // going to longjmp out of the signal handler, reset the crash handler depth counter
            thrd->resetCrashHandler();
        }
        longjmp(*(jmp_buf*)vm_thread->exception(), 1);
    }
}
