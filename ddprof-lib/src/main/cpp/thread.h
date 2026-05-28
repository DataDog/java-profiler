/*
 * Copyright 2025, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _THREAD_H
#define _THREAD_H

#include "context.h"
#include "context_api.h"
#include "otel_context.h"
#include "os.h"
#include "threadLocalData.h"
#include "threadState.h"
#include "unwindStats.h"
#include <atomic>
#include <cstdint>
#include <jvmti.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <vector>

class ProfiledThread : public ThreadLocalData {
public:
  enum ThreadType : u32 {
    TYPE_UNKNOWN = 0,
    TYPE_JAVA_THREAD = 0x1,
    TYPE_NOT_JAVA_THREAD = 0x2,
    TYPE_MASK = TYPE_JAVA_THREAD | TYPE_NOT_JAVA_THREAD
  };

  static constexpr u32 FLAG_PARKED = 0x4u;

private:
  // We are allowing several levels of nesting because we can be
  // eg. in a crash handler when wallclock signal kicks in,
  // catching sigseg while also triggering CPU signal handler
  // which would also potentially trigger sigseg we need to handle.
  // This means 3 levels but we allow for some wiggling space, just in case.
  // Even with 5 levels cap we will need any highly recursing signal handlers
  static constexpr u32 CRASH_HANDLER_NESTING_LIMIT = 5;
  static pthread_key_t _tls_key;
  static bool _tls_key_initialized;

  static void initTLSKey();
  static void doInitTLSKey();
  static inline void freeKey(void *key);

  u64 _pc;
  u64 _sp;
  u64 _span_id;  // Wall-clock collapsing cache: last-seen span ID (not a context store — read from _otel_ctx_record on each signal, cached here to detect "same as last time")
  volatile u32 _crash_depth;
  int _tid;
  u32 _cpu_epoch;
  u32 _wall_epoch;
  u64 _call_trace_id;
  u32 _recording_epoch;
  u32 _misc_flags;
  u64 _park_start_ticks;
  Context _park_context;
  int _filter_slot_id; // Slot ID for thread filtering
  uint8_t _init_window; // Countdown for JVM thread init race window (PROF-13072)
  UnwindFailures _unwind_failures;
  bool _otel_ctx_initialized;
  bool _crash_protection_active;
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

  // Wall-clock once-per-run filter state used to live here (per ProfiledThread). It now
  // lives on ThreadFilter::Slot — the wall-clock timer needs to read it cross-thread for
  // its IPI fast-path, and ProfiledThread instances are deleted on thread exit, which
  // made the cross-thread deref a use-after-free. ThreadFilter::Slot instances are
  // JVM-process stable, eliminating the hazard. The handler still writes the state
  // (via current->filterSlotId() → threadFilter()->slotForId() → markSampledThisRun/
  // resetSampledRun); see WallClockASGCT::signalHandler in wallClock.cpp.

  ProfiledThread(int tid)
      : ThreadLocalData(), _pc(0), _sp(0), _span_id(0), _crash_depth(0), _tid(tid), _cpu_epoch(0),
        _wall_epoch(0), _call_trace_id(0), _recording_epoch(0), _misc_flags(0),
        _park_start_ticks(0), _park_context{},
        _filter_slot_id(-1), _init_window(0),
        _otel_ctx_initialized(false), _crash_protection_active(false),
        _otel_ctx_record{}, _otel_tag_encodings{}, _otel_local_root_span_id(0) {};

  virtual ~ProfiledThread() { }
public:
  static ProfiledThread *forTid(int tid) { return new ProfiledThread(tid); }

  static void initCurrentThread();
  static void release();
  // Clears TLS without deleting the ProfiledThread. For unit tests only:
  // simulates the moment inside release() after pthread_setspecific(NULL) but
  // before delete, which is the race window the _thread_ptr fix covers.
  static void clearCurrentThreadTLS() {
    if (__atomic_load_n(&_tls_key_initialized, __ATOMIC_ACQUIRE)) {
      pthread_setspecific(_tls_key, nullptr);
    }
  }

  static ProfiledThread *current();
  static ProfiledThread *currentSignalSafe(); // Signal-safe version that never allocates
  static int currentTid();

  inline int tid() { return _tid; }

  inline u64 noteCPUSample(u32 recording_epoch) {
    _recording_epoch = recording_epoch;
    return ++_cpu_epoch;
  }

  /**
   * Attempts to reuse a cached call trace ID for wallclock sample collapsing.
   * Collapsing is allowed only when the execution state (PC, SP) and trace
   * context (spanId, rootSpanId) are identical to the previous sample.
   *
   * @param pc Program counter from ucontext
   * @param sp Stack pointer from ucontext
   * @param recording_epoch Current profiling session epoch
   * @param context_valid True if the OTEP valid flag was set; controls whether _otel_local_root_span_id is updated
   * @param span_id Current trace span ID
   * @param root_span_id Current trace root span ID
   * @return Cached call_trace_id if collapsing is allowed, 0 otherwise
   */
  u64 lookupWallclockCallTraceId(u64 pc, u64 sp, u32 recording_epoch,
                                  bool context_valid, u64 span_id, u64 root_span_id) {
    if (_pc == pc && _sp == sp && _span_id == span_id &&
        _otel_local_root_span_id == root_span_id && _recording_epoch == recording_epoch &&
        _call_trace_id != 0) {
      return _call_trace_id;
    }
    _pc = pc;
    _sp = sp;
    _span_id = span_id;
    // Only update the sidecar when context is valid (valid=1). If the signal fires
    // between detach() and attach() in Java, ContextApi::get returns valid=0 with
    // root_span_id=0; writing that would clobber the value Java just stored.
    if (context_valid) {
      // Plain store is safe: naturally-aligned u64 stores/loads are atomic on
      // x86-64 and aarch64 (the only supported targets). The Java writer uses
      // sidecarBuffer.putLong() which is a single aligned 8-byte store.
      _otel_local_root_span_id = root_span_id;
    }
    _recording_epoch = recording_epoch;
    return 0;
  }

  inline void recordCallTraceId(u64 call_trace_id) {
    _call_trace_id = call_trace_id;
  }

  // this is called in the crash handler to avoid recursing
  bool enterCrashHandler() {
    u32 prev = _crash_depth;
    // This is thread local; no need for atomic cmpxchg
    if (prev < CRASH_HANDLER_NESTING_LIMIT) {
      _crash_depth++;
      return true;
    }
    return false;
  }

  // needs to be called when the crash handler exits
  void exitCrashHandler() {
    // failsafe check - do not attempt to decrement if there are no crash handlers on stack
    if (_crash_depth > 0) _crash_depth--;
  }

  void resetCrashHandler() {
    _crash_depth = 0;
  }

  bool isDeepCrashHandler() {
    return _crash_depth > CRASH_HANDLER_NESTING_LIMIT;
  }

  UnwindFailures* unwindFailures(bool reset = true) {
    if (reset) {
      _unwind_failures.clear();
    }
    return &_unwind_failures;
  }

  int filterSlotId() { return _filter_slot_id; }
  void setFilterSlotId(int slotId) { _filter_slot_id = slotId; }

  // JVM thread init race window (PROF-13072): skip at most one signal that fires
  // between Profiler::registerThread() and the JVM's pd_set_thread() call.
  // Pure native threads (e.g. NativeThreadCreator) also see nullptr from
  // JVMThread::current(), so the window auto-expires after one skip, allowing
  // their subsequent samples through.
  inline bool inInitWindow() const { return _init_window > 0; }
  inline void startInitWindow() { _init_window = 1; }
  inline void tickInitWindow() { if (_init_window > 0) --_init_window; }

  // Signal handler reentrancy protection
  bool tryEnterCriticalSection() {
    // Uses GCC atomic builtin (no malloc, async-signal-safe)
    bool expected = false;
    return __atomic_compare_exchange_n(&_in_critical_section, &expected, true, false, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED);
  }
  void exitCriticalSection() {
    // Uses GCC atomic builtin (no malloc, async-signal-safe)
    __atomic_store_n(&_in_critical_section, false, __ATOMIC_RELEASE);
  }
  
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

  // Record java thread state.
  // Uses a CAS RMW instead of a plain load-mask-store to avoid silently clobbering FLAG_PARKED:
  // vmStructs.cpp::isJavaThread() can call this from signal-handler context, where a prior
  // parkExit() on the same thread (also running in the handler) may have just cleared FLAG_PARKED.
  // A plain store of the pre-signal load value would restore the cleared flag. The CAS correctly
  // updates only the TYPE_MASK bits and retries if any other bit changed under us.
  inline void setJavaThread(bool is_java) {
    const u32 type_bits = is_java ? static_cast<u32>(TYPE_JAVA_THREAD) : static_cast<u32>(TYPE_NOT_JAVA_THREAD);
    u32 cur = __atomic_load_n(&_misc_flags, __ATOMIC_RELAXED);
    u32 desired;
    do {
      desired = (cur & ~static_cast<u32>(TYPE_MASK)) | type_bits;
    } while (!__atomic_compare_exchange_n(&_misc_flags, &cur, desired,
                                          /*weak=*/true,
                                          __ATOMIC_ACQ_REL, __ATOMIC_RELAXED));
  }

  inline enum ThreadType threadType() const {
    return static_cast<ThreadType>(_misc_flags & TYPE_MASK);
  }

  inline bool isCrashProtectionActive() const { return _crash_protection_active; }
  inline void setCrashProtectionActive(bool active) { _crash_protection_active = active; }

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

  inline void parkEnter(u64 start_ticks) {
    // Snapshot the OTEP TLS context atomically (spanId/rootSpanId/tags captured under the
    // single validity gate inside ContextApi::snapshot). This replaces the prior hand-rolled
    // tag loop and removes the JNI-passed spanId/rootSpanId override path.
    _park_context = ContextApi::snapshot();
    _park_start_ticks = start_ticks;
    // Set FLAG_PARKED without disturbing other _misc_flags bits (thread type, etc.).
    // Release ordering pairs with the ACQ_REL in parkExit(), ensuring that _park_start_ticks
    // and _park_context are fully visible before FLAG_PARKED is observed as set. Both
    // operations run on the owning thread; no cross-thread reader accesses FLAG_PARKED.
    __atomic_fetch_or(&_misc_flags, FLAG_PARKED, __ATOMIC_RELEASE);
  }

  inline bool parkExit(u64 &start_ticks, Context &park_context) {
    u32 prev = __atomic_fetch_and(&_misc_flags, ~FLAG_PARKED, __ATOMIC_ACQ_REL);
    if ((prev & FLAG_PARKED) == 0) {
      return false;
    }
    start_ticks = _park_start_ticks;
    park_context = _park_context;
    return true;
  }

  // Wall-clock once-per-run filter accessors live on ThreadFilter::Slot
  // (see threadFilter.h Slot::sampledThisRun/lastSampledState/markSampledThisRun/
  // resetSampledRun). Reaching them from the signal handler:
  //   ThreadFilter::Slot* slot =
  //       Profiler::instance()->threadFilter()->slotForId(current->filterSlotId());

  Context snapshotContext(size_t numAttrs);

private:
  // Atomic flag for signal handler reentrancy protection within the same thread
  // Must be atomic because a signal handler can interrupt normal execution mid-instruction,
  // and both contexts may attempt to enter the critical section. Without atomic exchange(),
  // both could see the flag as false and both would think they successfully entered.
  // The atomic exchange() is uninterruptible, ensuring only one context succeeds.
  bool _in_critical_section{false};
};

#endif // _THREAD_H
