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

// ── StringArena concurrent chunk growth ───────────────────────────────────
//
// 8 threads each insert 1 000 large keys (≈88 bytes each).
// Total ≈ 8 × 1000 × 88 = 704 KB > 512 KB chunk size, so multiple threads
// will hit the chunk boundary simultaneously and race inside grow().
//
// Failure mode: if grow()'s CAS spinlock has a race, two threads could both
// create a new chunk and only one is linked — the other's allocations land in
// an unreachable chunk, corrupting those key strings and causing lookup misses.
// ASan/TSan also catch data races between concurrent alloc() and grow().
TEST(StressStringArena, ConcurrentChunkGrowthNoCorruption) {
    StringDictionaryBuffer buf;
    constexpr int N_THREADS        = 8;
    constexpr int KEYS_PER_THREAD  = 1000;
    const std::string pad(68, 'z');

    std::vector<std::thread> threads;
    // Store per-thread insert results to verify after join.
    std::vector<std::vector<u32>> got(N_THREADS,
                                      std::vector<u32>(KEYS_PER_THREAD, 0));
    for (int t = 0; t < N_THREADS; t++) {
        threads.emplace_back([&buf, &got, t, &pad]() {
            for (int i = 0; i < KEYS_PER_THREAD; i++) {
                std::string key = "cg_" + std::to_string(t)
                                + "_" + std::to_string(i) + "_" + pad;
                u32 id = static_cast<u32>(t * KEYS_PER_THREAD + i + 1);
                got[t][i] = buf.insert_with_id(key.c_str(), key.size(), id);
            }
        });
    }
    for (auto& th : threads) th.join();

    // Every key was unique so every insert must have succeeded.
    // If a key's arena region was clobbered by a concurrent alloc, the
    // stored string is corrupted and lookup returns 0 or the wrong id.
    for (int t = 0; t < N_THREADS; t++) {
        for (int i = 0; i < KEYS_PER_THREAD; i++) {
            u32 expected = static_cast<u32>(t * KEYS_PER_THREAD + i + 1);
            EXPECT_EQ(expected, got[t][i])
                << "insert failed for thread " << t << " key " << i;
            std::string key = "cg_" + std::to_string(t)
                            + "_" + std::to_string(i) + "_" + pad;
            EXPECT_EQ(expected, buf.lookup(key.c_str(), key.size()))
                << "lookup failed for thread " << t << " key " << i;
        }
    }
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

// ── rotate() without external lock ────────────────────────────────────────
//
// Production change: rotate() is called before lockAll() in rotateDictsAndRun().
// This test verifies that the standby snapshot is complete and correct when
// rotate() runs with NO external mutex while concurrent inserts are live.
//
// Failure mode: if rotate() needed lockAll() for correctness, concurrent inserts
// during Phase 1→Phase 2 would produce a standby missing entries or with wrong
// IDs, and the EXPECT_EQ assertions below would fire.
//
// Also run under TSan to catch ordering violations between the rotator and the
// concurrent inserters that rotate()'s internal protocol is supposed to handle.
TEST(StressStringDictionary, RotateWithoutMutexPreservesStandbySnapshot) {
    StringDictionary dict;
    constexpr int N_INSERTERS   = 6;
    constexpr int SEED_KEYS     = 50;
    constexpr int N_ROTATIONS   = 30;

    // Phase 1: pre-insert seed keys and record their ids.
    auto seed_keys = makeKeys(99, SEED_KEYS);
    std::unordered_map<std::string, u32> seed_ids;
    for (auto& k : seed_keys) seed_ids[k] = dict.lookup(k.c_str(), k.size());

    std::atomic<bool> done{false};

    // Concurrent inserters run the whole time — no mutex protecting rotate().
    std::vector<std::thread> inserters;
    for (int t = 0; t < N_INSERTERS; t++) {
        inserters.emplace_back([&dict, &done, t]() {
            auto keys = makeKeys(t, 200);
            int idx = 0;
            while (!done.load(std::memory_order_relaxed)) {
                auto& k = keys[idx++ % (int)keys.size()];
                dict.lookup(k.c_str(), k.size());
            }
        });
    }

    // Rotator: rotate without holding any external mutex, then verify standby.
    for (int r = 0; r < N_ROTATIONS; r++) {
        dict.rotate();  // no lockAll() — this is the invariant under test

        std::map<u32, const char*> snap;
        dict.standby()->collect(snap);
        for (auto& kv : seed_ids) {
            EXPECT_EQ(1u, snap.count(kv.second))
                << "rotation " << r << ": standby missing id " << kv.second
                << " for key '" << kv.first << "'";
        }

        dict.clearStandby();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    done.store(true);
    for (auto& th : inserters) th.join();
}

// ── clearAll() without external lock ──────────────────────────────────────
//
// Production change: clearAll() is called without lockAll() wrapper in
// Profiler::start(). This test verifies that clearAll()'s internal protocol
// (_accepting=false + RefCountGuard drain) is sufficient on its own.
//
// Failure mode: if clearAll() needed lockAll() to be safe, concurrent
// bounded_lookup() or lookup() calls that slip through the _accepting gate
// could dereference freed key memory — caught by ASan as a use-after-free.
// Without ASan the test would still catch it via crash or assertion failure.
//
// Contrast with ClearAllUnderConcurrentReaders, which uses a shared_mutex to
// model the *caller's* quiescing protocol.  This test exercises the dictionary
// entirely lock-free, proving the internal mechanism is self-contained.
TEST(StressStringDictionary, ClearAllWithoutExternalLockIsSafe) {
    StringDictionary dict;
    constexpr int N_INSERTERS  = 4;
    constexpr int N_READERS    = 4;
    constexpr int N_CLEAR_OPS  = 25;
    constexpr int SOAK_MS      = 1200;

    std::atomic<bool> done{false};

    std::vector<std::thread> inserters;
    for (int t = 0; t < N_INSERTERS; t++) {
        inserters.emplace_back([&dict, &done, t]() {
            auto keys = makeKeys(t, 80);
            int idx = 0;
            while (!done.load(std::memory_order_relaxed)) {
                auto& k = keys[idx++ % (int)keys.size()];
                dict.lookup(k.c_str(), k.size());
            }
        });
    }

    std::vector<std::thread> readers;
    for (int t = 0; t < N_READERS; t++) {
        readers.emplace_back([&dict, &done, t]() {
            auto keys = makeKeys(t + 100, 40);
            int idx = 0;
            while (!done.load(std::memory_order_relaxed)) {
                auto& k = keys[idx++ % (int)keys.size()];
                dict.bounded_lookup(k.c_str(), k.size());
            }
        });
    }

    // Clearer: call clearAll() with no external lock — internal mechanism only.
    std::thread clearer([&dict, &done]() {
        for (int i = 0; i < N_CLEAR_OPS && !done.load(std::memory_order_relaxed); i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(40));
            dict.clearAll();  // no lockAll() wrapper — this is the invariant under test
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(SOAK_MS));
    done.store(true);
    clearer.join();
    for (auto& th : inserters) th.join();
    for (auto& th : readers) th.join();

    SUCCEED();
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
