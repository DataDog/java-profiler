---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-13 18:07 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124376289](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124376289) | ❌ | main | - |
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
| 2026-07-13 | Integration | [#124376289](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124376289) | main | - | ❌ |
| 2026-07-13 | Integration | [#124368946](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124368946) | main | - | ❌ |
| 2026-07-13 | Integration | [#124365893](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124365893) | main | - | ❌ |
| 2026-07-13 | Integration | [#124361624](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124361624) | main | - | ❌ |
| 2026-07-13 | Integration | [#124353863](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124353863) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
