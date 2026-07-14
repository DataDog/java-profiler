---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-14 09:47 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124486827](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124486827) | ❌ | main | - |
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
| 2026-07-14 | Integration | [#124486827](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124486827) | main | - | ❌ |
| 2026-07-14 | Integration | [#124484404](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124484404) | main | - | ❌ |
| 2026-07-14 | Integration | [#124480748](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124480748) | main | - | ❌ |
| 2026-07-14 | Integration | [#124399885](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124399885) | main | - | ❌ |
| 2026-07-14 | Integration | [#124463894](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124463894) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
