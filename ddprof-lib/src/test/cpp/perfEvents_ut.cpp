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

#include "arguments.h"
#include "perfEvents.h"

#include <climits>
#include <cstdlib>
#include <sys/mman.h>

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

// Swaps PerfEvents' table, bound and ring mode for a test and restores them on
// destruction, including when an assertion returns early.
class PerfEventsTestAccessor {
public:
  class TableSwap {
  public:
    TableSwap(PerfEvent *events, int max_events, Ring ring)
        : _events(PerfEvents::_events), _max_events(PerfEvents::_max_events),
          _ring(PerfEvents::_ring) {
      PerfEvents::_events = events;
      PerfEvents::_max_events = max_events;
      PerfEvents::_ring = ring;
    }
    ~TableSwap() {
      PerfEvents::_events = _events;
      PerfEvents::_max_events = _max_events;
      PerfEvents::_ring = _ring;
    }
    TableSwap(const TableSwap &) = delete;
    TableSwap &operator=(const TableSwap &) = delete;

  private:
    PerfEvent *_events;
    int _max_events;
    Ring _ring;
  };
};

// After a failed table allocation, start() leaves _events NULL with
// _max_events == -1 while fds from an earlier recording may still fire
// SIGPROF. The signal-path readers must not index the NULL table, and
// unregisterThread() must reject every tid.
TEST(PerfEventsTableTest, SignalPathReadersSkipNullTable) {
  PerfEventsTestAccessor::TableSwap swap(nullptr, -1, RING_KERNEL);
  const void *callchain[4];

  for (int tid : {0, 1, 4096}) {
    EXPECT_EQ(0, PerfEvents::walkKernel(tid, callchain, 4, nullptr));
    PerfEvents::resetBuffer(tid);
    PerfEvents engine;
    engine.unregisterThread(tid);
  }
}

// The signal-path readers check the tid against the bound before indexing.
// The table points at an inaccessible page, so any access through it faults.
TEST(PerfEventsTableTest, SignalPathReadersRejectOutOfRangeTid) {
  void *page = mmap(nullptr, 1 << 16, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS,
                    -1, 0);
  ASSERT_NE(MAP_FAILED, page);
  {
    PerfEventsTestAccessor::TableSwap swap(
        reinterpret_cast<PerfEvent *>(page), 0, RING_KERNEL);
    const void *callchain[4];

    for (int tid : {-1, 0, 1}) {
      EXPECT_EQ(0, PerfEvents::walkKernel(tid, callchain, 4, nullptr));
      PerfEvents::resetBuffer(tid);
    }
  }
  munmap(page, 1 << 16);
}

#endif // __linux__
