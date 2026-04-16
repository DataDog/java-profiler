---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-16 12:32 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#107987818](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107987818) | ✅ | main | - |
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
| 2026-04-16 | Integration | [#107987818](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107987818) | main | - | ✅ |
| 2026-04-16 | Integration | [#107988827](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107988827) | main | - | ❓ |
| 2026-04-16 | Integration | [#107987922](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107987922) | main | - | ❓ |
| 2026-04-16 | Integration | [#107982398](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107982398) | main | - | ✅ |
| 2026-04-16 | Integration | [#107978918](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107978918) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
