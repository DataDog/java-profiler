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
 *                   skips rt_sigprocmask syscalls.
 *   SLOW_PATH     — prev handler has a non-empty sa_mask AND
 *                   DDPROF_FORWARD_APPLY_SIGMASK=1 is set (opt-in).
 *                   forwardForeignSignal applies SIG_BLOCK / SIG_SETMASK
 *                   (two syscalls).
 *
 * The delta between BASELINE and FAST_PATH is the overhead per foreign
 * signal when sa_mask chaining is disabled (the default). The delta between
 * FAST_PATH and SLOW_PATH is the cost of the two rt_sigprocmask syscalls.
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
#include <string>

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
        // slow path (non-empty sa_mask → rt_sigprocmask block + restore).
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

// Snapshot/restore an env var — same pattern as signalOrigin_ut.cpp, so the
// developer's own shell exports survive a test run.
class EnvGuard {
public:
    explicit EnvGuard(const char* name)
        : _name(name), _had_value(false) {
        const char* v = getenv(name);
        if (v != nullptr) { _had_value = true; _saved = v; }
    }
    void reset() const {
        if (_had_value) setenv(_name, _saved.c_str(), 1);
        else            unsetenv(_name);
    }
private:
    const char* _name;
    bool _had_value;
    std::string _saved;
};

// Optimization barrier — prevents the compiler from hoisting /
// constant-folding loop-invariant calls out of the measurement loop. A
// simple `volatile bool sink` forces the STORE but not necessarily the CALL;
// asm volatile with a read-write constraint makes the value `observable` at
// every iteration so the compiler must re-emit the load path.
inline void doNotOptimize(bool& v) {
    asm volatile("" : "+r"(v) : : "memory");
}

}  // namespace

class SignalOriginBench : public ::testing::Test {
protected:
    struct sigaction saved_action;
    EnvGuard _guard_mask{"DDPROF_FORWARD_APPLY_SIGMASK"};
    EnvGuard _guard_origin{"DDPROF_SIGNAL_ORIGIN_CHECK"};

    void SetUp() override {
        if (!benchEnabled()) {
            GTEST_SKIP() << "Set BENCH_SIGNAL_ORIGIN=1 to run the benchmark";
        }
        memset(&saved_action, 0, sizeof(saved_action));
        // Default prime — slow-path tests below override and re-prime.
        unsetenv("DDPROF_FORWARD_APPLY_SIGMASK");
        unsetenv("DDPROF_SIGNAL_ORIGIN_CHECK");
        OS::primeSignalOriginCheck(/*forceReload=*/true);
        OS::resetSignalHandlersForTesting();
    }

    void TearDown() override {
        OS::resetSignalHandlersForTesting();
        if (saved_action.sa_handler != nullptr || saved_action.sa_sigaction != nullptr) {
            sigaction(kBenchSignal, &saved_action, nullptr);
        }
        _guard_mask.reset();
        _guard_origin.reset();
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

// -------- FAST PATH: classifier rejects SI_TKILL from raise(), forwards --------

static void classifierHandler(int signo, siginfo_t* siginfo, void* ucontext) {
    if (!OS::shouldProcessSignal(siginfo, SI_TIMER, SignalCookie::cpu())) {
        OS::forwardForeignSignal(signo, siginfo, ucontext);
        return;
    }
    // Unreachable in this benchmark — raise() produces si_code=SI_TKILL on
    // Linux (glibc raise() uses tgkill internally), never SI_TIMER.
}

TEST_F(SignalOriginBench, FastPath_ClassifierPlusEmptyMaskForward) {
    // Pre-install the foreign handler so OS::installSignalHandler captures it
    // as the oldaction to chain to.
    ASSERT_EQ(0, setupForeignHandler(kBenchSignal, /*with_mask=*/false, &saved_action));

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
    // forwardForeignSignal has to invoke two rt_sigprocmask syscalls.
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
// Calls OS::shouldProcessSignal + OS::forwardForeignSignal directly with a
// fabricated siginfo_t, measuring only the in-process overhead of the
// origin-check machinery. This isolates the cost we actually added — the
// scenarios above include a constant ~300 ns per iteration for the kernel
// signal-delivery path that is common to ALL three end-to-end variants.
//
// All measurement loops pass the `sink` through `doNotOptimize()` so the
// compiler is forced to re-emit the call on every iteration instead of
// CSE-ing a loop-invariant result.
// NOTE: This file is compiled at -O0 in the test build, so reported ns/call
// include function-call overhead for SignalCookie::cpu() and shouldProcessSignal
// that disappears at -O2 in production (both inline to 3-4 instructions).
// Production overhead is substantially lower than the figures printed here.

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
    bool sink = false;

    // Warm up.
    for (int i = 0; i < 10000; ++i) {
        sink = OS::shouldProcessSignal(&si, SI_TIMER, SignalCookie::cpu());
        doNotOptimize(sink);
    }

    uint64_t start = nanosNow();
    for (int i = 0; i < kPureIterations; ++i) {
        sink = OS::shouldProcessSignal(&si, SI_TIMER, SignalCookie::cpu());
        doNotOptimize(sink);
    }
    uint64_t end = nanosNow();
    double ns = (double)(end - start) / (double)kPureIterations;

    std::printf("\n  [pure_classifier_reject] %.2f ns/call  (iters=%d)\n",
                ns, kPureIterations);
}

TEST_F(SignalOriginBench, Pure_ClassifierAccept) {
    siginfo_t si = makeOwnSiginfo();
    bool sink = false;

    for (int i = 0; i < 10000; ++i) {
        sink = OS::shouldProcessSignal(&si, SI_TIMER, SignalCookie::cpu());
        doNotOptimize(sink);
    }

    uint64_t start = nanosNow();
    for (int i = 0; i < kPureIterations; ++i) {
        sink = OS::shouldProcessSignal(&si, SI_TIMER, SignalCookie::cpu());
        doNotOptimize(sink);
    }
    uint64_t end = nanosNow();
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
    // Non-empty mask → rt_sigprocmask twice per call.
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
