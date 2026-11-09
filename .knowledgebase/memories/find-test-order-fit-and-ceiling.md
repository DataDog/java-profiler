---
id: find-test-order-fit-and-ceiling
title: test-order: what works, what its ceiling is, and the landed configuration
kind: finding
tags: [tests, test-order, tooling, decisions]
applies_to: [build-logic/conventions/src/main/kotlin/com/datadoghq/profiler/ProfilerTestPlugin.kt, ddprof-test/build.gradle.kts]
source: writing-any-code-thoroughly/find-test-order-fit-and-ceiling
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# test-order: what works, what its ceiling is, and the landed configuration

Working (verified): prioritization (order mode) always-on for ddprof-test
debug/release on a JDK 17+ test JVM — change detection detects changed Java
classes, boosts dependent tests (PriorityClassOrderer via
`junit.jupiter.testclass.order.default` system property, which Jupiter reads
as config parameter), and uses run history to front-load recently failing
tests; APFD metric reported per run (observed 25.6%–70.4% "faster than
default order"). Gated off for asan/tsan/coverage configs and pre-17 test
JVMs (per-task `testorder.mode.<taskName>=skip` extra property; Gradle 9's
`Test.setExecutable` populates javaLauncher metadata so test-order's own
pre-17 detection also fires). Musl Exec path has no wiring.

Ceiling (user decision 2026-10-30): test-order reorders, never skips — a green
run's wall time is unchanged; its index records Java classes only, so
native (.cpp) changes map to zero classes and the single
`libjavaProfiler.so` means any native change effectively affects all tests.
Prioritization for fail-fast + random-order opt-in were accepted as
"sufficient"; affected-subset selection was rejected as infeasible for this
Java+native layout. Review round: 11 fixes sealed (probe pessimism on unknown
JVM, probe consolidation/robustness with destroyForcibly and EA-string
parsing, teardown-test fixes, doc/gitignore corrections), verification green
vs the 4 known flaky reds; mavenLocal HIGH dismissed as accepted tradeoff.
