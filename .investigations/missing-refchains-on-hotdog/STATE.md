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

## Current focus: leak-tag redesign round 2 verification

Round 1 on-pod (build `1ce2b4f03`, see `ev-leaktag-onpod-round1`) proved
the pipeline end-to-end (tagged=28, chains cached and drained) but exposed
three defects, all fixed in round 2 (`0db70994d`):

1. `find-ema-batch-collapse` — per-tag EMA calibration collapsed the BFS
   batch to 2 (3 passes/15min, 10.4s CPU/pass), so the BFS never reached
   the leak-tagged 78MB [B; the 8 emitted chains are depth=1 noise.
   Fixed: AIMD on per-call EMA + per-iteration deadline check.
2. `find-leaktag-jfr-field-misalignment` — leakTag read from the first
   context-attribute byte (75/50 garbage). Fixed: field order on both sides.
3. Emergency multiplier unreachable (wrong progress counter). Fixed:
   `_passes_since_last_candidate_progress`.

Plus user-directed improvements: `tagLeakInstances` tags by per-tid
age-diversity priority (leak thread first), marker re-tag removed,
interception TEST_LOG added. Tests: pool (3), AIMD, interception —
all green in suite.

## Next step: deploy `0db70994d` and verify on-pod

1. `leakTag` populated on the 78MB [B rows (in [0x40000000, 0x40000100)),
   no garbage values.
2. `expandFrontier gotw` shows batch_size recovering toward 512 and
   edges/pass back in the ~1000s; passes bounded (~3 sub-ops × pause target).
3. `leak-tag intercepted` TEST_LOG fires; chains for 78MB [B with
   `targetTag ≥ 0x40000000` and depth > 1.
4. Emergency (100×) fires after 3 candidate-less passes, then 15×, then
   1× once all leak tags resolved.

## TEMP — MUST REVERT before finalizing

- `CANARY_NO_PROGRESS_PASS_LIMIT` 30 → 3 (commit `0b05d5f85`) for faster
  testing.
- Temp diagnostics still in code (kind_counts, gotw logs, blocking logs,
  discovered-loop logs) — remove before production.
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

## Ruled out (do NOT re-investigate)

- **Warm-up / needs more time** (`hyp-warmup-transience`).
- **Regression of the five fixes** (`hyp-regression-of-five-fixes`).
- **`jcmd JFR.dump` as evidence** (`dead-jcmd-jfr-dump-wrong-source`, `dead-jcmd-jfr-dump-wrong-source-v2`).
- **Toolkit `us1.prod.dog`** (`dead-toolkit-prod-datacenter`).
- **Hard reference_kind filter** (`dead-hard-reference-kind-filter`).
- **Deferring `admitObject` out of safepoint** — would save only 5-17%.

## Reproduction handle

Pod `prof-analyzer-hotdog-jb-86d8bf5854-zng9s` in `profiling-stg`,
container `prof-analyzer`, PID 32849 (build `1ce2b4f03`, round 1
verified, see `ev-leaktag-onpod-round1`). Needs redeploy with
`0db70994d` (round-2 fixes). Pod clock is UTC (2h behind local).

JFR: use `kubectl cp` from `/tmp/ddprof_root/pid_XXX/jfr/` (NOT jcmd).
Or use profiling toolkit `download.py` for uploaded profiles.
