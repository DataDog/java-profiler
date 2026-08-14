/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <map>
#include <unordered_set>
#include "countingAllocator.h"
#include "nativeMem.h"

class CountingAllocatorTest : public ::testing::Test {
protected:
    long long _baseline;

    void SetUp() override {
        _baseline = NativeMem::live(NM_MISC);
    }
    void TearDown() override {
        NativeMem::setLive(NM_MISC, _baseline);
    }
};

// allocate()/deallocate() report the exact requested byte count into the
// category's live gauge.
TEST_F(CountingAllocatorTest, AllocateAndDeallocateTrackLiveBytes) {
    CountingAllocator<int, NM_MISC> alloc;
    int *p = alloc.allocate(4);
    EXPECT_EQ(_baseline + (long long)(4 * sizeof(int)), NativeMem::live(NM_MISC));

    alloc.deallocate(p, 4);
    EXPECT_EQ(_baseline, NativeMem::live(NM_MISC));
}

// STL containers rebind Allocator<value_type> to their internal node type
// before calling allocate(), so the recorded size is the real per-node byte
// count -- not sizeof(value_type).
TEST_F(CountingAllocatorTest, RebindReportsRealNodeSizeNotValueTypeSize) {
    using TestMap = std::map<int, int, std::less<int>,
                             CountingAllocator<std::pair<const int, int>, NM_MISC>>;
    TestMap m;
    m.insert({1, 1});
    long long after_one_insert = NativeMem::live(NM_MISC) - _baseline;
    // A map node is at least the tree-node overhead (parent/child pointers,
    // color bit) plus the value_type -- strictly larger than sizeof(value_type).
    EXPECT_GT(after_one_insert, (long long)sizeof(std::pair<const int, int>));

    m.insert({2, 2});
    long long after_two_inserts = NativeMem::live(NM_MISC) - _baseline;
    EXPECT_EQ(2 * after_one_insert, after_two_inserts);

    m.clear();
    EXPECT_EQ(_baseline, NativeMem::live(NM_MISC));
}

// erase() deallocates the node, returning the gauge to its pre-insert value.
TEST_F(CountingAllocatorTest, EraseBalancesInsert) {
    using TestSet = std::unordered_set<int, std::hash<int>, std::equal_to<int>,
                                       CountingAllocator<int, NM_MISC>>;
    TestSet s;
    s.reserve(8);
    long long before_insert = NativeMem::live(NM_MISC);
    s.insert(42);
    EXPECT_GT(NativeMem::live(NM_MISC), before_insert);

    s.erase(42);
    EXPECT_EQ(before_insert, NativeMem::live(NM_MISC));
}
