---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-11 16:20 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112514890](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112514890) | ✅ | main | - |
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
| 2026-05-11 | Integration | [#112514890](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112514890) | main | - | ✅ |
| 2026-05-11 | Integration | [#112503563](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112503563) | main | - | ✅ |
| 2026-05-11 | Integration | [#112496128](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112496128) | main | - | ✅ |
| 2026-05-11 | Integration | [#112480386](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112480386) | main | - | ✅ |
| 2026-05-11 | Integration | [#112472036](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112472036) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
