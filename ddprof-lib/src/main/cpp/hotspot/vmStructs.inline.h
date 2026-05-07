/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_VMSTRUCTS_INLINE_H
#define _HOTSPOT_VMSTRUCTS_INLINE_H

#include "hotspot/vmStructs.h"
#include "jvmThread.h"
#include "vmEntry.h"

VMThread* VMThread::current() {
    // JVMThread::current() is the native thread self pointer. On OpenJ9/Zing it
    // is not a HotSpot JavaThread*; only HotSpot may reinterpret it as VMThread*.
    if (!VM::isHotspot() || JVMThread::current() == nullptr) {
        return nullptr;
    }
    return VMThread::cast(JVMThread::current());
}

VMThread* VMThread::fromJavaThread(JNIEnv* env, jthread thread) {
    if (!VM::isHotspot()) {
        return nullptr;
    }
    assert(_eetop != nullptr);
    if (_eetop != nullptr) {
        return VMThread::cast((void*)env->GetLongField(thread, _eetop));
    } else {
        return nullptr;
    }
}

int VMThread::nativeThreadId(JNIEnv* jni, jthread thread) {
    if (_has_native_thread_id) {
        VMThread* vm_thread = fromJavaThread(jni, thread);
        return vm_thread != NULL ? vm_thread->osThreadId() : -1;
    }
    return -1;
}

void** VMThread::vtable() {
    assert(SafeAccess::isReadable(this));
    return *(void***)this;
}

// This thread is considered a JavaThread if at least 2 of the selected 3 vtable entries
// match those of a known JavaThread (which is either application thread or AttachListener).
// Indexes were carefully chosen to work on OpenJDK 8 to 25, both product an debug builds.
bool VMThread::hasJavaThreadVtable() {
    void** vtbl = vtable();
    return (SafeAccess::load(&vtbl[1]) == _java_thread_vtbl[1]) +
           (SafeAccess::load(&vtbl[3]) == _java_thread_vtbl[3]) +
           (SafeAccess::load(&vtbl[5]) == _java_thread_vtbl[5]) >= 2;
}

VMNMethod* VMMethod::code() {
    assert(_method_code_offset >= 0);
    const void* code_ptr = *(const void**) at(_method_code_offset);
    return VMNMethod::cast(code_ptr);
}

VMMethod* VMThread::compiledMethod() {
    if (!isJavaThread(this)) return NULL;
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
