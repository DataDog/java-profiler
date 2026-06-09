/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Layer-1 reproducer for the logs-backend crash (Java 25, thread-churn ×
 * recording-dump). Drives the profiler's own thread-lifecycle and dump data
 * structures concurrently, with NO JVM in the process, so ASan/TSan can flag
 * the use-after-free / race at its origin.
 *
 * See doc/plans/2026-05-29-logs-backend-crash-simulation-design.md
 */
#include "gtest/gtest.h"

#ifdef __linux__

#include "callTraceStorage.h"
#include "callTraceHashTable.h"
#include "threadFilter.h"
#include "thread.h"
#include "arch.h"
#include "spinLock.h"

#include <atomic>
#include <thread>
#include <vector>
#include <cstring>
#include <cstdint>
#include <unordered_set>
#include "../../main/cpp/gtest_crash_handler.h"

// Crash handler test name (installed in each multithreaded test below).
static constexpr const char STRESS_TEST_NAME[] = "StressThreadLifecycle";

// Number of churn workers and iterations per worker.
static constexpr int kChurnWorkers = 16;
static constexpr int kChurnIterations = 2000;

// Shared dump-side storage. Churn workers write it through the same shard-lock
// protocol as profiler sample paths; the dump thread processes it under
// lock_all(), matching Profiler::rotateDictsAndRun().
static CallTraceStorage g_storage;
static std::atomic<bool> g_run{false};

// Mirrors Profiler::_locks. Sample writers take one shard lock with tryLock();
// dump takes all shard locks before processing/clearing shared dump-side state.
static constexpr int kLockCount = 16;
static SpinLock g_locks[kLockCount];

static u32 lock_index_for_tid(int tid) {
  u32 lock_index = tid;
  lock_index ^= lock_index >> 8;
  lock_index ^= lock_index >> 4;
  return lock_index % kLockCount;
}

static bool try_record_lock(int tid, u32* lock_index) {
  *lock_index = lock_index_for_tid(tid);
  if (g_locks[*lock_index].tryLock()) {
    return true;
  }
  *lock_index = (*lock_index + 1) % kLockCount;
  if (g_locks[*lock_index].tryLock()) {
    return true;
  }
  *lock_index = (*lock_index + 1) % kLockCount;
  return g_locks[*lock_index].tryLock();
}

static void lock_all() {
  for (int i = 0; i < kLockCount; i++) {
    g_locks[i].lock();
  }
}

static void unlock_all() {
  for (int i = 0; i < kLockCount; i++) {
    g_locks[i].unlock();
  }
}

// Record a small fake call trace, mirroring profiler sample paths that hold a
// shard lock while writing to CallTraceStorage. ASGCT_CallFrame uses `bci`
// (jint) and the `method_id` union member (see vmEntry.h).
static void record_trace(int salt, int tid) {
  u32 lock_index;
  if (!try_record_lock(tid, &lock_index)) {
    return;
  }

  ASGCT_CallFrame frames[4];
  std::memset(frames, 0, sizeof(frames));
  for (int i = 0; i < 4; i++) {
    frames[i].bci = i + salt;
    frames[i].method_id =
        reinterpret_cast<jmethodID>(static_cast<intptr_t>(0x1000 + i + salt));
  }
  g_storage.put(4, frames, false, 1);

  g_locks[lock_index].unlock();
}

// onThreadStart -> work -> onThreadEnd loop, mirroring the profiler's per-thread
// lifecycle: initCurrentThread / current / register filter slot / setFilterSlotId
// / (work) / remove + unregister / release.
//
// Thread-name / ThreadInfo coverage: this native reproducer does not call
// ThreadInfo::set() or updateJavaThreadNames(). That path is covered by the
// JVM-level DumpStormAntagonist antagonist (Layer 2). A clean ASan/TSan run
// here is not conclusive for the thread-name path.
static void churn_worker(ThreadFilter* filter, bool with_dump) {
  while (!g_run.load(std::memory_order_acquire)) { }
  for (int i = 0; i < kChurnIterations && g_run.load(std::memory_order_relaxed); i++) {
    ProfiledThread::initCurrentThread();
    ProfiledThread* self = ProfiledThread::current();
    EXPECT_NE(nullptr, self);
    if (!self) return;

    ThreadFilter::SlotID slot = filter->registerThread();
    if (slot >= 0) {
      self->setFilterSlotId(slot);
      filter->add(self->tid(), slot);
    }

    if (with_dump) {
      record_trace(i, self->tid());
    }
    std::this_thread::yield();

    if (slot >= 0) {
      filter->remove(slot);
      filter->unregisterThread(slot);
    }
    self->setFilterSlotId(-1);
    ProfiledThread::release();
  }
}

// Continuously processes the trace storage under lock_all(), matching the JFR
// dump path where Profiler::rotateDictsAndRun() holds all shard locks while
// writeStackTraces() calls processCallTraces().
static void dump_thread() {
  while (g_run.load(std::memory_order_relaxed)) {
    lock_all();
    g_storage.processTraces([](const std::unordered_set<CallTrace*>& traces) {
      volatile size_t n = 0;
      for (CallTrace* t : traces) {
        if (t && t != CallTraceSample::PREPARING) {
          n += 1;
        }
      }
      (void)n;
    });
    unlock_all();
  }
}

TEST(StressThreadLifecycle, Smoke) {
  CallTraceStorage storage;
  storage.clear();
  SUCCEED();
}

TEST(StressThreadLifecycle, ChurnOnly) {
  installGtestCrashHandler<STRESS_TEST_NAME>();
  g_storage.clear();

  ThreadFilter filter;
  filter.init("*");
  ASSERT_TRUE(filter.enabled());

  g_run.store(true, std::memory_order_release);
  std::vector<std::thread> ts;
  for (int t = 0; t < kChurnWorkers; t++) {
    ts.emplace_back(churn_worker, &filter, false);
  }
  for (auto& t : ts) {
    t.join();
  }
  g_run.store(false);

  restoreDefaultSignalHandlers();
  SUCCEED();
}

TEST(StressThreadLifecycle, ChurnDuringDump) {
  installGtestCrashHandler<STRESS_TEST_NAME>();
  g_storage.clear();

  ThreadFilter filter;
  filter.init("*");
  ASSERT_TRUE(filter.enabled());

  g_run.store(true, std::memory_order_release);
  std::thread dumper(dump_thread);
  std::vector<std::thread> ts;
  for (int t = 0; t < kChurnWorkers; t++) {
    ts.emplace_back(churn_worker, &filter, true);
  }
  for (auto& t : ts) {
    t.join();
  }
  g_run.store(false);
  dumper.join();

  restoreDefaultSignalHandlers();
  SUCCEED();
}

#endif // __linux__
