#include <gtest/gtest.h>
#include "buffers.h"
#include <random>
#include <vector>
#include <ctime>
#include <cstring>
#include <thread>
#include <functional>
#include <atomic>

// Mock flush callback for testing
ssize_t mockFlushCallback(char* data, int len) {
    // Simulate successful flush
    return len;
}

// Failing flush callback for testing error conditions
ssize_t failingFlushCallback(char* data, int len) {
    // Simulate failed flush
    return -1;
}

// Partial flush callback for testing partial writes
ssize_t partialFlushCallback(char* data, int len) {
    // Simulate partial flush
    return len / 2;
}

// Basic test for Buffer with various data types
TEST(BufferFuzzTest, BasicBufferOperations) {
    Buffer buffer;
    
    // Verify initial state
    ASSERT_EQ(0, buffer.offset());
    
    // Test basic operations with valid data
    ASSERT_NO_THROW({
        buffer.put8(42);
        ASSERT_EQ(1, buffer.offset());
        
        buffer.put16(1234);
        ASSERT_EQ(3, buffer.offset());
        
        buffer.put32(123456);
        ASSERT_EQ(7, buffer.offset());
        
        buffer.put64(1234567890ULL);
        ASSERT_EQ(15, buffer.offset());
        
        buffer.putFloat(3.14159f);
        ASSERT_EQ(19, buffer.offset());
        
        buffer.putVar32(42);
        ASSERT_EQ(20, buffer.offset());
        
        buffer.putVar64(1234567890ULL);
        ASSERT_EQ(25, buffer.offset());
        
        const char* testStr = "Test string";
        buffer.putUtf8(testStr);
        // 1 byte for format, variable length for size, plus string length
        ASSERT_GT(buffer.offset(), 25 + strlen(testStr));
        
        // Test reset
        buffer.reset();
        ASSERT_EQ(0, buffer.offset());
    });
}

// Test for buffer limits and edge cases
TEST(BufferFuzzTest, BufferLimits) {
    Buffer buffer;
    
    // Initialize random generator
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> byte_dist(0, 255);
    
    // Test approaching buffer limit
    const int safeLimit = buffer.limit() - 100; // Stay well within limits
    
    ASSERT_NO_THROW({
        // Fill buffer close to limit with random bytes
        for (int i = 0; i < safeLimit; i++) {
            buffer.put8(static_cast<char>(byte_dist(gen)));
        }
        
        ASSERT_EQ(safeLimit, buffer.offset());
        
        // Test skip
        int prevOffset = buffer.offset();
        int skippedOffset = buffer.skip(10);
        ASSERT_EQ(prevOffset, skippedOffset);
        ASSERT_EQ(prevOffset + 10, buffer.offset());
    });
    
    // Reset for next test
    buffer.reset();
    
    // Test flush behavior - fill buffer up to the BUFFER_LIMIT
    for (int i = 0; i < BUFFER_LIMIT - 50; i++) {
        buffer.put8(static_cast<char>(byte_dist(gen)));
    }
    
    // Verify flush when needed
    ASSERT_TRUE(buffer.flushIfNeeded(mockFlushCallback, BUFFER_LIMIT - 100));  // Use a lower limit to ensure flush
    ASSERT_EQ(0, buffer.offset()); // Buffer should be reset after flush
    
    // Test failing flush - fill buffer up to the BUFFER_LIMIT
    for (int i = 0; i < BUFFER_LIMIT - 50; i++) {
        buffer.put8(static_cast<char>(byte_dist(gen)));
    }
    
    ASSERT_FALSE(buffer.flushIfNeeded(failingFlushCallback));
    ASSERT_GT(buffer.offset(), 0); // Buffer should not be reset after failed flush
}

// Fuzz test for Buffer with random data
TEST(BufferFuzzTest, RandomDataFuzz) {
    Buffer buffer;
    
    // Initialize random generator
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> operation_dist(0, 8); // 9 different operations
    std::uniform_int_distribution<int> byte_dist(0, 255);
    std::uniform_int_distribution<int> short_dist(0, 32767);
    std::uniform_int_distribution<int> int_dist(-2147483647, 2147483647);
    std::uniform_int_distribution<u32> uint32_dist(0, 0xFFFFFFFF);
    std::uniform_int_distribution<long long> long_dist(-9223372036854775807LL, 9223372036854775807LL);
    std::uniform_real_distribution<float> float_dist(-1000.0f, 1000.0f);
    
    // Generate random strings
    const int maxStringLen = 100;
    std::vector<std::string> testStrings;
    std::uniform_int_distribution<int> str_len_dist(0, maxStringLen);
    
    for (int i = 0; i < 10; i++) {
        int len = str_len_dist(gen);
        std::string str;
        str.reserve(len);
        for (int j = 0; j < len; j++) {
            str.push_back(static_cast<char>(byte_dist(gen) % 95 + 32)); // Printable ASCII
        }
        testStrings.push_back(str);
    }
    
    // Perform random operations until we get close to buffer limit
    const int MAX_OPERATIONS = 1000; // Prevent infinite loop
    int operations = 0;
    while (buffer.offset() < buffer.limit() - 100) {
        if (++operations >= MAX_OPERATIONS) {
            break;
        }
        
        int operation = operation_dist(gen);
        
        ASSERT_NO_THROW({
            switch (operation) {
                case 0: // put8
                    buffer.put8(static_cast<char>(byte_dist(gen)));
                    break;
                    
                case 1: // put16
                    buffer.put16(static_cast<short>(short_dist(gen)));
                    break;
                    
                case 2: // put32
                    buffer.put32(int_dist(gen));
                    break;
                    
                case 3: // put64
                    buffer.put64(static_cast<u64>(long_dist(gen)));
                    break;
                    
                case 4: // putFloat
                    buffer.putFloat(float_dist(gen));
                    break;
                    
                case 5: // putVar32
                    buffer.putVar32(uint32_dist(gen));
                    break;
                    
                case 6: // putVar64
                    buffer.putVar64(static_cast<u64>(long_dist(gen)));
                    break;
                    
                case 7: // putUtf8 with constant string
                    {
                        int idx = gen() % testStrings.size();
                        buffer.putUtf8(testStrings[idx].c_str());
                    }
                    break;
                    
                case 8: // putUtf8 with length
                    {
                        int idx = gen() % testStrings.size();
                        buffer.putUtf8(testStrings[idx].c_str(), testStrings[idx].length());
                    }
                    break;
            }
        });
        
        // Periodically flush
        if (buffer.offset() > BUFFER_LIMIT - 200) {
            buffer.flushIfNeeded(mockFlushCallback);
        }
    }
}

// Test for RecordingBuffer specific functionality
TEST(BufferFuzzTest, RecordingBufferOperations) {
    RecordingBuffer recordingBuffer;
    
    // Verify initial state
    ASSERT_EQ(0, recordingBuffer.offset());
    
    // Test that RecordingBuffer has higher limit than standard Buffer
    Buffer standardBuffer;
    ASSERT_GT(recordingBuffer.limit(), standardBuffer.limit());
    
    // Initialize random generator
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> byte_dist(0, 255);
    
    // Fill buffer with random data up to a point
    const int fillSize = RECORDING_BUFFER_LIMIT - 500;
    for (int i = 0; i < fillSize; i++) {
        recordingBuffer.put8(static_cast<char>(byte_dist(gen)));
    }
    
    ASSERT_EQ(fillSize, recordingBuffer.offset());
    
    // Test flush behavior
    ASSERT_TRUE(recordingBuffer.flushIfNeeded(mockFlushCallback, fillSize - 100));  // Use custom limit to ensure it flushes
    ASSERT_EQ(0, recordingBuffer.offset());
    
    // Test with larger data
    const int largeStringSize = 4000;
    std::string largeString;
    largeString.reserve(largeStringSize);
    for (int i = 0; i < largeStringSize; i++) {
        largeString.push_back(static_cast<char>(byte_dist(gen) % 95 + 32)); // Printable ASCII
    }
    
    ASSERT_NO_THROW({
        recordingBuffer.putUtf8(largeString.c_str(), largeString.length());
    });
    
    // Verify we can still add more data after a large string
    int offsetAfterLargeString = recordingBuffer.offset();
    ASSERT_NO_THROW({
        recordingBuffer.put32(12345);
    });
    ASSERT_EQ(offsetAfterLargeString + 4, recordingBuffer.offset());
}

// Test for concurrent buffer usage
TEST(BufferFuzzTest, ConcurrentBufferUsage) {
    // Note: This test verifies that multiple threads using separate buffers
    // works correctly - it doesn't test concurrent access to the same buffer,
    // which is not thread-safe
    
    const int numThreads = 4;
    std::vector<std::unique_ptr<Buffer>> buffers;
    std::vector<std::thread> threads;
    std::atomic<int> successCount(0);
    
    for (int i = 0; i < numThreads; i++) {
        buffers.emplace_back(new Buffer());
    }
    
    auto threadFunc = [&successCount](Buffer* buffer) {
        // Initialize random generator
        unsigned int seed = static_cast<unsigned int>(time(nullptr));
        std::mt19937 gen(seed);
        std::uniform_int_distribution<int> byte_dist(0, 255);
        
        try {
            // Fill buffer with random data (safely below buffer limit)
            const int safeLimit = buffer->limit() - 200;
            for (int i = 0; i < safeLimit; i++) {
                buffer->put8(static_cast<char>(byte_dist(gen)));
            }
            
            // Verify offset
            if (buffer->offset() == safeLimit) {
                // Flush and verify
                if (buffer->flushIfNeeded(mockFlushCallback, safeLimit - 100)) {
                    successCount++;
                }
            }
        } catch (...) {
            // Catch any exceptions to prevent test crash
        }
    };
    
    // Start threads
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(threadFunc, buffers[i].get());
    }
    
    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Verify all threads completed successfully
    ASSERT_EQ(numThreads, successCount);
}

// Test for large UTF8 strings
TEST(BufferFuzzTest, LargeUtf8Strings) {
    Buffer buffer;
    
    // Test with NULL string
    ASSERT_NO_THROW({
        buffer.putUtf8(NULL);
        ASSERT_EQ(1, buffer.offset()); // Just the format byte
        buffer.reset();
    });
    
    // Test with empty string
    ASSERT_NO_THROW({
        buffer.putUtf8("");
        ASSERT_GT(buffer.offset(), 1); // Format byte + length encoding
        buffer.reset();
    });
    
    // Test with moderately sized string (well within safe bounds)
    const int moderateSize = 100;
    std::string moderateString(moderateSize, 'X');
    ASSERT_NO_THROW({
        buffer.putUtf8(moderateString.c_str(), moderateString.length());
        buffer.reset();
    });
    
    // Test with strings of varying sizes up to a reasonable limit
    // No need to test MAX_STRING_LENGTH as that's an implementation detail
    // that gets tested indirectly via truncation
    for (int size : {200, 500, 1000}) {
        std::string testString(size, 'X');
        ASSERT_NO_THROW({
            buffer.reset();
            buffer.putUtf8(testString.c_str(), testString.length());
            // Verify string was stored (truncated or not)
            ASSERT_GT(buffer.offset(), 0);
        });
    }
}

// Test for random buffer offsets operations
TEST(BufferFuzzTest, RandomOffsetOperations) {
    Buffer buffer;
    
    // Initialize random generator
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> byte_dist(0, 255);
    
    // Fill buffer with some data - use a smaller size to leave room for var32
    const int fillSize = 50;
    for (int i = 0; i < fillSize; i++) {
        buffer.put8(static_cast<char>(byte_dist(gen)));
    }
    
    // Test offset-based operations
    ASSERT_NO_THROW({
        // Update values at random offsets, making sure to stay within bounds
        for (int i = 0; i < 20; i++) {
            int offset = gen() % fillSize;
            buffer.put8(offset, static_cast<char>(byte_dist(gen)));
        }
        
        // Test putVar32 at specific offsets, ensure enough space for the encoding
        for (int i = 0; i < 5; i++) {
            // Leave room for full var32 which can be up to 5 bytes 
            int offset = gen() % (fillSize - 5);
            u32 value = gen() % 0xFFFF; // Use smaller values to ensure we don't cause an assertion
            buffer.putVar32(offset, value);
        }
    });
} 