/*
 * Copyright 2025, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _THREAD_H
#define _THREAD_H

#include "context.h"
#include "otel_context.h"
#include "os.h"
#include "support/threadContext.h"
#include "threadState.h"
#include "unwindStats.h"
#include <atomic>
#include <cstdint>
#include <jvmti.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <vector>

class ProfiledThread : public ThreadContext {
public:
  enum ThreadType : u32 {
    TYPE_UNKNOWN = 0,
    TYPE_JAVA_THREAD = 0x1,
    TYPE_NOT_JAVA_THREAD = 0x2,
    TYPE_MASK = TYPE_JAVA_THREAD | TYPE_NOT_JAVA_THREAD
  };

  static constexpr u32 FLAG_PARKED = 0x4u; // next free bit after TYPE_MASK (0x1|0x2)

private:
  // We are allowing several levels of nesting because we can be
  // eg. in a crash handler when wallclock signal kicks in,
  // catching sigseg while also triggering CPU signal handler
  // which would also potentially trigger sigseg we need to handle.
  // This means 3 levels but we allow for some wiggling space, just in case.
  // Even with 5 levels cap we will need any highly recursing signal handlers
  static constexpr u32 CRASH_HANDLER_NESTING_LIMIT = 5;

  u64 _pc;
  u64 _sp;
  u64 _span_id;  // Wall-clock collapsing cache: last-seen span ID (not a context store — read from the OTEL context record on each signal, cached here to detect "same as last time")
  volatile u32 _crash_depth;
  u32 _cpu_epoch;
  u32 _wall_epoch;
  u64 _call_trace_id;
  u32 _recording_epoch;
  u32 _misc_flags;
  u64 _park_block_token;
  int _filter_slot_id; // Slot ID for thread filtering
  uint8_t _init_window; // Countdown for JVM thread init race window (PROF-13072)
  uint8_t _signal_depth; // Nested signal-handler depth (see SignalHandlerScope)
  UnwindFailures _unwind_failures;
  bool _crash_protection_active;

  ProfiledThread(int tid)
      : ThreadContext(tid), _pc(0), _sp(0), _span_id(0), _crash_depth(0), _cpu_epoch(0),
        _wall_epoch(0), _call_trace_id(0), _recording_epoch(0), _misc_flags(0),
        _park_block_token(0), _filter_slot_id(-1), _init_window(0),
        _signal_depth(0), _crash_protection_active(false) {};

  virtual ~ProfiledThread() { }
public:
  static ProfiledThread *forTid(int tid) { return new ProfiledThread(tid); }

  static void initCurrentThread();
  static void release();
#ifdef UNIT_TEST
  // Simulates the moment inside release() after pthread_setspecific(NULL) but
  // before delete — the race window the clearCurrentThreadTLS fix covers.
  // Returns the detached pointer so the caller can delete it after assertions.
  static ProfiledThread* clearCurrentThreadTLS() {
    ThreadContext *tls = ThreadContext::clearCurrentThreadTLS();
    return tls != nullptr ? tls->asProfiledThread() : nullptr;
  }
  // Deletes a ProfiledThread returned by clearCurrentThreadTLS().
  // Needed because the destructor is private.
  static void deleteForTest(ProfiledThread *pt) { ThreadContext::deleteForTest(pt); }
#endif

  // Downcast hook (see ThreadContext::asProfiledThread).
  ProfiledThread* asProfiledThread() override { return this; }

  static ProfiledThread *currentProfiled();
  static ProfiledThread *currentSignalSafe(); // Signal-safe version that never allocates
  static int currentTid();

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

  // Signal-handler depth counter used by SignalHandlerScope (guards.h).  All
  // access happens on the owning thread (signal handlers are delivered to the
  // thread that's interrupted), so plain reads/writes are AS-safe — no locks,
  // no malloc, no syscalls.  See guards.h for the public API.
  inline uint8_t signalDepth() const { return _signal_depth; }
  inline void enterSignalScope()    { ++_signal_depth; }
  inline void exitSignalScope()     { if (_signal_depth > 0) --_signal_depth; }

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
  
  // CAS RMW to update only TYPE_MASK bits without clobbering FLAG_PARKED, which
  // is managed independently by the Java park hooks on the owning thread.
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
    u32 flags = __atomic_load_n(&_misc_flags, __ATOMIC_ACQUIRE);
    return static_cast<ThreadType>(flags & TYPE_MASK);
  }

  inline bool isCrashProtectionActive() const { return _crash_protection_active; }
  inline void setCrashProtectionActive(bool active) { _crash_protection_active = active; }

  inline bool parkEnter() {
    u32 prev = __atomic_fetch_or(&_misc_flags, FLAG_PARKED, __ATOMIC_RELEASE);
    return (prev & FLAG_PARKED) == 0;
  }

  inline void setParkBlockToken(u64 token) {
    _park_block_token = token;
  }

  // Returns false if the thread was not parked (idempotent).
  inline bool parkExit(u64 &park_block_token) {
    u32 prev = __atomic_fetch_and(&_misc_flags, ~FLAG_PARKED, __ATOMIC_ACQ_REL);
    if ((prev & FLAG_PARKED) == 0) {
      return false;
    }
    park_block_token = _park_block_token;
    _park_block_token = 0;
    return true;
  }

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
