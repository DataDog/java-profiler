---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-03 21:44 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128714480](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128714480) | ❓ | main | - |
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
| 2026-08-03 | Integration | [#128714480](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128714480) | main | - | ❓ |
| 2026-08-03 | Integration | [#128692398](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128692398) | main | - | ❓ |
| 2026-08-03 | Integration | [#128677781](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128677781) | main | - | ❓ |
| 2026-08-03 | Integration | [#128667807](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128667807) | main | - | ❓ |
| 2026-08-03 | Integration | [#128667024](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128667024) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
