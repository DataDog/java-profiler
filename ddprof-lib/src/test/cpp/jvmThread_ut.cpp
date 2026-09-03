/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Unit tests for tickInitWindowIfNeeded() (threadLocalData.inline.h).
//
// This gtest binary has no live JVM attached, so JVMThread::_jvm_thread's
// pthread key is never established by the normal path (see jvmSupport_ut.cpp
// for why JVMThread::initialize() can never succeed here) and
// JVMThread::current() asserts if called with that key still invalid.
// JVMThreadTestAccessor below fabricates a valid key via the same
// ThreadLocal<JVMThread*>::initialize() scan the real JVM startup path uses,
// backed by a plain pthread key this test controls directly -- letting
// JVMThread::current() be driven to both null and non-null without a JVM.

#include <gtest/gtest.h>
#include <pthread.h>
#include <atomic>
#include <cstdint>
#include "jvmThread.h"
#include "threadLocalData.inline.h"

namespace {
// A marker value guaranteed unique across the whole test binary run, so the
// initializeKey() scan below can never land on a stale key from an earlier
// test. Using `this` here would not be safe: successive TickInitWindowTest
// instances are allocated and freed by gtest between tests, so the allocator
// commonly hands the same address back out, and an earlier test's key (never
// deleted -- see TearDown) would still hold that now-reused address.
void* nextUniqueMarker() {
    static std::atomic<uintptr_t> counter{1};
    return reinterpret_cast<void*>(counter.fetch_add(1));
}
}  // namespace

class JVMThreadTestAccessor {
public:
    static bool initializeKey(void* current_thread_marker) {
        return JVMThread::_jvm_thread.initialize(current_thread_marker);
    }
};

class TickInitWindowTest : public ::testing::Test {
protected:
    void SetUp() override {
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::current();
        ASSERT_NE(nullptr, _pt);

        ASSERT_EQ(0, pthread_key_create(&_key, nullptr));
        _marker = nextUniqueMarker();
        ASSERT_EQ(0, pthread_setspecific(_key, _marker));
        ASSERT_TRUE(JVMThreadTestAccessor::initializeKey(_marker));
        // initializeKey() scans all live pthread keys for one holding `marker`;
        // guard against it landing on some other stale slot that happens to
        // hold the same pointer value, which would make current()/
        // setJvmThreadCurrent() disagree on which key they're touching.
        ASSERT_EQ(_key, JVMThread::key());
    }

    void TearDown() override {
        // Deliberately not calling pthread_key_delete(_key): JVMThread::_jvm_thread
        // is a static that keeps using whatever key the next test's SetUp scans
        // into it, mirroring the real (JVM-owned, never-deleted) key it normally
        // reflects. Deleting it here would leave that static holding a dangling
        // key for the brief window before the next SetUp re-scans it.
        ProfiledThread::release();
    }

    // JVMThread::current() reads whatever this test last stored in _key.
    void setJvmThreadCurrent(void* value) {
        ASSERT_EQ(0, pthread_setspecific(_key, value));
    }

    ProfiledThread* _pt = nullptr;
    pthread_key_t _key = 0;
    void* _marker = nullptr;
};

// JVMThread::current() == nullptr, not in window -> false.
TEST_F(TickInitWindowTest, NoJvmThreadNotInWindowReturnsFalse) {
    setJvmThreadCurrent(nullptr);
    ASSERT_FALSE(_pt->inInitWindow());

    EXPECT_FALSE(tickInitWindowIfNeeded(_pt));
}

// JVMThread::current() == nullptr, in window -> true, and the window ticks
// down. This is the pure-native-thread case tickInitWindowIfNeeded exists
// for.
TEST_F(TickInitWindowTest, NoJvmThreadInWindowReturnsTrueAndTicks) {
    setJvmThreadCurrent(nullptr);
    _pt->startInitWindow();
    ASSERT_TRUE(_pt->inInitWindow());

    EXPECT_TRUE(tickInitWindowIfNeeded(_pt));
    EXPECT_FALSE(_pt->inInitWindow());  // one-shot window exhausted by the tick
}

// JVMThread::current() != nullptr, not in window -> false.
TEST_F(TickInitWindowTest, HasJvmThreadNotInWindowReturnsFalse) {
    setJvmThreadCurrent(_marker);
    ASSERT_FALSE(_pt->inInitWindow());

    EXPECT_FALSE(tickInitWindowIfNeeded(_pt));
}

// JVMThread::current() != nullptr, in window -> still false: a thread the
// JVM already knows about must never take the init-window bypass. This is
// the case that would break if && were mutated to ||.
TEST_F(TickInitWindowTest, HasJvmThreadInWindowReturnsFalse) {
    setJvmThreadCurrent(_marker);
    _pt->startInitWindow();
    ASSERT_TRUE(_pt->inInitWindow());

    EXPECT_FALSE(tickInitWindowIfNeeded(_pt));
    EXPECT_TRUE(_pt->inInitWindow());  // not consumed: the call was a no-op
}
