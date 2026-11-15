---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-15 01:02 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#153306493](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153306493) | ✅ | main | - |
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
| 2026-11-15 | Integration | [#153306493](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153306493) | main | - | ✅ |
| 2026-11-15 | Integration | [#153306010](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153306010) | main | - | ✅ |
| 2026-11-14 | Integration | [#153297114](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153297114) | main | - | ✅ |
| 2026-11-14 | Integration | [#153296457](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153296457) | main | - | ✅ |
| 2026-11-14 | Integration | [#153289603](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153289603) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
