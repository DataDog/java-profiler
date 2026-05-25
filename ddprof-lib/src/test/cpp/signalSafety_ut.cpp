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

TEST(SignalSafetyTestNoContext, NullProfiledThreadIsTreatedAsSignal) {
    // No ProfiledThread on this thread — isInSignalContext() must return
    // true (conservative default for AS-safety gates like dlopen_hook).
    EXPECT_TRUE(isInSignalContext());
    EXPECT_EQ(0, getInSignalDepth());
}
