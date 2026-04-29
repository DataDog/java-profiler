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
    return VMKlass::load_then_cast(at(_pool_holder_offset));
}

VMSymbol* VMConstantPool::symbolAt(u16 index) const {
    return VMSymbol::cast(*(void**)&base()[index]);
}

intptr_t* VMConstantPool::base() const {
    assert(_VMConstantPool_size > 0);
    return (intptr_t*)(((char*)this) + _VMConstantPool_size);
}

VMConstMethod* VMMethod::constMethod() const {
    return VMConstMethod::load_then_cast(at(_method_constmethod_offset));
}

VMNMethod* VMMethod::code() const {
    assert(_method_code_offset >= 0);
    const void* code_ptr = *(const void**) at(_method_code_offset);
    return VMNMethod::cast(code_ptr);
}

VMKlass* VMMethod::methodHolder() const {
//    return constMethod()->constants()->holder();
    VMConstMethod* constMthd = constMethod();
    VMConstantPool* pool = constMthd->constants();
    VMKlass* holder = pool->holder();
    return holder;
}

VMConstantPool* VMConstMethod::constants() const {
    return VMConstantPool::load_then_cast(at(_constmethod_constants_offset));
}

uint16_t VMConstMethod::codeSize() const {
    assert(_constmethod_code_size >= 0);
    uint16_t code_size = *(uint16_t*)at(_constmethod_code_size);
    return code_size;
}

const char* VMConstMethod::base() const {
    return (const char*)this + _VMConstMethod_size;
}

u16 VMConstMethod::nameIndex() const {
    assert(_constmethod_name_index_offset >= 0 && "Invalid name index");
    return *(u16*)at(_constmethod_name_index_offset);
}

u16 VMConstMethod::signatureIndex() const {
    assert(_constmethod_sig_index_offset >= 0 && "Invalid signature index");
    return *(u16*)at(_constmethod_sig_index_offset);
}

VMSymbol* VMConstMethod::name() const {
    VMConstantPool* cpool = constants();
    u16 name_index = nameIndex();
    return cpool->symbolAt(name_index);
}

VMSymbol* VMConstMethod::signature() const {
    VMConstantPool* cpool = constants();
    u16 sig_index = signatureIndex();
    return cpool->symbolAt(sig_index);
}

VMKlass* VMClasses::obj_klass() {
    return VMKlass::load_then_cast(_obj_class_addr);
}

#endif // _HOTSPOT_VMSTRUCTS_INLINE_H
