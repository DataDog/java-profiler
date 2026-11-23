---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-23 13:37 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#155693906](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155693906) | ✅ | main | - |
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
| 2026-11-23 | Integration | [#155693906](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155693906) | main | - | ✅ |
| 2026-11-23 | Integration | [#155684153](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155684153) | main | - | ❓ |
| 2026-11-23 | Integration | [#155670984](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155670984) | main | - | ✅ |
| 2026-11-23 | Integration | [#155665162](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155665162) | main | - | ✅ |
| 2026-11-23 | Integration | [#155665691](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155665691) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
