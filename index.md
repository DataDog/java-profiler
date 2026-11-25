---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-25 17:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#156543630](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156543630) | ✅ | main | - |
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
| 2026-11-25 | Integration | [#156543630](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156543630) | main | - | ✅ |
| 2026-11-25 | Integration | [#156543589](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156543589) | main | - | ✅ |
| 2026-11-25 | Integration | [#156543542](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156543542) | main | - | ⚠️ |
| 2026-11-25 | Integration | [#156541040](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156541040) | main | - | ✅ |
| 2026-11-25 | Integration | [#156540177](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156540177) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
