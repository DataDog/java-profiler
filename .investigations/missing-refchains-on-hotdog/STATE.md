# Current State

## Active investigation

Why the hotdog pod emits zero `datadog.ReferenceChain` events.

The session ran in two phases and produced two different answers.

**Phase 1 — RESOLVED, not a code bug.** The pod was running stock
ddprof-lib **1.48.1**, which predates all reference-chain work.

**Phase 2 — real defects, progressively fixed.** Multiple root causes
found and fixed across sessions. Current state: BFS throughput is up
~1000x (3-4 → 1700-2800 edges/pass), 5 candidates appear, canary
representatives are re-tagged and all discovered instances auto-marked,
chains are cached per-instance (not per-class). JFR analysis confirmed 2
ReferenceChain events emitted — but one was for a noise [B instance.

## Current focus: Option C (candidate-scoped reach) COMMITTED+PUSHED - both prongs, all suites green, NOT yet deployed (pod round 7 pending)

Round-6 verdict made Option C a correctness requirement (breadth-
first FIFO over a rising heap can never drain; pendingExpand net-growing).
User decision: implement BOTH prongs, taxonomy-driven, explicitly NOT
shaped by probing hotdog's simulator ("we don't want to overfit this
particular scenario"). Design + implementation in
find-option-c-descend-walk-design (unified bounded descend-walk
mechanism, both prongs reuse heapReferenceCallback's whole admission
chain so interception = complete chain in one bounded STW):
- Prong 1 walkCandidateThreadLocals: qualifying tids' Thread objects,
  anchor-gated to ThreadLocalMap, no-descend set (ClassLoader/ThreadGroup/
  ProtectionDomain), own deadline slice before the static sweep.
- Prong 2 collectStaticFieldAnchorsForRotation + walkStaticFieldAnchors:
  root-attached STATIC_FIELD holders, wrapping cursor, batched GOTW
  resolve, descend walks at the head of rotation's slice.
- tid->jthread registry: onThreadStart/onThreadEnd hooks PLUS a
  one-time registerExistingThreads() sweep at Profiler::start() (a leak
  thread is typically alive since before the recording - the first
  ThreadLocalLeakScenario run caught this: walked=0 with the thread
  unregistered; the sweep must live in profiler.cpp's lifecycle, NOT in
  RCT::start(), or the JFR-roundtrip gtest's partial mock env crashes
  on the null GetAllThreads slot).
Verification: 553 gtests green (incl. 2 new descend-walk gtests);
reference-chain slow family 9/9 green (incl. NEW
ThreadLocalLeakReferenceChainTest - the missing thread-local taxonomy
scenario, found correlation live with the thread walk engaging:
walked=1 edges=18); spotlessApply clean.

## Next steps

1. DONE this session: committed (186468437 descend-walk core +
   gtests; 01c591eea ThreadLocal scenario; 93868362e memory sync) and
   pushed to origin/jb/reference-chains-pi.
1b. ALSO this session (NOT yet committed): per-hop retention-edge
   field names in ReferenceChain events (find-field-name-decoding node) -
   "edges" string array, spec-ordinal capture + fail-safe decode, all
   suites green (554 gtests, slow family 9/9, JMC parser test). Commit
   when the user says so; deploy together with the descend-walk commits.
2. Pod round 7: deploy and verify both prongs live on hotdog
   (walkCandidateThreadLocals/walkStaticFieldAnchors per-pass lines;
   watch interception count - the one remaining correctness gap; the
   edges array will name the retention fields directly in the emitted
   chains).
3. TEMP reverts before finalizing (list below).

## TEMP — MUST REVERT before finalizing

- `CANARY_NO_PROGRESS_PASS_LIMIT` 30 → 3 (commit `0b05d5f85`) for faster
  testing.
- Temp diagnostics still in code (kind_counts, gotw logs, blocking logs,
  discovered-loop logs) — remove before production.
- TEST_LOG in `maybeUpgradeRootAttachedRootKind` (upgrade attempts) —
  added this session.
- TEST_LOG `static_sweep_gate` in `runPassManualWalk` (per-pass sweep gate
  decision) — added this session.
- Per-tag TEST_LOG in `tagLeakInstances` RETIRED BY DESIGN (round-5
  follow-up): replaced by the per-poll per-(klass, tid) summary line
  ("tagLeakInstances summary klass_id=... tid=... tagged=... need_set=...
  min_age/max_age/max_size") - the per-instance flood rotated the pod's
  10MB container log inside a verification window. Still TEMP:
  `fanout-insert` log in `trackLeakAccumulation`,
  `requeueChainRootForRotation` log — from the repro round.
- Old marker-tag decode in heapReferenceCallback is now unused — confirm
  and remove.

## Confirmed findings (do NOT re-derive)

1. **`find-marker-tag-slot-index-mismatch`** — slot decode bug, FIXED.
2. **`find-one-shot-pretag-gate`** — pre-tagging one-shot, FIXED.
3. **`find-canary-search-cannot-terminate`** — termination/livelock, PARTIALLY ADDRESSED.
4. **`find-abandon-event-lost-to-dump-sampling-race`** — transient state race, FIXED (queue).
5. **`find-cpu-pain-budget-starves-canary-passes`** — pain budget starvation, FIXED (4x escalation).
6. **`find-canary-stuck-restart-wipes-frontier`** — frontier wipe on restart, FIXED (C+B).
7. **`find-static-field-sweep-never-completes`** — sweep never completes, FIXED (resumable cursor).
8. **`find-candidate1-never-tagged`** — CP edges burning sweep budget, FIXED (per-class quota).
9. **`find-sweep-completes-but-bfs-starved`** — sweep works but BFS can't reach entries. ADDRESSED by adaptive batch_size + deadline split.
10. **`ev-timing-split-callback-vs-jvmti`** — our callback 5-17%, JVMTI 83-92%. Deferring won't help.
11. **`find-getobjectswithtags-quadratic-bottleneck`** — GetObjectsWithTags O(tag_map × batch). FIXED: adaptive batch_size.
12. **`find-shared-deadline-starves-expand`** — shared deadline ate expand's time. FIXED: per-sub-op deadline reset.
13. **`find-rolling-resume-expandfrontier`** — truncated batch re-walked. FIXED: rolling resume cursor.
14. **`find-representative-changes-lose-canary`** — representative LRU-evicted, canary lost track. FIXED: re-tag + auto-mark all instances.
15. **`find-canary-continue-skips-discovered-instances`** — canary `continue` skipped discovered check. FIXED: removed `continue`.
16. **`find-cpu-pain-budget-blocks-bfs`** — cpu_pain_budget silently blocked RUNNING state. DIAGNOSED: diagnostic added.
17. **`find-per-class-caching-blocks-instances`** — per-class caching blocked all but first instance. FIXED: per-instance caching.
18. **`find-age-heuristic-insufficient`** — age heuristic picks noise over leak. DIAGNOSED: allocation-site clustering proposed.
19. **`find-lambda-fragments-calltrace-id`** — lambdas fragment call_trace_id. FIXED: switched to tid-based clustering.
20. **`q-dominant-gens-still-one-with-tid`** — RESOLVED: per-thread tracking works, dominant_gens=1 was from non-leak classes.
21. **`find-ages-vector-not-cleared`** — ages vector inflated across epochs. FIXED: ages.clear().
22. **`find-already-admitted-blocks-deeper-chain`** — ALREADY_ADMITTED blocks deeper chain. FIXED: improveChain().
23. **`find-holistic-design-issues`** — 4 design problems (wrong objects, no correlation, dead chains, flat 100× CPU). Redesign approved.
24. **`find-leak-tag-pool-implementation`** — redesign A-D implemented (294f09ff3..1ce2b4f03), gtest pass, NOT yet on-pod verified.
25. **`q-coverage-tracking-per-combination`** — coverage is per-object; user wants per-(call_trace_id, tid). Refine after on-pod verification.
26. **`find-ema-batch-collapse`** — round-1 regression: batch 400→2, passes 10.4s CPU. FIXED with AIMD + deadline check (0db70994d).
27. **`find-leaktag-jfr-field-misalignment`** — leakTag parsed from attribute byte. FIXED (0db70994d). Field-order invariant recorded.
28. **`find-priority-queue-starves-bfs-crawl`** — round-3 root cause chain (priority flood + slot exhaustion + tag overwrite + dead growth tier). FIXED (f4c73ba0f). Key insight: a cap alone does NOT fix starvation — a capped-but-pinned priority queue still never empties; fair-share alternation is what restores the pending drain.

## Ruled out (do NOT re-investigate)

- **Warm-up / needs more time** (`hyp-warmup-transience`).
- **Regression of the five fixes** (`hyp-regression-of-five-fixes`).
- **`jcmd JFR.dump` as evidence** (`dead-jcmd-jfr-dump-wrong-source`, `dead-jcmd-jfr-dump-wrong-source-v2`).
- **Toolkit `us1.prod.dog`** (`dead-toolkit-prod-datacenter`).
- **Hard reference_kind filter** (`dead-hard-reference-kind-filter`).
- **Deferring `admitObject` out of safepoint** — would save only 5-17%.

## Reproduction handle

Pod `prof-analyzer-hotdog-jb-86d8bf5854-zng9s` in `profiling-stg`,
container `prof-analyzer`, PID 48355 (build `0db70994d`, round 2
verified, see `ev-leaktag-onpod-round2`). Needs redeploy with
`f4c73ba0f` (round-3 fixes). Pod clock is UTC (2h behind local).
Verify the deployed build via a per-iteration log field (e.g.
`ema_call_ms=` in every gotw line) BEFORE interpreting event-driven
logs — round 3 saw one stale-build deploy (JVM 44624 ran the old
build; the redeploy as JVM 48355 had the right one).

JFR: use `kubectl cp` from `/tmp/ddprof_root/pid_XXX/jfr/` (NOT jcmd).
Or use profiling toolkit `download.py` for uploaded profiles.
