---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-23 22:06 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#147236263](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147236263) | ✅ | main | - |
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
| 2026-10-23 | Integration | [#147236263](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147236263) | main | - | ✅ |
| 2026-10-23 | Integration | [#147211446](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147211446) | main | - | ✅ |
| 2026-10-23 | Integration | [#147198469](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147198469) | main | - | ✅ |
| 2026-10-23 | Integration | [#147154496](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147154496) | main | - | ✅ |
| 2026-10-23 | Integration | [#147137530](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147137530) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
