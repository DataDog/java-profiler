/*
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <signal.h>
#include <string.h>
#include <atomic>

#include "os.h"
#include "signalCookie.h"

#ifdef __linux__

/**
 * Unit tests for the signal-origin validation helpers:
 *   OS::isOwnSignal(siginfo, expected_si_code, expected_cookie)
 *   OS::queueSignalToThread(tid, signo, cookie)
 *   OS::forwardForeignSignal(signo, siginfo, ucontext)
 *   OS::primeSignalOriginCheck(forceReload)
 *   OS::signalOriginCheckEnabled()
 *
 * These do not rely on timer_create or the full engine — they build siginfo_t
 * fakes directly and exercise the classifier / forwarder in isolation.
 */

class SignalOriginTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Default: origin check enabled.
        unsetenv("DDPROF_SIGNAL_ORIGIN_CHECK");
        OS::primeSignalOriginCheck(/*forceReload=*/true);
    }

    void TearDown() override {
        unsetenv("DDPROF_SIGNAL_ORIGIN_CHECK");
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
    EXPECT_TRUE(OS::isOwnSignal(&si, SI_TIMER, SignalCookie::cpu()));
}

TEST_F(SignalOriginTest, RejectsMismatchedSiCode) {
    siginfo_t si = makeSiginfo(SI_USER, SignalCookie::cpu());
    EXPECT_FALSE(OS::isOwnSignal(&si, SI_TIMER, SignalCookie::cpu()));
}

TEST_F(SignalOriginTest, RejectsMismatchedCookie) {
    siginfo_t si = makeSiginfo(SI_TIMER, /*foreign=*/(void*)0xF00D);
    EXPECT_FALSE(OS::isOwnSignal(&si, SI_TIMER, SignalCookie::cpu()));
}

TEST_F(SignalOriginTest, RejectsNullSiginfo) {
    EXPECT_FALSE(OS::isOwnSignal(nullptr, SI_TIMER, SignalCookie::cpu()));
}

TEST_F(SignalOriginTest, WallclockCookieDistinctFromCpu) {
    EXPECT_NE(SignalCookie::cpu(), SignalCookie::wallclock());
    siginfo_t si = makeSiginfo(SI_QUEUE, SignalCookie::cpu());
    // CPU cookie with SI_QUEUE / wallclock cookie must not be accepted.
    EXPECT_FALSE(OS::isOwnSignal(&si, SI_QUEUE, SignalCookie::wallclock()));
}

TEST_F(SignalOriginTest, FeatureFlagDisableAcceptsEverything) {
    setenv("DDPROF_SIGNAL_ORIGIN_CHECK", "false", /*overwrite=*/1);
    OS::primeSignalOriginCheck(/*forceReload=*/true);
    EXPECT_FALSE(OS::signalOriginCheckEnabled());

    // Any siginfo should be accepted when the flag is off.
    siginfo_t si = makeSiginfo(SI_USER, (void*)0xBADBAD);
    EXPECT_TRUE(OS::isOwnSignal(&si, SI_TIMER, SignalCookie::cpu()));
}

TEST_F(SignalOriginTest, FeatureFlagAcceptsCommonDisableSpellings) {
    for (const char* v : {"false", "0", "off", "no", "OFF", "No"}) {
        setenv("DDPROF_SIGNAL_ORIGIN_CHECK", v, 1);
        OS::primeSignalOriginCheck(/*forceReload=*/true);
        EXPECT_FALSE(OS::signalOriginCheckEnabled()) << "for value " << v;
    }
}

TEST_F(SignalOriginTest, FeatureFlagDefaultOn) {
    unsetenv("DDPROF_SIGNAL_ORIGIN_CHECK");
    OS::primeSignalOriginCheck(/*forceReload=*/true);
    EXPECT_TRUE(OS::signalOriginCheckEnabled());
}

// -------- queueSignalToThread + receive on SIGUSR2 --------

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

    void* cookie = (void*)0xCAFEBABE;
    ASSERT_TRUE(OS::queueSignalToThread(OS::threadId(), SIGUSR2, cookie));

    // Give the signal a moment to be delivered (the delivery happens on
    // return from the syscall — usleep ensures the handler has completed).
    for (int i = 0; i < 100 && g_received_si_code.load() == 0; ++i) {
        struct timespec ts{0, 1000000}; // 1ms
        nanosleep(&ts, nullptr);
    }

    EXPECT_EQ(SI_QUEUE, g_received_si_code.load());
    EXPECT_EQ(cookie, g_received_sival.load());

    sigaction(SIGUSR2, &prev, nullptr);
}

// -------- forwardForeignSignal chains to previous handler --------

static std::atomic<int> g_chained_calls{0};

static void chainedHandler(int /*signo*/, siginfo_t* /*si*/, void* /*uc*/) {
    g_chained_calls.fetch_add(1);
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

#endif  // __linux__
