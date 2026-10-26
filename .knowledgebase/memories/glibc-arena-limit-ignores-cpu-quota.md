---
id: glibc-arena-limit-ignores-cpu-quota
title: glibc's malloc arena limit is 8 x online CPUs and ignores the container CPU quota
kind: finding
tags: [glibc, malloc, arena, container, cgroup]
applies_to: []
source: malloc-arena-detection/find-arena-limit-ignores-cgroup
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


glibc gives each thread its own malloc arena until the arena limit is reached. On 64-bit the limit is
8 x `__get_nprocs()`, fixed once after the first 8 arenas exist (glibc 2.17 `malloc/arena.c:848`, 2.28 `:888`,
2.39 `:834`). `__get_nprocs()` reads the online CPUs (`/sys/devices/system/cpu/online`), so it ignores the cgroup
CPU quota. glibc 2.35-2.38 used the affinity mask instead (cpuset, still not the quota); 2.39 reverted that.

Consequence: a container with a 2-CPU quota on a 16-CPU host keeps a limit of 128 arenas; measured, 256 threads
created 128 arenas under `--cpus=2`. glibc never frees arenas; an exited thread's arena goes to a reuse list.

Override: `MALLOC_ARENA_MAX=N` or `GLIBC_TUNABLES=glibc.malloc.arena_max=N`. With N = 8 x quota CPUs, a
256-thread small-allocation workload retained 4-9x less memory than with the default limit.
