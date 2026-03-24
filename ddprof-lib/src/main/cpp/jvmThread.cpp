/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "jvmThread.h"
#include "j9/j9Ext.h"

pthread_key_t JVMThread::_thread_key = pthread_key_t(-1);
jfieldID JVMThread::_tid = nullptr;
jfieldID JVMThread::_eetop = nullptr;

bool JVMThread::initialize() {
  void* current_thread = current_thread_slow();
  if (current_thread == nullptr) {
    return false;
  }

  for (int i = 0; i < 1024; i++) {
    if (pthread_getspecific((pthread_key_t)i) == current_thread) {
        _thread_key = pthread_key_t(i);
        break;
    }
  }

  assert(_tid != nullptr);
  assert(!VM::isHotspot() || _eetop != nullptr);

  if (VM::isHotspot()) {
    VMThread::initialize(current_thread);
  }

  return true;
}

void* JVMThread::current_thread_slow() {
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

    // Get eetop field - a bridge from Java Thread to VMThread
    if ((_eetop = env->GetFieldID(thread_class, "eetop", "J")) == NULL) {
       // No such field - probably not a HotSpot JVM
       env->ExceptionClear();
    }

    if (VM::isOpenJ9()) {
      return J9Ext::j9thread_self();
    } else {
      assert(_eetop != nullptr);
      return (void*)env->GetLongField(thread, _eetop);
    }
}
