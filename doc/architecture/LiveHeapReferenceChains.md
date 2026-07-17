# Reference Chains for Surviving Live Heap Samples

**Status:** Design proposal (no implementation)
**Date:** 2026-07-07
**Jira:** [PROF-15341](https://datadoghq.atlassian.net/browse/PROF-15341)

## Implementation status

The "Chosen design" section below has been implemented following
[LiveHeapReferenceChains-ImplementationPlan.md](LiveHeapReferenceChains-ImplementationPlan.md)
(Phases 0-7). It is off by default; the shipping switch is the `referencechains` argument
parsed by `Arguments` (`arguments.cpp`'s `CASE("referencechains")`), e.g.
`referencechains=true:hops=64:budget=2000:ttl=60000:framecap=65536`.

Read this status note alongside the actual code before relying on it, not instead of it:

- **The BFS engine (frontier table, tag lifecycle, incremental resumption, termination,
  JFR event shapes) is implemented and unit-tested** (`ddprof-lib/src/main/cpp/referenceChains.h`/
  `.cpp`, `ddprof-lib/src/test/cpp/referenceChains_ut.cpp`).
- **The lifecycle gap is closed: it now runs inside a live profiling session.**
  `Profiler::start()` (`profiler.cpp`) calls `ReferenceChainTracker::instance()->start(args)`
  (gated on `args._reference_chains`, independent of the CPU/wall/alloc engine mask, the
  same way `malloc_tracer`/`NativeSocketSampler` are gated on their own flags) followed by
  the new `ReferenceChainTracker::startThread()`, which spawns the BFS thread
  (`threadLoop()`) - safe there because the JVM/JVMTI environment is already fully up by
  that point in the lifecycle, unlike inside `start()` itself, which must stay callable
  with no live JVM for `referenceChains_ut.cpp`'s tests. `Profiler::stop()` calls the
  matching `stopThread()`/`stop()` pair. Because `start()` runs, `SetEventNotificationMode`
  for the GC callbacks is now actually invoked, so `onGCStart()`/`onGCFinish()` fire and the
  BFS thread's `shouldRunPass()` scheduling loop (GC-epoch signal or the fixed cadence) is
  live. A `datadog.ReferenceChainAbandoned` event now reaches a real `Recording`: when a
  dump is requested (`Profiler::dump()`, the same call site that already flushes
  `LivenessTracker`) and the search's state is `SearchState::ABANDONED`,
  `buildAbandonedEvent()`'s output is written via the new
  `Profiler::writeReferenceChainAbandoned()` / `FlightRecorder::recordReferenceChainAbandoned()`
  wrappers (mirroring `writeHeapUsage()`'s exact shape).
- **`buildChainEvent()` now has a call site: the target-selection feed is closed.**
  `ReferenceChainTracker::pollWatchedTargets()` (referenceChains.cpp), called from
  `threadLoop()` once per scheduling cycle after `runPass()`, is that feed. It polls
  `LivenessTracker::selectLeakCandidates()` (the positive population-slope ranking, Open
  Question 3 below) and, for each ranked klass's live representative instance that an
  ordinary `runPass()` walk has *already* tagged (`getTag() > 0` - a read, never a `SetTag`
  seed; see Open Question 3 for why the design's original seeding proposal was replaced),
  calls `buildChainEvent(tag, ...)` and emits the resulting `datadog.ReferenceChain` event
  via `Profiler::writeReferenceChain()` / `FlightRecorder::recordReferenceChain()` (the
  wrappers this leaves at `profiler.cpp`/`flightRecorder.cpp`, mirroring the abandoned-event
  path). A per-search `_emitted_target_tags` set de-duplicates so a klass flagged across
  consecutive polls emits its chain only once. This is gated on `_gc_generations` *and*
  liveness tracking both being enabled - `referencechains=...` alone still gets the
  whole-graph-only behavior (no target seeding), resolving Open Question 3's "still
  undecided" fallback. See
  `ddprof-test/src/test/java/com/datadoghq/profiler/referencechains/ReferenceChainTrackingTest.java`:
  `shouldReportAbandonedSearchOnTinyFrontierCap` exercises the abandonment path.
  `shouldReconstructReferrerChainToGcRoot` (Phase E's own exit criterion) is no longer
  `@Disabled`: it allocates a growing, real population of a fixture class, drives GCs and
  `Profiler::dump()` calls until `LivenessTracker::selectLeakCandidates()` trusts the resulting
  trend, then asserts on the `datadog.ReferenceChain` event `pollWatchedTargets()` produces -
  a real end-to-end exercise of this whole mechanism against a live JVM, not a synthetic
  frontier fixture.
- **Phase 5's tuning defaults are provisional, not empirically finalized.** The hop cap,
  per-pass budget, TTL, and frontier-size cap (`arguments.h`'s `DEFAULT_REFERENCE_CHAINS_*`
  constants) are explicitly-labeled placeholders; no benchmark against this codebase has
  run yet (see Open Question 2 below and the implementation plan's Phase 5).

## Goal

For a subset of live-heap samples that survive past their allocation window, produce
a **reference chain** — a sequence of referrer *types* (not full field-level paths, not
necessarily to *all* GC roots) connecting the sampled instance back to *a* GC root. This
is diagnostic information ("what kind of object chain is keeping this alive"), not a
heap-dump-grade exact retainer analysis.

## Constraints

- Must run cheaply, with as short a safepoint / STW contribution as possible.
- Must work on stock vendor JDKs the agent attaches to — no forked/patched JVM builds.
- Exhaustive (all-roots, full-path) chains are explicitly **not** required; referrer-type-only,
  bounded-depth, best-effort chains are acceptable.

## Approaches considered

Three approaches were evaluated; two are ruled out as launch requirements for concrete,
evidence-backed reasons. One sub-idea (Approach C's `ParallelObjectIterator` variant) is
explicitly kept open as a conditional future option; see its discussion below.

| # | Approach | Completeness | Complexity | Feasibility | Status |
|---|---|---|---|---|---|
| A | Full JVMTI `FollowReferences` reverse-graph walk, piggybacked on an already-scheduled major GC | 4/5 | 4/5 | 2/5 | Rejected |
| B | Bounded BFS-from-roots with frontier pruning (JFR "leak profiler" technique, adapted) | 3/5 | 3/5\* | 4/5 | **Chosen** |
| C | Hook GC mark/copy closures (G1, ZGC) to record parent pointers inline during marking | 2/5 | 5/5 | 1/5 | Rejected |

Scale (1-5 for each column): Completeness — higher is more complete (5 = closest to exhaustive all-roots/full-path); Complexity — higher is more complex to implement/maintain (5 = most complex, lower is better); Feasibility — higher is more feasible to ship on stock vendor JDKs (5 = most feasible). No single column dominates the decision; see the per-approach rationale below for why B was chosen despite not scoring highest on every column.

\* This 3/5 reflects only the single-pass BFS sketched at selection time. The "Chosen
design" section below replaces that sketch with an incremental, resumable BFS
(JVMTI-tag-based frontier persistence across GC cycles, an agent-thread-driven pass that
gets its safepoint transparently from the JVMTI heap-walk call it makes, GC-callback
signaling, and explicit termination/tag-cleanup bookkeeping), which is materially more
complex than this score suggests — closer to 4/5 in implementation and maintenance
effort. The score is left unchanged above (it documents the state of the comparison at
decision time) rather than retroactively edited.

### A — Full reverse-reachability walk (rejected)

Safepoint length scales with live-set size regardless of how the walk is triggered.
Modern regionalized collectors (G1, Shenandoah) rarely perform a true full-heap walk
during ordinary major GCs, so "ride an already-paid pause" is not a reliable amortization
strategy. Cost is fundamentally at odds with the "short safepoint" constraint.

### B — Bounded BFS-from-roots (chosen)

Mirrors OpenJDK's own `jdk.OldObjectSample` leak-profiler implementation
(`src/hotspot/share/jfr/leakprofiler/chains/{edgeStore,bfsClosure,dfsClosure}.cpp`):
a `VM_Operation`-driven BFS from GC roots, retaining only edges on the frontier toward a
small, fixed sample set, with a hard hop cap (HotSpot itself caps chains at ~200 hops,
split 100/100 from leaf and from root). We can go cheaper than JFR because only the
**referrer class**, not object identity or field name, is needed — the `EdgeStore`
degenerates to `(referrer_klass, parent_tag, depth)` records, where `parent_tag` links
each record back to the record that discovered it, enabling chain reconstruction.

Adopting this pattern is a re-scoping of proven, shipping HotSpot code, not a novel
algorithm design.

### C — GC mark/copy closure piggyback (rejected)

Investigated specifically for G1 and ZGC on the premise that per-edge referrer
information is already available inside the collector's own marking/evacuation closures
(`G1ParCopyClosure::do_oop_work`, ZGC's `ZMarkConcurrentRootsIteratorClosure` /
load-barrier closures), so recording it would cost nothing beyond what the GC already
pays.

Rejected because there is no stable, externally reachable hook into these closures:

- They are internal, template-instantiated C++ classes compiled into `libjvm.so` at
  HotSpot build time — not a registrable/pluggable extension point.
- This differs categorically from `VMStructs`-style introspection already used in this
  codebase (`ddprof-lib/src/main/cpp/hotspot/vmStructs.cpp`), which reads VM state
  passively via an officially exported offset table. Intercepting a GC closure's
  *behavior* would require either shipping a patched OpenJDK build (a fork/maintenance
  commitment far beyond anything in this codebase) or binary-patching unversioned,
  per-build-mangled function addresses — not shippable across JDK point releases.

A related idea — using HotSpot's internal `ParallelObjectIterator`
(landed via [JDK-8322043](https://www.mail-archive.com/serviceability-dev@openjdk.org/msg12977.html),
used by `VM_HeapDumper` to partition heap regions across GC worker threads for parallel
heap dumping) to shrink Approach B's safepoint by parallelizing the walk — was also
investigated. Same verdict: it is an internal C++ class, not exposed via JVMTI, with no
stable ABI for an attached agent to call. Symbol-sniffing internal HotSpot functions *is*
an established pattern in this codebase (`VMStructs::findHeapUsageFunc`,
`vmStructs.cpp:489-509`), but that precedent covers a single leaf virtual method with a
value/POD-ish return; `ParallelObjectIterator` is a multi-class subsystem that coordinates
the VM's own GC worker threads under safepoint control — an order of magnitude larger
fragility surface, with a much higher blast radius if a layout assumption is wrong (GC
worker-thread coordination corruption vs. a bad JMX stat). Not pursued as a launch
requirement; revisit only if Approach B's single-threaded pause proves to be a measured
bottleneck, and treat it as an isolated, heavily version/flag-gated fast path with
automatic fallback — never a dependency.

## Chosen design: incremental, resumable bounded BFS

A single-pass bounded BFS still means one pause sized to whatever budget is configured.
The refinement below spreads that budget across multiple short passes instead of one
contiguous one, trading a possibly-higher *aggregate* STW total for a much better
*latency distribution* — no single long tail pause.

### Why the frontier can survive across passes: JVMTI object tags

The obstacle to pausing and resuming a BFS is that the frontier (the worklist of
not-yet-expanded objects) is normally a set of raw addresses, and a moving/compacting GC
between passes can relocate or collect any of them.

JVMTI object tags solve this:

- Tags are identity-based and GC-move-transparent — a tagged object can be re-resolved
  after a GC regardless of where it moved.
- Tags are **non-retaining** — tagging does not keep an object alive. This is a *new*
  subsystem dependency, not a reuse of one: the existing live-object sampler
  (`LivenessTracker`, `livenessTracker.cpp`) does not use JVMTI tags at all — it
  correlates sampled objects via JNI weak global references (`NewWeakGlobalRef`) held in
  its own index table with its own locking and GC-triggered cleanup
  (`livenessTracker.cpp:327-357`, `:53-70`). Non-retention is a property both mechanisms
  happen to share, not evidence that this reuses proven infrastructure.
- **Investigated replacing tags outright with `LivenessTracker`'s weak-ref + index-table
  pattern — resolved as "adopt the table pattern, keep the tags."** The pattern cannot
  fully substitute for tags: `FollowReferences`/`IterateThroughHeap` (the calls that
  actually discover a frontier object's referrers) can filter/report against a *tagged*
  object set natively; a JNI weak-ref table has no hook into that machinery, so the
  frontier-discovery step would still need tagged objects regardless of what stores the
  metadata. What the investigation *does* carry over: `LivenessTracker`'s proven
  `TrackingEntry`-style slot table — CAS-based index allocation, a signal-safe `SpinLock`
  (`spinLock.h`), doubling-resize, and GC-epoch-triggered cleanup
  (`livenessTracker.cpp:152-176`, `:213-278`, `:369-409`) — is a better-precedented design
  for the frontier's *metadata* storage than inventing one from scratch, since a JVMTI tag
  is a single `jlong` with no room for `(parent_tag, referrer_klass, depth)` on its own.
  Recommendation: use the tag as an index into a `TrackingEntry`-style table (fields:
  `parent_tag`, `referrer_klass`, `depth`) rather than encoding all three into the tag
  value or a from-scratch hashmap. See "Frontier metadata storage" below and Open
  Question 4.
- Non-retention gives incremental resumption a useful side effect for free: if a frontier
  object dies between passes, it simply fails to re-resolve on the next pass. That branch
  of the search is pruned automatically, with no extra liveness bookkeeping required.

### Data structures

- **Frontier**: a set of `(tag, parent_tag, referrer_klass, depth)` records. `tag` is the
  JVMTI tag assigned to a not-yet-expanded object; `parent_tag` links back for chain
  reconstruction; `depth` supports the hop cap.
- **EdgeStore**: accumulates `(referrer_klass, parent_tag, depth)` per discovered edge for
  objects that are on a path toward a target sample. Keyed by tag, not address —
  degenerate relative to JFR's `EdgeStore` since object identity/field names are not
  required, but it retains the same `parent_tag` linkage field as the Frontier so a chain
  can be walked back from a target sample to a root by following `parent_tag` across
  EdgeStore records.

### Frontier metadata storage: reusing `LivenessTracker`'s table pattern

A JVMTI tag is one `jlong` — it can identify a frontier object and make it visible to
`FollowReferences`/`IterateThroughHeap`, but it cannot itself hold the three fields
(`parent_tag`, `referrer_klass`, `depth`) each Frontier/EdgeStore record needs. Two ways
to close that gap were considered:

1. Build a bespoke hashmap keyed by tag value, from scratch.
2. Reuse `LivenessTracker`'s existing slot-table design (`livenessTracker.h:21-30`
   `TrackingEntry`, `livenessTracker.cpp:152-176` sizing, `:213-278`/`:369-409` CAS slot
   allocation and doubling resize, `spinLock.h`'s signal-safe `SpinLock`), using the tag
   value as the slot index instead of a `jweak` as the identity handle.

(2) is the better-precedented choice — it's shipping code, already exercises the exact
"per-slot payload, GC-cycle-driven cleanup, contention-safe locking" shape this needs —
provided the sizing formula is **not** copied as-is. `LivenessTracker` sizes its table
from `max_heap / sampling_interval` (a flat allocation-sample rate,
`livenessTracker.cpp:152-176`, capped at `MAX_TRACKING_TABLE_SIZE = 262144`,
`livenessTracker.h:39`); a BFS frontier's width is driven by per-hop fan-out in the object
graph, not by an allocation rate, and multiple concurrent searches (one per live-heap
sample being chased, see Open Question 3) each need their own capacity — the existing
formula does not transfer and a new one is an open question (folded into Open Question 2).

### Algorithm

1. Seed the frontier from GC roots (first pass) or from the persisted frontier
   (resumed pass).
2. Resolve currently-live tagged frontier objects. Objects that fail to resolve are
   dropped (dead — free pruning).
3. Expand the frontier up to a fixed per-pass budget (edge count or time slice).
4. Newly discovered objects are tagged and added to the frontier for the next pass.
5. Persist the frontier (native memory owned by the agent, not thread-local scratch) and
   return control to the VM.
6. Repeat until: a target sample is reached, the hop cap is hit, or a per-search
   abandonment limit (see Termination) is exceeded.

### Triggering passes: resolved — the profiler never schedules its own safepoint

Investigated whether pass-continuation work could ride the JVMTI
`GarbageCollectionStart`/`GarbageCollectionFinish` callbacks — the same callback this
codebase already uses to call `_heap_usage_func` (`vmStructs.cpp`) — instead of each pass
paying for its own safepoint.

**Correction to an earlier framing in this doc**: a pass does not run "inside a dedicated
`VM_Operation::doit()`" that the profiler constructs — HotSpot's `VM_Operation`/
`VMThread::execute()` machinery is internal, unexported C++ with no agent-facing entry
point; nothing outside HotSpot can submit one. What actually happens, confirmed against
`src/hotspot/share/prims/jvmtiTagMap.cpp` and `jvmtiEnv.cpp`:
`SetTag`/`GetTag` need no safepoint at all — they take only a `MutexLocker` over a
JVM-internal "hot lock" on the tag map. `FollowReferences`/`IterateThroughHeap` **do**
bring the VM to a safepoint, but the JVM does this internally and transparently
(`VM_HeapWalkOperation`/`VM_HeapIterateOperation`, dispatched via
`VMThread::execute()` *inside* HotSpot's own implementation of those calls) the moment an
ordinary attached agent thread calls them — the calling thread simply blocks until the
walk finishes. A pass is therefore: an agent-owned, already-attached thread (the same kind
`LivenessTracker` already runs on, see `livenessTracker.cpp:303-409`) calling
`FollowReferences`/`IterateThroughHeap` directly; the safepoint is a side effect of that
call, not something the profiler builds or schedules.

**Confirmed the VM is genuinely at a safepoint (all mutators stopped) for the full
duration of both callbacks**, on every collector:

- JVMTI spec: *"This event is sent while the VM is still stopped... the event handler
  must not use JNI functions and must not use JVM TI functions except those which
  specifically allow such use (see the raw monitor, memory management, and environment
  local storage functions)."*
- openjdk/jdk source: delivery is synchronous on the VMThread
  (`src/hotspot/share/prims/jvmtiExport.cpp:2752-2790`, comment *"this event is posted
  from VM-Thread"*); every call site is inside a safepoint-executing `VM_Operation::doit()`,
  backed by explicit asserts — e.g. Parallel GC's
  `assert(SafepointSynchronize::is_at_safepoint())` (`gc/parallel/psScavenge.cpp:305-306`),
  G1's `assert_at_safepoint_on_vm_thread()` (`gc/g1/g1VMOperations.cpp:141-157`),
  Shenandoah and ZGC wrapping the same `SvcGCMarker` only inside their respective
  `VM_Operation`/`VM_ZOperation::doit()` paths. Stable JDK 11 → mainline, across
  Serial/Parallel/G1/Shenandoah/ZGC.

**But this does not make the GC-triggered callback itself usable as the execution vehicle
for a pass.** The "functions which specifically allow such use" are exactly two:
`Allocate` and `Deallocate` (the entire **Memory Management** category). `SetTag`,
`GetTag`, `GetObjectsWithTags`, `FollowReferences`, and `IterateThroughHeap` are all in
the **Heap** category, which is *not* on that allowlist — calling any of them from inside
`GarbageCollectionStart`/`Finish` is exactly what the restriction forbids. The spec's own
prescribed escape hatch — notify a raw monitor from the callback, do the real work on a
separate agent thread — doesn't preserve "the pass rides the GC's own pause" property
either: the woken agent thread runs after the GC's collection pause has already ended
(mutators resumed), so calling `FollowReferences`/`IterateThroughHeap` there triggers a
**new**, separate safepoint of its own (per the corrected mechanism above) rather than
reusing the GC's.

The only way to fold the tag/walk work into the GC's own STW window would be to bypass
the official JVMTI entry points and reach into HotSpot's internal `JvmtiTagMap` directly
via symbol-sniffing — reintroducing exactly the fragility class already rejected for
Approach C (unversioned internal C++ state, no stable ABI). Doing that here would undo
the reason C was rejected.

**Conclusion: "no new marginal safepoints" is not achievable while staying within
official JVMTI usage.** Each pass still triggers its own safepoint — transparently, via
whichever agent thread calls `FollowReferences`/`IterateThroughHeap` for that pass, not
via anything the profiler schedules itself. The GC callbacks remain useful only as a
low-cost *signal* ("a GC just happened, a pass may be worth running soon") — not as the
execution vehicle for the pass itself. This does not change the core incremental design
(frontier persistence via JVMTI tags, self-pruning of dead branches, per-pass budget) —
it only removes the "zero marginal safepoints" claim from the cost/benefit case. The
design's actual value remains what it was framed as: trading one long pause for several
short, independently-triggered ones — a latency-distribution improvement, not a
total-STW reduction.

### Termination and abandonment

Because passes are spread across a mutating heap, a search that never reaches a root or
the hop cap could otherwise persist indefinitely, accumulating abandoned frontier state
across GC cycles. Required cutoffs:

- Hop cap (as in Approach B's single-pass form).
- A hard cap on passes-per-search or wall-clock TTL from first observation (value TBD —
  see Open Question 2).
- Explicit reporting of abandoned searches (no silent truncation) so this shows up as a
  measurable "chain not found within budget" outcome rather than being indistinguishable
  from "no chain exists."
- Tag release: on abandonment or completion, every JVMTI tag this search assigned to
  frontier/`EdgeStore` objects (`SetTag(obj, 0)`) must be cleared before the search's
  state is discarded. Without this, an abandoned search leaves its tags in place
  indefinitely, directly aggravating the tag-table sizing/contention risk raised in
  Open Question 4.
- A hard cap on frontier size (record count or native-memory footprint). The hop cap and
  pass/TTL cap bound how *long* a search runs, but not how *wide* the frontier can grow
  within that time — a wide fan-out graph could accumulate an unbounded number of
  `(tag, parent_tag, referrer_klass, depth)` records before either cutoff is hit. When
  the cap is reached, stop admitting new frontier entries for that search and report it
  as an abandoned/truncated search (value TBD — see Open Question 2).

### Correctness note: chains are historical, not a single consistent snapshot

A chain built across multiple passes stitches together `"A referenced B"` facts observed
at different points in time, not one frozen graph. For the stated purpose — explaining,
by referrer type, what typically retains this class of surviving object — this is
sufficient, and is not meaningfully weaker than a single-pass walk: GC roots (e.g. thread
stack frames) are themselves a live-changing set across a single pause's boundary, so
"one true snapshot" is already an approximation in the single-pass case. Any
documentation or output surface built on this must describe results as an **observed**
retaining path, not a claim about the object's current exact retention state.

### Cost/benefit summary

- **Does not reduce total STW time.** Each safepoint/callback entry pays fixed
  synchronization overhead; K short increments likely sum to equal or *more* aggregate
  pause time than one contiguous walk covering the same work.
- **Improves latency distribution.** No single long tail pause — the thing most likely to
  actually affect deployed application health (p99 latency, heartbeat timeouts), even
  when total accumulated pause-ms is flat or slightly worse.

## Non-goals

- Exhaustive paths to all GC roots.
- Field-level or object-identity-level chains (referrer *type* only).
- Any GC-internal-closure hook (Approach C) or internal parallel-iteration API use as a
  launch dependency.

## Open questions before implementation

1. ~~Confirm `GarbageCollectionStart`/`GarbageCollectionFinish` callback timing relative to
   safepoint release.~~ **Resolved** (see Triggering section): the callback is genuinely
   at a safepoint, but the JVMTI Heap-category functions needed to do frontier work
   (`SetTag`/`GetTag`/`FollowReferences`/`IterateThroughHeap`) are not in the callback's
   allowed function set. Each pass instead triggers its own safepoint transparently, via
   whichever agent thread calls `FollowReferences`/`IterateThroughHeap` for that pass —
   the profiler never constructs a `VM_Operation` itself (see correction in Triggering
   section). The "no new marginal safepoints" framing is dropped; the design's value is
   latency distribution, not total-STW reduction.
2. Choose per-pass budget defaults (edge count vs. time slice), hop cap, the
   passes-per-search/wall-clock TTL abandonment cutoff, and the frontier-size/memory cap
   (see Termination and "Frontier metadata storage") — needs measurement against
   representative heap shapes and per-hop fan-out, not a guess; `LivenessTracker`'s
   flat-sample-rate sizing formula does not transfer to a graph-search frontier.
   **Not resolved — provisional defaults only, no measurement has occurred.** The
   implementation currently ships explicitly-labeled "provisional default pending Phase 5
   empirical tuning" constants (`arguments.h`: `DEFAULT_REFERENCE_CHAINS_HOP_CAP = 200`,
   citing this doc's own JFR ~200-hop/100-100 precedent; `DEFAULT_REFERENCE_CHAINS_BUDGET
   = 1000`; `DEFAULT_REFERENCE_CHAINS_TTL_MS = 60000`; `DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP
   = 65536`, sized as a fraction of `LivenessTracker::MAX_TRACKING_TABLE_SIZE` rather than
   derived from any BFS-specific measurement; plus `referenceChains.h`'s
   `FrontierTable::INITIAL_TABLE_CAPACITY = 1024` and
   `ReferenceChainTracker::PASS_CADENCE_NS` = 1 s). These let the subsystem run and be
   tested end-to-end, but none are backed by a benchmark against this codebase — do not
   describe them as measured. The real resolution path is
   [LiveHeapReferenceChains-BenchmarkPlan.md](LiveHeapReferenceChains-BenchmarkPlan.md),
   which specifies the JMH/async-profiler matrix and decision rule Phase 5 still needs to
   execute; this question stays open until that plan is actually run.

   **Pause-time-SLO feedback loop — SHIPPED, reusing the existing `PidController`.**
   Implemented in
   [LiveHeapReferenceChains-RemainingWorkPlan.md](LiveHeapReferenceChains-RemainingWorkPlan.md)'s
   Phase D (`ReferenceChainTracker::updatePacing()`, `referenceChains.cpp`). This does not
   replace the hop/TTL/frontier-cap constants raised in the first half of this question — only
   the per-pass edge-count budget and the pass cadence, per the shipped mechanism below.
   - New config sub-option `referencechains=...:pausetarget=<ms>` (`arguments.cpp`'s
     `CASE("referencechains")` parser, field `Arguments::_reference_chains_pause_target_ms`),
     defaulting to `arguments.h`'s `DEFAULT_REFERENCE_CHAINS_PAUSE_TARGET_MS = 5` — explicitly
     labeled provisional/un-benchmarked, the same way the other
     `DEFAULT_REFERENCE_CHAINS_*` constants are. Choosing its real value is still a Phase-5-style
     empirical question, not resolved by this mechanism landing.
   - `ReferenceChainTracker::start()` (re)constructs its own `PidController` instance
     (`_pause_pid`) targeting `_pause_target_ms`, with its own gain triple —
     **not** `ObjectSampler`/`MallocTracer`/`NativeSocketSampler`'s shared, uncited
     P=31/I=511/D=3/cutoff=15s (the caveat this question raised about that triple being
     copy-pasted, not independently derived, still stands for those three; it was not
     "resolved," just not repeated here). The new instance uses P=10/I=1/D=2/window=1/cutoff=5s
     — smaller proportional gain than the shared triple because a pass-duration-ms error is
     single/low-double-digit in magnitude, unlike the shared triple's event-count scale
     (`referenceChains.cpp`'s `start()`, inline comment on each gain). Gain *convergence* is
     verified by gtest (three `ReferenceChainsTest` cases: steady-state at the ceiling, over-
     ceiling, under-ceiling — see Phase D's exit criteria below), not by a live benchmark
     against representative heap shapes; that remains a
     [LiveHeapReferenceChains-BenchmarkPlan.md](LiveHeapReferenceChains-BenchmarkPlan.md) item,
     not fully closed by this mechanism landing.
   - Measurement point: `runPass()` (`referenceChains.cpp`) times its own root
     `FollowReferences` call (first pass) or `expandFrontier()`'s
     `GetObjectsWithTags`+`FollowReferences` pair (resumed pass) — already the thread blocked
     inside the safepoint those calls trigger (Triggering section) — and converts to whole
     milliseconds before feeding `_pause_pid.compute()` (matching every other `PidController`
     caller in this codebase, which all feed integer counts).
   - `updatePacing(u64 pass_wall_ns)` folds the budget-scaling and cadence-widening/relaxing
     decisions into that one `compute()` call per pass: the signal is added to
     `_effective_budget` (the *value* `runPass()` now passes to `expandFrontier()` instead of
     the fixed `_budget`) and clamped to `[MIN_EFFECTIVE_BUDGET = 50, _budget]` — the config
     value `_budget` becomes the controller's ceiling, not a literal per-pass value anymore.
     Whatever the clamp could not absorb (`overflow`) drives `_effective_cadence_ns` (see Open
     Question 5 below for why cadence is folded into this same output rather than a second
     controller): `CADENCE_NS_PER_EDGE_OVERFLOW = 1ms/edge` scales the unabsorbed overflow into
     a nanosecond adjustment, widening `_effective_cadence_ns` toward
     `MAX_EFFECTIVE_CADENCE_NS = 4s` when still over-ceiling even at the budget floor, relaxing
     it toward `MIN_EFFECTIVE_CADENCE_NS = 10ms` when comfortably under-ceiling even at the
     budget ceiling.
   - The hop cap and the frontier-size hard cap (Termination section) are untouched by this
     mechanism — they stay fixed correctness/memory-safety bounds, not controller-tuned, exactly
     as this question originally specified.
   - One known, deliberate scope limit carried over from the plan: `buildAbandonedEvent()`'s
     `datadog.ReferenceChainAbandoned` event still reports the static config ceiling `_budget`,
     not the adaptive `_effective_budget` — changing that event's semantics was out of Phase D's
     stated scope.
3. Decide the sample-batching policy: one incremental search per live-heap sample, or
   batched multi-target BFS sharing a single frontier walk (batching amortizes better but
   couples unrelated samples' termination conditions together).
   **Shipped, but not in either form this question anticipated.** The implemented
   `ReferenceChainTracker::runPass()` (referenceChains.cpp) does not target any sample at
   all: it runs a single, singleton-owned search that walks the whole root-reachable graph
   (bounded by the hop/budget/frontier caps) with no per-sample seeding. Reconstructing a
   chain for a specific tag is a separate, read-only step (`buildChainEvent(target_tag, ...)`)
   applied after (or during) that one shared search - closer in spirit to "batched" (one
   frontier walk can answer for many targets) than "one search per sample", but arrived at
   by omission (the target-sample feed did not exist at that time, see the implementation
   plan's Phase 7 report) rather than a deliberate batching design.
   Whether this generalizes to true multi-target batching (explicit seeding from multiple
   samples, coordinated termination) is still open and deferred, consistent with this
   question's original framing.

   **Target-selection policy — SHIPPED (positive population-slope ranking).** Implemented in
   [LiveHeapReferenceChains-RemainingWorkPlan.md](LiveHeapReferenceChains-RemainingWorkPlan.md)'s
   Phases A-C. The missing piece above was *which* tag(s) `buildChainEvent()` should
   reconstruct for. As shipped: per klass, `LivenessTracker` tracks a rolling window of its
   live tracked-instance population count, sampled once per `LivenessTracker::cleanup_table()`
   epoch advance (the same GC-epoch cadence that already recomputes survivor status,
   `livenessTracker.cpp` — a *different*, slower cadence than `ReferenceChainTracker`'s own BFS pass cadence, Open
   Question 5; "past N passes" below means GC epochs observed by `LivenessTracker`, not BFS
   passes). A klass whose population trend over that window is positive — new instances
   arriving faster than old ones are dying — is a leak candidate; a bounded cache/pool also
   holds old objects but its population stabilizes or shrinks. Of all klasses with a
   positive trend, seed only the top 3–5 by trend magnitude for the next BFS pass — this
   doubles as the per-pass seeding cap this question's last bullet asks for, so no separate
   budget constant is needed.

   Mechanics (as shipped):
   - `LivenessTracker` resolves the class lazily at JFR-flush time (`flush_table()`) to keep
     the allocation-sampling path free of a `GetObjectClass` call. Per-klass population is
     computed by resolving the klass once per *surviving* entry inside the existing
     `cleanup_table()` epoch-advance pass instead (`resolveKlassId()`, the same
     `GetObjectClass` + `Class.getName()` + `Profiler::lookupClass()` sequence
     `flush_table()` uses) — cost scales with live-table size × GC frequency, not with
     allocation rate, so it does not touch the hot sampling path. This whole step is gated on
     `_gc_generations` (`cleanup_table()`), so a plain liveness session pays none of it.
   - A fixed-capacity table (`KlassPopulationEntry _klass_population[]`,
     `MAX_KLASS_POPULATION_ENTRIES = 256`) keyed by klass `StringDictionary` id holds a
     `KLASS_POPULATION_RING_SIZE = 30`-slot ring of per-epoch population counts plus one
     `jweak` of a currently-live representative instance (minted fresh in
     `foldKlassCountsLocked()`, deliberately *not* aliasing the source `TrackingEntry::ref`,
     which `cleanup_table()` can reap out from under it). When full, the
     least-recently-updated entry is evicted (`recordKlassPopulationSampleLocked()`), the
     same fixed-capacity/LRU shape every other table in this design uses. Counts are
     accumulated into a reused scratch array (`accumulateKlassCount()`) during the survivor
     loop, then folded into the ring at the end of the pass.
   - Trend/slope (`computeKlassPopulationSlope()`): average of the earliest third of the
     filled window vs. average of the most recent third (cheap, allocation-free, avoids full
     least-squares regression). Trend is trusted only once the ring reaches a minimum fill
     (`KLASS_POPULATION_MIN_FILL_FOR_TREND = 10` samples) to avoid noise right after a klass
     starts being tracked. The exact window size (up to 30) and the "top 3–5" cutoff are
     starting points, not measured values — a separate tuning pass, not folded into Open
     Question 2's pause-time work (this is a leak-detection sensitivity tradeoff, not a
     safepoint-cost tradeoff).
   - `LivenessTracker::selectLeakCandidates(KlassCandidate *out, int max)` returns, on
     demand under a shared lock, the positive-slope klasses ranked by magnitude descending,
     capped at `min(max, MAX_LEAK_CANDIDATES = 5)` — this top-N cutoff *is* the per-pass
     seeding cap, so no separate budget constant is needed. Each `KlassCandidate` carries the
     klass id and its representative `jweak`.
   - Known limitation, stated rather than solved: if population trends positive across
     *many* klasses simultaneously, that's more likely heap-wide growth (warm-up, load
     increase) than several independent leaks. The top-3–5 ranking limits how many candidates
     get chased, but does not distinguish this case from true multi-leak; a future refinement.
   - The leak *judgment* is retrospective (needs a full window of GC-epoch history to see the
     trend) but the *reconstruction target* does not need to be the exact instance that built
     up the trend — any currently-live tracked instance of the flagged klass is evidence of
     the same leak. **The bridging step is a READ, not a `SetTag` write** (a correction to
     this doc's original proposal, found while grounding
     [LiveHeapReferenceChains-RemainingWorkPlan.md](LiveHeapReferenceChains-RemainingWorkPlan.md);
     see its "Correction to the design doc's Open Question 3 mechanism"). Pre-`SetTag`ing a
     candidate before the forward walk reached it would make `heapReferenceCallback()`'s
     `*tag_ptr == 0` branch — the *only* branch that records `parent_tag`/`depth` — skip it,
     yielding an empty/root chain. Instead `ReferenceChainTracker::pollWatchedTargets()`
     resolves each candidate's `jweak`, and if `runPass()`'s whole-graph walk has already
     tagged it (`getTag() > 0`, a pure read), calls `buildChainEvent(tag, ...)` and emits the
     chain. A candidate still at tag 0 is retried on a later poll, since the whole-graph walk
     eventually visits every root-reachable object (barring the hop/budget/frontier caps). No
     new backward-walk primitive is needed; this reuses what the frontier table already
     records.
   - This couples two independently-flagged, independently-scheduled subsystems
     (`referencechains=...` vs. `_record_liveness`/`_gc_generations`) that had no existing
     relationship — `LivenessTracker` identifies objects via `jweak` and never calls JVMTI
     `SetTag`/`GetTag`, while `ReferenceChainTracker` identifies objects purely via JVMTI tags
     it assigns during its own traversal. `pollWatchedTargets()` bridging them is the one new
     piece of machinery this adds; everything else reuses existing structures.
   - **Resolved:** `referencechains=...` gets this target-seeding behavior only when liveness
     tracking *and* `_gc_generations` are both enabled (`LivenessTracker::gcGenerationsEnabled()`,
     checked in `pollWatchedTargets()`); otherwise it falls back to the whole-graph-only
     behavior (no target seeding), which is the doc's originally-stated fallback.
4. ~~Decide whether the frontier should use JVMTI object tags at all, or adopt
   `LivenessTracker`'s weak-ref + index-table pattern instead.~~ **Resolved** (see
   "Frontier metadata storage"): tags stay, because `FollowReferences`/
   `IterateThroughHeap` need tagged objects to filter/report frontier membership and a
   weak-ref table has no hook into that machinery — but the per-tag *metadata*
   (`parent_tag`, `referrer_klass`, `depth`) should be stored in a
   `LivenessTracker`-style slot table (tag value as index) rather than a bespoke
   structure, reusing its proven `SpinLock`/CAS-allocation/resize code. Remaining open
   item: the table-sizing formula, folded into Open Question 2.
5. Decide the actual pass-scheduling policy now that GC callbacks can only be a signal,
   not a vehicle: e.g. a background agent thread woken by the GC-callback signal that
   then calls `FollowReferences`/`IterateThroughHeap` for the next pass (paying its own
   transparent safepoint), vs. a fixed-cadence timer independent of GC activity. Needs a
   cost model for how many such safepoints per second are acceptable before this stops
   being "more palatable" than one larger pause.
   **A decision shipped, but not the cost-modeled one this question asks for.**
   `ReferenceChainTracker::shouldRunPass()` (referenceChains.cpp) combines both candidates
   rather than choosing between them: it triggers a pass when the GC-finish epoch has
   advanced since the last pass, *or* a fixed `PASS_CADENCE_NS` (1 second, explicitly
   labeled provisional in `referenceChains.h`) has elapsed, whichever comes first. No
   safepoints-per-second/per-pause-duration measurement backs the 1-second cadence value -
   it was chosen only so an idle search still makes progress without polling tightly. The
   cost model this question actually asks for is still open, deferred to Phase 5's
   benchmark plan ([LiveHeapReferenceChains-BenchmarkPlan.md](LiveHeapReferenceChains-BenchmarkPlan.md)),
   which has not been run.

   **SHIPPED — folded into Open Question 2's pause-time-SLO feedback loop, not solved
   separately.** Implemented in the same `ReferenceChainTracker::updatePacing()`
   (`referenceChains.cpp`, Phase D) described under Open Question 2: one `PidController`
   `compute()` call per pass drives both that question's budget adjustment and this question's
   cadence adjustment from the single measured per-pass safepoint duration, rather than two
   independently-tuned mechanisms. `shouldRunPass()` and `threadLoop()` now compare against
   `_effective_cadence_ns` in place of the fixed `PASS_CADENCE_NS` constant (which survives
   only as `_effective_cadence_ns`'s starting value in `start()` and as the unit
   `MAX_EFFECTIVE_CADENCE_NS` scales from); `threadLoop()`'s own sleep between iterations uses
   `_effective_cadence_ns` too; so a controller-driven relaxed cadence actually shortens how
   long an idle, no-GC-event search waits between passes, not just what the comparison in
   `shouldRunPass()` reads. The GC-finish-epoch trigger in `shouldRunPass()` remains unconditional
   on cadence, exactly as before — cadence only governs the fixed-interval fallback for an idle
   search, per this question's original framing. See Open Question 2 above for the concrete
   clamp/overflow mechanics (`MIN_EFFECTIVE_CADENCE_NS = 10ms`, `MAX_EFFECTIVE_CADENCE_NS = 4s`,
   `CADENCE_NS_PER_EDGE_OVERFLOW`) and the gain-tuning caveat, which applies identically here
   since it is the same controller instance. The cost-modeled "how many safepoints/sec is
   acceptable" question this Open Question originally asked for is answered structurally (the
   controller widens cadence exactly when passes are running long relative to the configured
   ceiling) rather than by a specific measured number — that number is still a
   [LiveHeapReferenceChains-BenchmarkPlan.md](LiveHeapReferenceChains-BenchmarkPlan.md) item.
