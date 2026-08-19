/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * PROF-15130 investigation: spurious STALE LEAF frames.
 *
 * Hypothesis under test (from the ticket): convertNativeTrace() leaves a
 * counted slot unwritten (depth counts a slot that was never populated),
 * leaking stale data from a previous sample into the leaf of a parked
 * thread's stack.
 *
 * These tests drive Profiler::convertNativeTrace() directly and assert the
 * counted-slot invariant: every slot in [0, depth) returned by
 * convertNativeTrace MUST have been written this call.  The output buffer is
 * pre-filled with a recognizable sentinel so any surviving sentinel below
 * `depth` is, by definition, a counted-but-unwritten (stale) slot.
 */

#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include "../../main/cpp/profiler.h"
#include "../../main/cpp/vmEntry.h"
#include "../../main/cpp/libraries.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char STALELEAF_TEST_NAME[] = "StaleLeafTest";

// Sentinel value pre-loaded into every output slot.  Distinct bci so we can
// tell "never touched by convertNativeTrace" from any value the function
// could legitimately write (BCI_NATIVE_FRAME == -11, BCI_NATIVE_FRAME_REMOTE
// == -19).
static constexpr jint SENTINEL_BCI = 0x5A5A5A5A;
static const void* const SENTINEL_MID = (const void*)(uintptr_t)0xDEADBEEFDEADBEEFULL;

class StaleLeafTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<STALELEAF_TEST_NAME>();
        // Without this, findNativeMethod() resolves every PC to nullptr and
        // convertNativeTrace() never writes a frame, so depth is always 0 and
        // the counted-slot invariant below is checked over an empty range.
        Libraries::instance()->updateSymbols(false);
    }
    void TearDown() override {
        restoreDefaultSignalHandlers();
    }

    static void fillSentinel(ASGCT_CallFrame* frames, int n) {
        for (int i = 0; i < n; i++) {
            frames[i].bci = SENTINEL_BCI;
            frames[i].method_id = (jmethodID)SENTINEL_MID;
        }
    }

    // Returns true if every slot in [0, depth) was overwritten (no sentinel
    // survives).  A surviving sentinel below `depth` is a stale leaf bug.
    static bool noCountedSlotIsStale(const ASGCT_CallFrame* frames, int depth) {
        for (int i = 0; i < depth; i++) {
            if (frames[i].bci == SENTINEL_BCI &&
                frames[i].method_id == (jmethodID)SENTINEL_MID) {
                return false;
            }
        }
        return true;
    }
};

// Empty callchain: depth must be 0, nothing written.
TEST_F(StaleLeafTest, emptyCallchain_returnsZero_noStaleSlot) {
    ASGCT_CallFrame frames[16];
    fillSentinel(frames, 16);

    int depth = Profiler::instance()->convertNativeTrace(0, nullptr, frames, 0, false);

    EXPECT_EQ(0, depth);
    EXPECT_TRUE(noCountedSlotIsStale(frames, depth));
}

// PCs that resolve to no library: traditional path yields method_name == NULL,
// so the frame is neither written nor counted.  depth must equal the number of
// slots actually written (0 here), with no stale slot below depth.
TEST_F(StaleLeafTest, unresolvablePcs_neverLeaveCountedStaleSlot) {
    // Deliberately bogus PCs not inside any loaded library.
    const void* callchain[] = {
        (const void*)0x1000,
        (const void*)0x2000,
        (const void*)0x3000,
        (const void*)0x4000,
    };
    const int n = (int)(sizeof(callchain) / sizeof(callchain[0]));

    ASGCT_CallFrame frames[16];
    fillSentinel(frames, 16);

    int depth = Profiler::instance()->convertNativeTrace(n, callchain, frames, 0, false);

    ASSERT_GE(depth, 0);
    ASSERT_LE(depth, n);
    // INVARIANT: no counted slot may remain a sentinel.
    EXPECT_TRUE(noCountedSlotIsStale(frames, depth))
        << "convertNativeTrace counted a slot it never wrote (stale leaf)";
}

// Mix of resolvable (test-binary code) and bogus PCs.  Whatever resolves, the
// invariant must hold: depth counts only written slots.
TEST_F(StaleLeafTest, realCodePcs_neverLeaveCountedStaleSlot) {
    // Use the address of this function and a few library functions as PCs that
    // are plausibly inside loaded code segments.  Even if symbol resolution
    // returns NULL (library not parsed because the profiler is not started),
    // the invariant is the same: counted == written.
    const void* callchain[] = {
        (const void*)&memcpy,
        (const void*)&snprintf,
        (const void*)0xBADC0DE,  // unresolvable
        (const void*)&strlen
    };
    const int n = (int)(sizeof(callchain) / sizeof(callchain[0]));

    ASGCT_CallFrame frames[16];
    fillSentinel(frames, 16);

    int depth = Profiler::instance()->convertNativeTrace(n, callchain, frames, 0, false);

    ASSERT_GE(depth, 0);
    ASSERT_LE(depth, n);
    EXPECT_TRUE(noCountedSlotIsStale(frames, depth))
        << "convertNativeTrace counted a slot it never wrote (stale leaf)";
}
