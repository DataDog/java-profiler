# Round 13 RESULTS: root cause of missing ReferenceChain events identified (ev)

Date: 2026-09-15, pod prof-analyzer-hotdog-jb-d9d8cf-rz992 (redeployed 17:27Z
with b5dd09675), container prof-analyzer.

## Probe results (decisive)

LEAK_BUFFER probe (JNI read of ProfileAnalyzer.LEAK_BUFFER each sweep chunk
pass) fired as designed:

```
probe: sweeping holder class Lcom/.../ProfileAnalyzer; at index 25301
probe wrapper_tag=0        (lap 1, pre-admission)
probe wrapper_tag=0        (lap 2, still pre-admission — chunk sweep
                           aborted or search restarted before the k8 edge)
probe wrapper_tag=198536 frontier_found=1 parent=0 root_kind=8 state=0
     leak_tag=0 depth=0 referrer_klass=29448
```

**The wrapper IS admitted root-attached STATIC_FIELD (root_kind=8, parent=0,
FRONTIER state)** — the sweep's k8 edge works. Admission is NOT the bug.

## The actual bug: deterministic anchor-selection tail starvation

Measured in one log window (134k-line buffer, 16 passes, single search):

- `root-attached STATIC_FIELD admit` lines: **4735** (and this window is
  mid-search) — sweep cursor 16596→22323 of 34310 classes, ~0.83 admits per
  class. Full-lap index size ≈ **28k anchors**.
- Anchor walks: **340** in the window = ~21/pass (budget 16+16), avg
  **81 edges** per anchor walk (max 2784) against effectiveBudget=3741 —
  the walk budget is already nearly saturated at 32/pass.
- Search lifetime: frontier 131k→250k cap at ~1.3-2k inserts/pass ≈
  **~190 passes** per search; collector coverage ≈ 190 × 21 ≈ **4k of 28k**
  (14%) per search, always from index position 0 (cursor reset on restart).
- The wrapper is admitted at sweep cursor 25301 (≈75% through the class
  array) → index position ≈ **12-21k** — **deterministically beyond the
  ~4k coverage of every search**. Fix B+C made the walk rate 8x faster but
  the selection ORDER (admission order = sweep class-array order) puts the
  leak holder at the unreachable tail. The old budget-4 lottery was
  actually a lottery; now it is deterministic never.

Why fix C (leak_tag priority) doesn't help: the wrapper entry has leak_tag=0
(the [B chunks carry leak tags, not their holder) — visible in the probe log.

## Downstream corollaries (all observed, all explained)

1. BFS expansion of the wrapper subtree is equally tail-starved: the wrapper
   is admitted mid-search into a pendingExpand FIFO that is already 148k
   deep; its subtree (ArrayList → elementData → chunks) is never expanded.
2. Zero `leak-tag intercepted` logs: no walk ever reaches a leak-tagged
   chunk (they are only reachable through the wrapper's subtree).
3. `_leak_parent_fanout`/leak_parents=4717 is mostly NOISE: fed by
   `seedLeakAccumulationForNewlyWatchedKlass`'s scan of [B entries ALREADY
   in the frontier — ordinary byte[]s admitted via root-reachable paths
   (kafka/netty buffers), each with fanout=1. The real chunks never get
   admitted, so their parents (elementData fanout=13, the wrapper) are never
   attributed. This also explains round-12's "all leak-accumulation
   selections fanout=1".
4. `pollWatchedTargets buildChainEvent failed ... reconstructChain failed
   for target_tag=8851/8853 klass_id=1`: **restartSearch() resets the
   frontier table and _next_tag=1 but does NOT clear
   _candidate_discovered_tags** (frontier tags of discovered watched-class
   instances). Stale tags from a previous search resolve (lookup returns
   found for any idx < table_size) into zeroed/reused slots → dangling
   parent chains → reconstructChain fails. Worse: when such a slot holds a
   live new-search entry, the poll can emit a chain event for the WRONG
   OBJECT — the likely origin of the earlier session's "noise [B instance"
   ReferenceChain event. Hygiene bug to fix regardless.

## Fix options considered

A. **Anchor-selection priority by class shape**: index only "interesting"
   anchors — exclude leaf classes (String/Class/boxed/primitive-arrays:
   identifiable from a fixed well-known class list) and/or prioritize
   collection-shaped holders (the wrapper is a List). Shrinks the effective
   cohort to (est.) 1-3k; coverage 4k/search then reaches the wrapper within
   one search. Implementation: shape must be resolved OUTSIDE heap callbacks
   (JNI in callback = illegal); lazy per-class cache (class_tag → shape),
   filled by a bounded post-sweep resolver pass; collector sorts
   (leak_tag, shape, cursor-fairness).
B. **Cross-restart coverage rotation + budget tuning**: persist a selection
   start fraction across restarts; measured avg 81 edges caps the walk at
   ~46/pass (3741/81), so full 28k coverage needs ~6-14 search lifetimes
   (hours). Cheap but slow convergence.
C. **One-shot unrestricted whole-heap pass at search start**: a single
   whole-heap FollowReferences would descend class→static→wrapper→…
   →chunks and fire leak-tag interception for everything in one bounded
   STW. Highest value per cost, but seconds-of-STW once per search and
   frontier-cap interplay (millions of edges vs 250k cap) need design work.
D. A+B combined.

## Also unchanged

- Pre-existing SIGSEGV in SearchRestartTest.UrgentOOMProjectionBypassesCandidateGate
  (clean-HEAD repro) — separate issue.
- Sweep-cycle `cycle_complete=1` never logs (_static_field_sweep_cycle_truncated
  not reset by restartSearch) — latent, unfixed.
