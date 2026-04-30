/*
 * Copyright 2026 Datadog, Inc.
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
#include "thread.h"

TEST(ProfiledThreadParkStateTest, ParkFlagLifecycle) {
  ProfiledThread *thread = ProfiledThread::forTid(12345);

  EXPECT_FALSE(thread->isParkedForWallclock());

  thread->parkEnter(101, 202, 777);
  EXPECT_TRUE(thread->isParkedForWallclock());

  u64 start_ticks = 0;
  Context park_context = {};
  EXPECT_TRUE(thread->parkExit(start_ticks, park_context));
  EXPECT_EQ(777ULL, start_ticks);
  EXPECT_EQ(101ULL, park_context.spanId);
  EXPECT_EQ(202ULL, park_context.rootSpanId);
  EXPECT_FALSE(thread->isParkedForWallclock());

  // Second exit is a no-op once the parked bit is cleared.
  EXPECT_FALSE(thread->parkExit(start_ticks, park_context));
}

TEST(ProfiledThreadParkStateTest, ParkEnterSnapshotsTagEncodings) {
  ProfiledThread *thread = ProfiledThread::forTid(12346);
  u32 *tags = thread->getOtelTagEncodingsPtr();
  tags[0] = 11;
  tags[1] = 22;
  tags[2] = 33;

  thread->parkEnter(303, 404, 888);

  // Mutate live encodings after enter: park context must keep the enter snapshot.
  tags[0] = 111;
  tags[1] = 222;
  tags[2] = 333;

  u64 start_ticks = 0;
  Context park_context = {};
  ASSERT_TRUE(thread->parkExit(start_ticks, park_context));
  EXPECT_EQ(888ULL, start_ticks);
  EXPECT_EQ(303ULL, park_context.spanId);
  EXPECT_EQ(404ULL, park_context.rootSpanId);
  EXPECT_EQ(11U, park_context.tags[0].value);
  EXPECT_EQ(22U, park_context.tags[1].value);
  EXPECT_EQ(33U, park_context.tags[2].value);
}
