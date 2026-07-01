/*
 * Copyright 2025, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SUPPORT_THREAD_CONTEXT_H
#define _SUPPORT_THREAD_CONTEXT_H

#include "context.h"
#include "otel_context.h"
#include "threadLocalData.h"
#include <atomic>
#include <cstdint>
#include <cstring>
#include <pthread.h>
#include <sys/types.h>

class ProfiledThread;

// Support-owned base class for per-thread OTEL context storage. This is
// shared by ProfiledThread (the full profiler thread-local record) and,
// later, a profiler-less libJavaSupport.so build which only needs the
// context sidecar without the rest of the profiling machinery.
class ThreadContext : public ThreadLocalData {
private:
  static pthread_key_t _tls_key;
  static bool _tls_key_initialized;

  static void initTLSKey();
  static void doInitTLSKey();
  static inline void freeKey(void *key);

protected:
  int _tid;
  bool _otel_ctx_initialized;
  // alignas(8) + sizeof(OtelThreadContextRecord)==640 (multiple of 8) guarantee
  // _otel_tag_encodings sits at +640 with no padding, so the three fields form one
  // 688-byte contiguous region exposed as a combined DirectByteBuffer.
  alignas(8) OtelThreadContextRecord _otel_ctx_record;
  // These two fields MUST be contiguous and 8-byte aligned — the JNI layer
  // exposes them as a single DirectByteBuffer (sidecar), and VarHandle long
  // views require 8-byte alignment for the buffer base address.
  // Read invariant: sidecar readers must gate on record->valid (see ContextApi::get).
  // ThreadContext.restore() relies on this to perform a bulk memcpy under valid=0.
  alignas(8) u32 _otel_tag_encodings[DD_TAGS_CAPACITY];
  u64 _otel_local_root_span_id;

public:
  ThreadContext(int tid)
      : ThreadLocalData(), _tid(tid), _otel_ctx_initialized(false),
        _otel_ctx_record{}, _otel_tag_encodings{}, _otel_local_root_span_id(0) {}

  virtual ~ThreadContext() {}

  // Downcast hook: returns nullptr for a plain ThreadContext; overridden by
  // ProfiledThread to return `this`.
  virtual ProfiledThread* asProfiledThread() { return nullptr; }

  static void initCurrentThread();
  static void release();
  static ThreadContext *current();
  static ThreadContext *currentSignalSafe(); // Signal-safe version that never allocates
  static int currentTid();

#ifdef UNIT_TEST
  // Simulates the moment inside release() after pthread_setspecific(NULL) but
  // before delete — the race window the clearCurrentThreadTLS fix covers.
  // Returns the detached pointer so the caller can delete it after assertions.
  static ThreadContext *clearCurrentThreadTLS() {
    if (__atomic_load_n(&_tls_key_initialized, __ATOMIC_ACQUIRE)) {
      ThreadContext *tls = (ThreadContext *)pthread_getspecific(_tls_key);
      pthread_setspecific(_tls_key, nullptr);
      return tls;
    }
    return nullptr;
  }
  // Deletes a ThreadContext returned by clearCurrentThreadTLS().
  static void deleteForTest(ThreadContext *tls) { delete tls; }
#endif

  inline int tid() { return _tid; }

  // Context TLS (OTEP #4947)
  inline void markContextInitialized() {
    _otel_ctx_initialized = true;
  }

  inline bool isContextInitialized() {
    return _otel_ctx_initialized;
  }

  inline OtelThreadContextRecord* getOtelContextRecord() {
    return &_otel_ctx_record;
  }

  // JFR tag encoding sidecar — populated by JNI thread, read by signal handler
  // (flightRecorder.cpp writeCurrentContext / wallClock.cpp collapsing).
  inline u32* getOtelTagEncodingsPtr() { return _otel_tag_encodings; }
  inline u32 getOtelTagEncoding(u32 idx) const {
    return idx < DD_TAGS_CAPACITY ? _otel_tag_encodings[idx] : 0;
  }
  inline u64 getOtelLocalRootSpanId() const { return _otel_local_root_span_id; }

  inline void clearOtelSidecar() {
    memset(_otel_tag_encodings, 0, sizeof(_otel_tag_encodings));
    _otel_local_root_span_id = 0;
  }
};

// Factory hook allowing the concrete per-thread type to be swapped between
// plain ThreadContext (support-only) and ProfiledThread (profiler present),
// decided at runtime.
typedef ThreadContext* (*ThreadContextFactory)(int tid);
extern std::atomic<ThreadContextFactory> g_thread_context_factory;

#endif // _SUPPORT_THREAD_CONTEXT_H
