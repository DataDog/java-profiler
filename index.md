---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-22 11:19 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#109002048](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109002048) | ✅ | main | - |
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
| 2026-04-22 | Integration | [#109002048](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109002048) | main | - | ✅ |
| 2026-04-22 | Integration | [#108999260](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108999260) | main | - | ❓ |
| 2026-04-22 | Integration | [#108974327](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108974327) | main | - | ❓ |
| 2026-04-22 | Integration | [#108965344](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108965344) | main | - | ✅ |
| 2026-04-22 | Integration | [#108966104](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/108966104) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
