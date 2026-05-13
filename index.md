---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-13 14:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112964379](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112964379) | ❌ | main | - |
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
| 2026-05-13 | Integration | [#112964379](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112964379) | main | - | ❌ |
| 2026-05-13 | Integration | [#112954289](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112954289) | main | - | ✅ |
| 2026-05-13 | Integration | [#112950252](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112950252) | main | - | ❌ |
| 2026-05-13 | Integration | [#112950536](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112950536) | main | - | ❌ |
| 2026-05-13 | Integration | [#112935226](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112935226) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
