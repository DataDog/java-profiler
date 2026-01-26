/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CALLTRACEHASHTABLE_H
#define _CALLTRACEHASHTABLE_H

#include "arch.h"
#include "linearAllocator.h"
#include "vmEntry.h"
#include <unordered_set>
#include <atomic>
#include <functional>

class LongHashTable;

struct CallTrace {
  bool truncated;
  int num_frames;
  u64 trace_id;  // 64-bit for JFR constant pool compatibility
  ASGCT_CallFrame frames[1];

  CallTrace(bool truncated, int num_frames, u64 trace_id) 
    : truncated(truncated), num_frames(num_frames), trace_id(trace_id) {
  }
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

// Forward declaration for circular dependency
class CallTraceStorage;

class CallTraceHashTable {
public:
  static CallTrace _overflow_trace;

private:
  u64 _instance_id;  // 64-bit instance ID for this hash table (set externally)
  CallTraceStorage* _parent_storage;  // Parent storage for RefCountGuard access

  LinearAllocator _allocator;
  
  // Single large pre-allocated table - no expansion needed!
  LongHashTable* _table;  // Simple pointer, no atomics needed
  
  volatile u64 _overflow;

  u64 calcHash(int num_frames, ASGCT_CallFrame *frames, bool truncated);
  CallTrace *storeCallTrace(int num_frames, ASGCT_CallFrame *frames,
                            bool truncated, u64 trace_id);
  CallTrace *findCallTrace(LongHashTable *table, u64 hash);
  

public:
  CallTraceHashTable();
  ~CallTraceHashTable();

  void clear();

  /**
   * Resets the hash table structure but defers memory deallocation.
   * Returns a ChunkList containing the detached memory chunks.
   * The caller must call LinearAllocator::freeChunks() on the returned
   * ChunkList after processing is complete.
   *
   * This is used to fix use-after-free in processTraces(): the table
   * structure is reset immediately (allowing rotation), but trace memory
   * remains valid until the processor finishes accessing it.
   */
  ChunkList clearTableOnly();

  void collect(std::unordered_set<CallTrace *> &traces, std::function<void(CallTrace*)> trace_hook = nullptr);

  u64 put(int num_frames, ASGCT_CallFrame *frames, bool truncated, u64 weight);
  void putWithExistingId(CallTrace* trace, u64 weight);  // For standby tables with no contention
  void setInstanceId(u64 instance_id) { _instance_id = instance_id; }
  void setParentStorage(CallTraceStorage* storage) { _parent_storage = storage; }
};

#endif // _CALLTRACEHASHTABLE_H
