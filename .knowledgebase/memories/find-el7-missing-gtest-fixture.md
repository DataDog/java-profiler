---
id: find-el7-missing-gtest-fixture
title: PR #800 CI failure root cause and fix (closed)
kind: finding
tags: [ci, el7, gtest, rc6]
applies_to: [ddprof-test/src/test/java/com/datadoghq/profiler/referencechains/ReferenceChainJfrParserTest.java]
source: failing-caching-enabled-caching/find-el7-missing-gtest-fixture
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# PR #800 CI failure root cause and fix (closed)

## Symptom
PR #800 (jb/rc-6-java-tests) failing on el7 CI runners. Investigation opened this
morning for the failure report (title mentioned Gradle "Caching not enabled /
Caching disabled for ExternalDependencyInstrumentingArtifactTransform"); the concrete
failing test was ReferenceChainJfrParserTest.

## Root cause (confirmed)
el7 CI runners have no Google Test installed, so the gtest-driven JFR roundtrip tool
never produces the fixture file the Java parser test expects; the test failed on the
missing file, not on parser logic.

## Fix
`Assumptions.assumeTrue` skip when the fixture is absent (JUnit 5), commit 218c2b7cc
on jb/rc-6-java-tests (pushed). jb/rc-7-tooling forked before that commit, so the same
fix was re-applied there during the humanize pass (currently in the uncommitted tree).

## Verification
ev-pr800-checks-green — `gh pr checks 800` after the fix: every check passes
(only `fuzz` 'skipping', an expected skip).
