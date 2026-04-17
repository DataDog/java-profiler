/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_VMSTRUCTS_INLINE_H
#define _HOTSPOT_VMSTRUCTS_INLINE_H

#include "hotspot/vmStructs.h"
#include "jvmThread.h"

#include <cassert>

VMThread* VMThread::current() {
    return VMThread::cast(JVMThread::current());
}

VMThread* VMThread::fromJavaThread(JNIEnv* env, jthread thread) {
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

bool VMClassLoaderData::isAnonymous() const {
    if (_class_loader_data_is_anonymous_offset >= 0) {
        return *(bool*) at(_class_loader_data_is_anonymous_offset);
    }
    return false;    
}

bool VMClassLoaderData::hasClassMirrorHolder() const {
    if (_class_loader_data_has_class_mirror_holder_offset >= 0) {             
        return  *(bool*) at(_class_loader_data_has_class_mirror_holder_offset);
    }
    return false;
}

VMKlass* VMConstantPool::holder() const {
    assert(_pool_holder_offset >= 0);
    return VMKlass::cast(at(_pool_holder_offset));
}

VMSymbol* VMConstantPool::symbolAt(int index) const {
    return VMSymbol::cast(&base()[index]);
}

intptr_t* VMConstantPool::base() const {
    assert(_VMConstantPool_size > 0);
    return (intptr_t*)(((char*)this) + _VMConstantPool_size);
}

uint16_t VMMethod::codeSize() const {
    assert(_constmethod_code_size >= 0);
    address code_size_addr =  *(unsigned char**)at(_method_constmethod_offset) + _constmethod_code_size;
    uint16_t code_size = *(uint16_t*)code_size_addr;
    TEST_LOG("VMMethod::codeSize(): code_size=%u\n", code_size);
    return code_size;
}

uint32_t VMMethod::flags() const {
    assert(_constmethod_flags_offset >= 0);
    return *(uint32_t*) ( *(const char**) at(_method_constmethod_offset) + _constmethod_flags_offset );
}

bool VMMethod::hasLineNumberTable() const {
    return (flags() & has_linenumber_table) != 0;
}

address VMMethod::codeBase() const {
    assert(_method_constmethod_offset >= 0);
    const char* const_method = (const char*) SafeAccess::load((void**) at(_method_constmethod_offset));
    return (address)(const_method+1);
}

VMConstantPool* VMMethod::constantPool() const {
    assert(_method_constmethod_offset >= 0);
    const char* const_method = (const char*) SafeAccess::load((void**) at(_method_constmethod_offset));
    assert(goodPtr(const_method));
    assert(_constmethod_constants_offset >= 0);
    VMConstantPool* cpool = *(VMConstantPool**) (const_method + _constmethod_constants_offset);
    return cpool;
}

VMSymbol* VMMethod::name() const {
    VMConstantPool* cpool = constantPool();
    assert(_method_constmethod_offset >= 0);
    const char* const_method = (const char*) SafeAccess::load((void**) at(_method_constmethod_offset));
    assert(goodPtr(const_method));
    assert(_constmethod_name_index_offset >= 0);
    int name_index = *(uint16_t*) (const_method + _constmethod_name_index_offset);
    return cpool->symbolAt(name_index);

}

VMSymbol* VMMethod::signature() const {
    VMConstantPool* cpool = constantPool();
    assert(_method_constmethod_offset >= 0);
    const char* const_method = (const char*) SafeAccess::load((void**) at(_method_constmethod_offset));
    assert(goodPtr(const_method));
    assert(_constmethod_sig_index_offset >= 0);
    int signature_index = *(uint16_t*) (const_method + _constmethod_sig_index_offset);
    return cpool->symbolAt(signature_index);
}

VMNMethod* VMMethod::code() const {
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

uintptr_t VMOopHandle::oop() const {
    assert(_oop_handle_obj_offset >= 0);
    return *(uintptr_t*) at(_oop_handle_obj_offset);
}

#endif // _HOTSPOT_VMSTRUCTS_INLINE_H
