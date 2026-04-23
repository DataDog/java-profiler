---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-23 09:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#109227810](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109227810) | ✅ | main | - |
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
| 2026-04-23 | Integration | [#109227810](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109227810) | main | - | ✅ |
| 2026-04-23 | Integration | [#109226487](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109226487) | main | - | ✅ |
| 2026-04-23 | Integration | [#109225395](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109225395) | main | - | ✅ |
| 2026-04-23 | Integration | [#109222995](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109222995) | main | - | ✅ |
| 2026-04-22 | Integration | [#109124725](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109124725) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
