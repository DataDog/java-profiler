# Implementation Plan: Target Selection and Pause-Time Pacing

**Status:** Implementation plan (no code yet)
**Date:** 2026-07-07
**Jira:** [PROF-15341](https://datadoghq.atlassian.net/browse/PROF-15341)
**Companion docs:** [LiveHeapReferenceChains.md](LiveHeapReferenceChains.md) (design, Open
Questions 2/3/5 — read the "Proposed mechanism" paragraphs there first, this plan sequences
and pins them to files but does not re-derive them),
[LiveHeapReferenceChains-ImplementationPlan.md](LiveHeapReferenceChains-ImplementationPlan.md)
(Phases 0-7, already implemented — this plan continues past its Phase 7),
[LiveHeapReferenceChains-BenchmarkPlan.md](LiveHeapReferenceChains-BenchmarkPlan.md) (Phase 5
tuning matrix — separate, not duplicated here; Phase D below produces one new input to it).

## Scope reminder

Everything in the design doc's "Chosen design" section is implemented and unit-tested
(`ddprof-lib/src/main/cpp/referenceChains.h`/`.cpp`, wired into `Profiler::start()`/`stop()`/
`dump()`). Two concrete gaps remain, both already resolved *on paper* in the design doc's Open
Questions 2/3/5 as "proposed, not implemented":

1. **No target-selection feed.** `buildChainEvent(target_tag, ...)` (`referenceChains.h:666`)
   has no caller. Nothing decides which live object's chain is worth reconstructing and
   reporting.
2. **No pause-time pacing.** The per-pass edge budget (`_budget`) and the pass cadence fallback
   (`PASS_CADENCE_NS`, `referenceChains.h:419`) are fixed constants, explicitly labeled
   provisional, with no feedback from actual measured pause time.

This plan implements both. It does **not** re-run or duplicate Phase 5's benchmark-matrix work
(separate document, separate exit criteria) — Phase D below only wires a live SLO input; picking
the SLO's numeric value is still a Phase-5-style measurement task, called out explicitly where it
applies.

## Correction to the design doc's Open Question 3 mechanism, found while grounding this plan

The design doc's proposed bridging step reads: *"resolve K's stored representative `jweak` → if
still alive, `SetTag` it as a watched target → let the existing forward BFS in `runPass()` reach
it naturally... → reconstruct backward via the already-recorded `parent_tag` chain."*

Tracing `heapReferenceCallback()` (`referenceChains.cpp:562-584`) shows this doesn't work as
written: a tag is only assigned, and `parent_tag`/`depth` only recorded, on the branch where
`*tag_ptr == 0` (object not yet visited this search). If a candidate object is pre-tagged via
`SetTag` *before* the walk reaches it, `*tag_ptr` is already non-zero when the callback fires for
it, so the `*tag_ptr == 0` branch is skipped entirely — the real referrer edge (`parent_tag`,
`depth`) is never recorded, and the object is silently treated as if it were already a
previously-discovered, root-level entry. Reconstructing a chain from that tag would report an
empty/root chain regardless of the object's actual retention path — wrong, not just imprecise.

The fix is simpler than the original proposal, not more complex: `runPass()` already walks and
tags the **entire** root-reachable graph unconditionally (design doc's Implementation status
note: *"it runs a single, singleton-owned search that walks the whole root-reachable graph...
with no per-sample seeding"*). A live, root-reachable candidate object will already carry a
correctly-chained tag once any pass has visited it — no `SetTag` seeding step is needed at all.
The bridging step becomes a **read**, not a write:

```
for each candidate (klass, representative jweak):
    obj = resolve jweak (JNI local ref); skip if null (candidate died)
    tag = ReferenceChainTracker::instance()->getTag(jvmti, obj)
    if tag > 0:
        buildChainEvent(tag, &event)  // already-recorded parent_tag chain
        emit event
    // tag == 0: not yet discovered by any pass; retry on the next poll
```

Phase C below implements this corrected mechanism. Everything else from the design doc's
proposal (per-klass rolling window, slope ranking, top 3-5 cutoff, the coupling caveat between
`_record_liveness`/`_gc_generations` and `referencechains=...`) is unaffected by this correction
and is implemented as originally proposed.

## Phased breakdown

### Phase A — Per-klass population tracking in `LivenessTracker`

**Goal:** the rolling-window population data Open Question 3's slope ranking needs. No BFS-side
code yet.

- New fixed-capacity table, keyed by klass `StringDictionary` id (the same id
  `TrackingEntry`/`AllocEvent` resolves lazily today only at flush time,
  `livenessTracker.cpp:115-122`). Each entry:
  ```cpp
  struct KlassPopulationEntry {
    u32 klass_id;
    jweak representative;      // a currently-live tracked instance of this klass
    u16 count_ring[30];        // ring buffer of population samples
    u8 ring_head;
    u8 ring_fill;               // samples written so far, caps at 30
    u64 last_updated_epoch;    // for LRU eviction
  };
  ```
  Fixed capacity (new constant, e.g. `MAX_KLASS_POPULATION_ENTRIES`), evict
  least-recently-updated on insert-when-full — same shape problem `FrontierTable`/
  `LivenessTracker`'s own table already solve, applied here (cite both as precedent, don't
  re-derive the eviction logic from scratch).
- Populate during `cleanup_table()`'s existing epoch-advance pass (`livenessTracker.cpp:63` for
  the epoch-cadence citation), **not** the allocation hot path: for each `TrackingEntry` that
  survives this cleanup, resolve its klass id (this is genuinely new cost on an existing
  GC-triggered pass — the class is currently resolved lazily only at JFR-flush time,
  `livenessTracker.cpp:115-122`; resolving it here instead/also must not touch the allocation
  sampling path). Accumulate per-klass counts in a small pre-allocated scratch array reused
  across calls (a member field, not a stack/heap allocation per call — cleanup_table() runs on a
  GC-signal cadence, not the hot path, but this codebase's allocation-free preference still
  applies wherever avoiding an allocation is cheap).
- At the end of each `cleanup_table()` pass, push that epoch's per-klass count into the
  matching `KlassPopulationEntry`'s ring buffer (creating the entry, with the surviving
  `TrackingEntry`'s own `jweak` — or a fresh one derived from it — as `representative`, if this
  is the klass's first sighting).
- Gate this entire mechanism behind `_gc_generations` (the flag that already signals "the caller
  wants generation/survival-shaped data" per `arguments.cpp:223-227,244`), not a new flag — this
  resolves the design doc's "still undecided" bullet under Open Question 3 by requiring liveness
  tracking *and* `_gc_generations` to be enabled; `referencechains=...` alone gets no
  target-seeding (today's whole-graph-only behavior), consistent with the doc's stated fallback.
- gtest coverage (`livenessTracker_ut.cpp`, extending its existing style): insert/evict
  round-trip, ring-buffer wraparound at 30 samples, epoch-driven population under a synthetic
  multi-klass allocation pattern.

**Exit criteria:** a rolling per-klass population history exists, gated on `_gc_generations`,
with zero new cost on the allocation sampling path; verified by gtest.

### Phase B — Slope computation and candidate ranking

**Goal:** turn Phase A's raw histories into a ranked candidate list, on demand (not
continuously recomputed).

- New `LivenessTracker` method, e.g. `int selectLeakCandidates(KlassCandidate *out, int max)`,
  called on demand (from Phase C's poll, not on a timer of its own):
  - Skip any `KlassPopulationEntry` with `ring_fill < 10` (design doc's minimum-fill
    requirement — don't trust a trend from a klass just starting to be tracked).
  - Slope: average of the earliest third of the filled window vs. average of the most recent
    third (design doc's explicit choice over full least-squares — cheap, allocation-free,
    reads directly from the ring buffer with no sorting or extra storage).
  - Keep only entries with positive slope; sort by magnitude descending; write the top
    `min(max, 3..5)` into `out` (`KlassCandidate { u32 klass_id; jweak representative; }`).
  - This ranking + top-N cutoff **is** the per-pass seeding budget the design doc's Open
    Question 3 discussion already noted — no separate cap constant needed.
- Explicitly out of scope here (per the design doc's own "known limitation, stated rather than
  solved" framing): distinguishing many-klasses-trending-positive (heap-wide growth) from
  several independent leaks. Do not add heuristics for this; the top-N cutoff is the only
  mitigation and that is a deliberate, documented choice, not an oversight to "fix" in this
  phase.
- gtest coverage: synthetic ring-buffer states (flat, growing, shrinking, just-below-minimum-
  fill) asserting the correct candidate set and ordering.

**Exit criteria:** `selectLeakCandidates()` returns a correctly ranked, correctly bounded
candidate list from synthetic population histories; no BFS-side code touched yet.

### Phase C — Bridging: `ReferenceChainTracker` polls `LivenessTracker`'s candidates

**Goal:** close the target-selection gap using the corrected (read-only) mechanism described
above.

- New `ReferenceChainTracker` method, e.g. `void pollWatchedTargets(jvmtiEnv *jvmti, JNIEnv
  *jni)`, called from `threadLoop()` once per scheduling cycle, **after** `runPass()` (so the
  most recent pass's tagging is already reflected):
  1. Guard: no-op if `_gc_generations`/`_record_liveness` is not enabled (Phase A's own gate
     already makes `selectLeakCandidates()` return nothing in that case, but check explicitly
     here too so this method's cost is zero when the feature isn't in use).
  2. Call `LivenessTracker::instance()->selectLeakCandidates(...)`.
  3. For each candidate: resolve its `jweak` to a JNI local ref; if null, the candidate died
     since it was flagged — skip. Otherwise call `getTag(jvmti, obj)` (existing helper,
     `referenceChains.h:590`). If the tag is `> 0` (already discovered and correctly
     parent-chained by a completed or in-progress pass), call `buildChainEvent(tag, &event)`
     and hand the event to a new emission path (next bullet). If the tag is `0`, the object
     hasn't been reached by any pass yet — do nothing this cycle; it will be retried on the
     next poll once a pass has had a chance to reach it (root-reachable objects are guaranteed
     to eventually be visited by the whole-graph walk, barring the hop/budget/frontier caps).
  4. De-duplicate: track which `target_tag`s have already produced an event this search (a
     small `std::unordered_set<jlong>`, cleared when a new search starts) so a klass flagged
     across multiple consecutive polls doesn't re-emit the same chain repeatedly.
- **Close the missing-wrapper gap** the design doc's Implementation status note already flagged:
  add `FlightRecorder::recordReferenceChain(int lock_index, ReferenceChainEvent *event)`
  (mirroring `recordReferenceChainAbandoned`, `flightRecorder.cpp:2149-2157` /
  `flightRecorder.h:454-455` exactly) and `Profiler::writeReferenceChain(ReferenceChainEvent
  *event)` (mirroring `writeReferenceChainAbandoned`, `profiler.cpp:794-805`). `pollWatchedTargets()`
  calls `Profiler::writeReferenceChain()` for each event it builds, rather than routing through
  `Profiler::dump()`'s existing call site (`profiler.cpp:1732-1735`) — unlike the abandoned-event
  path, chain events are produced continuously as candidates are discovered, not only at dump
  time, so they need their own write call site instead of piggybacking on the flush-on-dump
  pattern `LivenessTracker`/`buildAbandonedEvent()` use.
- gtest coverage: a fixture with a `LivenessTracker` stub/fake returning a fixed candidate list
  and a `ReferenceChainTracker` that has already tagged the corresponding object via a real
  `runPass()`-equivalent setup (mirror `referenceChainJfrRoundtrip_ut.cpp`'s existing
  `FrontierTable::insert()` seeding style rather than writing a third seeding pattern) — assert
  `pollWatchedTargets()` emits exactly one event per distinct candidate tag, none for
  not-yet-discovered candidates, and no duplicate for a candidate polled twice.

**Exit criteria:** a klass flagged by Phase B's ranking, once naturally discovered by an
ordinary pass, produces exactly one `datadog.ReferenceChain` JFR event with the correct
referrer-chain content; verified end-to-end by gtest (native) plus one Java/JMC integration test
(re-enable `ReferenceChainTrackingTest.shouldReconstructReferrerChainToGcRoot`,
`ddprof-test/.../referencechains/ReferenceChainTrackingTest.java:128-142`, since this phase is
exactly the gap that test's `@Disabled` reason cites).

### Phase D — Pause-time-SLO feedback loop (`PidController` reuse)

**Goal:** replace the fixed `_budget`/`PASS_CADENCE_NS` constants with values adaptively scaled
from measured per-pass safepoint duration, per Open Questions 2 and 5's shared proposed
mechanism.

- New config knob (Phase 0-style, `arguments.h`/`.cpp`'s `referencechains=...` sub-option): a
  single target ceiling, e.g. `pausetarget=<ms>`, replacing "guess 4 constants" with "measure and
  pick 1 ceiling" per the design doc's framing. Default value is itself a Phase-5-style
  empirical question — **do not** invent a number here; land the knob wired to a clearly-labeled
  provisional default (mirroring the existing `DEFAULT_REFERENCE_CHAINS_*` constants' own
  "provisional, not benchmark-derived" labeling) and file it as a new row in
  [LiveHeapReferenceChains-BenchmarkPlan.md](LiveHeapReferenceChains-BenchmarkPlan.md)'s tunables
  table.
- One new `PidController` instance per `ReferenceChainTracker` (own gains — do **not** copy
  `ObjectSampler`/`MallocTracer`/`NativeSocketSampler`'s shared P=31/I=511/D=3/cutoff=15s triple;
  the design doc's caveat on this is explicit and this plan does not relitigate it). Gain
  selection and convergence validation (does it stabilize vs. oscillate/overshoot the ceiling)
  is this phase's own measurement task, using the same harness
  [LiveHeapReferenceChains-BenchmarkPlan.md](LiveHeapReferenceChains-BenchmarkPlan.md) describes
  for the `ReferenceChainsPassBenchmark`/`ReferenceChainsCadenceBenchmark` classes — reuse that
  plan's matrix rather than building a second one for gain-tuning alone.
- Measurement point: wrap the `FollowReferences`/`GetObjectsWithTags` call in `runPass()`
  (`referenceChains.cpp:702,759,850`) with a wall-clock timestamp pair (`OS::nanotime()`, already
  used elsewhere in this class, e.g. `_search_start_ns`) — this is the safepoint duration with no
  new instrumentation, exactly as the design doc states (the calling thread is already blocked
  for that duration).
- Controller output scales the *effective* per-pass budget (`_budget`'s value for the next
  call), clamped to `[some floor, _budget_ceiling_from_config]` — never scaled above what the
  frontier cap or hop cap would allow regardless (those stay fixed correctness bounds per the
  design doc, not controller-tuned).
- Fold Open Question 5's cadence decision into the same controller (per the design doc's
  explicit "one shared mechanism" framing): when recent passes run comfortably under the
  ceiling, let the existing GC-finish-epoch trigger in `shouldRunPass()` fire back-to-back
  passes without `PASS_CADENCE_NS`'s floor; when passes are running long relative to the
  ceiling, widen the fallback interval instead of tightening the budget further (avoids
  shrinking the budget to a degenerate near-zero value just to hit an aggressive cadence).
- gtest coverage: feed `PidController::compute()` a synthetic sequence of "pass took Xms"
  inputs (over/under/at ceiling) and assert the derived budget/cadence move in the correct
  direction each step, plus a convergence check (does not oscillate indefinitely for a
  constant input).

**Exit criteria:** per-pass budget and cadence respond to a measured pause-time signal instead
of fixed constants; gain values are chosen via the benchmark plan's matrix (not guessed), and
the choice + supporting measurement is recorded in
[LiveHeapReferenceChains-BenchmarkPlan.md](LiveHeapReferenceChains-BenchmarkPlan.md), not just
left in code comments.

### Phase E — Design doc and test cleanup

- Update `LiveHeapReferenceChains.md`'s Open Questions 2/3/5 to mark them **shipped** with the
  actual mechanism (cross-reference this plan's phases + files), replacing "proposed, not yet
  implemented."
- Update `LiveHeapReferenceChains.md`'s Implementation status note: `buildChainEvent()` now has
  a call site (Phase C); the "real, un-closed gap" framing there is resolved.
- Remove the `@Disabled` annotation and stale header comment on
  `ReferenceChainTrackingTest.shouldReconstructReferrerChainToGcRoot` once Phase C's own
  integration test (see Phase C's exit criteria) supersedes it, or repurpose that existing test
  method directly instead of adding a parallel one — prefer the latter to avoid two tests
  asserting the same thing.

**Exit criteria:** design doc, implementation plan, and test suite all describe the
as-shipped state with no stale "not yet implemented"/"@Disabled" markers left over from this
work.

## Ordering and dependencies

Phase A → B → C is a strict chain (each needs the previous phase's data structure). Phase D is
independent of A/B/C (it only touches `runPass()`'s budget/cadence, not target selection) and
can be built in parallel once Phase 0-7's existing code is the baseline. Phase E depends on
whichever of C/D actually ship — do it last, and do it for whichever subset shipped (do not
block E on both C and D landing together if one is ready first).

## Non-goals (carried over, restated for this plan)

- No heap-wide-growth-vs-multi-leak disambiguation (Phase B, explicitly deferred by the design
  doc).
- No numeric SLO ceiling or PID gain values invented in this plan — both are measurement
  outputs of the benchmark plan, not design decisions to guess here.
- No second candidate-generator/seeding pattern where an existing one (gtest fixture styles,
  `FrontierTable::insert()` seeding, `PidController` class) already fits — reuse per each
  phase's own citations above.
