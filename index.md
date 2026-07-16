---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-16 22:38 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125160117](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125160117) | ❌ | main | - |
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
| 2026-07-16 | Integration | [#125160117](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125160117) | main | - | ❌ |
| 2026-07-16 | Integration | [#125160013](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125160013) | main | - | ❌ |
| 2026-07-16 | Integration | [#125152938](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125152938) | main | - | ❌ |
| 2026-07-16 | Integration | [#125136627](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125136627) | main | - | ❌ |
| 2026-07-16 | Integration | [#125119296](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125119296) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
