---
id: hyp-mallinfo-poll
title: mallinfo2() polling from a profiler thread is cheap enough for always-on arena-bloat detection
kind: finding
tags: [glibc, mallinfo, always-on]
applies_to: []
source: malloc-arena-detection/hyp-mallinfo-poll
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# mallinfo2() polling from a profiler thread is cheap enough for always-on arena-bloat detection

## Reasoning chain
mallinfo2 reports arena/fordblks/hblkhd aggregated over all arenas. If its cost is O(arenas) and lock hold times are short, a periodic (e.g. 60s) poll gives total arena footprint and free-but-retained bytes (fordblks) = fragmentation signal. Risk: int_mallinfo may walk every bin chunk list under the arena lock -> O(free chunks) and stalls allocating threads.

## Evidence
- glibc 2.39 malloc.c:5261-5300 int_mallinfo walks every fastbin and bin chunk -> O(free chunks); __libc_mallinfo2 (5325) locks each arena in turn for its whole walk. Added 2.33.
- malloc_info (5813) same + heap chain; malloc_stats fprintf under lock.
- Caveat: cheap enough at JFR-chunk cadence only; stalls allocating threads of the arena during the walk, worst exactly when fragmentation is high. See find-mallinfo-snapshot-dead-in-release: currently compiled out in release.

## What this rules out
- Higher-frequency polling of mallinfo2/malloc_info.
- mallinfo gives no arena count; per-arena view needs malloc_info (XML, stdio) or hyp-arena-list-walk.
