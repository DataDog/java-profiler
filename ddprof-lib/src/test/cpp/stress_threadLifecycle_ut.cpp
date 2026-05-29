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
#include "dictionary.h"
#include "threadFilter.h"
#include "thread.h"
#include "arch.h"

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

// Shared dump-side structures. They are exercised concurrently by the dump
// thread and (for the put() path) by the churn workers.
static CallTraceStorage g_storage;
static Dictionary g_dict;
static std::atomic<bool> g_run{false};

// Record a small fake call trace plus a dictionary lookup, mirroring what the
// profiler does for every sample. ASGCT_CallFrame uses `bci` (jint) and the
// `method_id` union member (see vmEntry.h).
static void record_trace(int salt) {
  ASGCT_CallFrame frames[4];
  std::memset(frames, 0, sizeof(frames));
  for (int i = 0; i < 4; i++) {
    frames[i].bci = i + salt;
    frames[i].method_id =
        reinterpret_cast<jmethodID>(static_cast<intptr_t>(0x1000 + i + salt));
  }
  g_storage.put(4, frames, false, 1);
  g_dict.lookup("logs-backend-sim");
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
    ASSERT_NE(nullptr, self);

    ThreadFilter::SlotID slot = filter->registerThread();
    if (slot >= 0) {
      self->setFilterSlotId(slot);
      filter->add(self->tid(), slot);
    }

    if (with_dump) {
      record_trace(i);
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

// Continuously dumps the trace storage and clears both the dictionary and the
// storage, racing against concurrent put() / lookup() from churn workers.
//
// Intentional divergence from production: production wraps clear() in
// lockAll()/unlockAll() (profiler.cpp) so clear() never races put(). Here
// we drop that guard deliberately so ASan/TSan can observe a UAF at its
// origin. A crash in this reproducer may surface a real bug or a test-only
// race; cross-reference with the Layer-2 DumpStormAntagonist (JVM-level)
// to confirm which it is. The CallTraceStorage concurrency contract
// (refcount-guard + CriticalSection) prevents permanent corruption from
// clear()-vs-put() racing, so this does not cause silent data loss.
static void dump_thread() {
  while (g_run.load(std::memory_order_relaxed)) {
    g_storage.processTraces([](const std::unordered_set<CallTrace*>& traces) {
      volatile size_t n = 0;
      for (CallTrace* t : traces) {
        if (t && t != CallTraceSample::PREPARING) {
          n += 1;
        }
      }
      (void)n;
    });
    // dict.clear() races dict.lookup() on churn threads — intentional (see above).
    g_dict.clear();
    g_storage.clear();
  }
}

TEST(StressThreadLifecycle, Smoke) {
  CallTraceStorage storage;
  Dictionary dict;
  dict.lookup("smoke");
  storage.clear();
  SUCCEED();
}

TEST(StressThreadLifecycle, ChurnOnly) {
  installGtestCrashHandler<STRESS_TEST_NAME>();

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
