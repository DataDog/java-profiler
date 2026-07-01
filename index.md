---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-01 13:53 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#122106855](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122106855) | ❌ | main | - |
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
| 2026-07-01 | Integration | [#122106855](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122106855) | main | - | ❌ |
| 2026-07-01 | Integration | [#122096667](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122096667) | main | - | ❌ |
| 2026-07-01 | Integration | [#122089427](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122089427) | main | - | ❌ |
| 2026-07-01 | Integration | [#122088165](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122088165) | main | - | ❌ |
| 2026-07-01 | Integration | [#122085585](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122085585) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
