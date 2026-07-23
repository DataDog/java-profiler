---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-23 11:25 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#126479462](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126479462) | ❌ | main | - |
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
| 2026-07-23 | Integration | [#126479462](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126479462) | main | - | ❌ |
| 2026-07-23 | Integration | [#126477548](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126477548) | main | - | ❌ |
| 2026-07-23 | Integration | [#126472003](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126472003) | main | - | ❌ |
| 2026-07-23 | Integration | [#126467580](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126467580) | main | - | ❌ |
| 2026-07-23 | Integration | [#126464246](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126464246) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
