---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-22 17:10 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#139239278](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139239278) | ✅ | main | - |
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
| 2026-09-22 | Integration | [#139239278](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139239278) | main | - | ✅ |
| 2026-09-22 | Integration | [#139224283](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139224283) | main | - | ✅ |
| 2026-09-22 | Integration | [#139222316](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139222316) | main | - | ✅ |
| 2026-09-22 | Integration | [#139222287](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139222287) | main | - | ✅ |
| 2026-09-22 | Integration | [#139222267](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139222267) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
