/*
 * Copyright 2020 Andrei Pangin
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

#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include "counters.h"
#include <map>
#include <stddef.h>
#include <stdlib.h>

#define ROW_BITS 7
#define ROWS (1 << ROW_BITS)
#define CELLS 3
#define TABLE_CAPACITY (ROWS * CELLS)

struct DictTable;

struct DictRow {
  char *keys[CELLS];
  DictTable *next;
};

struct DictTable {
  DictRow rows[ROWS];
  unsigned int base_index;

  unsigned int index(int row, int col) {
    return base_index + (col << ROW_BITS) + row;
  }
};

// Append-only concurrent hash table based on multi-level arrays
class Dictionary {
private:
  DictTable *_table;
  int _id;
  volatile unsigned int _base_index;
  volatile int _size;

  static void clear(DictTable *table, int id);

  static unsigned int hash(const char *key, size_t length);

  static void collect(std::map<unsigned int, const char *> &map,
                      DictTable *table);

  unsigned int lookup(const char *key, size_t length, bool for_insert,
                      unsigned int sentinel);

public:
  Dictionary() : Dictionary(0) {}
  Dictionary(int id) : _id(id) {
    _table = (DictTable *)calloc(1, sizeof(DictTable));
    Counters::set(DICTIONARY_PAGES, 1, id);
    Counters::set(DICTIONARY_BYTES, sizeof(DictTable), id);
    _table->base_index = _base_index = 1;
    _size = 0;
  }
  ~Dictionary();

  void clear();

  bool         check(const char* key);
  // NOT signal-safe: the inserting lookup overloads call malloc/calloc on miss
  // (see allocateKey and the calloc in dictionary.cpp). Signal handlers must use
  // bounded_lookup(key, length, 0) instead, which never inserts and returns
  // INT_MAX on miss.
  unsigned int lookup(const char *key);
  unsigned int lookup(const char *key, size_t length);
  unsigned int bounded_lookup(const char *key, size_t length, int size_limit);

  void collect(std::map<unsigned int, const char *> &map);

  int  counterId() const { return _id; }
  void setCounterId(int id) { _id = id; }
};

// Double-buffered wrapper: signal-handler-safe writers always target the active
// buffer; the dump thread reads from the standby buffer after rotate().
//
// Lifecycle per dump cycle:
//   rotate()          — swap active <-> standby (call before lockAll/dump)
//   standby()->...    — dump thread reads snapshot lock-free
//   clearStandby()    — free old-active memory (call after dump)
//
// For profiler reset call clearAll().
class DoubleBufferedDictionary {
    Dictionary _a;
    Dictionary _b;
    // 0 = _a is active, 1 = _b is active. Accessed only via __atomic_*.
    volatile int _active_index;

    Dictionary* bufAt(int idx) { return idx == 0 ? &_a : &_b; }

public:
    // _a starts as active with the real counter id; _b starts as standby
    // with id=0 (the aggregate/no-op slot) so that clearStandby() never
    // corrupts the named counter slot.
    DoubleBufferedDictionary(int id) : _a(id), _b(0), _active_index(0) {}

    unsigned int lookup(const char* key, size_t length) {
        return bufAt(__atomic_load_n(&_active_index, __ATOMIC_ACQUIRE))->lookup(key, length);
    }

    unsigned int bounded_lookup(const char* key, size_t length, int size_limit) {
        return bufAt(__atomic_load_n(&_active_index, __ATOMIC_ACQUIRE))->bounded_lookup(key, length, size_limit);
    }

    // Returns the standby buffer for lock-free read by the dump thread.
    // Only valid between rotate() and the next rotate().
    Dictionary* standby() {
        return bufAt(1 - __atomic_load_n(&_active_index, __ATOMIC_ACQUIRE));
    }

    // Atomically promotes standby to active and active to standby.
    // Transfers counter id ownership so that only the active buffer ever
    // touches the named counter slot; the standby uses id=0.
    // The named counter slot is NOT reset here — it retains the old active's
    // values so that writeCounters() / getDebugCounters() read the correct
    // snapshot for the dump in progress.  The slot is reset in clearStandby()
    // once the dump has finished.
    // Call before the dump; all in-flight writers on the old active complete
    // naturally (signal handlers: guaranteed by lockAll(); JNI threads: fast CAS).
    void rotate() {
        int old = __atomic_load_n(&_active_index, __ATOMIC_ACQUIRE);
        Dictionary* oldActive  = bufAt(old);
        Dictionary* newActive  = bufAt(1 - old);

        // Swap counter ids: new active takes the real id, old active takes 0.
        int realId = oldActive->counterId();
        oldActive->setCounterId(newActive->counterId()); // oldActive gets 0
        newActive->setCounterId(realId);

        __atomic_store_n(&_active_index, 1 - old, __ATOMIC_RELEASE);
    }

    // Frees all entries in the standby buffer and resets the named counter
    // slot to the new active's empty baseline.  Call after dump completes.
    // standby()->_id is 0 after rotate(), so clear() only touches slot 0;
    // the named slot is reset explicitly here.
    void clearStandby() {
        int realId = bufAt(__atomic_load_n(&_active_index, __ATOMIC_ACQUIRE))->counterId();
        standby()->clear();
        Counters::set(DICTIONARY_KEYS,       0,                 realId);
        Counters::set(DICTIONARY_KEYS_BYTES, 0,                 realId);
        Counters::set(DICTIONARY_BYTES,      sizeof(DictTable),  realId);
        Counters::set(DICTIONARY_PAGES,      1,                 realId);
    }

    // Clears both buffers. Call on profiler reset (no concurrent writers).
    void clearAll() {
        _a.clear();
        _b.clear();
    }
};

#endif // _DICTIONARY_H
