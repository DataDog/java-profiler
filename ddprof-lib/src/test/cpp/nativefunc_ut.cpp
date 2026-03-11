/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include <vector>
#include "../../main/cpp/codeCache.h"
#include "../../main/cpp/utils.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char NATIVEFUNC_TEST_NAME[] = "NativeFuncTest";

class NativeFuncTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<NATIVEFUNC_TEST_NAME>();
    }

    void TearDown() override {
        // Clean up any allocated NativeFunc instances
        for (char* name : created_names) {
            NativeFunc::destroy(name);
        }
        created_names.clear();
        restoreDefaultSignalHandlers();
    }

    std::vector<char*> created_names;

    char* createAndTrack(const char* name, short lib_index) {
        char* result = NativeFunc::create(name, lib_index);
        created_names.push_back(result);
        return result;
    }
};

TEST_F(NativeFuncTest, CreateReturnsNonNull) {
    char* name = createAndTrack("test_function", 42);
    ASSERT_NE(name, nullptr) << "NativeFunc::create() should not return nullptr";
}

TEST_F(NativeFuncTest, CreateReturnsAlignedPointer) {
    char* name = createAndTrack("test_function", 42);
    ASSERT_NE(name, nullptr);

    // The NativeFunc struct pointer (backing up from name)
    // should be aligned to sizeof(NativeFunc*)
    NativeFunc* func_ptr = (NativeFunc*)(name - sizeof(NativeFunc));
    EXPECT_TRUE(is_aligned(func_ptr, sizeof(NativeFunc*)))
        << "NativeFunc structure must be aligned to sizeof(NativeFunc*) = " << sizeof(NativeFunc*)
        << " for alignment checks to work correctly";
}

TEST_F(NativeFuncTest, CreatePreservesName) {
    const char* input_name = "my_test_function";
    char* name = createAndTrack(input_name, 1);
    ASSERT_NE(name, nullptr);

    EXPECT_STREQ(name, input_name)
        << "NativeFunc::create() should preserve the function name";
}

TEST_F(NativeFuncTest, LibIndexAccessible) {
    char* name = createAndTrack("my_function", 123);
    ASSERT_NE(name, nullptr);

    short lib_index = NativeFunc::libIndex(name);
    EXPECT_EQ(lib_index, 123)
        << "NativeFunc::libIndex() should return the lib_index set during create()";
}

TEST_F(NativeFuncTest, InitialMarkIsZero) {
    char* name = createAndTrack("unmarked_function", 1);
    ASSERT_NE(name, nullptr);

    EXPECT_FALSE(NativeFunc::is_marked(name))
        << "Newly created NativeFunc should not be marked (is_marked returns false)";
    EXPECT_EQ(NativeFunc::read_mark(name), 0)
        << "Newly created NativeFunc should have mark value of 0";
}

TEST_F(NativeFuncTest, SetAndReadMark) {
    char* name = createAndTrack("marked_function", 1);
    ASSERT_NE(name, nullptr);

    // Set mark to MARK_THREAD_ENTRY (5)
    NativeFunc::set_mark(name, 5);

    // Verify mark was set
    EXPECT_TRUE(NativeFunc::is_marked(name))
        << "After set_mark(5), is_marked() should return true";
    EXPECT_EQ(NativeFunc::read_mark(name), 5)
        << "After set_mark(5), read_mark() should return 5";
}

TEST_F(NativeFuncTest, SetMultipleDifferentMarks) {
    char* name1 = createAndTrack("func1", 1);
    char* name2 = createAndTrack("func2", 2);
    char* name3 = createAndTrack("func3", 3);

    NativeFunc::set_mark(name1, MARK_VM_RUNTIME);
    NativeFunc::set_mark(name2, MARK_INTERPRETER);
    NativeFunc::set_mark(name3, MARK_THREAD_ENTRY);

    EXPECT_EQ(NativeFunc::read_mark(name1), MARK_VM_RUNTIME);
    EXPECT_EQ(NativeFunc::read_mark(name2), MARK_INTERPRETER);
    EXPECT_EQ(NativeFunc::read_mark(name3), MARK_THREAD_ENTRY);
}

TEST_F(NativeFuncTest, OverwriteMark) {
    char* name = createAndTrack("func", 1);
    ASSERT_NE(name, nullptr);

    // Set initial mark
    NativeFunc::set_mark(name, MARK_INTERPRETER);
    EXPECT_EQ(NativeFunc::read_mark(name), MARK_INTERPRETER);

    // Overwrite with different mark
    NativeFunc::set_mark(name, MARK_THREAD_ENTRY);
    EXPECT_EQ(NativeFunc::read_mark(name), MARK_THREAD_ENTRY)
        << "Marks should be overwritable";
}

TEST_F(NativeFuncTest, MarkOnNonNativeFuncPointerReturnsSafe) {
    // Test that reading marks from random strings returns safe defaults
    // without crashing (due to alignment check protection)
    const char* random_string = "not_a_nativefunc";

    // Should return safe defaults without crashing
    EXPECT_FALSE(NativeFunc::is_marked(random_string))
        << "is_marked() on non-NativeFunc string should return false (safe default)";
    EXPECT_EQ(NativeFunc::read_mark(random_string), 0)
        << "read_mark() on non-NativeFunc string should return 0 (safe default)";
    EXPECT_EQ(NativeFunc::libIndex(random_string), -1)
        << "libIndex() on non-NativeFunc string should return -1 (safe default)";
}

TEST_F(NativeFuncTest, NullPointerReturnsSafe) {
    // Test that NULL pointer is handled safely
    // The from() method computes (NativeFunc*)(nullptr - sizeof(NativeFunc))
    // which is a large negative address that should fail alignment check

    EXPECT_FALSE(NativeFunc::is_marked(nullptr))
        << "is_marked(nullptr) should return false (safe default)";
    EXPECT_EQ(NativeFunc::read_mark(nullptr), 0)
        << "read_mark(nullptr) should return 0 (safe default)";
    EXPECT_EQ(NativeFunc::libIndex(nullptr), -1)
        << "libIndex(nullptr) should return -1 (safe default)";

    // set_mark should be a no-op on nullptr (doesn't crash)
    NativeFunc::set_mark(nullptr, MARK_THREAD_ENTRY);
    // If we got here without crashing, the test passes
}

TEST_F(NativeFuncTest, MarkingDisabledDetection) {
    // *** CRITICAL TEST ***
    // This test would have caught the is_aligned() bug where marking was silently disabled.
    // If is_aligned() is broken, marks won't be readable even though they're set.

    char* name = createAndTrack("critical_test", 99);
    ASSERT_NE(name, nullptr);

    // Set a mark
    NativeFunc::set_mark(name, MARK_THREAD_ENTRY);

    // Read it back - if alignment check is broken, this returns 0
    char mark = NativeFunc::read_mark(name);

    ASSERT_EQ(mark, MARK_THREAD_ENTRY)
        << "CRITICAL FAILURE: Marking appears to be disabled!\n"
        << "Set mark to " << (int)MARK_THREAD_ENTRY << " but read back " << (int)mark << "\n"
        << "\n"
        << "This likely means:\n"
        << "  1. is_aligned() has a bug (inverted logic? wrong mask?)\n"
        << "  2. NativeFunc::read_mark() alignment check is failing\n"
        << "  3. NativeFunc::set_mark() alignment check is failing\n"
        << "\n"
        << "Impact: ALL stack unwinding optimizations are broken:\n"
        << "  - THREAD_ENTRY detection won't work\n"
        << "  - COMPILER_ENTRY injection won't work\n"
        << "  - VM_RUNTIME filtering won't work\n"
        << "\n"
        << "This is a critical performance regression.";
}

TEST_F(NativeFuncTest, AllMarkTypesWork) {
    // Verify all mark enum values can be set and read
    const char mark_values[] = {
        MARK_VM_RUNTIME,
        MARK_INTERPRETER,
        MARK_COMPILER_ENTRY,
        MARK_ASYNC_PROFILER,
        MARK_THREAD_ENTRY
    };

    for (size_t i = 0; i < sizeof(mark_values); i++) {
        char mark_value = mark_values[i];
        char* name = createAndTrack("test", i);
        ASSERT_NE(name, nullptr);

        NativeFunc::set_mark(name, mark_value);
        EXPECT_EQ(NativeFunc::read_mark(name), mark_value)
            << "Mark value " << (int)mark_value << " should be readable after setting";
    }
}

TEST_F(NativeFuncTest, MultipleAllocationsIndependent) {
    // Create multiple NativeFunc instances and verify they're independent
    char* name1 = createAndTrack("func1", 10);
    char* name2 = createAndTrack("func2", 20);
    char* name3 = createAndTrack("func3", 30);

    ASSERT_NE(name1, nullptr);
    ASSERT_NE(name2, nullptr);
    ASSERT_NE(name3, nullptr);

    // Set different marks
    NativeFunc::set_mark(name1, 1);
    NativeFunc::set_mark(name2, 2);
    NativeFunc::set_mark(name3, 3);

    // Verify independence
    EXPECT_EQ(NativeFunc::read_mark(name1), 1);
    EXPECT_EQ(NativeFunc::read_mark(name2), 2);
    EXPECT_EQ(NativeFunc::read_mark(name3), 3);

    EXPECT_EQ(NativeFunc::libIndex(name1), 10);
    EXPECT_EQ(NativeFunc::libIndex(name2), 20);
    EXPECT_EQ(NativeFunc::libIndex(name3), 30);
}
