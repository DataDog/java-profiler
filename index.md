---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-21 09:40 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125894248](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125894248) | ❌ | main | - |
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
| 2026-07-21 | Integration | [#125894248](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125894248) | main | - | ❌ |
| 2026-07-21 | Integration | [#125894149](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125894149) | main | - | ❌ |
| 2026-07-21 | Integration | [#125893746](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125893746) | main | - | ❌ |
| 2026-07-21 | Integration | [#125885430](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125885430) | main | - | ❌ |
| 2026-07-21 | Integration | [#125883995](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125883995) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
