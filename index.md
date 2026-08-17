---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-17 13:05 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#131319893](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131319893) | ✅ | main | - |
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
| 2026-08-17 | Integration | [#131319893](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131319893) | main | - | ✅ |
| 2026-08-17 | Integration | [#131282709](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131282709) | main | - | ✅ |
| 2026-08-17 | Integration | [#131246778](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131246778) | main | - | ✅ |
| 2026-08-17 | Integration | [#131246317](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131246317) | main | - | ✅ |
| 2026-08-17 | Integration | [#131237054](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131237054) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
