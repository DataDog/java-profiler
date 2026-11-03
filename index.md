---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-03 18:50 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#149894647](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149894647) | ✅ | main | - |
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
| 2026-11-03 | Integration | [#149894647](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149894647) | main | - | ✅ |
| 2026-11-03 | Integration | [#149887946](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149887946) | main | - | ❓ |
| 2026-11-03 | Integration | [#149874040](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149874040) | main | - | ✅ |
| 2026-11-03 | Integration | [#149872248](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149872248) | main | - | ✅ |
| 2026-11-03 | Integration | [#149869689](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149869689) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
