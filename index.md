---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-22 13:34 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#126229395](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126229395) | ❌ | main | - |
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
| 2026-07-22 | Integration | [#126229395](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126229395) | main | - | ❌ |
| 2026-07-22 | Integration | [#125974259](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125974259) | main | - | ❌ |
| 2026-07-21 | Integration | [#126116372](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126116372) | main | - | ❌ |
| 2026-07-21 | Integration | [#126112332](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126112332) | main | - | ❌ |
| 2026-07-21 | Integration | [#126103468](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126103468) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
