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

TLS<ProfiledThread::_name, ProfiledThread*, ProfiledThread::freeKey> ProfiledThread::_current;

void ProfiledThread::freeKey(void *key) {
  ProfiledThread *tls_ref = (ProfiledThread *)(key);
  if (tls_ref != NULL) {
    SignalBlocker blocker;
    delete tls_ref;
  }
}

void ProfiledThread::initCurrentThread() {
  if (_current.get() == nullptr) {
    int tid = OS::threadId();
    ProfiledThread *tls = ProfiledThread::forTid(tid);
    _current.set(tls);
  }
}

void ProfiledThread::release() {
  ProfiledThread *tls = _current.get();
  _current.set(nullptr);
  if (tls == nullptr) {
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

  ProfiledThread *tls = _current.get();
  if (tls == NULL) {
    // Lazy allocation - safe since current() is never called from signal handlers
    int tid = OS::threadId();
    tls = ProfiledThread::forTid(tid);
    _current.set(tls);
  }
  return tls;
}

ProfiledThread *ProfiledThread::currentSignalSafe() {
  return _current.get();
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
