/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "stringDictionary.h"
#include "counters.h"
#include "nativeMem.h"
#include "profiler.h"
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <thread>
#include <vector>

// ── StringDictionaryBuffer ─────────────────────────────────────────────────

// Native-memory accounting must balance across the arena lifecycle: the root
// SBTable and initial chunk are counted at construction, growth adds overflow
// SBTables and arena chunks, clear() returns to the construction baseline, and
// destruction releases everything. 50k keys force at least one extra 512 KiB
// arena chunk so chunk alloc/free pairing is exercised too.
TEST(StringDictionaryBufferTest, NativeMemAccountingBalancesAcrossLifecycle) {
    long long before = NativeMem::live(NM_DICTIONARY);
    {
        StringDictionaryBuffer buf;
        long long after_ctor = NativeMem::live(NM_DICTIONARY);
        EXPECT_GT(after_ctor, before);  // root SBTable + initial arena chunk

        for (int i = 0; i < 50000; i++) {
            char key[32];
            int len = snprintf(key, sizeof(key), "string_key_%d", i);
            buf.insert_with_id(key, (size_t)len, (u32)(i + 1));
        }
        EXPECT_GT(NativeMem::live(NM_DICTIONARY), after_ctor);  // grew

        buf.clear();
        // Overflow SBTables + extra arena chunks freed; root + first chunk kept.
        EXPECT_EQ(after_ctor, NativeMem::live(NM_DICTIONARY));
    }
    EXPECT_EQ(before, NativeMem::live(NM_DICTIONARY));  // fully released
}

TEST(StringDictionaryBufferTest, InsertWithIdReturnsSameIdForSameKey) {
    StringDictionaryBuffer buf;
    u32 id = buf.insert_with_id("hello", 5, 42);
    EXPECT_EQ(42u, id);
    EXPECT_EQ(42u, buf.insert_with_id("hello", 5, 42));
}

TEST(StringDictionaryBufferTest, InsertPreservesExistingIdOnDuplicate) {
    StringDictionaryBuffer buf;
    buf.insert_with_id("key", 3, 7);
    // Second insert of same key must return 7, not some other value
    EXPECT_EQ(7u, buf.insert_with_id("key", 3, 99));
}

TEST(StringDictionaryBufferTest, LookupReturnZeroOnMiss) {
    StringDictionaryBuffer buf;
    EXPECT_EQ(0u, buf.lookup("absent", 6));
}

TEST(StringDictionaryBufferTest, LookupFindsInsertedKey) {
    StringDictionaryBuffer buf;
    buf.insert_with_id("java/lang/String", 16, 1);
    EXPECT_EQ(1u, buf.lookup("java/lang/String", 16));
}

TEST(StringDictionaryBufferTest, LookupDoesNotInsert) {
    StringDictionaryBuffer buf;
    buf.lookup("ghost", 5);
    std::map<u32, const char*> out;
    buf.collect(out);
    EXPECT_EQ(0u, out.size());
}

TEST(StringDictionaryBufferTest, CollectReturnsAllInsertedEntries) {
    StringDictionaryBuffer buf;
    buf.insert_with_id("a", 1, 1);
    buf.insert_with_id("b", 1, 2);
    buf.insert_with_id("c", 1, 3);
    std::map<u32, const char*> out;
    buf.collect(out);
    ASSERT_EQ(3u, out.size());
    EXPECT_STREQ("a", out[1]);
    EXPECT_STREQ("b", out[2]);
    EXPECT_STREQ("c", out[3]);
}

TEST(StringDictionaryBufferTest, CopyFromPreservesAllEntriesWithIds) {
    StringDictionaryBuffer src;
    src.insert_with_id("java/lang/String", 16, 10);
    src.insert_with_id("java/lang/Integer", 17, 20);

    StringDictionaryBuffer dst;
    dst.copyFrom(src);

    EXPECT_EQ(10u, dst.lookup("java/lang/String", 16));
    EXPECT_EQ(20u, dst.lookup("java/lang/Integer", 17));
}

TEST(StringDictionaryBufferTest, ClearResetsToEmpty) {
    StringDictionaryBuffer buf;
    buf.insert_with_id("x", 1, 5);
    buf.clear();
    EXPECT_EQ(0u, buf.lookup("x", 1));
    std::map<u32, const char*> out;
    buf.collect(out);
    EXPECT_EQ(0u, out.size());
}

// ── StringArena behaviour (via StringDictionaryBuffer) ────────────────────
//
// StringArena is a private implementation detail; these tests exercise its
// observable effects through StringDictionaryBuffer's public API.

// Inserting N distinct keys must not corrupt any of them: if arena regions
// overlapped, some key strings would be overwritten and lookups would fail.
TEST(StringArenaTest, AllocsAreNonOverlapping) {
    StringDictionaryBuffer buf;
    constexpr int N = 2000;
    for (int i = 0; i < N; i++) {
        std::string key = "nooverlap_" + std::to_string(i);
        u32 id = static_cast<u32>(i + 1);
        ASSERT_EQ(id, buf.insert_with_id(key.c_str(), key.size(), id))
            << "insert failed at key " << i;
    }
    for (int i = 0; i < N; i++) {
        std::string key = "nooverlap_" + std::to_string(i);
        EXPECT_EQ(static_cast<u32>(i + 1), buf.lookup(key.c_str(), key.size()))
            << "lookup failed at key " << i;
    }
}

// Each key is ~88 bytes aligned; 6 000 keys ≈ 528 KB > the 512 KB chunk size,
// forcing at least one new chunk to be allocated.  All keys must remain
// accessible across the chunk boundary.
TEST(StringArenaTest, GrowsAcrossChunkBoundary) {
    StringDictionaryBuffer buf;
    constexpr int N = 6000;
    const std::string pad(70, 'x');
    std::vector<std::string> keys;
    keys.reserve(N);
    for (int i = 0; i < N; i++) {
        keys.push_back("chunk_" + std::to_string(i) + "_" + pad);
    }
    for (int i = 0; i < N; i++) {
        ASSERT_NE(0u, buf.insert_with_id(keys[i].c_str(), keys[i].size(),
                                         static_cast<u32>(i + 1)))
            << "insert failed at key " << i << " (unexpected arena OOM)";
    }
    for (int i = 0; i < N; i++) {
        EXPECT_EQ(static_cast<u32>(i + 1),
                  buf.lookup(keys[i].c_str(), keys[i].size()))
            << "lookup failed at key " << i << " after chunk growth";
    }
}

// After clear() the arena is reset: old keys are gone and the arena space is
// reused for new inserts.
TEST(StringArenaTest, ClearResetsArena) {
    StringDictionaryBuffer buf;
    buf.insert_with_id("alpha", 5, 1);
    buf.insert_with_id("beta",  4, 2);
    buf.clear();
    EXPECT_EQ(0u, buf.lookup("alpha", 5)) << "stale key visible after clear";
    EXPECT_EQ(0u, buf.lookup("beta",  4)) << "stale key visible after clear";
    // Reinsertion into the recycled arena must work.
    EXPECT_EQ(10u, buf.insert_with_id("alpha", 5, 10));
    EXPECT_EQ(20u, buf.insert_with_id("gamma", 5, 20));
    EXPECT_EQ(10u, buf.lookup("alpha", 5));
    EXPECT_EQ(20u, buf.lookup("gamma", 5));
    EXPECT_EQ(0u,  buf.lookup("beta",  4)) << "beta must still be absent";
}

// After filling multiple chunks and then calling clear(), the extra chunks are
// freed and subsequent inserts succeed — verifying the arena is fully recycled.
TEST(StringArenaTest, ClearAfterChunkGrowthRecyclesExtraChunks) {
    StringDictionaryBuffer buf;
    constexpr int N = 6000;
    const std::string pad(70, 'y');
    for (int i = 0; i < N; i++) {
        std::string k = "recycle_" + std::to_string(i) + "_" + pad;
        buf.insert_with_id(k.c_str(), k.size(), static_cast<u32>(i + 1));
    }
    buf.clear();
    // Fresh inserts must succeed; the arena must be back to a usable state.
    for (int i = 0; i < 200; i++) {
        std::string k = "fresh_" + std::to_string(i);
        u32 id = static_cast<u32>(i + 1000);
        EXPECT_EQ(id, buf.insert_with_id(k.c_str(), k.size(), id))
            << "insert failed after clear+chunk-recycle at " << i;
    }
    // Verify all fresh keys are readable.
    for (int i = 0; i < 200; i++) {
        std::string k = "fresh_" + std::to_string(i);
        EXPECT_EQ(static_cast<u32>(i + 1000), buf.lookup(k.c_str(), k.size()))
            << "lookup failed after clear+chunk-recycle at " << i;
    }
}

// ── StringDictionary (persistent, global IDs) ─────────────────────────────

class StringDictionaryTest : public ::testing::Test {
protected:
    StringDictionary dict;
};

TEST_F(StringDictionaryTest, LookupAssignsGlobalId) {
    u32 id = dict.lookup("java/lang/String", 16);
    EXPECT_GT(id, 0u);
    EXPECT_EQ(id, dict.lookup("java/lang/String", 16));
}

TEST_F(StringDictionaryTest, BoundedLookupFindsActiveEntry) {
    u32 id = dict.lookup("Foo", 3);
    EXPECT_EQ(id, dict.bounded_lookup("Foo", 3));
}

TEST_F(StringDictionaryTest, BoundedLookupReturnsZeroOnMiss) {
    EXPECT_EQ(0u, dict.bounded_lookup("Absent", 6));
}

TEST_F(StringDictionaryTest, IdStableAcrossRotations) {
    u32 id = dict.lookup("java/lang/String", 16);
    for (int cycle = 0; cycle < 10; cycle++) {
        dict.rotate();
        dict.clearStandby();
        EXPECT_EQ(id, dict.bounded_lookup("java/lang/String", 16))
            << "id changed at cycle " << cycle;
    }
}

TEST_F(StringDictionaryTest, AllEntriesPresentInStandbyAfterRotate) {
    u32 id1 = dict.lookup("a", 1);
    u32 id2 = dict.lookup("b", 1);
    dict.rotate();

    std::map<u32, const char*> snap;
    dict.standby()->collect(snap);
    ASSERT_EQ(2u, snap.size());
    EXPECT_EQ(snap[id1], std::string("a"));
    EXPECT_EQ(snap[id2], std::string("b"));
}

TEST_F(StringDictionaryTest, NewEntryAfterRotateIsInNewActive) {
    dict.lookup("early", 5);
    dict.rotate();
    u32 id = dict.lookup("late", 4);

    EXPECT_EQ(id, dict.bounded_lookup("late", 4));

    dict.rotate();
    std::map<u32, const char*> snap;
    dict.standby()->collect(snap);
    bool found = false;
    for (auto& kv : snap) if (strcmp(kv.second, "late") == 0) { found = true; break; }
    EXPECT_TRUE(found);
}

TEST_F(StringDictionaryTest, LookupDuringDumpFindsPreregisteredKey) {
    u32 id = dict.lookup("java/lang/String", 16);
    dict.rotate();
    EXPECT_EQ(id, dict.lookupDuringDump("java/lang/String", 16));
}

TEST_F(StringDictionaryTest, LookupDuringDumpAlsoAddsToStandby) {
    dict.rotate();
    u32 id = dict.lookup("late/Class", 10);

    u32 found = dict.lookupDuringDump("late/Class", 10);
    EXPECT_EQ(id, found);

    std::map<u32, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(1u, snap.count(id));
}

TEST_F(StringDictionaryTest, ClearAllResetsEverything) {
    u32 id = dict.lookup("x", 1);
    (void)id;
    dict.rotate();
    ASSERT_TRUE(dict.clearAll());
    EXPECT_EQ(0u, dict.bounded_lookup("x", 1));
    dict.rotate();
    std::map<u32, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(0u, snap.size());
    u32 new_id = dict.lookup("x", 1);
    EXPECT_EQ(1u, new_id);
}

TEST_F(StringDictionaryTest, BoundedLookupWithSizeLimitRejectsNewKeyAtCapacity) {
    // Fill active up to size_limit distinct keys via the capped overload.
    const int size_limit = 5;
    for (int i = 0; i < size_limit; i++) {
        std::string k = "cap_" + std::to_string(i);
        u32 id = dict.bounded_lookup(k.c_str(), k.size(), size_limit);
        EXPECT_GT(id, 0u) << "insert " << i << " should have succeeded below the limit";
    }

    // A brand-new key must be rejected once active->size() >= size_limit.
    EXPECT_EQ(0u, dict.bounded_lookup("overflow", 8, size_limit));

    // An already-present key must still resolve to its existing id even at capacity
    // (cache hit is checked before the capacity check).
    u32 id0 = dict.bounded_lookup("cap_0", 5, size_limit);
    EXPECT_GT(id0, 0u);
}

TEST_F(StringDictionaryTest, LookupDuringDumpInsertsNewKeyIntoActiveAndStandby) {
    dict.rotate();  // empty active becomes dump, fresh active
    // Key is not in dump and not in active — lookupDuringDump must insert into both.
    u32 id = dict.lookupDuringDump("brand/New", 9);
    EXPECT_GT(id, 0u);

    // Must be in dump (standby)
    std::map<u32, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(1u, snap.count(id));

    // Must be in active (bounded_lookup is a probe of active)
    EXPECT_EQ(id, dict.bounded_lookup("brand/New", 9));
}

TEST_F(StringDictionaryTest, LookupDuringDumpWithSizeLimitRejectsNewKeyAtCapacity) {
    dict.rotate();  // empty active becomes dump, fresh active

    // Fill active up to size_limit distinct keys via the capped overload.
    const int size_limit = 5;
    for (int i = 0; i < size_limit; i++) {
        std::string k = "dump_cap_" + std::to_string(i);
        u32 id = dict.lookupDuringDump(k.c_str(), k.size(), size_limit);
        EXPECT_GT(id, 0u) << "insert " << i << " should have succeeded below the limit";
    }

    // A brand-new key must be rejected once active->size() >= size_limit —
    // neither active nor the dump snapshot should gain the entry.
    EXPECT_EQ(0u, dict.lookupDuringDump("dump_overflow", 13, size_limit));

    // An already-present key must still resolve to its existing id even at
    // capacity (dump/active hits are checked before the capacity check).
    u32 id0 = dict.lookupDuringDump("dump_cap_0", 10, size_limit);
    EXPECT_GT(id0, 0u);
}

// ── Reclamation while a guarded accessor is still active (PROF-16136) ─────
//
// A dictionary reset must never free or reset buffer storage that a guarded
// accessor is still using, even when the reference drain gives up waiting.
// The holder thread below stands in for an accessor that published its
// RefCountGuard, passed the _accepting recheck, obtained a key pointer and was
// then delayed.  The key is chosen from a non-first arena chunk, which clear()
// frees (the first chunk is only rewound), so the stale read is a
// heap-use-after-free that ASan reports.

namespace {

// Enough keys to spill past the first 512 KiB arena chunk.
constexpr int kSpillKeys = 50000;

void fillPastFirstArenaChunk(StringDictionary& dict) {
    for (int i = 0; i < kSpillKeys; i++) {
        char key[32];
        int len = snprintf(key, sizeof(key), "string_key_%d", i);
        ASSERT_GT(dict.lookup(key, (size_t)len), 0u);
    }
}

// Holds a RefCountGuard on buf while keeping a pointer to the last inserted
// key, then re-reads that key once released.
class GuardedKeyHolder {
public:
    explicit GuardedKeyHolder(StringDictionaryBuffer* buf) : _buf(buf), _thread([this] { run(); }) {
        while (!_ready.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
    }

    ~GuardedKeyHolder() {
        release();
        _thread.join();
    }

    // Lets the holder re-read its key and drop the guard; waits until it has.
    void release() {
        _release.store(true, std::memory_order_release);
        while (!_done.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
    }

    const std::string& expected() const { return _expected; }
    const std::string& observed() const { return _observed; }

private:
    void run() {
        RefCountGuard guard(_buf);
        char key[32];
        snprintf(key, sizeof(key), "string_key_%d", kSpillKeys - 1);
        _expected = key;
        std::map<u32, const char*> entries;
        _buf->collect(entries);
        const char* held = nullptr;
        for (auto& kv : entries) {
            if (strcmp(kv.second, key) == 0) { held = kv.second; break; }
        }
        _ready.store(true, std::memory_order_release);
        while (!_release.load(std::memory_order_acquire)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        // Stale read under the bug: the arena chunk holding this key was freed.
        _observed = held != nullptr ? std::string(held) : std::string();
        _done.store(true, std::memory_order_release);
    }

    StringDictionaryBuffer* _buf;
    std::string _expected;
    std::string _observed;
    std::atomic<bool> _ready{false};
    std::atomic<bool> _release{false};
    std::atomic<bool> _done{false};
    std::thread _thread;
};

} // namespace

// clearAll() must leave every buffer intact when the drain times out with a
// guard still held, and must reset normally once the guard is gone.
TEST(StringDictionaryReclamationTest, ClearAllKeepsStorageWhileGuardHeld) {
    StringDictionary dict;
    fillPastFirstArenaChunk(dict);
    dict.rotate();  // the filled buffer becomes the dump buffer; its keys stay put
    StringDictionaryBuffer* held_buf = dict.standby();
    const int held_size = held_buf->size();
    const u32 known_id = dict.bounded_lookup("string_key_0", 12);
    ASSERT_GT(known_id, 0u);
    const u64 gen_before = dict.generation();

    {
        GuardedKeyHolder holder(held_buf);

        EXPECT_FALSE(dict.clearAll());  // the drain must time out: the holder never lets go

        EXPECT_EQ(gen_before, dict.generation()) << "id namespace reset under an active guard";
        EXPECT_EQ(held_size, held_buf->size()) << "guarded buffer was cleared";
        EXPECT_EQ(known_id, dict.bounded_lookup("string_key_0", 12));

        holder.release();
        EXPECT_EQ(holder.expected(), holder.observed());
    }

    ASSERT_TRUE(dict.clearAll());
    EXPECT_EQ(gen_before + 1, dict.generation());
    EXPECT_EQ(0, held_buf->size());
    EXPECT_EQ(0u, dict.bounded_lookup("string_key_0", 12));
}

// clearAll() drains only its own buffers.  Profiler::start() resets three
// dictionaries back to back while JNI callers keep using the other two; a
// guard held on a different dictionary must neither fail nor delay the reset.
TEST(StringDictionaryReclamationTest, ClearAllIgnoresGuardsOnOtherDictionaries) {
    StringDictionary dict;
    StringDictionary other;
    ASSERT_GT(dict.lookup("mine", 4), 0u);
    fillPastFirstArenaChunk(other);
    other.rotate();
    const u64 gen_before = dict.generation();

    GuardedKeyHolder holder(other.standby());
    auto start = std::chrono::steady_clock::now();
    EXPECT_TRUE(dict.clearAll());
    EXPECT_LT(std::chrono::steady_clock::now() - start, std::chrono::milliseconds(100));
    EXPECT_EQ(gen_before + 1, dict.generation());
    EXPECT_EQ(0u, dict.bounded_lookup("mine", 4));
}

// clearStandby() must not clear a buffer that a guard still references.  This
// is the rotation-side variant: an accessor whose guard on the active buffer
// outlived rotate()'s drain is still using that buffer two rotations later,
// when it comes up as the clear target.  The guard is taken after the first
// rotate() so that drain is not exercised here; the scanner sees the same
// slot state either way.
TEST(StringDictionaryReclamationTest, ClearStandbyKeepsBufferWhileGuardHeld) {
    StringDictionary dict;
    fillPastFirstArenaChunk(dict);
    dict.rotate();
    dict.clearStandby();
    StringDictionaryBuffer* held_buf = dict.standby();
    const int held_size = held_buf->size();

    {
        GuardedKeyHolder holder(held_buf);

        dict.rotate();
        EXPECT_FALSE(dict.clearStandby());  // held_buf is now the clear target

        EXPECT_EQ(held_size, held_buf->size()) << "guarded buffer was cleared";

        holder.release();
        EXPECT_EQ(holder.expected(), holder.observed());
    }

    // The uncleared buffer becomes active on the next rotate() and keeps its
    // entries, which is harmless because ids are never reassigned outside
    // clearAll().  With the guard gone it is cleared normally the next time it
    // comes up as the clear target, three cycles later.
    u32 id = dict.bounded_lookup("string_key_0", 12);
    EXPECT_GT(id, 0u);
    for (int cycle = 0; cycle < 3; cycle++) {
        dict.rotate();
        EXPECT_TRUE(dict.clearStandby());
        EXPECT_EQ(id, dict.bounded_lookup("string_key_0", 12)) << "id changed at cycle " << cycle;
    }
    EXPECT_EQ(0, held_buf->size());
}

// A buffer whose clear was skipped must not bring stale ids back into use.
// A straggler that outlived rotate()'s drain can insert a key into the old
// buffer after both copies, while the active buffer gives the same key a
// different id.  If the straggler still holds its guard when clearStandby()
// runs, the clear is skipped; when rotate() later reuses that buffer as the
// new active, the current id must win over the straggler's.
TEST(StringDictionaryReclamationTest, ReusedUnclearedBufferKeepsCurrentIds) {
    StringDictionary dict;
    ASSERT_GT(dict.lookup("early", 5), 0u);
    dict.rotate();
    EXPECT_TRUE(dict.clearStandby());
    StringDictionaryBuffer* held_buf = dict.standby();

    const u32 stale_id = 999999;
    u32 current_id;
    {
        GuardedKeyHolder holder(held_buf);
        // The straggler's late insert into the old buffer...
        ASSERT_EQ(stale_id, held_buf->insert_with_id("late", 4, stale_id));
        // ...while the active buffer assigns the key its own id.
        current_id = dict.lookup("late", 4);
        ASSERT_GT(current_id, 0u);
        ASSERT_NE(stale_id, current_id);

        dict.rotate();
        EXPECT_FALSE(dict.clearStandby());  // held_buf is the clear target
    }

    // The straggler is gone; the next rotate() reuses held_buf as the active.
    EXPECT_TRUE(dict.rotate());
    EXPECT_EQ(current_id, dict.bounded_lookup("late", 4));
}

// ── Counter gauges across a skipped reset ─────────────────────────────────
//
// Profiler::start() calls Counters::reset() right after resetting the
// dictionaries.  A dictionary whose reset was skipped keeps all of its storage,
// so its memory gauges must be re-added after the counter reset; otherwise
// freeing that storage later drives them negative.

namespace {
constexpr int kEndpointsOffset = 2;  // the DICTIONARY_ENDPOINTS_* counter rows
}

TEST(StringDictionaryCountersTest, ReseedKeepsGaugesExactAcrossSkippedReset) {
    StringDictionary dict(kEndpointsOffset);
    Counters::reset();
    dict.reseedCounters();
    const long long base_pages = Counters::getCounter(DICTIONARY_PAGES, kEndpointsOffset);
    const long long base_bytes = Counters::getCounter(DICTIONARY_BYTES, kEndpointsOffset);
    ASSERT_GT(base_pages, 0);
    ASSERT_GT(base_bytes, 0);

    fillPastFirstArenaChunk(dict);
    dict.rotate();
    {
        GuardedKeyHolder holder(dict.standby());
        ASSERT_FALSE(dict.clearAll());
        Counters::reset();  // what Profiler::start() does next
        dict.reseedCounters();
        EXPECT_GT(Counters::getCounter(DICTIONARY_PAGES, kEndpointsOffset), base_pages);
        EXPECT_GT(Counters::getCounter(DICTIONARY_BYTES, kEndpointsOffset), base_bytes);
    }

    // Freeing the retained storage returns the gauges to the baseline.
    ASSERT_TRUE(dict.clearAll());
    EXPECT_EQ(base_pages, Counters::getCounter(DICTIONARY_PAGES, kEndpointsOffset));
    EXPECT_EQ(base_bytes, Counters::getCounter(DICTIONARY_BYTES, kEndpointsOffset));
}

// The reset steps of Profiler::start(): a skipped dictionary reset stays
// visible as a drain timeout, and its gauges stay non-negative once the
// storage is freed.
TEST(StringDictionaryCountersTest, ProfilerResetKeepsCountersAcrossSkippedReset) {
    Profiler* profiler = Profiler::instance();
    StringDictionary* labels = profiler->stringLabelMap();
    ASSERT_EQ(0, profiler->resetRecordingStateForTest());
    const long long base_pages = Counters::getCounter(DICTIONARY_PAGES, kEndpointsOffset);
    const long long base_bytes = Counters::getCounter(DICTIONARY_BYTES, kEndpointsOffset);

    fillPastFirstArenaChunk(*labels);
    labels->rotate();
    {
        GuardedKeyHolder holder(labels->standby());
        EXPECT_EQ(1, profiler->resetRecordingStateForTest());
        EXPECT_EQ(1, Counters::getCounter(DICTIONARY_DRAIN_TIMEOUTS));
    }

    EXPECT_EQ(0, profiler->resetRecordingStateForTest());
    EXPECT_EQ(base_pages, Counters::getCounter(DICTIONARY_PAGES, kEndpointsOffset));
    EXPECT_EQ(base_bytes, Counters::getCounter(DICTIONARY_BYTES, kEndpointsOffset));
}
