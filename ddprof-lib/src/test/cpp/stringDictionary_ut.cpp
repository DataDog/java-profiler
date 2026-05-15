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
