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
