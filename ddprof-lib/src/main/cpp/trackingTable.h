/*
 * Copyright 2025 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _TRACKINGTABLE_H
#define _TRACKINGTABLE_H

#include "arch_dd.h"
#include "context.h"
#include "event.h"
#include "spinLock.h"
#include <jvmti.h>
#include <map>
#include <functional>

typedef struct TrackingEntry {
  jweak ref;
  AllocEvent alloc;
  double skipped;
  u32 call_trace_id;
  jint tid;
  jlong time;
  jlong age;
  Context ctx;
} TrackingEntry;

class TrackingTable {
private:
  SpinLock _table_lock;
  volatile int _table_size;
  int _table_cap;
  int _table_max_cap;
  TrackingEntry *_table;

public:
  TrackingTable();
  ~TrackingTable();

  // Initialize table with given capacity
  bool initialize(int max_capacity);

  // Add an entry to the table (called by track())
  // Returns the index where the entry was added, or -1 if table is full
  int addEntry(const TrackingEntry& entry);

  // Thread-safe counting of call trace references using EXCLUSIVE lock
  
  // Direct callback approach: no maps, direct call trace marking
  template<typename CallbackFn>
  void markLiveCallTraces(CallbackFn callback) {
    _table_lock.lock(); // EXCLUSIVE lock - prevents race conditions with concurrent writes
    
    for (int i = 0; i < _table_size; i++) {
      if (_table[i].ref != nullptr && _table[i].call_trace_id != 0) {
        callback(_table[i].call_trace_id);
      }
    }
    
    _table_lock.unlock();
  }

  // Access table for cleanup and flushing operations
  void withExclusiveLock(std::function<void(TrackingEntry*, int&)> operation);

  // Resize table capacity
  bool resize(int new_capacity);

  // Get current metrics
  int size() const { return _table_size; }
  int capacity() const { return _table_cap; }
  int maxCapacity() const { return _table_max_cap; }
};

#endif // _TRACKINGTABLE_H