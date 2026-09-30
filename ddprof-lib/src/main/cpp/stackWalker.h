/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STACKWALKER_H
#define _STACKWALKER_H

#include <stdint.h>
#include <string.h>
#include "arguments.h"
#include "event.h"
#include "vmEntry.h"


class VMJavaFrameAnchor;
class ProfiledThread;

struct StackContext {
    const void* pc;
    uintptr_t sp;
    uintptr_t fp;
    u64 cpu;

    void set(const void* pc, uintptr_t sp, uintptr_t fp) {
        this->pc = pc;
        this->sp = sp;
        this->fp = fp;
    }
};

// Stack walking validation helpers (used by implementation and tests)
namespace StackWalkValidation {
    const intptr_t MAX_INTERPRETER_FRAME_SIZE = 0x1000;
    const uintptr_t DEAD_ZONE = 0x1000;
    const intptr_t MAX_FRAME_SIZE = 0x40000;

    // Check if pointer is in dead zone (very low or very high address)
    static inline bool inDeadZone(const void* ptr) {
        return ptr < (const void*)DEAD_ZONE || ptr > (const void*)-DEAD_ZONE;
    }

    // Check if pointer is properly aligned
    static inline bool aligned(uintptr_t ptr) {
        return (ptr & (sizeof(uintptr_t) - 1)) == 0;
    }

    // Check if a frame pointer is plausibly valid (not in dead zone, properly aligned)
    static inline bool isValidFP(uintptr_t fp) {
        return !inDeadZone((const void*)fp) && aligned(fp);
    }

    // Check if a stack pointer is within [lo, hi) and properly aligned
    static inline bool isValidSP(uintptr_t sp, uintptr_t lo, uintptr_t hi) {
        return sp > lo && sp < hi && aligned(sp);
    }

    // Drop unknown leaf frame (method_id == NULL at index 0).
    // Returns the new depth after removal.
    static inline int dropUnknownLeaf(ASGCT_CallFrame* frames, int depth) {
        if (depth > 0 && frames[0].method_id == NULL) {
            depth--;
            if (depth > 0) {
                memmove(frames, frames + 1, depth * sizeof(frames[0]));
            }
        }
        return depth;
    }

    static inline bool isPlausibleInterpreterFrame(uintptr_t fp, uintptr_t sp, int bcp_offset){
        return fp != 0 && aligned(fp) && !inDeadZone((const void*)fp)
                && sp != 0 && sp > fp - MAX_INTERPRETER_FRAME_SIZE
                && sp < fp + bcp_offset * (intptr_t)sizeof(void*);
    }
}

typedef struct {
    jint event_type;
    u32 lock_index;
    void* ucontext;
    ASGCT_CallFrame* frames;
    int max_depth;
    StackContext* java_ctx;
    bool* truncated;
} StackWalkRequest;

class StackWalker {
  public:
    // callchain[] must have room for max_depth + 1 entries whenever
    // `truncated` is non-null. Both walkers deliberately walk one frame past
    // max_depth to learn whether the stack really continued, write that frame,
    // and only then clamp the returned depth back to max_depth -- a buffer of
    // exactly max_depth is overflowed by one entry on any stack deep enough to
    // reach the limit. Without a truncation flag, max_depth entries suffice.
    //
    // ADDRESSING CONVENTION -- one rule, every walker, in-process and on the
    // wire.
    //
    // A recorded frame address is an *attribution* address: pc - 1 wherever
    // the pc came out of a return-address slot, the exact pc otherwise (see
    // attributionPC in stackWalker.inline.h). It names the instruction that
    // transferred control, not the one execution would resume at, so a call
    // that is the last instruction of its caller still resolves to the caller.
    //
    // This holds for walkFP, walkDwarf, walkVM and walkKernel alike. LBR
    // entries are the one thing left unadjusted, and are not an exception to
    // the rule: branch endpoints already name the instruction to symbolize.
    //
    // StackContext::pc is deliberately *not* adjusted -- it is a resume point
    // handed to the JVM, not something to symbolize.
    //
    // It reaches the wire unchanged: the remote-symbolication pc_offset is
    // this address minus the image base, whether it is packed by
    // populateRemoteFrame or by resolveNativeFrameForWalkVM. An off-process
    // symbolizer must therefore NOT apply its own return-address adjustment;
    // doing so would step off the front of the call instruction. The packed
    // field carries no version bit, so this comment and
    // doc/reference/RemoteSymbolication.md are the contract.
    static int walkFP(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated = nullptr);
    static int walkDwarf(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated = nullptr);
};

#endif // _STACKWALKER_H
