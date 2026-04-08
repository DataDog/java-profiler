---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-08 21:08 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#106767332](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/106767332) | ❓ | main | - |
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
| 2026-04-08 | Integration | [#106767332](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/106767332) | main | - | ❓ |
| 2026-04-08 | Integration | [#106713912](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/106713912) | main | - | ✅ |
| 2026-04-08 | Integration | [#106703302](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/106703302) | main | - | ✅ |
| 2026-04-08 | Integration | [#106694559](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/106694559) | main | - | ✅ |
| 2026-04-08 | Integration | [#106685198](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/106685198) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
