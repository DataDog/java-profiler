---
id: ev-leaktag-onpod-round7
type: evidence
status: confirmed
depends_on: [ev-leaktag-onpod-round6, find-option-c-descend-walk-design, find-field-name-decoding]
related: [find-priority-queue-starves-bfs-crawl]
tags: [pod-verification, round-7, descend-walk, interception-zero, depth-cap, NEW-THIS-SESSION]
created: 20260902
updated: 20260902
---

# Pod round 7: both descend-walk prongs live, interception still zero - holder sits deeper than the 6-hop cap or outside the covered root kinds

Deploy: 13d3f87b3 (descend walks + retention-edge labels), deployed in
place by the user on REPLACEMENT pod srwnz (the original zng9s was
EVICTED - my fault: an in-pod jcmd GC.heap_dump wrote a ~5GB hprof to the
node overlay and the container got OOM-killed (exit 137) then the pod
evicted; the in-place patch died with it. DO NOT dump in-pod on these
pods). JVM 4818, leak thread tid 5025, klass_id 7, 22 tagged chunks
(max_size 78643216), need_set=0 stable, ~1500+ passes over ~40 min.

## Verified live this round

- Prong 1 (walkCandidateThreadLocals): candidates=1 tids=1 walked=1
  every pass; first pass admitted the ThreadLocalMap structure (15
  edges), then idempotent 0s - and registerExistingThreads() worked: the
  leak thread predates the recording and IS registered (the round-7
  pre-flight catch: walked=0 before the sweep existed).
- Prong 2 (walkStaticFieldAnchors): exactly 4 root-attached STATIC_FIELD
  anchors exist (sweep lapped all 33622 classes; the low count is itself
  a signal - see below), all 4 walked every pass, single walks admitting
  up to 3119 edges (deep subgraphs - executor-task-shaped structures).
- Edge labels shipped (chains will carry field names once one is found).
- Tagging healthy: tagLeakInstances summary per poll, tagged=22 stable,
  ages growing (retained), need_set=0.
- BFS still can't drain: pendingExpand 73.0k -> 73.6k net-growing,
  frontier 113k->114k; gotw healthy (batch 512, ema_call_ms 29-33).

## The verdict: interception 0 with EVERYTHING live

The tagged chunks are neither (a) in the leak thread's ThreadLocalMap
(thread walk covers that subgraph fully and idempotently) nor (b)
within DESCENT_HOPS=6 below any root-attached static (all 4 anchors are
descend-walked every pass, wholesale, thousands of edges). They are also
not frame-locals (the leak thread parks idle between task runs - a
frame-local accumulator would be collectible while parked; tagged chunks
survive GCs, ages to 236).

## Remaining shapes (hypotheses, not yet proven)

1. DEEPER THAN 6 HOPS below a static anchor - the leading hypothesis:
   the leak task graph shape is static ExecutorService(0) ->
   DelayedWorkQueue(1) -> q[](2) -> ScheduledFutureTask(3) -> task(4)
   -> accumulator(5) -> list(6) -> chunks(7) - the 3000+-edge static
   walks admitting exactly that kind of task graph but stopping at the
   cap. The holder interior (accumulator at depth 5) IS likely admitted
   already.
2. A root kind outside both prongs (JNI_GLOBAL / MONITOR / another
   thread's stack root) - no current evidence for or against.

## Fix candidates (presented, NOT picked)

- Minimal, taxonomy-consistent: raise DESCENT_HOPS (6 -> 12-16); the
  walk is already deadline-bounded per slice, so cost is unchanged
  structurally - this is a one-constant rebuild+redeploy.
- Same-pattern extension if that does not close it: extend
  collectStaticFieldAnchorsForRotation's filter to other durable
  root kinds (JNI_GLOBAL), same wrapping-cursor bounded walks.

Pod log retention is ~30s at current volume (3.2M lines/6min) - use
kubectl logs -f streaming for evidence windows, not --since.
