---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-28 18:52 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#134015617](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134015617) | ❓ | main | - |
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
| 2026-08-28 | Integration | [#134015617](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134015617) | main | - | ❓ |
| 2026-08-28 | Integration | [#133999556](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133999556) | main | - | ✅ |
| 2026-08-28 | Integration | [#133998450](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133998450) | main | - | ❓ |
| 2026-08-28 | Integration | [#133979636](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133979636) | main | - | ✅ |
| 2026-08-28 | Integration | [#133982151](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133982151) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
