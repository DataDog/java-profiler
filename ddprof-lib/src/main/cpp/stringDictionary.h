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
static_assert(ROWS == 128, "StringDictionary assumes ROWS == 128 (sized into freeOverflowNodes/forEachEntry traversal)");
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
    std::atomic<int>    _extra_chunks{0};  // chunks linked after _first
    int                 _counter_offset{0};// 0 = no DICTIONARY_BYTES tracking
    bool                _oom_logged{false};// latched per generation; cleared by reset()

    static Chunk* make_chunk() {
        Chunk* c = static_cast<Chunk*>(calloc(1, sizeof(Chunk)));
        // Track every backing chunk regardless of _counter_offset (which only
        // gates the diagnostic DICTIONARY_BYTES counter). Keys are bump-allocated
        // inside these chunks, so they must not be counted separately.
        if (c != nullptr) {
            // recordAlloc measures the allocator overhead rather than assuming
            // it. These chunks are ~512 KB, so glibc serves them by mmap and the
            // overhead is ~16 bytes -- about 0.003 %, not the double-digit
            // percentage a small-allocation-derived blanket factor would imply.
            NativeMem::recordAlloc(NM_DICTIONARY, c, sizeof(Chunk));
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
            _extra_chunks.fetch_add(1, std::memory_order_relaxed);
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
            // Before free(): the overhead is read back off the live chunk.
            NativeMem::recordFreeBefore(NM_DICTIONARY, c, sizeof(Chunk));
            free(c);
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
            // Before free(): the overhead is read back off the live chunk.
            NativeMem::recordFreeBefore(NM_DICTIONARY, c, sizeof(Chunk));
            free(c);
            c = n;
            ++freed;
        }
        if (_first) {
            _first->next = nullptr;
            __atomic_store_n(&_first->pos, (size_t)0, __ATOMIC_RELAXED);
        }
        _active.store(_first, std::memory_order_release);
        _extra_chunks.store(0, std::memory_order_relaxed);
        countChunkFree(freed);
        _oom_logged = false;
    }

    // Re-adds every live chunk to DICTIONARY_BYTES, for use after a global
    // Counters::reset() zeroed the gauge while the chunks stayed allocated.
    void reseedCounters() {
        if (_counter_offset == 0) return;
        int chunks = (_first != nullptr ? 1 : 0) + _extra_chunks.load(std::memory_order_relaxed);
        Counters::increment(DICTIONARY_BYTES, (long long)chunks * (long long)sizeof(Chunk), _counter_offset);
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
    std::atomic<int>   _overflow_nodes{0};  // overflow SBTables linked below _table
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

    // Calls visit(key, id) for every entry of table and its overflow chains
    // whose id is published; entries still mid-insert (id == 0) are skipped.
    template <typename Visitor>
    static void forEachEntry(const SBTable* table, Visitor visit) {
        if (table == nullptr) return;
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
                    if (eid != 0) visit(k, eid);
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
                    _overflow_nodes.fetch_add(1, std::memory_order_relaxed);
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

    // Outcome of copyFrom().  copied counts src entries found here under
    // their src id, whether this call stored them or they were already
    // present - a phase 2 copy re-finds everything phase 1 stored, so copied
    // is not "entries newly stored".  conflicts counts src keys this buffer
    // already held under a different id (an id conflict - see
    // StringDictionary::rotate()).  Entries whose insert failed (allocation
    // failure) count as neither.
    struct CopyResult {
        int copied;
        int conflicts;
    };

    // Copy all entries from src into this buffer preserving their ids.
    // Walks src's table directly, so no per-entry allocation beyond the
    // inserts themselves; keys already present here are left untouched.
    // NOT signal-safe.
    CopyResult copyFrom(const StringDictionaryBuffer& src) {
        CopyResult result = {0, 0};
        forEachEntry(src._table, [this, &result](const char* key, u32 id) {
            u32 stored = insert_with_id(key, strlen(key), id);
            if (stored == id) {
                result.copied++;
            } else if (stored != 0) {
                result.conflicts++;
            }
        });
        return result;
    }

    // Populate out with {id -> key} for all entries in this buffer.
    void collect(std::map<u32, const char*>& out) const {
        forEachEntry(_table, [&out](const char* key, u32 id) { out[id] = key; });
    }

    // Free overflow nodes, zero the root table, reset the arena.
    // Call only with no concurrent accessors.
    void clear() {
        if (_table == nullptr) { _size.store(0, std::memory_order_relaxed); return; }
        int freed = freeOverflowNodes(_table);
        memset(_table, 0, sizeof(SBTable));
        _arena.reset();
        _size.store(0, std::memory_order_relaxed);
        _overflow_nodes.store(0, std::memory_order_relaxed);
        if (_counter_offset != 0 && freed > 0) {
            Counters::decrement(DICTIONARY_PAGES, freed, _counter_offset);
            Counters::decrement(DICTIONARY_BYTES, (long long)(freed * sizeof(SBTable)), _counter_offset);
        }
    }

    // Re-adds the root table, overflow tables and arena chunks to
    // DICTIONARY_PAGES / DICTIONARY_BYTES, for use after a global
    // Counters::reset() zeroed the gauges while the storage stayed allocated.
    void reseedCounters() {
        if (_counter_offset == 0) return;
        if (_table != nullptr) {
            int tables = 1 + _overflow_nodes.load(std::memory_order_relaxed);
            Counters::increment(DICTIONARY_PAGES, tables, _counter_offset);
            Counters::increment(DICTIONARY_BYTES, (long long)tables * (long long)sizeof(SBTable), _counter_offset);
        }
        _arena.reseedCounters();
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
// From just before new_active is published until phase 2 has finished,
// _transitioning is set and a lookup that misses takes its id from old_active
// rather than assigning one on its own (see rotate() for why).
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
//   may create its guard after clearAll()'s drain returns, missing
//   the drain.  A seq_cst recheck inside the guard scope catches this TOCTOU
//   window: the thread sees _accepting=false and returns 0 before touching any
//   buffer data (overflow nodes or arena chunks that clearAll() is freeing).
class StringDictionary {
    std::atomic<u32>  _next_id{1};      // starts at 1; id=0 reserved as "no entry"
    std::atomic<bool> _accepting{true}; // false while clearAll() is resetting buffers
    // Bumped by clearAll() only. Lets a cache keyed by ids from this
    // dictionary (e.g. ReferenceChainTracker::_class_tags, referenceChains.h)
    // detect "the id namespace was wiped out from under me" and invalidate
    // itself, rather than assuming ids stay valid across a clearAll().
    std::atomic<u64>  _generation{0};
    // Set by rotate() from just before it publishes the new active until its
    // phase 2 copy is done; first-time id assignment goes through old_active.
    std::atomic<bool> _transitioning{false};
    StringDictionaryBuffer _a, _b, _c;
    TripleBufferRotator<StringDictionaryBuffer> _rot;
    // The buffer whose last clearStandby() was skipped, or null.  rotate()
    // retries the clear before reusing it.  Accessed only by rotate(),
    // clearStandby() and clearAll(), which the caller serialises (Profiler:
    // _state_lock).
    StringDictionaryBuffer* _uncleared{nullptr};
    // Scans retryUnclearedTarget() makes before giving up (no sleeping).
    static constexpr int RETRY_SCANS = 100;
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

    // Clears target if drained, else remembers it as uncleared.  Returns drained.
    bool finishClear(StringDictionaryBuffer* target, bool drained) {
        if (drained) {
            target->clear();
        }
        _uncleared = drained ? nullptr : target;
        return drained;
    }

    // Clears the clear target if its last clearStandby() was skipped and its
    // guards have gone since.  Returns false if it is still in use.  The
    // straggler had a whole dump cycle to finish, so a short check is enough:
    // a full drain here would add a second ~500ms timeout on the dump thread
    // for a thread that is stuck.  No new guard can reach the target - it is
    // not the active buffer, and an accessor holding a stale pointer to it
    // re-checks _rot.active() and retries - so a scan that finds no guard
    // means it can be cleared.
    bool retryUnclearedTarget() {
        StringDictionaryBuffer* target = _rot.clearTarget();
        if (target != _uncleared) return true;
        void* const buffers[] = {target};
        bool drained = false;
        for (int attempt = 0; attempt < RETRY_SCANS && !drained; ++attempt) {
            drained = !RefCountGuard::isReferenced(buffers, 1);
            if (!drained) spinPause();
        }
        return finishClear(target, drained);
    }

    void countInsert(size_t len) {
        Counters::increment(DICTIONARY_KEYS, 1, _counter_offset);
        Counters::increment(DICTIONARY_KEYS_BYTES, (long long)(len + 1), _counter_offset);
    }

    // A key held under two ids means one of them may have been handed to a
    // caller and will not resolve in later snapshots.  rotate() rules this out
    // except after a drain timeout (a straggler's late insert, or a clear
    // target reused uncleared - see rotate()) and when a mid-rotation lookup
    // could not insert into the dump buffer and assigned its own id (see
    // assignDuringTransition()).  Only counted.
    void reportIdConflicts(int conflicts) {
        if (conflicts == 0) return;
        Counters::increment(DICTIONARY_ID_CONFLICTS, conflicts);
    }

    // Inserts (key, id) into the dump buffer and returns the id the dump
    // buffer holds for the key afterwards.  A transition straggler (see
    // assignDuringTransition()) can race this insert and hold the key under
    // a different id; the dump thread must then record the id the dump
    // snapshot - the source of this chunk's constant pool - actually
    // contains, not the active buffer's id.  The conflict is counted either
    // way.  Returns id unchanged when the dump insert failed (OOM): the id
    // is not in the dump buffer then, but nothing better is available.
    u32 addToDump(StringDictionaryBuffer* dump, const char* key, size_t len, u32 id) {
        u32 stored = dump->insert_with_id(key, len, id);
        reportIdConflicts(stored != 0 && stored != id ? 1 : 0);
        return stored != 0 ? stored : id;
    }

    // First-time id assignment while rotate() is between publishing the new
    // active and finishing phase 2.  The key may have been inserted into
    // old_active after phase 1 and not yet copied, so old_active, the dump
    // buffer, decides the id: its insert_with_id() returns the id it already
    // holds for the key, if any.  active then gets that id - the one phase 2
    // copies - unless a writer arriving after phase 2, which saw
    // _transitioning clear, got in first with another id.  active's id is
    // returned either way, so all callers agree; the dump buffer then keeps
    // the key under the other id until it is cleared.  No caller of lookup()
    // holds that id, but lookupDuringDump() probes the dump buffer first and
    // returns it to the dump thread.  That stays consistent: the id is in the
    // dump buffer, which is what the current chunk's constant pool is written
    // from, and the dump thread resolves class ids afresh in every chunk.
    // A writer still on old_active can see the gate set just before the new
    // active is published; it then goes through the previous dump buffer,
    // which costs nothing but an unused entry there: phase 2 copies its
    // insert into old_active (see the fences in lookupOrInsert() and rotate()).
    // Returns 0 if the dump buffer could not be used; the caller then assigns
    // the id itself.
    u32 assignDuringTransition(StringDictionaryBuffer* active, const char* key, size_t len) {
        StringDictionaryBuffer* dump = _rot.dumpBuffer();
        RefCountGuard guard(dump);
        if (!guard.isActive()) return 0;
        __atomic_thread_fence(__ATOMIC_SEQ_CST);
        // Same rule as for active (see retryUnclearedTarget()): once it is no
        // longer the dump buffer, clearStandby() may be clearing it.
        if (_rot.dumpBuffer() != dump) return 0;
        rotateHook(TRANSITION_BEFORE_DUMP_INSERT);
        // When the dump buffer already holds the key, the freshly drawn id
        // is discarded; ids need only be unique, not dense.
        u32 id = dump->insert_with_id(key, len, nextId());
        if (id == 0) return 0;
        rotateHook(TRANSITION_BETWEEN_INSERTS);
        u32 result = active->insert_with_id(key, len, id);
        // Two writers racing the same fresh key are both arbitrated by the
        // dump buffer to this same id, so both can observe result == id and
        // count the insert once each - DICTIONARY_KEYS then overcounts by
        // one under this race.  Accepted: the counters are diagnostic, and
        // insert_with_id() cannot reveal which caller created the active
        // slot when both pass the same id.
        if (result == id) countInsert(len);
        return result;
    }

    // Shared body of lookup() and the size-limited bounded_lookup(): returns
    // key's id, inserting it under a new id if absent and active holds fewer
    // than size_limit entries.
    u32 lookupOrInsert(const char* key, size_t len, int size_limit) {
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
            // Pairs with the fence in rotate(), which follows its publish of
            // the new active: either the re-check below sees that publish
            // (retry on the new active), or rotate()'s drain sees this guard
            // and waits for the insert below before running phase 2.  The
            // re-check before the probe is not enough: it precedes this fence.
            __atomic_thread_fence(__ATOMIC_SEQ_CST);
            if (_rot.active() != active) continue;
            if (active->size() >= size_limit) return 0;
            // A writer on the new active sees _transitioning set until phase 2
            // is done (see rotate()).
            if (_transitioning.load(std::memory_order_acquire)) {
                u32 result = assignDuringTransition(active, key, len);
                if (result != 0) return result;
            }
            u32 new_id = nextId();
            u32 result = active->insert_with_id(key, len, new_id);
            if (result == new_id) countInsert(len);
            return result;
        }
    }

public:
    // Points at which a UNIT_TEST build calls the hook installed with
    // setRotateHookForTest().  The ROTATE_* stages run on the rotating thread,
    // the TRANSITION_* stages on the thread doing a mid-rotation lookup, and
    // DUMP_BETWEEN_PROBES on the thread calling lookupDuringDump().
    enum RotateStage {
        ROTATE_AFTER_PHASE1,            // phase 1 copied; new active not yet published
        ROTATE_BEFORE_DRAIN,            // new active published; old active not yet drained
        ROTATE_AFTER_PHASE2,            // phase 2 copied; _transitioning still set
        TRANSITION_BEFORE_DUMP_INSERT,  // assignDuringTransition(): dump guard taken, dump insert not yet
        TRANSITION_BETWEEN_INSERTS,     // assignDuringTransition(): dump insert done, active insert not yet
        DUMP_BETWEEN_PROBES             // lookupDuringDump(): dump probe missed, active probe not yet
    };

private:
#ifdef UNIT_TEST
    void (*_rotate_hook)(RotateStage, void*) = nullptr;
    void* _rotate_hook_arg = nullptr;
#endif

    void rotateHook(RotateStage stage) {
#ifdef UNIT_TEST
        if (_rotate_hook != nullptr) _rotate_hook(stage, _rotate_hook_arg);
#else
        (void)stage;
#endif
    }

public:
#ifdef UNIT_TEST
    // Test seam: lets a test interleave other threads with the steps of rotate().
    void setRotateHookForTest(void (*hook)(RotateStage, void*), void* arg) {
        _rotate_hook = hook;
        _rotate_hook_arg = arg;
    }
#endif

    explicit StringDictionary(int counter_offset = 0)
        : _rot(&_a, &_b, &_c), _counter_offset(counter_offset) {
        if (counter_offset != 0) {
            _a.initCounters(counter_offset);
            _b.initCounters(counter_offset);
            _c.initCounters(counter_offset);
        }
    }

    // Current id-namespace generation; see _generation's own comment.
    u64 generation() const { return _generation.load(std::memory_order_acquire); }

    // Re-adds the storage of all three buffers to the DICTIONARY_PAGES /
    // DICTIONARY_BYTES gauges.  Call right after a global Counters::reset(),
    // which zeroes them although the buffers keep their root tables and first
    // arena chunks - and all of their storage if clearAll() was skipped.
    // Storage added between the reset and this call is counted twice; the
    // window is a few instructions and the gauges are diagnostic only.
    void reseedCounters() {
        if (_counter_offset == 0) return;
        _a.reseedCounters();
        _b.reseedCounters();
        _c.reseedCounters();
    }

    // Entry count of the active buffer - the count bounded_lookup() checks size_limit against.
    // Needs no RefCountGuard: _a/_b/_c are members, never freed.
    int activeSize() const { return _rot.active()->size(); }

    // Insert into active buffer; returns globally stable id.  NOT signal-safe.
    u32 lookup(const char* key, size_t len) {
        return lookupOrInsert(key, len, INT_MAX);
    }

    // Insert into active buffer if size < size_limit; returns 0 when at cap.
    // NOT signal-safe.
    u32 bounded_lookup(const char* key, size_t len, int size_limit) {
        return lookupOrInsert(key, len, size_limit);
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
    // serialising JFR operations with _state_lock).  rotate() itself must not
    // run concurrently with another rotate() or clearAll() on this dictionary.
    //
    // If clearStandby() had to skip that buffer, it may still hold an entry a
    // straggler inserted after both copies of an earlier rotate(), with an id
    // the active buffer has since assigned differently; Phase 1 would keep the
    // stale id.  So the clear is retried first.  Returns false if the buffer
    // is still in use and is reused uncleared; the caller reports it.  The
    // stale id then wins over the current one until the next clearAll(); the
    // alternative, overwriting it, would instead orphan whatever the
    // straggler recorded under it.  Either way it takes a thread stuck in a
    // guarded insert for a whole dump cycle.
    //
    // Transition: a key inserted into old_active after phase 1 only reaches
    // new_active in phase 2.  If a lookup that missed in new_active assigned a
    // fresh id before then, phase 2 would find the key already present and the
    // two ids would both be out with callers.  So between publishing
    // new_active and finishing phase 2, a lookup that misses takes the id from
    // old_active (assignDuringTransition()) and puts it into new_active under
    // that id, the one phase 2 copies.  Nothing waits for rotate().
    bool rotate() {
        bool fresh = retryUnclearedTarget();
        StringDictionaryBuffer* old_active = _rot.active();
        // Phase 1: pre-populate clearTarget from active (before rotate).
        // Conflicts here come only from a target reused uncleared (!fresh);
        // phase 2 finds and reports them again.
        _rot.clearTarget()->copyFrom(*old_active);
        rotateHook(ROTATE_AFTER_PHASE1);
        // Set before publishing: _rot.rotate() is a release CAS, so a writer
        // that acquire-loads the new active also sees _transitioning set.
        _transitioning.store(true, std::memory_order_relaxed);
        _rot.rotate();
        // Pairs with the fence in lookupOrInsert(), for writers still holding
        // a guard on old_active: either their post-fence re-check sees the new
        // active and they retry there, or the drain below sees their guard and
        // waits for their insert.
        __atomic_thread_fence(__ATOMIC_SEQ_CST);
        rotateHook(ROTATE_BEFORE_DRAIN);
        // Drain all in-flight accessors on old_active (now the dump buffer).
        // The result is not needed: nothing is reclaimed here.  On a timeout
        // a straggler's late insert may miss the snapshot, and clearStandby()
        // drains again before it clears old_active.
        (void)RefCountGuard::waitForRefCountToClear(old_active);
        // Phase 2: catch any entries inserted into old_active between Phase 1
        // and the drain completing.  Its conflict count includes phase 1's:
        // every phase-1-conflicting key is still in old_active, which only
        // gains entries between the phases (only clear() removes any, and
        // mid-rotate nothing clears old_active), so phase 2 re-finds each
        // one and reports it.
        reportIdConflicts(_rot.active()->copyFrom(*old_active).conflicts);
        rotateHook(ROTATE_AFTER_PHASE2);
        _transitioning.store(false, std::memory_order_release);
        return fresh;
    }

    // Resolve a key during the dump phase.  Safe to call from the dump thread
    // after rotate(); must NOT be called from signal handlers or concurrently
    // with another lookupDuringDump call.
    // size_limit bounds new insertions the same way bounded_lookup() does:
    // once active->size() reaches size_limit, previously-known keys still
    // resolve (dump/active hits above), but a genuinely new key returns 0
    // instead of growing the dictionary further.
    // The returned id is the one the dump buffer holds for the key, so it is
    // in the snapshot this chunk's constant pool is written from.  When a
    // transition straggler (a writer parked inside assignDuringTransition()
    // across the end of the transition) inserts the key into the dump buffer
    // under another id between this call's probes, the straggler's id is
    // returned and the conflict counted - the straggler's id is the one the
    // snapshot contains, and later resolutions of the same key in the same
    // dump return it too.  lookup() callers, by contrast, get the active
    // buffer's id; the two namespaces stay consistent within their own
    // snapshot, and the dump thread re-resolves ids in every chunk.
    u32 lookupDuringDump(const char* key, size_t len, int size_limit = INT_MAX) {
        StringDictionaryBuffer* dump = _rot.dumpBuffer();

        u32 id = dump->lookup(key, len);
        if (id != 0) return id;
        rotateHook(DUMP_BETWEEN_PROBES);

        {
            StringDictionaryBuffer* active = _rot.active();
            RefCountGuard guard(active);
            if (!guard.isActive()) return 0;
            id = active->lookup(key, len);
        }
        if (id != 0) {
            return addToDump(dump, key, len, id);
        }

        {
            StringDictionaryBuffer* active = _rot.active();
            RefCountGuard guard(active);
            if (!guard.isActive()) return 0;
            if (active->size() >= size_limit) return 0;
            u32 new_id = nextId();
            new_id = active->insert_with_id(key, len, new_id);
            if (new_id != 0) return addToDump(dump, key, len, new_id);
            return new_id;
        }
    }

    // Clear the scratch buffer (two rotations behind active).
    // An accessor whose guard on this buffer outlived rotate()'s drain may
    // still be using it, so drain it first.  If the drain times out the clear
    // is skipped and the buffer is remembered; the next rotate(), which makes
    // it the active buffer, retries the clear first (see rotate()).
    // Returns false when the clear was skipped; the caller reports it.
    //
    // Either way DICTIONARY_KEYS / DICTIONARY_KEYS_BYTES restart at 0: they
    // count keys newly assigned an id (lookup()/bounded_lookup()) since the
    // last clearStandby(), not the entries a buffer holds - the copies made
    // by rotate() are not counted either.
    bool clearStandby() {
        StringDictionaryBuffer* target = _rot.clearTarget();
        void* const buffers[] = {target};
        bool cleared = finishClear(target, RefCountGuard::tryWaitForRefCountsToClear(buffers, 1));
        Counters::set(DICTIONARY_KEYS, 0, _counter_offset);
        Counters::set(DICTIONARY_KEYS_BYTES, 0, _counter_offset);
        return cleared;
    }

    // Reset all three buffers and restart the ID counter.
    // _accepting=false gates new RefCountGuard creation; the subsequent drain
    // of this dictionary's buffers ensures no concurrent accessor is mid-read
    // when clear() zeroes the root table and frees overflow nodes and arena
    // chunks.  clear() is O(overflow_nodes + extra_arena_chunks); both are
    // typically zero for small-to-medium dictionaries.
    //
    // Returns false, leaving the dictionary unchanged, if an accessor still
    // holds a guard when the drain times out; the caller reports it.  The reset is all-or-nothing:
    // e.g. restarting _next_id without clearing the buffers would hand out ids
    // that existing entries already use.  An unreset dictionary stays
    // consistent - its ids remain valid and generation() is unchanged.
    [[nodiscard]] bool clearAll() {
        _accepting.store(false, std::memory_order_seq_cst);
        void* const buffers[] = {&_a, &_b, &_c};
        if (!RefCountGuard::tryWaitForRefCountsToClear(buffers, 3)) {
            _accepting.store(true, std::memory_order_release);
            return false;
        }
        _a.clear(); _b.clear(); _c.clear();
        _rot.reset();
        _uncleared = nullptr;
        _next_id.store(1, std::memory_order_relaxed);
        Counters::set(DICTIONARY_KEYS, 0, _counter_offset);
        Counters::set(DICTIONARY_KEYS_BYTES, 0, _counter_offset);
        _generation.fetch_add(1, std::memory_order_release);
        _accepting.store(true, std::memory_order_release);
        return true;
    }
};

#endif // _STRINGDICTIONARY_H
