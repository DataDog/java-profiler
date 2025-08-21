/*
 * Copyright 2025 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>
#include "branch_hints.h"

class BranchHintsTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(BranchHintsTest, BasicFunctionality) {
    // Test that macros work and don't crash
    int x = 42;
    
    if (likely(x == 42)) {
        EXPECT_EQ(x, 42);
    }
    
    if (unlikely(x == 0)) {
        FAIL() << "This should not be reached";
    }
    
    // Test that the macros return the expected boolean values
    EXPECT_TRUE(likely(true));
    EXPECT_FALSE(likely(false));
    EXPECT_TRUE(unlikely(true));
    EXPECT_FALSE(unlikely(false));
}

TEST_F(BranchHintsTest, ImplementationInfo) {
    // Report what implementation is being used
    #if defined(__GNUC__) || defined(__clang__)
        fprintf(stderr, "Using __builtin_expect for branch hints\n");
    #else
        fprintf(stderr, "Using no-op branch hints (fallback)\n");
    #endif
    
    // This test always passes - it's just for diagnostics
    EXPECT_TRUE(true);
}

TEST_F(BranchHintsTest, MacroExpansion) {
    // Test that macros expand to valid expressions
    volatile bool condition = true;
    
    // These should compile and work correctly
    bool likely_result = likely(condition);
    bool unlikely_result = unlikely(condition);
    
    EXPECT_EQ(likely_result, condition);
    EXPECT_EQ(unlikely_result, condition);
    
    // Test with complex expressions
    int a = 10, b = 20;
    EXPECT_TRUE(likely(a < b));
    EXPECT_FALSE(unlikely(a > b));
} 