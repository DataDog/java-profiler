---
id: find-attribution-standards-survey
type: finding
status: confirmed
depends_on: [find-anchor-holder-eviction]
related: [find-holistic-design-issues, find-jvmti-heap-walk-stw-vmop, find-already-admitted-blocks-deeper-chain]
tags: [survey, methodology, attribution, dominator-tree, dynamic-graph-algorithms, anytime-search, jfr, mat, leakcanary, NEW-THIS-SESSION]
created: 20260914
updated: 20260914
---

# Survey: how standard tools and theory answer "which reference chain explains retention"

Motivated by find-anchor-holder-eviction's fix options (A sticky / B
registry): user asked to check standard solutions (JVM and non-JVM,
including bleeding-edge research) before picking.

## Standard tools (source-verified)

- **JFR OldObjectSample / LeakProfiler** (openjdk/jdk
  `src/hotspot/share/jfr/leakprofiler/`, read at master 2026-09): keeps NO
  persistent path attribution. At every emit,
  `PathToGcRootsOperation::doit()` runs at a safepoint, enumerates the live
  root set FRESH (`RootSetClosure` feeding `BFSClosure`), ONE BFS over the
  live graph — heap-proportional EdgeQueue (5% of heap, min 32MB),
  first-path-wins mark bits (`closure_impl` marks on first visit → one
  path/object, BFS = shortest), DFS fallback when the queue fills,
  `GranularTimer` deadline. The attribution lives only for the operation;
  re-derived wholesale next emit. Nothing can go stale because nothing
  survives.
- **Eclipse MAT** (help.eclipse.org, `IPathsFromGCRootsComputer`): opposite
  tradeoff — stores the FULL reference graph of the snapshot, computes
  shortest paths ON DEMAND at query time (user can exclude weak/soft at
  query time, not baked in at walk time). Multiple paths remain available.
- **LeakCanary/shark** (square.github.io API docs): dominator tree
  "computed with Lengauer-Tarjan, which needs the whole graph up front…
  meant for tools running on a workstation, not for on-device analysis".
  MAT/Chrome DevTools/JProfiler all use dominator tree + retained size for
  attribution; MAT's "accumulation point" (object whose retained size dwarfs
  its largest child) is the principled version of our holder/growth-gating
  heuristics.

Common thread: **no standard tool keeps a long-lived, mutable
single-attribution per object.** JFR: recompute-often, persist-nothing.
MAT/shark: persist-everything, compute-on-demand. Our FrontierTable is a
third design — persist one guess per object and keep overwriting it — and
the anchor-tier eviction is the direct consequence.

## Theory (dynamic graph algorithms)

- Even–Shiloach decremental SSSP (JACM 1981): O(mn) total update time, best
  for three decades; near-linear improvements are heavy machinery.
- Fine-grained optimality of partially dynamic SSSP (arXiv:2407.09651,
  2024): conditional lower bounds — incremental/decremental exact SSSP
  can't asymptotically beat recompute in general. Fully dynamic APSP
  (arXiv:2306.02662; SODA 2023 hop-restricted) is further from practical.
- Dynamic dominator tree maintenance (Georgiadis–Italiano et al.
  arXiv:1604.02711; ESA 2019 low-high orders): exists, but with O(mn)-flavored
  conditional hardness even on DAGs — research-grade, deliberately avoided
  by every practical tool.
- Anytime/contract search (AIJ 2008 "Anytime search in dynamic graphs";
  Anytime Contract Search; Deadline-Aware Search): budget-sliced graph
  search under deadlines where the search frontier is DECOUPLED from answer
  bookkeeping and answers are recomputed at query time, not accumulated as
  persistent mutable guesses.

## Derived design principles (used to re-evaluate fix options)

1. Re-enumerate what is cheap to re-observe; maintain nothing you can
   derive fresh (JFR root set; our sweep lap re-proves every static edge).
2. A per-object single attribution is at best a heuristic stand-in for a
   dominator; it is known-unmaintainable incrementally, so it must NEVER
   gate selection (who to walk) — only reporting (which chain to print).
3. Lazy labels + bounded recompute is the theory-sanctioned compromise
   under mutation (matches our sweep-lap re-registration pattern).
4. Hop-bounded walks (DESCENT_HOPS=16) are their own cheaper problem
   class (SODA 2023 hop-restricted dynamic paths).

## Verdicts on the anchor-eviction fix options

- **A (sticky durable roots): REFUTED** from all three directions — freezes
  one guess harder, where every standard system re-derives or queries;
  still does not cover admission-order eviction. Do not implement.
- **B (static-attachment registry): defensible** — lazy per-lap
  re-derivation of the static-attachment fact, the sanctioned pattern; but
  keeps walk-set selection coupled to the mutated table and preserves the
  collector's full-frontier wrapping scan.
- **B' (live feed): selected design** — see
  find-anchor-live-feed-design; the confluence of all surveyed precedents.

Note (parked): the MAT accumulation-point pattern suggests a long-term
dominator-flavored retained-size ranking as the principled holder-selection
signal; out of scope for this fix.
