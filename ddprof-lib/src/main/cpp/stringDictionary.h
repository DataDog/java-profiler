/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STRINGDICTIONARY_H
#define _STRINGDICTIONARY_H

#include "refCountGuard.h"
#include "tripleBuffer.h"
#include "arch.h"
#include <atomic>
#include <map>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Reuse the same table geometry as Dictionary for cache-friendly layout.
#ifndef ROW_BITS
#define ROW_BITS 7
#define ROWS (1 << ROW_BITS)
#define CELLS 3
#endif

// ─── Internal storage types ────────────────────────────────────────────────

struct SBTable;

struct SBRow {
    char*    keys[CELLS];    // null = empty; CAS-claimed by the inserting thread
    u32      keylens[CELLS]; // set before key CAS (relaxed)
    u32      ids[CELLS];     // set before key CAS (relaxed); read via acquire of keys[]
    SBTable* next;           // overflow chain; CAS-created on overflow
};

struct SBTable {
    SBRow rows[ROWS];
};

// ─── StringDictionaryBuffer ────────────────────────────────────────────────
//
// Open-addressing concurrent hash table mapping string keys to u32 IDs.
//
// Concurrency model:
//   - Inserts (insert_with_id, copyFrom): use __sync_bool_compare_and_swap on
//     keys[c] (full fence on GCC) to claim a slot.  id and keylen are stored
//     BEFORE the CAS (relaxed); the CAS acts as a release fence so that any
//     reader that observes keys[c] != null via an acquire load also sees id and
//     keylen.  On x86 the CAS already implies a full memory barrier; on ARM the
//     acquire/release pairing provides the required ordering.
//   - Reads (lookup): acquire-load keys[c]; if non-null and key matches, return
//     the id (visible after the acquire).  Null means "slot unclaimed or not yet
//     written" — treated as miss.  There is a narrow window where a concurrent
//     inserter has started but not yet committed the CAS; this is safe (returns
//     miss = 0), identical to the existing Dictionary behaviour.
//   - clear(): called only when no concurrent readers/writers are active.
//
// Not signal-safe for insert_with_id / copyFrom (call malloc).
// Signal-safe for lookup (read-only, no allocation).
class StringDictionaryBuffer {
private:
    SBTable*           _table;
    std::atomic<int>   _size{0};

    static unsigned int hash(const char* key, size_t length) {
        unsigned int h = 2166136261U;
        for (size_t i = 0; i < length; i++) h = (h ^ (unsigned char)key[i]) * 16777619;
        return h;
    }

    static bool keyEquals(const char* candidate, const char* key, size_t length) {
        return strncmp(candidate, key, length) == 0 && candidate[length] == '\0';
    }

    static void freeTable(SBTable* table) {
        for (int i = 0; i < ROWS; i++) {
            SBRow* row = &table->rows[i];
            for (int j = 0; j < CELLS; j++) {
                if (row->keys[j]) free(row->keys[j]);
            }
            if (row->next) {
                freeTable(row->next);
                free(row->next);
            }
        }
    }

    static void collectTable(const SBTable* table,
                             std::map<u32, const char*>& out) {
        for (int i = 0; i < ROWS; i++) {
            const SBRow* row = &table->rows[i];
            for (int j = 0; j < CELLS; j++) {
                const char* k = __atomic_load_n(&row->keys[j], __ATOMIC_ACQUIRE);
                if (k) out[row->ids[j]] = k;
            }
            if (row->next) collectTable(row->next, out);
        }
    }

public:
    StringDictionaryBuffer() {
        _table = (SBTable*)calloc(1, sizeof(SBTable));
    }

    ~StringDictionaryBuffer() {
        freeTable(_table);
        free(_table);
    }

    // Signal-safe read-only probe. Returns 0 on miss.
    u32 lookup(const char* key, size_t len) const {
        const SBTable* table = _table;
        unsigned int h = hash(key, len);
        while (table) {
            const SBRow* row = &table->rows[h % ROWS];
            for (int c = 0; c < CELLS; c++) {
                const char* k = __atomic_load_n(&row->keys[c], __ATOMIC_ACQUIRE);
                if (!k) return 0;
                if (keyEquals(k, key, len)) return row->ids[c];
            }
            table = row->next;
            h = (h >> ROW_BITS) | (h << (32 - ROW_BITS));
        }
        return 0;
    }

    // Insert with the given id. Returns the id stored for this key
    // (either the given id on a new slot, or the existing id on a duplicate).
    // NOT signal-safe (calls malloc).
    u32 insert_with_id(const char* key, size_t len, u32 id) {
        SBTable* table = _table;
        unsigned int h = hash(key, len);
        while (true) {
            SBRow* row = &table->rows[h % ROWS];
            for (int c = 0; c < CELLS; c++) {
                char* existing = __atomic_load_n(&row->keys[c], __ATOMIC_ACQUIRE);
                if (!existing) {
                    char* new_key = (char*)malloc(len + 1);
                    memcpy(new_key, key, len);
                    new_key[len] = '\0';
                    row->keylens[c] = (u32)len;
                    row->ids[c] = id;
                    if (__sync_bool_compare_and_swap(&row->keys[c], nullptr, new_key)) {
                        _size.fetch_add(1, std::memory_order_relaxed);
                        return id;
                    }
                    free(new_key);
                    existing = __atomic_load_n(&row->keys[c], __ATOMIC_ACQUIRE);
                }
                if (existing && keyEquals(existing, key, len)) {
                    return row->ids[c];
                }
            }
            if (!row->next) {
                SBTable* nt = (SBTable*)calloc(1, sizeof(SBTable));
                if (!__sync_bool_compare_and_swap(&row->next, nullptr, nt)) free(nt);
            }
            table = row->next;
            h = (h >> ROW_BITS) | (h << (32 - ROW_BITS));
        }
    }

    // Copy all entries from src into this buffer preserving their ids.
    // NOT signal-safe.
    void copyFrom(const StringDictionaryBuffer& src) {
        std::map<u32, const char*> entries;
        src.collect(entries);
        for (auto& kv : entries) {
            insert_with_id(kv.second, strlen(kv.second), kv.first);
        }
    }

    // Populate out with {id -> key} for all entries in this buffer.
    void collect(std::map<u32, const char*>& out) const {
        collectTable(_table, out);
    }

    // Free all keys and reset to empty. Call only with no concurrent accessors.
    void clear() {
        freeTable(_table);
        memset(_table, 0, sizeof(SBTable));
        _size.store(0, std::memory_order_relaxed);
    }

    int size() const { return _size.load(std::memory_order_relaxed); }
};

#endif // _STRINGDICTIONARY_H
