---
id: hyp-mmap-threshold-drift
title: Dynamic mmap threshold drift pushes large allocations into arenas and is detectable from sampled chunks lacking IS_MMAPPED
kind: finding
tags: [glibc, mmap-threshold, arena]
applies_to: []
source: malloc-arena-detection/hyp-mmap-threshold-drift
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Dynamic mmap threshold drift pushes large allocations into arenas and is detectable from sampled chunks lacking IS_MMAPPED

## Reasoning chain
glibc raises mmap_threshold up to DEFAULT_MMAP_THRESHOLD_MAX (32MB on 64-bit) whenever an mmapped chunk is freed. After that, 128K..32MB allocations are served from arenas, inflating heaps and making trimming harder. Sampled large allocation (size>=128K) whose header lacks IS_MMAPPED (0x2) is a direct, cheap drift signal.

## Evidence
- __libc_free malloc.c:3379-3384: on free of an mmapped chunk > mmap_threshold and <= DEFAULT_MMAP_THRESHOLD_MAX (32MiB): mmap_threshold = chunksize, trim_threshold = 2x. Disabled by any explicit mallopt/tunable (no_dyn_threshold, malloc.c:5421-5457).
- Amplifier: trim_threshold can reach 64MiB = HEAP_MAX_SIZE, so non-main heap tops are effectively never shrunk (arena.c:545-606).
- Detection needs sampled allocations (size >= 128KiB returned without IS_MMAPPED) -> depends on nativemem/PROF-16349; mp_ is static, not readable cheaply.

## What this rules out
- Assuming large allocations always bypass arenas.
