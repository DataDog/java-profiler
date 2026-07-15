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
#include "threadLocalData.h"
#include "tsc.h"

#include <atomic>
#include <cerrno>
#include <thread>

namespace {

std::atomic<int> g_record_calls{0};
int g_record_tid = -1;
jthread g_record_thread = reinterpret_cast<jthread>(1);
int g_record_start_depth = -1;
TaskBlockEvent g_record_event{};

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
    if (ProfiledThread::currentSignalSafe() != nullptr) {
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

TEST_F(NativeBlockScopeTest, FinishSkipsAndLeavesSlotOwnedWhenFilterDisabledBeforeExit) {
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
  EXPECT_EQ(BlockRunOwner::NATIVE, slot->activeBlockOwner());
  EXPECT_EQ(OSThreadState::IO_WAIT, slot->activeBlockState());
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
