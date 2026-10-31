/*
 * Copyright 2026, Datadog, Inc.
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

#ifdef __linux__

#include "perfEvents.h"

#include <climits>
#include <cstdlib>

static int compare(int a, int b) { return PerfEvents::compareTids(&a, &b); }

// qsort() requires a negative result when the first argument orders first.
// A comparator that only returns 0/1 is sorted correctly by glibc's merge
// sort, which tests `cmp <= 0`, but not by musl's smoothsort.
TEST(PerfEventsCompareTidsTest, FollowsQsortContract) {
  EXPECT_LT(compare(1, 2), 0);
  EXPECT_GT(compare(2, 1), 0);
  EXPECT_EQ(compare(7, 7), 0);
  // Extremes must not overflow, as a subtraction-based comparator would.
  EXPECT_LT(compare(INT_MIN, INT_MAX), 0);
  EXPECT_GT(compare(INT_MAX, INT_MIN), 0);
  EXPECT_LT(compare(-1, 0), 0);
}

// /proc/self/task lists threads in creation order, so once tids are reused a
// later thread can carry a lower tid. PerfEvents::start() matches tids against
// the sorted list in ascending order and skips every thread after the first
// out-of-order entry, so the sort must hold for such input on every libc.
TEST(PerfEventsCompareTidsTest, SortsCreationOrderedTidsWithReuse) {
  int tids[] = {29, 5001, 5002, 5003, 5004, 5005, 201, 202, 203, 9001, 9002, 9003};
  const int n = sizeof(tids) / sizeof(tids[0]);

  qsort(tids, n, sizeof(int), PerfEvents::compareTids);

  for (int i = 1; i < n; i++) {
    EXPECT_LT(tids[i - 1], tids[i]) << "unsorted at index " << i;
  }
}

// A failed table allocation leaves _events NULL and _max_events -1, which is
// also the state before the first start(). Fds left armed by an earlier
// recording keep delivering SIGPROF, and the handler calls resetBuffer() on
// every exit, so resetBuffer() must not index the missing table. This checks
// only that no crash happens. Checking that releaseThreads() closes real fds
// needs slot setters in perfEvents_linux.cpp, which this binary does not have
// (PROF-16359).
TEST(PerfEventsTableTest, MissingTableIsNotIndexed) {
  PerfEvents::resetBuffer(5);
}

#endif // __linux__
