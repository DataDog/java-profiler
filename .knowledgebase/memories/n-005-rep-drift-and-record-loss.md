---
id: n-005-rep-drift-and-record-loss
title: n-005: two residual flake mechanisms after the seam fallback; fresh-chunk-per-attempt fix
kind: finding
tags: [reference-chains, flake, chunk]
applies_to: []
source: frontier-wait-untagged/n-005-rep-drift-and-record-loss
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


# n-005: two residual flake mechanisms after the seam fallback; fresh-chunk-per-attempt fix

## Status: FIXED - batch F 8/8 PASS; batch G confirmation + commit pending

## Mechanism 1 (B5): representative drift
klassPopulationSetRepresentativeForTest REPLACES reps with [lateChunk] per round call, but after
the rounds end, real allocation sampling re-populates the byte[] population entry's reps
(rep_count 1 -> 3 observed post-rounds, non-lateChunk at head). resolveCandidateRepresentative
then returns ANOTHER byte[]: the poll leak-tags/intercepts/builds THAT object's chain (entry
22365, leak 1073742079) while lateChunk - the scenario's actual seam target - holds an unbuilt
plain-admission entry (22363, cached=0, no leak tag). Seam: 0 forever.
Fix applied: tail loop re-pins the representative (later superseded by mechanism-2 fix).

## Mechanism 2 (C8): allocation-tracking record loss  [THE DEEPER ONE]
With the rep re-pinned correctly (rep_count=1, rep == lateChunk), lateChunk STILL reads tag=0
at 2134 consecutive polls: it never acquired a leak tag. tagLeakInstances tagged=19 (klass,
main-tid) with need_set=0 - the 19 tagged objects are others. The leak-tag pipeline keys on
the chunk's allocation-tracking record (records minted ONLY at allocation); table churn evicts
an old chunk's record, and once gone, that object can never be leak-tagged/intercepted/
chain-built again. Whether lateChunk's record survives the whole run is the remaining lottery.

## Fix (batch D, running): fresh-chunk-per-tail-attempt
Each tail attempt appends a NEW chunk to LEAK_BUFFER (still appended long after the collection
was EXPANDED - the scenario's invariant holds) and watches IT: fresh allocation => guaranteed-
live record => explicit poll tags it immediately => next anchor descend intercepts =>
later attempt's poll builds its chain (rep path, not the 8-slot discovered path) => seam returns
its tag => dump => JFR match. LEAK_BUFFER_CAPACITY raised to cover tail chunks (elementData
must never reallocate). Also keeps the no-local discipline (chunk reachable only via the static
field).

## Seam fallback (kept, from n-004): leak-tag branch in resolvedChainTargetTagForTest scans
_resolved_chains by event target tag - covers the leak-tag-on-object state across generations.
INVESTIGATE trace lines still in referenceChainEvents.cpp - MUST BE REMOVED before commit.

## Verified remote state: ~/go/src/github.com/DataDog/java-profiler at 6855e4b5e + uncommitted:
referenceChainEvents.cpp (fallback+traces), referenceChains.h (contract comment),
StaticFieldGrowingCollectionScenario.java (v2 rep wiring + stack-local removal + fresh-chunk tail).
Debug level via /tmp/ddprof_root/refchains_debug_level = 2. Compiler: -Pnative.forceCompiler=g++.
Batch results: A3 1/1 PASS, B 2/5, C 4/8 (mechanisms 1+2). Batch D (fresh-chunk) pending.

## Mechanism 3 (E-mode, batch E: 5/8): safepoint pain budget starvation
E8 dissection: chain WAS built for the watched chunk (target_tag=22343, root_kind=8 STATIC,
leak_tag=0 - PLAIN admission path needs NO tracking record, just reachability via elementData),
yet the seam read tag=0 at ALL ~40 explicit attempts. Tail of log: engine frozen in terminal
state - `canAffordNewSearch blocked by safepoint_pain_budget` x1902 consecutive 10Hz iterations
(vs 340 in passing E2), `shouldRunPass terminal_blocked tags_released=1`. A cold external JVM
search costs seconds of measured safepoint pain; default cap 5% of wall-clock clears the debt
in ~a minute; the tail's 60s window gets 1-2 search restarts at best - pure box-load lottery.
Note D8 already proved fresh chunks get plain-admitted+built when searches DO run (43 builds
leak_tag=0). The fresh-chunk rotation's D-era 0/8 was self-inflicted: rotating EVERY attempt read
each chunk before its maturation (interception+build spans >1.5s); fixed in E by
TAIL_CHUNK_ATTEMPTS=8 rotation window.

## Fix 3 (batch F, running): `:painbudget=100` in the flaky test's start command
(ExternalProcessReferenceChainTest:~166, alongside the already-raised budget/pausetarget).
100% = debt clears as fast as it accrues; cadence still bounded by each search's own ~seconds
of work. Test-only config, no product change.

## Full layer map (each layer evidence-backed, all distinct):
1. seam leak-tag fallback (n-004 corrected fix) - leak-tag observation states across generations
2. byte[] rep + stack-local removal (n-002) - candidate klass must be byte[]
3. tail rep re-pin (mechanism 1) - post-round rep drift
4. fresh-chunk rotation w/ 8-attempt maturation (mechanism 2) - tracking-record loss is moot via
   plain admission, but the chunk needs several attempts to mature
5. painbudget=100 (mechanism 3) - engine must actually run searches during the tail

## VERIFICATION RESULTS (final)
- Batch F (painbudget=100 + all prior layers): **8/8 PASS** on workspace-jb-tester.
- Batch G (2 confirmation runs, INVESTIGATE traces stripped, only the leak-tag fallback kept in
  referenceChainEvents.cpp): running, pid 93447, results /tmp/pr800-batchG.txt, logs /tmp/pr800-runG*.log.
- Final local diff (4 files, worktree address-pr-800 at 6855e4b5e, branch jb/rc-6-java-tests):
  referenceChainEvents.cpp (seam leak-tag fallback only, 21 diff lines),
  referenceChains.h (contract comment for resolvedChainTargetTagForTest),
  ExternalProcessReferenceChainTest.java (:painbudget=100 + rationale comment),
  StaticFieldGrowingCollectionScenario.java (TAIL_ATTEMPTS/TAIL_CHUNK_ATTEMPTS constants,
  LEAK_BUFFER_CAPACITY covers rotations, tail: fresh-chunk rotation with 8-attempt maturation
  window + per-attempt rep re-pin + explicit poll before each seam read).
- Batch history on this flake: pre-fix ~40-60% fail; fix-A-era A3 1/1, B 2/5, C 4/8 (mech 1+2),
  D 0/8 (self-inflicted every-attempt rotation), E 5/8 (mech 3), F 8/8.
- Remaining steps: batch G green -> spotlessApply (./.claude/commands/build-and-summarize) ->
  commit 4 files on jb/rc-6-java-tests -> push -> re-check PR 800 CI.
