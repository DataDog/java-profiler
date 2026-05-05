---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-05 12:22 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#111462025](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111462025) | ✅ | main | - |
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
| 2026-05-05 | Integration | [#111462025](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111462025) | main | - | ✅ |
| 2026-05-05 | Integration | [#111444443](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111444443) | main | - | ✅ |
| 2026-05-04 | Integration | [#111169963](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111169963) | main | - | ✅ |
| 2026-05-04 | Integration | [#111141101](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111141101) | main | - | ✅ |
| 2026-05-04 | Integration | [#111141556](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111141556) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
