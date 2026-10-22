---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-22 10:56 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#146668546](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146668546) | ✅ | main | - |
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
| 2026-10-22 | Integration | [#146668546](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146668546) | main | - | ✅ |
| 2026-10-22 | Integration | [#146668317](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146668317) | main | - | ❓ |
| 2026-10-22 | Integration | [#146654275](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146654275) | main | - | ✅ |
| 2026-10-22 | Integration | [#146638179](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146638179) | main | - | ✅ |
| 2026-10-22 | Integration | [#146630636](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146630636) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
