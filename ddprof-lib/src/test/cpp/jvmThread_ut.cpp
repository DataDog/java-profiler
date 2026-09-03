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
// One pthread key for the whole binary, created on first use and never
// deleted -- mirroring the ThreadLocal instances in threadLocal_ut.cpp,
// which are kept alive for the binary's lifetime rather than
// created/deleted per test to avoid exhausting pthread keys. Sharing the key
// across tests is safe here: each test still drives it with its own unique
// marker (see nextUniqueMarker()) to verify the scan below finds it.
pthread_key_t sharedTestKey() {
    static pthread_key_t key = [] {
        pthread_key_t k = 0;
        if (pthread_key_create(&k, nullptr) != 0) {
            ADD_FAILURE() << "pthread_key_create failed";
        }
        return k;
    }();
    return key;
}

// A marker value guaranteed unique across the whole test binary run, so the
// initializeKey() scan below can never land on a stale value from an
// earlier test that happens to still be sitting in sharedTestKey().
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

        _key = sharedTestKey();
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
        // _key is the binary-lifetime sharedTestKey(), not deleted here (see
        // its comment). JVMThread::_jvm_thread also keeps using whatever key
        // was last scanned into it, which is fine since that's always this
        // same shared key.
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
