---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-15 14:42 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124766483](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124766483) | ❌ | main | - |
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
| 2026-07-15 | Integration | [#124766483](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124766483) | main | - | ❌ |
| 2026-07-15 | Integration | [#124755968](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124755968) | main | - | ❌ |
| 2026-07-15 | Integration | [#124741516](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124741516) | main | - | ❌ |
| 2026-07-15 | Integration | [#124740938](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124740938) | main | - | ❌ |
| 2026-07-15 | Integration | [#124701843](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124701843) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
