---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-27 13:40 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#133632659](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133632659) | ✅ | main | - |
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
| 2026-08-27 | Integration | [#133632659](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133632659) | main | - | ✅ |
| 2026-08-27 | Integration | [#133627111](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133627111) | main | - | ❓ |
| 2026-08-27 | Integration | [#133620842](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133620842) | main | - | ✅ |
| 2026-08-27 | Integration | [#133618593](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133618593) | main | - | ❓ |
| 2026-08-27 | Integration | [#133608940](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133608940) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
