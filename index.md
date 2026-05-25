---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-25 01:33 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#114963754](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114963754) | ❌ | main | - |
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
| 2026-05-25 | Integration | [#114963754](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114963754) | main | - | ❌ |
| 2026-05-25 | Integration | [#114963716](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114963716) | main | - | ❌ |
| 2026-05-24 | Integration | [#114957876](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114957876) | main | - | ❌ |
| 2026-05-24 | Integration | [#114955073](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114955073) | main | - | ❓ |
| 2026-05-24 | Integration | [#114938562](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114938562) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
