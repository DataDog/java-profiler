---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-20 09:36 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#108496479](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108496479) | ✅ | main | - |
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
| 2026-04-20 | Integration | [#108496479](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108496479) | main | - | ✅ |
| 2026-04-20 | Integration | [#108487553](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108487553) | main | - | ✅ |
| 2026-04-20 | Integration | [#108485752](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108485752) | main | - | ✅ |
| 2026-04-20 | Integration | [#108480470](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108480470) | main | - | ✅ |
| 2026-04-20 | Integration | [#108473153](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108473153) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
