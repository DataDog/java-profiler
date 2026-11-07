---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-07 06:05 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#151202971](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151202971) | ✅ | main | - |
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
| 2026-11-07 | Integration | [#151202971](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151202971) | main | - | ✅ |
| 2026-11-07 | Integration | [#151196144](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151196144) | main | - | ✅ |
| 2026-11-06 | Integration | [#151129872](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151129872) | main | - | ✅ |
| 2026-11-06 | Integration | [#151127918](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151127918) | main | - | ✅ |
| 2026-11-06 | Integration | [#151114150](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151114150) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
