/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include "flightRecorder.h"
#include "tsc.h"

class RecordingTestAccessor {
public:
    static void write(Buffer* buffer, ExecutionEvent* event) {
        Recording::writeSampleHeader(buffer, T_METHOD_SAMPLE, 17, 300, 42, event);
    }
};

static u64 readVar(const Buffer& buffer, int& offset) {
    u64 value = 0;
    for (int i = 0; i < 9; ++i) {
        if (offset >= buffer.offset()) throw std::runtime_error("Truncated varint");
        unsigned char byte = buffer.data()[offset++];
        value |= static_cast<u64>(i == 8 ? byte : byte & 0x7f) << (i * 7);
        if (i == 8 || (byte & 0x80) == 0) return value;
    }
    throw std::runtime_error("Invalid varint");
}

TEST(MethodSampleEpochEncodingTest, RetainedTimestampAndWeightReachWireWithoutSchemaChange) {
    ExecutionEvent event;
    event._sample_ticks = 123456789;
    event._weight = 300;
    event._thread_state = OSThreadState::SLEEPING;
    event._execution_mode = ExecutionMode::UNKNOWN;
    Buffer buffer;
    RecordingTestAccessor::write(&buffer, &event);
    int offset = 0;
    EXPECT_EQ(T_METHOD_SAMPLE, readVar(buffer, offset));
    EXPECT_EQ(event._sample_ticks, readVar(buffer, offset));
    EXPECT_EQ(17ULL, readVar(buffer, offset));
    EXPECT_EQ(300ULL, readVar(buffer, offset));
    ASSERT_LT(offset + 1, buffer.offset());
    EXPECT_EQ(static_cast<char>(event._thread_state), buffer.data()[offset++]);
    EXPECT_EQ(static_cast<char>(event._execution_mode), buffer.data()[offset++]);
    EXPECT_EQ(300ULL, readVar(buffer, offset));
    EXPECT_EQ(42ULL, readVar(buffer, offset));
    EXPECT_EQ(buffer.offset(), offset);
}

TEST(MethodSampleEpochEncodingTest, OrdinarySamplesKeepActualSerializationTimestamp) {
    ExecutionEvent event;
    Buffer buffer;
    const u64 before = TSC::ticks();
    RecordingTestAccessor::write(&buffer, &event);
    const u64 after = TSC::ticks();
    int offset = 0;
    ASSERT_EQ(T_METHOD_SAMPLE, readVar(buffer, offset));
    const u64 timestamp = readVar(buffer, offset);
    EXPECT_GE(timestamp, before);
    EXPECT_LE(timestamp, after);
}
