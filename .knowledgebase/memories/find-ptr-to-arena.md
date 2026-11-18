---
id: find-ptr-to-arena
title: A malloc'd pointer maps to its arena lock-free: skip IS_MMAPPED, then NON_MAIN_ARENA -> heap_info at 64MiB-aligned base, ar_ptr first field
kind: finding
tags: [glibc, arena, attribution]
applies_to: []
source: malloc-arena-detection/find-ptr-to-arena
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# A malloc'd pointer maps to its arena lock-free: skip IS_MMAPPED, then NON_MAIN_ARENA -> heap_info at 64MiB-aligned base, ar_ptr first field

## Reasoning chain
Valid on 2.17/2.28/2.39. Check IS_MMAPPED (0x2) first; NON_MAIN_ARENA (0x4) then heap_info = p & ~(HEAP_MAX_SIZE-1), ar_ptr at offset 0. HEAP_MAX_SIZE = 64MiB on 64-bit, 4x hugepage with glibc.malloc.hugetlb>=2 (2.35+). Strip MTE tag on aarch64. Main-arena chunks give no address.

## Evidence
- Full derivation and citations in hyp-ptr-arena-attribution and evidence/ev-glibc-source-answers.md.

## What this rules out
- See hyp-ptr-arena-attribution.
