---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-04 08:47 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#111169963](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111169963) | ✅ | main | - |
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
| 2026-05-04 | Integration | [#111169963](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111169963) | main | - | ✅ |
| 2026-05-04 | Integration | [#111141101](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111141101) | main | - | ✅ |
| 2026-05-04 | Integration | [#111141556](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111141556) | main | - | ✅ |
| 2026-05-04 | Integration | [#111141116](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111141116) | main | - | ✅ |
| 2026-05-04 | Integration | [#111141112](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111141112) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
