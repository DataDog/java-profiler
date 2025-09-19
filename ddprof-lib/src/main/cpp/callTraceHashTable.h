/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CALLTRACEHASHTABLE_H
#define _CALLTRACEHASHTABLE_H

#include "arch_dd.h"
#include "linearAllocator.h"
// SpinLock removed - synchronization handled at CallTraceStorage level
#include "vmEntry.h"
#include <unordered_set>

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
  u64 _instance_id;  // 64-bit instance ID for this hash table (set externally)

  LinearAllocator _allocator;
  LongHashTable *_current_table;
  volatile u64 _overflow;

  u64 calcHash(int num_frames, ASGCT_CallFrame *frames, bool truncated);
  CallTrace *storeCallTrace(int num_frames, ASGCT_CallFrame *frames,
                            bool truncated, u64 trace_id);
  CallTrace *findCallTrace(LongHashTable *table, u64 hash);

public:
  CallTraceHashTable();
  ~CallTraceHashTable();

  void clear();
  void collect(std::unordered_set<CallTrace *> &traces);
  void collectAndCopySelective(std::unordered_set<CallTrace *> &traces, const std::unordered_set<u64> &trace_ids_to_preserve, CallTraceHashTable* target);

  u64 put(int num_frames, ASGCT_CallFrame *frames, bool truncated, u64 weight);
  void putWithExistingId(CallTrace* trace, u64 weight);
  void setInstanceId(u64 instance_id) { _instance_id = instance_id; }
};

#endif // _CALLTRACEHASHTABLE_H
