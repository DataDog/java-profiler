---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-27 20:33 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#110010249](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110010249) | ✅ | main | - |
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
| 2026-04-27 | Integration | [#110010249](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110010249) | main | - | ✅ |
| 2026-04-27 | Integration | [#110006250](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110006250) | main | - | ⚠️ |
| 2026-04-27 | Integration | [#109981945](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109981945) | main | - | ⚠️ |
| 2026-04-27 | Integration | [#109971825](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109971825) | main | - | ⚠️ |
| 2026-04-27 | Integration | [#109921192](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109921192) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
