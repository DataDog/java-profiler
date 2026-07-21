---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-21 14:39 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125966486](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125966486) | ❌ | main | - |
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
| 2026-07-21 | Integration | [#125966486](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125966486) | main | - | ❌ |
| 2026-07-21 | Integration | [#125959694](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125959694) | main | - | ❌ |
| 2026-07-21 | Integration | [#125952686](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125952686) | main | - | ❌ |
| 2026-07-21 | Integration | [#125945295](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125945295) | main | - | ❌ |
| 2026-07-21 | Integration | [#125934302](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125934302) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
