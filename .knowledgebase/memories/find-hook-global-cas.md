---
id: find-hook-global-cas
title: The nativemem unsampled fast path does a CAS on one process-global counter per malloc
kind: finding
tags: [nativemem, overhead, contention, always-on]
applies_to: []
source: malloc-arena-detection/find-hook-global-cas
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# The nativemem unsampled fast path does a CAS on one process-global counter per malloc

## Reasoning chain
`MallocTracer::maybeRecord` (ddprof-lib/src/main/cpp/mallocTracer.cpp:314-326) on every intercepted allocation while running():
TLS lookup `ProfiledThread::acquireCurrent()` (first touch claims a pool slot under SignalBlocker),
`CriticalSection` enter/exit, then `shouldSample()` (ddprof-lib/src/main/cpp/mallocTracer.cpp:282-298) which CASes the single global
`_bytes_until_sample`. Under the exact workload we want to detect (many threads x many small mallocs) all
threads hammer one cache line -> cross-core contention scaling with thread count. Hence running nativemem
always-on, even with a huge interval, is NOT cheap as implemented. A per-thread countdown in ProfiledThread
would remove the shared line, but that is a change to nativemem, not a detector.
Once stop()'d, hooks stay installed (ddprof-lib/src/main/cpp/mallocTracer.cpp:406-410) but cost only the `_running` load.

## Evidence
- ddprof-lib/src/main/cpp/mallocTracer.cpp:282-298 shouldSample CAS loop on `_bytes_until_sample`.
- ddprof-lib/src/main/cpp/threadLocalData.inline.h:23-37 acquireCurrent.

## What this rules out
- "Just turn on nativemem with a sparse interval everywhere" as the always-on detector, unless the sampler is first made per-thread. Filed PROF-16349 (2026-10-26): move the countdown into ProfiledThread, same model as HotSpot ThreadHeapSampler; statistically equivalent (independent per-thread Poisson, memoryless). Once fixed, hyp-hooks-always-on becomes viable again.
