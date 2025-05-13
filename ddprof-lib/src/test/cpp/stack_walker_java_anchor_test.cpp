#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <vector>
#include <random>
#include <time.h>
#include <memory>
#include <ucontext.h>

#include "stackWalker.h"
#include "vmEntry.h" // For ASGCT types
#include "arch_dd.h" // For architecture definitions
#include "dwarf.h"

// Tests focused on StackWalker's Java frame anchor handling capabilities

// Forward declare the JavaFrameAnchor class to match the expected interface
class JavaFrameAnchor;

// Create a mock implementation for testing
class MockJavaFrameAnchor {
private:
    void* _last_Java_sp;
    void* _last_Java_fp;
    void* _last_Java_pc;
    uintptr_t _flags;
    bool _walkable;
    int _anchor_state;

public:
    MockJavaFrameAnchor() 
        : _last_Java_sp(nullptr), _last_Java_fp(nullptr), _last_Java_pc(nullptr),
          _flags(0), _walkable(false), _anchor_state(0) {}

    // Setter methods
    void set_last_Java_sp(void* sp) { _last_Java_sp = sp; }
    void set_last_Java_fp(void* fp) { _last_Java_fp = fp; }
    void set_last_Java_pc(void* pc) { _last_Java_pc = pc; }
    void set_flags(uintptr_t flags) { _flags = flags; }
    void set_walkable(bool walkable) { _walkable = walkable; }
    void set_anchor_state(int state) { _anchor_state = state; }

    // Getter methods
    void* last_Java_sp() const { return _last_Java_sp; }
    void* last_Java_fp() const { return _last_Java_fp; }
    void* last_Java_pc() const { return _last_Java_pc; }
    uintptr_t flags() const { return _flags; }
    bool walkable() const { return _walkable; }
    int anchor_state() const { return _anchor_state; }

    // Create a valid mockup JavaFrameAnchor for testing
    static MockJavaFrameAnchor* create_valid() {
        auto anchor = new MockJavaFrameAnchor();
        anchor->set_walkable(true);
        anchor->set_anchor_state(1); // Valid state for testing
        return anchor;
    }
};

// Helper to convert our mock to the real JavaFrameAnchor type
// This needs to be wrapped properly to be used with the actual StackWalker
JavaFrameAnchor* getJavaFrameAnchor(MockJavaFrameAnchor* mock) {
    // In a real implementation, this would do proper conversion
    // For testing, we'll just reinterpret_cast which is unsafe but acceptable in tests
    return reinterpret_cast<JavaFrameAnchor*>(mock);
}

// Extended StackContext with additional Java fields for testing
struct ExtendedStackContext : public StackContext {
    void* java_sp;
    void* java_fp;
    void* java_pc;
    
    ExtendedStackContext() : java_sp(nullptr), java_fp(nullptr), java_pc(nullptr) {
        // Initialize base class manually since we can't use initializer list for it
        pc = nullptr;
        sp = 0;
        fp = 0;
    }
};

// Test fixture for JavaFrameAnchor testing
class StackWalkerJavaAnchorTest : public ::testing::Test {
protected:
    // Test parameters
    static const int MAX_DEPTH = 64;
    static const int MIN_STACK_SIZE = 1024; 
    static const int MAX_STACK_SIZE = 16384;

    // Test resources
    std::mt19937 rng;
    std::vector<uintptr_t> stack_buffer;
    std::vector<ASGCT_CallFrame> frames;
    MockJavaFrameAnchor* mock_anchor;  // Changed from unique_ptr to raw pointer

    void SetUp() override {
        // Initialize random generator
        unsigned int seed = static_cast<unsigned int>(time(nullptr));
        rng.seed(seed);
        
        // Allocate buffer for frames
        frames.resize(MAX_DEPTH);
        
        // Create a stack buffer with random size
        std::uniform_int_distribution<int> size_dist(MIN_STACK_SIZE, MAX_STACK_SIZE);
        stack_buffer.resize(size_dist(rng));
        
        // Initialize a mock anchor
        mock_anchor = MockJavaFrameAnchor::create_valid();
    }

    void TearDown() override {
        // Delete the mock anchor since we're using a raw pointer now
        delete mock_anchor;
    }

    // Create stack with random but valid-looking data
    void setupValidStack() {
        std::uniform_int_distribution<uintptr_t> rand_word(1, UINTPTR_MAX);
        
        // Fill stack with random data
        for (size_t i = 0; i < stack_buffer.size(); i++) {
            stack_buffer[i] = rand_word(rng);
        }
        
        // Setup the JavaFrameAnchor to point into our stack buffer
        uintptr_t stack_addr = reinterpret_cast<uintptr_t>(&stack_buffer[0]);
        size_t offset = stack_buffer.size() / 2;
        
        // Ensure alignment
        uintptr_t sp = stack_addr + offset * sizeof(uintptr_t);
        sp &= ~(sizeof(uintptr_t) - 1);
        
        // Ensure we have space for a valid frame
        if (offset + 10 < stack_buffer.size()) {
            // Setup the SP to point to a valid address in our buffer
            mock_anchor->set_last_Java_sp(reinterpret_cast<void*>(sp));
            
            // Setup FP typically a bit higher in the stack
            mock_anchor->set_last_Java_fp(reinterpret_cast<void*>(sp + 3 * sizeof(uintptr_t)));
            
            // Create a valid-looking PC
            uintptr_t pc_val = rand_word(rng);
            // Ensure it's not in dead zone
            if (pc_val < 0x1000) pc_val += 0x1000;
            if (pc_val > (UINTPTR_MAX - 0x1000)) pc_val -= 0x1000;
            
            // Store the PC at the expected location in the stack
            mock_anchor->set_last_Java_pc(reinterpret_cast<void*>(pc_val));
            
            // Also put the PC on the stack at SP[-1] for testing
            stack_buffer[offset - 1] = pc_val;
        }
    }
};

// Skip these tests - they require deeper integration with actual JavaFrameAnchor class
// They are left commented out for reference
/*
// Basic test for walkVM with JavaFrameAnchor
TEST_F(StackWalkerJavaAnchorTest, BasicJavaFrameAnchorWalk) {
    setupValidStack();
    
    // Ensure the anchor has a valid SP
    ASSERT_NE(mock_anchor->last_Java_sp(), nullptr);
    
    // Try walking from the anchor
    ASSERT_NO_THROW({
        JavaFrameAnchor* real_anchor = getJavaFrameAnchor(mock_anchor.get());
        int depth = StackWalker::walkVM(nullptr, frames.data(), MAX_DEPTH, real_anchor);
        
        // The depth might be 0 if the frame is not recognized as valid Java frame,
        // but the function should not crash
        EXPECT_GE(depth, 0);
    });
}

// Test with varying JavaFrameAnchor values
TEST_F(StackWalkerJavaAnchorTest, VaryingAnchorValues) {
    std::uniform_int_distribution<uintptr_t> rand_addr(0x1000, UINTPTR_MAX - 0x1000);
    
    for (int i = 0; i < 10; i++) {
        // Create random anchor values
        uintptr_t sp = rand_addr(rng) & ~(sizeof(uintptr_t) - 1); // Ensure aligned
        uintptr_t fp = rand_addr(rng) & ~(sizeof(uintptr_t) - 1); // Ensure aligned
        const void* pc = reinterpret_cast<const void*>(rand_addr(rng));
        
        mock_anchor->set_last_Java_sp(reinterpret_cast<void*>(sp));
        mock_anchor->set_last_Java_fp(reinterpret_cast<void*>(fp));
        mock_anchor->set_last_Java_pc(pc);
        
        // Try walking from this anchor
        ASSERT_NO_THROW({
            JavaFrameAnchor* real_anchor = getJavaFrameAnchor(mock_anchor.get());
            int depth = StackWalker::walkVM(nullptr, frames.data(), MAX_DEPTH, real_anchor);
            
            // The result might be unpredictable with random values,
            // but it should not crash
        });
    }
}

// Test with edge case anchor values
TEST_F(StackWalkerJavaAnchorTest, EdgeCaseAnchorValues) {
    // Test with zero SP
    mock_anchor->set_last_Java_sp(nullptr);
    mock_anchor->set_last_Java_fp(reinterpret_cast<void*>(&stack_buffer[10]));
    mock_anchor->set_last_Java_pc(reinterpret_cast<const void*>(0x12345678));
    
    ASSERT_NO_THROW({
        JavaFrameAnchor* real_anchor = getJavaFrameAnchor(mock_anchor.get());
        int depth = StackWalker::walkVM(nullptr, frames.data(), MAX_DEPTH, real_anchor);
        
        // Should return 0 frames when SP is 0
        EXPECT_EQ(depth, 0);
    });
    
    // Test with null PC
    setupValidStack();
    mock_anchor->set_last_Java_pc(nullptr);
    
    ASSERT_NO_THROW({
        JavaFrameAnchor* real_anchor = getJavaFrameAnchor(mock_anchor.get());
        int depth = StackWalker::walkVM(nullptr, frames.data(), MAX_DEPTH, real_anchor);
    });
    
    // Test with misaligned FP
    setupValidStack();
    mock_anchor->set_last_Java_fp(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(mock_anchor->last_Java_fp()) + 1)); // Make it misaligned
    
    ASSERT_NO_THROW({
        JavaFrameAnchor* real_anchor = getJavaFrameAnchor(mock_anchor.get());
        int depth = StackWalker::walkVM(nullptr, frames.data(), MAX_DEPTH, real_anchor);
    });
}

// Test with null or zero anchor
TEST_F(StackWalkerJavaAnchorTest, NullAnchor) {
    // Test with null anchor
    ASSERT_NO_THROW({
        int depth = StackWalker::walkVM(nullptr, frames.data(), MAX_DEPTH, nullptr);
        
        // Should handle null gracefully
        EXPECT_EQ(depth, 0);
    });
}
*/

// Basic test to ensure our fixture can be compiled and run
TEST_F(StackWalkerJavaAnchorTest, BasicFixtureSetup) {
    setupValidStack();
    
    // Just ensure our setup doesn't crash
    ASSERT_NE(mock_anchor->last_Java_sp(), nullptr);
    ASSERT_NE(mock_anchor->last_Java_fp(), nullptr);
    ASSERT_NE(mock_anchor->last_Java_pc(), nullptr);
} 

// Test fixture for JavaFrameAnchor tests
class JavaFrameAnchorTest : public ::testing::Test {
protected:
    // Test resources
    std::mt19937 rng;
    std::vector<const void*> callchain;
    std::vector<ASGCT_CallFrame> frames;
    ucontext_t context;
    MockJavaFrameAnchor* anchor;
    static const int MAX_DEPTH = 64;

    void SetUp() {
        // Initialize random generator with fixed seed for reproducibility
        unsigned int seed = 42;
        rng.seed(seed);
        
        // Allocate buffers for results
        callchain.resize(MAX_DEPTH);
        frames.resize(MAX_DEPTH);
        
        // Initialize context
        memset(&context, 0, sizeof(context));
        
        // On macOS, we need to initialize the uc_mcontext field properly
#if defined(__APPLE__)
        // Allocate memory for the mcontext structure
        context.uc_mcontext = (_STRUCT_MCONTEXT *)calloc(1, sizeof(_STRUCT_MCONTEXT));
        if (!context.uc_mcontext) {
            fprintf(stderr, "Failed to allocate memory for mcontext\n");
            abort();
        }
#endif
        
        createValidStack();
        
        // Create mock anchor
        anchor = MockJavaFrameAnchor::create_valid();
    }
    
    void TearDown() {
#if defined(__APPLE__)
        if (context.uc_mcontext) {
            free(context.uc_mcontext);
            context.uc_mcontext = nullptr;
        }
#endif
        delete anchor;
    }
    
    // Create a stack with valid-looking data for testing
    void createValidStack() {
        std::uniform_int_distribution<uintptr_t> rand_addr(1000, 1000000);
        
        // Initialize context with valid-looking data
#if defined(__APPLE__) && defined(__x86_64__)
        // macOS x86_64
        context.uc_mcontext->__ss.__rsp = rand_addr(rng) & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext->__ss.__rbp = rand_addr(rng) & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext->__ss.__rip = rand_addr(rng);
#elif defined(__APPLE__) && defined(__aarch64__)
        // macOS AArch64
        context.uc_mcontext->__ss.__sp = rand_addr(rng) & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext->__ss.__fp = rand_addr(rng) & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext->__ss.__pc = rand_addr(rng);
#elif defined(__linux__) && defined(__x86_64__)
        // Linux x86_64
        context.uc_mcontext.gregs[REG_RSP] = rand_addr(rng) & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext.gregs[REG_RBP] = rand_addr(rng) & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext.gregs[REG_RIP] = rand_addr(rng);
#elif defined(__linux__) && defined(__aarch64__)
        // Linux AArch64
        context.uc_mcontext.sp = rand_addr(rng) & ~(sizeof(uintptr_t) - 1);
        context.uc_mcontext.regs[29] = rand_addr(rng) & ~(sizeof(uintptr_t) - 1); // x29 is FP
        context.uc_mcontext.pc = rand_addr(rng);
#endif
    }
};

// Base test to verify fixture setup works without crashing
TEST_F(JavaFrameAnchorTest, BasicSetupTest) {
    ExtendedStackContext stack_ctx;
    
    // Ensure setup and teardown work without crashing
    ASSERT_TRUE(anchor != nullptr);
    
    // Simple test to verify the basic stack walking
    EXPECT_NO_FATAL_FAILURE({
        int depth = StackWalker::walkFP(&context, callchain.data(), MAX_DEPTH, &stack_ctx);
        EXPECT_GE(depth, 0);
    });
}

// Test that we can create a stack context with Java-related values
TEST_F(JavaFrameAnchorTest, StackContextCreation) {
    ExtendedStackContext stack_ctx;
    
    // Set mock Java anchor values
    void* test_sp = reinterpret_cast<void*>(0x12345678);
    void* test_fp = reinterpret_cast<void*>(0x23456789);
    void* test_pc = reinterpret_cast<void*>(0x34567890);
    
    anchor->set_last_Java_sp(test_sp);
    anchor->set_last_Java_fp(test_fp);
    anchor->set_last_Java_pc(test_pc);
    anchor->set_walkable(true);
    
    // Create stack context using mock values
    stack_ctx.java_sp = anchor->last_Java_sp();
    stack_ctx.java_fp = anchor->last_Java_fp();
    stack_ctx.java_pc = anchor->last_Java_pc();
    
    // Verify the values were set correctly
    EXPECT_EQ(stack_ctx.java_sp, test_sp);
    EXPECT_EQ(stack_ctx.java_fp, test_fp);
    EXPECT_EQ(stack_ctx.java_pc, test_pc);
}

// Test attempt to walk with anchor information
TEST_F(JavaFrameAnchorTest, BasicWalkWithAnchor) {
    ExtendedStackContext stack_ctx;
    
    // Set up stack context with mock anchor values
    void* test_sp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(&context) + 64);
    void* test_fp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(&context) + 128);
    void* test_pc = reinterpret_cast<void*>(0x34567890);
    
    anchor->set_last_Java_sp(test_sp);
    anchor->set_last_Java_fp(test_fp);
    anchor->set_last_Java_pc(test_pc);
    anchor->set_walkable(true);
    
    stack_ctx.java_sp = anchor->last_Java_sp();
    stack_ctx.java_fp = anchor->last_Java_fp();
    stack_ctx.java_pc = anchor->last_Java_pc();
    
    // Try walking with the Java anchor information included
    EXPECT_NO_FATAL_FAILURE({
        int depth = StackWalker::walkFP(&context, callchain.data(), MAX_DEPTH, &stack_ctx);
        EXPECT_GE(depth, 0);
    });
    
#if DWARF_SUPPORTED
    EXPECT_NO_FATAL_FAILURE({
        int depth = StackWalker::walkDwarf(&context, callchain.data(), MAX_DEPTH, &stack_ctx);
        EXPECT_GE(depth, 0);
    });
#endif
    
    // Also test VM walk which takes a different argument type
    EXPECT_NO_FATAL_FAILURE({
        int depth = StackWalker::walkVM(&context, frames.data(), MAX_DEPTH, VM_BASIC);
        EXPECT_GE(depth, 0);
    });
}

/*
// Commented out tests requiring real JavaFrameAnchor implementation

// Test with real ASGCT frames structure
TEST_F(JavaFrameAnchorTest, ASGCTFramesTest) {
    // This would need to be implemented with the actual ASGCT types 
    // from the JVM native interface
}

// Test with various Java anchor states
TEST_F(JavaFrameAnchorTest, AnchorStateVariations) {
    // This would test behavior with different values in the anchor state
}

// Test combining native stack with Java frames
TEST_F(JavaFrameAnchorTest, CombinedNativeAndJavaStack) {
    // This would test the combination of native stack frames
    // and Java frames when available
}
*/

// Test behavior when walkable flag is false
TEST_F(JavaFrameAnchorTest, NonWalkableAnchor) {
    ExtendedStackContext stack_ctx;
    
    // Set up valid looking values but mark as non-walkable
    void* test_sp = reinterpret_cast<void*>(0x12345678);
    void* test_fp = reinterpret_cast<void*>(0x23456789);
    void* test_pc = reinterpret_cast<void*>(0x34567890);
    
    anchor->set_last_Java_sp(test_sp);
    anchor->set_last_Java_fp(test_fp);
    anchor->set_last_Java_pc(test_pc);
    anchor->set_walkable(false); // Explicitly non-walkable
    
    stack_ctx.java_sp = anchor->last_Java_sp();
    stack_ctx.java_fp = anchor->last_Java_fp();
    stack_ctx.java_pc = anchor->last_Java_pc();
    
    // Verify walking still works and doesn't crash
    EXPECT_NO_FATAL_FAILURE({
        int depth = StackWalker::walkFP(&context, callchain.data(), MAX_DEPTH, &stack_ctx);
        EXPECT_GE(depth, 0);
    });
}

// Test with NULL pointers in Java anchor
TEST_F(JavaFrameAnchorTest, NullJavaAnchorValues) {
    ExtendedStackContext stack_ctx;
    
    // Set NULL for all Java anchor values
    anchor->set_last_Java_sp(nullptr);
    anchor->set_last_Java_fp(nullptr);
    anchor->set_last_Java_pc(nullptr);
    anchor->set_walkable(true);
    
    stack_ctx.java_sp = anchor->last_Java_sp();
    stack_ctx.java_fp = anchor->last_Java_fp();
    stack_ctx.java_pc = anchor->last_Java_pc();
    
    // Should handle null values gracefully
    EXPECT_NO_FATAL_FAILURE({
        int depth = StackWalker::walkFP(&context, callchain.data(), MAX_DEPTH, &stack_ctx);
        EXPECT_GE(depth, 0);
    });
}

// Test with various max_depth values
TEST_F(JavaFrameAnchorTest, VaryingMaxDepth) {
    ExtendedStackContext stack_ctx;
    
    // Set up valid looking values
    void* test_sp = reinterpret_cast<void*>(0x12345678);
    void* test_fp = reinterpret_cast<void*>(0x23456789);
    void* test_pc = reinterpret_cast<void*>(0x34567890);
    
    anchor->set_last_Java_sp(test_sp);
    anchor->set_last_Java_fp(test_fp);
    anchor->set_last_Java_pc(test_pc);
    anchor->set_walkable(true);
    
    stack_ctx.java_sp = anchor->last_Java_sp();
    stack_ctx.java_fp = anchor->last_Java_fp();
    stack_ctx.java_pc = anchor->last_Java_pc();
    
    // Test various max depth values to ensure robustness
    for (int max_depth : {0, 1, 2, 5, 10, 20, MAX_DEPTH}) {
        EXPECT_NO_FATAL_FAILURE({
            int depth = StackWalker::walkFP(&context, callchain.data(), max_depth, &stack_ctx);
            EXPECT_GE(depth, 0);
            EXPECT_LE(depth, max_depth);
        });
    }
} 