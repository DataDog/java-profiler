---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-22 14:44 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#139181294](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139181294) | ✅ | main | - |
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
| 2026-09-22 | Integration | [#139181294](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139181294) | main | - | ✅ |
| 2026-09-22 | Integration | [#139175928](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139175928) | main | - | ✅ |
| 2026-09-22 | Integration | [#139160780](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139160780) | main | - | ⚠️ |
| 2026-09-22 | Integration | [#139120791](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139120791) | main | - | ⚠️ |
| 2026-09-22 | Integration | [#139104334](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139104334) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
