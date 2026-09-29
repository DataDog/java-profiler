---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-29 09:50 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#140840768](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140840768) | ✅ | main | - |
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
| 2026-09-29 | Integration | [#140840768](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140840768) | main | - | ✅ |
| 2026-09-29 | Integration | [#140829996](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140829996) | main | - | ✅ |
| 2026-09-29 | Integration | [#140813415](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140813415) | main | - | ✅ |
| 2026-09-29 | Integration | [#140801322](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140801322) | main | - | ✅ |
| 2026-09-29 | Integration | [#140799610](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140799610) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
