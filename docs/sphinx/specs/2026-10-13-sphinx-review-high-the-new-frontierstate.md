# Spec: Reference-chain test seams — locking, contract docs, scenario predicate and JDK-8 args

This spec covers PR-800 change requests F-91f3cc84a25e, F-17cff193f8ed, F-054807ffb76e, F-3b9270c81830, F-b2e5089803c3 and F-32af0fcc0ab2.

The design is in `.sphinx/address/design.md`. Its "Cluster Rules & Invariants" section is the normative source of truth for this spec.

## Problem

The PR added two native test seams. Java test scenarios use them to stay in step with the reference-chain BFS engine.

- `ReferenceChainTracker::frontierStateForTest()` reads `_frontier` without `_engine_lock`. Every other engine-state seam takes that lock, so this seam can see a pass or a restart while it is only partly done (F-91f3cc84a25e). Its guard and sentinel paths have no tests (F-32af0fcc0ab2).
- `ReferenceChainTracker::resolvedChainTargetTagForTest()` samples the search generation (`_search_start_ns`) before it takes any lock. A concurrent `restartSearch()` or new `runPass()` can then change the generation between the sample and the comparison against the cached entry. The seam can return a stale chain's target tag (F-17cff193f8ed).
  - The real writers of the generation hold `_engine_lock`, not `_resolved_chains_lock`. Reordering the load relative to `_resolved_chains_lock` alone does not close the window.
- The javadoc and header comment for the frontier-state seam skip state value 2 (EDGE) without explaining why (F-3b9270c81830).
- `StaticFieldGrowingCollectionScenario` enables its seam-based synchronization only when the config is `"debug"`. The seams are also compiled into asan and tsan builds, so the strongest race-prevention path never runs on sanitizer CI (F-b2e5089803c3).
- `ExternalProcessReferenceChainTest` always passes `--add-opens`. A JDK 8 child JVM rejects that option (F-054807ffb76e).

## Correct behaviour

1. **R-LOCK (seam locking).**
   - `frontierStateForTest(tag)` and `resolvedChainTargetTagForTest(tag)` hold `_engine_lock` for their entire read of engine state. This matches `pendingExpandPositionForTest()` and `pendingExpandSizeForTest()`.
   - If another thread holds `_engine_lock`, a seam call with a valid tag does not return until that thread releases it.
   - The invalid-tag fast path returns the sentinel without locking. Invalid means `tag <= 0`, or a leak tag.
2. **R-ORDER (lock order).**
   - The lock order is `_engine_lock` first, then `_resolved_chains_lock`. This is the same order as the BFS thread (`finishLoopIterationSerialized` → `pollWatchedTargets`, and `cacheResolvedChain`).
   - No path holds `_resolved_chains_lock` while it waits on `_engine_lock`.
   - A seam call that runs concurrently with a lock holder finishes once that holder releases. It never deadlocks.
3. **R-GEN (generation guard).** `resolvedChainTargetTagForTest(tag)` returns the cached `_target_tag` only when all of the following hold. Otherwise it returns 0.
   - `tag > 0`.
   - The tag is not a leak tag.
   - `_search_start_ns != 0`.
   - `cached.source_search_ns == _search_start_ns`, with `_search_start_ns` read while both locks are held.

   If a lock holder changes the generation while a seam call is waiting, the seam call sees the new generation.
4. **R-SENTINEL (frontier-state contract).** `frontierStateForTest(tag)` returns -1 in each of these cases:
   - `tag <= 0`.
   - `tag` is a leak tag.
   - There is no frontier table.
   - There is no entry for `tag`.

   Otherwise it returns the raw `FrontierEntryState`: FRONTIER = 0, EXPANDED = 1, ABANDONED = 3. EDGE = 2 is retired; the production walk never produces it. From Java, an object that has never been tagged reads as -1.
5. **R-BUILD (scenario seam-path predicate).** `StaticFieldGrowingCollectionScenario` takes the seam path (holder-EXPANDED wait, lateChunk identity pinning, untagged-probe check) exactly when `config != null && ("debug".equals(config) || config.endsWith("san"))`. Release builds take the class-only path. The 45 s holder deadline and the 150 s parent launch timeout stay as they are.
6. **R-JDK (child JVM args).** The `leak-static-field` child always receives `-Dddprof_test.config=<config>`. It receives `--add-opens=java.base/java.util=ALL-UNNAMED` if and only if `Platform.isJavaVersionAtLeast(9)`.
7. **R-DOC (single source of truth).**
   - `FrontierEntryState` in `referenceChainFrontier.h` is the canonical numbering.
   - The JavaProfiler javadoc and the `referenceChains.h` seam comment list all four values. Both say that 2 = EDGE is retired.
   - The `EDGE` and `markEdge` comments say they have no production caller.
   - No numeric values change.

## Constraints

- No production behaviour change. Every native change touches test-only seams or comments.
- Keep the seam signatures, the JNI shims (`javaApi.cpp`), the release stubs, and the `FrontierEntryState` numeric values unchanged. Keep `markEdge`, because the fuzz harness uses it.
- `Mutex` is recursive (`PTHREAD_MUTEX_RECURSIVE`). Never take `_engine_lock` while holding `_resolved_chains_lock`.
- Java formatting goes through spotless. C++ style follows the existing two-space, ~100-column comments.
- Profiler hot paths are not touched. Both seams are called only from Java test threads via JNI.

## Scope

### Primary fixes

- `ddprof-lib/src/main/cpp/referenceChains.cpp:1066` (F-91f3cc84a25e). Defect class: a test seam reads engine state without `_engine_lock`. Fix: take `_engine_lock` after the tag guard, and move the `_frontier == nullptr` check under the lock.
- `ddprof-lib/src/main/cpp/referenceChainEvents.cpp:502` (F-17cff193f8ed). Defect class: a generation stamp is sampled outside the lock that serializes its writers. Fix: take `_engine_lock`, then `_resolved_chains_lock`, then load `_search_start_ns`.
- `ddprof-test/.../ExternalProcessReferenceChainTest.java:174` (F-054807ffb76e). Defect class: a JDK 9+ only JVM option is passed to the child unconditionally. Fix: add `--add-opens` only when `Platform.isJavaVersionAtLeast(9)`.
- `ddprof-lib/src/main/java/com/datadoghq/profiler/JavaProfiler.java:677` (F-3b9270c81830). Defect class: an incomplete enum contract in the docs. Fix: document all four states in the javadoc, in `referenceChains.h`, and in the `referenceChainFrontier.h` EDGE and `markEdge` comments.
- `ddprof-test/.../StaticFieldGrowingCollectionScenario.java:100` (F-b2e5089803c3). Defect class: the seam-path predicate is narrower than the builds where the seams exist. Fix: change it to debug-or-`*san`.
- `ddprof-lib/src/main/cpp/referenceChains.cpp:1067` (F-32af0fcc0ab2). Defect class: the sentinel and lock paths have no tests. Fix: the lock is covered by the first fix; add the untagged-probe `-1` assertion in the scenario before seeding. Native gtests per the tester plan.

### Auto-expanded sibling fixes

None identified. The candidates below were considered and deferred; see `planner-report.json`'s `architecture_notes`.

- **Debug-only predicate in other scenarios** (`ThreadLocalLeakScenario:223`, `LeakTagCorrelationScenario:244`, `LeakingCacheScenario:131`, and others). There the predicate only gates a seeding shortcut, not an identity or race guarantee. Widening it would change those tests' behaviour on sanitizer builds, and there is no runtime evidence that would hold up. The review did not ask for it.
- **`tagAsRootForTest`**. It is pre-existing, it mutates engine state rather than reading it (a different defect class), and this PR does not touch it.

## Assumptions

- I am at least 90% confident that taking `_engine_lock` in `resolvedChainTargetTagForTest()` is the minimal change that actually satisfies the reviewer's intent. The full writer list was grep-verified.
- A Java test thread blocked in native code on `_engine_lock` for up to one pass does not stall safepoints. The `pendingExpand*` seams already rely on the same pattern.
- `Platform.isJavaVersionAtLeast(9)` reflects the test JVM, which in the gradle matrix is the same JDK the child runs on.
- **Needs runtime evidence:** whether the strict path on asan/tsan completes within 45 s.
- **Residual, out of scope:** the JNI shims call `GetTag` outside `_engine_lock`, which is a time-of-check/time-of-use gap.
