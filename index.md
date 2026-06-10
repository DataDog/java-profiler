---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-10 16:15 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#117957779](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117957779) | ❌ | main | - |
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
| 2026-06-10 | Integration | [#117957779](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117957779) | main | - | ❌ |
| 2026-06-10 | Integration | [#117956795](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117956795) | main | - | ❌ |
| 2026-06-10 | Integration | [#117955972](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117955972) | main | - | ❌ |
| 2026-06-10 | Integration | [#117945715](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117945715) | main | - | ❌ |
| 2026-06-10 | Integration | [#117917782](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117917782) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
