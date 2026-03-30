/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "jvmThread.h"
#include "hotspot/vmStructs.inline.h"
#include "j9/j9Ext.h"
#include "zing/zingSupport.h"
#include "vmEntry.h"

pthread_key_t JVMThread::_thread_key = pthread_key_t(-1);
jmethodID JVMThread::_tid = nullptr;

bool JVMThread::initialize() {
  void* current_thread = currentThreadSlow();
  if (current_thread == nullptr) {
    return false;
  }

  for (int i = 0; i < 1024; i++) {
    if (pthread_getspecific((pthread_key_t)i) == current_thread) {
        _thread_key = pthread_key_t(i);
        break;
    }
  }
  // _tid is initialized in currentThreadSlow()
  assert(_tid != nullptr);
  return _thread_key != pthread_key_t(-1);
}

int JVMThread::nativeThreadId(JNIEnv* jni, jthread thread) {
    return VM::isOpenJ9() ? J9Ext::GetOSThreadID(thread) : VMThread::nativeThreadId(jni, thread);
}

void* JVMThread::currentThreadSlow() {
    jthread thread;
    if (VM::jvmti()->GetCurrentThread(&thread) != JVMTI_ERROR_NONE) {
        return nullptr;
    }

    JNIEnv* env = VM::jni();
    jclass thread_class = env->FindClass("java/lang/Thread");
    if (thread_class == NULL || (_tid = env->GetMethodID(thread_class, "getId", "()J")) == NULL) {
        env->ExceptionClear();
        return nullptr;
    }

    if (VM::isOpenJ9()) {
      return J9Ext::j9thread_self();
    } else if (VM::isZing()) {
      return ZingSupport::initialize(thread);
    } else {
      assert(VM::isHotspot());
      return VMThread::initialize(thread);
    }
}
