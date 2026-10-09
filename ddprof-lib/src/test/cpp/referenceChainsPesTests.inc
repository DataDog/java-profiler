// PriorityExpandSet and ClassTagAllocator tests.

TEST(PriorityExpandSetTest, InsertContainsClearRoundTrip) {
    ReferenceChainsTestAccessor::pesClear();

    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(42));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesInsert(42));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(42));
    // Already present.
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesInsert(42));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesInsert(43));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(43));

    ReferenceChainsTestAccessor::pesClear();
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(42))
        << "clear must empty the set";
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(43));

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

    queue.pop_front();
    ReferenceChainsTestAccessor::pesRebuildFrom(queue);
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(10))
        << "stale member after rebuildFrom";
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(20));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(30));
    ReferenceChainsTestAccessor::pesClear();
}

// insert() on a full table must return false instead of probing forever.
TEST(PriorityExpandSetTest, InsertOnFullTableTerminatesWithoutLivelock) {
    ReferenceChainsTestAccessor::pesClear();

    const int capacity = 1 << 11; // 2048 slots (SLOT_SHIFT == 11)
    for (int i = 0; i < capacity; i++) {
        ASSERT_TRUE(ReferenceChainsTestAccessor::pesInsert(1000 + (jlong)i * 7919))
            << "insert must succeed until the table is full (i=" << i << ")";
    }
    EXPECT_TRUE(ReferenceChainsTestAccessor::pesContains(1000));
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(987654321));
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesInsert(987654321));
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesInsert(1000));
    ReferenceChainsTestAccessor::pesClear();
    EXPECT_FALSE(ReferenceChainsTestAccessor::pesContains(1000));
}

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
