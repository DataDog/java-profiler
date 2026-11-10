---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-10 13:56 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#151844621](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151844621) | ✅ | main | - |
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
| 2026-11-10 | Integration | [#151844621](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151844621) | main | - | ✅ |
| 2026-11-10 | Integration | [#151843114](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151843114) | main | - | ✅ |
| 2026-11-10 | Integration | [#151828258](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151828258) | main | - | ✅ |
| 2026-11-10 | Integration | [#151809728](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151809728) | main | - | ✅ |
| 2026-11-10 | Integration | [#151806612](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151806612) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
