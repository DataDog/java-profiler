---
id: find-arena-walk-safe
title: The glibc arena list can be walked lock-free from any arena and self-validated via the (mstate)(heap_info+1) placement invariant
kind: finding
tags: [glibc, arena, malloc_state]
applies_to: []
source: malloc-arena-detection/find-arena-walk-safe
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# The glibc arena list can be walked lock-free from any arena and self-validated via the (mstate)(heap_info+1) placement invariant

## Reasoning chain
next list circular, append-only, published after atomic_write_barrier; arenas never freed. Offsets: 2.17 next 2152/system_mem 2168/max 2176; 2.23-2.26 next 2152/attached 2168/system_mem 2176/max 2184; 2.27+ next 2160/attached 2176/system_mem 2184/max 2192 (x86_64 == aarch64). Non-main arena a satisfies (a & (HEAP_MAX-1)) == sizeof(heap_info) and heap_info->ar_ptr == a; exactly main_arena fails.

## Evidence
- Full derivation and citations in hyp-arena-list-walk and evidence/ev-glibc-source-answers.md.

## What this rules out
- See hyp-arena-list-walk.
