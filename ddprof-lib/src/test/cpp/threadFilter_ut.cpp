/*
 * Copyright 2025, 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>
#include "counters.h"
#include "nativeMem.h"
#include "threadFilter.h"
#include "wallClockBlockTracker.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include <thread>
#include <vector>
#include <atomic>
#include <algorithm>
#include <set>
#include <chrono>

// Test name for crash handler
static constexpr char THREAD_FILTER_TEST_NAME[] = "ThreadFilterTest";

class ThreadFilterTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Install crash handler for debugging potential issues
        installGtestCrashHandler<THREAD_FILTER_TEST_NAME>();
        filter = std::make_unique<ThreadFilter>();
        filter->init("enabled");  // Enable filtering with non-empty string
        tracker = std::make_unique<WallClockBlockTracker>();
        filter->setBlockTracker(tracker.get());
    }

    void TearDown() override {
        filter.reset();
        tracker.reset();
        // Restore default signal handlers
        restoreDefaultSignalHandlers();
    }

    std::unique_ptr<ThreadFilter> filter;
    std::unique_ptr<WallClockBlockTracker> tracker;
};

// Basic functionality tests
TEST_F(ThreadFilterTest, BasicRegisterAndAccept) {
    EXPECT_TRUE(filter->enabled());
    
    int slot_id = filter->registerThread(1234);
    EXPECT_GE(slot_id, 0);
    
    // Initially should not accept (not yet in the context window)
    EXPECT_FALSE(filter->accept(slot_id));
    
    // Add tid and test accept
    filter->add(1234, slot_id);
    EXPECT_TRUE(filter->accept(slot_id));
    
    // Remove and test
    filter->remove(slot_id);
    EXPECT_FALSE(filter->accept(slot_id));
}

TEST_F(ThreadFilterTest, DisabledFilterAcceptsAll) {
    ThreadFilter disabled_filter;
    disabled_filter.init(nullptr);  // Disabled with nullptr

    EXPECT_FALSE(disabled_filter.enabled());
    EXPECT_TRUE(disabled_filter.accept(-1));
    EXPECT_TRUE(disabled_filter.accept(0));
    EXPECT_TRUE(disabled_filter.accept(999999));
}

TEST_F(ThreadFilterTest, EmptyStringDisablesFilter) {
    // Empty string should disable the filter (same as nullptr)
    // This allows 'no-thread-filter' when 'filter' argument is provided without value
    ThreadFilter empty_filter;
    empty_filter.init("");  // Disabled with empty string

    EXPECT_FALSE(empty_filter.enabled());
    EXPECT_TRUE(empty_filter.accept(-1));
    EXPECT_TRUE(empty_filter.accept(0));
    EXPECT_TRUE(empty_filter.accept(999999));

    // When disabled, registerThread() blocks new registrations
    EXPECT_EQ(empty_filter.registerThread(1234), -1);
}

TEST_F(ThreadFilterTest, InvalidSlotHandling) {
    // Test invalid slot IDs for accept() - still safe due to negative check
    EXPECT_FALSE(filter->accept(-1));
    EXPECT_FALSE(filter->accept(-999));
    
    // These should not crash
    filter->add(1234, -1);
    filter->remove(-1);
    filter->unregisterThread(-1);
    filter->unregisterThread(-999);
}

TEST_F(ThreadFilterTest, ValidSlotIDContract) {
    // Verify that all slot IDs returned by registerThread() are valid
    std::vector<int> slot_ids;
    
    for (int i = 0; i < 100; i++) {
        int slot_id = filter->registerThread(i + 10000);
        ASSERT_GE(slot_id, 0) << "registerThread() returned invalid slot_id: " << slot_id;
        ASSERT_LT(slot_id, ThreadFilter::kMaxThreads) << "slot_id out of range: " << slot_id;
        
        slot_ids.push_back(slot_id);
        
        // These operations should always be safe with slot_ids from registerThread()
        filter->add(i + 10000, slot_id);
        EXPECT_TRUE(filter->accept(slot_id));
        filter->remove(slot_id);
        EXPECT_FALSE(filter->accept(slot_id));
    }
    
    // Verify slot IDs are unique (no duplicates)
    std::set<int> unique_slots(slot_ids.begin(), slot_ids.end());
    EXPECT_EQ(unique_slots.size(), slot_ids.size()) << "registerThread() returned duplicate slot IDs";
}

// Edge case: Maximum capacity
TEST_F(ThreadFilterTest, MaxCapacityReached) {
    std::vector<int> slot_ids;
    
    // Register up to the maximum
    for (int i = 0; i < ThreadFilter::kMaxThreads; i++) {
        int slot_id = filter->registerThread(i + 1000);  // Use unique tids
        if (slot_id >= 0) {
            slot_ids.push_back(slot_id);
            filter->add(i + 1000, slot_id);
        }
    }
    
    fprintf(stderr, "Successfully registered %zu slots (max=%d)\n", 
            slot_ids.size(), ThreadFilter::kMaxThreads);
    
    // Should have registered all slots
    EXPECT_EQ(slot_ids.size(), ThreadFilter::kMaxThreads);
    
    // Next registration should fail and make capacity loss observable
#ifdef COUNTERS
    long long capacity_failures_before =
        Counters::getCounter(THREAD_REGISTRY_CAPACITY_EXHAUSTED);
#endif
    int overflow_slot = filter->registerThread(1000 + ThreadFilter::kMaxThreads);
    EXPECT_EQ(overflow_slot, -1);
#ifdef COUNTERS
    EXPECT_EQ(capacity_failures_before + 1,
              Counters::getCounter(THREAD_REGISTRY_CAPACITY_EXHAUSTED));
#endif
    
    // Verify all registered slots work
    std::vector<int> collected_tids;
    filter->collect(collected_tids);
    EXPECT_EQ(collected_tids.size(), ThreadFilter::kMaxThreads);
    
    // Verify all tids are unique
    std::set<int> unique_tids(collected_tids.begin(), collected_tids.end());
    EXPECT_EQ(unique_tids.size(), ThreadFilter::kMaxThreads);
}

// Edge case: Recovery after max capacity
TEST_F(ThreadFilterTest, RecoveryAfterMaxCapacity) {
    std::vector<int> slot_ids;
    
    // Fill to capacity
    for (int i = 0; i < ThreadFilter::kMaxThreads; i++) {
        int slot_id = filter->registerThread(i + 2000);
        ASSERT_GE(slot_id, 0);
        slot_ids.push_back(slot_id);
        filter->add(i + 2000, slot_id);
    }
    
    // Should fail to register more
    EXPECT_EQ(filter->registerThread(100000), -1);
    
    // Unregister half the slots
    int slots_to_free = ThreadFilter::kMaxThreads / 2;
    for (int i = 0; i < slots_to_free; i++) {
        filter->unregisterThread(slot_ids[i]);
        slot_ids[i] = -1;  // Mark as freed
    }
    
    // Should be able to register new slots again
    std::vector<int> new_slot_ids;
    for (int i = 0; i < slots_to_free; i++) {
        int slot_id = filter->registerThread(i + 5000);
        EXPECT_GE(slot_id, 0) << "Failed to register slot " << i << " after freeing";
        new_slot_ids.push_back(slot_id);
        // Keep replacement identities disjoint from the still-live 3024..4047
        // range. The registry intentionally rejects two slots for one native TID.
        filter->add(i + 5000, slot_id);
    }
    
    // Verify we can still register up to capacity
    EXPECT_EQ(new_slot_ids.size(), slots_to_free);
    
    // Should fail again when at capacity
    EXPECT_EQ(filter->registerThread(100001), -1);
    
    // Verify collect works correctly
    std::vector<int> collected_tids;
    filter->collect(collected_tids);
    EXPECT_EQ(collected_tids.size(), ThreadFilter::kMaxThreads);
}

// Free list stress test
TEST_F(ThreadFilterTest, FreeListStressTest) {
    const int iterations = 1000;
    const int batch_size = 100;
    
    for (int iter = 0; iter < iterations; iter++) {
        std::vector<int> slot_ids;
        
        // Register a batch
        for (int i = 0; i < batch_size; i++) {
            int slot_id = filter->registerThread(iter * batch_size + i);
            ASSERT_GE(slot_id, 0);
            slot_ids.push_back(slot_id);
            filter->add(iter * batch_size + i, slot_id);
        }
        
        // Verify all work
        for (int slot_id : slot_ids) {
            EXPECT_TRUE(filter->accept(slot_id));
        }
        
        // Unregister all
        for (int slot_id : slot_ids) {
            filter->unregisterThread(slot_id);
        }
        
        // Verify cleanup
        std::vector<int> tids;
        filter->collect(tids);
        EXPECT_EQ(tids.size(), 0) << "Iteration " << iter << " left " << tids.size() << " tids";
    }
}

// Multi-threaded edge case testing
TEST_F(ThreadFilterTest, ConcurrentMaxCapacityStress) {
    const int num_threads = 8;
    const int slots_per_thread = ThreadFilter::kMaxThreads / num_threads;
    
    std::vector<std::thread> threads;
    std::atomic<int> successful_registrations{0};
    std::atomic<int> failed_registrations{0};
    std::vector<std::vector<int>> thread_slots(num_threads);
    
    // Each thread tries to register its share of slots
    for (int t = 0; t < num_threads; t++) {
        threads.emplace_back([&, t]() {
            for (int i = 0; i < slots_per_thread + 10; i++) {  // Try to over-register
                int slot_id = filter->registerThread(t * 1000 + i);
                if (slot_id >= 0) {
                    thread_slots[t].push_back(slot_id);
                    filter->add(t * 1000 + i, slot_id);
                    successful_registrations++;
                } else {
                    failed_registrations++;
                }
            }
        });
    }
    
    // Wait for all threads
    for (auto& t : threads) {
        t.join();
    }
    
    fprintf(stderr, "Successful: %d, Failed: %d, Total attempted: %d\n",
            successful_registrations.load(), failed_registrations.load(),
            num_threads * (slots_per_thread + 10));
    
    // Should have registered exactly kMaxThreads
    EXPECT_EQ(successful_registrations.load(), ThreadFilter::kMaxThreads);
    EXPECT_GT(failed_registrations.load(), 0);  // Some should have failed
    
    // Verify collect works
    std::vector<int> collected_tids;
    filter->collect(collected_tids);
    EXPECT_EQ(collected_tids.size(), ThreadFilter::kMaxThreads);
}

// Chunk boundary testing
TEST_F(ThreadFilterTest, ChunkBoundaryBehavior) {
    std::vector<int> slot_ids;
    
    // Register enough slots to span multiple chunks
    int slots_to_register = ThreadFilter::kChunkSize * 3 + 10;  // 3+ chunks
    
    for (int i = 0; i < slots_to_register; i++) {
        int slot_id = filter->registerThread(i + 5000);
        ASSERT_GE(slot_id, 0) << "Failed at slot " << i;
        slot_ids.push_back(slot_id);
        filter->add(i + 5000, slot_id);
    }
    
    // Verify all chunks work correctly
    for (int i = 0; i < slots_to_register; i++) {
        EXPECT_TRUE(filter->accept(slot_ids[i])) << "Slot " << slot_ids[i] << " (index " << i << ") not accepted";
    }
    
    // Test collect across chunks
    std::vector<int> collected_tids;
    filter->collect(collected_tids);
    EXPECT_EQ(collected_tids.size(), slots_to_register);
    
    // Verify tids are correct
    std::sort(collected_tids.begin(), collected_tids.end());
    for (int i = 0; i < slots_to_register; i++) {
        EXPECT_EQ(collected_tids[i], i + 5000) << "TID mismatch at position " << i;
    }
}

// Race condition testing for add/remove/accept
TEST_F(ThreadFilterTest, ConcurrentAddRemoveAccept) {
    const int num_threads = 4;
    const int operations_per_thread = 10000;
    
    // Pre-register slots for each thread
    std::vector<int> slot_ids(num_threads);
    for (int i = 0; i < num_threads; i++) {
        slot_ids[i] = filter->registerThread(i + 6000);
        ASSERT_GE(slot_ids[i], 0);
    }
    
    std::vector<std::thread> threads;
    std::atomic<int> total_operations{0};
    
    for (int t = 0; t < num_threads; t++) {
        threads.emplace_back([&, t]() {
            int slot_id = slot_ids[t];
            int tid = t + 6000;
            
            for (int i = 0; i < operations_per_thread; i++) {
                // Add
                filter->add(tid, slot_id);
                
                // Should accept
                bool accepted = filter->accept(slot_id);
                if (!accepted) {
                    fprintf(stderr, "Thread %d: accept failed after add (op %d)\n", t, i);
                }
                
                // Remove
                filter->remove(slot_id);
                
                // Should not accept
                accepted = filter->accept(slot_id);
                if (accepted) {
                    fprintf(stderr, "Thread %d: accept succeeded after remove (op %d)\n", t, i);
                }
                
                total_operations++;
            }
        });
    }
    
    // Wait for all threads
    for (auto& t : threads) {
        t.join();
    }
    
    EXPECT_EQ(total_operations.load(), num_threads * operations_per_thread);
    
    // Final state should be empty
    std::vector<int> final_tids;
    filter->collect(final_tids);
    EXPECT_EQ(final_tids.size(), 0);
}

// Free list exhaustion and recovery
TEST_F(ThreadFilterTest, FreeListExhaustionRecovery) {
    // Fill up the free list by registering and unregistering
    std::vector<int> slot_ids;
    
    // Register many slots
    for (int i = 0; i < ThreadFilter::kFreeListSize + 100; i++) {
        int slot_id = filter->registerThread(i + 7000);
        if (slot_id >= 0) {
            slot_ids.push_back(slot_id);
            filter->add(i + 7000, slot_id);
        }
    }
    
    fprintf(stderr, "Registered %zu slots\n", slot_ids.size());
    
    // Unregister all (this should fill the free list)
    for (int slot_id : slot_ids) {
        filter->unregisterThread(slot_id);
    }
    
    // Try to register new slots - should reuse from free list
    std::vector<int> new_slot_ids;
    for (int i = 0; i < 100; i++) {
        int slot_id = filter->registerThread(i + 8000);
        EXPECT_GE(slot_id, 0) << "Failed to reuse slot " << i;
        new_slot_ids.push_back(slot_id);
        filter->add(i + 8000, slot_id);
    }
    
    // Verify reused slots work
    for (int slot_id : new_slot_ids) {
        EXPECT_TRUE(filter->accept(slot_id));
    }
    
    std::vector<int> final_tids;
    filter->collect(final_tids);
    EXPECT_EQ(final_tids.size(), new_slot_ids.size());
}

TEST_F(ThreadFilterTest, PerformanceRegression) {
    const int num_operations = 100000;

    // Pre-register slots
    std::vector<int> slot_ids;
    for (int i = 0; i < 100; i++) {
        int slot_id = filter->registerThread(i);
        ASSERT_GE(slot_id, 0);
        slot_ids.push_back(slot_id);
    }

    // Baseline: a plain atomic load + release store pair, measured on this
    // machine/run rather than assumed, so the comparison below is immune to
    // absolute clock-speed differences across CI hosts (a fixed ns ceiling
    // is not).
    std::atomic<u64> baseline_state{0};
    auto baseline_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_operations; i++) {
        u64 v = baseline_state.load(std::memory_order_relaxed);
        baseline_state.store(v + 1, std::memory_order_release);
    }
    auto baseline_end = std::chrono::high_resolution_clock::now();
    double baseline_ns_per_op =
        (double)std::chrono::duration_cast<std::chrono::nanoseconds>(baseline_end - baseline_start)
            .count() /
        num_operations;

    auto start = std::chrono::high_resolution_clock::now();

    // Perform many add/accept/remove operations
    for (int i = 0; i < num_operations; i++) {
        int slot_id = slot_ids[i % slot_ids.size()];
        filter->add(i % slot_ids.size(), slot_id);
        bool accepted = filter->accept(slot_id);
        EXPECT_TRUE(accepted);
        filter->remove(slot_id);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double ns_per_op = (double)duration.count() * 1000.0 / num_operations;

    fprintf(stderr,
            "Performance: %d operations in %ld microseconds (%.2f ns/op, baseline "
            "load+store: %.2f ns/op)\n",
            num_operations, duration.count(), ns_per_op, baseline_ns_per_op);

    // Compare against a baseline measured in this same run instead of a fixed
    // ns ceiling (see ContextWindowEnterExitPerformance below for the same
    // pattern). This test additionally does TID hashing via accept(), so it
    // gets a larger multiplier than the plain add()/remove() pair.
    EXPECT_LT(ns_per_op, baseline_ns_per_op * 25.0 + 20.0);
}

// Isolates the cost of add()/remove() (i.e. Slot::enterContextWindow()/
// exitContextWindow()) from accept()'s TID hashing, since this pair runs on
// every context-window transition for every context-filtered recording.
TEST_F(ThreadFilterTest, ContextWindowEnterExitPerformance) {
    const int num_operations = 1000000;

    constexpr int tid = 4242;
    int slot_id = filter->registerThread(tid);
    ASSERT_GE(slot_id, 0);

    // Baseline: a plain atomic load + release store pair, measured on this
    // machine/run rather than assumed, so the comparison below is immune to
    // absolute clock-speed differences across CI hosts (a fixed ns ceiling
    // is not).
    std::atomic<u64> baseline_state{0};
    auto baseline_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_operations; i++) {
        u64 v = baseline_state.load(std::memory_order_relaxed);
        baseline_state.store(v + 1, std::memory_order_release);
    }
    auto baseline_end = std::chrono::high_resolution_clock::now();
    double baseline_ns_per_op =
        (double)std::chrono::duration_cast<std::chrono::nanoseconds>(baseline_end - baseline_start)
            .count() /
        num_operations;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_operations; i++) {
        filter->add(tid, slot_id);
        filter->remove(slot_id);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double ns_per_op = (double)duration.count() * 1000.0 / (num_operations * 2);

    fprintf(stderr,
            "ContextWindow enter/exit: %d pairs in %ld microseconds (%.2f ns/op, baseline "
            "load+store: %.2f ns/op)\n",
            num_operations, duration.count(), ns_per_op, baseline_ns_per_op);

    // Compare against a baseline measured in this same run instead of a
    // fixed ns ceiling, so the assertion isn't sensitive to CI host speed.
    // add()/remove() does a bare load + release store plus a couple of
    // cheap extra checks (tid match, chunk lookup) on top of the baseline's
    // single load+store, so a generous multiplier still catches a
    // regression back to a CAS retry loop or worse, which would cost
    // several times more, not a fraction more. The flat floor absorbs
    // timer-resolution noise when the baseline itself measures near zero.
    EXPECT_LT(ns_per_op, baseline_ns_per_op * 15.0 + 20.0);
}

// Collect behavior with mixed states
TEST_F(ThreadFilterTest, CollectMixedStates) {
    std::vector<int> slot_ids;
    std::vector<int> expected_tids;
    
    // Register slots and add some tids, leave others empty
    for (int i = 0; i < 50; i++) {
        int slot_id = filter->registerThread(i + 9000);
        ASSERT_GE(slot_id, 0);
        slot_ids.push_back(slot_id);
        
        if (i % 3 == 0) {  // Add tid to every 3rd slot
            filter->add(i + 9000, slot_id);
            expected_tids.push_back(i + 9000);
        }
        // Leave other slots empty
    }
    
    // Collect should only return slots with tids
    std::vector<int> collected_tids;
    filter->collect(collected_tids);
    
    std::sort(expected_tids.begin(), expected_tids.end());
    std::sort(collected_tids.begin(), collected_tids.end());
    
    EXPECT_EQ(collected_tids.size(), expected_tids.size());
    for (size_t i = 0; i < expected_tids.size(); i++) {
        EXPECT_EQ(collected_tids[i], expected_tids[i]);
    }
}

TEST_F(ThreadFilterTest, ClearActiveDropsPreviousRecordingMembership) {
    int stale_slot = filter->registerThread(1111);
    int current_slot = filter->registerThread(2222);
    ASSERT_GE(stale_slot, 0);
    ASSERT_GE(current_slot, 0);

    filter->add(1111, stale_slot);
    filter->add(2222, current_slot);
    tracker->enterBlockedRun(filter.get(), stale_slot, OSThreadState::SLEEPING);
    WallClockBlockTracker::BlockState *stale = tracker->slotForId(stale_slot);
    ASSERT_NE(nullptr, stale);
    stale->markSampledThisRun(OSThreadState::SLEEPING);

    filter->clearActive();

    std::vector<int> collected_tids;
    filter->collect(collected_tids);
    EXPECT_TRUE(collected_tids.empty());
    EXPECT_FALSE(filter->accept(stale_slot));
    EXPECT_FALSE(filter->accept(current_slot));
    EXPECT_FALSE(stale->sampledThisRun());
    EXPECT_EQ(OSThreadState::UNKNOWN, stale->lastSampledState());
    EXPECT_EQ(OSThreadState::UNKNOWN, stale->activeBlockState());

    filter->add(2222, current_slot);
    filter->collect(collected_tids);
    ASSERT_EQ(1u, collected_tids.size());
    EXPECT_EQ(2222, collected_tids[0]);
}

// GenerationCheckedExitDoesNotClearAnotherOwner and NewGenerationRejectsStaleToken
// moved to wallClockBlockTracker_ut.cpp - they exercise pure WallClockBlockTracker
// generation-token behavior with no ThreadFilter-identity interaction.

TEST_F(ThreadFilterTest, TokenRoundTripPreservesHighGenerationBit) {
    ThreadFilter::SlotID slot_id = 7;
    u32 generation = 0x80000001u;
    u64 token = WallClockBlockTracker::encodeBlockRunToken(slot_id, generation);
    int64_t java_token = static_cast<int64_t>(token);

    EXPECT_LT(java_token, 0);
    EXPECT_EQ(slot_id, WallClockBlockTracker::tokenSlotId(static_cast<u64>(java_token)));
    EXPECT_EQ(generation, WallClockBlockTracker::tokenGeneration(static_cast<u64>(java_token)));
}

class ThreadRegistryTest : public ::testing::Test {
protected:
    void SetUp() override {
        registry.init("", true);
        registry.setBlockTracker(&tracker);
    }

    ThreadFilter registry;
    WallClockBlockTracker tracker;
};

TEST_F(ThreadRegistryTest, UnfilteredTrackingSeparatesRegistrationFromContextWindow) {

    EXPECT_TRUE(registry.registryActive());
    EXPECT_TRUE(registry.unfilteredWallTrackingActive());
    EXPECT_FALSE(registry.enabled());

    int slot_id = registry.registerThread(1234);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = registry.slotForId(slot_id);
    ASSERT_NE(nullptr, slot);
    EXPECT_EQ(1234, slot->nativeTid());
    EXPECT_FALSE(slot->inContextWindow());
    EXPECT_EQ(slot, registry.lookupByTid(1234));

    std::vector<ThreadEntry> context;
    registry.collect(context);
    EXPECT_TRUE(context.empty());

    registry.add(1234, slot_id);
    registry.collect(context);
    ASSERT_EQ(1u, context.size());
    EXPECT_EQ(1234, context[0].tid);

    registry.remove(slot_id);
    EXPECT_FALSE(slot->inContextWindow());
    EXPECT_EQ(slot, registry.lookupByTid(1234));
    registry.collect(context);
    EXPECT_TRUE(context.empty());
}

TEST_F(ThreadRegistryTest, RegisteringKnownTidReturnsExistingSlotWithoutMutation) {
    constexpr int tid = 4321;
    int slot_id = registry.registerThread(tid);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = registry.slotForId(slot_id);
    ASSERT_NE(nullptr, slot);

    u64 token = tracker.enterBlockedRun(&registry, slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0ULL, token);
    WallClockBlockTracker::BlockState* block_slot = tracker.slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    block_slot->markSampledThisRun(OSThreadState::SLEEPING);

    u64 lifecycle_generation = slot->lifecycleGeneration();
    EXPECT_EQ(slot_id, registry.registerThread(tid));
    EXPECT_EQ(slot, registry.lookupByTid(tid));
    EXPECT_EQ(lifecycle_generation, slot->lifecycleGeneration());
    EXPECT_EQ(OSThreadState::SLEEPING, block_slot->activeBlockState());
    EXPECT_TRUE(block_slot->sampledThisRun());
    EXPECT_TRUE(tracker.exitBlockedRun(
        slot_id, WallClockBlockTracker::tokenGeneration(token)));
}

TEST_F(ThreadRegistryTest, UnregisterByTidForUnknownTidIsNoOp) {
    constexpr int registered_tid = 1111;
    constexpr int unknown_tid = 2222;
    int slot_id = registry.registerThread(registered_tid);
    ASSERT_GE(slot_id, 0);

    registry.unregisterThreadByTid(unknown_tid);

    // The unrelated, already-registered slot must be untouched.
    EXPECT_NE(nullptr, registry.lookupByTid(registered_tid));
    EXPECT_EQ(nullptr, registry.lookupByTid(unknown_tid));
}

TEST_F(ThreadRegistryTest, UnregisterByTidFreesTheMatchingSlot) {
    constexpr int tid = 3333;
    int slot_id = registry.registerThread(tid);
    ASSERT_GE(slot_id, 0);
    ASSERT_NE(nullptr, registry.lookupByTid(tid));

    registry.unregisterThreadByTid(tid);

    EXPECT_EQ(nullptr, registry.lookupByTid(tid));
    // The freed slot must be available for reuse rather than leaked.
    int reused_slot_id = registry.registerThread(tid + 1);
    EXPECT_EQ(slot_id, reused_slot_id);
}

TEST_F(ThreadRegistryTest, LookupByTidPopulatesOutSlotId) {
    constexpr int tid = 4444;
    int slot_id = registry.registerThread(tid);
    ASSERT_GE(slot_id, 0);

    ThreadFilter::SlotID found_slot_id = -1;
    ThreadFilter::Slot* slot = registry.lookupByTid(tid, &found_slot_id);
    ASSERT_NE(nullptr, slot);
    EXPECT_EQ(slot_id, found_slot_id);

    found_slot_id = -1;
    EXPECT_EQ(nullptr, registry.lookupByTid(tid + 1, &found_slot_id));
    EXPECT_EQ(-1, found_slot_id);
}

// add() validates ownership against the slot's published tid. The two tests
// below cover the ways a cached slot id goes stale: the slot belongs to another
// thread, or an unfiltered init() reset it (and it may since have been handed
// out again).
TEST_F(ThreadRegistryTest, AddRejectsSlotOwnedByAnotherTid) {
    constexpr int tid = 5555;
    int slot_a = registry.registerThread(tid);
    int slot_b = registry.registerThread(tid + 1);
    ASSERT_GE(slot_a, 0);
    ASSERT_GE(slot_b, 0);
    ASSERT_NE(slot_a, slot_b);
    ThreadFilter::Slot* slot_b_ptr = registry.slotForId(slot_b);
    ASSERT_NE(nullptr, slot_b_ptr);
    u64 state_before = slot_b_ptr->rawContextWindowState();

    // A stale cached slot id must never let one thread write another
    // thread's context-window state.
    EXPECT_FALSE(registry.add(tid, slot_b));
    EXPECT_FALSE(slot_b_ptr->inContextWindow());
    EXPECT_EQ(state_before, slot_b_ptr->rawContextWindowState());
    EXPECT_EQ(registry.slotForId(slot_a), registry.lookupByTid(tid));
    EXPECT_EQ(slot_b_ptr, registry.lookupByTid(tid + 1));

    EXPECT_TRUE(registry.add(tid + 1, slot_b));
    EXPECT_TRUE(slot_b_ptr->inContextWindow());
}

TEST_F(ThreadRegistryTest, StaleAddAfterUnfilteredResetDoesNotResurrectSlot) {
    constexpr int stale_tid = 7001;
    constexpr int new_tid = 7002;
    int stale_slot = registry.registerThread(stale_tid);
    ASSERT_GE(stale_slot, 0);
    ThreadFilter::Slot* slot = registry.slotForId(stale_slot);
    ASSERT_NE(nullptr, slot);

    // A new unfiltered recording resets every registration; the thread still
    // holds its old slot id in TLS.
    registry.init("", true);
    ASSERT_EQ(-1, slot->nativeTid());

    // The allocator now considers the slot free: add() must not re-publish
    // the stale tid into it.
    EXPECT_FALSE(registry.add(stale_tid, stale_slot));
    EXPECT_EQ(-1, slot->nativeTid());
    EXPECT_EQ(nullptr, registry.lookupByTid(stale_tid));
    EXPECT_FALSE(slot->inContextWindow());

    // Once the slot is handed to another thread, the stale owner still must
    // not mark it in-context.
    int reassigned = registry.registerThread(new_tid);
    ASSERT_EQ(stale_slot, reassigned);
    EXPECT_FALSE(registry.add(stale_tid, stale_slot));
    EXPECT_EQ(new_tid, slot->nativeTid());
    EXPECT_FALSE(slot->inContextWindow());
    EXPECT_EQ(nullptr, registry.lookupByTid(stale_tid));

    // The stale thread re-registers into a slot of its own.
    int fresh = registry.registerThread(stale_tid);
    ASSERT_GE(fresh, 0);
    EXPECT_NE(stale_slot, fresh);
    EXPECT_TRUE(registry.add(stale_tid, fresh));
}

TEST_F(ThreadRegistryTest, RegisterThreadRejectsNegativeTid) {
    EXPECT_EQ(-1, registry.registerThread(-1));
    EXPECT_FALSE(registry.add(-1, 0));
}

TEST_F(ThreadRegistryTest, ConcurrentSameTidRegistrationConvergesOnOneSlot) {
    constexpr int thread_count = 32;
    constexpr int tid = 8765;
    std::atomic<int> ready{0};
    std::atomic<bool> start{false};
    std::vector<int> slots(thread_count, -1);
    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back([&, i] {
            ready.fetch_add(1, std::memory_order_release);
            while (!start.load(std::memory_order_acquire)) {
                std::this_thread::yield();
            }
            slots[i] = registry.registerThread(tid);
        });
    }

    while (ready.load(std::memory_order_acquire) != thread_count) {
        std::this_thread::yield();
    }
    start.store(true, std::memory_order_release);
    for (std::thread& thread : threads) {
        thread.join();
    }

    ASSERT_GE(slots[0], 0);
    for (int slot_id : slots) {
        EXPECT_EQ(slots[0], slot_id);
    }
    ThreadFilter::Slot* slot = registry.slotForId(slots[0]);
    ASSERT_NE(nullptr, slot);
    EXPECT_EQ(tid, slot->nativeTid());
    EXPECT_EQ(slot, registry.lookupByTid(tid));
}

TEST_F(ThreadRegistryTest, ContextWindowTransitionsAreIdempotent) {
    int slot_id = registry.registerThread(5678);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = registry.slotForId(slot_id);
    ASSERT_NE(nullptr, slot);

    u64 initial_epoch = slot->contextWindowEpoch();
    registry.add(5678, slot_id);
    EXPECT_TRUE(slot->inContextWindow());
    EXPECT_EQ(initial_epoch + 1, slot->contextWindowEpoch());

    registry.add(5678, slot_id);
    EXPECT_EQ(initial_epoch + 1, slot->contextWindowEpoch());

    registry.remove(slot_id);
    EXPECT_FALSE(slot->inContextWindow());
    EXPECT_EQ(initial_epoch + 2, slot->contextWindowEpoch());

    registry.remove(slot_id);
    EXPECT_EQ(initial_epoch + 2, slot->contextWindowEpoch());
}

TEST_F(ThreadRegistryTest, SlotReuseChangesLifecycleGenerationAndTidMapping) {
    int slot_id = registry.registerThread(1111);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = registry.slotForId(slot_id);
    ASSERT_NE(nullptr, slot);
    u64 first_generation = slot->lifecycleGeneration();

    registry.unregisterThread(slot_id);
    EXPECT_EQ(nullptr, registry.lookupByTid(1111));

    int reused_id = registry.registerThread(2222);
    ASSERT_EQ(slot_id, reused_id);
    EXPECT_GT(slot->lifecycleGeneration(), first_generation);
    EXPECT_EQ(nullptr, registry.lookupByTid(1111));
    EXPECT_EQ(slot, registry.lookupByTid(2222));
}

TEST_F(ThreadRegistryTest, ContextTransitionInvalidatesOwnedRunSuppression) {
    int slot_id = registry.registerThread(3333);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = registry.slotForId(slot_id);
    ASSERT_NE(nullptr, slot);

    u64 token = tracker.enterBlockedRun(&registry, slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0u, token);
    WallClockBlockTracker::BlockState* block_slot = tracker.slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    block_slot->markSampledThisRun(OSThreadState::SLEEPING);
    EXPECT_TRUE(block_slot->activeBlockRemainedOutsideContextWindow(slot));

    registry.add(3333, slot_id);
    registry.remove(slot_id);
    EXPECT_FALSE(block_slot->activeBlockRemainedOutsideContextWindow(slot));

    ThreadEntry entry{3333, slot, slot_id, slot->lifecycleGeneration(),
                      slot->recordingEpoch()};
    EXPECT_FALSE(tracker.shouldSuppressOwnedBlock(&registry, entry));
}

TEST_F(ThreadRegistryTest, UnfilteredSuppressionValidatesIdentityAndLifecycle) {
    int slot_id = registry.registerThread(4444);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = registry.slotForId(slot_id);
    ASSERT_NE(nullptr, slot);

    u64 token = tracker.enterBlockedRun(&registry, slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0u, token);
    WallClockBlockTracker::BlockState* block_slot = tracker.slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    block_slot->markSampledThisRun(OSThreadState::SLEEPING);
    ThreadEntry entry{4444, slot, slot_id, slot->lifecycleGeneration(),
                      slot->recordingEpoch()};
    EXPECT_TRUE(tracker.shouldSuppressOwnedBlock(&registry, entry));

    ThreadEntry wrong_tid{4445, slot, slot_id, entry.lifecycle_generation,
                          entry.recording_epoch};
    EXPECT_FALSE(tracker.shouldSuppressOwnedBlock(&registry, wrong_tid));
    ThreadEntry stale_generation{4444, slot, slot_id, entry.lifecycle_generation + 1,
                                 entry.recording_epoch};
    EXPECT_FALSE(tracker.shouldSuppressOwnedBlock(&registry, stale_generation));

    EXPECT_TRUE(tracker.exitBlockedRun(
        slot_id, WallClockBlockTracker::tokenGeneration(token)));
    EXPECT_FALSE(tracker.shouldSuppressOwnedBlock(&registry, entry));
}

TEST_F(ThreadRegistryTest, ContextFilteredSuppressionPreservesHistoricalEligibility) {
    registry.init("0");
    int slot_id = registry.registerThread(5555);
    ASSERT_GE(slot_id, 0);
    registry.add(5555, slot_id);
    ThreadFilter::Slot* slot = registry.slotForId(slot_id);
    ASSERT_NE(nullptr, slot);

    u64 token = tracker.enterBlockedRun(&registry, slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0u, token);
    WallClockBlockTracker::BlockState* block_slot = tracker.slotForId(slot_id);
    ASSERT_NE(nullptr, block_slot);
    block_slot->markSampledThisRun(OSThreadState::SLEEPING);
    ThreadEntry entry{5555, slot, slot_id, slot->lifecycleGeneration(),
                      slot->recordingEpoch()};
    EXPECT_TRUE(tracker.shouldSuppressOwnedBlock(&registry, entry));
}

TEST_F(ThreadRegistryTest, ConcurrentTidReuseInvalidatesSuppressionSnapshot) {
    constexpr int tid = 5601;
    int slot_id = registry.registerThread(tid);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = registry.slotForId(slot_id);
    ASSERT_NE(nullptr, slot);
    ASSERT_NE(0u, tracker.enterBlockedRun(&registry, slot_id, OSThreadState::SLEEPING));
    tracker.slotForId(slot_id)->markSampledThisRun(OSThreadState::SLEEPING);
    ThreadEntry stale{tid, slot, slot_id, slot->lifecycleGeneration(),
                      slot->recordingEpoch()};

    struct SnapshotPause {
        std::atomic<bool> reached{false};
        std::atomic<bool> resume{false};
    } pause;
    tracker.setSuppressionSnapshotHookForTest(
        [](void* raw) {
            SnapshotPause* pause = static_cast<SnapshotPause*>(raw);
            pause->reached.store(true, std::memory_order_release);
            while (!pause->resume.load(std::memory_order_acquire)) {
                std::this_thread::yield();
            }
        },
        &pause);

    std::atomic<bool> suppressed{true};
    std::thread reader([&] {
        suppressed.store(tracker.shouldSuppressOwnedBlock(&registry, stale),
                         std::memory_order_release);
    });
    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (!pause.reached.load(std::memory_order_acquire) &&
           std::chrono::steady_clock::now() < deadline) {
        std::this_thread::yield();
    }
    if (!pause.reached.load(std::memory_order_acquire)) {
        pause.resume.store(true, std::memory_order_release);
        reader.join();
        tracker.setSuppressionSnapshotHookForTest(nullptr, nullptr);
        GTEST_FAIL() << "Suppression reader did not reach the snapshot barrier";
    }

    registry.unregisterThread(slot_id, tid);
    int reused_id = registry.registerThread(tid);
    ThreadFilter::Slot* reused = registry.slotForId(reused_id);
    u64 new_token = tracker.enterBlockedRun(&registry, reused_id, OSThreadState::SLEEPING);
    if (reused != nullptr && new_token != 0) {
        tracker.slotForId(reused_id)->markSampledThisRun(OSThreadState::SLEEPING);
    }

    pause.resume.store(true, std::memory_order_release);
    reader.join();
    tracker.setSuppressionSnapshotHookForTest(nullptr, nullptr);

    ASSERT_EQ(slot_id, reused_id);
    ASSERT_NE(nullptr, reused);
    ASSERT_NE(0u, new_token);
    EXPECT_FALSE(suppressed.load(std::memory_order_acquire));
}

TEST_F(ThreadRegistryTest, TidIndexRemainsReusableAcrossLongThreadChurn) {
    for (int tid = 1; tid <= ThreadFilter::kTidIndexSize * 3; ++tid) {
        int slot_id = registry.registerThread(tid);
        ASSERT_GE(slot_id, 0) << "tid=" << tid;
        ThreadFilter::Slot* slot = registry.slotForId(slot_id);
        ASSERT_EQ(slot, registry.lookupByTid(tid));
        registry.unregisterThread(slot_id);
        ASSERT_EQ(nullptr, registry.lookupByTid(tid));
    }
}

TEST_F(ThreadRegistryTest, ConfigurationSeparatesFilterAndUnfilteredTracking) {
    registry.init("0", false);
    EXPECT_TRUE(registry.enabled());
    EXPECT_TRUE(registry.registryActive());
    EXPECT_FALSE(registry.unfilteredWallTrackingActive());

    registry.init("", false);
    EXPECT_FALSE(registry.enabled());
    EXPECT_FALSE(registry.registryActive());
    EXPECT_FALSE(registry.unfilteredWallTrackingActive());

    registry.init("", true);
    EXPECT_FALSE(registry.enabled());
    EXPECT_TRUE(registry.registryActive());
    EXPECT_TRUE(registry.unfilteredWallTrackingActive());
}

TEST_F(ThreadRegistryTest, NewUnfilteredRecordingReclaimsRetainedSlot) {
    constexpr int tid = 6101;
    int slot_id = registry.registerThread(tid);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = registry.slotForId(slot_id);
    ASSERT_NE(nullptr, slot);
    u64 first_lifecycle_generation = slot->lifecycleGeneration();
    ThreadFilter::RecordingEpoch first_epoch = registry.recordingEpoch();
    ASSERT_NE(0u, first_epoch);
    EXPECT_EQ(slot, registry.lookupByTid(tid, first_epoch));

    u64 token = tracker.enterBlockedRun(&registry, slot_id, OSThreadState::SLEEPING);
    ASSERT_NE(0u, token);
    tracker.slotForId(slot_id)->markSampledThisRun(OSThreadState::SLEEPING);
    ThreadEntry stale{tid, slot, slot_id, slot->lifecycleGeneration(),
                      slot->recordingEpoch()};
    ASSERT_TRUE(tracker.shouldSuppressOwnedBlock(&registry, stale));

    registry.init("", true);
    ThreadFilter::RecordingEpoch second_epoch = registry.recordingEpoch();
    ASSERT_NE(first_epoch, second_epoch);
    EXPECT_EQ(nullptr, registry.lookupByTid(tid, first_epoch));
    EXPECT_EQ(nullptr, registry.lookupByTid(tid, second_epoch));
    EXPECT_EQ(nullptr, registry.lookupByTid(tid));
    EXPECT_EQ(-1, slot->nativeTid());
    EXPECT_GT(slot->lifecycleGeneration(), first_lifecycle_generation);
    EXPECT_FALSE(tracker.shouldSuppressOwnedBlock(&registry, stale));

    EXPECT_EQ(slot_id, registry.registerThread(tid));
    EXPECT_EQ(slot, registry.lookupByTid(tid, second_epoch));
    WallClockBlockTracker::BlockState* block_slot = tracker.slotForId(slot_id);
    EXPECT_FALSE(block_slot->sampledThisRun());
    EXPECT_EQ(OSThreadState::UNKNOWN, block_slot->activeBlockState());
    EXPECT_EQ(BlockRunOwner::NONE, block_slot->activeBlockOwner());
}

TEST_F(ThreadRegistryTest, NewUnfilteredRecordingReclaimsFullCapacity) {
    for (int i = 0; i < ThreadFilter::kMaxThreads; ++i) {
        ASSERT_GE(registry.registerThread(10000 + i), 0) << "tid index=" << i;
    }
    ASSERT_EQ(-1, registry.registerThread(20000));

    registry.init("", true);

    EXPECT_EQ(nullptr, registry.lookupByTid(10000));
    for (int i = 0; i < ThreadFilter::kMaxThreads; ++i) {
        ASSERT_GE(registry.registerThread(30000 + i), 0) << "tid index=" << i;
    }
    EXPECT_EQ(-1, registry.registerThread(40000));
}

TEST_F(ThreadRegistryTest, ExpectedTidProtectsReusedSlotDuringTeardown) {
    int slot_id = registry.registerThread(6105);
    ASSERT_GE(slot_id, 0);
    registry.unregisterThread(slot_id, 9999);
    EXPECT_NE(nullptr, registry.lookupByTid(6105));

    registry.unregisterThread(slot_id, 6105);
    EXPECT_EQ(nullptr, registry.lookupByTid(6105));
}

TEST_F(ThreadRegistryTest, DeactivationMakesSlotsIneligibleWithoutClearingStorage) {
    constexpr int tid = 6106;
    int slot_id = registry.registerThread(tid);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::Slot* slot = registry.slotForId(slot_id);
    ASSERT_NE(nullptr, slot);
    ThreadFilter::RecordingEpoch epoch = registry.recordingEpoch();

    registry.deactivateRecording();
    EXPECT_FALSE(registry.registryActive());
    EXPECT_FALSE(registry.unfilteredWallTrackingActive());
    EXPECT_EQ(0u, registry.recordingEpoch());
    EXPECT_EQ(nullptr, registry.lookupByTid(tid, epoch));
    EXPECT_EQ(slot, registry.lookupByTid(tid));
    EXPECT_EQ(-1, registry.registerThread(7777));
}

TEST_F(ThreadRegistryTest, RegisterThreadRechecksActiveAfterLockAcquired) {
    // Simulates a concurrent deactivateRecording() landing in the window
    // between registerThread()'s pre-lock _registry_active check and its
    // acquisition of _registry_lock.
    registry.setPostActiveCheckHookForTest(
        [](void* arg) { static_cast<ThreadFilter*>(arg)->deactivateRecording(); },
        &registry);
    int slot_id = registry.registerThread(8888);
    registry.setPostActiveCheckHookForTest(nullptr, nullptr);

    EXPECT_EQ(-1, slot_id);
}

// Counts registerThread() calls that reach _registry_lock acquisition.
static void countLockAttempt(void* arg) {
    static_cast<std::atomic<int>*>(arg)->fetch_add(1, std::memory_order_relaxed);
}

static void fillRegistry(ThreadFilter& registry, int first_tid, std::vector<int>* slot_ids = nullptr) {
    for (int i = 0; i < ThreadFilter::kMaxThreads; ++i) {
        int slot_id = registry.registerThread(first_tid + i);
        ASSERT_GE(slot_id, 0) << "tid index=" << i;
        if (slot_ids != nullptr) {
            slot_ids->push_back(slot_id);
        }
    }
}

TEST_F(ThreadRegistryTest, FullRegistryRejectsUnknownTidWithoutLocking) {
    fillRegistry(registry, 10000);

    std::atomic<int> lock_attempts{0};
    registry.setPostActiveCheckHookForTest(countLockAttempt, &lock_attempts);
#ifdef COUNTERS
    long long capacity_failures_before =
        Counters::getCounter(THREAD_REGISTRY_CAPACITY_EXHAUSTED);
#endif
    // Threads past capacity retry on every hook call; none may reach the lock.
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(-1, registry.registerThread(20000 + (i % 4)));
    }
    registry.setPostActiveCheckHookForTest(nullptr, nullptr);

    EXPECT_EQ(0, lock_attempts.load());
#ifdef COUNTERS
    // Rejections stay observable even though they skip the locked path.
    EXPECT_EQ(capacity_failures_before + 100,
              Counters::getCounter(THREAD_REGISTRY_CAPACITY_EXHAUSTED));
#endif
}

TEST_F(ThreadRegistryTest, FullRegistryStillReturnsExistingSlotForKnownTid) {
    std::vector<int> slot_ids;
    fillRegistry(registry, 10000, &slot_ids);

    // A thread whose cached slot id was cleared must still recover its own
    // slot through the locked path while the registry is full.
    EXPECT_EQ(slot_ids[5], registry.registerThread(10005));
    EXPECT_EQ(slot_ids[ThreadFilter::kMaxThreads - 1],
              registry.registerThread(10000 + ThreadFilter::kMaxThreads - 1));
}

TEST_F(ThreadRegistryTest, FreedSlotReopensRegistrationAfterExhaustion) {
    fillRegistry(registry, 10000);
    ASSERT_EQ(-1, registry.registerThread(20000));

    registry.unregisterThreadByTid(10000);
    int reused = registry.registerThread(20000);
    EXPECT_GE(reused, 0);
    EXPECT_NE(nullptr, registry.lookupByTid(20000));

    // Full again once the freed slot has been taken.
    std::atomic<int> lock_attempts{0};
    registry.setPostActiveCheckHookForTest(countLockAttempt, &lock_attempts);
    EXPECT_EQ(-1, registry.registerThread(20001));
    registry.setPostActiveCheckHookForTest(nullptr, nullptr);
    EXPECT_EQ(0, lock_attempts.load());
}

TEST_F(ThreadRegistryTest, UnfilteredResetReopensRegistrationAfterExhaustion) {
    fillRegistry(registry, 10000);
    ASSERT_EQ(-1, registry.registerThread(20000));

    registry.init("", true);

    std::atomic<int> lock_attempts{0};
    registry.setPostActiveCheckHookForTest(countLockAttempt, &lock_attempts);
    EXPECT_GE(registry.registerThread(20000), 0);
    registry.setPostActiveCheckHookForTest(nullptr, nullptr);
    EXPECT_EQ(1, lock_attempts.load());
}

TEST_F(ThreadFilterTest, FullContextFilterRejectsWithoutLocking) {
    // The default context-filter mode shares the same registry and retry path.
    for (int i = 0; i < ThreadFilter::kMaxThreads; ++i) {
        ASSERT_GE(filter->registerThread(30000 + i), 0) << "tid index=" << i;
    }

    std::atomic<int> lock_attempts{0};
    filter->setPostActiveCheckHookForTest(countLockAttempt, &lock_attempts);
    EXPECT_EQ(-1, filter->registerThread(40000));
    filter->setPostActiveCheckHookForTest(nullptr, nullptr);
    EXPECT_EQ(0, lock_attempts.load());
}

// The tid index lives inside the process-lifetime Profiler's ThreadFilter, so
// embedding it would keep it resident from library load even for recordings
// that never activate the registry (no context filter, no unfiltered precheck).
static constexpr long long kTidIndexBytes =
    (long long)(ThreadFilter::kTidIndexSize * sizeof(std::atomic<int>));

TEST(ThreadFilterTidIndexStorageTest, FilterEmbedsNoTidIndex) {
    EXPECT_LT((long long)sizeof(ThreadFilter), kTidIndexBytes);
}

TEST(ThreadFilterTidIndexStorageTest, TidIndexIsAllocatedOnFirstRegistryActivationOnly) {
    ThreadFilter filter;
    const long long constructed = NativeMem::live(NM_THREAD_FILTER);

    filter.init("");  // no context filter, no unfiltered tracking: registry stays inactive
    ASSERT_FALSE(filter.registryActive());
    EXPECT_EQ(constructed, NativeMem::live(NM_THREAD_FILTER));

    filter.init("1");
    ASSERT_TRUE(filter.registryActive());
    EXPECT_EQ(constructed + kTidIndexBytes, NativeMem::live(NM_THREAD_FILTER));

    // Later activations, in either registry mode, reuse the same index.
    filter.init("", true);
    ASSERT_TRUE(filter.registryActive());
    filter.init("1");
    EXPECT_EQ(constructed + kTidIndexBytes, NativeMem::live(NM_THREAD_FILTER));

    ThreadFilter::SlotID slot_id = filter.registerThread(9001);
    ASSERT_GE(slot_id, 0);
    ThreadFilter::SlotID found = -1;
    EXPECT_NE(nullptr, filter.lookupByTid(9001, &found));
    EXPECT_EQ(slot_id, found);
}

TEST(ThreadFilterTidIndexStorageTest, TidLookupsBeforeActivationFindNothing) {
    ThreadFilter filter;
    const long long constructed = NativeMem::live(NM_THREAD_FILTER);
    ThreadFilter::SlotID found = 123;

    EXPECT_EQ(nullptr, filter.lookupByTid(9101, &found));
    EXPECT_EQ(-1, found);
    EXPECT_EQ(nullptr, filter.lookupByTid(9101, 1, &found));
    filter.unregisterThreadByTid(9101);  // ThreadEnd path, runs for every exiting thread
    EXPECT_EQ(-1, filter.registerThread(9101));
    EXPECT_EQ(constructed, NativeMem::live(NM_THREAD_FILTER));
}
