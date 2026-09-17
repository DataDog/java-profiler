/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <string>
#include "arguments.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char ARGUMENTS_TEST_NAME[] = "ArgumentsTest";

class ArgumentsGlobalSetup {
public:
    ArgumentsGlobalSetup() {
        installGtestCrashHandler<ARGUMENTS_TEST_NAME>();
    }
    ~ArgumentsGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

static ArgumentsGlobalSetup global_setup;

class ArgumentsTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// hops/budget/framecap are ceiling-clamped (MAX_REFERENCE_CHAINS_HOP_CAP/
// _BUDGET/_FRONTIER_CAP, arguments.h) as well as floored at 1 - an operator
// typo (an extra digit) must not flow straight into a loop bound or
// FrontierTable's allocation unchecked.
TEST_F(ArgumentsTest, HopsBudgetFrameCapAreCeilingClamped) {
    Arguments args;
    Error error = args.parse("referencechains=true:hops=2000000000:budget=2000000000:framecap=2000000000");
    EXPECT_FALSE(error);
    EXPECT_EQ(args._reference_chains_hop_cap, MAX_REFERENCE_CHAINS_HOP_CAP);
    EXPECT_EQ(args._reference_chains_budget, MAX_REFERENCE_CHAINS_BUDGET);
    EXPECT_EQ(args._reference_chains_frontier_cap, MAX_REFERENCE_CHAINS_FRONTIER_CAP);
}

TEST_F(ArgumentsTest, HopsBudgetFrameCapStillFlooredAtOne) {
    Arguments args;
    Error error = args.parse("referencechains=true:hops=-5:budget=-5:framecap=-5");
    EXPECT_FALSE(error);
    EXPECT_EQ(args._reference_chains_hop_cap, 1);
    EXPECT_EQ(args._reference_chains_budget, 1);
    EXPECT_EQ(args._reference_chains_frontier_cap, 1);
}
