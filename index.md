---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-03-12 14:34 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#102138366](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/102138366) | ✅ | jb/libraries_reentrancy | [#413](https://github.com/DataDog/java-profiler/pull/413) |
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
| 2026-03-12 | Integration | [#102138366](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/102138366) | jb/libraries_reentrancy | [#413](https://github.com/DataDog/java-profiler/pull/413) | ✅ |
| 2026-03-12 | Integration | [#102136447](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/102136447) | jb/libraries_reentrancy | [#413](https://github.com/DataDog/java-profiler/pull/413) | ✅ |
| 2026-03-12 | Integration | [#102067100](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/102067100) | jb/libraries_reentrancy | [#413](https://github.com/DataDog/java-profiler/pull/413) | ✅ |
| 2026-03-11 | Integration | [#102007899](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/102007899) | jb/libraries_reentrancy | [#413](https://github.com/DataDog/java-profiler/pull/413) | ✅ |
| 2026-03-11 | Integration | [#101961774](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/101961774) | jb/libraries_reentrancy | [#413](https://github.com/DataDog/java-profiler/pull/413) | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
