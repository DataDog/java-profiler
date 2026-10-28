---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-28 05:05 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#148080067](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148080067) | ✅ | main | - |
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
| 2026-10-28 | Integration | [#148080067](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148080067) | main | - | ✅ |
| 2026-10-28 | Integration | [#148060528](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148060528) | main | - | ✅ |
| 2026-10-28 | Integration | [#148053715](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148053715) | main | - | ✅ |
| 2026-10-27 | Integration | [#148044712](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148044712) | main | - | ✅ |
| 2026-10-27 | Integration | [#148044133](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148044133) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
