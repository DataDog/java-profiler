---
id: dead-end-cross-thread-free
title: Cross-thread free (producer/consumer) is not a driver of glibc arena blowup; no free hook is needed to detect it
kind: dead-end
tags: [glibc, free, tcache, arena]
applies_to: []
source: malloc-arena-detection/hyp-cross-thread-free
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


A chunk freed by a thread other than its allocator goes into the freeing thread's tcache (7 per bin), otherwise
back to the OWNING arena (fastbin via CAS or under that arena's lock; 2.39 `malloc.c:4547-4549`, `4621`,
`4640-4646`). The memory returns to the arena it came from and is reused there. Extra retention is bounded
(tcache, fastbins blocking coalescing). The blowup driver is arena count x per-arena peak plus non-trimming.
