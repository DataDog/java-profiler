---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-11 16:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#95868672](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95868672) | ⚠️ | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) |
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
| 2026-02-11 | Integration | [#95868672](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95868672) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |
| 2026-02-11 | Integration | [#95867417](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95867417) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |
| 2026-02-11 | Integration | [#95861107](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95861107) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |
| 2026-02-11 | Integration | [#95853148](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95853148) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |
| 2026-02-11 | Integration | [#95846421](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95846421) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
