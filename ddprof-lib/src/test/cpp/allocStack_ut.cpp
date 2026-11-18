/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <vector>
#include <climits>
#include "profiler.h"

TEST(AllocStackBufferTest, VerificationTailDoesNotOverlapCapturedFrames) {
    for (int depth : {1, 64, 1024, 1025, 2048}) {
        size_t normal = CallTraceBuffer::capacity(depth, ALLOCSTACK_VM);
        size_t verified = CallTraceBuffer::capacity(depth, ALLOCSTACK_VERIFY);
        EXPECT_EQ(static_cast<size_t>(depth + RESERVED_FRAMES), normal);
        EXPECT_EQ(normal, CallTraceBuffer::capacity(depth, ALLOCSTACK_JVMTI));
        EXPECT_EQ(normal, CallTraceBuffer::capacity(depth, ALLOCSTACK_AUTO));
        int expected_depth = depth < 1024 ? depth : 1024;
        EXPECT_EQ(expected_depth, CallTraceBuffer::verificationDepth(depth));
        ASSERT_EQ(normal + expected_depth, verified);
        std::vector<CallTraceBuffer> buffer(verified);
        ASGCT_CallFrame* frames = buffer.data()->_asgct_frames;
        for (int i = 0; i < depth + 1; i++) {
            frames[i].method_id = reinterpret_cast<jmethodID>(i + 1);
            frames[i].bci = i;
        }
        EXPECT_EQ(nullptr, buffer.data()->verificationFrames(depth, normal));
        EXPECT_EQ(nullptr, buffer.data()->verificationFrames(depth, verified - 1));
        jvmtiFrameInfo* scratch = buffer.data()->verificationFrames(depth, verified);
        ASSERT_NE(nullptr, scratch);
        EXPECT_EQ(reinterpret_cast<void*>(buffer.data() + normal), scratch);
        for (int i = 0; i < expected_depth; i++) {
            scratch[i].method = reinterpret_cast<jmethodID>(9999);
            scratch[i].location = -1;
        }
        for (int i = 0; i < depth + 1; i++) {
            EXPECT_EQ(reinterpret_cast<jmethodID>(i + 1), frames[i].method_id);
            EXPECT_EQ(i, frames[i].bci);
        }
    }
}

TEST(AllocStackBufferTest, CapacityDoesNotOverflowAtTheLargestAcceptedDepth) {
    EXPECT_EQ(static_cast<size_t>(INT_MAX) + RESERVED_FRAMES + 1024,
              CallTraceBuffer::capacity(INT_MAX, ALLOCSTACK_VERIFY));
}
