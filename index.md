---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-11 16:30 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#118211930](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118211930) | ❌ | main | - |
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
| 2026-06-11 | Integration | [#118211930](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118211930) | main | - | ❌ |
| 2026-06-11 | Integration | [#118171776](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118171776) | main | - | ❌ |
| 2026-06-11 | Integration | [#118166912](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118166912) | main | - | ❌ |
| 2026-06-11 | Integration | [#118158118](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118158118) | main | - | ❌ |
| 2026-06-11 | Integration | [#118143238](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118143238) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
