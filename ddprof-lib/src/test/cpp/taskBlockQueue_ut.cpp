/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "taskBlockQueue.h"

TEST(TaskBlockQueueTest, PreservesQueuedEventFields) {
  TaskBlockQueue queue;
  QueuedTaskBlockEvent in{};
  in.tid = 123;
  in.generation = 7;
  in.event._start = 10;
  in.event._end = 20;
  in.event._blocker = 30;
  in.event._unblockingSpanId = 40;
  in.event._ctx.spanId = 50;
  in.event._ctx.rootSpanId = 60;

  ASSERT_TRUE(queue.tryPush(in));

  QueuedTaskBlockEvent out{};
  ASSERT_TRUE(queue.tryPop(out));
  EXPECT_EQ(in.tid, out.tid);
  EXPECT_EQ(in.generation, out.generation);
  EXPECT_EQ(in.event._start, out.event._start);
  EXPECT_EQ(in.event._end, out.event._end);
  EXPECT_EQ(in.event._blocker, out.event._blocker);
  EXPECT_EQ(in.event._unblockingSpanId, out.event._unblockingSpanId);
  EXPECT_EQ(in.event._ctx.spanId, out.event._ctx.spanId);
  EXPECT_EQ(in.event._ctx.rootSpanId, out.event._ctx.rootSpanId);
  EXPECT_FALSE(queue.tryPop(out));
}

TEST(TaskBlockQueueTest, FullQueueRejectsWithoutBlocking) {
  TaskBlockQueue queue;
  QueuedTaskBlockEvent event{};
  int accepted = 0;
  while (queue.tryPush(event)) {
    accepted++;
  }

  EXPECT_GT(accepted, 0);
  EXPECT_FALSE(queue.tryPush(event));

  QueuedTaskBlockEvent out{};
  for (int i = 0; i < accepted; i++) {
    ASSERT_TRUE(queue.tryPop(out));
  }
  EXPECT_FALSE(queue.tryPop(out));
  EXPECT_TRUE(queue.tryPush(event));
}

TEST(TaskBlockQueueTest, DiscardAllEmptiesQueue) {
  TaskBlockQueue queue;
  QueuedTaskBlockEvent event{};
  ASSERT_TRUE(queue.tryPush(event));
  ASSERT_TRUE(queue.tryPush(event));

  queue.discardAll();

  QueuedTaskBlockEvent out{};
  EXPECT_FALSE(queue.tryPop(out));
}
