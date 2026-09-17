---
id: find-rotation-resize-blindspot
type: finding
status: confirmed-and-fixed
depends_on: [find-priority-queue-starves-bfs-crawl]
related: [find-priority-queue-starves-bfs-crawl, q-resize-instrumentation-rescan-priority, find-leak-tag-pool-implementation]
tags: [root-cause, fix, rotation, growing-collections, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# Rotation is blind to container RESIZES (the user's challenge was correct)

A fixed-slot fixture array was proposed to make the scenario pass; the
user challenged it ("what if an ArrayList grows in the real app?") - the
challenge was correct on both counts: the workaround was hiding the
requirement, AND the production path was genuinely broken.

## The structural blindspot (all links observed live in the child JVM)

For a growing collection (ArrayList swaps elementData, HashMap resizes
table):
1. The live holder (the list) is EXPANDED with a FROZEN children set - the
   NEW backing array is never admitted as its child.
2. The fanout only ever contains parents of watched instances ALREADY
   admitted - i.e. the OLD, now-dead backing arrays (a growing fanout of
   corpses: 11k->17k->23k entries observed, mostly machinery + dead).
3. The blind lap (the only thing that re-walks arbitrary EXPANDED holders)
   is ~table_size/budget passes deep - never reached in any window.

Net effect: chunks added after a resize are NEVER admitted; tagged
instances below them never intercepted; zero leak-correlated chains.
This plausibly blocked the POD too (its leak buffer is a growing
synchronizedList).

## Fix set (all in referenceChains.cpp)

1. FAIR-SHARE ROTATION: collectStaleExpandedEntriesForRotation() gives the
   fanout at most ceil(max_count/2) and the blind lap the rest - an
   unbounded fanout-first policy starves the lap, reproducing the
   starvation bug one level down (observed: rotation admitted edges in
   only 4 of 206 passes with an 11k fanout).
2. FANOUT HYGIENE: fanout entries whose frontier slot is gone or ABANDONED
   (clear() marks ABANDONED, does not remove - lookup still succeeds) are
   erased during selection.
3. ANCESTOR FANOUT: trackLeakAccumulation() now inserts every ancestor up
   to the root-attached entry (bounded by hop_cap, watched-admissions
   only), because the direct parent is not the part of the holder chain
   that stays live.
4. requeueChainRootForRotation(): the deterministic piece - on every poll,
   each candidate's representative chain ROOT is enqueued into
   _priority_expand (bounded by MAX_LEAK_CANDIDATES, de-duplicated). The
   holder's re-walk then admits each new backing array as it appears.
   This is the cheap, profiler-native version of the user's
   resize-instrumentation idea (q-resize-instrumentation-rescan-priority):
   the candidate chain already knows the holder - no bytecode needed.

Observed with all four in place: 4 leak-tag interceptions at depth 2
under the CURRENT elementData, correlated discoveries recorded with
noise-slot eviction. Remaining last-mile (candidate hysteresis aging)
tracked in find-test-seam-aliasing.
