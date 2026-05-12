---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-12 13:35 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112699279](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112699279) | ❌ | main | - |
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
| 2026-05-12 | Integration | [#112699279](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112699279) | main | - | ❌ |
| 2026-05-12 | Integration | [#112693332](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112693332) | main | - | ⚠️ |
| 2026-05-12 | Integration | [#112691019](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112691019) | main | - | ❌ |
| 2026-05-12 | Integration | [#112687767](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112687767) | main | - | ❌ |
| 2026-05-12 | Integration | [#112683524](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112683524) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
