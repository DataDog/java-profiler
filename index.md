---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-12 16:15 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#130496946](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130496946) | ✅ | main | - |
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
| 2026-08-12 | Integration | [#130496946](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130496946) | main | - | ✅ |
| 2026-08-12 | Integration | [#130451806](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130451806) | main | - | ✅ |
| 2026-08-12 | Integration | [#130444417](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130444417) | main | - | ✅ |
| 2026-08-12 | Integration | [#130411119](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130411119) | main | - | ✅ |
| 2026-08-12 | Integration | [#130410709](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130410709) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
