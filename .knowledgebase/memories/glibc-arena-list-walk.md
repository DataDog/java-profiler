---
id: glibc-arena-list-walk
title: The glibc arena list can be walked lock-free from any arena and self-validated with the (mstate)(heap_info + 1) placement invariant
kind: finding
tags: [glibc, malloc_state, arena, lock-free]
applies_to: []
source: malloc-arena-detection/find-arena-walk-safe
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


- `malloc_state->next` forms a circular list through `main_arena`. New arenas are inserted under `list_lock`
  and published after `atomic_write_barrier` (2.39 `arena.c:669-676`); arena structs are never freed. A walk
  with acquire loads is memory-safe; field values are racy snapshots.
- Every non-main arena is placed right after its first `heap_info`: `a = h->ar_ptr = (mstate)(h + 1)`
  (2.17 `arena.c:730`, 2.28 `:703`, 2.39 `:649`, 2.43 `:639`). So `(a & (HEAP_MAX_SIZE-1)) == sizeof(heap_info)`
  (32 before 2.35, 48 from 2.35) and `heap_info->ar_ptr == a`. Exactly one node fails this: `main_arena`.
- Per-arena `system_mem` (committed span, updated on every grow/shrink) and `attached_threads` (2.23+) read
  this way matched `malloc_info()` exactly on glibc 2.17 (EL7), 2.28, 2.39 and 2.43, aarch64 and x86_64.
- Seed: any arena pointer works (list is circular); a thread's own malloc usually yields a non-main arena, but
  past the arena limit `reused_arena` can hand out `main_arena`.
- Read through `SafeAccess`; recovery exists only on HotSpot and OpenJ9, so do not run such a walk on Zing.
