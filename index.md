---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-03 05:46 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128502312](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128502312) | ❓ | main | - |
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
| 2026-08-03 | Integration | [#128502312](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128502312) | main | - | ❓ |
| 2026-08-03 | Integration | [#128499878](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128499878) | main | - | ❓ |
| 2026-08-03 | Integration | [#128492679](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128492679) | main | - | ❓ |
| 2026-08-03 | Integration | [#128487241](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128487241) | main | - | ❓ |
| 2026-08-03 | Integration | [#128487119](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128487119) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
