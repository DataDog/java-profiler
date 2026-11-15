---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-15 19:32 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#153359625](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153359625) | ✅ | main | - |
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
| 2026-11-15 | Integration | [#153359625](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153359625) | main | - | ✅ |
| 2026-11-15 | Integration | [#153351068](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153351068) | main | - | ✅ |
| 2026-11-15 | Integration | [#153342669](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153342669) | main | - | ✅ |
| 2026-11-15 | Integration | [#153340920](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153340920) | main | - | ✅ |
| 2026-11-15 | Integration | [#153335738](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153335738) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
