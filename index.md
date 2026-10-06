---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-06 15:23 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#142754305](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142754305) | ⚠️ | main | - |
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
| 2026-10-06 | Integration | [#142754305](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142754305) | main | - | ⚠️ |
| 2026-10-06 | Integration | [#142718848](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142718848) | main | - | ✅ |
| 2026-10-06 | Integration | [#142702709](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142702709) | main | - | ✅ |
| 2026-10-06 | Integration | [#142695023](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142695023) | main | - | ✅ |
| 2026-10-06 | Integration | [#142684184](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142684184) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
