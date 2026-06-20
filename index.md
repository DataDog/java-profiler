---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-20 15:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#120034082](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120034082) | ❌ | main | - |
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
| 2026-06-20 | Integration | [#120034082](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120034082) | main | - | ❌ |
| 2026-06-20 | Integration | [#120033274](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120033274) | main | - | ❌ |
| 2026-06-20 | Integration | [#120031937](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120031937) | main | - | ❌ |
| 2026-06-20 | Integration | [#120030296](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120030296) | main | - | ❌ |
| 2026-06-20 | Integration | [#120029752](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120029752) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
