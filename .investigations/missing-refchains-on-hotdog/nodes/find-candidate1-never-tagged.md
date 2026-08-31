---
id: find-candidate1-never-tagged
type: finding
status: confirmed
depends_on: [ev-postfix-static-field-onpod-live-verification, ev-kind-counts-constant-pool-dominates]
supersedes: []
related: [find-static-field-sweep-cursor-fix]
tags: [referenceChains, candidate, canary, marker-tag, static-field, constant-pool, fix-implemented]
created: 2026-08-25
updated: 2026-08-26
---

# Open: candidate[1] (klass_id=283) never tagged/resolved despite sweep confirmed making real progress

## Observation

`candidate[1]` (klass_id=283, class `[Ljava/lang/Object;`,
`marker_tag=-4611686018427387907`, `slot=3`, `needRefresh=1`) shows
`buildCanaryChainEvent(slot=3) -> 0` (unresolved) on **every single
sample** checked, across two separate windows: a ~40s live tail and a
targeted 5-minute historical grep
(`kubectl logs ... --since=5m ... | grep -B1 -A3 "candidate\[1\]
klass_id=283$"`).

Critically: `candidate[0]` (klass_id=10, `[B`) prints a `tag=` line on
its samples; a matching grep for a `tag=` line following
`candidate[1] klass_id=283` returns **zero results** across the same
5-minute window. This means candidate[1]'s target object has never even
been found/tagged by the search at all — not merely "found but chain not
yet built."

This is despite `ev-postfix-static-field-onpod-live-verification`
confirming the static-field sweep is genuinely admitting real edges
every call (up to 737/chunk) and advancing its cursor correctly.

## Not yet confirmed (working hypothesis only)

One hypothesis worth checking against logs before asserting: the
app-classes-first partition in `admitStaticFieldRoots()` sorts by the
classloader of the **class being swept for static fields** (the holder
class), not by the referenced object's own class. `candidate[1]`'s own
class (`[Ljava/lang/Object;`) is very likely bootstrap-loaded (null
loader) itself, but that says nothing about which class *holds the
static field pointing to it* — if that holder is a JDK/bootstrap class,
it sweeps in the large tail-end of the partition and may simply not have
been reached yet in the current (or any completed) lap, since
`cycle_complete=1` has not yet been observed at all (see
`ev-postfix-static-field-onpod-live-verification`).

Alternative hypotheses not yet ruled out:
- candidate[1]'s referencing object is reachable via the general
  frontier/expandFrontier path, not the static-field-only path, and the
  bottleneck is unrelated to this fix entirely.
- some other admission gate/slot bug specific to slot=3 (distinct from
  the previously-fixed `find-marker-tag-slot-index-mismatch`).

## Timing check supports the "not-yet-swept" hypothesis (not proof)

JVM PID 92618 uptime at time of check: 23m42s (`ps -o etime`). Over an 8-
minute log window, `sweep_cursor` advanced from 13312 to 18944 (5632
classes / 8 min ≈ 700 classes/min) out of `last_resolved_class_count=34053`
total loaded classes — i.e. the sweep is still inside its **first lap**
(~40-55% through), extrapolating to ~45-50 min for one full lap. This is
consistent with `cycle_complete=1` never having been observed
(`ev-postfix-static-field-onpod-live-verification`) and supports (but
does not prove) the hypothesis that candidate[1]'s holder class — if it's
a JDK/bootstrap class ordered in the tail of the app-classes-first
partition — simply hasn't been reached yet by any lap. Not proof: did
not confirm which specific class holds the static field pointing to
candidate[1]'s object, nor whether app-classes-first laps that already
completed for early parts of the classlist would have covered it.

## Update: a full lap has since wrapped, "just needs time" is now weaker

Re-checked at JVM uptime 1:27:00. `sweep_cursor` observed wrapping
(`33792 -> 0 -> 512 -> 1024 -> ... -> 3072` in one continuous 40s live
capture) — i.e. the classlist has now been walked end-to-end at least
once (`cycle_complete` still never observed as `1`, consistent with
`truncated=1` recurring in most chunks). `buildCanaryChainEvent(slot=3)
-> 0` is still the outcome on every one of 870 samples in that same
window; no `tag=` line for klass_id=283 anywhere in ~250k lines of live
log. The "hasn't been reached by any lap yet" explanation is therefore
weaker than initially thought, since at least one full pass over the
classlist has now happened.

Also noted: candidate slot **assignment** (the `candidate[N]` loop-index
label in `pollWatchedTargets`) has shifted — klass_id=283 was previously
logged as `candidate[1]`, now as `candidate[0]`. The persistent identity
(`slot=3`, decoded from the marker tag) is unchanged, so this is NOT a
new occurrence of `find-marker-tag-slot-index-mismatch` — it matches the
already-investigated-and-retracted slot-churn concern in
`ev-postCB-onpod-live-verification` (loop-index label churns, `slot=N`
does not).

## New hypothesis (unconfirmed): per-chunk truncation may recur at the same point every lap

Chunks near the start of a lap (`sweep_cursor` 512-3072, right after
wrap) consistently show `truncated=1` with `edges_admitted≈0`, while
chunks further along (e.g. `sweep_cursor≈33280`) admitted hundreds of
edges in the same capture. Per the fix's design
(`find-static-field-sweep-cursor-fix`), a truncated chunk's cursor still
advances to the chunk boundary — the chunk is only revisited on the
*next* lap, called again with `FollowReferences` over the same 512-class
window from its start. If JVMTI's class enumeration order is stable
within a JVM's lifetime (typical, not guaranteed) and per-class
static-field-walk cost is roughly deterministic, the *same* subset of
classes near the tail of that chunk could be skipped by the deadline on
every single lap — a structural starvation gap at chunk granularity,
echoing the original whole-classlist version of this bug
(`find-static-field-sweep-never-completes`) but scoped smaller. **Not
confirmed** — would need per-class truncation-point visibility the
current `TEST_LOG` doesn't provide (it only reports chunk-level
`edges_admitted`/`truncated`, not which class index inside the chunk the
`FollowReferences` callback actually reached). If candidate[1]'s holder
class sits in such a starved region, that would fully explain the
persistent non-resolution independent of how many laps run.

## Code-confirmed mechanism strengthening the hypothesis

Read `heapReferenceCallback()` (`referenceChains.cpp:1480-1511`) and
`runPassManualWalk()` (`:2202-2345`) directly against the log data:

1. On deadline exceeded, `heapReferenceCallback()` returns
   `JVMTI_VISIT_ABORT` (`:1509-1510`), and the method's own comment at
   `:1516` states this "aborts the entire FollowReferences walk (JVMTI
   spec)" — i.e. a truncated chunk's call stops the whole 512-class
   holder-array walk at whatever point it had reached, not just the
   current class.
2. `_pass_deadline_ns` is set fresh (≈full `_effective_pause_target_ms`,
   ≤50ms) at the top of `runPassManualWalk()` (`:2222-2224`), and
   `admitStaticFieldRoots()` is the first thing that spends it
   (`:2323`) — `resolveLoadedClasses()`'s own classlist-tagging cost
   runs earlier, outside this budget (`:3000` vs. `:3067`). So each
   chunk call gets a near-full fresh deadline, not a leftover sliver.
3. Despite that, `edges_admitted` is 0-1 in the large majority of
   samples, including 5 consecutive post-wrap chunks
   (`sweep_cursor=1024,1536,2048,2560,3072`, all `truncated=1`,
   `edges_admitted∈{0,1,3}` -
   `ev-postfix-static-field-onpod-live-verification`) — i.e. the walk
   is tripping the 4096-callback-granularity deadline check almost
   immediately, visiting only a small prefix of the chunk before
   aborting, on call after call.

Combined: if `GetLoadedClasses()` ordering is stable within the JVM's
lifetime (no spec guarantee, but no reason to expect churn for classes
already loaded) and the app-classes-first partition is deterministic per
call, each chunk boundary lands on roughly the same classes every lap. If
an early class within a chunk reliably generates enough callback traffic
(e.g. a class with a large/richly-connected static field graph) to trip
the deadline before the walk reaches deeper into that chunk, **the tail
of that chunk would be starved on every lap, not merely delayed** — a
smaller-scoped recurrence of the same failure mode
`find-static-field-sweep-never-completes` originally described for the
whole classlist, now at chunk granularity instead. If the class holding
the static field to candidate[1]'s object sits in such a tail, this
would fully explain zero resolution even after a full lap has wrapped.

**Not proven, still a hypothesis**: cannot distinguish "deterministic
per-chunk cutoff" from "just unlucky most of the time under GC/scheduler
jitter" from current logs — `TEST_LOG` reports only chunk-level
`edges_admitted`/`truncated`, not which class index inside the chunk the
walk actually reached before aborting. Confirming would need either
per-class-index instrumentation inside `heapReferenceCallback()`'s
deadline-check path, or observing whether the SAME chunk's
`edges_admitted` value is stable/repeats across multiple laps (supports
determinism) vs. varies a lot (supports jitter-driven, eventually-covers-
everything).

## Correction: volume driver is NOT a class's own field count

User directly challenged the "a class's own static-field graph is large
enough to blow the full deadline" framing above: JVM class-file format
caps `fields_count` at `u2` (65535), and ordinary classes have far fewer
static fields than that — implausible as the sole explanation for
near-universal near-immediate per-chunk truncation.

Re-read `heapReferenceCallback()` (`referenceChains.cpp:1576-1600,
1690-1703`) to test this directly:

1. `:1576-1588` — when the static-field sweep's seed edge (holder[i] ->
   class, tag<0) is walked, the continuation explicitly returns
   `JVMTI_VISIT_OBJECTS`, and the surrounding comment (`:1594-1599`)
   states this opens up "this class's own outgoing references - static
   fields, superclass, interfaces, constant pool, class loader, ...".
   I.e. NOT limited to static fields — JVMTI reports the class's *entire*
   metadata reference graph as separate callbacks, one per edge.
2. `:1690-1703` — for the `admitStaticFieldRoots()` call,
   `ctx->batch_tags` points at an *empty* set (`:2859-2860`), so every
   referent reached one hop past the class fails
   `batch_tags->count(my_tag) != 0` and returns `0` — descent stops dead
   after exactly one hop. Confirms the "one hop past class" design intent
   IS correctly enforced: a referent's own array elements/collection
   internals are never visited via this path. This is not runaway
   recursion.

Conclusion: the user is correct that static-field count specifically
cannot explain the volume. The revised, code-grounded driver is the
class's *full* JVMTI-reported reference set — most plausibly dominated by
`JVMTI_HEAP_REFERENCE_CONSTANT_POOL` callbacks (one per resolved
constant-pool entry referencing a heap object: interned String literals,
Class literals, MethodHandle/MethodType constants). Constant-pool size is
capped at 65535 by the class file format (same order as `fields_count`),
but realistic population is very different from static-field count:
ordinary classes routinely carry hundreds to low-thousands of resolved CP
entries, vs. a handful of static fields — a fanout source with no
comparably small practical bound. Combined with the flat one-hop-wide
(not deep) expansion confirmed above, a small number of CP-heavy classes
near the front of a chunk could plausibly trip the 4096-callback
deadline-check granularity almost immediately, consistent with observed
`edges_admitted∈{0,1,3}` on successive chunks.

**Not yet measured directly** — this is inference from code +
JVMTI-spec semantics (`JVMTI_HEAP_REFERENCE_CONSTANT_POOL`'s
per-resolved-entry firing), not a logged per-`reference_kind` callback
count on-pod. To confirm, would need temporary instrumentation adding a
per-`reference_kind` counter inside the deadline-check path to verify
CONSTANT_POOL (vs. static fields/interfaces/superclass) actually
dominates volume in a truncated chunk.

## Confirmed via live per-kind instrumentation

Deployed the temp `kind_counts` diagnostic (commit `3a2fc0d5e`, pod
`prof-analyzer-hotdog-jb-c944876b9-8vtzw`) and observed 36 samples over a
10-minute window: `CONSTANT_POOL` (k9) is the largest and most variable
kind in every single sample (2353-10894), always 5-15x larger than
`STATIC_FIELD` (k8: 174-2339) in the same sample. Full data and reading in
`ev-kind-counts-constant-pool-dominates`. This closes the "not yet
measured directly" gap — the driver is confirmed, not inferred.

## Root cause, precisely

`heapReferenceCallback()`'s admission path
(`referenceChains.cpp:1672-1705` pre-fix) has no `reference_kind` filter:
once the `static_field_seed` branch (`:1593-1604`) opens descent into a
class's own metadata graph via `JVMTI_VISIT_OBJECTS`, JVMTI delivers
*every* kind of edge from that class object as a separate callback — not
just `STATIC_FIELD`, but also `CONSTANT_POOL`, `INTERFACE`, `SUPERCLASS`,
`CLASS_LOADER`, etc. All of these were being fully processed through
`admitObject()` (hash-insert, tag, `edges_admitted++`,
`trackLeakAccumulation()`), each counted as a JVMTI callback against the
4096-callback deadline-check granularity and the pass's overall budget —
despite `admitStaticFieldRoots()` only wanting the `STATIC_FIELD` edges.
`CONSTANT_POOL` callbacks specifically only fire for already-*resolved*
constant-pool slots (interned Strings, resolved Class mirrors,
MethodHandle/MethodType/CallSite constants) — they are real, live GC
reachability edges, not JVMTI bookkeeping artifacts or symbolic/unresolved
references — so admitting them isn't "wrong" in the sense of being fake,
it's wrong in *category*: this sweep is specifically hunting for
objects reachable only via a static field, and constant-pool-interned
objects are a distinct, effectively-permanent-root category that doesn't
belong labeled under this walk's `root_kind`.

## Fix — evolved through two iterations this session

### Iteration 1 (superseded): hard reference_kind filter

Initially implemented a hard filter at `referenceChains.cpp:1672-1686`:
when `ctx->static_field_seed` is true and the referrer is the opened
class object (`*referrer_tag_ptr < 0`), skip admission for any
`reference_kind != JVMTI_HEAP_REFERENCE_STATIC_FIELD`. This dropped ALL
non-STATIC_FIELD edges during the seed sweep. See
`dead-hard-reference-kind-filter` for why this was rejected.

### Iteration 2 (current, implemented, built, gtest-pass, NOT yet committed/deployed): per-class non-static quota + resumable cursor

User's real-world leak taxonomy drove the redesign: static fields are
the most common leak source, but CP-based leaks are still possible (if
rarer). The user's explicit requirement: "we need to design a system
working with this priority and not pushing completely out one or the
other." Two-part design:

**Part 1 — Per-class non-static quota** (`referenceChains.cpp:1699-1731`):
STATIC_FIELD edges always admitted (high-priority leak root).
Non-STATIC_FIELD edges (CONSTANT_POOL, INTERFACE, SUPERCLASS,
CLASS_LOADER, etc.) admitted up to `STATIC_FIELD_SWEEP_NON_STATIC_CAP_PER_CLASS
= 32` per class per lap, then dropped for the rest of that class. Cap
resets on class boundary (detected by `*referrer_tag_ptr !=
ctx->_seed_class_tag`). One fat class cannot exhaust the quota for any
other. The cap (32, per user request) covers almost all classes' full
constant-pool/interface sets while bounding outliers.

**Part 2 — Resumable cursor** (`referenceChains.cpp:2896-2908,
2993-3013`): the holder array is filled in **reversed** chunk order
(`holder[i] = classes[chunk_end - 1 - i]`) so HotSpot's LIFO
`FollowReferences` descent visits classes in **ascending** original
index order (see `ev-hotspot-lifo-visitation-order` for the source
proof). On truncation, the cursor resumes at the class being processed
(`chunk_start + _classes_in_chunk_visited - 1`) instead of skipping to
`chunk_end` — so classes after the interruption point are reached on
the next pass rather than lost for the rest of the lap. The partial
class is redone (already-admitted edges hit `ALREADY_ADMITTED` cheaply;
non-static edges complete within the cap). Chunk size stays at 512 —
the resumable cursor handles the timeout problem, so no chunk-size
decrease is needed.

**PassContext additions** (`referenceChains.cpp:1463-1491`):
`_seed_class_tag` (current class being descended),
`_class_other_admitted` (non-static count for current class),
`_class_other_cap` (per-class cap, 0 disables),
`_classes_in_chunk_visited` (class-boundary counter for resumable
cursor). All zero/false outside the seed sweep — no overhead elsewhere.

**Header** (`referenceChains.h:666-675`): new constexpr
`STATIC_FIELD_SWEEP_NON_STATIC_CAP_PER_CLASS = 32`.

### Scoping verified

`static_field_seed` has exactly one true-assignment call site
(`admitStaticFieldRoots()`), confirmed via grep — the quota logic
cannot fire during the general frontier walk. No risk of masking a
genuine static-field-reachable leak: JVMTI reports each edge separately
by kind, so an object reachable via a static field still gets its own
distinct `STATIC_FIELD`-kind callback regardless of whether
non-static callbacks for the same class were quota-dropped.

### Build + test status

`buildDebug` clean. `gtestDebug` full suite: 525 tests pass, 0 fail, 8
skipped (sigaction-interception + TSan-only stress test). Includes the
90-test `referenceChains_ut` suite. `spotlessApply` clean (no changes).

### Not yet committed / not yet deployed

The fix is uncommitted in the working tree (`referenceChains.cpp` +
`.h` modified). The temp diagnostic `kind_counts` tally (commit
`3a2fc0d5e`) is still in place. Next step: user reviews, commits,
deploys to the hotdog pod, and live-verifies whether candidate[1]
(klass_id=283, slot=3) finally resolves and a real `ReferenceChain`
event gets emitted.

## Update: sweep completed a full lap, candidates still 0/1

With the 200ms deadline diagnostic build (commit `fd18425c6`), the
sweep completed a full untruncated lap (`cycle_complete=1` observed,
`last_static_field_class_count` advanced from 33677 → 33752). All
chunks completed without truncation. See
`ev-timing-split-callback-vs-jvmti`.

Despite the sweep being healthy, candidates are **still 0/1**. The
bottleneck moved downstream: the sweep admits the static field value
(e.g., an `ArrayList`) to the frontier, but `expandFrontier()` must
then expand that `ArrayList` to reach the leaking object. The
`ArrayList` is pushed to the **back** of `_pending_expand` (144k
entries deep), and at 65-87 edges/pass the BFS can't reach it. See
`find-sweep-completes-but-bfs-starved`.

## Two-hop chain architecture (confirmed from code)

The sweep admits only **one hop** past the class: `batch_tags` is empty
for the sweep call (`:2859`), so `heapReferenceCallback()` returns `0`
(no descent) for every referent (`:1813`). A static field value gets
admitted to the frontier but its elements are NOT visited by the sweep.

`expandFrontier()` picks entries from the **front** of `_pending_expand`
(FIFO deque, `:2654`), calls `FollowReferences` on them — that's when
the collection's elements get visited and the canary match can fire.

```
Sweep:        class → STATIC_FIELD → ArrayList   [admitted, pushed to BACK of _pending_expand]
expandFrontier: front of _pending_expand → ... → ArrayList → elements → leakingObject
```

## Status

Root cause confirmed and fixed (per-class quota + resumable cursor,
committed `0e93ab4f7`). Sweep now completes laps cleanly. But the
end-to-end problem persists: BFS throughput is starved by a 144k
backlog. See `find-sweep-completes-but-bfs-starved`. Next: report to
user and propose a fix direction (prioritize sweep-admitted entries or
increase BFS throughput).
