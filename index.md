---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-05 12:14 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#150520669](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150520669) | ✅ | main | - |
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
| 2026-11-05 | Integration | [#150520669](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150520669) | main | - | ✅ |
| 2026-11-05 | Integration | [#150523046](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150523046) | main | - | ❓ |
| 2026-11-05 | Integration | [#150519760](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150519760) | main | - | ✅ |
| 2026-11-05 | Integration | [#150496232](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150496232) | main | - | ✅ |
| 2026-11-05 | Integration | [#150492302](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150492302) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
