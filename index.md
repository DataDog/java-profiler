---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-19 19:08 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125546835](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125546835) | ❌ | main | - |
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
| 2026-07-19 | Integration | [#125546835](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125546835) | main | - | ❌ |
| 2026-07-19 | Integration | [#125540308](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125540308) | main | - | ❌ |
| 2026-07-19 | Integration | [#125528974](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125528974) | main | - | ❌ |
| 2026-07-19 | Integration | [#125527748](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125527748) | main | - | ❌ |
| 2026-07-19 | Integration | [#125526448](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125526448) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
