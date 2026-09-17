---
id: find-static-field-sweep-cursor-fix
type: finding
status: confirmed
depends_on: [find-static-field-sweep-never-completes]
supersedes: []
related: []
tags: [fix, referenceChains, static-field, admitStaticFieldRoots, cursor, resumable, reordering, gtest-verified, NEW-THIS-SESSION]
created: 2026-08-25
updated: 2026-08-25
---

# Fix: resumable per-call cursor + app-classes-first reordering for admitStaticFieldRoots()

## Reasoning chain

`find-static-field-sweep-never-completes` established that
`admitStaticFieldRoots()` was architecturally incompatible with the
per-pass deadline: a single non-resumable `FollowReferences()` over
~34k loaded classes cannot complete within ≤50ms. This fix addresses
that by making the sweep incremental and resumable:

1. **Chunking**: process only `STATIC_FIELD_SWEEP_CHUNK_CLASSES=512`
   classes per call, advancing a persistent cursor. One expensive class
   can no longer block forward progress — the cursor advances
   regardless of truncation.
2. **App-classes-first**: in-place partition of `GetLoadedClasses()`
   result so app/library classes (non-null loader) sweep before the
   much larger JDK bootstrap tail — directly targeting the pod's
   confirmed "static field growing, just a few hops" (application-code)
   leak shape.
3. **Lap-level completion gating**: "sweep done" is now gated on
   `cycle_complete` (true only when a full lap completes with zero
   truncated chunks) instead of the old single-call "this one call
   didn't truncate" check. A lap with any truncation starts a new lap
   immediately.
4. **Reversed holder fill** (added in the per-class quota iteration,
   commit `0e93ab4f7`): holder array filled in reversed order so
   HotSpot's LIFO `FollowReferences` descent visits classes in
   ascending original index order, enabling the resumable cursor to
   resume at the partial class on truncation. See
   `ev-hotspot-lifo-visitation-order`.
5. **Per-class non-static quota** (added in the same iteration):
   STATIC_FIELD edges always admitted; non-STATIC_FIELD edges admitted
   up to 32 per class, then dropped. See `find-candidate1-never-tagged`'s
   fix section and `dead-hard-reference-kind-filter`.

## What changed

`ddprof-lib/src/main/cpp/referenceChains.h` / `.cpp`,
`admitStaticFieldRoots()`:

- New persistent state: `_static_field_sweep_cursor` (int, index into the
  per-call class list to resume from), `_static_field_sweep_cycle_truncated`
  (bool, set if any chunk within the current lap truncated),
  `STATIC_FIELD_SWEEP_CHUNK_CLASSES = 512` (chunk size per call,
  unbenchmarked like this subsystem's other per-pass caps).
- Every call: fetch `GetLoadedClasses()` fresh (as before), then in-place
  partition the array via `GetClassLoader()` so app/library classes
  (non-null loader) come before bootstrap/JDK classes (null loader) - a
  per-call heuristic since JVMTI gives no cross-call ordering guarantee.
  Two-way in-place swap partition, no extra allocation.
- Build the `FollowReferences` holder array from only
  `classes[cursor .. cursor+512)` instead of the whole list. Advance the
  cursor to the chunk end regardless of whether that chunk's call
  truncated (so one expensive class can't block forward progress
  forever). When the cursor reaches the end of the list (a "lap"), wrap to
  0.
- "Sweep done" (`_last_static_field_class_count = _last_resolved_class_count`,
  which suppresses future sweeps until the loaded-class count changes) is
  now gated on `cycle_complete` - true only when a full lap completes with
  **zero** truncated chunks - instead of the old single-call "this one
  call didn't truncate" check. A lap with any truncation starts a new lap
  immediately (cursor already back at 0) and keeps retrying.
- New out-param `bool *cycle_complete` on `admitStaticFieldRoots()`;
  caller (`runPassManualWalk()`) updated accordingly, `TEST_LOG` extended
  with `cycle_complete=%d sweep_cursor=%d`.

Chosen over: a separate/larger deadline budget for this sub-phase
(rejected - works within the existing shared per-pass budget model
instead of requesting more of it) and reordering alone (rejected as
insufficient by itself - without a cursor, a longer classlist still
permanently drops whatever is past one deadline's reach, see
`find-static-field-sweep-never-completes`'s STW-confirmation section for
why chunking was accepted as safe).

## Test-isolation regression found during verification, fixed

`./gradlew :ddprof-lib:gtestDebug_referenceChains_ut` initially reported
`ReferenceChainsBfsTest.RotationDiscoversLateElementOfExpandedStaticFieldCollectionWithoutSearchCompleting`
failing (search reached `SearchState::COMPLETED` unexpectedly instead of
staying `RUNNING`). Bisected via `git stash` (full suite green on
pre-change code, confirming a real regression, not pre-existing flake).

Root cause: `ReferenceChainTracker::instance()` is a process-wide
singleton shared across every gtest case in the binary. The fixture's
`ReferenceChainsTestAccessor::reset()` (`referenceChains_ut.cpp:67`, run
from every `ReferenceChainsBfsTest::SetUp()`) resets
`_last_resolved_class_count` but had **never** reset
`_last_static_field_class_count` - a pre-existing test-isolation gap that
the new cursor/lap fields also fell into. A single-class test running
earlier in the suite could leave `_last_static_field_class_count == 1`;
the next single-class test (the failing one) would then find
`_last_resolved_class_count == _last_static_field_class_count` already
true at its very first pass and skip `admitStaticFieldRoots()` entirely -
so the static-field-rooted node was never admitted, and the test's
"distractor chain" (500 nodes, designed to keep the search perpetually
`RUNNING` while the real target loiters in the frontier) drained to
completion instead, flipping `SearchState::COMPLETED`.

Fix: added `_last_static_field_class_count = -1`,
`_static_field_sweep_cursor = 0`, `_static_field_sweep_cycle_truncated =
false` to `ReferenceChainsTestAccessor::reset()`
(`referenceChains_ut.cpp`), mirroring the same reset
`resetForRestart()` already performs for the production restart path
(`referenceChains.cpp:1085-1086`). Also applied the identical reset to
`resetSearchStateForTest()` (`referenceChains.cpp` - the separate,
production-code test-seam called from `javaApi.cpp:1220`, not from any
gtest fixture) for the same contract, since it had the same latent gap.

Also added `mock_GetClassLoader` to `ReferenceChainsBfsTest`'s JVMTI
function-table mock (every fixture class reports as bootstrap/null-loader,
making the partition a no-op so existing tests' scripted class
order/indices are unaffected).

## Verification

- `./gradlew :ddprof-lib:gtestDebug_referenceChains_ut` - 90/90 tests pass.
- `./gradlew :ddprof-lib:gtestDebug` (full suite, not just this file) -
  188 actionable tasks, BUILD SUCCESSFUL.
- **Committed and pushed** as `a86f0dd87` on `jb/reference-chains`
  (`82fec4210..a86f0dd87`), three files only
  (`referenceChains.cpp`/`.h`/`referenceChains_ut.cpp`).
- **Deployed and confirmed live on the hotdog pod.** JVM PID 92618
  (started 15:29), scratch `.so` md5 `aeab8726e90e5f21e33393c3bfea043e`,
  `strings` confirms `_static_field_sweep_cursor`,
  `static_field_cycle_complete`, and the new `cycle_complete=%d
  sweep_cursor=%d` TEST_LOG format.
- **Live mechanism confirmed correct** — see
  `ev-postfix-static-field-onpod-live-verification`: cursor advances by
  512/call across laps, real edges admitted (up to 737/chunk observed,
  vs. 0-1 forever pre-fix), lap-level truncation-latch behaves exactly as
  designed (a lap with any truncated chunk never reports
  `cycle_complete=1`, confirmed with a concrete final-chunk example).
  `cycle_complete=1` has not yet been observed in any sample checked
  across ~10+ minutes combined — the JDK bootstrap classlist tail is
  large enough that a fully clean lap apparently hasn't happened yet;
  not treated as a problem since `edges_admitted` and `sweep_cursor`
  prove real forward progress every call.
- **End-to-end candidate resolution is still 0/5** despite the sweep
  mechanism being confirmed healthy — see new open findings
  `find-candidate1-never-tagged` and `find-candidates-234-die-before-resolution`.

## Open follow-up (not yet actioned)

- `STATIC_FIELD_SWEEP_CHUNK_CLASSES = 512` is a first guess, not
  benchmarked against a real ~34k-class JVM's actual per-class static-field
  fan-out cost.
- The app-classes-first partition is a per-call heuristic (JVMTI gives no
  guaranteed stable ordering across separate `GetLoadedClasses()` calls) -
  works well enough for the common case but isn't a persisted global
  ordering.
