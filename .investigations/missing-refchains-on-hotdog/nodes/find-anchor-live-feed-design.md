---
id: find-anchor-live-feed-design
type: finding
status: implemented
depends_on: [find-anchor-holder-eviction, find-attribution-standards-survey, find-option-c-descend-walk-design]
related: [find-isqueuedforrotation-quad-scan, find-priority-queue-starves-bfs-crawl]
tags: [fix, design, referenceChains, anchor-tier, live-feed, fifo, eviction-proof, NEW-THIS-SESSION]
created: 20260914
updated: 20260914
---

# Fix B' (recommended, NOT yet picked/implemented): feed the anchor walk-set from live enumeration, not from the mutated attribution table

Born from the standards survey (find-attribution-standards-survey): JFR
enumerates its root set fresh at operation time, never cached; theory says
per-object attribution is a heuristic that must not gate selection.

## Design

- **Push site**: heapReferenceCallback's root-like branch (the static
  sweep's class→field edge arrives with negative class referrer tag,
  referenceChains.cpp ~:2089 comment). When the edge's TARGET tag is in the
  frontier but its entry is NOT root-attached STATIC (the at-risk
  population — dual-reachable holders like LEAK_BUFFER; machinery statics
  stay on the existing collector path), push the target tag into a bounded
  preallocated FIFO (dedup via PriorityExpandSet pattern: fixed
  open-addressing, no allocation after construction).
- **Drain site**: walkStaticFieldAnchors drains the FIFO instead of
  collectStaticFieldAnchorsForRotation's wrapping-cursor full-table scan
  (190k+ entries per selection on pod).
- The anchor tier no longer reads parent_tag/root_kind AT ALL → the
  find-anchor-holder-eviction mechanism (admission-order birth +
  improveChain demotion + refused re-root) becomes structurally impossible.
  Both eviction orders covered by construction.

## Properties (argued, partially unverified)

- Fair by construction: FIFO order = sweep-cursor order; no priority
  starvation class. Bounded memory, O(1) push in the callback (no malloc,
  no lock — engine discipline already serializes drivers).
- Push rate ≪ drain rate REQUIRES the at-risk-only filter to actually
  shrink the population: INFERRED, not measured — the planned TEMP counter
  on the static-edge-onto-chain-attached path (already in
  find-anchor-holder-eviction's open verification) must confirm before
  sizing the FIFO. Without the filter, pushes (~1000+/chunk enumerated
  statics) would overwrite entries before the walk drains them.
- Perf win vs current: O(k) FIFO drain replaces the collector's
  full-frontier scan per pass (aligns with the project's O(N) linear-scan
  cutoff rule).
- **Chain correctness unaffected**: the holder's own frontier entry may
  remain chain-attached (its thread-path chain is a complete chain to a GC
  root; reparentToDurableRoot handles equal-depth durable re-parenting).
  Interception only needs the walk to ENUMERATE the tagged chunks —
  independent of the holder's own entry shape.
- **Scope**: JNI_GLOBAL anchor eligibility stays on the existing table
  path (that cohort is machinery anyway); a root-callback feed can be added
  later if dual-reachable JNI-global holders ever appear.

## Status

IMPLEMENTED 20260914 (design/review/implement/review loop, uncommitted).
Final shape:
- Members: _static_anchor_fifo (deque) + second PriorityExpandSet
  instance (cap 1024) + STATIC_ANCHOR_FIFO_DRAIN=16 + cumulative
  _static_anchor_fifo_pushed counter. pushAtRiskStaticAnchor() shared by
  both push sites (cap-drop + dedupe).
- TWO push sites (both required — the "next lap re-pushes" assumption
  was FALSIFIED: the sweep gate re-laps only while the class count is in
  flux, so a post-lap demotion in a stable-class JVM never sees another
  static edge): (1) DEMOTION TIME — in the improveChain success path when
  the replaced entry was root-attached durable (rootKindDurability >= 2);
  (2) SWEEP TIME — the STATIC_FIELD edge onto a chain-attached entry on
  the failed maybeUpgradeRootAttachedRootKind.
- Both sites were UNREACHABLE until find-already-admitted-blocks-
  unreachable's nesting fix (same session) — the enabling fix.
- Drain/requeue: runPass drains FIFO FIRST (16/pass) ahead of the
  collector, one GOTW batch for all; walkStaticFieldAnchors gained an
  `unwalked` out-vector (resolved-but-unwalked tags at the truncation
  break — a consumed index is useless because GOTW drops dead tags in
  its own order); runPass requeues the unwalked ∩ drained-fifo tags to
  the deque front (lookup-filtered, <=16x20 scan). No re-push on
  successful drain (next lap re-pushes; the sweep-push site covers it
  when laps recur).
- Review-corrected: the collector STAYS (root-attached statics incl.
  LEAK_BUFFER's unmodifiableList wrapper + JNI_GLOBALs are its disjoint
  cohort — the node's earlier "O(k) drain replaces the 190k scan" claim
  was WRONG, scan cost unchanged).
- Verification plumbing: per-pass rotation_candidates TEST_LOG extended
  with static_anchor_fifo_size/drained/pushed_total (TEMP — remove after
  round 10).
- Tests (referenceChains_ut, all green): DemotionPushFiresWhenImproveChain-
  EvictsRootAttachedStatic (real expandFrontier batch walk, includes
  no-double-push on re-walk), SweepPushFiresOnStaticEdgeOntoChainAttached-
  Holder (full runPass: sweep delivers, rotation drains same pass, entry
  never re-attributed), AtRiskAnchorFifoDrainAndWalkIntercept (drain+walk
  intercepts leak 3 hops below a chain-attached holder the collector
  demonstrably cannot select — negative control), TruncatedAnchorWalk-
  RequeuesUnwalkedFifoTags (budget-truncated walk reports exactly the
  un-walked tag; requeue restores FIFO order + set consistency).
  A full-E2E runPass test was ABANDONED: the mock's root-phase walk order
  + stale-expanded rotation queueing (isQueuedForRotation floods on tiny
  graphs) make the eviction shape non-deterministic there — the
  deterministic drives + the slow-suite scenario family are the coverage.
- Verified: 112 gtests green, full :ddprof-lib:gtestDebug green, ddprof-test
  *ReferenceChain* family green EXCEPT a pre-existing failure on clean
  HEAD (AggressiveLeakReferenceChainTest.shouldOpenSearchGateOnAggressive-
  HeapWideGrowthWithNoLeakCandidate, fails 3/3 with changes stashed —
  unrelated to B', flagged to user). spotlessApply clean.

NEXT: user review → commit → deploy → round 10: watch
`static_anchor_fifo_pushed_total` (sizes the at-risk population — the
push-rate caveat was inferred, now measurable) and `leak-tag intercepted`
→ the first leak chunk's chain (static_field → ... → byte[]).
