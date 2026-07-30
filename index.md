---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-30 15:08 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#127993710](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127993710) | ❓ | main | - |
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
| 2026-07-30 | Integration | [#127993710](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127993710) | main | - | ❓ |
| 2026-07-30 | Integration | [#127989026](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127989026) | main | - | ❓ |
| 2026-07-30 | Integration | [#127985221](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127985221) | main | - | ❓ |
| 2026-07-30 | Integration | [#127970843](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127970843) | main | - | ❓ |
| 2026-07-30 | Integration | [#127962410](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127962410) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
