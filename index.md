---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-02 13:19 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#134888468](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134888468) | ✅ | main | - |
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
| 2026-09-02 | Integration | [#134888468](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134888468) | main | - | ✅ |
| 2026-09-02 | Integration | [#134888603](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134888603) | main | - | ⚠️ |
| 2026-09-02 | Integration | [#134866809](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134866809) | main | - | ❓ |
| 2026-09-02 | Integration | [#134855299](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134855299) | main | - | ❓ |
| 2026-09-02 | Integration | [#134841919](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134841919) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
