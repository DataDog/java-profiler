---
id: find-leak-tag-pool-implementation
type: finding
status: implemented-round2-unverified
depends_on: [find-holistic-design-issues]
supersedes: []
related: [find-holistic-design-issues, find-marker-tag-slot-index-mismatch, find-candidate1-never-tagged, q-coverage-tracking-per-combination]
tags: [fix, design, referenceChains, livenessTracker, leak-tag, correlation, adaptive-cpu, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# Leak tag pool implementation (design A-D)

Implements the approved design addressing all four problems from
find-holistic-design-issues. Commits: `294f09ff3`, `0b05d5f85` (TEMP),
`8e3f7584a`, `1ce2b4f03`.

## A) Direct leak tagging (replaces marker tags)

- `LivenessTracker` owns a pool of 256 tags in range
  `[LEAK_TAG_BASE=0x40000000, LEAK_TAG_BASE+256)`, free-list +
  `LeakTagInfo {call_trace_id, tid}` side table per tag.
- `tagLeakInstances(jvmti, klass_ids, count)` scans `_table`, matches
  `cached_klass_id` against candidate klass_ids, acquires a tag,
  `SetTag`s every tracked instance of candidate classes.
- Tags returned to pool in `cleanup_table` when jweak is dead
  (reusable pool — user requirement, running out unlikely).
- `pollWatchedTargets` no longer mints marker tags
  (`MARKER_TAG_BASE - slot`) on representatives. Candidate slots
  still track klass_ids (`_candidate_tags[slot] = 0`), then
  `tagLeakInstances` tags ALL tracked instances.
- `heapReferenceCallback` intercepts leak tags (`isLeakTag(*tag_ptr)`)
  BEFORE the `*tag_ptr == 0` check: converts to frontier tag via
  `nextTag()`, inserts into frontier storing `leak_tag` in
  `FrontierEntry`, replaces `*tag_ptr`, auto-marks for candidate
  bookkeeping.
- Old marker-tag decode in heapReferenceCallback still exists
  (`tag <= MARKER_TAG_BASE`) but is now unused — may be dead code.

## B) Chain filtering

- Depth==0 discovered-instance chains (no holder path) are filtered
  in the pollWatchedTargets discovered loop (`event._depth == 0`).
- IMPORTANT placement lesson: the filter must NOT live in
  `buildChainEvent` itself — gtests (`EmitsEventForAlreadyDiscoveredCandidate`,
  `NoDuplicateOnRepeatPoll`, `ChainPersistsAfterRepresentativeDies`)
  and the canary path legitimately build depth==0 chains. Moving the
  filter into buildChainEvent broke 3 tests; fixed by filtering only
  in the discovered-instance path.

## C) Correlation via leak tag

- `ReferenceChainEvent.targetTag` = `FrontierEntry::leak_tag` when
  nonzero, else frontier tag (buildChainEvent).
- `ObjectLivenessEvent` gained `int64_t leak_tag` (NOTE: `jlong` does
  NOT work in event.h — no jni.h in TUs that include it; commit
  `8e3f7584a`), `flush_table` copies it, `recordHeapLiveObject`
  writes it, `datadog.HeapLiveObject` JFR metadata has `leakTag`
  (T_LONG, F_UNSIGNED).
- Backend joins ReferenceChain.targetTag == HeapLiveObject.leakTag.

## D) Adaptive CPU budget

- Multipliers: 100x emergency (canary_active AND
  `_passes_since_last_progress >= CANARY_NO_PROGRESS_PASS_LIMIT`),
  15x uncovered-but-progressing, 1x all covered.
- Coverage: `_leak_tags_assigned` (set from tagLeakInstances return),
  `_leak_tags_resolved` (incremented when chain cached with
  target_tag >= LEAK_TAG_BASE). Both reset in restartSearch and the
  second reset path.
- TEMP (commit `0b05d5f85`): `CANARY_NO_PROGRESS_PASS_LIMIT` 30 → 3
  for faster testing. **MUST REVERT before finalizing.**

## Lessons

- event.h is included from TUs without jni.h — JNI types unusable
  there (`jlong` → `int64_t`).
- `INT_MAX` needs `<climits>` in referenceChains.h.
- Edit-tool brace accounting: inserting a block inside an `if` produced
  an extraneous `}` that closed the function early — caught only by
  the remote Linux build (macOS-built fine earlier because the bad
  block was inside a `#if 0`-style path? No — actually the compile
  errors were in the pushed commit that had NOT been built locally;
  lesson: always build locally before pushing, even "trivial" edits).

## Round 2 fixes (commit 0db70994d) — from on-pod round 1 failures

- HeapLiveObject.leakTag field-order alignment
  (find-leaktag-jfr-field-misalignment).
- AIMD batch sizing + per-iteration deadline check in expandFrontier
  (find-ema-batch-collapse).
- tagLeakInstances tags by per-tid age-diversity priority (user-directed:
  "the leaking ones have the clearest surviving age diversity, they
  should be tagged first").
- Emergency keys on candidate progress, marker re-tag removed,
  interception TEST_LOG added.
- Tests: 3 pool tests (livenessTracker_ut), AIMD decrease/increase,
  leak-tag interception + correlation (referenceChains_ut). All pass.

## Unverified on-pod

Everything awaits hotdog redeploy verification:
- chains emitted only for actual leaking 78MB [B objects
- targetTag == HeapLiveObject.leakTag correlation works
- no depth==0 noise
- adaptive multiplier drops to 1x once covered
