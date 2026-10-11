# Spec: a-search-can-continue-across-two-recordi

## Problem

Three review-confirmed defects let one recording's reference-chain state leak into the
next recording, or lose events at the recording end:

1. `ReferenceChainTracker::stop()` (ddprof-lib/src/main/cpp/referenceChains.cpp:369-396)
   clears the resolved-chain cache and pending-abandonment queue but never ends an in-flight
   BFS search. A search still `RUNNING` at stop carries into the next recording: the stopped
   gap counts toward its TTL (`_search_start_ns` still holds the old recording's clock), so
   the new recording can abandon "its" search on the first pass with a spurious abandonment
   event, and the urgency episode (`_urgent_latched`, `_urgent_release_ticks`,
   `_urgent_search_spent`) carries over.
2. Frontier entries store `referrer_klass` as a `StringDictionary` id captured at admission
   time. `Profiler::start()` wipes `_class_map` (ids restart at 1) but the frontier's stored
   ids are never invalidated and cannot be remapped, so a chain reconstructed from a
   surviving entry after a restart names whichever class the new recording assigned that id
   to. A stale entry is reachable after a restart only when the previous recording's search
   was still in flight — through the dead-representative canary path, the
   discovered-instances path, and the representative path in `pollWatchedTargets()`.
3. Only `Profiler::dump()` (ddprof-lib/src/main/cpp/profiler.cpp:2034-2056) writes the
   tracker's events into a JFR chunk. `Profiler::stop()` runs
   `stopThread(); ReferenceChainTracker::stop();` — and `stop()` clears both queues — so a
   recording that ends with `stop()` and no preceding `dump()` drops queued abandonment
   events for good and emits a final chunk whose LivenessTracker live-object events (written
   by `_alloc_engine->stop()` earlier in `Profiler::stop()`) have no matching
   `ReferenceChain` events.

## Correct behaviour

- When `ReferenceChainTracker::stop()` runs, an in-flight search is terminated at the
  recording boundary: search state leaves `RUNNING` (terminal, with a distinct
  `SearchAbandonReason::RECORDING_END`), no abandonment event is enqueued for it, the TTL
  clock is zeroed, the urgency episode is cleared, and the BFS thread's per-search
  candidate/discovered state is cleared. The next recording starts from a brand-new-search
  shape: its first BFS pass releases the previous search's JVMTI tags via the existing
  terminal gate (before any chain-building poll), and the next `restartSearch()` resets the
  frontier content and `_next_tag`, so no chain can be built from a previous
  `_class_map` generation's ids.
- The tracker's frontier *table allocation* still spans recordings (unchanged), and stop()
  still does not release JVMTI tags itself (the next recording's first pass does, via the
  existing terminal gate — unchanged production shape documented in
  referenceChainsLifecycleTests.inc).
- `Profiler::stop()` writes the tracker's still-undrained events into the final JFR chunk:
  chain events (snapshot) and abandonment events (true drain) are recorded after the BFS
  thread is joined and before `ReferenceChainTracker::stop()` clears the queues, using the
  same per-lock writer pattern as `dump()`, so the final chunk's leak tags have matching
  chains and queued abandonment events survive.
- Recording-boundary resets must not enqueue JFR events for searches the new recording never
  ran, must not require new locking (the boundary is single-threaded w.r.t. the BFS state
  machine), and must keep the unit-testable shape (stop() callable with a mock jvmti/jni and
  no live JVM).

## Constraints

- `restartSearch()`'s invariant (never run before `_tags_released` is confirmed) is
  untouched; stop() must never call it.
- The JFR write in `Profiler::stop()` must happen after `SignalInflight::drain()` (no
  concurrent signal-path writers) and before `_jfr.stop()` inside `rotateDictsAndRun`.
- `SearchAbandonReason::RECORDING_END` is additive; the reason byte is never serialized for
  it (flightRecorder.cpp:2563 maps unknown reasons to "unknown" — never hit for this value).
- Style: match the file's existing comment density and locking idioms
  (`storeRelease`/`load` helpers for the search state atomics).

## Scope

### Primary fixes

- ddprof-lib/src/main/cpp/referenceChains.cpp:369 (`ReferenceChainTracker::stop()`) —
  missing recording-boundary search teardown — end an in-flight search (terminal
  `RECORDING_END`, no event), zero `_search_start_ns`, clear the urgency episode, clear the
  per-search candidate/discovered canary state.
- ddprof-lib/src/main/cpp/referenceChainFrontier.h:36 (`SearchAbandonReason`) — missing
  enum value — add `RECORDING_END = 4` with a comment.
- ddprof-lib/src/main/cpp/profiler.cpp:1853 (`Profiler::stop()`, reference-chains block) —
  events lost at stop — drain chain + abandonment events into the final chunk after
  `stopThread()` and before `ReferenceChainTracker::stop()`, mirroring dump()'s writer
  block.

### Auto-expanded sibling fixes

None identified. Checked surfaces: `LivenessTracker::start()/stop()` already reset its
per-recording state at the boundary (watched tids, urgent tracking, leak-tag free-list
rebuild — livenessTracker.cpp:1996-2058); `FlightRecorder::recordReferenceChain*` have no
recording-state precondition (flightRecorder.cpp:2757-2770, null/lock-guarded); the
tracker's `start()` hygiene block plus the new stop()-time teardown plus `restartSearch()`
cover every per-search field the BFS thread mutates.

## Assumptions

- Resolved at ≥90% confidence: ending an in-flight search at the recording boundary (rather
  than continuing it with a reset TTL clock) is the accepted strategy — a continued search
  would keep frontier entries whose dict ids are unsalvageable after the `_class_map` wipe,
  so continuation cannot be made correct; the reviewer's two asks (TTL clock, urgency state)
  are both satisfied by the teardown.
- Resolved at ≥90% confidence: `_search_pain_ms` accumulated by an in-flight search is spent
  by the next recording's first `shouldRunPass()` terminal visit (existing behavior for any
  terminal state) — no extra spend at stop().
- Resolved at ≥90% confidence: chain events re-emitted into the final chunk after a same-
  recording `dump()` is consistent with the established snapshot-and-keep semantics (chains
  re-emit into every chunk the sample survives into).
