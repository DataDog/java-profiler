/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "arguments.h"
#include "itimer.h"
#include "os.h"
#include "vmEntry.h"

#include <atomic>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <sys/time.h>

// This binary links itimer.o statically, so defining sigaction here binds every
// main-library sigaction call to the interposer below; the flag makes only
// SIGPROF installs fail. Relaxed suffices: it is same-thread-only, no data.
static std::atomic<bool> g_fail_sigprof_install{false};

typedef int (*sigaction_fn_t)(int, const struct sigaction *, struct sigaction *);

static sigaction_fn_t real_sigaction() {
  static sigaction_fn_t fn = (sigaction_fn_t)dlsym(RTLD_NEXT, "sigaction");
  if (fn == nullptr) {
    fprintf(stderr, "dlsym(RTLD_NEXT, sigaction) failed\n");
    abort();
  }
  return fn;
}

extern "C" int sigaction(int signum, const struct sigaction *act,
                         struct sigaction *oldact) {
  if (g_fail_sigprof_install.load(std::memory_order_relaxed) &&
      signum == SIGPROF && act != nullptr) {
    errno = EINVAL;
    return -1;
  }
  return real_sigaction()(signum, act, oldact);
}

class VMTestAccessor {
public:
  static jvmtiExtensionFunction requestStackTrace() {
    return VM::_request_stack_trace;
  }
  static void setRequestStackTrace(jvmtiExtensionFunction fn) {
    __atomic_store_n(&VM::_request_stack_trace, fn, __ATOMIC_RELEASE);
  }
};

static void dummyRequestStackTrace() {}

static void test_sigprof_handler(int, siginfo_t *, void *) {}

// Reads and seeds the engines' static _interval, so a test's pre-state does
// not depend on what earlier tests left behind.
class ITimerTestAccessor {
public:
  static long intervalItimer() { return ITimer::_interval; }
  static void intervalItimer(long v) { ITimer::_interval = v; }
  static long intervalJvmti() { return ITimerJvmti::_interval; }
  static void intervalJvmti(long v) { ITimerJvmti::_interval = v; }
  static SigAction signalHandler() { return ITimer::signalHandler; }
};

// Returns the current SIGPROF disposition (sa_handler and sa_sigaction share
// storage).
static struct sigaction sigprofDisposition() {
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sigaction(SIGPROF, nullptr, &sa);
  return sa;
}

// Linux/glibc fills only the first _NSIG/8 bytes of sa_mask on a sigaction
// read; the 128-byte sigset_t tail keeps the wrapper's internal buffer
// content, so compare the mask per signal instead of as raw bytes.
static bool sameSigmask(const sigset_t &a, const sigset_t &b) {
  for (int sig = 1; sig <= 64; sig++) {
    if (sigismember(&a, sig) != sigismember(&b, sig)) {
      return false;
    }
  }
  return true;
}

static bool sameDisposition(const struct sigaction &a, const struct sigaction &b) {
#ifdef __linux__
  // Some Linux libcs leave the kernel-internal SA_RESTORER bit (0x04000000)
  // in the read-back sa_flags (x86-64 glibc and musl set it; aarch64 glibc
  // strips it), whether or not the header exports the macro. It is libc
  // bookkeeping, not part of the application-level disposition.
  constexpr unsigned long kLibcInternal = 0x04000000;
#else
  constexpr unsigned long kLibcInternal = 0;
#endif
  return a.sa_sigaction == b.sa_sigaction &&
         (static_cast<unsigned long>(a.sa_flags) & ~kLibcInternal) ==
             (static_cast<unsigned long>(b.sa_flags) & ~kLibcInternal) &&
         sameSigmask(a.sa_mask, b.sa_mask);
}

static bool itimerDisarmed() {
  struct itimerval tv;
  memset(&tv, 0, sizeof(tv));
  getitimer(ITIMER_PROF, &tv);
  return tv.it_value.tv_sec == 0 && tv.it_value.tv_usec == 0;
}

class ITimerTest : public ::testing::Test {
protected:
  jvmtiExtensionFunction _saved_request_stack_trace;
  struct sigaction _saved_sigprof;

  void SetUp() override {
    _saved_request_stack_trace = VMTestAccessor::requestStackTrace();
    _saved_sigprof = sigprofDisposition();
    g_fail_sigprof_install = false;
  }

  void TearDown() override {
    g_fail_sigprof_install = false;
    // Discard a SIGPROF an armed timer already generated, so the saved
    // disposition cannot receive it as SIG_DFL.
    signal(SIGPROF, SIG_IGN);
    // Disarm in case a start() armed the timer before failing.
    struct itimerval tv = {};
    setitimer(ITIMER_PROF, &tv, nullptr);
    sigaction(SIGPROF, &_saved_sigprof, nullptr);
    VMTestAccessor::setRequestStackTrace(_saved_request_stack_trace);
  }
};

// check() must fail without restoring when the probing sigaction fails;
// restoring from the uninitialized oldsa would install garbage as the
// process-wide SIGPROF handler.
TEST_F(ITimerTest, JvmtiCheckFailsWhenSigactionProbeFails) {
  VMTestAccessor::setRequestStackTrace(
      reinterpret_cast<jvmtiExtensionFunction>(&dummyRequestStackTrace));
  struct sigaction before = sigprofDisposition();

  g_fail_sigprof_install = true;
  ITimerJvmti engine;
  Arguments args;
  Error error = engine.check(args);
  g_fail_sigprof_install = false;

  EXPECT_TRUE((bool)error);
  EXPECT_STREQ("failed to query the SIGPROF disposition", error.message());
  EXPECT_TRUE(sameDisposition(before, sigprofDisposition()));
  EXPECT_TRUE(itimerDisarmed());
}

// check() probes by temporarily installing SIG_IGN and must put the previous
// disposition back afterwards, unchanged.
TEST_F(ITimerTest, JvmtiCheckRestoresPreviousDisposition) {
  VMTestAccessor::setRequestStackTrace(
      reinterpret_cast<jvmtiExtensionFunction>(&dummyRequestStackTrace));
  struct sigaction custom;
  memset(&custom, 0, sizeof(custom));
  custom.sa_sigaction = test_sigprof_handler;
  custom.sa_flags = SA_SIGINFO | SA_RESTART;
  sigemptyset(&custom.sa_mask);
  ASSERT_EQ(0, sigaction(SIGPROF, &custom, nullptr));

  ITimerJvmti engine;
  Arguments args;
  Error error = engine.check(args);

  EXPECT_FALSE((bool)error);
  EXPECT_TRUE(sameDisposition(custom, sigprofDisposition()));
  EXPECT_TRUE(itimerDisarmed());
}

// A caller setting only the cpu parameter (leaving _interval at its default)
// must be accepted: the engine runs with the interval it actually assigns,
// cpuSamplerInterval(), not with the raw _interval field.
TEST_F(ITimerTest, JvmtiStartAcceptsCpuOnlyArguments) {
  ITimerJvmti engine;
  Arguments args;
  args._cpu = 1000000;
  args._interval = -1;

  Error error = engine.start(args);

  EXPECT_FALSE((bool)error);
  EXPECT_EQ(1000000, engine.interval());
  engine.stop();
  // stop() installs SIG_IGN: a late SIGPROF is discarded at kernel level.
  EXPECT_EQ(SIG_IGN, sigprofDisposition().sa_handler);
  EXPECT_TRUE(itimerDisarmed());
}

// With no cpu and no interval, cpuSamplerInterval() falls back to
// DEFAULT_CPU_INTERVAL, which start() must accept.
TEST_F(ITimerTest, JvmtiStartDefaultsInterval) {
  ITimerJvmti engine;
  Arguments args;
  args._event = EVENT_CPU;

  Error error = engine.start(args);

  EXPECT_FALSE((bool)error);
  EXPECT_EQ(DEFAULT_CPU_INTERVAL, engine.interval());
  engine.stop();
  EXPECT_TRUE(itimerDisarmed());
}

// With no cpu, cpuSamplerInterval() resolves the positive _interval before
// falling back to DEFAULT_CPU_INTERVAL; start() must run with that value.
TEST_F(ITimerTest, JvmtiStartUsesIntervalFallback) {
  ITimerJvmti engine;
  Arguments args;
  args._event = EVENT_CPU;
  args._cpu = -1;
  args._interval = 5000000;

  Error error = engine.start(args);

  EXPECT_FALSE((bool)error);
  EXPECT_EQ(5000000, engine.interval());
  engine.stop();
  EXPECT_TRUE(itimerDisarmed());
}

// cpuSamplerInterval() returns 0 for a non-CPU event; the engine must reject
// it instead of arming a zero (disarmed) timer. _interval stays at its
// default 0 so the rejection cannot come from a negative-field shortcut.
TEST_F(ITimerTest, JvmtiStartRejectsNonCpuEvent) {
  ITimerJvmti engine;
  Arguments args;
  args._event = EVENT_WALL;
  args._cpu = 1000000;
  ITimerTestAccessor::intervalJvmti(123456);
  long interval_before = ITimerTestAccessor::intervalJvmti();
  struct sigaction before = sigprofDisposition();

  Error error = engine.start(args);

  EXPECT_TRUE((bool)error);
  EXPECT_STREQ("interval must be positive", error.message());
  EXPECT_EQ(interval_before, engine.interval());
  EXPECT_TRUE(sameDisposition(before, sigprofDisposition()));
  EXPECT_TRUE(itimerDisarmed());
}

// The same validation contract as ITimerJvmti::start(): a non-CPU event
// reaching the CPU-time engine must be rejected, and _interval stays as-is.
TEST_F(ITimerTest, StartRejectsNonCpuEvent) {
  ITimer engine;
  Arguments args;
  args._event = EVENT_WALL;
  args._cpu = 1000000;
  ITimerTestAccessor::intervalItimer(123456);
  long interval_before = ITimerTestAccessor::intervalItimer();
  struct sigaction before = sigprofDisposition();

  Error error = engine.start(args);

  EXPECT_TRUE((bool)error);
  EXPECT_STREQ("interval must be positive", error.message());
  EXPECT_EQ(interval_before, engine.interval());
  EXPECT_TRUE(sameDisposition(before, sigprofDisposition()));
  EXPECT_TRUE(itimerDisarmed());
}

TEST_F(ITimerTest, StartAcceptsCpuOnlyArguments) {
  ITimer engine;
  Arguments args;
  args._cpu = 1000000;
  args._interval = -1;

  Error error = engine.start(args);

  EXPECT_FALSE((bool)error);
  EXPECT_EQ(1000000, engine.interval());
  engine.stop();
  // ITimer::stop() keeps the engine handler installed (drops on _enabled);
  // only the timer is disarmed.
  EXPECT_EQ(ITimerTestAccessor::signalHandler(),
            sigprofDisposition().sa_sigaction);
  EXPECT_TRUE(itimerDisarmed());
}
