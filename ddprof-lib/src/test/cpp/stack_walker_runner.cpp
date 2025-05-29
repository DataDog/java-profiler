#include <gtest/gtest.h>
#include <iostream>

// Main runner for stack walker tests
// This ensures appropriate setup and reporting for the tests

int main(int argc, char **argv) {
    std::cout << "Running StackWalker fuzzing tests..." << std::endl;
    
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);
    
    // Run all tests
    int result = RUN_ALL_TESTS();
    
    // Report results
    std::cout << "StackWalker fuzzing tests completed with result: " << result << std::endl;
    
    return result;
} 