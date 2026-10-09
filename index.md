---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-09 14:23 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#143718058](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143718058) | ✅ | main | - |
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
| 2026-10-09 | Integration | [#143718058](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143718058) | main | - | ✅ |
| 2026-10-09 | Integration | [#143678791](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143678791) | main | - | ✅ |
| 2026-10-09 | Integration | [#143672741](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143672741) | main | - | ✅ |
| 2026-10-09 | Integration | [#143671236](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143671236) | main | - | ✅ |
| 2026-10-09 | Integration | [#143663618](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143663618) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
