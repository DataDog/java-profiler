#include <gtest/gtest.h>
#include "stringDictionary.h"
#include <atomic>
#include <map>
#include <string>
#include <thread>
#include <vector>

// ── StringDictionaryBuffer ─────────────────────────────────────────────────

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
    dict.clearAll();
    EXPECT_EQ(0u, dict.bounded_lookup("x", 1));
    dict.rotate();
    std::map<u32, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(0u, snap.size());
    u32 new_id = dict.lookup("x", 1);
    EXPECT_EQ(1u, new_id);
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
