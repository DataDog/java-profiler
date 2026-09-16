---
id: find-wrapper-demotion-self-parent
type: root-cause
status: confirmed
depends_on: [find-fresh-lane-verification, ev-leaktag-onpod-round15-results]
related: [find-urgentoom-null-fn-mislabel, find-round16-endgoal-verification, find-refchains-log-flood-configurable]
tags: [root-cause, referenceChains, improveChain, self-edge, at-risk-fifo, round-16, FIXED, NEW-THIS-SESSION]
created: 20260916
updated: 20260916
---

# Find: wrapper frontier entry demoted to a self-parented chain-attached entry (round 16 — FIXED + VERIFIED ON POD: wrapper root-attached, walked, leak-tag interceptions, leak-correlated events)

Parent: find-fresh-lane-verification (the round-15 verification that
exposed this). Evidence: ev-leaktag-onpod-round15-results.md (measured
live on pod cgdtx, 05:44-06:23Z 2026-09-16, streams in
/tmp/r15_stream.log, r15_stream2.log, r15_tail.log). Implementation:
commit 4afe870a2, gtests 118/118.

## STATUS: implemented (awaiting user deploy + pod verification)

- Fix A: improveChain()/reparentToDurableRoot() refuse parent==tag
  (self-edge — mutex == this), counted in
  FrontierTable::selfEdgeGuardSkips (2 refusals per delivered callback
  edge; logged per pass as self_edge_skips in rotation_candidates).
  With the guard, the wrapper's entry stays root-attached → the
  collector's parent_tag==0 filter keeps selecting it.
- Fix B: B' at-risk FIFO entries carry their klass (AtRiskAnchor);
  per-class quota 64 (a full 1024 FIFO holds ≥ 16 distinct classes);
  drain/requeue maintain occupancy exactly; quota drops counted + logged
  (static_anchor_fifo_quota_drops_total). The wrapper's pushes land
  while the floods self-throttle.
- Pod verification channels: self_edge_skips climbs (2 per wrapper
  subtree walk per pass), pushAtRiskStaticAnchor klass_id=28366 lines
  with fifo_size ≪ 1024, wrapper probe returns to parent=0 root_kind=8,
  walkStaticFieldAnchors … SynchronizedRandomAccessList lines resume,
  then the interception cascade (seen_as=1, entry.leak_tag, chains with
targetTag=leak tag, canary resolves).

## The defect shape (all measured, not deduced) [historical record]

In search #2 the wrapper admitted ROOT-ATTACHED (parent=0 root_kind=8)
and was walked once. In every LATER search, the LEAK_BUFFER probe at each
holder-class crossing returns:

    wrapper_tag=2469/2679/2853 frontier_found=1 parent=<SAME TAG>
    root_kind=0 state=1 leak_tag=0 depth=1-3 referrer_klass=28366

- The entry is CHAIN-ATTACHED (parent != 0) with **parent equal to the
  wrapper's own tag** — a self-edge.
- The collector's eligibility filter (parent_tag == 0, root_kind
  STATIC_FIELD/JNI_GLOBAL) therefore skips it forever within the search
  → zero wrapper re-walks across 3 holder-class crossings (sweep laps
  re-cross index 24611-24874 every ~10-20 min).
- maybeUpgradeRootAttachedRootKind refuses parent_tag != 0 by design
  (B' comment) — so even the sweep's own re-encounter cannot restore the
  root-attached shape.

## The designed repair is dead too: B' FIFO cap-pinned by floods

The at-risk push (sweep's static edge onto an already-admitted
chain-attached entry → pushAtRiskStaticAnchor → FIFO drain walks it)
is exactly the repair for this demotion. Measured: the FIFO sits at its
1024 cap, flooded by klass 1 (1396 pushes), klass 215 (1063), klass 1733
(fifo_size 988-1024) — the wrapper's class 28366 got ZERO pushes through
(dropped at the cap check). Round-10 already observed "a cap-pinned
at-risk flood"; the per-klass counts are now measured.

## Why this blocks the end goal

The wrapper's chunks now carry leak tags (tagged=36-48, re-established
after each restart by the poll loop's correlate-not-retag state machine —
that machine itself verified working: no tag → SetTag branch observed
re-growing after releaseSearchTags collapses the count 137→13). ONE
wrapper walk while the chunks hold leak tags fires the heapReferenceCallback
leak-tag interception (seen_as=1) → frontier entry with leak_tag set →
chains built with targetTag=leak tag → correlateAdmittedLeakTag → the
canary's leak-tag target resolves → ReferenceChain events correlated with
HeapLiveObject.leakTag. Until then, the emitted events carry frontier-tag
targets (leak_correlated=0) — real chains, no leak correlation.

## Root-cause candidates for the demotion (round-16 work, in order)

1. **A self-edge insert: some path inserts/overwrites the wrapper's
   entry with parent_tag == its own tag.** Suspects: the leak-accumulator
   fanout/seed insert (trackLeakAccumulation — the fanout-insert path
   round-13 flagged as fanout=1 noise; a parent==child pair would be its
   degenerate case), improveChain's shallow→deep replacement (the
   DemotionPush test shape), or reparentToDurableRoot. Repro: a gtest
   admitting a root-attached static holder, then driving the suspects,
   asserting parent stays 0/root_kind stays 8 while the entry is live.
2. **B' FIFO per-class quota**: cap each klass's occupancy (or evict the
   oldest same-klass entry on push) so klass-1/1733/215 floods cannot pin
   the 1024 cap. Independent of (1) — either fix alone unblocks the
   re-walk; both cover each other's failure mode.

## Note on the probe's parent==tag reading

frontier_found=1 with parent==tag is what the probe READS — whether the
table literally contains a self-parented entry for the wrapper or the
lookup is landing on a related entry (the wrapper's child keyed
colliding) is part of the round-16 repro: dump the entry for the exact
tag in the gtest before assuming the self-edge is literal.
