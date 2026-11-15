---
id: find-sphinx-delta-review-fixes
title: Sphinx delta review on PR #921: 18 findings, 13 fixes sealed, implementation interrupted
kind: finding
tags: [sphinx-review, delta-review, fix-round, pr-921, stopped-workflow]
applies_to: [ddprof-lib/src/main/cpp, ddprof-test]
source: writing-any-code-thoroughly/find-sphinx-delta-review-fixes
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Sphinx delta review on PR #921: 18 findings, 13 fixes sealed, implementation interrupted

Review srs_I1GQw_NxWSlQuRNMbosG2IlK (range d723d998d..aa527d27d): 0 CRITICAL / 0 HIGH /
5 MEDIUM / 11 LOW / 2 INFO, 77/84 regions clean. Sealed: 13 fixes, 5 dismissals.
Work order durable at .sphinx/address-feedback/srs_I1GQw_NxWSlQuRNMbosG2IlK.json
(sha256 509bff0f...).

Key accepted findings:
- F-b85fb71f7438 (M): stop() does not reset _admission_growth_baseline -> stale
  baseline across recording boundary; first urgent observation of the next recording
  skips the re-snapshot branch. Real bug in the growth-gate commit.
- F-bb1c295b8649 (M): AggressiveLeak Java test passes vacuously during the 300s
  burn-in (no positive control that urgency engaged).
- F-d39bc4408ac4 (M): leak-signal test seams not #ifdef DEBUG in the shipped header.
- F-d438f05913b4 (M) DISMISSED: candidate-only gate = spread heap-wide leak never
  diagnosed near OOM, silently - by design (the staging fix's contract);
  observability follow-up candidate.

Address workflow 4265b5cc: design/plan/implement COMPLETED (13 fixes written into the
tree, 14 files +573/-150, UNCOMMITTED), verify-v1 found a failure, verify-fix-v1 was
interrupted mid-run (repeated-test-loop behavior), workflow STOPPED by operator.
Not resumable - restart required. State + restart instructions:
.sphinx/address-workflow-state.md (in the worktree, gitignored).

UNKNOWN at checkpoint: which test verify-v1 failed on (no verify report artifact
survived). First restart step: build + run reference-chain gtests and the two Java
classes manually. Prime suspect: the AggressiveLeak test rewrite (last thing
implement touched, what fix-v1 was re-running).
