---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-10 08:13 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#117893156](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117893156) | ❓ | main | - |
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
| 2026-06-10 | Integration | [#117893156](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117893156) | main | - | ❓ |
| 2026-06-10 | Integration | [#117883004](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117883004) | main | - | ❌ |
| 2026-06-09 | Integration | [#117842472](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117842472) | main | - | ❌ |
| 2026-06-09 | Integration | [#117837516](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117837516) | main | - | ❌ |
| 2026-06-09 | Integration | [#117836010](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117836010) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
