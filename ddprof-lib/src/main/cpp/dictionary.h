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
  bool _fail_key_alloc_for_test = false;
  int _key_alloc_failures_for_test = 0;
  bool failKeyAlloc() {
    if (_fail_key_alloc_for_test) {
      _key_alloc_failures_for_test++;
      return true;
    }
    return false;
  }
  bool failTableAlloc() {
    if (_fail_table_alloc_for_test) {
      _table_alloc_failures_for_test++;
      return true;
    }
    return false;
  }
#else
  bool failTableAlloc() const { return false; }
  bool failKeyAlloc() const { return false; }
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
  void failKeyAllocationForTest(bool fail) { _fail_key_alloc_for_test = fail; }
  int keyAllocFailuresForTest() const { return _key_alloc_failures_for_test; }
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

// A Dictionary whose failed inserts resolve to reserved ids, so a caller never
// stores 0 (no entry). Signatures get their own id because JFR consumers slice a
// descriptor at ')'. collect() emits a reserved id once a lookup has failed.
class SymbolDictionary : public Dictionary {
private:
  bool _name_failed = false;
  bool _sig_failed = false;

public:
  static constexpr unsigned int UNRESOLVED_ID = 0xFFFFFFFFU;
  static constexpr unsigned int UNRESOLVED_SIG_ID = 0xFFFFFFFEU;

  unsigned int lookup(const char *key, size_t length) {
    unsigned int id = Dictionary::lookup(key, length);
    if (id == 0) {
      _name_failed = true;
      return UNRESOLVED_ID;
    }
    return id;
  }
  unsigned int lookup(const char *key) { return lookup(key, strlen(key)); }

  unsigned int lookupSignature(const char *key, size_t length) {
    unsigned int id = Dictionary::lookup(key, length);
    if (id == 0) {
      _sig_failed = true;
      return UNRESOLVED_SIG_ID;
    }
    return id;
  }
  unsigned int lookupSignature(const char *key) {
    return lookupSignature(key, strlen(key));
  }

  bool failed() const { return _name_failed || _sig_failed; }

  // Hides Dictionary::collect: adds the reserved entries for the failed kinds,
  // so every reference handed out has a pool entry.
  void collect(std::map<unsigned int, const char *> &map) {
    Dictionary::collect(map);
    if (_name_failed) {
      map[UNRESOLVED_ID] = "<unresolved>";
    }
    if (_sig_failed) {
      map[UNRESOLVED_SIG_ID] = "()V";
    }
  }
};

#endif // _DICTIONARY_H
