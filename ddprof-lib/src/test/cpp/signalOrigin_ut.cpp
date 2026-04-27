/*
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <atomic>
#include <cstdlib>
#include <ctime>
#include <string>

#include "os.h"
#include "signalCookie.h"

#ifdef __linux__

/**
 * Unit tests for the signal-origin validation helpers:
 *   OS::shouldProcessSignal(siginfo, expected_si_code, expected_cookie)
 *   OS::sendSignalWithCookie(tid, signo, cookie)
 *   OS::forwardForeignSignal(signo, siginfo, ucontext)
 *   OS::primeSignalOriginCheck(forceReload)
 *   OS::signalOriginCheckEnabled()
 *
 * These do not rely on timer_create or the full engine — they build siginfo_t
 * fakes directly and exercise the classifier / forwarder in isolation.
 */

namespace {

// Snapshot an env var's value at SetUp and restore it at TearDown, so a
// developer who exported DDPROF_* in their shell to reproduce an issue does
// not have their environment wiped by running the test binary.
class EnvGuard {
public:
    explicit EnvGuard(const char* name)
        : _name(name), _had_value(false) {
        const char* v = getenv(name);
        if (v != nullptr) {
            _had_value = true;
            _saved = v;
        }
    }
    void reset() const {
        if (_had_value) {
            setenv(_name, _saved.c_str(), /*overwrite=*/1);
        } else {
            unsetenv(_name);
        }
    }
private:
    const char* _name;
    bool _had_value;
    std::string _saved;
};

}  // namespace

class SignalOriginTest : public ::testing::Test {
protected:
    // Snapshot/restore env vars the tests mutate so the developer's shell
    // exports survive a test run.
    EnvGuard _guard_origin{"DDPROF_SIGNAL_ORIGIN_CHECK"};
    EnvGuard _guard_mask{"DDPROF_FORWARD_APPLY_SIGMASK"};

    void SetUp() override {
        // Default: origin check enabled, sigmask chain disabled.
        unsetenv("DDPROF_SIGNAL_ORIGIN_CHECK");
        unsetenv("DDPROF_FORWARD_APPLY_SIGMASK");
        OS::primeSignalOriginCheck(/*forceReload=*/true);

        // Wipe any installed_oldaction state from previous tests so chaining
        // invariants can be observed in isolation.
        OS::resetSignalHandlersForTesting();
    }

    void TearDown() override {
        OS::resetSignalHandlersForTesting();
        _guard_origin.reset();
        _guard_mask.reset();
        OS::primeSignalOriginCheck(/*forceReload=*/true);
    }

    static siginfo_t makeSiginfo(int code, void* sival) {
        siginfo_t si;
        memset(&si, 0, sizeof(si));
        si.si_code = code;
        si.si_value.sival_ptr = sival;
        return si;
    }
};

TEST_F(SignalOriginTest, AcceptsMatchingCookieAndSiCode) {
    siginfo_t si = makeSiginfo(SI_TIMER, SignalCookie::cpu());
    EXPECT_TRUE(OS::shouldProcessSignal(&si, SI_TIMER, SignalCookie::cpu()));
}

TEST_F(SignalOriginTest, RejectsMismatchedSiCode) {
    siginfo_t si = makeSiginfo(SI_USER, SignalCookie::cpu());
    EXPECT_FALSE(OS::shouldProcessSignal(&si, SI_TIMER, SignalCookie::cpu()));
}

TEST_F(SignalOriginTest, RejectsMismatchedCookie) {
    siginfo_t si = makeSiginfo(SI_TIMER, /*foreign=*/(void*)0xF00D);
    EXPECT_FALSE(OS::shouldProcessSignal(&si, SI_TIMER, SignalCookie::cpu()));
}

TEST_F(SignalOriginTest, RejectsNullSiginfo) {
    EXPECT_FALSE(OS::shouldProcessSignal(nullptr, SI_TIMER, SignalCookie::cpu()));
}

TEST_F(SignalOriginTest, WallclockCookieDistinctFromCpu) {
    EXPECT_NE(SignalCookie::cpu(), SignalCookie::wallclock());
    siginfo_t si = makeSiginfo(SI_QUEUE, SignalCookie::cpu());
    // CPU cookie with SI_QUEUE / wallclock cookie must not be accepted.
    EXPECT_FALSE(OS::shouldProcessSignal(&si, SI_QUEUE, SignalCookie::wallclock()));
}

TEST_F(SignalOriginTest, FeatureFlagDisableAcceptsEverything) {
    setenv("DDPROF_SIGNAL_ORIGIN_CHECK", "false", /*overwrite=*/1);
    OS::primeSignalOriginCheck(/*forceReload=*/true);
    EXPECT_FALSE(OS::signalOriginCheckEnabled());

    // Any siginfo should be accepted when the flag is off.
    siginfo_t si = makeSiginfo(SI_USER, (void*)0xBADBAD);
    EXPECT_TRUE(OS::shouldProcessSignal(&si, SI_TIMER, SignalCookie::cpu()));
}

TEST_F(SignalOriginTest, FeatureFlagAcceptsCommonDisableSpellings) {
    for (const char* v : {"false", "0", "off", "no", "OFF", "No"}) {
        setenv("DDPROF_SIGNAL_ORIGIN_CHECK", v, 1);
        OS::primeSignalOriginCheck(/*forceReload=*/true);
        EXPECT_FALSE(OS::signalOriginCheckEnabled()) << "for value " << v;
    }
}

TEST_F(SignalOriginTest, FeatureFlagAcceptsCommonEnableSpellings) {
    for (const char* v : {"true", "1", "on", "yes", "ON", "Yes"}) {
        setenv("DDPROF_SIGNAL_ORIGIN_CHECK", v, 1);
        OS::primeSignalOriginCheck(/*forceReload=*/true);
        EXPECT_TRUE(OS::signalOriginCheckEnabled()) << "for value " << v;
    }
}

TEST_F(SignalOriginTest, FeatureFlagDefaultOn) {
    unsetenv("DDPROF_SIGNAL_ORIGIN_CHECK");
    OS::primeSignalOriginCheck(/*forceReload=*/true);
    EXPECT_TRUE(OS::signalOriginCheckEnabled());
}

TEST_F(SignalOriginTest, FeatureFlagUnknownValueKeepsDefault) {
    // Unknown values should not disable the origin check (default ON).
    // A warning is emitted via Log::warn — not asserted here, just sanity.
    for (const char* v : {"disable", "maybe", "2", "  "}) {
        setenv("DDPROF_SIGNAL_ORIGIN_CHECK", v, 1);
        OS::primeSignalOriginCheck(/*forceReload=*/true);
        EXPECT_TRUE(OS::signalOriginCheckEnabled())
            << "unknown value " << v << " should keep default";
    }
}

// -------- sendSignalWithCookie + receive on SIGUSR2 --------

static std::atomic<int> g_received_si_code{0};
static std::atomic<void*> g_received_sival{nullptr};

static void captureHandler(int /*signo*/, siginfo_t* si, void* /*uc*/) {
    g_received_si_code.store(si != nullptr ? si->si_code : 0);
    g_received_sival.store(si != nullptr ? si->si_value.sival_ptr : nullptr);
}

TEST_F(SignalOriginTest, QueueSignalDeliversCookieAndSiCode) {
    struct sigaction prev;
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = captureHandler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    ASSERT_EQ(0, sigaction(SIGUSR2, &sa, &prev));

    g_received_si_code.store(0);
    g_received_sival.store(nullptr);

    // Block SIGUSR2 so the pending signal is delivered deterministically
    // when we unblock — avoids a racy spin-wait and guarantees the handler
    // has run before the EXPECT checks below.
    sigset_t block_mask, old_mask;
    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGUSR2);
    ASSERT_EQ(0, pthread_sigmask(SIG_BLOCK, &block_mask, &old_mask));

    void* cookie = (void*)0xCAFEBABE;
    ASSERT_TRUE(OS::sendSignalWithCookie(OS::threadId(), SIGUSR2, cookie));

    // Restoring the old mask unblocks SIGUSR2; the kernel delivers the pending
    // signal before pthread_sigmask returns.
    ASSERT_EQ(0, pthread_sigmask(SIG_SETMASK, &old_mask, nullptr));

    EXPECT_EQ(SI_QUEUE, g_received_si_code.load());
    EXPECT_EQ(cookie, g_received_sival.load());

    sigaction(SIGUSR2, &prev, nullptr);
}

// -------- forwardForeignSignal chains to previous handler --------

static std::atomic<int> g_chained_calls{0};

static void chainedHandler(int /*signo*/, siginfo_t* /*si*/, void* /*uc*/) {
    g_chained_calls.fetch_add(1);
}

static void secondChainedHandler(int /*signo*/, siginfo_t* /*si*/, void* /*uc*/) {
    // Distinct from chainedHandler so installSignalHandler will not detect
    // this as a self-install on a second call.
    g_chained_calls.fetch_add(100);
}

TEST_F(SignalOriginTest, ForwardForeignSignalChainsToPrevious) {
    // Install a "previous" handler on SIGUSR1 using raw sigaction (not via
    // OS::installSignalHandler — we want this to be the "pre-existing" state).
    struct sigaction saved;
    struct sigaction prev_action;
    memset(&prev_action, 0, sizeof(prev_action));
    prev_action.sa_sigaction = chainedHandler;
    prev_action.sa_flags = SA_SIGINFO;
    sigemptyset(&prev_action.sa_mask);
    ASSERT_EQ(0, sigaction(SIGUSR1, &prev_action, &saved));

    // Now install OUR handler via OS::installSignalHandler — this should
    // capture the previous action for forwarding.
    OS::installSignalHandler(SIGUSR1, captureHandler);

    g_chained_calls.store(0);

    // Build a fake siginfo and call forwardForeignSignal directly.
    siginfo_t si = makeSiginfo(SI_USER, (void*)0);
    si.si_signo = SIGUSR1;
    OS::forwardForeignSignal(SIGUSR1, &si, nullptr);

    EXPECT_EQ(1, g_chained_calls.load());

    sigaction(SIGUSR1, &saved, nullptr);
}

TEST_F(SignalOriginTest, ForwardForeignSignalSilentOnUninstalledSignal) {
    // No previous handler has been captured for SIGUSR2 by OS::installSignalHandler.
    // forwardForeignSignal should be a no-op rather than crash.
    siginfo_t si = makeSiginfo(SI_USER, (void*)0);
    OS::forwardForeignSignal(SIGUSR2, &si, nullptr);
    SUCCEED();
}

// -------- store-exactly-once invariant --------
//
// Regression test for the "installed_oldaction is captured once, never
// overwritten" invariant. If a foreign library installs its handler over
// ours after profiler start, and the profiler then re-installs (restart),
// the captured prev must still be the ORIGINAL handler, not the foreign
// one that briefly owned the slot.

TEST_F(SignalOriginTest, ReinstallPreservesFirstCapturedPrev) {
    struct sigaction saved;
    sigaction(SIGUSR1, nullptr, &saved);

    // Install the "original" (e.g. JVM-like) handler.
    struct sigaction original;
    memset(&original, 0, sizeof(original));
    original.sa_sigaction = chainedHandler;
    original.sa_flags = SA_SIGINFO;
    sigemptyset(&original.sa_mask);
    ASSERT_EQ(0, sigaction(SIGUSR1, &original, nullptr));

    // First profiler install — captures original as prev.
    OS::installSignalHandler(SIGUSR1, captureHandler);

    // A foreign library sneaks in and overwrites our handler.
    struct sigaction foreign;
    memset(&foreign, 0, sizeof(foreign));
    foreign.sa_sigaction = secondChainedHandler;
    foreign.sa_flags = SA_SIGINFO;
    sigemptyset(&foreign.sa_mask);
    ASSERT_EQ(0, sigaction(SIGUSR1, &foreign, nullptr));

    // Profiler re-installs (simulates restart). Before the fix, this would
    // have overwritten our captured prev with `foreign` — losing the
    // original chain target. With store-exactly-once, the original is kept.
    OS::installSignalHandler(SIGUSR1, captureHandler);

    g_chained_calls.store(0);
    siginfo_t si = makeSiginfo(SI_USER, (void*)0);
    si.si_signo = SIGUSR1;
    OS::forwardForeignSignal(SIGUSR1, &si, nullptr);

    // Expect the ORIGINAL chainedHandler (+1), not secondChainedHandler (+100).
    EXPECT_EQ(1, g_chained_calls.load())
        << "forwardForeignSignal chained to the wrong handler — "
           "store-exactly-once invariant violated";

    sigaction(SIGUSR1, &saved, nullptr);
}

// -------- resetSignalHandlersForTesting clears oldaction state --------

TEST_F(SignalOriginTest, ResetForTestingClearsOldactionCache) {
    struct sigaction saved;
    struct sigaction prev_action;
    memset(&prev_action, 0, sizeof(prev_action));
    prev_action.sa_sigaction = chainedHandler;
    prev_action.sa_flags = SA_SIGINFO;
    sigemptyset(&prev_action.sa_mask);
    ASSERT_EQ(0, sigaction(SIGUSR1, &prev_action, &saved));

    OS::installSignalHandler(SIGUSR1, captureHandler);

    // Confirm chaining is armed.
    g_chained_calls.store(0);
    siginfo_t si = makeSiginfo(SI_USER, (void*)0);
    si.si_signo = SIGUSR1;
    OS::forwardForeignSignal(SIGUSR1, &si, nullptr);
    EXPECT_EQ(1, g_chained_calls.load());

    // Reset and confirm the chain is cleared (forward becomes a no-op).
    OS::resetSignalHandlersForTesting();
    g_chained_calls.store(0);
    OS::forwardForeignSignal(SIGUSR1, &si, nullptr);
    EXPECT_EQ(0, g_chained_calls.load())
        << "resetSignalHandlersForTesting did not clear installed_oldaction state";

    sigaction(SIGUSR1, &saved, nullptr);
}

TEST_F(SignalOriginTest, ForwardAppliesSigmaskWhenEnabled) {
    // Verify that the slow path (DDPROF_FORWARD_APPLY_SIGMASK=1) still
    // chains to the previous SA_SIGINFO handler correctly.
    EnvGuard guard_mask("DDPROF_FORWARD_APPLY_SIGMASK");
    setenv("DDPROF_FORWARD_APPLY_SIGMASK", "1", /*overwrite=*/1);
    OS::primeSignalOriginCheck(/*forceReload=*/true);

    // Install a previous handler with a non-empty sa_mask.
    struct sigaction prev_sa, saved;
    memset(&prev_sa, 0, sizeof(prev_sa));
    prev_sa.sa_sigaction = chainedHandler;
    prev_sa.sa_flags = SA_SIGINFO;
    sigemptyset(&prev_sa.sa_mask);
    sigaddset(&prev_sa.sa_mask, SIGUSR1);  // non-empty sa_mask
    ASSERT_EQ(0, sigaction(SIGUSR1, &prev_sa, &saved));

    OS::installSignalHandler(SIGUSR1, captureHandler);

    g_chained_calls.store(0);
    siginfo_t si = makeSiginfo(SI_USER, (void*)0);
    si.si_signo = SIGUSR1;
    OS::forwardForeignSignal(SIGUSR1, &si, nullptr);

    EXPECT_EQ(1, g_chained_calls.load())
        << "forwardForeignSignal with DDPROF_FORWARD_APPLY_SIGMASK=1 did not chain";

    sigaction(SIGUSR1, &saved, nullptr);
    guard_mask.reset();
    OS::primeSignalOriginCheck(/*forceReload=*/true);
}

#endif  // __linux__
