/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _JVMTHREAD_H
#define _JVMTHREAD_H

#include <cassert>
#include <jni.h>
#include <pthread.h>

#include "hotspot/vmStructs.h"
#include "j9/j9Ext.h"
#include "vmEntry.h"

/**
 * JVMThread represents a native JVM thread that is JVM implementation agnostic
 */
class JVMThread {
private:
    static pthread_key_t _thread_key;
    static jfieldID _tid;
    static jfieldID _eetop;

public:
    static bool is_initialized() {
        return _thread_key != pthread_key_t(-1);
    }

    /*
     * The initialization happens in early startup, in single-threaded mode,
     * no synchronization is needed
     */
    static bool initialize();
    static inline void* current() {
        return pthread_getspecific(_thread_key);
    }

    static inline pthread_key_t key() {
        return _thread_key;
    }

    static int native_thread_id(JNIEnv* jni, jthread thread);

    static inline jlong javaThreadId(JNIEnv* env, jthread thread) {
       return env->GetLongField(thread, _tid);
    }

    static inline bool hasJavaThreadId() {
        return _tid != nullptr;
    }

private:
    static void* current_thread_slow();
};

#endif // _JVMTHREAD_H
