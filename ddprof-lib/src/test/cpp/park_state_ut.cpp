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
#include "counters.h"
#include "nativeMem.h"
#include "threadLocalData.h"
#include "threadFilter.h"
#include "wallClock.h"
#include "wallClockBlockTracker.h"

namespace {

struct ProfiledThreadDeleter {
  void operator()(ProfiledThread *thread) const {
    ProfiledThread::deleteForTest(thread);
  }
};

using TestProfiledThread = std::unique_ptr<ProfiledThread, ProfiledThreadDeleter>;

class BlockSlotsAllocationFailure {
public:
  BlockSlotsAllocationFailure() { ProfiledThread::failBlockSlotsAllocationForTest = true; }
  ~BlockSlotsAllocationFailure() { ProfiledThread::failBlockSlotsAllocationForTest = false; }
  BlockSlotsAllocationFailure(const BlockSlotsAllocationFailure&) = delete;
  BlockSlotsAllocationFailure& operator=(const BlockSlotsAllocationFailure&) = delete;
};

const long long kBlockSlotsBytes =
    static_cast<long long>(ProfiledThread::blockSlotsBytesForTest());

TestProfiledThread testThread(int tid) {
  return TestProfiledThread(ProfiledThread::forTid(tid));
}

} // namespace

// Tests cover FLAG_PARKED lifecycle and owned-block slot state transitions.
// The slot state lives in WallClockBlockTracker process-lifetime storage so the
// wall-clock timer can read it without dereferencing per-thread objects from
// another thread.

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

TEST(ProfiledThreadParkStateTest, ParkExitReturnsEntrySnapshot) {
  TestProfiledThread thread = testThread(12351);
  Context entered{};
  entered.spanId = 17;
  entered.rootSpanId = 18;
  ASSERT_TRUE(thread->parkEnter(123, entered));
  thread->setParkBlockToken(456);

  u64 start_ticks = 0;
  u64 token = 0;
  Context exited{};
  ASSERT_TRUE(thread->parkExit(start_ticks, exited, token));
  EXPECT_EQ(123ULL, start_ticks);
  EXPECT_EQ(456ULL, token);
  EXPECT_EQ(17ULL, exited.spanId);
  EXPECT_EQ(18ULL, exited.rootSpanId);
}

TEST(ProfiledThreadMonitorStateTest, MatchingExitReturnsEntrySnapshot) {
  TestProfiledThread thread = testThread(12352);
  Context entered{};
  entered.spanId = 21;
  ASSERT_TRUE(thread->monitorEnter(
      100, entered, 200, OSThreadState::MONITOR_WAIT));
  thread->setMonitorBlockToken(300);

  u64 start_ticks = 0;
  u64 blocker = 0;
  u64 token = 0;
  Context exited{};
  ASSERT_TRUE(thread->monitorExit(OSThreadState::MONITOR_WAIT, start_ticks,
                                  exited, blocker, token));
  EXPECT_EQ(100ULL, start_ticks);
  EXPECT_EQ(200ULL, blocker);
  EXPECT_EQ(300ULL, token);
  EXPECT_EQ(21ULL, exited.spanId);
}

TEST(ProfiledThreadMonitorStateTest, NestedContentionDoesNotReplaceObjectWait) {
  TestProfiledThread thread = testThread(12353);
  Context context{};
  ASSERT_TRUE(thread->monitorEnter(
      100, context, 200, OSThreadState::OBJECT_WAIT));
  thread->setMonitorBlockToken(300);
  EXPECT_FALSE(thread->monitorEnter(
      400, context, 500, OSThreadState::MONITOR_WAIT));

  u64 start_ticks = 0;
  u64 blocker = 0;
  u64 token = 0;
  Context exited{};
  EXPECT_FALSE(thread->monitorExit(OSThreadState::MONITOR_WAIT, start_ticks,
                                   exited, blocker, token));
  ASSERT_TRUE(thread->monitorExit(OSThreadState::OBJECT_WAIT, start_ticks,
                                  exited, blocker, token));
  EXPECT_EQ(100ULL, start_ticks);
  EXPECT_EQ(200ULL, blocker);
  EXPECT_EQ(300ULL, token);
}

TEST(ProfiledThreadMonitorStateTest, ClearAllowsRecoveryFromStaleState) {
  TestProfiledThread thread = testThread(12354);
  Context context{};
  ASSERT_TRUE(thread->monitorEnter(
      100, context, 200, OSThreadState::OBJECT_WAIT));
  thread->setMonitorBlockToken(300);
  thread->clearMonitorBlock();

  ASSERT_TRUE(thread->monitorEnter(
      400, context, 500, OSThreadState::MONITOR_WAIT));
  EXPECT_EQ(0ULL, thread->monitorBlockToken());
}

TEST(ProfiledThreadBlockSlotsTest, FreshThreadHasNoBlockSlots) {
  TestProfiledThread thread = testThread(12360);
  EXPECT_FALSE(thread->hasBlockSlots());
  EXPECT_FALSE(thread->snapshotForTest().block_slots_allocated);
}

TEST(ProfiledThreadBlockSlotsTest, FirstEnterAllocatesOnceAndLaterEntersReuseIt) {
  TestProfiledThread thread = testThread(12361);
  long long base = NativeMem::live(NM_THREAD_LOCAL);
  Context context{};
  ASSERT_TRUE(thread->parkEnter(1, context));
  ASSERT_TRUE(thread->hasBlockSlots());
  EXPECT_EQ(base + kBlockSlotsBytes, NativeMem::live(NM_THREAD_LOCAL));

  u64 token = 0;
  ASSERT_TRUE(thread->parkExit(token));
  ASSERT_TRUE(thread->parkEnter(2, context));
  ASSERT_TRUE(thread->taskBlockEnter(3, 4, context));
  ASSERT_TRUE(thread->monitorEnter(5, context, 6, OSThreadState::MONITOR_WAIT));
  EXPECT_EQ(base + kBlockSlotsBytes, NativeMem::live(NM_THREAD_LOCAL));
}

// Covers the heap path: ~ProfiledThread() must free the slots and their accounting.
TEST(ProfiledThreadBlockSlotsTest, DeletingThreadReleasesBlockSlots) {
  long long base = NativeMem::live(NM_THREAD_LOCAL);
  TestProfiledThread thread = testThread(12362);
  long long with_thread = NativeMem::live(NM_THREAD_LOCAL);
  Context context{};
  ASSERT_TRUE(thread->taskBlockEnter(7, 8, context));
  EXPECT_EQ(with_thread + kBlockSlotsBytes, NativeMem::live(NM_THREAD_LOCAL));
  thread.reset();
  EXPECT_EQ(base, NativeMem::live(NM_THREAD_LOCAL));
}

TEST(ProfiledThreadBlockSlotsTest, AllocationFailureDropsEveryEnterWithoutState) {
  TestProfiledThread thread = testThread(12363);
  long long base = NativeMem::live(NM_THREAD_LOCAL);
  long long failed_before = Counters::getCounter(TASK_BLOCK_STATE_ALLOC_FAILED);
  u32 flags_before = thread->snapshotForTest().misc_flags;
  Context context{};
  {
    BlockSlotsAllocationFailure failure;
    EXPECT_FALSE(thread->parkEnter(1, context));
    EXPECT_FALSE(thread->taskBlockEnter(2, 3, context));
    EXPECT_FALSE(thread->monitorEnter(4, context, 5, OSThreadState::OBJECT_WAIT));
  }
  EXPECT_EQ(failed_before + 3, Counters::getCounter(TASK_BLOCK_STATE_ALLOC_FAILED));
  EXPECT_FALSE(thread->hasBlockSlots());
  EXPECT_EQ(flags_before, thread->snapshotForTest().misc_flags);
  EXPECT_EQ(base, NativeMem::live(NM_THREAD_LOCAL));

  ASSERT_TRUE(thread->parkEnter(6, context)) << "a later enter must retry the allocation";
  EXPECT_EQ(failed_before + 3, Counters::getCounter(TASK_BLOCK_STATE_ALLOC_FAILED));
}

TEST(ProfiledThreadBlockSlotsTest, ReadersWithoutBlockSlotsAreNoOps) {
  TestProfiledThread thread = testThread(12364);
  long long base = NativeMem::live(NM_THREAD_LOCAL);
  thread->refreshBlockState(9);
  EXPECT_EQ(9ULL, thread->snapshotForTest().block_recording_epoch);

  u64 start_ticks = 0, blocker = 0, token = 0;
  Context context{};
  EXPECT_FALSE(thread->parkExit(start_ticks, context, token));
  EXPECT_FALSE(thread->taskBlockExit(1, start_ticks, context));
  EXPECT_FALSE(thread->monitorExit(OSThreadState::UNKNOWN, start_ticks, context,
                                   blocker, token));
  EXPECT_EQ(0ULL, thread->taskBlockToken());
  EXPECT_EQ(0ULL, thread->monitorBlockToken());
  EXPECT_EQ(0ULL, thread->abandonTaskBlock());
  thread->clearMonitorBlock();
  EXPECT_FALSE(thread->hasBlockSlots());
  EXPECT_EQ(base, NativeMem::live(NM_THREAD_LOCAL));
}

TEST(ProfiledThreadBlockSlotsTest, RefreshClearsExistingSlotsWithoutFreeingThem) {
  TestProfiledThread thread = testThread(12365);
  Context context{};
  ASSERT_TRUE(thread->monitorEnter(1, context, 2, OSThreadState::OBJECT_WAIT));
  thread->setMonitorBlockToken(3);
  long long allocated = NativeMem::live(NM_THREAD_LOCAL);
  thread->refreshBlockState(10);
  EXPECT_TRUE(thread->hasBlockSlots());
  EXPECT_EQ(0ULL, thread->monitorBlockToken());
  EXPECT_EQ(allocated, NativeMem::live(NM_THREAD_LOCAL));
  ASSERT_TRUE(thread->monitorEnter(4, context, 5, OSThreadState::MONITOR_WAIT));
}

TEST(ProfiledThreadBlockSlotsTest, PayloadFreeParkZeroesAnExistingParkToken) {
  TestProfiledThread thread = testThread(12366);
  u64 token = 0;
  ASSERT_TRUE(thread->parkEnter());
  ASSERT_TRUE(thread->parkExit(token));
  // Seeds a stale token directly; the producers never leave one behind.
  thread->setParkBlockToken(0x55);
  ASSERT_TRUE(thread->parkEnterWithoutPayload());
  EXPECT_FALSE(thread->parkEnterWithoutPayload());
  EXPECT_FALSE(thread->parkEnter());
  token = 1;
  ASSERT_TRUE(thread->parkExit(token));
  EXPECT_EQ(0ULL, token);
}

TEST(ProfiledThreadBlockSlotsTest, PayloadFreeParkExitWithoutSlotsClearsTheFlag) {
  TestProfiledThread thread = testThread(12367);
  long long base = NativeMem::live(NM_THREAD_LOCAL);
  ASSERT_TRUE(thread->parkEnterWithoutPayload());
  EXPECT_NE(0u, thread->snapshotForTest().misc_flags & ProfiledThread::FLAG_PARKED);
  u64 start_ticks = 1, token = 1;
  Context context{};
  context.spanId = 1;
  ASSERT_TRUE(thread->parkExit(start_ticks, context, token));
  EXPECT_EQ(0ULL, start_ticks);
  EXPECT_EQ(0ULL, token);
  EXPECT_EQ(0ULL, context.spanId);
  EXPECT_EQ(0u, thread->snapshotForTest().misc_flags & ProfiledThread::FLAG_PARKED);
  EXPECT_FALSE(thread->parkExit(start_ticks, context, token));
  EXPECT_FALSE(thread->hasBlockSlots());
  EXPECT_EQ(base, NativeMem::live(NM_THREAD_LOCAL));
}

TEST(WallClockOwnedBlockFilterTest, SlotStateTransitions) {
  WallClockBlockTracker::BlockState slot;

  EXPECT_EQ(OSThreadState::UNKNOWN, slot.activeBlockState());

  slot.setActiveBlockState(OSThreadState::SLEEPING);
  EXPECT_EQ(OSThreadState::SLEEPING, slot.activeBlockState());

  slot.setActiveBlockState(OSThreadState::CONDVAR_WAIT);
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot.activeBlockState());
  slot.setActiveBlockState(OSThreadState::UNKNOWN);
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.activeBlockState());
}

TEST(WallClockOncePerRunFilterTest, UnownedBlockedFallbackCarriesWeight) {
  WallClockBlockTracker::BlockState slot;

  EXPECT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());

  for (u64 i = 1; i < WallClockBlockTracker::BlockState::kUnownedBlockedFallbackRatio; i++) {
    EXPECT_FALSE(slot.shouldRecordUnownedBlockedSample());
  }

  EXPECT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(WallClockBlockTracker::BlockState::kUnownedBlockedFallbackRatio,
            slot.consumeUnownedBlockedWeight());

  slot.restoreUnownedBlockedWeight(4);
  EXPECT_EQ(4ULL, slot.consumeUnownedBlockedWeight());

  slot.resetUnownedBlockedSampling();
  EXPECT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());
}

TEST(WallClockOncePerRunFilterTest, UnownedBlockedFallbackFlushesTailWeightWithRecordedStack) {
  WallClockBlockTracker::BlockState slot;

  ASSERT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());
  slot.recordUnownedBlockedSample(42, OSThreadState::SLEEPING);

  for (u64 i = 1; i < WallClockBlockTracker::BlockState::kUnownedBlockedFallbackRatio; i++) {
    EXPECT_FALSE(slot.shouldRecordUnownedBlockedSample());
  }

  u64 call_trace_id = 0;
  u64 weight = 0;
  OSThreadState state = OSThreadState::UNKNOWN;
  EXPECT_TRUE(slot.peekUnownedBlockedTail(call_trace_id, weight, state));
  EXPECT_EQ(42ULL, call_trace_id);
  EXPECT_EQ(WallClockBlockTracker::BlockState::kUnownedBlockedFallbackRatio - 1, weight);
  EXPECT_EQ(OSThreadState::SLEEPING, state);

  // The dump-time liveness hook must still see the ID after preparation.
  EXPECT_EQ(42ULL, slot.unowned_blocked_call_trace_id.load(std::memory_order_acquire));
  slot.resetUnownedBlockedSampling();
  EXPECT_EQ(0ULL, slot.unowned_blocked_call_trace_id.load(std::memory_order_acquire));

  EXPECT_FALSE(slot.peekUnownedBlockedTail(call_trace_id, weight, state));
  EXPECT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());
}

TEST(WallClockOncePerRunFilterTest, UnownedBlockedFallbackDoesNotFlushWithoutRecordedStack) {
  WallClockBlockTracker::BlockState slot;

  ASSERT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());

  for (u64 i = 1; i < WallClockBlockTracker::BlockState::kUnownedBlockedFallbackRatio; i++) {
    EXPECT_FALSE(slot.shouldRecordUnownedBlockedSample());
  }

  u64 call_trace_id = 0;
  u64 weight = 0;
  OSThreadState state = OSThreadState::UNKNOWN;
  EXPECT_FALSE(slot.peekUnownedBlockedTail(call_trace_id, weight, state));
  EXPECT_EQ(0ULL, call_trace_id);
  EXPECT_EQ(WallClockBlockTracker::BlockState::kUnownedBlockedFallbackRatio - 1, weight);
  EXPECT_EQ(OSThreadState::UNKNOWN, state);
  EXPECT_TRUE(slot.shouldRecordUnownedBlockedSample());
}

TEST(WallClockOncePerRunFilterTest, UnownedBlockedFallbackDoesNotFlushWithoutSavedState) {
  WallClockBlockTracker::BlockState slot;

  ASSERT_TRUE(slot.shouldRecordUnownedBlockedSample());
  EXPECT_EQ(1ULL, slot.consumeUnownedBlockedWeight());
  slot.recordUnownedBlockedSample(42, OSThreadState::SLEEPING);

  for (u64 i = 1; i < WallClockBlockTracker::BlockState::kUnownedBlockedFallbackRatio; i++) {
    EXPECT_FALSE(slot.shouldRecordUnownedBlockedSample());
  }

  slot.unowned_blocked_state.store(OSThreadState::UNKNOWN, std::memory_order_relaxed);

  u64 call_trace_id = 0;
  u64 weight = 0;
  OSThreadState state = OSThreadState::SLEEPING;
  EXPECT_FALSE(slot.peekUnownedBlockedTail(call_trace_id, weight, state));
  EXPECT_EQ(42ULL, call_trace_id);
  EXPECT_EQ(WallClockBlockTracker::BlockState::kUnownedBlockedFallbackRatio - 1, weight);
  EXPECT_EQ(OSThreadState::UNKNOWN, state);
}

TEST(WallClockOncePerRunFilterTest, UnownedBlockedTailStateConcurrentStress) {
  WallClockBlockTracker::BlockState slot;
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
          bool flushed = slot.peekUnownedBlockedTail(call_trace_id, weight, state);
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
  EXPECT_FALSE(slot.peekUnownedBlockedTail(call_trace_id, weight, state));
}

TEST(WallClockOncePerRunFilterTest, FilterHelpersManageActiveBlockState) {
  ThreadFilter filter;
  WallClockBlockTracker tracker;
  filter.setBlockTracker(&tracker);
  filter.init("1");
  ThreadFilter::SlotID slot_id = filter.registerThread(1234);

  tracker.enterBlockedRun(&filter, slot_id, OSThreadState::CONDVAR_WAIT);
  WallClockBlockTracker::BlockState *slot = tracker.slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot->activeBlockState());

  tracker.resetSlot(slot_id);
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_EQ(0ULL, slot->sampledBlockGeneration());
}

TEST(WallClockOncePerRunFilterTest, ResetClearsOwnedBlockOnSlotReuse) {
  ThreadFilter filter;
  WallClockBlockTracker tracker;
  filter.setBlockTracker(&tracker);
  filter.init("1");
  ThreadFilter::SlotID slot_id = filter.registerThread(1234);
  tracker.enterBlockedRun(&filter, slot_id, OSThreadState::CONDVAR_WAIT);
  WallClockBlockTracker::BlockState *slot = tracker.slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot->activeBlockState());
  slot->markBlockGenerationSampled(slot->blockGeneration());
  ASSERT_EQ(slot->blockGeneration(), slot->sampledBlockGeneration());

  filter.unregisterThread(slot_id, 1234);
  ASSERT_EQ(slot_id, filter.registerThread(5678));

  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_EQ(0ULL, slot->sampledBlockGeneration());
}
