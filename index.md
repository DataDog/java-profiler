---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-01 13:06 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#141607527](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141607527) | ✅ | main | - |
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
| 2026-10-01 | Integration | [#141607527](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141607527) | main | - | ✅ |
| 2026-10-01 | Integration | [#141597007](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141597007) | main | - | ✅ |
| 2026-10-01 | Integration | [#141594763](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141594763) | main | - | ✅ |
| 2026-10-01 | Integration | [#141588148](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141588148) | main | - | ✅ |
| 2026-10-01 | Integration | [#141587179](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141587179) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
