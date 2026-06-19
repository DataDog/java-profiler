---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-19 16:34 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#119989907](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119989907) | ❌ | main | - |
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
| 2026-06-19 | Integration | [#119989907](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119989907) | main | - | ❌ |
| 2026-06-19 | Integration | [#119978806](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119978806) | main | - | ❌ |
| 2026-06-19 | Integration | [#119968351](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119968351) | main | - | ❌ |
| 2026-06-19 | Integration | [#119950918](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119950918) | main | - | ❌ |
| 2026-06-19 | Integration | [#119950754](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119950754) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
