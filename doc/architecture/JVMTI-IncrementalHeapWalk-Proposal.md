# Proposal: decompose JVMTI's heap-walk API into resumable primitives

## Status

Sketch / discussion draft. Not submitted anywhere. Written to capture the
idea while it's fresh, in case it's worth taking to JVM vendors (Temurin,
Oracle) or the OpenJDK `serviceability-dev` list. This is deliberately
separate from `LiveHeapReferenceChains-VMStructsWalkDesign.md`, which covers
the internal (VMStructs-based, implementation-specific, G1-only) workaround
we'd actually ship if this proposal goes nowhere.

## Motivation

Building a live, low-pause reference-chain tracker on top of JVMTI's heap
walk API (`FollowReferences`, `IterateOverReachableObjects`) surfaced a
structural limitation: the API bundles three operations with very different
costs into one call, and doesn't let a caller drive them independently.

1. **Root enumeration** — walking all threads' stacks plus JNI/global
   handles to find GC roots. Unavoidably O(#threads × stack depth), but a
   *shared* cost that only needs paying once per logical pass.
2. **Escape-barrier deopt scan** (`EscapeBarrier::deoptimize_objects_all_threads()`)
   — materializes scalar-replaced objects so they're visible to the walk.
   Also O(#threads × stack depth), and unconditional on every heap-walk API
   call regardless of whether the caller asked for `object_ref_callback` at
   all.
3. **Graph expansion** — walking from tagged objects to their referents.
   This is the actual traversal, and today it's only reachable as an opaque
   internal loop over a HotSpot-owned `GrowableArray<oop>` stack, in
   HotSpot's own order (confirmed via source: LIFO, DFS, root-interleaving
   determined by arbitrary push order — not root-by-root, not breadth-first).

Because all three are fused into one call, a caller that wants to expand the
graph gradually — bounding each safepoint's pause time to a fixed budget,
resuming later, prioritizing fairly across roots — has no way to do it.
Budget/time cutoffs land wherever HotSpot's internal stack happens to be,
which can permanently strand entire root subgraphs (since there's no way to
resume "the rest of the roots" — the API has no concept of a paused walk,
only "start" and "finished/truncated").

This is very unlikely to be unique to this use case — any tool doing
incremental or paced heap analysis (debugger backends, IDE memory views,
other profilers/APM agents) plausibly hits the same wall.

## Proposed extension functions

Two new JVMTI Extension Functions (using the existing
`GetExtensionFunctions`/extension-registration mechanism JVMTI already has —
this doesn't need a new discovery mechanism, just two new registered
functions):

```c
// Enumerate roots only - equivalent to today's
// IterateOverReachableObjects(object_ref_callback=NULL), but with an
// explicit opt-out of the escape-barrier scan for callers that don't need
// scalar-replaced/escape-analyzed objects to be visible (the common case
// for long-lived object tracking, as opposed to short-lived temporaries).
jvmtiError JvmtiExt_GetRoots(
    jvmtiEnv* env,
    jvmtiHeapRootCallback root_cb,
    jvmtiStackReferenceCallback stack_cb,
    jint flags,                    // e.g. JVMTI_EXT_SKIP_ESCAPE_BARRIER
    void* user_data);

// Expand exactly the given already-tagged objects by one hop each, via
// HotSpot's normal barrier-mediated field/element reads. No root rescan,
// no escape-barrier scan - cost scales with object_count, not with heap
// size or thread count.
jvmtiError JvmtiExt_ExpandObjects(
    jvmtiEnv* env,
    jint object_count,
    const jlong* tags,             // caller's own tag space
    jvmtiHeapReferenceCallback edge_cb,
    void* user_data);
```

### How a caller would use this

Own the traversal loop entirely at the agent level:

- Call `GetRoots` occasionally to (re)seed a frontier of tagged root
  objects — this is the one place the O(#threads × stack depth) cost is
  paid, same as today, but now decoupled from every subsequent expansion
  step.
- Call `ExpandObjects` repeatedly in batches sized to whatever pause-time
  budget the caller is willing to spend *this* safepoint — with the
  caller's own fairness policy (round-robin across roots, prioritize by
  age, whatever), not HotSpot's internal LIFO-stack order.
- Persist exactly which tagged objects haven't been expanded yet between
  calls; resume from there next time, instead of the current
  all-or-nothing "the walk either finished or it didn't" model.

Each call is presumably still safepoint-bound (a moving-GC-safe read needs
that), but the pause length is now a function of what the caller asked for,
not of global VM/heap state — which is the actual fix. Correctness stays
entirely inside HotSpot's own barrier-aware dereferencing code; the caller
never touches raw memory or needs to know anything about the active
collector's pointer representation.

## Why this is a minimal ask, not an API redesign

- **Decomposition, not new capability.** Everything above is already
  implemented inside `FollowReferences` today; this asks for the internal
  expansion step to be independently callable, and for the escape-barrier
  scan to be opt-out for callers that don't need it. No new safety model,
  no new consistency guarantee beyond what the existing per-edge callback
  inside `FollowReferences` already provides.
- **Fits the existing extension mechanism.** JVMTI's Extension Functions
  are built for exactly this kind of vendor-prototype-first path — a vendor
  could ship these two functions without any JEP/spec process, gather real
  usage, and only pursue standardization once it's proven out.
- **No new safepoint semantics.** Same safepoint, same barrier semantics as
  today's per-edge callback. We're asking for the existing safety model to
  be callable in smaller, resumable pieces, not for a new one.

## Open questions before this could be pitched externally

- Does `ExpandObjects`' per-object edge callback need the same tagging
  guarantees `FollowReferences` provides today (e.g. can newly-discovered
  referents be tagged inline, same as now), or does splitting expansion
  from root-seeding change any tagging invariants callers currently rely
  on?
- Is `JVMTI_EXT_SKIP_ESCAPE_BARRIER` an acceptable opt-out from a JVM
  vendor's perspective, or does skipping it change observable semantics in
  a way that needs a stronger caller contract (e.g. "you may miss
  scalar-replaced objects that would otherwise be visible")?
- Batch size limits / pause-time interaction: does `ExpandObjects` need an
  internal cap independent of `object_count`, to prevent a caller from
  accidentally requesting a batch large enough to blow a pause-time budget
  anyway (e.g. objects with very large reference fan-out)?
- Worth prototyping against a real OpenJDK build before approaching anyone
  externally, to have working code rather than just a signature sketch.
