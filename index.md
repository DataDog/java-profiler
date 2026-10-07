---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-07 15:19 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#143086471](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143086471) | ✅ | main | - |
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
| 2026-10-07 | Integration | [#143086471](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143086471) | main | - | ✅ |
| 2026-10-07 | Integration | [#143073779](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143073779) | main | - | ⚠️ |
| 2026-10-07 | Integration | [#143064835](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143064835) | main | - | ✅ |
| 2026-10-07 | Integration | [#143018913](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143018913) | main | - | ✅ |
| 2026-10-07 | Integration | [#143008521](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143008521) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
