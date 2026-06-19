---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-19 10:25 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#119911853](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119911853) | ❌ | main | - |
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
| 2026-06-19 | Integration | [#119911853](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119911853) | main | - | ❌ |
| 2026-06-19 | Integration | [#119903907](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119903907) | main | - | ❌ |
| 2026-06-19 | Integration | [#119903802](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119903802) | main | - | ❌ |
| 2026-06-19 | Integration | [#119890623](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119890623) | main | - | ❌ |
| 2026-06-19 | Integration | [#119886634](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119886634) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
