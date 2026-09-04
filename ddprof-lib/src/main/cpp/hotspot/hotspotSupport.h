/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_HOTSPOTSUPPORT_H
#define _HOTSPOT_HOTSPOTSUPPORT_H

#include "guards.h"
#include "hotspot/hotspotStackFrame.h"
#include "hotspot/jitCodeCache.h"
#include "frame.h"
#include "stackFrame.h"
#include "stackWalker.h"
#include "threadLocalData.inline.h"

#include <jni.h>
#include <jvmti.h>

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

    // Runs `work` under the ucontext-fault-recovery protocol walkJavaStack()
    // needs around getJavaTraceAsync(): installs a sigsetjmp/siglongjmp
    // crash-protection scope chained on prof_thread (JmpCtxScope, guards.h),
    // and if a SIGSEGV strikes and is recovered by Profiler::checkFault(),
    // restores ucontext's pc/sp/fp to what they were before `work` ran.
    // getJavaTraceAsync() mutates those registers in place (its pc()/sp()/
    // fp() are references into uc_mcontext) and normally restores them
    // itself, but a fault mid-mutation (e.g. the PROBE_SP retry loop, or
    // inside unwindStub()/unwindCompiled()) skips that restore -- and this
    // ucontext is the exact one the kernel uses to resume the sampled
    // thread when the signal handler returns.
    //
    // `partial_result`, if non-null, is the caller's own accumulator for
    // whatever `work` has already committed to the output buffer (e.g.
    // walkJavaStack's java_frames): getJavaTraceAsync() can fault *after*
    // already returning a valid frame count and filling `frames` (e.g. inside
    // fillFrameTypes()/isCarryingVirtualThread()'s follow-up work), and that
    // partial progress must come back as a truncated-but-valid count rather
    // than being discarded as zero frames.
    //
    // Extracted into one place, rather than hand-rolled separately in
    // walkJavaStack(), so production and its regression test invoke the
    // identical recovery branch -- see hotspot_crash_protection_ut.cpp's
    // WalkJavaStackUcontextRestoreTest. A template rather than
    // std::function<int()> so the hot sample path pays no allocation for
    // captures.
    template <typename Fn>
    static int withUcontextFaultRecovery(void* ucontext, ProfiledThread* prof_thread, bool* truncated, Fn&& work, volatile int* partial_result = nullptr) {
        const bool prev_unwinding_java = prof_thread->is_unwinding_Java();
        StackFrame::RegisterSnapshot ctx_snapshot(ucontext);

        sigjmp_buf crash_protection_ctx;
        JmpCtxScope jmp_scope(prof_thread);

        if (sigsetjmp(crash_protection_ctx, 1) != 0) {
            // checkFault() does a siglongjmp from inside segvHandler, bypassing
            // segvHandler's SignalHandlerScope destructor. Compensate.
            SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
            jmp_scope.restore();
            // A recovered siglongjmp bypasses AsyncSampleMutex destructors, so
            // restore the per-thread guard to its pre-walk value.
            prof_thread->set_unwinding_Java(prev_unwinding_java);
            ctx_snapshot.restore();
            if (truncated) {
                *truncated = true;
            }
            return partial_result ? *partial_result : 0;
        }
        jmp_scope.install(&crash_protection_ctx);
        return work();
    }

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
