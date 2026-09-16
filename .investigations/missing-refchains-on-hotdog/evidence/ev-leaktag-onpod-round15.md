---
id: ev-leaktag-onpod-round15
type: evidence
status: confirmed
depends_on: [ev-leaktag-onpod-round14-results, find-tier1-tail-starvation]
related: [find-fresh-lane-verification]
tags: [implementation, fresh-lane, round-15, NEW-THIS-SESSION]
created: 20260916
---

# Round 15: fresh-admission priority (queue lane) — implementation (ev)

Direction from the round-15 diagnosis (see ev-leaktag-onpod-round14-results.md,
find-tier1-tail-starvation.md). Implemented same-turn, all gtests green
(348 OK: 347 + FreshContainerWalkedBeforeFairBacklog), spotless clean,
buildRelease -Pskip-tests clean.

## Design (as implemented, after one discarded approach)

**Fresh-admission queue lane** in collectStaticFieldAnchorsForRotation:

- `std::deque<jlong> _static_anchor_fresh_queue` (cap 1024, front-drop on
  overflow): every addToStaticAnchorIndex() append pushes here; restart
  and test-reset clear it. The queue is always a contiguous ordered SUFFIX
  WINDOW of the anchor index (both append together; removals only ever
  pop the front), which lets the drain recover each entry's index
  position in O(1) by lockstep counting from idx_size - queue_len (with a
  defensive std::find fallback if the invariant ever breaks).
- Selection order: leak-tagged (tier 0) → fresh (queue order = admission
  order) → container fair cursor → other fair cursor.
- The drain pops EVERY entry (each anchor gets exactly ONE first look):
  kept if eligible AND (container-shaped OR not-yet-classified) AND
  budget room; dropped otherwise (dead/demoted/queued/leak-tagged are
  dropped — the leak tier owns those via the index scan; classified
  non-containers drop to the other tier; budget-exhausted drop to their
  fair tier's ordinal). Nothing is ever lost — a spent first look only
  removes urgency.
- Not-yet-classified rides the lane: the wrapper admits one pass before
  reconcileAnchorClassShapes() can classify its class; unclassified is
  bounded in practice (shape cache is JVM-lifetime; churn classes are
  lambdas with no static fields).
- Fair-tier consumption skips fresh-kept tags (no double-select within a
  call) but advances the cursor past them.
- `STATIC_ANCHOR_ROTATION_BUDGET` 16 → 32: the measured fresh-container
  admit rate (~10-37/pass) exceeded 16, which would make the lane a
  growing backlog — the same starvation one level down. STW safety does
  NOT depend on the number: walkStaticFieldAnchors stops at the per-pass
  deadline and requeues (selection size and walked size are decoupled —
  observed on-pod round 10: "walked 6-16 of selected 20").

**Discarded first attempt — a positions-since-mark watermark:** simpler,
but a stale mark reorders selection when state leaks between units (the
StaticAnchorRotation* test caught it in test-order runs: a mark of 1 left
by the previous test demoted anchor 101 behind 104 — {101,104} became
{104,101}). The queue is per-anchor: each anchor's first look happens
exactly once, in admission order, regardless of stale state. Lesson
(reinforces find-test-seam-aliasing): singleton test-order sensitivity is
a design smell for production state that outlives a search.

## TEMP diagnostics retained for the pod round

- `anchorTierHistogram index=… leak_tier=… fresh_tier=… fresh_queue=…
  container_tier=… other_tier=… budget=…` — fresh_queue is the PRE-drain
  length (the admit-rate signal); fresh_tier is what the lane kept. THE
  gate: if fresh_queue consistently ≫ budget, the lane runs as a backlog
  and the wrapper waits fresh/budget passes (bounded, but belongs in the
  next analysis); if fresh_tier is 0 while the wrapper admits, the lane
  is not firing at all (shape/eligibility bug).
- Round-13 LEAK_BUFFER probe, round-12 walk klass_id logs, container
  classification log: all retained.

## Pod verification plan (next deploy, user builds + deploys)

Use `kubectl logs -f` streams (buffer rotates ~4 min at the current 16k
lines/min; --since windows burned ~20 min in round 14):

1. `anchorTierHistogram` — fresh_queue vs 32 budget (the gate above).
2. `LEAK_BUFFER probe … sweeping holder class …ProfileAnalyzer;` →
   `wrapper_tag=<tag>` (admitted, this JVM's crossing) — next lap after
   the crossing, wrapper_tag should be nonzero when a search is live.
3. `walkStaticFieldAnchors anchor … class=…Collections$SynchronizedRandomAccessList`
   within 1-2 passes of the admission (the fresh lane working).
4. `leak-tag intercepted` / `auto-marked chain` /
   `drainPendingChainEvents drained>0` / datadog.ReferenceChain events.
5. `buildChainEvent false: target_tag=1073742079` should STOP once the
   wrapper's subtree expansion admits the tagged chunks.
6. If the wrapper still never admits: the sweep gate (class churn) has
   not reopened around a live search — watch static_sweep_gate lines.
