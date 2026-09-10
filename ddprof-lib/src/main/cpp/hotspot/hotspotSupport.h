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

    // ctx_snapshot is owned by the caller's withUcontextFaultRecovery() scope
    // (hotspotSupport.cpp), not constructed locally: getJavaTraceAsync() must
    // record the JavaThread anchor mutation it's about to make (see
    // saveJavaAnchor() below) on the exact same RegisterSnapshot instance
    // whose restore() runs on a recovered SIGSEGV, or the anchor never gets
    // restored -- a fault siglongjmps past this whole function's frame,
    // skipping any local snapshot it might otherwise have owned.
    static int getJavaTraceAsync(void *ucontext, ASGCT_CallFrame *frames,
                                 int max_depth, StackContext *java_ctx,
                                 bool *truncated, HotspotStackFrame::RegisterSnapshot& ctx_snapshot);

    static bool loadMethodIDsIfNeededImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass, bool load_all);

    // Runs getJavaTraceAsync() under withUcontextFaultRecovery(), then layers
    // on its two post-processing steps: resolving frame types for the top
    // Java frame via fillFrameTypes(), and appending a synthetic "JVM
    // Continuation" frame when the sampled thread is carrying a virtual
    // thread. Shared by both of walkJavaStack()'s dispatch arms that reach
    // getJavaTraceAsync() -- previously duplicated verbatim in each.
    static int asyncJavaTraceWithPostProcessing(void* ucontext, ASGCT_CallFrame* frames,
                                                int max_depth, StackContext* java_ctx,
                                                bool* truncated, ProfiledThread* prof_thread);
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
    // `partial_result` is the caller's own accumulator for whatever `work`
    // has already committed to the output buffer (e.g. walkJavaStack's
    // java_frames): getJavaTraceAsync() can fault *after* already returning a
    // valid frame count and filling `frames` (e.g. inside
    // fillFrameTypes()/isCarryingVirtualThread()'s follow-up work). `work` is
    // void-returning and writes only into `partial_result` (by capturing it,
    // not by a return value) -- the wrapper reads `partial_result` back on
    // both the normal-completion path and the recovery path, so there is a
    // single channel for the result rather than two that a caller could wire
    // to different objects, or forget to wire at all (a plain return value
    // whose default became 0 on a recovered fault was exactly the
    // "recovered fault discards an already-valid partial trace" shape this
    // wrapper exists to avoid). The caller must initialize `partial_result`
    // itself before the call (normally to 0); before this recovery logic was
    // extracted into a shared helper, walkJavaStack() already reported the
    // fault-after-partial-progress case as a truncated-but-valid count by
    // reading back its own `volatile int java_frames` local from the recovery
    // branch -- this parameter is how that pre-existing behavior is preserved
    // now that the branch lives here instead, not a new fix on top of it.
    //
    // `work` receives ctx_snapshot by reference so that getJavaTraceAsync()
    // (via its own saveJavaAnchor() call, above) can record a JavaThread
    // anchor mutation on this exact instance -- the one whose restore()
    // actually runs below on a recovered fault. A local snapshot inside
    // getJavaTraceAsync() would be useless: a siglongjmp from a fault there
    // jumps straight back to this sigsetjmp, skipping getJavaTraceAsync's
    // entire stack frame (and anything it owned) without running any of its
    // code.
    //
    // Extracted into one place, rather than hand-rolled separately in
    // walkJavaStack(), so production and its regression test invoke the
    // identical recovery branch -- see hotspot_crash_protection_ut.cpp's
    // WalkJavaStackUcontextRestoreTest. A template rather than
    // std::function<void()> so the hot sample path pays no allocation for
    // captures. Must stay defined here (not in hotspotSupport.cpp): as a
    // template, its body needs to be visible wherever it's instantiated --
    // both walkJavaStack() and the regression test's own call sites, which
    // each pass a distinct closure type.
    template <typename Fn>
    static int withUcontextFaultRecovery(void* ucontext, ProfiledThread* prof_thread, bool* truncated, volatile int& partial_result, Fn&& work) {
        const bool prev_unwinding_java = prof_thread->is_unwinding_Java();
        HotspotStackFrame::RegisterSnapshot ctx_snapshot(ucontext);

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
            return partial_result;
        }
        jmp_scope.install(&crash_protection_ctx);
        work(ctx_snapshot);
        return partial_result;
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
