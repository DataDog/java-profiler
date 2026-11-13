/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "profiler.h"

// This accessor's translation unit needs a callable definition even when the
// profiler's own optimized calls are all inlined.
class ProfilerTestAccessor {
public:
  static u32 lockIndex(int tid) { return Profiler::instance()->getLockIndex(tid); }
};

TEST(ProfilerLockIndexTest, CrossTranslationUnitLookupCoversRecordingStripes) {
  bool seen[CONCURRENCY_LEVEL]{};
  for (int tid = 0; tid < 256; ++tid) {
    u32 index = ProfilerTestAccessor::lockIndex(tid);
    ASSERT_LT(index, static_cast<u32>(CONCURRENCY_LEVEL));
    seen[index] = true;
  }
  for (bool reached : seen) {
    EXPECT_TRUE(reached);
  }
}
