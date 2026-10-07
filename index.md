---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-07 20:34 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#143199110](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143199110) | ✅ | main | - |
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
| 2026-10-07 | Integration | [#143199110](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143199110) | main | - | ✅ |
| 2026-10-07 | Integration | [#143157590](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143157590) | main | - | ✅ |
| 2026-10-07 | Integration | [#143125601](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143125601) | main | - | ✅ |
| 2026-10-07 | Integration | [#143124921](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143124921) | main | - | ✅ |
| 2026-10-07 | Integration | [#143086471](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143086471) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
