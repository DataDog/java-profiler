# Reference chains: a VMStructs-based traversal alternative

## Problem this addresses

`ReferenceChainTracker`'s current walk is built entirely on JVMTI's heap-walk
API (`FollowReferences` for the root-seeded first pass, `expandFrontier()` for
later passes). JVMTI gives us safety and portability, but imposes costs and
constraints we don't control:

- Every `FollowReferences` call runs as one uninterruptible `VM_Operation` at
  a single safepoint, budget/time-bounded only from the *outside* (our own
  edge counter), not paced internally.
- The traversal order inside that call is HotSpot-internal and unspecified —
  confirmed (via OpenJDK source research) to be a single shared LIFO stack
  (`GrowableArray<oop>* _visit_stack`), i.e. DFS with root-interleaving
  determined by arbitrary push order, not BFS and not root-by-root. If our
  budget/time cutoff fires mid-stack, whichever roots' subgraphs weren't
  reached yet are **permanently** unreached — `expandFrontier()` only ever
  expands children of objects already admitted to the frontier table; it
  never re-enters `FollowReferences` from roots again.
- Every JVMTI heap-walk call variant (`follow_references`,
  `iterate_over_reachable_objects`, `iterate_over_heap`) unconditionally
  invokes `EscapeBarrier::deoptimize_objects_all_threads()` once per call
  (jvmtiTagMap.cpp ~3001-3020), which walks every live thread's stack frames
  (O(#threads × stack depth)) looking for scalar-replaced/escape-analyzed
  objects to materialize. It's gated (no-op unless escape analysis is active)
  and per-frame-cached, but the outer thread/stack scan re-runs every call
  regardless of caching.

Two alternatives were explored and rejected on cost grounds (see prior
discussion, not yet written up separately):

- **Reseeding** — repeated root-seeded `FollowReferences` calls using
  `JVMTI_HEAP_FILTER_TAGGED` to skip already-admitted objects. Rejected:
  penalized by O(rounds × explored-size) graph-visit cost at a safepoint,
  once per round.
- **Per-root calls** — one `FollowReferences(0, nullptr, <single root>, ...)`
  call per root, round-robining budget for fairness. Rejected: multiplies the
  `EscapeBarrier` O(#threads × stack-depth) cost by root count (potentially
  thousands) every pass.

JFR's own internal leak-profiler (`PathToGcRootsOperation`,
`jdk.OldObjectSample`) was also investigated as a possible source of a more
latency-aware traversal to piggyback on. Verdict: the internal classes
(`PathToGcRootsOperation`, `EdgeStore`, `BFSClosure`/`DFSClosure`) are
unexported C++, not `dlsym`-reachable, and architecturally the same hazard
class we're trying to escape — the whole traversal + event emission runs
inside one `doit()` at a single safepoint, just bounded to a 256-object
sample queue instead of the whole heap. The public `jdk.OldObjectSample`
event is a legitimate lightweight *complementary* signal (sampling-based,
fully supported, no private-header risk) but not a substitute for exhaustive
chain tracing, and it still safepoints during path resolution.

## Proposed direction: JVMTI for roots + safepoint, VMStructs for the walk

The codebase already has a mechanism for reading HotSpot's internal struct
field offsets at runtime without linking against private headers:
`hotspot/vmStructs.h`/`.cpp`/`.inline.h`, driven by HotSpot's own exported SA
(Serviceability Agent) struct table (`gHotSpotVMStructs`). It's already used
for `Klass`-level introspection (`VMKlass`, mapping `_class_loader_data`,
`_methods`, etc. — see `livenessTracker.cpp` and others). The idea: extend
this to walk the object graph ourselves, instead of handing traversal control
to JVMTI's `FollowReferences`.

### Why we don't need — and can't build — our own `VM_Operation`

The first version of this idea assumed we'd force our own safepoint via a
custom `VM_Operation`, submitted through `VMThread::execute()`, so GC
couldn't relocate objects mid-walk. That doesn't work: VMStructs exposes
*data* (field offsets into already-existing HotSpot objects); it gives no way
to construct a new object that HotSpot's safepoint machinery will correctly
dispatch. `VM_Operation::doit()` is virtual — subclassing it from outside
requires matching HotSpot's exact vtable/base-class ABI, which isn't part of
the VMStructs export contract (or any stable interface) at all. Confirmed via
`grep`: this codebase has zero existing `VM_Operation`/`VMThread::execute`
usage — there's no existing pattern to build on here, and no safe way to
start one.

### The actual design: piggyback on a JVMTI-opened safepoint

We don't need to build a safepoint op; JVMTI already gives us one for free,
and prior research already established the cheap entry point:
`IterateOverReachableObjects` with `object_ref_callback = nullptr` gates off
HotSpot's entire graph-expansion loop and is genuinely O(roots), not
O(graph) — confirmed via OpenJDK source (`jvmtiTagMap.cpp`,
`_following_object_refs` check). What still runs is `collect_stack_roots()`
and `collect_simple_roots()`, both callback-driven root enumeration, executed
*while already at the safepoint* that call opened.

Design:

1. Call `IterateOverReachableObjects` once per pass (same cadence as today).
   This is the one place we still pay for a safepoint plus the once-per-call
   `EscapeBarrier` cost — same profile as the current design, not worse.
2. Supply only `heap_root_callback`/`stack_ref_callback` (no
   `object_ref_callback`) to enumerate roots cheaply, with root-kind info
   (`root_kind`, and for stack refs: thread/depth/method/slot) directly from
   JVMTI rather than inferred indirectly from child-edge `reference_kind` as
   today.
3. From inside those root callbacks — still inside the safepoint window —
   walk N hops ourselves using VMStructs-derived offsets: object header →
   `Klass*` → oop-typed instance fields → recurse, budget-bounded by our own
   counter. This is where we get real control we don't have today: our own
   pacing, our own fairness across roots (e.g. round-robin instead of
   HotSpot's arbitrary LIFO-stack order), our own resumability semantics
   (persist exactly where each root's walk stopped, not just a shared
   frontier table).
4. Because steps 2–3 happen inside the single safepoint opened in step 1, GC
   cannot relocate or free anything mid-walk — this is what answers "how do
   we keep objects from moving while we read them" without inventing a
   `VM_Operation`.

### New scope required (not already covered by existing VMStructs entries)

Confirmed via `grep` over `vmStructs.h`: none of the following exist yet.
This is real, unstarted work, not a trivial extension:

- **Oop-map metadata** — which fields of an instance are oop-typed and at
  what offset. Needs `InstanceKlass::_nonstatic_oop_map_size` and an
  `OopMapBlock` type (`_offset`, `_count`). These are part of HotSpot's
  standard SA export set (the same table SA's own heap-dumping tooling
  uses), so this is "declare more entries" in the existing
  `MATCH_SYMBOLS`/`type_begin` pattern, not new introspection machinery.
- **Array handling** — walking `objArrayOop` elements, distinguishing oop
  arrays from primitive arrays via `layout_helper`. Net new.
- **Compressed-oops decoding** — `narrowOop` → real pointer via heap
  base/shift (`CompressedOops::_narrow_oop._base`/`_shift`, or via
  `Universe`). Confirmed absent from the codebase entirely (`grep` for
  `CompressedOops`/`narrowOop`/`decode_heap_oop` in `*.cpp`/`hotspot/*.h`
  returned nothing). Most JVMs run with compressed oops on by default, so
  this is a hard requirement, not optional.

### Trade-offs

- **Upside**: real fairness/pacing control we don't have today, without the
  cost multiplication that sank reseeding and per-root designs — the
  safepoint and `EscapeBarrier` cost stay paid once per pass, same as now.
  Root-cause of the original truncation problem (DFS order permanently
  missing late-enumerated roots' subgraphs) goes away, since we control
  which roots get walked and how far, not HotSpot's internal stack order.
- **Downside**: implementation-specific by construction (field offsets,
  oop-map layout, compressed-oops encoding are all HotSpot-internal and can
  shift across JDK versions/GCs) — consistent with, not beyond, the level of
  impl-specificity this codebase already accepts elsewhere via VMStructs.
  Real new engineering surface: oop-map/array/compressed-oops plumbing plus a
  hand-rolled field-walker, none of which exists today.
- **Not yet assessed**: G1/Shenandoah/ZGC region-specific concerns beyond
  "GC can't run because we're at a safepoint" (e.g. concurrent
  mark-bit/remembered-set bookkeeping some collectors expect around live
  oops even at a safepoint) — needs a dedicated pass before implementation
  starts, not before this design is accepted as the direction.

## Status

Design only — not yet implemented, not yet reviewed against GC-specific
correctness concerns beyond safepoint object-movement. The memory/RSS
overhead investigation for the existing JVMTI-based tracker remains shelved
separately and is unrelated to this document.
