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
    const uintptr_t SAME_STACK_DISTANCE = 8192;

    // Check if pointer is in dead zone (very low or very high address)
    static inline bool inDeadZone(const void* ptr) {
        return ptr < (const void*)DEAD_ZONE || ptr > (const void*)-DEAD_ZONE;
    }

    // Check if pointer is properly aligned
    static inline bool aligned(uintptr_t ptr) {
        return (ptr & (sizeof(uintptr_t) - 1)) == 0;
    }

    // Check if two pointers are on the same stack
    static inline bool sameStack(void* hi, void* lo) {
        return (uintptr_t)hi - (uintptr_t)lo < SAME_STACK_DISTANCE;
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
        if (depth > 0 && frames[0].method_id == JMETHODID_NOT_WALKABLE) {
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
    static int walkFP(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated = nullptr);
    static int walkDwarf(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated = nullptr);
};

#endif // _STACKWALKER_H
