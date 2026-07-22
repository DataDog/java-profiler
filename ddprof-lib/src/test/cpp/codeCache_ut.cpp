/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "codeCache.h"

// memoryUsage() must reflect the actual per-symbol name length, not a fixed
// per-symbol constant: adding one symbol grows the reported usage by exactly
// the allocation size of its name string.
TEST(CodeCacheTest, MemoryUsageCountsSymbolNameLength) {
    CodeCache cc("testlib");
    long long base = cc.memoryUsage();

    const char *name =
        "a_long_symbol_name_well_beyond_sizeof_NativeFunc_padding_xxxxxxxxxxxx";
    cc.add(reinterpret_cast<const void *>(0x1000), 16, name);

    EXPECT_EQ(NativeFunc::allocSize(name), (size_t)(cc.memoryUsage() - base));
}

// A longer name costs more than a shorter one — the reported size scales with
// the actual symbol-name length.
TEST(CodeCacheTest, MemoryUsageGrowsWithNameLength) {
    CodeCache shortc("lib");
    CodeCache longc("lib");
    long long short_base = shortc.memoryUsage();
    long long long_base = longc.memoryUsage();

    shortc.add(reinterpret_cast<const void *>(0x1000), 8, "f");
    longc.add(reinterpret_cast<const void *>(0x1000), 8,
              "an_extremely_long_symbol_name_padded_out_further_and_further_1234");

    EXPECT_GT(longc.memoryUsage() - long_base, shortc.memoryUsage() - short_base);
}

// A freshly-constructed, empty cache reports exactly the blob array (counted at
// the full CodeBlob size, not a pointer's worth) plus its own name — nothing
// more. An exact check so over-counting or an inflated constant would fail.
TEST(CodeCacheTest, MemoryUsageCountsFullBlobArray) {
    CodeCache cc("lib");
    EXPECT_EQ((long long)INITIAL_CODE_CACHE_CAPACITY * sizeof(CodeBlob)
                  + (long long)NativeFunc::allocSize("lib"),
              cc.memoryUsage());
}

// The DWARF unwind table contributes length * sizeof(FrameDesc). Populate it so
// a regression (e.g. * flipped to /) in that term is caught; the table is
// zero-length in the other tests.
TEST(CodeCacheTest, MemoryUsageCountsDwarfTable) {
    CodeCache cc("lib");
    long long base = cc.memoryUsage();

    const int entries = 7;
    // setDwarfTable() takes ownership; ~CodeCache frees it. Contents are
    // irrelevant here — memoryUsage() reads only the length.
    FrameDesc *table = (FrameDesc *)malloc(entries * sizeof(FrameDesc));
    cc.setDwarfTable(table, entries);

    EXPECT_EQ((long long)entries * sizeof(FrameDesc), cc.memoryUsage() - base);
}

// Copying a CodeCache must deep-copy each blob's name string. With the previous
// shallow memcpy the copy shared the originals' _name pointers, so destroying
// both double-freed them. Here both copies are populated, sized equally, and
// destroyed — a double-free would abort (or trip ASan).
TEST(CodeCacheTest, CopyIsDeepAndDoesNotDoubleFree) {
    CodeCache src("lib");
    src.add(reinterpret_cast<const void *>(0x1000), 16, "sym_one");
    src.add(reinterpret_cast<const void *>(0x2000), 16, "sym_two_longer_name");
    long long expected = src.memoryUsage();

    {
        CodeCache copy(src);
        EXPECT_EQ(expected, copy.memoryUsage());
    }  // copy destroyed — must not free src's name strings

    EXPECT_EQ(expected, src.memoryUsage());  // src's names still intact
}  // src destroyed — no double free

// CodeCacheArray::memoryUsage() is the aggregation production actually consumes
// (Profiler::dump()). Verify it sums the per-library values — guards the loop
// bound and the accumulation against regressions the per-instance tests miss.
TEST(CodeCacheTest, ArrayMemoryUsageSumsLibraries) {
    CodeCacheArray arr;
    CodeCache *a = new CodeCache("liba");
    CodeCache *b = new CodeCache("libb");
    // Populate before registering: add() must run pre-publication.
    a->add(reinterpret_cast<const void *>(0x1000), 16, "alpha_symbol");
    b->add(reinterpret_cast<const void *>(0x2000), 16, "beta_symbol_longer_name");

    long long expected = (long long)a->memoryUsage() + (long long)b->memoryUsage();
    ASSERT_TRUE(arr.add(a));
    ASSERT_TRUE(arr.add(b));
    EXPECT_EQ(expected, (long long)arr.memoryUsage());

    // CodeCacheArray does not own the entries.
    delete a;
    delete b;
}
