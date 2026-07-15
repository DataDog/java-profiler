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

TEST_F(WallClockCountersTest, DrainReturnsAndClearsSuppressedOwnedBlock) {
  WallClockCounters::incrementSuppressedOwnedBlock();
  WallClockCounters::incrementSuppressedOwnedBlock();

  EXPECT_EQ(2ULL, WallClockCounters::drainSuppressedOwnedBlock());
  EXPECT_EQ(0ULL, WallClockCounters::drainSuppressedOwnedBlock());
}

TEST_F(WallClockCountersTest, ResetClearsPendingSuppressedOwnedBlock) {
  WallClockCounters::incrementSuppressedOwnedBlock();

  WallClockCounters::reset();

  EXPECT_EQ(0ULL, WallClockCounters::drainSuppressedOwnedBlock());
}

TEST_F(WallClockCountersTest, ResetIsIdempotent) {
  WallClockCounters::reset();
  WallClockCounters::reset();

  EXPECT_EQ(0ULL, WallClockCounters::drainSuppressedOwnedBlock());
}
