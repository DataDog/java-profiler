<!-- Copyright 2026, Datadog, Inc. -->

# Reference-chain scheduling and cost control

## Scope

This document explains when `ReferenceChainTracker` runs a pass, delays a pass, starts a search, or restarts a search. See [LiveHeapReferenceChainsImplementation.md](LiveHeapReferenceChainsImplementation.md) for the heap-walk operations.

The source uses the name *pain budget* for a leaky-bucket cost limiter. This document uses *cost budget* except where it names a source field.

## GC callbacks

`GarbageCollectionStart()` and `GarbageCollectionFinish()` increment atomic epoch counters. They do not call JVMTI heap functions.

JVMTI callback restrictions require this separation. It also keeps the callback work small. The background thread reads the epoch and decides whether to run a pass.

The GC callback does not wake the thread. The normal idle loop checks the state at approximately the current fallback cadence. Shutdown uses a signal to wake a sleeping thread.

## Starting a search

Before the first search, `shouldRunPass()` calls `canAffordNewSearch()`. The gate requires a leak indication when GC-generation tracking is active. The indication is one of these conditions:

- `selectLeakCandidates()` finds a class with sustained population growth.
- The time-to-OOM estimate enters the urgent range and the current urgent episode has not started a search.

The safepoint cost budget must also permit the search.

If GC-generation tracking is not active, the leak-signal part of this gate does not apply.

## Scheduling a running search

A running search uses the following order:

1. Check the non-safepoint CPU cost budget.
2. If unresolved candidates exist, apply candidate-search backoff.
3. Otherwise, run after a new GC epoch or after the adaptive fallback cadence expires.

### Candidate-search backoff

The source calls the focused candidate search the *canary* path. A new candidate or a resolved candidate resets its spacing multiplier to one. With this value, the next pass can start after the previous pass finishes.

If a pass makes no candidate progress, the multiplier doubles up to its cap. The required spacing is:

```text
spacing = multiplier × candidate-pass-duration EMA
```

The OOM ramp disables this backoff. The non-safepoint CPU cost budget still applies.

### GC epoch and fallback cadence

When no unresolved candidate controls scheduling, a completed GC authorizes a pass. The tracker compares the current GC-finish epoch with the epoch recorded by the previous pass.

The fallback cadence also authorizes a pass. It starts at one second and the pause controller can adjust it between 10 milliseconds and four seconds.

## Leak signal

`LivenessTracker` bases the normal signal on sampled live-object populations by class.

- It stores 30 GC-epoch values per class.
- It requires at least 10 values before trend evaluation.
- It requires five consecutive qualifying epochs by default.
- It requires three when a rising post-GC heap floor corroborates the signal.

The aggregate heap-floor signal changes the hysteresis threshold. It does not identify a class.

Candidate selection also returns qualifying thread identifiers. During an active candidate search, allocations by those threads bypass the normal liveness subsampling ratio. This change increases the chance that the tracker can correlate a leak tag with the walk. It does not change the admission of other threads.

## Cost budgets

The tracker has two `PainBudget` instances with different scopes.

### Safepoint cost budget

`_safepoint_pain_budget` gates a new search or a restart. Each pass adds its measured in-safepoint time to `_search_pain_ms`. When a search reaches a terminal state, the scheduler charges that accumulated value to the budget before it considers a restart.

This budget does not stop a running search after a fixed cumulative duration. It controls when a later search can start.

### CPU cost budget

`_cpu_pain_budget` gates individual passes in a running search. Each pass charges the measured non-safepoint part of the pass.

While unresolved candidates exist, the scheduler increases the refill rate by a factor of 100, capped at full wall-clock rate. Candidate backoff remains the main rate control for that path.

### Meaning of a cost budget

A cost budget delays work until its leaky bucket drains prior cost. It is not a hard CPU or pause-time quota. The current operation can finish after it exceeds a target.

## Pause controller

The tracker measures time spent inside safepointing JVMTI calls. It supplies that value to a PID controller after ordinary expansion passes.

The controller adjusts:

- The effective edge-admission budget.
- The fallback cadence when the budget reaches its floor or ceiling.

Five consecutive passes at no more than half the pause target can start budget borrowing. A later pass that is not comfortably below the target removes the borrowed budget. A root-enumeration pass can also remove it.

Root-enumeration passes do not update the PID controller because they use a separate edge budget. Their safepoint time still contributes to search cost and can revoke borrowed budget.

The pause target controls resumable traversal phases. A callback asks JVMTI to stop when
it observes the deadline, but callback granularity and JVM work can cause overshoot.

Root enumeration does not use the deadline. JVMTI provides no cursor that lets the next
attempt resume after an abort, and the admission budget does not count every examined
root. For this release, a root-enumeration pause is acceptable if it is shorter than
three seconds. [PROF-16284](https://datadoghq.atlassian.net/browse/PROF-16284)
tracks measurement and improvement. Neither the pause target nor this acceptance
threshold is a hard real-time guarantee.

## OOM response

`secondsToOOM()` uses a confirmed rising heap-floor trend. A negative result means that the estimate is not available or that the trend is not rising.

Two ranges have different purposes:

- At less than 30 minutes, the OOM ramp increases the pause target, shortens the cadence, increases the edge-budget ceiling, and admits all liveness samples.
- At less than 5 minutes, `isUrgent()` latches an urgent episode. The episode can authorize one search without waiting for a class to complete normal hysteresis.

The urgent latch clears after five consecutive checks at 10 minutes or more, or after five consecutive checks with no valid rising-trend estimate. This hysteresis prevents repeated search restarts when the estimate moves around the threshold.

The ramp and the latch use different thresholds. Entering the ramp does not by itself activate the urgent search entitlement.

## Terminal state and restart

A search can become `COMPLETED` or `ABANDONED`. Before a restart, the tracker must confirm that it released all search-owned tags.

The scheduler then:

1. Charges the completed search's safepoint cost.
2. Clears that search-cost accumulator.
3. Checks the current leak signal.
4. Checks the safepoint cost budget.
5. Calls `restartSearch()` only when both checks pass.

A running search does not restart itself.

## Stop request

`stopThread()` stores an abort request, signals the background thread, and joins it. The signal wakes the thread when it sleeps.

If the thread is inside a JVMTI heap walk, the signal does not cancel the JVMTI call. `heapReferenceCallback()` checks the abort request on each callback and asks JVMTI to stop traversal. The stop latency therefore depends on callback progress.

## Operational interpretation

The scheduler aims to distribute work and react to measured cost. It cannot provide real-time guarantees.

Use these signals when evaluating behavior:

- In-safepoint time per pass.
- Non-safepoint pass time.
- Effective edge budget.
- Effective cadence.
- Candidate progress and backoff.
- Search outcome and abandonment reason.
