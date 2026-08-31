---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-31 10:41 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#134264264](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134264264) | ✅ | main | - |
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
| 2026-08-31 | Integration | [#134264264](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134264264) | main | - | ✅ |
| 2026-08-31 | Integration | [#134264238](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134264238) | main | - | ✅ |
| 2026-08-31 | Integration | [#134264261](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134264261) | main | - | ✅ |
| 2026-08-31 | Integration | [#134264194](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134264194) | main | - | ✅ |
| 2026-08-31 | Integration | [#134251246](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134251246) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
