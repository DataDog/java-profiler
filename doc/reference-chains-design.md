# Reference Chains for Surviving Live Heap Samples

**Status:** Implemented (see `doc/reference-chains-collection-summary.md` for the as-built design)
**Date:** 2026-07-07
**Jira:** TBD

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

\* This 3/5 reflects only the single-pass BFS sketched at selection time. The "Chosen
design" section below replaces that sketch with an incremental, resumable BFS
(JVMTI-tag-based frontier persistence across GC cycles, a dedicated `VM_Operation` per
pass, GC-callback signaling, and explicit termination/tag-cleanup bookkeeping), which is
materially more complex than this score suggests — closer to 4/5 in implementation and
maintenance effort. The score is left unchanged above (it documents the state of the
comparison at decision time) rather than retroactively edited.

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
degenerates to `(referrer_klass, parent_ref, depth)` records, where `parent_ref` links
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
- Tags are **non-retaining** — tagging does not keep an object alive. This is the same
  property the existing live-object sampler in this codebase already relies on, so this
  is a new *use* of an existing mechanism, not new risk surface.
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

### Triggering passes: resolved — cannot avoid dedicated safepoints

Investigated whether pass-continuation work could ride the JVMTI
`GarbageCollectionStart`/`GarbageCollectionFinish` callbacks — the same callback this
codebase already uses to call `_heap_usage_func` (`vmStructs.cpp`) — instead of
scheduling a dedicated `VM_Operation` per pass.

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

**But this does not make the callback usable as the execution vehicle for a pass.** The
"functions which specifically allow such use" are exactly two: `Allocate` and
`Deallocate` (the entire **Memory Management** category). `SetTag`, `GetTag`,
`GetObjectsWithTags`, `FollowReferences`, and `IterateThroughHeap` are all in the
**Heap** category, which is *not* on that allowlist — calling any of them from inside
`GarbageCollectionStart`/`Finish` is exactly what the restriction forbids. The spec's own
prescribed escape hatch — notify a raw monitor from the callback, do the real work on a
separate agent thread — doesn't preserve the "rides the pause" property either: by the
time the woken agent thread runs, `VM_Operation::doit()` has already returned and the
safepoint has been released, so the tagging/walk work ends up running concurrently with
resumed mutators, not during the STW window.

The only way to do the tag/walk work *while actually inside* the callback's STW window
would be to bypass the official JVMTI entry points and reach into HotSpot's internal
`JvmtiTagMap` directly via symbol-sniffing — reintroducing exactly the fragility class
already rejected for Approach C (unversioned internal C++ state, no stable ABI). Doing
that here would undo the reason C was rejected.

**Conclusion: "no new marginal safepoints" is not achievable while staying within
official JVMTI usage.** Each pass needs its own dedicated, budget-capped `VM_Operation`.
The GC callbacks remain useful only as a low-cost *signal* ("a GC just happened, a pass
may be worth scheduling soon") — not as the execution vehicle for the pass itself. This
does not change the core incremental design (frontier persistence via JVMTI tags,
self-pruning of dead branches, per-pass budget) — it only removes the "zero marginal
safepoints" claim from the cost/benefit case. The design's actual value remains what it
was framed as: trading one long pause for several short, independently-scheduled ones —
a latency-distribution improvement, not a total-STW reduction.

### Termination and abandonment

Because passes are spread across a mutating heap, a search that never reaches a root or
the hop cap could otherwise persist indefinitely, accumulating abandoned frontier state
across GC cycles. Required cutoffs:

- Hop cap (as in Approach B's single-pass form).
- A hard cap on passes-per-search or wall-clock TTL from first observation.
- Explicit reporting of abandoned searches (no silent truncation) so this shows up as a
  measurable "chain not found within budget" outcome rather than being indistinguishable
  from "no chain exists."

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
   allowed function set, so each pass still needs its own dedicated `VM_Operation`. The
   "no new marginal safepoints" framing is dropped; the design's value is latency
   distribution, not total-STW reduction.
2. Choose per-pass budget defaults (edge count vs. time slice) and hop cap — needs
   measurement against representative heap shapes, not a guess.
3. Decide the sample-batching policy: one incremental search per live-heap sample, or
   batched multi-target BFS sharing a single frontier walk (batching amortizes better but
   couples unrelated samples' termination conditions together).
4. Decide behavior when JVMTI tagging is already saturated by the existing live-object
   sampler (tag-table sizing/contention) — this reuses infrastructure that has other
   consumers in this codebase.
5. Decide the actual pass-scheduling policy now that GC callbacks can only be a signal,
   not a vehicle: e.g. a background thread woken by the GC-callback signal that then
   requests its own bounded `VM_Operation`, vs. a fixed-cadence timer independent of GC
   activity. Needs a cost model for how many dedicated small safepoints per second are
   acceptable before this stops being "more palatable" than one larger pause.
