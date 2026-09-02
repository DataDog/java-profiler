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

## Current focus: canary backoff + sampler-dead lottery fixed; A+B+backoff ready for pod round 5

This session (uncommitted):
- Chase-phase admission boost (find-admission-boost-implementation,
  user option A): tracked-allocation admission raised to 100% for
  candidate qualifying tids (poll-refreshed) and everything under the
  OOM urgency ramp. 550 gtests green; slow suite green except the
  known ToGcRoot family (q-togcroot-acceptance-paths, both failing
  runs hit exactly 124 passes - structural pass-budget ceiling).
- All four :l reference-chain test sites now pass the explicit
  ratio=1.0 (see find-default-live-samples-ratio-lottery).
- Option A (user point 3): work-scaled canary backoff (see
  find-canary-lane-backoff-design). Pod chase burn structurally
  bounded to <= ~1/16 core at the multiplier cap.
- Sampler-dead interaction (user-asked chase) CLOSED
  (find-default-live-samples-ratio-lottery): default 10% live-sample
  ratio + tiny scenario cohort = Bernoulli lottery; test now passes
  memory=64:l:1.0. All TEMP diagnostics added for the chase were
  fully reverted (referenceChains backoff state + its gtest remain).
- Doc: ReferenceChains-SignalsExplained.md sections 4/8/11 updated
  per user's points 1+2+3.
- 546 gtests green; slow suite: leak-correlation green (2/2 variants),
  ToGcRoot/UnboundedCache remain load-sensitive (separate family:
  in-process passes ~4.4s under 5s pausetarget at load 25+, work-scaled
  spacing follows them - timing, not a correctness bug; verify on a
  quiet box before judging).

## Next steps

1. Pod round 5 (user redeploying with A+B+backoff build): verify
   - `held off by canary backoff mult=... ema_ms=...` lines; stuck
     chase pacing; burn drop vs round 3-4;
   - Tier-2 FRONTIER-holder rotation (A) engaging:
     `collectLeakAccumulationCandidatesForRotation selected
     parent_tag=... state=FRONTIER`;
   - interception/correlation: leak-tag intercepted -> buildChainEvent
     with pool-range targetTag matching HeapLiveObject.leakTag;
   - batch growth under backlog pressure (B):
     expandFrontier next_batch beyond MIN under deep backlog.
2. Commit chunk-wise once pod-confirmed (backoff; A+B; test ratio fix;
   doc; memory).
3. TEMP reverts still due before finalizing (list below) - note the
   sampler-dead chase's diagnostics are already reverted.
4. Open: ToGcRoot/UnboundedCache flakiness - NOT the ratio lottery
   (the explicit :l:1.0 is now on ALL four :l reference-chain test
   sites; rep-died symptom gone) and not pure load (fail at load 3).
   See q-togcroot-acceptance-paths for the confusing 13-pass-green vs
   124-pass-fail data and the candidate factors (backoff EMA polluted
   by root-enum passes; Tier-2 coverage of the marker's parent;
   non-canary acceptance path). Parked: pod pass-wall decomposition
   (static sweep lap share).

## TEMP — MUST REVERT before finalizing

- `CANARY_NO_PROGRESS_PASS_LIMIT` 30 → 3 (commit `0b05d5f85`) for faster
  testing.
- Temp diagnostics still in code (kind_counts, gotw logs, blocking logs,
  discovered-loop logs) — remove before production.
- TEST_LOG in `maybeUpgradeRootAttachedRootKind` (upgrade attempts) —
  added this session.
- TEST_LOG `static_sweep_gate` in `runPassManualWalk` (per-pass sweep gate
  decision) — added this session.
- Per-tag TEST_LOG in `tagLeakInstances`, `fanout-insert` log in
  `trackLeakAccumulation`, `requeueChainRootForRotation` log — from the
  repro round.
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
