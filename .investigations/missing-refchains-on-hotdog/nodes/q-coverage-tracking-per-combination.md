---
id: q-coverage-tracking-per-combination
type: question
status: open
depends_on: [find-leak-tag-pool-implementation]
supersedes: []
related: [find-leak-tag-pool-implementation, find-lambda-fragments-calltrace-id]
tags: [adaptive-cpu, coverage, call_trace_id, tid, referenceChains, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# Coverage tracking: per-object vs per-(call_trace_id, tid) combination

## The gap

The user's requirement (design D): CPU should drop to ~1x "the moment
we have at least one reference chain for each of the
call_trace_id/tid combination for classes with growing surviving gens
metric."

Current implementation (commit `294f09ff3`) is per-OBJECT:
`_leak_tags_resolved` counts leak tags with chains vs
`_leak_tags_assigned`. If 10 objects share one (call_trace_id, tid)
combination, we need 10 chains before coverage completes — wasteful;
one chain per combination should suffice.

## Why per-object was chosen first

Simplicity: avoids a set data structure (allocation discipline).
`LivenessTracker::getLeakTagInfo(tag)` already returns
`{call_trace_id, tid}` per tag, so the data to do it properly exists.

## Options to refine

1. Fixed-size array of distinct (call_trace_id, tid) pairs in
   ReferenceChainTracker (universe computed at tagLeakInstances time
   from `_leak_tag_info[]`, covered incremented on first chain per
   combination). Distinct combinations expected small (1-5 on
   hotdog).
2. Keep per-object but only tag ONE representative per combination
   in tagLeakInstances (dedupe at tag time) — then per-object coverage
   IS per-combination coverage. Cleaner: no set needed downstream.
   Risk: loses the multi-instance redundancy for BFS discovery.

Option 2 is likely the leaner design — decide after on-pod
verification shows whether per-object counting actually stalls at
1x or wastes CPU.
