/*
 * Copyright 2025, 2026, Datadog, Inc.
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

// Fault-injection builds fail a key allocation at random, so an insert that must
// succeed retries; without injection it succeeds on the first try.
static unsigned int mustLookup(Dictionary &d, const char *key, size_t length) {
    for (int attempt = 0; attempt < 1000; attempt++) {
        unsigned int id = d.lookup(key, length);
        if (id != 0) return id;
    }
    ADD_FAILURE() << "insert of '" << key << "' kept failing";
    return 0;
}

TEST(DictionaryTest, LookupReturnsSameIdForSameKey) {
    Dictionary d(0);
    unsigned int id1 = mustLookup(d, "hello", 5);
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
            mustLookup(d, key, strlen(key));  // inserts key strings + overflow tables
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
    unsigned int a = mustLookup(d, "alpha", 5);
    unsigned int b = mustLookup(d, "beta",  4);
    EXPECT_NE(a, b);
}

TEST(DictionaryTest, BoundedLookupSkipsInsertWhenAtLimit) {
    Dictionary d(0);
    mustLookup(d, "key1", 4);
    // size is 1, limit is 1 → insert not allowed
    unsigned int r = d.bounded_lookup("key2", 4, 1);
    EXPECT_EQ(r, static_cast<unsigned int>(INT_MAX));
}

TEST(DictionaryTest, BoundedLookupReturnsExistingIdWhenAtLimit) {
    Dictionary d(0);
    unsigned int existing = mustLookup(d, "key1", 4);
    // size is 1, limit is 1 → existing key still found
    EXPECT_EQ(existing, d.bounded_lookup("key1", 4, 1));
}

TEST(DictionaryTest, CollectReturnsAllInsertedEntries) {
    Dictionary d(0);
    mustLookup(d, "a", 1);
    mustLookup(d, "b", 1);
    mustLookup(d, "c", 1);
    std::map<unsigned int, const char*> m;
    d.collect(m);
    EXPECT_EQ(m.size(), 3U);
}

TEST(DictionaryTest, ClearResetsToEmpty) {
    Dictionary d(0);
    mustLookup(d, "x", 1);
    d.clear();
    std::map<unsigned int, const char*> m;
    d.collect(m);
    EXPECT_EQ(m.size(), 0U);
}

// A failed overflow-table calloc must fail the insert, not be stored through.
TEST(DictionaryTest, OverflowTableAllocationFailureFailsTheInsert) {
    Dictionary d(0);
    char key[32];
    for (int i = 0; i < 5000; i++) {  // fills the root table and some overflow tables
        snprintf(key, sizeof(key), "fill_%d", i);
        mustLookup(d, key, strlen(key));
    }
    long long live_before = NativeMem::live(NM_DICTIONARY);

    d.failTableAllocationForTest(true);
    long long added_bytes = 0;
    for (int i = 0; i < 20000; i++) {
        snprintf(key, sizeof(key), "new_%d", i);
        if (d.lookup(key, strlen(key)) != 0) {  // a failed insert must not crash
            added_bytes += (long long)strlen(key) + 1;
        }
    }
    EXPECT_GT(d.tableAllocFailuresForTest(), 0) << "no insert needed an overflow table";
    EXPECT_GT(added_bytes, 0);  // keys that fit were still added
    // Only the keys that were inserted are accounted: failures leak nothing and
    // no table was allocated.
    EXPECT_EQ(live_before + added_bytes, NativeMem::live(NM_DICTIONARY));

    EXPECT_GT(d.lookup("fill_0", 6), 0U);  // existing keys still resolve
    d.failTableAllocationForTest(false);
    EXPECT_GT(mustLookup(d, "after_recovery", 14), 0U);
}

// A failed insert must never hand a caller id 0: it resolves to UNRESOLVED_ID,
// and the dictionary reports the failure so the owner can emit that entry.
TEST(DictionaryTest, SymbolDictionaryResolvesFailedInsertsToUnresolvedId) {
    SymbolDictionary d;
    char key[32];
    for (int i = 0; i < 3 * TABLE_CAPACITY; i++) {
        snprintf(key, sizeof(key), "fill_%d", i);
        ASSERT_NE(0U, d.lookup(key, strlen(key)));
    }
#ifndef __FAULT_INJECTION__
    EXPECT_FALSE(d.failed());  // injection can fail a key insert at random
#endif

    d.failTableAllocationForTest(true);
    int unresolved = 0;
    for (int i = 0; i < 20000; i++) {
        snprintf(key, sizeof(key), "new_%d", i);
        unsigned int id = d.lookup(key, strlen(key));
        ASSERT_NE(0U, id);
        if (id == SymbolDictionary::UNRESOLVED_ID) unresolved++;
    }
    EXPECT_GT(d.tableAllocFailuresForTest(), 0);
    EXPECT_GT(unresolved, 0);
    EXPECT_TRUE(d.failed());
}
