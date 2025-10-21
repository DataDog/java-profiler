/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _THREAD_H
#define _THREAD_H

#include "os_dd.h"
#include "threadLocalData.h"
#include "unwindStats.h"
#include <atomic>
#include <cstdint>
#include <jvmti.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <vector>

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
  static int _buffer_size;
  static std::atomic<int> _running_buffer_pos;
  static std::vector<ProfiledThread *> _buffer;

  static void initTLSKey();
  static void doInitTLSKey();
  static inline void freeKey(void *key);
  static void initCurrentThreadWithBuffer();
  static void doInitExistingThreads();
  static void prepareBuffer(int size);
  static void *delayedUninstallUSR1(void *unused);

  u64 _pc;
  u64 _span_id;
  volatile u32 _crash_depth;
  int _buffer_pos;
  int _tid;
  u32 _cpu_epoch;
  u32 _wall_epoch;
  u64 _call_trace_id;
  u32 _recording_epoch;
  int _filter_slot_id; // Slot ID for thread filtering
  UnwindFailures _unwind_failures;

  ProfiledThread(int buffer_pos, int tid)
      : ThreadLocalData(), _pc(0), _span_id(0), _crash_depth(0), _buffer_pos(buffer_pos), _tid(tid), _cpu_epoch(0),
        _wall_epoch(0), _call_trace_id(0), _recording_epoch(0), _filter_slot_id(-1) {};

  void releaseFromBuffer();

public:
  static ProfiledThread *forTid(int tid) { return new ProfiledThread(-1, tid); }
  static ProfiledThread *inBuffer(int buffer_pos) {
    return new ProfiledThread(buffer_pos, 0);
  }

  static void initCurrentThread();
  static void initExistingThreads();

  static void release();

  static ProfiledThread *current();
  static int currentTid();

  inline int tid() { return _tid; }

  inline u64 noteCPUSample(u32 recording_epoch) {
    _recording_epoch = recording_epoch;
    return ++_cpu_epoch;
  }

  u64 lookupWallclockCallTraceId(u64 pc, u32 recording_epoch, u64 span_id) {
    if (_wall_epoch == _cpu_epoch && _pc == pc && _span_id == span_id &&
        _recording_epoch == recording_epoch && _call_trace_id != 0) {
      return _call_trace_id;
    }
    _wall_epoch = _cpu_epoch;
    _pc = pc;
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

  static void signalHandler(int signo, siginfo_t *siginfo, void *ucontext);

  int filterSlotId() { return _filter_slot_id; }
  void setFilterSlotId(int slotId) { _filter_slot_id = slotId; }
  
  // Signal handler reentrancy protection
  bool tryEnterCriticalSection() { 
    return !_in_critical_section.exchange(true, std::memory_order_acquire); 
  }
  void exitCriticalSection() { 
    _in_critical_section.store(false, std::memory_order_release); 
  }
  
  // Hazard pointer management for lock-free memory reclamation (signal-safe)
  // 
  // How hazard pointers work:
  // 1. Before accessing a shared data structure, threads register a "hazard pointer" to it
  // 2. When deleting the structure, the deleter waits for all hazard pointers to clear
  // 3. This ensures no thread accesses freed memory, even in signal handler contexts
  // 4. Alternative to locks that avoids malloc/deadlock issues in signal handlers
  //
  // Currently used only in CallTraceStorage for safe table swapping during profiling
  void setHazardPointer(void* instance, void* hazard_pointer, int hazard_slot) {
    _hazard_instance = instance;
    _hazard_pointer = hazard_pointer;
    _hazard_slot = hazard_slot;
  }
  void* getHazardInstance() { return _hazard_instance; }
  void* getHazardPointer() { return _hazard_pointer; }
  int getHazardSlot() { return _hazard_slot; }
  
private:
  // Atomic flag for signal handler reentrancy protection within the same thread
  // Must be atomic because a signal handler can interrupt normal execution mid-instruction,
  // and both contexts may attempt to enter the critical section. Without atomic exchange(),
  // both could see the flag as false and both would think they successfully entered.
  // The atomic exchange() is uninterruptible, ensuring only one context succeeds.
  std::atomic<bool> _in_critical_section{false};
  
  // Hazard pointer instance for signal-safe access (not atomic since only accessed by same thread)
  void* _hazard_instance{nullptr};
  void* _hazard_pointer{nullptr};
  int _hazard_slot{-1};
};

#endif // _THREAD_H
