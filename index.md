---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-23 10:22 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#155631450](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155631450) | ✅ | main | - |
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
| 2026-11-23 | Integration | [#155631450](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155631450) | main | - | ✅ |
| 2026-11-23 | Integration | [#155619916](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155619916) | main | - | ✅ |
| 2026-11-23 | Integration | [#155618912](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155618912) | main | - | ✅ |
| 2026-11-23 | Integration | [#155618567](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155618567) | main | - | ⚠️ |
| 2026-11-23 | Integration | [#155610170](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155610170) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
