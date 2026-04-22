---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-22 18:03 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#109124365](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109124365) | ✅ | main | - |
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
| 2026-04-22 | Integration | [#109124365](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109124365) | main | - | ✅ |
| 2026-04-22 | Integration | [#109124547](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109124547) | main | - | ✅ |
| 2026-04-22 | Integration | [#109124455](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109124455) | main | - | ✅ |
| 2026-04-22 | Integration | [#109117382](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109117382) | main | - | ✅ |
| 2026-04-22 | Integration | [#109114930](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109114930) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
