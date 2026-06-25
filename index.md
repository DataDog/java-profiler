---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-25 12:15 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#121002316](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121002316) | ❌ | main | - |
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
| 2026-06-25 | Integration | [#121002316](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121002316) | main | - | ❌ |
| 2026-06-25 | Integration | [#120977130](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120977130) | main | - | ❌ |
| 2026-06-25 | Integration | [#120955623](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120955623) | main | - | ❌ |
| 2026-06-25 | Integration | [#120935978](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120935978) | main | - | ❌ |
| 2026-06-24 | Integration | [#120901554](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120901554) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
