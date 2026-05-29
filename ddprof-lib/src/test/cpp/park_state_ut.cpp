/*
 * Copyright 2026 Datadog, Inc.
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

#include <gtest/gtest.h>
#include "thread.h"
#include "threadFilter.h"

// Tests cover FLAG_PARKED lifecycle and the once-per-run slot filter state transitions.

TEST(ProfiledThreadParkStateTest, ParkFlagLifecycle) {
  ProfiledThread *thread = ProfiledThread::forTid(12345);

  u64 start_ticks = 0;
  Context park_context = {};
  EXPECT_FALSE(thread->parkExit(start_ticks, park_context)); // not parked initially

  thread->parkEnter(777);

  EXPECT_TRUE(thread->parkExit(start_ticks, park_context));
  EXPECT_EQ(777ULL, start_ticks);
  EXPECT_EQ(0ULL, park_context.spanId);    // no OTEP TLS in unit test
  EXPECT_EQ(0ULL, park_context.rootSpanId);

  EXPECT_FALSE(thread->parkExit(start_ticks, park_context)); // idempotent after clear
  ProfiledThread::deleteForTest(thread);
}

TEST(ProfiledThreadParkStateTest, NewThreadStartsNotParked) {
  ProfiledThread *thread = ProfiledThread::forTid(12346);
  u64 start_ticks = 0;
  Context park_context = {};
  EXPECT_FALSE(thread->parkExit(start_ticks, park_context));
  // Out-params must not be touched on failed exit.
  EXPECT_EQ(0ULL, start_ticks);
  ProfiledThread::deleteForTest(thread);
}

TEST(ProfiledThreadParkStateTest, SecondParkEnterOverwritesTicks) {
  ProfiledThread *thread = ProfiledThread::forTid(12347);
  thread->parkEnter(100);
  thread->parkEnter(200); // second enter before exit: overwrites ticks

  u64 start_ticks = 0;
  Context park_context = {};
  EXPECT_TRUE(thread->parkExit(start_ticks, park_context));
  EXPECT_EQ(200ULL, start_ticks); // most recent parkEnter wins

  // Flag is now clear; second exit is a no-op.
  EXPECT_FALSE(thread->parkExit(start_ticks, park_context));
  ProfiledThread::deleteForTest(thread);
}

TEST(WallClockOncePerRunFilterTest, SlotStateTransitions) {
  ThreadFilter::Slot slot;

  EXPECT_FALSE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.lastSampledState());

  // First signal: arm.
  slot.markSampledThisRun(OSThreadState::SLEEPING);
  EXPECT_TRUE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::SLEEPING, slot.lastSampledState());

  // Same state again: suppress (flag + state both match).
  EXPECT_TRUE(slot.sampledThisRun() &&
              OSThreadState::SLEEPING == slot.lastSampledState());

  // Transition within skip set (SLEEPING → CONDVAR_WAIT): state mismatch → re-arm.
  EXPECT_FALSE(slot.sampledThisRun() &&
               OSThreadState::CONDVAR_WAIT == slot.lastSampledState());
  slot.markSampledThisRun(OSThreadState::CONDVAR_WAIT);
  EXPECT_TRUE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot.lastSampledState());

  // Leave skip set: reset → next blocked entry re-arms.
  slot.resetSampledRun(OSThreadState::RUNNABLE);
  EXPECT_FALSE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::RUNNABLE, slot.lastSampledState());

  slot.markSampledThisRun(OSThreadState::SLEEPING);
  EXPECT_TRUE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::SLEEPING, slot.lastSampledState());
}

// Slot reuse: stale armed state from the previous owner must be cleared before
// the new thread takes the slot (ThreadFilter::resetSlotRunState does this).
TEST(WallClockOncePerRunFilterTest, ResetClearsArmedFlagOnSlotReuse) {
  ThreadFilter::Slot slot;
  slot.markSampledThisRun(OSThreadState::CONDVAR_WAIT);
  EXPECT_TRUE(slot.sampledThisRun());

  slot.resetSampledRun(OSThreadState::UNKNOWN);

  EXPECT_FALSE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.lastSampledState());
}
