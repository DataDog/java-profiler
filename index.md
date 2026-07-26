---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-26 16:01 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#127024529](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127024529) | ❌ | main | - |
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
| 2026-07-26 | Integration | [#127024529](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127024529) | main | - | ❌ |
| 2026-07-26 | Integration | [#127024522](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127024522) | main | - | ❌ |
| 2026-07-26 | Integration | [#127024524](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127024524) | main | - | ❌ |
| 2026-07-26 | Integration | [#127010800](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127010800) | main | - | ❌ |
| 2026-07-26 | Integration | [#126998949](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126998949) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
