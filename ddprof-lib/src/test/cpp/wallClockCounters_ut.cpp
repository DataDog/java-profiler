/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "wallClockCounters.h"
#include "counters.h"

#include <gtest/gtest.h>

class WallClockCountersTest : public ::testing::Test {
protected:
  void SetUp() override {
    Counters::reset();
    WallClockCounters::reset();
  }

  void TearDown() override {
    WallClockCounters::reset();
    Counters::reset();
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

TEST_F(WallClockCountersTest, TaskBlockDiagnosticsUseProfilerCounters) {
  Counters::increment(TASK_BLOCK_EMITTED);
  Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
  Counters::increment(TASK_BLOCK_SKIPPED_TOO_SHORT);
  Counters::increment(TASK_BLOCK_SKIPPED_NO_STACK_REFERENCE);
  Counters::increment(TASK_BLOCK_RECORD_FAILED);

  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_EMITTED));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TRACE_CONTEXT));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_NO_STACK_REFERENCE));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));

  WallClockCounters::reset();

  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_EMITTED));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TRACE_CONTEXT));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_NO_STACK_REFERENCE));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
}
