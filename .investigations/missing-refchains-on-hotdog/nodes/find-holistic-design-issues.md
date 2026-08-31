---
id: find-holistic-design-issues
type: finding
status: confirmed
depends_on: [find-already-admitted-blocks-deeper-chain, find-per-class-caching-blocks-instances]
supersedes: []
related: [find-already-admitted-blocks-deeper-chain, find-per-class-caching-blocks-instances, find-cpu-pain-budget-blocks-bfs]
tags: [root-cause, design, referenceChains, jni-local, targetTag, correlation, cpu-budget, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# Holistic design issues in reference chain pipeline

## Four problems identified from JFR recording
~/Downloads/20260831-092433_prof-analyzer-hotdog_AaBXI2uGAACSSh31cW40WAAA/main.jfr

### 1. Leaking [B not in the chains

The 27 leaking [B instances (78MB each, allocated by
`lambda$static$1` in `ProfileAnalyzer`) are NOT among the 40
ReferenceChain events. The chains are for OTHER [B instances:
- 6 depth=13 jni_global chains (some other [B reached via deep path)
- 2 depth=0 static_field chains (direct static field refs)
- 32 depth=1 jni_local/stack_local chains (noise)

The leaking [B instances are held via static field → ArrayList → [B,
but the BFS admits them as JNI-local roots (depth=0) before the
static field sweep reaches them. The `improveChain` fix should help
but never fires (0 invalidate logs) — likely because the BFS doesn't
revisit already-tagged objects' incoming edges in the same pass.

### 2. More chains than surviving live heap objects

40 ReferenceChain events vs 36 HeapLiveObject events. Chains are
cached and re-emitted across dump cycles even after the original
object has been GC'd. The cache (`_resolved_chains`) is never
invalidated when objects die — it's only cleared on search restart.

### 3. No correlation between HeapLiveObject and ReferenceChain

HeapLiveObject events have no tag/ID that matches ReferenceChain's
`targetTag`. The `targetTag` is a JVMTI tag (frontier table index),
while HeapLiveObject events are identified by (klass, tid, age, size).
There is no shared identifier to join them.

### 4. 45% CPU consumption from continuous heap walking

The 100× canary pain budget multiplier makes the BFS run
continuously, eating 45% CPU. The multiplier was set to 100 to
overcome cpu_pain_budget blocking, but it's way too high for
production. Need to find the right balance — enough to make progress
but not eat the CPU.

## Root cause

The fundamental issue is that the BFS and the liveness tracker operate
on different object sets with no correlation:

- **Liveness tracker** subsamples allocations (10%), tracks survivors
  by (klass_id, tid, age), and selects leak candidates by ring-buffer
  growth trend. It tags representatives with marker tags.
- **BFS** walks the entire heap from roots, admits objects into the
  frontier, and builds chains from frontier entries. It discovers
  [B instances via auto-mark (class match) but those may be different
  instances than the liveness tracker's representatives.

The leaking [B (78MB, from `lambda$static$1`) is in the liveness
tracker's table (we see it in HeapLiveObject events), but the BFS
finds OTHER [B instances first (JNI locals, small buffers from other
threads) and caches their chains. The leaking [B is never reached
because:
1. It's admitted as a JNI-local root (depth=0) before the static
   field sweep reaches it
2. `improveChain` doesn't fire because the BFS doesn't revisit
   already-tagged objects' incoming edges
3. Even if it did, the cached chain (depth=1) blocks rebuilding

## Proposed approach

Need a design-level rethink, not whack-a-mole fixes. Key questions:
1. How to correlate ReferenceChain targetTag with HeapLiveObject events
2. How to invalidate cached chains when objects die
3. How to prioritize the BFS to reach leaking instances before noise
4. How to bound CPU consumption while still making progress
