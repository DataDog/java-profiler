---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-30 15:36 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#141315309](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141315309) | ✅ | main | - |
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
| 2026-09-30 | Integration | [#141315309](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141315309) | main | - | ✅ |
| 2026-09-30 | Integration | [#141297529](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141297529) | main | - | ✅ |
| 2026-09-30 | Integration | [#141292100](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141292100) | main | - | ✅ |
| 2026-09-30 | Integration | [#141280517](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141280517) | main | - | ✅ |
| 2026-09-30 | Integration | [#141241321](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141241321) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
