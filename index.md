---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-27 01:17 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#109798116](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109798116) | ✅ | main | - |
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
| 2026-04-27 | Integration | [#109798116](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109798116) | main | - | ✅ |
| 2026-04-26 | Integration | [#109791987](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109791987) | main | - | ✅ |
| 2026-04-26 | Integration | [#109788853](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109788853) | main | - | ✅ |
| 2026-04-26 | Integration | [#109787750](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109787750) | main | - | ✅ |
| 2026-04-26 | Integration | [#109786627](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109786627) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
