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
#include "threadIdTable.h"
#include <thread>
#include <vector>
#include <atomic>
#include <algorithm>
#include <set>
#include <unordered_set>

class ThreadIdTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        table = std::make_unique<ThreadIdTable>();
    }

    void TearDown() override {
        table.reset();
    }

    std::unique_ptr<ThreadIdTable> table;
};

// Basic functionality tests
TEST_F(ThreadIdTableTest, BasicInsertAndCollect) {
    // Insert some thread IDs
    table->insert(1001);
    table->insert(1002);
    table->insert(1003);
    
    // Collect and verify
    std::unordered_set<int> result;
    table->collect(result);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_TRUE(result.count(1001));
    EXPECT_TRUE(result.count(1002));
    EXPECT_TRUE(result.count(1003));
}

TEST_F(ThreadIdTableTest, InvalidThreadIdHandling) {
    // Invalid thread ID (0) should be ignored
    table->insert(0);
    
    std::unordered_set<int> result;
    table->collect(result);
    EXPECT_EQ(result.size(), 0);
    
    // Negative thread IDs should still work (they're valid Linux thread IDs)
    table->insert(-1);
    table->collect(result);
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result.count(-1));
}

TEST_F(ThreadIdTableTest, DuplicateInsertions) {
    // Insert same thread ID multiple times
    table->insert(2001);
    table->insert(2001);
    table->insert(2001);
    
    std::unordered_set<int> result;
    table->collect(result);
    
    // Should only appear once
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result.count(2001));
}

TEST_F(ThreadIdTableTest, ClearFunctionality) {
    // Insert some thread IDs
    table->insert(3001);
    table->insert(3002);
    table->insert(3003);
    
    // Verify they're there
    std::unordered_set<int> result;
    table->collect(result);
    EXPECT_EQ(result.size(), 3);
    
    // Clear and verify empty
    table->clear();
    result.clear();
    table->collect(result);
    EXPECT_EQ(result.size(), 0);
}

// Hash collision testing
TEST_F(ThreadIdTableTest, HashCollisions) {
    // Create thread IDs that will hash to the same slot
    // TABLE_SIZE = 256, so tids with same (tid % 256) will collide
    std::vector<int> colliding_tids;
    int base_tid = 1000;
    
    // Generate 10 thread IDs that hash to the same slot
    for (int i = 0; i < 10; i++) {
        int tid = base_tid + (i * 256);  // All will hash to same slot
        colliding_tids.push_back(tid);
        table->insert(tid);
    }
    
    // All should be stored (linear probing should handle collisions)
    std::unordered_set<int> result;
    table->collect(result);
    
    EXPECT_EQ(result.size(), colliding_tids.size());
    for (int tid : colliding_tids) {
        EXPECT_TRUE(result.count(tid)) << "Missing tid: " << tid;
    }
}

// Capacity testing
TEST_F(ThreadIdTableTest, TableCapacityLimits) {
    std::vector<int> inserted_tids;
    
    // Try to insert more than TABLE_SIZE (256) unique thread IDs
    for (int i = 1; i <= 300; i++) {  // More than TABLE_SIZE
        table->insert(i + 10000);  // Use high numbers to avoid conflicts
        inserted_tids.push_back(i + 10000);
    }
    
    // Collect and see how many were actually stored
    std::unordered_set<int> result;
    table->collect(result);
    
    fprintf(stderr, "Inserted %zu tids, collected %zu tids\n", 
            inserted_tids.size(), result.size());
    
    // Should have stored at most TABLE_SIZE (256)
    EXPECT_LE(result.size(), 256);
    
    // All collected tids should be from our inserted set
    for (int tid : result) {
        EXPECT_TRUE(std::find(inserted_tids.begin(), inserted_tids.end(), tid) != inserted_tids.end())
            << "Unexpected tid in result: " << tid;
    }
}

// Concurrent access testing (signal safety)
TEST_F(ThreadIdTableTest, ConcurrentInsertions) {
    const int num_threads = 8;
    const int tids_per_thread = 50;
    
    std::vector<std::thread> threads;
    std::atomic<int> successful_insertions{0};
    std::vector<std::vector<int>> thread_tids(num_threads);
    
    // Each thread inserts its own set of thread IDs
    for (int t = 0; t < num_threads; t++) {
        threads.emplace_back([&, t]() {
            for (int i = 0; i < tids_per_thread; i++) {
                int tid = t * 1000 + i + 20000;  // Unique per thread
                thread_tids[t].push_back(tid);
                table->insert(tid);
                successful_insertions++;
            }
        });
    }
    
    // Wait for all threads
    for (auto& t : threads) {
        t.join();
    }
    
    EXPECT_EQ(successful_insertions.load(), num_threads * tids_per_thread);
    
    // Collect and verify
    std::unordered_set<int> result;
    table->collect(result);
    
    // Should have all unique thread IDs (or at least most of them)
    std::set<int> all_expected_tids;
    for (const auto& thread_tids_vec : thread_tids) {
        for (int tid : thread_tids_vec) {
            all_expected_tids.insert(tid);
        }
    }
    
    fprintf(stderr, "Expected %zu unique tids, collected %zu tids\n", 
            all_expected_tids.size(), result.size());
    
    // Table has fixed capacity of 256, so with 400 unique tids, we expect exactly 256
    EXPECT_EQ(result.size(), std::min(all_expected_tids.size(), (size_t)256));
    
    // All collected tids should be valid
    for (int tid : result) {
        EXPECT_TRUE(all_expected_tids.count(tid)) << "Unexpected tid: " << tid;
    }
}

// Edge case: Realistic thread ID patterns
TEST_F(ThreadIdTableTest, RealisticThreadIds) {
    // Linux thread IDs are typically large numbers
    std::vector<int> realistic_tids = {
        12345, 12346, 12347,  // Sequential
        98765, 98766, 98767,  // Another sequence
        1234567, 1234568,     // Large numbers
        2147483647,           // Max int
        -1, -2, -3            // Negative (valid in some contexts)
    };
    
    for (int tid : realistic_tids) {
        table->insert(tid);
    }
    
    std::unordered_set<int> result;
    table->collect(result);
    
    // Should have all except tid=0 if any
    size_t expected_size = realistic_tids.size();
    EXPECT_EQ(result.size(), expected_size);
    
    for (int tid : realistic_tids) {
        if (tid != 0) {  // 0 is invalid and ignored
            EXPECT_TRUE(result.count(tid)) << "Missing realistic tid: " << tid;
        }
    }
}

// Performance test (release builds only)
#ifdef NDEBUG
TEST_F(ThreadIdTableTest, PerformanceRegression) {
    const int num_operations = 100000;
    std::vector<int> tids;
    
    // Pre-generate thread IDs
    for (int i = 0; i < 100; i++) {
        tids.push_back(i + 30000);
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform many insertions
    for (int i = 0; i < num_operations; i++) {
        table->insert(tids[i % tids.size()]);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    fprintf(stderr, "ThreadIdTable Performance: %d operations in %ld microseconds (%.2f ns/op)\n",
            num_operations, duration.count(), 
            (double)duration.count() * 1000.0 / num_operations);
    
    // Should be very fast for signal-safe operations
    EXPECT_LT(duration.count() * 1000.0 / num_operations, 50.0);  // 50ns per op max
}
#endif // NDEBUG 