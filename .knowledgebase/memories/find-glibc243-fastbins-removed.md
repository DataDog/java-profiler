---
id: find-glibc243-fastbins-removed
title: glibc 2.43 removed fastbins from malloc_state: a fourth layout (next 2072, attached 2088, system_mem 2096, max 2104)
kind: finding
tags: [glibc, malloc_state, layout, calibration, glibc-2.43]
applies_to: []
source: malloc-arena-detection/find-glibc243-fastbins-removed
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# glibc 2.43 removed fastbins from malloc_state: a fourth layout (next 2072, attached 2088, system_mem 2096, max 2104)

## Reasoning chain
The JVM baseline check used eclipse-temurin:21-jdk, which now ships Ubuntu GLIBC 2.43-2ubuntu2.4. The walk failed
with `implausible` under all three known layouts: system_mem read 0 on the seed arena itself. The detector disabled
itself safely. glibc-2.43 malloc/malloc.c:1722-1759: struct malloc_state = mutex, flags, top, last_remainder,
bins[254], binmap[4], next, next_free, attached_threads, system_mem, max_system_mem — no fastbinsY, no
have_fastchunks. glibc-2.41 and 2.42 still contain fastbinsY (raw source grep), so the change landed in 2.43.
heap_info unchanged (pagesize field, 48 bytes; arena.c:74-78) and `a = h->ar_ptr = (mstate)(h + 1)` still holds
(arena.c:639), so the structural check is unaffected.
Added candidate {2072, 2088, 2096, 2104}, preferred for >= 2.43. Reproducer on glibc 2.43 arm64 (T=64): layout=3,
walk_count 66 == malloc_info 66, all system_mem identical (max_diff 0).

## Evidence
- build/arena-repro/arena_repro.c g_candidates[3]; JVM debug output `DEBUG cand=0..2 fail=implausible at=0 sys=0`.

## What this rules out
- Treating the candidate list as closed: any glibc release can change malloc_state. The detector must fail
  closed (no warning, walkStatus reason in the stats event), and new layouts need a candidate plus a
  malloc_info-backed test per supported distro image. Strengthens the case for a CI check that runs the walk
  against malloc_info on current distro images.
