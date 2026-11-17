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
#include "nativeMem.h"
#include <cassert>
#include <map>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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
#ifdef UNIT_TEST
  bool _fail_table_alloc_for_test = false;
  int _table_alloc_failures_for_test = 0;
  bool failTableAlloc() {
    if (_fail_table_alloc_for_test) {
      _table_alloc_failures_for_test++;
      return true;
    }
    return false;
  }
#else
  bool failTableAlloc() const { return false; }
#endif

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
    NativeMem::record(NM_DICTIONARY, (long long)sizeof(DictTable));
    _table->base_index = _base_index = 1;
    _size = 0;
  }
  ~Dictionary();

  void clear();

#ifdef UNIT_TEST
  void failTableAllocationForTest(bool fail) {
    _fail_table_alloc_for_test = fail;
  }
  int tableAllocFailuresForTest() const { return _table_alloc_failures_for_test; }
#endif

  bool         check(const char* key);
  // NOT signal-safe: the inserting lookup overloads call malloc/calloc on miss
  // (see allocateKey and the calloc in dictionary.cpp). Signal handlers must use
  // bounded_lookup(key, length, 0) instead, which never inserts and returns
  // INT_MAX on miss. If an insert's allocation fails, lookup() returns 0 and
  // bounded_lookup() returns INT_MAX; neither is a valid id.
  unsigned int lookup(const char *key);
  unsigned int lookup(const char *key, size_t length);
  unsigned int bounded_lookup(const char *key, size_t length, int size_limit);

  void collect(std::map<unsigned int, const char *> &map);
};

// A Dictionary whose failed inserts resolve to UNRESOLVED_ID, an id outside the
// table, so a caller never stores 0 (no entry) as a reference. The owner emits
// UNRESOLVED_ID as a pool entry when failed() is set.
class SymbolDictionary : public Dictionary {
private:
  bool _failed = false;
  bool _sealed = false;

public:
  static constexpr unsigned int UNRESOLVED_ID = 0xFFFFFFFFU;

  unsigned int lookup(const char *key, size_t length) {
    assert(!_sealed);
    unsigned int id = Dictionary::lookup(key, length);
    if (id == 0) {
      _failed = true;
      return UNRESOLVED_ID;
    }
    return id;
  }
  unsigned int lookup(const char *key) { return lookup(key, strlen(key)); }

  bool failed() const { return _failed; }
  // Returns failed() and forbids further inserts, which would make it stale.
  bool seal() {
    _sealed = true;
    return _failed;
  }
};

#endif // _DICTIONARY_H
