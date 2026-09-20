---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-20 05:00 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#138695418](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138695418) | ✅ | main | - |
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
| 2026-09-20 | Integration | [#138695418](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138695418) | main | - | ✅ |
| 2026-09-19 | Integration | [#138655659](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138655659) | main | - | ✅ |
| 2026-09-19 | Integration | [#138644085](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138644085) | main | - | ✅ |
| 2026-09-18 | Integration | [#138536103](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138536103) | main | - | ✅ |
| 2026-09-18 | Integration | [#138494587](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138494587) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
