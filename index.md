---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-30 14:30 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#110711148](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110711148) | ✅ | main | - |
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
| 2026-04-30 | Integration | [#110711148](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110711148) | main | - | ✅ |
| 2026-04-30 | Integration | [#110705574](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110705574) | main | - | ✅ |
| 2026-04-30 | Integration | [#110704130](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110704130) | main | - | ✅ |
| 2026-04-30 | Integration | [#110702250](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110702250) | main | - | ✅ |
| 2026-04-30 | Integration | [#110692453](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110692453) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
