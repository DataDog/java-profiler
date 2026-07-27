---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-27 12:07 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#127118071](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127118071) | ❌ | main | - |
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
| 2026-07-27 | Integration | [#127118071](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127118071) | main | - | ❌ |
| 2026-07-27 | Integration | [#127118586](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127118586) | main | - | ❓ |
| 2026-07-27 | Integration | [#127102867](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127102867) | main | - | ❌ |
| 2026-07-27 | Integration | [#127093833](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127093833) | main | - | ❌ |
| 2026-07-27 | Integration | [#127062847](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127062847) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
