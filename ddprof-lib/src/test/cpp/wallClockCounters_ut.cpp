/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "wallClockCounters.h"

#include <gtest/gtest.h>

class WallClockCountersTest : public ::testing::Test {
protected:
  void SetUp() override {
    WallClockCounters::reset();
  }

  void TearDown() override {
    WallClockCounters::reset();
  }
};

TEST_F(WallClockCountersTest, DrainReturnsAndClearsSuppressedSampledRun) {
  WallClockCounters::incrementSuppressedSampledRun();
  WallClockCounters::incrementSuppressedSampledRun();

  EXPECT_EQ(2ULL, WallClockCounters::drainSuppressedSampledRun());
  EXPECT_EQ(0ULL, WallClockCounters::drainSuppressedSampledRun());
}

TEST_F(WallClockCountersTest, ResetClearsPendingSuppressedSampledRun) {
  WallClockCounters::incrementSuppressedSampledRun();

  WallClockCounters::reset();

  EXPECT_EQ(0ULL, WallClockCounters::drainSuppressedSampledRun());
}

TEST_F(WallClockCountersTest, ResetIsIdempotent) {
  WallClockCounters::reset();
  WallClockCounters::reset();

  EXPECT_EQ(0ULL, WallClockCounters::drainSuppressedSampledRun());
}
