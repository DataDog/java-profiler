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
  static constexpr double LOAD_RATIO = 3.0 / 4.0;

public:
  static CallTrace _overflow_trace;

private:
  std::atomic<u64> _instance_id;  // 64-bit instance ID for this hash table - atomic for thread-safe access
  CallTraceStorage* _parent_storage;  // Parent storage for RefCountGuard access

  LinearAllocator _allocator;
  
  // Expandable hash table; put() doubles capacity when fill reaches 75%.
  // Memory-ordering protocol:
  //   - ACQ_REL CAS in put() when installing the expanded table
  //   - RELEASE store in clearTableOnly() when resetting to a fresh table
  //   - ACQUIRE loads in collect(), put(), and putWithExistingId()
  // Required for correct visibility on weakly-ordered architectures (aarch64).
  LongHashTable* _table;
  
  volatile u64 _overflow;

  u64 calcHash(int num_frames, ASGCT_CallFrame *frames, bool truncated);
  CallTrace *storeCallTrace(int num_frames, ASGCT_CallFrame *frames,
                            bool truncated, u64 trace_id);
  CallTrace *findCallTrace(LongHashTable *table, u64 hash);
  void decrementCounters();
  
  void expandTableIfNeeded(LongHashTable* table, u32 size);

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
  void setInstanceId(u64 instance_id) {
    // Use atomic store with RELEASE ordering to ensure visibility across threads
    _instance_id.store(instance_id, std::memory_order_release);
  }
  void setParentStorage(CallTraceStorage* storage) { _parent_storage = storage; }
};

#endif // _CALLTRACEHASHTABLE_H
