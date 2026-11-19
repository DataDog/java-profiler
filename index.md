---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-19 14:13 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#154743234](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154743234) | ✅ | main | - |
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
| 2026-11-19 | Integration | [#154743234](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154743234) | main | - | ✅ |
| 2026-11-19 | Integration | [#154744219](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154744219) | main | - | ✅ |
| 2026-11-19 | Integration | [#154735169](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154735169) | main | - | ✅ |
| 2026-11-19 | Integration | [#154729258](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154729258) | main | - | ✅ |
| 2026-11-19 | Integration | [#154725725](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154725725) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
