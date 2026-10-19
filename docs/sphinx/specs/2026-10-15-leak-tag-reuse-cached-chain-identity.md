# Spec: Leak-tag ownership-period identity for cached chains, and launcher reader join

This spec covers the PR-800 change requests `4282599797` (leak-tag reuse in the cached-chain
lookup) and `4282599807` (join the stdout/stderr readers before `launch()` returns).

The design is in `.sphinx/address/design.md`. It converged after 2 adversary rounds. Its "Cluster
Rules & Invariants" section (A-R1..A-R10, B-R1..B-R4) is the normative source of truth for this
spec.

## Problem

- **Stale chain attributed to a new object (seam).**
  `ReferenceChainTracker::resolvedChainTargetTagForTest()` (`referenceChainEvents.cpp:513-531`)
  answers a leak-tag query with `object_tag` whenever any cached chain has
  `_target_tag == object_tag`.
  - Leak tags are recycled. `cleanup_table()` releases the tag when its object dies
    (`livenessTracker.cpp:343-345`), and `acquireLeakTag()` hands it out again in LIFO order.
  - Cached chains are not invalidated when their target dies.
  - So the seam can match a dead object's chain against a new object that now holds the same tag.
  - The code comment and the header doc both claim that tag equality is exact object identity.
- **The same mix-up in emitted events (sibling, production).** `drainPendingChainEvents()`
  re-emits every cached chain in every dump, including chains whose leak-tagged target has died.
  - A consumer joins `ReferenceChain.targetTag` to `HeapLiveObject.leakTag`. That join attributes
    the dead object's chain to the tag's new owner.
  - `StaticFieldGrowingCollectionScenario.findMatch()` can also match the stale chain.
- **Launcher returns before its readers finish.** `AbstractProcessProfilerTest.launch()` returns
  after `p.waitFor()` without joining the stdout/stderr reader threads. Callback side effects, such
  as the marker flags the reference-chain tests assert on, can be incomplete or not yet visible
  when `launch()` returns.

## Correct behaviour

1. **R-STAMP (A-R2).**
   - `LivenessTracker` keeps a `u32` ownership-period stamp for every leak-tag slot.
   - The stamp changes, under `_leak_tag_pool_lock`, on every ownership transition of the slot:
     - `acquireLeakTag()` takes the slot (free → in use);
     - `releaseLeakTag()` actually releases it (in use → free);
     - `start()`'s ownership rebuild or `leakTagPoolResetForTest()` flips the slot's in-use bit.
   - Rejected and out-of-range releases, and rebuilds that leave a slot's ownership unchanged, do
     not change the stamp.
   - `u32 leakTagIncarnation(jlong tag) const` reads the stamp lock-free with acquire semantics.
     It returns 0 for a tag outside the pool range.
2. **R-CAPTURE (A-R3).**
   - Every production site that binds a leak tag to a frontier entry stores the current stamp with
     it, in `FrontierEntry::leak_tag_incarnation`. The sites are the edge interception in
     `heapReferenceCallback`, the root interception in `heapRootCallback`, and
     `correlateAdmittedLeakTag`.
   - `FrontierTable::setLeakTag` takes the stamp as a required argument with no default.
   - `insert()` zeroes the stamp.
3. **R-PROPAGATE (A-R4).** `buildChainEvent()` copies the entry's stamp into a new in-memory field,
   `ReferenceChainEvent::_leak_tag_incarnation`. That field defaults to 0. It is serialized as
   `ReferenceChain.leakTagIncarnation`, and `flush_table()` writes the owner's stamp as
   `HeapLiveObject.leakTagIncarnation`, so consumers join on `(tag, leakTagIncarnation)`: the tag
   alone is only unambiguous within one chunk.
4. **R-OWNER (A-R5).** A cached chain describes the current owner of its leak tag if and only if
   both of these hold:
   - `isLeakTag(_target_tag)`;
   - `_leak_tag_incarnation == LivenessTracker::instance()->leakTagIncarnation(_target_tag)`.

   One private helper implements this predicate, and both the seam and emission use it.
5. **R-SEAM (A-R6).** For a leak tag `L`, `resolvedChainTargetTagForTest(L)` returns `L` only if
   some cached chain satisfies R-OWNER for `L`. Otherwise it returns 0.
   - Search generation does not matter: the same owner's chain from an earlier generation still
     matches.
   - The frontier-tag path, the `<= 0` guard and the lock order are unchanged.
6. **R-EMIT (A-R7).** `drainPendingChainEvents()` does not emit a cached chain that has a leak-tag
   target and fails R-OWNER.
   - It erases that chain under `_resolved_chains_lock`: stamps only advance, so the mismatch is
     permanent. `cacheResolvedChain()` also refuses to cache such a chain.
   - Every other chain is emitted exactly as before.
7. **R-JOIN (B-R2/B-R3).** On both exit paths of `launch()` (in-time exit, and timeout followed by
   forced destroy), the method joins `stdoutReader` and `stderrReader` before it returns.
   - Each join is bounded by a named constant (10 s per reader).
   - When the bound expires, `launch()` returns as before.
   - `LaunchResult` and the `[ready]`/STOP handshake are unchanged.
8. **R-DOC.** Each of these documents its contract as "identity = (leak tag, ownership-period
   stamp)" and no longer claims "exact object identity":
   - the seam's in-body comment;
   - the `referenceChains.h` seam doc;
   - the `drainPendingChainEvents()` header doc;
   - the `JavaProfiler.getReferenceChainResolvedTargetTagForTest0` Javadoc.

## Constraints

- The JFR format and metadata are unchanged. `flightRecorder.cpp` is not touched.
- `sizeof(FrontierEntry)` stays the same. Put the new `u32` directly after `u8 state` and add a
  `static_assert` on the size.
- Heap callbacks add exactly one lock-free atomic load per leak-tag interception. They add no lock
  and no allocation.
- The emission filter adds only lock-free loads under `_resolved_chains_lock`.
- No new lock-order edges. `_leak_tag_pool_lock` stays a leaf lock. Do not take
  `_leak_tag_pool_lock` from reference-chain code.
- `improveChain()` and `reparentToDurableRoot()` must not touch the stamp. The stamp moves together
  with `leak_tag`, and only `insert()`/`setLeakTag()` write it.
- Java: no signature changes to `launch(...)`/`LaunchResult`. Formatting goes through spotless.
- C++ style follows the existing two-space indentation and comments of roughly 100 columns.

## Scope

### Primary fixes

- `ddprof-lib/src/main/cpp/referenceChainEvents.cpp:526` (`4282599797`).
  - Defect class: identity by a recycled numeric key without an ownership-period check (ABA).
  - Fix:
    - add the stamp array and accessor in `livenessTracker.{h,cpp}`, bumping the stamp in acquire,
      release, `start()`'s rebuild and the test reset;
    - add `FrontierEntry::leak_tag_incarnation` and change `setLeakTag`'s signature in
      `referenceChainFrontier.{h,cpp}`;
    - capture the stamp at the three binding sites (`referenceChainWalk.cpp:299`,
      `referenceChainTraversal.cpp:94`, `referenceChainEvents.cpp:782`);
    - add the event field `u32 _leak_tag_incarnation` to `ReferenceChainEvent`
      (`event.h:136`, initialized to 0 in the constructor) and fill it in `buildChainEvent`;
    - add the owner predicate and apply it in the seam;
    - update the docs (`referenceChains.h`, `JavaProfiler.java:685-691`).
- `ddprof-test/src/test/java/com/datadoghq/profiler/AbstractProcessProfilerTest.java:144`
  (`4282599807`).
  - Defect class: an asynchronous output consumer is not joined before the result is returned.
  - Fix: do a bounded join of both reader threads after the wait/destroy block, on both paths.

### Auto-expanded sibling fixes

- `ddprof-lib/src/main/cpp/referenceChainEvents.cpp:792-812`, `drainPendingChainEvents()`.
  - Same ABA class, on the production emission path.
  - Without this fix, the scenario-level identity assertion the reviewer named still matches the
    stale chain.
  - Apply the R-OWNER skip without erasing (R-EMIT).

The following candidates were considered and rejected because they are class signals, not
identity:

- `leak_tag != 0` checks in `buildDiscoveredInstanceChains` coverage accounting
  (`referenceChainEvents.cpp:679-690`);
- anchor-tier checks (`referenceChainAnchors.cpp:161,211`);
- noise eviction (`referenceChainEvents.cpp:742`);
- `tagLeakInstances`' `existing >= LEAK_TAG_BASE` branch, which compares an object with itself.

Frontier-tag ABA is already guarded by `source_search_ns`.

No launcher siblings: `waitFor(` appears only in `AbstractProcessProfilerTest`, and every
child-process test goes through that one `launch()`.

## Test plan (tester owns test edits)

- `livenessTracker_ut.cpp` `LeakTagPoolTest`:
  - the stamp changes on acquire and on release;
  - the stamp is unchanged after a rejected double release and after out-of-range releases;
  - after release and re-acquire of the same tag (LIFO), the stamp differs from the first
    ownership's;
  - `leakTagIncarnation()` returns 0 out of range.
- `referenceChainsTrackerTests.inc` `ResolvedChainCacheTest`. Use `makeEvent` with a leak-range
  target, set `_leak_tag_incarnation`, and drive the pool through the `LivenessTracker` test
  accessors:
  - (a) a chain whose stamp equals the current stamp is returned by the seam for `L` and emitted
    by `drain`;
  - (b) after `acquire` + `release` (+ re-`acquire`) of `L`, the same cached chain is rejected by
    the seam (0) and is absent from `drain`, and the drain evicts it (`resolvedChainCount()` drops);
  - (c) the seam still matches across a search-generation change when the stamp is unchanged;
  - (d) chains with a frontier-tag target are emitted regardless of pool state.

  Reset the pool in SetUp/TearDown so the stamp state stays isolated between tests.
- `referenceChainsEventTests.inc:361,367`: update the direct `setLeakTag` calls to pass the current
  stamp. `CorrelateAdmittedLeakTagSetsEntryAndDiscovers`: assert that the entry's stamp equals
  `leakTagIncarnation(kLeakTag)`.
- Java: the existing `ExternalProcessReferenceChainTest`/`JavaProfilerTest` runs are the regression
  check for R-JOIN. No new Java test is needed beyond these runs: the race cannot be forced
  deterministically.
- Verification: `./gradlew :ddprof-lib:gtestDebug` (or the per-binary targets for
  `livenessTracker_ut` and `referenceChains_ut`), the debug Java test build for the reference-chain
  tests, and `spotlessCheck`.

## Assumptions

- (≥90%) Lifetime-aware identity, rather than cache invalidation, is the minimal correct fix. An
  invalidated chain would be rebuilt from the dead object's frontier entry on the next poll.
- (≥90%) Not emitting chains whose leak-tag owner is gone matches the documented "live sample"
  contract of `_resolved_chains`. Such a target has no `HeapLiveObject` to correlate with.
- (≥90%) `releaseLeakTag()` runs only for dead rows (`livenessTracker.cpp:338-346`; there is no
  live-row eviction release). So at binding sites (a) and (b), a live object carrying `L` implies
  that its row owns `L` now.
- (≥90%) No reference-chain gtest acquires pool tags (only `leakTagPoolResetForTest()` at
  `referenceChainsPodTests.inc:42`). So the existing drain and seam expectations hold with stamp 0.
- Residual: the u32 stamp wraps after 2^32 transitions of one slot. This is accepted and
  documented at the field.
- Residual: if a pipe-holding descendant outlives the 10 s bound, the reader join gives up and the
  original race window remains (best effort).
