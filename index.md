---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-10 19:14 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124084195](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124084195) | ❌ | main | - |
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
| 2026-07-10 | Integration | [#124084195](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124084195) | main | - | ❌ |
| 2026-07-10 | Integration | [#124082199](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124082199) | main | - | ❌ |
| 2026-07-10 | Integration | [#124075709](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124075709) | main | - | ❓ |
| 2026-07-10 | Integration | [#124064152](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124064152) | main | - | ❌ |
| 2026-07-10 | Integration | [#124056299](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124056299) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
