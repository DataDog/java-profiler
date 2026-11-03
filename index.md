---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-03 02:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#149643425](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149643425) | ✅ | main | - |
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
| 2026-11-03 | Integration | [#149643425](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149643425) | main | - | ✅ |
| 2026-11-02 | Integration | [#149581998](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149581998) | main | - | ✅ |
| 2026-11-02 | Integration | [#149514197](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149514197) | main | - | ✅ |
| 2026-11-02 | Integration | [#149497691](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149497691) | main | - | ✅ |
| 2026-11-02 | Integration | [#149480812](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149480812) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
