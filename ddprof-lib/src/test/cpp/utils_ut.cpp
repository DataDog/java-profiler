/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include <cstdlib>
#include "../../main/cpp/utils.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char UTILS_TEST_NAME[] = "UtilsTest";

class GlobalSetup {
public:
    GlobalSetup() {
        installGtestCrashHandler<UTILS_TEST_NAME>();
    }
    ~GlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

static GlobalSetup global_setup;

TEST(UtilsTest, IsAlignedNullPointer) {
    // NULL should be aligned to any power-of-2
    EXPECT_TRUE(is_aligned((void*)0x0, 1));
    EXPECT_TRUE(is_aligned((void*)0x0, 2));
    EXPECT_TRUE(is_aligned((void*)0x0, 4));
    EXPECT_TRUE(is_aligned((void*)0x0, 8));
    EXPECT_TRUE(is_aligned((void*)0x0, 16));
}

TEST(UtilsTest, IsAlignedValidPointers) {
    // Aligned addresses
    EXPECT_TRUE(is_aligned((void*)0x1000, 8)) << "0x1000 should be 8-byte aligned";
    EXPECT_TRUE(is_aligned((void*)0x1008, 8)) << "0x1008 should be 8-byte aligned";
    EXPECT_TRUE(is_aligned((void*)0x2000, 16)) << "0x2000 should be 16-byte aligned";
    EXPECT_TRUE(is_aligned((void*)0x1000, 4)) << "0x1000 should be 4-byte aligned";

    // Common heap addresses are typically aligned to sizeof(void*)
    void* heap_mem = malloc(64);
    ASSERT_NE(heap_mem, nullptr);
    EXPECT_TRUE(is_aligned(heap_mem, sizeof(void*)))
        << "malloc() should return pointer aligned to sizeof(void*)";
    free(heap_mem);
}

TEST(UtilsTest, IsAlignedUnalignedPointers) {
    // Unaligned addresses
    EXPECT_FALSE(is_aligned((void*)0x1001, 8)) << "0x1001 is not 8-byte aligned (off by 1)";
    EXPECT_FALSE(is_aligned((void*)0x1002, 8)) << "0x1002 is not 8-byte aligned (off by 2)";
    EXPECT_FALSE(is_aligned((void*)0x1007, 8)) << "0x1007 is not 8-byte aligned (off by 7)";
    EXPECT_FALSE(is_aligned((void*)0x100F, 16)) << "0x100F is not 16-byte aligned (off by 15)";
    EXPECT_FALSE(is_aligned((void*)0x2001, 2)) << "0x2001 is not 2-byte aligned";
}

TEST(UtilsTest, IsAlignedPowerOf2Sizes) {
    // Test various power-of-2 alignments on the same address
    void* addr = (void*)0x1000;
    EXPECT_TRUE(is_aligned(addr, 1));
    EXPECT_TRUE(is_aligned(addr, 2));
    EXPECT_TRUE(is_aligned(addr, 4));
    EXPECT_TRUE(is_aligned(addr, 8));
    EXPECT_TRUE(is_aligned(addr, 16));
    EXPECT_TRUE(is_aligned(addr, 256));
    EXPECT_TRUE(is_aligned(addr, 4096));
}

TEST(UtilsTest, IsAlignedCriticalBugCheck) {
    // This test specifically catches the inverted logic bug where
    // is_aligned() was incorrectly using ~(alignment-1) instead of (alignment-1)

    void* aligned_ptr = (void*)0x1000;
    void* unaligned_ptr = (void*)0x1001;

    // With correct logic:
    //   aligned: (0x1000 & 0x7) == 0 → true ✓
    //   unaligned: (0x1001 & 0x7) == 1 → false ✓

    // With INVERTED logic (the bug):
    //   aligned: (0x1000 & ~0x7) == 0x1000 != 0 → false ✗
    //   unaligned: (0x1001 & ~0x7) == 0x1000 != 0 → false ✗

    ASSERT_TRUE(is_aligned(aligned_ptr, 8))
        << "CRITICAL BUG: is_aligned() returns false for aligned pointer 0x1000! "
        << "This suggests the alignment check logic is inverted. "
        << "Expected: (ptr & (alignment-1)) == 0, "
        << "Got: (ptr & ~(alignment-1)) == 0";

    ASSERT_FALSE(is_aligned(unaligned_ptr, 8))
        << "is_aligned() should return false for unaligned pointer 0x1001";
}

TEST(UtilsTest, AlignUpBasic) {
    EXPECT_EQ(align_up(0, 8), 0);
    EXPECT_EQ(align_up(1, 8), 8);
    EXPECT_EQ(align_up(7, 8), 8);
    EXPECT_EQ(align_up(8, 8), 8);
    EXPECT_EQ(align_up(9, 8), 16);
    EXPECT_EQ(align_up(15, 8), 16);
    EXPECT_EQ(align_up(16, 8), 16);
}

TEST(UtilsTest, AlignDownBasic) {
    EXPECT_EQ(align_down(0, 8), 0);
    EXPECT_EQ(align_down(1, 8), 0);
    EXPECT_EQ(align_down(7, 8), 0);
    EXPECT_EQ(align_down(8, 8), 8);
    EXPECT_EQ(align_down(9, 8), 8);
    EXPECT_EQ(align_down(15, 8), 8);
    EXPECT_EQ(align_down(16, 8), 16);
}

TEST(UtilsTest, IsPowerOf2) {
    EXPECT_FALSE(is_power_of_2(0));
    EXPECT_TRUE(is_power_of_2(1));
    EXPECT_TRUE(is_power_of_2(2));
    EXPECT_FALSE(is_power_of_2(3));
    EXPECT_TRUE(is_power_of_2(4));
    EXPECT_FALSE(is_power_of_2(5));
    EXPECT_TRUE(is_power_of_2(8));
    EXPECT_TRUE(is_power_of_2(16));
    EXPECT_TRUE(is_power_of_2(256));
    EXPECT_FALSE(is_power_of_2(255));
}
