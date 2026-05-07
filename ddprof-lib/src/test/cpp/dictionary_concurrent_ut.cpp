/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <climits>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "dictionary.h"
#include "spinLock.h"
#include "../../main/cpp/gtest_crash_handler.h"

// PROF-14549 regression tests.
//
// These tests pin down two contracts:
//   (1) bounded_lookup(key, length, 0) is read-only (no malloc/calloc) and
//       returns INT_MAX on miss. This is the contract walkVM relies on at
//       hotspotSupport.cpp:388 to be async-signal-safe.
//   (2) Dictionary::collect, when externally guarded by a SpinLock taken
//       shared, can run concurrently with shared-lock inserters and is
//       serialized against an exclusive-lock Dictionary::clear() — matching
//       the protocol Recording::writeClasses now uses around _class_map_lock.
//
// Test name for crash handler
static constexpr char DICTIONARY_CONCURRENT_TEST_NAME[] = "DictionaryConcurrent";

namespace {

class DictionaryConcurrentSetup {
public:
    DictionaryConcurrentSetup() {
        installGtestCrashHandler<DICTIONARY_CONCURRENT_TEST_NAME>();
    }
    ~DictionaryConcurrentSetup() {
        restoreDefaultSignalHandlers();
    }
};

static DictionaryConcurrentSetup dictionary_concurrent_global_setup;

}  // namespace

// (1a) bounded_lookup with size_limit=0 must not insert on miss.
TEST(DictionaryConcurrent, BoundedLookupMissReturnsSentinelAndDoesNotInsert) {
    Dictionary dict(/*id=*/0);

    std::map<unsigned int, const char*> before;
    dict.collect(before);
    ASSERT_TRUE(before.empty());

    const char* key = "Lorg/example/Cold;";
    unsigned int id = dict.bounded_lookup(key, strlen(key), 0);
    EXPECT_EQ(static_cast<unsigned int>(INT_MAX), id);

    std::map<unsigned int, const char*> after;
    dict.collect(after);
    EXPECT_TRUE(after.empty());

    // A second miss on a different key must also leave the dictionary empty.
    const char* key2 = "Lorg/example/Other;";
    unsigned int id2 = dict.bounded_lookup(key2, strlen(key2), 0);
    EXPECT_EQ(static_cast<unsigned int>(INT_MAX), id2);

    std::map<unsigned int, const char*> after2;
    dict.collect(after2);
    EXPECT_TRUE(after2.empty());
}

// (1b) bounded_lookup with size_limit=0 must return the existing id when the
// key is already present (e.g. previously inserted from a non-signal context).
TEST(DictionaryConcurrent, BoundedLookupHitReturnsExistingId) {
    Dictionary dict(/*id=*/0);

    const char* key = "Ljava/util/HashMap;";
    unsigned int inserted_id = dict.lookup(key, strlen(key));
    ASSERT_NE(0u, inserted_id);
    ASSERT_NE(static_cast<unsigned int>(INT_MAX), inserted_id);

    unsigned int looked_up_id = dict.bounded_lookup(key, strlen(key), 0);
    EXPECT_EQ(inserted_id, looked_up_id);
}

// (2) Stress test: shared-lock inserters + exclusive-lock clear + shared-lock
// collect, all driven from separate threads. This mirrors the discipline that
// Recording::writeClasses (shared-lock collect) and Profiler::dump (exclusive-lock
// clear) follow around _class_map_lock. Without the lock, this pattern races
// (and SIGSEGVs on dictionary corruption); with the lock it is well-formed and
// the test passes cleanly under TSan/ASan.
TEST(DictionaryConcurrent, ConcurrentInsertCollectClearWithExternalLock) {
    Dictionary dict(/*id=*/0);
    SpinLock lock;

    constexpr int kWriters = 4;
    constexpr int kKeysPerWriter = 256;
    const auto kDuration = std::chrono::milliseconds(500);

    std::atomic<bool> stop{false};
    std::atomic<long> total_inserts{0};
    std::atomic<long> total_collects{0};
    std::atomic<long> total_clears{0};

    std::vector<std::thread> writers;
    writers.reserve(kWriters);
    for (int w = 0; w < kWriters; ++w) {
        writers.emplace_back([&, w]() {
            char buf[64];
            int counter = 0;
            while (!stop.load(std::memory_order_relaxed)) {
                snprintf(buf, sizeof(buf), "Lcom/example/W%d/K%d;",
                         w, counter % kKeysPerWriter);
                size_t len = strlen(buf);
                lock.lockShared();
                unsigned int id = dict.lookup(buf, len);
                lock.unlockShared();
                EXPECT_NE(static_cast<unsigned int>(INT_MAX), id);
                total_inserts.fetch_add(1, std::memory_order_relaxed);
                ++counter;
            }
        });
    }

    std::thread collector([&]() {
        while (!stop.load(std::memory_order_relaxed)) {
            std::map<unsigned int, const char*> snapshot;
            lock.lockShared();
            dict.collect(snapshot);
            lock.unlockShared();
            // The map may be empty if a clear() just ran; either way it must
            // be a well-formed map of (id, key) pairs that we can iterate.
            for (auto it = snapshot.begin(); it != snapshot.end(); ++it) {
                ASSERT_NE(nullptr, it->second);
            }
            total_collects.fetch_add(1, std::memory_order_relaxed);
        }
    });

    std::thread clearer([&]() {
        while (!stop.load(std::memory_order_relaxed)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            lock.lock();
            dict.clear();
            lock.unlock();
            total_clears.fetch_add(1, std::memory_order_relaxed);
        }
    });

    std::this_thread::sleep_for(kDuration);
    stop.store(true, std::memory_order_relaxed);

    for (auto& t : writers) {
        t.join();
    }
    collector.join();
    clearer.join();

    // Sanity: each role made progress.
    EXPECT_GT(total_inserts.load(), 0L);
    EXPECT_GT(total_collects.load(), 0L);
    EXPECT_GT(total_clears.load(), 0L);
}
