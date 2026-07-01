/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "threadContext.h"
#include "guards.h"
#include "os.h"

pthread_key_t ThreadContext::_tls_key;
bool ThreadContext::_tls_key_initialized = false;

static ThreadContext* defaultFactory(int tid) { return new ThreadContext(tid); }
std::atomic<ThreadContextFactory> g_thread_context_factory{defaultFactory};

void ThreadContext::initTLSKey() {
  static pthread_once_t tls_initialized = PTHREAD_ONCE_INIT;
  pthread_once(&tls_initialized, doInitTLSKey);
}

void ThreadContext::doInitTLSKey() {
  pthread_key_create(&_tls_key, freeKey);
  // Must be set AFTER pthread_key_create so signal handlers see a valid key.
  // Store-release pairs with the acquire loads in currentSignalSafe() and release()
  // to prevent hardware load-load reordering on weakly-ordered architectures (aarch64):
  // a plain volatile write is not sufficient there.
  __atomic_store_n(&_tls_key_initialized, true, __ATOMIC_RELEASE);
}

inline void ThreadContext::freeKey(void *key) {
  ThreadContext *tls_ref = (ThreadContext *)(key);
  if (tls_ref != NULL) {
    SignalBlocker blocker;
    delete tls_ref;
  }
}

void ThreadContext::initCurrentThread() {
  // JVMTI callback path - does NOT use buffer
  // Allocate dedicated ThreadContext for Java threads (not from buffer)
  // This MUST happen here to prevent lazy allocation in signal handler
  initTLSKey();

  if (pthread_getspecific(_tls_key) != NULL) {
    return; // Already initialized
  }

  int tid = OS::threadId();
  ThreadContext *tls = g_thread_context_factory.load(std::memory_order_acquire)(tid);
  pthread_setspecific(_tls_key, (const void *)tls);
}

void ThreadContext::release() {
  if (!__atomic_load_n(&_tls_key_initialized, __ATOMIC_ACQUIRE)) {
    return;
  }
  pthread_key_t key = _tls_key;
  ThreadContext *tls = (ThreadContext *)pthread_getspecific(key);
  if (tls != NULL) {
    SignalBlocker blocker;
    pthread_setspecific(key, NULL);
    delete tls;
  }
}

int ThreadContext::currentTid() {
  ThreadContext *tls = current();
  if (tls != NULL) {
    return tls->tid();
  }
  return OS::threadId();
}

ThreadContext *ThreadContext::current() {
  initTLSKey();

  ThreadContext *tls = (ThreadContext *)pthread_getspecific(_tls_key);
  if (tls == NULL) {
    // Lazy allocation - safe since current() is never called from signal handlers
    int tid = OS::threadId();
    tls = g_thread_context_factory.load(std::memory_order_acquire)(tid);
    pthread_setspecific(_tls_key, (const void *)tls);
  }
  return tls;
}

ThreadContext *ThreadContext::currentSignalSafe() {
  // Signal-safe: never allocate, just return existing TLS or null.
  // Use _tls_key_initialized instead of key != 0 because pthread_key_create
  // can legitimately return key 0 (common on musl where keys start at 0).
  return __atomic_load_n(&_tls_key_initialized, __ATOMIC_ACQUIRE) ? (ThreadContext *)pthread_getspecific(_tls_key) : nullptr;
}
