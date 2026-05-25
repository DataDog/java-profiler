/*
 * Copyright 2026, Datadog, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "signalSafety.h"
#include "thread.h"
#include <gtest/gtest.h>

class SignalSafetyTest : public ::testing::Test {
protected:
    void SetUp() override {
        // SignalHandlerScope reads/writes ProfiledThread::_signal_depth — the
        // tests need a thread context to exist on the gtest thread, otherwise
        // every scope is a no-op (which is the intended production behavior
        // on uninstrumented threads, but not what these unit tests assert).
        ProfiledThread::initCurrentThread();
    }

    void TearDown() override {
        // Catch leaked depth from a failed test so subsequent tests start clean.
        ASSERT_EQ(0, getInSignalDepth()) << "depth not zero after test — check for leaked SignalHandlerScope";
        ProfiledThread::release();
    }
};

TEST_F(SignalSafetyTest, DepthStartsAtZero) {
    EXPECT_EQ(0, getInSignalDepth());
}

TEST_F(SignalSafetyTest, DepthSymmetry) {
    EXPECT_EQ(0, getInSignalDepth());
    {
        SignalHandlerScope scope;
        EXPECT_EQ(1, getInSignalDepth());
    }
    EXPECT_EQ(0, getInSignalDepth());
}

TEST_F(SignalSafetyTest, NestedDepth) {
    EXPECT_EQ(0, getInSignalDepth());
    {
        SignalHandlerScope outer;
        EXPECT_EQ(1, getInSignalDepth());
        {
            SignalHandlerScope inner;
            EXPECT_EQ(2, getInSignalDepth());
        }
        EXPECT_EQ(1, getInSignalDepth());
    }
    EXPECT_EQ(0, getInSignalDepth());
}

TEST_F(SignalSafetyTest, TrackedSignalContextRequiresScope) {
    EXPECT_FALSE(isInTrackedSignalContext());
    {
        SignalHandlerScope scope;
        EXPECT_TRUE(isInTrackedSignalContext());
    }
    EXPECT_FALSE(isInTrackedSignalContext());
}

// SIGNAL_HANDLER_GUARD_RELEASE path: explicit early release inside a scope,
// destructor must not double-decrement.
TEST_F(SignalSafetyTest, ReleaseDecrementsAndDestructorIsNoOp) {
    EXPECT_EQ(0, getInSignalDepth());
    {
        SignalHandlerScope scope;
        EXPECT_EQ(1, getInSignalDepth());
        scope.release();
        EXPECT_EQ(0, getInSignalDepth());
        // Destructor runs at end of scope and must NOT decrement again.
    }
    EXPECT_EQ(0, getInSignalDepth());
}

// SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP path: simulate a longjmp that bypasses
// SignalHandlerScope's destructor.  signalHandlerUnwindAfterLongjmp() must
// decrement the depth even when no live scope object is around.
//
// Sequence (longjmp simulated by an extra block-scope guard that we don't
// destroy):
//   outer scope ctor   → depth=1
//   inner scope ctor   → depth=2
//   imagine longjmp: inner scope's dtor is skipped
//   signalHandlerUnwindAfterLongjmp() at landing → depth=1
//   outer scope dtor   → depth=0
TEST_F(SignalSafetyTest, SignalHandlerUnwindAfterLongjmpDecrementsOnce) {
    EXPECT_EQ(0, getInSignalDepth());
    {
        SignalHandlerScope outer;
        EXPECT_EQ(1, getInSignalDepth());

        // Heap-allocate the inner scope so we can drop it without running its
        // destructor — emulating a longjmp that bypasses the C++ stack unwind.
        SignalHandlerScope *leaked_inner = new SignalHandlerScope();
        EXPECT_EQ(2, getInSignalDepth());

        // Pretend the longjmp landed here.  Compensate for the bypassed dtor.
        SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
        EXPECT_EQ(1, getInSignalDepth());

        // Outer scope dtor runs next and brings depth back to 0.
        // Free leaked_inner without calling its destructor (placement-new
        // wasn't used so a plain operator delete would invoke the destructor;
        // route the storage through ::operator delete to skip dtor).
        ::operator delete(leaked_inner);
    }
    EXPECT_EQ(0, getInSignalDepth());
}

// Safety property: signalHandlerUnwindAfterLongjmp() saturates at zero;
// double calls do not underflow.
TEST_F(SignalSafetyTest, SignalHandlerUnwindAfterLongjmpSaturatesAtZero) {
    EXPECT_EQ(0, getInSignalDepth());
    signalHandlerUnwindAfterLongjmp();
    signalHandlerUnwindAfterLongjmp();
    EXPECT_EQ(0, getInSignalDepth());
}

TEST(SignalSafetyTestNoContext, NullProfiledThreadIsNotTrackedSignal) {
    // isInTrackedSignalContext() returns false on null because the
    // SignalHandlerScope never ran — used by Profiler::dlopen_hook so
    // uninstrumented JVM threads doing a normal dlopen take the fast
    // (synchronous refresh) path instead of deferring.
    EXPECT_FALSE(isInTrackedSignalContext());
}

TEST(SignalSafetyTestNoContext, NullProfiledThreadDepthIsZero) {
    // Mutation guard: getInSignalDepth() must return 0 on null PT, not a
    // sentinel that happens to equal zero today.
    EXPECT_EQ(0, getInSignalDepth());
}
