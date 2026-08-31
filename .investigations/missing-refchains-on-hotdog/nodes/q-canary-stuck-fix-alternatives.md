---
id: q-canary-stuck-fix-alternatives
type: question
status: confirmed
depends_on: [find-canary-stuck-restart-wipes-frontier]
supersedes: []
related: [find-canary-fixes-e-f, find-canary-stuck-abandon-detector]
tags: [decision-made, fix-implemented, referenceChains, canary, research, NEW-THIS-SESSION]
created: 2026-08-25
updated: 2026-08-25
---

# Which fix for the CANARY_STUCK/frontier-wipe convergence bug? RESOLVED: user chose C+B, implemented and gtest-verified

## Context

`find-canary-stuck-restart-wipes-frontier` is now a CONFIRMED root cause
(not just a hypothesis) for why candidates resolve 0/5 even after Fix E/F
resolved the earlier starvation. User confirmed the target is a synthetic,
permanently-reachable leak, ruling out "candidate unreachable" as a
competing explanation. User asked to analyze the leading suspect and
research well-established/bleeding-edge solutions before proposing fixes.

## Research grounding

- **Incremental BFS (IBFS)**: standard technique for "restart destroys
  frontier/visited state" — reuse the queue/frontier across cycles instead
  of resetting to empty.
- **G1 GC's SATB (snapshot-at-the-beginning) marking**: concurrent/
  incremental collectors never re-mark from roots per increment; they
  snapshot the live-set logically once and drain a write-barrier log
  instead of discarding accumulated marking work — same shape of problem
  in GC's domain.
- **Luby/adaptive restart theory (SAT solving)**: a *fixed* cutoff before
  restart is provably suboptimal when the true cost-to-converge is unknown
  or variable — directly indicts `CANARY_NO_PROGRESS_PASS_LIMIT=30` as a
  heap-size-agnostic constant. Established alternative: adaptive/growing
  cutoffs, or restarting only when *multiple independent* progress signals
  have all stalled.

## Four alternatives proposed

**C — Merge the two stuck detectors (recommended lean).** Only fire
`CANARY_STUCK` when `_passes_since_last_progress` (whole-graph) is ALSO
over its own limit, not just `_passes_since_last_candidate_progress`
alone. Live trace directly falsifies the current design's premise: the
frontier was still growing (12k→16k) throughout — the graph walk was not
stuck, only the (narrower) "found this specific candidate" signal was.
Smallest diff (one condition), lowest risk.

**A — Stop wiping the frontier on `CANARY_STUCK` (IBFS-style).** Keep
`_frontier`/tag state intact across the restart; only clear the stuck
counter and keep walking. More invasive (touches `restartSearch()`'s
contract and candidate-tag release logic) but correct if `CANARY_STUCK`
should mean "pause and reassess" rather than "declare defeat".

**B — Adaptive/Luby-style growing limit instead of fixed 30.** Scale
`CANARY_NO_PROGRESS_PASS_LIMIT` per retry (30, 60, 120, ...). Keeps the
existing destructive-restart architecture but is a bandage — still
forgets everything each cycle, just tries longer before forgetting.

**D — Persistent tag/visited-set across restarts (full SATB-style
resumability).** Decouple "restart" from "re-walk from empty" by
preserving `_next_tag`/the tag-identity table so a restarted search treats
previously-explored regions as already-visited. Most architecturally
faithful to established incremental-GC design, but touches JVMTI tag
lifecycle and frontier-table capacity assumptions — highest implementation
risk for likely the same practical outcome as A here.

## Recommendation given to user

Lean: **C**, optionally combined with **B** as a belt-and-suspenders hard
ceiling in case the whole-graph frontier itself ever genuinely stalls on a
very large heap. A/D flagged as worth keeping in mind if canary searches
need true pause/resume semantics later, but more invasive than this
specific bug requires.

## Decision and implementation (this session)

User: "Try C/B first. Then I will deploy and you will check if it helped."
Implemented both, in `ddprof-lib/src/main/cpp/referenceChains.{h,cpp}`:

- **C (merged stuck detectors)**: `runPass()`'s `CANARY_STUCK` branch
  (`referenceChains.cpp:3120-3149`) now additionally requires
  `_passes_since_last_progress >= NO_PROGRESS_PASS_LIMIT` — the whole-graph
  frontier must ALSO have stalled — before firing, on top of the existing
  `_passes_since_last_candidate_progress >= canaryStuckPassLimit()` check.
  Directly counters the live-trace evidence (frontier still growing
  12k→16k while chasing the candidate).
- **B (adaptive/Luby-style escalating limit)**: new field
  `_canary_stuck_restart_count` (referenceChains.h) tracks consecutive
  `CANARY_STUCK` restarts of the same candidate-chase sequence — NOT reset
  by `restartSearch()` itself, only reset in the terminal-state block when
  a search ends for a reason OTHER than `CANARY_STUCK`
  (`referenceChains.cpp:3200-3206`). New method `canaryStuckPassLimit()`
  doubles `CANARY_NO_PROGRESS_PASS_LIMIT` (base 30) per consecutive
  restart, capped at `MAX_CANARY_STUCK_BACKOFF_SHIFT=8` doublings (7680
  passes ceiling) so a genuinely-stuck-forever search still terminates in
  finite time.
- Test seams added: `setCandidateCountForTest()`,
  `passesSinceLastCandidateProgressForTest()`,
  `canaryStuckRestartCountForTest()` (referenceChains.h, wrapped by
  `ReferenceChainsTestAccessor` in the test file). Also fixed a
  test-isolation gap in `ReferenceChainsTestAccessor::reset()` — it did not
  clear `_passes_since_last_candidate_progress`, `_last_candidate_progress_mark`,
  or the new `_canary_stuck_restart_count` between `TEST_F` cases.
- **New regression test**:
  `ReferenceChainsBfsTest.CanaryStuckRequiresWholeGraphFrontierAlsoStalled`
  in `referenceChains_ut.cpp` — builds a 50-node linear mock heap chain with
  `budget=1` (frontier grows by exactly one node every pass, so
  `_passes_since_last_progress` never reaches `NO_PROGRESS_PASS_LIMIT`) and
  a canary candidate that is never found. Asserts the search stays
  `RUNNING` for `CANARY_NO_PROGRESS_PASS_LIMIT + 2` passes — well past the
  point the old single-condition check would have abandoned it.
  **Verified rigorously**: temporarily reverted just the merged condition
  back to the pre-fix single-condition form and reran — the new test
  failed (canary abandoned prematurely, `Value of: SearchState::RUNNING`
  assertion tripped). Restored the fix — test passes, and the full
  `gtestDebug_referenceChains_ut` suite (90 tests) passes clean.
- Compiles cleanly: `./gradlew :ddprof-lib:compileDebug -Pskip-gtest` →
  BUILD SUCCESSFUL, 69 files, no warnings.
- **Not yet committed/pushed** (not requested this session). **Not yet
  deployed** — user will deploy and this investigation will need another
  live-pod verification pass afterward.

## Not yet done

- Alternatives A and D remain unimplemented/deferred by explicit user
  choice ("Try C/B first").
- Commit, push, deploy, and the follow-up live-pod re-check are all
  pending — see `find-canary-stuck-restart-wipes-frontier`'s "Not yet
  done" section.
