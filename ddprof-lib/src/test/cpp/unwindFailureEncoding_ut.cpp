/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include "flightRecorder.h"
#include "unwindStats.h"

#ifdef DEBUG
class RecordingTestAccessor {
public:
    static void writeFailure(Buffer* buffer, const char* kind, const char* name, u64 count) {
        Recording::writeUnwindFailureEvent(buffer, 123456789, kind, name, count);
    }
};

// JFR varints use seven bits per byte, with all eight bits used in byte nine.
static u64 readVar(const Buffer& buffer, int& offset) {
    u64 result = 0;
    for (int i = 0; i < 9; i++) {
        if (offset >= buffer.offset()) throw std::runtime_error("Truncated varint");
        unsigned char byte = buffer.data()[offset++];
        result |= (u64)(i == 8 ? byte : byte & 0x7f) << (i * 7);
        if (i == 8 || (byte & 0x80) == 0) return result;
    }
    return result;
}

static std::string readString(const Buffer& buffer, int& offset) {
    if (offset >= buffer.offset() || buffer.data()[offset++] != 3) {
        throw std::runtime_error("Expected UTF-8 string");
    }
    u64 length = readVar(buffer, offset);
    if (length > (u64)(buffer.offset() - offset)) throw std::runtime_error("Truncated string");
    std::string value(buffer.data() + offset, (size_t)length);
    offset += (int)length;
    return value;
}

class UnwindFailureEncodingTest : public ::testing::TestWithParam<size_t> {};

TEST_P(UnwindFailureEncodingTest, PreservesEventBoundariesAndDiagnosticFields) {
    size_t length = GetParam();
    // Keep an assertion in the old writer from aborting the whole test binary.
    ASSERT_EXIT({
        Buffer buffer;
        buffer.skip(13);
        std::string name(length, 'x');
        UnwindFailures failures;
        failures.record(UNWIND_FAILURE_STUB, name.c_str());
        failures.forEach([&](UnwindFailureKind, const char* stored_name, u64 count) {
            RecordingTestAccessor::writeFailure(&buffer, "stub", stored_name, count);
        });
        int next = buffer.offset();
        RecordingTestAccessor::writeFailure(&buffer, "other", "control", ~0ULL);

        int offset = 13;
        u64 event_size = readVar(buffer, offset);
        EXPECT_EQ((u64)(next - 13), event_size);
        EXPECT_EQ((u64)T_UNWIND_FAILURE, readVar(buffer, offset));
        EXPECT_EQ(123456789u, readVar(buffer, offset));
        EXPECT_EQ("stub", readString(buffer, offset));
        EXPECT_EQ(name.substr(0, MAX_NAME_LENGTH - 1), readString(buffer, offset));
        EXPECT_EQ(1u, readVar(buffer, offset));
        EXPECT_EQ(next, offset);

        EXPECT_EQ((u64)(buffer.offset() - next), readVar(buffer, offset));
        EXPECT_EQ((u64)T_UNWIND_FAILURE, readVar(buffer, offset));
        EXPECT_EQ(123456789u, readVar(buffer, offset));
        EXPECT_EQ("other", readString(buffer, offset));
        EXPECT_EQ("control", readString(buffer, offset));
        EXPECT_EQ(~0ULL, readVar(buffer, offset));
        EXPECT_EQ(buffer.offset(), offset);
        _exit(::testing::Test::HasFailure() ? 1 : 0);
    }, ::testing::ExitedWithCode(0), "");
}

INSTANTIATE_TEST_SUITE_P(NameLengths, UnwindFailureEncodingTest,
                        ::testing::Values(32, 110, 127, 230, 255, 512));
#endif
