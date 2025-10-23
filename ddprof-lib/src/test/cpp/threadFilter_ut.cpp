/*
 * Copyright 2025 Datadog, Inc
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
#include "threadFilter.h"
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
        filter->init("");  // Enable filtering
    }

    void TearDown() override {
        filter.reset();
        // Restore default signal handlers
        restoreDefaultSignalHandlers();
    }

    std::unique_ptr<ThreadFilter> filter;
};

// Basic functionality tests
TEST_F(ThreadFilterTest, BasicRegisterAndAccept) {
    EXPECT_TRUE(filter->enabled());
    
    int slot_id = filter->registerThread();
    EXPECT_GE(slot_id, 0);
    
    // Initially should not accept (no tid added)
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
    disabled_filter.init(nullptr);  // Disabled
    
    EXPECT_FALSE(disabled_filter.enabled());
    EXPECT_TRUE(disabled_filter.accept(-1));
    EXPECT_TRUE(disabled_filter.accept(0));
    EXPECT_TRUE(disabled_filter.accept(999999));
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
        int slot_id = filter->registerThread();
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
        int slot_id = filter->registerThread();
        if (slot_id >= 0) {
            slot_ids.push_back(slot_id);
            filter->add(i + 1000, slot_id);  // Use unique tids
        }
    }
    
    fprintf(stderr, "Successfully registered %zu slots (max=%d)\n", 
            slot_ids.size(), ThreadFilter::kMaxThreads);
    
    // Should have registered all slots
    EXPECT_EQ(slot_ids.size(), ThreadFilter::kMaxThreads);
    
    // Next registration should fail
    int overflow_slot = filter->registerThread();
    EXPECT_EQ(overflow_slot, -1);
    
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
        int slot_id = filter->registerThread();
        ASSERT_GE(slot_id, 0);
        slot_ids.push_back(slot_id);
        filter->add(i + 2000, slot_id);
    }
    
    // Should fail to register more
    EXPECT_EQ(filter->registerThread(), -1);
    
    // Unregister half the slots
    int slots_to_free = ThreadFilter::kMaxThreads / 2;
    for (int i = 0; i < slots_to_free; i++) {
        filter->unregisterThread(slot_ids[i]);
        slot_ids[i] = -1;  // Mark as freed
    }
    
    // Should be able to register new slots again
    std::vector<int> new_slot_ids;
    for (int i = 0; i < slots_to_free; i++) {
        int slot_id = filter->registerThread();
        EXPECT_GE(slot_id, 0) << "Failed to register slot " << i << " after freeing";
        new_slot_ids.push_back(slot_id);
        filter->add(i + 3000, slot_id);
    }
    
    // Verify we can still register up to capacity
    EXPECT_EQ(new_slot_ids.size(), slots_to_free);
    
    // Should fail again when at capacity
    EXPECT_EQ(filter->registerThread(), -1);
    
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
            int slot_id = filter->registerThread();
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
                int slot_id = filter->registerThread();
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
        int slot_id = filter->registerThread();
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
        slot_ids[i] = filter->registerThread();
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
        int slot_id = filter->registerThread();
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
        int slot_id = filter->registerThread();
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

// Performance regression test - only run in release builds
#ifdef NDEBUG
TEST_F(ThreadFilterTest, PerformanceRegression) {
    const int num_operations = 100000;
    
    // Pre-register slots
    std::vector<int> slot_ids;
    for (int i = 0; i < 100; i++) {
        int slot_id = filter->registerThread();
        ASSERT_GE(slot_id, 0);
        slot_ids.push_back(slot_id);
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform many add/accept/remove operations
    for (int i = 0; i < num_operations; i++) {
        int slot_id = slot_ids[i % slot_ids.size()];
        filter->add(i, slot_id);
        bool accepted = filter->accept(slot_id);
        EXPECT_TRUE(accepted);
        filter->remove(slot_id);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    fprintf(stderr, "Performance: %d operations in %ld microseconds (%.2f ns/op)\n",
            num_operations, duration.count(), 
            (double)duration.count() * 1000.0 / num_operations);
    
    // Should be fast - less than 200ns per operation is reasonable for this complex test
    EXPECT_LT(duration.count() * 1000.0 / num_operations, 200.0);  // 200ns per op max
}
#endif // NDEBUG

// Collect behavior with mixed states
TEST_F(ThreadFilterTest, CollectMixedStates) {
    std::vector<int> slot_ids;
    std::vector<int> expected_tids;
    
    // Register slots and add some tids, leave others empty
    for (int i = 0; i < 50; i++) {
        int slot_id = filter->registerThread();
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