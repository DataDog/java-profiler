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

void JVMSupport::loadAllMethodIDs(jvmtiEnv *jvmti, JNIEnv *jni) {
    jint class_count = 0;
    jclass *classes = nullptr;
    int loaded_count = 0;

    if ((!VM::isHotspot() || HotspotSupport::needJMethodIDs()) &&
        jvmti->GetLoadedClasses(&class_count, &classes) == JVMTI_ERROR_NONE) {
        for (int i = 0; i < class_count; i++) {
            if(loadMethodIDs(jvmti, jni, classes[i])) {
                loaded_count++;
            }
        }
        jvmti->Deallocate((unsigned char *)classes);
    }
    TEST_LOG("Preloaded jmethodIDs for %d/%d classes", loaded_count, class_count);
}

bool JVMSupport::loadMethodIDs(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass) {
    if (!VM::isHotspot() || HotspotSupport::needJMethodIDs()) {
        return loadMethodIDsImpl(jvmti, jni, klass);
    }
    return false;
}

bool JVMSupport::loadMethodIDsImpl(jvmtiEnv *jvmti, JNIEnv *jni, jclass klass) {
  bool needs_patch = VM::isHotspot() && VM::hotspot_version() == 8;
  if (needs_patch) {
    // Workaround for JVM bug https://bugs.openjdk.org/browse/JDK-8062116
    // Preallocate space for jmethodIDs at the beginning of the list (rather than at the end)
    // This is relevant only for JDK 8 - later versions do not have this bug
    if (VMStructs::hasClassLoaderData()) {
      VMKlass *vmklass = VMKlass::fromJavaClass(jni, klass);
      int method_count = vmklass->methodCount();
      if (method_count > 0) {
        VMClassLoaderData *cld = vmklass->classLoaderData();
        cld->lock();
        for (int i = 0; i < method_count; i += MethodList::SIZE) {
          *cld->methodList() = new MethodList(*cld->methodList());
        }
        cld->unlock();
      }
    }
  }
 
  // CRITICAL: GetClassMethods must be called to preallocate jmethodIDs for AsyncGetCallTrace.
  // AGCT operates in signal handlers where lock acquisition is forbidden, so jmethodIDs must
  // exist before profiling encounters them. Without preallocation, AGCT cannot identify methods
  // in stack traces, breaking profiling functionality.
  //
  // JVM-internal allocation: This triggers JVM to allocate jmethodIDs internally, which persist
  // until class unload. High class churn causes significant memory growth, but this is inherent
  // to AGCT architecture and necessary for signal-safe profiling.
  //
  // See: https://mostlynerdless.de/blog/2023/07/17/jmethodids-in-profiling-a-tale-of-nightmares/
  jint method_count;
  jmethodID *methods;
  if (jvmti->GetClassMethods(klass, &method_count, &methods) == JVMTI_ERROR_NONE) {
    jvmti->Deallocate((unsigned char *)methods);
    return true;
  }
  return false;
}
