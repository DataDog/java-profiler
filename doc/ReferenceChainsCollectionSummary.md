<!-- Copyright 2026, Datadog, Inc. -->

# Reference-chain collection summary

## Purpose

Reference-chain collection helps explain why a sampled object remains live. It records a bounded chain of referrer classes from a GC root to a sampled object. It does not replace a heap dump or compute an exact retained set.

The profiler disables this feature by default. Enable generation tracking or liveheap tracking
(either supplies the leak signal) together with reference-chain collection, e.g.
`generations=true,referencechains=true`. The bare `referencechains=true` option does not activate
the allocation engine that supplies candidates, and without a signal source the collector stays
idle: it never starts a search.

## Data flow

1. `LivenessTracker` counts sampled live objects by class across GC epochs.
2. It selects classes whose sampled population has sustained growth.
3. It assigns leak tags to tracked instances of those classes.
4. `ReferenceChainTracker` walks from roots toward those tagged instances.
5. The tracker stores its frontier as JVMTI object tags and resumes it in later passes.
6. When the walk reaches a tagged instance, the tracker reconstructs its chain.
7. The dump path writes the chain as a `datadog.ReferenceChain` JFR event.

In this document, *class* means the Java class. Source identifiers use the existing `klass` spelling.

## Candidate selection

`LivenessTracker` keeps a fixed-size population table. Each entry has a ring of 30 GC-epoch samples. The tracker requires at least 10 samples before it evaluates a trend.

A class must show sustained growth. The base hysteresis is five qualifying epochs. It decreases to three epochs when the post-GC heap floor also rises. The tracker returns at most five candidate classes.

The population table has at most 256 entries. A linear scan is therefore bounded and occurs outside the allocation hot path. The existing table lock protects the population data.

Candidate selection uses sampled objects. It can miss a leak when sampling does not retain enough representative objects or when the population does not satisfy the trend gates.

## Resumable walk

`ReferenceChainTracker` owns a background thread and a persistent frontier. The frontier contains positive JVMTI tags. JVMTI preserves tag identity when the GC moves an object. A tag does not keep an object live.

Each pass can perform these operations:

1. Enumerate roots and stack references. The first pass always does this. Later passes retry a truncated enumeration or wait at least two seconds.
2. Walk candidate thread objects when the candidate data identifies qualifying threads.
3. Scan static fields in chunks when the loaded-class count changes.
4. Expand a batch of frontier entries.
5. Revisit selected entries whose references can change after their first expansion.

The walk records parent tags, class identifiers, depth, root kind, admitting-edge identity (field index and reference kind), and leak-tag data in the frontier table. These records let the tracker reconstruct a chain after the walk reaches a candidate instance.

The walk is best effort. The heap can change between passes. A recorded chain is therefore historical evidence from several observations, not a single consistent heap snapshot.

## Candidate correlation

`LivenessTracker::tagLeakInstances()` assigns positive leak tags from a fixed pool. The heap walk correlates a leak tag with a frontier entry when it reaches that object. The tracker can keep up to eight discovered instances for each watched class.

The implementation does not pre-tag candidate representatives with negative marker tags. Older design material that describes marker tags is obsolete.

While a candidate search is active, `LivenessTracker` admits allocations from qualifying threads at 100 percent. Other allocations still use the configured liveness-sampling ratio. This admission increase improves correlation for small per-thread populations.

## Mutable-container coverage

A one-time breadth-first walk cannot observe references that appear after the first expansion of an object. This matters for a long-lived collection that receives new elements.

The tracker addresses this case with bounded rotation:

- Leak-accumulation rotation selects parent objects that receive instances of watched classes.
- Stale-entry rotation revisits older expanded entries.
- Root-kind rotation revisits entries with transient root attribution.
- Static-anchor rotation descends from selected objects held by static fields.

Rotation improves coverage. It does not guarantee that the tracker observes every mutation.

## Cost controls

The implementation uses several independent controls:

- An edge-admission budget limits work admitted by callbacks.
- A pause target guides a PID controller that adjusts the edge budget and fallback cadence.
- A safepoint-cost budget gates the start of a later search.
- A CPU-cost budget gates passes in a running search.
- A frontier cap limits metadata growth.
- A search TTL and no-progress checks stop searches that do not converge.

Most traversal work is resumable. A callback asks JVMTI to stop when it observes the
pause deadline, and a later pass continues from the saved frontier. The operation can
still exceed the target because the JVM can work between callbacks.

Root enumeration is the main exception. JVMTI does not expose a cursor for resuming
`IterateOverReachableObjects()`, and the edge budget counts admitted roots rather than
all examined roots. For this release, a root-enumeration pause is acceptable if it is
shorter than three seconds. This is an acceptance threshold, not the desired latency or
a hard real-time guarantee. [PROF-16284](https://datadoghq.atlassian.net/browse/PROF-16284)
tracks measurement and improvement of this phase.

`stopThread()` requests cooperative cancellation. The heap callback checks the request on each invocation. Cancellation therefore depends on the JVM reaching another callback; it is not instantaneous.

## Completion and abandonment

A search completes when all current candidates have chains, or when no work remains and no class remains under watch.

A search can stop with one of these abandonment reasons:

- `FRONTIER_CAP`: the frontier table cannot admit more entries.
- `TTL`: the configured lifetime expired, or the ordinary frontier made no progress for 30 passes.
- `CANARY_STUCK`: candidate discovery and frontier growth both remained stalled for the configured checks. The ordinary no-progress `TTL` check runs first, so this reason appears only while the OOM-urgent latch is active.

The tracker reports abandonment through `datadog.ReferenceChainAbandoned`. It releases search-owned tags before a restart. A restart also requires a current leak signal and sufficient safepoint-cost budget.

## Output and limits

The resolved-chain cache holds at most 128 entries. The dump path copies valid cached chains without clearing the cache, so a live sample can appear in later JFR chunks. The cache removes a chain when the leak-tag ownership no longer matches the recorded instance.

The output has these limits:

- It contains referrer classes and selected edge metadata, not a complete object graph.
- It can omit paths because of sampling, hop limits, budgets, mutation, or abandonment.
- It can describe observations from different points in time.
- It does not prove that a reported path is the shortest path or the only retaining path.

For implementation details, see [LiveHeapReferenceChainsImplementation.md](architecture/LiveHeapReferenceChainsImplementation.md). For scheduling details, see [ReferenceChainsSignalsExplained.md](architecture/ReferenceChainsSignalsExplained.md).
