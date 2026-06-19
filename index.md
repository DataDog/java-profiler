---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-19 19:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#120005956](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120005956) | ❌ | main | - |
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
| 2026-06-19 | Integration | [#120005956](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120005956) | main | - | ❌ |
| 2026-06-19 | Integration | [#120003923](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120003923) | main | - | ❌ |
| 2026-06-19 | Integration | [#120002449](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120002449) | main | - | ❌ |
| 2026-06-19 | Integration | [#120000746](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120000746) | main | - | ❌ |
| 2026-06-19 | Integration | [#119998017](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119998017) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
