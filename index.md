---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-29 17:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#148657002](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148657002) | ✅ | main | - |
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
| 2026-10-29 | Integration | [#148657002](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148657002) | main | - | ✅ |
| 2026-10-29 | Integration | [#148641624](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148641624) | main | - | ⚠️ |
| 2026-10-29 | Integration | [#148629169](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148629169) | main | - | ✅ |
| 2026-10-29 | Integration | [#148607428](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148607428) | main | - | ✅ |
| 2026-10-29 | Integration | [#148604551](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148604551) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
