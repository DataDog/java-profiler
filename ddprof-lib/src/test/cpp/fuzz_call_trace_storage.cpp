#include <gtest/gtest.h>
#include "callTraceStorage.h"
#include "vmEntry.h"
#include <random>
#include <vector>
#include <thread>
#include <atomic>
#include <algorithm>
#include <chrono>
#include <functional>
#include <string>
#include <map>

// Helper method for generating random call traces
void generateRandomTrace(std::mt19937& rng, ASGCT_CallFrame* frames, int num_frames) {
    std::uniform_int_distribution<int> bci_dist(-1, 10000);
    std::uniform_int_distribution<int> method_id_dist(1, 1000000);
    
    for (int i = 0; i < num_frames; i++) {
        frames[i].bci = bci_dist(rng);
        frames[i].method_id = (jmethodID)(intptr_t)method_id_dist(rng);
    }
}

// Test for CallTraceSample operations
TEST(CallTraceStorageFuzzTest, CallTraceSampleOperations) {
    // Create a sample call trace
    const int num_frames = 5;
    size_t trace_size = sizeof(CallTrace) + (num_frames - 1) * sizeof(ASGCT_CallFrame);
    CallTrace* trace1 = (CallTrace*)malloc(trace_size);
    CallTrace* trace2 = (CallTrace*)malloc(trace_size);
    
    trace1->num_frames = num_frames;
    trace2->num_frames = num_frames;
    trace1->truncated = false;
    trace2->truncated = true;
    
    // Initialize with random values
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    generateRandomTrace(gen, trace1->frames, num_frames);
    generateRandomTrace(gen, trace2->frames, num_frames);
    
    // Test atomic operations on CallTraceSample
    CallTraceSample sample1, sample2;
    sample1.trace = trace1;
    sample1.samples = 10;
    sample1.counter = 100;
    
    sample2.trace = trace2;
    sample2.samples = 5;
    sample2.counter = 50;
    
    // Test atomic acquire and release operations
    ASSERT_EQ(sample1.acquireTrace(), trace1);
    
    sample1.setTrace(trace2);
    ASSERT_EQ(sample1.acquireTrace(), trace2);
    
    // Test addition operator
    CallTraceSample sample3 = sample1;
    sample3 += sample2;
    
    ASSERT_EQ(sample3.trace, sample2.trace);
    ASSERT_EQ(sample3.samples, sample1.samples + sample2.samples);
    ASSERT_EQ(sample3.counter, sample1.counter + sample2.counter);
    
    // Test comparison operator (used for sorting)
    ASSERT_TRUE(sample1 < sample2); // sample1.counter (50) > sample2.counter (100) makes sample1 < sample2
    
    free(trace1);
    free(trace2);
}

// Fuzz test for CallTraceStorage basic operations
TEST(CallTraceStorageFuzzTest, BasicOperations) {
    CallTraceStorage storage;
    
    // Create random call traces
    const int num_iterations = 100;
    const int max_frames = 20;
    
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> frames_dist(1, max_frames);
    std::uniform_int_distribution<int> weight_dist(1, 100);
    std::uniform_int_distribution<int> bool_dist(0, 1);
    
    // Generate and store random call traces
    std::vector<std::vector<ASGCT_CallFrame>> stored_traces;
    
    for (int i = 0; i < num_iterations; i++) {
        int num_frames = frames_dist(gen);
        bool truncated = bool_dist(gen) == 1;
        u64 weight = weight_dist(gen);
        
        std::vector<ASGCT_CallFrame> frames(num_frames);
        generateRandomTrace(gen, frames.data(), num_frames);
        
        u32 trace_id = storage.put(num_frames, frames.data(), truncated, weight);
        
        // Verify the trace was stored (id should be non-zero except in rare cases)
        if (trace_id != 0) {
            stored_traces.push_back(frames);
        }
    }
    
    // Collect all traces and verify we can find at least some of them
    std::map<u32, CallTrace*> collected_traces;
    storage.collectTraces(collected_traces);
    
    ASSERT_GT(collected_traces.size(), 0);
    
    // Clear storage and verify it's empty
    storage.clear();
    
    std::map<u32, CallTrace*> empty_traces;
    storage.collectTraces(empty_traces);
    
    ASSERT_EQ(empty_traces.size(), 0);
}

// Test for hash collision handling
TEST(CallTraceStorageFuzzTest, HashCollisionHandling) {
    CallTraceStorage storage;
    
    // Create traces with slight differences to increase chance of collisions
    const int num_iterations = 1000;
    const int num_frames = 5;
    
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    
    std::vector<ASGCT_CallFrame> base_frames(num_frames);
    generateRandomTrace(gen, base_frames.data(), num_frames);
    
    // Store the same trace multiple times with small variations
    std::uniform_int_distribution<int> frame_idx_dist(0, num_frames - 1);
    std::uniform_int_distribution<int> bci_delta_dist(-10, 10);
    
    for (int i = 0; i < num_iterations; i++) {
        // Make a copy of the base frames
        std::vector<ASGCT_CallFrame> frames = base_frames;
        
        // Slightly modify one random frame
        int frame_to_modify = frame_idx_dist(gen);
        frames[frame_to_modify].bci += bci_delta_dist(gen);
        
        // Store the modified trace
        storage.put(num_frames, frames.data(), false, 1);
    }
    
    // Collect all traces
    std::map<u32, CallTrace*> collected_traces;
    storage.collectTraces(collected_traces);
    
    // We expect to have multiple traces stored due to the variations
    ASSERT_GT(collected_traces.size(), 1);
}

// Test with concurrent access
TEST(CallTraceStorageFuzzTest, ConcurrentAccess) {
    CallTraceStorage storage;
    
    // Create and run multiple threads that store traces concurrently
    const int num_threads = 4;
    const int traces_per_thread = 100;
    const int max_frames = 10;
    
    std::atomic<int> success_count(0);
    
    auto thread_func = [&](int thread_id) {
        unsigned int thread_seed = static_cast<unsigned int>(time(nullptr)) + thread_id;
        std::mt19937 gen(thread_seed);
        std::uniform_int_distribution<int> frames_dist(1, max_frames);
        std::uniform_int_distribution<int> bool_dist(0, 1);
        
        for (int i = 0; i < traces_per_thread; i++) {
            int num_frames = frames_dist(gen);
            bool truncated = bool_dist(gen) == 1;
            
            std::vector<ASGCT_CallFrame> frames(num_frames);
            generateRandomTrace(gen, frames.data(), num_frames);
            
            u32 trace_id = storage.put(num_frames, frames.data(), truncated, 1);
            
            if (trace_id != 0) {
                success_count++;
            }
        }
    };
    
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(thread_func, i);
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Verify that at least some traces were stored successfully
    ASSERT_GT(success_count, 0);
    
    // Collect traces and verify we have stored multiple traces
    std::map<u32, CallTrace*> collected_traces;
    storage.collectTraces(collected_traces);
    
    ASSERT_GT(collected_traces.size(), 0);
}

// Test with safer edge cases that shouldn't cause crashes
TEST(CallTraceStorageFuzzTest, SafeEdgeCases) {
    CallTraceStorage storage;
    
    // Case 1: Single frame trace
    {
        ASGCT_CallFrame frames[1];
        frames[0].bci = 42;
        frames[0].method_id = (jmethodID)12345;
        
        u32 trace_id = storage.put(1, frames, false, 1);
        // We just verify it doesn't crash
    }
    
    // Case 2: Small trace with truncation flag
    {
        ASGCT_CallFrame frames[3];
        frames[0].bci = 1;
        frames[0].method_id = (jmethodID)1001;
        frames[1].bci = 2;
        frames[1].method_id = (jmethodID)1002;
        frames[2].bci = 3;
        frames[2].method_id = (jmethodID)1003;
        
        u32 trace_id = storage.put(3, frames, true, 1);
        // Just verify it doesn't crash with truncation flag
    }
    
    // Case 3: Different weights
    {
        ASGCT_CallFrame frames[2];
        frames[0].bci = 100;
        frames[0].method_id = (jmethodID)2001;
        frames[1].bci = 200;
        frames[1].method_id = (jmethodID)2002;
        
        // Try different weights
        for (u64 weight : {1ULL, 10ULL, 100ULL, 1000ULL}) {
            u32 trace_id = storage.put(2, frames, false, weight);
            // Just verify it doesn't crash with different weights
        }
    }
}

// Stress test with repeated clear operations
TEST(CallTraceStorageFuzzTest, StressClearOperations) {
    CallTraceStorage storage;
    
    // Add traces, then clear, repeat multiple times
    const int num_cycles = 5;
    const int traces_per_cycle = 100;
    const int max_frames = 10;
    
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> frames_dist(1, max_frames);
    
    for (int cycle = 0; cycle < num_cycles; cycle++) {
        // Add traces
        for (int i = 0; i < traces_per_cycle; i++) {
            int num_frames = frames_dist(gen);
            
            std::vector<ASGCT_CallFrame> frames(num_frames);
            generateRandomTrace(gen, frames.data(), num_frames);
            
            storage.put(num_frames, frames.data(), false, 1);
        }
        
        // Verify traces were added
        std::map<u32, CallTrace*> collected_traces;
        storage.collectTraces(collected_traces);
        ASSERT_GT(collected_traces.size(), 0);
        
        // Clear storage
        storage.clear();
        
        // Verify storage is empty
        std::map<u32, CallTrace*> empty_traces;
        storage.collectTraces(empty_traces);
        ASSERT_EQ(empty_traces.size(), 0);
    }
}

// Test for duplicate trace detection
TEST(CallTraceStorageFuzzTest, DuplicateTraces) {
    CallTraceStorage storage;
    
    // Create a single trace and add it multiple times
    const int num_iterations = 10;
    const int num_frames = 5;
    
    ASGCT_CallFrame frames[num_frames];
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    generateRandomTrace(gen, frames, num_frames);
    
    u32 first_id = 0;
    u32 last_id = 0;
    
    // Add the same trace multiple times
    for (int i = 0; i < num_iterations; i++) {
        u32 trace_id = storage.put(num_frames, frames, false, 1);
        
        if (i == 0) {
            first_id = trace_id;
        }
        last_id = trace_id;
        
        // The trace IDs should be the same for identical traces
        ASSERT_EQ(trace_id, first_id);
    }
    
    // Collect traces and verify we have just one trace (or very few due to hash collisions)
    std::map<u32, CallTrace*> collected_traces;
    storage.collectTraces(collected_traces);
    
    // Even with hash collisions, the number should be much less than iterations
    ASSERT_LT(collected_traces.size(), num_iterations);
}

// Test for memory limitations by creating many traces
TEST(CallTraceStorageFuzzTest, MemoryLimitations) {
    CallTraceStorage storage;
    
    // Create many random call traces to test memory handling
    const int num_iterations = 10000;  // Large number of iterations
    const int num_frames = 20;  // Moderately sized traces
    
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    
    std::vector<u32> trace_ids;
    
    for (int i = 0; i < num_iterations; i++) {
        std::vector<ASGCT_CallFrame> frames(num_frames);
        generateRandomTrace(gen, frames.data(), num_frames);
        
        u32 trace_id = storage.put(num_frames, frames.data(), false, 1);
        if (trace_id != 0) {
            trace_ids.push_back(trace_id);
        }
        
        // Occasionally collect traces to verify the system is still functioning
        if (i % 1000 == 999) {
            std::map<u32, CallTrace*> collected_traces;
            storage.collectTraces(collected_traces);
            
            // We should have some traces, but we don't assert exactly how many
            // as the implementation may handle memory limitations differently
            ASSERT_GT(collected_traces.size(), 0);
        }
    }
    
    // Verify that at least some traces were stored
    ASSERT_GT(trace_ids.size(), 0);
} 