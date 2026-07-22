/*
 * Copyright 2025, 2026 Datadog, Inc
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
#include "nativeMem.h"
#include <climits>
#include <cstdio>
#include <cstring>
#include <map>

// ── Dictionary ─────────────────────────────────────────────────────────────

TEST(DictionaryTest, LookupReturnsSameIdForSameKey) {
    Dictionary d(0);
    unsigned int id1 = d.lookup("hello", 5);
    EXPECT_GT(id1, 0U);
    EXPECT_EQ(id1, d.lookup("hello", 5));
}

// Native-memory accounting must balance: growth is tracked, clear() returns to
// the root-table baseline, and destruction releases everything. Exercises the
// per-key strlen-at-free path and the overflow-table inc/dec pairing.
TEST(DictionaryTest, NativeMemAccountingBalancesAcrossLifecycle) {
    long long before = NativeMem::live(NM_DICTIONARY);
    {
        Dictionary d(0);
        long long after_ctor = NativeMem::live(NM_DICTIONARY);
        EXPECT_GT(after_ctor, before);  // root table counted

        for (int i = 0; i < 5000; i++) {
            char key[32];
            snprintf(key, sizeof(key), "symbol_%d", i);
            d.lookup(key, strlen(key));  // inserts key strings + overflow tables
        }
        EXPECT_GT(NativeMem::live(NM_DICTIONARY), after_ctor);  // grew

        d.clear();
        // Keys + overflow tables freed; root table retained.
        EXPECT_EQ(after_ctor, NativeMem::live(NM_DICTIONARY));
    }
    EXPECT_EQ(before, NativeMem::live(NM_DICTIONARY));  // fully released
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
