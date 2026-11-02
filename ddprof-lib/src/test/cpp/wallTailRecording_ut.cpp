/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "profiler.h"

class ProfilerTestAccessor {
public:
  static void lockAll(Profiler* profiler) { profiler->lockAll(); }
  static void unlockAll(Profiler* profiler) { profiler->unlockAll(); }
};

namespace {
class HeldWriterStripes {
  Profiler* _profiler;
public:
  explicit HeldWriterStripes(Profiler* profiler) : _profiler(profiler) {
    ProfilerTestAccessor::lockAll(_profiler);
  }
  ~HeldWriterStripes() { ProfilerTestAccessor::unlockAll(_profiler); }
};
}

TEST(WallTailRecordingTest, ContendedPrimaryDoesNotPublishAnUnrecordedTrace) {
  Profiler* profiler = Profiler::instance();
  WallClockBlockTracker::BlockState slot;
  slot.recordUnownedBlockedSample(42, OSThreadState::SLEEPING);
  ExecutionEvent event;
  event._thread_state = OSThreadState::SLEEPING;

  HeldWriterStripes held(profiler);
  EXPECT_FALSE(profiler->recordWallSample(nullptr, 1, 1234, 43, &event, &slot));
  EXPECT_EQ(42ULL, slot.unowned_blocked_call_trace_id.load(std::memory_order_acquire));
}

TEST(WallTailRecordingTest, ContendedTailIsDiscardedWithoutWaitingOrRetrying) {
  Profiler* profiler = Profiler::instance();
  WallClockBlockTracker::BlockState slot;
  slot.recordUnownedBlockedSample(42, OSThreadState::SLEEPING);

  HeldWriterStripes held(profiler);
  profiler->recordUnownedBlockedTail(1234, &slot, 9);
  EXPECT_EQ(0ULL, slot.unowned_blocked_call_trace_id.load(std::memory_order_acquire));
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.unowned_blocked_state.load(std::memory_order_acquire));
}

TEST(WallTailRecordingTest, InactiveRecordingDoesNotPublishAnUnrecordedTrace) {
  // No recording is started in this native test binary. Supplying a trace ID
  // exercises the JFR rejection path without requiring a JVM stack walk.
  Profiler* profiler = Profiler::instance();
  WallClockBlockTracker::BlockState slot;
  slot.recordUnownedBlockedSample(42, OSThreadState::SLEEPING);
  ExecutionEvent event;
  event._thread_state = OSThreadState::SLEEPING;

  EXPECT_FALSE(profiler->recordWallSample(nullptr, 1, 1234, 43, &event, &slot));
  EXPECT_EQ(42ULL, slot.unowned_blocked_call_trace_id.load(std::memory_order_acquire));
}

TEST(WallTailRecordingTest, InactiveRecordingDiscardsTailAndReleasesWriterStripe) {
  Profiler* profiler = Profiler::instance();
  WallClockBlockTracker::BlockState slot;
  slot.recordUnownedBlockedSample(42, OSThreadState::SLEEPING);

  profiler->recordUnownedBlockedTail(1234, &slot, 9);
  EXPECT_EQ(0ULL, slot.unowned_blocked_call_trace_id.load(std::memory_order_acquire));
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.unowned_blocked_state.load(std::memory_order_acquire));
  // Acquiring all stripes after the rejected write verifies its unlock path.
  HeldWriterStripes held(profiler);
}
