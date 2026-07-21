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

// The blob array is counted at the full CodeBlob size (a CodeBlob is several
// pointers wide): an empty cache already accounts for
// capacity * sizeof(CodeBlob) plus its own name.
TEST(CodeCacheTest, MemoryUsageCountsFullBlobArray) {
    CodeCache cc("lib");
    long long usage = cc.memoryUsage();
    EXPECT_GT(usage, (long long)(INITIAL_CODE_CACHE_CAPACITY * sizeof(CodeBlob)));
    // Sanity: a pointer-sized count would be far smaller than the real array.
    EXPECT_GT((long long)(INITIAL_CODE_CACHE_CAPACITY * sizeof(CodeBlob)),
              (long long)(INITIAL_CODE_CACHE_CAPACITY * sizeof(CodeBlob *)));
}
