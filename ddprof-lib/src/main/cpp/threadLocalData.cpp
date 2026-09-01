/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "faultInjection.h"
#include "threadLocalData.inline.h"
#include "threadLocalDataPool.h"
#include "context_api.h"
#include "guards.h"
#include "otel_context.h"
#include "os.h"
#include <cassert>
#include <cstring>
#include <time.h>


// Namespace-scope static: the ctor (pthread_key_create) runs during library
// load — single-threaded, before profiling signals or the pthread_create
// interceptor are armed. So current()/isThreadKeyValid() may read _key without
// synchronization: the ctor's write happens-before any later thread/signal that
// reads it.
ThreadLocal<ProfiledThread*, nullptr, ProfiledThread::freeValue>  ProfiledThread::_current_thread;

#ifdef UNIT_TEST
void (*ProfiledThread::forTidTestHook)() = nullptr;
#endif

bool ProfiledThread::supportPriming() {
  // Key must be valid
  assert(_current_thread.isKeyValid());
  if (OS::isMusl()) {
    return true;
  }
#ifdef __GLIBC__
  bool rc = _current_thread.key() < PTHREAD_KEY_2NDLEVEL_SIZE;
  return INJECT_FAULT_BOOL_HIGH(rc);
#else
  // Neither musl nor glibc (e.g. macOS libpthread): PTHREAD_KEY_2NDLEVEL_SIZE
  // is a glibc NPTL implementation detail (see threadLocalData.h) that doesn't
  // describe this libc's pthread_key_t allocation scheme. Fail safe by
  // disabling signal-handler TLS priming rather than assuming glibc-compatible
  // pthread_setspecific behavior.
  return false;
#endif
}

ProfiledThread* ProfiledThread::initCurrentThread() {
  if (!isThreadKeyValid()) {
    return nullptr;
  }
  ProfiledThread* tls = _current_thread.get();
  if (tls == nullptr) {
    int tid = OS::threadId();
    tls = ProfiledThread::forTid(tid);
    // forTid()'s `new` can recurse into a malloc hook (e.g. nativemem
    // profiling) that calls acquireCurrent() before we get here. Seeing TLS
    // still unset, it claims a ThreadLocalDataPool slot and publishes it to
    // TLS. Release that slot instead of silently clobbering it below, or it
    // stays claimed forever and the pool leaks one slot per occurrence.
    //
    // Not a signal race: initCurrentThread() is documented above as callable
    // only with profiling signals already blocked on this thread (the
    // SignalBlocker in initCurrentThreadSignalSafe(), or an explicit one at
    // the call site otherwise -- see e.g. libraryPatcher_linux.cpp's
    // init_tls_and_register()). So no signal handler can run -- and
    // therefore none can observe or act on the primed slot -- between the
    // claim above and the release below.
    ProfiledThread* primed = _current_thread.get();
    if (primed != nullptr) {
      ThreadLocalDataPool::release(primed);
    }
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
  // Block future profiling signals that prevents re-allocating
  // ProfiledThread that cannot be released - memory leak
  blockProfilingForExit();

  ProfiledThread* pt = reinterpret_cast<ProfiledThread*>(value);
  if (!ThreadLocalDataPool::release(pt)) {
    // Sole deletion site for a ProfiledThread (invoked by the ThreadLocal
    // destructor callback), so the THREAD_LOCAL decrement belongs here. Record
    // after the delete, consistent with the other decrement sites.
    delete pt;
    NativeMem::record(NM_THREAD_LOCAL, -(long long)sizeof(ProfiledThread));
  }
}

void ProfiledThread::release() {
  _current_thread.clear();
}

#ifdef UNIT_TEST
ProfiledThread* ProfiledThread::clearCurrentThreadTLS() {
    assert(isThreadKeyValid() && "Should not reach here - profiling should have been disabled");
    ProfiledThread* pt = _current_thread.get();
    _current_thread.set(nullptr);
    return pt;
}

void ProfiledThread::deleteForTest(ProfiledThread* pt) {
  if (!ThreadLocalDataPool::release(pt)) {
    delete pt;
    NativeMem::record(NM_THREAD_LOCAL, -(long long)sizeof(ProfiledThread));
  }
}
#endif

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

void ProfiledThread::unclaimAndReset() {
  _unwinding_Java = false;
  _jmp_buf = nullptr;
  _pc = 0;
  _sp = 0;
  _span_id = 0;
  _crash_depth = 0;
  _tid = 0;
  _cpu_epoch = 0;
  _wall_epoch = 0;
  _call_trace_id = 0;
  _recording_epoch = 0;
  _park_slot.block_token = 0;
  _filter_slot_id = -1;
  _init_window = 0;
  _signal_depth = 0;
  _in_critical_section = false;

  _otel_ctx_initialized = false;
  _otel_ctx_record = {};
  _otel_local_root_span_id = 0;
  for (int index = 0; index < DD_TAGS_CAPACITY; index++) {
    _otel_tag_encodings[index] = 0;
  }

  DEBUG_ONLY(_unwind_failures.reset();)
  FAULT_INJECTION_ONLY(_fi_rng = 0;)

  __atomic_store_n(&_misc_flags, 0, __ATOMIC_RELEASE);
}
