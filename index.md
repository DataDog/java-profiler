---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-03-06 18:00 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#100983844](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100983844) | ✅ | jb/netty_native_socket | - |
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
| 2026-03-06 | Integration | [#100983844](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100983844) | jb/netty_native_socket | - | ✅ |
| 2026-03-06 | Integration | [#100942066](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100942066) | jb/native_allocs | [#398](https://github.com/DataDog/java-profiler/pull/398) | ⚠️ |
| 2026-03-06 | Integration | [#100878526](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100878526) | dependabot/github_actions/actions/download-artifact-8 | [#402](https://github.com/DataDog/java-profiler/pull/402) | ✅ |
| 2026-03-06 | Integration | [#100877904](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100877904) | dependabot/github_actions/actions/download-artifact-8 | [#402](https://github.com/DataDog/java-profiler/pull/402) | ✅ |
| 2026-03-06 | Integration | [#100863417](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100863417) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
