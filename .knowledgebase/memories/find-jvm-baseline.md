---
id: find-jvm-baseline
title: JVM baseline: arena count ~= thread count, so condition 1 never filters; on aarch64 glibc 2.43 the warnings are true positives (MALLOC_ARENA_MAX=8 cuts JVM RSS 44-60%)
kind: finding
tags: [jvm, validation, baseline, arena, rule]
applies_to: []
source: malloc-arena-detection/find-jvm-baseline
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# JVM baseline: arena count ~= thread count, so condition 1 never filters; on aarch64 glibc 2.43 the warnings are true positives (MALLOC_ARENA_MAX=8 cuts JVM RSS 44-60%)

## Reasoning chain
Probe: build/arena-repro/jvm/arena_preload.c (LD_PRELOAD sampler reusing the walk; maxHeap passed via env), Workloads.java
(idle / http: HttpServer pool 16 + 16 clients / deflate: 64 threads using java.util.zip.Deflater), run_jvm.sh.
Matrix: Temurin 8/17/21 (Ubuntu GLIBC 2.43), arm64 native, container 512 MiB, -Xmx384m (headroom 128 MiB, P=25% -> 32 MiB),
quotas 1/2/4. 27 runs, walk ok in every sample (layout 3, 2.43).
- Arenas ~= threads: idle 14 (JDK21), 15 (JDK17), 34 (JDK8); http 49-69; deflate 78-98. Condition 1
  (arenas > 8 x quota) was true in every run except idle JDK17/21 at quota 2/4 -> condition 1 does not filter JVMs;
  condition 2 decides.
- aarch64 committed (= free-held, = resident) arena bytes: idle 26-68 MiB, http 116-180, deflate 156-196. Rule fired on
  all JDK8 runs and all http/deflate runs; silent on idle JDK17/21 (25-30 MiB < 32).
- Remedy test (quota 1): JDK8 idle default 34 arenas, arena RSS 66 MiB, VmRSS 87 MiB -> MALLOC_ARENA_MAX=8: 8 arenas,
  arena RSS 14, VmRSS 35 (-60%). JDK21 http default 49 arenas, arena RSS 96, VmRSS 171 -> ARENA_MAX=8: arena RSS 14,
  VmRSS 96 (-44%). Warnings flipped to 0 with the remedy -> the default-config warnings were true positives.
- x86_64 (qemu-emulated, system_mem only; smaps RSS not emulated): idle 2.4-5.5 MiB committed; http JDK21 22.8 MiB
  (free 6.6), JDK8 46.7 MiB (free 26.5) -> committed criterion fires on JDK8 http, free-held criterion does not.

## Evidence
- build/arena-repro/jvm/results/jdk*-q*-*.txt, summarize_jvm.py (worktree start-cairn-investigation, gitignored).

## What this rules out
- Fear that the rule mostly flags healthy JVMs: on aarch64/2.43 the flagged memory is real RSS and reclaimable.
- Committed bytes as condition 2: it includes in-use bytes that fewer arenas do not reclaim -> use free-held
  (mallinfo2 fordblks) when available; fall back to committed only without mallinfo2.
- Residual: x86_64 RSS not measured natively (emulator); x86_64 native check would close it.
