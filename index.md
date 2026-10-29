---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-29 11:57 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#148508274](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148508274) | ✅ | main | - |
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
| 2026-10-29 | Integration | [#148508274](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148508274) | main | - | ✅ |
| 2026-10-29 | Integration | [#148492019](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148492019) | main | - | ✅ |
| 2026-10-29 | Integration | [#148436997](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148436997) | main | - | ✅ |
| 2026-10-29 | Integration | [#148414352](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148414352) | main | - | ✅ |
| 2026-10-28 | Integration | [#148272442](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148272442) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
