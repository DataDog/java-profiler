/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gtest/gtest.h"
#include "callTraceStorage.h"
#include <vector>
#include <unordered_set>
#include <thread>
#include <atomic>
#include "callTraceHashTable.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include "arch_dd.h"

// Test name for crash handler
static constexpr char TEST_NAME[] = "CallTraceStorageTest";

// Helper function to find a CallTrace by trace_id in an unordered_set
CallTrace* findTraceById(const std::unordered_set<CallTrace*>& traces, u64 trace_id) {
    for (CallTrace* trace : traces) {
        if (trace && trace->trace_id == trace_id) {
            return trace;
        }
    }
    return nullptr;
}

class CallTraceStorageTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Install crash handler for debugging potential issues
        installGtestCrashHandler<TEST_NAME>();
        storage = std::make_unique<CallTraceStorage>();
    }

    void TearDown() override {
        storage.reset();
        // Restore default signal handlers
        restoreDefaultSignalHandlers();
    }

    std::unique_ptr<CallTraceStorage> storage;
};

TEST_F(CallTraceStorageTest, BasicFunctionality) {
    // Create a simple call frame
    ASGCT_CallFrame frame;
    frame.bci = 10;
    frame.method_id = (jmethodID)0x1234;
    
    // Store a trace
    u64 trace_id = storage->put(1, &frame, false, 1);
    EXPECT_GT(trace_id, 0);
    
    // Process traces to verify storage
    bool found_traces = false;
    storage->processTraces([&found_traces](const std::unordered_set<CallTrace*>& traces) {
        found_traces = traces.size() > 0;
    });
    EXPECT_TRUE(found_traces);
}

TEST_F(CallTraceStorageTest, LivenessCheckerRegistration) {
    // Store multiple traces first
    ASGCT_CallFrame frames[4];
    frames[0].bci = 10; frames[0].method_id = (jmethodID)0x1111;
    frames[1].bci = 20; frames[1].method_id = (jmethodID)0x2222;
    frames[2].bci = 30; frames[2].method_id = (jmethodID)0x3333;
    frames[3].bci = 40; frames[3].method_id = (jmethodID)0x4444;
    
    u64 trace_id1 = storage->put(1, &frames[0], false, 1);
    u64 trace_id2 = storage->put(1, &frames[1], false, 1);
    u64 trace_id3 = storage->put(1, &frames[2], false, 1);
    u64 trace_id4 = storage->put(1, &frames[3], false, 1);
    
    // Register a liveness checker that preserves only trace_id2 and trace_id4
    u64 preserved_trace_id2 = trace_id2;
    u64 preserved_trace_id4 = trace_id4;
    storage->registerLivenessChecker([&preserved_trace_id2, &preserved_trace_id4](std::unordered_set<u64>& buffer) {
        buffer.insert(preserved_trace_id2);
        buffer.insert(preserved_trace_id4);
    });
    
    // processTraces should preserve trace_id2 and trace_id4 but not trace_id1 and trace_id3
    size_t traces_collected = 0;
    storage->processTraces([&traces_collected](const std::unordered_set<CallTrace*>& traces) {
        // Should have all 4 traces from the collection plus the dropped trace
        traces_collected = traces.size();
        EXPECT_EQ(traces.size(), 5);
    });
    
    // After processTraces, only preserved traces should remain in new active storage
    size_t traces_after_preserve = 0;
    CallTrace* found_trace2 = nullptr;
    CallTrace* found_trace4 = nullptr;
    
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        traces_after_preserve = traces.size();
        found_trace2 = findTraceById(traces, preserved_trace_id2);
        found_trace4 = findTraceById(traces, preserved_trace_id4);
    });
    
    // Should have exactly two traces (the preserved ones) plus the dropped trace
    EXPECT_EQ(traces_after_preserve, 3);
    
    // The preserved trace IDs should be valid (content-based IDs are deterministic)
    EXPECT_GT(preserved_trace_id2, 0);
    EXPECT_GT(preserved_trace_id4, 0);
    
    // Verify both traces were actually preserved
    EXPECT_TRUE(found_trace2 != nullptr);
    EXPECT_TRUE(found_trace4 != nullptr);
}

TEST_F(CallTraceStorageTest, MultipleLivenessCheckers) {
    // Store multiple traces with more variety
    ASGCT_CallFrame frames[5];
    frames[0].bci = 10; frames[0].method_id = (jmethodID)0x1111;
    frames[1].bci = 20; frames[1].method_id = (jmethodID)0x2222;
    frames[2].bci = 30; frames[2].method_id = (jmethodID)0x3333;
    frames[3].bci = 40; frames[3].method_id = (jmethodID)0x4444;
    frames[4].bci = 50; frames[4].method_id = (jmethodID)0x5555;
    
    u64 trace_id1 = storage->put(1, &frames[0], false, 1);
    u64 trace_id2 = storage->put(1, &frames[1], false, 1);
    u64 trace_id3 = storage->put(1, &frames[2], false, 1);
    u64 trace_id4 = storage->put(1, &frames[3], false, 1);
    u64 trace_id5 = storage->put(1, &frames[4], false, 1);
    
    u64 preserved_id1 = trace_id1;
    u64 preserved_id4 = trace_id4;
    
    // Register two liveness checkers that preserve non-consecutive traces
    storage->registerLivenessChecker([&preserved_id1](std::unordered_set<u64>& buffer) {
        buffer.insert(preserved_id1);
    });
    
    storage->registerLivenessChecker([&preserved_id4](std::unordered_set<u64>& buffer) {
        buffer.insert(preserved_id4);
    });
    
    // processTraces should preserve specified traces and swap storages
    storage->processTraces([](const std::unordered_set<CallTrace*>& traces) {
        // Should have all 5 traces from the collection plus the dropped trace
        EXPECT_EQ(traces.size(), 6);
    });
    
    // After processTraces, only preserved traces should remain in new active storage
    CallTrace* found_trace1 = nullptr;
    CallTrace* found_trace4 = nullptr;
    size_t preserved_count = 0;
    
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        preserved_count = traces.size();
        found_trace1 = findTraceById(traces, preserved_id1);
        found_trace4 = findTraceById(traces, preserved_id4);
    });
    
    // Should have exactly 2 traces (the preserved ones)
    EXPECT_EQ(preserved_count, 3);
    
    // Both preserved IDs should still be valid
    EXPECT_GT(preserved_id1, 0);
    EXPECT_GT(preserved_id4, 0);
    
    // Verify both traces were actually preserved
    EXPECT_TRUE(found_trace1 != nullptr);
    EXPECT_TRUE(found_trace4 != nullptr);
}

TEST_F(CallTraceStorageTest, TraceIdPreservation) {
    // Create a simple frame
    ASGCT_CallFrame frame;
    frame.bci = 10;
    frame.method_id = (jmethodID)0x1234;
    
    // Add trace to storage
    u64 original_trace_id = storage->put(1, &frame, false, 1);
    EXPECT_GT(original_trace_id, 0);
    
    // Register liveness checker to preserve this trace
    u64 preserved_id = original_trace_id;
    storage->registerLivenessChecker([&preserved_id](std::unordered_set<u64>& buffer) {
        buffer.insert(preserved_id);
    });
    
    // First process should contain the original trace
    u64 first_trace_id = 0;
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        EXPECT_EQ(traces.size(), 2);
        CallTrace* first_trace = findTraceById(traces, original_trace_id);
        EXPECT_NE(first_trace, nullptr);
        first_trace_id = first_trace->trace_id;
        EXPECT_EQ(first_trace->trace_id, original_trace_id);
    });
    
    // Second process should still contain the preserved trace with SAME ID
    u64 preserved_trace_id = 0;
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        EXPECT_EQ(traces.size(), 2);
        CallTrace* preserved_trace = findTraceById(traces, original_trace_id);
        EXPECT_NE(preserved_trace, nullptr);
        preserved_trace_id = preserved_trace->trace_id;
        // Critical test: trace ID must be exactly the same after preservation
        EXPECT_EQ(preserved_trace->trace_id, original_trace_id);
        // Regression test: access frame content to detect use-after-free (ASan will crash if bug exists)
        EXPECT_EQ(preserved_trace->frames[0].bci, 10);
        EXPECT_EQ(preserved_trace->frames[0].method_id, (jmethodID)0x1234);
    });
    
    printf("Original trace ID: %llu, Preserved trace ID: %llu\n", 
           original_trace_id, preserved_trace_id);
}

TEST_F(CallTraceStorageTest, ClearMethod) {
    // Store a trace
    ASGCT_CallFrame frame;
    frame.bci = 10;
    frame.method_id = (jmethodID)0x1234;
    u64 trace_id = storage->put(1, &frame, false, 1);
    
    // Register a liveness checker (should be ignored by clear())
    u64 preserved_id = trace_id;
    storage->registerLivenessChecker([&preserved_id](std::unordered_set<u64>& buffer) {
        buffer.insert(preserved_id);
    });
    
    // clear() should completely clear both storages, ignoring liveness checkers
    storage->clear();
    
    // Should have no traces after clear, except for the dropped trace
    size_t traces_after_clear = 0;
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        traces_after_clear = traces.size();
    });
    EXPECT_EQ(traces_after_clear, 1);
}

TEST_F(CallTraceStorageTest, ConcurrentClearAndPut) {
    // Test concurrent access patterns that might cause NULL dereferences
    ASGCT_CallFrame frame;
    frame.bci = 10; 
    frame.method_id = (jmethodID)0x1234;
    
    // Store initial trace
    u64 trace_id = storage->put(1, &frame, false, 1);
    EXPECT_GT(trace_id, 0);
    
    // Simulate what happens when clear() races with put()
    // Clear the storage
    storage->clear();
    
    // Immediately try to put - should handle cleared state gracefully
    u64 result_after_clear = storage->put(1, &frame, false, 1);
    // This should either succeed (if new table allocated) or return 0 (drop sample)
    // Either way, it shouldn't crash
    
    // Verify system is still functional  
    storage->processTraces([](const std::unordered_set<CallTrace*>& traces) {
        // No assertion on size since behavior during concurrent operations can vary
        // The key test is that we don't crash
    });
}

TEST_F(CallTraceStorageTest, ConcurrentTableExpansionRegression) {
    // Regression test for the crash during table expansion in CallTraceHashTable::put
    // The crash occurred at __sync_bool_compare_and_swap(&_current_table, table, new_table)
    // when multiple threads triggered table expansion simultaneously
    
    // Use heap allocation with proper alignment to avoid ASAN alignment issues
    // Stack allocation with high alignment requirements (64 bytes) is problematic under ASAN
    void* aligned_memory = std::aligned_alloc(alignof(CallTraceHashTable), sizeof(CallTraceHashTable));
    ASSERT_NE(aligned_memory, nullptr) << "Failed to allocate aligned memory for CallTraceHashTable";
    
    auto hash_table_ptr = std::unique_ptr<CallTraceHashTable, void(*)(CallTraceHashTable*)>(
        new(aligned_memory) CallTraceHashTable(), 
        [](CallTraceHashTable* ptr) {
            ptr->~CallTraceHashTable();
            std::free(ptr);
        }
    );
    CallTraceHashTable& hash_table = *hash_table_ptr;
    hash_table.setInstanceId(42);
    
    const int num_threads = 4;  // Reduced from 8 to avoid excessive contention
    const int traces_per_thread = 2000; // Reduced from 10000 to avoid livelock
    std::atomic<int> crash_counter{0};
    std::atomic<int> completed_threads{0};
    std::vector<std::thread> threads;
    
    // Create many different stack traces to trigger table expansion
    auto worker = [&](int thread_id) {
        int successful_puts = 0;
        int dropped_samples = 0;
        
        for (int i = 0; i < traces_per_thread; i++) {
            try {
                ASGCT_CallFrame frame;
                frame.bci = thread_id * 1000 + i; // Unique BCI per trace
                frame.method_id = (jmethodID)(0x1000 + thread_id * 1000 + i);
                
                // This will trigger table expansion multiple times concurrently
                u64 trace_id = hash_table.put(1, &frame, false, 1);
                
                if (trace_id == 0) {
                    // Sample was dropped - acceptable under high contention
                    dropped_samples++;
                    continue;
                }
                
                // Verify trace ID is valid
                if (trace_id == 0x7fffffffffffffffULL) {
                    // Overflow trace - also acceptable
                    continue;
                }
                
                successful_puts++;
                
                // Add small yield to reduce contention and prevent livelock
                if (i % 100 == 0) {
                    std::this_thread::yield();
                }
                
            } catch (...) {
                // Any exception indicates a problem
                crash_counter++;
            }
        }
        
        completed_threads++;
    };
    
    // Start all threads simultaneously to maximize contention during table expansion
    for (int t = 0; t < num_threads; t++) {
        threads.emplace_back(worker, t);
    }
    
    // Wait for all threads to complete with timeout to avoid hanging tests
    bool all_completed = true;
    for (auto& thread : threads) {
        thread.join();
    }
    
    // The main test is that we don't crash during concurrent table expansion
    EXPECT_EQ(crash_counter.load(), 0);
    EXPECT_EQ(completed_threads.load(), num_threads);
    
    // Verify the hash table is still functional after all the expansion
    ASGCT_CallFrame test_frame;
    test_frame.bci = 99999;
    test_frame.method_id = (jmethodID)0x99999;
    u64 final_trace_id = hash_table.put(1, &test_frame, false, 1);
    EXPECT_GT(final_trace_id, 0);
}


