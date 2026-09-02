/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _JVMTHREAD_H
#define _JVMTHREAD_H

#include <jni.h>
#include <jvmti.h>

#include "threadLocal.h"
#include "threadLocalData.h"

/**
 * JVMThread represents a native JVM thread that is JVM implementation agnostic
 */
class JVMThread {
private:
    friend class JVMThreadTestAccessor;
    static jfieldID _tid;
    static ThreadLocal<JVMThread*> _jvm_thread;

public:
    /*
     * The initialization happens in early startup, in single-threaded mode,
     * no synchronization is needed
     */
    static bool initialize();

    static inline bool isInitialized() {
        return _tid != nullptr && _jvm_thread.isKeyValid();
    }

    static inline void* current() {
        // If the key is invalid, we should *never* reach here, because
        // profiling should have been disabled. See VM::initShared()d
        assert(_jvm_thread.isKeyValid() && "Should not reach here");
        return _jvm_thread.get();
    }

    static inline pthread_key_t key() {
        return _jvm_thread.key();
    }

    static int nativeThreadId(JNIEnv* jni, jthread thread);
    static inline jlong javaThreadId(JNIEnv* env, jthread thread) {
       return env->GetLongField(thread, _tid);
    }

    static inline bool hasJavaThreadId() {
        return _tid != nullptr;
    }
private:
    static void* currentThreadSlow();
};

// Shared init-window guard used by the CPU/wall profiling signal handlers.
// Guards against the race window between Profiler::registerThread() and
// thread_native_entry setting JVM TLS (PROF-13072): a pure native thread
// (where JVMThread::current() is always null) is allowed through once its
// one-shot init window has ticked down. Returns true if the caller should
// tick-and-return, in which case the tick has already happened. All call
// sites are signal handlers holding an ErrnoPreserver, so no manual errno
// handling is needed on this return path.
static inline bool tickInitWindowIfNeeded(ProfiledThread* current) {
    if (JVMThread::current() == nullptr && current->inInitWindow()) {
        current->tickInitWindow();
        return true;
    }
    return false;
}

#endif // _JVMTHREAD_H
