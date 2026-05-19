/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "stringDictionary.h"
#include <array>
#include <atomic>
#include <chrono>
#include <map>
#include <mutex>
#include <shared_mutex>
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

// ── Multi-dictionary atomic rotation ──────────────────────────────────────
//
// Mirrors the production pattern in Profiler::dump(): three independent
// StringDictionaries are rotated atomically under a single critical section
// while inserters and signal-style readers run concurrently against all three.
//
// Invariants asserted:
//   - Seed keys recorded before the rotator starts retain stable ids in every
//     dictionary across many rotation cycles (concurrent inserts must not
//     shift them).
//   - After each atomic rotate-of-all-three, every seed id is present in the
//     standby buffer of its dictionary — i.e. the rotation snapshot is
//     consistent across the three dictionaries simultaneously.
TEST(StressStringDictionary, MultiDictionaryAtomicRotation) {
    StringDictionary d1, d2, d3;
    StringDictionary* dicts[3] = {&d1, &d2, &d3};

    constexpr int N_INSERTERS_PER_DICT = 2;
    constexpr int N_READERS            = 3;
    constexpr int SEED_KEY_COUNT       = 40;
    constexpr int SOAK_MS              = 1500;

    // Pre-insert seed keys into all three dicts and record their ids.
    auto seed_keys = makeKeys(99, SEED_KEY_COUNT);
    std::unordered_map<std::string, std::array<u32, 3>> seed_ids;
    for (auto& k : seed_keys) {
        seed_ids[k] = {
            d1.lookup(k.c_str(), k.size()),
            d2.lookup(k.c_str(), k.size()),
            d3.lookup(k.c_str(), k.size())
        };
    }

    std::atomic<bool> done{false};
    std::mutex        rotate_mutex;  // simulates Profiler::lockAll()

    // Rotator: rotate all three atomically, then verify the rotation snapshot.
    std::thread rotator([&]() {
        while (!done.load(std::memory_order_relaxed)) {
            {
                std::lock_guard<std::mutex> lk(rotate_mutex);
                d1.rotate();
                d2.rotate();
                d3.rotate();

                // Atomic snapshot: every seed id is present in every standby.
                std::map<u32, const char*> s1, s2, s3;
                d1.standby()->collect(s1);
                d2.standby()->collect(s2);
                d3.standby()->collect(s3);
                for (auto& kv : seed_ids) {
                    EXPECT_EQ(1u, s1.count(kv.second[0]))
                        << "d1 standby missing seed id " << kv.second[0] << " for '" << kv.first << "'";
                    EXPECT_EQ(1u, s2.count(kv.second[1]))
                        << "d2 standby missing seed id " << kv.second[1] << " for '" << kv.first << "'";
                    EXPECT_EQ(1u, s3.count(kv.second[2]))
                        << "d3 standby missing seed id " << kv.second[2] << " for '" << kv.first << "'";
                }
            }
            d1.clearStandby();
            d2.clearStandby();
            d3.clearStandby();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    // Inserters: per dict, hammer a per-thread key set.  Each inserter loops
    // its key list to keep memory bounded while exercising the lookup path
    // (first iteration inserts; subsequent iterations are hot-hit lookups).
    std::vector<std::thread> inserters;
    for (int d = 0; d < 3; d++) {
        for (int t = 0; t < N_INSERTERS_PER_DICT; t++) {
            inserters.emplace_back([dicts, d, t, &done]() {
                auto keys = makeKeys(d * 10 + t, 100);
                while (!done.load(std::memory_order_relaxed)) {
                    for (auto& k : keys) {
                        dicts[d]->lookup(k.c_str(), k.size());
                    }
                }
            });
        }
    }

    // Readers: signal-style bounded_lookup of seed keys on all three dicts.
    // Ids must remain stable across rotations.
    std::vector<std::thread> readers;
    for (int r = 0; r < N_READERS; r++) {
        readers.emplace_back([&]() {
            while (!done.load(std::memory_order_relaxed)) {
                for (auto& kv : seed_ids) {
                    u32 i1 = d1.bounded_lookup(kv.first.c_str(), kv.first.size());
                    u32 i2 = d2.bounded_lookup(kv.first.c_str(), kv.first.size());
                    u32 i3 = d3.bounded_lookup(kv.first.c_str(), kv.first.size());
                    EXPECT_EQ(kv.second[0], i1) << "d1 id drifted for '" << kv.first << "'";
                    EXPECT_EQ(kv.second[1], i2) << "d2 id drifted for '" << kv.first << "'";
                    EXPECT_EQ(kv.second[2], i3) << "d3 id drifted for '" << kv.first << "'";
                }
            }
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(SOAK_MS));
    done.store(true);
    rotator.join();
    for (auto& th : inserters) th.join();
    for (auto& th : readers) th.join();
}

// ── clearAll under concurrent readers ─────────────────────────────────────
//
// StringDictionary::clearAll() frees every malloc'd key in all three buffers.
// Its contract is that the caller must quiesce signal handlers first
// (cf. RefCountGuard::waitForAllRefCountsToClear in the production callsite).
// This test models that protocol using a std::shared_mutex barrier:
// readers/inserters acquire it shared, the clearer acquires it exclusive.
//
// Under ASan/TSan, this test catches: UAF on freed keys, lost stores from a
// torn clearAll, or any heap corruption from clear-and-reinsert cycles.
//
// Invariants asserted:
//   - No use-after-free, no heap corruption (caught by sanitizers).
//   - Each clearAll-then-reinsert cycle yields a self-consistent id mapping:
//     the same key resolves to one id through all reads in that epoch.
TEST(StressStringDictionary, ClearAllUnderConcurrentReaders) {
    StringDictionary dict;

    constexpr int N_READERS    = 4;
    constexpr int N_INSERTERS  = 2;
    constexpr int N_CLEAR_OPS  = 20;
    constexpr int SOAK_MS      = 1500;

    auto seed_keys = makeKeys(99, 30);

    // shared_mutex: shared = workers; unique = clearer.  Mirrors the production
    // requirement that clearAll runs only after all signal handlers are quiesced.
    std::shared_mutex   epoch_mtx;
    std::atomic<u64>    epoch{0};  // bumped every clearAll; readers re-snapshot ids per epoch

    // Re-seed under exclusive lock.  Returns the per-key id map for this epoch.
    auto reseed = [&](std::unordered_map<std::string, u32>& out) {
        out.clear();
        for (auto& k : seed_keys) {
            out[k] = dict.lookup(k.c_str(), k.size());
        }
    };

    std::unordered_map<std::string, u32> seed_ids;
    reseed(seed_ids);  // initial epoch 0

    std::atomic<bool> done{false};

    // Clearer: bounded number of clearAll cycles, then exits.
    std::thread clearer([&]() {
        for (int i = 0; i < N_CLEAR_OPS && !done.load(std::memory_order_relaxed); i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::unordered_map<std::string, u32> new_ids;
            {
                std::unique_lock<std::shared_mutex> lk(epoch_mtx);
                dict.clearAll();
                reseed(new_ids);
                seed_ids = std::move(new_ids);
                epoch.fetch_add(1, std::memory_order_release);
            }
        }
    });

    // Inserters: arbitrary keys, just to stress the malloc/CAS paths under
    // contention with clearAll cycles.
    std::vector<std::thread> inserters;
    for (int t = 0; t < N_INSERTERS; t++) {
        inserters.emplace_back([&, t]() {
            auto ks = makeKeys(t, 60);
            while (!done.load(std::memory_order_relaxed)) {
                std::shared_lock<std::shared_mutex> lk(epoch_mtx);
                for (auto& k : ks) {
                    dict.lookup(k.c_str(), k.size());
                }
            }
        });
    }

    // Readers: snapshot the current-epoch id map, then verify lookups within
    // the epoch are consistent.  An epoch bump invalidates the snapshot, so
    // re-read it under shared lock on each loop.
    std::vector<std::thread> readers;
    for (int t = 0; t < N_READERS; t++) {
        readers.emplace_back([&]() {
            while (!done.load(std::memory_order_relaxed)) {
                std::shared_lock<std::shared_mutex> lk(epoch_mtx);
                u64 my_epoch = epoch.load(std::memory_order_acquire);
                auto local = seed_ids;  // snapshot under lock
                for (auto& kv : local) {
                    u32 id = dict.bounded_lookup(kv.first.c_str(), kv.first.size());
                    // While the shared lock is held, no clearAll can run, so
                    // the id must equal what reseed recorded for this epoch.
                    EXPECT_EQ(kv.second, id)
                        << "epoch " << my_epoch << " key '" << kv.first
                        << "' expected " << kv.second << " got " << id;
                }
            }
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(SOAK_MS));
    done.store(true);
    clearer.join();
    for (auto& th : inserters) th.join();
    for (auto& th : readers) th.join();
}
