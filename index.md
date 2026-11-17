---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-17 12:40 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#153886136](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153886136) | ✅ | main | - |
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
| 2026-11-17 | Integration | [#153886136](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153886136) | main | - | ✅ |
| 2026-11-17 | Integration | [#153882342](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153882342) | main | - | ✅ |
| 2026-11-17 | Integration | [#153882776](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153882776) | main | - | ❓ |
| 2026-11-17 | Integration | [#153868312](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153868312) | main | - | ✅ |
| 2026-11-17 | Integration | [#153870468](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153870468) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
