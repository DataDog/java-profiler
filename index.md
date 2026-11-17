---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-17 15:58 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#153974012](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153974012) | ⚠️ | main | - |
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
| 2026-11-17 | Integration | [#153974012](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153974012) | main | - | ⚠️ |
| 2026-11-17 | Integration | [#153968203](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153968203) | main | - | ⚠️ |
| 2026-11-17 | Integration | [#153959334](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153959334) | main | - | ⚠️ |
| 2026-11-17 | Integration | [#153953758](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153953758) | main | - | ❓ |
| 2026-11-17 | Integration | [#153943877](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153943877) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
