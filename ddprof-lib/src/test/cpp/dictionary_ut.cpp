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
    ASSERT_NE(0U, id1);
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
            ASSERT_NE(0U, mustLookup(d, key, strlen(key)));  // key strings + overflow tables
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
    ASSERT_NE(0U, a);
    ASSERT_NE(0U, b);
    EXPECT_NE(a, b);
}

TEST(DictionaryTest, BoundedLookupSkipsInsertWhenAtLimit) {
    Dictionary d(0);
    ASSERT_NE(0U, mustLookup(d, "key1", 4));
    // size is 1, limit is 1 → insert not allowed
    unsigned int r = d.bounded_lookup("key2", 4, 1);
    EXPECT_EQ(r, static_cast<unsigned int>(INT_MAX));
}

TEST(DictionaryTest, BoundedLookupReturnsExistingIdWhenAtLimit) {
    Dictionary d(0);
    unsigned int existing = mustLookup(d, "key1", 4);
    ASSERT_NE(0U, existing);
    // size is 1, limit is 1 → existing key still found
    EXPECT_EQ(existing, d.bounded_lookup("key1", 4, 1));
}

TEST(DictionaryTest, CollectReturnsAllInsertedEntries) {
    Dictionary d(0);
    ASSERT_NE(0U, mustLookup(d, "a", 1));
    ASSERT_NE(0U, mustLookup(d, "b", 1));
    ASSERT_NE(0U, mustLookup(d, "c", 1));
    std::map<unsigned int, const char*> m;
    d.collect(m);
    EXPECT_EQ(m.size(), 3U);
}

TEST(DictionaryTest, ClearResetsToEmpty) {
    Dictionary d(0);
    ASSERT_NE(0U, mustLookup(d, "x", 1));
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
        ASSERT_NE(0U, mustLookup(d, key, strlen(key)));
    }
    long long live_before = NativeMem::live(NM_DICTIONARY);

    d.failTableAllocationForTest(true);
    long long added_bytes = 0;
    int zero_returns = 0;
    for (int i = 0; i < 20000; i++) {
        snprintf(key, sizeof(key), "new_%d", i);
        if (d.lookup(key, strlen(key)) != 0) {  // a failed insert must not crash
            added_bytes += (long long)strlen(key) + 1;
        } else {
            zero_returns++;
        }
    }
    EXPECT_GT(d.tableAllocFailuresForTest(), 0) << "no insert needed an overflow table";
    // Every refused table allocation fails its insert with 0.
    EXPECT_GE(zero_returns, d.tableAllocFailuresForTest());
    EXPECT_GT(added_bytes, 0);  // keys that fit were still added
    // Only the keys that were inserted are accounted: failures leak nothing and
    // no table was allocated.
    EXPECT_EQ(live_before + added_bytes, NativeMem::live(NM_DICTIONARY));

    EXPECT_GT(d.lookup("fill_0", 6), 0U);  // existing keys still resolve
    d.failTableAllocationForTest(false);
    EXPECT_NE(0U, mustLookup(d, "after_recovery", 14));
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

// A failed key malloc must fail the insert (return 0) without touching the
// accounting; removing the NULL check dereferences the missing key.
TEST(DictionaryTest, KeyAllocationFailureFailsTheInsert) {
    Dictionary d(0);
    ASSERT_NE(0U, mustLookup(d, "present", 7));
    long long live_before = NativeMem::live(NM_DICTIONARY);

    d.failKeyAllocationForTest(true);
    EXPECT_EQ(0U, d.lookup("absent", 6));
    EXPECT_EQ(1, d.keyAllocFailuresForTest());  // the failure path was reached
    EXPECT_EQ(live_before, NativeMem::live(NM_DICTIONARY));
    EXPECT_NE(0U, d.lookup("present", 7));  // existing keys need no allocation
    d.failKeyAllocationForTest(false);

    std::map<unsigned int, const char*> m;
    d.collect(m);
    EXPECT_EQ(1U, m.size());  // "absent" was not inserted
    EXPECT_NE(0U, mustLookup(d, "absent", 6));
}

// Fault-injection builds fail a key allocation at random, which a SymbolDictionary
// reports as UNRESOLVED_ID; retry until the insert yields a real id.
static unsigned int mustLookupSymbol(SymbolDictionary &d, const char *key) {
    for (int attempt = 0; attempt < 1000; attempt++) {
        unsigned int id = d.lookup(key);
        if (id != SymbolDictionary::UNRESOLVED_ID) return id;
    }
    ADD_FAILURE() << "insert of '" << key << "' kept failing";
    return SymbolDictionary::UNRESOLVED_ID;
}

// The pool must contain the entry every failed insert resolved to, and only then.
TEST(DictionaryTest, SymbolDictionaryCollectAddsUnresolvedEntryOnlyAfterFailure) {
    SymbolDictionary d;
    ASSERT_NE(SymbolDictionary::UNRESOLVED_ID, mustLookupSymbol(d, "ok"));
    std::map<unsigned int, const char*> before;
    d.collect(before);
#ifndef __FAULT_INJECTION__
    EXPECT_FALSE(d.failed());
    EXPECT_EQ(0U, before.count(SymbolDictionary::UNRESOLVED_ID));
#endif

    d.failKeyAllocationForTest(true);
    EXPECT_EQ(SymbolDictionary::UNRESOLVED_ID, d.lookup("lost"));
    d.failKeyAllocationForTest(false);
    EXPECT_TRUE(d.failed());

    std::map<unsigned int, const char*> after;
    d.collect(after);
    ASSERT_EQ(1U, after.count(SymbolDictionary::UNRESOLVED_ID));
    EXPECT_STREQ("<unresolved>", after[SymbolDictionary::UNRESOLVED_ID]);
    EXPECT_EQ(0U, after.count(0));  // 0 means "no entry" and is never emitted
}

// The one-argument overload must derive the length itself and share ids with the
// two-argument form.
TEST(DictionaryTest, SymbolDictionaryOneArgLookupMatchesTwoArgLookup) {
    SymbolDictionary d;
    unsigned int id = mustLookupSymbol(d, "abcdef");
    ASSERT_NE(SymbolDictionary::UNRESOLVED_ID, id);
    EXPECT_EQ(id, d.lookup("abcdef", 6));
    unsigned int longer = mustLookupSymbol(d, "abcdefg");
    EXPECT_NE(SymbolDictionary::UNRESOLVED_ID, longer);
    EXPECT_NE(id, longer);  // full length, not a prefix match
}

// A failed signature insert must resolve to a valid method descriptor: JFR
// consumers slice a descriptor at ')', so "<unresolved>" would crash them. Name
// and signature failures are tracked apart, so each adds only its own entry.
TEST(DictionaryTest, SymbolDictionarySignatureFailureResolvesToValidDescriptor) {
    SymbolDictionary d;
    d.failKeyAllocationForTest(true);
    EXPECT_EQ(SymbolDictionary::UNRESOLVED_SIG_ID, d.lookupSignature("(I)V"));
    d.failKeyAllocationForTest(false);
    EXPECT_TRUE(d.failed());

    std::map<unsigned int, const char*> m;
    d.collect(m);
    ASSERT_EQ(1U, m.count(SymbolDictionary::UNRESOLVED_SIG_ID));
    const char *descriptor = m[SymbolDictionary::UNRESOLVED_SIG_ID];
    ASSERT_NE(nullptr, strchr(descriptor, ')'));
    EXPECT_EQ('(', descriptor[0]);
    EXPECT_EQ(0U, m.count(SymbolDictionary::UNRESOLVED_ID));  // no name failed

    SymbolDictionary names;
    names.failKeyAllocationForTest(true);
    EXPECT_EQ(SymbolDictionary::UNRESOLVED_ID, names.lookup("name"));
    names.failKeyAllocationForTest(false);
    std::map<unsigned int, const char*> nm;
    names.collect(nm);
    EXPECT_EQ(1U, nm.count(SymbolDictionary::UNRESOLVED_ID));
    EXPECT_EQ(0U, nm.count(SymbolDictionary::UNRESOLVED_SIG_ID));  // no signature failed
}

// The signature overloads share ids with the name lookups of the same key.
TEST(DictionaryTest, SymbolDictionaryLookupSignatureMatchesLookup) {
    SymbolDictionary d;
    unsigned int id = mustLookupSymbol(d, "(J)V");
    ASSERT_NE(SymbolDictionary::UNRESOLVED_ID, id);
    EXPECT_EQ(id, d.lookupSignature("(J)V"));
    EXPECT_EQ(id, d.lookupSignature("(J)V", 4));
}
