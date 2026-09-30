// Tests from the rc-4 monolith-era ut body: PriorityExpandSet and ClassTagAllocator
// coverage the split-TU .inc families never had. (The five fold-gap regression
// tests are already present in the Bfs/Traversal/Core .inc families on this stack.)

// PriorityExpandSet (referenceChains.h) - the fixed-capacity open-addressed
// set behind _priority_expand. Reviewed gaps: no test referenced the class
// at all, so the probe/insert/clear/rebuildFrom paths and the full-table
// self-termination were only covered indirectly. Driven through the test
// accessor (the class is a private member of the tracker singleton); all
// operations here are pure in-process logic, no JVMTI.
// ---------------------------------------------------------------------------
TEST(PriorityExpandSetTest, InsertContainsClearRoundTrip) {
    ReferenceChainsTestAccessor::pesClear();

    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(42));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesInsert(42));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(42));
    // Idempotent insert: already present returns false.
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesInsert(42));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesInsert(43));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(43));

    ReferenceChainsTestAccessor::pesClear();
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(42))
        << "clear must empty the set";
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(43));

    // Re-insert after clear (slot reuse must work).
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesInsert(42));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(42));
    ReferenceChainsTestAccessor::pesClear();
}

TEST(PriorityExpandSetTest, RebuildFromMatchesQueueContents) {
    ReferenceChainsTestAccessor::pesClear();

    std::deque<jlong> queue = {10, 20, 30};
    ReferenceChainsTestAccessor::pesRebuildFrom(queue);
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(10));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(20));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(30));
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(40));

    // Pop the front (rotation collection's ordinary shape) and rebuild:
    // membership must track the queue exactly - 10 is gone.
    queue.pop_front();
    ReferenceChainsTestAccessor::pesRebuildFrom(queue);
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(10))
        << "stale member after rebuildFrom";
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(20));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(30));
    ReferenceChainsTestAccessor::pesClear();
}

// A completely full table must not livelock the linear-probe loop: insert()
// is required to be self-terminating (returning false - the same "treated
// as not-queued" degradation a full deque push already accepts) even if a
// call site breaks the external "<= PRIORITY_EXPAND_CAP by construction"
// invariant. Fills to capacity with DISTINCT tags, then asserts one more
// insert on a fresh tag terminates (and returns false), and that a
// duplicate of an existing member still returns false via the key match.
// ClassTagAllocator (classTagAllocator.h) - the process-wide negative
// class-object tag allocator shared by ReferenceChainTracker and
// LivenessTracker. Reviewed gap: no test exercised its conventions
// directly. resetForTest() makes each test's minting sequence
// deterministic despite the process-wide counter.
TEST(ClassTagAllocatorTest, MintsStrictlyNegativeStrictlyDecreasingTags) {
    ClassTagAllocator::resetForTest();
    jlong first = ClassTagAllocator::next();
    jlong second = ClassTagAllocator::next();
    EXPECT_LT(first, 0) << "class tags must be negative (heapReferenceCallback"
                           "() dispatches on the sign)";
    EXPECT_LT(second, first) << "tags must decrease monotonically (no reuse)";
    ClassTagAllocator::resetForTest();
    EXPECT_EQ(first, ClassTagAllocator::next())
        << "resetForTest must restart the sequence at the same value";
}

TEST(PriorityExpandSetTest, InsertOnFullTableTerminatesWithoutLivelock) {
    ReferenceChainsTestAccessor::pesClear();

    const int capacity = 1 << 11; // 2048 slots (SLOT_SHIFT == 11)
    for (int i = 0; i < capacity; i++) {
        // Distinct tags spread by Fibonacci hashing - sequential ints are
        // the worst case for proving full-table behavior is probe-safe, so
        // use them deliberately: they land on distinct slots only via the
        // mix(), exercising the wrap path.
        ASSERT_TRUE(ReferenceChainsTestAccessor::pesInsert(1000 + (jlong)i * 7919))
            << "insert must succeed until the table is full (i=" << i << ")";
    }
    // Table full: a fresh tag must return false promptly (no hang).
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesInsert(987654321));
    // A duplicate of an existing member still returns false via the key
    // match (found while probing).
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesInsert(1000));
    ReferenceChainsTestAccessor::pesClear();
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(1000));
}
