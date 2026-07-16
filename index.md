---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-16 14:58 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125025068](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125025068) | ❌ | main | - |
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
| 2026-07-16 | Integration | [#125025068](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125025068) | main | - | ❌ |
| 2026-07-16 | Integration | [#125013370](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125013370) | main | - | ❌ |
| 2026-07-16 | Integration | [#125009935](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125009935) | main | - | ❓ |
| 2026-07-16 | Integration | [#125007228](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125007228) | main | - | ❌ |
| 2026-07-16 | Integration | [#125006450](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125006450) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
