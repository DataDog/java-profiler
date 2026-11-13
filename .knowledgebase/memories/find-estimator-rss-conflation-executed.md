---
id: find-estimator-rss-conflation-executed
title: per-object allocation estimates cannot gate attributable RSS - same estimate, 2x measured residency
kind: finding
tags: [malloc, rss, estimator, mallocfootprint, memory-gate]
applies_to: [ddprof-lib/src/main/cpp/mallocFootprint.h]
source: native-safety-hypothesis-loop/find-estimator-rss-conflation-executed
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


With the requested/usable estimates held fixed, measured residency at 8192 B
differs by 2x between glibc and musl while `MallocFootprint` returns identical
values for both: the estimator is blind to occupancy and touching. Any memory
gate must state its accounting target - per-object allocator accounting (usable
size plus the probed header) for allocation cost, residency measurements for
attributable memory - and never equate the two.
