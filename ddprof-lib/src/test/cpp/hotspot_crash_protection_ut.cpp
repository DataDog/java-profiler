/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Unit tests for the crash-protection and thread-classification mechanisms
 * used by HotspotSupport::walkVM().
 *
 * Background: profiling signals can interrupt any JVM thread — including
 * JVM-internal threads such as MonitorDeflationThread.  walkVM must never
 * dereference JavaThread-only fields (anchor, vframe_top, …) on such threads.
 * VMThread::isJavaThread() provides the gate.
 *
 * Crash recovery inside walkVM relies on setjmp/longjmp:
 *   1. walkVM stores a jmp_buf* in HotspotSupport::_jmp_ctx (thread-local).
 *   2. If a fault fires during the walk, checkFault() detects the live context
 *      via isThreadProtectedByLongjmp() and calls longjmp() to unwind.
 *   3. ProfiledThread tracks nested crash-handler depth so recursive faults
 *      (e.g. wall-clock signal inside a crash handler) are capped safely.
 *
 * Tests cover:
 *   A. ProfiledThread thread-type classification (isJavaThread fast path)
 *   B. Vtable majority-vote logic (isJavaThread slow path)
 *   C. Crash-handler nesting depth (ProfiledThread crash handler state)
 *   D. Longjmp-protection state via HotspotSupport public API
 */

#include <gtest/gtest.h>
#include "thread.h"
#include "hotspot/hotspotSupport.h"

#ifdef __linux__

#include <cstring>

// ---------------------------------------------------------------------------
// A. ProfiledThread thread-type classification (isJavaThread fast path)
//
// JVMTI ThreadStart callbacks call setJavaThread(true/false) to cache the
// result; isJavaThread() returns it directly without touching the vtable.
// ---------------------------------------------------------------------------

class ProfiledThreadTypeTest : public ::testing::Test {
protected:
    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::currentSignalSafe();
        ASSERT_NE(nullptr, _pt);
    }

    void TearDown() override {
        ProfiledThread::release();
    }

    ProfiledThread* _pt = nullptr;
};

// A fresh ProfiledThread is not yet classified.
TEST_F(ProfiledThreadTypeTest, InitialStateIsUnknown) {
    EXPECT_EQ(ProfiledThread::TYPE_UNKNOWN, _pt->threadType());
}

TEST_F(ProfiledThreadTypeTest, MarkAsJavaThreadSetsCorrectType) {
    _pt->setJavaThread(true);
    EXPECT_EQ(ProfiledThread::TYPE_JAVA_THREAD, _pt->threadType());
}

// MonitorDeflationThread and similar JVM-internal threads are marked false.
TEST_F(ProfiledThreadTypeTest, MarkAsNonJavaThreadSetsCorrectType) {
    _pt->setJavaThread(false);
    EXPECT_EQ(ProfiledThread::TYPE_NOT_JAVA_THREAD, _pt->threadType());
}

TEST_F(ProfiledThreadTypeTest, ReclassificationFromJavaToNonJava) {
    _pt->setJavaThread(true);
    EXPECT_EQ(ProfiledThread::TYPE_JAVA_THREAD, _pt->threadType());

    _pt->setJavaThread(false);
    EXPECT_EQ(ProfiledThread::TYPE_NOT_JAVA_THREAD, _pt->threadType());
}

// Replicate the fast-path branch used by isJavaThread():
//   if (type != TYPE_UNKNOWN) return type == TYPE_JAVA_THREAD;
TEST_F(ProfiledThreadTypeTest, FastPathReturnsTrueForJavaThread) {
    _pt->setJavaThread(true);
    ProfiledThread::ThreadType type = _pt->threadType();
    bool result = (type != ProfiledThread::TYPE_UNKNOWN)
               && (type == ProfiledThread::TYPE_JAVA_THREAD);
    EXPECT_TRUE(result);
}

TEST_F(ProfiledThreadTypeTest, FastPathReturnsFalseForNonJavaThread) {
    _pt->setJavaThread(false);
    ProfiledThread::ThreadType type = _pt->threadType();
    bool result = (type != ProfiledThread::TYPE_UNKNOWN)
               && (type == ProfiledThread::TYPE_JAVA_THREAD);
    EXPECT_FALSE(result);
}

// ---------------------------------------------------------------------------
// B. Vtable majority-vote logic (isJavaThread slow path via hasJavaThreadVtable)
//
// hasJavaThreadVtable() compares vtable entries at indices 1, 3, 5 against
// _java_thread_vtbl[] captured from a known JavaThread at profiler start.
// At least 2 of 3 must match — tolerating product-vs-debug vtable variation.
// ---------------------------------------------------------------------------

namespace {

// Replicates the 2-of-3 vote in hasJavaThreadVtable().
static bool vtableVote(void** thread_vtbl, void** known_vtbl) {
    int matches = (thread_vtbl[1] == known_vtbl[1])
                + (thread_vtbl[3] == known_vtbl[3])
                + (thread_vtbl[5] == known_vtbl[5]);
    return matches >= 2;
}

}  // namespace

class VtableVoteTest : public ::testing::Test {
protected:
    void* known[8] = {
        (void*)0x1000, (void*)0x1001, (void*)0x1002,
        (void*)0x1003, (void*)0x1004, (void*)0x1005,
        (void*)0x1006, (void*)0x1007
    };

    // Identical to `known` — a real JavaThread.
    void* same[8] = {
        (void*)0x1000, (void*)0x1001, (void*)0x1002,
        (void*)0x1003, (void*)0x1004, (void*)0x1005,
        (void*)0x1006, (void*)0x1007
    };

    // Completely different — MonitorDeflationThread or other JVM-internal thread.
    void* different[8] = {
        (void*)0x2000, (void*)0x2001, (void*)0x2002,
        (void*)0x2003, (void*)0x2004, (void*)0x2005,
        (void*)0x2006, (void*)0x2007
    };
};

TEST_F(VtableVoteTest, ExactMatchIsJavaThread) {
    EXPECT_TRUE(vtableVote(same, known));
}

TEST_F(VtableVoteTest, NoMatchIsNotJavaThread) {
    EXPECT_FALSE(vtableVote(different, known));
}

// 2/3 match — handles product vs. debug JVM where one entry differs.
TEST_F(VtableVoteTest, TwoMatchesIsJavaThread) {
    void* partial[8];
    memcpy(partial, same, sizeof(partial));
    partial[1] = (void*)0xDEAD;  // corrupt one of the three checked entries
    EXPECT_TRUE(vtableVote(partial, known));
}

TEST_F(VtableVoteTest, OneMatchIsNotJavaThread) {
    void* partial[8];
    memcpy(partial, different, sizeof(partial));
    partial[3] = known[3];  // one real entry — still below threshold
    EXPECT_FALSE(vtableVote(partial, known));
}

// _java_thread_vtbl not yet initialised (profiler just attached): any real
// thread vtable scores 0/3 against an all-zero reference.
TEST_F(VtableVoteTest, UninitializedReferenceGivesNoMatches) {
    void* zero_ref[8] = {};
    EXPECT_FALSE(vtableVote(same, zero_ref));
}

// ---------------------------------------------------------------------------
// C. Crash-handler nesting depth
//
// ProfiledThread tracks how many crash-handler invocations are active on this
// thread so recursive signals (wall-clock arriving inside a crash handler)
// are capped at CRASH_HANDLER_NESTING_LIMIT.
//
// Profiler::crashHandlerInternal calls:
//   enterCrashHandler()   — on entry, returns false if limit reached
//   exitCrashHandler()    — on normal exit
//   resetCrashHandler()   — from checkFault before longjmp to unwind all
//                           nesting at once
// ---------------------------------------------------------------------------

class CrashHandlerNestingTest : public ::testing::Test {
protected:
    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::currentSignalSafe();
        ASSERT_NE(nullptr, _pt);
    }

    void TearDown() override {
        ProfiledThread::release();
    }

    ProfiledThread* _pt = nullptr;
};

TEST_F(CrashHandlerNestingTest, InitialDepthAllowsEntry) {
    EXPECT_TRUE(_pt->enterCrashHandler());
    _pt->exitCrashHandler();
}

TEST_F(CrashHandlerNestingTest, ExitDecrements) {
    _pt->enterCrashHandler();
    _pt->exitCrashHandler();
    // After a balanced enter/exit, another enter should still succeed.
    EXPECT_TRUE(_pt->enterCrashHandler());
    _pt->exitCrashHandler();
}

// At the nesting limit enterCrashHandler returns false to prevent runaway recursion.
TEST_F(CrashHandlerNestingTest, LimitBlocksFurtherEntry) {
    for (u32 i = 0; i < ProfiledThread::CRASH_HANDLER_NESTING_LIMIT; i++) {
        EXPECT_TRUE(_pt->enterCrashHandler()) << "entry " << i << " should succeed";
    }
    EXPECT_FALSE(_pt->enterCrashHandler()) << "entry at limit should fail";

    // Clean up the nesting we opened above.
    for (u32 i = 0; i < ProfiledThread::CRASH_HANDLER_NESTING_LIMIT; i++) {
        _pt->exitCrashHandler();
    }
}

// resetCrashHandler() is called by checkFault() before longjmp so that the
// landing pad in walkVM starts with a clean nesting count.
TEST_F(CrashHandlerNestingTest, ResetAllowsEntryAfterDeepNesting) {
    for (u32 i = 0; i < ProfiledThread::CRASH_HANDLER_NESTING_LIMIT; i++) {
        _pt->enterCrashHandler();
    }
    _pt->resetCrashHandler();
    EXPECT_TRUE(_pt->enterCrashHandler());
    _pt->exitCrashHandler();
}

// exitCrashHandler is a no-op if depth is already 0 (failsafe against
// unbalanced calls during error paths).
TEST_F(CrashHandlerNestingTest, ExitAtZeroIsNoop) {
    _pt->exitCrashHandler();  // depth was 0, must not underflow
    EXPECT_TRUE(_pt->enterCrashHandler());
    _pt->exitCrashHandler();
}

// isDeepCrashHandler returns true only when depth *exceeds* the limit.
// At exactly the limit, it is false — entry is refused but "deep" is not yet set.
TEST_F(CrashHandlerNestingTest, IsDeepOnlyAboveLimit) {
    for (u32 i = 0; i < ProfiledThread::CRASH_HANDLER_NESTING_LIMIT; i++) {
        _pt->enterCrashHandler();
    }
    EXPECT_FALSE(_pt->isDeepCrashHandler());  // at limit, not above it
    _pt->resetCrashHandler();
}

// ---------------------------------------------------------------------------
// D. Longjmp-protection state (HotspotSupport::isThreadProtectedByLongjmp)
//
// walkVM arms crash recovery by storing a jmp_buf* in a thread-local slot
// (_jmp_ctx) before the stack walk and clearing it afterward.  checkFault()
// reads this slot via isThreadProtectedByLongjmp() to decide whether to
// longjmp.
//
// HotspotSupport::initThread() initialises the slot to nullptr (so the key
// is valid but the protection is off).  isThreadProtectedByLongjmp() returns
// true only when the slot holds a non-null jmp_buf*.
// ---------------------------------------------------------------------------

TEST(LongjmpProtectionTest, UninitializedKeyMeansNotProtected) {
    // Without initThread() the pthread key may not be valid at all; either way
    // isThreadProtectedByLongjmp() must not crash and must return false.
    // (On a thread that has never called initThread the get() returns nullptr.)
    EXPECT_FALSE(HotspotSupport::isThreadProtectedByLongjmp());
}

TEST(LongjmpProtectionTest, AfterInitThreadKeyIsValidButNotProtected) {
    HotspotSupport::initThread();
    EXPECT_TRUE(HotspotSupport::isInitialized());
    // The slot is initialised to nullptr — no active walkVM on this thread.
    EXPECT_FALSE(HotspotSupport::isThreadProtectedByLongjmp());
}

#endif  // __linux__
