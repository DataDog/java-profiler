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

#include "trackingTable.h"
#include <cstdlib>
#include <cstring>
#include <functional>

TrackingTable::TrackingTable() 
    : _table_size(0), _table_cap(0), _table_max_cap(0), _table(nullptr) {
}

TrackingTable::~TrackingTable() {
  if (_table) {
    free(_table);
  }
}

bool TrackingTable::initialize(int max_capacity) {
  _table_max_cap = max_capacity;
  _table_cap = std::max(2048, _table_max_cap / 8); // Start with 1/8 of max capacity
  _table_size = 0;
  
  _table = (TrackingEntry*)malloc(sizeof(TrackingEntry) * _table_cap);
  if (!_table) {
    return false;
  }
  
  memset(_table, 0, sizeof(TrackingEntry) * _table_cap);
  return true;
}

int TrackingTable::addEntry(const TrackingEntry& entry) {
  if (!_table_lock.tryLockShared()) {
    return -1; // Failed to acquire shared lock
  }

  // Increment _table_size in a thread-safe manner (CAS) and store the new value in idx
  // It bails out if _table_size would overflow _table_cap
  int idx;
  do {
    idx = __atomic_load_n(&_table_size, __ATOMIC_RELAXED);
  } while (idx < _table_cap &&
           !__sync_bool_compare_and_swap(&_table_size, idx, idx + 1));

  if (idx < _table_cap) {
    _table[idx] = entry;
  }

  _table_lock.unlockShared();
  return idx < _table_cap ? idx : -1;
}


void TrackingTable::withExclusiveLock(std::function<void(TrackingEntry*, int&)> operation) {
  _table_lock.lock();
  int size = _table_size; // Convert volatile to non-volatile
  operation(_table, size);
  _table_size = size; // Write back any changes
  _table_lock.unlock();
}

bool TrackingTable::resize(int new_capacity) {
  _table_lock.lock();
  
  if (new_capacity <= _table_cap || new_capacity > _table_max_cap) {
    _table_lock.unlock();
    return false;
  }
  
  TrackingEntry* new_table = (TrackingEntry*)realloc(_table, sizeof(TrackingEntry) * new_capacity);
  if (!new_table) {
    _table_lock.unlock();
    return false;
  }
  
  _table = new_table;
  _table_cap = new_capacity;
  
  _table_lock.unlock();
  return true;
}