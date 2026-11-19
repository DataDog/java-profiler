<!-- Copyright 2026, Datadog, Inc. -->

# Reference-chain scheduling and cost control

## Scope

This document explains when `ReferenceChainTracker` starts, delays, or restarts a search.
See [LiveHeapReferenceChainsImplementation.md](LiveHeapReferenceChainsImplementation.md)
for traversal, termination, and output.

The source calls its leaky-bucket cost limiter a *pain budget*. This document uses
*cost budget* except when naming a source field. Neither budget is a hard overhead quota.

## GC callbacks

`ReferenceChainTracker`'s GC callbacks increment atomic epoch counters. The liveness
callback also records usage samples. The callbacks do not execute reference-chain heap walks.

GC does not wake the traversal thread or independently authorize a pass. The background
loop checks state at its effective cadence. Shutdown signals it to wake a sleeping thread.

## Starting a search

`shouldRunPass()` calls `canAffordNewSearch()` before the first search. The gate checks:

1. The safepoint-cost debt has drained.
2. The root-enumeration interval permits another attempt, if one has already run.
3. The leak signal is enabled and `selectLeakCandidates()` returns a qualifying class.

The signal requires generations tracking or liveheap tracking with reference chains
active. A plain liveheap session keeps it disarmed. Reference-chain activation also
requires the allocation engine to have started successfully.

A rising aggregate heap floor does not replace a class/thread candidate. Without a
qualifying candidate, the collector does not start a search.

## Scheduling a running search

The scheduler uses this order:

1. Set the CPU-cost refill rate for the current candidate state.
2. Require minimum spacing since the previous pass ended.
3. Check the CPU-cost debt.
4. Apply candidate-search backoff when unresolved candidates remain.
5. Run the pass when those gates permit it.

A completed GC is not a separate authorization lane. Terminal tag-release retries and
the initial/restart gate use their own paths, not this running-search sequence.

### Minimum pass spacing

Ordinary running-search spacing is `max(effective cadence, 100 ms)`. Thus, reducing the
controller's cadence below 100 milliseconds does not remove the fixed scheduling floor.
CPU debt and candidate backoff can delay a pass further.

The OOM ramp described below is the exception: it uses its effective cadence without
the 100-millisecond floor and disables candidate backoff. The CPU-cost gate still applies.

### Candidate-search backoff

The source calls the focused candidate search the *canary* path. A new or resolved
candidate resets its spacing multiplier to one. Minimum pass spacing still applies.

Without candidate progress, the multiplier doubles up to its cap. Above one, it adds
this work-scaled spacing requirement unless the OOM ramp is active:

```text
spacing = multiplier × candidate-pass-duration EMA
```

### Effective cadence

The cadence starts at one second. The PID controller can adjust it between 10 milliseconds
and four seconds when the edge budget reaches a limit. Ordinary scheduling still applies
the separate 100-millisecond floor.

The OOM ramp also writes the cadence while a search runs. When its episode ends, it
restores one second. With no search running, ramp-band idle evaluation stays at one second.

## Leak signal

`LivenessTracker` counts distinct GC ages among a class's surviving tracked instances,
not raw live-instance population. The class table holds at most 256 entries with
30-value history rings. Several GCs can be coalesced into one processed-epoch fold.

A class needs at least 10 values. Full-window linear regression must show fitted endpoint
growth of at least the larger of 15% of the fitted start and one distinct age. Five
consecutive qualifying folds are required, or three when the aggregate heap floor rises.

The rise need not be monotonic. Heap-floor corroboration changes the hysteresis threshold
uniformly; it does not attribute growth to a class or reorder candidates.

At least one allocating thread must qualify for the class. Its surviving-age trend or
at least eight retained tracked instances can qualify a fold. Consecutive qualification
must meet the same hysteresis threshold. At most five candidate classes are selected.

Polling publishes qualifying thread identifiers as the watched admission set. Those
threads bypass liveness subsampling for already-sampled allocation callbacks, not every
Java allocation. The separate global OOM admission boost is described below.

## Cost budgets

### Safepoint cost budget

Each pass adds elapsed time around its heap-walk calls to `_search_pain_ms`. Once a
terminal search has released its tags, the scheduler charges this accumulated value to
`_safepoint_pain_budget` before considering a successor, then clears the accumulator.

This budget delays a later search. It does not stop a running search after a fixed
cumulative duration. The timed calls are not a direct measurement of application pauses.

### CPU cost budget

`_cpu_pain_budget` uses `runPassManualWalk()` elapsed time minus the time around its
heap-walk calls. This is a wall-time proxy, not CPU consumption. Class resolution,
candidate polling, and tag release are outside the timed region.

While unresolved candidates exist, the refill rate rises by a factor of 100, capped at
full wall-clock rate. The minimum spacing floor and candidate backoff remain separate
controls; the OOM ramp disables only the latter.

### Meaning of a cost budget

A cost budget records prior cost and delays later work until that debt drains. Its
refill percentage is a pacing input, not a measured or guaranteed CPU/pause-time quota.

## Pause controller

Only passes without root enumeration feed `_pause_pid` with their measured heap-walk-call
time. It adjusts the effective edge budget and, at budget limits, the effective cadence.
Root-enumeration passes still contribute to search cost and can revoke borrowed headroom.

The effective-budget floor is `min(2000, current ceiling)`, not an unconditional 2,000
admissions. These counts do not count every callback or bound call duration.

Five consecutive ordinary passes at no more than half the target can earn borrowing.
Headroom grows by 25% of the base ceiling per qualifying pass, up to a total ceiling of
four times that base. A pass outside the comfort band removes the grant.

### Callback deadlines

Reference callbacks check time every 4,096 invocations; expansion also checks its outer
loop. Candidate-thread traversal, ordinary expansion, and rotation receive separate
deadlines. Static scanning shares an earlier deadline, so earlier work can consume it.

The target is therefore not a hard whole-pass pause ceiling. JVM work and callback
granularity can cause overshoot. Root callbacks do not check this deadline.

### Root-enumeration interval

The first attempt is mandatory. Later attempts wait after the previous attempt ends:
`max(2 s, min(last attempt duration in ms × 20 ms, 30 s))`. Truncated and errored attempts
use the same interval. The new-search gate also enforces it before restarting.

The phase has no saved enumeration cursor. Already-admitted roots do not consume ordinary
admission budget, and direct-root leak-tag conversion bypasses that budget check. Neither
the deadline mechanism nor the admission count bounds root-enumeration elapsed time.

For this release, a root-enumeration pause is acceptable if it is shorter than three
seconds. This acceptance threshold and the controller target are not hard real-time
guarantees. See [root discovery](LiveHeapReferenceChainsImplementation.md#root-discovery).

## OOM response

`secondsToOOM()` requires an enabled leak signal, a known maximum heap, and at least
10 usage-history values. It projects heap and available container-memory boundaries
separately and chooses the shorter valid estimate.

Each boundary needs rising full-window and recent-half regressions. A negative result
means no usable projection, including during burn-in; it does not prove OOM impossible.

For five minutes after the signal's first activation in the process, the projection
returns -1. The burn-in clock is not restarted for each recording and does not depend
on how many seconds the usage ring spans.

### Ramp below 30 minutes

The raw projection below 30 minutes moves the pause target exponentially toward
100 milliseconds and raises the base edge-budget ceiling fourfold, subject to its cap.
For a running search, cadence moves from one second toward 10 milliseconds.

With no running search, cadence stays at one second. The ramp follows the raw projection,
not the urgent latch. Leaving the band restores the configured budget and one-second cadence.

### Global tracking admission

In the 5–30 minute band, global admission boost requires a new heap-floor sample above
the episode's running high-water mark. Each admitted growth sample raises that mark;
the decision is held until another sample arrives.

Below five minutes, the boost needs no additional heap-growth evidence and can engage
without candidates or a running search. At a full tracking table, admission falls back
to watched-thread and configured-ratio rules.

The boost bypasses liveness subsampling of already-sampled allocations, not the allocation
sampler or storage limits. Backoff increments `LIVENESS_URGENT_BOOST_BACKED_OFF`;
boosted admission increments `LIVENESS_URGENT_BOOST_ADMITS`.

### Urgent latch below five minutes

A raw projection below five minutes latches urgency. It clears after five consecutive
checks with an estimate of at least ten minutes or no usable projection. This hysteresis
is separate from the ramp and admission decisions.

The loop refreshes the latch once per iteration, even while search gates block work.
It suppresses ordinary no-progress abandonment, but never authorizes a candidate-less
search. Refused urgent evaluations increment `reference_chain_urgent_no_candidate`.

That counter advances only when cost and root-enumeration interval gates permit the
candidate probe. A heap-wide problem with no qualifying class/thread candidate can
therefore produce no chains even near exhaustion.

## Terminal state and restart

Incomplete root enumeration defers TTL and ordinary no-progress abandonment. Expansion-only
passes hold the frontier no-progress counter while waiting for enumeration; its attempts
can still advance the counter. Configured TTL is not a hard search-lifetime bound.

Three consecutive enumeration JVMTI errors can abandon the search. `CANARY_STUCK` can
also fire without urgency when incomplete enumeration suppresses the earlier no-progress
exit. See the implementation reference for the full priority ladder.

For a terminal search, the scheduler:

1. Confirms release of all search-owned tags, retrying release before proceeding.
2. Charges the completed search's accumulated heap-walk-call cost and clears the accumulator.
3. Checks safepoint-cost debt, then the root-enumeration interval, then the current leak signal.
4. Calls `restartSearch()` only when those checks pass.

A running search does not restart itself. Recording stop forces a terminal state without
enqueueing a recording-end abandonment event and clears the recording's cached output.

## Stop request

`stopThread()` stores an abort request, signals the background thread, and joins it.
The signal wakes a sleeping thread; it does not cancel a JVM call in progress.

Root and reference callbacks check the abort request on each invocation. Stop latency
therefore depends on callback progress, not immediate interruption of JVM work.

## Operational interpretation

Inspect heap-walk-call time, manual-walk remainder, effective budget and cadence, candidate
progress/backoff, search outcome, and drop counters together. None alone establishes
application pause time, CPU overhead, or complete reference-chain coverage.
