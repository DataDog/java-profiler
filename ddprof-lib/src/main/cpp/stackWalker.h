/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STACKWALKER_H
#define _STACKWALKER_H

#include <stdint.h>
#include "arguments.h"
#include "event.h"
#include "vmEntry.h"


class JavaFrameAnchor;
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
}

class StackWalker {
  private:
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                      StackWalkFeatures features, EventType event_type,
                      const void* pc, uintptr_t sp, uintptr_t fp, int lock_index, bool* truncated);

  public:
    static int walkFP(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated = nullptr);
    static int walkDwarf(void* ucontext, const void** callchain, int max_depth, StackContext* java_ctx, bool* truncated = nullptr);
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, StackWalkFeatures features, EventType event_type, int lock_index, bool* truncated = nullptr);
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, JavaFrameAnchor* anchor, EventType event_type, int lock_index, bool* truncated = nullptr);

    static void checkFault(ProfiledThread* thrd = nullptr);
};

#endif // _STACKWALKER_H
