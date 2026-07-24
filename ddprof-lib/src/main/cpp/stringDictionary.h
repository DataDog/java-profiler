/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STRINGDICTIONARY_H
#define _STRINGDICTIONARY_H

#include "counters.h"
#include "log.h"
#include "nativeMem.h"
#include "refCountGuard.h"
#include "tripleBuffer.h"
#include "arch.h"
#include <atomic>
#include <climits>
#include <map>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

// Reuse the same table geometry as Dictionary for cache-friendly layout.
// The two headers share these macros via this #ifndef guard; the static_asserts
// below catch any divergence at compile time so a future change to dictionary.h
// cannot silently change SBTable geometry depending on include order.
#ifndef ROW_BITS
#define ROW_BITS 7
#define ROWS (1 << ROW_BITS)
#define CELLS 3
#endif
static_assert(ROW_BITS == 7, "StringDictionary assumes ROW_BITS == 7");
static_assert(ROWS == 128, "StringDictionary assumes ROWS == 128 (sized into freeOverflowNodes/collectTable traversal)");
static_assert(CELLS == 3, "StringDictionary assumes CELLS == 3 (SBRow layout)");

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

// ─── StringArena ──────────────────────────────────────────────────────────
//
// Auto-growing bump allocator for key strings inside StringDictionaryBuffer.
//
// Memory is organised as a linked list of 512 KB chunks.  alloc() is a single
// atomic fetch_add on the current chunk — fully contention-free as long as
// the chunk is not full.  When a chunk fills up, grow() serialises creation of
// the next chunk via a CAS spinlock; contention here is extremely rare.
//
// Threads that lose a CAS race in insert_with_id leave their arena allocation
// as waste; space is recovered on the next reset().
//
// reset() frees all chunks after the first and resets the first chunk's
// position counter.  The first chunk is kept to avoid a malloc on the next
// use.  reset() must only be called when no concurrent alloc() calls are in
// flight.
class StringArena {
    static constexpr size_t CHUNK_SIZE = 512 * 1024;

    // Plain struct allocated via calloc (zero-initialised); pos accessed via
    // __atomic builtins, consistent with the rest of the file.
    struct Chunk {
        Chunk* next;        // singly-linked for traversal in reset() / ~StringArena()
        size_t pos;         // bump pointer within data[]
        char   data[CHUNK_SIZE];
    };

    Chunk*              _first;            // head of chain; kept across resets
    std::atomic<Chunk*> _active;           // current allocation target
    std::atomic<bool>   _growing{false};   // serialises new-chunk creation
    int                 _counter_offset{0};// 0 = no DICTIONARY_BYTES tracking
    bool                _oom_logged{false};// latched per generation; cleared by reset()

    static Chunk* make_chunk() {
        Chunk* c = static_cast<Chunk*>(calloc(1, sizeof(Chunk)));
        // Track every backing chunk regardless of _counter_offset (which only
        // gates the diagnostic DICTIONARY_BYTES counter). Keys are bump-allocated
        // inside these chunks, so they must not be counted separately.
        if (c != nullptr) {
            NativeMem::record(NM_DICTIONARY, (long long)sizeof(Chunk));
        }
        return c;
    }

    void countChunkAlloc() {
        if (_counter_offset != 0) {
            Counters::increment(DICTIONARY_BYTES, (long long)sizeof(Chunk), _counter_offset);
        }
    }

    void countChunkFree(int n) {
        if (_counter_offset != 0 && n > 0) {
            Counters::decrement(DICTIONARY_BYTES, (long long)(n * sizeof(Chunk)), _counter_offset);
        }
    }

    void grow(Chunk* full) {
        // One thread at a time creates the next chunk.  Others spin briefly
        // then re-check _active; if it has already advanced they return.
        bool expected = false;
        while (!_growing.compare_exchange_weak(expected, true,
               std::memory_order_acquire, std::memory_order_relaxed)) {
            if (_active.load(std::memory_order_relaxed) != full) return;
            expected = false;
            spinPause();
        }
        if (_active.load(std::memory_order_relaxed) != full) {
            _growing.store(false, std::memory_order_release);
            return;
        }
        Chunk* fresh = make_chunk();
        // On OOM store nullptr so alloc() returns nullptr instead of spinning.
        _active.store(fresh, std::memory_order_release);
        if (fresh) {
            full->next = fresh;            // link into chain for reset() traversal
            countChunkAlloc();
        } else {
            // Make the failure observable in production logs.  Latched per
            // arena instance: only the first OOM in the current generation
            // logs; reset() clears the latch.
            if (!_oom_logged) {
                _oom_logged = true;
                Log::warn("StringArena: chunk allocation failed; new inserts will "
                          "be dropped on this buffer until the next clearAll/reset");
            }
        }
        _growing.store(false, std::memory_order_release);
    }

public:
    StringArena() : _first(make_chunk()), _active(_first) {}

    ~StringArena() {
        Chunk* c = _first;
        while (c) {
            Chunk* n = c->next;
            free(c);
            NativeMem::record(NM_DICTIONARY, -(long long)sizeof(Chunk));
            c = n;
        }
    }

    StringArena(const StringArena&) = delete;
    StringArena& operator=(const StringArena&) = delete;

    // Enable DICTIONARY_BYTES tracking for arena chunks beyond the initial one.
    // The initial chunk is counted by StringDictionaryBuffer::initCounters(),
    // which calls this method after construction.
    void initCounters(int offset) {
        _counter_offset = offset;
        if (offset != 0 && _first != nullptr) {
            Counters::increment(DICTIONARY_BYTES, (long long)sizeof(Chunk), offset);
        }
    }

    char* alloc(size_t n) {
        n = (n + alignof(void*) - 1) & ~(alignof(void*) - 1);
        for (;;) {
            Chunk* c = _active.load(std::memory_order_acquire);
            if (!c) return nullptr;  // OOM
            size_t off = __atomic_fetch_add(&c->pos, n, __ATOMIC_RELAXED);
            if (off + n <= CHUNK_SIZE) return c->data + off;
            grow(c);
        }
    }

    // Free all chunks after the first; reset the first.
    // O(extra_chunks).  Also clears the OOM state: if alloc() had returned
    // nullptr after a failed make_chunk(), the next alloc() after reset()
    // will succeed again (up to one chunk's worth).
    void reset() {
        Chunk* c = _first ? _first->next : nullptr;
        int freed = 0;
        while (c) {
            Chunk* n = c->next;
            free(c);
            NativeMem::record(NM_DICTIONARY, -(long long)sizeof(Chunk));
            c = n;
            ++freed;
        }
        if (_first) {
            _first->next = nullptr;
            __atomic_store_n(&_first->pos, (size_t)0, __ATOMIC_RELAXED);
        }
        _active.store(_first, std::memory_order_release);
        countChunkFree(freed);
        _oom_logged = false;
    }
};

// ─── StringDictionaryBuffer ────────────────────────────────────────────────
//
// Open-addressing concurrent hash table mapping string keys to u32 IDs.
//
// Key strings are owned by the per-buffer StringArena.  Overflow SBTable
// nodes are heap-allocated (calloc) and freed by freeOverflowNodes() on
// clear() and destruction.  This makes clear() O(number-of-overflow-nodes)
// rather than O(number-of-entries), and eliminates per-key malloc/free.
//
// Concurrency model:
//   - Inserts (insert_with_id, copyFrom): CAS on keys[c] to claim a slot.
//     id stored AFTER winning CAS (release); readers check ids[c] != 0.
//     Losers of the CAS leave their arena allocation as recoverable waste.
//   - Reads (lookup): acquire-load keys[c]; miss on null or unpublished id.
//   - clear(): called only when no concurrent readers/writers are active.
//
// Not signal-safe for insert_with_id / copyFrom (arena alloc + calloc).
// Signal-safe for lookup (read-only, no allocation).
class StringDictionaryBuffer {
private:
    SBTable*           _table;
    std::atomic<int>   _size{0};
    StringArena        _arena;
    int                _counter_offset{0};  // 0 = no page/byte tracking

    static unsigned int hash(const char* key, size_t length) {
        unsigned int h = 2166136261U;
        for (size_t i = 0; i < length; i++) h = (h ^ (unsigned char)key[i]) * 16777619;
        return h;
    }

    static bool keyEquals(const char* candidate, const char* key, size_t length) {
        return strncmp(candidate, key, length) == 0 && candidate[length] == '\0';
    }

    // Common-case overflow-chain depth; std::vector reserves this many frames
    // up front so the typical traversal never reallocates.  Deeper chains grow
    // the vector — no silent truncation.
    static constexpr int RESERVED_TRAVERSAL_DEPTH = 34;

    // Free only overflow SBTable chain nodes (not key strings — arena-owned).
    // Returns the number of overflow nodes freed (excludes the root table).
    static int freeOverflowNodes(SBTable* table) {
        struct Frame { SBTable* t; int row; };
        std::vector<Frame> stk;
        stk.reserve(RESERVED_TRAVERSAL_DEPTH);
        int freed = 0;
        stk.push_back({table, 0});
        while (!stk.empty()) {
            Frame& f = stk.back();
            if (f.row >= ROWS) {
                if (f.t != table) {
                    free(f.t);
                    NativeMem::record(NM_DICTIONARY, -(long long)sizeof(SBTable));
                    freed++;
                }
                stk.pop_back();
                continue;
            }
            SBRow* row = &f.t->rows[f.row++];
            if (row->next) stk.push_back({row->next, 0});
        }
        return freed;
    }

    static void collectTable(const SBTable* table,
                             std::map<u32, const char*>& out) {
        struct Frame { const SBTable* t; int row; };
        std::vector<Frame> stk;
        stk.reserve(RESERVED_TRAVERSAL_DEPTH);
        stk.push_back({table, 0});
        while (!stk.empty()) {
            Frame& f = stk.back();
            if (f.row >= ROWS) { stk.pop_back(); continue; }
            const SBRow* row = &f.t->rows[f.row++];
            for (int j = 0; j < CELLS; j++) {
                const char* k = __atomic_load_n(&row->keys[j], __ATOMIC_ACQUIRE);
                if (k) {
                    u32 eid = __atomic_load_n(&row->ids[j], __ATOMIC_ACQUIRE);
                    if (eid != 0) out[eid] = k;
                }
            }
            const SBTable* next = __atomic_load_n(&row->next, __ATOMIC_ACQUIRE);
            if (next) stk.push_back({next, 0});
        }
    }

public:
    StringDictionaryBuffer() {
        _table = static_cast<SBTable*>(calloc(1, sizeof(SBTable)));
        if (_table != nullptr) {
            NativeMem::record(NM_DICTIONARY, (long long)sizeof(SBTable));
        }
    }

    ~StringDictionaryBuffer() {
        if (_table != nullptr) {
            freeOverflowNodes(_table);  // records its own decrements
            free(_table);
            NativeMem::record(NM_DICTIONARY, -(long long)sizeof(SBTable));
            _table = nullptr;
        }
    }

    StringDictionaryBuffer(const StringDictionaryBuffer&)            = delete;
    StringDictionaryBuffer& operator=(const StringDictionaryBuffer&) = delete;
    StringDictionaryBuffer(StringDictionaryBuffer&&)                 = delete;
    StringDictionaryBuffer& operator=(StringDictionaryBuffer&&)      = delete;

    // Enable DICTIONARY_PAGES / DICTIONARY_BYTES tracking for this buffer.
    // Called by StringDictionary after construction; counts the root SBTable
    // and the initial arena Chunk.  Subsequent arena growth and reset() are
    // accounted for by StringArena itself.
    void initCounters(int offset) {
        _counter_offset = offset;
        if (_table != nullptr) {
            Counters::increment(DICTIONARY_PAGES, 1, offset);
            Counters::increment(DICTIONARY_BYTES, (long long)sizeof(SBTable), offset);
        }
        _arena.initCounters(offset);
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

    // Insert with the given id. Returns the id stored for this key.
    // NOT signal-safe (arena alloc; calloc for overflow nodes).
    u32 insert_with_id(const char* key, size_t len, u32 id) {
        SBTable* table = _table;
        if (table == nullptr) return 0;   // calloc OOM at ctor; match lookup() contract
        unsigned int h = hash(key, len);
        while (true) {
            SBRow* row = &table->rows[h % ROWS];
            for (int c = 0; c < CELLS; c++) {
                char* existing = __atomic_load_n(&row->keys[c], __ATOMIC_ACQUIRE);
                if (!existing) {
                    char* new_key = _arena.alloc(len + 1);
                    if (!new_key) return 0;
                    memcpy(new_key, key, len);
                    new_key[len] = '\0';
                    if (__sync_bool_compare_and_swap(&row->keys[c], nullptr, new_key)) {
                        __atomic_store_n(&row->ids[c], id, __ATOMIC_RELEASE);
                        _size.fetch_add(1, std::memory_order_relaxed);
                        return id;
                    }
                    // CAS lost — new_key is arena waste, recovered on clear().
                    // Bump-allocator design does not support per-slot reclaim;
                    // expose the waste so operators can quantify the cost.
                    if (_counter_offset != 0) {
                        size_t wasted = (len + 1 + alignof(void*) - 1) & ~(alignof(void*) - 1);
                        Counters::increment(DICTIONARY_ARENA_WASTE_BYTES,
                                            (long long)wasted, _counter_offset);
                    }
                    existing = __atomic_load_n(&row->keys[c], __ATOMIC_ACQUIRE);
                }
                if (existing && keyEquals(existing, key, len)) {
                    u32 stored_id;
                    while ((stored_id = __atomic_load_n(&row->ids[c], __ATOMIC_ACQUIRE)) == 0) { spinPause(); }
                    return stored_id;
                }
            }
            // Relaxed is fine here: the optimization hint may be stale; the CAS
            // below will handle that, and the ACQUIRE load of row->next below
            // provides the necessary happens-before for the newly-created SBTable's contents.
            if (!__atomic_load_n(&row->next, __ATOMIC_RELAXED)) {
                SBTable* nt = static_cast<SBTable*>(calloc(1, sizeof(SBTable)));
                if (nt == nullptr) return 0;
                if (!__sync_bool_compare_and_swap(&row->next, nullptr, nt)) {
                    free(nt);
                } else {
                    NativeMem::record(NM_DICTIONARY, (long long)sizeof(SBTable));
                    if (_counter_offset != 0) {
                        Counters::increment(DICTIONARY_PAGES, 1, _counter_offset);
                        Counters::increment(DICTIONARY_BYTES, (long long)sizeof(SBTable), _counter_offset);
                    }
                }
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

    // Free overflow nodes, zero the root table, reset the arena.
    // Call only with no concurrent accessors.
    void clear() {
        if (_table == nullptr) { _size.store(0, std::memory_order_relaxed); return; }
        int freed = freeOverflowNodes(_table);
        memset(_table, 0, sizeof(SBTable));
        _arena.reset();
        _size.store(0, std::memory_order_relaxed);
        if (_counter_offset != 0 && freed > 0) {
            Counters::decrement(DICTIONARY_PAGES, freed, _counter_offset);
            Counters::decrement(DICTIONARY_BYTES, (long long)(freed * sizeof(SBTable)), _counter_offset);
        }
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
// lookupDuringDump(key): probes dump then active; inserts into both if new.
//
// Concurrency:
//   bounded_lookup acquires RefCountGuard on active before reading.
//   lookup also acquires RefCountGuard before inserting (not signal-safe due to
//   arena alloc, but the guard protects the buffer pointer lifetime).
//   lookupDuringDump is NOT signal-safe; call from dump thread only.
//
//   _accepting gates new guard creation during clearAll().  A thread that
//   passed the outer acquire-load check before clearAll() sets _accepting=false
//   may create its guard after waitForAllRefCountsToClear() returns, missing
//   the drain.  A seq_cst recheck inside the guard scope catches this TOCTOU
//   window: the thread sees _accepting=false and returns 0 before touching any
//   buffer data (overflow nodes or arena chunks that clearAll() is freeing).
class StringDictionary {
    std::atomic<u32>  _next_id{1};      // starts at 1; id=0 reserved as "no entry"
    std::atomic<bool> _accepting{true}; // false while clearAll() is resetting buffers
    StringDictionaryBuffer _a, _b, _c;
    TripleBufferRotator<StringDictionaryBuffer> _rot;
    int _counter_offset;  // offset into DICTIONARY_KEYS / DICTIONARY_KEYS_BYTES counter rows

    u32 nextId() {
        // id 0 is the "no entry" sentinel.  After ~4 billion lookup() calls
        // _next_id wraps; skip the resulting 0 so insert_with_id never stores
        // 0 in ids[c] (which would make readers in the spin-wait loop hang).
        u32 id;
        do {
            id = _next_id.fetch_add(1, std::memory_order_relaxed);
        } while (__builtin_expect(id == 0, 0));
        return id;
    }

    void countInsert(size_t len) {
        Counters::increment(DICTIONARY_KEYS, 1, _counter_offset);
        Counters::increment(DICTIONARY_KEYS_BYTES, (long long)(len + 1), _counter_offset);
    }

public:
    explicit StringDictionary(int counter_offset = 0)
        : _rot(&_a, &_b, &_c), _counter_offset(counter_offset) {
        if (counter_offset != 0) {
            _a.initCounters(counter_offset);
            _b.initCounters(counter_offset);
            _c.initCounters(counter_offset);
        }
    }

    // Insert into active buffer; returns globally stable id.  NOT signal-safe.
    u32 lookup(const char* key, size_t len) {
        if (!_accepting.load(std::memory_order_acquire)) return 0;
        while (true) {
            StringDictionaryBuffer* active = _rot.active();
            RefCountGuard guard(active);
            if (!guard.isActive()) return 0;
            // Re-check _accepting after guard creation to close the TOCTOU window:
            // clearAll() sets _accepting=false then drains; a thread that passed the
            // outer check but hadn't yet incremented its guard count would be missed
            // by the drain and could access freed overflow nodes or arena chunks.
            if (!_accepting.load(std::memory_order_seq_cst)) return 0;
            if (_rot.active() != active) continue;
            u32 id = active->lookup(key, len);
            if (id != 0) return id;
            u32 new_id = nextId();
            u32 result = active->insert_with_id(key, len, new_id);
            if (result == new_id) countInsert(len);
            return result;
        }
    }

    // Insert into active buffer if size < size_limit; returns 0 when at cap.
    // NOT signal-safe.
    u32 bounded_lookup(const char* key, size_t len, int size_limit) {
        if (!_accepting.load(std::memory_order_acquire)) return 0;
        while (true) {
            StringDictionaryBuffer* active = _rot.active();
            RefCountGuard guard(active);
            if (!guard.isActive()) return 0;
            if (!_accepting.load(std::memory_order_seq_cst)) return 0;
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
            if (!_accepting.load(std::memory_order_seq_cst)) return 0;
            if (_rot.active() != active) continue;
            return active->lookup(key, len);
        }
    }

    // Returns the dump buffer (snapshot of old active after rotate()).
    StringDictionaryBuffer* standby() {
        return _rot.dumpBuffer();
    }

    // Two-phase ID-preserving rotate.
    // StringDictionary makes no assumption about which callers are blocked.
    // In the Profiler context, three caller-side invariants reduce the
    // concurrency that phase 2 must handle:
    //   - Signal paths: the caller (rotateDictsAndRun) holds a SignalBlocker
    //     that masks SIGPROF/SIGVTALRM on the calling thread during rotate(),
    //     so no profiler signal fires on this thread between Phase 1 and 2.
    //   - JNI callers (e.g. recordTrace0): they bypass lockAll() and CAN
    //     still insert into old_active after Phase 1.  Phase 2's
    //     waitForRefCountToClear(old_active) drains those in-flight inserts
    //     before copying — that is the reason phase 2 exists.
    //   - lookupDuringDump(): same thread as the rotate() caller — no
    //     concurrency.
    // clearTarget() is the buffer that becomes the new active after rotate().
    // The caller is responsible for ensuring it is empty on entry (Profiler
    // achieves this by calling clearStandby() after every cycle and
    // serialising JFR operations with _state_lock).
    void rotate() {
        StringDictionaryBuffer* old_active = _rot.active();
        // Phase 1: pre-populate clearTarget from active (before rotate).
        _rot.clearTarget()->copyFrom(*old_active);
        _rot.rotate();
        // Drain all in-flight accessors on old_active (now the dump buffer).
        RefCountGuard::waitForRefCountToClear(old_active);
        // Phase 2: catch any entries inserted into old_active between Phase 1
        // and the drain completing.
        _rot.active()->copyFrom(*old_active);
    }

    // Resolve a key during the dump phase.  Safe to call from the dump thread
    // after rotate(); must NOT be called from signal handlers or concurrently
    // with another lookupDuringDump call.
    // size_limit bounds new insertions the same way bounded_lookup() does:
    // once active->size() reaches size_limit, previously-known keys still
    // resolve (dump/active hits above), but a genuinely new key returns 0
    // instead of growing the dictionary further.
    u32 lookupDuringDump(const char* key, size_t len, int size_limit = INT_MAX) {
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
            if (active->size() >= size_limit) return 0;
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
    // _accepting=false gates new RefCountGuard creation; the subsequent drain
    // ensures no concurrent accessor is mid-read when clear() zeroes the root
    // table.  clear() is O(overflow_nodes + extra_arena_chunks); both are
    // typically zero for small-to-medium dictionaries.
    void clearAll() {
        _accepting.store(false, std::memory_order_seq_cst);
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
