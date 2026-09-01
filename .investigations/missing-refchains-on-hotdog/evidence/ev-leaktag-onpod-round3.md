---
id: ev-leaktag-onpod-round3
type: evidence
status: verified-partial
related: [find-ema-batch-collapse, find-rotation-resize-blindspot, find-depth0-durable-root-upgrade-gap, find-leak-tag-pool-implementation]
tags: [pod-logs, on-pod, post-fix, live-verification, proportional-batch, leak-tag, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# On-pod round 3 (build 663784137, JVM 75258, started 07:03:38Z)

Deploy note: first "redeploy" (07:03:29Z) restarted the JVM but left the
Aug-23 ddprof binary in place - the extracted lib had ZERO round-2+ markers.
After the real binary copy, JVM 75258 loaded the 663784137 build (verified:
requeueChainRootForRotation=4, maybeUpgradeRootAttachedRootKind=4,
ema_call_ms, static_sweep_gate all present in the extracted .so).

## Verified working on pod (2.5h window)

- **Proportional batch control**: gotw batch 8-14, gotw_ms 18-21,
  ema_call_ms 19-20, next_batch 8-14 - stable, no AIMD collapse, no
  collapse to MIN. ~12 passes/min.
- **Static sweep**: full laps complete (resolved=33504 swept=33504
  cursor=0, repeatedly) - chunked sweep covers all 33.5k classes.
- **Depth-0 durable-root upgrade (NEW)**: 76 fires - 9(CONSTANT_POOL)->25
  (THREAD), 25->21(JNI_GLOBAL) - the root-like-edge upgrade path works in
  production.
- **Leak-tag pool**: 247 tagLeakInstances tagged lines (klass_id=4 [B],
  tids 7525x/7565x, ages 31-156s, sizes 24-16016, need_set=0 - stable
  waiters, pool not churning).
- **Discovered loop**: finds 8 live candidate instances per poll,
  discoveredCounts=[8,0,0,0,0].
- **Noise gate + emission**: buildChainEvent built THREAD(25)-rooted
  depth-1 chains for frontier-admitted byte[]s; transient (24) ones
  suppressed; TWO ReferenceChain events drained to JFR
  (`Profiler::dump reference-chain batch=1 write_dropped=0` x2, same
  target 6215 re-emitted from cache). ReferenceChain emission verified
  end-to-end ON POD for the first time.
- **Fanout tracking**: leak_parents=37619, fanout-inserts flowing
  (child_class_tag=-2 = byte[]).

## Not firing (the remaining last mile)

- `intercepted:` = 0, `recordDiscoveredInstance` = 0,
  `auto-marked chain` = 0, `requeueChainRootForRotation` = 0 (log line
  count; the function early-returns before its TEST_LOG when the tag
  isn't in the frontier).
- Recurring failure: `pollWatchedTargets buildChainEvent(tag=1073742076)
  -> 0` + `buildChainEvent false: target_tag=... not in frontier`.

## Root cause (evidence-backed)

The tagged instances and the frontier-admitted instances are DISJOINT
sets. Both bridges from "leak tag on object" to "frontier entry" require
the crawl to touch the object:
- interception fires in heapReferenceCallback only when the walk
  delivers an edge whose TARGET is leak-tagged;
- correlateAdmittedLeakTag fires only if the object already carries a
  frontier tag at tagging time.

On this workload the crawl admits ~15-40 edges/pass at ~12 passes/min
(~200-500 edges/min) against a 199k frontier; the 18 tagged instances
(age-priority-selected old machinery byte[]s - sizes 24-16016, the same
shape the local scenario's TEMP comment documented: "age-priority kept
re-selecting old machinery byte[]s while the young leak chunks churned
out") sit under holders the crawl has not reached in 2.5h.

KEY OBSERVATION for the fix design: the static sweep completes FULL
33.5k-class laps - raw JVMTI heap-walk throughput is NOT the wall; the
crawl's GetObjectsWithTags batch resolution + frontier admission is. A
dedicated intercept-only sweep (full-graph walk that reacts ONLY to
leak-tagged targets: record + admit that one edge, no batch tag
resolution, no frontier growth) would cover the whole graph per lap at
sweep-like cost and bridge the disjoint sets deterministically.

Also notable: the pod's own container was OOMKilled at 04:00:30Z (the
07:03 JVM start was the recovery) - there is real memory pressure on this
analyzer; [B as the leak candidate is plausible, but the tagged selection
landing on machinery byte[]s suggests the [B growth signal is dominated
by machinery churn, not one growing collection.

## CORRECTIONS + option retraction (user challenges, all verified)

- Elapsed was 32 MINUTES (JVM 75258 started 09:13:29Z), not 2.5h - the
  2.5h log window covered the stale JVM 44911 too. All counts (76
  upgrades, 247 tagged, 0 intercepted, 2 emitted chains) are from ~32
  min.
- Pass rate: passesRun=2803/32min ~= 88 passes/min (NOT ~12 - that was
  round-2's pre-proportional number). At ~15 edges admitted/pass that is
  ~1300 edges/min, ~40k edges in 32 min vs a 199k frontier. Disjoint-set
  observation stands, margin ~5x less dire than first stated.
- The tracker is in BASIC/canary-search mode: `blocked` (cpu pain
  budget) never fires; `shouldRunPass -> true (canary search, 0/1
  candidates found)` every iteration - the unfindable candidate[0] marker
  forces max cadence (the user's 30%+ CPU burn; see
  find-canary-search-forces-max-cadence).
- Option B (intercept-only full-graph sweep) RETRACTED: FollowReferences
  is a VM operation - a full-heap lap is one ~10s stop-the-world pause
  (find-jvmti-heap-walk-stw-vmop, jdk21 jvmtiTagMap.cpp:2379/:2934). The
  static sweep argument was invalid: it is a RESTRICTED walk over a tiny
  subgraph, not evidence about full-graph walk affordability.
- C does NOT reduce B's cost (irrelevant now) - but C attacks the current
  burn: retiring a churn candidate ends the forced canary-search
  cadence. Remaining lever for real candidates is crawl throughput:
  the per-pass cost is dominated by O(tag-map) GetObjectsWithTags scans
  (18-21ms x ~5/pass), not the walk itself.
