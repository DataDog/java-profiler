// Unless explicitly stated otherwise all files in this repository are licensed under the Apache License (Version 2.0).
// This product includes software developed at Datadog (https://www.datadoghq.com/) Copyright 2025 Datadog, Inc.

#ifndef _HOTSPOT_VMSTRUCTS_INLINE_H
#define _HOTSPOT_VMSTRUCTS_INLINE_H

#include "hotspot/vmStructs.h"
#include "jvmThread.h"

VMThread* VMThread::current() {
    return VMThread::cast(JVMThread::current());
}

VMThread* VMThread::fromJavaThread(JNIEnv* env, jthread thread) {
    assert(_eetop != nullptr);
    if (_eetop != nullptr) {
        void* thr = (void*)env->GetLongField(thread, _eetop);
        return VMThread::cast(thr);
    } else {
        return nullptr;
    }
}

int VMThread::nativeThreadId(JNIEnv* jni, jthread thread) {
//    assert(_has_native_thread_id);
    if (_has_native_thread_id) {
        VMThread* vm_thread = fromJavaThread(jni, thread);
        return vm_thread != NULL ? vm_thread->osThreadId() : -1;
    }
    return -1;
}

VMNMethod* VMMethod::code() {
    assert(_method_code_offset >= 0);
    const void* code_ptr = *(const void**) at(_method_code_offset);
    return VMNMethod::cast(code_ptr);
}

VMMethod* VMThread::compiledMethod() {
    if (!cachedIsJavaThread()) return NULL;
    assert(_comp_method_offset >= 0);
    assert(_comp_env_offset >= 0);
    assert(_comp_task_offset >= 0);
    const char* env = *(const char**) at(_comp_env_offset);
    if (env != NULL) {
        const char* task = *(const char**) (env + _comp_task_offset);
        if (task != NULL) {
            return VMMethod::load_then_cast((const void*)(task + _comp_method_offset));
        }
    }
    return NULL;
}

#endif // _HOTSPOT_VMSTRUCTS_INLINE_H
