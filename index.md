---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-12 07:21 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#144011540](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144011540) | ✅ | main | - |
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
| 2026-10-12 | Integration | [#144011540](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144011540) | main | - | ✅ |
| 2026-10-12 | Integration | [#143999972](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143999972) | main | - | ✅ |
| 2026-10-12 | Integration | [#143999968](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143999968) | main | - | ✅ |
| 2026-10-12 | Integration | [#143999964](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143999964) | main | - | ✅ |
| 2026-10-12 | Integration | [#143999961](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143999961) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
