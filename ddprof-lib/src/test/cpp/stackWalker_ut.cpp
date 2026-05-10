/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include "../../main/cpp/stackWalker.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char STACKWALKER_TEST_NAME[] = "StackWalkerTest";

class StackWalkerTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<STACKWALKER_TEST_NAME>();
    }

    void TearDown() override {
        restoreDefaultSignalHandlers();
    }

    // Helper to create a frame with a non-NULL method_id
    static ASGCT_CallFrame knownFrame(int id) {
        ASGCT_CallFrame f = {};
        f.bci = 0;
        f.method_id = (jmethodID)(uintptr_t)(id + 1);  // non-NULL
        return f;
    }

    // Helper to create a frame with NULL method_id (unknown)
    static ASGCT_CallFrame unknownFrame() {
        ASGCT_CallFrame f = {};
        f.bci = 0;
        f.method_id = NULL;
        return f;
    }
};

TEST_F(StackWalkerTest, dropUnknownLeaf_empty_trace) {
    ASGCT_CallFrame frames[1];
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 0);
    EXPECT_EQ(0, depth);
}

TEST_F(StackWalkerTest, dropUnknownLeaf_single_unknown_frame) {
    ASGCT_CallFrame frames[1] = { unknownFrame() };
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 1);
    EXPECT_EQ(0, depth);
}

TEST_F(StackWalkerTest, dropUnknownLeaf_single_known_frame) {
    ASGCT_CallFrame frames[1] = { knownFrame(1) };
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 1);
    EXPECT_EQ(1, depth);
    EXPECT_NE(nullptr, frames[0].method_id);
}

TEST_F(StackWalkerTest, dropUnknownLeaf_unknown_leaf_with_known_callers) {
    // frames[0] is the leaf (top of stack), frames[1..2] are callers
    ASGCT_CallFrame frames[3] = { unknownFrame(), knownFrame(1), knownFrame(2) };
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 3);
    EXPECT_EQ(2, depth);
    // The former frames[1] and frames[2] should now be at [0] and [1]
    EXPECT_EQ((jmethodID)(uintptr_t)2, frames[0].method_id);
    EXPECT_EQ((jmethodID)(uintptr_t)3, frames[1].method_id);
}

TEST_F(StackWalkerTest, dropUnknownLeaf_known_leaf_not_dropped) {
    ASGCT_CallFrame frames[3] = { knownFrame(1), knownFrame(2), knownFrame(3) };
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 3);
    EXPECT_EQ(3, depth);
    EXPECT_EQ((jmethodID)(uintptr_t)2, frames[0].method_id);
    EXPECT_EQ((jmethodID)(uintptr_t)3, frames[1].method_id);
    EXPECT_EQ((jmethodID)(uintptr_t)4, frames[2].method_id);
}

TEST_F(StackWalkerTest, dropUnknownLeaf_unknown_non_leaf_not_dropped) {
    // Only the leaf (index 0) should be checked — unknown at other positions stays
    ASGCT_CallFrame frames[3] = { knownFrame(1), unknownFrame(), knownFrame(2) };
    int depth = StackWalkValidation::dropUnknownLeaf(frames, 3);
    EXPECT_EQ(3, depth);
    EXPECT_NE(nullptr, frames[0].method_id);
    EXPECT_EQ(nullptr, frames[1].method_id);
    EXPECT_NE(nullptr, frames[2].method_id);
}

// ---- isValidFP ----

TEST_F(StackWalkerTest, isValidFP_null_is_invalid) {
    EXPECT_FALSE(StackWalkValidation::isValidFP(0));
}

TEST_F(StackWalkerTest, isValidFP_low_address_is_invalid) {
    EXPECT_FALSE(StackWalkValidation::isValidFP(0x100));       // below DEAD_ZONE (0x1000)
    EXPECT_FALSE(StackWalkValidation::isValidFP(0xfff));
}

TEST_F(StackWalkerTest, isValidFP_high_address_is_invalid) {
    // Within DEAD_ZONE of UINTPTR_MAX (i.e. >= -DEAD_ZONE)
    EXPECT_FALSE(StackWalkValidation::isValidFP(~(uintptr_t)0));         // UINTPTR_MAX
    EXPECT_FALSE(StackWalkValidation::isValidFP(~(uintptr_t)0 - 0x100)); // still in dead zone
}

TEST_F(StackWalkerTest, isValidFP_misaligned_is_invalid) {
    // Aligned address in valid range but with low bits set
    EXPECT_FALSE(StackWalkValidation::isValidFP(0x10001));  // odd
    EXPECT_FALSE(StackWalkValidation::isValidFP(0x10002));  // 2-byte aligned but not pointer-aligned
}

TEST_F(StackWalkerTest, isValidFP_valid_aligned_address) {
    // Aligned addresses well within valid range should pass
    EXPECT_TRUE(StackWalkValidation::isValidFP(0x10000));
    EXPECT_TRUE(StackWalkValidation::isValidFP(0x7fff0000));
}

// ---- isValidSP ----

TEST_F(StackWalkerTest, isValidSP_must_be_strictly_above_lo) {
    uintptr_t lo = 0x1000;
    uintptr_t hi = 0x5000;
    EXPECT_FALSE(StackWalkValidation::isValidSP(lo, lo, hi));      // sp == lo: not strictly above
    EXPECT_FALSE(StackWalkValidation::isValidSP(lo - 8, lo, hi));  // sp < lo
}

TEST_F(StackWalkerTest, isValidSP_must_be_strictly_below_hi) {
    uintptr_t lo = 0x1000;
    uintptr_t hi = 0x5000;
    EXPECT_FALSE(StackWalkValidation::isValidSP(hi, lo, hi));      // sp == hi: not strictly below
    EXPECT_FALSE(StackWalkValidation::isValidSP(hi + 8, lo, hi));  // sp > hi
}

TEST_F(StackWalkerTest, isValidSP_misaligned_is_invalid) {
    uintptr_t lo = 0x1000;
    uintptr_t hi = 0x5000;
    EXPECT_FALSE(StackWalkValidation::isValidSP(0x2001, lo, hi));  // in range but misaligned
}

TEST_F(StackWalkerTest, isValidSP_valid_aligned_in_range) {
    uintptr_t lo = 0x1000;
    uintptr_t hi = 0x5000;
    EXPECT_TRUE(StackWalkValidation::isValidSP(0x2000, lo, hi));
    EXPECT_TRUE(StackWalkValidation::isValidSP(lo + 8, lo, hi));
    EXPECT_TRUE(StackWalkValidation::isValidSP(hi - 8, lo, hi));
}
