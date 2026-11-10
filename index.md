---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-10 15:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#151881097](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151881097) | ⚠️ | main | - |
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
| 2026-11-10 | Integration | [#151881097](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151881097) | main | - | ⚠️ |
| 2026-11-10 | Integration | [#151880911](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151880911) | main | - | ✅ |
| 2026-11-10 | Integration | [#151879276](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151879276) | main | - | ✅ |
| 2026-11-10 | Integration | [#151849867](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151849867) | main | - | ✅ |
| 2026-11-10 | Integration | [#151849875](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151849875) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
