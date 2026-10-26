---
id: glibc-arena-retention
title: glibc arenas keep freed memory: interior free chunks are never released and the heap top shrinks only above trim_threshold
kind: finding
tags: [glibc, malloc, arena, fragmentation, mmap-threshold]
applies_to: []
source: malloc-arena-detection/find-mmap-threshold-drift
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


- Each non-main arena reserves 64 MiB heaps (`HEAP_MAX_SIZE` = 2 x `DEFAULT_MMAP_THRESHOLD_MAX` on 64-bit). The
  committed part grows to the arena's peak.
- `free()` shrinks a non-main heap only from the top and only when the top chunk exceeds `trim_threshold`
  (2.39 `arena.c:545-606`); interior free chunks stay committed. `malloc_trim(0)` madvises interior free pages
  of every arena, but shrinks the top only for `main_arena` (2.39 `malloc.c:5198`).
- Dynamic mmap threshold: freeing an mmapped chunk larger than `mmap_threshold` (up to 32 MiB) raises
  `mmap_threshold` to that size and `trim_threshold` to 2x (2.39 `__libc_free`, `malloc.c:3379-3384`). Later
  allocations up to 32 MiB then land in arenas, and with `trim_threshold` at 64 MiB a heap top effectively
  never shrinks. Any explicit `mallopt`/tunable for these thresholds disables the dynamic behaviour.
- Result: retained arena memory ~= number of arenas x per-arena peak, even after all memory is freed and the
  threads have exited (measured: ~1.2 GiB held, ~0 in use, 256 threads).
