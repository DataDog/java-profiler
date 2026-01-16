/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "symbols_linux_dd.h"
#include "vmEntry.h"
#include "../../main/cpp/gtest_crash_handler.h"

#ifdef __linux__

static constexpr char REMOTE_TEST_NAME[] = "RemoteSymbolicationTest";

class RemoteSymbolicationGlobalSetup {
public:
    RemoteSymbolicationGlobalSetup() {
        installGtestCrashHandler<REMOTE_TEST_NAME>();
    }
    ~RemoteSymbolicationGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

static RemoteSymbolicationGlobalSetup global_setup;

class RemoteSymbolicationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test setup
    }

    void TearDown() override {
        // Test cleanup
    }
};

TEST_F(RemoteSymbolicationTest, RemoteFrameInfoConstruction) {
    const char* test_build_id = "deadbeefcafebabe";
    uintptr_t test_offset = 0x1234;
    short test_lib_index = 5;

    RemoteFrameInfo rfi(test_build_id, test_offset, test_lib_index);

    EXPECT_STREQ(rfi.build_id, test_build_id);
    EXPECT_EQ(rfi.pc_offset, test_offset);
    EXPECT_EQ(rfi.lib_index, test_lib_index);
}

TEST_F(RemoteSymbolicationTest, BciFrameTypeConstants) {
    // Verify that the new BCI constant is defined
    EXPECT_EQ(BCI_NATIVE_FRAME_REMOTE, -19);

    // Verify it doesn't conflict with existing constants
    EXPECT_NE(BCI_NATIVE_FRAME_REMOTE, BCI_NATIVE_FRAME);
    EXPECT_NE(BCI_NATIVE_FRAME_REMOTE, BCI_ERROR);
    EXPECT_NE(BCI_NATIVE_FRAME_REMOTE, BCI_ALLOC);
}

// Test build-id extraction from a minimal ELF
TEST_F(RemoteSymbolicationTest, BuildIdExtractionBasic) {
    // Create a minimal ELF file with a build-id note section
    // This test would be more comprehensive with a real ELF file
    // For now, just test the function doesn't crash on invalid input

    size_t build_id_len = 0;
    char* build_id = ddprof::SymbolsLinux::extractBuildId("/nonexistent", &build_id_len);

    // Should return null for non-existent file
    EXPECT_EQ(build_id, nullptr);
    EXPECT_EQ(build_id_len, 0);
}

TEST_F(RemoteSymbolicationTest, BuildIdExtractionInvalidInput) {
    size_t build_id_len = 0;

    // Test null inputs
    char* build_id1 = ddprof::SymbolsLinux::extractBuildId(nullptr, &build_id_len);
    EXPECT_EQ(build_id1, nullptr);

    char* build_id2 = ddprof::SymbolsLinux::extractBuildId("/some/file", nullptr);
    EXPECT_EQ(build_id2, nullptr);

    // Test non-ELF file
    const char* test_content = "This is not an ELF file";
    char temp_file[] = "/tmp/not_an_elf_XXXXXX";

    int fd = mkstemp(temp_file);
    if (fd >= 0) {
        write(fd, test_content, strlen(test_content));
        close(fd);

        char* build_id3 = ddprof::SymbolsLinux::extractBuildId(temp_file, &build_id_len);
        EXPECT_EQ(build_id3, nullptr);

        unlink(temp_file);
    }
}

TEST_F(RemoteSymbolicationTest, BuildIdFromMemoryInvalidInput) {
    size_t build_id_len = 0;

    // Test null pointer
    char* build_id1 = ddprof::SymbolsLinux::extractBuildIdFromMemory(nullptr, 100, &build_id_len);
    EXPECT_EQ(build_id1, nullptr);

    // Test invalid size
    char dummy_data[10] = {0};
    char* build_id2 = ddprof::SymbolsLinux::extractBuildIdFromMemory(dummy_data, 0, &build_id_len);
    EXPECT_EQ(build_id2, nullptr);

    // Test null output parameter
    char* build_id3 = ddprof::SymbolsLinux::extractBuildIdFromMemory(dummy_data, 10, nullptr);
    EXPECT_EQ(build_id3, nullptr);
}

#endif // __linux__