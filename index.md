---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-02 16:13 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#149432544](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149432544) | ❓ | main | - |
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
| 2026-11-02 | Integration | [#149432544](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149432544) | main | - | ❓ |
| 2026-11-02 | Integration | [#149421945](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149421945) | main | - | ✅ |
| 2026-11-02 | Integration | [#149422151](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149422151) | main | - | ⚠️ |
| 2026-11-02 | Integration | [#149419785](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149419785) | main | - | ✅ |
| 2026-11-02 | Integration | [#149412614](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149412614) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
