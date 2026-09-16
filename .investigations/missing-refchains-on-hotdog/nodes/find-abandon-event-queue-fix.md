---
id: find-abandon-event-queue-fix
type: finding
status: confirmed
depends_on: [find-abandon-event-lost-to-dump-sampling-race]
supersedes: []
related: [find-canary-stuck-abandon-detector, ev-fixes-compile-and-gtest-pass]
tags: [fix, jfr-emission, race-condition, referenceChains, queue, NEW-THIS-SESSION]
created: 2026-08-25
updated: 2026-08-25
---

# Fix D: bounded pending-abandoned-events queue closes the dump() sampling race

## Reasoning chain

User's own framing of the two remaining directions (verbatim): "keep counter
of abandoned searches and emit the event using that counter; resetting it on
dump" vs. "figure out why we are not getting closer to the canaries". User
chose both, in that order.

A literal single integer counter cannot work: `restartSearch()`
(`referenceChains.cpp:1036`) clears `_abandon_reason`, `_search_start_ns`,
`_last_pass_ns`, `_passes_run` — the exact fields `buildAbandonedEvent()`
needs to populate `ReferenceChainAbandonedEvent`'s payload
(`_reason`/`_passes_run`/`_frontier_size`/`_hop_cap`/`_budget`/`_ttl_ms`/
`_elapsed_ns`, see `event.h:126-141`). A bare count would lose all of that
diagnostic detail. The user was told this reasoning directly and separately
questioned whether per-event fidelity was worth it at all ("why not just
emit the number of abandoned searches") — answered with the same point plus
the observed abandon rate (~5 per 20 min, under one per 60s dump interval),
making per-event cost negligible. User accepted ("ok. fair points").

Implemented instead: a bounded queue (`_pending_abandoned_events`,
`MAX_PENDING_ABANDONED_EVENTS = 16`) that snapshots a fully-built
`ReferenceChainAbandonedEvent` at the exact moment of abandon — synchronously,
on the BFS thread, before `restartSearch()` can run and clear the source
fields. `Profiler::dump()` now does a **true drain** (not the
snapshot-and-keep re-emit pattern `_resolved_chains`/`drainPendingChainEvents()`
uses), since an abandon is a one-off past occurrence, not an ongoing live
sample.

## Changes made

- `referenceChains.h`: added `_pending_abandoned_events` (vector),
  `_pending_abandoned_events_lock` (SpinLock), `MAX_PENDING_ABANDONED_EVENTS`
  constant; declared `enqueuePendingAbandonedEvent()` (private) and
  `drainPendingAbandonedEvents(std::vector<ReferenceChainAbandonedEvent>*)`
  (public).
- `referenceChains.cpp`:
  - `enqueuePendingAbandonedEvent()` builds the event via the existing
    `buildAbandonedEvent()`, pushes it under the lock, drops with
    `Counters::increment(REFERENCE_CHAIN_EVENTS_DROPPED)` +  `TEST_LOG` if
    the queue is at cap (mirrors `cacheResolvedChain()`'s no-silent-drop
    pattern).
  - `drainPendingAbandonedEvents()` moves the whole vector out under the
    lock and clears it.
  - Called `enqueuePendingAbandonedEvent()` immediately after
    `storeRelease(_search_state, (u8)SearchState::ABANDONED)` at all three
    abandon sites in `runPass()` (FRONTIER_CAP, TTL, CANARY_STUCK branches).
  - `resetSearchStateForTest()` now also clears `_pending_abandoned_events`
    under its lock, next to the existing `_resolved_chains.clear()` — same
    test-isolation rationale (one test's abandons must not leak into the
    next).
- `profiler.cpp` `Profiler::dump()` (was lines 2049-2062): replaced the old
  `searchState() == SearchState::ABANDONED` + single `buildAbandonedEvent()`
  read with a call to `drainPendingAbandonedEvents()` and a loop calling
  `writeReferenceChainAbandoned()` per drained event.

## Verification

- `./gradlew :ddprof-lib:compileDebug -Pskip-gtest` — compiles cleanly, no
  new warnings.
- `./gradlew :ddprof-lib:gtestDebug` (full suite, no filter available on this
  gradle task) — BUILD SUCCESSFUL, no test failures.
- **Not yet done**: no new gtest added that specifically exercises the queue
  (e.g. abandon -> drain -> assert event contents survive a subsequent
  `restartSearch()`) — not requested, existing suite already passes so no
  regression, but the new code path itself has no direct test coverage yet.
- **Committed and pushed** as `01047a6aa` on `jb/reference-chains` (on top
  of `623d3712a`), together with Fix E + Fix F
  (`find-canary-fixes-e-f`). **Not yet done**: not deployed/re-verified on
  the hotdog pod.

## What this rules out

- Plain-integer-counter design — insufficient, would lose per-event
  diagnostic payload; confirmed by design necessity, then separately
  challenged and re-confirmed by the user.
