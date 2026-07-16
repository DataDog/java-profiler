---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-16 16:46 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125065519](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125065519) | ❌ | main | - |
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
| 2026-07-16 | Integration | [#125065519](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125065519) | main | - | ❌ |
| 2026-07-16 | Integration | [#125054272](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125054272) | main | - | ❌ |
| 2026-07-16 | Integration | [#125044290](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125044290) | main | - | ❌ |
| 2026-07-16 | Integration | [#125043676](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125043676) | main | - | ❌ |
| 2026-07-16 | Integration | [#125029918](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125029918) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
