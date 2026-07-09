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
    friend class HotspotSupportTestAccessor;

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

    static bool loadMethodIDsIfNeededImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass, bool load_all);
public:
    static void initClassloaderInfo(JNIEnv* jni);
    
    static void checkFault(ProfiledThread* thrd = nullptr);
    static int walkJavaStack(StackWalkRequest& request);
    static inline bool canUnwind(const StackFrame& frame, const void*& pc) {
        return HotspotStackFrame::unwindAtomicStub(frame, pc);
    }

    static inline bool isJitCode(const void* p) {
        return JitCodeCache::isJitCode(p);
    }

    // If should load all jmethodIDs
    static inline bool shouldPreloadJmethodIDs(Arguments& args) {
        CStack cstack = args._cstack;
        return args._force_jmethodID ||
            !(cstack == CSTACK_VM || cstack == CSTACK_DEFAULT); // Can only use Method* when cstack = vm
    }

    // Resolve a method to a jmethodID at dumping time
    static jmethodID resolve(const void* method);
};

#endif // _HOTSPOT_HOTSPOTSUPPORT_H
