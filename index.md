---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-18 07:34 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#138385710](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138385710) | ✅ | main | - |
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
| 2026-09-18 | Integration | [#138385710](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138385710) | main | - | ✅ |
| 2026-09-18 | Integration | [#138385620](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138385620) | main | - | ✅ |
| 2026-09-18 | Integration | [#138385702](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138385702) | main | - | ✅ |
| 2026-09-18 | Integration | [#138385700](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138385700) | main | - | ✅ |
| 2026-09-18 | Integration | [#138381183](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138381183) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
