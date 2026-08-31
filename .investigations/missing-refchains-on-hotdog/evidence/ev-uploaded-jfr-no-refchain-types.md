---
id: ev-uploaded-jfr-no-refchain-types
type: evidence
status: confirmed
depends_on: []
supersedes: []
related: [find-refchains-not-deployed, dead-jcmd-jfr-dump-wrong-source, dead-toolkit-prod-datacenter]
tags: [jfr, profiling-toolkit, event-types, pre-resync]
created: 2026-08-24
updated: 2026-08-24
---

# Phase 1: uploaded profiles do not even declare datadog.ReferenceChain

## Source
Profiling Toolkit `download.py`, org 2, `--datacenter us1.staging.dog`,
`--service prof-analyzer-hotdog --app prof-analyzer-hotdog-jb`,
last 60 minutes, downloaded to `/tmp/hotdog-jb-only/`.

## Raw excerpts

```
Query: service:prof-analyzer-hotdog app:prof-analyzer-hotdog-jb
Found 5 matching profiles
  -> prof-analyzer-hotdog-2026-08-24_13-41-35.010Z-...-stripe.jfr    (9.5M)
  -> prof-analyzer-hotdog-2026-08-24_13-40-35.011Z-...-stripe.jfr    (8.6M)
  (three .tar entries contained cpu.pprof only, "no JFR found in tar")
```

`strings <jfr> | grep -oE "datadog\.[A-Za-z]+" | sort -u` for both real JFRs:

```
datadog.AggregatedSmapEntry      datadog.HeapLiveObject
datadog.AvailableProcessorCores  datadog.HeapUsage
datadog.BackpressureSample       datadog.MethodSample
datadog.DatadogProfilerClassRefCache
datadog.DatadogProfilerConfig    datadog.NativeMemoryAllocation
datadog.Deadlock                 datadog.NativeSocketEvent
datadog.DeadlockedThread         datadog.ObjectSample
datadog.DirectAllocationSample   datadog.ProfilerCounter
datadog.DirectAllocationTotal    datadog.ProfilerSetting
datadog.Endpoint                 datadog.QueueTime
datadog.ExceptionCount           datadog.SmapEntry
datadog.ExceptionSample
datadog.ExecutionSample
```

```
=== referencechain hit count ===
0
```

`datadog.ReferenceChain` / `datadog.ReferenceChainAbandoned` are absent
entirely — not zero-count, not declared. `datadog.HeapLiveObject` IS
present, so liveheap itself was working.

Agent version confirmed from the same JFRs:

```
1.65.0~dd00372bdd
```

## Contrast: jcmd JFR.dump (wrong source)

`jcmd 231 JFR.dump filename=/tmp/hotdog-check-jb.jfr` produced a 1.7 MB
recording; jafar `jfr_list_types filter=datadog scan=true` on it returned
only 11 types / 220 events:

```
datadog.ProfilerSetting 110, datadog.ExceptionSample 83,
datadog.ExceptionCount 19, datadog.AvailableProcessorCores 6,
datadog.DirectAllocationTotal 1, datadog.DirectAllocationSample 1,
datadog.AggregatedSmapEntry 0, datadog.DeadlockedThread 0,
datadog.SmapEntry 0, datadog.BackpressureSample 0, datadog.Deadlock 0
```

i.e. dd-trace-java's own JFR only — see `dead-jcmd-jfr-dump-wrong-source`.
