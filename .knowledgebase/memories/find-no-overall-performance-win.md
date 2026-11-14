---
id: find-no-overall-performance-win
title: Targeted reference-chain allocation reductions showed no overall CPU or RSS win
kind: finding
tags: [reference-chains, performance, allocation, limits]
applies_to: []
source: refchain-allocation-fixes/find-no-overall-performance-win
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


Matched clean runs (same workload, fixed pre-touched heap, n=3 per arm) showed overlapping CPU and growth-end RSS means across baseline, fanout-fix, batch-fix and combined arms: neither an overall win nor a regression is proven. Specific node reductions are real but demonstrated by regression tests and site-attributed allocation traces, not by RSS.

JVM-owned tag/field-map/heap-walk allocations may dominate feature cost. Cumulative allocator requests are not resident memory or an exact fragmentation measure. Do not promise a production memory reduction from these fixes; multi-hour stability, other JVM vendors and rollout stay outside the verified scope.
