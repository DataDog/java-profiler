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

void pauseTaskBlockCompletionForTest(ThreadFilter::SlotID, u64) {
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
    Profiler::instance()->threadFilter()->init("enabled");
    Profiler::instance()->threadFilter()->clearActive();
  }

  void TearDown() override {
    Profiler::setTaskBlockCompletionObserverForTest(nullptr);
    g_completion_published.store(nullptr, std::memory_order_release);
    g_completion_resume.store(nullptr, std::memory_order_release);
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
    int slot_id = filter->registerThread();
    EXPECT_GE(slot_id, 0);
    thread->setJavaThread(true);
    thread->setFilterSlotId(slot_id);
    filter->add(thread->tid(), slot_id);
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

TEST_F(NativeBlockScopeTest, MissingSlotGateLeavesScopeInactiveAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  current.thread()->setJavaThread(true);
  current.thread()->setFilterSlotId(-1);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeBlockScopeTest, InactiveRegistryGateLeavesSlotUntouchedAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  ThreadFilter* filter = Profiler::instance()->threadFilter();
  filter->init(nullptr);
  ASSERT_FALSE(filter->registryActive());
  ThreadFilter::Slot* slot = filter->slotForId(slot_id);
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
  EXPECT_EQ(0ULL, Profiler::instance()->taskBlockRunGenerationForTest(slot_id));
  EXPECT_EQ(0, g_record_calls.load());
}

TEST_F(NativeBlockScopeTest, RegistrationFailureAfterEntryReleasesSlotAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  Profiler* profiler = Profiler::instance();
  ThreadFilter::Slot* slot = profiler->threadFilter()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  u64 generation = slot->blockGeneration();
  // Rotation rejects registerTaskBlockRun after enterBlockedRun has succeeded.
  profiler->beginTaskBlockRotationForTest();
  errno = E2BIG;
  {
    NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);
    EXPECT_FALSE(scope.active());
    EXPECT_EQ(E2BIG, errno);
    EXPECT_EQ(generation + 1, slot->blockGeneration());
    EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
    EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  }
  EXPECT_EQ(E2BIG, errno);
  EXPECT_EQ(0ULL, profiler->taskBlockRunGenerationForTest(slot_id));
  EXPECT_EQ(0ULL, profiler->taskBlockInflightForTest());
  EXPECT_EQ(0, g_record_calls.load());
  profiler->endTaskBlockRotationForTest();
  // A failed registration must not prevent the next scope from owning the slot.
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
  ThreadFilter::Slot* slot = filter->slotForId(slot_id);
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
  ThreadFilter::Slot* slot = Profiler::instance()->threadFilter()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
}

TEST_F(NativeBlockScopeTest, EnterBlockedRunFailureLeavesExistingOwnerIntact) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  ThreadFilter* filter = Profiler::instance()->threadFilter();
  u64 token = filter->enterBlockedRun(slot_id, OSThreadState::CONDVAR_WAIT,
                                      BlockRunOwner::JVMTI);
  ASSERT_NE(0ULL, token);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
  ThreadFilter::Slot* slot = filter->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::JVMTI, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot->activeBlockState());
  EXPECT_TRUE(filter->exitBlockedRun(slot_id, ThreadFilter::tokenGeneration(token)));
}

TEST_F(NativeBlockScopeTest, ActiveScopeExitsSlotAndRecordsSynchronousIoWaitEvent) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17,
                         OSThreadState::IO_WAIT);
  ASSERT_TRUE(scope.active());
  ThreadFilter::Slot* active_slot = Profiler::instance()->threadFilter()->slotForId(slot_id);
  ASSERT_NE(nullptr, active_slot);
  EXPECT_EQ(E2BIG, errno);
  scope.finishForTest(eligibleEndTicks(scope.startTicksForTest()));

  ThreadFilter::Slot* slot = Profiler::instance()->threadFilter()->slotForId(slot_id);
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
  ThreadFilter::Slot* slot =
      Profiler::instance()->threadFilter()->slotForId(slot_id);
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

  ThreadFilter::Slot* slot = filter->slotForId(slot_id);
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
  std::future<void> result = std::async(std::launch::async, [&]() {
    scope.finishForTest(eligibleEndTicks(scope.startTicksForTest()));
  });

  std::future_status status = result.wait_for(std::chrono::seconds(1));
  profiler->endTaskBlockRotationForTest();
  ASSERT_EQ(std::future_status::ready, status);
  result.get();

  ThreadFilter::Slot* slot = filter->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_EQ(0, g_record_calls.load(std::memory_order_relaxed));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_DROPPED_ROTATION));
}

TEST_F(NativeBlockScopeTest,
       AdmittedFinishKeepsCommittedBoundaryDuringReclamation) {
  CurrentThreadScope current;
  ScopedTaskBlockEnabled task_block_enabled(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  Profiler* profiler = Profiler::instance();
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17,
                         OSThreadState::IO_WAIT);
  ASSERT_TRUE(scope.active());
  u64 generation = profiler->taskBlockRunGenerationForTest(slot_id);
  u64 end_ticks = eligibleEndTicks(scope.startTicksForTest());
  profiler->beginTaskBlockRotationForTest();
  profiler->commitTaskBlockBoundaryForTest(end_ticks);
  profiler->endTaskBlockRotationForTest();

  std::promise<void> completion_published;
  std::future<void> published = completion_published.get_future();
  std::promise<void> resume_finisher;
  std::shared_future<void> resume = resume_finisher.get_future().share();
  g_completion_published.store(&completion_published, std::memory_order_release);
  g_completion_resume.store(&resume, std::memory_order_release);
  Profiler::setTaskBlockCompletionObserverForTest(pauseTaskBlockCompletionForTest);
  std::future<void> result = std::async(std::launch::async, [&]() {
    scope.finishForTest(end_ticks);
  });

  std::future_status status = published.wait_for(std::chrono::seconds(5));
  EXPECT_EQ(std::future_status::ready, status);
  if (status == std::future_status::ready) {
    EXPECT_EQ(1ULL, profiler->taskBlockInflightForTest());
    EXPECT_EQ(generation, profiler->taskBlockRunGenerationForTest(slot_id));
    EXPECT_EQ(end_ticks, profiler->taskBlockRunSegmentStartForTest(slot_id));
    profiler->flushCompletedTaskBlockRunsForTest();
    EXPECT_EQ(0ULL, profiler->taskBlockRunGenerationForTest(slot_id));
  }
  resume_finisher.set_value();
  result.get();
  EXPECT_EQ(0, g_record_calls.load(std::memory_order_acquire));
  EXPECT_EQ(0ULL, profiler->taskBlockInflightForTest());
  EXPECT_EQ(BlockRunOwner::NONE,
            profiler->threadFilter()->slotForId(slot_id)->activeBlockOwner());
  profiler->clearTaskBlockRun(slot_id, generation);
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
      BlockRunSnapshot snapshot = filter->slotForId(slot_id)->snapshotBlockRun();
      if (snapshot.active && snapshot.owner != BlockRunOwner::NATIVE) {
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
    ThreadFilter::Slot* slot = filter->slotForId(slot_id);
    ASSERT_NE(nullptr, slot);
    ASSERT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
    ASSERT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  }

  stop.store(true, std::memory_order_release);
  observer.join();
  EXPECT_EQ(0, failures.load(std::memory_order_relaxed));
}

#endif // __linux__
