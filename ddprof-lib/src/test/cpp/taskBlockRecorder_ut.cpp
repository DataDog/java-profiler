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
#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <thread>

class ProfilerTestAccessor {
public:
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
  static int stripe(int tid) { return Profiler::instance()->getLockIndex(tid); }
  static SpinLock& lock(int stripe) { return Profiler::instance()->_locks[stripe]; }
};

class FlightRecorderTestAccessor {
public:
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
    ProfilerTestAccessor::exchangeTaskBlockEnabled(previous_enabled);
    EXPECT_EQ(0, Profiler::instance()->taskBlockInflightForTest());
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
  EXPECT_TRUE(barrier.await(1));
  EXPECT_TRUE(profiler->beginTaskBlockRotationForTest());
  barrier.resume(1);
  EXPECT_TRUE(barrier.await(2));
  EXPECT_TRUE(profiler->taskBlockRotationActiveForTest());
  EXPECT_EQ(0, profiler->taskBlockInflightForTest())
      << "a closed and drained recording cannot gain a transient reservation";
  barrier.resume(2);
  recorder.join();
  EXPECT_FALSE(entered);
  profiler->endTaskBlockRotationForTest();
  Profiler::setTaskBlockActivityHookForTest(nullptr);
  admission_barrier = nullptr;
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
  EXPECT_TRUE(barrier.await(1));
  std::atomic<bool> rotation_returned{false};
  bool drained = false;
  std::thread rotation([&] {
    drained = profiler->beginTaskBlockRotationForTest();
    rotation_returned.store(true, std::memory_order_release);
  });
  EXPECT_TRUE(barrier.await(2));
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
  ASSERT_TRUE(exceedsMinTaskBlockDuration(1, TSC::ticks()));
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
  std::unique_ptr<Recording> recording;
  Recording* previous_recording = nullptr;
  bool previous_omit = false;

  void SetUp() override {
    TaskBlockRecorderTest::SetUp();
    recording = std::make_unique<Recording>();
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
  int stripe = ProfilerTestAccessor::stripe(tid);
  FlightRecorder& recorder = ProfilerTestAccessor::recorder();
  TaskBlockEvent event{};
  event._start = 1;
  event._end = 2;
  int represented_tid = -1;
  for (int existing = 1000; existing < 1256; ++existing) {
    EXPECT_TRUE(recorder.recordTaskBlock(stripe, existing, &event));
    if (ProfilerTestAccessor::stripe(existing) == stripe) represented_tid = existing;
  }
  ASSERT_GE(represented_tid, 0);
  int before = recording->buffer(stripe)->offset();
  Context context{};
  u64 end = minEligibleEndTicks(1);
  EXPECT_FALSE(recordTaskBlockIfEligible(
      tid, nullptr, 0, 1, end, context, 0, 0, OSThreadState::SLEEPING));
  EXPECT_EQ(before, recording->buffer(stripe)->offset());
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(0, Counters::getCounter(TASK_BLOCK_EMITTED));
  EXPECT_EQ(0, Profiler::instance()->taskBlockInflightForTest());

  EXPECT_TRUE(recordTaskBlockIfEligible(
      represented_tid, nullptr, 0, 1, end, context, 0, 0, OSThreadState::SLEEPING));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_RECORD_FAILED));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_EMITTED));
  EXPECT_GT(recording->buffer(stripe)->offset(), before);
}
