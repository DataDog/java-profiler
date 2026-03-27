/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _JVMTHREAD_H
#define _JVMTHREAD_H

#include <cassert>
#include <jni.h>
#include <jvmti.h>
#include <pthread.h>

/**
 * JVMThread represents a native JVM thread that is JVM implementation agnostic
 */
class JVMThread {
private:
    static pthread_key_t _thread_key;
    static jmethodID _tid;

public:
    static bool isInitialized() {
        return _thread_key != pthread_key_t(-1);
    }

    /*
     * The initialization happens in early startup, in single-threaded mode,
     * no synchronization is needed
     */
    static bool initialize();
    static inline void* current() {
        assert(isInitialized());
        return pthread_getspecific(_thread_key);
    }

    static inline pthread_key_t key() {
        return _thread_key;
    }

    static int nativeThreadId(JNIEnv* jni, jthread thread);

    static inline jlong javaThreadId(JNIEnv* env, jthread thread) {
       return env->CallLongMethod(thread, _tid);
    }

    static inline bool hasJavaThreadId() {
        return _tid != nullptr;
    }

private:
    static void* currentThreadSlow();
};

#endif // _JVMTHREAD_H
