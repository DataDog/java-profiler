---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-21 17:54 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#108856566](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108856566) | ✅ | main | - |
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
| 2026-04-21 | Integration | [#108856566](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108856566) | main | - | ✅ |
| 2026-04-21 | Integration | [#108817849](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108817849) | main | - | ✅ |
| 2026-04-21 | Integration | [#108801782](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108801782) | main | - | ✅ |
| 2026-04-21 | Integration | [#108799445](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108799445) | main | - | ✅ |
| 2026-04-21 | Integration | [#108786376](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108786376) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
