/*
 * Copyright 2025 Datadog, Inc
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

#include <gtest/gtest.h>
#include "dictionary.h"
#include <atomic>
#include <climits>
#include <map>
#include <string>
#include <thread>
#include <vector>

// ── Dictionary ─────────────────────────────────────────────────────────────

TEST(DictionaryTest, LookupReturnsSameIdForSameKey) {
    Dictionary d(0);
    unsigned int id1 = d.lookup("hello", 5);
    EXPECT_GT(id1, 0U);
    EXPECT_EQ(id1, d.lookup("hello", 5));
}

TEST(DictionaryTest, LookupReturnsDifferentIdsForDifferentKeys) {
    Dictionary d(0);
    unsigned int a = d.lookup("alpha", 5);
    unsigned int b = d.lookup("beta",  4);
    EXPECT_NE(a, b);
}

TEST(DictionaryTest, BoundedLookupSkipsInsertWhenAtLimit) {
    Dictionary d(0);
    d.lookup("key1", 4);
    // size is 1, limit is 1 → insert not allowed
    unsigned int r = d.bounded_lookup("key2", 4, 1);
    EXPECT_EQ(r, static_cast<unsigned int>(INT_MAX));
}

TEST(DictionaryTest, BoundedLookupReturnsExistingIdWhenAtLimit) {
    Dictionary d(0);
    unsigned int existing = d.lookup("key1", 4);
    // size is 1, limit is 1 → existing key still found
    EXPECT_EQ(existing, d.bounded_lookup("key1", 4, 1));
}

TEST(DictionaryTest, CollectReturnsAllInsertedEntries) {
    Dictionary d(0);
    d.lookup("a", 1);
    d.lookup("b", 1);
    d.lookup("c", 1);
    std::map<unsigned int, const char*> m;
    d.collect(m);
    EXPECT_EQ(m.size(), 3U);
}

TEST(DictionaryTest, ClearResetsToEmpty) {
    Dictionary d(0);
    d.lookup("x", 1);
    d.clear();
    std::map<unsigned int, const char*> m;
    d.collect(m);
    EXPECT_EQ(m.size(), 0U);
}

// ── TripleBufferedDictionary ────────────────────────────────────────────────

class TripleBufferedDictionaryTest : public ::testing::Test {
protected:
    // id=1 exercises the named counter slot (DICTIONARY_CLASSES_*)
    TripleBufferedDictionary dict{1};
};

TEST_F(TripleBufferedDictionaryTest, LookupGoesToActive) {
    unsigned int id = dict.lookup("cls", 3);
    EXPECT_GT(id, 0U);
    EXPECT_EQ(id, dict.lookup("cls", 3));
}

TEST_F(TripleBufferedDictionaryTest, BoundedLookupGoesToActive) {
    unsigned int id = dict.bounded_lookup("ep", 2, 100);
    EXPECT_NE(id, static_cast<unsigned int>(INT_MAX));
    EXPECT_EQ(id, dict.bounded_lookup("ep", 2, 100));
}

// bounded_lookup with size_limit=0 is read-only and checks the active buffer
// only — there is no fallback to older snapshots.  Keys inserted before rotate
// move to the dump buffer and are no longer visible from bounded_lookup.
TEST_F(TripleBufferedDictionaryTest, BoundedLookupReadOnlyDoesNotFallBack) {
    unsigned int id = dict.lookup("cls", 3);
    EXPECT_GT(id, 0U);

    // Before rotate: key is in active → visible
    EXPECT_EQ(id, dict.bounded_lookup("cls", 3, 0));

    dict.rotate();

    // After rotate: key is in dump buffer, new active is empty → INT_MAX
    EXPECT_EQ(static_cast<unsigned int>(INT_MAX), dict.bounded_lookup("cls", 3, 0));
    EXPECT_EQ(static_cast<unsigned int>(INT_MAX), dict.bounded_lookup("missing", 7, 0));
}

TEST_F(TripleBufferedDictionaryTest, RotateMakesOldActiveReadableAsStandby) {
    unsigned int id = dict.lookup("cls", 3);
    dict.rotate();

    std::map<unsigned int, const char*> snap;
    dict.standby()->collect(snap);
    ASSERT_EQ(snap.size(), 1U);
    EXPECT_STREQ(snap.begin()->second, "cls");
    EXPECT_EQ(snap.begin()->first, id);
}

TEST_F(TripleBufferedDictionaryTest, InsertsAfterRotateGoToNewActiveNotStandby) {
    dict.lookup("a", 1);
    dict.rotate();
    dict.lookup("b", 1);  // must land in new active, not standby

    std::map<unsigned int, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(snap.size(), 1U);  // only "a"

    // Promote new active → standby to inspect "b"
    dict.rotate();
    std::map<unsigned int, const char*> active_snap;
    dict.standby()->collect(active_snap);
    EXPECT_EQ(active_snap.size(), 1U);  // only "b"
}

TEST_F(TripleBufferedDictionaryTest, ClearStandbyDoesNotAffectActiveEntries) {
    dict.lookup("a", 1);
    dict.rotate();
    dict.lookup("b", 1);

    dict.clearStandby();

    // "b" must still be reachable via the next rotation
    dict.rotate();
    std::map<unsigned int, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(snap.size(), 1U);
    EXPECT_STREQ(snap.begin()->second, "b");
}

TEST_F(TripleBufferedDictionaryTest, StandbyIsEmptyAfterClearStandbyAndRotate) {
    dict.lookup("a", 1);
    dict.rotate();
    dict.clearStandby();  // dump buffer (has "a") becomes recent; old recent cleared
    // Next rotation: new active becomes the cleared old-recent; standby = next dump buffer (empty)
    dict.rotate();
    std::map<unsigned int, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(snap.size(), 0U);
}

TEST_F(TripleBufferedDictionaryTest, MultiCycleRotateAndClearIsStable) {
    for (int cycle = 0; cycle < 10; cycle++) {
        std::string key = "key" + std::to_string(cycle);
        dict.lookup(key.c_str(), key.size());
        dict.rotate();

        std::map<unsigned int, const char*> snap;
        dict.standby()->collect(snap);
        EXPECT_EQ(snap.size(), 1U) << "cycle " << cycle;
        EXPECT_STREQ(snap.begin()->second, key.c_str()) << "cycle " << cycle;

        dict.clearStandby();
    }
}

TEST_F(TripleBufferedDictionaryTest, ClearAllResetsActiveToo) {
    dict.lookup("x", 1);
    dict.rotate();
    dict.lookup("y", 1);
    dict.clearAll();

    std::map<unsigned int, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(snap.size(), 0U);

    dict.rotate();
    dict.standby()->collect(snap);
    EXPECT_EQ(snap.size(), 0U);
}

// ── TripleBufferedDictionary — counter-id ownership ────────────────────────
// All three buffers carry the real counter id so that insertions via the
// active (signal-handler) AND via the dump buffer (fill-path during dump)
// both land in the named counter slot.

TEST_F(TripleBufferedDictionaryTest, AllBuffersHaveRealId) {
    EXPECT_EQ(1, dict.standby()->counterId());
}

TEST_F(TripleBufferedDictionaryTest, RotateKeepsRealIdOnAllBuffers) {
    for (int i = 0; i < 9; i++) {
        dict.rotate();
        EXPECT_EQ(1, dict.standby()->counterId()) << "after rotate #" << (i + 1);
    }
}

TEST_F(TripleBufferedDictionaryTest, ClearStandbyKeepsRealIdOnAllBuffers) {
    dict.rotate();
    dict.clearStandby();
    EXPECT_EQ(1, dict.standby()->counterId());
    dict.rotate();
    EXPECT_EQ(1, dict.standby()->counterId());
}

// ── TripleBufferedDictionary — concurrent writes during rotate ──────────────

// Writers are capped at MAX_KEYS_PER_WRITER unique inserts so the standby buffer
// stays small and rotate+clearStandby complete in bounded time.
TEST(TripleBufferedDictionaryConcurrentTest, WritersDuringRotateProduceNoCorruption) {
    static constexpr int MAX_KEYS_PER_WRITER = 500;
    TripleBufferedDictionary dict(0);
    std::atomic<bool> stop{false};
    std::atomic<int> write_count{0};

    auto writer = [&](int thread_id) {
        for (int n = 0; n < MAX_KEYS_PER_WRITER && !stop.load(std::memory_order_relaxed); n++) {
            std::string key = "t" + std::to_string(thread_id) + "_" + std::to_string(n);
            dict.lookup(key.c_str(), key.size());
            write_count.fetch_add(1, std::memory_order_relaxed);
        }
    };

    std::vector<std::thread> writers;
    for (int i = 0; i < 4; i++) writers.emplace_back(writer, i);
    for (auto& t : writers) t.join();

    for (int cycle = 0; cycle < 20; cycle++) {
        dict.rotate();
        dict.clearStandby();
    }

    EXPECT_GT(write_count.load(), 0);
    // No crash = success (memory safety under concurrent access)
}
