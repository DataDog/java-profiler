/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "profiler.h"

#include <atomic>

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

std::atomic<int> g_observed_tails{0};
std::atomic<u64> g_observed_weight{0};
std::atomic<u64> g_observed_call_trace_id{0};

void observeUnownedTail(int tid, u64 call_trace_id, const ExecutionEvent* event) {
  g_observed_call_trace_id.store(call_trace_id, std::memory_order_relaxed);
  g_observed_weight.store(event->_weight, std::memory_order_relaxed);
  g_observed_tails.fetch_add(1, std::memory_order_release);
}

class UnownedTailObserverScope {
public:
  UnownedTailObserverScope() {
    g_observed_tails.store(0, std::memory_order_relaxed);
    g_observed_weight.store(0, std::memory_order_relaxed);
    g_observed_call_trace_id.store(0, std::memory_order_relaxed);
    Profiler::setUnownedTailRecordObserverForTest(observeUnownedTail);
  }
  ~UnownedTailObserverScope() { Profiler::setUnownedTailRecordObserverForTest(nullptr); }
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
  // The published trace and state reach the observer call site, so with no
  // observer installed this test also covers its null check.
  Profiler::setUnownedTailRecordObserverForTest(nullptr);

  profiler->recordUnownedBlockedTail(1234, &slot, 9);
  EXPECT_EQ(0ULL, slot.unowned_blocked_call_trace_id.load(std::memory_order_acquire));
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.unowned_blocked_state.load(std::memory_order_acquire));
  // Acquiring all stripes after the rejected write verifies its unlock path.
  HeldWriterStripes held(profiler);
}

TEST(WallTailRecordingTest, TailCarriesWeightAccumulatedWhileBlocked) {
  Profiler* profiler = Profiler::instance();
  WallClockBlockTracker::BlockState slot;
  // The first blocked observation is recorded and publishes the trace; the
  // following ones are suppressed and accumulate the tail's pending weight.
  ASSERT_TRUE(slot.shouldRecordUnownedBlockedSample());
  slot.recordUnownedBlockedSample(42, OSThreadState::SLEEPING);
  constexpr u64 kSuppressed = 4;
  for (u64 i = 0; i < kSuppressed; i++) {
    ASSERT_FALSE(slot.shouldRecordUnownedBlockedSample());
  }

  u64 call_trace_id = 0;
  u64 weight = 0;
  OSThreadState state = OSThreadState::UNKNOWN;
  ASSERT_TRUE(slot.prepareUnownedBlockedTail(call_trace_id, weight, state));
  ASSERT_EQ(kSuppressed, weight);

  UnownedTailObserverScope observer;
  profiler->recordUnownedBlockedTail(1234, &slot, weight);

  ASSERT_EQ(1, g_observed_tails.load(std::memory_order_acquire));
  EXPECT_EQ(42ULL, g_observed_call_trace_id.load(std::memory_order_relaxed));
  EXPECT_EQ(kSuppressed, g_observed_weight.load(std::memory_order_relaxed))
      << "the tail sample must carry the weight accumulated while blocked";
  EXPECT_EQ(0ULL, slot.unowned_blocked_call_trace_id.load(std::memory_order_acquire));
}
