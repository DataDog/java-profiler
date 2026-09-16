---
id: find-abandon-event-lost-to-dump-sampling-race
type: finding
status: confirmed
depends_on: [ev-postfix-onpod-live-verification]
supersedes: []
related: [find-canary-stuck-abandon-detector, find-canary-search-cannot-terminate, ev-jafar-zero-refchain-events]
tags: [root-cause, jfr-emission, race-condition, search-state, dump, referenceChains, NEW-BUG]
created: 2026-08-25
updated: 2026-08-25
---

# NEW ROOT CAUSE: SearchState::ABANDONED is transient and almost always overwritten before Profiler::dump() ever samples it

## Reasoning chain

With Fix A/B/C live and working (`ev-postfix-onpod-live-verification`), the
canary search now cleanly reaches `SearchState::ABANDONED` every time it
gets stuck (`abandonReason=3`, confirmed 5x in pod logs). But
`datadog.ReferenceChainAbandoned` and `datadog.ReferenceChain` both show
count **0** in every downloaded JFR chunk checked so far, including one
whose empirically-derived time range (`09:01:37.95` -> `09:02:37.56`,
established via `datadog.SafepointBegin`'s `startTime` min/max, see below)
squarely brackets a confirmed pod-log abandon event at `09:01:53`.

The user's working hypothesis mid-session was that abandon *counters* might
not carry over across ~60s profile-chunk boundaries. **That hypothesis is
refuted by this evidence**: the abandon event at 09:01:53 falls fully
inside the chunk's own 09:01:37-09:02:37 window, not near either edge, so a
pure boundary-clipping explanation cannot account for the 0 count.

The actual root cause is a **read/write race on `_search_state`, on two
different clocks**:

1. `Profiler::dump()` (`profiler.cpp:2055-2062`) is the *only* place that
   reads `ReferenceChainTracker::instance()->searchState() ==
   SearchState::ABANDONED` to build and emit a
   `datadog.ReferenceChainAbandoned` event. It only runs on JFR chunk
   rotation - roughly a 60s cadence in this deployment, entirely decoupled
   from the BFS thread's own timing.
2. `ReferenceChainTracker::threadLoop()`'s own BFS thread calls
   `shouldRunPass()` on a fixed ~1s cadence
   (`referenceChains.cpp:840-935`). When `_search_state != RUNNING` (i.e.
   terminal - COMPLETED or ABANDONED) and `_tags_released` is true,
   `shouldRunPass()` calls `canAffordNewSearch()` and, if it returns true,
   calls `restartSearch()` **synchronously, inline** (`:876-881`), which
   sets `_search_state` back to `RUNNING`
   (`referenceChains.cpp:1145` inside `restartSearch()`, confirmed at
   `:1036`).

Pod logs already show this restart happening on the very next iteration
after every observed abandon (`abandonReason=3` -> next line
`shouldRunPass -> true (restarting search)` -> `passesRun` reset to 0) -
i.e. `SearchState::ABANDONED` is only actually readable for **about one BFS
loop iteration (~1s)** out of every ~60s JFR chunk. `dump()`'s snapshot has
roughly a 1-in-60 chance of landing inside that window on any given chunk
rotation. Across 5 confirmed abandon events and the several chunks sampled
so far, seeing 0 hits is the expected outcome of this race, not evidence of
a missing/broken emission path.

This is architecturally the same shape of bug as
`find-canary-search-cannot-terminate`'s livelock, but on the *reporting*
side rather than the *search* side: a transient state that self-heals
faster than the only consumer that reads it gets scheduled.

## Evidence

- `flightRecorder.cpp:2140` `Recording::recordReferenceChain()`,
  `:2192` `Recording::recordReferenceChainAbandoned()` - the JFR write
  functions themselves, confirmed to exist and be well-formed (not the
  bug).
- `profiler.cpp:863-876` `Profiler::writeReferenceChainAbandoned()` and
  `:898-943` `Profiler::writeReferenceChain()` - both correctly wired to
  `_jfr.recordReferenceChain(Abandoned)`; confirmed the only two call sites
  of the record functions in the whole codebase (grepped
  `ddprof-lib/src/main/cpp/`).
- `profiler.cpp:2049-2086` `Profiler::dump()` - the **only** call site of
  `writeReferenceChainAbandoned()`/`writeReferenceChain()`, gated on
  `searchState() == SearchState::ABANDONED` read at dump-time.
- `referenceChains.cpp:857-881` `shouldRunPass()`'s terminal-state branch -
  calls `restartSearch()` inline the very next time it's invoked once
  `canAffordNewSearch()` allows it, flipping state back to `RUNNING`.
- `referenceChains.cpp:1036` `restartSearch()`,
  `referenceChains.cpp:1145` sets `_search_state = RUNNING`.
- Empirical chunk-boundary check (this session):
  `prof-analyzer-hotdog-2026-08-25_09-02-37.564Z-...jfr` opened via jafar
  (sessionId 21). `events/datadog.ReferenceChainAbandoned | count()` = 0,
  `events/datadog.ReferenceChain | count()` = 0.
  `events/datadog.SafepointBegin | select(startTime)` (limit 2000, 820
  results) gives min `1787648497953939200` ns = `2026-08-25 09:01:37.953939`
  UTC and max `1787648557564531000` ns = `2026-08-25 09:02:37.564531` UTC -
  a ~59.6s chunk squarely containing the confirmed pod-log abandon at
  `09:01:53`.
- (Earlier, less precise) `events/datadog.ProfilerCounter |
  select(startTime,name)` returned 163 results all with the identical
  `startTime=1787648497743735000` (~09:01:37.74) - a registration burst at
  chunk start, useful only for establishing the chunk's start, not its end;
  superseded by the SafepointBegin min/max above for the full range.

## What this rules out

- **The user's chunk-boundary/counter-carryover hypothesis**, at least as
  a full explanation - refuted directly: the 09:01:53 abandon is not near
  either edge of the 09:01:37-09:02:37 chunk, yet the event count is still
  0.
- **A broken/missing JFR write path** - the record/write functions are
  present, correctly wired, and the only bug is in *when* the ABANDONED
  state is observable, not in how the event is serialized once built.
- **Fix C not actually abandoning** - it clearly is (5 confirmed
  `abandonReason=3` cycles); the gap is entirely in `dump()`'s sampling of
  that transient state.

## Not yet done

- No fix proposed or implemented for this - purely diagnostic so far. A fix
  would need `dump()` to observe the abandon event through something other
  than a live re-read of `_search_state` at an arbitrary later time - e.g.
  a one-shot "pending abandon" flag/queue set by `runPass()`'s abandon
  branch and cleared by `dump()`'s own read, mirroring how
  `_resolved_chains` already handles the analogous case for successful
  chains (`drainPendingChainEvents()` snapshots without clearing - though
  note that pattern re-reports on every dump rather than being one-shot,
  so it is not a direct template; a `ReferenceChain` success is presumably
  affected by the exact same underlying race, since it is also only
  read/emitted from `dump()`).
- Whether `datadog.ReferenceChain` (the success event, not the abandon
  event) is affected by the *same* race, or a different one, is not yet
  separately confirmed - `find-onpod-verification` above notes zero
  candidates have ever resolved on this pod, so that path has not yet even
  been exercised to test independently. Worth revisiting once a resolution
  is observed.
