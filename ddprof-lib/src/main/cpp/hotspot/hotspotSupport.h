/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_HOTSPOTSUPPORT_H
#define _HOTSPOT_HOTSPOTSUPPORT_H

#include "hotspot/hotspotStackFrame.h"
#include "hotspot/jitCodeCache.h"
#include "frame.h"
#include "stackFrame.h"
#include "stackWalker.h"

#include <jni.h>
#include <jvmti.h>

class ProfiledThread;
class VMMethod;

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
    
    static int walkJavaStack(StackWalkRequest& request);
    static inline bool canUnwind(const StackFrame& frame, const void*& pc) {
        return HotspotStackFrame::unwindAtomicStub(frame, pc);
    }

    static inline bool isJitCode(const void* p) {
        return JitCodeCache::isJitCode(p);
    }

    static inline long long runtimeStubsMemoryUsage() {
        return JitCodeCache::runtimeStubsMemoryUsage();
    }

    // If should load all jmethodIDs
    static inline bool shouldPreloadJmethodIDs(Arguments& args) {
        CStack cstack = args._cstack;
        return args._force_jmethodID ||
            !(cstack == CSTACK_VM || cstack == CSTACK_DEFAULT); // Can only use Method* when cstack = vm
    }

    // Resolve a method to a jmethodID at dumping time
    static jmethodID resolve(const void* method);

    // Store a Java frame captured from HotSpot metadata. A null jmethodID
    // triggers the raw Method* fallback only when fjmethodid=false; with
    // fjmethodid=true the sentinel is used instead to avoid deferring a
    // raw Method* dereference to the dump thread. The rejected-ID sentinel
    // is always stored as an ordinary frame, resolved to the shared unknown
    // method at dump time.
    static void fillJavaFrame(ASGCT_CallFrame& frame, FrameTypeId type, int bci,
                              jmethodID method_id, const VMMethod* method);
};

#endif // _HOTSPOT_HOTSPOTSUPPORT_H
