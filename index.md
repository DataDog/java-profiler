---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-07 16:39 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112037135](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112037135) | ✅ | main | - |
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
| 2026-05-07 | Integration | [#112037135](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112037135) | main | - | ✅ |
| 2026-05-07 | Integration | [#112014060](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112014060) | main | - | ✅ |
| 2026-05-07 | Integration | [#112007172](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112007172) | main | - | ✅ |
| 2026-05-07 | Integration | [#112005702](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112005702) | main | - | ✅ |
| 2026-05-07 | Integration | [#112004466](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112004466) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
