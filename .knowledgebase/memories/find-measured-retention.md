---
id: find-measured-retention
title: Active reference-chain collector adds ~18 MiB RSS in matched short runs; not all of it is fragmentation
kind: finding
tags: [reference-chains, fragmentation, experiment, retention]
applies_to: [ddprof-lib/src/main/cpp/referenceChainTraversal.cpp:expandFrontier]
source: refchain-fragmentation/find-measured-retention
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


Matched fresh-process experiments (HotSpot 21, glibc 2.39, fixed pre-touched G1 heap, identical dumps; n=3 per arm): collector-on added ~18 MiB growth-end RSS (619.9-621.0 vs 602.2-602.9 MiB), with both arms holding substantial allocator-free memory. Collector-on added one observed arena, but a diagnostic two-arena cap left a similar gap - arena count alone is not the explanation. A 240-round run showed a short on-arm RSS plateau (~630.5 MiB) while application objects kept growing - not proof of long-run boundedness.

Accounting traps: mallinfo2's uordblks is not requested live bytes (it counts system_mem minus free bins, including metadata and tcache-hidden chunks; hblkhd is separate mmap space). malloc_trim(0) after stop reclaimed ~9-10 MiB on vs ~6 MiB off - reclaimable residency exists in both arms; whole-page advice is possible inside arena free chunks (mtrim). A diagnostic trim is not a production recommendation.

Frontier counters reset on later starts while the retained table is not reallocated - do not read a zeroed counter as zero capacity or an idle search.
