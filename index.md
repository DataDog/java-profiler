---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-20 06:50 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#114145373](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114145373) | ❌ | main | - |
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
| 2026-05-20 | Integration | [#114145373](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114145373) | main | - | ❌ |
| 2026-05-19 | Integration | [#114049889](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114049889) | main | - | ❌ |
| 2026-05-19 | Integration | [#114051013](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114051013) | main | - | ❌ |
| 2026-05-19 | Integration | [#113996438](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113996438) | main | - | ❌ |
| 2026-05-19 | Integration | [#113974083](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113974083) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
