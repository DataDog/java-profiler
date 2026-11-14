/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include <atomic>
#include <cstdlib>
#include <new>
#include <pthread.h>

#include "arguments.h"
#include "referenceChains.h"
#include "referenceChainsTestAccessors.h"
#include "referenceChainsMockHeap.h"
#include "referenceChainsBatchTestSupport.h"

// Counts operator new calls made by the constructing thread while an
// AllocCounter scope is open; the hook pauses mock bookkeeping so mock
// internals never pollute the count. Allocations of other threads never count.
static std::atomic<bool> g_counting{false};
// Identity is published once (first AllocCounter) and never rewritten: an
// interceptor on any thread reads it only after acquiring g_counting == true,
// which is stored after the single write - no repeated-write race exists.
static pthread_t g_counting_thread;
static std::atomic<bool> g_thread_published{false};
// Relaxed: only the counting thread increments and reads the counter (the
// identity check excludes every other thread), and all of that is same-thread.
static std::atomic<long> g_allocs{0};
// Relaxed: only the counting thread's value decides counting - foreign
// threads exit at the identity check before reaching this load.
static std::atomic<int> g_pause_depth{0};

static void accountingHook(bool pause) {
    g_pause_depth.fetch_add(pause ? 1 : -1, std::memory_order_relaxed);
}

static bool shouldCount() {
    if (!g_counting.load(std::memory_order_acquire)) return false;
    if (!pthread_equal(pthread_self(), g_counting_thread)) return false;
    return g_pause_depth.load(std::memory_order_relaxed) == 0;
}

static void *plainAlloc(std::size_t size, bool nothrow) {
    if (shouldCount()) g_allocs.fetch_add(1, std::memory_order_relaxed);
    void *ptr = malloc(size ? size : 1);
    if (ptr == nullptr && !nothrow) throw std::bad_alloc();
    return ptr;
}

static void *alignedAlloc(std::size_t size, std::size_t alignment, bool nothrow) {
    if (shouldCount()) g_allocs.fetch_add(1, std::memory_order_relaxed);
    void *ptr = nullptr;
    if (posix_memalign(&ptr, alignment, size ? size : 1) != 0) ptr = nullptr;
    if (ptr == nullptr && !nothrow) throw std::bad_alloc();
    return ptr;
}

// TSan's runtime (libclang_rt.tsan_cxx, linked --whole-archive) defines strong
// operator new/delete symbols; interposing here fails the TSan link. Without
// the interposition the counting is inert, so SetUp() skips the fixture under TSan.
#ifndef TSAN_ENABLED
void *operator new(std::size_t size) { return plainAlloc(size, false); }
void *operator new[](std::size_t size) { return plainAlloc(size, false); }
void *operator new(std::size_t size, const std::nothrow_t &) noexcept {
    return plainAlloc(size, true);
}
void *operator new[](std::size_t size, const std::nothrow_t &) noexcept {
    return plainAlloc(size, true);
}
void *operator new(std::size_t size, std::align_val_t alignment) {
    return alignedAlloc(size, static_cast<std::size_t>(alignment), false);
}
void *operator new[](std::size_t size, std::align_val_t alignment) {
    return alignedAlloc(size, static_cast<std::size_t>(alignment), false);
}
void *operator new(std::size_t size, std::align_val_t alignment,
                   const std::nothrow_t &) noexcept {
    return alignedAlloc(size, static_cast<std::size_t>(alignment), true);
}
void *operator new[](std::size_t size, std::align_val_t alignment,
                     const std::nothrow_t &) noexcept {
    return alignedAlloc(size, static_cast<std::size_t>(alignment), true);
}

// Every new variant above allocates through malloc/posix_memalign, so every
// delete variant frees with free(); freeing itself never counts.
void operator delete(void *ptr) noexcept { free(ptr); }
void operator delete[](void *ptr) noexcept { free(ptr); }
void operator delete(void *ptr, std::size_t) noexcept { free(ptr); }
void operator delete[](void *ptr, std::size_t) noexcept { free(ptr); }
void operator delete(void *ptr, std::align_val_t) noexcept { free(ptr); }
void operator delete[](void *ptr, std::align_val_t) noexcept { free(ptr); }
void operator delete(void *ptr, std::size_t, std::align_val_t) noexcept { free(ptr); }
void operator delete[](void *ptr, std::size_t, std::align_val_t) noexcept { free(ptr); }
void operator delete(void *ptr, const std::nothrow_t &) noexcept { free(ptr); }
void operator delete[](void *ptr, const std::nothrow_t &) noexcept { free(ptr); }
void operator delete(void *ptr, std::align_val_t, const std::nothrow_t &) noexcept { free(ptr); }
void operator delete[](void *ptr, std::align_val_t, const std::nothrow_t &) noexcept { free(ptr); }
#endif  // !TSAN_ENABLED

// RAII owner of one counting interval: construction zeroes the count and
// publishes counting, destruction closes it. All callers are serial scopes on
// the gtest thread - it is not a general concurrent/multi-owner utility.
struct AllocCounter {
    AllocCounter() {
        if (!g_thread_published.exchange(true, std::memory_order_acq_rel)) {
            g_counting_thread = pthread_self();
        }
        g_allocs.store(0, std::memory_order_relaxed);
        g_counting.store(true, std::memory_order_release);
    }
    ~AllocCounter() { g_counting.store(false, std::memory_order_release); }
    AllocCounter(const AllocCounter &) = delete;
    AllocCounter &operator=(const AllocCounter &) = delete;
    AllocCounter(AllocCounter &&) = delete;
    AllocCounter &operator=(AllocCounter &&) = delete;
    long count() const { return g_allocs.load(std::memory_order_relaxed); }
};

class ReferenceChainsAllocationTest : public ::testing::Test,
                                      public ReferenceChainsMockHeap {
protected:
    void SetUp() override {
#if defined(TSAN_ENABLED)
        GTEST_SKIP() << "operator new/delete interposition is compiled out under TSan (runtime owns them); counting is inert";
#endif
        setUp();
        alloc_accounting_hook = &accountingHook;
    }
    void TearDown() override {
        alloc_accounting_hook = nullptr;
        tearDown();
    }
};

// Positive control: explicit operator new/delete calls (a new-expression
// can be elided, these cannot) drive every counting state, so a permanently
// paused or broken hook fails here instead of falsely passing the F1 tests.
TEST_F(ReferenceChainsAllocationTest, ExplicitNewCountsAcrossPauseAndResume) {
    long counted_new, while_paused, while_resumed, while_repaused, after_pause, pause_depth;
    {
        AllocCounter counter;
        ::operator delete(::operator new(16));
        counted_new = counter.count();
        {
            MockAllocPause pause;
            ::operator delete(::operator new(16));
            while_paused = counter.count();
            {
                MockAllocResume resume;
                ::operator delete(::operator new(16));
                while_resumed = counter.count();
            }
            ::operator delete(::operator new(16));
            while_repaused = counter.count();
        }
        ::operator delete(::operator new(16));
        after_pause = counter.count();
        pause_depth = g_pause_depth.load(std::memory_order_relaxed);
    }
    ::operator delete(::operator new(16));
    EXPECT_GT(counted_new, 0);
    EXPECT_EQ(counted_new, while_paused);
    EXPECT_GT(while_resumed, while_paused);
    EXPECT_EQ(while_resumed, while_repaused);
    EXPECT_GT(after_pause, while_repaused);
    EXPECT_EQ(0, pause_depth);
    EXPECT_EQ(after_pause, g_allocs.load(std::memory_order_relaxed))
        << "an explicit new after the scope must not be counted";
}

// Each guard balances through the hook it captured at construction: swapping
// the global hook mid-scope (null included) can neither redirect nor lose the
// release, and a null-captured guard stays fully inert.
TEST_F(ReferenceChainsAllocationTest, GuardsReleaseThroughCapturedHook) {
    EXPECT_EQ(0, g_pause_depth.load(std::memory_order_relaxed));
    {
        MockAllocPause pause;
        EXPECT_EQ(1, g_pause_depth.load(std::memory_order_relaxed));
        {
            MockAllocResume resume;
            EXPECT_EQ(0, g_pause_depth.load(std::memory_order_relaxed));
            alloc_accounting_hook = nullptr;
        }
        EXPECT_EQ(1, g_pause_depth.load(std::memory_order_relaxed))
            << "the resume must re-pause through its captured hook";
    }
    EXPECT_EQ(0, g_pause_depth.load(std::memory_order_relaxed));
    {
        MockAllocPause null_hook_pause;
        alloc_accounting_hook = &accountingHook;
        EXPECT_EQ(0, g_pause_depth.load(std::memory_order_relaxed))
            << "a guard built with a null hook must not call it";
    }
    EXPECT_EQ(0, g_pause_depth.load(std::memory_order_relaxed));
}

static void *foreignAllocator(void *) {
    ::operator delete(::operator new(32));
    ::operator delete(::operator new[](32));
    return nullptr;
}

// The interceptor also runs on foreign threads (any library code); with the
// one-time-published identity their allocations must never be counted.
TEST_F(ReferenceChainsAllocationTest, ForeignThreadAllocationsDoNotCount) {
    pthread_t tid;
    ASSERT_EQ(0, pthread_create(&tid, nullptr, foreignAllocator, nullptr));
    ASSERT_EQ(0, pthread_join(tid, nullptr));
    long owner_count, after_foreign;
    {
        AllocCounter counter;
        ::operator delete(::operator new(32));
        owner_count = counter.count();
        ASSERT_EQ(0, pthread_create(&tid, nullptr, foreignAllocator, nullptr));
        ASSERT_EQ(0, pthread_join(tid, nullptr));
        after_foreign = counter.count();
    }
    EXPECT_GE(owner_count, 1);
    EXPECT_EQ(owner_count, after_foreign)
        << "only the constructing thread's operator new calls may count";
}

TEST_F(ReferenceChainsAllocationTest, TrackLeakAccumulationRecordedAncestorDoesNotAllocate) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100, kMidKlass = 200, kRootKlass = 300;
    jlong rootTag = 1, midTag = 2, parentTag = 3;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, rootTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kRootKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, midTag, rootTag, 1, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kMidKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, midTag, 2, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kParentKlass));

    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parentTag, 10);

    long counted = 0;
    {
        AllocCounter counter;
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parentTag, 11);
        counted = counter.count();
    }
    // The counted call updates in place the fanout entry the warm-up call
    // created, and the walk stops at the first already-recorded ancestor
    // (midTag): no node is inserted, so zero allocations on any STL.
    EXPECT_EQ(0, counted);

    EXPECT_EQ(2u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(midTag));
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(rootTag));

    tracker->stop();
}

TEST_F(ReferenceChainsAllocationTest, TrackLeakAccumulationSeededAncestorsDoNotAllocate) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100, kMidKlass = 200, kRootKlass = 300;
    jlong rootTag = 1, midTag = 2, parentTag = 3;
    jlong leafUnderParentTag = 4, leafUnderMidTag = 5, leafUnderRootTag = 6;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, rootTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kRootKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, midTag, rootTag, 1, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kMidKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, midTag, 2, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kParentKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, leafUnderParentTag, parentTag, 3, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kLeafKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, leafUnderMidTag, midTag, 2, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kLeafKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, leafUnderRootTag, rootTag, 1, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kLeafKlass));

    // Seeding inserts parent, mid and root with ancestors_recorded=false.
    ReferenceChainsTestAccessor::seedLeakAccumulationForNewlyWatchedKlass(kLeafKlass);
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    long counted = 0;
    {
        AllocCounter counter;
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parentTag, 10);
        counted = counter.count();
    }
    // Seeded mid and root already exist with ancestors_recorded=false, so the
    // walk finds both without inserting: zero allocations on any STL - an
    // emplace-first revert may allocate a node per duplicate visited.
    EXPECT_EQ(0, counted);

    u64 key = 0;
    u32 mid_fanout = 0, root_fanout = 0, parent_fanout = 0;
    bool mid_recorded = false, root_recorded = false, parent_recorded = false;
    ASSERT_TRUE(ReferenceChainsTestAccessor::leakParentFanoutEntry(
        midTag, &key, &mid_fanout, &mid_recorded));
    ASSERT_TRUE(ReferenceChainsTestAccessor::leakParentFanoutEntry(
        rootTag, &key, &root_fanout, &root_recorded));
    ASSERT_TRUE(ReferenceChainsTestAccessor::leakParentFanoutEntry(
        parentTag, &key, &parent_fanout, &parent_recorded));
    EXPECT_EQ(1u, mid_fanout);
    EXPECT_TRUE(mid_recorded);
    EXPECT_EQ(1u, root_fanout);
    EXPECT_TRUE(root_recorded);
    EXPECT_EQ(2u, parent_fanout);
    EXPECT_TRUE(parent_recorded);

    tracker->stop();
}

TEST_F(ReferenceChainsAllocationTest, ExpandFrontierBatchBookkeepingDoesNotScaleWithBatchSize) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    // Empty-queue warm-up: exercises expandFrontier()'s first-call setup (the
    // holder-array element class cache) so both counted calls take an identical path.
    int edges = 0;
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti, &mock_jni, &edges);

    std::vector<jlong> small_tags;
    for (int i = 0; i < 8; i++) {
        small_tags.push_back(seedBatchEntry(tracker, *this, frontier, addNode()));
    }
    ReferenceChainsTestAccessor::setGotwBatchSize(256);
    long small = 0;
    int small_gotw_calls = gotw_calls_;
    {
        AllocCounter counter;
        ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti, &mock_jni, &edges);
        small = counter.count();
    }
    int small_gotw_delta = gotw_calls_ - small_gotw_calls;
    EXPECT_EQ(1, small_gotw_delta);
    for (jlong tag : small_tags) {
        FrontierEntry entry{};
        ASSERT_TRUE(frontier->lookup(tag, &entry));
        EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state);
    }

    std::vector<jlong> large_tags;
    for (int i = 0; i < 256; i++) {
        large_tags.push_back(seedBatchEntry(tracker, *this, frontier, addNode()));
    }
    // The counted call above re-calibrated the adaptive batch size, so pin it again.
    ReferenceChainsTestAccessor::setGotwBatchSize(256);
    long large = 0;
    int large_gotw_calls = gotw_calls_;
    {
        AllocCounter counter;
        ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti, &mock_jni, &edges);
        large = counter.count();
    }
    int large_gotw_delta = gotw_calls_ - large_gotw_calls;
    EXPECT_EQ(1, large_gotw_delta);
    for (jlong tag : large_tags) {
        FrontierEntry entry{};
        ASSERT_TRUE(frontier->lookup(tag, &entry));
        EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state);
    }
    EXPECT_TRUE(ReferenceChainsTestAccessor::pendingExpandContents().empty());
    // Mock allocations are paused; the remaining per-call allocation is the
    // candidate_tags vector (one block per call), independent of batch size.
    EXPECT_LE(large - small, 2);

    tracker->stop();
}
