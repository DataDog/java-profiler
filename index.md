---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-19 10:39 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#145631171](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145631171) | ✅ | main | - |
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
| 2026-10-19 | Integration | [#145631171](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145631171) | main | - | ✅ |
| 2026-10-19 | Integration | [#145618207](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145618207) | main | - | ✅ |
| 2026-10-19 | Integration | [#145618161](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145618161) | main | - | ✅ |
| 2026-10-19 | Integration | [#145603942](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145603942) | main | - | ✅ |
| 2026-10-19 | Integration | [#145579959](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145579959) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
