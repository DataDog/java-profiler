/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#ifdef __linux__
#include <features.h>
#endif

#include <atomic>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <mutex>
#include <signal.h>
#include <thread>
#include <vector>

#include "mallocArenaWalker.h"
#include "os.h"
#include "safeAccess.h"
#include "../../main/cpp/gtest_crash_handler.h"

TEST(MallocArenaWalkerStatus, NamesCoverEveryValue) {
  static const char* const expected[ARENA_WALK_STATUS_COUNT] = {
      "ok",          "unsupported-platform", "unsupported-jvm", "replaced-allocator",
      "hugetlb-tunable", "no-seed",          "no-layout",       "fault",
      "implausible", "bad-next",             "second-main",     "no-main",
      "too-many"};
  for (int i = 0; i < ARENA_WALK_STATUS_COUNT; i++) {
    EXPECT_STREQ(expected[i], arenaWalkStatusName((ArenaWalkStatus)i)) << i;
  }
  EXPECT_STREQ("unknown", arenaWalkStatusName(ARENA_WALK_STATUS_COUNT));
}

TEST(MallocArenaWalkerLayout, PreferredLayoutByVersion) {
  EXPECT_EQ(0, preferredArenaLayout(2, 17));
  EXPECT_EQ(0, preferredArenaLayout(2, 22));
  EXPECT_EQ(1, preferredArenaLayout(2, 23));
  EXPECT_EQ(1, preferredArenaLayout(2, 26));
  EXPECT_EQ(2, preferredArenaLayout(2, 27));
  EXPECT_EQ(2, preferredArenaLayout(2, 42));
  EXPECT_EQ(3, preferredArenaLayout(2, 43));
  EXPECT_NE(nullptr, arenaLayoutAt(3));
  EXPECT_EQ(nullptr, arenaLayoutAt(4));
  EXPECT_EQ(nullptr, arenaLayoutAt(-1));
}

#if !(defined(__linux__) && defined(__GLIBC__))

TEST(MallocArenaWalkerPlatform, NonGlibcIsUnsupported) {
  ArenaWalkResult r;
  MallocArenaWalker::walk(&r, 64);
  EXPECT_EQ(ARENA_WALK_UNSUPPORTED_PLATFORM, r.status);
  MallocArenaWalker::walkWithLayout(*arenaLayoutAt(2), &r, 64);
  EXPECT_EQ(ARENA_WALK_UNSUPPORTED_PLATFORM, r.status);
}

#elif defined(ASAN_ENABLED) || defined(TSAN_ENABLED)

// The sanitizer allocator replaces glibc malloc, so no glibc arena exists.
TEST(MallocArenaWalkerGlibc, SkippedUnderSanitizerAllocator) {
  GTEST_SKIP() << "malloc is replaced by the sanitizer allocator";
}

#else

static constexpr char WALKER_TEST_NAME[] = "MallocArenaWalkerTest";

static void (*orig_segvHandler)(int, siginfo_t*, void*);
static void (*orig_busHandler)(int, siginfo_t*, void*);

static void walkerSignalWrapper(int signo, siginfo_t* siginfo, void* context) {
  if (!SafeAccess::handle_safefetch(signo, context)) {
    if (signo == SIGBUS && orig_busHandler != nullptr) {
      orig_busHandler(signo, siginfo, context);
    } else if (signo == SIGSEGV && orig_segvHandler != nullptr) {
      orig_segvHandler(signo, siginfo, context);
    } else {
      gtestCrashHandler(signo, siginfo, context, WALKER_TEST_NAME);
    }
  }
}

class MallocArenaWalkerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    if (dlsym(RTLD_DEFAULT, "mallctl") != nullptr || dlsym(RTLD_DEFAULT, "tc_malloc_size") != nullptr) {
      GTEST_SKIP() << "malloc is replaced by a non-glibc allocator";
    }
    orig_segvHandler = OS::replaceSigsegvHandler(walkerSignalWrapper);
    orig_busHandler = OS::replaceSigbusHandler(walkerSignalWrapper);
    installed = true;
    MallocArenaWalker::resetForTest();
  }

  void TearDown() override {
    if (installed) {
      OS::replaceSigsegvHandler(orig_segvHandler);
      OS::replaceSigbusHandler(orig_busHandler);
    }
    MallocArenaWalker::resetForTest();
  }

  bool installed = false;
};

// Runs fn(i) on n threads that are all alive, each with a malloc-ed block, when
// fn runs. Live threads force glibc to create per-thread arenas.
template <typename Fn>
static void runOnLiveThreads(int n, Fn fn) {
  std::atomic<int> arrived(0);
  std::atomic<bool> go(false);
  std::vector<std::thread> threads;
  for (int i = 0; i < n; i++) {
    threads.emplace_back([&, i]() {
      void* keep = malloc(4096);
      arrived.fetch_add(1);
      while (!go.load()) {
        std::this_thread::yield();
      }
      fn(i);
      free(keep);
    });
  }
  while (arrived.load() < n) {
    std::this_thread::yield();
  }
  go.store(true);
  for (auto& t : threads) {
    t.join();
  }
}

TEST_F(MallocArenaWalkerTest, WalkWithLiveThreadsFindsArenas) {
  std::mutex mu;
  std::vector<ArenaWalkResult> results;
  runOnLiveThreads(16, [&](int) {
    ArenaWalkResult r;
    MallocArenaWalker::walk(&r, 4096);
    std::lock_guard<std::mutex> g(mu);
    results.push_back(r);
  });
  // A thread whose chunk lives in main_arena reports NO_SEED; at least one
  // thread must get a non-main arena.
  const ArenaWalkResult* ok = nullptr;
  for (const ArenaWalkResult& r : results) {
    if (r.status == ARENA_WALK_OK) {
      ok = &r;
      break;
    }
  }
  ASSERT_NE(nullptr, ok) << "no thread obtained a walkable result";

  // The threads have run, so the seed is cached; walk on the test thread.
  ArenaWalkResult cached;
  MallocArenaWalker::walk(&cached, 4096);
  if (cached.status == ARENA_WALK_NO_SEED) {
    GTEST_SKIP() << "no non-main arena seed available on the test thread";
  }
  ASSERT_EQ(ARENA_WALK_OK, cached.status);
  EXPECT_GE(cached.arenaCount, 2);
  EXPECT_GT(cached.nonMainBytes, 0u);

  EXPECT_GE(ok->arenaCount, 2);
  EXPECT_GT(ok->nonMainBytes, 0u);
  EXPECT_GT(ok->mainBytes, 0u);
  EXPECT_GE(ok->layoutIndex, 0);
  EXPECT_GE(ok->largestMaxBytes, ok->largestBytes);
}

TEST_F(MallocArenaWalkerTest, WrongLayoutFailsClosed) {
  std::mutex mu;
  ArenaWalkResult calibrated;
  bool haveCalibrated = false;
  runOnLiveThreads(16, [&](int) {
    ArenaWalkResult r;
    MallocArenaWalker::walk(&r, 4096);
    std::lock_guard<std::mutex> g(mu);
    if (r.status == ARENA_WALK_OK && !haveCalibrated) {
      calibrated = r;
      haveCalibrated = true;
    }
  });
  ASSERT_TRUE(haveCalibrated);

  // The seed is cached, so the walks below run on the test thread.
  for (int i = 0; i < ARENA_LAYOUT_COUNT; i++) {
    if (i == calibrated.layoutIndex) continue;
    ArenaWalkResult r;
    MallocArenaWalker::walkWithLayout(*arenaLayoutAt(i), &r, 4096);
    EXPECT_NE(ARENA_WALK_OK, r.status) << "layout " << i;
  }
  ArenaLayout garbage = {8, 16, 24, 32, "garbage"};
  ArenaWalkResult r;
  MallocArenaWalker::walkWithLayout(garbage, &r, 4096);
  EXPECT_NE(ARENA_WALK_OK, r.status);
  ArenaLayout unmapped = {1, 2, 3, 4, "unmapped"};
  MallocArenaWalker::walkWithLayout(unmapped, &r, 4096);
  EXPECT_NE(ARENA_WALK_OK, r.status);
}

TEST_F(MallocArenaWalkerTest, CapBoundsTheWalk) {
  std::mutex mu;
  ArenaWalkStatus tooMany = ARENA_WALK_OK;
  bool seen = false;
  runOnLiveThreads(16, [&](int) {
    ArenaWalkResult r;
    MallocArenaWalker::walk(&r, 4096);
    if (r.status != ARENA_WALK_OK || r.arenaCount < 2) return;
    ArenaWalkResult small;
    MallocArenaWalker::walk(&small, 1);
    std::lock_guard<std::mutex> g(mu);
    if (!seen) {
      tooMany = small.status;
      seen = true;
    }
  });
  ASSERT_TRUE(seen);
  EXPECT_EQ(ARENA_WALK_TOO_MANY, tooMany);
}

#endif
