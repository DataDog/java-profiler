---
id: glibc-pointer-to-arena
title: A pointer returned by glibc malloc maps to its arena without locks: check IS_MMAPPED, then NON_MAIN_ARENA, then read heap_info->ar_ptr
kind: finding
tags: [glibc, malloc, arena, attribution]
applies_to: []
source: malloc-arena-detection/find-ptr-to-arena
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


The size word at `p - 8` carries `IS_MMAPPED` (0x2) and `NON_MAIN_ARENA` (0x4). Check `IS_MMAPPED` first:
mmapped chunks carry no arena bit. For a non-main chunk, `heap_info` sits at `p & ~(HEAP_MAX_SIZE - 1)` and its
first field `ar_ptr` is the arena (true in 2.17 through 2.43). `HEAP_MAX_SIZE` is 64 MiB on 64-bit, but
`glibc.malloc.hugetlb >= 2` (2.35+) changes it to 4 x the huge page size. Strip the MTE tag on aarch64.
Main-arena chunks give no address (`main_arena` and `narenas` are static, not exported).
