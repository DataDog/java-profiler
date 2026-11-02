---
id: find-repro-arm64-results
title: Reproducer (arm64, glibc 2.17-el7/2.28/2.39): walk == malloc_info exactly; arenas = min(threads+2, 8*online CPUs) even under a 2-CPU quota; freed memory stays held
kind: finding
tags: [reproducer, arena, measurement, arm64]
applies_to: []
source: malloc-arena-detection/find-repro-arm64-results
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Reproducer (arm64, glibc 2.17-el7/2.28/2.39): walk == malloc_info exactly; arenas = min(threads+2, 8*online CPUs) even under a 2-CPU quota; freed memory stays held

## Reasoning chain
Workload: T threads, 8 MiB each of 16..1024 B mallocs, free all but every 8th, barrier, probe ("retained"),
free rest, join, probe ("threads-exited"). Probe thread owns the seed arena (adds 1 arena; main adds 1).
- Walk: ok on all 72 results; count and per-arena system_mem identical to malloc_info (N/N, max_diff 0);
  sum_sys == mallinfo2.arena on 2.39.
- Default limit 128 (16 online CPUs). quota2_default (podman --cpus=2, cpu.max 200000/100000) still 128 arenas
  -> glibc ignores the CPU quota (empirical confirmation of find-arena-limit-ignores-cgroup).
- Retention after all memory freed and all threads exited (sum_sys MiB / RSS MiB), T=256:
  default ~1152-1186 / ~1169-1204 on all three; MALLOC_ARENA_MAX=2: 95-299 / 113-316;
  quota2 + MALLOC_ARENA_MAX=16 (8 x quota): 132-313 / 149-330. In-use after exit ~0 (2.39 mi2).
- Default footprint scales linearly: T=4 33 MiB, 16 132, 64 528, 256 ~1170 (capped by 128 arenas).
- Per-arena max_sys ~8-16 MiB default vs 100-600 MiB with 2 arenas (shared); max_attached 1 default
  (thread-private) vs 33-155 when shared (during retained phase).
- In the "retained" phase (1/8 live, pinned) shared arenas do NOT help much (e.g. 2.39 T=256: 1224 vs 1083 MiB):
  the win is reuse after frees, not fragmentation.

## Evidence
- build/arena-repro/results/*-arm64.txt (worktree start-cairn-investigation, gitignored); summarize.py.
- Podman gotcha: remote client queries all credHelpers (ddtool) even for docker.io; run with
  DOCKER_CONFIG/REGISTRY_AUTH_FILE pointing at an empty {} config; use fully qualified image names.

## What this rules out
- Doubt that the walk reads the same values glibc reports (exact match).
- amd64 (qemu-emulated) matrix: walk ok in 72/72; malloc_info match N/N in 71/72. One OL7 quota2 threads-exited
  run had 127/128 (one arena differed 8.1 MiB); 3 reruns matched 128/128 -> transient race between the two
  non-atomic reads (malloc_info first, walk second), not reproduced. Same retention pattern: T=256 default
  872-1047 MiB sum_sys vs quota2+ARENA_MAX=16 107-193 MiB. RSS under qemu is inflated by the emulator and not used.
