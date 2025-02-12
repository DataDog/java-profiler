/*
 * Copyright The async-profiler authors
 * SPDX-License-Identifier: Apache-2.0
 */

#include "callTraceStorage.h"
#include "counters.h"
#include "os.h"
#include <string.h>

#define COMMA ,

static const u32 INITIAL_CAPACITY = 65536;
static const u32 CALL_TRACE_CHUNK = 8 * 1024 * 1024;
static const u32 OVERFLOW_TRACE_ID = 0x7fffffff;

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

CallTrace CallTraceStorage::_overflow_trace = {false, 1, {BCI_ERROR, LP64_ONLY(0 COMMA) (jmethodID)"storage_overflow"}};

CallTraceStorage::CallTraceStorage() : _allocator(CALL_TRACE_CHUNK), _lock(0) {
  _current_table = LongHashTable::allocate(NULL, INITIAL_CAPACITY);
  _overflow = 0;
}

CallTraceStorage::~CallTraceStorage() {
  while (_current_table != NULL) {
    _current_table = _current_table->destroy();
  }
}

void CallTraceStorage::clear() {
  _lock.lock();
  while (_current_table->prev() != NULL) {
    _current_table = _current_table->destroy();
  }
  _current_table->clear();
  _allocator.clear();
  _overflow = 0;
  Counters::set(CALLTRACE_STORAGE_BYTES, 0);
  Counters::set(CALLTRACE_STORAGE_TRACES, 0);
  _lock.unlock();
}

void CallTraceStorage::collectTraces(std::map<u32, CallTrace *> &map) {
  for (LongHashTable *table = _current_table; table != NULL;
       table = table->prev()) {
    u64 *keys = table->keys();
    CallTraceSample *values = table->values();
    u32 capacity = table->capacity();

    for (u32 slot = 0; slot < capacity; slot++) {
      if (keys[slot] != 0 && loadAcquire(values[slot].samples) != 0) {
        // Reset samples to avoid duplication of call traces between JFR chunks
        values[slot].samples = 0;
        CallTrace *trace = values[slot].acquireTrace();
        if (trace != NULL) {
          map[capacity - (INITIAL_CAPACITY - 1) + slot] = trace;
        }
      }
    }
  }
  if (_overflow > 0) {
    map[OVERFLOW_TRACE_ID] = &_overflow_trace;
  }
}

// Adaptation of MurmurHash64A by Austin Appleby
u64 CallTraceStorage::calcHash(int num_frames, ASGCT_CallFrame *frames,
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

CallTrace *CallTraceStorage::storeCallTrace(int num_frames,
                                            ASGCT_CallFrame *frames,
                                            bool truncated) {
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
    Counters::increment(CALLTRACE_STORAGE_BYTES, total_size);
    Counters::increment(CALLTRACE_STORAGE_TRACES);
  }
  return buf;
}

CallTrace *CallTraceStorage::findCallTrace(LongHashTable *table, u64 hash) {
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

u32 CallTraceStorage::put(int num_frames, ASGCT_CallFrame *frames,
                          bool truncated, u64 weight) {
  // Currently, CallTraceStorage is a singleton used globally in Profiler and
  // therefore start-stop operation requires data structures cleanup. This
  // cleanup may and will race this method and the racing can cause all sorts of
  // trouble. Unfortunately, this code running in a signal handler we can not
  // just wait till the cleanup is finished and must drop samples instead.
  if (!_lock.tryLockShared()) {
    // FIXME: take proper snapshot of the data instead of dropping samples
    return 0;
  }

  u64 hash = calcHash(num_frames, frames, truncated);

  LongHashTable *table = _current_table;
  u64 *keys = table->keys();
  u32 capacity = table->capacity();
  u32 slot = hash & (capacity - 1);
  u32 step = 0;
  while (true) {
    u64 key_value = __atomic_load_n(&keys[slot], __ATOMIC_RELAXED);
    if (key_value == hash) { // Hash matches, exit the loop
      break;
    }
    if (key_value == 0) {
      if (!__sync_bool_compare_and_swap(&keys[slot], 0, hash)) {
        continue; // another thread claimed it, go to next slot
      }
      // Increment the table size, and if the load factor exceeds 0.75, reserve
      // a new table
      if (table->incSize() == capacity * 3 / 4) {
        LongHashTable *new_table = LongHashTable::allocate(table, capacity * 2);
        if (new_table != NULL) {
          __sync_bool_compare_and_swap(&_current_table, table, new_table);
        }
      }

      // Migrate from a previous table to save space
      CallTrace *trace =
          table->prev() == NULL ? NULL : findCallTrace(table->prev(), hash);
      if (trace == NULL) {
        trace = storeCallTrace(num_frames, frames, truncated);
      }
      table->values()[slot].setTrace(trace);

      // clear the slot in the prev table such it is not written out to constant
      // pool multiple times
      LongHashTable *prev_table = table->prev();
      if (prev_table != NULL) {
        prev_table->keys()[slot] = 0;
      }
      break;
    }

    if (++step >= capacity) {
      // Very unlikely case of a table overflow
      atomicInc(_overflow);
      _lock.unlockShared();
      return OVERFLOW_TRACE_ID;
    }
    // Improved version of linear probing
    slot = (slot + step) & (capacity - 1);
  }

  CallTraceSample &s = table->values()[slot];
  atomicInc(s.samples);
  atomicInc(s.counter, weight);

  _lock.unlockShared();
  return capacity - (INITIAL_CAPACITY - 1) + slot;
}
