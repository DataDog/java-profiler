/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <future>
#include <string>
#include <thread>
#include <vector>
#include "arguments.h"
#include "counters.h"
#include "profiler.h"
#include "wallClock.h"

#include <memory>

class WallClockInitialEpochTest : public ::testing::Test {
protected:
    void SetUp() override { WallClockCounters::reset(); }
    void TearDown() override { WallClockCounters::reset(); }
};

TEST_F(WallClockInitialEpochTest, ReadyEpochDoesNotNeedATimeoutBudget) {
    const u64 epoch = TSC::ticks();
    WallClockCounters::beginSamplingEpoch(epoch);
    EXPECT_TRUE(BaseWallClock::awaitInitialSamplingEpochForTest(0));
    EXPECT_EQ(epoch, WallClockCounters::samplingEpochStart());
}

TEST_F(WallClockInitialEpochTest, DelayedPublicationReleasesTheWaiter) {
    std::promise<void> started;
    auto result = std::async(std::launch::async, [&] {
        started.set_value();
        return BaseWallClock::awaitInitialSamplingEpochForTest(5 * NANOTIME_FREQ);
    });
    started.get_future().wait();
    EXPECT_EQ(std::future_status::timeout, result.wait_for(std::chrono::milliseconds(10)));
    EXPECT_EQ(0ULL, WallClockCounters::samplingEpochStart());
    const u64 epoch = TSC::ticks();
    WallClockCounters::beginSamplingEpoch(epoch);
    EXPECT_TRUE(result.get());
    EXPECT_EQ(epoch, WallClockCounters::samplingEpochStart());
}

TEST_F(WallClockInitialEpochTest, TimeoutLeavesZeroEpochUnchanged) {
    const u64 timeout_nanos = 1000000;
    const u64 start = OS::nanotime();
    EXPECT_FALSE(BaseWallClock::awaitInitialSamplingEpochForTest(timeout_nanos));
    EXPECT_GE(OS::nanotime() - start, timeout_nanos);
    EXPECT_EQ(0ULL, WallClockCounters::samplingEpochStart());
}

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
    explicit PhaseLedgerWallClock(bool precheck) : precheck(precheck) {}
    const char* name() override { return "Phase ledger test timer"; }
    bool precheck;
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
    void observeEpochForTest(const WallClockEpochEvent& epoch) override {
        EXPECT_EQ(epoch._start_time, WallClockCounters::samplingEpochStart());
        EXPECT_NE(0ULL, epoch._start_time);
    }

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
            if (precheck && entry.tid % 3 == 0) {
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
        timerLoopCommon<ThreadEntry>(collect, sample, clean, 16, 1000000, precheck);
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

TEST_F(WallClockPhaseLedgerTest, PrecheckPhasesIncludeRejectedCandidatesButNotAsSends) {
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
        ASSERT_TRUE(tracker.ensureAllocated());
        baseline = NativeMem::live(NM_WALLCLOCK);
        ASSERT_GT(baseline, 0);
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
    WallClockBlockTracker tracker;
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

// Exercises bounded registry visits and candidate coverage through the real
// reservoir loop, including sparse populations of unsuppressed threads.
class ReservoirPrecheckWallClock : public BaseWallClock {
public:
    static constexpr int kPoolSize = 200;
    static constexpr int kReservoir = 16;

    struct Pass {
        int visited = 0;
        int sent = 0;
        int rejected = 0;
    };

    explicit ReservoirPrecheckWallClock(bool (*accept)(int tid)) : _accept(accept) {}
    const char* name() override { return "Reservoir precheck test timer"; }

    bool awaitPasses(int passes, std::chrono::seconds timeout = std::chrono::seconds(20)) const {
        auto deadline = std::chrono::steady_clock::now() + timeout;
        while (completed_passes.load(std::memory_order_acquire) < passes ||
               covered_threads.load(std::memory_order_acquire) < kPoolSize) {
            if (std::chrono::steady_clock::now() >= deadline) return false;
            std::this_thread::yield();
        }
        return true;
    }

    // Call after stop/join: visited_tid is timer-owned. Name rejected tids too.
    ::testing::AssertionResult coverageCompleted(bool completed) const {
        if (completed) return ::testing::AssertionSuccess();
        auto result = ::testing::AssertionFailure();
        result << "passes=" << completed_passes.load(std::memory_order_acquire)
               << ", covered=" << covered_threads.load(std::memory_order_acquire)
               << "/" << kPoolSize << ", missing tids:";
        bool missing = false;
        for (int tid = 1; tid <= kPoolSize; ++tid) {
            if (!visited_tid[tid]) {
                result << " " << tid;
                missing = true;
            }
        }
        if (!missing) result << " none";
        return result;
    }

    // Written only by the timer thread; read after stop() has joined it.
    std::vector<Pass> passes;
    bool visited_tid[kPoolSize + 1] = {};
    std::atomic<int> completed_passes{0};
    std::atomic<int> covered_threads{0};

private:
    void timerLoop() override {
        Pass current;
        int visited_count = 0;
        auto collect = [](std::vector<ThreadEntry>& entries) {
            for (int tid = 1; tid <= kPoolSize; ++tid) {
                entries.push_back(ThreadEntry{tid, nullptr, -1, 0, 0});
            }
        };
        auto sample = [&](ThreadEntry entry, int&, int&, int&, int& lookups, bool) {
            current.visited++;
            lookups++;
            if (!visited_tid[entry.tid]) {
                visited_tid[entry.tid] = true;
                ++visited_count;
            }
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
            covered_threads.store(visited_count, std::memory_order_release);
            completed_passes.store(static_cast<int>(passes.size()), std::memory_order_release);
        };
        timerLoopCommon<ThreadEntry>(collect, sample, clean, kReservoir, 1000000,
                                     /*lookupRegistrySlot=*/true);
    }

    bool (*_accept)(int tid);
};

class WallClockReservoirPrecheckTest : public ::testing::Test {
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
    };

    static Totals totals(const ReservoirPrecheckWallClock& clock) {
        Totals t;
        for (const auto& pass : clock.passes) {
            t.visited += pass.visited;
            t.rejected += pass.rejected;
        }
        return t;
    }

    Arguments args;
    AccountingWallClock enabler;  // only used to toggle the shared _enabled flag
    using SignalHandler = void (*)(int);
    SignalHandler previous_handler = SIG_DFL;
};

// Rejections consume selected slots without additional visits or signals.
TEST_F(WallClockReservoirPrecheckTest, RejectedCandidatesConsumeReservoirSlots) {
    constexpr int kPasses = 300;
    ReservoirPrecheckWallClock clock(+[](int tid) { return tid % 4 != 0; });
#ifdef COUNTERS
    long long rejected_before = Counters::getCounter(WC_PRECHECK_CANDIDATES_REJECTED);
    long long lookups_before = Counters::getCounter(WC_PRECHECK_REGISTRY_LOOKUPS);
#endif
    bool started = !clock.start(args);
    bool completed = started && clock.awaitPasses(kPasses);
    clock.stop();  // joins the timer thread before any assertion reads its state
    ASSERT_TRUE(started);
    ASSERT_TRUE(clock.coverageCompleted(completed));

    for (size_t i = 0; i < clock.passes.size(); ++i) {
        const auto& pass = clock.passes[i];
        EXPECT_EQ(ReservoirPrecheckWallClock::kReservoir, pass.visited) << "pass " << i;
        EXPECT_EQ(ReservoirPrecheckWallClock::kReservoir, pass.sent + pass.rejected)
            << "pass " << i;
        EXPECT_EQ(pass.visited, pass.sent + pass.rejected) << "pass " << i;
    }
    for (int tid = 1; tid <= ReservoirPrecheckWallClock::kPoolSize; ++tid) {
        if (tid % 4 != 0) {
            EXPECT_TRUE(clock.visited_tid[tid]) << "accepted tid " << tid << " never visited";
        }
    }
#ifdef COUNTERS
    Totals t = totals(clock);
    EXPECT_EQ(rejected_before + t.rejected,
              Counters::getCounter(WC_PRECHECK_CANDIDATES_REJECTED));
    EXPECT_EQ(lookups_before + t.visited, Counters::getCounter(WC_PRECHECK_REGISTRY_LOOKUPS));
#endif
}

TEST_F(WallClockReservoirPrecheckTest, PassCountWithoutCoverageDoesNotComplete) {
    ReservoirPrecheckWallClock clock(+[](int) { return true; });
    clock.completed_passes.store(100);
    clock.covered_threads.store(ReservoirPrecheckWallClock::kPoolSize - 1);
    EXPECT_FALSE(clock.awaitPasses(100, std::chrono::seconds(0)));
    clock.covered_threads.store(ReservoirPrecheckWallClock::kPoolSize);
    EXPECT_TRUE(clock.awaitPasses(100, std::chrono::seconds(0)));
    clock.completed_passes.store(99);
    EXPECT_FALSE(clock.awaitPasses(100, std::chrono::seconds(0)));
}

TEST_F(WallClockReservoirPrecheckTest, CoverageTimeoutNamesOmittedRejectedTidAndCounts) {
    ReservoirPrecheckWallClock clock(+[](int tid) { return tid % 4 != 0; });
    // No timer is running, so the omitted rejected tid cannot gain coverage.
    for (int tid = 1; tid <= ReservoirPrecheckWallClock::kPoolSize; ++tid) {
        clock.visited_tid[tid] = tid != 184;
    }
    clock.completed_passes.store(100);
    clock.covered_threads.store(199);
    bool completed = clock.awaitPasses(100, std::chrono::seconds(0));
    ::testing::TestPartResultArray failures;
    {
        ::testing::ScopedFakeTestPartResultReporter reporter(
            ::testing::ScopedFakeTestPartResultReporter::INTERCEPT_ONLY_CURRENT_THREAD, &failures);
        auto require_completion = [&] { ASSERT_TRUE(clock.coverageCompleted(completed)); };
        require_completion();
    }
    ASSERT_EQ(1, failures.size());
    const auto& failure = failures.GetTestPartResult(0);
    EXPECT_TRUE(failure.fatally_failed());
    const std::string message = failure.message();
    EXPECT_NE(std::string::npos, message.find("passes=100")) << message;
    EXPECT_NE(std::string::npos, message.find("covered=199/200")) << message;
    EXPECT_NE(std::string::npos, message.find("missing tids: 184")) << message;
}

// A sparse accepted population cannot expand visits beyond the reservoir.
TEST_F(WallClockReservoirPrecheckTest, SparseAcceptedPoolStillVisitsOnlyReservoir) {
    constexpr int kPasses = 100;
    ReservoirPrecheckWallClock clock(+[](int tid) { return tid % 25 == 0; });
    bool started = !clock.start(args);
    bool completed = started && clock.awaitPasses(kPasses);
    clock.stop();
    ASSERT_TRUE(started);
    ASSERT_TRUE(clock.coverageCompleted(completed));

    for (size_t i = 0; i < clock.passes.size(); ++i) {
        EXPECT_EQ(ReservoirPrecheckWallClock::kReservoir,
                  clock.passes[i].visited) << "pass " << i;
    }
    for (int tid = 1; tid <= ReservoirPrecheckWallClock::kPoolSize; ++tid) {
        EXPECT_TRUE(clock.visited_tid[tid]) << "tid " << tid << " never visited";
    }
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

class WallClockPrecheckTest : public ::testing::Test {
protected:
    static constexpr int kTid = 12345;
    Profiler* profiler = Profiler::instance();
    ThreadFilter* filter = profiler->threadFilter();
    WallClockBlockTracker* tracker = profiler->blockTracker();
    std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current{
        nullptr, ProfiledThread::deleteForTest};
    ThreadFilter::SlotID slot_id = -1;

    void SetUp() override {
        Counters::reset();
        filter->init("", true);
        slot_id = filter->registerThread(kTid);
        ASSERT_GE(slot_id, 0);
        current.reset(ProfiledThread::forTid(kTid));
        current->setFilterSlotId(slot_id);
    }

    void TearDown() override {
        tracker->resetAll();
        filter->unregisterThread(slot_id, kTid);
        filter->deactivateRecording();
        current.reset();
        Counters::reset();
    }
};

TEST_F(WallClockPrecheckTest, UnownedObservationsRetainUnitWeightWithoutFallback) {
    // Repeated short blocked bursts used to lose their suppressed remainder
    // on every runnable observation in the delegated JVMTI path.
    for (int burst = 0; burst < 3; ++burst) {
        for (int observation = 0; observation < 7; ++observation) {
            OSThreadState state = observation < 6 ? OSThreadState::SLEEPING
                                                  : OSThreadState::RUNNABLE;
            u64 weight = 0;
            EXPECT_FALSE(BaseWallClock::wallPrecheckForTest(
                current.get(), false, state, weight, true));
            EXPECT_EQ(1ULL, weight);
        }
    }
    EXPECT_EQ(0ULL, tracker->slotForId(slot_id)->unowned_blocked_pending_weight.load());
    EXPECT_EQ(0, Counters::getCounter(WC_UNOWNED_BLOCKED_SUPPRESSED));
    EXPECT_EQ(0, Counters::getCounter(WC_UNOWNED_BLOCKED_RECORDED));
}

TEST_F(WallClockPrecheckTest, OwnedBlocksStillSuppressWithoutUnownedFallback) {
    u64 token = tracker->enterBlockedRun(
        filter, slot_id, OSThreadState::SLEEPING, BlockRunOwner::TASK_BLOCK);
    ASSERT_NE(0ULL, token);
    u64 weight = 0;

    // A failed write must leave the owned run eligible for another attempt.
    EXPECT_FALSE(BaseWallClock::wallPrecheckForTest(
        current.get(), false, OSThreadState::SLEEPING, weight, false));
    EXPECT_FALSE(BaseWallClock::wallPrecheckForTest(
        current.get(), false, OSThreadState::SLEEPING, weight, true));
    EXPECT_TRUE(BaseWallClock::wallPrecheckForTest(
        current.get(), false, OSThreadState::SLEEPING, weight));
    EXPECT_EQ(1, Counters::getCounter(WC_SIGNAL_SUPPRESSED_OWNED_BLOCK));

    ASSERT_TRUE(tracker->exitBlockedRun(
        slot_id, WallClockBlockTracker::tokenGeneration(token)));
    EXPECT_FALSE(BaseWallClock::wallPrecheckForTest(
        current.get(), false, OSThreadState::SLEEPING, weight, true));
    EXPECT_EQ(1ULL, weight);
}

class RetainedWallClockPrecheckTest : public WallClockPrecheckTest,
                                      public ::testing::WithParamInterface<bool> {
protected:
    WallClockASGCT clock;
    BaseWallClock::ThreadStateReaderForTest previous_reader = nullptr;
    u64 trace_id = 0;
    std::vector<u64> weights;
    std::vector<u64> epochs;

    void SetUp() override {
        WallClockPrecheckTest::SetUp();
        tracker->setUnownedContextSnapshotsNeeded(true);
        filter->init(GetParam() ? "0" : "", !GetParam());
        slot_id = filter->registerThread(kTid);
        ASSERT_GE(slot_id, 0);
        current->setFilterSlotId(slot_id);
        if (GetParam()) ASSERT_TRUE(filter->add(kTid, slot_id));
        ASGCT_CallFrame frame{};
        frame.method_id = reinterpret_cast<jmethodID>(0x12345);
        trace_id = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
        ASSERT_GT(trace_id >> 32, 0ULL);
        previous_reader = BaseWallClock::exchangeThreadStateReaderForTest(
            +[] { return OSThreadState::SLEEPING; });
        profiler->sampleWriteHookArgForTest = this;
        profiler->sampleWriteHookForTest = +[](u32, u64 id, Event* event, const Context* context, void* arg) {
            auto* self = static_cast<RetainedWallClockPrecheckTest*>(arg);
            EXPECT_EQ(self->trace_id, id);
            EXPECT_NE(nullptr, context);
            auto* sample = static_cast<ExecutionEvent*>(event);
            self->weights.push_back(sample->_weight);
            self->epochs.push_back(sample->_sample_ticks);
            return true;
        };
        WallClockCounters::beginSamplingEpoch(TSC::ticks());
    }

    void TearDown() override {
        profiler->sampleWriteHookForTest = nullptr;
        profiler->sampleWriteHookArgForTest = nullptr;
        BaseWallClock::exchangeThreadStateReaderForTest(previous_reader);
        tracker->setUnownedContextSnapshotsNeeded(false);
        WallClockCounters::reset();
        WallClockPrecheckTest::TearDown();
    }

    WallSampleRequest prepare(bool& suppressed) {
        return clock.prepareWallSampleRequestForTest(current.get(), suppressed);
    }

    WallSampleResult record(const WallSampleRequest& request) {
        ExecutionEvent event;
        event._thread_state = request.observed_state;
        return profiler->recordWallSample(nullptr, 1, trace_id, &event, request);
    }
};

TEST_P(RetainedWallClockPrecheckTest, WeightedFallbackConservesEveryObservation) {
    bool suppressed = true;
    auto first = prepare(suppressed);
    ASSERT_FALSE(suppressed);
    ASSERT_TRUE(first.unowned_sample);
    ASSERT_TRUE(record(first).ordinary_recorded);
    Context retained{};
    u64 publication = 0;
    ASSERT_TRUE(tracker->readUnownedContext(slot_id, retained, publication));
    EXPECT_GT(publication, 0ULL);
    for (int observation = 0; observation < 9; ++observation) {
        prepare(suppressed);
        ASSERT_TRUE(suppressed);
    }
    EXPECT_EQ(9ULL, tracker->slotForId(slot_id)->unowned_blocked_pending_weight.load());
    auto periodic = prepare(suppressed);
    ASSERT_FALSE(suppressed);
    ASSERT_TRUE(record(periodic).ordinary_recorded);
    EXPECT_EQ((std::vector<u64>{1, 10}), weights);
    EXPECT_EQ(0ULL, tracker->slotForId(slot_id)->unowned_blocked_pending_weight.load());
    EXPECT_EQ(9, Counters::getCounter(WC_UNOWNED_BLOCKED_SUPPRESSED));
    EXPECT_EQ(2, Counters::getCounter(WC_UNOWNED_BLOCKED_RECORDED));
}

TEST_P(RetainedWallClockPrecheckTest, ContextBoundaryRetainsEpochSegmentsAndCommitsEachOnce) {
    bool suppressed = true;
    auto first = prepare(suppressed);
    ASSERT_FALSE(suppressed);
    ASSERT_TRUE(record(first).ordinary_recorded);
    const u64 first_epoch = WallClockCounters::samplingEpochStart();
    prepare(suppressed);
    ASSERT_TRUE(suppressed);
    const u64 second_epoch = TSC::ticks();
    ASSERT_GT(second_epoch, first_epoch);
    WallClockCounters::beginSamplingEpoch(second_epoch);
    prepare(suppressed);
    ASSERT_TRUE(suppressed);
    Context retained{};
    u64 publication = 0;
    ASSERT_TRUE(tracker->readUnownedContext(slot_id, retained, publication));
    ASSERT_TRUE(filter->add(kTid, slot_id));
    filter->remove(slot_id);
    if (GetParam()) ASSERT_TRUE(filter->add(kTid, slot_id));
    u64 after = 0;
    ASSERT_TRUE(tracker->readUnownedContext(slot_id, retained, after));
    EXPECT_EQ(publication, after);
    EXPECT_EQ(2ULL, tracker->slotForId(slot_id)->unowned_blocked_pending_weight.load());
    BaseWallClock::exchangeThreadStateReaderForTest(+[] { return OSThreadState::RUNNABLE; });
    auto boundary = prepare(suppressed);
    ASSERT_FALSE(suppressed);
    ASSERT_TRUE(boundary.flush_tail);
    auto result = record(boundary);
    EXPECT_TRUE(result.ordinary_recorded);
    EXPECT_TRUE(result.tail_recorded);
    EXPECT_EQ((std::vector<u64>{1, 1, 1, 1}), weights);
    EXPECT_EQ((std::vector<u64>{0, 0, first_epoch, second_epoch}), epochs);
    EXPECT_EQ(0ULL, tracker->slotForId(slot_id)->unowned_blocked_pending_weight.load());
    EXPECT_FALSE(record(boundary).tail_recorded);
    EXPECT_EQ(2, Counters::getCounter(WC_UNOWNED_BLOCKED_SUPPRESSED));
    EXPECT_EQ(2, Counters::getCounter(WC_UNOWNED_BLOCKED_TAIL_RECORDED));
}

INSTANTIATE_TEST_SUITE_P(FilteredAndUnfiltered, RetainedWallClockPrecheckTest, ::testing::Bool());

TEST_F(WallClockPrecheckTest, UnfilteredContextWindowsDoNotSuppressUnownedObservations) {
    ASSERT_TRUE(filter->add(kTid, slot_id));
    for (int observation = 0; observation < 12; ++observation) {
        u64 weight = 0;
        EXPECT_FALSE(BaseWallClock::wallPrecheckForTest(
            current.get(), true, OSThreadState::SLEEPING, weight, true));
        EXPECT_EQ(1ULL, weight);
    }
    EXPECT_EQ(0, Counters::getCounter(WC_UNOWNED_BLOCKED_SUPPRESSED));
    EXPECT_EQ(0ULL, tracker->slotForId(slot_id)->unowned_blocked_pending_weight.load());
}

TEST_F(WallClockPrecheckTest, ContextScopedOwnedBlocksAreNotSuppressed) {
    filter->init("0", false);
    slot_id = filter->registerThread(kTid);
    ASSERT_GE(slot_id, 0);
    current->setFilterSlotId(slot_id);
    ASSERT_TRUE(filter->add(kTid, slot_id));
    u64 token = tracker->enterBlockedRun(
        filter, slot_id, OSThreadState::SLEEPING, BlockRunOwner::TASK_BLOCK);
    ASSERT_NE(0ULL, token);
    tracker->slotForId(slot_id)->markBlockGenerationSampled(
        WallClockBlockTracker::tokenGeneration(token));
    for (int observation = 0; observation < 3; ++observation) {
        u64 weight = 0;
        EXPECT_FALSE(BaseWallClock::wallPrecheckForTest(
            current.get(), true, OSThreadState::SLEEPING, weight, true));
        EXPECT_EQ(1ULL, weight);
    }
    EXPECT_EQ(0, Counters::getCounter(WC_SIGNAL_SUPPRESSED_OWNED_BLOCK));
    EXPECT_EQ(0, Counters::getCounter(WC_UNOWNED_BLOCKED_SUPPRESSED));
    EXPECT_TRUE(tracker->exitBlockedRun(
        slot_id, WallClockBlockTracker::tokenGeneration(token)));
}

// Exercise selection and epoch accounting in the production loop without kernel signals.
class OwnedPrecheckWallClock : public BaseWallClock {
public:
    static constexpr int pool_size = 512;
    static constexpr int reservoir_size = 16;
    bool mixed_outcomes = false;
    std::atomic<bool> observed{false};
    u32 selected = 0;
    u32 successful = 0;
    u32 failures = 0;
    u32 pool = 0;
    u64 suppressed = 0;

    const char* name() override { return "Owned selection test timer"; }

private:
    u32 visits = 0;
    void observeEpochForTest(const WallClockEpochEvent& epoch) override {
        if (observed.load(std::memory_order_acquire)) return;
        selected = visits;
        successful = epoch._num_successful_samples;
        failures = epoch._num_failed_samples;
        pool = epoch._num_samplable_threads;
        suppressed = epoch._num_suppressed_owned_block;
        observed.store(true, std::memory_order_release);
    }

    void timerLoop() override {
        auto collect = [&](std::vector<ThreadEntry>& entries) {
            visits = 0;
            auto* registry = Profiler::instance()->threadFilter();
            entries.clear();
            for (int i = 0; i < pool_size; ++i) {
                ThreadEntry entry{3000000 + i};
                if (registry->lookupThreadEntry(entry, registry->recordingEpoch())) {
                    entries.push_back(entry);
                }
            }
        };
        auto sample = [&](ThreadEntry entry, int& failed, int&, int&, int&, bool) {
            ++visits;
            if (mixed_outcomes && visits % 4 == 0) {
                ++failed;
                return WallClockCandidateOutcome::SIGNAL_FAILED;
            }
            if (mixed_outcomes && visits % 2 == 0) {
                return WallClockCandidateOutcome::SIGNAL_SENT;
            }
            if (suppressAlreadySampled(entry)) {
                return WallClockCandidateOutcome::PRECHECK_REJECTED;
            }
            return WallClockCandidateOutcome::SIGNAL_SENT;
        };
        timerLoopCommon<ThreadEntry>(collect, sample, [] {}, reservoir_size, 1000000);
    }
};

class WallClockOwnedSelectionTest : public ::testing::Test {
protected:
    OwnedPrecheckWallClock clock;
    std::vector<int> slots;
    using SignalHandler = void (*)(int);
    SignalHandler previous_handler = SIG_DFL;

    void SetUp() override {
        previous_handler = std::signal(WAKEUP_SIGNAL, +[](int) {});
        auto* registry = Profiler::instance()->threadFilter();
        auto* tracker = Profiler::instance()->blockTracker();
        registry->init("", true);
        WallClockCounters::drainSuppressedOwnedBlock();
        for (int i = 0; i < OwnedPrecheckWallClock::pool_size; ++i) {
            int tid = 3000000 + i;
            int id = registry->registerThread(tid);
            ASSERT_GE(id, 0);
            slots.push_back(id);
            u64 token = tracker->enterBlockedRun(registry, id, OSThreadState::SLEEPING);
            ASSERT_NE(0u, token);
            tracker->slotForId(id)->markBlockGenerationSampled(
                WallClockBlockTracker::tokenGeneration(token));
        }
        clock.enableEvents(true);
    }

    void TearDown() override {
        clock.stop();
        clock.enableEvents(false);
        auto* registry = Profiler::instance()->threadFilter();
        for (int id : slots) registry->unregisterThread(id);
        registry->deactivateRecording();
        WallClockCounters::drainSuppressedOwnedBlock();
        std::signal(WAKEUP_SIGNAL, previous_handler);
    }

    void run() {
        Arguments args;
        args._wall = 1000000;
        ASSERT_FALSE(clock.start(args));
        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (!clock.observed.load(std::memory_order_acquire) &&
               std::chrono::steady_clock::now() < deadline) {
            std::this_thread::yield();
        }
        ASSERT_TRUE(clock.observed.load(std::memory_order_acquire));
        clock.stop();
    }
};

TEST_F(WallClockOwnedSelectionTest, SuppressedSelectionsConsumeReservoirAndEpochCapacity) {
    run();
    EXPECT_EQ(512u, clock.pool);
    EXPECT_EQ(16u, clock.selected);
    EXPECT_EQ(16u, clock.successful);
    EXPECT_EQ(0u, clock.failures);
    EXPECT_EQ(16u, clock.suppressed);
}

TEST_F(WallClockOwnedSelectionTest, FailedSignalsDoNotCountAsSuccessfulSelections) {
    clock.mixed_outcomes = true;
    run();
    EXPECT_EQ(512u, clock.pool);
    EXPECT_EQ(16u, clock.selected);
    EXPECT_EQ(12u, clock.successful);
    EXPECT_EQ(4u, clock.failures);
    EXPECT_EQ(8u, clock.suppressed);
}

TEST_F(WallClockOwnedSelectionTest, ContextScopedSelectionsAreNotSuppressed) {
    auto* registry = Profiler::instance()->threadFilter();
    auto* tracker = Profiler::instance()->blockTracker();
    registry->init("0", false);
    for (int id : slots) {
        auto* slot = registry->slotForId(id);
        ASSERT_TRUE(registry->add(slot->nativeTid(), id));
        u64 token = tracker->enterBlockedRun(registry, id, OSThreadState::SLEEPING);
        ASSERT_NE(0u, token);
        tracker->slotForId(id)->markBlockGenerationSampled(
            WallClockBlockTracker::tokenGeneration(token));
    }
    run();
    EXPECT_EQ(512u, clock.pool);
    EXPECT_EQ(16u, clock.selected);
    EXPECT_EQ(16u, clock.successful);
    EXPECT_EQ(0u, clock.failures);
    EXPECT_EQ(0u, clock.suppressed);
}

// Model a fixed unfiltered population through the production selection/epoch loop.
class UnfilteredWeightWallClock : public BaseWallClock {
public:
    static constexpr int pool_size = 128;
    static constexpr int reservoir_size = 16;
    static constexpr int rounds = 2000;
    int suppressed_population = 112;
    std::atomic<bool> observed{false};
    double effective_weight = 0;
    u32 max_visits = 0;
    u32 max_lookups = 0;
    u64 rejected = 0;
    const char* name() override { return "Unfiltered weighting test timer"; }
private:
    int completed = 0;
    u32 visits = 0;
    u32 signals = 0;
    u32 lookups = 0;
    void observeEpochForTest(const WallClockEpochEvent& epoch) override {
        if (observed.load(std::memory_order_acquire)) return;
        max_visits = std::max(max_visits, visits);
        max_lookups = std::max(max_lookups, lookups);
        if (epoch._num_successful_samples != 0) {
            effective_weight += static_cast<double>(signals) *
                epoch._num_samplable_threads / epoch._num_successful_samples;
        }
        if (++completed == rounds) observed.store(true, std::memory_order_release);
    }
    void timerLoop() override {
        auto collect = [&](std::vector<int>& entries) {
            visits = signals = lookups = 0;
            for (int i = 0; i < pool_size; ++i) entries.push_back(i);
        };
        auto sample = [&](int candidate, int&, int&, int&, int& registry_lookups, bool lookup) {
            ++visits;
            if (lookup) { ++registry_lookups; ++lookups; }
            if (candidate < suppressed_population) {
                if (!observed.load(std::memory_order_acquire)) ++rejected;
                return WallClockCandidateOutcome::PRECHECK_REJECTED;
            }
            ++signals;
            return WallClockCandidateOutcome::SIGNAL_SENT;
        };
        timerLoopCommon<int>(collect, sample, [] {}, reservoir_size, 1000, true);
    }
};

TEST(WallClockUnfilteredSelectionTest, MixedPopulationRetainsEffectiveWeightAndLookupBound) {
    auto previous = std::signal(WAKEUP_SIGNAL, +[](int) {});
    UnfilteredWeightWallClock clock;
    clock.enableEvents(true);
    Arguments args;
    args._wall = 1000;
    ASSERT_FALSE(clock.start(args));
    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(10);
    while (!clock.observed.load(std::memory_order_acquire) &&
           std::chrono::steady_clock::now() < deadline) std::this_thread::yield();
    clock.stop();
    clock.enableEvents(false);
    std::signal(WAKEUP_SIGNAL, previous);
    ASSERT_TRUE(clock.observed.load(std::memory_order_acquire));
    double expected = (clock.pool_size - clock.suppressed_population) * clock.rounds;
    EXPECT_NEAR(expected, clock.effective_weight, expected * 0.15);
    EXPECT_LE(clock.max_visits, clock.reservoir_size);
    EXPECT_LE(clock.max_lookups, clock.reservoir_size);
    EXPECT_GT(clock.max_lookups, 0u);
    EXPECT_GT(clock.rejected, 0u);
}

class ProfilerTestAccessor {
public:
    static void setOmitStacktraces(Profiler* profiler, bool omit) {
        profiler->_omit_stacktraces = omit;
    }
};

TEST_F(WallClockPrecheckTest, LightweightShortBurstsConserveEveryObservation) {
    filter->remove(slot_id);
    ASSERT_FALSE(filter->activeSlotForId(slot_id, kTid)->inContextWindow());
    ASSERT_EQ(BlockRunOwner::NONE, tracker->slotForId(slot_id)->activeBlockOwner());
    ASSERT_TRUE(tracker->slotForId(slot_id)->unownedBlockedFallbackEnabled());
    bool previous = profiler->omitStacktraces();
    ProfilerTestAccessor::setOmitStacktraces(profiler, true);
    u64 emitted_weight = 0;
    for (int burst = 0; burst < 3; ++burst) {
        for (int observation = 0; observation < 7; ++observation) {
            OSThreadState state = observation < 6 ? OSThreadState::SLEEPING
                                                  : OSThreadState::RUNNABLE;
            u64 weight = 0;
            bool suppressed = BaseWallClock::wallPrecheckForTest(
                current.get(), true, state, weight, true);
            if (!suppressed) emitted_weight += weight;
        }
    }
    ProfilerTestAccessor::setOmitStacktraces(profiler, previous);
    EXPECT_EQ(21ULL, emitted_weight);
    EXPECT_EQ(0ULL, tracker->slotForId(slot_id)->unowned_blocked_pending_weight.load());
    EXPECT_EQ(0, Counters::getCounter(WC_UNOWNED_BLOCKED_SUPPRESSED));
}

class EpochWindowBoundaryWallClock : public BaseWallClock {
public:
    int initial_pool = 16;
    int later_pool = 160;
    u64 origin_epoch = 0;
    std::atomic<bool> completed{false};
    std::vector<WallClockEpochEvent> closed;
    const char* name() override { return "Epoch boundary test timer"; }

private:
    void observeClosedEpochForTest(const WallClockEpochEvent& epoch) override {
        closed.push_back(epoch);
    }
    void timerLoop() override {
        int pass = 0;
        auto collect = [&](std::vector<int>& entries) {
            if (pass == 1) origin_epoch = WallClockCounters::samplingEpochStart();
            int population = pass < 10 ? initial_pool : later_pool;
            for (int tid = 0; tid < population; ++tid) entries.push_back(tid);
        };
        auto sample = [](int, int&, int&, int&, int&, bool) {
            return WallClockCandidateOutcome::SIGNAL_SENT;
        };
        auto clean = [&] {
            if (++pass > 11) completed.store(true, std::memory_order_release);
        };
        timerLoopCommon<int>(collect, sample, clean, 16, 1000000);
    }
};

TEST(WallClockSamplingEpochTest, PopulationBoundaryClosesWithPriorScaleInBothDirections) {
    auto previous_handler = std::signal(WAKEUP_SIGNAL, +[](int) {});
    for (const auto& pools : {std::pair<int, int>{16, 160}, {160, 16}}) {
        EpochWindowBoundaryWallClock clock;
        clock.initial_pool = pools.first;
        clock.later_pool = pools.second;
        clock.enableEvents(true);
        Arguments args;
        args._wall = 1000000;
        bool started = !clock.start(args);
        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (started && !clock.completed.load(std::memory_order_acquire) &&
               std::chrono::steady_clock::now() < deadline) std::this_thread::yield();
        clock.stop();
        clock.enableEvents(false);
        EXPECT_TRUE(started);
        EXPECT_TRUE(clock.completed.load());
        bool found = false;
        for (const auto& epoch : clock.closed) {
            if (epoch._start_time != clock.origin_epoch) continue;
            found = true;
            EXPECT_EQ(static_cast<u32>(pools.first), epoch._num_samplable_threads);
            EXPECT_EQ(16u, epoch._num_successful_samples);
            double effective = 9.0 * epoch._num_samplable_threads / epoch._num_successful_samples;
            EXPECT_DOUBLE_EQ(9.0 * pools.first / 16, effective);
        }
        EXPECT_TRUE(found) << "The original sampling window was not closed";
    }
    std::signal(WAKEUP_SIGNAL, previous_handler);
}
