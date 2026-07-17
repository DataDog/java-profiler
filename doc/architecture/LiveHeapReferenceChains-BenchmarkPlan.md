# Phase 5 Benchmark Plan: Reference Chains Tuning

**Status:** Plan only — no benchmark in this document has been run. Nothing below is a
measured result. This document exists so a human or a future agent with real hardware
access can execute Phase 5 without re-deriving scope from scratch.

**Companion docs:** [LiveHeapReferenceChains.md](LiveHeapReferenceChains.md) (design,
Open Question 2 and Termination section), [LiveHeapReferenceChains-ImplementationPlan.md](LiveHeapReferenceChains-ImplementationPlan.md)
(Phase 5 section, which this document expands into something executable).

## What is currently in code (as of this writing)

Every tunable this plan measures currently ships as a **provisional default**, labeled
in code comments as "provisional default pending Phase 5 empirical tuning" (not
benchmark-derived):

| Tunable | Current default | Location |
|---|---|---|
| Hop cap | 200 | `arguments.h`, `DEFAULT_REFERENCE_CHAINS_HOP_CAP` |
| Per-pass edge budget | 1000 | `arguments.h`, `DEFAULT_REFERENCE_CHAINS_BUDGET` |
| Per-search wall-clock TTL | 60000 ms | `arguments.h`, `DEFAULT_REFERENCE_CHAINS_TTL_MS` |
| Frontier-size cap | 65536 entries | `arguments.h`, `DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP` |
| Frontier table initial capacity | 1024 | `referenceChains.h`, `FrontierTable::INITIAL_TABLE_CAPACITY` |
| Pass-scheduling fallback cadence | 1 s | `referenceChains.h`, `ReferenceChainTracker::PASS_CADENCE_NS` |

Running the matrix below and recording results is what turns each of these from
"conservative guess" into "measured default." Until that happens, do not describe any of
these values as benchmark-derived in code comments, commit messages, or the design doc.

## Heap-shape / collector / size matrix (from the Implementation Plan's Phase 5 section)

Minimum matrix, unchanged from the implementation plan:

| Dimension | Values |
|---|---|
| Heap shape | narrow-deep chain, wide-shallow fan-out, mixed |
| Collector | G1, ZGC (Shenandoah is a stretch goal, not a blocker) |
| Live-set size | small (~256 MB live set), large (~4 GB live set) |

3 shapes × 2 collectors × 2 sizes = **12 cells minimum**. Each cell needs the target JVM
started with `-XX:+Use<Collector>GC` and a live-object generator sized to hold the
target live-set roughly constant while `FollowReferences` walks it (see generator note
below) — a synthetic heap-graph generator that only allocates and never retains would
defeat the point of measuring a walk over a *live* graph.

## What a JMH benchmark class would need to look like

This repo's existing JMH benchmarks live under
`ddprof-stresstest/src/jmh/java/com/datadoghq/profiler/stresstest/`, organized into
`scenarios/<theme>/` packages (e.g. `scenarios/throughput/`, `scenarios/counters/`),
each a plain class with `@Benchmark`-annotated methods, an `@State`-annotated fixture
class (see `scenarios/counters/GraphState.java` for a fixture that pre-builds a graph of
JMH-benchmarked nodes), and run via `Main.java`'s harness
(`ddprof-stresstest/src/jmh/java/com/datadoghq/profiler/stresstest/Main.java`). A new
`scenarios/referencechains/` package, following this exact shape, is the natural home:

- **`ReferenceChainsGraphState`** (`@State(Scope.Benchmark)`): builds and retains a live
  object graph matching one heap-shape cell (narrow-deep / wide-shallow / mixed),
  parameterized by node count and fan-out so the same generator can hit both the
  ~256 MB and ~4 GB live-set targets. This should extend/reuse the synthetic-graph
  generator already used by the Phase 3/4 native gtest fixture
  (`ddprof-lib/src/test/cpp/referenceChains_ut.cpp`'s `ReferenceChainsBfsTest` /
  `ScriptedClass` machinery), per the implementation plan's explicit instruction not to
  write a second generator — the JMH state class would need a *real* Java object graph
  (not the gtest's mocked JVMTI callbacks), but the shape parameters (node count,
  fan-out, chain depth) should mirror the same knobs.
- **`ReferenceChainsPassBenchmark`**: a `@Benchmark` method that calls into the agent
  (via the existing `AbstractProfilerTest`-style JNI/attach path this repo already uses
  for integration tests, e.g. `ddprof-test/src/test/java/com/datadoghq/profiler/memleak/LivenessTrackingTest.java`
  as the closest existing precedent for driving this subsystem from Java) with
  `referencechains=true:hops=<H>:budget=<B>:ttl=<T>:framecap=<F>` and measures:
  - per-pass wall-clock pause (wrap the `FollowReferences`/`GetObjectsWithTags` call
    boundary, or measure via async-profiler wall-clock samples around the call, per the
    implementation plan's stated harness — async-profiler validation, not just JMH
    timers, since a JMH `@Benchmark` return-to-caller time does not by itself distinguish
    "safepoint pause" from "everything else the call did").
  - passes needed to reach a synthetic target object at a known depth (drive the
    benchmark to call `runPass()` in a loop until `searchState()` leaves `RUNNING`,
    counting `passesRun()`).
  - frontier-table peak occupancy (`FrontierTable::size()`, exposed for tests already via
    `frontierTable()`).
- **`ReferenceChainsCadenceBenchmark`**: a `@Benchmark` variant that runs a fixed total
  amount of BFS work as one single non-resumable pass (`budget` set high enough to never
  truncate) vs. spread across N passes at the candidate cadence, and compares the p99
  pause of each — this is the specific comparison Open Question 5 and the implementation
  plan's Phase 5 section ask for ("the bar to clear is p99 pause drops materially versus
  the single-pass baseline").

None of the classes above exist yet. Writing and running them is exactly the out-of-scope
work this document defers to a future pass with real hardware.

## What each measurement would feed

| Measurement | Feeds this decision |
|---|---|
| Per-pass wall-clock pause distribution (p50/p99) across the matrix | Per-pass edge budget default (`DEFAULT_REFERENCE_CHAINS_BUDGET`) — the largest budget whose p99 pause stays acceptable |
| Passes needed to reach a target sample at various depths | Hop cap default (`DEFAULT_REFERENCE_CHAINS_HOP_CAP`) and TTL default (`DEFAULT_REFERENCE_CHAINS_TTL_MS`) — is 200 hops / 60 s enough headroom for realistic chain lengths, or wasteful? |
| Frontier-table peak occupancy per cell | Frontier-size cap (`DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP`) and the table's initial capacity (`FrontierTable::INITIAL_TABLE_CAPACITY`) — set the cap above realistic peak occupancy for the matrix's largest cell with headroom, and the initial capacity close to the smallest cell's typical occupancy to avoid redundant `growLocked()` calls |
| Safepoints/second and per-pause duration at the candidate cadence vs. a single-pass baseline covering the same work | Pass-scheduling cadence (`PASS_CADENCE_NS`) and Open Question 5's overall verdict — does the incremental design actually improve p99 pause, or should it be revisited |
| (Time permitting) one-search-per-sample vs. batched multi-target BFS comparison | Open Question 3 — whether batching is worth the added complexity of coupling unrelated samples' termination conditions |

## Decision rule (carried over from the implementation plan)

A placeholder only counts as resolved once a specific value is chosen **and** the
measurement that justified it is written down — collecting numbers without picking a
default does not close Phase 5. When this benchmark plan is executed, record results and
chosen values either as a "Tuning results" appendix to the implementation plan, or
directly in the design doc's Open Questions section (Question 2), replacing the
"provisional default" label in code with a comment citing the actual measurement.

## Explicitly out of scope for this document

- Running any of the benchmarks described above.
- Any numeric result, chart, or percentile figure — none exist yet for this subsystem.
- Implementing the JMH classes themselves (sketched above, not written).
