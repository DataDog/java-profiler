/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "counters.h"
#include "profiler.h"
#include "taskBlockRecorder.h"
#include "tsc.h"

#include <atomic>
#include <chrono>
#include <future>
#include <memory>
#include <thread>

namespace {

std::atomic<Profiler::TaskBlockRecordResult> g_record_result{
    Profiler::TaskBlockRecordResult::RECORDED};
std::atomic<int> g_record_calls{0};

Profiler::TaskBlockRecordResult recordTaskBlockForTest(
    int tid, jthread thread, int start_depth, TaskBlockEvent* event) {
  g_record_calls.fetch_add(1, std::memory_order_relaxed);
  return g_record_result.load(std::memory_order_acquire);
}

u64 minEligibleEndTicks(u64 start_ticks) {
  u64 low = start_ticks + 1;
  u64 high = low;
  while (!exceedsMinTaskBlockDuration(start_ticks, high)) {
    high = start_ticks + ((high - start_ticks) * 2);
  }
  while (low < high) {
    u64 mid = low + ((high - low) / 2);
    if (exceedsMinTaskBlockDuration(start_ticks, mid)) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return low;
}

class TaskBlockRecorderTest : public ::testing::Test {
protected:
  void SetUp() override {
    Counters::reset();
    initializeTaskBlockDurationThreshold();
    g_record_result.store(Profiler::TaskBlockRecordResult::RECORDED,
                          std::memory_order_release);
    g_record_calls.store(0, std::memory_order_relaxed);
    Profiler::setTaskBlockRecordOverrideForTest(recordTaskBlockForTest);
  }

  void TearDown() override {
    Profiler::setTaskBlockRecordOverrideForTest(nullptr);
    Counters::reset();
  }
};

} // namespace

TEST_F(TaskBlockRecorderTest, TraceContextIsRejectedBeforeDuration) {
  Context context{};
  context.spanId = 123;

  EXPECT_FALSE(taskBlockPassesBasicEligibility(100, 100, context));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TRACE_CONTEXT));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
}

TEST_F(TaskBlockRecorderTest, DurationThresholdIncludesExactBoundary) {
  Context context{};
  u64 start_ticks = TSC::ticks();
  u64 passing_end = minEligibleEndTicks(start_ticks);

  EXPECT_TRUE(taskBlockPassesBasicEligibility(
      start_ticks, passing_end, context));
  EXPECT_FALSE(taskBlockPassesBasicEligibility(
      start_ticks, passing_end - 1, context));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
}

TEST_F(TaskBlockRecorderTest, RotationRejectsNewActivity) {
  Profiler* profiler = Profiler::instance();
  profiler->beginTaskBlockRotationForTest();

  EXPECT_FALSE(profiler->tryEnterTaskBlockActivity());
  TaskBlockActivity activity;
  EXPECT_FALSE(activity.active());
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));

  profiler->endTaskBlockRotationForTest();
  ASSERT_TRUE(profiler->tryEnterTaskBlockActivity());
  profiler->leaveTaskBlockActivity();
}

TEST_F(TaskBlockRecorderTest, RotationWaitsForInflightActivity) {
  Profiler* profiler = Profiler::instance();
  ASSERT_TRUE(profiler->tryEnterTaskBlockActivity());
  ASSERT_EQ(1, profiler->taskBlockInflightForTest());

  std::atomic<bool> rotation_returned{false};
  std::thread rotation([&]() {
    profiler->beginTaskBlockRotationForTest();
    rotation_returned.store(true, std::memory_order_release);
    profiler->endTaskBlockRotationForTest();
  });

  auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
  while (!profiler->taskBlockRotationActiveForTest() &&
         std::chrono::steady_clock::now() < deadline) {
    std::this_thread::yield();
  }

  bool rotation_active = profiler->taskBlockRotationActiveForTest();
  EXPECT_TRUE(rotation_active);
  EXPECT_EQ(1, profiler->taskBlockInflightForTest());
  EXPECT_FALSE(rotation_returned.load(std::memory_order_acquire));
  if (rotation_active) {
    bool entered = profiler->tryEnterTaskBlockActivity();
    EXPECT_FALSE(entered);
    if (entered) profiler->leaveTaskBlockActivity();
  }

  profiler->leaveTaskBlockActivity();
  rotation.join();

  EXPECT_TRUE(rotation_returned.load(std::memory_order_acquire));
  EXPECT_FALSE(profiler->taskBlockRotationActiveForTest());
  EXPECT_EQ(0, profiler->taskBlockInflightForTest());
  ASSERT_TRUE(profiler->tryEnterTaskBlockActivity());
  profiler->leaveTaskBlockActivity();
}

TEST_F(TaskBlockRecorderTest, RotationRejectsEndWithoutStrandingLifecycle) {
  constexpr int tid = 12345;
  ThreadFilter filter;
  filter.init("", true);
  ThreadFilter::SlotID slot_id = filter.registerThread(tid);
  ASSERT_GE(slot_id, 0);

  std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current(
      ProfiledThread::forTid(tid), ProfiledThread::deleteForTest);
  current->setFilterSlotId(slot_id);
  u64 token = filter.enterBlockedRun(
      slot_id, OSThreadState::SLEEPING, BlockRunOwner::JAVA);
  ASSERT_NE(0ULL, token);
  Context context{};
  ASSERT_TRUE(current->taskBlockEnter(token, TSC::ticks(), context));

  Profiler* profiler = Profiler::instance();
  profiler->beginTaskBlockRotationForTest();
  std::future<bool> result = std::async(std::launch::async, [&]() {
    return recordTaskBlockAtExit(
        current.get(), &filter, nullptr, 1, token,
        ThreadFilter::tokenSlotId(token),
        ThreadFilter::tokenGeneration(token), 0, 0);
  });

  std::future_status status = result.wait_for(std::chrono::seconds(1));
  bool returned_during_rotation = status == std::future_status::ready;
  EXPECT_TRUE(returned_during_rotation);
  if (returned_during_rotation) {
    ThreadFilter::Slot* slot = filter.slotForId(slot_id);
    EXPECT_NE(nullptr, slot);
    if (slot != nullptr) {
      EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
      EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
    }

    u64 next_token = filter.enterBlockedRun(
        slot_id, OSThreadState::SLEEPING, BlockRunOwner::JAVA);
    EXPECT_NE(0ULL, next_token);
    EXPECT_TRUE(current->taskBlockEnter(next_token, TSC::ticks(), context));
    u64 ignored_ticks = 0;
    Context ignored_context{};
    EXPECT_TRUE(current->taskBlockExit(
        next_token, ignored_ticks, ignored_context));
    EXPECT_TRUE(filter.exitBlockedRun(
        slot_id, ThreadFilter::tokenGeneration(next_token)));
  }

  profiler->endTaskBlockRotationForTest();
  EXPECT_FALSE(result.get());
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));
}

TEST_F(TaskBlockRecorderTest, StackCaptureFailureIsCountedAndActivityReleased) {
  g_record_result.store(Profiler::TaskBlockRecordResult::STACK_CAPTURE_FAILED,
                        std::memory_order_release);
  Context context{};
  u64 start_ticks = TSC::ticks();
  u64 end_ticks = minEligibleEndTicks(start_ticks);

  EXPECT_FALSE(recordTaskBlockIfEligible(
      123, nullptr, 0, start_ticks, end_ticks, context, 0, 0,
      OSThreadState::SLEEPING));

  EXPECT_EQ(1, g_record_calls.load(std::memory_order_relaxed));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_EMITTED));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_STACK_CAPTURE_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_SKIPPED_TRACE_CONTEXT));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));
  EXPECT_EQ(0, Profiler::instance()->taskBlockInflightForTest());
  ASSERT_TRUE(Profiler::instance()->tryEnterTaskBlockActivity());
  Profiler::instance()->leaveTaskBlockActivity();
}

TEST_F(TaskBlockRecorderTest, RecordFailureIsCountedAndActivityReleased) {
  g_record_result.store(Profiler::TaskBlockRecordResult::RECORD_FAILED,
                        std::memory_order_release);
  Context context{};
  u64 start_ticks = TSC::ticks();
  u64 end_ticks = minEligibleEndTicks(start_ticks);

  EXPECT_FALSE(recordTaskBlockIfEligible(
      123, nullptr, 0, start_ticks, end_ticks, context, 0, 0,
      OSThreadState::SLEEPING));

  EXPECT_EQ(1, g_record_calls.load(std::memory_order_relaxed));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_EMITTED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_STACK_CAPTURE_FAILED));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_SKIPPED_TRACE_CONTEXT));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));
  EXPECT_EQ(0, Profiler::instance()->taskBlockInflightForTest());
  ASSERT_TRUE(Profiler::instance()->tryEnterTaskBlockActivity());
  Profiler::instance()->leaveTaskBlockActivity();
}
