---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-28 15:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#148227441](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148227441) | ✅ | main | - |
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
| 2026-10-28 | Integration | [#148227441](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148227441) | main | - | ✅ |
| 2026-10-28 | Integration | [#148197383](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148197383) | main | - | ✅ |
| 2026-10-28 | Integration | [#148192847](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148192847) | main | - | ✅ |
| 2026-10-28 | Integration | [#148179766](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148179766) | main | - | ✅ |
| 2026-10-28 | Integration | [#148172719](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148172719) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
