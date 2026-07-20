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


// Namespace-scope static: the ctor (pthread_key_create) runs during library
// load — single-threaded, before profiling signals or the pthread_create
// interceptor are armed. So current()/isThreadKeyValid() may read _key without
// synchronization: the ctor's write happens-before any later thread/signal that
// reads it.
ThreadLocal<ProfiledThread*, nullptr, ProfiledThread::freeValue>  ProfiledThread::_current_thread;

ProfiledThread* ProfiledThread::initCurrentThread() {
  if (!isThreadKeyValid()) {
    return nullptr;
  }
  ProfiledThread* tls = _current_thread.get();
  if (tls == nullptr) {
    int tid = OS::threadId();
    tls = ProfiledThread::forTid(tid);
    _current_thread.set(tls);
  }
  return tls;
}

ProfiledThread* ProfiledThread::initCurrentThreadSignalSafe() {
  if (!isThreadKeyValid()) {
    return nullptr;
  }

  ProfiledThread* cur = current();
  if (cur == nullptr) {
    SignalBlocker blocker;
    return initCurrentThread();
  } else {
    return cur;
  }
}

void ProfiledThread::freeValue(void* value) {
  SignalBlocker blocker;
  ProfiledThread* pt = reinterpret_cast<ProfiledThread*>(value);
  // Sole deletion site for a ProfiledThread (invoked by the ThreadLocal
  // destructor callback), so the THREAD_LOCAL decrement belongs here.
  NativeMem::record(NM_THREAD_LOCAL, -(long long)sizeof(ProfiledThread));
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
