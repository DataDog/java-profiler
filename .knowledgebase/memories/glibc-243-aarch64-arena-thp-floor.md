---
id: glibc-243-aarch64-arena-thp-floor
title: glibc 2.43 on aarch64 sizes every arena heap in 2 MiB THP units; with THP madvise each arena costs at least 2 MiB RSS
kind: finding
tags: [glibc-2.43, aarch64, thp, arena, rss, jvm]
applies_to: []
source: malloc-arena-detection/find-aarch64-243-thp-floor
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


glibc 2.43 defines `DEFAULT_THP_PAGESIZE` = 2 MiB for aarch64 (`sysdeps/unix/sysv/linux/aarch64/malloc-hugepages.h:19`)
and sets `thp_pagesize` "even if thp_mode is never" (`malloc.c:1912-1915`); `new_heap` sizes heaps in that unit
(`arena.c:446`). With kernel THP mode `madvise`, glibc advises huge pages, so each arena is at least 2 MiB resident
even when a thread uses a few KiB. x86_64 and generic builds default to 0; glibc 2.42 lacks this code.

Measured in JVMs (Temurin 8/17/21 on Ubuntu glibc 2.43, aarch64): every non-main arena = 2048 KiB committed and
resident; idle JVMs held 26-68 MiB in arenas with < 4 MiB in use. `MALLOC_ARENA_MAX=8` cut JVM RSS from 87 to
35 MiB (idle JDK 8) and from 171 to 96 MiB (JDK 21 under HTTP load).
