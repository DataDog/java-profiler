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

// ── DoubleBufferedDictionary ────────────────────────────────────────────────

class DoubleBufferedDictionaryTest : public ::testing::Test {
protected:
    // id=1 exercises the named counter slot (DICTIONARY_CLASSES_*)
    DoubleBufferedDictionary dict{1};
};

TEST_F(DoubleBufferedDictionaryTest, LookupGoesToActive) {
    unsigned int id = dict.lookup("cls", 3);
    EXPECT_GT(id, 0U);
    EXPECT_EQ(id, dict.lookup("cls", 3));
}

TEST_F(DoubleBufferedDictionaryTest, BoundedLookupGoesToActive) {
    unsigned int id = dict.bounded_lookup("ep", 2, 100);
    EXPECT_NE(id, static_cast<unsigned int>(INT_MAX));
    EXPECT_EQ(id, dict.bounded_lookup("ep", 2, 100));
}

TEST_F(DoubleBufferedDictionaryTest, RotateMakesOldActiveReadableAsStandby) {
    unsigned int id = dict.lookup("cls", 3);
    dict.rotate();

    std::map<unsigned int, const char*> snap;
    dict.standby()->collect(snap);
    ASSERT_EQ(snap.size(), 1U);
    EXPECT_STREQ(snap.begin()->second, "cls");
    EXPECT_EQ(snap.begin()->first, id);
}

TEST_F(DoubleBufferedDictionaryTest, InsertsAfterRotateGoToNewActiveNotStandby) {
    dict.lookup("a", 1);
    dict.rotate();
    dict.lookup("b", 1);  // must land in new active, not standby

    std::map<unsigned int, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(snap.size(), 1U);  // only "a"

    // "b" is in the new active
    std::map<unsigned int, const char*> active_snap;
    // rotate once more to promote new active → standby
    dict.rotate();
    dict.standby()->collect(active_snap);
    EXPECT_EQ(active_snap.size(), 1U);  // only "b"
}

TEST_F(DoubleBufferedDictionaryTest, ClearStandbyDoesNotAffectActiveEntries) {
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

TEST_F(DoubleBufferedDictionaryTest, StandbyIsEmptyAfterClearStandbyAndRotate) {
    dict.lookup("a", 1);
    dict.rotate();
    dict.clearStandby();  // frees "a"
    // After clear, old-active buffer is empty; promote it back to standby
    dict.rotate();
    std::map<unsigned int, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(snap.size(), 0U);
}

TEST_F(DoubleBufferedDictionaryTest, MultiCycleRotateAndClearIsStable) {
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

TEST_F(DoubleBufferedDictionaryTest, ClearAllResetsActiveToo) {
    dict.lookup("x", 1);
    dict.rotate();
    dict.lookup("y", 1);
    dict.clearAll();

    // Both buffers should be empty; promote to standby to verify
    std::map<unsigned int, const char*> snap;
    dict.standby()->collect(snap);
    EXPECT_EQ(snap.size(), 0U);

    dict.rotate();
    dict.standby()->collect(snap);
    EXPECT_EQ(snap.size(), 0U);
}

// ── DoubleBufferedDictionary — counter-id ownership ────────────────────────
// The active buffer always owns the real counter id; the standby buffer always
// carries id=0.  This drives correct counter targeting without COUNTERS being
// defined in the test build (Counters::set/get are no-ops there).

TEST_F(DoubleBufferedDictionaryTest, StandbyStartsWithIdZero) {
    // id=1 passed to constructor → active (_a) holds id=1, standby (_b) holds id=0.
    EXPECT_EQ(0, dict.standby()->counterId());
}

TEST_F(DoubleBufferedDictionaryTest, RotateMovesIdZeroToNewStandby) {
    // Invariant: standby always has id=0 regardless of how many rotates happened.
    for (int i = 0; i < 6; i++) {
        dict.rotate();
        EXPECT_EQ(0, dict.standby()->counterId()) << "after rotate #" << (i + 1);
    }
}

TEST_F(DoubleBufferedDictionaryTest, ClearStandbyKeepsStandbyAtIdZero) {
    dict.rotate();
    dict.clearStandby();
    // standby still has id=0 after clear.
    EXPECT_EQ(0, dict.standby()->counterId());
    // And a subsequent rotate still produces standby with id=0.
    dict.rotate();
    EXPECT_EQ(0, dict.standby()->counterId());
}

// ── DoubleBufferedDictionary — concurrent writes during rotate ─────────────

TEST(DoubleBufferedDictionaryConcurrentTest, WritersDuringRotateProduceNoCorruption) {
    DoubleBufferedDictionary dict(0);
    std::atomic<bool> stop{false};
    std::atomic<int> write_count{0};

    // Writer threads continuously insert unique keys
    auto writer = [&](int thread_id) {
        int n = 0;
        while (!stop.load(std::memory_order_relaxed)) {
            std::string key = "t" + std::to_string(thread_id) + "_" + std::to_string(n++);
            dict.lookup(key.c_str(), key.size());
            write_count.fetch_add(1, std::memory_order_relaxed);
        }
    };

    std::vector<std::thread> writers;
    for (int i = 0; i < 4; i++) writers.emplace_back(writer, i);

    // Perform several rotate+collect+clear cycles from the "dump thread"
    int collected_total = 0;
    for (int cycle = 0; cycle < 20; cycle++) {
        dict.rotate();
        std::map<unsigned int, const char*> snap;
        dict.standby()->collect(snap);
        collected_total += static_cast<int>(snap.size());
        dict.clearStandby();
    }

    stop.store(true, std::memory_order_relaxed);
    for (auto& t : writers) t.join();

    // Sanity: at least some writes were collected across cycles
    EXPECT_GT(collected_total, 0);
    // No crash = success (memory safety under concurrent access)
}
