---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-08 15:42 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#117668262](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117668262) | ❌ | main | - |
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
| 2026-06-08 | Integration | [#117668262](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117668262) | main | - | ❌ |
| 2026-06-08 | Integration | [#117661036](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117661036) | main | - | ❌ |
| 2026-06-08 | Integration | [#117659996](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117659996) | main | - | ❌ |
| 2026-06-08 | Integration | [#117636526](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117636526) | main | - | ❌ |
| 2026-06-08 | Integration | [#117636471](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117636471) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
