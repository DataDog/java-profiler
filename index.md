---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-25 18:02 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#133147691](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133147691) | ❓ | main | - |
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
| 2026-08-25 | Integration | [#133147691](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133147691) | main | - | ❓ |
| 2026-08-25 | Integration | [#133110198](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133110198) | main | - | ❓ |
| 2026-08-25 | Integration | [#133099757](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133099757) | main | - | ✅ |
| 2026-08-25 | Integration | [#133092285](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133092285) | main | - | ✅ |
| 2026-08-25 | Integration | [#133080052](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133080052) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
