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
#include "thread.h"
#include "tsc.h"

#include <atomic>
#include <cerrno>
#include <thread>

namespace {

class ScopedTaskBlockAsyncActive {
public:
  explicit ScopedTaskBlockAsyncActive(bool active)
      : _saved(Profiler::instance()->setTaskBlockAsyncActiveForTest(active)) {}
  ~ScopedTaskBlockAsyncActive() {
    Profiler::instance()->setTaskBlockAsyncActiveForTest(_saved);
  }

private:
  bool _saved;
};

class ScopedWallPrecheck {
public:
  explicit ScopedWallPrecheck(bool enabled) {
    Profiler::instance()->setWallPrecheckForTest(enabled);
  }
  ~ScopedWallPrecheck() {
    Profiler::instance()->setWallPrecheckForTest(false);
  }
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

private:
  ProfiledThread* _thread;
};

class DetachedCurrentThread {
public:
  DetachedCurrentThread() : _thread(ProfiledThread::clearCurrentThreadTLS()) {}
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
    Profiler::resetTaskBlockRecordObservableForTest();
    Profiler::instance()->setWallPrecheckForTest(false);
    Profiler::instance()->setTaskBlockAsyncActiveForTest(false);
    Profiler::instance()->discardTaskBlockQueueForTest();
    Profiler::instance()->threadFilter()->init("enabled");
    Profiler::instance()->threadFilter()->clearActive();
  }

  void TearDown() override {
    if (ProfiledThread::currentSignalSafe() != nullptr) {
      ProfiledThread::release();
    }
    Profiler::resetTaskBlockRecordObservableForTest();
    Profiler::instance()->setTaskBlockAsyncActiveForTest(false);
    Profiler::instance()->setWallPrecheckForTest(false);
    Profiler::instance()->discardTaskBlockQueueForTest();
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

bool recordTaskBlockSuccessForTest(int, TaskBlockEvent*) {
  return true;
}

u64 eligibleEndTicks(u64 start_ticks) {
  return start_ticks + (TSC::frequency() / 1000) + 1;
}

} // namespace

TEST_F(NativeBlockScopeTest, InactiveAsyncDrainGateLeavesScopeInactiveAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockAsyncActive async_active(false);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeBlockScopeTest, NullCurrentThreadGateLeavesScopeInactiveAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockAsyncActive async_active(true);
  DetachedCurrentThread detached;

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeBlockScopeTest, NonJavaThreadGateLeavesScopeInactiveAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockAsyncActive async_active(true);
  current.thread()->setJavaThread(false);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeBlockScopeTest, MissingSlotGateLeavesScopeInactiveAndPreservesErrno) {
  CurrentThreadScope current;
  ScopedTaskBlockAsyncActive async_active(true);
  current.thread()->setJavaThread(true);
  current.thread()->setFilterSlotId(-1);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
}

TEST_F(NativeBlockScopeTest, TraceContextGateLeavesScopeInactiveAndSlotUnowned) {
  CurrentThreadScope current;
  ScopedTaskBlockAsyncActive async_active(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  current.thread()->setContextForTest(0x1234, 0x5678);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17);

  EXPECT_FALSE(scope.active());
  EXPECT_EQ(E2BIG, errno);
  ThreadFilter::Slot* slot = Profiler::instance()->threadFilter()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
}

TEST_F(NativeBlockScopeTest, EnterBlockedRunFailureLeavesExistingOwnerIntact) {
  CurrentThreadScope current;
  ScopedTaskBlockAsyncActive async_active(true);
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

TEST_F(NativeBlockScopeTest, ActiveScopeDestructorExitsSlotAndRecordsSampledState) {
  CurrentThreadScope current;
  ScopedTaskBlockAsyncActive async_active(true);
  ScopedWallPrecheck wall_precheck(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  Profiler::instance()->setRecordTaskBlockLiveOverrideForTest(recordTaskBlockSuccessForTest);

  errno = E2BIG;
  NativeBlockScope scope(NativeBlockKind::STREAM_SOCKET, 17,
                         OSThreadState::IO_WAIT);
  ASSERT_TRUE(scope.active());
  ThreadFilter::Slot* active_slot = Profiler::instance()->threadFilter()->slotForId(slot_id);
  ASSERT_NE(nullptr, active_slot);
  active_slot->markSampledThisRun(OSThreadState::CONDVAR_WAIT, 0x111, 0);
  EXPECT_EQ(E2BIG, errno);
  scope.finishForTest(eligibleEndTicks(scope.startTicksForTest()));

  ThreadFilter::Slot* slot = Profiler::instance()->threadFilter()->slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(BlockRunOwner::NONE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  Profiler::instance()->drainTaskBlockQueueForTest(true);
  EXPECT_EQ(1, Profiler::recordTaskBlockLiveCallsForTest());
  TaskBlockEvent event = Profiler::lastRecordedTaskBlockEventForTest();
  EXPECT_EQ(0x111ULL, event._callTraceId);
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, event._observedBlockingState);
  EXPECT_EQ(NativeBlockScope::blocker(NativeBlockKind::STREAM_SOCKET, 17),
            event._blocker);
}

TEST_F(NativeBlockScopeTest, ActiveScopeUsesActiveStateWhenNoSampledStateExists) {
  CurrentThreadScope current;
  ScopedTaskBlockAsyncActive async_active(true);
  ScopedWallPrecheck wall_precheck(true);
  registerCurrentJavaThread(current.thread());
  Profiler::instance()->setRecordTaskBlockLiveOverrideForTest(recordTaskBlockSuccessForTest);

  NativeBlockScope scope(NativeBlockKind::CONNECT, 19, OSThreadState::IO_WAIT);
  ASSERT_TRUE(scope.active());
  ThreadFilter::Slot* slot = Profiler::instance()->threadFilter()->slotForId(
      current.thread()->filterSlotId());
  ASSERT_NE(nullptr, slot);
  slot->markSampledThisRun(OSThreadState::UNKNOWN, 0x222, 0);
  scope.finishForTest(eligibleEndTicks(scope.startTicksForTest()));

  Profiler::instance()->drainTaskBlockQueueForTest(true);
  EXPECT_EQ(1, Profiler::recordTaskBlockLiveCallsForTest());
  TaskBlockEvent event = Profiler::lastRecordedTaskBlockEventForTest();
  EXPECT_EQ(0x222ULL, event._callTraceId);
  EXPECT_EQ(OSThreadState::IO_WAIT, event._observedBlockingState);
}

TEST_F(NativeBlockScopeTest, FinishSkipsAndLeavesSlotOwnedWhenFilterDisabledBeforeExit) {
  CurrentThreadScope current;
  ScopedTaskBlockAsyncActive async_active(true);
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
  EXPECT_EQ(BlockRunOwner::NATIVE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::IO_WAIT, slot->activeBlockState());
}

TEST_F(NativeBlockScopeTest, ConcurrentScopeLifecyclePreservesSlotOwnership) {
  CurrentThreadScope current;
  ScopedTaskBlockAsyncActive async_active(true);
  int slot_id = registerCurrentJavaThread(current.thread());
  ThreadFilter* filter = Profiler::instance()->threadFilter();
  std::atomic<bool> stop{false};
  std::atomic<int> failures{0};

  std::thread observer([&]() {
    while (!stop.load(std::memory_order_acquire)) {
      BlockRunSnapshot snapshot = filter->snapshotBlockedRun(slot_id);
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
      ThreadFilter::Slot* slot = filter->slotForId(slot_id);
      ASSERT_NE(nullptr, slot);
      slot->markSampledThisRun(OSThreadState::IO_WAIT, static_cast<u64>(i + 1), 0);
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
