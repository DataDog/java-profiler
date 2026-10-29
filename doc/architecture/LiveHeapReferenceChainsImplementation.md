<!-- Copyright 2026, Datadog, Inc. -->

# Live-heap reference chains: implementation reference

**Status:** Implemented and disabled by default

## Scope

This document describes the current reference-chain implementation. It focuses on data flow, traversal, lifecycle, limits, and output.

Related documents:

- [Reference-chain design](../ReferenceChainsDesign.md) records the design decision and trade-offs.
- [Reference-chain collection summary](../ReferenceChainsCollectionSummary.md) gives a short overview.
- [Reference-chain scheduling and cost control](ReferenceChainsSignalsExplained.md) explains scheduling.

## Main components

`LivenessTracker` detects sustained growth in sampled live-object populations. It assigns leak tags to selected instances.

`ReferenceChainTracker` maintains a root-based frontier and searches for those instances. It runs on one agent-owned background thread. `_engine_lock` serializes engine state across lifecycle and test paths.

`FrontierTable` stores one record for each admitted object. Important fields include:

| Field | Purpose |
|---|---|
| `parent_tag` | Identifies the entry that admitted this object. Zero means that the entry is root-attached. |
| `referrer_klass` | Identifies the object's class in the profiler class dictionary. |
| `referrer_class_tag` | Class tag of the referrer when the referrer is a class object (a root-attached static-field admission, where there is no parent entry). Zero otherwise. |
| `referrer_field_index` | Field index of the admitting edge (-1 when the edge is not a field or static-field edge). Used to label each hop in the emitted chain. |
| `edge_kind` | JVMTI reference kind of the admitting edge for an interior hop (`parent_tag != 0`). |
| `depth` | Records the number of edges from the root. |
| `state` | Records `FRONTIER`, `EXPANDED`, `EDGE`, or `ABANDONED`. |
| `root_kind` | Records the JVMTI root or edge kind for a root-attached entry. |
| `class_tag` | The entry's own object class tag. It provides class identity across class-dictionary regeneration. |
| `leak_tag` and incarnation | Correlate the entry with the current owner of a sampled leak tag. |

## Search lifecycle

A search starts only after the scheduler accepts the leak signal and the cost gate.

The first pass starts the search timestamp and enumerates roots. Later passes resume the same frontier. A running search does not restart itself.

A terminal search releases its search-owned tags. A later search can start only after release succeeds, the current leak signal permits it, and the safepoint cost budget permits it.

`restartSearch()` resets the frontier state and the frontier-tag sequence. Stable class tags and valid resolved-chain entries have separate lifecycles.

## Pass structure

`runPass()` resolves loaded classes and calls `runPassManualWalk()`. The pass can contain these phases:

1. Root and stack-reference enumeration.
2. Candidate thread-object traversal.
3. Static-field scanning.
4. Ordinary frontier expansion.
5. Rotation and static-anchor traversal.

Candidate thread traversal, ordinary frontier expansion, and rotation each receive a fresh
callback deadline. Static-field scanning does not receive a fresh deadline. It shares the
candidate-thread deadline when that phase runs. Otherwise, it uses the deadline set before root
enumeration. Earlier work can therefore reduce or consume the time available for static-field
scanning.

The tracker measures total pass time and in-safepoint time separately. It charges the remainder to the CPU cost budget.

## Root discovery

### Root and stack references

`IterateOverReachableObjects()` calls `heapRootCallback()` and `stackRefCallback()`. These callbacks admit root-attached objects. They do not traverse all children of each root.

The first pass always performs root enumeration. A later pass performs it after a truncated enumeration or an interval of at least two seconds.

Root enumeration uses `firstpassbudget`. The name is historical: the implementation can use this budget again during later root-enumeration attempts.

This phase does not use the callback deadline. JVMTI does not expose a cursor for
resuming `IterateOverReachableObjects()`. An aborted attempt starts again from the first
root and can repeatedly omit roots later in the enumeration order. The edge budget does
not bound elapsed time when callbacks examine roots that the frontier already contains.

For this release, a root-enumeration pause is acceptable if it is shorter than three
seconds. This threshold is not the desired latency and is not a hard real-time
guarantee. [PROF-16284](https://datadoghq.atlassian.net/browse/PROF-16284)
tracks separate measurement and a progress-preserving mitigation.

### Static fields

Root callbacks do not provide the static-field edges needed by this implementation. `admitStaticFieldRoots()` therefore scans loaded classes with `FollowReferences()`.

The scan:

- Partitions each `GetLoadedClasses()` result so application classes come first.
- Processes at most 512 classes in one chunk.
- Saves a cursor and retries a truncated chunk.
- Admits static-field edges.
- Admits at most 32 other class edges per class.
- Starts a new completed sweep when the loaded-class count changes.

The loaded-class API does not guarantee stable ordering. The code repartitions each returned array before it uses the saved cursor.

### Candidate thread objects

Candidate selection records qualifying native thread identifiers. The tracker maps them to Java `Thread` objects and walks a rotating set of at most four thread objects per pass.

The descend walk admits at most 16 hops below an anchor and still obeys the global hop cap. This path improves coverage for `ThreadLocal` retention. It does not assume that every candidate is thread-local.

## Frontier expansion

`expandFrontier()` takes a batch of pending frontier tags and calls `GetObjectsWithTags()`. Dead objects do not resolve and leave no object to expand.

The tracker places the resolved objects in one JNI object array. It calls `FollowReferences()` with that array as the initial object. Callback filtering limits normal expansion to the selected boundary objects.

If JNI setup fails or leaves an exception, the tracker marks the operation as truncated. It does not mark the affected entries as expanded. A later pass can retry them.

The callback stops admission when it reaches the edge budget, deadline check, hop cap, frontier cap, or abort request. These checks bound admitted work. They do not provide a strict bound on JVMTI operation duration.

## Candidate tags and correlation

`pollWatchedTargets()` asks `LivenessTracker` for at most five candidate classes. It then calls `tagLeakInstances()` for the current candidates.

Leak tags are positive tags from a fixed pool. Each reuse has an incarnation value. The incarnation prevents emission of an old owner's cached chain for a new owner of the same numeric tag.

Candidate representatives are not pre-tagged with negative marker tags. The walk discovers a candidate when it reaches a leak-tagged instance or correlates a leak tag with an object that the frontier already admitted.

For each watched class, the tracker keeps at most eight discovered frontier entries. A leak-correlated entry can replace an uncorrelated entry when those slots are full.

The tracker can complete a candidate search after each occupied candidate slot has produced a valid chain.

## Mutable references and rotation

An object can change after its first expansion. For example, a long-lived collection can receive a new backing array or new elements. The tracker uses bounded rotation to revisit selected entries.

| Rotation source | Per-pass selection limit | Purpose |
|---|---:|---|
| Leak accumulation | 16 | Select parents that accumulate instances of watched classes. |
| Stale expanded entries | 256 | Provide eventual low-priority rechecks across the frontier table. |
| Transient root kinds | 16 | Improve root attribution when later observations provide a more durable root kind. |
| Static anchors | 32 selected, plus 16 FIFO entries | Descend from selected objects held by static fields. |

Leak accumulation has two levels. The first groups admissions by leaf class and parent class. The second ranks parent object tags within the selected group.

When a class first becomes watched, the tracker scans existing expanded entries for matching stable class tags. This scan supplies data that admission-time tracking could not collect before the class became watched.

Rotation improves coverage but remains bounded and best effort.

## Search termination

The implementation evaluates terminal conditions after each pass, in this priority order
(`runPass()`, `referenceChainTraversal.cpp`). A search can:

1. Abandon with `FRONTIER_CAP` when the frontier cannot admit another entry.
2. Complete when the pass has no pending truncated work and no class remains under watch.
3. Abandon with `TTL` when the configured search lifetime expires.
4. Abandon with `TTL` when the frontier makes no progress for 30 passes and the urgent latch is not active.
5. Complete when all current candidates have been found.
6. Abandon with `CANARY_STUCK` when both frontier progress and candidate progress remain stalled for their limits.

The no-progress `TTL` check runs before the `CANARY_STUCK` check, and `CANARY_STUCK` also
requires 30 passes without frontier progress. `CANARY_STUCK` can therefore fire only while
the urgent latch is active.

`ReferenceChainTracker::stop()` forces a running search into a terminal state with the internal
reason `RECORDING_END`, so the next recording starts a fresh search. No abandonment event is
emitted for this reason.

The base candidate-stall limit is 30 passes. Consecutive `CANARY_STUCK` restarts can double this limit, up to eight doublings. Other terminal outcomes reset that escalation.

`datadog.ReferenceChainAbandoned` records an abandonment. The event queue is separate from the resolved-chain cache.

## Cost control

The implementation controls different costs separately:

- `_effective_budget` limits edge admission for ordinary work.
- `_pause_pid` adjusts that budget from measured in-safepoint time.
- `_effective_cadence_ns` changes when the budget controller reaches a limit.
- `_safepoint_pain_budget` gates a later search.
- `_cpu_pain_budget` gates passes in the current search.
- `_configured_frontier_cap` limits native metadata.
- `_ttl_ms` limits search lifetime.

For resumable traversal phases, the pause target controls when a callback asks JVMTI to
stop. Callback granularity and JVM work can cause overshoot. Root enumeration does not
use this deadline. See [Reference-chain scheduling and cost control](ReferenceChainsSignalsExplained.md).

## Automatic defaults

`autoTuneDefaults()` changes only options that the user did not set.

- The edge budget scales with the square root of the maximum heap size.
- The first-pass budget defaults to 10 times the resulting edge budget, up to its cap. If the
  maximum heap size is unknown, auto-tuning is skipped, and an unset first-pass budget becomes
  `min(50 × budget, 200000)` instead.
- The TTL scales with heap size, up to 30 minutes.
- The frontier cap scales with the edge-budget ratio.
- The code caps the pause target at 50 milliseconds.
- The code caps the cost-budget refill percentage at 5 percent.

These values are tuning inputs. They do not state guaranteed overhead.

## Configuration

Reference-chain collection requires the allocation engine and a leak-signal source. The signal
source is generations tracking OR liveheap tracking (the two drive the same liveness mechanisms;
liveheap additionally preserves stack traces for its samples). With neither, the leak-signal gate
can never pass and the collector stays idle. Enable one of them in the same command:

```text
generations=true,referencechains=true:hops=N:budget=N:ttl=N:framecap=N:pausetarget=N:painbudget=N:firstpassbudget=N
```

- `generations=true` activates the allocation engine and supplies leak candidates. Liveheap
  tracking (`memory=<interval>b:l|L`) is an equivalent signal source.
- `hops` limits chain depth.
- `budget` supplies the base edge-admission budget.
- `ttl` sets search lifetime in milliseconds. A value at or below zero disables this time check.
- `framecap` limits frontier entries.
- `pausetarget` supplies the controller target in milliseconds.
- `painbudget` supplies the cost-budget refill percentage.
- `firstpassbudget` supplies the root-enumeration edge budget.

The parser clamps values to implementation limits. Consult `arguments.h` for current defaults and maximum values.

## JFR output

`buildChainEvent()` reconstructs a chain by following `parent_tag` values in the frontier table. Static-field-rooted chains can add the declaring class as the root-side type.

`cacheResolvedChain()` stores resolved chains per source frontier tag, not per class. The cache
holds at most 128 entries. It rejects a chain whose leak-tag owner has already died. When the
cache is full, it first evicts entries cached by an earlier search. If that frees no slot, it
drops the new chain and increments `REFERENCE_CHAIN_EVENTS_DROPPED`.

`drainPendingChainEvents()` is a snapshot operation despite its name. It copies valid cached chains and keeps them for later dumps. Before emission, it checks the leak-tag incarnation and removes entries whose tag now belongs to another object.

The dump thread writes `datadog.ReferenceChain` events. The traversal thread does not write JFR events.

## Result semantics

A chain can combine observations from different passes. It is not a consistent heap snapshot.

The implementation does not guarantee:

- The shortest path.
- The only retaining path.
- A result for every candidate.
- Observation of every reference mutation.
- A hard real-time pause limit.

Consumers must use the chain as diagnostic evidence and must also inspect abandonment events and drop counters.
