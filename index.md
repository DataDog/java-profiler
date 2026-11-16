---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-16 12:35 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#153475199](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153475199) | ✅ | main | - |
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
| 2026-11-16 | Integration | [#153475199](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153475199) | main | - | ✅ |
| 2026-11-16 | Integration | [#153472827](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153472827) | main | - | ⚠️ |
| 2026-11-16 | Integration | [#153471809](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153471809) | main | - | ⚠️ |
| 2026-11-16 | Integration | [#153471655](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153471655) | main | - | ⚠️ |
| 2026-11-16 | Integration | [#153463192](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153463192) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
