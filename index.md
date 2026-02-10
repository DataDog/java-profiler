---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-10 22:36 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#95680405](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95680405) | ⚠️ | zgu/vmstruct_safety | [#363](https://github.com/DataDog/java-profiler/pull/363) |
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
| 2026-02-10 | Integration | [#95680405](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95680405) | zgu/vmstruct_safety | [#363](https://github.com/DataDog/java-profiler/pull/363) | ⚠️ |
| 2026-02-10 | Integration | [#95669408](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95669408) | zgu/vmstruct_safety | [#363](https://github.com/DataDog/java-profiler/pull/363) | ⚠️ |
| 2026-02-10 | Integration | [#95479316](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95479316) | jb/asan | [#362](https://github.com/DataDog/java-profiler/pull/362) | ✅ |
| 2026-02-06 | Integration | [#95012625](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95012625) | main | - | ✅ |
| 2026-02-06 | Integration | [#95002956](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95002956) | zgu/validatedId | [#359](https://github.com/DataDog/java-profiler/pull/359) | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
