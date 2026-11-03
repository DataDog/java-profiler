---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-03 10:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#149713552](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149713552) | ✅ | main | - |
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
| 2026-11-03 | Integration | [#149713552](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149713552) | main | - | ✅ |
| 2026-11-03 | Integration | [#149655974](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149655974) | main | - | ✅ |
| 2026-11-03 | Integration | [#149643425](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149643425) | main | - | ✅ |
| 2026-11-02 | Integration | [#149581998](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149581998) | main | - | ✅ |
| 2026-11-02 | Integration | [#149514197](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149514197) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
