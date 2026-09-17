---
id: ev-tid-clustering-per-thread-working
type: evidence
status: confirmed
depends_on: [find-lambda-fragments-calltrace-id, q-dominant-gens-still-one-with-tid]
supersedes: [ev-tid-clustering-onpod-verification]
related: [find-lambda-fragments-calltrace-id, q-dominant-gens-still-one-with-tid]
tags: [pod-logs, on-pod, post-fix, live-verification, tid-clustering, per-thread, dominant-gens, NEW-THIS-SESSION]
created: 20260828
updated: 20260828
---

# Per-thread generation tracking confirmed working on-pod

## Context

After switching from call_trace_id to tid (2c50bf0cd) and adding
per-thread diagnostic (5e4493dbf), deployed to pod PID 91958.

## Observation

klass_id=6 (later klass_id=9 on new JVM) shows dominant thread with
multiple ages:

```
foldKlassCountsLocked scratch[1] klass_id=6 gen_count=5 thread_count=10 oldest_count=3
  thread[0] tid=92169 age_count=3    ← dominant leak thread
  thread[1] tid=93010 age_count=2
  thread[2] tid=92380 age_count=1
  ...
```

`tid=92169` has `age_count=3` — the leak thread. The per-thread
tracking IS working. Earlier `dominant_gens=1` lines were from other
classes, not the leak class.

## Re-mint confirmed

```
foldKlassCountsLocked re-minting klass_id=9: dominant_tid=92383 dominant_gens=2 but no rep matches
```

Re-mint fired when dominant thread changed and no existing rep matched.

## Leak candidate confirmed

klass_id=9 ([B]) is the leak candidate:
```
selectLeakCandidates entry[1] klass_id=9 ring_fill=30 has_trend=1
  slope=4.025806 consecutive_positive=8 required=3 rep_count=1
```

## Chains emitted

8 ReferenceChain events emitted:
```
drainPendingChainEvents re-emitted=8
Profiler::writeReferenceChain ×8
Profiler::dump reference-chain batch=8 write_dropped=0
```

But chains are depth=1 with no holder — see
`find-already-admitted-blocks-deeper-chain`.
