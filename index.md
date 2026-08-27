---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-27 16:08 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#133690124](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133690124) | ❓ | main | - |
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
| 2026-08-27 | Integration | [#133690124](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133690124) | main | - | ❓ |
| 2026-08-27 | Integration | [#133687289](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133687289) | main | - | ❓ |
| 2026-08-27 | Integration | [#133672522](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133672522) | main | - | ❓ |
| 2026-08-27 | Integration | [#133654536](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133654536) | main | - | ✅ |
| 2026-08-27 | Integration | [#133654517](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133654517) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
