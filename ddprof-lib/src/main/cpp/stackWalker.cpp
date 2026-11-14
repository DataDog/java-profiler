/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include <setjmp.h>
#include "dwarfStep.inline.h"
#include "stackWalker.inline.h"
#include "dwarf.h"
#include "faultInjection.h"
#include "guards.h"
#include "profiler.h"
#include "stackFrame.h"
#include "symbols.h"
#include "jvmSupport.inline.h"
#include "jvmThread.h"
#include "threadLocalData.inline.h"

// Use validation helpers from header (shared with tests)
using StackWalkValidation::inDeadZone;
using StackWalkValidation::aligned;
using StackWalkValidation::MAX_FRAME_SIZE;


int StackWalker::walkFP(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated) {
    uintptr_t fp;
    uintptr_t sp;
    uintptr_t bottom = (uintptr_t)&sp + MAX_WALK_SIZE;

    StackFrame frame(ucontext);
    WalkPc walk_pc;
    if (ucontext == NULL) {
        // stripPointer() for the same reason the recovery paths below need it:
        // where callerPC() is a real return address it carries the platform's
        // pointer tagging (PAC bits on aarch64, the Thumb interworking bit on
        // arm).
        walk_pc.setSeed(stripPointer(callerPC()), CALLER_PC_IS_RETURN_ADDRESS);
        fp = (uintptr_t)callerFP();
        sp = (uintptr_t)callerSP();
    } else {
        walk_pc.setExactAddress((const void*)frame.pc());
        fp = frame.fp();
        sp = frame.sp();
    }

    volatile int depth = 0;
    int actual_max_depth = truncated ? max_depth + 1 : max_depth;

    // Mirrors HotspotSupport::walkVM's crash protection: a SIGSEGV whose PC
    // falls inside this library while a jmp ctx is installed gets caught by
    // Profiler::checkFault() from the SEGV handler and siglongjmp'd back here,
    // instead of crashing the process.
    ProfiledThread* prof_thread = ProfiledThread::acquireCurrent();
    if (prof_thread == nullptr) {
        Counters::increment(SAMPLES_DROPPED_THREAD_LOCAL);
        return 0;
    }

    sigjmp_buf crash_protection_ctx;
    JmpCtxScope jmp_scope(prof_thread);

    if (sigsetjmp(crash_protection_ctx, 1) != 0) {
        // checkFault() does a siglongjmp from inside segvHandler, bypassing
        // segvHandler's SignalHandlerScope destructor. Compensate.
        SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
        jmp_scope.restore();
        if (truncated) {
            *truncated = true;
            if (depth > max_depth) {
                depth = max_depth;
            }
        }
        return depth;
    }
    jmp_scope.install(&crash_protection_ctx);

    // Walk until the bottom of the stack or until the first Java frame
    while (depth < actual_max_depth) {
        if (JVMSupport::isJitCode(walk_pc.raw())) {
            const void* unwound_pc = walk_pc.raw();
            if (depth == 0 && JVMSupport::canUnwind(frame, unwound_pc)) {
                // unwindAtomicStub rewrites the pc to the link register, i.e.
                // to a genuine return address, so the flag travels with it.
                walk_pc.setReturnAddress(unwound_pc);
            } else if (JVMThread::current() != nullptr) {  // If it is not a JVM thread, it cannot have Java frame
                java_ctx->set(walk_pc.raw(), sp, fp);
                break;
            }
        }

        callchain[depth++] = walk_pc.attribution();

        // Check if the next frame is below on the current stack
        if (fp < sp || fp >= sp + MAX_FRAME_SIZE || fp >= bottom) {
            break;
        }

        // Frame pointer must be word aligned
        if (!aligned(fp)) {
            break;
        }

        // Unconditionally a return address here: the frame-pointer walk has no
        // DWARF row, so it cannot see a signal-frame CIE the way walkDwarf can.
        walk_pc.setReturnAddress(
            stripPointer(SafeAccess::load(INJECT_FAULT_ADDRESS_LIKELY((void**)fp + FRAME_PC_SLOT))));
        if (inDeadZone(walk_pc.raw())) {
            break;
        }

        sp = fp + (FRAME_PC_SLOT + 1) * sizeof(void*);
        fp = (uintptr_t)SafeAccess::load(INJECT_FAULT_ADDRESS_LIKELY((void**)fp));
    }

    if (truncated && depth > max_depth) {
        *truncated = true;
        depth = max_depth;
    }

    return depth;
}

int StackWalker::walkDwarf(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated) {
    uintptr_t fp;
    uintptr_t sp;
    uintptr_t bottom = (uintptr_t)&sp + MAX_WALK_SIZE;

    StackFrame frame(ucontext);
    WalkPc walk_pc;
    if (ucontext == NULL) {
        // stripPointer() for the same reason the recovery paths below need it:
        // where callerPC() is a real return address it carries the platform's
        // pointer tagging (PAC bits on aarch64, the Thumb interworking bit on
        // arm).
        walk_pc.setSeed(stripPointer(callerPC()), CALLER_PC_IS_RETURN_ADDRESS);
        fp = (uintptr_t)callerFP();
        sp = (uintptr_t)callerSP();
    } else {
        walk_pc.setExactAddress((const void*)frame.pc());
        fp = frame.fp();
        sp = frame.sp();
    }

    volatile int depth = 0;
    Profiler* profiler = Profiler::instance();
    int actual_max_depth = truncated ? max_depth + 1 : max_depth;

    // Mirrors HotspotSupport::walkVM's crash protection: a SIGSEGV whose PC
    // falls inside this library while a jmp ctx is installed gets caught by
    // Profiler::checkFault() from the SEGV handler and siglongjmp'd back here,
    // instead of crashing the process.
    ProfiledThread* prof_thread = ProfiledThread::acquireCurrent();
    if (prof_thread == nullptr) {
        Counters::increment(SAMPLES_DROPPED_THREAD_LOCAL);
        return 0;
    }

    sigjmp_buf crash_protection_ctx;
    JmpCtxScope jmp_scope(prof_thread);

    if (sigsetjmp(crash_protection_ctx, 1) != 0) {
        // checkFault() does a siglongjmp from inside segvHandler, bypassing
        // segvHandler's SignalHandlerScope destructor. Compensate.
        SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
        jmp_scope.restore();
        if (truncated) {
            *truncated = true;
            if (depth > max_depth) {
                depth = max_depth;
            }
        }
        return depth;
    }
    jmp_scope.install(&crash_protection_ctx);

    // Walk until the bottom of the stack or until the first Java frame
    while (depth < actual_max_depth) {
        if (JVMSupport::isJitCode(walk_pc.raw())) {
            const void* unwound_pc = walk_pc.raw();
            if (depth == 0 && JVMSupport::canUnwind(frame, unwound_pc)) {
                // unwindAtomicStub rewrites the pc to the link register, i.e.
                // to a genuine return address, so the flag travels with it.
                walk_pc.setReturnAddress(unwound_pc);
            } else if (JVMThread::current() != nullptr) {  // If it is not a JVM thread, it cannot have Java frame
                // Don't dereference pc as it may point to unreadable memory
                // frame.adjustSP(page_start, pc, sp);
                java_ctx->set(walk_pc.raw(), sp, fp);
                break;
            }
        }

        const void* attribution_pc = walk_pc.attribution();
        callchain[depth++] = attribution_pc;

        if (!advanceDwarfFrame(walk_pc, sp, fp, bottom, depth, frame,
                               profiler)) {
            break;
        }
    }

    if (truncated && depth > max_depth) {
        *truncated = true;
        depth = max_depth;
    }

    return depth;
}
