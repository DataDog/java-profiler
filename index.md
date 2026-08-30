---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-30 09:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#134162251](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134162251) | ✅ | main | - |
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
| 2026-08-30 | Integration | [#134162251](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134162251) | main | - | ✅ |
| 2026-08-30 | Integration | [#134149294](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134149294) | main | - | ✅ |
| 2026-08-29 | Integration | [#134100934](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134100934) | main | - | ✅ |
| 2026-08-29 | Integration | [#134088963](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134088963) | main | - | ✅ |
| 2026-08-28 | Integration | [#134059323](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134059323) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
