---
id: dead-jcmd-jfr-dump-wrong-source
type: deadend
status: refuted
depends_on: [ev-uploaded-jfr-no-refchain-types]
supersedes: []
related: [find-onpod-evidence-methodology, dead-toolkit-prod-datacenter]
tags: [methodology, wrong-evidence-source, jcmd, jfr]
created: 2026-08-24
updated: 2026-08-24
---

# Dead end: `jcmd <pid> JFR.dump` is the wrong evidence source for ddprof events

## Reasoning chain

The first attempt to answer "are there reference-chain events?" was to
dump the live recording on the pod:

```
jcmd 231 JFR.dump filename=/tmp/hotdog-check-jb.jfr   # 1.7 MB
kubectl cp … /tmp/hotdog-jfr/hotdog-check-jb.jfr
```

jafar's `jfr_list_types filter=datadog scan=true` on that dump returned 11
types / 220 events: `ProfilerSetting` 110, `ExceptionSample` 83,
`ExceptionCount` 19, `AvailableProcessorCores` 6, two `DirectAllocation*`
at 1, and five zero-count types. `filter=chain` and `filter=liveheap`
returned **0 types** — which looks like damning evidence but proves
nothing.

Reason: `JFR.dump` captures only the JVM-side `dd-profiling` recording
that dd-trace-java itself drives. ddprof writes its own recording and
uploads it separately. The absence of ddprof event types in a `JFR.dump`
is expected regardless of whether the feature works. Note the same dump
also lacked `datadog.ExecutionSample`, `MethodSample`, `ObjectSample` and
`HeapLiveObject` — all features known to be working.

The correct source is the uploaded profile fetched via the Profiling
Toolkit (`ev-uploaded-jfr-no-refchain-types`), whose type list is ~2x
longer and does include the ddprof events.

## Evidence
- `evidence/ev-uploaded-jfr-no-refchain-types.md` (contains both type lists
  side by side)

## What this rules out
- Using `jcmd JFR.dump` / the `hotdog-check --jfr` path to reason about any
  ddprof-emitted event type. Always download the uploaded profile instead.
