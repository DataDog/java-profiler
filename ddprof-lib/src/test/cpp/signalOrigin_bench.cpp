/*
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 *
 * Microbenchmark for foreign-signal forwarding overhead.
 *
 * Quantifies the per-signal cost added by the origin-validation gate when
 * the kernel delivers a signal that does NOT carry our cookie (so the
 * handler rejects it, increments CTIMER_SIGNAL_FOREIGN, and chains via
 * forwardForeignSignal).
 *
 * Three scenarios are measured:
 *   BASELINE      — only the "foreign" handler is installed; raise() goes
 *                   straight to it. Measures the signal-delivery baseline.
 *   FAST_PATH     — our classifier is installed on top; prev handler has
 *                   an empty sa_mask (common case). forwardForeignSignal
 *                   short-circuits pthread_sigmask.
 *   SLOW_PATH     — prev handler has a non-empty sa_mask; forwardForeignSignal
 *                   applies SIG_BLOCK / SIG_SETMASK (two syscalls).
 *
 * The delta between BASELINE and FAST_PATH is the overhead per foreign
 * signal when sa_mask chaining is not needed. The delta between FAST_PATH
 * and SLOW_PATH is the cost of the two pthread_sigmask calls.
 *
 * The benchmark runs only when the env var BENCH_SIGNAL_ORIGIN is set, so
 * normal CI does not pay for it.
 */

#include <gtest/gtest.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <atomic>
#include <cstdio>
#include <cstdlib>

#include "os.h"
#include "signalCookie.h"

#ifdef __linux__

namespace {

// "Foreign" handler — the target of forwardForeignSignal. Kept as lean as
// possible so the timing reflects the forwarding-path cost, not the prev
// handler's own work.
std::atomic<uint64_t> g_prev_calls{0};

void noopForeignHandler(int /*signo*/, siginfo_t* /*si*/, void* /*uc*/) {
    g_prev_calls.fetch_add(1, std::memory_order_relaxed);
}

int setupForeignHandler(int signo, bool with_mask, struct sigaction* saved_out) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = noopForeignHandler;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if (with_mask) {
        // Populate with a few signals to force forwardForeignSignal onto the
        // slow path (non-empty sa_mask → pthread_sigmask block + restore).
        sigaddset(&sa.sa_mask, SIGUSR2);
        sigaddset(&sa.sa_mask, SIGALRM);
        sigaddset(&sa.sa_mask, SIGCHLD);
    }
    return sigaction(signo, &sa, saved_out);
}

uint64_t nanosNow() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

struct Result {
    double ns_per_signal;
    uint64_t iterations;
    uint64_t prev_calls;
};

Result measure(int iters, int signo) {
    g_prev_calls.store(0);
    uint64_t start = nanosNow();
    for (int i = 0; i < iters; ++i) {
        raise(signo);
    }
    uint64_t end = nanosNow();
    return {
        (double)(end - start) / (double)iters,
        (uint64_t)iters,
        g_prev_calls.load()
    };
}

const int kIterations = 500000;
const int kBenchSignal = SIGUSR1;

bool benchEnabled() {
    const char* v = getenv("BENCH_SIGNAL_ORIGIN");
    return v != nullptr && v[0] != '\0' && strcmp(v, "0") != 0;
}

}  // namespace

class SignalOriginBench : public ::testing::Test {
protected:
    struct sigaction saved_action;

    void SetUp() override {
        if (!benchEnabled()) {
            GTEST_SKIP() << "Set BENCH_SIGNAL_ORIGIN=1 to run the benchmark";
        }
        memset(&saved_action, 0, sizeof(saved_action));
        // Default prime — slow-path tests below override and re-prime.
        unsetenv("DDPROF_FORWARD_APPLY_SIGMASK");
        OS::primeSignalOriginCheck(/*forceReload=*/true);
    }

    void TearDown() override {
        if (saved_action.sa_handler != nullptr || saved_action.sa_sigaction != nullptr) {
            sigaction(kBenchSignal, &saved_action, nullptr);
        }
        unsetenv("DDPROF_FORWARD_APPLY_SIGMASK");
        OS::primeSignalOriginCheck(/*forceReload=*/true);
    }

    // Enable sa_mask-respecting chain for the slow-path benchmark variants.
    void enableSigmaskChain() {
        setenv("DDPROF_FORWARD_APPLY_SIGMASK", "1", 1);
        OS::primeSignalOriginCheck(/*forceReload=*/true);
    }
};

// -------- BASELINE: just the foreign handler, no ddprof classifier --------

TEST_F(SignalOriginBench, Baseline_NoClassifier) {
    ASSERT_EQ(0, setupForeignHandler(kBenchSignal, /*with_mask=*/false, &saved_action));

    // Warm up.
    for (int i = 0; i < 1000; ++i) raise(kBenchSignal);

    Result r = measure(kIterations, kBenchSignal);
    EXPECT_EQ((uint64_t)kIterations, r.prev_calls);

    std::printf("\n  [BASELINE]        %.1f ns/signal  (iters=%llu prev_calls=%llu)\n",
                r.ns_per_signal,
                (unsigned long long)r.iterations,
                (unsigned long long)r.prev_calls);
}

// -------- FAST PATH: classifier rejects SI_USER, forwards to empty-mask prev --------

static void classifierHandler(int signo, siginfo_t* siginfo, void* ucontext) {
    if (!OS::isOwnSignal(siginfo, SI_TIMER, SignalCookie::cpu())) {
        OS::forwardForeignSignal(signo, siginfo, ucontext);
        return;
    }
    // Unreachable in this benchmark — raise() always produces SI_USER.
}

TEST_F(SignalOriginBench, FastPath_ClassifierPlusEmptyMaskForward) {
    // Pre-install the foreign handler so OS::installSignalHandler captures it
    // as the oldaction to chain to.
    struct sigaction foreign_sa;
    ASSERT_EQ(0, setupForeignHandler(kBenchSignal, /*with_mask=*/false, &saved_action));
    sigaction(kBenchSignal, nullptr, &foreign_sa);  // query current

    OS::installSignalHandler(kBenchSignal, classifierHandler);

    for (int i = 0; i < 1000; ++i) raise(kBenchSignal);

    Result r = measure(kIterations, kBenchSignal);
    EXPECT_EQ((uint64_t)kIterations, r.prev_calls) << "forwardForeignSignal did not chain";

    std::printf("\n  [FAST_PATH]       %.1f ns/signal  (iters=%llu prev_calls=%llu)\n",
                r.ns_per_signal,
                (unsigned long long)r.iterations,
                (unsigned long long)r.prev_calls);
}

// -------- SLOW PATH: classifier rejects, prev handler has non-empty sa_mask --------

TEST_F(SignalOriginBench, SlowPath_ClassifierPlusMaskedForward) {
    // Slow-path chain is opt-in behind DDPROF_FORWARD_APPLY_SIGMASK.
    enableSigmaskChain();
    // Install a "foreign" handler with a non-empty sa_mask so
    // forwardForeignSignal has to call pthread_sigmask twice.
    ASSERT_EQ(0, setupForeignHandler(kBenchSignal, /*with_mask=*/true, &saved_action));

    OS::installSignalHandler(kBenchSignal, classifierHandler);

    for (int i = 0; i < 1000; ++i) raise(kBenchSignal);

    Result r = measure(kIterations, kBenchSignal);
    EXPECT_EQ((uint64_t)kIterations, r.prev_calls);

    std::printf("\n  [SLOW_PATH]       %.1f ns/signal  (iters=%llu prev_calls=%llu)\n",
                r.ns_per_signal,
                (unsigned long long)r.iterations,
                (unsigned long long)r.prev_calls);
}

// -------- PURE FUNCTION CALL: no kernel, no signal delivery --------
//
// Calls OS::isOwnSignal + OS::forwardForeignSignal directly with a fabricated
// siginfo_t, measuring only the in-process overhead of the origin-check
// machinery. This isolates the cost we actually added — the scenarios above
// include a constant ~300 ns per iteration for the kernel signal-delivery
// path that is common to ALL three end-to-end variants.
//
// Three variants:
//   pure_classifier_reject     — isOwnSignal returns false (SI_USER)
//   pure_classifier_accept     — isOwnSignal returns true  (SI_TIMER + cookie)
//   pure_forward_fast_path     — forwardForeignSignal with empty-mask prev
//   pure_forward_slow_path     — forwardForeignSignal with non-empty-mask prev
//
// The prev handler is a no-op that increments a counter, so timings for the
// forward variants include the prev-call itself (one indirect call + an
// atomic increment).

static const int kPureBenchSignal = SIGUSR1;
static const int kPureIterations  = 5000000;  // more iters — fast path is ~ns

namespace {

siginfo_t makeForeignSiginfo() {
    siginfo_t si;
    memset(&si, 0, sizeof(si));
    si.si_signo = kPureBenchSignal;
    si.si_code  = SI_USER;   // not SI_TIMER → classifier rejects
    return si;
}

siginfo_t makeOwnSiginfo() {
    siginfo_t si;
    memset(&si, 0, sizeof(si));
    si.si_signo = kPureBenchSignal;
    si.si_code  = SI_TIMER;
    si.si_value.sival_ptr = SignalCookie::cpu();
    return si;
}

}  // namespace

TEST_F(SignalOriginBench, Pure_ClassifierReject) {
    siginfo_t si = makeForeignSiginfo();
    volatile bool sink = false;

    // Warm up.
    for (int i = 0; i < 10000; ++i) {
        sink = OS::isOwnSignal(&si, SI_TIMER, SignalCookie::cpu());
    }

    uint64_t start = nanosNow();
    for (int i = 0; i < kPureIterations; ++i) {
        sink = OS::isOwnSignal(&si, SI_TIMER, SignalCookie::cpu());
    }
    uint64_t end = nanosNow();
    (void)sink;
    double ns = (double)(end - start) / (double)kPureIterations;

    std::printf("\n  [pure_classifier_reject] %.2f ns/call  (iters=%d)\n",
                ns, kPureIterations);
}

TEST_F(SignalOriginBench, Pure_ClassifierAccept) {
    siginfo_t si = makeOwnSiginfo();
    volatile bool sink = false;

    for (int i = 0; i < 10000; ++i) {
        sink = OS::isOwnSignal(&si, SI_TIMER, SignalCookie::cpu());
    }

    uint64_t start = nanosNow();
    for (int i = 0; i < kPureIterations; ++i) {
        sink = OS::isOwnSignal(&si, SI_TIMER, SignalCookie::cpu());
    }
    uint64_t end = nanosNow();
    (void)sink;
    double ns = (double)(end - start) / (double)kPureIterations;

    std::printf("\n  [pure_classifier_accept] %.2f ns/call  (iters=%d)\n",
                ns, kPureIterations);
}

TEST_F(SignalOriginBench, Pure_ForwardFastPath) {
    // Install an empty-mask foreign handler so forwardForeignSignal captures
    // it as the oldaction via OS::installSignalHandler.
    ASSERT_EQ(0, setupForeignHandler(kPureBenchSignal, /*with_mask=*/false, &saved_action));
    OS::installSignalHandler(kPureBenchSignal, classifierHandler);

    siginfo_t si = makeForeignSiginfo();
    g_prev_calls.store(0);

    for (int i = 0; i < 10000; ++i) {
        OS::forwardForeignSignal(kPureBenchSignal, &si, nullptr);
    }

    uint64_t start = nanosNow();
    for (int i = 0; i < kPureIterations; ++i) {
        OS::forwardForeignSignal(kPureBenchSignal, &si, nullptr);
    }
    uint64_t end = nanosNow();
    double ns = (double)(end - start) / (double)kPureIterations;
    uint64_t chained = g_prev_calls.load();

    std::printf("\n  [pure_forward_fast]      %.2f ns/call  (iters=%d chained=%llu)\n",
                ns, kPureIterations, (unsigned long long)chained);
    EXPECT_GE(chained, (uint64_t)kPureIterations);
}

TEST_F(SignalOriginBench, Pure_ForwardSlowPath) {
    enableSigmaskChain();
    // Non-empty mask → pthread_sigmask twice per call.
    ASSERT_EQ(0, setupForeignHandler(kPureBenchSignal, /*with_mask=*/true, &saved_action));
    OS::installSignalHandler(kPureBenchSignal, classifierHandler);

    siginfo_t si = makeForeignSiginfo();
    g_prev_calls.store(0);

    for (int i = 0; i < 10000; ++i) {
        OS::forwardForeignSignal(kPureBenchSignal, &si, nullptr);
    }

    // Fewer iterations — this path has 2 syscalls per call.
    const int slow_iters = kPureIterations / 10;
    uint64_t start = nanosNow();
    for (int i = 0; i < slow_iters; ++i) {
        OS::forwardForeignSignal(kPureBenchSignal, &si, nullptr);
    }
    uint64_t end = nanosNow();
    double ns = (double)(end - start) / (double)slow_iters;
    uint64_t chained = g_prev_calls.load();

    std::printf("\n  [pure_forward_slow]      %.2f ns/call  (iters=%d chained=%llu)\n",
                ns, slow_iters, (unsigned long long)chained);
    EXPECT_GE(chained, (uint64_t)slow_iters);
}

#endif  // __linux__
