---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-03-11 14:07 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#101863519](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/101863519) | ✅ | zgu/ctx_benchmark | - |
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
| 2026-03-11 | Integration | [#101863519](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/101863519) | zgu/ctx_benchmark | - | ✅ |
| 2026-03-11 | Integration | [#101845918](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/101845918) | jb/libraries_reentrancy | [#413](https://github.com/DataDog/java-profiler/pull/413) | ⚠️ |
| 2026-03-11 | Integration | [#101843330](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/101843330) | jb/libraries_reentrancy | [#413](https://github.com/DataDog/java-profiler/pull/413) | ⚠️ |
| 2026-03-11 | Integration | [#101811096](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/101811096) | jb/libraries_reentrancy | [#413](https://github.com/DataDog/java-profiler/pull/413) | ⚠️ |
| 2026-03-11 | Integration | [#101810015](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/101810015) | jb/libraries_reentrancy | [#413](https://github.com/DataDog/java-profiler/pull/413) | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
