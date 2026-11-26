---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-26 11:52 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#156649782](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156649782) | ✅ | main | - |
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
| 2026-11-26 | Integration | [#156649782](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156649782) | main | - | ✅ |
| 2026-11-26 | Integration | [#156643078](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156643078) | main | - | ✅ |
| 2026-11-26 | Integration | [#156642093](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156642093) | main | - | ✅ |
| 2026-11-26 | Integration | [#156641340](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156641340) | main | - | ✅ |
| 2026-11-26 | Integration | [#156641355](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156641355) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
