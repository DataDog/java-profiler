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

## Corrections

- (2026-09-16, round 19) `open(path, "w")` TRUNCATES the file BEFORE the
  write argument is evaluated — a failed `write(list)` left INDEX.md
  empty and the chained `git add` committed the wreckage (118 lines
  lost, restored from git). Build the complete string first, write
  once; never open-for-write before the content exists. Same family as
  the atomic-multi-edit lesson: a failed step plus an unconditional
  follow-up destroys state.

- "Pre-existing gtest SIGSEGV UrgentOOMProjectionBypassesCandidateGate"
  was MISLABELED — it was this investigation's own regression, hidden
  from its own round notes by lazy "clean HEAD" testing (HEAD = this
  branch's tip, all investigation commits). True timeline: the test
  landed 5adb32831 (2026-08-12); autoTuneDefaults facdc70c0 (2026-08-17)
  began calling GetAvailableProcessors from start(); the fixture's table
  was never wired → the ONLY max-heap-setting test in the file null-
  crashed at start() for 5 weeks — its real subject (OOM-urgency bypass
  of the candidate gate) never executed. FIXED this round: wired
  mock_GetAvailableProcessors (returns 1) — test passes its subject,
  gtestRelease green with no exclusions for the first time since
  2026-08-17. LESSON: "reproduces on HEAD" proves "not from today's
  diff", nothing more; bisect to the introducing commit before calling
  anything pre-existing — and a crashing test is never "separate debt",
  it is lost signal (this one carried valid assertions the whole time).

## Current focus: round 20 COMPLETE — P0 harness fully live (de15e521f)

All system invariants run in CI (128 tests / 127 pass / 1 skip-with-reason):
L1 leak chains + L2 canary resolution + L3 natural completion + L6 restart
hygiene (chains persist by design) + L8 dormancy + L4 log budget (live in
DEBUG-built test binaries only). The round-20 "candidate suppression" catch
is RETRACTED — it was the harness builder's own dangling jclass-identity
pointer (vector reallocation; find-candidate-presence-suppresses-static-
admission, now a retracted-deadend node with the fixture capacity contract
encoded as a permanent regression test). NEXT: P1 keyspaces audit + dead
marker-path retirement, P2 always-on per-search health line, P4 deferred
queue (sporadic batch coverage stays open for upstreaming). The pod remains
verification-only (no more pod-driven discovery rounds).

Prior focus: STRATEGY SHIFT (round 19) — stop pod-driven whackamole; build the missing oracle

Meta-review 2 (meta-whackamole-analysis, user challenge): goal achieved
(round 16) but rounds 17-19 are whackamole — 30+ fixed defects fall into
7 producing classes, 5 of which are invisible to the 348-test unit
suite by construction, so the staging pod (hours/iteration, n=1) is the
only end-to-end oracle and surfaces them in random order. THE PLAN
(design-pod-in-a-jar-harness, pending user approval): P0 pod-in-a-jar
system harness (real loop + mock topology + 8 invariants incl. LOG
BUDGET and dormancy; 1 session), P1 keyspaces audit + dead marker-path
retirement, P2 always-on per-search health line (exits-by-reason,
canary-resolution histogram, coverage ratio — pod verification becomes
one line), P3 reset-contract invariant test, P4 deferred queue triaged
to harness-flagged-only. NO more pod-driven fix rounds; the pod becomes
verification, not discovery.

Prior focus (round 19, superseded by the shift): canary found-criterion
root-caused + fixed (788d7b2a7, pending pod verification on next
deploy — watch 'canary found:' + 1/1 + natural completion).: ROUND 16 VERIFIED ON POD — leak-correlated ReferenceChain events FLOWING (end goal reached)

Build 4afe870a2 on pod cgdtx (JVM 07:45:11Z, wrapper klass 28516, leak
[B klass 5): fix A live at scale (self_edge_skips=30816+, wrapper
admitted root-attached parent=0 root_kind=8 and WALKED as anchor tag
2184 — the round-15 parent==self demotion is gone); fix B live
(quota_drops=6351, fifo_size=132 ≪ 1024 — the floods contained, 16
drained/pass); FIRST leak-tag interceptions ever (12+, leak_tag ≥
2^30 admitted with parent chains); leak-correlated chains cached
(auto-marked target_tag=1073742071/72/77 — leak-tag targets) and
re-emitted 6→14 sustained per dump. Also an accidental CONTROL run:
3h of the non-leaking app image → ZERO tracker activity — the
candidate gate keeps the machinery dormant on a healthy app.
Remaining watch: canary 0/1 (its representative not yet intercepted;
the round-15 chase deadlock is broken — walks + interceptions every
pass; exit expected as coverage reaches it). LOG FLOOD SOLVED (f70bcc454):
the round-12..16 TEST_LOG diagnostics are now runtime-gated
(rcDebugLevel.h) — level 0 SILENT by default (same debug .so, pod-safe),
1 = lifecycle/summary (per-pass/per-poll: candidates, canary, rotation
counters, re-emit, leak-tag correlation), 2 = full per-object firehose.
Env DD_PROFILING_REFERENCE_CHAINS_DEBUG=N at start; runtime override
(no restart): kubectl exec … -- sh -c 'echo N >
/tmp/ddprof_root/refchains_debug_level' (single digit, re-checked ~1s
by the RC thread loop; remove the file to fall back to env). The TEMP
removal list below is superseded: diagnostics KEPT but gated; slimming
for upstream is a later round. Node: find-refchains-log-flood-configurable
(tier empirics, the callback-context constraint, the two build/workflow
lessons + the two pod-verified escapes: header-inline TEST_LOG sites
bypass the TU macro gate — fixed 7aa68744b by moving buildChainEvent/
buildCanaryChainEvent out of line; tick-cadence lines demoted 524c35325
— level 1 is transitions/bounded outcomes only, verified <500/min).
CANARY 0/1 ROOT-CAUSED + FIXED (788d7b2a7,
find-canary-found-criterion-unmigrated): the marker->leak-tag migration
never migrated the found criterion — found bits set only in the dead
marker path; the rep path checked/built by leak tag (never a frontier
key). Moving-target hypothesis REFUTED (stable tag across 203 ticks).
Fix: leak-tag-target chains mark slots found (any-instance criterion —
the per-instance guarantee lives in the leak-tag correlation); rep
path resolves by the slot key. Pending pod verification on the next
deploy: 'canary found:' + 1/1 + clean search-restart cycle. Separate
upstreaming topic observed: subtree coverage is sporadic at batch scale
(5-min window: wrapper not walked, zero new interceptions, 34 cached
chains). See ev-leaktag-onpod-round16-results.md,
find-wrapper-demotion-self-parent.md (FIXED+verified),
find-round16-endgoal-verification.md (the milestone + the control
run), find-urgentoom-null-fn-mislabel.md (the same round's test-infra
root cause: the 5-week null-fn crash + the 'pre-existing' mislabel
lesson).

Prior focus: round 15 verified (first wrapper walk, first events);
round-16 gap measured+fixed (demotion guard, FIFO quota, UrgentOOM
root-cause — all in 4afe870a2, gtests 118/118 no exclusions).

Prior focus (round 13 prepared): fix B+C verified working mechanically on
the pod (ccdb03b89), but the LEAK_BUFFER wrapper is STILL never walked;

Design/review/implement/review loop run for B' (user-picked). Two
load-bearing discoveries during the loop (both in
find-already-admitted-blocks-unreachable + find-anchor-live-feed-design):
1. The "sweep re-laps every pass" feed assumption was FALSE — the sweep
   gate re-laps only while the class count is in flux → B' needed TWO
   push sites (demotion time + sweep time), not one.
2. BOTH push sites sat in a pre-existing DEAD NEST: 57aec4895 misplaced
   improveChain inside heapReferenceCallback's first-admission block,
   where improveChain/reparentToDurableRoot/maybeUpgradeRootAttachedRootKind
   were all guaranteed no-ops for already-admitted entries (since
   2026-08-28). This rewrites the eviction mechanism: improveChain
   demotion never fired on any pod round; the holder was born
   chain-attached and the upgrade path was dead. Fixed with a real
   `else if (*tag_ptr > 0)` arm — the enabling fix for B'.

Verification: 112 gtests green (4 new deterministic B' tests + no
regressions from the now-live re-attribution), full gtestDebug green,
ddprof-test *ReferenceChain* family green. ONE pre-existing failure on
clean HEAD (proven via git stash, 3/3 runs):
AggressiveLeakReferenceChainTest.shouldOpenSearchGateOnAggressiveHeapWideGrowth-
WithNoLeakCandidate — urgent-OOM-gate test unrelated to B'; needs its own
investigation (user flagged). spotlessApply clean. NOT COMMITTED.

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
1b. DONE this session, committed+pushed: per-hop retention-edge field
   names (4d473e727) + memory sync; pod round 7 verified both prongs
   live with interception still zero (ev-leaktag-onpod-round7) and the
   user-picked fixes implemented and pushed (c6635fe0e: DESCENT_HOPS
   6->16 + JNI_GLOBAL anchors in the rotation tier; 9d3d0afe6 memory
   sync). One slow-suite failure en route was the known intermittent
   hysteresis family (candidate never qualified; green on rerun).
2. DONE (previous session, checkpointed now): pod round 8 verified on
   RENAMED pod prof-analyzer-hotdog-jb1-668df5bcff-f75l8 (JVM 4445,
   agent 1.66.0-SNAPSHOT~e188d0ff7f): both prongs live, walks
   un-truncated at 16 hops (per-pass edges 10→3608, rotation cycling
   different anchors), tagging healthy (klass_id=5 tid=4655 tagged=8
   max_size=78MB), interception STILL ZERO — and the app's retention
   shape was found in its bytecode: ProfileAnalyzer.LEAK_BUFFER, a
   static final List<byte[]> wrapped in Collections.unmodifiableList,
   3-4 hops from the root static = textbook prong-2 (see
   ev-leaktag-onpod-round8). Local scenario intercepts the identical
   shape, so the machinery is sound in-process — the suspect is WHICH
   anchors enter the anchor tier (wrapper never admitted root-attached /
   root_kind misclassified / root-attached entry replaced by a
   chain-attached one via improveChain).
3. DONE this session: round 9 verified (ev-leaktag-onpod-round9).
   Anchor diagnostic answered: tier = 76 machinery statics, NO holder,
   zero app classes. UPLOADED recordings contain 12 ReferenceChain
   events with working edge names + HeapLiveObject events with leakTags
   on the 78MB leak chunks — the ORIGINAL zero-events question is
   RESOLVED; the machinery cohort's retention is fully explained
   (Mac/HmacCore ThreadLocals, charset constants). Local pod chunks are
   a bad source for dump-time events (q-heapliveobject resolved: use
   uploads only; jfr print crashes on ReferenceChain — use JMC API).
   ROOT CAUSE of the remaining gap isolated in code:
   find-anchor-holder-eviction (parent_tag==0 is unidirectional;
   improveChain evicts root-attached holders; re-root refused at
   referenceChains.cpp:2376).
4. DONE this session: B' implemented, committed (6f3c6cc2e), deployed,
   and round-10 VERIFIED live (see ev-leaktag-onpod-round10 + the round-10
   blocker chain). Round-10 response (user-picked A+B) committed and
   pushed: 8888e6d42 (TEMP CANARY_NO_PROGRESS_PASS_LIMIT 3→30 revert —
   the suspected restart driver) + 04539b821 (collector-first anchor
   ordering — the collector's root-attached cohort no longer starved by
   the cap-pinned at-risk flood; truncated passes fall on the FIFO suffix
   which the requeue path protects).
5. DONE this session: round 11 verified (ev-leaktag-onpod-round11): A
   WORKED (search lifetimes up; cycle_complete=1 REPEATEDLY — sweep laps
   complete for the first time ever on this pod), B is a production no-op
   (real GetObjectsWithTags returns unspecified order — the starvation
   model was mock-order-based; requeue still works, order-independent).
   The candidate flapped out once (slope=-47.3 while the heap marches to
   OOM — suspected self-reinforcing dropout via boost-clearing) then
   RE-QUALIFIED on its own (~20:45 UTC). DECISIVE: at 21:10 UTC the
   wrapper WAS walked with ZERO interception → "not admitted/not
   eligible" REFUTED. Round-12 diagnostic prepared+committed+pushed
   (8ca24a524: holder_class naming via GOTW on referrer_class_tag +
   admission-sequence trace (klass_id x fresh/leak/already, 48 entries) +
   per-anchor walk outcome line).
   NEXT: user deploys 8ca24a524 → round 12. READ THE DIAGNOSTIC — the
   three outcomes and their fixes:
   (a) holder_class != ProfileAnalyzer → every walked wrapper is a decoy;
       the leak wrapper is never selected → collector-lottery problem →
       fix = raise STATIC_ANCHOR_ROTATION_BUDGET (4→16, nearly free under
       the GOTW floor) or prioritize by holder size.
   (b) holder_class = ProfileAnalyzer + walk outcome edges=0 truncated=1
       → budget starved before the descend → fix = per-anchor budget
       reservation or anchor-count reduction.
   (c) holder_class = ProfileAnalyzer + edges>0 + [B entries seen_as=0
       (fresh) → chunks enumerated but UNTAGGED at walk time → tag-lifetime
       problem (tagLeakInstances vs walk timing) → a wholly different fix.
   Fallback still queued: option C (sweep-cursor persistence across
   restarts) — only if restarts remain the blocker after A.
   ALSO: investigate the pre-existing AggressiveLeak urgent-OOM-gate
   failure (3/3 on clean HEAD).
   SUPERSEDED: user deploys 04539b821 → round 11: watch for (a) restarts spacing
   to ~30+ min (limit 30) and the sweep reaching cycle_complete=1 with
   cursor past ProfileAnalyzer's class, (b) the LEAK_BUFFER
   UnmodifiableRandomAccessList wrapper admitted root-attached STATIC
   and walked by the collector picks, (c) `leak-tag intercepted` → the
   first LEAK chunk's chain (static_field → ... → byte[]). Fallback if
   restarts persist: option C (sweep-cursor persistence across
   restarts) — NOT yet designed. ALSO: investigate the pre-existing
   AggressiveLeak urgent-OOM-gate failure (3/3 on clean HEAD).
4b. SUPERSEDED: user picks the anchor-eviction fix. Original options A/B were
   re-evaluated after a standards survey (this session, see
   find-attribution-standards-survey + find-anchor-live-feed-design):
   **A refuted** (freezes one attribution where every standard system
   re-derives or queries — JFR enumerates its root set fresh at every emit,
   source-verified; MAT computes paths on demand; dominator-tree
   attribution is offline-only per LeakCanary docs; dynamic-SSSP theory
   says exact incremental path labels are hopeless), **B minimal-diff
   fallback**, **B' (live feed) recommended**: the sweep's static-edge
   callback pushes frontier-present-but-chain-attached holder tags into a
   bounded FIFO; walkStaticFieldAnchors drains it; anchor selection stops
   reading parent_tag/root_kind → eviction structurally impossible.
   Verify the at-risk filter shrinks the population (TEMP counter) before
   sizing the FIFO. Then implement + gtest + deploy → round 10: watch
   `leak-tag intercepted` and the first LEAK chunk's chain
   (static_field → ... → byte[]).
5. TEMP reverts before finalizing (list below).

## TEMP — MUST REVERT before finalizing

- ~~`CANARY_NO_PROGRESS_PASS_LIMIT` 30 → 3~~ REVERTED this session (commit
  `8888e6d42`) — round 10 showed the TEMP value 3 abandons an unfound
  canary every ~3 min at 1 pass/min, and each restart resets the sweep
  cursor so the lap never reached the leak holder's class.
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
- TEMP per-anchor diagnostic in walkStaticFieldAnchors (c9a57f681):
  class signature + chain shape per walked anchor — remove once round 9
  names the tier-membership answer. KEEP for round 10 (it names the
  at-risk anchors B' now feeds into the walk).
- TEMP (round 12, commit 8ca24a524, deployed tomorrow): wrapper-class
  anchor trace - holder_class via GOTW on referrer_class_tag + the descend
  walk's admission sequence (klass_id x seen_as, 48 entries) + per-anchor
  walk outcome (edges/truncated). Round-11 watch data that shaped it: at
  21:10-21:12 UTC the wrapper WAS walked (2 lines) with ZERO interception -
  so "not in the eligible set" is REFUTED; the diagnostic must answer
  whether the wrapper walk enumerates list -> elementData -> chunks at
  all, and whether enumerated chunks carry leak tags at that moment.
  Remove once the pod answers the wrapper question.
- TEMP (B', this session): static_anchor_fifo_size/drained/pushed_total
  fields in runPassManualWalk's rotation_candidates TEST_LOG — remove
  after round 10 sizes the at-risk population.

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

Pod `prof-analyzer-hotdog-jb1-668df5bcff-7h5n9` in `profiling-stg`,
container `prof-analyzer`, JVM 77972 (round 9 verified on c9a57f681, see
`ev-leaktag-onpod-round9`). Pod clock is UTC (2h behind local).
Verify the deployed build via a per-iteration log field (e.g.
`ema_call_ms=` in every gotw line) BEFORE interpreting event-driven
logs — round 3 saw one stale-build deploy (JVM 44624 ran the old
build; the redeploy as JVM 48355 had the right one).

JFR: use `kubectl cp` from `/tmp/ddprof_root/pid_XXX/jfr/` (NOT jcmd).
Or use profiling toolkit `download.py` for uploaded profiles.
