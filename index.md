---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-27 20:38 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#133773560](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133773560) | ❓ | main | - |
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
| 2026-08-27 | Integration | [#133773560](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133773560) | main | - | ❓ |
| 2026-08-27 | Integration | [#133773147](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133773147) | main | - | ❓ |
| 2026-08-27 | Integration | [#133729898](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133729898) | main | - | ✅ |
| 2026-08-27 | Integration | [#133727669](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133727669) | main | - | ❓ |
| 2026-08-27 | Integration | [#133711985](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/133711985) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
