---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-22 01:16 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#120109954](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120109954) | ❌ | main | - |
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
| 2026-06-22 | Integration | [#120109954](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120109954) | main | - | ❌ |
| 2026-06-22 | Integration | [#120109948](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120109948) | main | - | ❌ |
| 2026-06-21 | Integration | [#120078843](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120078843) | main | - | ❌ |
| 2026-06-21 | Integration | [#120069077](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120069077) | main | - | ❌ |
| 2026-06-20 | Integration | [#120034082](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120034082) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
