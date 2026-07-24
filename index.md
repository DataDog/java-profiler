---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-24 11:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#126756165](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126756165) | ❌ | main | - |
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
| 2026-07-24 | Integration | [#126756165](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126756165) | main | - | ❌ |
| 2026-07-24 | Integration | [#126750267](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126750267) | main | - | ❌ |
| 2026-07-24 | Integration | [#126731768](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126731768) | main | - | ❌ |
| 2026-07-24 | Integration | [#126730964](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126730964) | main | - | ❌ |
| 2026-07-24 | Integration | [#126726205](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126726205) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
