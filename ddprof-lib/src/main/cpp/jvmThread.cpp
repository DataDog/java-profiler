/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "jvmThread.h"
#include "hotspot/hotspotSupport.h"
#include "hotspot/vmStructs.inline.h"
#include "j9/j9Support.h"
#include "zing/zingSupport.h"
#include "vmEntry.h"

jfieldID JVMThread::_tid = nullptr;
ThreadLocal<JVMThread*> JVMThread::_jvm_thread;

bool JVMThread::initialize() {
  void* current_thread = currentThreadSlow();
  if (current_thread == nullptr) {
    return false;
  }
  // _tid is initialized inside currentThreadSlow() via
  // JNI call.
  // _tid (jfieldID) is a field of java/lang/Thread object, stores native
  // thread pointer. Current thread is resolved via this field
  // of current java thread.
  if (_tid == nullptr) {
    return false;
  }
  return _jvm_thread.initialize(current_thread);
}

bool JVMThread::supportsNativeThreadIdLookup() {
  return VM::isOpenJ9() || VMThread::hasNativeThreadId();
}

int JVMThread::nativeThreadId(JNIEnv* jni, jthread thread) {
    return VM::isOpenJ9() ? J9Support::GetOSThreadID(thread) : VMThread::nativeThreadId(jni, thread);
}

void* JVMThread::currentThreadSlow() {
    jthread thread;
    if (VM::jvmti()->GetCurrentThread(&thread) != JVMTI_ERROR_NONE) {
        return nullptr;
    }

    JNIEnv* env = VM::jni();
    jclass thread_class = env->FindClass("java/lang/Thread");
    if (thread_class == NULL || (_tid = env->GetFieldID(thread_class, "tid", "J")) == NULL) {
        env->ExceptionClear();
        return nullptr;
    }

    if (VM::isOpenJ9()) {
      return J9Support::j9thread_self();
    } else if (VM::isZing()) {
      return ZingSupport::initialize(thread);
    } else {
      assert(VM::isHotspot());
      return VMThread::initialize(thread);
    }
}
