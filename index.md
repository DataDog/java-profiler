---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-24 09:34 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#139738678](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139738678) | ✅ | main | - |
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
| 2026-09-24 | Integration | [#139738678](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139738678) | main | - | ✅ |
| 2026-09-24 | Integration | [#139733637](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139733637) | main | - | ✅ |
| 2026-09-24 | Integration | [#139734270](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139734270) | main | - | ✅ |
| 2026-09-24 | Integration | [#139721413](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139721413) | main | - | ✅ |
| 2026-09-24 | Integration | [#139721792](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139721792) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
