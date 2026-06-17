/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "thread.h"
#include "context_api.h"
#include "guards.h"
#include "otel_context.h"
#include "os.h"
#include <cstring>
#include <time.h>

pthread_key_t ProfiledThread::_tls_key;
bool ProfiledThread::_tls_key_initialized = false;

void ProfiledThread::initTLSKey() {
  static pthread_once_t tls_initialized = PTHREAD_ONCE_INIT;
  pthread_once(&tls_initialized, doInitTLSKey);
}

void ProfiledThread::doInitTLSKey() {
  pthread_key_create(&_tls_key, freeKey);
  // Must be set AFTER pthread_key_create so signal handlers see a valid key.
  // Store-release pairs with the acquire loads in currentSignalSafe() and release()
  // to prevent hardware load-load reordering on weakly-ordered architectures (aarch64):
  // a plain volatile write is not sufficient there.
  __atomic_store_n(&_tls_key_initialized, true, __ATOMIC_RELEASE);
}

inline void ProfiledThread::freeKey(void *key) {
  ProfiledThread *tls_ref = (ProfiledThread *)(key);
  if (tls_ref != NULL) {
    SignalBlocker blocker;
    delete tls_ref;
  }
}

void ProfiledThread::initCurrentThread() {
  // JVMTI callback path - does NOT use buffer
  // Allocate dedicated ProfiledThread for Java threads (not from buffer)
  // This MUST happen here to prevent lazy allocation in signal handler
  initTLSKey();

  if (pthread_getspecific(_tls_key) != NULL) {
    return; // Already initialized
  }

  int tid = OS::threadId();
  ProfiledThread *tls = ProfiledThread::forTid(tid);
  pthread_setspecific(_tls_key, (const void *)tls);
}

void ProfiledThread::release() {
  if (!__atomic_load_n(&_tls_key_initialized, __ATOMIC_ACQUIRE)) {
    return;
  }
  pthread_key_t key = _tls_key;
  ProfiledThread *tls = (ProfiledThread *)pthread_getspecific(key);
  if (tls != NULL) {
    SignalBlocker blocker;
    pthread_setspecific(key, NULL);
    delete tls;
  }
}


int ProfiledThread::currentTid() {
  ProfiledThread *tls = current();
  if (tls != NULL) {
    return tls->tid();
  }
  return OS::threadId();
}

ProfiledThread *ProfiledThread::current() {
  initTLSKey();

  ProfiledThread *tls = (ProfiledThread *)pthread_getspecific(_tls_key);
  if (tls == NULL) {
    // Lazy allocation - safe since current() is never called from signal handlers
    int tid = OS::threadId();
    tls = ProfiledThread::forTid(tid);
    pthread_setspecific(_tls_key, (const void *)tls);
  }
  return tls;
}

ProfiledThread *ProfiledThread::currentSignalSafe() {
  // Signal-safe: never allocate, just return existing TLS or null.
  // Use _tls_key_initialized instead of key != 0 because pthread_key_create
  // can legitimately return key 0 (common on musl where keys start at 0).
  return __atomic_load_n(&_tls_key_initialized, __ATOMIC_ACQUIRE) ? (ProfiledThread *)pthread_getspecific(_tls_key) : nullptr;
}


Context ProfiledThread::snapshotContext(size_t numAttrs) {
  Context ctx = {};
  u64 span_id = 0, root_span_id = 0;
  if (ContextApi::get(span_id, root_span_id)) {
    ctx.spanId = span_id;
    ctx.rootSpanId = root_span_id;
    size_t count = numAttrs < DD_TAGS_CAPACITY ? numAttrs : DD_TAGS_CAPACITY;
    for (size_t i = 0; i < count; i++) {
      ctx.tags[i].value = _otel_tag_encodings[i];
    }
  }
  return ctx;
}
