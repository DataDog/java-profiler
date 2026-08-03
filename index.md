---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-03 11:16 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128541596](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128541596) | ❓ | main | - |
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
| 2026-08-03 | Integration | [#128541596](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128541596) | main | - | ❓ |
| 2026-08-03 | Integration | [#128541594](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128541594) | main | - | ❓ |
| 2026-08-03 | Integration | [#128541619](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128541619) | main | - | ❓ |
| 2026-08-03 | Integration | [#128541614](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128541614) | main | - | ❓ |
| 2026-08-03 | Integration | [#128539112](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128539112) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
