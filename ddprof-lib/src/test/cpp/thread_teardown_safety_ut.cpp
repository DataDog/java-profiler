/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Acceptance tests for the PROF-14603 signal-race fix in thread teardown.
 *
 * Root cause: SIGVTALRM delivered between ProfiledThread::release() clearing TLS
 * (pthread_setspecific(NULL)) and deleting the ProfiledThread object, causing
 * a signal handler to call current() and dereference a freed pointer.
 *
 * Fix coverage:
 * - Signal-safe TLS accessor returns null in the race window (no crash).
 * - SignalBlocker properly guards the unregister+release sequence.
 * - Thread lifecycle (init/release) is race-free under concurrent signal load.
 */

#include <gtest/gtest.h>

#ifdef __linux__

#include "guards.h"
#include "nativeMem.h"
#include "threadLocalData.h"

#include <atomic>
#include <pthread.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <vector>

#ifdef __GLIBC__
// <pthread.h> declares these only inside the C (non-C++) conditional.
// Redeclare with extern "C" so we can call them directly from C++ code.
extern "C" {
    extern void __pthread_register_cancel(__pthread_unwind_buf_t*);
    extern void __pthread_unregister_cancel(__pthread_unwind_buf_t*);
    [[noreturn]] extern void __pthread_unwind_next(__pthread_unwind_buf_t*);
}
#endif

// Sentinel value meaning "handler has not run yet" — distinct from both nullptr
// (not registered) and any real ProfiledThread address.
static ProfiledThread* const kNotYetRun = reinterpret_cast<ProfiledThread*>(1);

// Use sigaction() instead of signal() so the handler persists across platforms;
// signal() has implementation-defined reset-on-deliver (SA_RESETHAND) behaviour.
static inline void install_handler(int sig, void (*handler)(int)) {
  struct sigaction sa{};
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(sig, &sa, nullptr);
}

// RAII helper: saves the current sigaction for `sig` and restores it on
// destruction, preventing signal-disposition leaks across tests.
struct SigGuard {
  int sig;
  struct sigaction saved;
  explicit SigGuard(int s) : sig(s) { sigaction(s, nullptr, &saved); }
  ~SigGuard() { sigaction(sig, &saved, nullptr); }
  SigGuard(const SigGuard&) = delete;
  SigGuard& operator=(const SigGuard&) = delete;
};

// ── T-01: current() is non-null while live, null after release ─────

static std::atomic<ProfiledThread *> g_t01_seen{nullptr};

static void t01_handler(int) {
  g_t01_seen.store(ProfiledThread::current(), std::memory_order_relaxed);
}

static void *t01_body(void *) {
  ProfiledThread::initCurrentThread();

  SigGuard guard(SIGVTALRM);
  install_handler(SIGVTALRM, t01_handler);
  g_t01_seen.store(kNotYetRun, std::memory_order_relaxed);
  pthread_kill(pthread_self(), SIGVTALRM);
  ProfiledThread *t01_pre = g_t01_seen.load(std::memory_order_relaxed);
  if (t01_pre == kNotYetRun) {
    ADD_FAILURE() << "SIGVTALRM handler must have run before release() (handler did not execute)";
    return nullptr;
  }
  EXPECT_NE(nullptr, t01_pre)
      << "current() must return non-null while ProfiledThread is live";

  ProfiledThread::release();

  g_t01_seen.store(kNotYetRun, std::memory_order_relaxed);
  pthread_kill(pthread_self(), SIGVTALRM);
  ProfiledThread *t01_post = g_t01_seen.load(std::memory_order_relaxed);
  if (t01_post == kNotYetRun) {
    ADD_FAILURE() << "SIGVTALRM handler must have run after release() (handler did not execute)";
    return nullptr;
  }
  EXPECT_EQ(nullptr, t01_post)
      << "current() must return null after release()";

  return nullptr;
}

// Verifies the post-release null guarantee seen from a signal handler.
TEST(ThreadTeardownSafetyTest, TLSAccessibleDuringLifetimeNullAfterRelease) {
  pthread_t t;
  ASSERT_EQ(0, pthread_create(&t, nullptr, t01_body, nullptr));
  pthread_join(t, nullptr);
}

// ── T-02: Signal in the TLS-clear/delete window does not crash ───────────────

static std::atomic<ProfiledThread *> g_t02_seen{nullptr};

static void t02_handler(int) {
  g_t02_seen.store(ProfiledThread::current(), std::memory_order_relaxed);
}

static void *t02_body(void *) {
  ProfiledThread::initCurrentThread();

  SigGuard guard(SIGVTALRM);
  install_handler(SIGVTALRM, t02_handler);
  g_t02_seen.store(kNotYetRun, std::memory_order_relaxed);

  // Simulate the race window: TLS cleared but object not yet freed.
  ProfiledThread *detached = ProfiledThread::clearCurrentThreadTLS();

  // Signal delivered in the race window must see null, not a dangling pointer.
  pthread_kill(pthread_self(), SIGVTALRM);
  EXPECT_EQ(nullptr, g_t02_seen.load(std::memory_order_relaxed))
      << "current() must return null in the TLS-clear/delete window";

  // release() with TLS already null must not double-free.
  ProfiledThread::release();
  // Complete the simulated teardown: delete the object (mirrors what freeKey
  // would do). Destructor is private so we need the test helper.
  ProfiledThread::deleteForTest(detached);
  EXPECT_EQ(nullptr, ProfiledThread::current());
  return nullptr;
}

// Regression for the primary crash path: signal fires between clearTLS and delete.
TEST(ThreadTeardownSafetyTest, SignalInTLSClearDeleteWindowDoesNotCrash) {
  pthread_t t;
  ASSERT_EQ(0, pthread_create(&t, nullptr, t02_body, nullptr));
  pthread_join(t, nullptr);
}

// ── T-03: Double release() is idempotent ─────────────────────────────────────

static void *t03_body(void *) {
  ProfiledThread::initCurrentThread();
  ProfiledThread::release();
  ProfiledThread::release(); // must not crash or double-free
  return nullptr;
}

TEST(ThreadTeardownSafetyTest, DoubleReleaseIsIdempotent) {
  pthread_t t;
  ASSERT_EQ(0, pthread_create(&t, nullptr, t03_body, nullptr));
  pthread_join(t, nullptr);
}

// ── T-04: Signal-safe accessor returns null without initCurrentThread() ──────

static std::atomic<ProfiledThread *> g_t04_seen{nullptr};

static void t04_handler(int) {
  g_t04_seen.store(ProfiledThread::current(), std::memory_order_relaxed);
}

static void *t04_body(void *) {
  // Intentionally no initCurrentThread().
  SigGuard guard(SIGVTALRM);
  install_handler(SIGVTALRM, t04_handler);
  g_t04_seen.store(kNotYetRun, std::memory_order_relaxed);
  pthread_kill(pthread_self(), SIGVTALRM);
  EXPECT_EQ(nullptr, g_t04_seen.load(std::memory_order_relaxed))
      << "current() must return null for unregistered threads";
  return nullptr;
}

TEST(ThreadTeardownSafetyTest, SignalSafeAccessorReturnsNullWithoutInit) {
  pthread_t t;
  ASSERT_EQ(0, pthread_create(&t, nullptr, t04_body, nullptr));
  pthread_join(t, nullptr);
}

// ── T-05: Concurrent signals during teardown stress ──────────────────────────

static std::atomic<int> g_t05_signal_count{0};

static void t05_handler(int) {
  (void)ProfiledThread::current();
  g_t05_signal_count.fetch_add(1, std::memory_order_relaxed);
}

static void *t05_worker(void *) {
  ProfiledThread::initCurrentThread();
  for (int i = 0; i < 10; ++i) {
    pthread_kill(pthread_self(), SIGVTALRM);
  }
  ProfiledThread::release();
  return nullptr;
}

// 20 threads × 5 rounds with signal spray; handler invocation is verified.
// Signal dispositions are process-wide — install once from the test body so
// no worker can race to restore SIG_DFL (terminate) mid-flight.
TEST(ThreadTeardownSafetyTest, ConcurrentSignalsDuringTeardownStress) {
  SigGuard gVtalrm(SIGVTALRM);
  SigGuard gProf(SIGPROF);
  g_t05_signal_count.store(0, std::memory_order_relaxed);
  install_handler(SIGVTALRM, t05_handler);
  install_handler(SIGPROF, SIG_IGN);
  for (int round = 0; round < 5; ++round) {
    std::vector<pthread_t> threads(20);
    for (auto &tid : threads) {
      ASSERT_EQ(0, pthread_create(&tid, nullptr, t05_worker, nullptr));
    }
    for (auto &tid : threads) {
      pthread_join(tid, nullptr);
    }
  }
  EXPECT_GT(g_t05_signal_count.load(std::memory_order_relaxed), 0)
      << "SIGVTALRM handler must have been invoked at least once";
}

// ── T-06: SignalBlocker masks SIGPROF + SIGVTALRM and restores on exit ────────

static void *t06_body(void *) {
  sigset_t before, during, after;

  pthread_sigmask(SIG_SETMASK, nullptr, &before);

  {
    SignalBlocker blocker;
    pthread_sigmask(SIG_SETMASK, nullptr, &during);
    EXPECT_TRUE(sigismember(&during, SIGVTALRM))
        << "SignalBlocker must block SIGVTALRM";
    EXPECT_TRUE(sigismember(&during, SIGPROF))
        << "SignalBlocker must block SIGPROF";
  }

  pthread_sigmask(SIG_SETMASK, nullptr, &after);
  EXPECT_EQ(sigismember(&before, SIGVTALRM), sigismember(&after, SIGVTALRM))
      << "SignalBlocker must restore SIGVTALRM to its initial state on exit";
  EXPECT_EQ(sigismember(&before, SIGPROF), sigismember(&after, SIGPROF))
      << "SignalBlocker must restore SIGPROF to its initial state on exit";
  return nullptr;
}

TEST(ThreadTeardownSafetyTest, SignalBlockerMasksAndRestoresProfSignals) {
  pthread_t t;
  ASSERT_EQ(0, pthread_create(&t, nullptr, t06_body, nullptr));
  pthread_join(t, nullptr);
}

// ── T-07: Forced unwind with concurrent signal does not crash ─────────────────
// Cancellation mechanism differs between glibc (abi::__forced_unwind via C++
// unwinder) and musl (C-style pthread_cleanup_push callbacks).

static std::atomic<bool> g_t07_cleanup_ran{false};
static std::atomic<bool> g_t07_release_ran{false};

#ifdef __GLIBC__

// t07 uses __pthread_register_cancel for cleanup (same as run_with_cleanup in
// libraryPatcher_linux.cpp).  Two constraints follow from the static-libgcc /
// libgcc_s.so.1 incompatibility:
//
// 1. No C++ RAII objects with destructors in this frame.  After the longjmp
//    from glibc's stop function, __pthread_unwind_next calls _Unwind_ForcedUnwind
//    again to continue unwinding through this frame.  Any LSDA cleanup entry
//    (e.g. SigGuard, std::unique_ptr) would make __gxx_personality_v0 call
//    _Unwind_SetGR with a cross-version context → abort().
//
// 2. No try/catch: handler frames also add LSDA entries, same problem.
//
// Signal handler save/restore is done manually (plain struct sigaction, no
// destructor) so there is nothing in the LSDA for this frame.
__attribute__((noinline, no_stack_protector)) static void *t07_body(void *) {
  g_t07_cleanup_ran.store(false, std::memory_order_relaxed);
  g_t07_release_ran.store(false, std::memory_order_relaxed);

  // Save and install the signal handler WITHOUT RAII (no destructor = no LSDA
  // cleanup entry for this frame).
  struct sigaction old_sa_vtalrm;
  sigaction(SIGVTALRM, nullptr, &old_sa_vtalrm);
  install_handler(SIGVTALRM, SIG_IGN);

  ProfiledThread::initCurrentThread();

  __pthread_unwind_buf_t cancel_buf = {};
  if (__builtin_expect(
          __sigsetjmp((struct __jmp_buf_tag*)(void*)cancel_buf.__cancel_jmp_buf, 0), 0)) {
    // Restore handler before continuing forced unwind (no RAII to do it for us).
    sigaction(SIGVTALRM, &old_sa_vtalrm, nullptr);
    g_t07_cleanup_ran.store(true, std::memory_order_relaxed);
    ProfiledThread::release();
    g_t07_release_ran.store(true, std::memory_order_relaxed);
    __pthread_unwind_next(&cancel_buf);
  }
  __pthread_register_cancel(&cancel_buf);
  // No matching __pthread_unregister_cancel: the only legal exit from this body
  // is the forced unwind raised by pthread_cancel, which longjmps into the
  // __sigsetjmp branch above and continues via __pthread_unwind_next.  The loop
  // below never returns normally; if it ever did, cancel_buf would be left
  // registered against a destroyed frame.
  // Inject a signal before the cancellation point to exercise the combined path.
  pthread_kill(pthread_self(), SIGVTALRM);
  while (true) {
    pthread_testcancel();
    usleep(100);
  }
  // Must only exit via pthread_cancel above.  If control reaches here, the
  // frame was not cancelled as expected and cancel_buf is now a dangling
  // registration — abort rather than corrupt glibc's cleanup list.
  __builtin_unreachable();
}

#else  // !__GLIBC__ — musl: cancellation runs C cleanup callbacks

static void t07_cleanup_fn(void *) {
  g_t07_cleanup_ran.store(true, std::memory_order_relaxed);
  ProfiledThread::release();
  g_t07_release_ran.store(true, std::memory_order_relaxed);
}

static void *t07_body(void *) {
  g_t07_cleanup_ran.store(false, std::memory_order_relaxed);
  g_t07_release_ran.store(false, std::memory_order_relaxed);

  SigGuard guard(SIGVTALRM);
  install_handler(SIGVTALRM, SIG_IGN);
  ProfiledThread::initCurrentThread();

  pthread_cleanup_push(t07_cleanup_fn, nullptr);
  // Inject a signal before the cancellation point to exercise the combined path.
  pthread_kill(pthread_self(), SIGVTALRM);
  while (true) {
    pthread_testcancel();
    usleep(100);
  }
  pthread_cleanup_pop(0);
  ProfiledThread::release();
  return nullptr;
}

#endif  // __GLIBC__

TEST(ThreadTeardownSafetyTest, ForcedUnwindWithConcurrentSignalDoesNotCrash) {
  pthread_t t;
  ASSERT_EQ(0, pthread_create(&t, nullptr, t07_body, nullptr));
  usleep(5000);
  pthread_cancel(t);
  void *retval;
  ASSERT_EQ(0, pthread_join(t, &retval));
  EXPECT_TRUE(g_t07_cleanup_ran.load());
  EXPECT_TRUE(g_t07_release_ran.load());
  EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ── T-08: Double initCurrentThread() is idempotent ───────────────────────────

static void *t08_body(void *) {
  ProfiledThread::initCurrentThread();
  ProfiledThread *first = ProfiledThread::current();
  EXPECT_NE(nullptr, first);

  ProfiledThread::initCurrentThread(); // second call on the same thread
  ProfiledThread *second = ProfiledThread::current();
  EXPECT_NE(nullptr, second);
  EXPECT_EQ(first, second) << "double init must not allocate a second ProfiledThread";

  ProfiledThread::release();
  return nullptr;
}

TEST(ThreadTeardownSafetyTest, DoubleInitIsIdempotent) {
  pthread_t t;
  ASSERT_EQ(0, pthread_create(&t, nullptr, t08_body, nullptr));
  pthread_join(t, nullptr);
}

// ── T-09: High-frequency signals during thread churn ─────────────────────────

static std::atomic<bool> g_t09_stop{false};
static std::atomic<int> g_t09_signal_count{0};

static void t09_handler(int) {
  (void)ProfiledThread::current();
  g_t09_signal_count.fetch_add(1, std::memory_order_relaxed);
}

static void *t09_injector(void *) {
  while (!g_t09_stop.load(std::memory_order_relaxed)) {
    kill(getpid(), SIGVTALRM);
    usleep(500); // ~2 kHz
  }
  return nullptr;
}

static void *t09_worker(void *) {
  ProfiledThread::initCurrentThread();
  usleep(100);
  ProfiledThread::release();
  return nullptr;
}

// Mirrors DumpWhileChurningThreadsTest at native level: 100 short-lived threads
// under continuous SIGVTALRM injection must complete without crash; handler
// invocation is verified.
TEST(ThreadTeardownSafetyTest, HighFrequencySignalsDuringThreadChurn) {
  SigGuard testGuard(SIGVTALRM);
  g_t09_signal_count.store(0, std::memory_order_relaxed);
  install_handler(SIGVTALRM, t09_handler);

  g_t09_stop.store(false, std::memory_order_relaxed);
  pthread_t injector;
  ASSERT_EQ(0, pthread_create(&injector, nullptr, t09_injector, nullptr));

  for (int i = 0; i < 100; ++i) {
    pthread_t worker;
    ASSERT_EQ(0, pthread_create(&worker, nullptr, t09_worker, nullptr));
    pthread_join(worker, nullptr);
  }

  g_t09_stop.store(true, std::memory_order_relaxed);
  pthread_join(injector, nullptr);
  EXPECT_GT(g_t09_signal_count.load(std::memory_order_relaxed), 0)
      << "SIGVTALRM handler must have been invoked at least once";
}

// ── T-10: CriticalSection reentrancy guard prevents double-entry ──────────────

static void *t10_body(void *) {
  ProfiledThread::initCurrentThread();
  ProfiledThread *pt = ProfiledThread::current();
  if (pt == nullptr) {
    ADD_FAILURE() << "current() returned nullptr";
    return nullptr;
  }

  // Outer critical section must succeed.
  EXPECT_TRUE(pt->tryEnterCriticalSection());

  // Simulated reentrancy from the same thread (e.g. nested signal handler).
  EXPECT_FALSE(pt->tryEnterCriticalSection())
      << "reentrancy must be rejected while outer critical section is active";

  pt->exitCriticalSection();

  // After exit, entry succeeds again.
  EXPECT_TRUE(pt->tryEnterCriticalSection());
  pt->exitCriticalSection();

  ProfiledThread::release();
  return nullptr;
}

TEST(ThreadTeardownSafetyTest, CriticalSectionReentrancyGuard) {
  pthread_t t;
  ASSERT_EQ(0, pthread_create(&t, nullptr, t10_body, nullptr));
  pthread_join(t, nullptr);
}

// ── NM_THREAD_LOCAL accounting balances across the ProfiledThread lifecycle ──
// forTid() (in initCurrentThread) increments NM_THREAD_LOCAL; the matching
// decrement lives in freeValue(), which is invoked both by release() (via
// ThreadLocal::clear()) and by the pthread-key destructor on thread exit.
// These verify both teardown paths return the gauge to its baseline.

static std::atomic<long long> g_tl_live_during{0};

static void *tl_release_body(void *) {
  ProfiledThread::initCurrentThread();
  g_tl_live_during.store(NativeMem::live(NM_THREAD_LOCAL),
                         std::memory_order_relaxed);
  ProfiledThread::release();
  return nullptr;
}

TEST(ThreadTeardownSafetyTest, NativeMemThreadLocalBalancesOnRelease) {
  long long base = NativeMem::live(NM_THREAD_LOCAL);
  pthread_t t;
  ASSERT_EQ(0, pthread_create(&t, nullptr, tl_release_body, nullptr));
  pthread_join(t, nullptr);
  EXPECT_GT(g_tl_live_during.load(std::memory_order_relaxed), base)
      << "forTid() must account the ProfiledThread allocation";
  EXPECT_EQ(base, NativeMem::live(NM_THREAD_LOCAL))
      << "release() -> clear() -> freeValue() must balance the accounting";
}

static void *tl_exit_body(void *) {
  ProfiledThread::initCurrentThread();
  return nullptr;  // no explicit release: thread exit runs freeValue()
}

TEST(ThreadTeardownSafetyTest, NativeMemThreadLocalReleasedOnThreadExit) {
  long long base = NativeMem::live(NM_THREAD_LOCAL);
  pthread_t t;
  ASSERT_EQ(0, pthread_create(&t, nullptr, tl_exit_body, nullptr));
  pthread_join(t, nullptr);
  EXPECT_EQ(base, NativeMem::live(NM_THREAD_LOCAL))
      << "pthread-key destructor (freeValue) must balance the accounting";
}

#endif // __linux__
