---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-03-06 09:35 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#100836908](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100836908) | ✅ | dependabot/gradle/gradle-minor-6ec1433625 | [#412](https://github.com/DataDog/java-profiler/pull/412) |
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
| 2026-03-06 | Integration | [#100836908](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100836908) | dependabot/gradle/gradle-minor-6ec1433625 | [#412](https://github.com/DataDog/java-profiler/pull/412) | ✅ |
| 2026-03-05 | Integration | [#100742160](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100742160) | main | - | ⚠️ |
| 2026-03-05 | Integration | [#100742167](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100742167) | main | - | ⚠️ |
| 2026-03-05 | Integration | [#100696413](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100696413) | main | - | ⚠️ |
| 2026-03-05 | Integration | [#100696124](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100696124) | jb/native_allocs | [#398](https://github.com/DataDog/java-profiler/pull/398) | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
