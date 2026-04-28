---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-28 13:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#110145046](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110145046) | ❓ | main | - |
| [Benchmarks](benchmarks/) | - | - | - | - |
| [Reliability](reliability/) | - | - | - | - |

---

## Test Types

### Integration Tests
dd-trace-java compatibility tests verifying profiler works correctly with the Datadog tracer.
Tests run on every main branch build across multiple JDK versions and platforms.

### Benchmarks
Performance regression testing using Renaissance benchmark suite.
Compares profiler overhead against baseline (no profiling).

### Reliability Tests
Long-running stability tests checking for memory leaks and crashes.
Tests multiple allocator configurations (gmalloc, tcmalloc, jemalloc).

---

## Recent Runs (All Types)

| Date | Type | Pipeline | Branch | PR | Status |
|------|------|----------|--------|-----|--------|
| 2026-04-28 | Integration | [#110145046](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110145046) | main | - | ❓ |
| 2026-04-28 | Integration | [#110138110](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110138110) | main | - | ✅ |
| 2026-04-28 | Integration | [#110110935](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110110935) | main | - | ✅ |
| 2026-04-27 | Integration | [#110025423](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110025423) | main | - | ⚠️ |
| 2026-04-27 | Integration | [#110020727](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110020727) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
