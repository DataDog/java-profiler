---
id: find-aarch64-243-thp-floor
title: glibc 2.43 on aarch64 sizes every arena heap in 2 MiB THP units; with THP=madvise each arena costs >= 2 MiB RSS
kind: finding
tags: [glibc-2.43, aarch64, thp, arena, rss]
applies_to: []
source: malloc-arena-detection/find-aarch64-243-thp-floor
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# glibc 2.43 on aarch64 sizes every arena heap in 2 MiB THP units; with THP=madvise each arena costs >= 2 MiB RSS

## Reasoning chain
glibc 2.43 sysdeps/unix/sysv/linux/aarch64/malloc-hugepages.h:19 `#define DEFAULT_THP_PAGESIZE (1UL << 21)`;
malloc.c:1912-1915 sets mp_.thp_pagesize "even if thp_mode is never"; arena.c:446 new_heap uses thp_pagesize as the
heap page size; madvise_thp (malloc.c:1919-1927) advises huge pages when the kernel THP mode is madvise. Generic
sysdeps default is 0 (malloc-hugepages.h:44-45), so x86_64 is unaffected. glibc 2.42 source lacks this code.
Measured in the JVM probe (podman VM kernel THP `always [madvise] never`): every non-main arena system_mem = 2048 KiB,
and smaps RSS of the arena heaps == system_mem (idle JDK21: 26 MiB RSS for 13 arenas, 1.9 MiB in use).

## Evidence
- build/arena-repro/jvm DIST output (all non-main arenas 2048K), arena_rss_mib vs nonmain_mib.

## What this rules out
- Treating per-arena cost as negligible for idle threads on aarch64/2.43: N threads -> >= 2N MiB resident.
- The warning will fire broadly on aarch64 glibc 2.43 small containers; each firing is actionable (MALLOC_ARENA_MAX).
  With THP=never the 2 MiB is committed but not resident (not measured).
