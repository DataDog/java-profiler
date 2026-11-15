---
id: assert-state-gate-ndebug
title: State read only by assert() must be gated on NDEBUG (ASSERT_ONLY), not DEBUG (DEBUG_ONLY)
kind: finding
tags: [build, gtest, assertions, macros]
applies_to: [ddprof-lib/src/main/cpp/common.h, build-logic/conventions/src/main/kotlin/com/datadoghq/native/gtest/GtestTaskBuilder.kt]
source: feedback-1/find-c6-debugonly-wrong-gate
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


`assert()` is compiled in whenever `NDEBUG` is undefined. `DEBUG_ONLY()` keys on `DEBUG`.
The two diverge in the gtest release build: `GtestTaskBuilder.kt` removes `-DNDEBUG` to keep
assertions on but does not add `-DDEBUG`. A variable declared under `DEBUG_ONLY()` and read in
an `assert()` therefore fails to compile there (or, if the assert is also hidden, that build
silently loses the check).

Use `ASSERT_ONLY()` from `common.h` (`#ifndef NDEBUG`) for state whose only readers are asserts.
Keep `DEBUG_ONLY()` for code that genuinely belongs to `DEBUG` builds.
