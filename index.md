---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-22 15:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#126271866](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126271866) | ❌ | main | - |
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
| 2026-07-22 | Integration | [#126271866](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126271866) | main | - | ❌ |
| 2026-07-22 | Integration | [#126270792](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126270792) | main | - | ❌ |
| 2026-07-22 | Integration | [#126270463](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126270463) | main | - | ❌ |
| 2026-07-22 | Integration | [#126266275](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126266275) | main | - | ❌ |
| 2026-07-22 | Integration | [#126264498](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126264498) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
