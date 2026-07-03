---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-03 08:09 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#122526310](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122526310) | ❌ | main | - |
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
| 2026-07-03 | Integration | [#122526310](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122526310) | main | - | ❌ |
| 2026-07-03 | Integration | [#122515116](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122515116) | main | - | ❌ |
| 2026-07-02 | Integration | [#122420464](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122420464) | main | - | ❓ |
| 2026-07-02 | Integration | [#122403806](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122403806) | main | - | ❌ |
| 2026-07-02 | Integration | [#122400168](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122400168) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
