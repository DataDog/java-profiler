---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-13 10:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124272331](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124272331) | ❌ | main | - |
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
| 2026-07-13 | Integration | [#124272331](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124272331) | main | - | ❌ |
| 2026-07-13 | Integration | [#124272350](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124272350) | main | - | ❌ |
| 2026-07-13 | Integration | [#124272297](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124272297) | main | - | ❌ |
| 2026-07-13 | Integration | [#124268545](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124268545) | main | - | ❌ |
| 2026-07-13 | Integration | [#124266079](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124266079) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
