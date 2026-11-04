# Spec: possible-early-termination-before-root-enum

Date: 2026-11-04 · Run: `addr-learn-925-1761889000` · Source: local (PR #925 review threads)

## Problem

PR #925 reworked the `ReferenceChainTracker` BFS pass scheduling: root/stack-ref
enumeration attempts (`IterateOverReachableObjects`, the only call site is
`referenceChainTraversal.cpp:213`) are now interval-gated by
`rootEnumIntervalFloorNs()` (2s base, cost-scaled, 30s cap), and pass frequency is
paced by `_effective_cadence_ns`. Four review findings describe defects in this
machinery:

1. **Root-enum completeness is recorded nowhere** (`referenceChainTraversal.cpp:235`).
   Root enumeration admits roots in chunks (`heapRootCallback()` charges no budget
   for `ALREADY_ADMITTED` roots, so each retry admits the next chunk). A truncated
   attempt early-returns the pass; the retry waits out the floor. During the wait,
   expansion-only passes run with `truncated == false`, so `runPass()`'s termination
   ladder has two premature exits: a spurious `COMPLETED` (frontier drained,
   `_watched_leak_klass_count == 0`) and a spurious no-progress `ABANDONED` (30
   stagnant passes at 10ms cadence fit inside the 2s floor). Chains reachable only
   from unenumerated roots would be lost.
2. **The GC-epoch branch in `shouldRunPass()` no longer changes any scheduling
   decision** (`referenceChains.cpp:783`): once the spacing gate passes, the epoch
   branch and the fallback branch both `return true`; the epoch only selects the log
   line. Dead lane plus its test-only machinery (native hook, JNI pair, Java
   declaration, tests).
3. **The spacing gate does not bound safepoint frequency** (`referenceChains.cpp:742`):
   it compares only against `_effective_cadence_ns`, which `updatePacing()` relaxes
   to `MIN_EFFECTIVE_CADENCE_NS` (10ms) for cheap passes and `applyOomRamp()` drives
   to `URGENT_CADENCE_NS` (10ms). The PID controller paces pause LENGTH, not pass
   RATE — under cheap expansion passes the gate still admits ~100 safepointing
   passes/second.
4. **Restarts bypass both new gates** (`referenceChains.cpp:824`): the restart lane
   and the search-not-started lane return before the spacing gate; after
   `restartSearch()` sets `_search_started == false`, `shouldRunRootEnum()`'s
   `manual_first_pass` branch forces an immediate enumeration regardless of the
   floor, so an enumerate → early-terminate → restart → enumerate loop's only brake
   is `_safepoint_pain_budget` refill.

The umbrella review comment (no file/line) requests changes for findings 1 and 2
and endorses root-enum frequency + cost-scaled intervals as the right lever; it
adds no separate fix.

## Correct behaviour

Rules carried from the design's shared invariants (all must hold after the fix):

- **R1 (ownership/locking):** `_root_enum_incomplete` is BFS-thread-owned exactly
  like `_last_root_enum_ns`; any test seeding hook that touches it must take
  `_engine_lock` (pattern: `setRootEnumStateForTest`).
- **R2 (restart inheritance):** `_last_root_enum_ns` is NEVER reset by
  `restartSearch()` (only `resetSearchStateForTest()` zeroes it) — the root-enum
  interval floor carries across restarts; `restartSearch()` must clear
  `_root_enum_incomplete` and `resetSearchStateForTest()` must clear it too (a stale
  `true` would freeze every restarted search's progress counter and block
  `COMPLETED` forever).
- **R3 (single spacing law):** every pass-authorization lane keeps passing through
  the floored spacing gate and the CPU pain budget; the gate enforces
  `min_spacing_ns = _oom_ramp_active ? cadence_ns : max(cadence_ns,
  MIN_PASS_SPACING_NS)` — the OOM ramp is the ONLY path to sub-100ms pass spacing.
- **R4 (termination honesty):** a pass with an incomplete root enumeration is
  treated as having pending frontier work: neither `COMPLETED` exit (ordinary
  frontier-drained nor canary all-found) nor the no-progress abandon may fire while
  `_root_enum_incomplete` is set. The hold on `_passes_since_last_progress` covers
  both the ordinary and the canary-stuck abandon (canary-stuck requires the primary
  counter to reach its limit too).
- **R5 (absolute bounds untouched):** the TTL wall-clock branch and the
  frontier-cap abandon remain absolute and are NOT suppressed by the new flag — a
  frontier-cap hit abandons the search even with enumeration incomplete.
- **R6 (PID signal purity):** `updatePacing()` and
  `maybeRevokeBorrowForRootEnumPass()` are unchanged — root-enum passes stay
  excluded from the PID signal.
- **R7 (pure cadence, no epoch lane):** passes run on a pure cadence bounded by the
  fixed `MIN_PASS_SPACING_NS` floor; the last-pass GC-epoch snapshot lane
  (`_last_pass_gc_finish_epoch`, `shiftLastPassGcEpochForTest`, its JNI/Java hooks
  and tests) is deleted wholesale. The LIVE epoch counter (`_gc_finish_epoch`,
  `gcFinishEpoch()`) and its read hook `referenceChainGcFinishEpochForTest0`
  survive.
- **R8 (restart floor):** `canAffordNewSearch()` returns false while
  `_last_root_enum_ns != 0 && now_ns - _last_root_enum_ns <
  rootEnumIntervalFloorNs()`, in addition to the existing pain-budget and
  leak-signal checks; the brand-new-tracker exemption (`_last_root_enum_ns == 0`)
  is preserved, and a restarted search's first enumeration still runs immediately
  once the floor elapses (its `manual_first_pass` semantics are unchanged).
- **R9 (overflow/edge policy):** the flag makes the search outlive its frontier —
  this is correct: the retry is bounded by `rootEnumIntervalFloorNs()` (2-30s) plus
  the ungated TTL wall-clock branch, the flag has hard clear conditions (completed
  attempt / `restartSearch()`), so it cannot wedge. Nothing is dropped or
  force-invalidated.

## Constraints

- C++17, JVMTI heap-category call discipline (no `IterateOverReachableObjects`
  from GC callbacks) — unchanged.
- `TEST_LOG_SUMMARY` format strings: every added/edited log call must keep its
  arg count/order matched (`runPass done` already has 15+ args).
- Java test seams are debug-build-only; release stubs in `javaApi.cpp` must mirror
  deletions (BOTH definitions of a deleted hook).
- API surface test (`JavaProfilerApiSurfaceTest`) pins the exact JNI hook list —
  every deleted hook must be removed from the list.
- PR description must state the choice: epoch-lane removal (passes run on pure
  cadence) and the 100ms fixed floor value (behavior change vs "op volume
  unchanged" framing).
- Build/test via `./.claude/commands/build-and-summarize <task>` (never bare
  `./gradlew`): `buildDebug`, `:ddprof-lib:gtestDebug`, `:ddprof-test:testDebug
  -Ptests=...`.

## Scope

### Primary fixes

- **4454738299** — `ddprof-lib/src/main/cpp/referenceChainTraversal.cpp:235` (+
  `referenceChains.h`, `referenceChainTraversal.cpp` termination ladder ~1105-1180)
  — *unrecorded incomplete stateful enumeration*: add BFS-thread-owned
  `_root_enum_incomplete`; SET on the root-enum error and truncated early-return
  paths of `runPassManualWalk()`'s root-enum block; CLEAR on a completed attempt,
  in `restartSearch()`, and in `resetSearchStateForTest()`; treat as pending
  frontier in `runPass()`'s termination checks (`has_pending_frontier`, canary
  all-found gate, progress-counter hold, belt-and-braces on the ordinary
  no-progress abandon ONLY — never the TTL or frontier-cap branches); add
  `rootEnumIncomplete=%d` to the `runPass done` log.
- **4454738318** — `ddprof-lib/src/main/cpp/referenceChains.cpp:742` (+
  `referenceChains.h` constant) — *gate bounded by controller output instead of a
  fixed bound*: add `MIN_PASS_SPACING_NS = 100000000ULL` (100ms); spacing gate
  becomes `max(cadence_ns, MIN_PASS_SPACING_NS)` with the OOM ramp as the only
  exemption (while `_oom_ramp_active`, the gate uses `cadence_ns` alone).
- **4454738307** — `ddprof-lib/src/main/cpp/referenceChains.cpp:783` (+ 11
  enumerated deletion sites across `referenceChains.cpp/.h`,
  `referenceChainTraversal.cpp:1074`, `javaApi.cpp` (both definitions ~1487-1494
  and ~1681-1686), `JavaProfiler.java:811-847`, `ReferenceChainTestHooks.java:57`,
  `JavaProfilerApiSurfaceTest.java:44`, `ReferenceChainSchedulingTest.java`,
  `referenceChainsBfsTests.inc:1063-1085`, `referenceChainsTestAccessors.h:73,735-740`)
  — *dead scheduling branch*: delete the last-pass GC-epoch lane wholesale (field,
  store, resets, branch, log terms, test hook, JNI pair, Java declaration + javadoc
  `{@link}`, Java/gtest tests, accessor references). Keep the live epoch counter
  and `referenceChainGcFinishEpochForTest0`. Keep
  `canaryBackToBackPassWaitsForMinimumPassSpacing` minus its
  `shiftReferenceChainLastGcEpochForTest0(1_000)` call. Reword (do not leave
  dangling) the surviving `referenceChainGcFinishEpochForTest0` javadoc's
  `{@link #shiftReferenceChainLastGcEpochForTest0(long)}` sentence.
- **4454738326** — `ddprof-lib/src/main/cpp/referenceChains.cpp:824` (+
  `referenceChains.h` declaration comment) — *restart path bypasses pacing gate*:
  apply `rootEnumIntervalFloorNs()` inside `canAffordNewSearch(now_ns,
  seconds_to_oom)` after the pain-budget check, before `hasLeakSignal()`, guarded
  by `_last_root_enum_ns != 0`; update the declaration comment.
- **5752281501** (umbrella, no file/line) — no separate fix; satisfied by the four
  items above (root-enum completeness + pure-cadence pacing).

### Auto-expanded sibling fixes

None identified. Sibling-defect hunt over the two defect classes:

```
FLOW: runPassManualWalk() -> walkCandidateThreadLocals()/admitStaticFieldRoots()
      truncation paths (referenceChainTraversal.cpp:258-266, ~285-320)
PRECONDITION: a sub-phase truncates while root enumeration completed
REACHABLE: structurally covered — every such path writes *truncated, which feeds
      has_pending_frontier in runPass()'s ladder directly; the new flag adds the
      only uncovered case (root enumeration itself).
CONCLUSION: no separate fix needed.
```

```
FLOW: shouldRunPass() -> canary lane spacing (referenceChains.cpp:765-781),
      threadLoop() cadence sleep (referenceChains.cpp:584)
PRECONDITION: adaptive value used as a frequency bound
REACHABLE: no — the canary lane is work-scaled by _canary_backoff_mult's own
      progress-driven backoff (a separate stated law); the threadLoop sleep is a
      sleep interval, not a safepoint authorization.
CONCLUSION: not the same defect class; no fix.
```

```
FLOW: _passes_since_last_candidate_progress increments during floor-wait passes
      (referenceChainTraversal.cpp:1189-1206)
PRECONDITION: root-enum incomplete + canary chase open
REACHABLE: no spurious abandon — the canary-stuck branch ALSO requires
      _passes_since_last_progress >= NO_PROGRESS_PASS_LIMIT, which R4's hold keeps
      below the limit.
CONCLUSION: latent but harmless under R4; no fix (recorded so the writer does not
      "fix" it).
```

## Assumptions

- **A1 (runtime evidence):** the reviewer of 4454738299 could not reproduce; the
  "17 = 17 chains" repro presumably ran at a cadence slow enough to avoid both
  premature exits. The COMPLETED-exit hole exists regardless of cadence regime, so
  the fix proceeds. If testing shows another mechanism keeps the search alive, the
  flag is still correct and cheap.
- **A2 (design choice, ≥90%):** epoch-lane REMOVAL chosen over "give the epoch a
  real effect" — the gate comment at `referenceChains.cpp:736` states the PR's law
  is "a completed GC must not bypass the pacing"; a real-effect epoch would
  re-introduce the GC-driven pass-frequency lane this PR deliberately removed. The
  umbrella reviewer also leaned removal. Note it in the PR body.
- **A3 (value choice, ≥90%):** `MIN_PASS_SPACING_NS = 100ms` (10 non-urgent
  safepointing passes/s max). The reviewer left the value open, demanding only that
  it not be the controller's 10ms. If the team intends 10ms, retune the constant
  and the PR framing only.
- **A4 (restart latency):** with R8, a restart can wait up to
  `ROOT_ENUM_MAX_INTERVAL_NS` (30s) after an expensive final enumeration; urgent
  latches are delayed too. The plain full-floor version is the consistent law. If
  restart latency regresses in practice, key the floor to search end instead.
- **A5 (unattended):** no external consumers of the deleted Java test hook beyond
  `JavaProfilerApiSurfaceTest` are assumed (grepped this worktree; none found).
- **A6 (unattended):** `MIN_PASS_SPACING_NS` sits in `referenceChains.h` next to
  `MIN_EFFECTIVE_CADENCE_NS` (constants block ~line 670-724).
