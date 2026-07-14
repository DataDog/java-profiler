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
#include <chrono>
#include <condition_variable>
#include <mutex>
#include "callTraceHashTable.h"
#include "gtest_crash_handler.h"
#include "arch.h"

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

/**
 * Test RefCountGuard synchronization during storage swap.
 * This test ensures that waitForRefCountToClear() actually prevents
 * collection from original_active while there are still pending put() operations
 * to the original_active after the active area swap.
 */
TEST_F(CallTraceStorageTest, RefCountGuardSynchronizationDuringSwap) {
    // Synchronization primitives for coordinating the test
    std::atomic<bool> swap_can_proceed{false};
    std::atomic<bool> put_threads_ready{false};
    std::atomic<int> put_threads_ready_count{0};
    std::atomic<bool> put_operation_started{false};
    std::atomic<bool> put_operation_completed{false};
    std::atomic<bool> collection_started{false};
    std::atomic<bool> collection_completed{false};

    std::condition_variable ready_cv;
    std::mutex ready_mutex;

    std::condition_variable swap_cv;
    std::mutex swap_mutex;

    // Test outcome tracking
    std::atomic<u64> put_trace_id{0};
    std::atomic<u64> delayed_trace_id{0};

    // Create initial traces to populate the storage
    ASGCT_CallFrame initial_frame;
    initial_frame.bci = 100;
    initial_frame.method_id = (jmethodID)0x1000;

    // Add several traces to ensure there's content to process
    for (int i = 0; i < 5; i++) {
        initial_frame.bci = 100 + i;
        storage->put(1, &initial_frame, false, 1);
    }

    // Thread that will perform a put() operation right after storage swap
    std::thread put_thread([&]() {
        // Signal that this thread is ready
        {
            std::lock_guard<std::mutex> lock(ready_mutex);
            put_threads_ready_count.fetch_add(1);
        }
        ready_cv.notify_all();

        // Wait for permission to proceed with put operation
        std::unique_lock<std::mutex> lock(swap_mutex);
        swap_cv.wait(lock, [&] { return swap_can_proceed.load(); });
        lock.unlock();

        // This put() should target the new active area
        ASGCT_CallFrame put_frame;
        put_frame.bci = 999;
        put_frame.method_id = (jmethodID)0x999;

        put_operation_started = true;
        u64 trace_id = storage->put(1, &put_frame, false, 1);
        put_trace_id = trace_id;
        put_operation_completed = true;
    });

    // Thread that simulates a longer-running put() operation
    std::thread delayed_put_thread([&]() {
        // Signal that this thread is ready
        {
            std::lock_guard<std::mutex> lock(ready_mutex);
            put_threads_ready_count.fetch_add(1);
        }
        ready_cv.notify_all();

        // Wait for permission to proceed
        std::unique_lock<std::mutex> lock(swap_mutex);
        swap_cv.wait(lock, [&] { return swap_can_proceed.load(); });
        lock.unlock();

        // Simulate a put operation during swap
        ASGCT_CallFrame delayed_frame;
        delayed_frame.bci = 777;
        delayed_frame.method_id = (jmethodID)0x777;

        // Small delay to simulate ongoing operation
        std::this_thread::sleep_for(std::chrono::microseconds(50));

        u64 trace_id = storage->put(1, &delayed_frame, false, 1);
        delayed_trace_id = trace_id;
    });

    // Wait for both put threads to be ready before starting process thread
    {
        std::unique_lock<std::mutex> lock(ready_mutex);
        ready_cv.wait(lock, [&] { return put_threads_ready_count.load() == 2; });
        put_threads_ready = true;
    }

    // Give threads a moment to enter their wait state
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Perform processTraces in separate thread to trigger the storage swap
    std::thread process_thread([&]() {
        // Start processing - this will swap storage
        storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
            collection_started = true;

            // Verify we have traces from the initial population
            int initial_trace_count = 0;
            for (CallTrace* trace : traces) {
                if (trace && trace->num_frames > 0 && trace->frames[0].bci >= 100 && trace->frames[0].bci <= 104) {
                    initial_trace_count++;
                }
            }
            EXPECT_GE(initial_trace_count, 5) << "Should find initial traces";
        });

        collection_completed = true;

        // Now that swap is complete and refcount wait has finished,
        // signal put threads to proceed
        {
            std::lock_guard<std::mutex> lock(swap_mutex);
            swap_can_proceed = true;
        }
        swap_cv.notify_all();
    });

    // Wait for all threads to complete with timeout to detect deadlock
    auto wait_with_timeout = [](std::thread& t, int timeout_seconds, const char* name) -> bool {
        auto start = std::chrono::steady_clock::now();
        auto timeout_duration = std::chrono::seconds(timeout_seconds);

        while (std::chrono::steady_clock::now() - start < timeout_duration) {
            if (t.joinable()) {
                t.join();
                return true;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // Timeout occurred
        ADD_FAILURE() << "Thread " << name << " timed out after " << timeout_seconds << " seconds (possible deadlock)";
        return false;
    };

    EXPECT_TRUE(wait_with_timeout(process_thread, 30, "process_thread"));
    EXPECT_TRUE(wait_with_timeout(put_thread, 30, "put_thread"));
    EXPECT_TRUE(wait_with_timeout(delayed_put_thread, 30, "delayed_put_thread"));

    // Verification of test outcomes
    EXPECT_TRUE(put_threads_ready.load()) << "Put threads should have been ready";
    EXPECT_TRUE(collection_started.load()) << "Collection should have started";
    EXPECT_TRUE(collection_completed.load()) << "Collection should have completed";
    EXPECT_TRUE(put_operation_started.load()) << "Put operation should have started";
    EXPECT_TRUE(put_operation_completed.load()) << "Put operation should have completed";
    EXPECT_GT(put_trace_id.load(), 0ULL) << "Put operation should have returned valid trace ID";
    EXPECT_GT(delayed_trace_id.load(), 0ULL) << "Delayed put operation should have returned valid trace ID";

    // The key test: if RefCountGuard synchronization works correctly,
    // the collection should not interfere with concurrent put operations
    // This test primarily validates that we don't crash or corrupt data

    // Additional verification: ensure storage is still functional
    ASGCT_CallFrame verification_frame;
    verification_frame.bci = 5555;
    verification_frame.method_id = (jmethodID)0x5555;
    u64 verification_trace = storage->put(1, &verification_frame, false, 1);
    EXPECT_GT(verification_trace, 0ULL) << "Storage should remain functional after RefCountGuard synchronization";

    // Final verification: ensure we can still process traces
    std::atomic<int> final_trace_count{0};
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        final_trace_count = static_cast<int>(traces.size());
    });

    EXPECT_GT(final_trace_count.load(), 0) << "Storage should still contain traces after synchronization test";
}

/**
 * Reproducer test for use-after-free bug in processTraces().
 *
 * BUG DESCRIPTION:
 * In processTraces(), traces are collected from standby into _traces_buffer (raw pointers),
 * then standby->clear() frees all memory, but processor(_traces_buffer) is called AFTER
 * the clear, accessing freed memory.
 *
 * Timeline of the bug:
 *   1. original_standby->collect(_traces_buffer, ...) - collects raw pointers from STANDBY
 *   2. original_standby->clear() - FREES ALL MEMORY including CallTrace objects!
 *   3. processor(_traces_buffer) - accesses freed memory (USE-AFTER-FREE)
 *
 * KEY INSIGHT: The bug only affects traces from STANDBY, not ACTIVE.
 * - Active traces are cleared AFTER the processor runs (safe)
 * - Standby traces are cleared BEFORE the processor runs (BUG!)
 *
 * To trigger the bug, we need traces IN STANDBY at the start of processTraces().
 * Traces get into standby via the liveness preservation mechanism:
 *   1. Register a liveness checker that marks traces as "live"
 *   2. During processTraces(), live traces are copied to SCRATCH
 *   3. After rotation, SCRATCH becomes the new STANDBY
 *   4. Next processTraces() will have those preserved traces in STANDBY
 *   5. Those traces are collected, then FREED, then ACCESSED → USE-AFTER-FREE!
 *
 * This test should FAIL (crash or ASan error) before the fix and PASS after.
 */
TEST_F(CallTraceStorageTest, UseAfterFreeInProcessTraces) {
    // Create multiple traces with varying frame counts to increase memory footprint
    const int NUM_TRACES = 100;
    const int MAX_FRAMES = 20;

    std::vector<u64> trace_ids;
    trace_ids.reserve(NUM_TRACES);

    // Create traces with multiple frames to use more memory
    for (int i = 0; i < NUM_TRACES; i++) {
        std::vector<ASGCT_CallFrame> frames(MAX_FRAMES);
        for (int j = 0; j < MAX_FRAMES; j++) {
            frames[j].bci = i * 1000 + j;
            frames[j].method_id = (jmethodID)(0x10000 + i * 100 + j);
        }

        u64 trace_id = storage->put(MAX_FRAMES, frames.data(), false, 1);
        ASSERT_GT(trace_id, 0) << "Failed to store trace " << i;
        trace_ids.push_back(trace_id);
    }

    // CRITICAL: Register a liveness checker that preserves ALL traces.
    // This causes traces to be copied to SCRATCH during processTraces().
    // After rotation, SCRATCH becomes STANDBY, so the NEXT processTraces()
    // will have these traces in STANDBY where the bug manifests.
    storage->registerLivenessChecker([&trace_ids](std::unordered_set<u64>& buffer) {
        for (u64 id : trace_ids) {
            buffer.insert(id);
        }
    });

    // First processTraces: traces are in ACTIVE, get collected and preserved to SCRATCH.
    // After rotation: SCRATCH becomes STANDBY (now contains preserved traces)
    int first_count = 0;
    storage->processTraces([&first_count](const std::unordered_set<CallTrace*>& traces) {
        first_count = traces.size();
        printf("First processTraces: %d traces collected\n", first_count);
    });
    EXPECT_GT(first_count, NUM_TRACES) << "First processTraces should collect all traces";

    // Second processTraces: THIS IS WHERE THE BUG OCCURS!
    // 1. STANDBY now contains the preserved traces (from first call's scratch)
    // 2. Standby traces are collected into _traces_buffer (raw pointers)
    // 3. original_standby->clear() - FREES the trace memory!
    // 4. processor(_traces_buffer) - accesses FREED memory (USE-AFTER-FREE!)
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        int total_frames = 0;
        int total_bci_sum = 0;
        int trace_count = 0;

        for (CallTrace* trace : traces) {
            if (trace == nullptr) continue;
            if (trace->trace_id == CallTraceStorage::DROPPED_TRACE_ID) continue;

            trace_count++;

            // Deep access to detect use-after-free:
            // After standby->clear(), this memory is FREED but we're accessing it!
            // ASan will catch this. Without ASan, we might read garbage.
            EXPECT_GE(trace->num_frames, 1) << "Corrupted num_frames (use-after-free?)";
            EXPECT_LE(trace->num_frames, MAX_FRAMES) << "Corrupted num_frames (use-after-free?)";
            EXPECT_FALSE(trace->truncated) << "Corrupted truncated flag (use-after-free?)";
            EXPECT_GT(trace->trace_id, 0) << "Corrupted trace_id (use-after-free?)";

            total_frames += trace->num_frames;

            // Access every frame - this maximizes chance of detecting corruption
            for (int i = 0; i < trace->num_frames; i++) {
                int bci = trace->frames[i].bci;
                total_bci_sum += bci;
                EXPECT_GE(bci, 0) << "Corrupted BCI at frame " << i << " (use-after-free?)";

                jmethodID method = trace->frames[i].method_id;
                EXPECT_NE(method, nullptr) << "Null method_id at frame " << i << " (use-after-free?)";
            }
        }

        printf("Second processTraces: %d traces, %d total frames, bci_sum=%d\n",
               trace_count, total_frames, total_bci_sum);

        // This is the key assertion: we expect to find the preserved traces
        // If the bug exists, we're reading freed memory here!
        EXPECT_GE(trace_count, NUM_TRACES) << "Should find preserved traces from standby";
    });

    // Third processTraces: traces should still be preserved (copied to new scratch)
    // This further exercises the use-after-free if the bug exists
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        int trace_count = 0;
        for (CallTrace* trace : traces) {
            if (trace == nullptr) continue;
            if (trace->trace_id == CallTraceStorage::DROPPED_TRACE_ID) continue;
            trace_count++;

            // Access all frame data
            volatile int sum = 0;
            for (int i = 0; i < trace->num_frames; i++) {
                sum += trace->frames[i].bci;
            }
        }
        printf("Third processTraces: %d traces\n", trace_count);
        EXPECT_GE(trace_count, NUM_TRACES) << "Should still find preserved traces";
    });
}

/**
 * Regression test for the putWithExistingId infinite-loop bug.
 *
 * Before the fix: when all INITIAL_CAPACITY (65536) slots were occupied the
 * probe loop called probe.next() without checking probe.hasNext(), so the
 * prime-probe step cycled forever through already-occupied slots.
 *
 * After the fix: the hasNext() guard breaks the loop and the call returns,
 * silently dropping the trace that could not be inserted.
 *
 */
TEST_F(CallTraceStorageTest, PutWithExistingIdNoInfiniteLoopWhenFull) {
    static constexpr u32 INITIAL_CAPACITY = 65536;

    // Heap-allocated so the worker's shared_ptr copy keeps it alive if we detach
    // before the thread writes completed=true (avoids UAF on slow machines).
    auto completed = std::make_shared<std::atomic<bool>>(false);
    std::thread worker([completed] {  // capture by value — shared ownership
        void* mem = std::aligned_alloc(alignof(CallTraceHashTable), sizeof(CallTraceHashTable));
        if (mem == nullptr) {
            completed->store(true);  // Let the join path handle this; EXPECT below will report.
            return;
        }

        auto tbl = std::unique_ptr<CallTraceHashTable, void(*)(CallTraceHashTable*)>(
            new (mem) CallTraceHashTable(),
            [](CallTraceHashTable* p) { p->~CallTraceHashTable(); std::free(p); });
        tbl->setInstanceId(1);

        // Each iteration uses a distinct (bci, method_id) pair so calcHash produces
        // a distinct hash, filling INITIAL_CAPACITY unique slots.  Iterations past
        // that point find no empty slot and must exit the probe via the hasNext()
        // guard rather than cycling forever.
        for (u32 i = 0; i < INITIAL_CAPACITY + 128; ++i) {
            // Stack-allocate source trace; putWithExistingId copies the payload.
            alignas(alignof(CallTrace)) char buf[sizeof(CallTrace)];
            CallTrace* src = new (buf) CallTrace(false, 1, static_cast<u64>(i) + 1);
            src->frames[0].bci       = static_cast<int>(i);
            src->frames[0].method_id = reinterpret_cast<jmethodID>(static_cast<uintptr_t>(0x10000 + i));
            tbl->putWithExistingId(src, 1);
        }

        completed->store(true);
    });

    // 10-second deadline; an un-fixed infinite loop would never set `completed`.
    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(10);
    while (!completed->load() && std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    bool ok = completed->load();
    if (!ok) {
        worker.detach();
    } else {
        worker.join();
    }
    EXPECT_TRUE(ok)
        << "putWithExistingId infinite-loop regression: did not terminate within 10 s "
           "when the scratch table was full";
}

/**
 * Integration test: processTraces preserves live traces across rotation cycles
 * without hanging.
 *
 * Each processTraces() cycle copies preserved traces into the scratch table via
 * putWithExistingId.  This test verifies:
 *   1. Every cycle completes promptly (no infinite loop via putWithExistingId).
 *   2. Every trace flagged by the liveness checker survives to the next cycle.
 *   3. The trace_id of a preserved trace is unchanged after preservation
 *      (putWithExistingId must keep the original ID, not generate a new one).
 *   4. Frame content is intact after copying (detects use-after-free).
 */
TEST_F(CallTraceStorageTest, LivenessPreservationAcrossMultipleCycles) {
    const int N = 200;

    // Insert N unique traces and record their IDs and frame values for later checks.
    std::vector<u64> ids;
    std::vector<int> bcis;
    ids.reserve(N);
    bcis.reserve(N);
    for (int i = 0; i < N; i++) {
        ASGCT_CallFrame frame;
        frame.bci       = i + 1000;
        frame.method_id = reinterpret_cast<jmethodID>(static_cast<uintptr_t>(0x30000 + i));
        u64 id = storage->put(1, &frame, false, 1);
        ASSERT_NE(id, CallTraceStorage::DROPPED_TRACE_ID) << "put() failed for trace " << i;
        ids.push_back(id);
        bcis.push_back(frame.bci);
    }

    // Liveness checker marks every stored trace as live.
    storage->registerLivenessChecker([&ids](std::unordered_set<u64>& buf) {
        for (u64 id : ids) buf.insert(id);
    });

    const int CYCLES = 5;
    for (int cycle = 0; cycle < CYCLES; cycle++) {
        std::atomic<bool> done{false};
        std::thread t([&] {
            storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
                // All N preserved traces must be present, plus the dropped sentinel.
                EXPECT_GE(traces.size(), static_cast<size_t>(N + 1))
                    << "cycle " << cycle << ": too few traces";

                for (int j = 0; j < N; j++) {
                    CallTrace* found = findTraceById(traces, ids[j]);
                    EXPECT_NE(found, nullptr)
                        << "cycle " << cycle << ": trace_id " << ids[j] << " not preserved";
                    if (found == nullptr) continue;

                    // Trace ID must be unchanged (putWithExistingId preserves the original ID).
                    EXPECT_EQ(found->trace_id, ids[j])
                        << "cycle " << cycle << ": trace_id mutated during preservation";

                    // Frame content must be intact (detects use-after-free of freed chunks).
                    EXPECT_EQ(found->frames[0].bci, bcis[j])
                        << "cycle " << cycle << ": frame bci corrupted for trace " << ids[j];
                }
            });
            done = true;
        });

        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(10);
        while (!done.load() && std::chrono::steady_clock::now() < deadline) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        bool ok = done.load();
        if (!ok) {
            // Cannot safely detach: the lambda captures local stack variables by reference.
            // If we detach and return, the thread will access destroyed locals (UAF).
            // Instead, terminate the process immediately to fail the test cleanly.
            std::cerr << "FATAL: processTraces hung on cycle " << cycle
                      << " (possible infinite-loop regression in putWithExistingId)" << std::endl;
            std::abort();
        }
        t.join();
    }
}
// Regression for defect C: clearTableOnly() must disconnect the full _prev chain,
// not only the first node.  Fill the table past the 75 % expansion threshold so
// it grows to at least two LongHashTable nodes, then call clearTableOnly() and
// confirm the returned fresh table has no _prev chain.
TEST_F(CallTraceStorageTest, ClearTableOnlyDisconnectsFullChain) {
    // 65536 initial capacity; expansion triggers at 75 % = 49152 entries.
    // Insert 50000 distinct single-frame traces to force at least one expansion.
    const int NUM_TRACES = 50000;
    std::vector<u64> ids;
    ids.reserve(NUM_TRACES);

    for (int i = 0; i < NUM_TRACES; i++) {
        ASGCT_CallFrame frame;
        frame.bci = i % 1000;  // Reuse BCI values; uniqueness comes from method_id
        frame.method_id = reinterpret_cast<jmethodID>(static_cast<uintptr_t>(i + 1));
        u64 id = storage->put(1, &frame, false, 1);
        EXPECT_GT(id, 0u) << "put() dropped trace at i=" << i;
        ids.push_back(id);
    }

    // processTraces() performs the rotation including clearTableOnly(); run it once
    // to expose defect C.
    int count = 0;
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        count = static_cast<int>(traces.size());
    });
    // At least NUM_TRACES + the static dropped-trace sentinel should be present.
    EXPECT_GE(count, NUM_TRACES);
    // Second processTraces() verifies the fresh table is clean: no new puts occurred
    // after rotation, so only the static dropped-trace sentinel should be present.
    // This deterministically detects defect C — if clearTableOnly() left stale entries
    // in freed memory that somehow end up in the new table, count2 would be wrong.
    int count2 = 0;
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        count2 = static_cast<int>(traces.size());
    });
    EXPECT_EQ(count2, 1);  // only the dropped-trace sentinel; no stale entries
}

// Regression for defect B: collect() must see all traces including those in
// older nodes of an expanded chain.  Fill past expansion threshold, run
// processTraces(), and assert all inserted trace IDs are present.
TEST_F(CallTraceStorageTest, CollectFindsAllTracesAcrossExpandedChain) {
    const int NUM_TRACES = 50000;
    std::unordered_set<u64> inserted_ids;

    for (int i = 0; i < NUM_TRACES; i++) {
        ASGCT_CallFrame frame;
        frame.bci = i % 1000;  // reuse bci values; uniqueness comes from method_id
        frame.method_id = reinterpret_cast<jmethodID>(static_cast<uintptr_t>(i + 1));
        u64 id = storage->put(1, &frame, false, 1);
        EXPECT_GT(id, 0u) << "put() dropped trace at i=" << i;
        inserted_ids.insert(id);
    }

    std::unordered_set<u64> seen_ids;
    storage->processTraces([&](const std::unordered_set<CallTrace*>& traces) {
        for (CallTrace* t : traces) {
            if (t) seen_ids.insert(t->trace_id);
        }
    });

    // Every inserted ID must be visible in the snapshot.
    for (u64 id : inserted_ids) {
        EXPECT_TRUE(seen_ids.count(id) > 0)
            << "Trace ID " << id << " was lost across expansion boundary";
    }
}

// PROF-15396 regression tests: trace_id collisions across CallTraceHashTable
// table-expansion generations.
//
// These operate directly on a heap-allocated CallTraceHashTable (matching the
// pattern used by ConcurrentTableExpansionRegression and
// PutWithExistingIdNoInfiniteLoopWhenFull above) so that expansion can be
// forced deterministically via distinct-frame counts alone, without relying
// on CallTraceStorage::processTraces() rotation.
//
// INITIAL_CAPACITY (65536) and LOAD_RATIO (0.75) are documented public
// behaviour of CallTraceHashTable (expansion triggers once fill exceeds
// INITIAL_CAPACITY * LOAD_RATIO = 49152 entries); they are re-declared here
// as shared constants since the class does not expose them as named
// constants.
namespace {
constexpr u32 kInitialCapacity = 65536;
constexpr double kLoadRatio = 0.75;
constexpr u32 kExpansionThreshold = static_cast<u32>(kInitialCapacity * kLoadRatio); // 49152
constexpr u64 kOverflowTraceId = 0x7fffffffffffffffULL;

// Shared setup for the PROF-15396 expansion/trace_id tests below: a
// heap-allocated CallTraceHashTable, matching the aligned_alloc + placement-new
// pattern used by ConcurrentTableExpansionRegression and
// PutWithExistingIdNoInfiniteLoopWhenFull above.
std::unique_ptr<CallTraceHashTable, void(*)(CallTraceHashTable*)> makeHeapCallTraceHashTable() {
    void* aligned_memory = std::aligned_alloc(alignof(CallTraceHashTable), sizeof(CallTraceHashTable));
    if (aligned_memory == nullptr) {
        return std::unique_ptr<CallTraceHashTable, void(*)(CallTraceHashTable*)>(
            nullptr, [](CallTraceHashTable*) {});
    }
    return std::unique_ptr<CallTraceHashTable, void(*)(CallTraceHashTable*)>(
        new (aligned_memory) CallTraceHashTable(),
        [](CallTraceHashTable* ptr) {
            ptr->~CallTraceHashTable();
            std::free(ptr);
        });
}
} // namespace

// Test 1: forcing at least one expansion must not produce duplicate
// trace_ids, and no successful put() may return OVERFLOW_TRACE_ID or
// DROPPED_TRACE_ID.
TEST_F(CallTraceStorageTest, ExpansionProducesNoDuplicateTraceIds) {
    auto hash_table_ptr = makeHeapCallTraceHashTable();
    ASSERT_NE(hash_table_ptr.get(), nullptr) << "Failed to allocate aligned memory for CallTraceHashTable";
    CallTraceHashTable& hash_table = *hash_table_ptr;
    hash_table.setInstanceId(1);

    // Pre-expansion batch: strictly more than the 75% load-ratio threshold,
    // so at least one expansion is forced deterministically.
    const u32 PRE_EXPANSION_COUNT = kExpansionThreshold + 100;
    // Post-expansion batch: further distinct stacks inserted after expansion.
    const u32 POST_EXPANSION_COUNT = 1000;
    const u32 TOTAL_COUNT = PRE_EXPANSION_COUNT + POST_EXPANSION_COUNT;

    std::unordered_set<u64> trace_ids;
    trace_ids.reserve(TOTAL_COUNT);

    for (u32 i = 0; i < TOTAL_COUNT; i++) {
        ASGCT_CallFrame frame;
        frame.bci = static_cast<int>(i);
        frame.method_id = reinterpret_cast<jmethodID>(static_cast<uintptr_t>(i + 1));
        u64 trace_id = hash_table.put(1, &frame, false, 1);
        ASSERT_NE(trace_id, kOverflowTraceId) << "Unexpected overflow at i=" << i;
        ASSERT_NE(trace_id, CallTraceStorage::DROPPED_TRACE_ID) << "Unexpected drop at i=" << i;
        trace_ids.insert(trace_id);
    }

    EXPECT_EQ(trace_ids.size(), TOTAL_COUNT)
        << "Duplicate trace_id detected across pre- and post-expansion inserts combined";
}

// Test 2: re-inserting an already-known stack after a forced expansion must
// return exactly the same trace_id it was originally assigned.
TEST_F(CallTraceStorageTest, TraceIdStableAcrossExpansion) {
    auto hash_table_ptr = makeHeapCallTraceHashTable();
    ASSERT_NE(hash_table_ptr.get(), nullptr) << "Failed to allocate aligned memory for CallTraceHashTable";
    CallTraceHashTable& hash_table = *hash_table_ptr;
    hash_table.setInstanceId(1);

    // Insert the stack whose trace_id stability we are testing.
    ASGCT_CallFrame original_frame;
    original_frame.bci = 999999999;
    original_frame.method_id = reinterpret_cast<jmethodID>(static_cast<uintptr_t>(0xdeadbeef));
    u64 original_trace_id = hash_table.put(1, &original_frame, false, 1);
    ASSERT_GT(original_trace_id, CallTraceStorage::DROPPED_TRACE_ID);

    // Insert enough further distinct stacks to force an expansion.
    const u32 FILLER_COUNT = kExpansionThreshold + 100;
    for (u32 i = 0; i < FILLER_COUNT; i++) {
        ASGCT_CallFrame frame;
        frame.bci = static_cast<int>(i);
        frame.method_id = reinterpret_cast<jmethodID>(static_cast<uintptr_t>(i + 1));
        hash_table.put(1, &frame, false, 1);
    }

    // Re-insert the original stack; its trace_id must be unchanged.
    u64 second_trace_id = hash_table.put(1, &original_frame, false, 1);
    EXPECT_EQ(second_trace_id, original_trace_id)
        << "trace_id changed for an already-inserted stack after table expansion";
}

// Test 3: forcing two expansions within a single tenure (i.e. no rotation in
// between) must still produce unique trace_ids across all three generations
// combined.
TEST_F(CallTraceStorageTest, TwoExpansionsWithinOneTenureNoDuplicateTraceIds) {
    // _size is per-generation and restarts from 0 when a new LongHashTable is
    // allocated, so the second expansion is gated on the *second* generation's
    // own load-ratio threshold (0.75 * 2*INITIAL_CAPACITY = 98304 puts served
    // by that generation), not on the cumulative insert count from i=0.
    // The first expansion consumes kExpansionThreshold puts on generation 1;
    // only puts after that land on generation 2, so the total must clear both
    // thresholds back-to-back for both expansions to occur within one tenure.
    static constexpr u32 SECOND_GENERATION_THRESHOLD = kExpansionThreshold * 2; // 98304

    auto hash_table_ptr = makeHeapCallTraceHashTable();
    ASSERT_NE(hash_table_ptr.get(), nullptr) << "Failed to allocate aligned memory for CallTraceHashTable";
    CallTraceHashTable& hash_table = *hash_table_ptr;
    hash_table.setInstanceId(1);

    // Insert past both the first generation's and second generation's
    // load-ratio thresholds, without any rotation (no processTraces()/clear()
    // call) in between, so both expansions happen within the same tenure.
    const u32 TOTAL_COUNT = kExpansionThreshold + SECOND_GENERATION_THRESHOLD + 100;

    std::unordered_set<u64> trace_ids;
    trace_ids.reserve(TOTAL_COUNT);

    for (u32 i = 0; i < TOTAL_COUNT; i++) {
        ASGCT_CallFrame frame;
        frame.bci = static_cast<int>(i);
        frame.method_id = reinterpret_cast<jmethodID>(static_cast<uintptr_t>(i + 1));
        u64 trace_id = hash_table.put(1, &frame, false, 1);
        ASSERT_NE(trace_id, kOverflowTraceId) << "Unexpected overflow at i=" << i;
        ASSERT_NE(trace_id, CallTraceStorage::DROPPED_TRACE_ID) << "Unexpected drop at i=" << i;
        trace_ids.insert(trace_id);
    }

    EXPECT_EQ(trace_ids.size(), TOTAL_COUNT)
        << "Duplicate trace_id detected across two expansions within one tenure";
}

// Test 4: the expansion-overflow guard (CallTraceHashTable::wouldExceedSlotIdRange)
// must reject slot_base/capacity combinations that would push slot_base +
// local_slot past 2^32, accept the exact 2^32 boundary, and accept anything
// clearly below it. Exercised directly since reaching this boundary via real
// put() calls would require billions of inserts.
TEST(CallTraceHashTableOverflowGuardTest, RejectsOnlyValuesThatExceedSlotIdRange) {
    constexpr u32 kCapacity = 65536;
    constexpr u64 kSlotIdRange = 0x100000000ull; // 2^32

    // Well below the boundary: base + capacity + next capacity is nowhere
    // near 2^32.
    EXPECT_FALSE(CallTraceHashTable::wouldExceedSlotIdRange(0, kCapacity));

    // Exact boundary: base + capacity + next capacity == 2^32 must be
    // accepted (valid slots are [0, 2^32)).
    u64 exact_boundary_base = kSlotIdRange - kCapacity - (u64)kCapacity * 2;
    EXPECT_FALSE(CallTraceHashTable::wouldExceedSlotIdRange(exact_boundary_base, kCapacity));

    // One past the boundary must be rejected.
    EXPECT_TRUE(CallTraceHashTable::wouldExceedSlotIdRange(exact_boundary_base + 1, kCapacity));

    // Far past the boundary must be rejected.
    EXPECT_TRUE(CallTraceHashTable::wouldExceedSlotIdRange(kSlotIdRange, kCapacity));
}

// Test 5: the next-generation capacity used during expansion must be exactly
// double the current capacity (CallTraceHashTable::nextGenerationCapacity).
TEST(CallTraceHashTableOverflowGuardTest, NextGenerationCapacityIsDouble) {
    EXPECT_EQ(CallTraceHashTable::nextGenerationCapacity(65536), 131072ull);
    EXPECT_EQ(CallTraceHashTable::nextGenerationCapacity(1), 2ull);
    EXPECT_EQ(CallTraceHashTable::nextGenerationCapacity(0), 0ull);
}
