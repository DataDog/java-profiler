/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _JVMTHREAD_H
#define _JVMTHREAD_H

#include <jni.h>
#include <jvmti.h>

#include "threadLocal.h"

/**
 * JVMThread represents a native JVM thread that is JVM implementation agnostic
 */
class JVMThread {
private:
    static jfieldID _tid;
    static ThreadLocal<JVMThread*> _jvm_thread;

public:
    /*
     * The initialization happens in early startup, in single-threaded mode,
     * no synchronization is needed
    */
    static bool initialize();

    // Whether nativeThreadId can resolve a Java thread other than the caller.
    static bool supportsNativeThreadIdLookup();

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

#endif // _JVMTHREAD_H
