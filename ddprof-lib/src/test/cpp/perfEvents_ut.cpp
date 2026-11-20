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
#include <sys/mman.h>
#include <unistd.h>

#include "../../main/cpp/gtest_crash_handler.h"

#ifdef __linux__

#include "perfEvents.h"

#include <climits>
#include <cstdlib>

static int compare(int a, int b) { return PerfEvents::compareTids(&a, &b); }

// A NULL-dereference or guard-page fault in the table tests below must be
// reported as this binary's crash (backtrace and test name) instead of a
// bare signal death, so a regression is diagnosable from the CI artifacts.
static constexpr char PERF_EVENTS_TEST_NAME[] = "PerfEventsTableTest";

class GlobalSetup {
public:
  GlobalSetup() { installGtestCrashHandler<PERF_EVENTS_TEST_NAME>(); }
  ~GlobalSetup() { restoreDefaultSignalHandlers(); }
};

static GlobalSetup global_setup;

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
// needs slot setters in perfEvents_linux.cpp, which this binary does not have.
TEST(PerfEventsTableTest, MissingTableIsNotIndexed) {
  PerfEvents::resetBuffer(5);
}

// Test-only friend accessor for PerfEvents' private table statics (the
// CTimerTestAccessor pattern in ctimer_ut.cpp). It exists solely so the
// unregisterThread() tests below can place the table in the states the
// start() resize window produces -- a NULL table with a stale capacity, or
// a zeroed table backed by a guard page -- without starting the engine, and
// must never be used from production code.
class PerfEventsTestAccessor {
public:
  static PerfEvent *events() { return PerfEvents::_events; }
  static int maxEvents() { return PerfEvents::_max_events; }

  // Swaps the table statics for a test's and restores them on scope exit,
  // without freeing anything: the swapped-in table belongs to the test
  // (mmap or NULL), and the saved one is reinstated as it was found.
  class TableSwap {
  public:
    TableSwap(PerfEvent *events, int max_events)
        : _saved_events(PerfEventsTestAccessor::events()),
          _saved_max_events(PerfEventsTestAccessor::maxEvents()) {
      PerfEvents::_events = events;
      PerfEvents::_max_events = max_events;
    }

    ~TableSwap() {
      PerfEvents::_events = _saved_events;
      PerfEvents::_max_events = _saved_max_events;
    }

    // Non-copyable: a copy would restore the statics twice, the second time
    // from a stale saved pair (the TimerTableSwap precedent deletes both).
    TableSwap(const TableSwap &) = delete;
    TableSwap &operator=(const TableSwap &) = delete;

  private:
    PerfEvent *_saved_events;
    int _saved_max_events;
  };
};

// start()'s table resize publishes NULL before freeing the old table, and
// the new table only after calloc succeeds, so across the swap -- and after
// a failed allocation, until _max_events is reset -- a hook unregister can
// see _events == NULL while _max_events still holds the old size. The tid
// bound alone would accept such a tid (0 and 63 are both < 64), so the NULL
// check must reject the call before it indexes the missing table: this is
// exactly the mid-swap/failed-allocation state, which no single thread can
// observe inside start() itself. Without the guard, &_events[tid] is a NULL
// dereference; surviving the calls (and leaving the statics untouched) is
// the pass condition.
TEST(PerfEventsTableTest, NullTableWithStaleCapacityIsNotIndexed) {
  PerfEvents engine;
  {
    PerfEventsTestAccessor::TableSwap swap(NULL, 64);
    engine.unregisterThread(0);   // lowest tid the stale bound accepts
    engine.unregisterThread(63);  // highest tid the stale bound accepts
    EXPECT_EQ(NULL, PerfEventsTestAccessor::events());
    EXPECT_EQ(64, PerfEventsTestAccessor::maxEvents());
  }
}

// A negative tid passes the plain upper bound but must not index below the
// table. The table is placed at the start of a page whose predecessor is
// PROT_NONE (the CTimerTableTest guard-page pattern): slot -1 spans the
// sizeof(PerfEvent) bytes below the table -- a cache-line-aligned (64-byte)
// SpinLock plus _fd and _page, so a multiple of 64 and under a page -- and
// every byte of it lies in the PROT_NONE page, so a call that wrongly passed
// the bound faults deterministically instead of reading whatever precedes a
// real allocation. Passing also leaves every slot untouched, which the
// all-zero page shows.
TEST(PerfEventsTableTest, NegativeTidIsNotIndexed) {
  size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
  char *base = (char *)mmap(NULL, 2 * page_size, PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(MAP_FAILED, (void *)base);
  ASSERT_EQ(0, mprotect(base, page_size, PROT_NONE));
  PerfEvent *table = (PerfEvent *)(base + page_size);
  {
    PerfEventsTestAccessor::TableSwap swap(table, 16);
    PerfEvents engine;
    engine.unregisterThread(-1);
    unsigned char *bytes = (unsigned char *)table;
    for (size_t i = 0; i < page_size; i++) {
      EXPECT_EQ(0, bytes[i]) << "slot byte " << i;
    }
  }
  munmap(base, 2 * page_size);
}

// A tid exactly at _max_events must not index one past the table. The
// mapping is one RW page for the table followed by eight PROT_NONE pages,
// and _max_events is page_size/64 slots: sizeof(PerfEvent) is a multiple of
// the 64-byte cache-line alignment (and 128 today: SpinLock + _fd + _page),
// so the bound slot starts somewhere in that PROT_NONE tail -- a call that
// wrongly passed the bound faults on its _fd read instead of indexing
// whatever follows the table. The rejected call also leaves the table page
// untouched, which the all-zero readback shows.
TEST(PerfEventsTableTest, TidAtBoundIsNotIndexed) {
  size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
  size_t map_bytes = 9 * page_size;
  char *base = (char *)mmap(NULL, map_bytes, PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(MAP_FAILED, (void *)base);
  ASSERT_EQ(0, mprotect(base + page_size, map_bytes - page_size, PROT_NONE));
  {
    PerfEventsTestAccessor::TableSwap swap((PerfEvent *)base,
                                           (int)(page_size / 64));
    PerfEvents engine;
    engine.unregisterThread((int)(page_size / 64));
    unsigned char *bytes = (unsigned char *)base;
    for (size_t i = 0; i < page_size; i++) {
      EXPECT_EQ(0, bytes[i]) << "slot byte " << i;
    }
  }
  munmap(base, map_bytes);
}

#endif // __linux__
