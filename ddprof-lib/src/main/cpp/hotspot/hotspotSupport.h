/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_HOTSPOTSUPPORT_H
#define _HOTSPOT_HOTSPOTSUPPORT_H

#include <setjmp.h>

#include "hotspot/hotspotStackFrame.h"
#include "hotspot/jitCodeCache.h"
#include "stackFrame.h"
#include "stackWalker.h"

class ProfiledThread;

class HotspotSupport {
private:
    static ThreadLocal<jmp_buf*> _jmp_ctx;

    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                      StackWalkFeatures features, EventType event_type,
                      const void* pc, uintptr_t sp, uintptr_t fp, int lock_index, bool* truncated);
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, 
                      StackWalkFeatures features, EventType event_type,
                      int lock_index, bool* truncated = nullptr);

    static int getJavaTraceAsync(void *ucontext, ASGCT_CallFrame *frames,
                                 int max_depth, StackContext *java_ctx,
                                 bool *truncated);

public:
    static void checkFault(ProfiledThread* thrd = nullptr);
    static int walkJavaStack(StackWalkRequest& request);
    static inline bool canUnwind(const StackFrame& frame, const void*& pc) {
        return HotspotStackFrame::unwindAtomicStub(frame, pc);
    }

    // Per-thread initialization.
    // *Must* be called before signal is enabled for the thread
    static void initThread();

    static bool isInitialized() {
        return _jmp_ctx.isKeyValid();
    }

    static bool isThreadProtectedByLongjmp() {
        return _jmp_ctx.get() != nullptr;
    }

    static inline bool isJitCode(const void* p) {
        return JitCodeCache::isJitCode(p);
    }
};

#endif // _HOTSPOT_HOTSPOTSUPPORT_H
