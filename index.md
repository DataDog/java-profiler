---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-06 10:10 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#129354596](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129354596) | ❓ | main | - |
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
| 2026-08-06 | Integration | [#129354596](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129354596) | main | - | ❓ |
| 2026-08-06 | Integration | [#129349566](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129349566) | main | - | ❓ |
| 2026-08-06 | Integration | [#129340533](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129340533) | main | - | ✅ |
| 2026-08-06 | Integration | [#129334897](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129334897) | main | - | ❓ |
| 2026-08-06 | Integration | [#129321815](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129321815) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
