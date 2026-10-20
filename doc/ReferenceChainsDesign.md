<!-- Copyright 2026, Datadog, Inc. -->

# Reference chains for surviving live-heap samples

**Status:** Implemented

## Decision

Use an incremental breadth-first walk from GC roots. Persist the frontier with JVMTI object tags. Run the walk in multiple bounded-work passes.

This document records the design decision. It does not describe every current implementation detail. See [LiveHeapReferenceChainsImplementation.md](architecture/LiveHeapReferenceChainsImplementation.md) for the as-built behavior.

## Goal

For selected live-heap samples, record a chain of referrer classes from a GC root to the sampled object.

The chain is diagnostic data. It is not an exact retainer analysis.

## Constraints

- The profiler must work on supported stock JDKs.
- The profiler must not require a patched JVM.
- Graph expansion must not require one unbounded stop-the-world operation.
- The feature must limit memory use and background work.
- The result can be incomplete.

## Non-goals

- Find every path to every GC root.
- Compute retained sizes or dominators.
- Record a complete heap graph.
- Provide a consistent heap snapshot across all passes.
- Guarantee a fixed maximum pause time.

## Options

### Full reverse-reachability walk

A complete reverse graph gives strong results, but its work grows with the live heap. Starting it during an existing GC pause does not remove that work. Many collectors also do not provide a suitable full-heap pause on demand.

We rejected this option because it does not meet the pause-distribution goal.

### Incremental breadth-first walk

HotSpot JFR uses a root-based graph search for old-object paths. The profiler uses the same general direction, but it persists work between passes and records a smaller result.

We chose this option because JVMTI supplies the required portable operations:

- Root and stack-reference enumeration.
- Reference traversal.
- Object tags that survive object relocation.
- Object lookup by tag.

This option remains best effort. A moving and mutating heap can change between passes.

### Collector-internal hooks

G1, Shenandoah, and ZGC have internal traversal mechanisms. An external agent does not have a stable API for these implementation details. Calling private symbols would bind the profiler to JVM build details and collector internals.

We rejected this option because the profiler supports multiple JDK vendors and versions.

## Why tags make resumption possible

The GC can move an object between passes. A raw address would then become invalid. A JVMTI tag identifies the object after relocation.

A tag does not keep the object live. If the object dies before the next pass, lookup by tag does not return it. The tracker can then remove that branch from pending work.

The frontier table stores the information needed to reconstruct a chain:

- The object tag.
- The parent tag.
- The referrer class.
- The reference depth.
- The root kind.
- The candidate leak tag, when available.

The implementation places fixed caps on the frontier and on chain depth.

## Pass model

The tracker separates root discovery from frontier expansion.

1. Root enumeration admits root-attached objects.
2. Static-field scanning admits objects that root callbacks do not report as static-field edges.
3. Frontier expansion resolves a batch of tags and follows one bounded step from those objects.
4. Rotation revisits selected expanded objects whose outgoing references can change.

The edge budget and callback deadline stop admission after the current limit. A later
pass continues frontier expansion from saved tags. JVMTI can still perform work before
or between callbacks, so the deadline is not a hard real-time bound.

Root enumeration is not resumable through the JVMTI API. Aborting it and retrying starts
again from the first root, which can prevent later roots from being examined. The current
release therefore permits this phase to finish. For this release, a root-enumeration
pause is acceptable if it is shorter than three seconds. Improvement is
tracked in [PROF-16284](https://datadoghq.atlassian.net/browse/PROF-16284).

## Scheduling

The JVMTI specification restricts functions that an agent can call from heap and GC callbacks. The profiler therefore does not run the heap walk from a GC callback. A GC callback only updates an atomic epoch.

The background thread calls the JVMTI heap functions. The JVM performs the required safepoint operation for those calls.

The scheduler uses the GC epoch, a fallback cadence, leak signals, adaptive cost budgets, and candidate-search backoff. See [ReferenceChainsSignalsExplained.md](architecture/ReferenceChainsSignalsExplained.md).

## Correctness model

The tracker constructs a chain from observations that can occur in different passes. It guarantees neither a single-snapshot view nor the shortest retaining path.

The chain remains useful when it identifies a plausible root class and a sequence of referrer classes. Consumers must treat missing chains as an expected outcome. Sampling, mutation, depth limits, time limits, and frontier limits can all prevent a result.

## Trade-offs

The design improves pause distribution. It does not guarantee lower total stop-the-world time. Repeated passes can use more total work than one complete walk because they resolve tags and revisit entries.

The design also uses native metadata for the frontier. The frontier cap bounds this memory use. A cap hit abandons the search and emits a diagnostic event.

## Sources

- [JVM TI specification: Heap functions](https://docs.oracle.com/en/java/javase/25/docs/specs/jvmti.html#Heap)
- [OpenJDK JFR leak-profiler chain implementation](https://github.com/openjdk/jdk/tree/master/src/hotspot/share/jfr/leakprofiler/chains)
