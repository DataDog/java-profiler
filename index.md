---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-02 15:41 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#116548642](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116548642) | ❌ | main | - |
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
| 2026-06-02 | Integration | [#116548642](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116548642) | main | - | ❌ |
| 2026-06-02 | Integration | [#116536967](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116536967) | main | - | ❌ |
| 2026-06-02 | Integration | [#116525571](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116525571) | main | - | ❌ |
| 2026-06-02 | Integration | [#116505214](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116505214) | main | - | ❌ |
| 2026-06-02 | Integration | [#116505228](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116505228) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
