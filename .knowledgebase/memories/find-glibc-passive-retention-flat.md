---
id: find-glibc-passive-retention-flat
title: no passive glibc signal distinguishes retained from releasable memory - a retention check needs an actual release step
kind: finding
tags: [glibc, malloc, retention, rss, smaps, memory-gate, testing]
applies_to: [.gitlab/reliability/memory_trend_check.sh]
source: native-safety-hypothesis-loop/find-glibc-passive-retention-flat
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


Pre-release RSS, mincore and `smaps` `Private_Dirty` stay within 0.2 percent
across the whole allocation-pattern matrix on glibc 2.35 and 2.39 at equal live
bytes, and a field-by-field sweep of every `smaps` field (both libcs, to 0.1
percent) is equally flat: `MADV_DONTNEED` zeroes everything and `MADV_FREE`
moves `LazyFree` only after a real release. There is no passive glibc signal
that separates retained from releasable memory, so any gate must exercise the
release itself - a harness-issued `malloc_trim`/`madvise` from outside the
profiler, with RSS recorded before and after. musl post-free RSS does
discriminate. The mallinfo2-stall side of the original finding is glibc-version
dependent (no stall on 2.35, 3-17 ms stalls on 2.39); treat any mallinfo2 timing
claim as version-scoped.
