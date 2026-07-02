---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-02 08:54 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#122297212](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122297212) | ❌ | main | - |
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
| 2026-07-02 | Integration | [#122297212](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122297212) | main | - | ❌ |
| 2026-07-02 | Integration | [#122296189](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122296189) | main | - | ❌ |
| 2026-07-02 | Integration | [#122290189](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122290189) | main | - | ❌ |
| 2026-07-02 | Integration | [#122287376](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122287376) | main | - | ❌ |
| 2026-07-02 | Integration | [#122284659](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122284659) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
