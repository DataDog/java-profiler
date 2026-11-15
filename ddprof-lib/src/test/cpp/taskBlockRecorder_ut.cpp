/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "counters.h"
#include "profiler.h"
#include "taskBlockRecorder.h"
#include "tsc.h"
#include "vmEntry.h"

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <future>
#include <memory>
#include <mutex>
#include <thread>

class ProfilerTestAccessor {
public:
  static bool omit(Profiler* p) { return p->_omit_stacktraces; }
  static void setOmit(Profiler* p, bool omit) { p->_omit_stacktraces = omit; }
  static int depth(Profiler* p) { return p->_max_stack_depth; }
  static void setDepth(Profiler* p, int depth) { p->_max_stack_depth = depth; }
  static int stripe(Profiler* p, int tid) { return p->getLockIndex(tid); }
  static CallTraceBuffer* exchangeBuffer(Profiler* p, int stripe, CallTraceBuffer* buffer) {
    CallTraceBuffer* previous = p->_calltrace_buffer[stripe];
    p->_calltrace_buffer[stripe] = buffer;
    return previous;
  }
  static SpinLock& lock(Profiler* p, int stripe) { return p->_locks[stripe]; }
  static FlightRecorder& recorder(Profiler* p) { return p->_jfr; }
  static bool exchangeTaskBlockEnabled(bool enabled) {
    return Profiler::instance()->_task_block_enabled.exchange(enabled, std::memory_order_acq_rel);
  }
  static bool exchangeOmitStacktraces(bool omit) {
    Profiler* profiler = Profiler::instance();
    bool previous = profiler->_omit_stacktraces;
    profiler->_omit_stacktraces = omit;
    return previous;
  }
  static FlightRecorder& recorder() { return Profiler::instance()->_jfr; }
  static SpinLock& lock(int stripe) { return Profiler::instance()->_locks[stripe]; }
};

class FlightRecorderTestAccessor {
public:
  static SpinLock& lock(FlightRecorder& recorder) { return recorder._rec_lock; }
  static void setRecording(FlightRecorder& recorder, Recording* recording) { recorder._rec = recording; }
  static Recording* exchangeRecording(FlightRecorder& recorder, Recording* recording) {
    Recording* previous = recorder._rec;
    recorder._rec = recording;
    return previous;
  }
};

namespace {

std::atomic<Profiler::TaskBlockRecordResult> g_record_result{
    Profiler::TaskBlockRecordResult::RECORDED};
std::atomic<int> g_record_calls{0};

Profiler::TaskBlockRecordResult recordTaskBlockForTest(
    int tid, jthread thread, int start_depth, TaskBlockEvent* event) {
  g_record_calls.fetch_add(1, std::memory_order_relaxed);
  return g_record_result.load(std::memory_order_acquire);
}

bool isEligibleDuration(u64 start_ticks, u64 end_ticks) {
  return checkTaskBlockDuration(start_ticks, end_ticks) ==
         TaskBlockDurationCheck::ELIGIBLE;
}

u64 minEligibleEndTicks(u64 start_ticks) {
  u64 low = start_ticks + 1;
  u64 high = low;
  while (!isEligibleDuration(start_ticks, high)) {
    high = start_ticks + ((high - start_ticks) * 2);
  }
  while (low < high) {
    u64 mid = low + ((high - low) / 2);
    if (isEligibleDuration(start_ticks, mid)) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return low;
}

class TaskBlockRecorderTest : public ::testing::Test {
protected:
  bool previous_enabled;

  void SetUp() override {
    previous_enabled = ProfilerTestAccessor::exchangeTaskBlockEnabled(false);
    Counters::reset();
    initializeTaskBlockDurationThreshold();
    g_record_result.store(Profiler::TaskBlockRecordResult::RECORDED,
                          std::memory_order_release);
    g_record_calls.store(0, std::memory_order_relaxed);
    Profiler::setTaskBlockRecordOverrideForTest(recordTaskBlockForTest);
  }

  void TearDown() override {
    Profiler::setTaskBlockActivityHookForTest(nullptr);
    Profiler::setTaskBlockRecordOverrideForTest(nullptr);
    setTaskBlockFrequencySourceForTest(nullptr);
    initializeTaskBlockDurationThreshold();
    ProfilerTestAccessor::exchangeTaskBlockEnabled(previous_enabled);
    EXPECT_EQ(0, Profiler::instance()->taskBlockInflightForTest());
    Counters::reset();
  }
};

u64 uncalibratedFrequency() { return 0; }

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
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_THRESHOLD_INVALID));
}

TEST_F(TaskBlockRecorderTest, UninitializedThresholdIsRecomputedFromTscFrequency) {
  resetTaskBlockDurationThresholdForTest();
  u64 expected_ticks = (TSC::frequency() * 1000000ULL) / NANOTIME_FREQ;
  ASSERT_GT(expected_ticks, 0ULL);
  u64 start_ticks = TSC::ticks();

  EXPECT_TRUE(isEligibleDuration(start_ticks, start_ticks + expected_ticks));
  EXPECT_FALSE(isEligibleDuration(start_ticks, start_ticks + expected_ticks - 1))
      << "the lazy fallback must enforce the 1 ms threshold, not accept every block";
}

TEST_F(TaskBlockRecorderTest, UncalibratedTscFailsClosed) {
  setTaskBlockFrequencySourceForTest(uncalibratedFrequency);
  initializeTaskBlockDurationThreshold();
  Context context{};
  u64 start_ticks = TSC::ticks();

  EXPECT_FALSE(isEligibleDuration(start_ticks, start_ticks + 1));
  EXPECT_FALSE(isEligibleDuration(start_ticks, start_ticks + NANOTIME_FREQ))
      << "an uncalibrated TSC must reject blocks of any length";
  EXPECT_EQ(TaskBlockDurationCheck::THRESHOLD_INVALID,
            checkTaskBlockDuration(start_ticks, start_ticks + NANOTIME_FREQ));
  EXPECT_FALSE(taskBlockPassesBasicEligibility(
      start_ticks, start_ticks + NANOTIME_FREQ, context));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_THRESHOLD_INVALID))
      << "an uncalibrated TSC must be visible as a disabled threshold";
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT))
      << "each rejection must be counted under exactly one counter";
}

TEST_F(TaskBlockRecorderTest, ShortContentionIsNotRecordedAndDoesNotSuppressNextEvent) {
  Context context{};
  u64 start_ticks = TSC::ticks();
  u64 one_millisecond = TSC::frequency() / 1000;
  ASSERT_GT(one_millisecond, 1ULL);
  u64 passing_end = start_ticks + one_millisecond;

  EXPECT_FALSE(recordTaskBlockIfEligible(
      12345, nullptr, 0, start_ticks, passing_end - 1, context, 0, 0,
      OSThreadState::MONITOR_WAIT));
  EXPECT_EQ(0, g_record_calls.load(std::memory_order_acquire));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TOO_SHORT));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_EMITTED));

  EXPECT_TRUE(recordTaskBlockIfEligible(
      12345, nullptr, 0, start_ticks, passing_end, context, 0, 0,
      OSThreadState::MONITOR_WAIT));
  EXPECT_EQ(1, g_record_calls.load(std::memory_order_acquire));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_EMITTED));
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

class AbandonedTaskBlockTest : public TaskBlockRecorderTest {
protected:
  static constexpr int kTid = 22201;
  ThreadFilter filter;
  WallClockBlockTracker tracker;
  ThreadFilter::SlotID slot_id = -1;
  std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current{
      nullptr, ProfiledThread::deleteForTest};

  void SetUp() override {
    TaskBlockRecorderTest::SetUp();
    filter.setBlockTracker(&tracker);
    filter.init("", true);
    slot_id = filter.registerThread(kTid);
    ASSERT_GE(slot_id, 0);
    current.reset(ProfiledThread::forTid(kTid));
    current->setFilterSlotId(slot_id);
  }

  // Arms a TASK_BLOCK run and its TLS interval, as beginTaskBlock0 does.
  u64 beginTaskBlock() {
    u64 token = tracker.enterBlockedRun(
        &filter, slot_id, OSThreadState::SLEEPING, BlockRunOwner::TASK_BLOCK);
    Context context{};
    if (token == 0 || !current->taskBlockEnter(token, TSC::ticks(), context)) {
      return 0;
    }
    return token;
  }

  BlockRunOwner owner() {
    return tracker.slotForId(slot_id)->activeBlockOwner();
  }
};

TEST_F(AbandonedTaskBlockTest, AbandonedIntervalIsClearedAndItsRunClosed) {
  u64 abandoned = beginTaskBlock();
  ASSERT_NE(0ULL, abandoned);
  ASSERT_EQ(0ULL, beginTaskBlock())
      << "precondition: a pending interval blocks the next begin";

  EXPECT_TRUE(recoverAbandonedTaskBlock(current.get(), &tracker, slot_id));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECOVERED_ABANDONED));
  EXPECT_EQ(BlockRunOwner::NONE, owner())
      << "the abandoned TASK_BLOCK run must stop suppressing wall-clock signals";
  u64 ignored_ticks = 0;
  Context ignored_context{};
  EXPECT_FALSE(current->taskBlockExit(abandoned, ignored_ticks, ignored_context))
      << "the abandoned token must no longer close an interval";

  u64 next = beginTaskBlock();
  EXPECT_NE(0ULL, next) << "recovery must let the thread arm a new interval";
  EXPECT_NE(abandoned, next);
  EXPECT_EQ(BlockRunOwner::TASK_BLOCK, owner());
}

TEST_F(AbandonedTaskBlockTest, NothingPendingIsNotCounted) {
  EXPECT_FALSE(recoverAbandonedTaskBlock(current.get(), &tracker, slot_id));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_RECOVERED_ABANDONED));
}

TEST_F(AbandonedTaskBlockTest, NonDecodableTokenIsDroppedWithoutClosingARun) {
  // decodeBlockRunToken() rejects a non-zero token whose generation is 0.
  // Its slot bits must be non-zero for the token itself to be non-zero, so
  // use a non-zero slot that holds a live TASK_BLOCK run.
  ThreadFilter::SlotID other_slot = filter.registerThread(kTid + 1);
  ASSERT_GE(other_slot, 0);
  ThreadFilter::SlotID target = slot_id != 0 ? slot_id : other_slot;
  u64 live = tracker.enterBlockedRun(
      &filter, target, OSThreadState::SLEEPING, BlockRunOwner::TASK_BLOCK);
  ASSERT_NE(0ULL, live);
  u64 corrupt = WallClockBlockTracker::encodeBlockRunToken(target, 0);
  ASSERT_NE(0ULL, corrupt);
  ThreadFilter::SlotID ignored_slot = -1;
  u64 ignored_generation = 0;
  ASSERT_FALSE(WallClockBlockTracker::decodeBlockRunToken(
      corrupt, ignored_slot, ignored_generation));
  Context context{};
  ASSERT_TRUE(current->taskBlockEnter(corrupt, TSC::ticks(), context));

  EXPECT_TRUE(recoverAbandonedTaskBlock(current.get(), &tracker, target));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECOVERED_ABANDONED));
  EXPECT_EQ(BlockRunOwner::TASK_BLOCK, tracker.slotForId(target)->activeBlockOwner())
      << "a non-decodable token must not close any run";
  u64 ignored_ticks = 0;
  Context ignored_context{};
  EXPECT_FALSE(current->taskBlockExit(corrupt, ignored_ticks, ignored_context))
      << "the non-decodable token must be dropped from TLS";
  EXPECT_TRUE(tracker.exitBlockedRun(
      target, WallClockBlockTracker::tokenGeneration(live)));
}

TEST_F(AbandonedTaskBlockTest, NewerRunOnSlotIsNotClosed) {
  u64 abandoned = beginTaskBlock();
  ASSERT_NE(0ULL, abandoned);
  // A registry reset clears the run but not the TLS token; a later run on
  // the same slot then gets a newer generation.
  tracker.resetSlot(slot_id);
  u64 newer = tracker.enterBlockedRun(
      &filter, slot_id, OSThreadState::SLEEPING, BlockRunOwner::JAVA);
  ASSERT_NE(0ULL, newer);

  EXPECT_TRUE(recoverAbandonedTaskBlock(current.get(), &tracker, slot_id));
  EXPECT_EQ(BlockRunOwner::JAVA, owner())
      << "the generation check must leave a newer run untouched";
  EXPECT_TRUE(tracker.exitBlockedRun(
      slot_id, WallClockBlockTracker::tokenGeneration(newer)));
}

TEST_F(AbandonedTaskBlockTest, RunOnAnotherSlotIsNotClosed) {
  u64 abandoned = beginTaskBlock();
  ASSERT_NE(0ULL, abandoned);
  ThreadFilter::SlotID other_slot = filter.registerThread(kTid + 1);
  ASSERT_GE(other_slot, 0);
  ASSERT_NE(slot_id, other_slot);

  // The thread now resolves to other_slot, so slot_id may belong to another
  // thread and must not be touched.
  EXPECT_TRUE(recoverAbandonedTaskBlock(current.get(), &tracker, other_slot));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECOVERED_ABANDONED));
  EXPECT_EQ(BlockRunOwner::TASK_BLOCK, owner());
  u64 ignored_ticks = 0;
  Context ignored_context{};
  EXPECT_FALSE(current->taskBlockExit(abandoned, ignored_ticks, ignored_context))
      << "the TLS interval is cleared even when its run is not closed";
  EXPECT_TRUE(tracker.exitBlockedRun(
      slot_id, WallClockBlockTracker::tokenGeneration(abandoned)));
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

TEST_F(TaskBlockRecorderTest, RotationTimesOutOnStuckInflightActivity) {
  Profiler* profiler = Profiler::instance();
  ASSERT_TRUE(profiler->tryEnterTaskBlockActivity()); // leaked on purpose: simulates a stuck recorder
  ASSERT_EQ(1, profiler->taskBlockInflightForTest());

  auto start = std::chrono::steady_clock::now();
  bool result = profiler->beginTaskBlockRotationForTest();
  auto elapsed = std::chrono::steady_clock::now() - start;

  EXPECT_FALSE(result);
  // Lower bound is deliberately looser than the 200ms timeout to avoid flakiness
  // from clock/scheduling jitter around the deadline boundary.
  EXPECT_GE(elapsed, std::chrono::milliseconds(150));
  EXPECT_LT(elapsed, std::chrono::milliseconds(2000)); // sanity bound, not a tight timing assertion
  EXPECT_FALSE(profiler->taskBlockRotationActiveForTest());
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_ROTATION_TIMEOUT));

  profiler->leaveTaskBlockActivity(); // clean up the leaked inflight count for later tests
  ASSERT_EQ(0, profiler->taskBlockInflightForTest());
}

TEST_F(TaskBlockRecorderTest, RotationRejectsEndWithoutStrandingLifecycle) {
  constexpr int tid = 12345;
  ThreadFilter filter;
  WallClockBlockTracker tracker;
  filter.setBlockTracker(&tracker);
  filter.init("", true);
  ThreadFilter::SlotID slot_id = filter.registerThread(tid);
  ASSERT_GE(slot_id, 0);

  std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current(
      ProfiledThread::forTid(tid), ProfiledThread::deleteForTest);
  current->setFilterSlotId(slot_id);
  u64 token = tracker.enterBlockedRun(
      &filter, slot_id, OSThreadState::SLEEPING, BlockRunOwner::JAVA);
  ASSERT_NE(0ULL, token);
  Context context{};
  ASSERT_TRUE(current->taskBlockEnter(token, TSC::ticks(), context));

  Profiler* profiler = Profiler::instance();
  profiler->beginTaskBlockRotationForTest();
  std::future<bool> result = std::async(std::launch::async, [&]() {
    return recordTaskBlockAtExit(
        current.get(), &filter, &tracker, nullptr, 1, token, 0, 0);
  });

  std::future_status status = result.wait_for(std::chrono::seconds(1));
  bool returned_during_rotation = status == std::future_status::ready;
  EXPECT_TRUE(returned_during_rotation);
  if (returned_during_rotation) {
    WallClockBlockTracker::BlockState* slot = tracker.slotForId(slot_id);
    EXPECT_NE(nullptr, slot);
    if (slot != nullptr) {
      EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
      EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
    }

    u64 next_token = tracker.enterBlockedRun(
        &filter, slot_id, OSThreadState::SLEEPING, BlockRunOwner::JAVA);
    EXPECT_NE(0ULL, next_token);
    EXPECT_TRUE(current->taskBlockEnter(next_token, TSC::ticks(), context));
    u64 ignored_ticks = 0;
    Context ignored_context{};
    EXPECT_TRUE(current->taskBlockExit(
        next_token, ignored_ticks, ignored_context));
    EXPECT_TRUE(tracker.exitBlockedRun(
        slot_id, WallClockBlockTracker::tokenGeneration(next_token)));
  }

  profiler->endTaskBlockRotationForTest();
  EXPECT_FALSE(result.get());
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));
}

TEST_F(TaskBlockRecorderTest, StaleCachedFilterSlotIsSelfHealedBeforeExit) {
  constexpr int tid1 = 22101;
  constexpr int tid2 = 22102;
  ThreadFilter filter;
  WallClockBlockTracker tracker;
  filter.setBlockTracker(&tracker);
  filter.init("", true);
  ThreadFilter::SlotID slot1 = filter.registerThread(tid1);
  ThreadFilter::SlotID slot2 = filter.registerThread(tid2);
  ASSERT_GE(slot1, 0);
  ASSERT_GE(slot2, 0);
  ASSERT_NE(slot1, slot2);

  std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current(
      ProfiledThread::forTid(tid1), ProfiledThread::deleteForTest);
  current->setFilterSlotId(slot1);

  u64 token = tracker.enterBlockedRun(
      &filter, slot1, OSThreadState::SLEEPING, BlockRunOwner::JAVA);
  ASSERT_NE(0ULL, token);

  // Simulate a TLS cache that drifted away from the slot that actually holds
  // this tid's live block run, e.g. another code path re-registered tid1's
  // central registry entry without updating this thread's own TLS cache.
  current->setFilterSlotId(slot2);

  Context context{};
  u64 start_ticks = TSC::ticks();
  finishTaskBlockAtExit(current.get(), &filter, &tracker, nullptr, 0, token,
                        start_ticks, context, 0, 0);

  EXPECT_EQ(slot1, current->filterSlotId())
      << "a stale cached slot must be self-healed back to the registry's "
         "actual slot for this tid before being compared against the token";
  WallClockBlockTracker::BlockState* slot = tracker.slotForId(slot1);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner())
      << "the live block run must still be cleared once the stale slot is "
         "healed, instead of being stranded by a spurious slot mismatch";
}

TEST_F(TaskBlockRecorderTest, RotationRejectsParkExitWithoutBlockingOrStranding) {
  constexpr int tid = 12346;
  ThreadFilter filter;
  WallClockBlockTracker tracker;
  filter.setBlockTracker(&tracker);
  filter.init("", true);
  ThreadFilter::SlotID slot_id = filter.registerThread(tid);
  ASSERT_GE(slot_id, 0);

  std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current(
      ProfiledThread::forTid(tid), ProfiledThread::deleteForTest);
  current->setFilterSlotId(slot_id);
  Context context{};
  ASSERT_TRUE(current->parkEnter(TSC::ticks(), context));
  u64 token = tracker.enterBlockedRun(
      &filter, slot_id, OSThreadState::CONDVAR_WAIT, BlockRunOwner::JAVA);
  ASSERT_NE(0ULL, token);
  current->setParkBlockToken(token);

  Profiler* profiler = Profiler::instance();
  profiler->beginTaskBlockRotationForTest();
  std::future<bool> result = std::async(std::launch::async, [&]() {
    u64 start_ticks = 0;
    u64 exit_token = 0;
    Context exit_context{};
    if (!current->parkExit(start_ticks, exit_context, exit_token)) return true;
    return finishTaskBlockAtExit(
        current.get(), &filter, &tracker, nullptr, 1, exit_token, start_ticks,
        exit_context, 0, 0);
  });

  EXPECT_EQ(std::future_status::ready,
            result.wait_for(std::chrono::seconds(1)));
  WallClockBlockTracker::BlockState* slot = tracker.slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_TRUE(current->parkEnter(TSC::ticks(), context));
  u64 ignored_ticks = 0;
  u64 ignored_token = 0;
  Context ignored_context{};
  EXPECT_TRUE(current->parkExit(
      ignored_ticks, ignored_context, ignored_token));

  profiler->endTaskBlockRotationForTest();
  EXPECT_FALSE(result.get());
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));
}

TEST_F(TaskBlockRecorderTest,
       RotationRejectsMonitorExitWithoutBlockingOrStranding) {
  constexpr int tid = 12347;
  ThreadFilter filter;
  WallClockBlockTracker tracker;
  filter.setBlockTracker(&tracker);
  filter.init("", true);
  ThreadFilter::SlotID slot_id = filter.registerThread(tid);
  ASSERT_GE(slot_id, 0);

  std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current(
      ProfiledThread::forTid(tid), ProfiledThread::deleteForTest);
  current->setFilterSlotId(slot_id);
  Context context{};
  ASSERT_TRUE(current->monitorEnter(
      TSC::ticks(), context, 7, OSThreadState::OBJECT_WAIT));
  u64 token = tracker.enterBlockedRun(
      &filter, slot_id, OSThreadState::OBJECT_WAIT, BlockRunOwner::JVMTI);
  ASSERT_NE(0ULL, token);
  current->setMonitorBlockToken(token);

  Profiler* profiler = Profiler::instance();
  profiler->beginTaskBlockRotationForTest();
  std::future<bool> result = std::async(std::launch::async, [&]() {
    u64 start_ticks = 0;
    u64 blocker = 0;
    u64 exit_token = 0;
    Context exit_context{};
    if (!current->monitorExit(OSThreadState::OBJECT_WAIT, start_ticks,
                              exit_context, blocker, exit_token)) {
      return true;
    }
    return finishTaskBlockAtExit(
        current.get(), &filter, &tracker, nullptr, 0, exit_token, start_ticks,
        exit_context, blocker, 0);
  });

  EXPECT_EQ(std::future_status::ready,
            result.wait_for(std::chrono::seconds(1)));
  WallClockBlockTracker::BlockState* slot = tracker.slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_TRUE(current->monitorEnter(
      TSC::ticks(), context, 8, OSThreadState::MONITOR_WAIT));
  current->clearMonitorBlock();

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

namespace {
struct AdmissionBarrier {
  std::mutex mutex;
  std::condition_variable changed;
  int reached = 0;
  int resumed = 0;

  void pause() {
    std::unique_lock<std::mutex> lock(mutex);
    int stage = ++reached;
    changed.notify_all();
    changed.wait(lock, [&] { return resumed >= stage; });
  }
  bool await(int stage) {
    std::unique_lock<std::mutex> lock(mutex);
    return changed.wait_for(lock, std::chrono::seconds(5), [&] { return reached >= stage; });
  }
  void resume(int stage) {
    std::lock_guard<std::mutex> lock(mutex);
    resumed = stage;
    changed.notify_all();
  }
};
AdmissionBarrier* admission_barrier = nullptr;
void pauseAdmission(Profiler::TaskBlockActivityStage stage) {
  if (stage == Profiler::TaskBlockActivityStage::BEFORE_RESERVATION ||
      stage == Profiler::TaskBlockActivityStage::AFTER_RESERVATION) admission_barrier->pause();
}
void pauseReservationAndClosure(Profiler::TaskBlockActivityStage stage) {
  if (stage == Profiler::TaskBlockActivityStage::AFTER_RESERVATION ||
      stage == Profiler::TaskBlockActivityStage::AFTER_CLOSURE) admission_barrier->pause();
}
void pauseExitAcrossRestart(Profiler::TaskBlockActivityStage stage) {
  if (stage == Profiler::TaskBlockActivityStage::BEFORE_RESERVATION ||
      stage == Profiler::TaskBlockActivityStage::AFTER_EXIT) admission_barrier->pause();
}
} // namespace

TEST_F(TaskBlockRecorderTest, ClosedAndDrainedRotationCannotGainAReservation) {
  Profiler* profiler = Profiler::instance();
  AdmissionBarrier barrier;
  admission_barrier = &barrier;
  Profiler::setTaskBlockActivityHookForTest(pauseAdmission);
  bool entered = true;
  std::thread recorder([&] {
    entered = profiler->tryEnterTaskBlockActivity();
    if (entered) profiler->leaveTaskBlockActivity();
  });
  bool before_reservation = barrier.await(1);
  EXPECT_TRUE(before_reservation);
  bool drained = profiler->beginTaskBlockRotationForTest();
  EXPECT_TRUE(drained);
  barrier.resume(1);
  bool after_reservation = barrier.await(2);
  EXPECT_TRUE(after_reservation);
  EXPECT_TRUE(profiler->taskBlockRotationActiveForTest());
  EXPECT_EQ(0, profiler->taskBlockInflightForTest())
      << "a drained, closed recording must not acquire even a transient reservation";
  barrier.resume(2);
  recorder.join();
  EXPECT_FALSE(entered);
  profiler->endTaskBlockRotationForTest();
  Profiler::setTaskBlockActivityHookForTest(nullptr);
  admission_barrier = nullptr;
}

// Access only configuration and locks; failure tests execute recordTaskBlock(),
// captureJVMTIFrames(), and FlightRecorder's real rejection paths.
class VMTestAccessor {
public:
  static jvmtiEnv* exchangeJvmti(jvmtiEnv* env) {
    jvmtiEnv* previous = VM::_jvmti;
    VM::_jvmti = env;
    return previous;
  }
};

class TaskBlockRealRecorderTest : public ::testing::Test {
protected:
  static constexpr int kTid = 123;
  Profiler* profiler = Profiler::instance();
  bool previous_omit;
  int previous_depth;
  CallTraceBuffer buffer{};
  CallTraceBuffer* previous_buffer;
  int stripe;

  void SetUp() override {
    Counters::reset();
    initializeTaskBlockDurationThreshold();
    Profiler::setTaskBlockRecordOverrideForTest(nullptr);
    previous_omit = ProfilerTestAccessor::omit(profiler);
    previous_depth = ProfilerTestAccessor::depth(profiler);
    stripe = ProfilerTestAccessor::stripe(profiler, kTid);
    previous_buffer = ProfilerTestAccessor::exchangeBuffer(profiler, stripe, &buffer);
    ProfilerTestAccessor::setDepth(profiler, 1);
    ProfilerTestAccessor::setOmit(profiler, false);
  }

  void TearDown() override {
    ProfilerTestAccessor::setOmit(profiler, previous_omit);
    ProfilerTestAccessor::setDepth(profiler, previous_depth);
    ProfilerTestAccessor::exchangeBuffer(profiler, stripe, previous_buffer);
    EXPECT_EQ(0, profiler->taskBlockInflightForTest());
    // Assert every stripe, including fallback stripes, is released by failure.
    for (int index = 0; index < CONCURRENCY_LEVEL; ++index) {
      bool acquired = ProfilerTestAccessor::lock(profiler, index).tryLock();
      EXPECT_TRUE(acquired) << "leaked stripe " << index;
      if (acquired) ProfilerTestAccessor::lock(profiler, index).unlock();
    }
    Counters::reset();
  }

  bool record() {
    Context context{};
    u64 start = TSC::ticks();
    return recordTaskBlockIfEligible(kTid, nullptr, 0, start, minEligibleEndTicks(start),
                                     context, 0, 0, OSThreadState::SLEEPING);
  }
};

TEST_F(TaskBlockRealRecorderTest, JvmtiStackFailureReleasesStripeAndCountsExactlyOnce) {
  jvmtiInterface_1_ functions{};
  functions.GetStackTrace = [](jvmtiEnv*, jthread, jint, jint, jvmtiFrameInfo*, jint*) -> jvmtiError {
    return JVMTI_ERROR_INTERNAL;
  };
  jvmtiEnv env{&functions};
  jvmtiEnv* previous = VMTestAccessor::exchangeJvmti(&env);
  EXPECT_FALSE(record());
  VMTestAccessor::exchangeJvmti(previous);
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_STACK_CAPTURE_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_EMITTED));
}

TEST_F(TaskBlockRealRecorderTest, MissingStackBufferReleasesStripeAndCountsExactlyOnce) {
  ProfilerTestAccessor::exchangeBuffer(profiler, stripe, nullptr);
  EXPECT_FALSE(record());
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_STACK_CAPTURE_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
}

TEST_F(TaskBlockRealRecorderTest, ContendedStripesFailWithoutCapturingStack) {
  for (int index = 0; index < CONCURRENCY_LEVEL; ++index) {
    ProfilerTestAccessor::lock(profiler, index).lock();
  }
  EXPECT_FALSE(record());
  for (int index = 0; index < CONCURRENCY_LEVEL; ++index) {
    ProfilerTestAccessor::lock(profiler, index).unlock();
  }
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_STACK_CAPTURE_FAILED));
}

TEST_F(TaskBlockRealRecorderTest, InactiveRecorderReleasesStripeAndCountsExactlyOnce) {
  ProfilerTestAccessor::setOmit(profiler, true);
  EXPECT_FALSE(record());
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_STACK_CAPTURE_FAILED));
}

TEST_F(TaskBlockRealRecorderTest, ContendedRecorderReleasesStripeAndCountsExactlyOnce) {
  ProfilerTestAccessor::setOmit(profiler, true);
  SpinLock& lock = FlightRecorderTestAccessor::lock(ProfilerTestAccessor::recorder(profiler));
  lock.lock();
  EXPECT_FALSE(record());
  lock.unlock();
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_STACK_CAPTURE_FAILED));
}

TEST_F(TaskBlockRealRecorderTest, ThreadTableOverflowIsCountedBeforeSerialization) {
  auto output = std::unique_ptr<FILE, int (*)(FILE*)>(tmpfile(), fclose);
  ASSERT_NE(nullptr, output);
  auto recording = std::make_unique<Recording>(fileno(output.get()));
  FlightRecorder& recorder = ProfilerTestAccessor::recorder(profiler);
  FlightRecorderTestAccessor::setRecording(recorder, recording.get());
  TaskBlockEvent event{};
  event._start = 1;
  event._end = 2;
  for (int tid = 1000; tid < 1256; ++tid) {
    EXPECT_TRUE(recorder.recordTaskBlock(stripe, tid, &event));
  }
  int before = recording->buffer(stripe)->offset();
  ProfilerTestAccessor::setOmit(profiler, true);
  EXPECT_FALSE(record()); // kTid is not one of the 256 represented IDs.
  EXPECT_EQ(before, recording->buffer(stripe)->offset());
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_EMITTED));
  FlightRecorderTestAccessor::setRecording(recorder, nullptr);
}

TEST_F(TaskBlockRecorderTest, ReservationBeforeClosureMustDrainBeforeRotationReturns) {
  Profiler* profiler = Profiler::instance();
  AdmissionBarrier barrier;
  admission_barrier = &barrier;
  Profiler::setTaskBlockActivityHookForTest(pauseReservationAndClosure);
  bool entered = false;
  std::thread recorder([&] {
    entered = profiler->tryEnterTaskBlockActivity();
    if (entered) profiler->leaveTaskBlockActivity();
  });
  EXPECT_TRUE(barrier.await(1)); // Reservation is held; recorder has not returned.
  std::atomic<bool> rotation_returned{false};
  bool drained = false;
  std::thread rotation([&] {
    drained = profiler->beginTaskBlockRotationForTest();
    rotation_returned.store(true, std::memory_order_release);
  });
  EXPECT_TRUE(barrier.await(2)); // Closure is published, before the drain check.
  EXPECT_TRUE(profiler->taskBlockRotationActiveForTest());
  EXPECT_EQ(1, profiler->taskBlockInflightForTest());
  EXPECT_FALSE(rotation_returned.load(std::memory_order_acquire));
  barrier.resume(1);
  recorder.join();
  EXPECT_TRUE(entered);
  EXPECT_EQ(0, profiler->taskBlockInflightForTest());
  barrier.resume(2);
  rotation.join();
  EXPECT_TRUE(drained);
  profiler->endTaskBlockRotationForTest();
  Profiler::setTaskBlockActivityHookForTest(nullptr);
  admission_barrier = nullptr;
}

TEST_F(TaskBlockRecorderTest, ExitPausedBeforeAdmissionCannotRecordIntoNextRecording) {
  constexpr int tid = 12345;
  ThreadFilter filter;
  WallClockBlockTracker tracker;
  filter.setBlockTracker(&tracker);
  filter.init("", true);
  ThreadFilter::SlotID slot_id = filter.registerThread(tid);
  ASSERT_GE(slot_id, 0);
  std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current(
      ProfiledThread::forTid(tid), ProfiledThread::deleteForTest);
  current->setFilterSlotId(slot_id);
  u64 token = tracker.enterBlockedRun(
      &filter, slot_id, OSThreadState::SLEEPING, BlockRunOwner::TASK_BLOCK);
  ASSERT_NE(0ULL, token);
  Context context{};
  ASSERT_TRUE(isEligibleDuration(1, TSC::ticks()));
  ASSERT_TRUE(current->taskBlockEnter(token, 1, context));

  Profiler* profiler = Profiler::instance();
  ProfilerTestAccessor::exchangeTaskBlockEnabled(true);
  AdmissionBarrier barrier;
  admission_barrier = &barrier;
  Profiler::setTaskBlockActivityHookForTest(pauseExitAcrossRestart);
  bool recorded = true;
  std::thread recorder([&] {
    recorded = recordTaskBlockAtExit(
        current.get(), &filter, &tracker, nullptr, 0, token, 0, 0);
  });
  EXPECT_TRUE(barrier.await(1));
  // Exercise stop's enabled/drain/registry sequence without a live JVM.
  ProfilerTestAccessor::exchangeTaskBlockEnabled(false);
  EXPECT_TRUE(profiler->beginTaskBlockRotationForTest());
  filter.deactivateRecording();
  profiler->endTaskBlockRotationForTest();
  EXPECT_EQ(0, filter.recordingEpoch());
  barrier.resume(1);
  EXPECT_TRUE(barrier.await(2));
  EXPECT_EQ(BlockRunOwner::NONE, tracker.slotForId(slot_id)->activeBlockOwner());
  filter.init("", true);
  ProfilerTestAccessor::exchangeTaskBlockEnabled(true);
  barrier.resume(2);
  recorder.join();
  Profiler::setTaskBlockActivityHookForTest(nullptr);
  admission_barrier = nullptr;

  EXPECT_FALSE(recorded);
  EXPECT_EQ(0, g_record_calls.load(std::memory_order_acquire));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_EMITTED));
  EXPECT_EQ(0, profiler->taskBlockInflightForTest());

  slot_id = filter.registerThread(tid);
  current->setFilterSlotId(slot_id);
  token = tracker.enterBlockedRun(
      &filter, slot_id, OSThreadState::SLEEPING, BlockRunOwner::TASK_BLOCK);
  ASSERT_NE(0ULL, token);
  ASSERT_TRUE(current->taskBlockEnter(token, 1, context));
  EXPECT_TRUE(recordTaskBlockAtExit(
      current.get(), &filter, &tracker, nullptr, 0, token, 0, 0));
  EXPECT_EQ(1, g_record_calls.load(std::memory_order_acquire));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_EMITTED));
}

class TaskBlockRecorderOverflowTest : public TaskBlockRecorderTest {
protected:
  std::unique_ptr<FILE, int (*)(FILE*)> output{nullptr, fclose};
  std::unique_ptr<Recording> recording;
  Recording* previous_recording = nullptr;
  bool previous_omit = false;

  void SetUp() override {
    TaskBlockRecorderTest::SetUp();
    output.reset(tmpfile());
    ASSERT_NE(nullptr, output);
    recording = std::make_unique<Recording>(fileno(output.get()));
    Profiler::setTaskBlockRecordOverrideForTest(nullptr);
    previous_omit = ProfilerTestAccessor::exchangeOmitStacktraces(true);
    previous_recording = FlightRecorderTestAccessor::exchangeRecording(
        ProfilerTestAccessor::recorder(), recording.get());
  }

  void TearDown() override {
    if (recording) {
      FlightRecorderTestAccessor::exchangeRecording(
          ProfilerTestAccessor::recorder(), previous_recording);
      ProfilerTestAccessor::exchangeOmitStacktraces(previous_omit);
      recording.reset();
    }
    for (int stripe = 0; stripe < CONCURRENCY_LEVEL; ++stripe) {
      bool acquired = ProfilerTestAccessor::lock(stripe).tryLock();
      EXPECT_TRUE(acquired) << "leaked stripe " << stripe;
      if (acquired) ProfilerTestAccessor::lock(stripe).unlock();
    }
    TaskBlockRecorderTest::TearDown();
  }
};

TEST_F(TaskBlockRecorderOverflowTest, ThreadTableOverflowIsCountedBeforeSerialization) {
  constexpr int tid = 123;
  constexpr int represented_tid = 1000;
  FlightRecorder& recorder = ProfilerTestAccessor::recorder();
  TaskBlockEvent event{};
  event._start = 1;
  event._end = 2;
  int before[CONCURRENCY_LEVEL];
  int total_before = 0;
  for (int stripe = 0; stripe < CONCURRENCY_LEVEL; ++stripe) {
    for (int existing = represented_tid; existing < represented_tid + 256; ++existing) {
      EXPECT_TRUE(recorder.recordTaskBlock(stripe, existing, &event));
    }
    before[stripe] = recording->buffer(stripe)->offset();
    total_before += before[stripe];
  }
  Context context{};
  u64 end = minEligibleEndTicks(1);
  EXPECT_FALSE(recordTaskBlockIfEligible(
      tid, nullptr, 0, 1, end, context, 0, 0, OSThreadState::SLEEPING));
  for (int stripe = 0; stripe < CONCURRENCY_LEVEL; ++stripe) {
    EXPECT_EQ(before[stripe], recording->buffer(stripe)->offset()) << "stripe " << stripe;
  }
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_EMITTED));
  EXPECT_EQ(0, Profiler::instance()->taskBlockInflightForTest());

  EXPECT_TRUE(recordTaskBlockIfEligible(
      represented_tid, nullptr, 0, 1, end, context, 0, 0, OSThreadState::SLEEPING));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_EMITTED));
  int total_after = 0;
  int changed_stripes = 0;
  for (int stripe = 0; stripe < CONCURRENCY_LEVEL; ++stripe) {
    int after = recording->buffer(stripe)->offset();
    total_after += after;
    if (after != before[stripe]) ++changed_stripes;
  }
  EXPECT_EQ(1, changed_stripes);
  EXPECT_GT(total_after, total_before);
}

TEST_F(TaskBlockRecorderTest, InactiveExitRejectsMissingOrForeignCachedIdentity) {
  for (bool missing_identity : {false, true}) {
    SCOPED_TRACE(missing_identity);
    ThreadFilter filter;
    WallClockBlockTracker tracker;
    filter.setBlockTracker(&tracker);
    filter.init("", true);
    const int slot_id = filter.registerThread(54321);
    ASSERT_GE(slot_id, 0);
    const u64 token = tracker.enterBlockedRun(
        &filter, slot_id, OSThreadState::SLEEPING, BlockRunOwner::TASK_BLOCK);
    ASSERT_NE(0ULL, token);
    std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current(
        ProfiledThread::forTid(12345), ProfiledThread::deleteForTest);
    current->setFilterSlotId(missing_identity ? -1 : slot_id);
    Context context{};
    ASSERT_TRUE(current->taskBlockEnter(token, 1, context));
    filter.deactivateRecording();
    EXPECT_FALSE(recordTaskBlockAtExit(
        current.get(), &filter, &tracker, nullptr, 0, token, 0, 0));
    EXPECT_EQ(BlockRunOwner::TASK_BLOCK, tracker.slotForId(slot_id)->activeBlockOwner());
    EXPECT_EQ(0, g_record_calls.load());
    EXPECT_EQ(nullptr, filter.lookupByTid(current->tid()));
  }
}
