/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <csignal>
#include <thread>
#include <vector>
#include "arguments.h"
#include "counters.h"
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
        // The profiler's tracker storage is allocated lazily on first
        // registration, so the baseline may be 0; tests assert deltas against it.
        ASSERT_GE(baseline, 0);
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

// Drives the real lazy-backfill timer loop (precheck + lazyBackfill) over a
// synthetic candidate pool, so the visit budget and the backfill of
// precheck-rejected candidates are exercised end to end through
// timerLoopCommon() rather than only through the selector in isolation.
class LazyBackfillWallClock : public BaseWallClock {
public:
    static constexpr int kPoolSize = 200;
    static constexpr int kReservoir = 16;
    static constexpr size_t kVisitBudget =
        static_cast<size_t>(kReservoir) * PRECHECK_VISIT_BUDGET_MULTIPLIER;

    struct Pass {
        int visited = 0;
        int sent = 0;
        int rejected = 0;
    };

    explicit LazyBackfillWallClock(bool (*accept)(int tid)) : _accept(accept) {}
    const char* name() override { return "Lazy backfill test timer"; }

    bool awaitPasses(int passes) const {
        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(20);
        while (completed_passes.load(std::memory_order_acquire) < passes) {
            if (std::chrono::steady_clock::now() >= deadline) return false;
            std::this_thread::yield();
        }
        return true;
    }

    // Written only by the timer thread; read after stop() has joined it.
    std::vector<Pass> passes;
    bool visited_tid[kPoolSize + 1] = {};
    std::atomic<int> completed_passes{0};

private:
    void timerLoop() override {
        Pass current;
        auto collect = [](std::vector<ThreadEntry>& entries) {
            for (int tid = 1; tid <= kPoolSize; ++tid) {
                entries.push_back(ThreadEntry{tid, nullptr, -1, 0, 0});
            }
        };
        auto sample = [&](ThreadEntry entry, int&, int&, int&, int& lookups, bool) {
            current.visited++;
            lookups++;
            visited_tid[entry.tid] = true;
            if (!_accept(entry.tid)) {
                current.rejected++;
                return WallClockCandidateOutcome::PRECHECK_REJECTED;
            }
            current.sent++;
            return WallClockCandidateOutcome::SIGNAL_SENT;
        };
        auto clean = [&] {
            passes.push_back(current);
            current = Pass();
            completed_passes.store(static_cast<int>(passes.size()), std::memory_order_release);
        };
        timerLoopCommon<ThreadEntry>(collect, sample, clean, kReservoir, 1000000,
                                     /*precheck=*/true, /*lazyBackfill=*/true);
    }

    bool (*_accept)(int tid);
};

class WallClockLazyBackfillTest : public ::testing::Test {
protected:
    void SetUp() override {
        previous_handler = std::signal(WAKEUP_SIGNAL, +[](int) {});
        enabler.enableEvents(true);
        args._wall = 1000000;
    }

    void TearDown() override {
        enabler.enableEvents(false);
        std::signal(WAKEUP_SIGNAL, previous_handler);
    }

    struct Totals {
        long long visited = 0;
        long long rejected = 0;
        long long budget_exhausted = 0;
    };

    static Totals totals(const LazyBackfillWallClock& clock) {
        Totals t;
        for (const auto& pass : clock.passes) {
            t.visited += pass.visited;
            t.rejected += pass.rejected;
            if (pass.sent < LazyBackfillWallClock::kReservoir &&
                static_cast<size_t>(pass.visited) == LazyBackfillWallClock::kVisitBudget) {
                t.budget_exhausted++;
            }
        }
        return t;
    }

    Arguments args;
    AccountingWallClock enabler;  // only used to toggle the shared _enabled flag
    using SignalHandler = void (*)(int);
    SignalHandler previous_handler = SIG_DFL;
};

// 25% of the pool is precheck-rejected: rejections are backfilled without
// consuming reservoir slots, so every pass still sends a full reservoir, and
// the walk stays within the visit budget.
TEST_F(WallClockLazyBackfillTest, RejectedCandidatesAreBackfilledWithoutConsumingSlots) {
    constexpr int kPasses = 300;
    LazyBackfillWallClock clock(+[](int tid) { return tid % 4 != 0; });
#ifdef COUNTERS
    long long rejected_before = Counters::getCounter(WC_PRECHECK_CANDIDATES_REJECTED);
    long long lookups_before = Counters::getCounter(WC_PRECHECK_REGISTRY_LOOKUPS);
    long long exhausted_before = Counters::getCounter(WC_PRECHECK_LOOKUP_BUDGET_EXHAUSTED);
#endif
    bool started = !clock.start(args);
    bool completed = started && clock.awaitPasses(kPasses);
    clock.stop();  // joins the timer thread before any assertion reads its state
    ASSERT_TRUE(started);
    ASSERT_TRUE(completed);

    for (size_t i = 0; i < clock.passes.size(); ++i) {
        const auto& pass = clock.passes[i];
        EXPECT_EQ(LazyBackfillWallClock::kReservoir, pass.sent) << "pass " << i;
        EXPECT_LE(static_cast<size_t>(pass.visited), LazyBackfillWallClock::kVisitBudget)
            << "pass " << i;
        EXPECT_EQ(pass.visited, pass.sent + pass.rejected) << "pass " << i;
    }
    for (int tid = 1; tid <= LazyBackfillWallClock::kPoolSize; ++tid) {
        if (tid % 4 != 0) {
            EXPECT_TRUE(clock.visited_tid[tid]) << "accepted tid " << tid << " never visited";
        }
    }
#ifdef COUNTERS
    Totals t = totals(clock);
    EXPECT_EQ(rejected_before + t.rejected,
              Counters::getCounter(WC_PRECHECK_CANDIDATES_REJECTED));
    EXPECT_EQ(lookups_before + t.visited, Counters::getCounter(WC_PRECHECK_REGISTRY_LOOKUPS));
    EXPECT_EQ(exhausted_before, Counters::getCounter(WC_PRECHECK_LOOKUP_BUDGET_EXHAUSTED));
#endif
}

// Only 8 of 200 candidates are accepted, so the reservoir can never fill and
// every pass stops at the visit budget; the randomized prefix still reaches
// the whole pool over time.
TEST_F(WallClockLazyBackfillTest, VisitBudgetBindsWhenPoolCannotFillReservoir) {
    constexpr int kPasses = 100;
    LazyBackfillWallClock clock(+[](int tid) { return tid % 25 == 0; });
#ifdef COUNTERS
    long long exhausted_before = Counters::getCounter(WC_PRECHECK_LOOKUP_BUDGET_EXHAUSTED);
#endif
    bool started = !clock.start(args);
    bool completed = started && clock.awaitPasses(kPasses);
    clock.stop();
    ASSERT_TRUE(started);
    ASSERT_TRUE(completed);

    for (size_t i = 0; i < clock.passes.size(); ++i) {
        EXPECT_EQ(static_cast<int>(LazyBackfillWallClock::kVisitBudget),
                  clock.passes[i].visited) << "pass " << i;
    }
    for (int tid = 1; tid <= LazyBackfillWallClock::kPoolSize; ++tid) {
        EXPECT_TRUE(clock.visited_tid[tid]) << "tid " << tid << " never visited";
    }
#ifdef COUNTERS
    EXPECT_EQ(exhausted_before + static_cast<long long>(clock.passes.size()),
              Counters::getCounter(WC_PRECHECK_LOOKUP_BUDGET_EXHAUSTED));
#endif
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
