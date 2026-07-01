/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "thread.h"
#include "support/context_api.h"
#include "guards.h"
#include "otel_context.h"
#include "os.h"
#include <cstring>
#include <time.h>

// The shared ThreadContext TLS slot defaults to producing plain ThreadContext
// instances (support-only build). This translation unit is only linked into
// the full profiler build, so it commits the factory to produce ProfiledThread
// instead, at library-load time — before any thread (including the one that
// calls Profiler::start()) can observe the TLS slot and lazily allocate a
// plain ThreadContext.
static ThreadContext *newProfiledThread(int tid) { return ProfiledThread::forTid(tid); }

namespace {
struct ProfiledThreadFactoryInstaller {
  ProfiledThreadFactoryInstaller() {
    g_thread_context_factory.store(newProfiledThread, std::memory_order_release);
  }
};
static ProfiledThreadFactoryInstaller profiled_thread_factory_installer;
} // namespace

void ProfiledThread::initCurrentThread() {
  // JVMTI callback path - does NOT use buffer
  // Allocate dedicated ProfiledThread for Java threads (not from buffer)
  // This MUST happen here to prevent lazy allocation in signal handler
  ThreadContext::initCurrentThread();
}

void ProfiledThread::release() {
  ThreadContext::release();
}

int ProfiledThread::currentTid() {
  return ThreadContext::currentTid();
}

// Non-null under the committed init-at-premain scope (factory yields ProfiledThread).
ProfiledThread *ProfiledThread::currentProfiled() {
  return ThreadContext::current()->asProfiledThread();
}

ProfiledThread *ProfiledThread::currentSignalSafe() {
  // Signal-safe: never allocate, just return existing TLS or null.
  ThreadContext *tls = ThreadContext::currentSignalSafe();
  return tls != nullptr ? tls->asProfiledThread() : nullptr;
}

Context ProfiledThread::snapshotContext(size_t numAttrs) {
  Context ctx = {};
  u64 span_id = 0, root_span_id = 0;
  if (ContextApi::get(span_id, root_span_id)) {
    ctx.spanId = span_id;
    ctx.rootSpanId = root_span_id;
    size_t count = numAttrs < DD_TAGS_CAPACITY ? numAttrs : DD_TAGS_CAPACITY;
    for (size_t i = 0; i < count; i++) {
      ctx.tags[i].value = getOtelTagEncodingsPtr()[i];
    }
  }
  return ctx;
}
