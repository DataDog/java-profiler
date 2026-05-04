/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "jvmSupport.h"

#include "asyncSampleMutex.h"
#include "frames.h"
#include "os.h"
#include "profiler.h"
#include "thread.h"
#include "vmEntry.h"

#include "hotspot/hotspotSupport.h"

#include <jni.h>

int JVMSupport::walkJavaStack(StackWalkRequest& request) {
    if (VM::isHotspot()) {
        return HotspotSupport::walkJavaStack(request);
    } else if (VM::isOpenJ9() || VM::isZing()) {
        assert(request.event_type == BCI_CPU ||
               request.event_type == BCI_WALL ||
               request.event_type == BCI_NATIVE_MALLOC);
        return asyncGetCallTrace(request.frames, request.max_depth, request.ucontext);
    }
    assert(false && "Unsupported JVM");
    return 0;
}

int JVMSupport::asyncGetCallTrace(ASGCT_CallFrame *frames, int max_depth, void* ucontext) {
    JNIEnv *jni = VM::jni();
    if (jni == nullptr) {
        return 0;
    }

    AsyncSampleMutex mutex(ProfiledThread::currentSignalSafe());
    if (!mutex.acquired()) {
        return 0;
    }
  
    JitWriteProtection jit(false);
    // AsyncGetCallTrace writes to ASGCT_CallFrame array
    ASGCT_CallTrace trace = {jni, 0, frames};
    VM::_asyncGetCallTrace(&trace, max_depth, ucontext);
    if (trace.num_frames > 0) {
        return trace.num_frames;
    }

    const char* err_string = Profiler::asgctError(trace.num_frames);
    if (err_string == NULL) {
        // No Java stack, because thread is not in Java context
        return 0;
    }

    Profiler::instance()->incFailure(-trace.num_frames);
    return makeFrame(frames, BCI_ERROR, err_string);
}
