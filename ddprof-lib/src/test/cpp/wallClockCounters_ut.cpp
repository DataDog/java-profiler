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

TEST_F(WallClockCountersTest, ResetClearsAllPendingCounters) {
  WallClockCounters::incrementTaskBlockEmitted();
  WallClockCounters::incrementTaskBlockSkippedTraceContext();
  WallClockCounters::incrementTaskBlockSkippedTooShort();
  WallClockCounters::incrementSuppressedSampledRun();

  WallClockCounters::reset();

  WallClockCounterSnapshot snapshot = WallClockCounters::drain();
  EXPECT_EQ(0ULL, snapshot.task_block_emitted);
  EXPECT_EQ(0ULL, snapshot.task_block_skipped_trace_context);
  EXPECT_EQ(0ULL, snapshot.task_block_skipped_too_short);
  EXPECT_EQ(0ULL, snapshot.suppressed_sampled_run);
}

TEST_F(WallClockCountersTest, ResetIsIdempotent) {
  WallClockCounters::reset();
  WallClockCounters::reset();

  EXPECT_EQ(0ULL, WallClockCounters::drainSuppressedSampledRun());
}
