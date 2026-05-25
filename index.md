---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-25 12:39 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#115009139](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115009139) | ❌ | main | - |
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
| 2026-05-25 | Integration | [#115009139](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115009139) | main | - | ❌ |
| 2026-05-25 | Integration | [#115005403](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115005403) | main | - | ❌ |
| 2026-05-25 | Integration | [#115004730](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115004730) | main | - | ❌ |
| 2026-05-25 | Integration | [#115001865](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115001865) | main | - | ❌ |
| 2026-05-25 | Integration | [#115000017](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115000017) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
