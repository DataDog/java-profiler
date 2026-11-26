---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-26 05:04 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#156614067](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156614067) | ✅ | main | - |
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
| 2026-11-26 | Integration | [#156614067](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156614067) | main | - | ✅ |
| 2026-11-25 | Integration | [#156584274](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156584274) | main | - | ✅ |
| 2026-11-25 | Integration | [#156581501](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156581501) | main | - | ✅ |
| 2026-11-25 | Integration | [#156581183](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156581183) | main | - | ✅ |
| 2026-11-25 | Integration | [#156581127](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156581127) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
