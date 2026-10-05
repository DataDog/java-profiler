---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-05 15:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#142430004](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142430004) | ✅ | main | - |
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
| 2026-10-05 | Integration | [#142430004](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142430004) | main | - | ✅ |
| 2026-10-05 | Integration | [#142402795](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142402795) | main | - | ✅ |
| 2026-10-05 | Integration | [#142328435](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142328435) | main | - | ✅ |
| 2026-10-05 | Integration | [#142312754](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142312754) | main | - | ✅ |
| 2026-10-05 | Integration | [#142303711](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142303711) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
