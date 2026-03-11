/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "symbols_linux.h"
#include "profiler.h"
#include "vmEntry.h"
#include "../../main/cpp/gtest_crash_handler.h"

// RemoteFramePacker tests are platform-independent (pure bit manipulation)
using RFP = Profiler::RemoteFramePacker;

TEST(RemoteFramePackerTest, RoundTrip) {
    uintptr_t pc_offset = 0x123456789AB;
    char mark = 5;
    uint32_t lib_index = 1000;

    unsigned long packed = RFP::pack(pc_offset, mark, lib_index);
    EXPECT_EQ(RFP::unpackPcOffset(packed), pc_offset);
    EXPECT_EQ(RFP::unpackMark(packed), mark);
    EXPECT_EQ(RFP::unpackLibIndex(packed), lib_index);
}

TEST(RemoteFramePackerTest, ZeroValues) {
    unsigned long packed = RFP::pack(0, 0, 0);
    EXPECT_EQ(packed, 0UL);
    EXPECT_EQ(RFP::unpackPcOffset(packed), 0UL);
    EXPECT_EQ(RFP::unpackMark(packed), 0);
    EXPECT_EQ(RFP::unpackLibIndex(packed), 0U);
}

TEST(RemoteFramePackerTest, MaxValues) {
    uintptr_t max_pc = RFP::PC_OFFSET_MASK;     // 44 bits all set
    char max_mark = (char)RFP::MARK_MASK;        // 3 bits all set = 7
    uint32_t max_lib = (uint32_t)RFP::LIB_INDEX_MASK; // 15 bits all set = 32767

    unsigned long packed = RFP::pack(max_pc, max_mark, max_lib);
    EXPECT_EQ(RFP::unpackPcOffset(packed), max_pc);
    EXPECT_EQ(RFP::unpackMark(packed), max_mark);
    EXPECT_EQ(RFP::unpackLibIndex(packed), max_lib);
}

TEST(RemoteFramePackerTest, FieldIsolation) {
    // Setting only pc_offset should not affect mark or lib_index
    unsigned long packed_pc = RFP::pack(0xABCDE, 0, 0);
    EXPECT_EQ(RFP::unpackMark(packed_pc), 0);
    EXPECT_EQ(RFP::unpackLibIndex(packed_pc), 0U);

    // Setting only mark should not affect pc_offset or lib_index
    unsigned long packed_mark = RFP::pack(0, 3, 0);
    EXPECT_EQ(RFP::unpackPcOffset(packed_mark), 0UL);
    EXPECT_EQ(RFP::unpackLibIndex(packed_mark), 0U);

    // Setting only lib_index should not affect pc_offset or mark
    unsigned long packed_lib = RFP::pack(0, 0, 500);
    EXPECT_EQ(RFP::unpackPcOffset(packed_lib), 0UL);
    EXPECT_EQ(RFP::unpackMark(packed_lib), 0);
}

TEST(RemoteFramePackerTest, Overflow_PcOffsetTruncated) {
    // pc_offset larger than 44 bits should be silently truncated
    uintptr_t oversize_pc = (1ULL << 44) | 0x42;
    unsigned long packed = RFP::pack(oversize_pc, 0, 0);
    EXPECT_EQ(RFP::unpackPcOffset(packed), (uintptr_t)0x42)
        << "Bits above 44 should be masked off";
}

TEST(RemoteFramePackerTest, UnsymbolizedFramePacksWithZeroMark) {
    // The new code path packs unsymbolized frames with mark=0
    uintptr_t pc_offset = 0x1A2B3C;
    uint32_t lib_index = 7;
    unsigned long packed = RFP::pack(pc_offset, 0, lib_index);

    EXPECT_EQ(RFP::unpackPcOffset(packed), pc_offset);
    EXPECT_EQ(RFP::unpackMark(packed), 0);
    EXPECT_EQ(RFP::unpackLibIndex(packed), lib_index);
    // Packed value is non-zero even with mark=0 (prevents false NULL check)
    EXPECT_NE(packed, 0UL);
}

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
    char* build_id = SymbolsLinux::extractBuildId("/nonexistent", &build_id_len);

    // Should return null for non-existent file
    EXPECT_EQ(build_id, nullptr);
    EXPECT_EQ(build_id_len, 0);
}

TEST_F(RemoteSymbolicationTest, BuildIdExtractionInvalidInput) {
    size_t build_id_len = 0;

    // Test null inputs
    char* build_id1 = SymbolsLinux::extractBuildId(nullptr, &build_id_len);
    EXPECT_EQ(build_id1, nullptr);

    char* build_id2 = SymbolsLinux::extractBuildId("/some/file", nullptr);
    EXPECT_EQ(build_id2, nullptr);

    // Test non-ELF file
    const char* test_content = "This is not an ELF file";
    char temp_file[] = "/tmp/not_an_elf_XXXXXX";

    int fd = mkstemp(temp_file);
    if (fd >= 0) {
        write(fd, test_content, strlen(test_content));
        close(fd);

        char* build_id3 = SymbolsLinux::extractBuildId(temp_file, &build_id_len);
        EXPECT_EQ(build_id3, nullptr);

        unlink(temp_file);
    }
}

TEST_F(RemoteSymbolicationTest, BuildIdFromMemoryInvalidInput) {
    size_t build_id_len = 0;

    // Test null pointer
    char* build_id1 = SymbolsLinux::extractBuildIdFromMemory(nullptr, 100, &build_id_len);
    EXPECT_EQ(build_id1, nullptr);

    // Test invalid size
    char dummy_data[10] = {0};
    char* build_id2 = SymbolsLinux::extractBuildIdFromMemory(dummy_data, 0, &build_id_len);
    EXPECT_EQ(build_id2, nullptr);

    // Test null output parameter
    char* build_id3 = SymbolsLinux::extractBuildIdFromMemory(dummy_data, 10, nullptr);
    EXPECT_EQ(build_id3, nullptr);
}

#endif // __linux__
