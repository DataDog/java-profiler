---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-27 12:16 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#133608940](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133608940) | ❓ | main | - |
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
| 2026-08-27 | Integration | [#133608940](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133608940) | main | - | ❓ |
| 2026-08-27 | Integration | [#133593448](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133593448) | main | - | ❓ |
| 2026-08-27 | Integration | [#133573306](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133573306) | main | - | ❓ |
| 2026-08-27 | Integration | [#133541138](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133541138) | main | - | ✅ |
| 2026-08-26 | Integration | [#133499036](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133499036) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
