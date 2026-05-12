/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * AC-2: When lookupClassSignalSafe() returns -1 (clear in progress), the vtable-target
 *       frame must NOT be added (depth must not be incremented).
 *
 * This test models the fixed conditional guard:
 *   int class_id = profiler->lookupClassSignalSafe(symbol->body(), symbol->length());
 *   if (class_id > 0) {
 *       fillFrame(frames[depth++], BCI_ALLOC, class_id);
 *   }
 *
 * We verify the guard logic in isolation using a miniature stub that mirrors
 * the production pattern, so the test does not depend on the full profiler.
 */

#include <gtest/gtest.h>

// ---------------------------------------------------------------------------
// Minimal stubs that mirror only what the guard logic needs
// ---------------------------------------------------------------------------

static constexpr int BCI_ALLOC = -12; // production value from vmEntry.h

struct ASGCT_CallFrame {
    int bci;
    unsigned int method_id;
};

static void fillFrame(ASGCT_CallFrame& f, int bci, unsigned int id) {
    f.bci = bci;
    f.method_id = id;
}

// Simulate the two outcomes of lookupClassSignalSafe():
//   > 0  – class found, normal operation
//   -1   – lock not acquired (clear in progress), graceful skip

static int guardedEmit(int lookup_result, ASGCT_CallFrame* frames, int depth) {
    // This is the FIXED code path (AC-2 guard).
    if (lookup_result > 0) {
        fillFrame(frames[depth++], BCI_ALLOC, (unsigned int)lookup_result);
    }
    return depth;
}

// ---------------------------------------------------------------------------

TEST(VTableGracefulSkipAC2, FrameEmittedWhenClassFound) {
    ASGCT_CallFrame frames[8] = {};
    int depth = 0;

    // lookup succeeded
    depth = guardedEmit(42, frames, depth);

    EXPECT_EQ(depth, 1) << "Depth must increment when class_id > 0";
    EXPECT_EQ(frames[0].bci, BCI_ALLOC);
    EXPECT_EQ(frames[0].method_id, 42u);
}

TEST(VTableGracefulSkipAC2, FrameNotEmittedWhenLookupReturnsMinus1) {
    ASGCT_CallFrame frames[8] = {};
    int depth = 0;

    // lookup failed (-1) – clear in progress
    depth = guardedEmit(-1, frames, depth);

    EXPECT_EQ(depth, 0)
        << "Depth must NOT increment when lookupClassSignalSafe() returns -1 (AC-2)";
    // The frame slot must be untouched
    EXPECT_EQ(frames[0].bci, 0);
    EXPECT_EQ(frames[0].method_id, 0u);
}

TEST(VTableGracefulSkipAC2, FrameNotEmittedWhenLookupReturnsZero) {
    // Zero is also "not found" – guard must be > 0, not >= 0.
    ASGCT_CallFrame frames[8] = {};
    int depth = 0;

    depth = guardedEmit(0, frames, depth);

    EXPECT_EQ(depth, 0)
        << "Depth must NOT increment when lookupClassSignalSafe() returns 0 (AC-2)";
}
