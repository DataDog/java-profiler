#include <gtest/gtest.h>
#include "linearAllocator.h"
#include "arch_dd.h" // For standard type definitions
#include <string.h>
#include <vector>

class LinearAllocatorTest : public ::testing::Test {
protected:
    const size_t DEFAULT_CHUNK_SIZE = 4096;
};

// Test basic allocation functionality
TEST_F(LinearAllocatorTest, BasicAllocation) {
    LinearAllocator allocator(DEFAULT_CHUNK_SIZE);
    
    // Allocate memory and verify it's non-null
    void* ptr1 = allocator.alloc(100);
    ASSERT_NE(nullptr, ptr1);
    
    // Make sure we can write to the allocated memory
    memset(ptr1, 0xCC, 100);
    
    // Allocate a second chunk and verify it's different from the first
    void* ptr2 = allocator.alloc(100);
    ASSERT_NE(nullptr, ptr2);
    ASSERT_NE(ptr1, ptr2);
    
    // Write to the second allocation
    memset(ptr2, 0xDD, 100);
}

// Test that clear resets the allocator
TEST_F(LinearAllocatorTest, ClearReset) {
    LinearAllocator allocator(DEFAULT_CHUNK_SIZE);
    
    // Fill up most of a chunk
    const size_t ALLOC_SIZE = 1000;
    void* ptr1 = allocator.alloc(ALLOC_SIZE);
    void* ptr2 = allocator.alloc(ALLOC_SIZE);
    void* ptr3 = allocator.alloc(ALLOC_SIZE);
    
    ASSERT_NE(nullptr, ptr1);
    ASSERT_NE(nullptr, ptr2);
    ASSERT_NE(nullptr, ptr3);
    
    // Clear the allocator
    allocator.clear();
    
    // After clear, the next allocation should be at the beginning again
    void* ptr_after_clear = allocator.alloc(ALLOC_SIZE);
    ASSERT_NE(nullptr, ptr_after_clear);
    
    // Since LinearAllocator reuses the same chunk after clear(),
    // the new pointer should be close to the initial one
    // We can compare pointers as ptrdiff_t values
    ASSERT_EQ(reinterpret_cast<ptrdiff_t>(ptr1), 
              reinterpret_cast<ptrdiff_t>(ptr_after_clear));
}

// Test allocation of memory that spans multiple chunks
TEST_F(LinearAllocatorTest, MultipleChunks) {
    const size_t SMALL_CHUNK_SIZE = 1024;
    LinearAllocator allocator(SMALL_CHUNK_SIZE);
    
    // Allocate memory that will fill the first chunk
    void* ptr1 = allocator.alloc(SMALL_CHUNK_SIZE - sizeof(Chunk) - 8);
    ASSERT_NE(nullptr, ptr1);
    
    // This allocation should go to a new chunk
    void* ptr2 = allocator.alloc(100);
    ASSERT_NE(nullptr, ptr2);
    
    // Write to both allocations to verify they're valid
    memset(ptr1, 0xAA, SMALL_CHUNK_SIZE - sizeof(Chunk) - 8);
    memset(ptr2, 0xBB, 100);
}

// Test behavior when allocating very small chunks
TEST_F(LinearAllocatorTest, SmallAllocations) {
    LinearAllocator allocator(DEFAULT_CHUNK_SIZE);
    
    // Allocate many small chunks
    const int NUM_ALLOCS = 1000;
    std::vector<void*> ptrs;
    
    for (int i = 0; i < NUM_ALLOCS; i++) {
        void* ptr = allocator.alloc(8);
        ASSERT_NE(nullptr, ptr);
        ptrs.push_back(ptr);
    }
    
    // Verify all allocations are usable
    for (int i = 0; i < NUM_ALLOCS; i++) {
        memset(ptrs[i], i & 0xFF, 8);
    }
    
    // Clear and verify we can allocate again
    allocator.clear();
    void* ptr = allocator.alloc(8);
    ASSERT_NE(nullptr, ptr);
}

// Test behavior with zero-sized allocation
TEST_F(LinearAllocatorTest, ZeroSizeAllocation) {
    LinearAllocator allocator(DEFAULT_CHUNK_SIZE);
    
    // Allocate with size 0
    void* ptr = allocator.alloc(0);
    
    // Implementation-dependent whether this returns nullptr or a valid pointer
    // Just make sure it doesn't crash
}

// Test allocating the entire chunk size
TEST_F(LinearAllocatorTest, LargeAllocation) {
    const size_t CHUNK_SIZE = 16384;
    LinearAllocator allocator(CHUNK_SIZE);
    
    // Try to allocate most of the chunk
    // Note: need to account for the Chunk header size and any alignment requirements
    void* ptr = allocator.alloc(CHUNK_SIZE - sizeof(Chunk) - 64);
    
    // This may succeed or fail depending on implementation details
    if (ptr != nullptr) {
        // If it succeeded, we should be able to write to it
        memset(ptr, 0xEE, CHUNK_SIZE - sizeof(Chunk) - 64);
    }
}

// Test allocation after many chunk allocations and releases
TEST_F(LinearAllocatorTest, ChunkReuseAfterClear) {
    LinearAllocator allocator(DEFAULT_CHUNK_SIZE);
    
    for (int i = 0; i < 5; i++) {
        // Fill up a chunk
        std::vector<void*> ptrs;
        for (int j = 0; j < 10; j++) {
            void* ptr = allocator.alloc(DEFAULT_CHUNK_SIZE / 20);
            ASSERT_NE(nullptr, ptr);
            ptrs.push_back(ptr);
        }
        
        // Write to the allocated memory
        for (size_t j = 0; j < ptrs.size(); j++) {
            memset(ptrs[j], 0xAA, DEFAULT_CHUNK_SIZE / 20);
        }
        
        // Clear and verify next round works
        allocator.clear();
    }
    
    // Final allocation should succeed
    void* final_ptr = allocator.alloc(100);
    ASSERT_NE(nullptr, final_ptr);
    memset(final_ptr, 0xFF, 100);
} 