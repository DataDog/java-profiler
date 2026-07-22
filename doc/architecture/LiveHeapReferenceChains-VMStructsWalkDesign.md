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

## Review findings (adversarial pass against OpenJDK source)

An adversarial review against actual `jvmtiTagMap.cpp` source (not just the
prior research summaries above) confirmed two claims and broke two others in
ways that block the design as written:

- **Holds up**: root callbacks (`heap_root_callback`/`stack_ref_callback`) do
  run for the operation's entire duration inside one safepoint —
  `VM_HeapWalkOperation` is a real `VM_Operation` dispatched through
  `VMThread::execute()`, and standard safepoint semantics park all
  `JavaThread`s for its whole `doit()`. Also holds up: `EscapeBarrier`'s
  per-call deopt cost is unconditional — it doesn't check whether
  `object_ref_callback` is null, so §"piggyback" design's cost claim ("same
  profile as today, not worse") is correct.

- **Broken: the safepoint-object-movement argument (step 4) does not, by
  itself, make raw VMStructs-offset oop reads safe on Shenandoah/ZGC.** Being
  at a safepoint stops *new* relocation from starting, but doesn't mean
  in-flight forwarding/color-bit state from a concurrent phase is already
  resolved. Shenandoah leaves forwarding words on from-space copies that are
  normally resolved transparently through `HeapAccess` load barriers — a raw
  offset read skips that and can walk a stale, or already-recycled,
  from-space object as live data. ZGC's colored pointers are worse: a raw
  pointer at an offset isn't even guaranteed to be a dereferenceable address
  without barrier-mediated color stripping, independent of safepoint state.
  This was filed above as a deferrable "not yet assessed" item (see the old
  trade-offs section) — that framing was wrong. It's not a peripheral
  add-on to check later; it's a correctness precondition for every hop of
  the walk under non-G1 collectors, and fixing it means reimplementing a
  meaningful slice of `HeapAccess`/barrier logic via VMStructs — scope well
  beyond the oop-map/array/compressed-oops list above, which doesn't mention
  forwarding or color-bit resolution at all.

- **Broken: cross-pass resumability doesn't hold for the root kind most
  implicated in the original problem.** Stable-identity roots (JNI handles,
  CLDs) can meaningfully persist "where the walk stopped" across passes.
  Stack-local roots (thread/depth/method/slot) cannot — mutators run freely
  between safepoints, so a persisted (thread, depth, slot) tuple from pass N
  can point at a completely different local variable, or nothing, by pass
  N+1. That undercuts the "root-cause of truncation goes away" claim
  specifically for stack roots.

- **Understated, not broken**: doing the N-hop walk from inside a root
  callback needs constraints the design doesn't state explicitly —
  bookkeeping allocation must stay off the Java heap (ResourceArea/C-heap
  only, matching what `collect_stack_refs`/`report_string_value` already do
  in that same callback context) to avoid reentering GC/safepoint machinery,
  and the walk must not recurse on the native call stack to arbitrary depth
  (today's design uses a heap-allocated `GrowableArray`, not C++ recursion,
  for exactly this reason) or reacquire `Heap_lock` (already held for the
  whole operation).

- **Minor accounting correction**: "genuinely O(roots)" (for the
  graph-expansion skip) is accurate but easy to misread as cheap. Two
  mandatory O(#threads × stack-depth) scans still run every pass regardless
  of root count or callback nullness — the `EscapeBarrier` deopt scan and
  `collect_stack_roots()`'s own per-thread vframe walk.

## Proposed fixes for the broken parts

### Fix for barrier/forwarding safety: gate the whole design on G1, don't
### solve Shenandoah/ZGC in v1

G1 never relocates live objects except during STW evacuation pauses, and
those pauses are themselves `VM_Operation`s — `VMThread` serializes all
`VM_Operation`s, so no evacuation can be in flight while *our* safepoint
operation holds the VM. That means raw VMStructs-offset oop reads are
actually sound on G1 with no barrier logic needed at all — the forwarding/
color-bit problem is specific to collectors whose relocation work is
concurrent with mutation (Shenandoah, ZGC), not to "any GC that can move
objects."

So: detect the active collector (a VMStructs-read global flag, or
`Universe::heap()->kind()`) once per pass, and only take the manual-walk
path when G1 is active. Fall back to today's pure-JVMTI
`FollowReferences`/`expandFrontier()` path otherwise — no regression on
Shenandoah/ZGC, just no improvement there either. This is a real scope cut,
not a workaround: it drops "GC-agnostic" as a goal and ships correctness
for the collector most production JVMs still default to.

**Correction (round-2 adversarial review):** the mechanism cited above is
wrong, though the conclusion survives. "Those pauses are `VM_Operation`s,
and `VMThread` serializes all `VM_Operation`s" is a category error — G1's
concurrent helper threads (concurrent-mark workers, concurrent refinement,
concurrent string deduplication) are plain `JavaThread`s, never
`VM_Operation`s, and are never subject to `VM_Operation` serialization at
all. What actually stops them is the general safepoint protocol
(`SafepointSynchronize::begin()`) plus G1's own hook into it
(`G1CollectedHeap::safepoint_synchronize_begin()` →
`SuspendibleThreadSet::synchronize()`, `g1CollectedHeap.cpp:1663-1681`) — a
separate mechanism from `VM_Operation` queuing. Verified concretely against
concurrent string deduplication (`stringDedupTable.cpp:610`,
`java_lang_String::set_value(...)` — an in-place, non-relocating live-object
field mutation running concurrently with mutators on a plain `JavaThread`):
it's blocked during our safepoint by ordinary safepoint sync, not by any
`VM_Operation`-serialization property. No new hazard was found — G1 still
has no concurrent phase that *moves* live object data outside STW pauses,
and evacuation-failure self-forwarding is fully resolved within the same STW
pause before it ends (`RemoveSelfForwardPtrHRClosure`) — so the "G1-only is
safe" conclusion holds. But the stated *justification* needs fixing before
this reasoning gets reused for a future collector decision: it's the
safepoint protocol stopping concurrent workers, not `VM_Operation` queuing.

#### Addendum: Shenandoah/ZGC forwarding mechanics, verified against source

A follow-up question ("what about ZGC/Shenandoah, could either be solved
rather than excluded?") was checked directly against OpenJDK source
(`markWord.hpp`, `shenandoahForwarding.inline.hpp`, `shenandoahHeap.cpp`,
`zAddress.hpp`/`zGlobals.hpp` at `master` and at the `jdk-20-ga`/`jdk-21-ga`/
`jdk-23-ga` tags). The two collectors are not equally hard, and one is worth
scoping as a real follow-up:

- **Shenandoah is plausibly tractable, more precisely than first described.**
  Forwarding state does live in the mark word (Brooks pointers removed;
  `shenandoahForwarding.inline.hpp`'s `get_forwardee_raw_unchecked()` reads
  `mark()`, checks `is_marked()`, and follows `clear_lock_bits()` for the
  forwardee) — but "forwarded" is a 3-state check, not a single bit: the 2
  lock bits + 1 self-forward bit distinguish "real forwarding pointer"
  (`0b011`) from "self-forwarded" (evacuation failure — object stayed put,
  no second hop, `0b1xx`) from "not forwarded." A reader also needs to
  handle a documented HotSpot-internal edge case: JVMTI/JFR can leave a
  "marked" mark word with a **null** forwardee (their own scratch use of the
  same bits) — a naive reader that checks `is_marked()` and blindly follows
  the pointer without a null check can crash on this specific case.
  Critically, **the race conditions the source comments warn about are
  mutator/GC-worker-concurrent-with-mutator races, which don't exist at a
  safepoint** — no thread, including GC workers, executes during one, so
  the mark word is always a fully-committed value whenever we'd actually be
  reading it. And from-space reuse is confirmed safe: Shenandoah does not
  recycle collection-set regions until `update_heap_refs_work` has walked
  and fixed up all live references (`shenandoahHeap.cpp`, `final_update_refs_*`
  gates `trash_cset_regions()`/`rebuild_free_set()`), so there's no window
  where stale from-space memory gets silently repurposed while unfixed
  references to it still exist. Net: a per-object mark-word check (3-state,
  with the null-forwardee guard) is a bounded, source-grounded addition —
  worth scoping as a real v1.5 follow-up, not just a "further-out" idea.

- **ZGC's exclusion is confirmed, and the reason is now more precise than
  "colored pointers are hard."** Every reference is a `zpointer` (colored,
  unsafe to dereference) until decoded to a `zaddress`  — confirmed via the
  explicit type split in current `zAddress.hpp` — so there is genuinely no
  "clean, skip-the-decode" subset, exactly as suspected. The layout-changed-
  across-versions claim was directionally right but the JDK version was
  wrong: the generational-ZGC bit layout (`RRRRMMmmFFrr0000`, 16 metadata
  bits, young/old-specific marked bits, remembered-set bits) landed in-tree
  at **JDK 21** but only as an opt-in experimental mode
  (`-XX:+ZGenerational`); the older 4-bit layout (`Marked0/1`, `Remapped`,
  `Finalizable`) remained the **default** through JDK 22, and generational
  ZGC only became the default engine at **JDK 23** (JEP 474). A second,
  independent reason a static bitmask can't work even for one fixed layout:
  the "good"/"bad" mask values themselves are runtime-computed and flip on
  every GC phase transition (`ZGlobalsPointers::flip_young_mark_start()`,
  `flip_old_relocate_start()`, etc.), so even a version-correct compile-time
  mask isn't sufficient — the decode step is unavoidable, not just
  version-fragile. This closes the door a bit more firmly than the original
  framing: it's not "harder to implement," it's "the wrong kind of state
  (runtime-computed, phase-dependent) for a static VMStructs-offset
  approach to represent at all."

A further-out, higher-risk alternative worth naming but not pursuing for v1:
the codebase already has a *second* introspection mechanism beyond
VMStructs — `CodeCache::findSymbol`/`findSymbolByPrefix`
(`codeCache.cpp:263-280`) resolves arbitrary libjvm.so ELF symbols by
(mangled) name, already used elsewhere (e.g. the `CodeHeap::findNMethod`
symbol seen in an unrelated crash during this investigation). In principle
this could resolve and call HotSpot's actual barrier-resolution functions
(e.g. `ShenandoahBarrierSet`/`ZBarrier` internals) instead of reimplementing
forwarding/color-bit logic by hand. Rejected for now: calling an arbitrary
internal non-`extern "C"` C++ function via a raw resolved address requires
guessing its exact ABI (argument registers, `this`-pointer convention,
possible inlining meaning the symbol doesn't exist as a distinct entry in
some builds) — a mismatch here doesn't crash predictably, it silently
miscalls. Worth revisiting only if G1-only turns out to be an unacceptable
scope cut in practice.

### Fix for stack-root resumability: it's already solved by the existing
### frontier-table design, if we use it correctly

The reviewer's concern was that persisting a stack-root's *location*
(thread/depth/method/slot) across passes doesn't work, because that
location's contents change as mutators run between safepoints. But looking
at how `FrontierTable` already works (see `referenceChains.cpp`): it's
*tag-indexed*, keyed by object identity, not by root descriptor. We don't
actually need to resume "the stack slot" — we only need to resume "the
object that slot pointed to at the moment we saw it," which is exactly what
the frontier table already persists for every other root kind.

So the fix is: when a `stack_ref_callback` fires, immediately admit its
target object into the frontier table (tagged `root_kind = STACK_LOCAL` for
reporting) exactly as any other newly-discovered object would be, then hand
off to the existing resumable frontier machinery. `expandFrontier()` never
needs to know or care that the object was first reached via a stack slot —
by the time it's in the table, it's just another tagged object. This isn't
new mechanism; it's using the existing one for the case the earlier version
of this design bypassed by trying to persist root descriptors instead of
tags.

**Caveat (round-2 adversarial review): this fixes resumability, but leaves a
separate, pre-existing reporting-correctness gap unaddressed.**
`root_kind` is set once, at first admission (`referenceChains.cpp` — insert
only happens on the `*tag_ptr == 0` first-discovery path, never updated on
later passes). Stack-local roots are transient by construction — the frame
that discovered the object can return long before the object itself stops
being live. Concretely: pass N discovers object X via a stack local in
thread T; the method returns after pass N; X survives, now reachable only
through some entirely different, durable path (a static field, say). Passes
N+1..N+k will keep reporting X as "reachable via stack-local root in thread
T" — attribution that's now simply false. For a tool whose entire value
proposition is "here's the reason this object is alive," that's a
correctness-of-*output* bug, not a cosmetic one, and it's not new: it
already affects `JNI_LOCAL` roots today under the exact same
first-discovery-sticks logic, independent of anything in this design. The
tag-indexed frontier table fully solves "don't crash or misresolve a stale
stack coordinate" (the resumability bug reviewed earlier) — it does not, by
itself, solve "don't misreport why an object is still alive," which is a
different bug that predates this design and should be tracked separately
(e.g. label such entries "first observed via," or periodically re-verify
root-attribution for root-attached frontier entries rather than trusting the
first observation for the object's entire tracked lifetime).

## Status

Design **viable with a scope cut**: gate the manual-walk path on G1 only
(raw offset reads are sound there without reimplementing barrier logic;
Shenandoah/ZGC keep using today's pure-JVMTI path, no regression). Stack-root
resumability is not actually a separate problem to solve — it falls out of
routing stack-root discoveries through the existing tag-indexed frontier
table like any other root, rather than trying to persist root descriptors.
Remaining open item before implementation: making the callback-side walk
non-recursive (heap-allocated stack, matching today's `GrowableArray`
pattern, not native C++ recursion) and free of Java-heap allocation, to
respect the constraints root callbacks already run under
(`Heap_lock` held, no safepoint-reentrant allocation). The memory/RSS
overhead investigation for the existing JVMTI-based tracker remains shelved
separately and is unrelated to this document.
