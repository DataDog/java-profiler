---
id: hyp-arena-list-walk
title: Walking the circular malloc_state->next list from one known arena yields arena count and per-arena system_mem/attached_threads lock-free
kind: finding
tags: [glibc, arena, malloc_state, always-on]
applies_to: []
source: malloc-arena-detection/hyp-arena-list-walk
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Walking the circular malloc_state->next list from one known arena yields arena count and per-arena system_mem/attached_threads lock-free

## Reasoning chain
mallinfo2 gives only process totals. The arena-blowup signature is per-arena: many arenas, each holding
system_mem far above its in-use share. struct malloc_state carries next, attached_threads, system_mem,
max_system_mem. If arenas are never freed and `next` is published with a barrier, a profiler thread can:
(1) malloc() once on its own (non-main) thread, (2) derive its arena via heap_info->ar_ptr
(hyp-ptr-arena-attribution), (3) walk ->next until it returns, reading word-sized fields racily.
O(narenas) (<= 8*ncores), no locks, no hooks, no nativemem. Risk: field offsets are glibc-version
specific; need validation (circularity, plausible values) and a version table.

## Evidence
- `next` list circular from main_arena, append-only: new arenas inserted after main_arena under list_lock with atomic_write_barrier before publication (2.39 arena.c:669-676; dmb ish on aarch64). Arena structs never freed (first heap never matches heap_trim unmap, arena.c:545,649). -> lock-free walk memory-safe; use acquire loads, values racy.
- system_mem updated on every grow/shrink (malloc.c:2619/2628/2746/2790/2877/3012, arena.c:563/603); committed span, not RSS (madvised interior pages still counted).
- Offsets (x86_64 == aarch64), mutex is int, NFASTBINS=10, NBINS=128, BINMAPSIZE=4:
  2.17: next 2152, system_mem 2168, max_system_mem 2176 (no attached_threads)
  2.23-2.26: next 2152, attached_threads 2168, system_mem 2176, max 2184 (hand-computed)
  2.27+: next 2160, attached_threads 2176, system_mem 2184, max 2192 (clang-computed, 2.28/2.39)
- Self-validation (all versions): `a = h->ar_ptr = (mstate)(h+1)` — 2.17 arena.c:730, 2.28:703, 2.39:649. Every non-main node satisfies ((uintptr)a & (HEAP_MAX_SIZE-1)) == sizeof(heap_info) (32 pre-2.35, 48 2.35+) AND heap_info->ar_ptr == a. Exactly one node fails it: main_arena (static in libc .data/.bss).
- Seed: any arena pointer works (list is circular); a profiler thread's own malloc usually yields a non-main arena; if it lands in main_arena (reused_arena past limit, arena.c:763-770), retry — round-robin advances.
- Full source: evidence/ev-glibc-source-answers.md Q2, Q3, Q8.

## What this rules out
- Need for mallinfo/malloc_info locks to obtain arena COUNT, per-arena committed bytes and attached threads.
- Residual risks: unsupported internal layout (distro backports UNVERIFIED, e.g. RHEL7 2.17); hugetlb tunable changes HEAP_MAX_SIZE (try both masks or read tunable); misread offsets beyond `next` are not caught by the structural check -> add plausibility (page-multiple, <= heaps*HEAP_MAX) and read via SafeAccess. Per-arena IN-USE bytes are not available without walking bins.
