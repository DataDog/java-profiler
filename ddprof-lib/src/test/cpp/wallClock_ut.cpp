/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <csignal>
#include <thread>
#include "arguments.h"
#include "wallClock.h"

// profiler.cpp's Profiler::start() falls back to ThreadFilter::deactivateRecording()
// when the wall engine fails to start. This proves BaseWallClock::start() can
// genuinely return a non-OK Error, i.e. that the fallback's trigger condition
// is reachable in production.
TEST(WallClockStartTest, StartReturnsErrorWhenForced) {
    WallClockASGCT wall_clock;
    Arguments args;

    BaseWallClock::setForceStartFailureForTest(true);
    Error error = wall_clock.start(args);
    BaseWallClock::setForceStartFailureForTest(false);

    EXPECT_TRUE(error);
}

// Drive the real timer loop without sending profiling signals or starting a JVM.
// Each phase changes the vector's capacity once; cleanThreads publishes after
// the production loop has accounted for that iteration's backing allocation.
class AccountingWallClock : public BaseWallClock {
public:
    const char* name() override { return "Accounting test timer"; }
    using BaseWallClock::sampleThreadCommon;

    bool awaitPhase(int phase) const {
        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (completed_phase.load(std::memory_order_acquire) < phase) {
            if (std::chrono::steady_clock::now() >= deadline) return false;
            std::this_thread::yield();
        }
        return true;
    }

    std::atomic<int> requested_phase{1};
    std::atomic<int> completed_phase{0};
    std::atomic<long long> buffer_bytes{0};

private:
    void timerLoop() override {
        int applied_phase = 0;
        auto collect = [&](std::vector<ThreadEntry>& entries) {
            int phase = requested_phase.load(std::memory_order_acquire);
            if (phase != applied_phase) {
                if (phase == 2) {
                    entries.reserve(512);
                } else if (phase == 3) {
                    std::vector<ThreadEntry>().swap(entries);
                }
                applied_phase = phase;
            }
            buffer_bytes.store(static_cast<long long>(entries.capacity() * sizeof(ThreadEntry)),
                               std::memory_order_relaxed);
        };
        auto sample = [](ThreadEntry, int&, int&, int&, int&, bool) {
            return WallClockCandidateOutcome::SIGNAL_SENT;
        };
        auto clean = [&] {
            completed_phase.store(applied_phase, std::memory_order_release);
        };
        timerLoopCommon<ThreadEntry>(collect, sample, clean, 16, 1000000);
    }
};

class WallClockAccountingTest : public ::testing::Test {
protected:
    void SetUp() override {
        baseline = NativeMem::live(NM_WALLCLOCK);
        ASSERT_GT(baseline, 0);  // The profiler's tracker remains resident.
        previous_handler = std::signal(WAKEUP_SIGNAL, +[](int) {});
        first.enableEvents(true);
    }

    void TearDown() override {
        first.stop();
        second.stop();
        first.enableEvents(false);
        std::signal(WAKEUP_SIGNAL, previous_handler);
        // Preserve the process-global gauge even in the unfixed reproduction.
        NativeMem::setLive(NM_WALLCLOCK, baseline);
    }

    Arguments args;
    AccountingWallClock first;
    AccountingWallClock second;
    long long baseline = 0;
    using SignalHandler = void (*)(int);
    SignalHandler previous_handler = SIG_DFL;
};

TEST_F(WallClockAccountingTest, TimerPreservesTrackerBytesAcrossStopAndRestart) {
    args._wall = 1000000;
    for (int recording = 0; recording < 2; ++recording) {
        first.completed_phase.store(0, std::memory_order_release);
        ASSERT_FALSE(first.start(args));
        ASSERT_TRUE(first.awaitPhase(1));
        EXPECT_EQ(baseline + first.buffer_bytes.load(), NativeMem::live(NM_WALLCLOCK));
        first.stop();
        EXPECT_EQ(baseline, NativeMem::live(NM_WALLCLOCK));
    }
}

TEST_F(WallClockAccountingTest, IndependentTimersBalanceGrowthAndShrink) {
    args._wall = 1000000;
    ASSERT_FALSE(first.start(args));
    ASSERT_TRUE(first.awaitPhase(1));
    ASSERT_FALSE(second.start(args));
    ASSERT_TRUE(second.awaitPhase(1));
    EXPECT_EQ(baseline + first.buffer_bytes.load() + second.buffer_bytes.load(),
              NativeMem::live(NM_WALLCLOCK));

    first.requested_phase.store(2, std::memory_order_release);
    ASSERT_TRUE(first.awaitPhase(2));
    EXPECT_EQ(baseline + first.buffer_bytes.load() + second.buffer_bytes.load(),
              NativeMem::live(NM_WALLCLOCK));

    second.requested_phase.store(3, std::memory_order_release);
    ASSERT_TRUE(second.awaitPhase(3));
    EXPECT_EQ(0, second.buffer_bytes.load());
    EXPECT_EQ(baseline + first.buffer_bytes.load(), NativeMem::live(NM_WALLCLOCK));
    first.stop();
    EXPECT_EQ(baseline, NativeMem::live(NM_WALLCLOCK));
    second.stop();
    EXPECT_EQ(baseline, NativeMem::live(NM_WALLCLOCK));
}

static volatile sig_atomic_t sampling_signal_received = 0;

class WallClockCapacityTest : public ::testing::Test {
protected:
    void SetUp() override {
        struct sigaction action = {};
        action.sa_handler = +[](int) { sampling_signal_received = 1; };
        sigemptyset(&action.sa_mask);
        ASSERT_EQ(0, sigaction(SIGVTALRM, &action, &previous_action));
        handler_installed = true;
        sigset_t signal;
        sigemptyset(&signal);
        sigaddset(&signal, SIGVTALRM);
        ASSERT_EQ(0, pthread_sigmask(SIG_UNBLOCK, &signal, &previous_mask));
        mask_saved = true;
    }

    void TearDown() override {
        if (handler_installed) sigaction(SIGVTALRM, &previous_action, nullptr);
        if (mask_saved) pthread_sigmask(SIG_SETMASK, &previous_mask, nullptr);
    }

    struct sigaction previous_action = {};
    sigset_t previous_mask;
    bool handler_installed = false;
    bool mask_saved = false;
};

TEST_F(WallClockCapacityTest, ExhaustionKeepsSendingSignalsAcrossRecordings) {
    ThreadFilter registry;
    WallClockBlockTracker tracker;
    registry.setBlockTracker(&tracker);
    registry.init("", true);
    for (int i = 0; i < ThreadFilter::kMaxThreads; ++i) {
        ASSERT_GE(registry.registerThread(1000000 + i), 0);
    }

    AccountingWallClock clock;
    int tid = OS::threadId();
    for (int recording = 0; recording < 2; ++recording) {
        ASSERT_EQ(-1, registry.registerThread(tid));
        sampling_signal_received = 0;
        ThreadEntry entry{tid, nullptr, -1, 0, 0};
        int failures = 0, exited = 0, denied = 0, lookups = 0;
        EXPECT_EQ(WallClockCandidateOutcome::SIGNAL_SENT,
                  clock.sampleThreadCommon(entry, failures, exited, denied, lookups,
                                           true, true, &registry, registry.recordingEpoch()));
        EXPECT_EQ(0, failures);
        EXPECT_EQ(1, lookups);

        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (sampling_signal_received == 0 && std::chrono::steady_clock::now() < deadline) {
            std::this_thread::yield();
        }
        EXPECT_EQ(1, sampling_signal_received)
            << "Unfiltered registry exhaustion must fall back to ordinary signals";
        registry.deactivateRecording();
        registry.init("", true);
    }
}
