---
id: hyp-ptr-arena-attribution
title: The owning arena of a sampled malloc result can be derived lock-free from the pointer (NON_MAIN_ARENA bit + 64MB-aligned heap_info->ar_ptr)
kind: finding
tags: [glibc, arena, nativemem, attribution]
applies_to: []
source: malloc-arena-detection/hyp-ptr-arena-attribution
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# The owning arena of a sampled malloc result can be derived lock-free from the pointer (NON_MAIN_ARENA bit + 64MB-aligned heap_info->ar_ptr)

## Reasoning chain
glibc chunk header at ptr-8 has bit 0x4 NON_MAIN_ARENA; for such chunks heap_info sits at ptr & ~(HEAP_MAX_SIZE-1) and its first field ar_ptr is the arena. Reading both right after malloc returned is memory-safe. Gives thread->arena mapping and distinct-arena count from samples without any glibc lock. Risk: layout is glibc-internal (version drift), HEAP_MAX_SIZE differs (64MB on 64-bit, configurable via tunables?).

## Evidence
- heap_info.ar_ptr is the first field in 2.17/2.28/2.39; HEAP_MAX_SIZE=64MiB on 64-bit (arena.c:30, malloc.c:957); bits IS_MMAPPED 0x2, NON_MAIN_ARENA 0x4.
- Conditions: check IS_MMAPPED first (mmapped chunks carry no arena bit, malloc.c:2467); in 2.35+ with glibc.malloc.hugetlb>=2 HEAP_MAX_SIZE = 4x hugepage size (arena.c:53-56); strip MTE tag on aarch64.
- Main-arena chunks yield no address (main_arena static, malloc.c:1906).

## What this rules out
- Need for any glibc lock to attribute a sampled pointer to an arena.
