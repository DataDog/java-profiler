#include <gtest/gtest.h>
#include "linearAllocator.h"
#include "arch_dd.h" // For standard type definitions
#include <random>
#include <chrono>
#include <vector>
#include <thread>
#include <atomic>
#include <cstring>
#include <time.h>

// Fuzz test for LinearAllocator::alloc with random sizes
TEST(LinearAllocatorFuzzTest, AllocRandomSizes) {
    // Test with different chunk sizes
    const std::vector<size_t> chunk_sizes = {4096, 8192, 16384};
    
    // Initialize random generator with current time as seed
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    // Size distribution within reasonable bounds for testing
    std::uniform_int_distribution<size_t> size_dist(1, 1024);
    
    for (auto chunk_size : chunk_sizes) {
        LinearAllocator allocator(chunk_size);
        
        // Make multiple allocations with random sizes
        for (int i = 0; i < 1000; i++) {
            size_t alloc_size = size_dist(gen);
            
            // Call alloc within ASSERT_NO_THROW
            ASSERT_NO_THROW({
                void* ptr = allocator.alloc(alloc_size);
                // Verify allocation succeeded
                ASSERT_NE(nullptr, ptr);
                
                // Try to write to the allocated memory to ensure it's valid
                if (ptr != nullptr) {
                    memset(ptr, 0xAB, alloc_size);
                }
            });
            
            // Clear every 100 iterations to prevent OOM
            if (i % 100 == 99) {
                allocator.clear();
            }
        }
        
        // Test clear functionality
        ASSERT_NO_THROW({
            allocator.clear();
        });
        
        // Verify we can allocate again after clearing
        ASSERT_NO_THROW({
            void* ptr = allocator.alloc(64);
            ASSERT_NE(nullptr, ptr);
        });
    }
}

// Test for LinearAllocator with concurrent threads
TEST(LinearAllocatorFuzzTest, ConcurrentAlloc) {
    const size_t chunk_size = 16384;
    const int num_threads = 4;
    const int allocs_per_thread = 100;
    
    // Initialize random generator with current time as seed
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<size_t> size_dist(1, 128); // Smaller allocations for concurrent test
    
    LinearAllocator allocator(chunk_size);
    std::atomic<int> success_count(0);
    
    auto allocation_func = [&allocator, &size_dist, &gen, &success_count, allocs_per_thread]() {
        for (int i = 0; i < allocs_per_thread; i++) {
            size_t alloc_size = size_dist(gen);
            void* ptr = allocator.alloc(alloc_size);
            if (ptr != nullptr) {
                // Write to memory to verify it's usable
                memset(ptr, i & 0xFF, alloc_size);
                success_count++;
            }
        }
    };
    
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(allocation_func);
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Verify most allocations succeeded
    ASSERT_GE(success_count, num_threads * allocs_per_thread * 0.9);
    
    // Test that clear works after concurrent allocations
    ASSERT_NO_THROW({
        allocator.clear();
    });
}

// Edge case test with very small and large allocation sizes
TEST(LinearAllocatorFuzzTest, EdgeCaseSizes) {
    const size_t chunk_size = 8192;
    LinearAllocator allocator(chunk_size);
    
    // Test very small allocation
    ASSERT_NO_THROW({
        void* ptr = allocator.alloc(1);
        ASSERT_NE(nullptr, ptr);
    });
    
    // Test allocation of size 0
    ASSERT_NO_THROW({
        void* ptr = allocator.alloc(0);
        // The implementation may or may not allocate for size 0
    });
    
    // Test allocation close to chunk size (but not exceeding it)
    ASSERT_NO_THROW({
        void* ptr = allocator.alloc(chunk_size - sizeof(Chunk) - 64);
        // Should succeed without issues
        if (ptr != nullptr) {
            memset(ptr, 0xAA, chunk_size - sizeof(Chunk) - 64);
        }
    });
    
    // Clear before attempting large allocation
    allocator.clear();
    
    // Test allocation that's just a bit larger than chunk size
    // This is likely to fail but shouldn't hang
    void* large_ptr = allocator.alloc(chunk_size + 8);
    // Just verify it doesn't crash, we don't care about the result
    // The implementation should return nullptr for too large allocations
}

// Test multiple clears and allocations
TEST(LinearAllocatorFuzzTest, MultipleClears) {
    const size_t chunk_size = 4096;
    LinearAllocator allocator(chunk_size);
    
    for (int i = 0; i < 5; i++) {
        // Allocate several blocks
        for (int j = 0; j < 10; j++) {
            void* ptr = allocator.alloc(100);
            ASSERT_NE(nullptr, ptr);
            memset(ptr, 0xCD, 100);
        }
        
        // Clear and verify we can allocate again
        allocator.clear();
        void* ptr = allocator.alloc(200);
        ASSERT_NE(nullptr, ptr);
        memset(ptr, 0xEF, 200);
    }
} 