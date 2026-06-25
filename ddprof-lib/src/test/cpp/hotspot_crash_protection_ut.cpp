/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Unit tests for the MonitorDeflationThread crash-protection gate.
 *
 * Root cause (JDK 25.0.2): walkVM() unconditionally wrote a jmp_buf address
 * into ThreadShadow::_exception_file for every non-null VMThread, including
 * JVM-internal threads like MonitorDeflationThread.  In JDK 25,
 * ObjectMonitorDeflationSafepointer reads _exception_file at safepoint
 * boundaries; a stale jmp_buf address caused a crash in deflate_monitor_list.
 *
 * Fix: gate the write on `VMThread::isJavaThread(vm_thread)`.
 *
 * `isJavaThread()` has two paths:
 *  1. Fast path  — reads the cached ProfiledThread::ThreadType set by the
 *                  JVMTI ThreadStart callback (TYPE_JAVA_THREAD /
 *                  TYPE_NOT_JAVA_THREAD).
 *  2. Slow path  — falls back to the vtable majority vote in
 *                  VMThread::hasJavaThreadVtable(): at least 2 of the 3
 *                  selected vtable entries (indices 1, 3, 5) must match
 *                  those of a known JavaThread captured at profiler start.
 *
 * Tests here cover:
 *  A. ProfiledThread classification (fast path) — setJavaThread / threadType.
 *  B. Vtable majority-vote logic (slow path)    — replicated inline as a
 *     whitebox test because hasJavaThreadVtable() is private.
 *  C. setup_crash_protection gate condition     — the boolean that walkVM
 *     uses to decide whether to touch _exception_file.
 */

#include <gtest/gtest.h>
#include "thread.h"

#ifdef __linux__

#include <pthread.h>
#include <cstring>

// ---------------------------------------------------------------------------
// A. ProfiledThread thread-type classification (fast path of isJavaThread)
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

// A fresh ProfiledThread carries TYPE_UNKNOWN until explicitly classified.
TEST_F(ProfiledThreadTypeTest, InitialStateIsUnknown) {
    EXPECT_EQ(ProfiledThread::TYPE_UNKNOWN, _pt->threadType());
}

// After being marked as a Java thread the type is TYPE_JAVA_THREAD.
TEST_F(ProfiledThreadTypeTest, MarkAsJavaThreadSetsCorrectType) {
    _pt->setJavaThread(true);
    EXPECT_EQ(ProfiledThread::TYPE_JAVA_THREAD, _pt->threadType());
}

// After being marked as a non-Java thread (e.g. MonitorDeflationThread) the
// type is TYPE_NOT_JAVA_THREAD, which makes isJavaThread() return false and
// prevents walkVM from writing _exception_file.
TEST_F(ProfiledThreadTypeTest, MarkAsNonJavaThreadSetsCorrectType) {
    _pt->setJavaThread(false);
    EXPECT_EQ(ProfiledThread::TYPE_NOT_JAVA_THREAD, _pt->threadType());
}

// Reclassification works: a thread initially marked Java can be reclassified.
TEST_F(ProfiledThreadTypeTest, ReclassificationFromJavaToNonJava) {
    _pt->setJavaThread(true);
    EXPECT_EQ(ProfiledThread::TYPE_JAVA_THREAD, _pt->threadType());

    _pt->setJavaThread(false);
    EXPECT_EQ(ProfiledThread::TYPE_NOT_JAVA_THREAD, _pt->threadType());
}

// The fast-path short-circuit: if threadType() != TYPE_UNKNOWN,
// isJavaThread() returns it directly without consulting the vtable.
// Verify the logic isJavaThread() uses:
//   type != TYPE_UNKNOWN  →  return type == TYPE_JAVA_THREAD
TEST_F(ProfiledThreadTypeTest, FastPathLogicForJavaThread) {
    _pt->setJavaThread(true);
    ProfiledThread::ThreadType type = _pt->threadType();
    bool fast_path_result = (type != ProfiledThread::TYPE_UNKNOWN)
                          && (type == ProfiledThread::TYPE_JAVA_THREAD);
    EXPECT_TRUE(fast_path_result);
}

TEST_F(ProfiledThreadTypeTest, FastPathLogicForNonJavaThread) {
    _pt->setJavaThread(false);
    ProfiledThread::ThreadType type = _pt->threadType();
    bool fast_path_result = (type != ProfiledThread::TYPE_UNKNOWN)
                          && (type == ProfiledThread::TYPE_JAVA_THREAD);
    EXPECT_FALSE(fast_path_result);
}

// ---------------------------------------------------------------------------
// B. Vtable majority-vote logic (slow path of hasJavaThreadVtable)
//
// VMThread::hasJavaThreadVtable() compares vtable entries at indices 1, 3, 5
// against _java_thread_vtbl[1/3/5] and returns true when >= 2 match.
// This ensures a MonitorDeflationThread (which is a JavaThread subclass but
// has its own vtable) is correctly classified as a non-Java thread.
//
// We replicate the vote logic here as a whitebox unit test, keeping it in
// sync with the comment in vmStructs.inline.h.
// ---------------------------------------------------------------------------

namespace {

// Simulate the 2-of-3 majority vote performed by hasJavaThreadVtable().
// Arguments:
//   thread_vtbl  – vtable pointer array of the candidate thread
//   known_vtbl   – _java_thread_vtbl captured from a real JavaThread
static bool vtableVote(void** thread_vtbl, void** known_vtbl) {
    int matches = (thread_vtbl[1] == known_vtbl[1])
                + (thread_vtbl[3] == known_vtbl[3])
                + (thread_vtbl[5] == known_vtbl[5]);
    return matches >= 2;
}

}  // namespace

class VtableVoteTest : public ::testing::Test {
protected:
    // Sentinel vtable entries used as the "known JavaThread vtable".
    void* known[8] = {
        (void*)0x1000, (void*)0x1001, (void*)0x1002,
        (void*)0x1003, (void*)0x1004, (void*)0x1005,
        (void*)0x1006, (void*)0x1007
    };

    // A thread vtable that exactly matches `known`.
    void* same[8] = {
        (void*)0x1000, (void*)0x1001, (void*)0x1002,
        (void*)0x1003, (void*)0x1004, (void*)0x1005,
        (void*)0x1006, (void*)0x1007
    };

    // A thread vtable that shares no entries with `known`
    // (simulates MonitorDeflationThread or another JVM-internal thread).
    void* different[8] = {
        (void*)0x2000, (void*)0x2001, (void*)0x2002,
        (void*)0x2003, (void*)0x2004, (void*)0x2005,
        (void*)0x2006, (void*)0x2007
    };
};

// Exact match (3/3) → java thread.
TEST_F(VtableVoteTest, ExactMatchIsJavaThread) {
    EXPECT_TRUE(vtableVote(same, known));
}

// Zero matches → not a java thread (MonitorDeflationThread case).
TEST_F(VtableVoteTest, NoMatchIsNotJavaThread) {
    EXPECT_FALSE(vtableVote(different, known));
}

// Exactly 2 matches → still a java thread (handles product vs. debug JVM).
TEST_F(VtableVoteTest, TwoMatchesIsJavaThread) {
    void* partial[8];
    memcpy(partial, same, sizeof(partial));
    // Corrupt one of the three checked entries (index 1).
    partial[1] = (void*)0xDEAD;
    EXPECT_TRUE(vtableVote(partial, known));
}

// Exactly 1 match → not a java thread.
TEST_F(VtableVoteTest, OneMatchIsNotJavaThread) {
    void* partial[8];
    memcpy(partial, different, sizeof(partial));
    // Give it one real entry (index 3) to stay below the threshold.
    partial[3] = known[3];
    EXPECT_FALSE(vtableVote(partial, known));
}

// All zeros (uninitialized _java_thread_vtbl before profiler attaches) →
// a thread whose own vtable is also all-zero scores 3/3 but that cannot
// happen in practice because NULL vtable entries dereference to nothing.
// More practically: a non-zero vtable against an all-zero reference → 0/3.
TEST_F(VtableVoteTest, UninitializedReferenceVtableGivesNoMatches) {
    void* zero_ref[8] = {};  // _java_thread_vtbl not yet initialized
    EXPECT_FALSE(vtableVote(same, zero_ref));
}

// ---------------------------------------------------------------------------
// C. setup_crash_protection gate condition
//
// walkVM computes: setup_crash_protection = (vm_thread != NULL) && isJavaThread()
// Verify that the gate is false for TYPE_NOT_JAVA_THREAD threads (fast path).
// ---------------------------------------------------------------------------

class CrashProtectionGateTest : public ::testing::Test {
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

    // Replicate the fast-path of isJavaThread() for gating purposes.
    static bool fastPathIsJavaThread(ProfiledThread* pt) {
        if (pt == nullptr) return false;
        ProfiledThread::ThreadType type = pt->threadType();
        if (type != ProfiledThread::TYPE_UNKNOWN) {
            return type == ProfiledThread::TYPE_JAVA_THREAD;
        }
        return false; // TYPE_UNKNOWN → slow vtable path (not tested here)
    }
};

// Gate is off for a JVM-internal thread (TYPE_NOT_JAVA_THREAD):
// _exception_file must NOT be written.
TEST_F(CrashProtectionGateTest, GateOffForNonJavaThread) {
    _pt->setJavaThread(false);
    // Simulate: vm_thread != NULL (non-null pointer means JVM thread struct exists)
    bool vm_thread_non_null = true;
    bool setup_crash_protection = vm_thread_non_null && fastPathIsJavaThread(_pt);
    EXPECT_FALSE(setup_crash_protection);
}

// Gate is on for a real Java application thread (TYPE_JAVA_THREAD):
// _exception_file IS written so crash recovery via longjmp works.
TEST_F(CrashProtectionGateTest, GateOnForJavaThread) {
    _pt->setJavaThread(true);
    bool vm_thread_non_null = true;
    bool setup_crash_protection = vm_thread_non_null && fastPathIsJavaThread(_pt);
    EXPECT_TRUE(setup_crash_protection);
}

// Gate is always off when vm_thread is NULL (no JVM thread struct).
TEST_F(CrashProtectionGateTest, GateOffWhenNoVmThread) {
    _pt->setJavaThread(true);  // would be a Java thread, but vm_thread is NULL
    bool vm_thread_non_null = false;
    bool setup_crash_protection = vm_thread_non_null && fastPathIsJavaThread(_pt);
    EXPECT_FALSE(setup_crash_protection);
}

#endif  // __linux__
