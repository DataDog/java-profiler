---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-02 19:07 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#135010836](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135010836) | ❓ | main | - |
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
| 2026-09-02 | Integration | [#135010836](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135010836) | main | - | ❓ |
| 2026-09-02 | Integration | [#135009326](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135009326) | main | - | ❓ |
| 2026-09-02 | Integration | [#135001750](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135001750) | main | - | ✅ |
| 2026-09-02 | Integration | [#134976197](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134976197) | main | - | ✅ |
| 2026-09-02 | Integration | [#134946818](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134946818) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
