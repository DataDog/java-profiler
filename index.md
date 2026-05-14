---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-14 17:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#113230770](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113230770) | ❌ | main | - |
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
| 2026-05-14 | Integration | [#113230770](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113230770) | main | - | ❌ |
| 2026-05-14 | Integration | [#113157459](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113157459) | main | - | ❌ |
| 2026-05-13 | Integration | [#113016565](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113016565) | main | - | ❌ |
| 2026-05-13 | Integration | [#113016065](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113016065) | main | - | ❌ |
| 2026-05-13 | Integration | [#113016703](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113016703) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
