/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "engine.h"
#include "event.h"
#include "flightRecorder.h"

#include <gtest/gtest.h>

TEST(FlightRecorderResultTest, RecordEventReturnsFalseWithoutActiveRecording) {
  FlightRecorder recorder;
  ExecutionEvent event;

  EXPECT_FALSE(recorder.recordEvent(/*lock_index=*/0, /*tid=*/1,
                                    /*call_trace_id=*/42, BCI_WALL, &event));
}

TEST(FlightRecorderResultTest, RecordEventDelegatedReturnsFalseWithoutActiveRecording) {
  FlightRecorder recorder;
  ExecutionEvent event;

  EXPECT_FALSE(recorder.recordEventDelegated(/*lock_index=*/0, /*tid=*/1,
                                             /*correlation_id=*/42, BCI_WALL,
                                             &event));
}

TEST(FlightRecorderResultTest, RecordEventDelegatedReturnsFalseForUnsupportedEventType) {
  FlightRecorder recorder;
  AllocEvent event;

  EXPECT_FALSE(recorder.recordEventDelegated(/*lock_index=*/0, /*tid=*/1,
                                             /*correlation_id=*/42, BCI_ALLOC,
                                             &event));
}
