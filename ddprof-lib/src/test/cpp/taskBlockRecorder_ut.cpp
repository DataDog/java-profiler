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
#include <thread>
#include <vector>

namespace {

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
    Profiler::resetTaskBlockRecordObservableForTest();
    Profiler::instance()->setTaskBlockAsyncActiveForTest(false);
    Profiler::instance()->discardTaskBlockQueueForTest();
    Profiler::instance()->threadFilter()->init("enabled");
    Profiler::instance()->threadFilter()->clearActive();
  }

  void TearDown() override {
    Profiler::resetTaskBlockRecordObservableForTest();
    Profiler::instance()->setTaskBlockAsyncActiveForTest(false);
    Profiler::instance()->discardTaskBlockQueueForTest();
    Profiler::instance()->threadFilter()->clearActive();
    Counters::reset();
  }

  static bool recordSuccess(int, TaskBlockEvent*) {
    return true;
  }

  static bool recordFailure(int, TaskBlockEvent*) {
    return false;
  }

  TaskBlockEvent eventWithStack(u64 id) {
    TaskBlockEvent event{};
    event._start = TSC::ticks();
    event._end = minEligibleEndTicks(event._start);
    event._blocker = 0x10 + id;
    event._callTraceId = id;
    event._observedBlockingState = OSThreadState::IO_WAIT;
    return event;
  }
};

} // namespace

TEST_F(TaskBlockRecorderTest, BasicEligibilityRejectsTraceContextBeforeDuration) {
  Context ctx{};
  ctx.spanId = 123;
  EXPECT_FALSE(taskBlockPassesBasicEligibility(100, 100, ctx));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TRACE_CONTEXT));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
}

TEST_F(TaskBlockRecorderTest, BasicEligibilityCoversDurationBoundary) {
  Context ctx{};
  u64 start_ticks = TSC::ticks();
  u64 passing_end = minEligibleEndTicks(start_ticks);

  EXPECT_TRUE(taskBlockPassesBasicEligibility(start_ticks, passing_end, ctx));
  EXPECT_FALSE(taskBlockPassesBasicEligibility(start_ticks, passing_end - 1, ctx));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
}

TEST_F(TaskBlockRecorderTest, StackReferencePathCoversExplicitIdsAndMissingReference) {
  Profiler::instance()->setRecordTaskBlockLiveOverrideForTest(recordSuccess);
  Context ctx{};
  u64 start_ticks = TSC::ticks();
  u64 end_ticks = minEligibleEndTicks(start_ticks);

  EXPECT_TRUE(recordTaskBlockWithStackReferenceIfEligible(
      17, start_ticks, end_ticks, ctx, 0x10, 0x20, 0x1, 0,
      OSThreadState::IO_WAIT));
  EXPECT_EQ(0x1ULL, Profiler::lastRecordedTaskBlockEventForTest()._callTraceId);

  EXPECT_TRUE(recordTaskBlockWithStackReferenceIfEligible(
      17, start_ticks, end_ticks, ctx, 0x10, 0x20, 0, 0x2,
      OSThreadState::IO_WAIT));
  EXPECT_EQ(0x2ULL, Profiler::lastRecordedTaskBlockEventForTest()._correlationId);

  EXPECT_TRUE(recordTaskBlockWithStackReferenceIfEligible(
      17, start_ticks, end_ticks, ctx, 0x10, 0x20, 0x3, 0x4,
      OSThreadState::IO_WAIT));
  TaskBlockEvent both = Profiler::lastRecordedTaskBlockEventForTest();
  EXPECT_EQ(0x3ULL, both._callTraceId);
  EXPECT_EQ(0x4ULL, both._correlationId);

  EXPECT_FALSE(recordTaskBlockWithStackReferenceIfEligible(
      17, start_ticks, end_ticks, ctx, 0x10, 0x20, 0, 0,
      OSThreadState::IO_WAIT));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_NO_STACK_REFERENCE));
}

TEST_F(TaskBlockRecorderTest, AsyncStackReferencePathQueuesObservedStateAndSkipsCounters) {
  Context ctx{};
  u64 start_ticks = TSC::ticks();
  u64 end_ticks = minEligibleEndTicks(start_ticks);
  Profiler::instance()->setTaskBlockAsyncActiveForTest(true);

  EXPECT_TRUE(recordTaskBlockAsyncWithStackReferenceIfEligible(
      17, start_ticks, end_ticks, ctx, 0x10, 0x20, 0x3, 0x4,
      OSThreadState::IO_WAIT));
  Profiler::instance()->drainTaskBlockQueueForTest(true);
  TaskBlockEvent event = Profiler::lastRecordedTaskBlockEventForTest();
  EXPECT_EQ(OSThreadState::IO_WAIT, event._observedBlockingState);
  EXPECT_EQ(0x3ULL, event._callTraceId);
  EXPECT_EQ(0x4ULL, event._correlationId);

  EXPECT_FALSE(recordTaskBlockAsyncWithStackReferenceIfEligible(
      17, start_ticks, start_ticks, ctx, 0x10, 0x20, 0x3, 0x4,
      OSThreadState::IO_WAIT));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));

  ctx.spanId = 1;
  EXPECT_FALSE(recordTaskBlockAsyncWithStackReferenceIfEligible(
      17, start_ticks, end_ticks, ctx, 0x10, 0x20, 0x3, 0x4,
      OSThreadState::IO_WAIT));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TRACE_CONTEXT));
}

TEST_F(TaskBlockRecorderTest, RecordFailureIncrementsRecordFailed) {
  Profiler::instance()->setRecordTaskBlockLiveOverrideForTest(recordFailure);
  Context ctx{};
  u64 start_ticks = TSC::ticks();
  u64 end_ticks = minEligibleEndTicks(start_ticks);

  EXPECT_FALSE(recordTaskBlockWithStackReferenceIfEligible(
      17, start_ticks, end_ticks, ctx, 0x10, 0x20, 0x3, 0,
      OSThreadState::IO_WAIT));

  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
}

TEST_F(TaskBlockRecorderTest, AsyncRecordDropsWhenDrainInactive) {
  TaskBlockEvent event = eventWithStack(1);

  EXPECT_FALSE(Profiler::instance()->recordTaskBlockAsync(17, &event));

  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_QUEUE_DROPPED));
  EXPECT_TRUE(Profiler::instance()->taskBlockQueueEmptyForTest());
}

TEST_F(TaskBlockRecorderTest, RotationGateRejectsNewTaskBlockActivity) {
  Profiler* profiler = Profiler::instance();
  profiler->beginTaskBlockRotationForTest();

  EXPECT_FALSE(profiler->tryEnterTaskBlockActivity());
  Context context{};
  EXPECT_FALSE(recordTaskBlockWithStackReferenceIfEligible(
      17, 1, minEligibleEndTicks(1), context, 1, 0, 1, 0,
      OSThreadState::SLEEPING));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));

  profiler->endTaskBlockRotationForTest();
  ASSERT_TRUE(profiler->tryEnterTaskBlockActivity());
  profiler->leaveTaskBlockActivity();
}

TEST_F(TaskBlockRecorderTest, AsyncQueueFullIncrementsDropCounter) {
  Profiler::instance()->setTaskBlockAsyncActiveForTest(true);
  TaskBlockEvent event = eventWithStack(1);
  int pushed = 0;
  while (Profiler::instance()->recordTaskBlockAsync(17, &event)) {
    pushed++;
  }

  EXPECT_GT(pushed, 0);
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_QUEUE_DROPPED));
  Profiler::instance()->discardTaskBlockQueueForTest();
}

TEST_F(TaskBlockRecorderTest, DrainDiscardsStaleGenerationEvents) {
  Profiler::instance()->setRecordTaskBlockLiveOverrideForTest(recordSuccess);
  Profiler::instance()->setTaskBlockGenerationForTest(10);
  Profiler::instance()->setTaskBlockAsyncActiveForTest(true);
  TaskBlockEvent stale = eventWithStack(1);
  ASSERT_TRUE(Profiler::instance()->recordTaskBlockAsync(17, &stale));
  Profiler::instance()->incrementTaskBlockGenerationForTest();

  Profiler::instance()->drainTaskBlockQueueForTest(true);

  EXPECT_EQ(0, Profiler::recordTaskBlockLiveCallsForTest());
  EXPECT_TRUE(Profiler::instance()->taskBlockQueueEmptyForTest());
}

TEST_F(TaskBlockRecorderTest, DrainRecordsCurrentGenerationAndDropsStaleOnStopLikeDrain) {
  Profiler::instance()->setRecordTaskBlockLiveOverrideForTest(recordSuccess);
  Profiler::instance()->setTaskBlockGenerationForTest(20);
  Profiler::instance()->setTaskBlockAsyncActiveForTest(true);
  TaskBlockEvent current = eventWithStack(1);
  ASSERT_TRUE(Profiler::instance()->recordTaskBlockAsync(17, &current));
  Profiler::instance()->incrementTaskBlockGenerationForTest();
  TaskBlockEvent stale = eventWithStack(2);
  ASSERT_TRUE(Profiler::instance()->recordTaskBlockAsync(18, &stale));
  Profiler::instance()->incrementTaskBlockGenerationForTest();

  Profiler::instance()->drainTaskBlockQueueForTest(true);

  EXPECT_EQ(0, Profiler::recordTaskBlockLiveCallsForTest());
  EXPECT_TRUE(Profiler::instance()->taskBlockQueueEmptyForTest());

  TaskBlockEvent next = eventWithStack(3);
  ASSERT_TRUE(Profiler::instance()->recordTaskBlockAsync(19, &next));
  Profiler::instance()->drainTaskBlockQueueForTest(true);
  EXPECT_EQ(1, Profiler::recordTaskBlockLiveCallsForTest());
  EXPECT_EQ(19, Profiler::lastRecordedTaskBlockTidForTest());
}

TEST_F(TaskBlockRecorderTest, StartStopTaskBlockDrainIsIdempotent) {
  Profiler* profiler = Profiler::instance();
  profiler->setWallPrecheckForTest(false);
  profiler->setTaskBlockAsyncActiveForTest(false);
  u64 initial_generation = profiler->taskBlockGenerationForTest();

  profiler->startTaskBlockDrainForTest();
  profiler->startTaskBlockDrainForTest();
  EXPECT_FALSE(profiler->taskBlockAsyncActive());
  EXPECT_EQ(initial_generation, profiler->taskBlockGenerationForTest());

  profiler->stopTaskBlockDrainForTest();
  profiler->stopTaskBlockDrainForTest();
  EXPECT_FALSE(profiler->taskBlockAsyncActive());
}

TEST_F(TaskBlockRecorderTest, ConcurrentProducersAndDrainRecordEachCurrentEventOnce) {
  Profiler* profiler = Profiler::instance();
  profiler->setRecordTaskBlockLiveOverrideForTest(recordSuccess);
  profiler->setTaskBlockGenerationForTest(30);
  profiler->setTaskBlockAsyncActiveForTest(true);

  constexpr int producers = 4;
  constexpr int events_per_producer = 50;
  std::atomic<int> accepted{0};
  std::vector<std::thread> threads;
  for (int p = 0; p < producers; p++) {
    threads.emplace_back([&, p]() {
      for (int i = 0; i < events_per_producer; i++) {
        TaskBlockEvent event = eventWithStack(static_cast<u64>(p * events_per_producer + i + 1));
        if (profiler->recordTaskBlockAsync(1000 + p, &event)) {
          accepted.fetch_add(1, std::memory_order_relaxed);
        }
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }
  profiler->drainTaskBlockQueueForTest(true);

  EXPECT_EQ(accepted.load(std::memory_order_relaxed),
            Profiler::recordTaskBlockLiveCallsForTest());
  EXPECT_TRUE(profiler->taskBlockQueueEmptyForTest());
}

TEST_F(TaskBlockRecorderTest, ConcurrentStopLikeDisableDropsLaterProducerEvents) {
  Profiler* profiler = Profiler::instance();
  profiler->setRecordTaskBlockLiveOverrideForTest(recordSuccess);
  profiler->setTaskBlockGenerationForTest(40);
  profiler->setTaskBlockAsyncActiveForTest(true);
  std::atomic<bool> stop{false};
  std::atomic<int> accepted{0};
  std::atomic<int> rejected{0};

  std::thread producer([&]() {
    int id = 1;
    while (!stop.load(std::memory_order_acquire)) {
      TaskBlockEvent event = eventWithStack(static_cast<u64>(id++));
      if (profiler->recordTaskBlockAsync(17, &event)) {
        accepted.fetch_add(1, std::memory_order_relaxed);
      } else {
        rejected.fetch_add(1, std::memory_order_relaxed);
      }
      std::this_thread::yield();
    }
  });

  while (accepted.load(std::memory_order_acquire) == 0) {
    std::this_thread::yield();
  }
  profiler->setTaskBlockAsyncActiveForTest(false);
  profiler->drainTaskBlockQueueForTest(true);
  TaskBlockEvent rejected_event = eventWithStack(9999);
  EXPECT_FALSE(profiler->recordTaskBlockAsync(18, &rejected_event));
  stop.store(true, std::memory_order_release);
  producer.join();

  EXPECT_GT(accepted.load(std::memory_order_relaxed), 0);
  EXPECT_GT(Counters::getCounter(TASK_BLOCK_QUEUE_DROPPED), 0);
  EXPECT_TRUE(profiler->taskBlockQueueEmptyForTest());
}
