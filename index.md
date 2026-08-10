---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-10 10:47 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#129908497](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129908497) | ✅ | main | - |
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
| 2026-08-10 | Integration | [#129908497](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129908497) | main | - | ✅ |
| 2026-08-10 | Integration | [#129908373](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129908373) | main | - | ✅ |
| 2026-08-10 | Integration | [#129903309](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129903309) | main | - | ✅ |
| 2026-08-10 | Integration | [#129899398](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129899398) | main | - | ✅ |
| 2026-08-10 | Integration | [#129897015](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129897015) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
