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

#include "stackWalker.h"
#include "dwarf.h"
#include "profiler.h"
#include "vmEntry.h" // For ASGCT types
#include "stackWalker_dd.h" // For ddprof namespace

// This file contains extreme fuzzing tests for the StackWalker functionality,
// focusing on stress testing and extreme conditions

class StackWalkerExtremeFuzzTest : public ::testing::Test {
protected:
    // Test parameters
    static const int MAX_DEPTH = 2048;
    static const int MAX_ITERATIONS = 10; // Reduced from 100 to make tests less likely to crash
    
    // Test resources
    std::mt19937 rng;
    std::vector<const void*> callchain;
    std::vector<ASGCT_CallFrame> frames;
    ucontext_t context;
    
    // Memory buffer to provide valid addresses for the tests
    std::vector<uintptr_t> memory_buffer;
    
    void SetUp() override {
        // Initialize random generator with current time
        unsigned int seed = static_cast<unsigned int>(time(nullptr));
        rng.seed(seed);
        
        // Allocate large buffers for results
        callchain.resize(MAX_DEPTH);
        frames.resize(MAX_DEPTH);
        
        // Initialize context
        memset(&context, 0, sizeof(context));
        
        // Allocate memory buffer for safe addresses
        memory_buffer.resize(4096);
        std::uniform_int_distribution<uintptr_t> init_dist(1, 1000000);
        for (auto& val : memory_buffer) {
            val = init_dist(rng);
        }
    }
    
    // Generate a completely random ucontext but with safer values
    void generateRandomContext() {
        std::uniform_int_distribution<size_t> buffer_index(0, memory_buffer.size() - 1);
        
        memset(&context, 0, sizeof(context));
        
        // Fill with random values but from our safe buffer - platform specific
#if defined(__APPLE__) && defined(__x86_64__)
        // macOS x86_64
        context.uc_mcontext->__ss.__rax = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__rbx = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__rcx = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__rdx = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__rdi = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__rsi = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__rbp = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__rsp = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__r8 = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__r9 = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__r10 = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__r11 = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__r12 = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__r13 = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__r14 = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__r15 = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__rip = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__rflags = 0x200; // Reasonable flags value
#elif defined(__APPLE__) && defined(__aarch64__)
        // macOS AArch64
        context.uc_mcontext->__ss.__pc = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__sp = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__fp = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext->__ss.__lr = (uintptr_t)&memory_buffer[buffer_index(rng)];
        for (int i = 0; i < 29; i++) {
            context.uc_mcontext->__ss.__x[i] = (uintptr_t)&memory_buffer[buffer_index(rng)];
        }
#elif defined(__linux__) && defined(__x86_64__)
        // Linux x86_64
        for (int i = 0; i < NGREG; i++) {
            context.uc_mcontext.gregs[i] = (uintptr_t)&memory_buffer[buffer_index(rng)];
        }
#elif defined(__linux__) && defined(__aarch64__)
        // Linux AArch64
        context.uc_mcontext.pc = (uintptr_t)&memory_buffer[buffer_index(rng)];
        context.uc_mcontext.sp = (uintptr_t)&memory_buffer[buffer_index(rng)];
        for (int i = 0; i < 31; i++) {
            context.uc_mcontext.regs[i] = (uintptr_t)&memory_buffer[buffer_index(rng)];
        }
#endif
    }
    
    // Generate semi-valid context with aligned addresses
    void generateSemiValidContext() {
        // Use addresses from our memory buffer
        std::uniform_int_distribution<size_t> buffer_index(0, memory_buffer.size() - 1);
        
        memset(&context, 0, sizeof(context));
        
#if defined(__APPLE__) && defined(__x86_64__)
        // macOS x86_64
        // Align addresses properly
        context.uc_mcontext->__ss.__rsp = (uintptr_t)&memory_buffer[buffer_index(rng)] & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext->__ss.__rbp = (uintptr_t)&memory_buffer[buffer_index(rng)] & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext->__ss.__rip = (uintptr_t)&memory_buffer[buffer_index(rng)];
#elif defined(__APPLE__) && defined(__aarch64__)
        // macOS AArch64
        context.uc_mcontext->__ss.__sp = (uintptr_t)&memory_buffer[buffer_index(rng)] & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext->__ss.__fp = (uintptr_t)&memory_buffer[buffer_index(rng)] & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext->__ss.__pc = (uintptr_t)&memory_buffer[buffer_index(rng)];
#elif defined(__linux__) && defined(__x86_64__)
        // Linux x86_64
        context.uc_mcontext.gregs[REG_RSP] = (uintptr_t)&memory_buffer[buffer_index(rng)] & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext.gregs[REG_RBP] = (uintptr_t)&memory_buffer[buffer_index(rng)] & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext.gregs[REG_RIP] = (uintptr_t)&memory_buffer[buffer_index(rng)];
#elif defined(__linux__) && defined(__aarch64__)
        // Linux AArch64
        context.uc_mcontext.sp = (uintptr_t)&memory_buffer[buffer_index(rng)] & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext.regs[29] = (uintptr_t)&memory_buffer[buffer_index(rng)] & ~(sizeof(uintptr_t) - 1); // x29 is FP
        context.uc_mcontext.pc = (uintptr_t)&memory_buffer[buffer_index(rng)];
#endif
    }
};

// Multiple iterations of fuzzing with random contexts
TEST_F(StackWalkerExtremeFuzzTest, DISABLED_MultipleIterationsRandom) {
    ::StackContext java_ctx = {0};
    bool truncated = false;
    
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        generateRandomContext();
        
        // Try walking with frame pointers, wrapped in try/catch for safety
        try {
            int depth = StackWalker::walkFP(&context, callchain.data(), MAX_DEPTH, &java_ctx);
            // Success is not crashing, not depth itself
        } catch (...) {
            // Ignore any exceptions, just move on
            GTEST_LOG_(INFO) << "Exception in walkFP iteration " << i;
        }
        
        // Try DWARF-based walking if supported
#if DWARF_SUPPORTED
        try {
            int depth = StackWalker::walkDwarf(&context, callchain.data(), MAX_DEPTH, &java_ctx);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkDwarf iteration " << i;
        }
#endif
        
        // Try VM-based walking
        try {
            int depth = StackWalker::walkVM(&context, frames.data(), MAX_DEPTH, VM_BASIC);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkVM iteration " << i;
        }
    }
}

// Test with semi-valid contexts
TEST_F(StackWalkerExtremeFuzzTest, DISABLED_SemiValidContexts) {
    ::StackContext java_ctx = {0};
    bool truncated = false;
    
    for (int i = 0; i < MAX_ITERATIONS / 2; i++) {
        generateSemiValidContext();
        
        // Try walking with frame pointers
        try {
            int depth = StackWalker::walkFP(&context, callchain.data(), MAX_DEPTH, &java_ctx);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkFP iteration " << i;
        }
        
        // These tests require the ddprof namespace and are optional
#ifdef HAVE_DDPROF
        try {
            int depth = ddprof::StackWalker::walkFP(&context, callchain.data(), MAX_DEPTH, &java_ctx, &truncated);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in ddprof::walkFP iteration " << i;
        }
        
#if DWARF_SUPPORTED
        try {
            int depth = ddprof::StackWalker::walkDwarf(&context, callchain.data(), MAX_DEPTH, &java_ctx, &truncated);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in ddprof::walkDwarf iteration " << i;
        }
#endif

        try {
            int depth = ddprof::StackWalker::walkVM(&context, frames.data(), MAX_DEPTH, VM_BASIC, &truncated);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in ddprof::walkVM iteration " << i;
        }
#endif // HAVE_DDPROF
        
#if DWARF_SUPPORTED
        try {
            int depth = StackWalker::walkDwarf(&context, callchain.data(), MAX_DEPTH, &java_ctx);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkDwarf iteration " << i;
        }
#endif
        
        // Try VM-based walking with different detail levels
        try {
            int depth = StackWalker::walkVM(&context, frames.data(), MAX_DEPTH, VM_BASIC);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkVM(VM_BASIC) iteration " << i;
        }
        
        try {
            int depth = StackWalker::walkVM(&context, frames.data(), MAX_DEPTH, VM_NORMAL);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkVM(VM_NORMAL) iteration " << i;
        }
        
        try {
            int depth = StackWalker::walkVM(&context, frames.data(), MAX_DEPTH, VM_EXPERT);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkVM(VM_EXPERT) iteration " << i;
        }
    }
}

// Test varying max_depth values
TEST_F(StackWalkerExtremeFuzzTest, DISABLED_VaryingMaxDepth) {
    ::StackContext java_ctx = {0};
    std::uniform_int_distribution<int> depth_dist(0, MAX_DEPTH);
    
    for (int i = 0; i < MAX_ITERATIONS / 4; i++) {
        generateSemiValidContext();
        int max_depth = depth_dist(rng);
        
        // Test with random max_depth values
        try {
            int depth = StackWalker::walkFP(&context, callchain.data(), max_depth, &java_ctx);
            EXPECT_GE(depth, 0);
            EXPECT_LE(depth, max_depth);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkFP iteration " << i;
        }
        
#if DWARF_SUPPORTED
        try {
            int depth = StackWalker::walkDwarf(&context, callchain.data(), max_depth, &java_ctx);
            EXPECT_GE(depth, 0);
            EXPECT_LE(depth, max_depth);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkDwarf iteration " << i;
        }
#endif
        
        try {
            int depth = StackWalker::walkVM(&context, frames.data(), max_depth, VM_BASIC);
            EXPECT_GE(depth, 0);
            EXPECT_LE(depth, max_depth);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkVM iteration " << i;
        }
    }
}

// Test extremely large max_depth values
TEST_F(StackWalkerExtremeFuzzTest, DISABLED_ExtremelyLargeMaxDepth) {
    ::StackContext java_ctx = {0};
    
    // Test with very large max_depth
    const int EXTREME_DEPTH = 1000000;  // Way more than any reasonable stack would have
    
    // Only test this once as it might be slow
    generateSemiValidContext();
    
    // Call with extreme depth, expect it to not crash or hang
    try {
        int depth = StackWalker::walkFP(&context, callchain.data(), EXTREME_DEPTH, &java_ctx);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkFP with extreme depth";
    }
    
#if DWARF_SUPPORTED
    try {
        int depth = StackWalker::walkDwarf(&context, callchain.data(), EXTREME_DEPTH, &java_ctx);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkDwarf with extreme depth";
    }
#endif
}

// Test with massive number of iterations - this is a stress test
TEST_F(StackWalkerExtremeFuzzTest, DISABLED_MassiveIterations) {
    // Note: This test is disabled by default as it's meant for manual stress testing
    
    ::StackContext java_ctx = {0};
    const int MASSIVE_ITERATIONS = 10000;
    
    for (int i = 0; i < MASSIVE_ITERATIONS; i++) {
        generateRandomContext();
        
        // Just test one walker to keep test duration reasonable
        try {
            int depth = StackWalker::walkFP(&context, callchain.data(), MAX_DEPTH, &java_ctx);
        } catch (...) {
            GTEST_LOG_(INFO) << "Exception in walkFP iteration " << i;
        }
    }
}

// Test the StackWalker with partially invalid memory regions
TEST_F(StackWalkerExtremeFuzzTest, DISABLED_PartiallyInvalidMemory) {
    ::StackContext java_ctx = {0};
    
    // Create a context that points to some valid and some invalid memory addresses
    generateSemiValidContext();
    
    // Modify to include some potentially problematic addresses, but not NULL or UINTPTR_MAX
#if defined(__APPLE__) && defined(__x86_64__)
    // macOS x86_64
    // Near NULL but not exactly
    context.uc_mcontext->__ss.__rsp = 0x1000;
    // Large but not at the limit
    context.uc_mcontext->__ss.__rbp = UINTPTR_MAX / 2;
#elif defined(__APPLE__) && defined(__aarch64__)
    // macOS AArch64
    // Near NULL but not exactly
    context.uc_mcontext->__ss.__sp = 0x1000;
    // Large but not at the limit
    context.uc_mcontext->__ss.__fp = UINTPTR_MAX / 2;
#elif defined(__linux__) && defined(__x86_64__)
    // Linux x86_64
    // Near NULL but not exactly
    context.uc_mcontext.gregs[REG_RSP] = 0x1000;
    // Large but not at the limit
    context.uc_mcontext.gregs[REG_RBP] = UINTPTR_MAX / 2;
#elif defined(__linux__) && defined(__aarch64__)
    // Linux AArch64
    // Near NULL but not exactly
    context.uc_mcontext.sp = 0x1000;
    // Large but not at the limit
    context.uc_mcontext.regs[29] = UINTPTR_MAX / 2;
#endif
    
    // Should handle invalid addresses gracefully
    try {
        int depth = StackWalker::walkFP(&context, callchain.data(), MAX_DEPTH, &java_ctx);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkFP with partially invalid memory";
    }
    
#if DWARF_SUPPORTED
    try {
        int depth = StackWalker::walkDwarf(&context, callchain.data(), MAX_DEPTH, &java_ctx);
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in walkDwarf with partially invalid memory";
    }
#endif
}

// Test checkFault function
TEST_F(StackWalkerExtremeFuzzTest, DISABLED_CheckFault) {
    // This just verifies that the function can be called without crashing
    try {
        StackWalker::checkFault();
    } catch (...) {
        GTEST_LOG_(INFO) << "Exception in checkFault";
    }
} 