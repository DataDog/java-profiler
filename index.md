---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-14 17:51 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124590044](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124590044) | ❌ | main | - |
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
| 2026-07-14 | Integration | [#124590044](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124590044) | main | - | ❌ |
| 2026-07-14 | Integration | [#124574049](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124574049) | main | - | ❌ |
| 2026-07-14 | Integration | [#124569193](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124569193) | main | - | ❌ |
| 2026-07-14 | Integration | [#124564011](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124564011) | main | - | ❌ |
| 2026-07-14 | Integration | [#124557487](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124557487) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
