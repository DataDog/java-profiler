---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-25 13:45 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#133051825](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133051825) | ✅ | main | - |
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
| 2026-08-25 | Integration | [#133051825](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133051825) | main | - | ✅ |
| 2026-08-25 | Integration | [#133050197](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133050197) | main | - | ❓ |
| 2026-08-25 | Integration | [#133036698](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133036698) | main | - | ⚠️ |
| 2026-08-25 | Integration | [#133036659](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133036659) | main | - | ✅ |
| 2026-08-25 | Integration | [#133032804](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133032804) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
