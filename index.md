---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-03 08:37 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#142153107](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142153107) | ✅ | main | - |
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
| 2026-10-03 | Integration | [#142153107](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142153107) | main | - | ✅ |
| 2026-10-03 | Integration | [#142142478](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142142478) | main | - | ✅ |
| 2026-10-02 | Integration | [#142037552](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142037552) | main | - | ✅ |
| 2026-10-02 | Integration | [#141993372](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141993372) | main | - | ✅ |
| 2026-10-02 | Integration | [#141882792](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141882792) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
