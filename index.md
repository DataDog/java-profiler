---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-21 21:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#126103468](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126103468) | ❌ | main | - |
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
| 2026-07-21 | Integration | [#126103468](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126103468) | main | - | ❌ |
| 2026-07-21 | Integration | [#126084270](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126084270) | main | - | ❌ |
| 2026-07-21 | Integration | [#126064350](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126064350) | main | - | ❌ |
| 2026-07-21 | Integration | [#126008898](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126008898) | main | - | ❌ |
| 2026-07-21 | Integration | [#125973702](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125973702) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
