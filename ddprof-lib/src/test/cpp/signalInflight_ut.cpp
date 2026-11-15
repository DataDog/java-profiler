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

#include "signalInflight.h"

#include <gtest/gtest.h>
#include <thread>

// The drain contract these tests pin down is what Profiler::stop() relies on:
// disableEngines() first, then SignalInflight::drain(), then teardown -- and
// no teardown when drain() returns false.

class SignalInflightTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Pre-condition: the counter is process-global static state; a nonzero
        // value here means a previous test (or suite in the same binary) left
        // it stuck and every drain() below would time out spuriously.
        ASSERT_EQ(0, SignalInflight::hasInflight() ? 1 : 0);
    }

    void TearDown() override {
        // Repair a counter leaked by a failed test so the next drain()-based
        // test does not wedge into its timeout; balance bugs are reported by
        // each test's own hasInflight() assertions, not here.
        while (SignalInflight::hasInflight()) {
            SignalInflight::exit();
        }
    }
};

TEST_F(SignalInflightTest, GuardBalancesAcrossEarlyReturn) {
    EXPECT_FALSE(SignalInflight::hasInflight());
    auto enter_and_return_early = []() {
        InflightGuard inflight;
        EXPECT_TRUE(SignalInflight::hasInflight());
        return; // every handler bail-out path (dropped sample, disabled engine)
    };
    enter_and_return_early();
    EXPECT_FALSE(SignalInflight::hasInflight());
}

TEST_F(SignalInflightTest, NestedGuardsCount) {
    {
        InflightGuard outer;
        EXPECT_TRUE(SignalInflight::hasInflight());
        {
            InflightGuard inner;
            EXPECT_TRUE(SignalInflight::hasInflight());
        }
        EXPECT_TRUE(SignalInflight::hasInflight());
    }
    EXPECT_FALSE(SignalInflight::hasInflight());
}

TEST_F(SignalInflightTest, DrainFastPathWithNothingInFlight) {
    EXPECT_TRUE(SignalInflight::drain());
}

TEST_F(SignalInflightTest, DrainWaitsForConcurrentHandlerAndSucceeds) {
    // Simulate a handler past its gate on another thread: plain enter(), not
    // InflightGuard -- the exit is performed by the releaser thread, so an
    // RAII guard here would decrement a second time at scope end.
    SignalInflight::enter();
    std::thread releaser([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        SignalInflight::exit();
    });
    // drain() must block until the concurrent handler leaves (its exit is a
    // RELEASE, drain's load an ACQUIRE) and then report a clean drain.
    EXPECT_TRUE(SignalInflight::drain());
    releaser.join();
    EXPECT_FALSE(SignalInflight::hasInflight());
}

// drain() returning false is the signal for callers to skip teardown
// (Profiler::stop() keeps state == RUNNING and refuses JFR teardown). Pin
// that a stuck counter actually produces the false, not a hang or a true.
TEST_F(SignalInflightTest, DrainTimesOutWithStuckHandler) {
    InflightGuard stuck;
    EXPECT_FALSE(SignalInflight::drain());
    EXPECT_TRUE(SignalInflight::hasInflight());
}
