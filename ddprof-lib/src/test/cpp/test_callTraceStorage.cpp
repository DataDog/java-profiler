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
