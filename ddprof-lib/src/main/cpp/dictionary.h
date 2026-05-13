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
#include "tripleBuffer.h"
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
  int  size() const { return _size; }
};

// Triple-buffered wrapper for signal-handler-safe concurrent dictionary access.
//
// Three roles cycle through three Dictionary buffers:
//
//   active  — current writes (signal handlers + fill-path)
//   dump    — snapshot being read by the current dump (old active after rotate)
//   scratch — two rotations behind active; cleared lock-free by clearStandby()
//
// The scratch role exists for safe lock-free reclamation: when a buffer is in
// the scratch role, at least one full dump cycle has passed since it was last
// in the "active" or "dump" role.  Signal handlers (per-thread locks drained
// by lockAll) and JNI writers (microsecond lookups) cannot still hold a stale
// pointer to it after such a long grace period, so it is safe to clear without
// any explicit drain.
//
// Lifecycle per dump cycle:
//   rotate()        — advance active; dump thread reads standby()
//   standby()->...  — dump thread reads snapshot lock-free
//   clearStandby()  — clear the scratch buffer (NOT the just-completed dump
//                     buffer — that becomes scratch next cycle and is cleared
//                     one cycle later)
//
// Memory: at most two non-empty buffers at any time (active + dump).
// Churn: entries from dynamic classes purged after at most two full dump cycles.
//
// For profiler reset call clearAll().
class TripleBufferedDictionary {
    int _counter_id;
    Dictionary _a;
    Dictionary _b;
    Dictionary _c;
    TripleBufferRotator<Dictionary> _rot;

public:
    // All three buffers carry the real counter id so that insertions through
    // any buffer (signal-handler path via active, fill-path via dump buffer)
    // are tracked in the named counter slot.  clearStandby() resets the slot.
    TripleBufferedDictionary(int id)
        : _counter_id(id), _a(id), _b(id), _c(id), _rot(&_a, &_b, &_c) {}

    unsigned int lookup(const char* key, size_t length) {
        return _rot.active()->lookup(key, length);
    }

    // Signal-safe lookup against the active buffer only.  Returns INT_MAX if
    // the key is not yet present; callers must tolerate misses — there is no
    // fallback to older snapshots.
    unsigned int bounded_lookup(const char* key, size_t length, int size_limit) {
        return _rot.active()->bounded_lookup(key, length, size_limit);
    }

    // Returns the dump buffer for lock-free read by the dump thread.
    // Only valid between rotate() and the next rotate().
    Dictionary* standby() {
        return _rot.dumpBuffer();
    }

    // Atomically promotes the dump buffer to active.
    // Call before the dump; in-flight writers on the old active complete
    // naturally (signal handlers: per-thread locks; JNI threads: fast CAS).
    void rotate() { _rot.rotate(); }

    // Clears the scratch buffer (two rotations behind active).  Safe to do
    // lock-free: the grace period since its last use as active or dump is one
    // full dump cycle, much longer than any in-flight signal-handler or JNI
    // lookup.  Call after the dump completes.
    void clearStandby() {
        _rot.clearTarget()->clear();
        // clearTarget()->clear() already zeroed the named counter slot via _id;
        // restate explicitly for clarity and belt-and-suspenders.
        Counters::set(DICTIONARY_KEYS,       0,                 _counter_id);
        Counters::set(DICTIONARY_KEYS_BYTES, 0,                 _counter_id);
        Counters::set(DICTIONARY_BYTES,      sizeof(DictTable), _counter_id);
        Counters::set(DICTIONARY_PAGES,      1,                 _counter_id);
    }

    // Clears all three buffers. Call on profiler reset (no concurrent writers).
    void clearAll() {
        _a.clear();
        _b.clear();
        _c.clear();
        _rot.reset();
    }
};

#endif // _DICTIONARY_H
