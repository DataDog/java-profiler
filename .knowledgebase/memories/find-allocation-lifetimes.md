---
id: find-allocation-lifetimes
title: Reference-chain collector has four distinct allocation lifetime classes - batch, search, recording and process
kind: finding
tags: [reference-chains, allocation, ownership, lifetime]
applies_to: [ddprof-lib/src/main/cpp/referenceChainFrontier.h]
source: refchain-fragmentation/find-allocation-lifetimes
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


- Batch: expandFrontier creates per-invocation unordered sets (cleared per batch), a candidate-tag vector, a live tag-to-jobject map per batch and possibly a truncation-requeue vector; the completion set is filled from heap-walk callbacks on the VM thread and cleared on the BFS caller.
- Search: restartSearch clears search-specific containers; the frontier table itself is a contiguous calloc/realloc array of fixed-size records whose backing array survives resetForRestart without freeing - a retained frontier after stop/restart is not by itself evidence of fragmentation or a leak.
- Recording: class-signature resolution per pass (GetLoadedClasses each pass, signatures only for unresolved mappings) has its own lifetime.
- Process: node-based class caches and JVM-internal storage live for the process.

Consequences: do not treat every frontier admission as a distinct profiler malloc; do not infer fragmentation from a large retained frontier allocation or from the presence of unordered containers. Measure allocation stacks, requested sizes, live bytes and allocating threads during verified active searches.
