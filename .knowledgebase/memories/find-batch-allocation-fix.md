---
id: find-batch-allocation-fix
title: Bounded per-batch scratch removes the batch containers' per-admission allocations
kind: finding
tags: [reference-chains, allocation, batch]
applies_to: [ddprof-lib/src/main/cpp/referenceChainTraversal.cpp, ddprof-lib/src/main/cpp/referenceChains.h]
source: refchain-allocation-fixes/find-batch-allocation-fix
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


Giving the batch machinery bounded, pre-reserved scratch (membership set, live map, completion set) removes their per-admission node and bucket allocations entirely: allocation traces showed zero targeted nodes where the unbounded variant allocated tens of thousands per traced run. The independent batch-only variant admitted ~2.3 percent more edges than baseline, within the agreed work gate.

The approved per-batch reset also fixes stale-completion consumption after a later JNI setup failure. Measured tracker instance size grows by the reserved scratch (tens of KiB), traded against unbounded node churn; x64 stack frames shrink.

Limits: allocator-request bytes are not RSS; no overall CPU/RSS win was demonstrated (matched clean runs overlapped); JVM-owned tag/field-map/heap-walk allocations remain.
