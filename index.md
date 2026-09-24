---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-24 11:03 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#139557659](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139557659) | ✅ | main | - |
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
| 2026-09-24 | Integration | [#139557659](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139557659) | main | - | ✅ |
| 2026-09-24 | Integration | [#139752087](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139752087) | main | - | ✅ |
| 2026-09-24 | Integration | [#139743609](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139743609) | main | - | ✅ |
| 2026-09-24 | Integration | [#139738678](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139738678) | main | - | ✅ |
| 2026-09-24 | Integration | [#139733637](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139733637) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
