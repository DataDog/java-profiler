---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-30 13:50 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#148924141](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148924141) | ✅ | main | - |
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
| 2026-10-30 | Integration | [#148924141](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148924141) | main | - | ✅ |
| 2026-10-30 | Integration | [#148921141](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148921141) | main | - | ✅ |
| 2026-10-30 | Integration | [#148917173](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148917173) | main | - | ✅ |
| 2026-10-30 | Integration | [#148895016](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148895016) | main | - | ✅ |
| 2026-10-30 | Integration | [#148892728](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148892728) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
