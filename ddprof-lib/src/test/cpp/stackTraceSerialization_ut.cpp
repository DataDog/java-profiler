/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "callTraceHashTable.h"
#include "flightRecorder.h"

class RecordingTestAccessor {
public:
    static void writeHeader(Buffer* buffer, const CallTrace* trace, const MethodInfo* root) {
        Recording::writeStackTraceHeader(buffer, trace, root);
    }
};

namespace {

class StackTraceSerializationTest : public ::testing::Test {
protected:
    void check(bool walker_truncated, FrameTypeId root_type, bool entry, bool expected) {
        CallTrace trace(walker_truncated, 3, 300);
        MethodInfo root;
        root._type = root_type;
        root._is_entry = entry;
        Buffer buffer;
        RecordingTestAccessor::writeHeader(&buffer, &trace, &root);
        ASSERT_EQ(4, buffer.offset());
        // Decode the variable-length pool id before inspecting the serialized
        // flag, so a field-order or varint-boundary error cannot pass unnoticed.
        const unsigned char* bytes = (const unsigned char*)buffer.data();
        EXPECT_EQ(0xac, bytes[0]);
        EXPECT_EQ(0x02, bytes[1]);
        EXPECT_EQ(expected ? 1 : 0, bytes[2]);
        EXPECT_EQ(3, bytes[3]);
    }
};

TEST_F(StackTraceSerializationTest, ExplicitTruncationSurvivesJavaEntryRoot) {
    check(true, FRAME_INTERPRETED, true, true);
}

TEST_F(StackTraceSerializationTest, JavaEntryRootWithoutMissingFramesIsComplete) {
    check(false, FRAME_INTERPRETED, true, false);
}

TEST_F(StackTraceSerializationTest, JavaNonEntryRootIsIncompleteWithoutWalkerFlag) {
    check(false, FRAME_INTERPRETED, false, true);
}

TEST_F(StackTraceSerializationTest, JavaNonEntryRootPreservesWalkerFlag) {
    check(true, FRAME_INTERPRETED, false, true);
}

TEST_F(StackTraceSerializationTest, NativeRootPreservesExplicitTruncation) {
    check(true, FRAME_NATIVE, false, true);
}

TEST_F(StackTraceSerializationTest, NativeRootWithoutWalkerFlagIsComplete) {
    check(false, FRAME_NATIVE, false, false);
}

} // namespace
