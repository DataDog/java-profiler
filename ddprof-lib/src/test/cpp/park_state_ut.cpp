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
#include <memory>
#include "thread.h"
#include "threadFilter.h"

namespace {

struct ProfiledThreadDeleter {
  void operator()(ProfiledThread *thread) const {
    ProfiledThread::deleteForTest(thread);
  }
};

using TestProfiledThread = std::unique_ptr<ProfiledThread, ProfiledThreadDeleter>;

TestProfiledThread testThread(int tid) {
  return TestProfiledThread(ProfiledThread::forTid(tid));
}

} // namespace

// Tests cover FLAG_PARKED lifecycle and the once-per-run slot filter state transitions.
// The slot state lives in ThreadFilter process-lifetime storage so the wall-clock
// timer can read it without dereferencing per-thread objects from another thread.

TEST(ProfiledThreadParkStateTest, ParkFlagLifecycle) {
  TestProfiledThread thread = testThread(12345);

  u64 park_block_token = 0;
  EXPECT_FALSE(thread->parkExit(park_block_token)); // not parked initially

  EXPECT_TRUE(thread->parkEnter());
  thread->setParkBlockToken(0x123400000001ULL);

  EXPECT_TRUE(thread->parkExit(park_block_token));
  EXPECT_EQ(0x123400000001ULL, park_block_token);

  EXPECT_FALSE(thread->parkExit(park_block_token)); // idempotent after clear
}

TEST(ProfiledThreadParkStateTest, NewThreadStartsNotParked) {
  TestProfiledThread thread = testThread(12346);
  u64 park_block_token = 0;
  EXPECT_FALSE(thread->parkExit(park_block_token));
  // Out-params must not be touched on failed exit.
  EXPECT_EQ(0ULL, park_block_token);
}

TEST(ProfiledThreadParkStateTest, SecondParkEnterPreservesToken) {
  TestProfiledThread thread = testThread(12347);
  EXPECT_TRUE(thread->parkEnter());
  thread->setParkBlockToken(0xfeed00000001ULL);
  EXPECT_FALSE(thread->parkEnter());

  u64 park_block_token = 0;
  EXPECT_TRUE(thread->parkExit(park_block_token));
  EXPECT_EQ(0xfeed00000001ULL, park_block_token); // first owner token wins

  // Flag is now clear; second exit is a no-op.
  EXPECT_FALSE(thread->parkExit(park_block_token));
  EXPECT_EQ(0xfeed00000001ULL, park_block_token);
}

TEST(ProfiledThreadParkStateTest, ParkExitReturnsZeroTokenWhenBlockRunWasNotArmed) {
  TestProfiledThread thread = testThread(12348);
  EXPECT_TRUE(thread->parkEnter());
  thread->setParkBlockToken(0);

  u64 park_block_token = 42;
  EXPECT_TRUE(thread->parkExit(park_block_token));
  EXPECT_EQ(0ULL, park_block_token);
}

TEST(WallClockOncePerRunFilterTest, SlotStateTransitions) {
  ThreadFilter::Slot slot;

  EXPECT_FALSE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.lastSampledState());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.activeBlockState());

  // First signal: arm.
  slot.setActiveBlockState(OSThreadState::SLEEPING);
  slot.markSampledThisRun(OSThreadState::SLEEPING);
  EXPECT_TRUE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::SLEEPING, slot.lastSampledState());
  EXPECT_EQ(OSThreadState::SLEEPING, slot.activeBlockState());

  // Same state again: suppress (flag + state both match).
  EXPECT_TRUE(slot.sampledThisRun() &&
              OSThreadState::SLEEPING == slot.lastSampledState());
  EXPECT_TRUE(slot.sampledThisRun() &&
              slot.activeBlockState() == slot.lastSampledState());

  // Transition within skip set (SLEEPING -> CONDVAR_WAIT): state mismatch -> re-arm.
  slot.setActiveBlockState(OSThreadState::CONDVAR_WAIT);
  EXPECT_FALSE(slot.sampledThisRun() &&
               OSThreadState::CONDVAR_WAIT == slot.lastSampledState());
  slot.markSampledThisRun(OSThreadState::CONDVAR_WAIT);
  EXPECT_TRUE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot.lastSampledState());
  EXPECT_TRUE(slot.sampledThisRun() &&
              slot.activeBlockState() == slot.lastSampledState());

  // Leave skip set: reset -> next blocked entry re-arms.
  slot.setActiveBlockState(OSThreadState::UNKNOWN);
  slot.resetSampledRun(OSThreadState::RUNNABLE);
  EXPECT_FALSE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::RUNNABLE, slot.lastSampledState());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.activeBlockState());

  slot.setActiveBlockState(OSThreadState::SLEEPING);
  slot.markSampledThisRun(OSThreadState::SLEEPING);
  EXPECT_TRUE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::SLEEPING, slot.lastSampledState());
  EXPECT_EQ(OSThreadState::SLEEPING, slot.activeBlockState());
}

TEST(WallClockOncePerRunFilterTest, UnownedBlockedFallbackCarriesWeight) {
  ThreadFilter::Slot slot;

  EXPECT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());

  for (u64 i = 1; i < ThreadFilter::Slot::kUnownedBlockedFallbackRatio; i++) {
    EXPECT_FALSE(slot.shouldRecordUnownedBlockedSample());
  }

  EXPECT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(ThreadFilter::Slot::kUnownedBlockedFallbackRatio,
            slot.consumeUnownedBlockedWeight());

  slot.restoreUnownedBlockedWeight(4);
  EXPECT_EQ(4ULL, slot.consumeUnownedBlockedWeight());

  slot.resetUnownedBlockedSampling();
  EXPECT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());
}

TEST(WallClockOncePerRunFilterTest, FilterHelpersManageActiveBlockState) {
  ThreadFilter filter;
  filter.init("1");
  ThreadFilter::SlotID slot_id = filter.registerThread();

  filter.enterBlockedRun(slot_id, OSThreadState::CONDVAR_WAIT);
  ThreadFilter::Slot *slot = filter.slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot->activeBlockState());

  slot->markSampledThisRun(OSThreadState::CONDVAR_WAIT);
  EXPECT_TRUE(slot->sampledThisRun());
  EXPECT_TRUE(slot->sampledThisRun() &&
              slot->activeBlockState() == slot->lastSampledState());

  filter.exitBlockedRun(slot_id);
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_FALSE(slot->sampledThisRun());
  EXPECT_EQ(OSThreadState::RUNNABLE, slot->lastSampledState());
}

// Slot reuse: stale armed state from the previous owner must be cleared before
// the new thread takes the slot (ThreadFilter::resetSlotRunState does this).
TEST(WallClockOncePerRunFilterTest, ResetClearsArmedFlagOnSlotReuse) {
  ThreadFilter filter;
  filter.init("1");
  ThreadFilter::SlotID slot_id = filter.registerThread();
  filter.enterBlockedRun(slot_id, OSThreadState::CONDVAR_WAIT);
  ThreadFilter::Slot *slot = filter.slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  slot->markSampledThisRun(OSThreadState::CONDVAR_WAIT);
  EXPECT_TRUE(slot->sampledThisRun());
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot->activeBlockState());

  filter.resetSlotRunState(slot_id);

  EXPECT_FALSE(slot->sampledThisRun());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->lastSampledState());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
}
