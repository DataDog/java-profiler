/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Regression test for PROF-15130: duplicate jdk.types.Method constant-pool
 * ids. resolveMethod() used `mi->_key = _method_map->size() + 1`, but
 * cleanupUnreferencedMethods() erases unreferenced entries and shrinks the
 * map, so size()+1 later reissues an id still owned by a surviving method.
 * Two live methods then share an id in one chunk → first-wins strict parsers
 * (JMC/jafar/Datadog backend) render a phantom method.
 *
 * The fix replaced size()+1 with MethodMap::allocId()/freeId(): a free-list
 * id allocator that recycles an id only after the owning method is erased.
 * These tests drive the allocator directly and assert the live-id-uniqueness
 * invariant, including the exact scenario that broke size()+1.
 */

#include <gtest/gtest.h>
#include "../../main/cpp/flightRecorder.h"
#include <set>
#include <vector>

// Reference model of the BUGGY scheme that the fix replaced.
// size()+1 derives the id from the current number of live entries.
static u32 buggyNextId(size_t live_count) {
    return static_cast<u32>(live_count) + 1; // avoid zero key
}

// 1) Basic monotonic allocation with no frees: ids are unique and start at 1.
TEST(MethodMapIdTest, AllocWithoutFreeIsUniqueAndStartsAtOne) {
    MethodMap m;
    std::set<u32> seen;
    u32 prev = 0;
    for (int i = 0; i < 1000; i++) {
        u32 id = m.allocId();
        EXPECT_NE(id, 0U) << "id 0 is reserved as the no-entry sentinel";
        EXPECT_TRUE(seen.insert(id).second) << "duplicate id handed out: " << id;
        EXPECT_GT(id, prev) << "ids must be monotonic before any free";
        prev = id;
    }
}

// 2) freeId(0) is a no-op: the sentinel must never enter the free list.
TEST(MethodMapIdTest, FreeIdZeroIsNoOp) {
    MethodMap m;
    m.freeId(0);
    EXPECT_NE(m.allocId(), 0U);
}

// 3) A freed id is recycled (LEB128 stays compact) and is only re-handed out
//    after it was freed.
TEST(MethodMapIdTest, FreedIdIsRecycled) {
    MethodMap m;
    u32 a = m.allocId(); // 1
    u32 b = m.allocId(); // 2
    u32 c = m.allocId(); // 3
    EXPECT_EQ(a, 1U);
    EXPECT_EQ(b, 2U);
    EXPECT_EQ(c, 3U);

    m.freeId(b); // free the middle id
    u32 d = m.allocId();
    EXPECT_EQ(d, b) << "the freed id should be recycled before the high water grows";
}

// 4) THE INVARIANT (this is what size()+1 violated).
//    Simulate the resolve/erase cycle: alloc a batch, free a middle subset
//    (the "erased" methods), alloc more, and assert at every step that the set
//    of ids currently held by live entries has no duplicates and that a newly
//    allocated id never collides with a still-live id.
TEST(MethodMapIdTest, LiveIdsNeverCollideAcrossEraseReuseCycle) {
    MethodMap m;
    std::set<u32> live; // ids currently owned by live methods

    auto alloc = [&]() {
        u32 id = m.allocId();
        EXPECT_NE(id, 0U);
        // The core invariant: a newly handed-out id must not already be live.
        EXPECT_EQ(live.count(id), 0U)
            << "allocId() returned id " << id << " that is still owned by a live method";
        live.insert(id);
        return id;
    };
    auto freeOne = [&](u32 id) {
        live.erase(id);
        m.freeId(id);
    };

    // Phase 1: allocate ids 1..N for an initial population of live methods.
    const int N = 64;
    std::vector<u32> ids;
    for (int i = 0; i < N; i++) ids.push_back(alloc());

    // Phase 2: free a middle subset (simulating cleanupUnreferencedMethods
    //          erasing methods that aged out) while a disjoint set survives.
    //          Free indices 20..39 (ids 21..40); keep 1..20 and 41..64 live.
    for (int i = 20; i < 40; i++) freeOne(ids[i]);

    // Phase 3: allocate a new batch. With size()+1 these would collide with the
    //          surviving high ids; with the free-list they reuse the freed ids.
    //          The alloc lambda asserts no collision with any live id.
    for (int i = 0; i < 40; i++) alloc();

    // Cross-check: enumerate every live id and confirm uniqueness holds.
    std::set<u32> uniq(live.begin(), live.end());
    EXPECT_EQ(uniq.size(), live.size()) << "duplicate id among live methods";
}

// 5) Demonstrate that the OLD size()+1 scheme DOES produce a duplicate live id
//    in exactly the erase+reuse scenario above. This pins the bug so the test
//    is not vacuous: if someone reintroduces size()+1, the asserted property
//    (no duplicate live ids) is false.
TEST(MethodMapIdTest, BuggySizePlusOneSchemeProducesDuplicateLiveId) {
    // Model live methods as a set of ids. size()+1 derives the id from the
    // current live count, mirroring `mi->_key = _method_map->size() + 1`.
    std::set<u32> live;

    // Phase 1: resolve N methods → ids 1..N (count grows each insert).
    const int N = 64;
    std::vector<u32> ids;
    for (int i = 0; i < N; i++) {
        u32 id = buggyNextId(live.size());
        ids.push_back(id);
        live.insert(id);
    }
    // After phase 1, live = {1..64}.

    // Phase 2: erase a middle subset (ids 21..40), shrinking the map. NOTE the
    // buggy scheme has nothing analogous to freeId — it just shrinks.
    for (int i = 20; i < 40; i++) live.erase(ids[i]);
    // live now = {1..20, 41..64}, size() == 44.

    // Phase 3: resolve ONE more method. size()+1 == 44+1 == 45, but 45 is still
    // owned by a surviving phase-1 method → DUPLICATE id in the chunk.
    u32 next = buggyNextId(live.size());
    EXPECT_TRUE(live.count(next) > 0)
        << "expected size()+1 to collide with a live id, got fresh id " << next;
    EXPECT_EQ(next, 45U);

    // Contrast: the fixed allocator does NOT collide for the same sequence.
    MethodMap m;
    std::set<u32> fixedLive;
    std::vector<u32> fixedIds;
    for (int i = 0; i < N; i++) {
        u32 id = m.allocId();
        fixedIds.push_back(id);
        fixedLive.insert(id);
    }
    for (int i = 20; i < 40; i++) {
        fixedLive.erase(fixedIds[i]);
        m.freeId(fixedIds[i]);
    }
    u32 fixedNext = m.allocId();
    EXPECT_EQ(fixedLive.count(fixedNext), 0U)
        << "fixed allocator handed out a still-live id " << fixedNext;
}
