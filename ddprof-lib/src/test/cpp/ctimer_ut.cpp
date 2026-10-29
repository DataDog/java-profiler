/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#ifdef __linux__

#include "arguments.h"
#include "common.h"
#include "ctimer.h"
#include "engine.h"
#include "nativeMem.h"
#include "os.h"
#include "profiler.h"

#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <pthread.h>
#include <sys/mman.h>
#include <thread>
#include <unistd.h>

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
  static bool closeThreadRegistration(Profiler *p) {
    return p->closeThreadRegistration();
  }
  static bool startCpuEngine(Profiler *p, Arguments &args) {
    return p->startCpuEngine(args);
  }
  static void enableCpuEngine(Profiler *p, int activated) {
    p->enableCpuEngine(activated);
  }
  // Runs body(drained) while a real ThreadTablesFreeze is alive.
  template <typename F> static void withThreadTablesFreeze(Profiler *p, F body) {
    Profiler::ThreadTablesFreeze freeze(p);
    body(freeze.drained());
  }

  // Sets the hook-call wait budget for its lifetime and restores the previous
  // one on destruction, including when a test assertion returns early.
  class DrainBudget {
  public:
    explicit DrainBudget(long long ns) : _saved(Profiler::_hook_drain_timeout_ns) {
      Profiler::_hook_drain_timeout_ns = ns;
    }
    ~DrainBudget() { Profiler::_hook_drain_timeout_ns = _saved; }
    DrainBudget(const DrainBudget &) = delete;
    DrainBudget &operator=(const DrainBudget &) = delete;

  private:
    long long _saved;
  };
  // Counts a hook call in flight for its lifetime, as if one were stuck inside
  // an engine, without needing a thread or an engine to hold it.
  class HookCallHold {
  public:
    explicit HookCallHold(Profiler *p) : _p(p) {
      p->_hook_calls_inflight.fetch_add(1, std::memory_order_seq_cst);
    }
    ~HookCallHold() {
      _p->_hook_calls_inflight.fetch_sub(1, std::memory_order_release);
    }
    HookCallHold(const HookCallHold &) = delete;
    HookCallHold &operator=(const HookCallHold &) = delete;

  private:
    Profiler *_p;
  };
  static bool threadTablesStable(Profiler *p) {
    return p->_thread_tables_stable.load(std::memory_order_acquire);
  }
  static void setThreadTablesStable(Profiler *p, bool stable) {
    p->_thread_tables_stable.store(stable, std::memory_order_seq_cst);
  }

  // Installs the given engines for its lifetime and puts the previous ones
  // back on destruction, including when a test assertion returns early.
  class EngineSwap {
  public:
    EngineSwap(Profiler *p, Engine *cpu, Engine *wall)
        : _p(p), _cpu(p->_cpu_engine), _wall(p->_wall_engine) {
      p->_cpu_engine = cpu;
      p->_wall_engine = wall;
    }
    ~EngineSwap() {
      _p->_cpu_engine = _cpu;
      _p->_wall_engine = _wall;
    }
    EngineSwap(const EngineSwap &) = delete;
    EngineSwap &operator=(const EngineSwap &) = delete;

  private:
    Profiler *_p;
    Engine *_cpu;
    Engine *_wall;
  };

  // Opens the registration gate for its lifetime and closes it on
  // destruction, including when a test assertion returns early. Declare it
  // after EngineSwap, so the gate closes before the engines are put back.
  class RegistrationGate {
  public:
    explicit RegistrationGate(Profiler *p) : _p(p) {
      p->openThreadRegistration();
    }
    ~RegistrationGate() { _p->closeThreadRegistration(); }
    RegistrationGate(const RegistrationGate &) = delete;
    RegistrationGate &operator=(const RegistrationGate &) = delete;

  private:
    Profiler *_p;
  };
};

// Polls cond until it holds or a 5 s deadline passes, so a gate regression
// fails the test instead of hanging the gtest binary.
template <typename Cond> static bool waitFor(Cond cond) {
  auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
  while (!cond()) {
    if (std::chrono::steady_clock::now() > deadline) {
      return false;
    }
    std::this_thread::yield();
  }
  return true;
}

// Exposes CTimer's tid-indexed timer table. The table accessors work without
// starting the engine; startWithTableSize() does start it (installs the
// SIGPROF handler and arms a timer for every live thread), and only
// StartOpensThreadRegistration uses it on a real table.
class CTimerTestAccessor {
public:
  static bool resizeTimers(int max_timers) { return CTimer::resizeTimers(max_timers); }
  static Error sizeTimerTable(int max_timers) {
    return CTimer::sizeTimerTable(max_timers);
  }
  static int maxTimers() { return CTimer::_max_timers; }
  static int *timers() { return CTimer::_timers; }
  static Error startWithTableSize(CTimer &engine, Arguments &args,
                                  int max_timers) {
    return engine.startWithTableSize(args, max_timers);
  }
  static int registerThread(CTimer &engine, int tid) {
    return engine.registerThread(tid);
  }
  static void unregisterThread(CTimer &engine, int tid) {
    engine.unregisterThread(tid);
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

  // Installs a caller-owned table for its lifetime and puts the previous one
  // back on destruction, without freeing either.
  class TimerTableSwap {
  public:
    TimerTableSwap(int *timers, int max_timers)
        : _timers(CTimer::_timers), _max_timers(CTimer::_max_timers) {
      CTimer::_timers = timers;
      CTimer::_max_timers = max_timers;
    }
    ~TimerTableSwap() {
      CTimer::_timers = _timers;
      CTimer::_max_timers = _max_timers;
    }
    TimerTableSwap(const TimerTableSwap &) = delete;
    TimerTableSwap &operator=(const TimerTableSwap &) = delete;

  private:
    int *_timers;
    int _max_timers;
  };
};

// Returns the current SIGPROF handler address (sa_handler and sa_sigaction
// share storage), to check whether a call installed a handler.
static void *sigprofHandler() {
  struct sigaction sa;
  sigaction(SIGPROF, nullptr, &sa);
  return (void *)sa.sa_sigaction;
}

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
// is stopped, the gate closed and the SIGPROF disposition restored before the
// fixture restores the table, so later tests see the process as it was.
TEST_F(CTimerNativeMemTest, StartOpensThreadRegistration) {
  Profiler *profiler = Profiler::instance();
  ASSERT_FALSE(ProfilerTestAccessor::enginesReady(profiler));
  struct sigaction saved_sigprof;
  sigaction(SIGPROF, nullptr, &saved_sigprof);
  CTimer engine;
  Arguments args;

  Error error = CTimerTestAccessor::startWithTableSize(engine, args,
                                                       OS::getMaxThreadId());
  bool opened = ProfilerTestAccessor::enginesReady(profiler);
  // Ignore SIGPROF before stopping, so a signal an armed timer already
  // generated is discarded instead of hitting a restored SIG_DFL.
  signal(SIGPROF, SIG_IGN);
  engine.stop();
  ProfilerTestAccessor::closeThreadRegistration(profiler);
  sigaction(SIGPROF, &saved_sigprof, nullptr);

  EXPECT_FALSE((bool)error);
  EXPECT_TRUE(opened);
}

// start() fails when the timer table cannot be allocated, and returns before
// it installs the SIGPROF handler or arms a timer for any thread.
TEST_F(CTimerNativeMemTest, StartFailsWhenTableAllocationFails) {
  SKIP_IF_CALLOC_OVERFLOW_ABORTS();
  CTimer engine;
  Arguments args;
  void *handler_before = sigprofHandler();

  Error error = CTimerTestAccessor::startWithTableSize(engine, args, -1);
  EXPECT_TRUE((bool)error);
  EXPECT_EQ(handler_before, sigprofHandler());
  EXPECT_FALSE(ProfilerTestAccessor::enginesReady(Profiler::instance()));
  EXPECT_STREQ("Failed to allocate CPU timer table", error.message());
  EXPECT_EQ(nullptr, CTimerTestAccessor::timers());
  EXPECT_EQ(0, CTimerTestAccessor::maxTimers());
  EXPECT_EQ(0, NativeMem::live(NM_CTIMER));
}

// A restart with an unchanged pid_max keeps the table without freezing thread
// unregistration, so a thread that exits during start() still releases its
// timer. A hook call is held in flight: a freeze would wait for it and time
// out, so success shows that none ran.
TEST_F(CTimerNativeMemTest, SameSizeRestartDoesNotFreezeUnregistration) {
  Profiler *profiler = Profiler::instance();
  ASSERT_TRUE(CTimerTestAccessor::resizeTimers(64));
  int *table = CTimerTestAccessor::timers();
  ProfilerTestAccessor::DrainBudget budget(100000000LL);

  Error error = Error::OK;
  {
    ProfilerTestAccessor::HookCallHold hold(profiler);
    error = CTimerTestAccessor::sizeTimerTable(64);
  }

  EXPECT_FALSE((bool)error);
  EXPECT_EQ(table, CTimerTestAccessor::timers());
  EXPECT_EQ(64, CTimerTestAccessor::maxTimers());
  EXPECT_TRUE(ProfilerTestAccessor::threadTablesStable(profiler));
}

// A size change replaces the table only under a freeze. While a hook call is
// still in flight after the wait budget, start() fails retryably and keeps the
// old table, and unregistration is open again afterwards.
TEST_F(CTimerNativeMemTest, ResizeKeepsTableWhenHookCallsDoNotDrain) {
  Profiler *profiler = Profiler::instance();
  ASSERT_TRUE(CTimerTestAccessor::resizeTimers(64));
  int *table = CTimerTestAccessor::timers();
  ProfilerTestAccessor::DrainBudget budget(100000000LL);

  Error error = Error::OK;
  {
    ProfilerTestAccessor::HookCallHold hold(profiler);
    error = CTimerTestAccessor::sizeTimerTable(128);
  }

  EXPECT_TRUE((bool)error);
  EXPECT_STREQ("thread hook calls did not drain; retry start()",
               error.message());
  EXPECT_EQ(table, CTimerTestAccessor::timers());
  EXPECT_EQ(64, CTimerTestAccessor::maxTimers());
  EXPECT_EQ(bytes(64), NativeMem::live(NM_CTIMER));
  EXPECT_TRUE(ProfilerTestAccessor::threadTablesStable(profiler));
  EXPECT_FALSE(ProfilerTestAccessor::enginesReady(profiler));
}

// With no hook call in flight, a size change replaces the table and reopens
// unregistration.
TEST_F(CTimerNativeMemTest, ResizeReplacesTableWhenHookCallsDrain) {
  Profiler *profiler = Profiler::instance();
  ASSERT_TRUE(CTimerTestAccessor::resizeTimers(64));

  Error error = CTimerTestAccessor::sizeTimerTable(128);

  EXPECT_FALSE((bool)error);
  EXPECT_NE(nullptr, CTimerTestAccessor::timers());
  EXPECT_EQ(128, CTimerTestAccessor::maxTimers());
  EXPECT_EQ(bytes(128), NativeMem::live(NM_CTIMER));
  EXPECT_TRUE(ProfilerTestAccessor::threadTablesStable(profiler));
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
  EXPECT_EQ(-1, Profiler::registerThread(OS::threadId()));
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
  EXPECT_TRUE(ProfilerTestAccessor::threadTablesStable(profiler));
}

// A CPU engine whose registerThread() blocks until released, to hold a real
// Profiler::registerThread() call inside the engine.
class BlockingEngine : public Engine {
public:
  std::atomic<bool> entered{false};
  std::atomic<bool> released{false};
  // Thread cancellation state seen inside the call (PTHREAD_CANCEL_*), or -1.
  std::atomic<int> cancel_state_inside{-1};

  int registerThread(int tid) override {
    int state;
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &state);
    pthread_setcancelstate(state, nullptr);
    cancel_state_inside.store(state);
    entered.store(true);
    waitFor([this] { return released.load(); });
    return 0;
  }
};

// stop() relies on closeThreadRegistration() not returning while a hook call
// that passed the gate is still inside an engine; otherwise CTimer::stop() or
// the next resizeTimers() could run under it.
TEST(ProfilerEnginesGateTest, CloseThreadRegistrationWaitsForHookCalls) {
  Profiler *profiler = Profiler::instance();
  BlockingEngine cpu;
  Engine wall;
  ProfilerTestAccessor::EngineSwap swap(profiler, &cpu, &wall);
  ProfilerTestAccessor::RegistrationGate gate(profiler);

  // Well above the 50 ms check below and below BlockingEngine's 5 s hold, so a
  // slow sanitizer host does not turn the wait into a false timeout.
  ProfilerTestAccessor::DrainBudget budget(4000000000LL);

  std::thread hook([] { Profiler::registerThread(OS::threadId()); });
  bool entered = waitFor([&] { return cpu.entered.load(); });
  std::atomic<bool> closed{false};
  std::atomic<bool> closed_ok{false};
  std::thread closer([&] {
    closed_ok.store(ProfilerTestAccessor::closeThreadRegistration(profiler));
    closed.store(true);
  });
  // Wait until the closer has cleared the gate, so it is in the wait loop.
  bool gate_closed =
      waitFor([&] { return !ProfilerTestAccessor::enginesReady(profiler); });
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_TRUE(gate_closed);
  EXPECT_FALSE(closed.load());

  cpu.released.store(true);
  hook.join();
  closer.join();
  EXPECT_TRUE(closed.load());
  EXPECT_TRUE(closed_ok.load());
  EXPECT_TRUE(entered);
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
}

// The wait is bounded: a hook call stuck inside an engine makes
// closeThreadRegistration() report failure after the budget instead of
// hanging stop() under _state_lock. The registration gate stays closed, and
// the unregistration gate is not touched.
TEST(ProfilerEnginesGateTest, CloseThreadRegistrationTimesOutOnStuckHookCall) {
  Profiler *profiler = Profiler::instance();
  BlockingEngine cpu;
  Engine wall;
  ProfilerTestAccessor::EngineSwap swap(profiler, &cpu, &wall);
  ProfilerTestAccessor::RegistrationGate gate(profiler);
  ProfilerTestAccessor::DrainBudget budget(200000000LL);

  std::thread hook([] { Profiler::registerThread(OS::threadId()); });
  bool entered = waitFor([&] { return cpu.entered.load(); });
  auto begin = std::chrono::steady_clock::now();
  bool ok = ProfilerTestAccessor::closeThreadRegistration(profiler);
  long long elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - begin)
                            .count();
  bool ready = ProfilerTestAccessor::enginesReady(profiler);
  int inflight = ProfilerTestAccessor::hookCallsInflight(profiler);
  bool stable = ProfilerTestAccessor::threadTablesStable(profiler);

  cpu.released.store(true);
  hook.join();

  EXPECT_TRUE(entered);
  EXPECT_FALSE(ok);
  EXPECT_FALSE(ready);
  EXPECT_EQ(1, inflight);
  EXPECT_TRUE(stable);
  EXPECT_GE(elapsed_ms, 150);
  EXPECT_LT(elapsed_ms, 3000);
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
}

// The ThreadTablesFreeze a CPU engine's start() takes around a table
// replacement closes both gates before it waits for hook
// calls already inside an engine, does not return while one is, keeps
// unregisterThread() off the engines while alive, and on destruction reopens
// unregistration but not registration (only a CPU engine that started opens
// that).
TEST(ProfilerEnginesGateTest, ThreadTablesFreezeClosesGatesAndWaitsForHookCalls) {
  Profiler *profiler = Profiler::instance();
  BlockingEngine cpu;
  Engine wall;
  ProfilerTestAccessor::EngineSwap swap(profiler, &cpu, &wall);
  ProfilerTestAccessor::RegistrationGate gate(profiler);
  ProfilerTestAccessor::DrainBudget budget(4000000000LL);
  int tid = OS::threadId();

  std::thread hook([] { Profiler::registerThread(OS::threadId()); });
  bool entered = waitFor([&] { return cpu.entered.load(); });
  std::atomic<bool> in_body{false};
  std::atomic<bool> drained_inside{false};
  std::atomic<bool> stable_inside{true};
  std::atomic<bool> ready_inside{true};
  std::atomic<int> unreg_inside{0};
  std::thread freezer([&] {
    ProfilerTestAccessor::withThreadTablesFreeze(profiler, [&](bool drained) {
      drained_inside.store(drained);
      stable_inside.store(ProfilerTestAccessor::threadTablesStable(profiler));
      ready_inside.store(ProfilerTestAccessor::enginesReady(profiler));
      Profiler::resetUnregisterObservableForTest();
      Profiler::unregisterThread(tid);
      unreg_inside.store(Profiler::lastUnregisteredTidForTest());
      in_body.store(true);
    });
  });
  bool cleared =
      waitFor([&] { return !ProfilerTestAccessor::threadTablesStable(profiler); });
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  bool in_body_early = in_body.load();

  cpu.released.store(true);
  hook.join();
  freezer.join();

  EXPECT_TRUE(entered);
  EXPECT_TRUE(cleared);
  EXPECT_FALSE(in_body_early);
  EXPECT_TRUE(in_body.load());
  EXPECT_TRUE(drained_inside.load());
  EXPECT_FALSE(stable_inside.load());
  EXPECT_FALSE(ready_inside.load());
  EXPECT_EQ(-1, unreg_inside.load());
  EXPECT_TRUE(ProfilerTestAccessor::threadTablesStable(profiler));
  EXPECT_FALSE(ProfilerTestAccessor::enginesReady(profiler));
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
  Profiler::resetUnregisterObservableForTest();
}

// A freeze whose wait times out reports it, so start() can fail without
// replacing any table, and its destructor still reopens unregistration.
TEST(ProfilerEnginesGateTest, ThreadTablesFreezeReportsUndrainedOnStuckHookCall) {
  Profiler *profiler = Profiler::instance();
  BlockingEngine cpu;
  Engine wall;
  ProfilerTestAccessor::EngineSwap swap(profiler, &cpu, &wall);
  ProfilerTestAccessor::RegistrationGate gate(profiler);
  ProfilerTestAccessor::DrainBudget budget(200000000LL);

  std::thread hook([] { Profiler::registerThread(OS::threadId()); });
  bool entered = waitFor([&] { return cpu.entered.load(); });
  bool body_ran = false;
  bool drained_inside = true;
  ProfilerTestAccessor::withThreadTablesFreeze(profiler, [&](bool drained) {
    body_ran = true;
    drained_inside = drained;
  });
  bool stable_after = ProfilerTestAccessor::threadTablesStable(profiler);
  bool ready_after = ProfilerTestAccessor::enginesReady(profiler);

  cpu.released.store(true);
  hook.join();

  EXPECT_TRUE(entered);
  EXPECT_TRUE(body_ran);
  EXPECT_FALSE(drained_inside);
  EXPECT_TRUE(stable_after);
  EXPECT_FALSE(ready_after);
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
}

// A CPU engine fake: start() optionally opens the registration gate the way
// CTimer/PerfEvents do, and fails or succeeds. Counts enableEvents(true) and
// registerThread() calls.
class FakeCpuEngine : public Engine {
public:
  FakeCpuEngine(bool fail, bool open_gate) : _fail(fail), _open_gate(open_gate) {}
  std::atomic<bool> gate_open_in_start{false};
  std::atomic<int> enable_true_calls{0};
  std::atomic<int> register_calls{0};

  Error start(Arguments &args) override {
    if (_open_gate) {
      Profiler::instance()->openThreadRegistration();
      gate_open_in_start.store(
          ProfilerTestAccessor::enginesReady(Profiler::instance()));
    }
    return _fail ? Error("injected CPU engine start failure") : Error::OK;
  }
  void enableEvents(bool enabled) override {
    if (enabled) {
      enable_true_calls.fetch_add(1);
    }
  }
  int registerThread(int tid) override {
    register_calls.fetch_add(1);
    return 0;
  }

private:
  bool _fail;
  bool _open_gate;
};

// A CPU engine that opened the gate and then failed leaves it closed, so the
// hook never reaches an engine that did not start.
TEST(ProfilerEnginesGateTest, FailedCpuEngineStartClosesThreadRegistration) {
  Profiler *profiler = Profiler::instance();
  ASSERT_FALSE(ProfilerTestAccessor::enginesReady(profiler));
  FakeCpuEngine cpu(/*fail=*/true, /*open_gate=*/true);
  Engine wall;
  ProfilerTestAccessor::EngineSwap swap(profiler, &cpu, &wall);
  Arguments args;

  bool started = ProfilerTestAccessor::startCpuEngine(profiler, args);
  bool ready = ProfilerTestAccessor::enginesReady(profiler);
  int registered = Profiler::registerThread(OS::threadId());
  // Restores the closed gate if the call under test regressed.
  ProfilerTestAccessor::closeThreadRegistration(profiler);

  EXPECT_FALSE(started);
  EXPECT_TRUE(cpu.gate_open_in_start.load());
  EXPECT_FALSE(ready);
  EXPECT_EQ(-1, registered);
  EXPECT_EQ(0, cpu.register_calls.load());
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
  EXPECT_TRUE(ProfilerTestAccessor::threadTablesStable(profiler));
}

// A CPU engine without a per-thread table (ITimer-like) never opens the gate
// itself; startCpuEngine() opens it once the engine started, so the hook
// reaches it.
TEST(ProfilerEnginesGateTest, StartedCpuEngineOpensThreadRegistration) {
  Profiler *profiler = Profiler::instance();
  ASSERT_FALSE(ProfilerTestAccessor::enginesReady(profiler));
  FakeCpuEngine cpu(/*fail=*/false, /*open_gate=*/false);
  Engine wall;
  ProfilerTestAccessor::EngineSwap swap(profiler, &cpu, &wall);
  Arguments args;

  bool started = ProfilerTestAccessor::startCpuEngine(profiler, args);
  bool ready = ProfilerTestAccessor::enginesReady(profiler);
  Profiler::registerThread(OS::threadId());
  int registered = cpu.register_calls.load();
  bool closed_ok = ProfilerTestAccessor::closeThreadRegistration(profiler);

  EXPECT_TRUE(started);
  EXPECT_TRUE(ready);
  EXPECT_EQ(1, registered);
  EXPECT_TRUE(closed_ok);
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
}

// The CPU engine is enabled only if its own start() succeeded, even when
// another mode activated.
TEST(ProfilerEnginesGateTest, CpuEngineEnabledOnlyIfItStarted) {
  Profiler *profiler = Profiler::instance();
  FakeCpuEngine cpu(/*fail=*/true, /*open_gate=*/false);
  Engine wall;
  ProfilerTestAccessor::EngineSwap swap(profiler, &cpu, &wall);
  Arguments args;

  bool started = ProfilerTestAccessor::startCpuEngine(profiler, args);
  ProfilerTestAccessor::closeThreadRegistration(profiler);
  int activated = EM_WALL | (started ? EM_CPU : 0);
  ProfilerTestAccessor::enableCpuEngine(profiler, activated);
  EXPECT_FALSE(started);
  EXPECT_EQ(0, cpu.enable_true_calls.load());

  ProfilerTestAccessor::enableCpuEngine(profiler, EM_CPU | EM_WALL);
  EXPECT_EQ(1, cpu.enable_true_calls.load());
}

// The idle fast path in registerThread() only short-cuts a closed gate: with
// the gate open the call still reaches the engine, and the in-flight count is
// back at zero afterwards either way. The return value is not checked with
// the gate open: the plain wall engine reports -1, which is OR-ed in.
TEST(ProfilerEnginesGateTest, RegisterThreadFastPathDoesNotSkipOpenGate) {
  Profiler *profiler = Profiler::instance();
  ASSERT_FALSE(ProfilerTestAccessor::enginesReady(profiler));
  FakeCpuEngine cpu(/*fail=*/false, /*open_gate=*/false);
  Engine wall;
  ProfilerTestAccessor::EngineSwap swap(profiler, &cpu, &wall);

  EXPECT_EQ(-1, Profiler::registerThread(OS::threadId()));
  EXPECT_EQ(0, cpu.register_calls.load());
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
  {
    ProfilerTestAccessor::RegistrationGate gate(profiler);
    Profiler::registerThread(OS::threadId());
    EXPECT_EQ(1, cpu.register_calls.load());
    EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
  }
  EXPECT_FALSE(ProfilerTestAccessor::enginesReady(profiler));
}

// A negative tid must not index before CTimer's table. The page before the
// table is inaccessible, so an access through _timers[-1] faults.
TEST(CTimerTableTest, NegativeTidIsRejected) {
  size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
  char *base = (char *)mmap(nullptr, 2 * page_size, PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(MAP_FAILED, (void *)base);
  ASSERT_EQ(0, mprotect(base, page_size, PROT_NONE));
  int *table = (int *)(base + page_size);
  {
    CTimerTestAccessor::TimerTableSwap swap(table, 16);
    CTimer engine;
    // unregisterThread() first: registerThread() may fail earlier, in
    // timer_create, so this is the discriminating call.
    CTimerTestAccessor::unregisterThread(engine, -1);
    EXPECT_EQ(-1, CTimerTestAccessor::registerThread(engine, -1));
    for (int i = 0; i < 16; i++) {
      EXPECT_EQ(0, table[i]) << "slot " << i;
    }
  }
  munmap(base, 2 * page_size);
}

// Thread body for the cancellation test: makes a hook call with asynchronous
// cancellation enabled, then reaches a cancellation point. A plain C-style
// thread is used so that no C++ frame with cleanups sits above the call when
// the cancellation unwinds it.
static std::atomic<bool> survived_cancellation{false};
static void *registerWithAsyncCancel(void *) {
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, nullptr);
  Profiler::registerThread(OS::threadId());
  pthread_testcancel();
  survived_cancellation.store(true);
  return nullptr;
}

// A cancellation requested during a hook call stays pending until the call has
// left every destructor-bearing scope. Current glibc acts on a pending
// asynchronous request as soon as cancellation is re-enabled, so re-enabling it
// from a destructor would unwind out of an implicitly noexcept function and
// terminate the process. Older glibc (2.35) keeps it pending until the next
// cancellation point instead. Either way the process must survive, the thread
// must not run past that cancellation point, and the in-flight count must be
// back at zero. The join value is not checked: a forced unwind that crosses
// differently versioned libgcc copies (see run_with_cleanup() in
// libraryPatcher_linux.cpp) does not always report PTHREAD_CANCELED.
TEST(ProfilerEnginesGateTest, CancellationDuringHookCallActsAfterTheCall) {
#if defined(TSAN_ENABLED)
  GTEST_SKIP() << "TSan does not support asynchronous thread cancellation";
#endif
  Profiler *profiler = Profiler::instance();
  BlockingEngine cpu;
  Engine wall;
  ProfilerTestAccessor::EngineSwap swap(profiler, &cpu, &wall);
  ProfilerTestAccessor::RegistrationGate gate(profiler);

  survived_cancellation.store(false);
  pthread_t thread;
  ASSERT_EQ(0, pthread_create(&thread, nullptr, registerWithAsyncCancel,
                              nullptr));
  bool entered = waitFor([&] { return cpu.entered.load(); });
  // Cancellation is disabled inside the hook call, so this stays pending.
  EXPECT_EQ(0, pthread_cancel(thread));
  cpu.released.store(true);
  EXPECT_EQ(0, pthread_join(thread, nullptr));

  EXPECT_TRUE(entered);
  // The hook call ran with cancellation disabled; without that, the request
  // could act at a cancellation point inside the engine and unwind through
  // ~HookCallScope().
  EXPECT_EQ(PTHREAD_CANCEL_DISABLE, cpu.cancel_state_inside.load());
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));
  EXPECT_FALSE(survived_cancellation.load());
}

// Unregistration is skipped, without touching the engines, while start() may
// replace their per-thread tables, and goes through once the tables are
// stable. In this binary the call records the tid instead of calling the
// (null) engines, so the recorded tid shows whether it passed the gate.
TEST(ProfilerEnginesGateTest, UnregisterThreadSkipsEnginesWhileTablesFrozen) {
  Profiler *profiler = Profiler::instance();
  int tid = OS::threadId();

  ProfilerTestAccessor::setThreadTablesStable(profiler, false);
  Profiler::resetUnregisterObservableForTest();
  Profiler::unregisterThread(tid);
  EXPECT_EQ(-1, Profiler::lastUnregisteredTidForTest());
  EXPECT_EQ(0, ProfilerTestAccessor::hookCallsInflight(profiler));

  ProfilerTestAccessor::setThreadTablesStable(profiler, true);
  Profiler::unregisterThread(tid);
  EXPECT_EQ(tid, Profiler::lastUnregisteredTidForTest());
  Profiler::resetUnregisterObservableForTest();
}

#endif // __linux__
