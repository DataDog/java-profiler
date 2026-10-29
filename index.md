---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-29 13:35 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#148536769](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148536769) | ✅ | main | - |
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
| 2026-10-29 | Integration | [#148536769](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148536769) | main | - | ✅ |
| 2026-10-29 | Integration | [#148524869](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148524869) | main | - | ✅ |
| 2026-10-29 | Integration | [#148522991](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148522991) | main | - | ✅ |
| 2026-10-29 | Integration | [#148513835](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148513835) | main | - | ✅ |
| 2026-10-29 | Integration | [#148508274](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148508274) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
