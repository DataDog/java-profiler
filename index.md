---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-19 09:47 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#113904231](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113904231) | ❌ | main | - |
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
| 2026-05-19 | Integration | [#113904231](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113904231) | main | - | ❌ |
| 2026-05-19 | Integration | [#113897622](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113897622) | main | - | ❌ |
| 2026-05-19 | Integration | [#113874531](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113874531) | main | - | ❌ |
| 2026-05-18 | Integration | [#113804124](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113804124) | main | - | ❌ |
| 2026-05-18 | Integration | [#113803675](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113803675) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
