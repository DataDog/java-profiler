/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_HOTSPOTSUPPORT_H
#define _HOTSPOT_HOTSPOTSUPPORT_H

#include "stackWalker.h"

class ProfiledThread;

class HotspotSupport {
private:
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                      StackWalkFeatures features, EventType event_type,
                      const void* pc, uintptr_t sp, uintptr_t fp, int lock_index, bool* truncated);
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, 
                      StackWalkFeatures features, EventType event_type,
                      int lock_index, bool* truncated = nullptr);
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                      VMJavaFrameAnchor* anchor, EventType event_type,
                      int lock_index, bool* truncated = nullptr);

    static int getJavaTraceAsync(void *ucontext, ASGCT_CallFrame *frames,
                                 int max_depth, StackContext *java_ctx,
                                 bool *truncated);

public:
    static void checkFault(ProfiledThread* thrd = nullptr);
    static int walkJavaStack(StackWalkRequest& request);
};

#endif // _HOTSPOT_HOTSPOTSUPPORT_H
