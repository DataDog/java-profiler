---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-24 08:38 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#120681108](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120681108) | ❌ | main | - |
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
| 2026-06-24 | Integration | [#120681108](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120681108) | main | - | ❌ |
| 2026-06-24 | Integration | [#120662822](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120662822) | main | - | ❌ |
| 2026-06-23 | Integration | [#120625840](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120625840) | main | - | ❌ |
| 2026-06-23 | Integration | [#120615824](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120615824) | main | - | ❌ |
| 2026-06-23 | Integration | [#120595380](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120595380) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
