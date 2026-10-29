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
#include "nativeMem.h"
#include "perfEvents.h"

#include <cerrno>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// The failure-path tests force calloc to fail with a negative count, which
// makes count * size overflow. The CI sanitizer jobs run gtest binaries
// without *SAN_OPTIONS, so allocator_may_return_null defaults to 0 and the
// sanitizer reports that overflow as a fatal error instead of returning NULL.
#if defined(ASAN_ENABLED) || defined(TSAN_ENABLED)
#define SKIP_IF_CALLOC_OVERFLOW_ABORTS()                                       \
  GTEST_SKIP() << "sanitizer allocators abort on calloc overflow"
#else
#define SKIP_IF_CALLOC_OVERFLOW_ABORTS()
#endif

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

  static bool resizeEvents(PerfEvents &engine, int max_events) {
    return engine.resizeEvents(max_events);
  }
  static PerfEvent *events() { return PerfEvents::_events; }
  static int maxEvents() { return PerfEvents::_max_events; }
  static PerfEvent *eventFor(int tid) { return PerfEvents::eventFor(tid); }
  static unsigned int gen() { return PerfEvents::_events_gen; }
  static void setGen(unsigned int gen) { PerfEvents::_events_gen = gen; }
  static void setSlot(int tid, int fd, void *page) {
    PerfEvents::setSlotForTest(tid, fd, page);
  }
  static int slotFd(int tid) { return PerfEvents::slotFdForTest(tid); }

  // Hands the current table to the caller without freeing it, so a test can
  // start from an empty table and later reinstate the original one.
  static void detach() {
    PerfEvents::_events = nullptr;
    PerfEvents::_max_events = -1;
  }

  // Frees the test-owned table and reinstates the detached one, without
  // touching the gauge (the fixture restores that separately).
  static void reattach(PerfEvent *events, int max_events) {
    free(PerfEvents::_events);
    PerfEvents::_events = events;
    PerfEvents::_max_events = max_events;
  }
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

// Runs resizeEvents() against an empty table and an NM_PERF gauge starting at
// zero, and puts the original table, generation and gauge back afterwards.
class PerfEventsResizeTest : public ::testing::Test {
protected:
  PerfEvent *_saved_events;
  int _saved_max;
  unsigned int _saved_gen;
  long long _saved_live;
  size_t _page_size;

  void SetUp() override {
    _saved_events = PerfEventsTestAccessor::events();
    _saved_max = PerfEventsTestAccessor::maxEvents();
    _saved_gen = PerfEventsTestAccessor::gen();
    _saved_live = NativeMem::live(NM_PERF);
    _page_size = (size_t)sysconf(_SC_PAGESIZE);
    PerfEventsTestAccessor::detach();
    NativeMem::setLive(NM_PERF, 0);
  }

  void TearDown() override {
    PerfEventsTestAccessor::reattach(_saved_events, _saved_max);
    PerfEventsTestAccessor::setGen(_saved_gen);
    NativeMem::setLive(NM_PERF, _saved_live);
  }

  // Puts a pipe read end and a 2-page anonymous mapping into slot tid, and
  // accounts the ring the way registerThread() does. Returns the write end
  // through *write_fd.
  void armSlot(int tid, int *read_fd, int *write_fd, void **page) {
    int fds[2];
    ASSERT_EQ(0, pipe(fds));
    *read_fd = fds[0];
    *write_fd = fds[1];
    *page = mmap(nullptr, 2 * _page_size, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    ASSERT_NE(MAP_FAILED, *page);
    *(uint64_t *)*page = RING_SENTINEL;
    PerfEventsTestAccessor::setSlot(tid, *read_fd, *page);
    NativeMem::record(NM_PERF, (long long)(2 * _page_size));
  }

  // Reports whether the ring armSlot() mapped at page is still mapped. Once
  // the ring is unmapped, the allocator may map new memory at the same
  // address: musl's malloc does when resizeEvents() allocates the new table.
  // So the check reads back the sentinel armSlot() wrote instead of only
  // probing the address. The read goes through a pipe, which fails with
  // EFAULT instead of faulting when the page is unmapped or inaccessible.
  static bool ringMapped(void *page) {
    int fds[2];
    if (pipe(fds) != 0) {
      ADD_FAILURE() << "pipe() failed: " << errno;
      return true;
    }
    uint64_t value = 0;
    bool readable = write(fds[1], page, sizeof(value)) == sizeof(value) &&
                    read(fds[0], &value, sizeof(value)) == sizeof(value);
    close(fds[0]);
    close(fds[1]);
    return readable && value == RING_SENTINEL;
  }

  static constexpr uint64_t RING_SENTINEL = 0x5a5a5a5a5a5a5a5aULL;
};

// A failed allocation leaves a NULL table with a -1 bound, not a NULL table
// with a stale bound, releases the old table's bytes from the gauge, and a
// later resize recovers.
TEST_F(PerfEventsResizeTest, FailedAllocationLeavesNoTable) {
  SKIP_IF_CALLOC_OVERFLOW_ABORTS();
  PerfEvents engine;
  ASSERT_TRUE(PerfEventsTestAccessor::resizeEvents(engine, 1024));
  ASSERT_NE(nullptr, PerfEventsTestAccessor::events());
  EXPECT_EQ(1024, PerfEventsTestAccessor::maxEvents());
  long long one = NativeMem::live(NM_PERF);
  EXPECT_GT(one, 0);

  EXPECT_FALSE(PerfEventsTestAccessor::resizeEvents(engine, -1));
  EXPECT_EQ(nullptr, PerfEventsTestAccessor::events());
  EXPECT_EQ(-1, PerfEventsTestAccessor::maxEvents());
  EXPECT_EQ(0, NativeMem::live(NM_PERF));
  EXPECT_EQ(nullptr, PerfEventsTestAccessor::eventFor(0));
  // The failure state reads as "not started" and rejects every tid.
  EXPECT_EQ(0, engine.registerThread(5));
  engine.unregisterThread(5);

  ASSERT_TRUE(PerfEventsTestAccessor::resizeEvents(engine, 1024));
  EXPECT_NE(nullptr, PerfEventsTestAccessor::eventFor(1023));
  EXPECT_EQ(nullptr, PerfEventsTestAccessor::eventFor(1024));
  EXPECT_EQ(one, NativeMem::live(NM_PERF));
}

// Replacing the table closes every fd and unmaps every ring the old table
// holds: once it is freed nothing could reach them. The fd check runs right
// after the resize, before anything else in the test opens a file, so the fd
// number cannot have been reused (gtest is single-threaded here). The ring
// address can be: see ringMapped().
TEST_F(PerfEventsResizeTest, ResizeReleasesOldSlots) {
  PerfEvents engine;
  ASSERT_TRUE(PerfEventsTestAccessor::resizeEvents(engine, 64));
  long long base = NativeMem::live(NM_PERF);
  int fd = -1, write_fd = -1;
  void *page = nullptr;
  armSlot(5, &fd, &write_fd, &page);
  ASSERT_FALSE(HasFatalFailure());
  ASSERT_EQ(base + (long long)(2 * _page_size), NativeMem::live(NM_PERF));

  ASSERT_TRUE(PerfEventsTestAccessor::resizeEvents(engine, 128));
  errno = 0;
  int fcntl_rc = fcntl(fd, F_GETFD);
  int fcntl_errno = errno;
  bool mapped = ringMapped(page);

  EXPECT_EQ(-1, fcntl_rc);
  EXPECT_EQ(EBADF, fcntl_errno);
  EXPECT_FALSE(mapped);
  EXPECT_EQ(2 * base, NativeMem::live(NM_PERF));
  EXPECT_EQ(0, PerfEventsTestAccessor::slotFd(5));
  close(write_fd);
}

// The failure path releases the old table's slots too.
TEST_F(PerfEventsResizeTest, FailedResizeReleasesOldSlots) {
  SKIP_IF_CALLOC_OVERFLOW_ABORTS();
  PerfEvents engine;
  ASSERT_TRUE(PerfEventsTestAccessor::resizeEvents(engine, 64));
  int fd = -1, write_fd = -1;
  void *page = nullptr;
  armSlot(5, &fd, &write_fd, &page);
  ASSERT_FALSE(HasFatalFailure());

  EXPECT_FALSE(PerfEventsTestAccessor::resizeEvents(engine, -1));
  errno = 0;
  int fcntl_rc = fcntl(fd, F_GETFD);
  int fcntl_errno = errno;
  bool mapped = ringMapped(page);

  EXPECT_EQ(-1, fcntl_rc);
  EXPECT_EQ(EBADF, fcntl_errno);
  EXPECT_FALSE(mapped);
  EXPECT_EQ(0, NativeMem::live(NM_PERF));
  close(write_fd);
}

// An unchanged size keeps the table, its fds and the gauge, so fds survive a
// stop()/start() when pid_max did not change.
TEST_F(PerfEventsResizeTest, SameSizeKeepsTable) {
  PerfEvents engine;
  ASSERT_TRUE(PerfEventsTestAccessor::resizeEvents(engine, 64));
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  PerfEventsTestAccessor::setSlot(3, fds[0], nullptr);
  PerfEvent *table = PerfEventsTestAccessor::events();
  unsigned int gen = PerfEventsTestAccessor::gen();
  long long live = NativeMem::live(NM_PERF);

  bool resized = PerfEventsTestAccessor::resizeEvents(engine, 64);
  int fcntl_rc = fcntl(fds[0], F_GETFD);

  EXPECT_TRUE(resized);
  EXPECT_EQ(table, PerfEventsTestAccessor::events());
  EXPECT_EQ(gen, PerfEventsTestAccessor::gen());
  EXPECT_EQ(live, NativeMem::live(NM_PERF));
  EXPECT_NE(-1, fcntl_rc);
  PerfEventsTestAccessor::setSlot(3, 0, nullptr);
  close(fds[0]);
  close(fds[1]);
}

// eventFor() rejects the table while the generation is odd (a replacement in
// progress), and every resize, failed or not, advances the generation by two
// and leaves it even.
TEST_F(PerfEventsResizeTest, EventForRejectsOddGenerationAndResizeAdvancesIt) {
  PerfEvents engine;
  ASSERT_TRUE(PerfEventsTestAccessor::resizeEvents(engine, 64));
  unsigned int g = PerfEventsTestAccessor::gen();
  EXPECT_EQ(0u, g & 1);
  EXPECT_NE(nullptr, PerfEventsTestAccessor::eventFor(3));

  PerfEventsTestAccessor::setGen(g + 1);
  EXPECT_EQ(nullptr, PerfEventsTestAccessor::eventFor(3));
  PerfEventsTestAccessor::setGen(g);
  EXPECT_NE(nullptr, PerfEventsTestAccessor::eventFor(3));

  ASSERT_TRUE(PerfEventsTestAccessor::resizeEvents(engine, 128));
  EXPECT_EQ(g + 2, PerfEventsTestAccessor::gen());
}

TEST_F(PerfEventsResizeTest, FailedResizeAdvancesGenerationToEven) {
  SKIP_IF_CALLOC_OVERFLOW_ABORTS();
  PerfEvents engine;
  ASSERT_TRUE(PerfEventsTestAccessor::resizeEvents(engine, 64));
  unsigned int g = PerfEventsTestAccessor::gen();
  EXPECT_FALSE(PerfEventsTestAccessor::resizeEvents(engine, -1));
  EXPECT_EQ(g + 2, PerfEventsTestAccessor::gen());
  EXPECT_EQ(0u, PerfEventsTestAccessor::gen() & 1);
}

// A negative tid must not index before the table. The page before the table
// is inaccessible, so an access through _events[-1] faults.
TEST(PerfEventsTableTest, NegativeTidIsRejected) {
  size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
  char *base = (char *)mmap(nullptr, 3 * page_size, PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(MAP_FAILED, (void *)base);
  ASSERT_EQ(0, mprotect(base, page_size, PROT_NONE));
  {
    PerfEventsTestAccessor::TableSwap swap(
        reinterpret_cast<PerfEvent *>(base + page_size), 4, RING_KERNEL);
    PerfEvents engine;
    EXPECT_EQ(-1, engine.registerThread(-1));
    engine.unregisterThread(-1);
    EXPECT_EQ(nullptr, PerfEventsTestAccessor::eventFor(-1));
  }
  munmap(base, 3 * page_size);
}

#endif // __linux__
