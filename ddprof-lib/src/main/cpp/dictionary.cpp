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

#include "dictionary.h"
#include "arch_dd.h"
#include "counters.h"
#include <climits>
#include <stdlib.h>
#include <string.h>

static inline char *allocateKey(const char *key, size_t length) {
  char *result = (char *)malloc(length + 1);
  memcpy(result, key, length);
  result[length] = 0;
  return result;
}

static inline bool keyEquals(const char *candidate, const char *key,
                             size_t length) {
  return strncmp(candidate, key, length) == 0 && candidate[length] == 0;
}

Dictionary::~Dictionary() {
  clear(_table, _id);
  free(_table);
  Counters::set(DICTIONARY_BYTES, 0, _id);
  Counters::set(DICTIONARY_PAGES, 0, _id);
}

void Dictionary::clear() {
  clear(_table, _id);
  memset(_table, 0, sizeof(DictTable));
  _table->base_index = _base_index = 1;
  Counters::set(DICTIONARY_KEYS, 0, _id);
  Counters::set(DICTIONARY_KEYS_BYTES, 0, _id);
  Counters::set(DICTIONARY_BYTES, sizeof(DictTable), _id);
  Counters::set(DICTIONARY_PAGES, 1, _id);
  _size = 0;
}

void Dictionary::clear(DictTable *table, int id) {
  for (int i = 0; i < ROWS; i++) {
    DictRow *row = &table->rows[i];
    for (int j = 0; j < CELLS; j++) {
      if (row->keys[j]) {
        free(row->keys[j]); // content is zeroed en-mass in the clear() function
      }
    }
    if (row->next != NULL) {
      clear(row->next, id);
      DictTable *tmp = row->next;
      row->next = NULL;
      free(tmp);
    }
  }
}

// Many popular symbols are quite short, e.g. "[B", "()V" etc.
// FNV-1a is reasonably fast and sufficiently random.
unsigned int Dictionary::hash(const char *key, size_t length) {
  unsigned int h = 2166136261U;
  for (size_t i = 0; i < length; i++) {
    h = (h ^ key[i]) * 16777619;
  }
  return h;
}

unsigned int Dictionary::lookup(const char *key) {
  return lookup(key, strlen(key));
}

unsigned int Dictionary::lookup(const char *key, size_t length) {
  return lookup(key, length, true, 0);
}

unsigned int Dictionary::lookup(const char *key, size_t length, bool for_insert,
                                unsigned int sentinel) {
  DictTable *table = _table;
  unsigned int h = hash(key, length);

  while (true) {
    DictRow *row = &table->rows[h % ROWS];
    for (int c = 0; c < CELLS; c++) {
      if (for_insert && row->keys[c] == NULL) {
        char *new_key = allocateKey(key, length);
        if (__sync_bool_compare_and_swap(&row->keys[c], NULL, new_key)) {
          Counters::increment(DICTIONARY_KEYS, 1, _id);
          Counters::increment(DICTIONARY_KEYS_BYTES, length + 1, _id);
          atomicInc(_size);
          return table->index(h % ROWS, c);
        }
        free(new_key);
      }
      if (row->keys[c] && keyEquals(row->keys[c], key, length)) {
        return table->index(h % ROWS, c);
      }
    }

    if (row->next == NULL) {
      if (for_insert) {
        DictTable *new_table = (DictTable *)calloc(1, sizeof(DictTable));
        new_table->base_index =
            __sync_add_and_fetch(&_base_index, TABLE_CAPACITY);
        if (!__sync_bool_compare_and_swap(&row->next, NULL, new_table)) {
          free(new_table);
        } else {
          Counters::increment(DICTIONARY_PAGES, 1, _id);
          Counters::increment(DICTIONARY_BYTES, sizeof(DictTable), _id);
        }
      } else {
        return sentinel;
      }
    }

    table = row->next;
    h = (h >> ROW_BITS) | (h << (32 - ROW_BITS));
  }
}

bool Dictionary::check(const char* key) {
  return lookup(key, strlen(key), false, 0) != 0;
}

unsigned int Dictionary::bounded_lookup(const char *key, size_t length,
                                        int size_limit) {
  // bounded lookup will find the encoding if the key is already mapped,
  // but will only grow the dictionary if the current size is below the limit
  return lookup(key, length, _size < size_limit, INT_MAX);
}

void Dictionary::collect(std::map<unsigned int, const char *> &map) {
  collect(map, _table);
}

void Dictionary::collect(std::map<unsigned int, const char *> &map,
                         DictTable *table) {
  for (int i = 0; i < ROWS; i++) {
    DictRow *row = &table->rows[i];
    for (int j = 0; j < CELLS; j++) {
      if (row->keys[j] != NULL) {
        map[table->index(i, j)] = row->keys[j];
      }
    }
    if (row->next != NULL) {
      collect(map, row->next);
    }
  }
}
