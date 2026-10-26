---
id: dead-end-free-ratio-arena-signal
title: The free-held ratio (fordblks / arena) does not identify glibc arena blowup; use absolute free-held bytes
kind: dead-end
tags: [glibc, mallinfo, detection, arena]
applies_to: []
source: malloc-arena-detection/find-detection-signature
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


After the frees, the ratio of free to committed arena bytes is about 100% both with the default arena limit and
with a quota-aware `MALLOC_ARENA_MAX`, so a ratio threshold cannot separate the pathological case from a healthy
one. What differs is the absolute amount: the default limit held 3.7-9x more bytes. Committed bytes also mislead,
because they include in-use memory that fewer arenas do not reclaim; free-held bytes (`mallinfo2().fordblks`) are
the reclaimable part.
