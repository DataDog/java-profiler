---
id: find-static-field-sweep-never-completes
type: finding
status: confirmed
depends_on: [ev-postCB-onpod-live-verification, find-canary-stuck-restart-wipes-frontier]
supersedes: []
related: [q-canary-stuck-fix-alternatives, find-static-field-sweep-cursor-fix]
tags: [root-cause, referenceChains, static-field, admitStaticFieldRoots, truncation, fixed, NEW-THIS-SESSION]
created: 2026-08-25
updated: 2026-08-25
---

# New candidate root cause: admitStaticFieldRoots() never completes a single sweep, has no resume cursor, restarts from class 0 every attempt

## Reasoning chain

With C+B confirmed live (frontier growing unbroken past 80k entries, zero
`CANARY_STUCK` abandons - `ev-postCB-onpod-live-verification`), candidates
still resolve 0/5 across ~430s of combined observation. User confirmed the
live target is "static field growing, just a few hops" - i.e. an object
that should be trivially reachable, which made the continued 0/5 result
suspicious rather than "just needs more time."

Per the code's own design comment (`referenceChains.cpp:2287-2292`):
> Static-field roots (SomeClass.staticField -> obj) are not reachable via
> IterateOverReachableObjects' root/stack-ref callbacks above ... so this
> pass would otherwise never discover an object retained only that way.

This means an object reachable *only* through a static field is invisible
to the ordinary root-enumeration/`expandFrontier()`/rotation machinery
entirely - the general frontier growing to 80k entries is irrelevant to
finding it. The *only* discovery path is `admitStaticFieldRoots()`
(`referenceChains.cpp:2702-2822`), gated to run only when
`_last_resolved_class_count != _last_static_field_class_count`
(`:2305`), i.e. only re-attempted when the loaded-class count has changed
since the last time the sweep *completed*.

Live trace shows this gate never closing:

```
static_field_phase edges_admitted=0-1 truncated=1 frontier_cap_hit=0 \
  last_resolved_class_count=33868 last_static_field_class_count=-1
```

on all 275/275 `runPass` samples across the 5-minute trace
(`ev-postCB-onpod-live-verification`'s trace 5). `truncated=1` every time
means the sweep never finishes; `last_static_field_class_count` staying at
its initial `-1` sentinel forever confirms it has *never once* completed
successfully (the "sweep completed" branch at `:2337-2344` that would set
`_last_static_field_class_count = _last_resolved_class_count` has never
executed). `edges_admitted` staying at 0-1 per attempt (out of ~34k loaded
classes worth of static fields to sweep) shows each attempt dies almost
immediately.

Code-read of `admitStaticFieldRoots()` confirms there is no resume/cursor
state: it calls `GetLoadedClasses()` fresh every invocation, builds a
holder array of ALL loaded classes, and does exactly one
`jvmti->FollowReferences(0, nullptr, holder, &callbacks, &ctx)` call over
the whole set at once (`:2812`). If that single call is truncated
(deadline or budget exhaustion inside `heapReferenceCallback`, same
mechanism as the general pass - see `:1490-1499`), the entire sweep is
discarded with `_last_static_field_class_count` left unset (`:2341-2342`,
"Left unset on a truncated sweep ... so the next pass retries instead of
wrongly treating a still-incomplete sweep as done"). The *next* attempt
starts the whole `FollowReferences` walk over from class index 0 again -
with JVMTI's class enumeration order presumably stable across calls, this
means whichever classes come after wherever the deadline/budget hits
first are structurally unreachable by this mechanism, no matter how many
times or how long it retries.

## What this would explain

- Why a "just a few hops" static-field-rooted candidate is never found
  even after the CANARY_STUCK/frontier-wipe bug (C+B) is fixed and the
  general frontier grows unboundedly - the general frontier's growth has
  no bearing on this specific candidate shape at all.
- Why fixing C+B alone did not change the 0/5 outcome, despite directly
  addressing the previously-confirmed restart-wipe mechanism.

## WHY it truncates so early - CONFIRMED

The per-pass wall-clock deadline (`_pass_deadline_ns`,
`referenceChains.cpp:2210-2212`) is derived from
`_effective_pause_target_ms`, which without urgency ramping equals
`_pause_target_ms` - itself auto-tuned at startup
(`referenceChains.cpp:367-375`):

```cpp
// --- Pause target ---
// More available processors = the JVM can afford a slightly
// longer per-pass safepoint without impacting application
// throughput. Scale linearly: 1 core = 5ms, 4 cores = 10ms,
// 8 cores = 15ms, capped at 50ms.
long scaled_pause = DEFAULT_REFERENCE_CHAINS_PAUSE_TARGET_MS * (1 + (nprocs - 1) / 3);
args._reference_chains_pause_target_ms = std::min(scaled_pause, (long)50);
```

`DEFAULT_REFERENCE_CHAINS_PAUSE_TARGET_MS = 5` (`arguments.h:94`). Even at
the maximum core-scaled ceiling this is **50ms**, and this single deadline
is shared across the static-field sweep + ordinary `expandFrontier()` +
rotation for the *entire* pass (`:2205-2209`, "Shared wall-clock ceiling
for this whole call's static-field sweep, expandFrontier(), and rotation
sub-calls below").

`admitStaticFieldRoots()` is architecturally incompatible with this
budget: it is a single, non-resumable `jvmti->FollowReferences()` call
over a holder array of **all ~34,000 loaded classes at once**
(`:2775-2812`). The only escape hatch is the deadline check inside
`heapReferenceCallback()`, which samples wall-clock only every 4096
callback invocations (`:1490-1491`,
`(++ctx->deadline_check_counter & 0xFFF) == 0`) - so the abort fires
somewhere inside whatever the first slice of ~4096-ish callback
invocations covers, which is evidently a small fraction of 34k classes.

This matches the observed data precisely: `edges_admitted=0-1` on every
attempt, while the pass's *edge-count* budget was 3741
(`effectiveBudget=3741` in the same trace's `runPass done` lines) - ruling
out the numeric edge budget as the limiter. The wall-clock deadline
(≤50ms, shared with two other sub-phases) is what kills it, and it dies
this early on **every single attempt** because there is no cursor: each
retry restarts `GetLoadedClasses()` + the whole `FollowReferences` walk
from class index 0, hitting the identical wall. Unless the leaking
static field's owning class happens to be among the very first classes in
JVMTI's enumeration order, it is structurally unreachable by this
mechanism - independent of C+B, independent of how many passes run, ever.

This is an architecture mismatch, not a tuning knob: a per-pass STW-safety
budget designed for *incremental*, resumable graph expansion was reused
for a full-classlist sweep that has no incremental/resumable structure at
all.

## STW confirmation (required before choosing a fix)

User required proof the sweep is genuinely stop-the-world before accepting
a chunked/resumable rewrite as safe. Confirmed via code-read (Explore
agent): `FollowReferences()` triggers HotSpot's internal
`VMThread::execute()` on a `HeapWalkOperation` - a real JVM-internal
safepoint, not something the profiler schedules or controls
(`referenceChains.cpp:2300`, `referenceChains.h:627,1378-1381`, "the
safepoint is a side effect of that call, not something the profiler builds
or schedules"). Confirmed further by an existing
`assert(!t_inGCCallback ...)` at the top of `admitStaticFieldRoots()`
(JVMTI Heap-category calls must not run from GC callbacks, which
themselves already run at a safepoint).

This made chunking safe by precedent: `expandFrontier()` already does
incremental, resumable batching across separate `FollowReferences` calls,
re-resolving JVMTI tags to current live objects via `GetObjectsWithTags`
(non-safepoint) immediately before each bounded call - safe against
GC/object-moving between calls because JVMTI tags persist across GC.
Chunking `admitStaticFieldRoots()`'s class list the same way is
correctness-safe, not a novel risk.

## Fix implemented and gtest-verified — see `find-static-field-sweep-cursor-fix`

Combined per user's explicit request: (1) a persistent resume cursor so
the sweep processes a bounded chunk of classes
(`STATIC_FIELD_SWEEP_CHUNK_CLASSES = 512`) per call instead of all ~34k at
once, advancing every call so one pathologically expensive class can never
block progress forever, with "done" now gated on a full untruncated lap
rather than a single non-truncated call; (2) an app-classes-first
in-place partition of the per-call `GetLoadedClasses()` result (via
`GetClassLoader() != nullptr`) so application/library code is swept
before the much larger JDK bootstrap classlist tail - directly targeting
the pod's confirmed "static field growing, just a few hops" (application-
code) leak shape. Full detail, code locations, and the test-isolation
regression found + fixed during verification are in
`find-static-field-sweep-cursor-fix`. `./gradlew
:ddprof-lib:gtestDebug` passes clean (188 tasks, full suite, not just
`referenceChains_ut`). **Committed (`a86f0dd87`), deployed, and confirmed
live on-pod** — see `find-static-field-sweep-cursor-fix`'s Verification
section and `ev-postfix-static-field-onpod-live-verification`. End-to-end
candidate resolution is still 0/5; two new distinct open questions
(`find-candidate1-never-tagged`, `find-candidates-234-die-before-resolution`)
surfaced downstream of this fix.
