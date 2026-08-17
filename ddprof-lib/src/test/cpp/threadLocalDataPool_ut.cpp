/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
// threadLocalData.h must precede threadLocalDataPool.h: ProfiledThread needs to
// be a complete type before contains()'s pointer arithmetic is parsed (the
// pool header only forward-declares it).
#include "threadLocalData.h"
#include "threadLocalDataPool.h"
#include "threadLocalData.inline.h"
#include "counters.h"

#include <mutex>
#include <pthread.h>

// Covers ThreadLocalDataPool::contains(), whose result feeds directly into
// unclaim()'s double-release guard. Uses createForTest()/destroyForTest() to
// build a pool isolated from the process-wide singleton (_pool), so these
// boundary checks don't interact with other tests' initialize()/acquire()/
// release() calls.
class ThreadLocalDataPoolTest : public ::testing::Test {};

TEST_F(ThreadLocalDataPoolTest, firstElementIsContained) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(4);
    ProfiledThread* base = pool->threadsForTest();

    EXPECT_TRUE(pool->containsForTest(base));

    ThreadLocalDataPool::destroyForTest(pool);
}

TEST_F(ThreadLocalDataPoolTest, lastElementIsContained) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(4);
    ProfiledThread* base = pool->threadsForTest();
    uint64_t capacity = pool->capacityForTest();

    EXPECT_TRUE(pool->containsForTest(base + (capacity - 1)));

    ThreadLocalDataPool::destroyForTest(pool);
}

TEST_F(ThreadLocalDataPoolTest, onePastEndIsNotContained) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(4);
    ProfiledThread* base = pool->threadsForTest();
    uint64_t capacity = pool->capacityForTest();

    EXPECT_FALSE(pool->containsForTest(base + capacity));

    ThreadLocalDataPool::destroyForTest(pool);
}

TEST_F(ThreadLocalDataPoolTest, oneBeforeStartIsNotContained) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(4);
    ProfiledThread* base = pool->threadsForTest();

    EXPECT_FALSE(pool->containsForTest(base - 1));

    ThreadLocalDataPool::destroyForTest(pool);
}

TEST_F(ThreadLocalDataPoolTest, nullptrIsNotContained) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(4);

    EXPECT_FALSE(pool->containsForTest(nullptr));

    ThreadLocalDataPool::destroyForTest(pool);
}

// Covers claim() once every slot is taken. Two things must hold, and neither is
// visible in the return value alone (which is nullptr on every failure path):
//
//  1. The drop is recorded in SAMPLES_DROPPED_TLS_POOL_EXHAUSTED. This counter
//     is the only signal that priming is silently failing in the field; an
//     earlier revision incremented it solely on the scan fallthrough, so the
//     real (used >= _capacity) path dropped samples untracked.
//  2. The rejected claim rolls back the speculative _used increment it took
//     before the capacity check. Without the rollback, _used never falls back
//     below _capacity and the pool stays permanently full even after slots are
//     returned -- which the reclaim at the end of this test exercises.
TEST_F(ThreadLocalDataPoolTest, claimAtCapacityRejectsAndRecordsExhaustion) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(2);

    ProfiledThread* first = pool->claimForTest(0);
    ASSERT_NE(first, nullptr);
    ASSERT_NE(pool->claimForTest(1), nullptr);

    long long before = Counters::getCounter(SAMPLES_DROPPED_TLS_POOL_EXHAUSTED);
    EXPECT_EQ(pool->claimForTest(2), nullptr);
    EXPECT_EQ(Counters::getCounter(SAMPLES_DROPPED_TLS_POOL_EXHAUSTED), before + 1);

    EXPECT_TRUE(pool->unclaimForTest(first));
    EXPECT_NE(pool->claimForTest(0), nullptr);

    ThreadLocalDataPool::destroyForTest(pool);
}

// Covers unclaimAndReset(): a slot handed to a new tid after a prior owner
// released it must not carry over that owner's per-thread state. claimAcquire()
// itself only ever sets _tid on the fast path (threadLocalData.inline.h) --
// every other field's "clean" value is whatever unclaimAndReset() left behind,
// so a reset that drops a field is invisible until a slot is actually reused.
TEST_F(ThreadLocalDataPoolTest, reclaimedSlotHasResetState) {
    ThreadLocalDataPool* pool = ThreadLocalDataPool::createForTest(1);

    ProfiledThread* first = pool->claimForTest(100);
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first->tid(), 100);

    // Dirty the fields unclaimAndReset() is responsible for restoring.
    first->setFilterSlotId(7);
    EXPECT_TRUE(first->tryEnterCriticalSection());

    ASSERT_TRUE(pool->unclaimForTest(first));

    ProfiledThread* second = pool->claimForTest(200);
    ASSERT_EQ(second, first) << "capacity-1 pool must hand back the same slot";
    EXPECT_EQ(second->tid(), 200);
    EXPECT_EQ(second->filterSlotId(), -1);
    // If _in_critical_section had leaked as true, this compare-and-swap would
    // fail because the slot would already look "entered".
    EXPECT_TRUE(second->tryEnterCriticalSection());
    second->exitCriticalSection();

    ThreadLocalDataPool::destroyForTest(pool);
}

// Broader companion to reclaimedSlotHasResetState above, which only checks
// filterSlotId and _in_critical_section. This dirties every field
// unclaimAndReset() is responsible for and asserts the result matches a
// freshly-constructed instance field-for-field, via the raw snapshot
// (snapshotForTest()) so a field that's silently dropped from the reset
// can't hide behind a getter that happens to read as "clean" anyway.
// Uses forTid() directly rather than going through the pool -- unclaimAndReset()
// doesn't care how the instance was created.
TEST(ProfiledThreadTest, UnclaimAndResetMatchesFreshInstance) {
    ProfiledThread* dirty = ProfiledThread::forTid(123);
    // unclaimAndReset() always zeroes _tid, so the fresh reference instance
    // must be constructed with 0 to be comparable (_tid is intentionally
    // excluded from snapshotForTest() for this reason, but tid() is checked
    // directly below).
    ProfiledThread* fresh = ProfiledThread::forTid(0);

    sigjmp_buf fake_jmp_buf;
    dirty->set_unwinding_Java(true);
    dirty->setJmpCtx(&fake_jmp_buf);
    // Falls through to the cache-miss path (fresh _call_trace_id is 0),
    // unconditionally dirtying pc/sp/span_id/recording_epoch/otel_local_root_span_id.
    dirty->lookupWallclockCallTraceId(/*pc*/0x1000, /*sp*/0x2000, /*recording_epoch*/7,
                                       /*context_valid*/true, /*span_id*/0x3000, /*root_span_id*/0x4000);
    dirty->recordCallTraceId(0x5000);
    dirty->noteCPUSample(9);
    dirty->setJavaThread(true);
    ASSERT_TRUE(dirty->parkEnter());
    dirty->setParkBlockToken(0x1234);
    dirty->setFilterSlotId(42);
    dirty->startInitWindow();
    dirty->enterSignalScope();
    ASSERT_TRUE(dirty->tryEnterCriticalSection());
    dirty->markContextInitialized();
    ASSERT_TRUE(dirty->enterCrashHandler());
    memset(dirty->getOtelContextRecord(), 0xAB, sizeof(OtelThreadContextRecord));
    u32* tags = dirty->getOtelTagEncodingsPtr();
    for (u32 i = 0; i < DD_TAGS_CAPACITY; i++) {
        tags[i] = 0xAAAAAAAA;
    }
#ifdef DEBUG
    dirty->unwindFailures()->record(UNWIND_FAILURE_STUB, "dirty");
#endif

    // Sanity-check the dirtying above actually took effect, so a broken
    // mutator can't make the post-reset comparison pass vacuously.
    ASSERT_NE(dirty->snapshotForTest().misc_flags, fresh->snapshotForTest().misc_flags);

    dirty->unclaimAndResetForTest();

    EXPECT_EQ(dirty->tid(), fresh->tid());

    auto reset_snapshot = dirty->snapshotForTest();
    auto fresh_snapshot = fresh->snapshotForTest();
    EXPECT_EQ(reset_snapshot.unwinding_java, fresh_snapshot.unwinding_java);
    EXPECT_EQ(reset_snapshot.jmp_buf, fresh_snapshot.jmp_buf);
    EXPECT_EQ(reset_snapshot.pc, fresh_snapshot.pc);
    EXPECT_EQ(reset_snapshot.sp, fresh_snapshot.sp);
    EXPECT_EQ(reset_snapshot.span_id, fresh_snapshot.span_id);
    EXPECT_EQ(reset_snapshot.crash_depth, fresh_snapshot.crash_depth);
    EXPECT_EQ(reset_snapshot.cpu_epoch, fresh_snapshot.cpu_epoch);
    // _wall_epoch has no public mutator anywhere in the codebase today, so
    // this only confirms the trivial zero-stays-zero case.
    EXPECT_EQ(reset_snapshot.wall_epoch, fresh_snapshot.wall_epoch);
    EXPECT_EQ(reset_snapshot.call_trace_id, fresh_snapshot.call_trace_id);
    EXPECT_EQ(reset_snapshot.recording_epoch, fresh_snapshot.recording_epoch);
    EXPECT_EQ(reset_snapshot.misc_flags, fresh_snapshot.misc_flags);
    EXPECT_EQ(reset_snapshot.park_block_token, fresh_snapshot.park_block_token);
    EXPECT_EQ(reset_snapshot.filter_slot_id, fresh_snapshot.filter_slot_id);
    EXPECT_EQ(reset_snapshot.init_window, fresh_snapshot.init_window);
    EXPECT_EQ(reset_snapshot.signal_depth, fresh_snapshot.signal_depth);
    EXPECT_EQ(reset_snapshot.in_critical_section, fresh_snapshot.in_critical_section);
    EXPECT_EQ(reset_snapshot.otel_ctx_initialized, fresh_snapshot.otel_ctx_initialized);
    EXPECT_EQ(reset_snapshot.otel_local_root_span_id, fresh_snapshot.otel_local_root_span_id);

    OtelThreadContextRecord zero_record{};
    EXPECT_EQ(memcmp(dirty->getOtelContextRecord(), &zero_record, sizeof(OtelThreadContextRecord)), 0);
    for (u32 i = 0; i < DD_TAGS_CAPACITY; i++) {
        EXPECT_EQ(dirty->getOtelTagEncoding(i), 0u);
    }
#ifdef DEBUG
    EXPECT_EQ(dirty->unwindFailures(false)->findName("dirty"), -1);
#endif

    dirty->exitCriticalSection();
    ProfiledThread::deleteForTest(dirty);
    ProfiledThread::deleteForTest(fresh);
}

// Regression for a ThreadLocalDataPool slot leak in
// ProfiledThread::initCurrentThread(): forTid()'s `new ProfiledThread(tid)`
// can recurse into a malloc hook (e.g. nativemem profiling's
// MallocTracer::maybeRecord) before initCurrentThread() has published the new
// instance to TLS. Seeing TLS still unset, the hook's acquireCurrent() claims
// a pool slot and publishes it to TLS itself. initCurrentThread() then
// unconditionally overwrites TLS with the heap-allocated instance, and
// without the fix the pool slot is never released -- it stays claimed
// forever, permanently shrinking the 64-slot pool by one.
//
// forTidTestHook (threadLocalData.h, UNIT_TEST-only) simulates that reentrant
// call deterministically, without needing real malloc-hook plumbing.
static std::once_flag g_priming_race_pool_init;
static ProfiledThread* g_primed_during_fortid = nullptr;

static void simulateNestedMallocHookPriming() {
    g_primed_during_fortid = ProfiledThread::acquireCurrent();
}

static void* threadPrimingRaceBody(void*) {
    std::call_once(g_priming_race_pool_init, [] { ThreadLocalDataPool::initialize(); });
    EXPECT_EQ(nullptr, ProfiledThread::current());

    g_primed_during_fortid = nullptr;
    ProfiledThread::forTidTestHook = simulateNestedMallocHookPriming;
    ProfiledThread* tls = ProfiledThread::initCurrentThread();
    ProfiledThread::forTidTestHook = nullptr;

    EXPECT_NE(nullptr, g_primed_during_fortid) << "hook did not simulate a nested claim";
    EXPECT_NE(nullptr, tls);
    if (tls == nullptr) {
        return nullptr;
    }
    EXPECT_NE(tls, g_primed_during_fortid)
        << "the heap-allocated thread and the nested pool claim must be distinct objects";
    EXPECT_EQ(tls, ProfiledThread::current())
        << "TLS must end up holding the heap-allocated thread, not the pool one";
    if (g_primed_during_fortid != nullptr) {
        EXPECT_FALSE(g_primed_during_fortid->isClaimedForTest())
            << "pool slot claimed by the nested acquireCurrent() must be released, not orphaned";
    }

    ProfiledThread::release();
    return nullptr;
}

TEST(ProfiledThreadTest, NestedPrimingDuringForTidReleasesPoolSlot) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, threadPrimingRaceBody, nullptr));
    pthread_join(t, nullptr);
}
