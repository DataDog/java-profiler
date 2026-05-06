---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-06 12:18 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#111710147](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111710147) | ✅ | main | - |
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
| 2026-05-06 | Integration | [#111710147](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111710147) | main | - | ✅ |
| 2026-05-06 | Integration | [#111707111](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111707111) | main | - | ❓ |
| 2026-05-06 | Integration | [#111637253](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111637253) | main | - | ❌ |
| 2026-05-05 | Integration | [#111462025](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111462025) | main | - | ✅ |
| 2026-05-05 | Integration | [#111444443](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111444443) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
