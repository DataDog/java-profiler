/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Unit tests for tickInitWindowIfNeededImpl() (threadLocalData.inline.h).
//
// tickInitWindowIfNeeded() takes "does the JVM already know this thread" from
// JVMThread::current(); tickInitWindowIfNeededImpl() takes it as a plain bool.
// The tests below drive that bool directly, covering all four
// has_jvm_thread x inInitWindow() combinations with no JVM involved.
//
// The one-line derivation in tickInitWindowIfNeeded() itself is deliberately
// not unit tested. JVMThread::current() reads a pthread key established by
// JVM startup, and this gtest binary has no JVM attached; fabricating that
// key means mutating process-global state and leaning on
// ThreadLocal<JVMThread*>::initialize()'s scan over every live pthread key,
// which costs far more than a single `!= nullptr` argument expression that
// compilation and inspection already cover.

#include <gtest/gtest.h>
#include "threadLocalData.inline.h"
#include "gtest_crash_handler.h"

static constexpr char TICKINITWINDOW_TEST_NAME[] = "TickInitWindowImplTest";

class TickInitWindowImplTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<TICKINITWINDOW_TEST_NAME>();
        ProfiledThread::initCurrentThread();
        _pt = ProfiledThread::current();
        ASSERT_NE(nullptr, _pt);
    }

    void TearDown() override {
        ProfiledThread::release();
        restoreDefaultSignalHandlers();
    }

    ProfiledThread* _pt = nullptr;
};

// !has_jvm_thread, not in window -> false.
TEST_F(TickInitWindowImplTest, NoJvmThreadNotInWindowReturnsFalse) {
    ASSERT_FALSE(_pt->inInitWindow());

    EXPECT_FALSE(tickInitWindowIfNeededImpl(false, _pt));
}

// !has_jvm_thread, in window -> true, and the window ticks down. This is the
// pure-native-thread case tickInitWindowIfNeeded exists for.
TEST_F(TickInitWindowImplTest, NoJvmThreadInWindowReturnsTrueAndTicks) {
    _pt->startInitWindow();
    ASSERT_TRUE(_pt->inInitWindow());

    EXPECT_TRUE(tickInitWindowIfNeededImpl(false, _pt));
    EXPECT_FALSE(_pt->inInitWindow());  // one-shot window exhausted by the tick

    // The window is one-shot: a second call must return false, not tick again.
    EXPECT_FALSE(tickInitWindowIfNeededImpl(false, _pt));
}

// has_jvm_thread, not in window -> false.
TEST_F(TickInitWindowImplTest, HasJvmThreadNotInWindowReturnsFalse) {
    ASSERT_FALSE(_pt->inInitWindow());

    EXPECT_FALSE(tickInitWindowIfNeededImpl(true, _pt));
}

// has_jvm_thread, in window -> still false: a thread the JVM already knows
// about must never take the init-window bypass. This is the case that would
// break if && were mutated to ||.
TEST_F(TickInitWindowImplTest, HasJvmThreadInWindowReturnsFalse) {
    _pt->startInitWindow();
    ASSERT_TRUE(_pt->inInitWindow());

    EXPECT_FALSE(tickInitWindowIfNeededImpl(true, _pt));
    EXPECT_TRUE(_pt->inInitWindow());  // not consumed: the call was a no-op
}
