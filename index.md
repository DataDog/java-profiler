---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-12 04:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124180657](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124180657) | ❌ | main | - |
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
| 2026-07-12 | Integration | [#124180657](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124180657) | main | - | ❌ |
| 2026-07-11 | Integration | [#124145342](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124145342) | main | - | ❌ |
| 2026-07-11 | Integration | [#124137359](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124137359) | main | - | ❌ |
| 2026-07-10 | Integration | [#124114275](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124114275) | main | - | ❌ |
| 2026-07-10 | Integration | [#124094581](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124094581) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
