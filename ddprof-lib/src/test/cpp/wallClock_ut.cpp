/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <string>
#include <thread>
#include <vector>
#include "arguments.h"
#include "counters.h"
#include "wallClock.h"

TEST(WallClockTimerTest, WorkAndWakeLatenessDoNotAccumulate) {
    WallClockTimer timer(1000000);
    EXPECT_EQ(900000ULL, timer.nextSleep(1100000, 1000000));
    // Wake 200us late and do another 100us of work. The next opportunity
    // remains at 3ms, not 3.3ms as with a new relative sleep.
    EXPECT_EQ(700000ULL, timer.nextSleep(2300000, 1000000));
    EXPECT_EQ(850000ULL, timer.nextSleep(3150000, 1000000));
}

TEST(WallClockTimerTest, MissedDeadlineRestartsWithoutCatchUpBurst) {
    WallClockTimer timer(1000000);
    EXPECT_EQ(1000000ULL, timer.nextSleep(2000000, 1000000));
    EXPECT_EQ(1000000ULL, timer.nextSleep(9000000, 1000000));
    EXPECT_EQ(900000ULL, timer.nextSleep(10100000, 1000000));
}

TEST(WallClockTimerTest, DitheredPeriodsStayOnTheSameSchedule) {
    WallClockTimer timer(1000000);
    EXPECT_EQ(800000ULL, timer.nextSleep(1100000, 900000));
    EXPECT_EQ(950000ULL, timer.nextSleep(2050000, 1100000));
    EXPECT_EQ(750000ULL, timer.nextSleep(3050000, 800000));
}

// Exercise the production phase probes, not a second implementation of the
// ledger. All expected totals are produced by the callbacks on the timer thread
// and read only after stop() joins it.
class PhaseLedgerWallClock : public BaseWallClock {
public:
    explicit PhaseLedgerWallClock(bool lazy) : lazy(lazy) {}
    const char* name() override { return "Phase ledger test timer"; }
    bool lazy;
    u64 iterations = 0, empty = 0, single = 0, large = 0;
    u64 selected = 0, sent = 0, failed = 0, rejected = 0;
    std::atomic<int> completed{0};

    bool awaitPasses(int passes) const {
        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (completed.load(std::memory_order_acquire) < passes) {
            if (std::chrono::steady_clock::now() >= deadline) return false;
            std::this_thread::yield();
        }
        return true;
    }

private:
    void timerLoop() override {
        iterations = empty = single = large = selected = sent = failed = rejected = 0;
        completed.store(0, std::memory_order_release);
        auto collect = [&](std::vector<ThreadEntry>& entries) {
            size_t count = iterations % 4 == 0 ? 0 : iterations % 4 == 1 ? 1 :
                           iterations % 4 == 2 ? 17 : 2;
            ++iterations;
            empty += count == 0;
            single += count == 1;
            large += count > 16;
            for (size_t tid = 1; tid <= count; ++tid) {
                entries.push_back(ThreadEntry{static_cast<int>(tid), nullptr, -1, 0, 0});
            }
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        };
        auto sample = [&](ThreadEntry entry, int& failures, int&, int&, int&, bool) {
            ++selected;
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            if (lazy && entry.tid % 3 == 0) {
                ++rejected;
                return WallClockCandidateOutcome::PRECHECK_REJECTED;
            }
            if (entry.tid % 2 == 0) {
                ++failures;
                ++failed;
                return WallClockCandidateOutcome::SIGNAL_FAILED;
            }
            ++sent;
            return WallClockCandidateOutcome::SIGNAL_SENT;
        };
        auto clean = [&] {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            completed.store(static_cast<int>(iterations), std::memory_order_release);
        };
        timerLoopCommon<ThreadEntry>(collect, sample, clean, 16, 1000000, lazy, lazy);
    }
};

class WallClockPhaseLedgerTest : public ::testing::Test {
protected:
    void SetUp() override {
        const char* value = std::getenv("DDPROF_WALL_TIMER_DIAGNOSTICS");
        had_environment = value != nullptr;
        if (value != nullptr) saved_environment = value;
        previous_handler = std::signal(WAKEUP_SIGNAL, +[](int) {});
        args._wall = 1000000;
    }

    void TearDown() override {
        if (had_environment) {
            setenv("DDPROF_WALL_TIMER_DIAGNOSTICS", saved_environment.c_str(), 1);
        } else {
            unsetenv("DDPROF_WALL_TIMER_DIAGNOSTICS");
        }
        std::signal(WAKEUP_SIGNAL, previous_handler);
    }

    void run(PhaseLedgerWallClock& clock) {
        clock.enableEvents(true);
        clock.completed.store(0, std::memory_order_release);
        bool started = !clock.start(args);
        bool completed = started && clock.awaitPasses(16);
        clock.stop();
        clock.enableEvents(false);
        ASSERT_TRUE(started);
        ASSERT_TRUE(completed);
    }

    void expectEnabled(const PhaseLedgerWallClock& clock) {
        const auto& phases = clock.timerPhasesForTest();
        EXPECT_EQ(clock.iterations, phases.iterations);
        EXPECT_EQ(clock.empty, phases.empty);
        EXPECT_EQ(clock.single, phases.single);
        EXPECT_EQ(clock.large, phases.large);
        EXPECT_EQ(clock.selected, phases.selected);
        EXPECT_EQ(clock.sent, phases.sent);
        EXPECT_EQ(clock.failed, phases.failed);
        EXPECT_EQ(clock.selected, clock.sent + clock.failed + clock.rejected);
        EXPECT_GT(phases.empty, 0ULL);
        EXPECT_GT(phases.single, 0ULL);
        EXPECT_GT(phases.large, 0ULL);
        EXPECT_GT(phases.collect_ns, 0ULL);
        EXPECT_GT(phases.select_ns, 0ULL);
        EXPECT_GT(phases.send_ns, 0ULL);
        EXPECT_GT(phases.finish_ns, 0ULL);
        EXPECT_GT(phases.requested_sleep_ns, 0ULL);
        EXPECT_GT(phases.actual_sleep_ns, 0ULL);
        EXPECT_GT(phases.first_eligible, 0ULL);
        EXPECT_LE(phases.first_eligible, phases.first_send);
        EXPECT_LE(phases.first_send, phases.last_send);
        EXPECT_LE(phases.first_eligible, phases.last_eligible);
        EXPECT_LE(phases.last_eligible, phases.last_send);
    }

    Arguments args;
    bool had_environment = false;
    std::string saved_environment;
    using SignalHandler = void (*)(int);
    SignalHandler previous_handler = SIG_DFL;
};

TEST_F(WallClockPhaseLedgerTest, OrdinaryPhasesCountCallbacksAndPoolSizes) {
    setenv("DDPROF_WALL_TIMER_DIAGNOSTICS", "1", 1);
    PhaseLedgerWallClock clock(false);
    run(clock);
    expectEnabled(clock);
    EXPECT_EQ(0ULL, clock.rejected);
}

TEST_F(WallClockPhaseLedgerTest, LazyPhasesIncludeRejectedCandidatesButNotAsSends) {
    setenv("DDPROF_WALL_TIMER_DIAGNOSTICS", "1", 1);
    PhaseLedgerWallClock clock(true);
    run(clock);
    expectEnabled(clock);
    EXPECT_GT(clock.rejected, 0ULL);
}

TEST_F(WallClockPhaseLedgerTest, DisabledRecordingClearsPreviousSnapshot) {
    setenv("DDPROF_WALL_TIMER_DIAGNOSTICS", "1", 1);
    PhaseLedgerWallClock clock(false);
    run(clock);
    expectEnabled(clock);
    setenv("DDPROF_WALL_TIMER_DIAGNOSTICS", "0", 1);
    run(clock);
    const auto& phases = clock.timerPhasesForTest();
    EXPECT_GT(clock.iterations, 0ULL);
    EXPECT_EQ(0ULL, phases.iterations);
    EXPECT_EQ(0ULL, phases.empty + phases.single + phases.large);
    EXPECT_EQ(0ULL, phases.selected + phases.sent + phases.failed);
    EXPECT_EQ(0ULL, phases.first_eligible + phases.last_eligible +
                    phases.first_send + phases.last_send);
    EXPECT_EQ(0ULL, phases.collect_ns + phases.select_ns + phases.send_ns + phases.finish_ns);
    EXPECT_EQ(0ULL, phases.requested_sleep_ns + phases.actual_sleep_ns);
}

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
