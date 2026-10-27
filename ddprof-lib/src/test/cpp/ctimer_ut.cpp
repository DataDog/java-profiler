/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#ifdef __linux__

#include "arguments.h"
#include "common.h"
#include "ctimer.h"
#include "nativeMem.h"
#include "os.h"
#include "profiler.h"

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <thread>

// The failure-path tests force calloc to fail with a negative count, which
// makes count * size overflow. The CI sanitizer jobs run gtest binaries
// without *SAN_OPTIONS, so allocator_may_return_null defaults to 0 and the
// sanitizer reports that overflow as a fatal error instead of returning NULL.
#if defined(ASAN_ENABLED) || defined(TSAN_ENABLED)
#define SKIP_IF_CALLOC_OVERFLOW_ABORTS()                                       \
  GTEST_SKIP() << "sanitizer allocators abort on calloc overflow"
#else
#define SKIP_IF_CALLOC_OVERFLOW_ABORTS()
#endif

class ProfilerTestAccessor {
public:
  static bool enginesReady(Profiler *p) {
    return p->_engines_ready.load(std::memory_order_acquire);
  }
  static int hookCallsInflight(Profiler *p) {
    return p->_hook_calls_inflight.load(std::memory_order_acquire);
  }
  static void closeThreadRegistration(Profiler *p) {
    p->closeThreadRegistration();
  }
  static bool threadTablesStable(Profiler *p) {
    return p->_thread_tables_stable.load(std::memory_order_acquire);
  }
  static void addHookCalls(Profiler *p, int delta) {
    p->_hook_calls_inflight.fetch_add(delta, std::memory_order_seq_cst);
  }
};

// Exposes CTimer's tid-indexed timer table without starting the engine, which
// would install a SIGPROF handler and arm a timer for every live thread.
class CTimerTestAccessor {
public:
  static bool resizeTimers(int max_timers) { return CTimer::resizeTimers(max_timers); }
  static int maxTimers() { return CTimer::_max_timers; }
  static int *timers() { return CTimer::_timers; }
  static Error startWithTableSize(CTimer &engine, Arguments &args,
                                  int max_timers) {
    return engine.startWithTableSize(args, max_timers);
  }

  // Hands the current table to the caller without freeing it, so a test can
  // run against an empty table and later reinstate the original one.
  static void detach() {
    CTimer::_timers = nullptr;
    CTimer::_max_timers = 0;
  }

  // Frees the test-owned table and reinstates the detached one, without
  // touching the gauge (the fixture restores that separately).
  static void reattach(int max_timers, int *timers) {
    free(CTimer::_timers);
    CTimer::_timers = timers;
    CTimer::_max_timers = max_timers;
  }
};

// Size of a timer table with n slots, as recorded under NM_CTIMER.
static long long bytes(int n) { return (long long)((size_t)n * sizeof(int)); }

class CTimerNativeMemTest : public ::testing::Test {
protected:
  int _saved_max;
  int *_saved_timers;
  long long _saved_live;

  void SetUp() override {
    _saved_max = CTimerTestAccessor::maxTimers();
    _saved_timers = CTimerTestAccessor::timers();
    _saved_live = NativeMem::live(NM_CTIMER);
    // Detach the existing table so resizeTimers() neither frees it nor
    // subtracts its size; the gauge starts from zero for this test.
    CTimerTestAccessor::detach();
    NativeMem::setLive(NM_CTIMER, 0);
  }

  void TearDown() override {
    CTimerTestAccessor::reattach(_saved_max, _saved_timers);
    NativeMem::setLive(NM_CTIMER, _saved_live);
  }
};

// The timer table is reported under NM_CTIMER, and a resize replaces the old
// size rather than adding to it.
TEST_F(CTimerNativeMemTest, TimerTableIsAccounted) {
  CTimerTestAccessor::resizeTimers(1024);
  ASSERT_NE(nullptr, CTimerTestAccessor::timers());
  EXPECT_EQ(bytes(1024), NativeMem::live(NM_CTIMER));

  CTimerTestAccessor::resizeTimers(4096);
  ASSERT_NE(nullptr, CTimerTestAccessor::timers());
  EXPECT_EQ(bytes(4096), NativeMem::live(NM_CTIMER));

  CTimerTestAccessor::resizeTimers(512);
  EXPECT_EQ(bytes(512), NativeMem::live(NM_CTIMER));
}

// Restarting with an unchanged pid_max keeps the table and the gauge as-is.
// The sentinel shows the table was not reallocated: a free + calloc of the
// same size can return the same block, but calloc zeroes it.
TEST_F(CTimerNativeMemTest, SameSizeDoesNotReaccount) {
  ASSERT_TRUE(CTimerTestAccessor::resizeTimers(2048));
  int *table = CTimerTestAccessor::timers();
  table[2047] = 0x5a5a5a5a;

  ASSERT_TRUE(CTimerTestAccessor::resizeTimers(2048));
  EXPECT_EQ(table, CTimerTestAccessor::timers());
  EXPECT_EQ(0x5a5a5a5a, CTimerTestAccessor::timers()[2047]);
  EXPECT_EQ(bytes(2048), NativeMem::live(NM_CTIMER));
}

// A failed allocation leaves an empty table rather than a NULL table with a
// non-zero bound, releases the old table's bytes from the gauge, and a later
// resize to a valid size succeeds.
TEST_F(CTimerNativeMemTest, FailedAllocationLeavesEmptyTable) {
  SKIP_IF_CALLOC_OVERFLOW_ABORTS();
  ASSERT_TRUE(CTimerTestAccessor::resizeTimers(1024));

  EXPECT_FALSE(CTimerTestAccessor::resizeTimers(-1));
  EXPECT_EQ(nullptr, CTimerTestAccessor::timers());
  EXPECT_EQ(0, CTimerTestAccessor::maxTimers());
  EXPECT_EQ(0, NativeMem::live(NM_CTIMER));

  ASSERT_TRUE(CTimerTestAccessor::resizeTimers(1024));
  EXPECT_NE(nullptr, CTimerTestAccessor::timers());
  EXPECT_EQ(1024, CTimerTestAccessor::maxTimers());
  EXPECT_EQ(bytes(1024), NativeMem::live(NM_CTIMER));
}

// start() opens the native-thread registration gate once the table is sized,
// so a thread that starts or exits while start() registers the existing
// threads is handled by the pthread hook instead of being missed. The engine
// is stopped and the gate closed again before the fixture restores the table.
TEST_F(CTimerNativeMemTest, StartOpensThreadRegistration) {
  Profiler *profiler = Profiler::instance();
  ASSERT_FALSE(ProfilerTestAccessor::enginesReady(profiler));
  CTimer engine;
  Arguments args;

  Error error = CTimerTestAccessor::startWithTableSize(engine, args,
                                                       OS::getMaxThreadId());
  bool opened = ProfilerTestAccessor::enginesReady(profiler);
  engine.stop();
  ProfilerTestAccessor::closeThreadRegistration(profiler);

  EXPECT_FALSE((bool)error);
  EXPECT_TRUE(opened);
}

// start() fails when the timer table cannot be allocated, and returns before
// it installs the SIGPROF handler or arms a timer for any thread.
TEST_F(CTimerNativeMemTest, StartFailsWhenTableAllocationFails) {
  SKIP_IF_CALLOC_OVERFLOW_ABORTS();
  CTimer engine;
  Arguments args;

  Error error = CTimerTestAccessor::startWithTableSize(engine, args, -1);
  EXPECT_TRUE((bool)error);
  EXPECT_FALSE(ProfilerTestAccessor::enginesReady(Profiler::instance()));
  EXPECT_STREQ("Failed to allocate CPU timer table", error.message());
  EXPECT_EQ(nullptr, CTimerTestAccessor::timers());
  EXPECT_EQ(0, CTimerTestAccessor::maxTimers());
  EXPECT_EQ(0, NativeMem::live(NM_CTIMER));
}

// Profiler::registerThread() is reached from the pthread hook without
// _state_lock. Until start() has sized the engines' per-thread structures
// (CTimer::resizeTimers()) and set the engines-ready flag, it must return
// without touching the engines. In this binary the profiler is never
// started, so its engine pointers are null and any engine call would crash.
// The call must also leave the in-flight count at zero, or stop() would wait
// on it forever.
//
// Unregistration has its own gate, which stays open while the profiler is
// idle: PerfEvents keeps per-thread fds across stop(), and only
// unregisterThread() closes the fd of a thread that exits after stop().
TEST(ProfilerEnginesGateTest, RegisterThreadSkipsEnginesUntilReady) {
  Profiler *profiler = Profiler::instance();
  ASSERT_FALSE(ProfilerTestAccessor::enginesReady(profiler));
  EXPECT_EQ(0, Profiler::registerThread(OS::threadId()));
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
  EXPECT_TRUE(ProfilerTestAccessor::threadTablesStable(profiler));
}

// stop() relies on closeThreadRegistration() not returning while a hook call
// that passed the gate may still be inside an engine.
TEST(ProfilerEnginesGateTest, CloseThreadRegistrationWaitsForHookCalls) {
  Profiler *profiler = Profiler::instance();
  profiler->openThreadRegistration();
  ProfilerTestAccessor::addHookCalls(profiler, 1);

  std::atomic<bool> closed{false};
  std::thread closer([&] {
    ProfilerTestAccessor::closeThreadRegistration(profiler);
    closed.store(true);
  });
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_FALSE(closed.load());
  EXPECT_FALSE(ProfilerTestAccessor::enginesReady(profiler));

  ProfilerTestAccessor::addHookCalls(profiler, -1);
  closer.join();
  EXPECT_TRUE(closed.load());
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
}

#endif // __linux__
