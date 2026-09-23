/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

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

// VMTestAccessor - friend of VM (vmEntry.h), lets tests swap VM::_jvmti for a
class VMTestAccessor {
public:
    static jvmtiEnv* getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
};

// ReferenceChainsTestAccessor - same pattern as VMTestAccessor above, for the
class ReferenceChainsTestAccessor {
public:
    static void reset() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        delete t->_frontier;
        t->_frontier = nullptr;
        t->_class_tags = ClassTagTable();
        t->_last_resolved_class_count = 0;
        // Without these two, a prior test's fully-swept (or partially-swept)
        // admitStaticFieldRoots() state survives in this process-wide singleton and can wrongly
        // skip the sweep entirely on this test's first pass if its resolved class count happens to
        // match whatever an earlier test last left behind - see resetForRestart()'s identical reset
        // of these same fields for the production-restart equivalent of this same contract.
        t->_last_static_field_class_count = -1;
        t->_static_field_sweep_cursor = 0;
        t->_static_field_sweep_cycle_truncated = false;
        t->_next_tag = 1;
        // Shared with LivenessTracker (classTagAllocator.h) - process-wide, not
        // per-ReferenceChainTracker-instance, so it needs its own reset seam rather than being a
        // plain member write.
        ClassTagAllocator::resetForTest();
        t->_search_started = false;
        t->_tags_released = true;
        t->_search_state = SearchState::RUNNING;
        t->_abandon_reason = SearchAbandonReason::NONE;
        t->_search_start_ns = 0;
        t->_pending_expand.clear();
        t->_priority_expand.clear();
        t->_priority_expand_set.clear();
        // B' at-risk FIFO + its indexes/counters, and the round-15 fresh lane: production clears
        // all of these on every restartSearch()/ resetSearchStateForTest(), but this seam predates
        // the FIFO and was never given the clears - until round 16 a test left at-risk entries
        // behind and only survived because LATER tests' own runPass()s drained the residue with the
        // full Bfs mock.
        t->_static_anchor_fifo.clear();
        t->_static_anchor_fifo_set.clear();
        t->_static_anchor_fifo_klass_counts.clear();
        t->_static_anchor_fresh_queue.clear();
        t->_last_pass_gc_finish_epoch = 0;
        t->_last_pass_ns = 0;
        t->_passes_run = 0;
        t->_passes_since_last_progress = 0;
        t->_candidate_count = 0;
        t->_candidate_found_bits = 0;
        memset(t->_candidate_discovered_count, 0, sizeof(t->_candidate_discovered_count));
        t->_passes_since_last_candidate_progress = 0;
        t->_last_candidate_progress_mark = 0;
        t->_canary_stuck_restart_count = 0;
        t->_resolved_chains.clear();
        t->_safepoint_pain_budget = PainBudget();
        t->_cpu_pain_budget = PainBudget();
        t->_search_pain_ms = 0;
        t->_root_kind_rotation_cursor = 1;
        t->_stale_expanded_rotation_cursor = 1;
        t->_static_anchor_index.clear();
        t->_static_anchor_own_class_tags.clear();
        t->_static_anchor_index_tags.clear();
        t->_anchor_container_cursor = 0;
        t->_anchor_other_cursor = 0;
        t->_class_shape_cache.clear();
        t->_thread_walk_anchor_cursor = 0;
        memset(t->_candidate_qualifying_tid_count, 0,
               sizeof(t->_candidate_qualifying_tid_count));
        t->_hop_label_cache.clear();
        t->_watched_leak_klass_count = 0;
        t->_leak_signature_totals.clear();
        t->_leak_signature_prev_totals.clear();
        t->_leak_parent_fanout.clear();
        t->_borrowed_budget = 0;
        t->_consecutive_under_target_passes = 0;
        // Adaptive batch + lane state: NOT covered by anything above, and a prior test that drove
        // expansion leaves a non-zero EMA, a live batch size, a stale pass deadline, and/or a
        // mid-alternation lane toggle behind - all of which silently change the next test's
        // expandFrontier() arithmetic (exact-value asserts on batch sizing only pass standalone
        // otherwise).
        t->_gotw_ema_call_ns = 0;
        t->_gotw_batch_size = 0;
        t->_pass_deadline_ns = 0;
        t->_expand_lane_prefer_priority = true;
    }

    // Search restart + pain budget (SearchRestartTest below) - same rationale as the pacing
    // accessors above: private state a test needs to drive/observe directly.
    static bool canAffordNewSearch(u64 now_ns) {
        return ReferenceChainTracker::instance()->canAffordNewSearch(now_ns);
    }

    static bool shouldRunPass(u64 now_ns) {
        return ReferenceChainTracker::instance()->shouldRunPass(now_ns);
    }

    static void setSearchPainMs(u64 ms) {
        ReferenceChainTracker::instance()->_search_pain_ms = ms;
    }

    static void setCandidateFrontierTagForTest(int idx, jlong tag) {
        ReferenceChainTracker::instance()->setCandidateFrontierTagForTest(idx, tag);
    }

    static void setCandidateCountForTest(int n) {
        ReferenceChainTracker::instance()->setCandidateCountForTest(n);
    }

    // Canary-lane backoff state wrappers - see _canary_backoff_mult's own comment
    // (referenceChains.h).
    static int canaryBackoffMult() {
        return ReferenceChainTracker::instance()->canaryBackoffMultForTest();
    }
    static u64 lastCanaryPassNs() {
        return ReferenceChainTracker::instance()->lastCanaryPassNsForTest();
    }
    static void setCanaryBackoffForTest(int mult, u64 ema_ms, u64 last_pass_ns) {
        ReferenceChainTracker::instance()->setCanaryBackoffForTest(mult, ema_ms,
                                                                   last_pass_ns);
    }
    static void setOomRampActive(bool active) {
        ReferenceChainTracker::instance()->setOomRampActiveForTest(active);
    }

    static int passesSinceLastCandidateProgress() {
        return ReferenceChainTracker::instance()->passesSinceLastCandidateProgressForTest();
    }

    static int canaryStuckRestartCount() {
        return ReferenceChainTracker::instance()->canaryStuckRestartCountForTest();
    }

    static u64 searchPainMs() {
        return ReferenceChainTracker::instance()->_search_pain_ms;
    }

    // Resolved-chain cache: read-only size peek and a pass-through to the private snapshot
    // (drainPendingChainEvents()) and insert (cacheResolvedChain()), for ResolvedChainCacheTest
    // below - same rationale as hasResolvedChainForTag()/resolvedChainCount() below.
    static size_t resolvedChainCount() {
        return ReferenceChainTracker::instance()->_resolved_chains.size();
    }

    static void drain(std::vector<ReferenceChainEvent> *out) {
        ReferenceChainTracker::instance()->drainPendingChainEvents(out);
    }

    static void cacheChain(jlong source_tag, ReferenceChainEvent event,
                           jlong source_tag_val, u64 source_search_ns) {
        ReferenceChainTracker::instance()->cacheResolvedChain(
            source_tag, std::move(event), source_tag_val, source_search_ns);
    }

    static int maxResolvedChains() {
        return ReferenceChainTracker::MAX_RESOLVED_CHAINS;
    }

    // Target-selection bridging step: read-only peeks into the resolved-chain cache, for asserting
    // exactly which klass a chain was resolved for and the tag it was reconstructed from - see
    // PollWatchedTargetsTest below.
    static bool hasResolvedChainForTag(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return t->_resolved_chains.find(tag) != t->_resolved_chains.end();
    }

    static jlong resolvedChainSourceTag(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        auto it = t->_resolved_chains.find(tag);
        return it == t->_resolved_chains.end() ? 0 : it->second.source_tag;
    }

    // Leak-tag correlation (design C): read a frontier entry's stored leak tag, and a pass-through
    // to the private buildChainEvent(), for LeakTagInterceptionTest below - same friend-accessor
    // rationale as hasResolvedChainForTag() above.
    static jlong frontierLeakTag(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        FrontierEntry entry{};
        if (t->_frontier == nullptr || !t->_frontier->lookup(tag, &entry)) {
            return -1;
        }
        return entry.leak_tag;
    }

    static void setCandidateKlassIdForTest(int idx, u32 klass_id) {
        ReferenceChainTracker::instance()->setCandidateKlassIdForTest(idx, klass_id);
    }

    // Round-19: the leak-tag canary found criterion (pod 289f8 — the chase was structurally
    // unresolvable after the marker->leak-tag migration; see buildDiscoveredInstanceChains' own
    // comment).
    static u64 candidateFoundBitsForTest() {
        return ReferenceChainTracker::instance()->_candidate_found_bits;
    }

    static jlong candidateFrontierTagForTest(int slot) {
        return ReferenceChainTracker::instance()->_candidate_frontier_tags[slot];
    }

    static void buildDiscoveredInstanceChainsForTest(u32 klass_id,
                                                       u64 current_search_ns) {
        // jvmti/jni null is safe: resolveHopEdgeLabel() null-guards and degrades hop labels to kind
        // labels.
        ReferenceChainTracker::instance()->buildDiscoveredInstanceChains(
            nullptr, nullptr, klass_id, current_search_ns);
    }

    // ---- pod-in-a-jar system harness (design-pod-in-a-jar-harness) ----
    static u8 searchStateForTest() {
        return ReferenceChainTracker::instance()->_search_state;
    }

    static int sweepGateResolvedCountForTest() {
        return ReferenceChainTracker::instance()->_last_resolved_class_count;
    }

    static int sweepGateStaticCountForTest() {
        return ReferenceChainTracker::instance()->_last_static_field_class_count;
    }

    static int sweepCursorForTest() {
        return ReferenceChainTracker::instance()->_static_field_sweep_cursor;
    }

    static int passesRunForTest() {
        return ReferenceChainTracker::instance()->_passes_run;
    }

    static int candidateCountForTest() {
        return ReferenceChainTracker::instance()->_candidate_count;
    }

    static u32 candidateKlassIdForTest(int slot) {
        return ReferenceChainTracker::instance()->_candidate_klass_ids[slot];
    }

    static size_t resolvedChainCountForTest() {
        return ReferenceChainTracker::instance()->_resolved_chains.size();
    }

    static std::vector<u64> resolvedChainTargetsForTest() {
        std::vector<u64> out;
        for (auto &kv :
             ReferenceChainTracker::instance()->_resolved_chains) {
            out.push_back(kv.second.event._target_tag);
        }
        return out;
    }

    static size_t staticAnchorFreshQueueSizeForTest() {
        return ReferenceChainTracker::instance()
            ->_static_anchor_fresh_queue.size();
    }

    static jlong candidateDiscoveredTagForTest(int slot, int idx) {
        return ReferenceChainTracker::instance()->candidateDiscoveredTagForTest(slot, idx);
    }

    static int candidateDiscoveredCountForTest(int slot) {
        return ReferenceChainTracker::instance()->candidateDiscoveredCountForTest(slot);
    }

    // recordDiscoveredInstance()/correlateAdmittedLeakTag() are the production paths for the
    // leak-correlation tests below.
    static void recordDiscoveredInstanceForTest(u32 klass_id, jlong tag,
                                                 bool leak_correlated) {
        ReferenceChainTracker::instance()->recordDiscoveredInstance(klass_id, tag,
                                                                   leak_correlated);
    }

    // Drive restartSearch() directly (the accessor base already set _tags_released, so its assert
    // is satisfied).
    static void restartSearchForTest() {
        ReferenceChainTracker::instance()->restartSearch();
    }

    static bool anchorIndexIsEmptyForTest() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return t->_static_anchor_index.empty() &&
               t->_static_anchor_own_class_tags.empty() &&
               t->_static_anchor_index_tags.empty();
    }

    // Read back discovered-instance slots (frontier tags recorded by recordDiscoveredInstance).
    static jlong discoveredTagForTest(int slot, int idx) {
        return ReferenceChainTracker::instance()
            ->_candidate_discovered_tags[slot][idx];
    }

    static int discoveredCountForTest(int slot) {
        return ReferenceChainTracker::instance()
            ->_candidate_discovered_count[slot];
    }

    static size_t priorityExpandCap() {
        return ReferenceChainTracker::PRIORITY_EXPAND_CAP;
    }

    static int maxDiscoveredPerClass() {
        return ReferenceChainTracker::MAX_DISCOVERED_INSTANCES_PER_CLASS;
    }

    static bool buildChainEventForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                      jlong tag, ReferenceChainEvent *out) {
        return ReferenceChainTracker::instance()->buildChainEvent(jvmti, jni,
                                                                   tag, out);
    }

    // Direct expandFrontier() drive for the AIMD batch test: a full runPass() drains a small graph
    // to completion and its rotation phase adds extra GetObjectsWithTags calls, so per-call AIMD
    // assertions cannot be made deterministic through runPass().
    static void pushPendingExpandForTest(jlong tag) {
        ReferenceChainTracker::instance()->_pending_expand.push_back(tag);
    }

    static void expandFrontierForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                      int *edges_admitted) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        bool truncated = false;
        bool cap_hit = false;
        u64 safepoint_ticks = 0;
        t->expandFrontier(jvmti, jni, t->_hop_cap, 1000, edges_admitted,
                          &truncated, &cap_hit, &safepoint_ticks);
    }

    // Pause-time pacing controller: read-only peeks at the controller's derived values, and a
    // pass-through to the private updatePacing() itself, for ReferenceChainsPacingTest below - same
    // rationale as hasResolvedChainForTag()/resolvedChainCount() above (the target-selection
    // bridging step): private state a test needs to drive/ observe directly, exposed via this
    // existing friend accessor rather than adding public getters/setters to ReferenceChainTracker
    // itself.
    static int effectiveBudget() {
        return ReferenceChainTracker::instance()->_effective_budget;
    }

    static u64 effectiveCadenceNs() {
        return ReferenceChainTracker::instance()->_effective_cadence_ns;
    }

    static void updatePacing(u64 pass_wall_ns) {
        ReferenceChainTracker::instance()->updatePacing(pass_wall_ns);
    }

    static u64 baselineCadenceNs() { return ReferenceChainTracker::PASS_CADENCE_NS; }

    // Test-only seams for PacingGrowsBudgetBackAndRelaxesCadenceWhenUnderCeiling below, which needs
    // to start from a controlled below-ceiling/above- baseline point with a freshly reset
    // controller (see that test's own comment for why chaining directly off a prior constant-input
    // sequence would leave _pause_pid's integral state mid-recovery from that sequence's windup,
    // muddying this method's per-step direction assertions with a transient the test is not about).
    static void setEffectiveBudget(int v) {
        ReferenceChainTracker::instance()->_effective_budget = v;
    }

    static void setEffectiveCadenceNs(u64 v) {
        ReferenceChainTracker::instance()->_effective_cadence_ns = v;
    }

    static void resetPacingController() {
        ReferenceChainTracker::instance()->_pause_pid.reset();
    }

    // Budget-borrowing (referenceChains.h's _borrowed_budget comment): the configured multiplier
    // PacingGrowsBudgetBackAndRelaxesCadenceWhenUnderCeiling below asserts convergence against,
    // instead of hardcoding it a second time in the test itself.
    static int borrowCeilingMultiplier() {
        return ReferenceChainTracker::BORROW_CEILING_MULTIPLIER;
    }

    static int64_t borrowedBudget() {
        return ReferenceChainTracker::instance()->_borrowed_budget;
    }

    // MaybeRevokeBorrowForRootEnumPass* tests below: drive the borrow state directly into "already
    // granted" before exercising the revocation-only seam, and a pass-through to that seam itself -
    // same rationale as updatePacing()'s own accessor above.
    static void setBorrowedBudget(int64_t v) {
        ReferenceChainTracker::instance()->_borrowed_budget = v;
    }

    static int consecutiveUnderTargetPasses() {
        return ReferenceChainTracker::instance()->_consecutive_under_target_passes;
    }

    static void setConsecutiveUnderTargetPasses(int v) {
        ReferenceChainTracker::instance()->_consecutive_under_target_passes = v;
    }

    static void maybeRevokeBorrowForRootEnumPass(u64 pass_wall_ticks) {
        ReferenceChainTracker::instance()->maybeRevokeBorrowForRootEnumPass(
            pass_wall_ticks);
    }

    // ReleaseSearchTagsFailureTest below: read-only peek at whether the tracker still owes a tag
    // release before it can allow a restart - see _tags_released's own comment.
    static bool tagsReleased() {
        return ReferenceChainTracker::instance()->_tags_released;
    }

    // ResolveLoadedClassesRescansAfterClassCountShrinksAndPartiallyRegrows below: direct
    // pass-through to the private resolveLoadedClasses(), plus a read-only peek at the count it
    // stashes - the same rationale as tagsReleased() above (private state/behavior a test needs to
    // drive/observe directly, without going through a full runPass()/search lifecycle that
    // resolveLoadedClasses() alone does not need).
    static void resolveLoadedClasses(jvmtiEnv *jvmti, JNIEnv *jni) {
        ReferenceChainTracker::instance()->resolveLoadedClasses(jvmti, jni);
    }

    static int lastResolvedClassCount() {
        return ReferenceChainTracker::instance()->_last_resolved_class_count;
    }

    // Durability re-verification test seams: direct pass-throughs to the private tie-break/rotation
    // methods, plus FrontierTable::insert() itself (also private-by-convention here in the sense
    // that production code only ever calls it via admitObject()) so tests can set up a frontier
    // entry's exact starting root_kind/state/parent_tag without needing a live JVMTI mock for
    // IterateOverReachableObjects/FollowReferences (neither is mocked in this file - see the file
    // header's FollowReferences- only mock rationale).
    static bool insertFrontierEntry(FrontierTable *frontier, jlong tag,
                                     jlong parent_tag, u32 depth, u8 state,
                                     u8 root_kind, u32 referrer_klass = 0,
                                     jlong class_tag = 0,
                                     jint referrer_field_index = -1,
                                     u8 edge_kind = 0,
                                     jlong referrer_class_tag = 0) {
        return frontier->insert(tag, parent_tag, referrer_klass, depth,
                                 state, root_kind, class_tag,
                                 referrer_field_index, edge_kind,
                                 referrer_class_tag);
    }

    static bool maybeUpgradeRootAttachedRootKind(FrontierTable *frontier,
                                                  jlong tag,
                                                  u8 new_root_kind) {
        return ReferenceChainTracker::instance()
            ->maybeUpgradeRootAttachedRootKind(frontier, tag, new_root_kind);
    }

    static std::vector<jlong> collectStaleRootKindEntriesForRotation(
        int max_count) {
        return ReferenceChainTracker::instance()
            ->collectStaleRootKindEntriesForRotation(max_count);
    }

    static std::vector<jlong> collectStaleExpandedEntriesForRotation(
        int max_count) {
        return ReferenceChainTracker::instance()
            ->collectStaleExpandedEntriesForRotation(max_count);
    }

    // Candidate-scoped reach (descendFromAnchor()/walkCandidateThreadLocals()/
    // walkStaticFieldAnchors()): direct drives for the same reason as expandFrontierForTest() above
    // - a full runPass() drains a small graph to completion and its other phases add interference,
    // so the walk phases are exercised on their own.
    static void walkCandidateThreadLocalsForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                                 int budget,
                                                 int *edges_admitted) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        bool truncated = false;
        bool cap_hit = false;
        u64 safepoint_ticks = 0;
        t->walkCandidateThreadLocals(jvmti, jni, budget, edges_admitted,
                                     &truncated, &cap_hit, &safepoint_ticks);
    }

    static void walkStaticFieldAnchorsForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                               const std::vector<jlong> &tags,
                                               int budget,
                                               int *edges_admitted) {
        walkStaticAnchorFifoForTest(jvmti, jni, tags, budget, edges_admitted,
                                    nullptr);
    }

    static std::vector<jlong>
    collectStaticFieldAnchorsForRotationForTest(int max_count) {
        return ReferenceChainTracker::instance()
            ->collectStaticFieldAnchorsForRotation(max_count);
    }

    static void addToStaticAnchorIndexForTest(jlong tag, jlong own_class_tag,
                                               u8 root_kind) {
        ReferenceChainTracker::instance()
            ->addToStaticAnchorIndex(tag, own_class_tag, root_kind);
    }

    // Prime the class-shape cache as if reconcileAnchorClassShapes() had classified `class_tag`
    // (tests script shapes instead of driving the JNI interface walk, which needs real classes).
    static void primeClassShapeForTest(jlong class_tag, bool container) {
        ReferenceChainTracker::instance()->_class_shape_cache[class_tag] =
            container
                ? (u8)ReferenceChainTracker::AnchorClassShape::CONTAINER
                : (u8)ReferenceChainTracker::AnchorClassShape::NON_CONTAINER;
    }

    // B' at-risk static-anchor FIFO (see _static_anchor_fifo's declaration comment in
    // referenceChains.h).
    using AtRiskAnchor = ReferenceChainTracker::AtRiskAnchor;
    static constexpr u32 kAtRiskPerKlassCap =
        ReferenceChainTracker::STATIC_ANCHOR_ATRISK_PER_KLASS_CAP;

    static void pushStaticAnchorFifoForTest(jlong tag, u32 klass_id) {
        ReferenceChainTracker::instance()->pushAtRiskStaticAnchor(tag,
                                                                  klass_id);
    }

    static int drainStaticAnchorFifoForTest(
            int max_count,
            std::vector<ReferenceChainTracker::AtRiskAnchor> &out) {
        return ReferenceChainTracker::instance()->drainStaticAnchorFifo(
            max_count, out);
    }

    static void requeueStaticAnchorFifoFrontForTest(
            const std::vector<ReferenceChainTracker::AtRiskAnchor> &entries) {
        ReferenceChainTracker::instance()->requeueStaticAnchorFifoFront(
            entries);
    }

    static size_t staticAnchorFifoSizeForTest() {
        return ReferenceChainTracker::instance()->_static_anchor_fifo.size();
    }

    static bool staticAnchorFifoContainsForTest(jlong tag) {
        return ReferenceChainTracker::instance()
            ->_static_anchor_fifo_set.contains(tag);
    }

    static void walkStaticAnchorFifoForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                             const std::vector<jlong> &tags,
                                             int budget, int *edges_admitted,
                                             std::vector<jlong> *unwalked) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        bool truncated = false;
        bool cap_hit = false;
        u64 safepoint_ticks = 0;
        t->walkStaticFieldAnchors(jvmti, jni, tags, budget, edges_admitted,
                                  &truncated, &cap_hit, &safepoint_ticks,
                                  unwalked);
    }

    // Direct candidate-slot seeding (the production path fills these via pollWatchedTargets()'s
    // snapshot loop - see _candidate_qualifying_tids' own comment): the walk phase tests need
    // exactly one (slot, klass, tid) combination without driving LivenessTracker's hysteresis
    // machinery.
    static void seedCandidateSlotForTest(int slot, u32 klass_id,
                                          const jint *tids, int tid_count) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        t->_candidate_klass_ids[slot] = klass_id;
        for (int i = 0; i < tid_count; i++) {
            t->_candidate_qualifying_tids[slot][i] = tids[i];
        }
        t->_candidate_qualifying_tid_count[slot] = tid_count;
        if (slot + 1 > t->_candidate_count) {
            t->_candidate_count = slot + 1;
        }
    }

    static int candidateQualifyingTidCountForTest(int slot) {
        return ReferenceChainTracker::instance()
            ->_candidate_qualifying_tid_count[slot];
    }

    static jlong getTagForTest(jvmtiEnv *jvmti, jobject obj) {
        return ReferenceChainTracker::instance()->getTag(jvmti, obj);
    }

    // Snapshot of _priority_expand's current contents, in queue order - used by tests to check for
    // duplicate tags after both rotation collectors have run against it within the same simulated
    // pass.
    static std::vector<jlong> priorityExpandContents() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return std::vector<jlong>(t->_priority_expand.begin(),
                                   t->_priority_expand.end());
    }

    // StaleExpandedRotationSkipsPreexistingQueueEntries below: simulates a tag left in
    // _priority_expand by a prior pass's truncated expandFrontier() batch (expandFrontier()'s own
    // "leave the batch at the front of the source queue for a later pass to retry" comment) without
    // driving a full expandFrontier()/JVMTI round-trip to produce one.
    static void pushPriorityExpand(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        t->_priority_expand.push_back(tag);
        t->_priority_expand_set.insert(tag);
    }

    // Simulates expandFrontier() having fully drained _priority_expand at the end of a pass (the
    // common case: rotation's whole selection fit within that pass's rotation_budget slice) - see
    // StaleExpandedRotationStarvesHighTagEntryBehindLowTagPopulation below, which needs this to
    // model collectStaleExpandedEntriesForRotation() being called fresh on each of several
    // simulated passes, the way runPassManualWalk() actually does it once per real pass.
    static void clearPriorityExpand() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        t->_priority_expand.clear();
        t->_priority_expand_set.clear();
    }

    static void setRootKindRotationCursor(jlong tag) {
        ReferenceChainTracker::instance()->_root_kind_rotation_cursor = tag;
    }

    static jlong rootKindRotationCursor() {
        return ReferenceChainTracker::instance()->_root_kind_rotation_cursor;
    }

    static int rootKindRotationBudget() {
        return ReferenceChainTracker::ROOT_KIND_ROTATION_BUDGET;
    }

    static int staleExpandedRotationBudget() {
        return ReferenceChainTracker::STALE_EXPANDED_ROTATION_BUDGET;
    }

    static size_t priorityExpandSize() {
        return ReferenceChainTracker::instance()->_priority_expand.size();
    }

    // Snapshot of _pending_expand's current contents, in queue order - used by the rolling-resume
    // smoke test to verify that a truncated expandFrontier() batch pops fully-processed entries
    // (mark EXPANDED) and leaves only the partially-processed and unvisited entries at the front of
    // the queue for the next pass to retry.
    static std::vector<jlong> pendingExpandContents() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return std::vector<jlong>(t->_pending_expand.begin(),
                                  t->_pending_expand.end());
    }

    static size_t pendingExpandSize() {
        return ReferenceChainTracker::instance()->_pending_expand.size();
    }

    // Self-calibrating adaptive batch size (AIMD): read/write the per-call EMA and live batch size
    // so tests can verify the AIMD dynamics.
    static u64 gotwEmaCallNs() {
        return ReferenceChainTracker::instance()->_gotw_ema_call_ns;
    }

    static void setGotwEmaCallNs(u64 v) {
        ReferenceChainTracker::instance()->_gotw_ema_call_ns = v;
    }

    static size_t gotwBatchSize() {
        return ReferenceChainTracker::instance()->_gotw_batch_size;
    }

    static void setGotwBatchSize(size_t v) {
        ReferenceChainTracker::instance()->_gotw_batch_size = v;
    }

    // Read-only peeks at the batch-control constants (private statics - friendship applies inside
    // this class's methods, not in test bodies).
    static u64 gotwCpuBudgetNs() {
        return ReferenceChainTracker::GOTW_CPU_BUDGET_NS;
    }

    static size_t gotwInitialBatchSize() {
        return (size_t)ReferenceChainTracker::GOTW_INITIAL_BATCH_SIZE;
    }

    static size_t gotwMinBatch() {
        return ReferenceChainTracker::GOTW_MIN_BATCH;
    }

    static size_t gotwMaxBatch() {
        return ReferenceChainTracker::GOTW_MAX_BATCH;
    }

    static size_t gotwBacklogMinDepth() {
        return ReferenceChainTracker::GOTW_BACKLOG_MIN_DEPTH;
    }

    static u64 gotwBacklogWindowMult() {
        return ReferenceChainTracker::GOTW_BACKLOG_WINDOW_MULT;
    }

    // gotwWindowNs() is a pure function of (remaining window, lane depth) and the seeded EMA -
    // directly unit-testable without a mock JVMTI call.
    static u64 gotwWindowNs(u64 remaining_ns, size_t lane_depth) {
        return ReferenceChainTracker::instance()->gotwWindowNs(remaining_ns,
                                                                lane_depth);
    }

    static void setPassDeadlineNs(u64 v) {
        ReferenceChainTracker::instance()->_pass_deadline_ns = v;
    }

    static bool expandLanePreferPriority() {
        return ReferenceChainTracker::instance()->_expand_lane_prefer_priority;
    }

    // Leak-tag pool range base (private static) - same friend-access rationale as the AIMD
    // constants above.
    static jlong leakTagBase() {
        return ReferenceChainTracker::LEAK_TAG_BASE;
    }

    // Leak-accumulation rotation test seams (collectLeakAccumulationCandidatesForRotation()).
    static void setWatchedLeakKlassIdsForTest(const std::vector<u32> &ids) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        int n = (int)std::min(ids.size(),
                               (size_t)ReferenceChainTracker::MAX_WATCHED_LEAK_KLASSES);
        for (int i = 0; i < n; i++) {
            t->_watched_leak_klass_ids[i] = ids[i];
        }
        t->_watched_leak_klass_count = n;
    }

    static void trackLeakAccumulation(FrontierTable *frontier, u32 referrer_klass,
                                       jlong parent_tag, jlong tag) {
        ReferenceChainTracker::instance()->trackLeakAccumulation(
            frontier, referrer_klass, parent_tag, tag);
    }

    static std::vector<jlong> collectLeakAccumulationCandidatesForRotation(
        int max_count) {
        return ReferenceChainTracker::instance()
            ->collectLeakAccumulationCandidatesForRotation(max_count);
    }

    static int leakAccumulationRotationBudget() {
        return ReferenceChainTracker::LEAK_ACCUMULATION_ROTATION_BUDGET;
    }

    static u32 leakSignatureTotal(u32 leaf_klass_id, u32 parent_class_id) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        u64 key = t->leakSignatureKey(leaf_klass_id, parent_class_id);
        auto it = t->_leak_signature_totals.find(key);
        return it != t->_leak_signature_totals.end() ? it->second : 0;
    }

    static u32 leakParentFanout(jlong parent_tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        auto it = t->_leak_parent_fanout.find(parent_tag);
        return it != t->_leak_parent_fanout.end() ? it->second.fanout : 0;
    }

    static size_t leakSignatureCount() {
        return ReferenceChainTracker::instance()->_leak_signature_totals.size();
    }

    static void seedLeakAccumulationForNewlyWatchedKlass(u32 klass_id) {
        ReferenceChainTracker::instance()
            ->seedLeakAccumulationForNewlyWatchedKlass(klass_id);
    }
};

static jvmtiError JNICALL mock_SetEventNotificationMode(jvmtiEnv *, jvmtiEventMode,
                                                         jvmtiEvent, jthread, ...) {
    return JVMTI_ERROR_NONE;
}

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

