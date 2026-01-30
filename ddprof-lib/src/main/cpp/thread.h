/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _THREAD_H
#define _THREAD_H

#include "os.h"
#include "threadLocalData.h"
#include "unwindStats.h"
#include <atomic>
#include <cstdint>
#include <jvmti.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <vector>

// Forward declaration to avoid circular dependency
class Context;

class ProfiledThread : public ThreadLocalData {     
private:
  // We are allowing several levels of nesting because we can be
  // eg. in a crash handler when wallclock signal kicks in,
  // catching sigseg while also triggering CPU signal handler
  // which would also potentially trigger sigseg we need to handle.
  // This means 3 levels but we allow for some wiggling space, just in case.
  // Even with 5 levels cap we will need any highly recursing signal handlers
  static constexpr u32 CRASH_HANDLER_NESTING_LIMIT = 5;
  static pthread_key_t _tls_key;
  static volatile bool _tls_key_initialized;  // Tracks whether _tls_key is valid
  static int _buffer_size;
  static volatile int _running_buffer_pos;
  static ProfiledThread** _buffer;

  // Misc flags
  static constexpr u32 FLAG_JAVA_THREAD = 0x01;

  // Free slot recycling - lock-free stack of available buffer slots
  // Note: Using plain int with GCC atomic builtins instead of std::atomic
  // because std::atomic is not guaranteed async-signal-safe (may use mutexes)
  static volatile int _free_stack_top;
  static int* _free_slots;  // Array to store free slot indices

  static void initTLSKey();
  static void doInitTLSKey();
  static inline void freeKey(void *key);
  static void doInitExistingThreads();
  static void prepareBuffer(int size);
  static void cleanupBuffer();

  // Free slot management - lock-free operations
  static int popFreeSlot();    // Returns -1 if no free slots
  static void pushFreeSlot(int slot_index);

  u64 _pc;
  u64 _sp;
  u64 _span_id;
  u64 _root_span_id;
  volatile u32 _crash_depth;
  int _buffer_pos;
  int _tid;
  u32 _cpu_epoch;
  u32 _wall_epoch;
  u64 _call_trace_id;
  u32 _recording_epoch;
  u32 _misc_flags;
  int _filter_slot_id; // Slot ID for thread filtering
  UnwindFailures _unwind_failures;
  bool _ctx_tls_initialized;
  Context* _ctx_tls_ptr;

  ProfiledThread(int buffer_pos, int tid)
      : ThreadLocalData(), _pc(0), _sp(0), _span_id(0), _root_span_id(0), _crash_depth(0), _buffer_pos(buffer_pos), _tid(tid), _cpu_epoch(0),
        _wall_epoch(0), _call_trace_id(0), _recording_epoch(0), _misc_flags(0), _filter_slot_id(-1), _ctx_tls_initialized(false), _ctx_tls_ptr(nullptr) {};

  void releaseFromBuffer();

public:
  static ProfiledThread *forTid(int tid) { return new ProfiledThread(-1, tid); }
  static ProfiledThread *inBuffer(int buffer_pos) {
    return new ProfiledThread(buffer_pos, 0);
  }

  static void initCurrentThread();
  static void initCurrentThreadWithBuffer(); // Called by signal handler for native threads
  static void initExistingThreads();
  static void cleanupTlsPriming();

  static void release();

  static ProfiledThread *current();
  static ProfiledThread *currentSignalSafe(); // Signal-safe version that never allocates
  static int currentTid();

  // TLS priming status checks
  static bool isTlsPrimingAvailable();
  static bool wasTlsPrimingAttempted();
  
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
   * @param span_id Current trace span ID
   * @param root_span_id Current trace root span ID
   * @return Cached call_trace_id if collapsing is allowed, 0 otherwise
   */
  u64 lookupWallclockCallTraceId(u64 pc, u64 sp, u32 recording_epoch,
                                  u64 span_id, u64 root_span_id) {
    if (_pc == pc && _sp == sp && _span_id == span_id &&
        _root_span_id == root_span_id && _recording_epoch == recording_epoch &&
        _call_trace_id != 0) {
      return _call_trace_id;
    }
    _pc = pc;
    _sp = sp;
    _span_id = span_id;
    _root_span_id = root_span_id;
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

  static void simpleTlsSignalHandler(int signo);

  int filterSlotId() { return _filter_slot_id; }
  void setFilterSlotId(int slotId) { _filter_slot_id = slotId; }
  
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
  
  // context sharing TLS
  inline void markContextTlsInitialized(Context* ctx_ptr) {
    _ctx_tls_ptr = ctx_ptr;
    _ctx_tls_initialized = true;
  }

  inline bool isContextTlsInitialized() {
    return _ctx_tls_initialized;
  }

  inline Context* getContextTlsPtr() {
    return _ctx_tls_ptr;
  }
  
  // Flags
  inline void setJavaThread() {
    _misc_flags |= FLAG_JAVA_THREAD;
  }

  inline bool isJavaThread() const {
    return (_misc_flags & FLAG_JAVA_THREAD) == FLAG_JAVA_THREAD;
  }

private:
  // Atomic flag for signal handler reentrancy protection within the same thread
  // Must be atomic because a signal handler can interrupt normal execution mid-instruction,
  // and both contexts may attempt to enter the critical section. Without atomic exchange(),
  // both could see the flag as false and both would think they successfully entered.
  // The atomic exchange() is uninterruptible, ensuring only one context succeeds.
  bool _in_critical_section{false};
};

#endif // _THREAD_H
