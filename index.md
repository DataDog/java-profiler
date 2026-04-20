---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-20 01:17 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#108459101](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108459101) | ✅ | main | - |
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
| 2026-04-20 | Integration | [#108459101](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108459101) | main | - | ✅ |
| 2026-04-17 | Integration | [#108341864](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108341864) | main | - | ❓ |
| 2026-04-17 | Integration | [#108272733](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108272733) | main | - | ✅ |
| 2026-04-17 | Integration | [#108269597](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108269597) | main | - | ✅ |
| 2026-04-17 | Integration | [#108242209](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108242209) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
