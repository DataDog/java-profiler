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
#include "refCountGuard.h"
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
  const int _id;
  volatile unsigned int _base_index;
  volatile int _size;

  static void clear(DictTable *table, int id);

  static unsigned int hash(const char *key, size_t length);

  static void collect(std::map<unsigned int, const char *> &map,
                      DictTable *table);

  unsigned int lookup(const char *key, size_t length, bool for_insert,
                      unsigned int sentinel);

  void mergeFrom(const DictTable *table);

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

  // Re-inserts all entries from src into this dictionary.  Called from the
  // dump thread during rotatePersistent(); not signal-safe (calls malloc).
  void mergeFrom(const Dictionary &src);

  int  counterId() const { return _id; }
  int  size() const { return _size; }
};

// Triple-buffered wrapper for signal-handler-safe concurrent dictionary access.
//
// Three roles cycle through three Dictionary buffers:
//
//   active  — current writes (signal handlers + fill-path)
//   dump    — snapshot being read by the current dump (old active after rotate)
//   scratch — two rotations behind active; ready to be cleared by clearStandby()
//
// Concurrency safety:
//   lookup() and bounded_lookup() acquire a per-thread RefCountGuard on the
//   active buffer pointer before touching it.  rotate() and rotatePersistent()
//   call RefCountGuard::waitForRefCountToClear(old_active) after advancing the
//   active index, which provably drains all in-flight callers (signal handlers
//   AND JNI threads) before the old buffer is handed to the dump thread.
//   clearStandby() clears the scratch buffer, which was already drained by the
//   rotate() two cycles earlier — no additional drain is needed.
//
//   Trace-drop window: RefCountGuard uses a pointer-first activation protocol
//   (see refCountGuard.h).  In the theoretical window between storing the active
//   pointer and incrementing the reference count a scanner could skip the slot.
//   In practice signal handlers complete in microseconds and a buffer is only
//   cleared after TWO dump cycles (seconds), so this window is never hit.
//   Should it occur, bounded_lookup returns INT_MAX (miss) — a dropped trace or
//   generic vtable frame — not a crash.
//
// Lifecycle per dump cycle:
//   rotate()        — advance active; drain old active via RefCountGuard
//   standby()->...  — dump thread reads stable snapshot
//   clearStandby()  — clear the scratch buffer (safe: drained two cycles ago)
//
// Memory: at most two non-empty buffers at any time (active + dump).
// Churn: entries purged after at most two full dump cycles.
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
    // any buffer are tracked in the named counter slot.
    TripleBufferedDictionary(int id)
        : _counter_id(id), _a(id), _b(id), _c(id), _rot(&_a, &_b, &_c) {}

    unsigned int lookup(const char* key, size_t length) {
        Dictionary* active = _rot.active();
        RefCountGuard guard(active);
        return active->lookup(key, length);
    }

    // Signal-safe: acquires a per-thread RefCountGuard then performs a
    // read-only probe (size_limit=0 never calls malloc).  Returns INT_MAX
    // on miss; callers must tolerate misses.
    unsigned int bounded_lookup(const char* key, size_t length, int size_limit) {
        Dictionary* active = _rot.active();
        RefCountGuard guard(active);
        return active->bounded_lookup(key, length, size_limit);
    }

    // Returns the dump buffer for read by the dump thread.
    // Safe to read after rotate() returns (all in-flight writers drained).
    Dictionary* standby() {
        return _rot.dumpBuffer();
    }

    // Advances the active buffer and drains all in-flight accesses to the
    // old active via RefCountGuard before returning.  After this call the
    // dump thread may read standby() safely.
    void rotate() {
        Dictionary* old_active = _rot.active();
        _rot.rotate();
        RefCountGuard::waitForRefCountToClear(old_active);
    }

    // Variant of rotate() for persistent dictionaries (e.g. class map) whose
    // entries must survive across dump cycles.
    //
    // Before rotating, all entries from the current active are merged into the
    // current clearTarget (the future active after rotation).  Signal handlers
    // observe no gap: they use the old active — still live during the merge —
    // and after rotate() the new active is already fully populated.
    void rotatePersistent() {
        Dictionary* old_active = _rot.active();
        _rot.clearTarget()->mergeFrom(*old_active);
        _rot.rotate();
        RefCountGuard::waitForRefCountToClear(old_active);
    }

    // Clears the scratch buffer (two rotations behind active).
    // The scratch buffer was drained by the rotate() call two cycles ago;
    // no additional synchronisation is required here.
    void clearStandby() {
        _rot.clearTarget()->clear();
        // Dictionary::clear() zeroed the shared DICTIONARY_KEYS slot.  Re-set it
        // to the active buffer's actual insertion count so that monitoring sees
        // only live entries, not the just-cleared scratch buffer's (zero) state.
        Counters::set(DICTIONARY_KEYS, _rot.active()->size(), _counter_id);
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
