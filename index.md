---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-03 16:00 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#149814254](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149814254) | ✅ | main | - |
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
| 2026-11-03 | Integration | [#149814254](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149814254) | main | - | ✅ |
| 2026-11-03 | Integration | [#149815285](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149815285) | main | - | ✅ |
| 2026-11-03 | Integration | [#149740208](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149740208) | main | - | ✅ |
| 2026-11-03 | Integration | [#149720074](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149720074) | main | - | ✅ |
| 2026-11-03 | Integration | [#149713552](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149713552) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
