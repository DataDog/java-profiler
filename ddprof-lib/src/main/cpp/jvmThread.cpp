/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "jvmThread.h"

pthread_key_t JVMThread::_thread_key = pthread_key_t(-1);

bool JVMThread::init_key() {
  void* current_thread = current_thread_slow();
  if (current_thread == nullptr) {
    return false;
  }
  for (int i = 0; i < 1024; i++) {
    if (pthread_getspecific((pthread_key_t)i) == current_thread) {
        _thread_key = pthread_key_t(i);
        return true;
    }
  }
  return false;
}

void* JVMThread::current_thread_slow() {
    void* current_thread = nullptr;
    if (VM::isOpenJ9()) {
        current_thread = J9Ext::j9thread_self();
    } else {
        current_thread = VMThread::init_and_get_current();
    }
    return current_thread;
}
