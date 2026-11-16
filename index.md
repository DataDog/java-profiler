---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-16 01:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#153379147](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153379147) | ✅ | main | - |
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
| 2026-11-16 | Integration | [#153379147](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153379147) | main | - | ✅ |
| 2026-11-16 | Integration | [#153379141](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153379141) | main | - | ✅ |
| 2026-11-16 | Integration | [#153379114](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153379114) | main | - | ✅ |
| 2026-11-16 | Integration | [#153377148](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153377148) | main | - | ✅ |
| 2026-11-16 | Integration | [#153374168](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153374168) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
