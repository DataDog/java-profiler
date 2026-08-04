---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-04 10:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128801065](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128801065) | ❓ | main | - |
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
| 2026-08-04 | Integration | [#128801065](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128801065) | main | - | ❓ |
| 2026-08-04 | Integration | [#128800856](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128800856) | main | - | ❓ |
| 2026-08-04 | Integration | [#128796796](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128796796) | main | - | ❓ |
| 2026-08-04 | Integration | [#128788179](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128788179) | main | - | ❓ |
| 2026-08-04 | Integration | [#128782557](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128782557) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
