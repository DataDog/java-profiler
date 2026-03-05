---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-03-05 18:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#100696413](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100696413) | ⚠️ | main | - |
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
| 2026-03-05 | Integration | [#100696413](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100696413) | main | - | ⚠️ |
| 2026-03-05 | Integration | [#100696124](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100696124) | jb/native_allocs | [#398](https://github.com/DataDog/java-profiler/pull/398) | ⚠️ |
| 2026-03-05 | Integration | [#100696212](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100696212) | dependabot/github_actions/actions/download-artifact-8 | [#402](https://github.com/DataDog/java-profiler/pull/402) | ⚠️ |
| 2026-03-05 | Integration | [#100695262](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100695262) | main | - | ⚠️ |
| 2026-02-13 | Integration | [#96351177](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/96351177) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
