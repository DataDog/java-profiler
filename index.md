---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-29 22:42 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#116041330](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116041330) | ❌ | main | - |
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
| 2026-05-29 | Integration | [#116041330](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116041330) | main | - | ❌ |
| 2026-05-29 | Integration | [#116036520](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116036520) | main | - | ❌ |
| 2026-05-29 | Integration | [#116030607](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116030607) | main | - | ❓ |
| 2026-05-29 | Integration | [#115946587](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115946587) | main | - | ❌ |
| 2026-05-29 | Integration | [#115929454](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115929454) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
