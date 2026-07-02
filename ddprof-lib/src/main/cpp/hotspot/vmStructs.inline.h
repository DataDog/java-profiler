/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_VMSTRUCTS_INLINE_H
#define _HOTSPOT_VMSTRUCTS_INLINE_H

#include "hotspot/hotspotSupport.h"
#include "hotspot/vmStructs.h"
#include "jvmThread.h"
#include "threadLocalData.h"

inline bool crashProtectionActive() {
    ProfiledThread* pt = ProfiledThread::currentSignalSafe();
    if (pt != nullptr) {
        return pt->isProtected();
    }
    return false;
}

template <typename T>
inline T* cast_to(const void* ptr) {
    assert(VM::isHotspot()); // This should only be used in HotSpot-specific code
    assert(T::type_size() > 0); // Ensure type size has been initialized
    assert(crashProtectionActive() || ptr == nullptr || SafeAccess::isReadableRange(ptr, T::type_size()));
    return reinterpret_cast<T*>(const_cast<void*>(ptr));
}

VMThread* VMThread::current() {
    assert(VM::isHotspot());
    return VMThread::cast(JVMThread::current());
}

VMThread* VMThread::fromJavaThread(JNIEnv* env, jthread thread) {
    assert(VM::isHotspot());
    assert(_eetop != nullptr);
    if (_eetop != nullptr) {
        jlong eetop = env->GetLongField(thread, _eetop);
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
            return nullptr;
        }
        return eetop != 0 ? VMThread::cast((void*)eetop) : nullptr;
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

VMConstMethod* VMMethod::constMethod_or_null() const {
    assert(_method_constmethod_offset >= 0);
    return VMConstMethod::load_then_cast(at(_method_constmethod_offset));
}

jmethodID VMMethod::id() {
    // We may find a bogus NMethod during stack walking, it does not always point to a valid VMMethod
    const char* const_method = (const char*) SafeAccess::load((void**) at(_method_constmethod_offset));
    if (!goodPtr(const_method)) {
        return JMETHODID_NOT_WALKABLE;
    }

    const char* cpool = (const char*) SafeAccess::load((void**)(const_method + _constmethod_constants_offset));
    unsigned short num = (unsigned short) SafeAccess::load32((int32_t*)(const_method + _constmethod_idnum_offset), 0);
    if (goodPtr(cpool)) {
        VMKlass* holder = (VMKlass*) SafeAccess::loadPtr((void**)(cpool + _pool_holder_offset), nullptr);
        if (goodPtr(holder)) {
            jmethodID* ids = (jmethodID*) SafeAccess::loadPtr((void**)((char*)holder + _jmethod_ids_offset), nullptr);
            if (ids != NULL) {
                size_t len = (size_t) SafeAccess::load32((int32_t*)ids, 0);
                if (num < len) {
                    return (jmethodID) SafeAccess::loadPtr((void**)(ids + num + 1), JMETHODID_NOT_WALKABLE);
                } else {
                    // The jmethodID is not populated
                    return nullptr;
                }
            } else {
                // No jmethodID was populated
                return nullptr;
            }
        }
    }
    return JMETHODID_NOT_WALKABLE;
}


jmethodID VMMethod::validatedId() {
    jmethodID method_id = id();
    // We are sure about the value, return it
    if (method_id == JMETHODID_NOT_WALKABLE || method_id == nullptr) {
        return method_id;
    }
    // Check if the value make sense
    if (!_can_dereference_jmethod_id ||
        ((goodPtr(method_id) && SafeAccess::loadPtr((void**)method_id, nullptr) == this))) {
        return method_id;
    }

    return JMETHODID_NOT_WALKABLE;
}

VMKlass* VMConstantPool::holder_or_null() const {
    assert(_pool_holder_offset >= 0);
    return VMKlass::load_then_cast(at(_pool_holder_offset));   
}
VMSymbol* VMConstantPool::symbolAt(int index) const {
    if (index < 0) return nullptr;
    void* ptr = SafeAccess::load((void**)&base()[index], nullptr); 
    return VMSymbol::cast_or_null(ptr);
}

intptr_t* VMConstantPool::base() const {
    assert(_VMConstantPool_size > 0);
    return (intptr_t*)(((char*)this) + _VMConstantPool_size);
}

VMConstantPool* VMConstMethod::constants_or_null() const {
    return VMConstantPool::load_then_cast(at(_constmethod_constants_offset));
}

VMSymbol* VMConstMethod::name() const {
    VMConstantPool* cpool = constants_or_null();
    if (cpool == nullptr) return nullptr;

    u16 name_index = nameIndex();
    return cpool->symbolAt(name_index);
}

VMSymbol* VMConstMethod::signature() const {
    VMConstantPool* cpool = constants_or_null();
    if (cpool == nullptr) return nullptr;

    u16 sig_index = signatureIndex();
    return cpool->symbolAt(sig_index);
}

u16 VMConstMethod::nameIndex() const {
    assert(_constmethod_name_index_offset >= 0 && "Invalid name index");
    return *(u16*)at(_constmethod_name_index_offset);
}

u16 VMConstMethod::signatureIndex() const {
    assert(_constmethod_sig_index_offset >= 0 && "Invalid signature index");
    return *(u16*)at(_constmethod_sig_index_offset);
}


#endif // _HOTSPOT_VMSTRUCTS_INLINE_H
