/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Churns registry ownership, context windows, and block runs during restarts.
 * ASan/TSan detect invalid memory access and races under concurrent lifecycle hooks.
 */
#include "gtest/gtest.h"

#ifdef __linux__

#include "threadFilter.h"
#include "wallClockBlockTracker.h"
#include "threadLocalData.inline.h"
#include "../../main/cpp/gtest_crash_handler.h"

#include <atomic>
#include <thread>
#include <vector>

static constexpr const char BLOCK_TRACKER_STRESS_TEST_NAME[] = "StressWallClockBlockTracker";

static constexpr int kChurnWorkers = 16;
static constexpr int kChurnIterations = 4000;

static std::atomic<bool> g_run{false};

static void block_run_churn_worker(ThreadFilter* filter, WallClockBlockTracker* tracker) {
  while (!g_run.load(std::memory_order_acquire)) { }
  for (int i = 0; i < kChurnIterations && g_run.load(std::memory_order_relaxed); i++) {
    ProfiledThread::initCurrentThread();
    ProfiledThread* self = ProfiledThread::current();
    EXPECT_NE(nullptr, self);
    if (!self) return;

    ThreadFilter::SlotID slot = filter->registerThread(self->tid());
    if (slot >= 0) {
      self->setFilterSlotId(slot);
      filter->add(self->tid(), slot);

      OSThreadState state = (i & 1) ? OSThreadState::SLEEPING : OSThreadState::CONDVAR_WAIT;
      u64 token = tracker->enterBlockedRun(filter, slot, state);
      std::this_thread::yield();
      if (token != 0) {
        // Either exit path may lose the race against a concurrent registry
        // reset (which is expected and fine); neither may crash or corrupt.
        if (i & 1) {
          tracker->exitBlockedRun(slot, WallClockBlockTracker::tokenGeneration(token));
        } else {
          tracker->resetSlot(slot, OSThreadState::RUNNABLE);
        }
      }

      filter->remove(slot);
      filter->unregisterThread(slot);
    }
    self->setFilterSlotId(-1);
    ProfiledThread::release();
  }
}

// Periodically advances the unfiltered recording epoch while churn workers are
// mid-registration/mid-block-run. Each retained owner refreshes its block state
// when it registers against the new epoch.
static void registry_restart_thread(ThreadFilter* filter) {
  while (g_run.load(std::memory_order_relaxed)) {
    filter->init("", /*track_unfiltered_wall=*/true);
    std::this_thread::yield();
  }
}

TEST(StressWallClockBlockTracker, ChurnOnly) {
  installGtestCrashHandler<BLOCK_TRACKER_STRESS_TEST_NAME>();

  ThreadFilter filter;
  WallClockBlockTracker tracker;
  filter.setBlockTracker(&tracker);
  filter.init("", /*track_unfiltered_wall=*/true);

  g_run.store(true, std::memory_order_release);
  std::vector<std::thread> workers;
  for (int t = 0; t < kChurnWorkers; t++) {
    workers.emplace_back(block_run_churn_worker, &filter, &tracker);
  }
  for (auto& w : workers) {
    w.join();
  }
  g_run.store(false);

  restoreDefaultSignalHandlers();
  SUCCEED();
}

TEST(StressWallClockBlockTracker, ChurnDuringConcurrentRegistryRestart) {
  installGtestCrashHandler<BLOCK_TRACKER_STRESS_TEST_NAME>();

  ThreadFilter filter;
  WallClockBlockTracker tracker;
  filter.setBlockTracker(&tracker);
  filter.init("", /*track_unfiltered_wall=*/true);

  g_run.store(true, std::memory_order_release);
  std::thread restarter(registry_restart_thread, &filter);
  std::vector<std::thread> workers;
  for (int t = 0; t < kChurnWorkers; t++) {
    workers.emplace_back(block_run_churn_worker, &filter, &tracker);
  }
  for (auto& w : workers) {
    w.join();
  }
  g_run.store(false);
  restarter.join();

  restoreDefaultSignalHandlers();
  SUCCEED();
}

#endif // __linux__
