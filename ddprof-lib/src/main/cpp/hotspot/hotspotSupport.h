/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_HOTSPOTSUPPORT_H
#define _HOTSPOT_HOTSPOTSUPPORT_H

#include "hotspot/hotspotStackFrame.h"
#include "hotspot/jitCodeCache.h"
#include "stackFrame.h"
#include "stackWalker.h"

#include <jni.h>
#include <jvmti.h>

class ProfiledThread;

class HotspotSupport {
    friend class JVMSupport;

private:
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth,
                      StackWalkFeatures features, EventType event_type,
                      const void* pc, uintptr_t sp, uintptr_t fp, int lock_index, bool* truncated);
    static int walkVM(void* ucontext, ASGCT_CallFrame* frames, int max_depth, 
                      StackWalkFeatures features, EventType event_type,
                      int lock_index, bool* truncated = nullptr);

    static int getJavaTraceAsync(void *ucontext, ASGCT_CallFrame *frames,
                                 int max_depth, StackContext *java_ctx,
                                 bool *truncated);

    static bool loadMethodIDsImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass);
public:
    static void checkFault(ProfiledThread* thrd = nullptr);
    static int walkJavaStack(StackWalkRequest& request);

    static inline bool canUnwind(const StackFrame& frame, const void*& pc) {
        return HotspotStackFrame::unwindAtomicStub(frame, pc);
    }

    static inline bool isJitCode(const void* p) {
        return JitCodeCache::isJitCode(p);
    }

    static jmethodID resolve(const void* method);

    static void JNICALL NativeMethodBind(jvmtiEnv *jvmti, JNIEnv *jni,
                                         jthread thread, jmethodID method,
                                         void *address, void **new_address_ptr);
};

#endif // _HOTSPOT_HOTSPOTSUPPORT_H
