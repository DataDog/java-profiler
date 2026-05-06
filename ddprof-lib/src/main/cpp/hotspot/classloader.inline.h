/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_CLASSLOADER_INLINE_H
#define _HOTSPOT_CLASSLOADER_INLINE_H

#include "hotspot/classloader.h"

#include <cassert>

bool VMClassLoader::isLoadedByBootstrapClassLoader(const VMMethod* method) {
    if (method == nullptr) {
        return false;
    }
    
    VMKlass* method_klass = method->methodHolderSafe();
    if (method_klass == nullptr) {
        return false;
    }

    VMClassLoaderData* cld = method_klass->classLoaderDataSafe();
    if (cld == nullptr) {
        return false;
    }

    // java/lang/Object must be loaded by bootstrap class loader
    VMKlass* obj_klass = VMClasses::obj_klass();
    assert(obj_klass != nullptr && "VMClasses not yet initialized");
    assert(obj_klass->classLoaderData() != nullptr && "Object class has no class loader data");

    return cld == obj_klass->classLoaderData();
}

#endif // _HOTSPOT_CLASSLOADER_INLINE_H

