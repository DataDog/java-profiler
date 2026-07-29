---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-29 20:37 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#127830537](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127830537) | ❓ | main | - |
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
| 2026-07-29 | Integration | [#127830537](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127830537) | main | - | ❓ |
| 2026-07-29 | Integration | [#127815905](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127815905) | main | - | ❓ |
| 2026-07-29 | Integration | [#127788750](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127788750) | main | - | ❓ |
| 2026-07-29 | Integration | [#127761044](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127761044) | main | - | ❓ |
| 2026-07-29 | Integration | [#127744050](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127744050) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
