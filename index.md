---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-28 14:31 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#133928102](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133928102) | ✅ | main | - |
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
| 2026-08-28 | Integration | [#133928102](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133928102) | main | - | ✅ |
| 2026-08-28 | Integration | [#133933406](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133933406) | main | - | ❓ |
| 2026-08-28 | Integration | [#133905953](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133905953) | main | - | ❓ |
| 2026-08-28 | Integration | [#133904088](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133904088) | main | - | ⚠️ |
| 2026-08-28 | Integration | [#133900438](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133900438) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
