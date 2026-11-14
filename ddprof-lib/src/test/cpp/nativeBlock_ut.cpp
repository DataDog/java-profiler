/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#if defined(__linux__)

#include "context_api.h"
#include "counters.h"
#include "nativeBlock.h"
#include "profiler.h"
#include "threadLocalData.inline.h"
#include "tsc.h"

#include <atomic>
#include <chrono>
#include <cerrno>
#include <future>
#include <thread>

namespace {

std::atomic<int> g_record_calls{0};
int g_record_tid = -1;
jthread g_record_thread = reinterpret_cast<jthread>(1);
int g_record_start_depth = -1;
TaskBlockEvent g_record_event{};
std::atomic<std::promise<void>*> g_completion_published{nullptr};
std::atomic<std::shared_future<void>*> g_completion_resume{nullptr};
std::atomic<std::promise<void>*> g_rotation_closed{nullptr};

void pauseTaskBlockCompletionForTest(Profiler::TaskBlockActivityStage stage) {
  if (stage == Profiler::TaskBlockActivityStage::AFTER_CLOSURE) {
    auto* closed = g_rotation_closed.load(std::memory_order_acquire);
    if (closed != nullptr) closed->set_value();
    return;
  }
  if (stage != Profiler::TaskBlockActivityStage::AFTER_EXIT) return;
  g_completion_published.load(std::memory_order_acquire)->set_value();
  g_completion_resume.load(std::memory_order_acquire)->wait();
}

Profiler::TaskBlockRecordResult recordTaskBlockSuccessForTest(
    int tid, jthread thread, int start_depth, TaskBlockEvent* event) {
  g_record_tid = tid;
  g_record_thread = thread;
  g_record_start_depth = start_depth;
  g_record_event = *event;
  g_record_calls.fetch_add(1, std::memory_order_relaxed);
  return Profiler::TaskBlockRecordResult::RECORDED;
}

class ScopedTaskBlockEnabled {
public:
  explicit ScopedTaskBlockEnabled(bool enabled)
      : _saved(Profiler::instance()->setTaskBlockEnabledForTest(enabled)) {}
  ~ScopedTaskBlockEnabled() {
    Profiler::instance()->setTaskBlockEnabledForTest(_saved);
  }

private:
  bool _saved;
};

class CurrentThreadScope {
public:
  CurrentThreadScope() {
    ProfiledThread::initCurrentThread();
    _thread = ProfiledThread::current();
    _thread->clearContextForTest();
    _thread->setFilterSlotId(-1);
    _thread->setJavaThread(false);
  }
  ~CurrentThreadScope() {
    if (_thread != nullptr) {
      _thread->clearContextForTest();
    }
    ProfiledThread::release();
  }

  ProfiledThread* thread() const { return _thread; }

  void releaseOwnership() { _thread = nullptr; }

private:
  ProfiledThread* _thread;
};

class DetachedCurrentThread {
public:
  explicit DetachedCurrentThread(CurrentThreadScope& current)
      : _thread(ProfiledThread::clearCurrentThreadTLS()) {
    current.releaseOwnership();
  }
  ~DetachedCurrentThread() {
    if (_thread != nullptr) {
      ProfiledThread::deleteForTest(_thread);
    }
  }

private:
  ProfiledThread* _thread;
};

class NativeBlockScopeTest : public ::testing::Test {
protected:
  void SetUp() override {
    Counters::reset();
    Profiler::setTaskBlockRecordOverrideForTest(recordTaskBlockSuccessForTest);
    g_record_calls = 0;
    g_record_tid = -1;
    g_record_thread = reinterpret_cast<jthread>(1);
    g_record_start_depth = -1;
    g_record_event = {};
    Profiler::instance()->threadFilter()->init("", true);
    Profiler::instance()->threadFilter()->clearActive();
  }

  void TearDown() override {
    Profiler::setTaskBlockActivityHookForTest(nullptr);
    g_completion_published.store(nullptr, std::memory_order_release);
    g_completion_resume.store(nullptr, std::memory_order_release);
    g_rotation_closed.store(nullptr, std::memory_order_release);
    if (ProfiledThread::current() != nullptr) {
      ProfiledThread::release();
    }
    Profiler::setTaskBlockRecordOverrideForTest(nullptr);
    Profiler::instance()->setTaskBlockEnabledForTest(false);
    Profiler::instance()->threadFilter()->clearActive();
    Counters::reset();
  }

  int registerCurrentJavaThread(ProfiledThread* thread) {
    ThreadFilter* filter = Profiler::instance()->threadFilter();
    int slot_id = filter->registerThread(thread->tid());
    EXPECT_GE(slot_id, 0);
    thread->setJavaThread(true);
    thread->setFilterSlotId(slot_id);

    return slot_id;
  }
};

u64 eligibleEndTicks(u64 start_ticks) {
  return start_ticks + (TSC::frequency() / 1000) + 1;
}

} // namespace

TEST_F(NativeBlockScopeTest, DisabledTaskBlockGateLeavesScopeInactiveAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(false);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeBlockScopeTest, NullCurrentThreadGateLeavesScopeInactiveAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  DetachedCurrentThread detached(current);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeBlockScopeTest, NonJavaThreadGateLeavesScopeInactiveAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  current.thread()->setJavaThread(false);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeBlockScopeTest, JvmInternalThreadGateLeavesScopeInactiveAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  registerCurrentJavaThread(current.thread());
  current.thread()->setJvmInternalThread(true);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_JVM_INTERNAL_THREAD));
}

TEST_F(NativeBlockScopeTest, FirstNativeHookProjectsOwnerLazilyAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  current.thread()->setJavaThread(true);
  current.thread()->setFilterSlotId(-1);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_TRUE(scope.active());
  EXPECT_GE(current.thread()->filterSlotId(), 0);
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeBlockScopeTest, InactiveRegistryGateLeavesSlotUntouchedAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  ThreadFilter* filter = Profiler::instance()->threadFilter();
  filter->init(nullptr);
  ASSERT_FALSE(filter->registryActive());
  WallClockBlockTracker::BlockState* slot = Profiler::instance()->blockTracker()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  u64 generation = slot->blockGeneration();
  errno = E2BIG;
  {
    NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);
    EXPECT_FALSE(scope.active());
    EXPECT_EQ(E2BIG, errno);
  }
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(generation, slot->blockGeneration());
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_EQ(0, g_record_calls.load());
}

TEST_F(NativeBlockScopeTest, ClosedAdmissionLeavesSlotReusableAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  Profiler* profiler = Profiler::instance();
  WallClockBlockTracker::BlockState* slot = profiler->blockTracker()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  u64 generation = slot->blockGeneration();
  // Closed admission rejects native scopes before publishing a blocked run.
  profiler->beginTaskBlockRotationForTest();
  errno = E2BIG;
  {
    NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);
    EXPECT_FALSE(scope.active());
    EXPECT_EQ(E2BIG, errno);
    EXPECT_EQ(generation, slot->blockGeneration());
    EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  }
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(0ULL, profiler->taskBlockInflightForTest());
  EXPECT_EQ(0, g_record_calls.load());
  profiler->endTaskBlockRotationForTest();
  // Reopening admission must leave the next scope able to own the slot.
  NativeBlockScope next(NativeBlockKind::STREAM_SOCKET, 17);
  EXPECT_TRUE(next.active());
  next.finishForTest(eligibleEndTicks(next.startTicksForTest()));
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
}

TEST_F(NativeBlockScopeTest, AllThreadRegistryWorksWithoutLegacyContextFilter) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  ThreadFilter* filter = Profiler::instance()->threadFilter();
  filter->init(nullptr, true);
  int slot_id = filter->registerThread(current.thread()->tid());
  ASSERT_GE(slot_id, 0);
  current.thread()->setJavaThread(true);
  current.thread()->setFilterSlotId(slot_id);
  ASSERT_FALSE(filter->enabled());
  ASSERT_TRUE(filter->registryActive());

  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_TRUE(scope.active());
  scope.finishForTest(eligibleEndTicks(scope.startTicksForTest()));
  WallClockBlockTracker::BlockState* slot = Profiler::instance()->blockTracker()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
}

TEST_F(NativeBlockScopeTest, TraceContextGateLeavesScopeInactiveAndSlotUnowned) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  current.thread()->setContextForTest(0x1234, 0x5678);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_SKIPPED_TRACE_CONTEXT));
  WallClockBlockTracker::BlockState* slot = Profiler::instance()->blockTracker()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
}

TEST_F(NativeBlockScopeTest, EnterBlockedRunFailureLeavesExistingOwnerIntact) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  ThreadFilter* filter = Profiler::instance()->threadFilter();
  u64 token = Profiler::instance()->blockTracker()->enterBlockedRun(filter, slot_id, OSThreadState::CONDVAR_WAIT,
                                      BlockRunOwner::JVMTI);
  ASSERT_NE(0ULL, token);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
  WallClockBlockTracker::BlockState* slot = Profiler::instance()->blockTracker()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::JVMTI, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot->activeBlockState());
  EXPECT_TRUE(Profiler::instance()->blockTracker()->exitBlockedRun(slot_id, WallClockBlockTracker::tokenGeneration(token)));
}

TEST_F(NativeBlockScopeTest, ActiveScopeExitsSlotAndRecordsSynchronousIoWaitEvent) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17,
                         OSThreadState::IO_WAIT);
  ASSERT_TRUE(scope.active());
  WallClockBlockTracker::BlockState* active_slot = Profiler::instance()->blockTracker()->slotForId(slot_id);
  ASSERT_NE(nullptr, active_slot);
  EXPECT_EQ(E2BIG, errno);
  scope.finishForTest(eligibleEndTicks(scope.startTicksForTest()));

  WallClockBlockTracker::BlockState* slot = Profiler::instance()->blockTracker()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_EQ(1, g_record_calls.load(std::memory_order_relaxed));
  EXPECT_EQ(current.thread()->tid(), g_record_tid);
  EXPECT_EQ(nullptr, g_record_thread);
  EXPECT_EQ(0, g_record_start_depth);
  EXPECT_EQ(OSThreadState::IO_WAIT, g_record_event._observedBlockingState);
  EXPECT_EQ(NativeBlockScope::blocker(NativeBlockKind::STREAM_SOCKET, 17),
            g_record_event._blocker);
}

TEST_F(NativeBlockScopeTest, FinishAfterTaskBlockDisableExitsWithoutRecording) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());

  NativeBlockScope scope(NativeBlockKind::CONNECT, 19, OSThreadState::IO_WAIT);
  ASSERT_TRUE(scope.active());
  Profiler::instance()->setTaskBlockEnabledForTest(false);
  scope.finishForTest(eligibleEndTicks(scope.startTicksForTest()));

  EXPECT_EQ(0, g_record_calls.load(std::memory_order_relaxed));
  WallClockBlockTracker::BlockState* slot =
      Profiler::instance()->blockTracker()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
}

TEST_F(NativeBlockScopeTest, FinishAfterFilterDisableExitsWithoutRecording) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  ThreadFilter* filter = Profiler::instance()->threadFilter();

  {
    NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17,
                           OSThreadState::IO_WAIT);
    ASSERT_TRUE(scope.active());
    filter->init(nullptr);
  }

  WallClockBlockTracker::BlockState* slot = Profiler::instance()->blockTracker()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_EQ(0, g_record_calls.load(std::memory_order_relaxed));
}

TEST_F(NativeBlockScopeTest, RotationRejectsFinishWithoutBlockingOrStranding) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  ThreadFilter* filter = Profiler::instance()->threadFilter();
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17,
                         OSThreadState::IO_WAIT);
  ASSERT_TRUE(scope.active());

  Profiler* profiler = Profiler::instance();
  profiler->beginTaskBlockRotationForTest();
  scope.finishForTest(eligibleEndTicks(scope.startTicksForTest()));
  EXPECT_EQ(0, profiler->taskBlockInflightForTest());
  profiler->endTaskBlockRotationForTest();

  WallClockBlockTracker::BlockState* slot = Profiler::instance()->blockTracker()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_EQ(0, g_record_calls.load(std::memory_order_relaxed));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));
}

TEST_F(NativeBlockScopeTest, AdmittedExitRetainsFullIntervalAcrossRotation) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  Profiler* profiler = Profiler::instance();
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);
  ASSERT_TRUE(scope.active());
  auto* slot = profiler->blockTracker()->slotForId(slot_id);
  u64 generation = slot->blockGeneration();
  u64 start_ticks = scope.startTicksForTest();
  ASSERT_TRUE(profiler->beginTaskBlockRotationForTest());
  EXPECT_EQ(generation, slot->blockGeneration());
  EXPECT_EQ(BlockRunOwner::NATIVE, slot->activeBlockOwner());
  EXPECT_EQ(0, g_record_calls.load());
  profiler->endTaskBlockRotationForTest();

  scope.finishForTest(eligibleEndTicks(start_ticks));
  EXPECT_EQ(1, g_record_calls.load());
  EXPECT_EQ(start_ticks, g_record_event._start);
  EXPECT_EQ(eligibleEndTicks(start_ticks), g_record_event._end);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(0, profiler->taskBlockInflightForTest());
}

TEST_F(NativeBlockScopeTest, AdmittedExitHoldsReservationUntilFullIntervalIsRecorded) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  Profiler* profiler = Profiler::instance();
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);
  ASSERT_TRUE(scope.active());
  u64 start = scope.startTicksForTest();
  std::promise<void> completion_published;
  auto published = completion_published.get_future();
  std::promise<void> resume_finisher;
  auto resume = resume_finisher.get_future().share();
  g_completion_published.store(&completion_published, std::memory_order_release);
  g_completion_resume.store(&resume, std::memory_order_release);
  Profiler::setTaskBlockActivityHookForTest(pauseTaskBlockCompletionForTest);
  std::promise<void> rotation_closed;
  auto closed = rotation_closed.get_future();
  g_rotation_closed.store(&rotation_closed, std::memory_order_release);
  std::thread rotation([&]() {
    EXPECT_EQ(std::future_status::ready, published.wait_for(std::chrono::seconds(5)));
    auto drained = std::async(std::launch::async, [&]() {
      return profiler->beginTaskBlockRotationForTest();
    });
    EXPECT_EQ(std::future_status::ready, closed.wait_for(std::chrono::seconds(5)));
    EXPECT_TRUE(profiler->taskBlockRotationActiveForTest());
    EXPECT_EQ(1, profiler->taskBlockInflightForTest());
    EXPECT_EQ(std::future_status::timeout, drained.wait_for(std::chrono::seconds(0)));
    EXPECT_EQ(BlockRunOwner::NONE,
              profiler->blockTracker()->slotForId(slot_id)->activeBlockOwner());
    EXPECT_EQ(0, g_record_calls.load());
    resume_finisher.set_value();
    EXPECT_TRUE(drained.get());
    EXPECT_EQ(0, profiler->taskBlockInflightForTest());
    EXPECT_EQ(1, g_record_calls.load());
    profiler->endTaskBlockRotationForTest();
  });
  scope.finishForTest(eligibleEndTicks(start));
  rotation.join();
  Profiler::setTaskBlockActivityHookForTest(nullptr);
  EXPECT_EQ(start, g_record_event._start);
  EXPECT_EQ(eligibleEndTicks(start), g_record_event._end);
}

TEST_F(NativeBlockScopeTest, OldRecordingExitCannotConsumeRestartedNativeOwner) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  Profiler* profiler = Profiler::instance();
  NativeBlockScope old(NativeBlockKind::STREAM_SOCKET, 17);
  ASSERT_TRUE(old.active());
  u64 generation = profiler->blockTracker()->slotForId(slot_id)->blockGeneration();
  profiler->threadFilter()->deactivateRecording();
  profiler->threadFilter()->init("", true);
  NativeBlockScope next(NativeBlockKind::STREAM_SOCKET, 18);
  ASSERT_TRUE(next.active());
  auto* slot = profiler->blockTracker()->slotForId(current.thread()->filterSlotId());
  ASSERT_NE(generation, slot->blockGeneration());
  old.finishForTest(eligibleEndTicks(old.startTicksForTest()));
  EXPECT_EQ(BlockRunOwner::NATIVE, slot->activeBlockOwner());
  EXPECT_EQ(0, g_record_calls.load());
  next.finishForTest(eligibleEndTicks(next.startTicksForTest()));
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(1, g_record_calls.load());
  EXPECT_EQ(NativeBlockScope::blocker(NativeBlockKind::STREAM_SOCKET, 18),
            g_record_event._blocker);
}

TEST_F(NativeBlockScopeTest, ConcurrentScopeLifecyclePreservesSlotOwnership) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  ThreadFilter* filter = Profiler::instance()->threadFilter();
  std::atomic<bool> stop{false};
  std::atomic<int> failures{0};

  std::thread observer([&]() {
    while (!stop.load(std::memory_order_acquire)) {
      BlockRunSnapshot snapshot = Profiler::instance()->blockTracker()->slotForId(slot_id)->snapshotBlockRun(filter->slotForId(slot_id));
      BlockRunOwner owner = Profiler::instance()->blockTracker()->slotForId(slot_id)->activeBlockOwner();
      if ((snapshot.active_state != OSThreadState::UNKNOWN &&
           snapshot.active_state != OSThreadState::IO_WAIT) ||
          (owner != BlockRunOwner::NONE && owner != BlockRunOwner::NATIVE)) {
        failures.fetch_add(1, std::memory_order_relaxed);
      }
      std::this_thread::yield();
    }
  });

  for (int i = 0; i < 1000; i++) {
    {
      NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17,
                             OSThreadState::IO_WAIT);
      ASSERT_TRUE(scope.active());
    }
    WallClockBlockTracker::BlockState* slot = Profiler::instance()->blockTracker()->slotForId(slot_id);
    ASSERT_NE(nullptr, slot);
    ASSERT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
    ASSERT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  }

  stop.store(true, std::memory_order_release);
  observer.join();
  EXPECT_EQ(0, failures.load(std::memory_order_relaxed));
}

#endif // __linux__
