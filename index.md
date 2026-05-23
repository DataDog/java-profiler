---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-23 18:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#114908059](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114908059) | ❌ | main | - |
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
| 2026-05-23 | Integration | [#114908059](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114908059) | main | - | ❌ |
| 2026-05-23 | Integration | [#114907648](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114907648) | main | - | ❓ |
| 2026-05-23 | Integration | [#114907474](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114907474) | main | - | ❓ |
| 2026-05-23 | Integration | [#114904117](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114904117) | main | - | ❓ |
| 2026-05-23 | Integration | [#114902631](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114902631) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
