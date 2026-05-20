/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STRINGDICTIONARY_H
#define _STRINGDICTIONARY_H

#include "counters.h"
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
    u32      ids[CELLS];     // set AFTER winning the key CAS (release); 0 until published
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
//     AFTER the CAS wins (release); a reader that observes keys[c] != null via
//     an acquire load must also check ids[c] != 0 before using it.  On x86 the
//     CAS already implies a full memory barrier; on ARM the acquire/release
//     pairing provides the required ordering.  id remains 0 until published.
//   - Reads (lookup): acquire-load keys[c]; if non-null and key matches, return
//     the id — only if ids[c] != 0 (not yet published = miss).  Null means
//     "slot unclaimed" — treated as miss.  There is a narrow window where a
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

    // Iterative DFS walk of the overflow tree.  Each frame tracks one table and
    // the next row to visit.  Because we descend into row->next immediately and
    // only pop the frame after every row has been processed, the stack holds at
    // most one frame per overflow-chain level.  The hash rotation has period
    // 32 / gcd(32, ROW_BITS) = 32: after 32 levels the row index cycles back to
    // the original.  In practice, reaching level N requires N*CELLS keys with
    // identical 32-bit FNV hashes (gcd(7,32)=1 means any two keys that share
    // the same row index across all 32 rotation steps must hash identically).
    // A chain longer than 33 levels therefore requires 99+ exact FNV collisions
    // — statistically negligible for real-world string inputs.  stk[34] covers
    // this practical bound; the top < 34 guard is safety-overflow protection.
    // If it ever fires, entries beyond level 33 are silently dropped rather than
    // crashing — acceptable given how the bound is reached only by adversarial
    // or degenerate inputs.
    static void freeTable(SBTable* table) {
        struct Frame { SBTable* t; int row; };
        Frame stk[34];
        int top = 0;
        stk[top++] = {table, 0};
        while (top > 0) {
            Frame& f = stk[top - 1];
            if (f.row >= ROWS) {
                if (f.t != table) free(f.t);
                --top;
                continue;
            }
            SBRow* row = &f.t->rows[f.row++];
            for (int j = 0; j < CELLS; j++) {
                if (row->keys[j]) free(row->keys[j]);
            }
            if (row->next && top < 34) stk[top++] = {row->next, 0};
        }
    }

    static void collectTable(const SBTable* table,
                             std::map<u32, const char*>& out) {
        struct Frame { const SBTable* t; int row; };
        Frame stk[34];
        int top = 0;
        stk[top++] = {table, 0};
        while (top > 0) {
            Frame& f = stk[top - 1];
            if (f.row >= ROWS) { --top; continue; }
            const SBRow* row = &f.t->rows[f.row++];
            for (int j = 0; j < CELLS; j++) {
                const char* k = __atomic_load_n(&row->keys[j], __ATOMIC_ACQUIRE);
                if (k) {
                    u32 eid = __atomic_load_n(&row->ids[j], __ATOMIC_ACQUIRE);
                    if (eid != 0) out[eid] = k;
                }
            }
            const SBTable* next = __atomic_load_n(&row->next, __ATOMIC_ACQUIRE);
            if (next && top < 34) stk[top++] = {next, 0};
        }
    }

public:
    StringDictionaryBuffer() {
        _table = (SBTable*)calloc(1, sizeof(SBTable));
    }

    ~StringDictionaryBuffer() {
        if (_table != nullptr) { freeTable(_table); }
        free(_table);
        _table = nullptr;
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
                if (keyEquals(k, key, len)) {
                    u32 id = __atomic_load_n(&row->ids[c], __ATOMIC_ACQUIRE);
                    return id;
                }
            }
            table = __atomic_load_n(&row->next, __ATOMIC_ACQUIRE);
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
                    if (!new_key) return 0;
                    memcpy(new_key, key, len);
                    new_key[len] = '\0';
                    if (__sync_bool_compare_and_swap(&row->keys[c], nullptr, new_key)) {
                        __atomic_store_n(&row->ids[c], id, __ATOMIC_RELEASE);
                        _size.fetch_add(1, std::memory_order_relaxed);
                        return id;
                    }
                    free(new_key);
                    existing = __atomic_load_n(&row->keys[c], __ATOMIC_ACQUIRE);
                }
                if (existing && keyEquals(existing, key, len)) {
                    u32 stored_id;
                    while ((stored_id = __atomic_load_n(&row->ids[c], __ATOMIC_ACQUIRE)) == 0) { spinPause(); }
                    return stored_id;
                }
            }
            if (!row->next) {
                SBTable* nt = (SBTable*)calloc(1, sizeof(SBTable));
                if (nt == nullptr) return 0;
                if (!__sync_bool_compare_and_swap(&row->next, nullptr, nt)) free(nt);
            }
            table = __atomic_load_n(&row->next, __ATOMIC_ACQUIRE);
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
        if (_table == nullptr) { _size.store(0, std::memory_order_relaxed); return; }
        freeTable(_table);
        memset(_table, 0, sizeof(SBTable));
        _size.store(0, std::memory_order_relaxed);
    }

    int size() const { return _size.load(std::memory_order_relaxed); }
};

// ─── StringDictionary ─────────────────────────────────────────────────────
//
// Triple-buffered wrapper around StringDictionaryBuffer.
//
// Roles cycle through three buffers:
//   active  — receives new writes (lookup, insert_with_id)
//   dump    — stable snapshot for the current JFR chunk (after rotate())
//   scratch — two rotations behind; cleared by clearStandby()
//
// _next_id is a global monotonic counter that never resets until clearAll().
// rotate() does a two-phase ID-preserving copy so no entry is lost due to
// concurrent inserts in the rotation window:
//   phase 1: copy active → clearTarget (before rotate)
//   phase 2: copy old_active → new_active (after drain, catch late inserts)
// lookupDuringDump(key): probes dump then active; inserts into both if new,
//   using the existing global ID (or a new fetch-add if truly new everywhere).
//
// Signal safety:
//   bounded_lookup acquires RefCountGuard on active before reading.
//   lookup also acquires RefCountGuard before inserting (not signal-safe due to
//   malloc, but the guard protects the buffer pointer lifetime).
//   lookupDuringDump is NOT signal-safe; call from dump thread only.
class StringDictionary {
    std::atomic<u32>  _next_id{1};      // starts at 1; id=0 reserved as "no entry"
    std::atomic<bool> _accepting{true}; // false while clearAll() is resetting buffers
    StringDictionaryBuffer _a, _b, _c;
    TripleBufferRotator<StringDictionaryBuffer> _rot;
    int _counter_offset;  // offset into DICTIONARY_KEYS / DICTIONARY_KEYS_BYTES counter rows

    u32 nextId() {
        return _next_id.fetch_add(1, std::memory_order_relaxed);
    }

    void countInsert(size_t len) {
        Counters::increment(DICTIONARY_KEYS, 1, _counter_offset);
        Counters::increment(DICTIONARY_KEYS_BYTES, (long long)(len + 1), _counter_offset);
    }

public:
    explicit StringDictionary(int counter_offset = 0)
        : _rot(&_a, &_b, &_c), _counter_offset(counter_offset) {}

    // Insert into active buffer; returns globally stable id.  NOT signal-safe.
    u32 lookup(const char* key, size_t len) {
        // Bail immediately if clearAll() is resetting the buffers; creating a
        // RefCountGuard here could race with freeTable() inside clear().
        if (!_accepting.load(std::memory_order_acquire)) return 0;
        while (true) {
            StringDictionaryBuffer* active = _rot.active();
            RefCountGuard guard(active);
            if (!guard.isActive()) return 0;
            if (_rot.active() != active) continue;
            u32 id = active->lookup(key, len);
            if (id != 0) return id;
            // nextId() may be consumed without assignment if a concurrent insert wins
            // the CAS for the same key; IDs are unique but not guaranteed to be dense.
            u32 new_id = nextId();
            u32 result = active->insert_with_id(key, len, new_id);
            if (result == new_id) countInsert(len);
            return result;
        }
    }

    // Insert into active buffer if size < size_limit; returns 0 when at cap.
    // NOT signal-safe.
    u32 bounded_lookup(const char* key, size_t len, int size_limit) {
        // Bail immediately if clearAll() is resetting the buffers; creating a
        // RefCountGuard here could race with freeTable() inside clear().
        if (!_accepting.load(std::memory_order_acquire)) return 0;
        while (true) {
            StringDictionaryBuffer* active = _rot.active();
            RefCountGuard guard(active);
            if (!guard.isActive()) return 0;
            if (_rot.active() != active) continue;
            u32 id = active->lookup(key, len);
            if (id != 0) return id;
            if (active->size() >= size_limit) return 0;
            u32 new_id = nextId();
            u32 result = active->insert_with_id(key, len, new_id);
            if (result == new_id) countInsert(len);
            return result;
        }
    }

    // Signal-safe read-only probe of active. Returns 0 on miss.
    u32 bounded_lookup(const char* key, size_t len) {
        if (!_accepting.load(std::memory_order_acquire)) return 0;
        while (true) {
            StringDictionaryBuffer* active = _rot.active();
            RefCountGuard guard(active);
            if (!guard.isActive()) return 0;
            if (_rot.active() != active) continue;
            return active->lookup(key, len);
        }
    }

    // Returns the dump buffer (snapshot of old active after rotate()).
    StringDictionaryBuffer* standby() {
        return _rot.dumpBuffer();
    }

    // Two-phase ID-preserving rotate.
    void rotate() {
        StringDictionaryBuffer* old_active = _rot.active();
        // Phase 1: pre-populate clearTarget from active (before rotate).
        _rot.clearTarget()->copyFrom(*old_active);
        _rot.rotate();
        // Drain all in-flight accessors on old_active (now the dump buffer).
        RefCountGuard::waitForRefCountToClear(old_active);
        // Phase 2: copy old_active → new active to catch late inserts.
        _rot.active()->copyFrom(*old_active);
    }

    // Resolve a key during the dump phase.  Safe to call from the dump thread
    // after rotate(); must NOT be called from signal handlers or concurrently
    // with another lookupDuringDump call.
    u32 lookupDuringDump(const char* key, size_t len) {
        StringDictionaryBuffer* dump = _rot.dumpBuffer();

        u32 id = dump->lookup(key, len);
        if (id != 0) return id;

        {
            StringDictionaryBuffer* active = _rot.active();
            RefCountGuard guard(active);
            if (!guard.isActive()) return 0;
            id = active->lookup(key, len);
        }
        if (id != 0) {
            dump->insert_with_id(key, len, id);
            return id;
        }

        {
            StringDictionaryBuffer* active = _rot.active();
            RefCountGuard guard(active);
            if (!guard.isActive()) return 0;
            u32 new_id = nextId();
            new_id = active->insert_with_id(key, len, new_id);
            if (new_id != 0) dump->insert_with_id(key, len, new_id);
            return new_id;
        }
    }

    // Clear the scratch buffer (two rotations behind active; safe to clear).
    // Resets per-dump counters to 0 so they track only post-clearStandby inserts.
    void clearStandby() {
        _rot.clearTarget()->clear();
        Counters::set(DICTIONARY_KEYS, 0, _counter_offset);
        Counters::set(DICTIONARY_KEYS_BYTES, 0, _counter_offset);
    }

    // Reset all three buffers and restart the ID counter.
    // Sets _accepting=false so that bounded_lookup callers that bypass lockAll()
    // (JNI paths) do not create new RefCountGuards after the caller's initial
    // waitForAllRefCountsToClear() drains.  Drains again internally to catch any
    // guard that started between the caller's drain and this flag flip, then
    // clears, then re-enables lookups.
    void clearAll() {
        _accepting.store(false, std::memory_order_seq_cst);
        // Drain guards that were already past the _accepting check when the flag
        // was set.  After this returns, no new guards will be created (they all
        // see _accepting=false) so the clear below is safe.
        RefCountGuard::waitForAllRefCountsToClear();
        _a.clear(); _b.clear(); _c.clear();
        _rot.reset();
        _next_id.store(1, std::memory_order_relaxed);
        Counters::set(DICTIONARY_KEYS, 0, _counter_offset);
        Counters::set(DICTIONARY_KEYS_BYTES, 0, _counter_offset);
        _accepting.store(true, std::memory_order_release);
    }
};

#endif // _STRINGDICTIONARY_H
