---
id: q-heapliveobject-absent-on-pod-chunks
type: question
status: open
depends_on: [ev-leaktag-onpod-round8]
related: [find-leak-tag-pool-implementation]
tags: [heapliveobject, liveness, jfr, emission, open, NEW-THIS-SESSION]
created: 20260902
updated: 20260902
---

# Why do pod JFR chunks contain zero datadog.HeapLiveObject events?

Round-8 JFR chunks (pod pid_4445) declare no HeapLiveObject event type
at all and contain zero events, while LivenessTracker is clearly
tracking (tagLeakInstances summaries live, tagged=8). Earlier rounds
(ev-jfr-analysis-real-recording) DID see 13 [B HeapLiveObject events,
so emission worked at some point on the older pod/build.

## What is known

- The emission path exists: BCI_LIVENESS →
  `Recording::recordHeapLiveObject` (flightRecorder.cpp:2077, call at
  :2471).
- Round 8 chunks DO contain other datadog events (ExceptionSample,
  ProfilerSetting, ExceptionCount), so chunks are not the wrong source
  (kubectl cp from /tmp/ddprof_root, per the recorded methodology).

## Why it matters

HeapLiveObject.leakTag is one half of the correlation pair
(ReferenceChain.targetTag ↔ HeapLiveObject.leakTag,
find-leak-tag-pool-implementation). Even when interception fires, a
missing HeapLiveObject event breaks the backend join.

## Candidate causes to check (NOT yet investigated)

- The new pod's agent config differs on liveness settings (memory=...
  ratio / liveheap flags in ProfilerSetting — the round-8 chunk dump
  was only partially inspected).
- The liveness sampler thread not running on this JVM / not emitting
  BCI_LIVENESS events (check counters).
- Emission gated behind something that changed between the round-2
  pod (where HeapLiveObject events appeared) and round 8.

Priority: secondary — resolve after interception fires; but verify the
ProfilerSetting memory= line on the next chunk pull (free, one grep).
