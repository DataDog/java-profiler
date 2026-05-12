/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * AC-3 / AC-4: Stress-test for Dictionary concurrent access.
 *
 * TWO sub-tests are provided:
 *
 *  1. BrokenPath_DirectLookupRacesWithClear
 *     Calls Dictionary::lookup() directly (no SpinLock) while another thread
 *     calls Dictionary::clear() under exclusive lock.  On the *unfixed* code
 *     this reproduced the UAF SIGSEGV.  With ASAN it produces a
 *     heap-use-after-free error.  Without ASAN, the test is expected to crash
 *     or produce corrupt results non-deterministically.
 *
 *     NOTE: This sub-test is intentionally structured to fail on unfixed code.
 *     It is guarded by a preprocessor macro STRESS_BROKEN_PATH_ENABLED so that
 *     it can be excluded from normal CI runs where the unfixed crash would
 *     break the test suite.  To validate the UAF behaviour, build with
 *     -DSTRESS_BROKEN_PATH_ENABLED=1 and AddressSanitizer.
 *
 *  2. FixedPath_LockedLookupRacesWithClear
 *     Wraps every lookup in tryLockShared() / unlockShared(), mirroring the
 *     Profiler::lookupClassSignalSafe() pattern.  Runs for at least 500 ms and must
 *     complete without any crash or data corruption.
 *
 * Key types used:
 *   Dictionary   – dictionary.h  (lookup, clear)
 *   SpinLock     – spinLock.h    (lock/unlock, tryLockShared/unlockShared)
 */

#include <gtest/gtest.h>
#include "dictionary.h"
#include "spinLock.h"
#include "../../main/cpp/gtest_crash_handler.h"

#include <atomic>
#include <chrono>
#include <cstring>
#include <string>
#include <thread>
#include <vector>

static constexpr const char STRESS_DICT_TEST_NAME[] = "StressDictionary";

// ---------------------------------------------------------------------------
// Helper: populate a Dictionary with a representative set of class-name keys.
// Returns the number of inserted entries.
// ---------------------------------------------------------------------------
static int populateDictionary(Dictionary& dict, int count) {
    int inserted = 0;
    for (int i = 0; i < count; ++i) {
        // Build a synthetic class name such as "Lcom/example/Class0000;"
        char buf[64];
        int len = snprintf(buf, sizeof(buf), "Lcom/example/Class%04d;", i);
        unsigned int id = dict.lookup(buf, (size_t)len);
        if (id > 0) ++inserted;
    }
    return inserted;
}

// ---------------------------------------------------------------------------
// Common probe keys – a slice that will be looked up during the stress loop.
// We keep these as fixed-length byte arrays so no heap allocation is needed
// inside the lookup threads.
// ---------------------------------------------------------------------------
static const char* PROBE_KEYS[] = {
    "Lcom/example/Class0000;",
    "Lcom/example/Class0025;",
    "Lcom/example/Class0049;",
    "Lcom/example/Class0074;",
    "Lcom/example/Class0099;",
};
static constexpr int NUM_PROBE_KEYS = 5;

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------
class StressDictionaryTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<STRESS_DICT_TEST_NAME>();
    }
    void TearDown() override {
        restoreDefaultSignalHandlers();
    }
};

// ===========================================================================
// AC-4 / sub-test 1: BROKEN PATH (direct lookup without lock)
//
// This test is *disabled* in normal builds because it deliberately exercises
// the UAF code path that crashes on the unfixed implementation.  Enable it
// only when validating that the bug reproduces (e.g. with ASAN on old code).
// ===========================================================================
#ifdef STRESS_BROKEN_PATH_ENABLED
TEST_F(StressDictionaryTest, BrokenPath_DirectLookupRacesWithClear) {
    /*
     * WARNING: This test is expected to trigger a heap-use-after-free with
     * AddressSanitizer when run against unfixed code.
     * Without ASAN it may crash with SIGSEGV or silently produce corrupt
     * results.  It is compiled only when STRESS_BROKEN_PATH_ENABLED is
     * defined, and must NOT be included in standard CI.
     */
    SpinLock lock;
    Dictionary dict;
    populateDictionary(dict, 100);

    constexpr auto DURATION = std::chrono::milliseconds(500);
    std::atomic<bool> stop{false};
    std::atomic<int>  cleared{0};

    // Clear thread: holds exclusive lock, calls clear(), then re-populates.
    std::thread clearThread([&] {
        auto deadline = std::chrono::steady_clock::now() + DURATION;
        while (!stop.load(std::memory_order_relaxed) &&
               std::chrono::steady_clock::now() < deadline) {
            lock.lock();
            dict.clear();
            lock.unlock();
            // Re-populate so lookup threads have something to read.
            populateDictionary(dict, 100);
            ++cleared;
        }
        stop.store(true, std::memory_order_release);
    });

    // Lookup threads: call lookup() directly WITHOUT acquiring the lock –
    // this is the UNFIXED / broken code path.
    auto lookupWorker = [&] {
        while (!stop.load(std::memory_order_relaxed)) {
            for (int k = 0; k < NUM_PROBE_KEYS; ++k) {
                const char* key = PROBE_KEYS[k];
                // BROKEN: no lock around lookup() – races with clear().
                (void)dict.lookup(key, strlen(key));
            }
        }
    };

    constexpr int NUM_LOOKUP_THREADS = 4;
    std::vector<std::thread> workers;
    workers.reserve(NUM_LOOKUP_THREADS);
    for (int i = 0; i < NUM_LOOKUP_THREADS; ++i)
        workers.emplace_back(lookupWorker);

    clearThread.join();
    for (auto& t : workers) t.join();

    // If we reach here without a crash, record how many clears happened.
    EXPECT_GT(cleared.load(), 0) << "Clear thread must have run at least once";
    // With ASAN the test would have aborted above with heap-use-after-free.
}
#endif // STRESS_BROKEN_PATH_ENABLED

// ===========================================================================
// AC-3: FIXED PATH – locked lookup races with clear (must not crash)
// ===========================================================================
TEST_F(StressDictionaryTest, FixedPath_LockedLookupRacesWithClear) {
    /*
     * This test mirrors Profiler::lookupClassSignalSafe():
     *   if (_class_map_lock.tryLockShared()) {
     *       int ret = _class_map.lookup_readonly(key, length);
     *       _class_map_lock.unlockShared();
     *       return ret;
     *   }
     *   return -1;
     *
     * The clear thread holds the exclusive lock, which prevents
     * tryLockShared() from succeeding, so lookup threads gracefully skip
     * (return -1) instead of dereferencing freed memory.
     *
     * Duration: at least 500 ms (AC-3).
     * Expected outcome: no crash, no ASAN error.
     */
    SpinLock lock;
    Dictionary dict;
    populateDictionary(dict, 100);

    constexpr auto DURATION = std::chrono::milliseconds(500);
    std::atomic<bool> stop{false};
    std::atomic<int>  cleared{0};
    std::atomic<int>  lookups{0};
    std::atomic<int>  skipped{0};

    // Clear thread: acquires exclusive lock, clears, releases, re-populates.
    std::thread clearThread([&] {
        auto deadline = std::chrono::steady_clock::now() + DURATION;
        while (!stop.load(std::memory_order_relaxed) &&
               std::chrono::steady_clock::now() < deadline) {
            lock.lock();
            dict.clear();
            lock.unlock();
            populateDictionary(dict, 100);
            ++cleared;
        }
        stop.store(true, std::memory_order_release);
    });

    // Lookup threads: FIXED path – tryLockShared() guards every lookup.
    auto lookupWorker = [&] {
        while (!stop.load(std::memory_order_relaxed)) {
            for (int k = 0; k < NUM_PROBE_KEYS; ++k) {
                const char* key = PROBE_KEYS[k];
                if (lock.tryLockShared()) {
                    // FIXED: shared lock held, mirrors signal-safe path.
                    (void)dict.lookup_readonly(key, strlen(key));
                    lock.unlockShared();
                    lookups.fetch_add(1, std::memory_order_relaxed);
                } else {
                    // Lock not acquired – graceful skip, matches AC-2.
                    skipped.fetch_add(1, std::memory_order_relaxed);
                }
            }
        }
    };

    constexpr int NUM_LOOKUP_THREADS = 4;
    std::vector<std::thread> workers;
    workers.reserve(NUM_LOOKUP_THREADS);
    for (int i = 0; i < NUM_LOOKUP_THREADS; ++i)
        workers.emplace_back(lookupWorker);

    clearThread.join();
    for (auto& t : workers) t.join();

    // Sanity checks: the race window must have been exercised.
    EXPECT_GT(cleared.load(), 0)
        << "Clear thread must have executed at least once";
    EXPECT_GT(lookups.load() + skipped.load(), 0)
        << "Lookup threads must have executed at least some iterations";
    // AC-3: no crash means we reach this assertion.
    SUCCEED() << "Fixed-path stress completed without crash. cleared="
              << cleared.load() << " lookups=" << lookups.load()
              << " skipped=" << skipped.load();
}

// ===========================================================================
// AC-3 variant: extended duration (1 s) with higher thread count
// ===========================================================================
TEST_F(StressDictionaryTest, FixedPath_ExtendedDuration_NoRace) {
    SpinLock lock;
    Dictionary dict;
    populateDictionary(dict, 200);

    // Run for at least 1 000 ms to satisfy the '>= 500 ms' requirement with
    // margin.
    constexpr auto DURATION = std::chrono::milliseconds(1000);
    std::atomic<bool> stop{false};
    std::atomic<int>  cycles{0};

    std::thread clearThread([&] {
        auto deadline = std::chrono::steady_clock::now() + DURATION;
        while (std::chrono::steady_clock::now() < deadline) {
            lock.lock();
            dict.clear();
            lock.unlock();
            populateDictionary(dict, 200);
            ++cycles;
        }
        stop.store(true, std::memory_order_release);
    });

    constexpr int NUM_LOOKUP_THREADS = 8;
    std::vector<std::thread> workers;
    workers.reserve(NUM_LOOKUP_THREADS);
    for (int i = 0; i < NUM_LOOKUP_THREADS; ++i) {
        workers.emplace_back([&] {
            while (!stop.load(std::memory_order_relaxed)) {
                for (int k = 0; k < NUM_PROBE_KEYS; ++k) {
                    const char* key = PROBE_KEYS[k];
                    if (lock.tryLockShared()) {
                        (void)dict.lookup_readonly(key, strlen(key));
                        lock.unlockShared();
                    }
                    // else: graceful skip
                }
            }
        });
    }

    clearThread.join();
    for (auto& t : workers) t.join();

    EXPECT_GT(cycles.load(), 0);
    SUCCEED() << "Extended fixed-path stress completed. clear cycles=" << cycles.load();
}

// ===========================================================================
// Verify lookup_readonly does not insert keys (allocation-safety by invariant)
//
// lookup_readonly calls the internal lookup(key, length, for_insert=false, 0).
// With for_insert=false, the code path that calls allocateKey()/malloc() is
// never reached.  We verify this by design: after calling lookup_readonly on
// keys that were never inserted, re-calling lookup_readonly must still return
// 0 (miss), proving no insertion — and therefore no heap allocation — occurred.
// ===========================================================================
TEST_F(StressDictionaryTest, LookupReadonly_DoesNotInsertKeys) {
    SpinLock lock;
    Dictionary dict;
    // Pre-populate some keys
    populateDictionary(dict, 50);

    // Keys that were never inserted — lookup_readonly must not insert them.
    const char* ghost_keys[] = {
        "Lcom/example/Ghost0;",
        "Lcom/example/Ghost1;",
        "Lcom/example/Ghost2;",
    };
    constexpr int NUM_GHOST_KEYS = 3;

    constexpr auto DURATION = std::chrono::milliseconds(300);
    std::atomic<bool> stop{false};
    std::atomic<int>  lookups{0};
    std::atomic<int>  violations{0};

    std::thread clearThread([&] {
        auto deadline = std::chrono::steady_clock::now() + DURATION;
        while (std::chrono::steady_clock::now() < deadline) {
            lock.lock();
            dict.clear();
            lock.unlock();
            populateDictionary(dict, 50);
        }
        stop.store(true, std::memory_order_release);
    });

    // Lookup threads use lookup_readonly (the signal-handler-safe path).
    auto lookupWorker = [&] {
        while (!stop.load(std::memory_order_relaxed)) {
            for (int k = 0; k < NUM_GHOST_KEYS; ++k) {
                if (lock.tryLockShared()) {
                    unsigned int id = dict.lookup_readonly(ghost_keys[k], strlen(ghost_keys[k]));
                    lock.unlockShared();
                    if (id != 0u) {
                        violations.fetch_add(1, std::memory_order_relaxed);
                    }
                }
            }
            lookups.fetch_add(1, std::memory_order_relaxed);
        }
    };

    constexpr int NUM_LOOKUP_THREADS = 4;
    std::vector<std::thread> workers;
    workers.reserve(NUM_LOOKUP_THREADS);
    for (int i = 0; i < NUM_LOOKUP_THREADS; ++i)
        workers.emplace_back(lookupWorker);

    clearThread.join();
    for (auto& t : workers) t.join();

    EXPECT_GT(lookups.load(), 0);
    int v = violations.load();
    EXPECT_EQ(0, v)
        << "lookup_readonly inserted a ghost key in " << v
        << " iteration(s) -- no-insert invariant violated";
    if (v == 0) SUCCEED() << "lookup_readonly did not insert any ghost key. iterations=" << lookups.load();
}
