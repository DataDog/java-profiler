/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "threadLocalData.h"

#include "context_api.h"
#include "guards.h"
#include "otel_context.h"
#include "os.h"
#include <cstring>
#include <time.h>

ThreadLocal<ProfiledThread*> ProfiledThread::_profiled_thread;

ProfiledThread* ProfiledThread::initCurrentThread() {
  ProfiledThread* tls = current();
  if (tls != nullptr) {
    return tls;
  }

  int tid = OS::threadId();
  tls = ProfiledThread::forTid(tid);
  _profiled_thread.initValue(tls);
  return tls;
}

void ProfiledThread::release() {
  SignalBlocker blocker;
  ProfiledThread* pt = _profiled_thread.get();
  if (pt != nullptr) {
    _profiled_thread.clear();
    delete pt;
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
  ProfiledThread* tls = _profiled_thread.get();
  if (tls == nullptr) {
    // Lazy allocation - safe since current() is never called from signal handlers
    int tid = OS::threadId();
    tls = ProfiledThread::forTid(tid);
    _profiled_thread.initValue(tls);
  }
  return tls;
}

ProfiledThread *ProfiledThread::currentSignalSafe() {
  // Signal-safe: never allocate, just return existing TLS or null.
  // Use _tls_key_initialized instead of key != 0 because pthread_key_create
  // can legitimately return key 0 (common on musl where keys start at 0).
  return _profiled_thread.get();
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
