---
id: hyp-static-risk-score
title: A static risk score from cores, live thread count and effective arena_max predicts worst-case arena footprint cheaply
kind: finding
tags: [glibc, arena_max, config, always-on]
applies_to: []
source: malloc-arena-detection/hyp-static-risk-score
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# A static risk score from cores, live thread count and effective arena_max predicts worst-case arena footprint cheaply

## Reasoning chain
Worst case retained ~= min(threads, arena_max) x per-arena heap peak. arena_max defaults to 8*cores on 64-bit unless MALLOC_ARENA_MAX / GLIBC_TUNABLES=glibc.malloc.arena_max set. Containers often see host cores -> huge limit. Reading env + cpu count + thread count is trivially cheap. Risk: no measure of actual usage, just potential.

## Evidence
- arena limit fixed once at 8 x ncores (64-bit) after the first 8 arenas (arena.c:822-842, malloc.c:1921-1922); MALLOC_ARENA_MAX = glibc.malloc.arena_max tunable (dl-tunables.list:58-67).
- ncores = __get_nprocs() = /sys/devices/system/cpu/online (2.39 arena.c:834): ignores cpuset AND cgroup CPU quota. 2.35-2.38 used __get_nprocs_sched (affinity: cpuset yes, quota no); reverted in 2.39 (BZ 30945).
- => a container with a 2-CPU quota on a 96-core host gets limit 768 arenas; each a 64MiB reservation whose committed part grows to per-arena peak and rarely shrinks.
- Arenas are never freed; exited threads' arenas go to free_list (arena.c:892).

## What this rules out
- Relying on container CPU limits to bound arena count.
- Limit: a potential, not usage; must be combined with an actual-usage signal (count/system_mem).
