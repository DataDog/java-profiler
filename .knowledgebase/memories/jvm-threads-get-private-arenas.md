---
id: jvm-threads-get-private-arenas
title: In a JVM the glibc arena count is about the thread count, so 'arenas > 8 x quota CPUs' is true for almost every small-container JVM
kind: finding
tags: [jvm, glibc, arena, container]
applies_to: []
source: malloc-arena-detection/find-jvm-baseline
status: active
recorded: 2026-10-26
valid_at: 2026-10-26
---


JVM-internal threads (GC workers, JIT compilers, runtime threads) and application pools each get their own arena
until glibc's limit. Measured (Temurin 8/17/21): idle 14-34 arenas, HTTP server with clients 49-69, 64
`Deflater` threads 78-98; nearly all with `attached_threads == 1`. Any check of the form
`arena_count > 8 x ceil(quota CPUs)` therefore holds for almost every JVM at quotas of 1-4 CPUs; it indicates that
`MALLOC_ARENA_MAX` would take effect, not that memory is wasted. Judge the waste by bytes (free-held), not count.
