/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "callTraceHashTable.h"
#include "callTraceStorage.h"
#include "counters.h"
#include "os.h"
#include "arch_dd.h"
#include "common.h"
#include <string.h>
#include <signal.h>
#include <pthread.h>

static const u32 INITIAL_CAPACITY = 65536;  // 64K initial table size (matches upstream)
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
  LongHashTable(LongHashTable *prev = nullptr, u32 capacity = 0, bool should_clean = true) 
    : _prev(prev), _padding0(nullptr), _capacity(capacity), _size(0) {
    memset(_padding1, 0, sizeof(_padding1));
    memset(_padding2, 0, sizeof(_padding2));
    if (should_clean) {
      clear();
    }
  }

  static LongHashTable *allocate(LongHashTable *prev, u32 capacity, LinearAllocator* allocator) {
    void *memory = allocator->alloc(getSize(capacity));
    if (memory != nullptr) {
      // Use placement new to invoke constructor in-place with parameters
      // LinearAllocator doesn't zero memory like OS::safeAlloc with anon mmap
      // so we need to explicitly clear the keys and values (should_clean = true)
      LongHashTable *table = new (memory) LongHashTable(prev, capacity, true);
      return table;
    }
    return nullptr;
  }

  LongHashTable *prev() { return _prev; }
  void setPrev(LongHashTable* prev) { _prev = prev; }

  u32 capacity() { return _capacity; }

  u32 size() { return _size; }

  u32 incSize() { return __sync_add_and_fetch(&_size, 1); }

  u64 *keys() { return (u64 *)(this + 1); }

  CallTraceSample *values() { return (CallTraceSample *)(keys() + _capacity); }

  u32 nextSlot(u32 slot) const { return (slot + 1) & (_capacity - 1); }

  void clear() {
    memset(keys(), 0, (sizeof(u64) + sizeof(CallTraceSample)) * _capacity);
    _size = 0;
  }
};

CallTrace CallTraceHashTable::_overflow_trace(false, 1, OVERFLOW_TRACE_ID);

// Static initializer for overflow trace frame
__attribute__((constructor))
static void init_overflow_trace() {
  CallTraceHashTable::_overflow_trace.frames[0] = {BCI_ERROR, LP64_ONLY(0 COMMA) (jmethodID)"storage_overflow"};
}

CallTraceHashTable::CallTraceHashTable() : _allocator(CALL_TRACE_CHUNK), _instance_id(0), _parent_storage(nullptr) {
  // Instance ID will be set externally via setInstanceId()
  
  // Start with initial capacity, allowing expansion as needed
  _table = LongHashTable::allocate(nullptr, INITIAL_CAPACITY, &_allocator);
  _overflow = 0;
}

CallTraceHashTable::~CallTraceHashTable() {
  // LinearAllocator handles all memory cleanup automatically
  // No need to explicitly destroy tables since they're allocated from LinearAllocator
  // Note: No synchronization needed here because CallTraceStorage ensures
  // no new operations can start by nullifying storage pointers first
  _table = nullptr;
}


void CallTraceHashTable::clear() {
  // Wait for all hazard pointers to clear before deallocation to prevent races
  HazardPointer::waitForAllHazardPointersToClear();
  
  // Clear previous chain pointers to prevent traversal during deallocation
  for (LongHashTable *table = _table; table != nullptr; table = table->prev()) {
    LongHashTable *prev_table = table->prev();
    if (prev_table != nullptr) {
      table->setPrev(nullptr);  // Clear link before deallocation
    }
  }
  
  // Now safe to deallocate all memory
  _allocator.clear();
  
  // Reinitialize with fresh table
  _table = LongHashTable::allocate(nullptr, INITIAL_CAPACITY, &_allocator);
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
  void *memory = _allocator.alloc(total_size);
  CallTrace *buf = nullptr;
  if (memory != nullptr) {
    // Use placement new to invoke constructor in-place
    buf = new (memory) CallTrace(truncated, num_frames, trace_id);
    // Do not use memcpy inside signal handler
    for (int i = 0; i < num_frames; i++) {
      buf->frames[i] = frames[i];
    }
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
      return nullptr;
    }
    if (++step >= capacity) {
      return nullptr;
    }
    slot = (slot + step) & (capacity - 1);
  }

  return table->values()[slot].trace;
}

u64 CallTraceHashTable::put(int num_frames, ASGCT_CallFrame *frames,
                          bool truncated, u64 weight) {
  u64 hash = calcHash(num_frames, frames, truncated);

  LongHashTable *table = _table;
  if (table == nullptr) {
    // Table allocation failed or was cleared - drop sample
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
        // Trace is nullptr but hash exists - preparation failed
        u64 recheck_key = __atomic_load_n(&keys[slot], __ATOMIC_ACQUIRE);
        if (recheck_key != hash) {
          continue; // Key was cleared, retry
        }
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

      // Increment size counter for statistics and check for expansion
      u32 new_size = table->incSize();
      u32 capacity = table->capacity();

      // EXPANSION LOGIC: Check if 75% capacity reached after incrementing size
      if (new_size == capacity * 3 / 4) {
        // Allocate new table with double capacity using LinearAllocator
        LongHashTable* new_table = LongHashTable::allocate(table, capacity * 2, &_allocator);
        if (new_table != nullptr) {
          // Atomic table swap - only one thread succeeds
          __atomic_compare_exchange_n(&_table, &table, new_table, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED);
        }
      }

      // Check if trace exists in previous tables to avoid duplication
      CallTrace *trace = nullptr;
      if (table->prev() != nullptr) {
        trace = findCallTrace(table->prev(), hash);
      }
      
      if (trace == nullptr) {
        // Generate unique trace ID: upper 32 bits = instance_id, lower 32 bits = slot
        u64 instance_id = _instance_id;
        u64 trace_id = (instance_id << 32) | slot;
        trace = storeCallTrace(num_frames, frames, truncated, trace_id);
        if (trace == nullptr) {
          // Allocation failure - reset trace first, then clear key
          table->values()[slot].setTrace(nullptr);
          __atomic_thread_fence(__ATOMIC_SEQ_CST);
          __atomic_store_n(&keys[slot], 0, __ATOMIC_RELEASE);
          Counters::increment(CALLTRACE_STORAGE_DROPPED);
          return CallTraceStorage::DROPPED_TRACE_ID;
        }
      }
      
      // Set the actual trace (this changes state from PREPARING to ready)
      table->values()[slot].setTrace(trace);
      return trace->trace_id;
    }

    if (++step >= capacity) {
      // Table overflow - very unlikely with expansion logic
      atomicIncRelaxed(_overflow);
      return OVERFLOW_TRACE_ID;
    }
    // Linear probing with step increment
    slot = (slot + step) & (capacity - 1);
  }
}

void CallTraceHashTable::collect(std::unordered_set<CallTrace *> &traces, std::function<void(CallTrace*)> trace_hook) {
  // Lock-free collection for read-only tables (after atomic swap)
  // No new put() operations can occur, so no synchronization needed
  
  // Collect from all tables in the chain (current and previous tables)
  for (LongHashTable *table = _table; table != nullptr; table = table->prev()) {
    u64 *keys = table->keys();
    CallTraceSample *values = table->values();
    u32 capacity = table->capacity();
    for (u32 slot = 0; slot < capacity; slot++) {
      if (keys[slot] != 0) {
        CallTrace *trace = values[slot].acquireTrace();
        if (trace != nullptr && trace != CallTraceSample::PREPARING) {
          if (trace_hook) {
            trace_hook(trace);  // Call hook first if provided
          }
          traces.insert(trace);
        }
      }
    }
  }
  
  // Handle overflow trace
  if (_overflow > 0) {
    if (trace_hook) {
      trace_hook(&_overflow_trace);  // Call hook for overflow trace too
    }
    traces.insert(&_overflow_trace);
  }
}


void CallTraceHashTable::putWithExistingId(CallTrace* source_trace, u64 weight) {
  // Trace preservation for standby tables (no contention with new puts)
  // This is safe because new put() operations go to the new active table
  
  u64 hash = calcHash(source_trace->num_frames, source_trace->frames, source_trace->truncated);
  
  // First check if trace already exists in any table in the chain
  for (LongHashTable *search_table = _table; search_table != nullptr; search_table = search_table->prev()) {
    CallTrace *existing_trace = findCallTrace(search_table, hash);
    if (existing_trace != nullptr) {
      // Trace already exists in the chain
      return;
    }
  }
  
  LongHashTable *table = _table;
  if (table == nullptr) {
    return; // Table allocation failed
  }
  
  u64 *keys = table->keys();
  u32 capacity = table->capacity();
  u32 slot = hash & (capacity - 1);
  
  // Look for existing entry or empty slot - no locking needed
  while (true) {
    u64 key_value = __atomic_load_n(&keys[slot], __ATOMIC_RELAXED);
    if (key_value == hash) {
      // Found existing entry - just use it (trace already preserved)
      break;
    }
    if (key_value == 0) {
      // Found empty slot - claim it atomically
      u64 expected = 0;
      if (!__atomic_compare_exchange_n(&keys[slot], &expected, hash, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)) {
        // Another thread claimed it, try next slot
        slot = table->nextSlot(slot);
        continue;
      }
      
      // Create a copy of the source trace preserving its exact ID
      const size_t header_size = sizeof(CallTrace) - sizeof(ASGCT_CallFrame);
      const size_t total_size = header_size + source_trace->num_frames * sizeof(ASGCT_CallFrame);
      void *memory = _allocator.alloc(total_size);
      if (memory != nullptr) {
        // Use placement new to invoke constructor in-place
        CallTrace* copied_trace = new (memory) CallTrace(source_trace->truncated, source_trace->num_frames, source_trace->trace_id);
        // memcpy safe since not in signal handler
        memcpy(copied_trace->frames, source_trace->frames, source_trace->num_frames * sizeof(ASGCT_CallFrame));
        table->values()[slot].setTrace(copied_trace);
        Counters::increment(CALLTRACE_STORAGE_BYTES, total_size);
        Counters::increment(CALLTRACE_STORAGE_TRACES);
        
        // Increment table size
        table->incSize();
      } else {
        // Allocation failure - clear the key we claimed
        __atomic_store_n(&keys[slot], 0, __ATOMIC_RELEASE);
      }
      break;
    }
    
    slot = table->nextSlot(slot);
  }
}
