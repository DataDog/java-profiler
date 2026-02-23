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
