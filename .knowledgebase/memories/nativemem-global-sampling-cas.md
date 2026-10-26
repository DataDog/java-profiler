---
id: nativemem-global-sampling-cas
title: nativemem's unsampled malloc path does a CAS on one process-global counter, which contends across threads
kind: finding
tags: [nativemem, overhead, contention, malloc]
applies_to: [ddprof-lib/src/main/cpp/mallocTracer.cpp]
source: malloc-arena-detection/find-hook-global-cas
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


On every intercepted allocation while running, `MallocTracer::maybeRecord` acquires the `ProfiledThread`, enters a
`CriticalSection`, then `shouldSample()` runs a CAS loop on the global `_bytes_until_sample`. Under many threads
doing small mallocs, all threads write one cache line, so the unsampled cost grows with thread count. Running
nativemem always-on with a sparse interval is therefore not cheap as implemented. Fix direction (PROF-16349):
per-thread countdown in `ProfiledThread`, as HotSpot's `ThreadHeapSampler` does; statistically equivalent because
per-thread Poisson sampling is independent and memoryless.
