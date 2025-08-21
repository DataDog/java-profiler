/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "callTraceHashTable.h"
#include "callTraceStorage.h"
#include "counters.h"
#include "os.h"
#include "arch_dd.h"
#include <string.h>

static const u32 INITIAL_CAPACITY = 65536;
static const u32 CALL_TRACE_CHUNK = 8 * 1024 * 1024;
static const u64 OVERFLOW_TRACE_ID = 0x7fffffffffffffffULL;  // Max 64-bit signed value

// Define the sentinel value for CallTraceSample
CallTrace* const CallTraceSample::PREPARING = reinterpret_cast<CallTrace*>(1);

class LongHashTable {
private:
  LongHashTable *_prev;
  void *_padding0;
  u32 _capacity;
  u32 _padding1[15];
  volatile u32 _size;
  u32 _padding2[15];

  static size_t getSize(u32 capacity) {
    size_t size = sizeof(LongHashTable) +
                  (sizeof(u64) + sizeof(CallTraceSample)) * capacity;
    return (size + OS::page_mask) & ~OS::page_mask;
  }

public:
  LongHashTable() : _prev(NULL), _padding0(NULL), _capacity(0), _size(0) {
    memset(_padding1, 0, sizeof(_padding1));
    memset(_padding2, 0, sizeof(_padding2));
  }

  static LongHashTable *allocate(LongHashTable *prev, u32 capacity) {
    LongHashTable *table = (LongHashTable *)OS::safeAlloc(getSize(capacity));
    if (table != NULL) {
      table->_prev = prev;
      table->_capacity = capacity;
      // The reset is not useful with the anon mmap setting the memory is
      // zeroed. However this silences a false positive and should not have a
      // performance impact.
      table->clear();
    }
    return table;
  }

  LongHashTable *destroy() {
    LongHashTable *prev = _prev;
    OS::safeFree(this, getSize(_capacity));
    return prev;
  }

  LongHashTable *prev() { return _prev; }

  u32 capacity() { return _capacity; }

  u32 size() { return _size; }

  u32 incSize() { return __sync_add_and_fetch(&_size, 1); }

  u64 *keys() { return (u64 *)(this + 1); }

  CallTraceSample *values() { return (CallTraceSample *)(keys() + _capacity); }

  void clear() {
    memset(keys(), 0, (sizeof(u64) + sizeof(CallTraceSample)) * _capacity);
    _size = 0;
  }
};

CallTrace CallTraceHashTable::_overflow_trace = {false, 1, OVERFLOW_TRACE_ID, {BCI_ERROR, LP64_ONLY(0 COMMA) (jmethodID)"storage_overflow"}};

CallTraceHashTable::CallTraceHashTable() : _allocator(CALL_TRACE_CHUNK) {
  _instance_id = 0;  // Will be set externally via setInstanceId()
  _current_table = LongHashTable::allocate(NULL, INITIAL_CAPACITY);
  _overflow = 0;
}

CallTraceHashTable::~CallTraceHashTable() {
  while (_current_table != NULL) {
    _current_table = _current_table->destroy();
  }
}

void CallTraceHashTable::clear() {
  if (_current_table != NULL) {
    while (_current_table->prev() != NULL) {
      _current_table = _current_table->destroy();
    }
    _current_table->clear();
  }
  _allocator.clear();
  _overflow = 0;
}

// Adaptation of MurmurHash64A by Austin Appleby
u64 CallTraceHashTable::calcHash(int num_frames, ASGCT_CallFrame *frames,
                               bool truncated) {
  const u64 M = 0xc6a4a7935bd1e995ULL;
  const int R = 47;

  int len = num_frames * sizeof(ASGCT_CallFrame);
  u64 h = len * M * (truncated ? 1 : 2);

  const u64 *data = (const u64 *)frames;
  const u64 *end = data + len / sizeof(u64);

  while (data != end) {
    u64 k = *data++;
    k *= M;
    k ^= k >> R;
    k *= M;
    h ^= k;
    h *= M;
  }

  if (len & 4) {
    h ^= *(u32 *)data;
    h *= M;
  }

  h ^= h >> R;
  h *= M;
  h ^= h >> R;

  return h;
}

CallTrace *CallTraceHashTable::storeCallTrace(int num_frames,
                                            ASGCT_CallFrame *frames,
                                            bool truncated, u64 trace_id) {
  const size_t header_size = sizeof(CallTrace) - sizeof(ASGCT_CallFrame);
  const size_t total_size = header_size + num_frames * sizeof(ASGCT_CallFrame);
  CallTrace *buf = (CallTrace *)_allocator.alloc(total_size);
  if (buf != NULL) {
    buf->num_frames = num_frames;
    // Do not use memcpy inside signal handler
    for (int i = 0; i < num_frames; i++) {
      buf->frames[i] = frames[i];
    }
    buf->truncated = truncated;
    buf->trace_id = trace_id;
    Counters::increment(CALLTRACE_STORAGE_BYTES, total_size);
    Counters::increment(CALLTRACE_STORAGE_TRACES);
  }
  return buf;
}

CallTrace *CallTraceHashTable::findCallTrace(LongHashTable *table, u64 hash) {
  u64 *keys = table->keys();
  u32 capacity = table->capacity();
  u32 slot = hash & (capacity - 1);
  u32 step = 0;

  while (keys[slot] != hash) {
    if (keys[slot] == 0) {
      return NULL;
    }
    if (++step >= capacity) {
      return NULL;
    }
    slot = (slot + step) & (capacity - 1);
  }

  return table->values()[slot].trace;
}

u64 CallTraceHashTable::put(int num_frames, ASGCT_CallFrame *frames,
                          bool truncated, u64 weight) {
  // Synchronization is now handled at CallTraceStorage facade level
  
  u64 hash = calcHash(num_frames, frames, truncated);

  LongHashTable *table = _current_table;
  if (table == NULL) {
    // Table allocation failed or was cleared - drop sample
    // This could be: 1) Initial allocation failure, 2) Use-after-destruction during shutdown
    Counters::increment(CALLTRACE_STORAGE_DROPPED);
    return CallTraceStorage::DROPPED_TRACE_ID;
  }
  
  u64 *keys = table->keys();
  u32 capacity = table->capacity();
  u32 slot = hash & (capacity - 1);
  u32 step = 0;
  while (true) {
    u64 key_value = __atomic_load_n(&keys[slot], __ATOMIC_RELAXED);
    if (key_value == hash) { 
      // Hash matches - wait for the preparing thread to complete
      CallTrace* current_trace = table->values()[slot].acquireTrace();
      
      // If another thread is preparing this slot, wait for completion
      if (current_trace == CallTraceSample::PREPARING) {
        // Wait for the preparing thread to complete, with timeout
        int wait_cycles = 0;
        const int MAX_WAIT_CYCLES = 1000; // ~1000 cycles should be enough for allocation
        
        do {
          // Brief spin-wait to allow preparing thread to complete
          for (volatile int i = 0; i < 10; i++) {
            spinPause(); // Architecture-specific pause instruction
          }
          
          current_trace = table->values()[slot].acquireTrace();
          wait_cycles++;
          
          // Check if key was cleared (preparation failed)
          if (__atomic_load_n(&keys[slot], __ATOMIC_RELAXED) != hash) {
            break; // Key cleared, restart search
          }
          
        } while (current_trace == CallTraceSample::PREPARING && wait_cycles < MAX_WAIT_CYCLES);
        
        // If still preparing after timeout, something is wrong - continue search
        if (current_trace == CallTraceSample::PREPARING) {
          continue;
        }
      }
      
      // Check final state after waiting
      if (current_trace != nullptr && current_trace != CallTraceSample::PREPARING) {
        // Trace is ready, use it
        return current_trace->trace_id;
      } else {
        // Trace is NULL but hash exists - this indicates preparation failed
        // Read the key again to confirm it's still there
        u64 recheck_key = __atomic_load_n(&keys[slot], __ATOMIC_ACQUIRE);
        if (recheck_key != hash) {
          // Key was cleared by the preparing thread, retry the search
          continue;
        }
        // Key still exists but trace is null - preparation failed
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return CallTraceStorage::DROPPED_TRACE_ID;
      }
    }
    if (key_value == 0) {
      u64 expected = 0;
      if (!__atomic_compare_exchange_n(&keys[slot], &expected, hash, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)) {
        continue; // another thread claimed it, go to next slot
      }
      
      // Mark the slot as being prepared so other threads know to wait
      if (!table->values()[slot].markPreparing()) {
        // Failed to mark as preparing (shouldn't happen), clear key with full barrier and retry
        __atomic_thread_fence(__ATOMIC_SEQ_CST);
        __atomic_store_n(&keys[slot], 0, __ATOMIC_RELEASE);
        continue;
      }
      
      // Increment the table size, and if the load factor exceeds 0.75, reserve
      // a new table
      u32 current_size = table->incSize();
      if (current_size == capacity * 3 / 4) {
        LongHashTable *new_table = LongHashTable::allocate(table, capacity * 2);
        if (new_table != NULL) {
          // Use atomic CAS to safely update _current_table
          __atomic_compare_exchange_n(&_current_table, &table, new_table, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED);
        }
      }

      // Migrate from a previous table to save space
      CallTrace *trace =
          table->prev() == NULL ? NULL : findCallTrace(table->prev(), hash);
      if (trace == NULL) {
        // Generate unique trace ID: upper 32 bits = instance_id, lower 32 bits = slot
        // 64-bit provides massive collision space and JFR constant pool compatibility
        u64 trace_id = (_instance_id << 32) | slot;
        trace = storeCallTrace(num_frames, frames, truncated, trace_id);
        if (trace == NULL) {
          // Allocation failure - reset trace first, then clear key with proper memory ordering
          table->values()[slot].setTrace(nullptr);
          // Use full memory barrier to ensure trace=null is visible before key=0
          __atomic_thread_fence(__ATOMIC_SEQ_CST);
          __atomic_store_n(&keys[slot], 0, __ATOMIC_RELEASE);
          Counters::increment(CALLTRACE_STORAGE_DROPPED);
          return CallTraceStorage::DROPPED_TRACE_ID;
        }
      }
      // Note: For migrated traces, we preserve their original trace_id from when they were first created
      // Set the actual trace (this changes state from PREPARING to ready)
      table->values()[slot].setTrace(trace);
      
      // clear the slot in the prev table such it is not written out to constant
      // pool multiple times
      LongHashTable *prev_table = table->prev();
      if (prev_table != NULL) {
        __atomic_store_n(&prev_table->keys()[slot], 0, __ATOMIC_RELEASE);
      }
      
      // Return immediately since we just created/set up this trace
      return trace->trace_id;
    }

    if (++step >= capacity) {
      // Very unlikely case of a table overflow
      atomicInc(_overflow);
      return OVERFLOW_TRACE_ID;
    }
    // Improved version of linear probing
    slot = (slot + step) & (capacity - 1);
  }
}

void CallTraceHashTable::collect(std::unordered_set<CallTrace *> &traces) {
  // Simple collection without copying - used for lock-free processing
  for (LongHashTable *table = _current_table; table != NULL; table = table->prev()) {
    u64 *keys = table->keys();
    CallTraceSample *values = table->values();
    u32 capacity = table->capacity();
    for (u32 slot = 0; slot < capacity; slot++) {
      if (keys[slot] != 0) {
        CallTrace *trace = values[slot].acquireTrace();
        if (trace != NULL) {
          traces.insert(trace);
        }
      }
    }
  }
  
  // Handle overflow trace
  if (_overflow > 0) {
    traces.insert(&_overflow_trace);
  }
}

void CallTraceHashTable::collectAndCopySelective(std::unordered_set<CallTrace *> &traces, 
                                                  const std::unordered_set<u64> &trace_ids_to_preserve, 
                                                  CallTraceHashTable* target) {
  for (LongHashTable *table = _current_table; table != NULL; table = table->prev()) {
    u64 *keys = table->keys();
    CallTraceSample *values = table->values();
    u32 capacity = table->capacity();
    for (u32 slot = 0; slot < capacity; slot++) {
      if (keys[slot] != 0) {
        CallTrace *trace = values[slot].acquireTrace();
        if (trace != NULL) {
          // Always collect for JFR output - trace contains its own ID
          traces.insert(trace);
          
          // Copy to target if this trace should be preserved, preserving the original trace ID
          if (trace_ids_to_preserve.find(trace->trace_id) != trace_ids_to_preserve.end()) {
            target->putWithExistingId(trace, 1);
          }
        }
      }
    }
  }
  
  // Handle overflow trace
  if (_overflow > 0) {
    traces.insert(&_overflow_trace);
    if (trace_ids_to_preserve.find(OVERFLOW_TRACE_ID) != trace_ids_to_preserve.end()) {
      // Copy overflow trace to target - it's a static trace so just increment overflow counter
      atomicInc(target->_overflow);
    }
  }
}

void CallTraceHashTable::putWithExistingId(CallTrace* source_trace, u64 weight) {
  // Synchronization is now handled at CallTraceStorage facade level
  
  u64 hash = calcHash(source_trace->num_frames, source_trace->frames, source_trace->truncated);
  
  LongHashTable *table = _current_table;
  if (table == NULL) {
    // Table allocation failed or was cleared - drop sample
    return;
  }
  
  u64 *keys = table->keys();
  u32 capacity = table->capacity();
  u32 slot = hash & (capacity - 1);
  
  // Look for existing entry or empty slot
  while (true) {
    u64 key_value = __atomic_load_n(&keys[slot], __ATOMIC_RELAXED);
    if (key_value == hash) {
      // Found existing entry - just use it
      break;
    }
    if (key_value == 0) {
      // Found empty slot - claim it
      u64 expected = 0;
      if (!__atomic_compare_exchange_n(&keys[slot], &expected, hash, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)) {
        continue; // another thread claimed it, try next slot
      }
      
      // Create a copy of the source trace preserving its exact ID
      const size_t header_size = sizeof(CallTrace) - sizeof(ASGCT_CallFrame);
      const size_t total_size = header_size + source_trace->num_frames * sizeof(ASGCT_CallFrame);
      CallTrace* copied_trace = (CallTrace*)_allocator.alloc(total_size);
      if (copied_trace != NULL) {
        copied_trace->truncated = source_trace->truncated;
        copied_trace->num_frames = source_trace->num_frames;
        copied_trace->trace_id = source_trace->trace_id; // Preserve exact trace ID
        // Safe to use memcpy since this is not called from signal handler
        memcpy(copied_trace->frames, source_trace->frames, source_trace->num_frames * sizeof(ASGCT_CallFrame));
        table->values()[slot].setTrace(copied_trace);
        Counters::increment(CALLTRACE_STORAGE_BYTES, total_size);
        Counters::increment(CALLTRACE_STORAGE_TRACES);
      } else {
        // Allocation failure - clear the key we claimed and return
        __atomic_store_n(&keys[slot], 0, __ATOMIC_RELEASE);
        return;
      }
      
      // Check if we need to expand the table
      u32 current_size = table->incSize();
      if (current_size == capacity * 3 / 4) {
        LongHashTable *new_table = LongHashTable::allocate(table, capacity * 2);
        if (new_table != NULL) {
          // Use atomic CAS to safely update _current_table
          __atomic_compare_exchange_n(&_current_table, &table, new_table, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED);
        }
      }
      break;
    }
    
    slot = (slot + 1) & (capacity - 1);
  }
}
