---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-28 20:20 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#127542535](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127542535) | ❌ | main | - |
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
| 2026-07-28 | Integration | [#127542535](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127542535) | main | - | ❌ |
| 2026-07-28 | Integration | [#127530859](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127530859) | main | - | ❌ |
| 2026-07-28 | Integration | [#127423902](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127423902) | main | - | ❌ |
| 2026-07-28 | Integration | [#127420564](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127420564) | main | - | ❌ |
| 2026-07-28 | Integration | [#127419766](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127419766) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
