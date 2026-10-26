---
id: glibc-mallinfo-cost
title: mallinfo2() and malloc_info() lock each arena and walk all its free chunks; use them at JFR-chunk cadence only
kind: finding
tags: [glibc, mallinfo, cost, locking]
applies_to: [ddprof-lib/src/main/cpp/flightRecorder.cpp]
source: malloc-arena-detection/find-mallinfo-cost
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


`int_mallinfo` walks every fastbin and regular-bin chunk of an arena (2.39 `malloc.c:5261-5300`), so the cost
is O(free chunks). `__libc_mallinfo2` visits arenas one after another and holds each arena's mutex for that
arena's whole walk; allocating threads of that arena stall meanwhile. `malloc_info()` does the same walk plus the
heap chain and writes XML through stdio. `mallinfo2` exists since glibc 2.33. Neither gives an arena count.

Field semantics (easy to get wrong): `arena` = sum of `system_mem` over ALL arenas (not brk only); `keepcost` =
top chunk of `main_arena` only; `fordblks` = free bytes held in all arenas (including the unused top space).
Acceptable once per JFR chunk on the flush path; never from a signal handler or at higher frequency.
