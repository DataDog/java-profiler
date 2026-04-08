/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "zingSupport.h"

#include "vmEntry.h"
#include <jni.h>

void* ZingSupport::initialize(jthread thread) {
    JNIEnv* env = VM::jni();
    jclass thread_class = env->FindClass("java/lang/Thread");
    if (thread_class == nullptr) {
        env->ExceptionClear();
        return nullptr;
    }
    jfieldID eetop = nullptr;
    // Get eetop field - a bridge from Java Thread to JVMThread
    if ((eetop = env->GetFieldID(thread_class, "eetop", "J")) == nullptr) {
        // No such field - probably not use standard java library
        env->ExceptionClear();
        return nullptr;
    }

    return (void*)env->GetLongField(thread, eetop);
}

