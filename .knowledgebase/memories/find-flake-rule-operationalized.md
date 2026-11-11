---
id: find-flake-rule-operationalized
title: a single failing gtest run under load is not a catch - require a standalone failure or a majority of repetitions
kind: finding
tags: [testing, flake, gtest, load, ci]
applies_to: []
source: native-safety-hypothesis-loop/find-flake-rule-operationalized
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


A clean-source binary fails the same canary gtest in 1 of 12 contended runs -
mutation-independent flake exists at the suite layer. Before treating a native
test failure as a catch, require a standalone (out-of-suite) failure or at
least 2 of 3 in-Gradle repetitions; a single in-suite failure under load is
evidence of nothing. The same rule applies to CI gates: a single failing run of
a load-sensitive check should be rerun before being treated as a regression.
