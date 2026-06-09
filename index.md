---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-09 15:01 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#117799690](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117799690) | ❌ | main | - |
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
| 2026-06-09 | Integration | [#117799690](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117799690) | main | - | ❌ |
| 2026-06-09 | Integration | [#117794804](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117794804) | main | - | ❌ |
| 2026-06-09 | Integration | [#117786876](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117786876) | main | - | ❌ |
| 2026-06-09 | Integration | [#117786895](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117786895) | main | - | ❌ |
| 2026-06-09 | Integration | [#117781882](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117781882) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
