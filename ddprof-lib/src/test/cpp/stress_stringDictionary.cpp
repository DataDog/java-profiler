/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "stringDictionary.h"
#include <atomic>
#include <chrono>
#include <map>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

// ── helpers ───────────────────────────────────────────────────────────────

static std::vector<std::string> makeKeys(int thread_id, int count) {
    std::vector<std::string> keys;
    keys.reserve(count);
    for (int i = 0; i < count; i++) {
        keys.push_back("t" + std::to_string(thread_id) + "_k" + std::to_string(i));
    }
    return keys;
}

// ── StringDictionaryBuffer concurrent insert + read ────────────────────────

TEST(StressStringDictionaryBuffer, ConcurrentInsertNoCorruption) {
    StringDictionaryBuffer buf;
    constexpr int N_THREADS = 8;
    constexpr int KEYS_PER_THREAD = 500;

    std::vector<std::thread> threads;
    for (int t = 0; t < N_THREADS; t++) {
        threads.emplace_back([&buf, t]() {
            auto keys = makeKeys(t, KEYS_PER_THREAD);
            for (int i = 0; i < (int)keys.size(); i++) {
                u32 id = static_cast<u32>(t * KEYS_PER_THREAD + i + 1);
                buf.insert_with_id(keys[i].c_str(), keys[i].size(), id);
            }
        });
    }
    for (auto& th : threads) th.join();

    EXPECT_LE(buf.size(), N_THREADS * KEYS_PER_THREAD);
    EXPECT_GT(buf.size(), 0);
}

TEST(StressStringDictionaryBuffer, ConcurrentInsertAndLookupNoCorruption) {
    StringDictionaryBuffer buf;
    constexpr int N_WRITERS = 4;
    constexpr int N_READERS = 4;
    constexpr int OPS = 1000;
    std::atomic<bool> stop{false};

    std::vector<std::thread> writers;
    for (int t = 0; t < N_WRITERS; t++) {
        writers.emplace_back([&buf, &stop, t]() {
            auto keys = makeKeys(t, OPS);
            for (int i = 0; i < OPS && !stop.load(std::memory_order_relaxed); i++) {
                buf.insert_with_id(keys[i].c_str(), keys[i].size(),
                                   static_cast<u32>(t * OPS + i + 1));
            }
        });
    }

    std::vector<std::thread> readers;
    for (int t = 0; t < N_READERS; t++) {
        readers.emplace_back([&buf, &stop, t]() {
            while (!stop.load(std::memory_order_relaxed)) {
                std::string key = "t0_k" + std::to_string(t % OPS);
                buf.lookup(key.c_str(), key.size());
            }
        });
    }

    for (auto& th : writers) th.join();
    stop.store(true);
    for (auto& th : readers) th.join();

    SUCCEED();
}

// Same key inserted by multiple threads: exactly one ID must survive and
// all threads must return that same ID.
TEST(StressStringDictionaryBuffer, ConcurrentSameKeyInsertReturnsConsistentId) {
    StringDictionaryBuffer buf;
    constexpr int N_THREADS = 16;
    std::vector<u32> results(N_THREADS, 0);

    std::vector<std::thread> threads;
    for (int t = 0; t < N_THREADS; t++) {
        threads.emplace_back([&buf, &results, t]() {
            // All threads try to insert the same key with different ids.
            results[t] = buf.insert_with_id("shared/Key", 10, static_cast<u32>(t + 1));
        });
    }
    for (auto& th : threads) th.join();

    // All results must be the same value (the winner's id).
    u32 expected = results[0];
    EXPECT_GT(expected, 0u);
    for (int t = 0; t < N_THREADS; t++) {
        EXPECT_EQ(expected, results[t]) << "thread " << t << " got different id";
    }
}

// ── StringDictionary concurrent stress ────────────────────────────────────

// Invariant: once a key is assigned an id, every subsequent bounded_lookup
// must return the same id, across any number of rotations.
TEST(StressStringDictionary, IdStabilityUnderConcurrentRotation) {
    StringDictionary dict;
    constexpr int N_INSERTERS = 4;
    constexpr int KEYS_PER_THREAD = 200;

    // Phase 1: insert all keys and record their ids.
    std::vector<std::unordered_map<std::string, u32>> recorded(N_INSERTERS);
    {
        std::vector<std::thread> inserters;
        for (int t = 0; t < N_INSERTERS; t++) {
            inserters.emplace_back([&dict, &recorded, t]() {
                for (auto& key : makeKeys(t, KEYS_PER_THREAD)) {
                    u32 id = dict.lookup(key.c_str(), key.size());
                    recorded[t][key] = id;
                }
            });
        }
        for (auto& th : inserters) th.join();
    }

    // Phase 2: rotate many times; ids must remain stable.
    constexpr int N_ROTATIONS = 20;
    for (int r = 0; r < N_ROTATIONS; r++) {
        dict.rotate();
        dict.clearStandby();

        for (int t = 0; t < N_INSERTERS; t++) {
            for (auto& kv : recorded[t]) {
                u32 current = dict.bounded_lookup(kv.first.c_str(), kv.first.size());
                EXPECT_EQ(kv.second, current)
                    << "id changed for key '" << kv.first << "' at rotation " << r;
            }
        }
    }
}

// Concurrent inserts AND rotations simultaneously.
TEST(StressStringDictionary, ConcurrentInsertAndRotateNoCorruption) {
    StringDictionary dict;
    constexpr int N_INSERTERS = 6;
    constexpr int KEYS_PER_THREAD = 300;
    std::atomic<bool> done{false};

    std::thread rotator([&dict, &done]() {
        while (!done.load(std::memory_order_relaxed)) {
            dict.rotate();
            dict.clearStandby();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    std::vector<std::thread> inserters;
    for (int t = 0; t < N_INSERTERS; t++) {
        inserters.emplace_back([&dict, t]() {
            for (auto& key : makeKeys(t, KEYS_PER_THREAD)) {
                dict.lookup(key.c_str(), key.size());
            }
        });
    }
    for (auto& th : inserters) th.join();
    done.store(true);
    rotator.join();

    SUCCEED();
}

// bounded_lookup (simulating signal handlers) concurrent with inserts and rotation.
TEST(StressStringDictionary, BoundedLookupSafeUnderConcurrentRotation) {
    StringDictionary dict;
    constexpr int N_INSERTERS = 4;
    constexpr int N_READERS   = 4;
    constexpr int KEYS_PER_THREAD = 200;
    std::atomic<bool> done{false};

    // Pre-insert known keys for readers to probe.
    auto base_keys = makeKeys(99, 50);
    for (auto& key : base_keys) dict.lookup(key.c_str(), key.size());

    std::thread rotator([&dict, &done]() {
        while (!done.load(std::memory_order_relaxed)) {
            dict.rotate();
            dict.clearStandby();
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    });

    std::vector<std::thread> inserters;
    for (int t = 0; t < N_INSERTERS; t++) {
        inserters.emplace_back([&dict, t]() {
            for (auto& key : makeKeys(t, KEYS_PER_THREAD)) {
                dict.lookup(key.c_str(), key.size());
            }
        });
    }

    std::vector<std::thread> readers;
    for (int t = 0; t < N_READERS; t++) {
        readers.emplace_back([&dict, &base_keys, &done]() {
            while (!done.load(std::memory_order_relaxed)) {
                for (auto& key : base_keys) {
                    dict.bounded_lookup(key.c_str(), key.size());
                }
            }
        });
    }

    for (auto& th : inserters) th.join();
    done.store(true);
    rotator.join();
    for (auto& th : readers) th.join();

    SUCCEED();
}

// lookupDuringDump called concurrently with inserts into active.
// Invariant: all keys found or inserted by lookupDuringDump must appear in standby.
TEST(StressStringDictionary, LookupDuringDumpSafeUnderConcurrentInserts) {
    StringDictionary dict;
    constexpr int N_INSERTERS = 4;
    constexpr int KEYS_PER_THREAD = 100;

    // Pre-populate and rotate so lookupDuringDump has a dump buffer.
    for (auto& key : makeKeys(99, 20)) dict.lookup(key.c_str(), key.size());
    dict.rotate();

    // Start inserters FIRST so lookupDuringDump races with active inserts.
    std::atomic<bool> done{false};
    std::vector<std::thread> inserters;
    for (int t = 0; t < N_INSERTERS; t++) {
        inserters.emplace_back([&dict, &done, t]() {
            for (auto& key : makeKeys(t, KEYS_PER_THREAD)) {
                if (done.load(std::memory_order_relaxed)) break;
                dict.lookup(key.c_str(), key.size());
            }
        });
    }

    // Dump thread probes pre-populated keys concurrently with active inserts.
    std::vector<std::pair<std::string, u32>> dump_results;
    for (auto& key : makeKeys(99, 20)) {
        u32 id = dict.lookupDuringDump(key.c_str(), key.size());
        EXPECT_GT(id, 0u) << "lookupDuringDump returned 0 for pre-populated key";
        dump_results.push_back({key, id});
    }

    done.store(true);
    for (auto& th : inserters) th.join();

    // All keys returned by lookupDuringDump must be in the dump buffer (standby).
    std::map<u32, const char*> snap;
    dict.standby()->collect(snap);
    for (auto& kv : dump_results) {
        EXPECT_EQ(1u, snap.count(kv.second))
            << "key '" << kv.first << "' with id " << kv.second << " not in standby";
    }
}
