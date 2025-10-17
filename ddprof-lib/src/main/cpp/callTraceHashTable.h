/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CALLTRACEHASHTABLE_H
#define _CALLTRACEHASHTABLE_H

#include "arch_dd.h"
#include "linearAllocator.h"
#include "spinLock.h"
#include "vmEntry.h"
#include <unordered_set>
#include <atomic>

class LongHashTable;

struct CallTrace {
  bool truncated;
  int num_frames;
  u64 trace_id;  // 64-bit for JFR constant pool compatibility
  ASGCT_CallFrame frames[1];
};

struct CallTraceSample {
  CallTrace *trace;

  // Sentinel value to indicate slot is being prepared
  static CallTrace* const PREPARING;

  CallTrace *acquireTrace() {
    return __atomic_load_n(&trace, __ATOMIC_ACQUIRE);
  }

  void setTrace(CallTrace *value) {
    __atomic_store_n(&trace, value, __ATOMIC_RELEASE);
  }
  
  bool markPreparing() {
    CallTrace* expected = nullptr;
    return __atomic_compare_exchange_n(&trace, &expected, PREPARING, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED);
  }
  
  bool isPreparing() {
    return acquireTrace() == PREPARING;
  }
};

class CallTraceHashTable {
private:
  static CallTrace _overflow_trace;
  std::atomic<u64> _instance_id;  // 64-bit instance ID for this hash table (set externally)

  LinearAllocator _allocator;
  
  // Single large pre-allocated table - no expansion needed!
  LongHashTable* _table;  // Simple pointer, no atomics needed
  
  volatile u64 _overflow;
  
  // SpinLock for put() vs collect() synchronization
  // Shared locks for put() (multiple readers), exclusive lock for collect()
  SpinLock _access_lock;

  u64 calcHash(int num_frames, ASGCT_CallFrame *frames, bool truncated);
  CallTrace *storeCallTrace(int num_frames, ASGCT_CallFrame *frames,
                            bool truncated, u64 trace_id);
  CallTrace *findCallTrace(LongHashTable *table, u64 hash);
  

public:
  CallTraceHashTable();
  ~CallTraceHashTable();

  void clear();
  void collect(std::unordered_set<CallTrace *> &traces);
  void collectLockFree(std::unordered_set<CallTrace *> &traces);  // For read-only tables after atomic swap

  u64 put(int num_frames, ASGCT_CallFrame *frames, bool truncated, u64 weight);
  void putWithExistingId(CallTrace* trace, u64 weight);
  void putWithExistingIdLockFree(CallTrace* trace, u64 weight);  // For standby tables with no contention
  void setInstanceId(u64 instance_id) { _instance_id.store(instance_id, std::memory_order_release); }
};

#endif // _CALLTRACEHASHTABLE_H
