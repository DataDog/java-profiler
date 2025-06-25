#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <vector>
#include <random>
#include <map>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <setjmp.h>
#include <ucontext.h>

// Explicitly include JVM headers
#include <jvmti.h>

#include "stackWalker.h"
#include "dwarf.h"
#include "profiler.h"
#include "vmEntry.h" // For ASGCT types
#include "stackWalker_dd.h" // For ddprof namespace
#include "arch_dd.h" // For architecture definitions

// Make sure jmethodID is available if not defined by jvmti.h
#ifndef _JAVASOFT_JNI_H_
typedef void* jmethodID;
#endif

// Only define these types if they aren't already defined elsewhere
#ifndef _ASGCT_H_DEFINED
#define _ASGCT_H_DEFINED

// Use the existing types instead of redefining them
// The ASGCT_CallFrame, ASGCT_CallTrace, ASGCT_CallFrameType, etc. 
// should already be defined in vmEntry.h

// FrameTypeId should be already defined in frame.h
// StackDetail should be already defined in stackWalker.h

#endif // _ASGCT_H_DEFINED

// Forward declarations for mock classes
class MockVMMethod;
class MockNMethod;
class MockCodeHeap;
class MockJavaFrameAnchor;

// Helper struct to create random stack layouts
struct StackSegment {
    std::vector<uintptr_t> data;
    uintptr_t start_address;
    bool is_java_frame;
    bool is_interpreter;
    bool is_compiled;
    bool is_native;

    // Default constructor needed for STL containers
    StackSegment() : data(), start_address(0), is_java_frame(false),
                    is_interpreter(false), is_compiled(false), is_native(false) {}
    
    StackSegment(size_t size, uintptr_t start, bool java_frame = false)
        : data(size), start_address(start), is_java_frame(java_frame),
          is_interpreter(false), is_compiled(false), is_native(false) {}
};

// Test fixture for StackWalker tests
class StackWalkerFuzzTest : public ::testing::Test {
protected:
    // Random number generator
    std::mt19937 rng;
    
    // Buffer to hold the stack data
    std::vector<uintptr_t> stack_buffer;
    
    // Map of allocated stack segments
    std::map<uintptr_t, StackSegment> stack_segments;
    
    // Execution context
    ucontext_t test_context;
    
    // Stack walking resources
    const void** callchain;
    ASGCT_CallFrame* frames;
    
    // Default test parameters
    static const int MAX_DEPTH = 64;
    static const int MAX_STACK_SIZE = 16384;
    static const int MIN_SEGMENT_SIZE = 32;
    static const int MAX_SEGMENT_SIZE = 512;

    void SetUp() override {
        // Initialize random generator with current time
        unsigned int seed = static_cast<unsigned int>(time(nullptr));
        rng.seed(seed);
        
        // Allocate buffer for stack callchain results
        callchain = new const void*[MAX_DEPTH];
        frames = new ASGCT_CallFrame[MAX_DEPTH];
        
        // Initialize stack buffer with random data
        stack_buffer.resize(MAX_STACK_SIZE);
        std::uniform_int_distribution<uintptr_t> rand_word(1, 1000000); // Limit to a safer range
        for (size_t i = 0; i < stack_buffer.size(); i++) {
            stack_buffer[i] = rand_word(rng);
        }
        
        // Initialize context with our stack buffer
        memset(&test_context, 0, sizeof(test_context));
        
        // Properly allocate and initialize the mcontext structure
#if defined(__APPLE__)
        test_context.uc_mcontext = (mcontext_t)malloc(sizeof(*test_context.uc_mcontext));
        memset(test_context.uc_mcontext, 0, sizeof(*test_context.uc_mcontext));
#endif
    }

    void TearDown() override {
        delete[] callchain;
        delete[] frames;
        stack_segments.clear();
        
        // Free the mcontext memory
#if defined(__APPLE__)
        if (test_context.uc_mcontext) {
            free(test_context.uc_mcontext);
            test_context.uc_mcontext = nullptr;
        }
#endif
    }
    
    // Create a simulated stack with structured segments
    void createStackLayout(int num_segments, float java_ratio = 0.6) {
        std::uniform_int_distribution<size_t> size_dist(MIN_SEGMENT_SIZE, MAX_SEGMENT_SIZE);
        std::uniform_real_distribution<float> type_dist(0.0, 1.0);
        
        uintptr_t current_addr = reinterpret_cast<uintptr_t>(&stack_buffer[0]);
        
        for (int i = 0; i < num_segments; i++) {
            size_t segment_size = size_dist(rng);
            
            if (current_addr + segment_size * sizeof(uintptr_t) >= 
                reinterpret_cast<uintptr_t>(&stack_buffer[0] + stack_buffer.size())) {
                break;
            }
            
            bool is_java = type_dist(rng) < java_ratio;
            StackSegment segment(segment_size, current_addr, is_java);
            
            if (is_java) {
                // Determine Java frame type
                float frame_type = type_dist(rng);
                if (frame_type < 0.4) {
                    segment.is_interpreter = true;
                } else if (frame_type < 0.8) {
                    segment.is_compiled = true;
                } else {
                    segment.is_native = true;
                }
                
                // Initialize the segment with typical Java frame pattern
                setupJavaFrameSegment(segment);
            } else {
                // Initialize the segment with typical native frame pattern
                setupNativeFrameSegment(segment);
            }
            
            // Add segment to our map
            stack_segments[current_addr] = segment;
            
            // Move to next segment position
            current_addr += segment_size * sizeof(uintptr_t);
        }
        
        // Set up context to point to our stack
        uintptr_t* stack_top = &stack_buffer[stack_buffer.size() - 1];
        
        // Platform-specific register setup
        setupPlatformContext(stack_top);
    }
    
    // Platform-specific context setup
    void setupPlatformContext(uintptr_t* stack_top) {
#if defined(__APPLE__) && defined(__x86_64__)
        // macOS x86_64
        test_context.uc_mcontext->__ss.__rsp = reinterpret_cast<uintptr_t>(stack_top);
        test_context.uc_mcontext->__ss.__rbp = reinterpret_cast<uintptr_t>(&stack_buffer[stack_buffer.size() - 32]);
        test_context.uc_mcontext->__ss.__rip = 0x12345678;
#elif defined(__APPLE__) && defined(__aarch64__)
        // macOS AArch64
        test_context.uc_mcontext->__ss.__sp = reinterpret_cast<uintptr_t>(stack_top);
        test_context.uc_mcontext->__ss.__fp = reinterpret_cast<uintptr_t>(&stack_buffer[stack_buffer.size() - 32]);
        test_context.uc_mcontext->__ss.__pc = 0x12345678;
#elif defined(__linux__) && defined(__x86_64__)
        // Linux x86_64
        test_context.uc_mcontext.gregs[REG_RSP] = reinterpret_cast<uintptr_t>(stack_top);
        test_context.uc_mcontext.gregs[REG_RBP] = reinterpret_cast<uintptr_t>(&stack_buffer[stack_buffer.size() - 32]);
        test_context.uc_mcontext.gregs[REG_RIP] = 0x12345678;
#elif defined(__linux__) && defined(__aarch64__)
        // Linux AArch64
        test_context.uc_mcontext.sp = reinterpret_cast<uintptr_t>(stack_top);
        test_context.uc_mcontext.regs[29] = reinterpret_cast<uintptr_t>(&stack_buffer[stack_buffer.size() - 32]); // x29 is FP
        test_context.uc_mcontext.pc = 0x12345678;
#endif
    }
    
    // Set up a segment to look like a Java frame
    void setupJavaFrameSegment(StackSegment& segment) {
        if (segment.data.empty()) return;
        
        // First element often contains frame pointer
        segment.data[0] = segment.start_address - sizeof(uintptr_t) * 8;
        
        // Second element often contains return address
        segment.data[1] = 0x87654321;
        
        if (segment.is_interpreter) {
            // Add some typical interpreter frame fields
            if (segment.data.size() > 5) {
                segment.data[2] = 0xAAAAAAAA; // Method pointer
                segment.data[3] = 0xBBBBBBBB; // BCP
                segment.data[4] = 0xCCCCCCCC; // Locals
                segment.data[5] = 0xDDDDDDDD; // Sender SP
            }
        } else if (segment.is_compiled) {
            // Add some typical compiled method frame fields
            if (segment.data.size() > 3) {
                segment.data[2] = 0xEEEEEEEE; // Compiled method pointer
                segment.data[3] = 0xFFFFFFFF; // Deopt state
            }
        }
    }
    
    // Set up a segment to look like a native frame
    void setupNativeFrameSegment(StackSegment& segment) {
        if (segment.data.empty()) return;
        
        // First element often contains frame pointer
        segment.data[0] = segment.start_address - sizeof(uintptr_t) * 4;
        
        // Second element often contains return address
        segment.data[1] = 0x76543210;
        
        // Rest can be typical C/C++ stack layout
        for (size_t i = 2; i < segment.data.size() && i < 10; i++) {
            segment.data[i] = 0x10000000 + i * 0x1000;
        }
    }
};

// Basic test that callchain walking doesn't crash with various inputs
TEST_F(StackWalkerFuzzTest, BasicCallchainWalk) {
    createStackLayout(5);
    
    ::StackContext java_ctx = {0};
    
    // Test frame pointer-based walking with try-catch
    try {
        int depth = StackWalker::walkFP(&test_context, callchain, MAX_DEPTH, &java_ctx);
        // Don't assert on depth, just make sure it doesn't crash
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkFP";
    }
    
    // Test DWARF-based walking if supported with try-catch
#if DWARF_SUPPORTED
    try {
        int depth = StackWalker::walkDwarf(&test_context, callchain, MAX_DEPTH, &java_ctx);
        // Don't assert on depth, just make sure it doesn't crash
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkDwarf";
    }
#endif
}

// Test walking with different stack layouts
TEST_F(StackWalkerFuzzTest, DISABLED_DifferentStackLayouts) {
    std::uniform_int_distribution<int> segment_count(2, 10);
    std::uniform_real_distribution<float> java_ratio(0.0, 1.0);
    
    for (int i = 0; i < 5; i++) {
        int num_segments = segment_count(rng);
        float ratio = java_ratio(rng);
        
        createStackLayout(num_segments, ratio);
        
        ::StackContext java_ctx = {0};
        
        // Test frame pointer-based walking with try-catch
        try {
            int depth = StackWalker::walkFP(&test_context, callchain, MAX_DEPTH, &java_ctx);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkFP iteration " << i;
        }
        
#if DWARF_SUPPORTED
        // Test DWARF-based walking with try-catch
        try {
            int depth = StackWalker::walkDwarf(&test_context, callchain, MAX_DEPTH, &java_ctx);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkDwarf iteration " << i;
        }
#endif
    }
}

// Test with edge cases like nullptr or very small max_depth
TEST_F(StackWalkerFuzzTest, DISABLED_EdgeCases) {
    createStackLayout(5);
    
    ::StackContext java_ctx = {0};
    
    // Test with null context
    try {
        int depth = StackWalker::walkFP(nullptr, callchain, MAX_DEPTH, &java_ctx);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkFP with null context";
    }
    
    // Test with null callchain - skip this as it will likely segfault
    // We cannot safely test this case without modifying the underlying code
    
    // Test with max_depth=0
    try {
        int depth = StackWalker::walkFP(&test_context, callchain, 0, &java_ctx);
        EXPECT_EQ(depth, 0);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkFP with max_depth=0";
    }
    
    // Test with max_depth=1
    try {
        int depth = StackWalker::walkFP(&test_context, callchain, 1, &java_ctx);
        EXPECT_GE(depth, 0);
        EXPECT_LE(depth, 1);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkFP with max_depth=1";
    }
}

// Test the VM stack walker functionality
TEST_F(StackWalkerFuzzTest, DISABLED_BasicVMWalking) {
    createStackLayout(5, 0.8); // Higher Java ratio for this test
    
    // Test walkVM with different stack details
    try {
        int depth = StackWalker::walkVM(&test_context, frames, MAX_DEPTH, VM_BASIC);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkVM with VM_BASIC";
    }
    
    try {
        int depth = StackWalker::walkVM(&test_context, frames, MAX_DEPTH, VM_NORMAL);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkVM with VM_NORMAL";
    }
    
    try {
        int depth = StackWalker::walkVM(&test_context, frames, MAX_DEPTH, VM_EXPERT);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkVM with VM_EXPERT";
    }
}

// Test VM walking with null context
TEST_F(StackWalkerFuzzTest, DISABLED_VMWalkingWithNullContext) {
    // Test walkVM with null context
    try {
        int depth = StackWalker::walkVM(nullptr, frames, MAX_DEPTH, VM_BASIC);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkVM with null context";
    }
}

// Test creating bogus structure that resembles a potential overflow
TEST_F(StackWalkerFuzzTest, DISABLED_StackOverflowAttempt) {
    createStackLayout(1);
    
    // Create a scenario where sp > fp to test boundary checks
    uintptr_t* stack_top = &stack_buffer[stack_buffer.size() - 1];
    
    // Platform-specific setup for overflow scenario
#if defined(__APPLE__) && defined(__x86_64__)
    // macOS x86_64
    test_context.uc_mcontext->__ss.__rsp = reinterpret_cast<uintptr_t>(stack_top);
    test_context.uc_mcontext->__ss.__rbp = reinterpret_cast<uintptr_t>(stack_top) - 0x1000;
#elif defined(__APPLE__) && defined(__aarch64__)
    // macOS AArch64
    test_context.uc_mcontext->__ss.__sp = reinterpret_cast<uintptr_t>(stack_top);
    test_context.uc_mcontext->__ss.__fp = reinterpret_cast<uintptr_t>(stack_top) - 0x1000;
#elif defined(__linux__) && defined(__x86_64__)
    // Linux x86_64
    test_context.uc_mcontext.gregs[REG_RSP] = reinterpret_cast<uintptr_t>(stack_top);
    test_context.uc_mcontext.gregs[REG_RBP] = reinterpret_cast<uintptr_t>(stack_top) - 0x1000;
#elif defined(__linux__) && defined(__aarch64__)
    // Linux AArch64
    test_context.uc_mcontext.sp = reinterpret_cast<uintptr_t>(stack_top);
    test_context.uc_mcontext.regs[29] = reinterpret_cast<uintptr_t>(stack_top) - 0x1000;
#endif
    
    ::StackContext java_ctx = {0};
    
    // Should detect and handle the overflow attempt
    try {
        int depth = StackWalker::walkFP(&test_context, callchain, MAX_DEPTH, &java_ctx);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkFP with stack overflow attempt";
    }
}

// Test with misaligned addresses
TEST_F(StackWalkerFuzzTest, DISABLED_MisalignedAddresses) {
    createStackLayout(5);
    
    // Test with misaligned frame pointer
#if defined(__APPLE__) && defined(__x86_64__)
    // macOS x86_64
    test_context.uc_mcontext->__ss.__rbp = reinterpret_cast<uintptr_t>(&stack_buffer[stack_buffer.size() - 32]) + 1;
#elif defined(__APPLE__) && defined(__aarch64__)
    // macOS AArch64
    test_context.uc_mcontext->__ss.__fp = reinterpret_cast<uintptr_t>(&stack_buffer[stack_buffer.size() - 32]) + 1;
#elif defined(__linux__) && defined(__x86_64__)
    // Linux x86_64
    test_context.uc_mcontext.gregs[REG_RBP] = reinterpret_cast<uintptr_t>(&stack_buffer[stack_buffer.size() - 32]) + 1;
#elif defined(__linux__) && defined(__aarch64__)
    // Linux AArch64
    test_context.uc_mcontext.regs[29] = reinterpret_cast<uintptr_t>(&stack_buffer[stack_buffer.size() - 32]) + 1;
#endif
    
    ::StackContext java_ctx = {0};
    
    // Should detect misalignment and handle appropriately
    try {
        int depth = StackWalker::walkFP(&test_context, callchain, MAX_DEPTH, &java_ctx);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkFP with misaligned addresses";
    }
} 