---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-11 11:35 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#152186605](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152186605) | ✅ | main | - |
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
| 2026-11-11 | Integration | [#152186605](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152186605) | main | - | ✅ |
| 2026-11-11 | Integration | [#151992155](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151992155) | main | - | ✅ |
| 2026-11-11 | Integration | [#152179681](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152179681) | main | - | ✅ |
| 2026-11-11 | Integration | [#152178535](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152178535) | main | - | ✅ |
| 2026-11-11 | Integration | [#152177628](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152177628) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
