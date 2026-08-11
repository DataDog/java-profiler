---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-11 10:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#130143908](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130143908) | ✅ | main | - |
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
| 2026-08-11 | Integration | [#130143908](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130143908) | main | - | ✅ |
| 2026-08-11 | Integration | [#130134705](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130134705) | main | - | ✅ |
| 2026-08-11 | Integration | [#130121242](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130121242) | main | - | ✅ |
| 2026-08-11 | Integration | [#130117930](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130117930) | main | - | ✅ |
| 2026-08-11 | Integration | [#130103358](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130103358) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
