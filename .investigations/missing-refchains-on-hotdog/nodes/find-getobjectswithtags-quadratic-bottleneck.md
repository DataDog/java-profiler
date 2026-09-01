---
id: find-getobjectswithtags-quadratic-bottleneck
type: finding
status: fixed
depends_on: [ev-timing-split-callback-vs-jvmti, find-sweep-completes-but-bfs-starved]
supersedes: []
related: [find-sweep-completes-but-bfs-starved]
tags: [root-cause, referenceChains, bfs, expandFrontier, GetObjectsWithTags, quadratic, throughput, NEW-THIS-SESSION]
created: 2026-08-26
updated: 2026-08-27
---

# GetObjectsWithTags is a quadratic O(tag_map × batch_size) bottleneck starving BFS

## Observation

`expandFrontier` admits only 3-4 edges/pass despite `remaining_budget=3440`.
Per-iteration timing diagnostics (commit `2d310e0fa`) show:

| batch_size | gotw_ms | follow_ms | edges | truncated |
|------------|---------|-----------|-------|----------|
| 3440       | 226     | 6         | 1     | 1        |
| 272        | 40      | 1         | 0     | 0        |
| 3727       | 230     | 5         | 0     | 1        |
| 3452       | 226     | 5         | 1     | 1        |
| 272        | 35      | 1         | 0     | 0        |
| 3739       | 243     | 5         | 0     | 1        |
| 3439       | 242     | 6         | 0     | 1        |
| 272        | 40      | 2         | 1     | 0        |
| 1          | 14      | 0         | 2     | 0        |
| 1          | 11      | 0         | 2     | 0        |
| 3727       | 236     | 6         | 2     | 1        |

`GetObjectsWithTags` takes 226-243ms when batch_size is ~3400-3700, but only
35-40ms when batch_size is 272, and 11-14ms when batch_size is 1. The cost
scales linearly with batch_size.

## Root cause: O(tag_map_size × batch_size) in HotSpot

`GetObjectsWithTags` (`jvmtiTagMap.cpp:1305`) calls `entry_iterate` which
visits every tagged object in the JVMTI tag map (163k entries on this pod).
For each entry, `TagObjectCollector::do_entry` (`:1249`) does an O(N)
linear scan of the `_tags` array:

```cpp
bool do_entry(JvmtiTagMapKey& key, jlong& value) {
    for (int i = 0; i < _tag_count; i++) {
      if (_tags[i] == value) { ... collect ... }
    }
    return true;
  }
```

So the total cost is O(tag_map_size × batch_size) = 163k × 3400 ≈ 554M
comparisons. That's the 226ms. This is a **quadratic blowup**: the tag
map is O(tag_map_size) and the search array is O(batch_size), nested loop.

`FollowReferences` only gets 5-6ms (the leftover after GetObjectsWithTags
consumes the entire 200ms deadline), admits 0-1 edges, and truncates.
The BFS is starved by `GetObjectsWithTags`'s quadratic cost, not by
`FollowReferences` or our callback code.

## Why batch_size is ~3400

`expandFrontier` caps batch_size at `min(source.size(), min(budget, _budget))`
(`:2680`). On this pod, `budget=3741` and `_budget=3741`, so batch_size
collapses to the entire `_pending_expand` backlog (163k entries) divided
into chunks of ~3741. Each chunk triggers one `GetObjectsWithTags` call
with ~3400 tags.

## Fix direction: eliminate GetObjectsWithTags from the hot path

### Constraint: no O(1) tag→object lookup in JVMTI

`GetObjectsWithTags` is the **only** JVMTI API that reverse-looks-up
tags to objects. There is no `GetObjectByTag`. `GetTag(env, object, &tag)`
takes an object and returns its tag — the wrong direction. So any
fix must either (a) avoid the reverse lookup entirely, or (b) make
the lookup cheaper.

### Cannot create JNI ref at admission time

Inside `heapReferenceCallback`, we get `tag_ptr` (pointer to JVMTI's
tag slot) but NOT a `jobject`. The actual `oop` is inside
HotSpot's `CallbackWrapper` (`jvmtiTagMap.cpp:193`) and not
exposed to the callback. We cannot call `JNIHandles::make_local` or
`NewWeakGlobalRef` from inside the callback — we don't have the
object reference, only the tag pointer. So we cannot populate a
tag→jobject cache at admission time.

### Can cache jweak after first GetObjectsWithTags resolution

`expandFrontier` gets jobjects back from `GetObjectsWithTags` as JNI
local refs. We could promote them to weak global refs (`NewWeakGlobalRef`)
and cache them in a parallel array indexed by tag-1 (matching
FrontierTable's flat-array layout). On subsequent expansions (rotation
re-expansion of already-EXPANDED entries), check the jweak first — if
non-null, the object is alive, skip `GetObjectsWithTags` for that entry.

This eliminates `GetObjectsWithTags` for rotation (256 entries/pass →
~0ms instead of ~17ms). But it does NOT help first-time `_pending_expand`
expansion — those entries have never been resolved before, so there's no
cached jweak.

### First-time expansion still needs GetObjectsWithTags

For `_pending_expand` entries (first-time expansion), we have no way to
get the jobject without `GetObjectsWithTags`. The only mitigation is
reducing batch_size to keep the O(tag_map × batch) cost bounded.

Adaptive batch_size: if we want `GetObjectsWithTags` to take ≤5ms, and
the tag map is 163k entries, then batch_size ≤ 5ms / (163k × ~1.4ns) ≈ 22.
That's tiny — each `FollowReferences` would only expand 22 entries, and
draining 163k entries would need ~7400 iterations (safepoints).

### Self-calibrating adaptive batch_size (approved, implementing)

User rejected a fixed per-comparison cost estimate (varies by CPU,
cache, memory bandwidth). Instead: self-calibrate from measured
`GetObjectsWithTags` elapsed time.

```
// After each GetObjectsWithTags call:
measured_cost_per_tag = gotw_elapsed_ns / batch_size
// Before the next call:
batch_size = max(1, cpu_budget_ns / ema_cost_per_tag)
// Exponential moving average to smooth jitter:
ema_cost_per_tag = ema * 0.8 + measured * 0.2
```

Properties:
- No machine-specific constants — adapts to whatever CPU it's on
- Adapts as tag map grows (batch_size shrinks automatically)
- Only knob is `cpu_budget_ns` (policy choice, not machine estimate)
- First call: conservative small default (e.g. 64), then adapt
- `cpu_budget_ns` target: ~25ms per pass (CPU overhead, not safepoint)

Not yet implemented — implementing now.

## Fix: self-calibrating adaptive batch_size (COMMITTED, DEPLOYED, CONFIRMED LIVE ON-POD)

Commit `337b4c21d` + verification log `8f69683f9`. Deployed on pod
`prof-analyzer-hotdog-jb-c944876b9-q8vd8`, JVM PID 263646.

### Implementation

- `_gotw_ema_cost_per_tag_ns` (EMA of cost-per-tag) on the tracker
- After each `GetObjectsWithTags` call: `measured = gotw_elapsed_ns / batch_size`,
  `ema = ema * 4/5 + measured / 5`
- Before each call: `batch_size = max(1, GOTW_CPU_BUDGET_NS / ema)`
- `GOTW_CPU_BUDGET_NS = 25ms` (CPU overhead target, NOT safepoint)
- `GOTW_INITIAL_BATCH_SIZE = 64` (conservative first call)
- Still capped at `min(budget, _budget)` for JNI safety
- Also reverted temp 200ms deadline override + removed temp timing diagnostics

### On-pod results (2026-08-27)

| Phase | batch_size | gotw_ms | edges/call | edges/pass |
|-------|-----------|---------|------------|------------|
| Before fix | ~3400 | 226-243 | 0-1 | 3-4 |
| After fix (warmup) | 1-64 | 2-7 | 3-7 | — |
| After fix (converged) | ~390-420 | 20-35 | 0-503 | 456-971 |

EMA converged to ~62k ns/tag. BFS throughput up **~100-200x** (456-971
edges/pass vs 3-4 before). `GetObjectsWithTags` bounded at 20-35ms
(target was 25ms).

### Remaining

0 candidates at time of verification because JVM restarted and liveness
tracker needs warmup (`heapFloorRising=0`, `required_hysteresis=5`).
Monitoring for candidates to appear once enough GC generations pass.

## Semantics clarification (this session, jdk21 source + pod)

GetObjectsWithTags is NOT a VM op (jvmtiTagMap.cpp:1305): it scans the
whole tag map under the tag-map mutex, O(tag-map size) per call
regardless of tags requested - it blocks other tag users but does not
stop the world. Measured on hotdog JVM 75258: 18-21ms/call at ~200k
entries, ~5 calls/pass at ~88 passes/min = ~100ms of tag-map-locked
scanning per pass - the dominant per-pass cost, vs the walk VM op's
bounded ~15ms STW. See find-jvmti-heap-walk-stw-vmop for the full
pause-vs-lock picture.
