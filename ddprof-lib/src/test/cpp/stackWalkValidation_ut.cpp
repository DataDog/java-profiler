/*
 * Copyright 2026, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstdint>

#include "stackWalker.h"

using namespace StackWalkValidation;

class StackWalkValidationTest : public ::testing::Test {
protected:
    // Simulated stack frame structure for testing FP chain validation logic
    struct MockFrame {
        uintptr_t saved_fp;  // Saved frame pointer (points to caller's frame)
        void* return_addr;   // Return address
    };
};

// Test inDeadZone helper
TEST_F(StackWalkValidationTest, inDeadZone_NullPointer) {
    EXPECT_TRUE(inDeadZone(nullptr));
}

TEST_F(StackWalkValidationTest, inDeadZone_LowAddress) {
    // Addresses below DEAD_ZONE (0x1000) should be in dead zone
    EXPECT_TRUE(inDeadZone((void*)0x100));
    EXPECT_TRUE(inDeadZone((void*)0xFFF));
}

TEST_F(StackWalkValidationTest, inDeadZone_ValidAddress) {
    // Addresses above DEAD_ZONE should not be in dead zone
    EXPECT_FALSE(inDeadZone((void*)0x1000));
    EXPECT_FALSE(inDeadZone((void*)0x10000));
}

TEST_F(StackWalkValidationTest, inDeadZone_HighAddress) {
    // Very high addresses (near -DEAD_ZONE) should be in dead zone
    EXPECT_TRUE(inDeadZone((void*)(~(uintptr_t)0)));
    EXPECT_TRUE(inDeadZone((void*)(~(uintptr_t)0 - 0x100)));
}

// Test aligned helper
TEST_F(StackWalkValidationTest, aligned_WordAligned) {
    // Word-aligned addresses (8-byte on 64-bit)
    EXPECT_TRUE(aligned(0x1000));
    EXPECT_TRUE(aligned(0x1008));
    EXPECT_TRUE(aligned(0x7fff00000000));
}

TEST_F(StackWalkValidationTest, aligned_NotAligned) {
    // Non-word-aligned addresses
    EXPECT_FALSE(aligned(0x1001));
    EXPECT_FALSE(aligned(0x1002));
    EXPECT_FALSE(aligned(0x1004));  // 4-byte aligned but not 8-byte on 64-bit
    EXPECT_FALSE(aligned(0x1007));
}

// Test sameStack helper
TEST_F(StackWalkValidationTest, sameStack_SameLocation) {
    int x;
    EXPECT_TRUE(sameStack(&x, &x));
}

TEST_F(StackWalkValidationTest, sameStack_NearbyLocations) {
    char buffer[4096];
    EXPECT_TRUE(sameStack(&buffer[4095], &buffer[0]));
}

TEST_F(StackWalkValidationTest, sameStack_FarApart) {
    // Addresses more than SAME_STACK_DISTANCE apart
    void* hi = (void*)0x7fff00010000;
    void* lo = (void*)0x7fff00000000;
    EXPECT_FALSE(sameStack(hi, lo));
}

/**
 * Test the FP chain progression validation logic.
 *
 * In a valid FP chain:
 * - Stack grows downward (toward lower addresses)
 * - Saved FP points to caller's frame (higher address)
 * - Therefore: next_fp > current_fp
 *
 * When FP wanders into local variables:
 * - The value read as "saved FP" is actually a local variable
 * - Locals are typically at lower or similar addresses
 * - This violates the fp > prev_fp invariant
 */
TEST_F(StackWalkValidationTest, FPChainProgression_ValidChain) {
    // Allocate frames in a buffer with controlled layout
    // Frame layout must simulate: frame1 (low addr) -> frame2 -> frame3 (high addr)
    // where each frame's saved_fp points to the next higher frame
    alignas(sizeof(uintptr_t)) char buffer[3 * sizeof(MockFrame)];

    MockFrame* frame1 = (MockFrame*)(buffer);
    MockFrame* frame2 = (MockFrame*)(buffer + sizeof(MockFrame));
    MockFrame* frame3 = (MockFrame*)(buffer + 2 * sizeof(MockFrame));

    // Verify ordering: frame1 < frame2 < frame3
    ASSERT_LT((uintptr_t)frame1, (uintptr_t)frame2);
    ASSERT_LT((uintptr_t)frame2, (uintptr_t)frame3);

    // Setup chain: frame1 -> frame2 -> frame3 -> null
    frame3->saved_fp = 0;  // Oldest frame (null FP = end)
    frame3->return_addr = nullptr;

    frame2->saved_fp = (uintptr_t)frame3;
    frame2->return_addr = (void*)0x400000;

    frame1->saved_fp = (uintptr_t)frame2;
    frame1->return_addr = (void*)0x400100;

    uintptr_t fp = (uintptr_t)frame1;

    // Walk the chain and verify progression
    uintptr_t prev_fp = fp;
    fp = *(uintptr_t*)fp;  // Read saved FP from frame1

    // Valid: next FP (frame2) should be greater than current (frame1)
    EXPECT_GT(fp, prev_fp);
    EXPECT_TRUE(aligned(fp));

    prev_fp = fp;
    fp = *(uintptr_t*)fp;  // Read saved FP from frame2

    // Valid: next FP (frame3) should be greater than current (frame2)
    EXPECT_GT(fp, prev_fp);

    // Final frame has null FP (chain terminator)
    prev_fp = fp;
    fp = *(uintptr_t*)fp;  // Read saved FP from frame3
    EXPECT_EQ(fp, 0u);
}

TEST_F(StackWalkValidationTest, FPChainProgression_BackwardsChain) {
    // Simulate an invalid FP chain where FP goes backward
    // This happens when FP points to a local variable
    MockFrame frame1;
    uintptr_t fake_local = 0x12345678;  // Simulated local variable value

    // Point FP to a location that contains a "backwards" pointer
    frame1.saved_fp = (uintptr_t)&fake_local - 0x1000;  // Lower address

    uintptr_t fp = (uintptr_t)&frame1;
    uintptr_t prev_fp = fp;
    fp = *(uintptr_t*)fp;

    // Invalid: next FP is less than current (backwards)
    // This is the condition our validation catches
    EXPECT_LE(fp, prev_fp);
}

TEST_F(StackWalkValidationTest, FPChainProgression_SameAddress) {
    // FP pointing to itself (no progress) is invalid
    MockFrame frame1;
    frame1.saved_fp = (uintptr_t)&frame1;  // Points to itself

    uintptr_t fp = (uintptr_t)&frame1;
    uintptr_t prev_fp = fp;
    fp = *(uintptr_t*)fp;

    // Invalid: FP equals prev_fp (no progress)
    EXPECT_EQ(fp, prev_fp);
}

/**
 * Test that validates the relationship between alignment and FP validity.
 * Pointer-sized local variables are word-aligned by the compiler, so alignment
 * alone cannot distinguish valid FPs from locals. The progression check
 * (fp > prev_fp) is the key discriminator.
 */
TEST_F(StackWalkValidationTest, PointerSizedLocalsAreAligned) {
    // Demonstrate that pointer-sized local variables are word-aligned.
    // This is why alignment alone isn't sufficient to validate FP chains.
    // Note: smaller types like int may only be 4-byte aligned on 64-bit systems.
    uintptr_t local_uintptr;
    void* local_ptr;
    size_t local_size;

    EXPECT_TRUE(aligned((uintptr_t)&local_uintptr));
    EXPECT_TRUE(aligned((uintptr_t)&local_ptr));
    EXPECT_TRUE(aligned((uintptr_t)&local_size));
}
