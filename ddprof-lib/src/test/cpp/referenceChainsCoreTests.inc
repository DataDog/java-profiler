/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "referenceChainsTestAccessors.h"
#include "referenceChainsMockHeap.h"

TEST(RcDebugLevelTest, ParseAcceptsTrimmedSingleDigits) {
    EXPECT_EQ(parseRcDebugLevel(nullptr), -1);
    EXPECT_EQ(parseRcDebugLevel(""), -1);
    EXPECT_EQ(parseRcDebugLevel("0"), 0);
    EXPECT_EQ(parseRcDebugLevel("1"), 1);
    EXPECT_EQ(parseRcDebugLevel("2"), 2);
    EXPECT_EQ(parseRcDebugLevel(" 2\n"), 2); // the `echo 2 >` form
    EXPECT_EQ(parseRcDebugLevel("\t1\r\n"), 1);
    EXPECT_EQ(parseRcDebugLevel("3"), -1);
    EXPECT_EQ(parseRcDebugLevel("12"), -1);
    EXPECT_EQ(parseRcDebugLevel("-1"), -1);
    EXPECT_EQ(parseRcDebugLevel("abc"), -1);
    EXPECT_EQ(parseRcDebugLevel("2 garbage"), -1);
}

TEST(RcDebugLevelTest, ReadFileParsesTrimmedAndRejectsInvalid) {
    char path[] = "/tmp/rc_dbg_test_XXXXXX";
    int fd = mkstemp(path);
    ASSERT_GE(fd, 0);
    close(fd);
    struct Case {
        const char *content;
        int expected;
    };
    const Case cases[] = {
        {"2\n", 2}, {"1", 1}, {" 2 ", 2}, {"\n1\n", 1},
        {"", -1}, {"3", -1}, {"22", -1}, {"abc", -1}, {"x", -1},
    };
    for (const Case &c : cases) {
        FILE *f = fopen(path, "w");
        ASSERT_NE(f, nullptr);
        EXPECT_GE(fputs(c.content, f), 0); // non-negative on success
        fclose(f);
        EXPECT_EQ(readRcDebugLevelFile(path), c.expected) << "content='" << c.content << "'";
    }
    unlink(path);
    EXPECT_EQ(readRcDebugLevelFile(path), -1); // now missing
    EXPECT_EQ(readRcDebugLevelFile(nullptr), -1);
}

TEST(RcDebugLevelTest, ReadFileRejectsSymlinkedOverride) {
    // The knob path lives under world-writable /tmp: a symlink planted by a
    // local user must not be followed (see readRcDebugLevelFile's lstat
    // guard) - only regular files owned by root or the current user are read.
    char target[] = "/tmp/rc_dbg_target_XXXXXX";
    int fd = mkstemp(target);
    ASSERT_GE(fd, 0);
    ASSERT_GE(write(fd, "2\n", 2), 0);
    close(fd);
    char link[] = "/tmp/rc_dbg_link_XXXXXX";
    int lfd = mkstemp(link);
    ASSERT_GE(lfd, 0);
    close(lfd);
    ASSERT_EQ(unlink(link), 0);
    ASSERT_EQ(symlink(target, link), 0);
    EXPECT_EQ(readRcDebugLevelFile(link), -1) // symlink itself: rejected
        << "symlinked override must not be followed";
    EXPECT_EQ(readRcDebugLevelFile(target), 2); // plain regular file: accepted
    unlink(link);
    unlink(target);
}

TEST(RcDebugLevelTest, RefreshFollowsEnvWhenNoOverrideFile) {
    // The refresh's fixed override path is machine-global; skip rather than flake on a developer
    // machine that happens to have the file.
    if (access("/tmp/ddprof_root/refchains_debug_level", F_OK) == 0) {
        GTEST_SKIP() << "override file present on this machine";
    }
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "1", 1);
    rcDebugLevelRefresh(true);
    EXPECT_EQ(rcDebugLevel(), 1);
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "2", 1);
    rcDebugLevelRefresh(true);
    EXPECT_EQ(rcDebugLevel(), 2);
    // invalid env value means silent, not "keep the previous level"
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "bogus", 1);
    rcDebugLevelRefresh(true);
    EXPECT_EQ(rcDebugLevel(), 0);
    // restore the pinned level for any later test's diagnostics
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "2", 1);
    rcDebugLevelRefresh(true);
    EXPECT_EQ(rcDebugLevel(), 2);
}


// ReferenceChainsTestAccessor - same pattern as VMTestAccessor above, for the


class ReferenceChainsTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ tbl{};
    _jvmtiEnv mock_env{};
    jvmtiEnv *orig_jvmti = nullptr;

    void SetUp() override {
        orig_jvmti = VMTestAccessor::getJvmti();
        tbl = jvmtiInterface_1_{};
        tbl.SetEventNotificationMode = &mock_SetEventNotificationMode;
        mock_env.functions = &tbl;
        VMTestAccessor::setJvmti(&mock_env);
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
    }
};

TEST_F(ReferenceChainsTest, DefaultDisabled) {
    Arguments args;
    EXPECT_FALSE(args._reference_chains);
}

TEST_F(ReferenceChainsTest, FlagParsesEnabled) {
    Arguments args;
    Error error = args.parse("referencechains=true");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._reference_chains);
}

TEST_F(ReferenceChainsTest, FlagParsesDisabled) {
    Arguments args;
    Error error = args.parse("referencechains=false");
    EXPECT_FALSE(error);
    EXPECT_FALSE(args._reference_chains);
}

TEST_F(ReferenceChainsTest, FlagParsesSubOptions) {
    Arguments args;
    Error error = args.parse("referencechains=true:hops=64:budget=2000:ttl=5000:framecap=128");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._reference_chains);
    EXPECT_EQ(64, args._reference_chains_hop_cap);
    EXPECT_EQ(2000, args._reference_chains_budget);
    EXPECT_EQ(5000, args._reference_chains_ttl_ms);
    EXPECT_EQ(128, args._reference_chains_frontier_cap);
}

// Negative/out-of-range sub-options must be floored/clamped at the parse boundary
// (Arguments::parse(), arguments.cpp) rather than stored verbatim - see that call site's own
// comment for why an unclamped negative hops in particular is dangerous: `depth >=
// (u32)ctx->hop_cap` (referenceChains.cpp) casts a negative int to u32, wrapping to ~4e9 and
// silently disabling the hop cap entirely.
TEST_F(ReferenceChainsTest, FlagClampsNegativeSubOptions) {
    Arguments args;
    Error error = args.parse(
        "referencechains=true:hops=-1:budget=-5:ttl=-1:framecap=-3:"
        "pausetarget=-1:painbudget=-10");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._reference_chains);
    // Floored to a sane minimum (1), not left negative - a negative value cast to u32 downstream
    // would otherwise wrap to a huge positive number.
    EXPECT_GT(args._reference_chains_hop_cap, 0);
    EXPECT_GT(args._reference_chains_budget, 0);
    EXPECT_GT(args._reference_chains_frontier_cap, 0);
    // ttl/pausetarget are floored at 0 (their own downstream gates already treat 0 as "disabled",
    // so 0 - not 1 - is the correct floor).
    EXPECT_GE(args._reference_chains_ttl_ms, 0);
    EXPECT_GE(args._reference_chains_pause_target_ms, 0);
    // painbudget is a percentage - clamped into [0, 100].
    EXPECT_GE(args._reference_chains_pain_budget_percent, 0);
    EXPECT_LE(args._reference_chains_pain_budget_percent, 100);
}

// A too-large painbudget must be clamped down to 100, not stored verbatim - the sibling of
// FlagClampsNegativeSubOptions above, for the upper bound rather than the lower one.
TEST_F(ReferenceChainsTest, FlagClampsOversizedPainBudgetPercent) {
    Arguments args;
    Error error = args.parse("referencechains=true:painbudget=250");
    EXPECT_FALSE(error);
    EXPECT_EQ(100, args._reference_chains_pain_budget_percent);
}

TEST_F(ReferenceChainsTest, FlagWithOtherArgsDoesNotClobberOuterParse) {
    Arguments args;
    Error error = args.parse("event=cpu,referencechains=true:hops=32,interval=1000000");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._reference_chains);
    EXPECT_EQ(32, args._reference_chains_hop_cap);
    EXPECT_STREQ("cpu", args._event);
    EXPECT_EQ(1000000, args._interval);
}

TEST_F(ReferenceChainsTest, StartStopDisabledDoesNotCrash) {
    Arguments args;
    Error error = args.parse("referencechains=false");
    ASSERT_FALSE(error);

    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    Error startError = tracker->start(args);
    EXPECT_FALSE(startError);
    EXPECT_FALSE(tracker->enabled());
    tracker->stop();
}

TEST_F(ReferenceChainsTest, StartStopEnabledDoesNotCrash) {
    Arguments args;
    Error error = args.parse("referencechains=true:hops=10:budget=100");
    ASSERT_FALSE(error);

    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    Error startError = tracker->start(args);
    EXPECT_FALSE(startError);
    EXPECT_TRUE(tracker->enabled());
    tracker->stop();
}

// GC signal (GarbageCollectionStart/Finish -> epoch counters).

TEST_F(ReferenceChainsTest, GCCallbacksIncrementEpochWhenEnabled) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));

    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    u64 startBefore = tracker->gcStartEpoch();
    u64 finishBefore = tracker->gcFinishEpoch();

    ReferenceChainTracker::GarbageCollectionStart(nullptr);
    ReferenceChainTracker::GarbageCollectionFinish(nullptr);

    EXPECT_EQ(startBefore + 1, tracker->gcStartEpoch());
    EXPECT_EQ(finishBefore + 1, tracker->gcFinishEpoch());

    tracker->stop();
}

TEST_F(ReferenceChainsTest, GCCallbacksAreNoOpWhenDisabled) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=false"));

    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ASSERT_FALSE(tracker->enabled());

    u64 startBefore = tracker->gcStartEpoch();
    u64 finishBefore = tracker->gcFinishEpoch();

    ReferenceChainTracker::GarbageCollectionStart(nullptr);
    ReferenceChainTracker::GarbageCollectionFinish(nullptr);

    EXPECT_EQ(startBefore, tracker->gcStartEpoch());
    EXPECT_EQ(finishBefore, tracker->gcFinishEpoch());
}

// Tag round-trip (SetTag/GetTag/clear).

class ReferenceChainsTagTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ tbl{};
    _jvmtiEnv mock_env{};
    std::unordered_map<void *, jlong> tags;

    static ReferenceChainsTagTest *active_fixture;

    void SetUp() override {
        active_fixture = this;
        tbl = jvmtiInterface_1_{};
        tbl.SetTag = &mock_SetTag;
        tbl.GetTag = &mock_GetTag;
        mock_env.functions = &tbl;
    }

    void TearDown() override {
        active_fixture = nullptr;
    }

    static jvmtiError JNICALL mock_SetTag(jvmtiEnv *, jobject object, jlong tag) {
        if (tag == 0) {
            active_fixture->tags.erase(object);
        } else {
            active_fixture->tags[object] = tag;
        }
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_GetTag(jvmtiEnv *, jobject object, jlong *tag_ptr) {
        auto it = active_fixture->tags.find(object);
        *tag_ptr = it != active_fixture->tags.end() ? it->second : 0;
        return JVMTI_ERROR_NONE;
    }
};

ReferenceChainsTagTest *ReferenceChainsTagTest::active_fixture = nullptr;

TEST_F(ReferenceChainsTagTest, TagRoundTripsThenClears) {
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);

    jlong tag = tracker->tagObject(&mock_env, obj);
    EXPECT_NE(0, tag);
    EXPECT_EQ(tag, tracker->getTag(&mock_env, obj));

    tracker->clearTag(&mock_env, obj);
    EXPECT_EQ(0, tracker->getTag(&mock_env, obj));
}

TEST_F(ReferenceChainsTagTest, TagsAreUniqueAndNeverZero) {
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    int a = 0, b = 0;
    jlong tagA = tracker->tagObject(&mock_env, reinterpret_cast<jobject>(&a));
    jlong tagB = tracker->tagObject(&mock_env, reinterpret_cast<jobject>(&b));

    EXPECT_NE(0, tagA);
    EXPECT_NE(0, tagB);
    EXPECT_NE(tagA, tagB);
}

TEST_F(ReferenceChainsTagTest, UntaggedObjectReadsBackZero) {
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    int untagged = 0;
    EXPECT_EQ(0, tracker->getTag(&mock_env, reinterpret_cast<jobject>(&untagged)));
}

// FrontierTable (tag-indexed frontier metadata table).

TEST(FrontierTableTest, InsertThenLookupRoundTrips) {
    FrontierTable table(64);

    ASSERT_TRUE(table.insert(1, /*parent_tag=*/0, /*referrer_klass=*/7,
                             /*depth=*/0, FrontierEntryState::FRONTIER));

    FrontierEntry entry{};
    ASSERT_TRUE(table.lookup(1, &entry));
    EXPECT_EQ(0, entry.parent_tag);
    EXPECT_EQ(7u, entry.referrer_klass);
    EXPECT_EQ(0u, entry.depth);
    EXPECT_EQ(FrontierEntryState::FRONTIER, entry.state);
}

TEST(FrontierTableTest, LookupOfNeverInsertedTagFails) {
    FrontierTable table(64);
    FrontierEntry entry{};
    EXPECT_FALSE(table.lookup(1, &entry));
    EXPECT_FALSE(table.lookup(5, &entry));
}

TEST(FrontierTableTest, NonPositiveTagIsRejected) {
    FrontierTable table(64);
    FrontierEntry entry{};
    EXPECT_FALSE(table.insert(0, 0, 0, 0));
    EXPECT_FALSE(table.insert(-1, 0, 0, 0));
    EXPECT_FALSE(table.lookup(0, &entry));
    EXPECT_FALSE(table.lookup(-1, &entry));
}

TEST(FrontierTableTest, LookupLockedRejectsNonPositiveTag) {
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 7, 0, FrontierEntryState::FRONTIER));
    FrontierEntry entry{};
    // tag=0 must be rejected the same way lookup() rejects it - callers index the table with tag-1,
    // so a `tag <= 0` check (not just `tag < 0`) is required to keep that subtraction from wrapping
    // into a valid slot.
    EXPECT_FALSE(table.lookupLocked(0, &entry));
    EXPECT_FALSE(table.lookupLocked(-1, &entry));
}

TEST(FrontierTableTest, LookupLockedRejectsTagPastCurrentSize) {
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 7, 0, FrontierEntryState::FRONTIER));
    FrontierEntry entry{};
    // Only tag=1 has ever been inserted (table_size == 1); tag=2 maps to idx=1, exactly at the
    // current size boundary, and must be rejected rather than read out of bounds.
    EXPECT_FALSE(table.lookupLocked(2, &entry));
}

TEST(FrontierTableTest, ParentTagChainReconstructsAcrossHops) {
    // Mirrors how the heap-walk engine walks parent_tag links back to a root: insert a small chain
    // root(tag=1) <- mid(tag=2) <- leaf(tag=3) and confirm the links resolve in order.
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 100, 0, FrontierEntryState::EDGE));
    ASSERT_TRUE(table.insert(2, 1, 200, 1, FrontierEntryState::EDGE));
    ASSERT_TRUE(table.insert(3, 2, 300, 2, FrontierEntryState::EDGE));

    FrontierEntry entry{};
    jlong tag = 3;
    std::vector<u32> chain;
    while (tag != 0) {
        ASSERT_TRUE(table.lookup(tag, &entry));
        chain.push_back(entry.referrer_klass);
        tag = entry.parent_tag;
    }

    ASSERT_EQ(3u, chain.size());
    EXPECT_EQ(300u, chain[0]);
    EXPECT_EQ(200u, chain[1]);
    EXPECT_EQ(100u, chain[2]);
}

TEST(FrontierTableTest, ClearMarksAbandonedWithoutRemovingEntry) {
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 7, 0, FrontierEntryState::FRONTIER));

    table.clear(1);

    FrontierEntry entry{};
    ASSERT_TRUE(table.lookup(1, &entry));
    EXPECT_EQ(FrontierEntryState::ABANDONED, entry.state);
}

TEST(FrontierTableTest, ClearOfNeverInsertedTagIsNoOp) {
    FrontierTable table(64);
    table.clear(1); // must not crash
    FrontierEntry entry{};
    EXPECT_FALSE(table.lookup(1, &entry));
}

TEST(FrontierTableTest, GrowsPastInitialCapacityUpToMaxCap) {
    // Force at least one resize by inserting beyond the small max_cap.
    const int max_cap = 10;
    FrontierTable table(max_cap);
    ASSERT_LE(table.capacity(), max_cap);

    for (jlong tag = 1; tag <= max_cap; tag++) {
        ASSERT_TRUE(table.insert(tag, tag - 1, (u32)tag, (u32)(tag - 1)))
            << "insert failed for tag " << tag;
    }
    EXPECT_EQ(max_cap, table.capacity());

    for (jlong tag = 1; tag <= max_cap; tag++) {
        FrontierEntry entry{};
        ASSERT_TRUE(table.lookup(tag, &entry));
        EXPECT_EQ((u32)tag, entry.referrer_klass);
    }
}

TEST(FrontierTableTest, CapacityExhaustedReportsFailureInsteadOfCrashing) {
    const int max_cap = 4;
    FrontierTable table(max_cap);

    for (jlong tag = 1; tag <= max_cap; tag++) {
        ASSERT_TRUE(table.insert(tag, 0, 0, 0));
    }
    // One past max_cap must be rejected, not silently dropped-but-crashing.
    EXPECT_FALSE(table.insert(max_cap + 1, 0, 0, 0));
    EXPECT_EQ(max_cap, table.capacity());

    // Existing entries remain intact after the failed insert.
    FrontierEntry entry{};
    EXPECT_TRUE(table.lookup(1, &entry));
}

TEST(FrontierTableTest, ZeroMaxCapRejectsEveryInsert) {
    FrontierTable table(0);
    EXPECT_EQ(0, table.capacity());
    EXPECT_FALSE(table.insert(1, 0, 0, 0));
}

TEST(FrontierTableTest, ConcurrentInsertWhileGrowingDoesNotCrash) {
    // Small max_cap relative to thread/tag count forces repeated resizes while other threads are
    // concurrently inserting distinct tags.
    const int max_cap = 4096;
    const int thread_count = 8;
    const int tags_per_thread = 256;
    FrontierTable table(max_cap);

    std::vector<std::thread> threads;
    for (int t = 0; t < thread_count; t++) {
        threads.emplace_back([&table, t, tags_per_thread]() {
            for (int i = 0; i < tags_per_thread; i++) {
                jlong tag = (jlong)t * tags_per_thread + i + 1;
                table.insert(tag, 0, (u32)tag, 0);
            }
        });
    }
    for (auto &th : threads) {
        th.join();
    }

    int found = 0;
    for (jlong tag = 1; tag <= (jlong)thread_count * tags_per_thread; tag++) {
        FrontierEntry entry{};
        if (table.lookup(tag, &entry)) {
            EXPECT_EQ((u32)tag, entry.referrer_klass);
            found++;
        }
    }
    // Every tag fits well within max_cap, so all inserts must have succeeded and be independently
    // readable.
    EXPECT_EQ(thread_count * tags_per_thread, found);
}

TEST(FrontierTableTest, ReconstructChainWalksParentTagsAndPreservesState) {
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 100, 0, FrontierEntryState::FRONTIER));
    ASSERT_TRUE(table.insert(2, 1, 200, 1, FrontierEntryState::FRONTIER));
    ASSERT_TRUE(table.insert(3, 2, 300, 2, FrontierEntryState::EXPANDED));

    std::vector<u32> chain;
    ASSERT_TRUE(table.reconstructChain(3, &chain));
    ASSERT_EQ(3u, chain.size());
    EXPECT_EQ(300u, chain[0]);
    EXPECT_EQ(200u, chain[1]);
    EXPECT_EQ(100u, chain[2]);

    // Every visited entry must KEEP its pre-walk state: the earlier EDGE demotion made
    // resolved-path holders invisible to the rotation collectors (which select EXPANDED entries),
    // so later leak instances behind a changed holder were never re-discovered.
    for (jlong tag = 1; tag <= 2; tag++) {
        FrontierEntry entry{};
        ASSERT_TRUE(table.lookup(tag, &entry));
        EXPECT_EQ(FrontierEntryState::FRONTIER, entry.state);
    }
    FrontierEntry entry{};
    ASSERT_TRUE(table.lookup(3, &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state);
}

TEST(FrontierTableTest, ReconstructChainOfNeverInsertedTagFails) {
    FrontierTable table(64);
    std::vector<u32> chain;
    EXPECT_FALSE(table.reconstructChain(1, &chain));
}

// Heap-walk engine (ReferenceChainTracker::runPass()/

