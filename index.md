---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-24 10:57 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#147274053](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147274053) | ✅ | main | - |
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
| 2026-10-24 | Integration | [#147274053](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147274053) | main | - | ✅ |
| 2026-10-24 | Integration | [#147273389](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147273389) | main | - | ✅ |
| 2026-10-24 | Integration | [#147272515](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147272515) | main | - | ✅ |
| 2026-10-24 | Integration | [#147271064](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147271064) | main | - | ✅ |
| 2026-10-23 | Integration | [#147243683](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147243683) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
