---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-06 11:16 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#122828590](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122828590) | ❌ | main | - |
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
| 2026-07-06 | Integration | [#122828590](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122828590) | main | - | ❌ |
| 2026-07-06 | Integration | [#122814721](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122814721) | main | - | ❌ |
| 2026-07-06 | Integration | [#122814468](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122814468) | main | - | ❌ |
| 2026-07-05 | Integration | [#122784844](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122784844) | main | - | ❌ |
| 2026-07-05 | Integration | [#122783219](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122783219) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
