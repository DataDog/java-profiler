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
#include <atomic>
#include <memory>
#include <thread>
#include <vector>
#include "threadLocalData.h"
#include "threadFilter.h"
#include "wallClock.h"

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

// Tests cover FLAG_PARKED lifecycle and owned-block slot state transitions.
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

TEST(ProfiledThreadParkStateTest, JavaThreadTypeSurvivesParkTransitions) {
  TestProfiledThread thread = testThread(12349);

  thread->setJavaThread(true);
  EXPECT_EQ(ProfiledThread::TYPE_JAVA_THREAD, thread->threadType());

  EXPECT_TRUE(thread->parkEnter());
  EXPECT_EQ(ProfiledThread::TYPE_JAVA_THREAD, thread->threadType());

  thread->setJavaThread(false);
  EXPECT_EQ(ProfiledThread::TYPE_NOT_JAVA_THREAD, thread->threadType());

  u64 park_block_token = 0;
  EXPECT_TRUE(thread->parkExit(park_block_token));
  EXPECT_EQ(ProfiledThread::TYPE_NOT_JAVA_THREAD, thread->threadType());
}

TEST(ProfiledThreadParkStateTest, ConcurrentTypeAndParkUpdatesKeepValidTypeBits) {
  TestProfiledThread thread = testThread(12350);
  std::atomic<bool> stop{false};

  std::thread type_toggler([&] {
    for (int i = 0; i < 10000; i++) {
      thread->setJavaThread((i & 1) == 0);
    }
    stop.store(true, std::memory_order_release);
  });

  while (!stop.load(std::memory_order_acquire)) {
    thread->parkEnter();
    u64 park_block_token = 0;
    thread->parkExit(park_block_token);
    ProfiledThread::ThreadType type = thread->threadType();
    EXPECT_TRUE(type == ProfiledThread::TYPE_JAVA_THREAD ||
                type == ProfiledThread::TYPE_NOT_JAVA_THREAD ||
                type == ProfiledThread::TYPE_UNKNOWN);
  }

  type_toggler.join();
  u64 park_block_token = 0;
  thread->parkExit(park_block_token);
  ProfiledThread::ThreadType type = thread->threadType();
  EXPECT_TRUE(type == ProfiledThread::TYPE_JAVA_THREAD ||
              type == ProfiledThread::TYPE_NOT_JAVA_THREAD);
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

TEST(WallClockOwnedBlockFilterTest, SlotStateTransitions) {
  ThreadFilter::Slot slot;

  EXPECT_EQ(OSThreadState::UNKNOWN, slot.activeBlockState());

  slot.setActiveBlockState(OSThreadState::SLEEPING);
  EXPECT_EQ(OSThreadState::SLEEPING, slot.activeBlockState());

  slot.setActiveBlockState(OSThreadState::CONDVAR_WAIT);
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot.activeBlockState());
  slot.setActiveBlockState(OSThreadState::UNKNOWN);
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.activeBlockState());
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

TEST(WallClockOncePerRunFilterTest, UnownedBlockedFallbackFlushesTailWeightWithRecordedStack) {
  ThreadFilter::Slot slot;

  ASSERT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());
  slot.recordUnownedBlockedSample(42, OSThreadState::SLEEPING);

  for (u64 i = 1; i < ThreadFilter::Slot::kUnownedBlockedFallbackRatio; i++) {
    EXPECT_FALSE(slot.shouldRecordUnownedBlockedSample());
  }

  u64 call_trace_id = 0;
  u64 weight = 0;
  OSThreadState state = OSThreadState::UNKNOWN;
  EXPECT_TRUE(slot.flushUnownedBlockedTail(call_trace_id, weight, state));
  EXPECT_EQ(42ULL, call_trace_id);
  EXPECT_EQ(ThreadFilter::Slot::kUnownedBlockedFallbackRatio - 1, weight);
  EXPECT_EQ(OSThreadState::SLEEPING, state);

  EXPECT_FALSE(slot.flushUnownedBlockedTail(call_trace_id, weight, state));
  EXPECT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());
}

TEST(WallClockOncePerRunFilterTest, UnownedBlockedFallbackDoesNotFlushWithoutRecordedStack) {
  ThreadFilter::Slot slot;

  ASSERT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());

  for (u64 i = 1; i < ThreadFilter::Slot::kUnownedBlockedFallbackRatio; i++) {
    EXPECT_FALSE(slot.shouldRecordUnownedBlockedSample());
  }

  u64 call_trace_id = 0;
  u64 weight = 0;
  OSThreadState state = OSThreadState::UNKNOWN;
  EXPECT_FALSE(slot.flushUnownedBlockedTail(call_trace_id, weight, state));
  EXPECT_EQ(0ULL, call_trace_id);
  EXPECT_EQ(ThreadFilter::Slot::kUnownedBlockedFallbackRatio - 1, weight);
  EXPECT_EQ(OSThreadState::UNKNOWN, state);
  EXPECT_TRUE(slot.shouldRecordUnownedBlockedSample());
}

TEST(WallClockOncePerRunFilterTest, UnownedBlockedFallbackDoesNotFlushWithoutSavedState) {
  ThreadFilter::Slot slot;

  ASSERT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());
  slot.recordUnownedBlockedSample(42, OSThreadState::SLEEPING);

  for (u64 i = 1; i < ThreadFilter::Slot::kUnownedBlockedFallbackRatio; i++) {
    EXPECT_FALSE(slot.shouldRecordUnownedBlockedSample());
  }

  slot.unowned_blocked_state.store(OSThreadState::UNKNOWN, std::memory_order_relaxed);

  u64 call_trace_id = 0;
  u64 weight = 0;
  OSThreadState state = OSThreadState::SLEEPING;
  EXPECT_FALSE(slot.flushUnownedBlockedTail(call_trace_id, weight, state));
  EXPECT_EQ(42ULL, call_trace_id);
  EXPECT_EQ(ThreadFilter::Slot::kUnownedBlockedFallbackRatio - 1, weight);
  EXPECT_EQ(OSThreadState::UNKNOWN, state);
}

TEST(WallClockOncePerRunFilterTest, UnownedBlockedTailStateConcurrentStress) {
  ThreadFilter::Slot slot;
  std::atomic<bool> start{false};
  std::atomic<int> invariant_failures{0};
  std::vector<std::thread> workers;

  for (int worker = 0; worker < 4; worker++) {
    workers.emplace_back([&, worker] {
      while (!start.load(std::memory_order_acquire)) {
      }
      for (int i = 0; i < 2000; i++) {
        int operation = (i + worker) % 4;
        if (operation == 0) {
          if (slot.shouldRecordUnownedBlockedSample()) {
            u64 weight = slot.consumeUnownedBlockedWeight();
            if (weight == 0) {
              invariant_failures.fetch_add(1, std::memory_order_relaxed);
            }
          }
        } else if (operation == 1) {
          slot.recordUnownedBlockedSample(
              1000 + static_cast<u64>(worker), OSThreadState::SLEEPING);
        } else if (operation == 2) {
          u64 call_trace_id = 0;
          u64 weight = 0;
          OSThreadState state = OSThreadState::UNKNOWN;
          bool flushed = slot.flushUnownedBlockedTail(call_trace_id, weight, state);
          if (flushed &&
              (call_trace_id == 0 || weight == 0 ||
               state != OSThreadState::SLEEPING)) {
            invariant_failures.fetch_add(1, std::memory_order_relaxed);
          }
        } else {
          slot.resetUnownedBlockedSampling();
        }
      }
    });
  }

  start.store(true, std::memory_order_release);
  for (std::thread& worker : workers) {
    worker.join();
  }

  EXPECT_EQ(0, invariant_failures.load(std::memory_order_relaxed));

  slot.resetUnownedBlockedSampling();
  u64 call_trace_id = 0;
  u64 weight = 0;
  OSThreadState state = OSThreadState::UNKNOWN;
  EXPECT_FALSE(slot.flushUnownedBlockedTail(call_trace_id, weight, state));
}

TEST(WallClockOncePerRunFilterTest, FilterHelpersManageActiveBlockState) {
  ThreadFilter filter;
  filter.init("1");
  ThreadFilter::SlotID slot_id = filter.registerThread();

  filter.enterBlockedRun(slot_id, OSThreadState::CONDVAR_WAIT);
  ThreadFilter::Slot *slot = filter.slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot->activeBlockState());

  filter.exitBlockedRun(slot_id);
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
}

TEST(WallClockOncePerRunFilterTest, ResetClearsOwnedBlockOnSlotReuse) {
  ThreadFilter filter;
  filter.init("1");
  ThreadFilter::SlotID slot_id = filter.registerThread();
  filter.enterBlockedRun(slot_id, OSThreadState::CONDVAR_WAIT);
  ThreadFilter::Slot *slot = filter.slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot->activeBlockState());

  filter.resetSlotRunState(slot_id);

  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
}
