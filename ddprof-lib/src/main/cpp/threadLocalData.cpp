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


ThreadLocal<ProfiledThread*, nullptr, ProfiledThread::freeValue>  ProfiledThread::_current_thread;

ProfiledThread* ProfiledThread::initCurrentThread() {
  ProfiledThread* tls = current();
  if (tls == nullptr) {
    int tid = OS::threadId();
    tls = ProfiledThread::forTid(tid);
    _current_thread.set(tls);
  }
  return tls;
}

ProfiledThread* ProfiledThread::initCurrentThreadSignalSafe() {
  SignalBlocker blocker;
  return initCurrentThread();
}

void ProfiledThread::freeValue(void* value) {
  ProfiledThread* pt = reinterpret_cast<ProfiledThread*>(value);
  delete pt;
}

void ProfiledThread::release() {
  _current_thread.clear();
}

int ProfiledThread::currentTid() {
  ProfiledThread *tls = current();
  if (tls != NULL) {
    return tls->tid();
  }
  return OS::threadId();
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
