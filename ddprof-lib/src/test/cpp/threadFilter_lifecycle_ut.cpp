/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Coverage for three previously-untested cells in the thread-lifecycle ×
 * profiler-state matrix, exercised at the native layer (no JVM required):
 *
 *   Cell 1 – Disabling + teardown: ThreadFilter::unregisterThread races the
 *             clearActive() drain that stop() performs before disabling.
 *   Cell 2 – Enabling + startup:   ThreadFilter::registerThread races a
 *             concurrent init() call that alternately enables/disables the filter.
 *   Cell 3 – Disabled + teardown:  unregisterThread(-1) called when the filter
 *             was never initialised (idle profiler path).
 *
 * All three test cases are runnable under TSan and ASan.
 */
#include "gtest/gtest.h"

#ifdef __linux__

#include "threadFilter.h"
#include "thread.h"
#include "../../main/cpp/gtest_crash_handler.h"

#include <atomic>
#include <thread>
#include <vector>

static constexpr const char TEST_NAME[] = "ThreadFilterLifecycle";
static constexpr int kWorkers = 16;
static constexpr int kIterations = 2000;

// ── Cell 1: unregisterThread racing clearActive (simulated stop() drain) ──────

TEST(ThreadFilterLifecycle, UnregisterRacesClearActive) {
    installGtestCrashHandler<TEST_NAME>();

    ThreadFilter filter;
    filter.init("*");
    ASSERT_TRUE(filter.enabled());

    std::atomic<bool> run{true};

    // Drain thread: simulates what stop() does — clearActive() empties the active
    // slots without disabling the filter, to flush in-flight samples.
    std::thread drainer([&]() {
        while (run.load(std::memory_order_relaxed)) {
            filter.clearActive();
        }
    });

    std::vector<std::thread> workers;
    workers.reserve(kWorkers);
    for (int i = 0; i < kWorkers; i++) {
        workers.emplace_back([&]() {
            for (int j = 0; j < kIterations; j++) {
                ProfiledThread::initCurrentThread();
                ProfiledThread* self = ProfiledThread::current();
                if (!self) {
                    ProfiledThread::release();
                    continue;
                }
                ThreadFilter::SlotID slot = filter.registerThread();
                if (slot >= 0) {
                    filter.add(self->tid(), slot);
                    filter.remove(slot);
                    filter.unregisterThread(slot);
                    self->setFilterSlotId(-1);
                }
                ProfiledThread::release();
            }
        });
    }
    for (auto& t : workers) t.join();
    run.store(false, std::memory_order_relaxed);
    drainer.join();

    restoreDefaultSignalHandlers();
    SUCCEED();
}

// ── Cell 2: registerThread racing concurrent init() enable/disable toggles ────

TEST(ThreadFilterLifecycle, RegisterRacesInit) {
    installGtestCrashHandler<TEST_NAME>();

    ThreadFilter filter;

    std::atomic<bool> run{true};

    // Init thread: alternates between enabling ("*") and disabling (nullptr) the
    // filter, mirroring start()/stop() engine cycling under test conditions.
    std::thread initer([&]() {
        int toggle = 0;
        while (run.load(std::memory_order_relaxed)) {
            // Even: enable ("*"), odd: disable (nullptr / empty string)
            filter.init(toggle++ % 2 == 0 ? "*" : nullptr);
        }
    });

    std::vector<std::thread> workers;
    workers.reserve(kWorkers);
    for (int i = 0; i < kWorkers; i++) {
        workers.emplace_back([&]() {
            for (int j = 0; j < kIterations; j++) {
                // Mirror the production onThreadStart guard: skip if filter disabled.
                if (!filter.enabled()) continue;

                ProfiledThread::initCurrentThread();
                ProfiledThread* self = ProfiledThread::current();
                if (!self) {
                    ProfiledThread::release();
                    continue;
                }
                ThreadFilter::SlotID slot = filter.registerThread();
                if (slot >= 0) {
                    // filter may have been disabled between the enabled() check and
                    // registerThread(); the slot is still valid and must be released.
                    filter.unregisterThread(slot);
                    self->setFilterSlotId(-1);
                }
                ProfiledThread::release();
            }
        });
    }
    for (auto& t : workers) t.join();
    run.store(false, std::memory_order_relaxed);
    initer.join();

    restoreDefaultSignalHandlers();
    SUCCEED();
}

// ── Cell 3: unregisterThread with sentinel slot when filter never init'd ───────

TEST(ThreadFilterLifecycle, UnregisterWithNoInitDoesNotCrash) {
    // No crash handler — single-threaded, expected outcome is "no crash".
    ThreadFilter filter;

    // enabled() must be false without init().
    EXPECT_FALSE(filter.enabled());

    // unregisterThread(-1) is what onThreadEnd calls when filterSlotId() == -1
    // (thread was registered before profiler started, so slot was never assigned).
    // Must not crash, assert, or invoke UB.
    filter.unregisterThread(-1);

    SUCCEED();
}

#endif // __linux__
