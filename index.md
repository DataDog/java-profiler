---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-30 16:23 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128019992](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128019992) | ❓ | main | - |
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
| 2026-07-30 | Integration | [#128019992](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128019992) | main | - | ❓ |
| 2026-07-30 | Integration | [#128006202](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128006202) | main | - | ❓ |
| 2026-07-30 | Integration | [#128005354](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128005354) | main | - | ❓ |
| 2026-07-30 | Integration | [#128002444](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128002444) | main | - | ❓ |
| 2026-07-30 | Integration | [#127993710](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127993710) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
