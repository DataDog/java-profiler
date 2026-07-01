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
  // Called by known JavaThread, cannot be nullpltr
  assert(current_thread != nullptr && "Must not be nullptr");
  _jvm_thread.initialize(current_thread);
  // _tid is side-effect of currentThreadSlow()
  assert(_tid != nullptr);
  return _jvm_thread.isKeyValid();
}

/**
 * Per-thread initialization
 * 
 * This method *must* be called before signal is enabled
 * for the thread.
 */
void JVMThread::initThread() {
}

bool JVMThread::isInitialized() {
    return (_tid != nullptr && _jvm_thread.isKeyValid());
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
