---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-14 05:03 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#144515922](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144515922) | ✅ | main | - |
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
| 2026-10-14 | Integration | [#144515922](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144515922) | main | - | ✅ |
| 2026-10-13 | Integration | [#144374937](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144374937) | main | - | ✅ |
| 2026-10-13 | Integration | [#144357321](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144357321) | main | - | ✅ |
| 2026-10-13 | Integration | [#144309747](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144309747) | main | - | ✅ |
| 2026-10-13 | Integration | [#144270749](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144270749) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
