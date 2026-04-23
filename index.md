---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-23 16:53 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#109357385](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109357385) | ✅ | main | - |
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
| 2026-04-23 | Integration | [#109357385](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109357385) | main | - | ✅ |
| 2026-04-23 | Integration | [#109353274](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109353274) | main | - | ✅ |
| 2026-04-23 | Integration | [#109305697](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109305697) | main | - | ✅ |
| 2026-04-23 | Integration | [#109301228](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109301228) | main | - | ✅ |
| 2026-04-23 | Integration | [#109289534](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109289534) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
