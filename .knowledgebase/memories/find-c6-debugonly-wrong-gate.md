---
id: find-c6-debugonly-wrong-gate
title: C6 premise valid, fix wrong: DEBUG_ONLY keys DEBUG, asserts key NDEBUG; gtest-release strips NDEBUG without DEBUG -> compile break or lost I3 coverage
kind: finding
tags: [pr-797, debug-only, build, gtest]
applies_to: []
source: feedback-1/find-c6-debugonly-wrong-gate
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# C6 premise valid, fix wrong: DEBUG_ONLY keys DEBUG, asserts key NDEBUG; gtest-release strips NDEBUG without DEBUG -> compile break or lost I3 coverage

## Reasoning chain
All 7 readers are asserts. GtestTaskBuilder.kt:249-252 removes -DNDEBUG only. Recommend #ifndef NDEBUG. Sibling: unguarded *ForTest seams in release despite -DUNIT_TEST; resetCapacityForTest is why capacity() locks.

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/C.md. Lines at 9521394e8.

## Follow-up (2026-10-01)
- Survey: ~40 `#ifdef DEBUG` sites in 15 files plus 9 DEBUG_ONLY; NDEBUG has only 2 code gates plus ~103 asserts. gtest-release (asserts on, DEBUG off) is the only build that mixes the axes.
- No existing assert reads a DEBUG-only symbol (spot check). refCountGuard.cpp:208 comment says "DEBUG builds" but the gate is #ifndef NDEBUG.
- Policy: assert-only state goes under NDEBUG, optionally via an ASSERT_ONLY macro (needs approval).
