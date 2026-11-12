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
#include "counters.h"
#include "profiler.h"
#include "wallClock.h"

#include <memory>

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

TEST_F(WallClockPrecheckTest, UnownedFallbackStillAccumulatesWeightWhenEnabled) {
    u64 weight = 0;
    EXPECT_FALSE(BaseWallClock::wallPrecheckForTest(
        current.get(), true, OSThreadState::SLEEPING, weight, true));
    EXPECT_EQ(1ULL, weight);
    for (int observation = 0; observation < 9; ++observation) {
        EXPECT_TRUE(BaseWallClock::wallPrecheckForTest(
            current.get(), true, OSThreadState::SLEEPING, weight));
    }
    EXPECT_FALSE(BaseWallClock::wallPrecheckForTest(
        current.get(), true, OSThreadState::SLEEPING, weight, true));
    EXPECT_EQ(10ULL, weight);
    EXPECT_EQ(9, Counters::getCounter(WC_UNOWNED_BLOCKED_SUPPRESSED));
}

TEST_F(WallClockPrecheckTest, ContextScopedUnownedFallbackResetsWeightAtBoundaries) {
    filter->init("0", false);
    slot_id = filter->registerThread(kTid);
    ASSERT_GE(slot_id, 0);
    current->setFilterSlotId(slot_id);
    ASSERT_TRUE(filter->add(kTid, slot_id));
    u64 weight = 0;
    EXPECT_FALSE(BaseWallClock::wallPrecheckForTest(
        current.get(), true, OSThreadState::SLEEPING, weight, true));
    EXPECT_EQ(1ULL, weight);
    for (int observation = 0; observation < 2; ++observation) {
        EXPECT_TRUE(BaseWallClock::wallPrecheckForTest(
            current.get(), true, OSThreadState::SLEEPING, weight));
    }
    EXPECT_EQ(2ULL, tracker->slotForId(slot_id)->unowned_blocked_pending_weight.load());
    filter->remove(slot_id);
    ASSERT_TRUE(filter->add(kTid, slot_id));
    EXPECT_FALSE(BaseWallClock::wallPrecheckForTest(
        current.get(), true, OSThreadState::SLEEPING, weight, true));
    EXPECT_EQ(1ULL, weight);
}

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
