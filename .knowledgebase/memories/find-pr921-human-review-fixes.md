---
id: find-pr921-human-review-fixes
title: PR #921 human-review fixes: admission pulse + ungated burn-in stamp (a63517c59)
kind: finding
tags: [pr-921, review-fixes, admission-pulse, burn-in, reference-chains]
applies_to: []
source: writing-any-code-thoroughly/find-pr921-human-review-fixes
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# PR #921 human-review fixes: admission pulse + ungated burn-in stamp (a63517c59)

The /sphinx address run over PR #921's human review threads confirmed two
genuine defects in the already-reviewed gate code, both fixed in commit
a63517c59 (SSH-signed, FF-pushed onto the remote's rebased tip 1b95808ce):

1. **Admission pulse** (referenceChains.cpp:869): the admission growth gate
   compared the latest heap-floor sample against a baseline the previous
   loop iteration had just raised. threadLoop() runs at ~1s cadence;
   `newestHeapFloorSample()` only changes at GC. So inside the ramp band the
   100% admission boost enabled on a growing sample was disabled on every
   subsequent iteration until the next GC (equality read as plateau) - a
   per-GC single-iteration pulse, not a sustained state. The gtests always
   recorded a fresh sample between calls, so the pulse was untested. Fix:
   compare against the sample the decision last consumed / latch on sample
   identity; test added for two decision calls with no intervening sample.
2. **Ungated burn-in stamp** (livenessTracker.cpp:2163): the
   `_leak_signal_activation_ns` CAS ran whenever `_enabled == true`, but
   `_leak_signal_enabled` (the flag secondsToOOM()'s burn-in gate consults)
   is `gc_generations || (record_liveness && reference_chains)` - false for
   a plain `memory=N:l` start. A later recording enabling reference chains
   inherited an expired burn-in and lost the 5-minute warmup suppression
   (including emergency-band admission). The adjacent comment claimed the
   opposite and was factually wrong; comment corrected, stamp now gated on
   the effective flag, test added for the two-session scenario.

Both fix threads replied ("Fixed in a63517c59") and resolved; the third
bundled review comment (3 concerns) was rebutted as no_change (2 already in
d8e594993, 1 documented design) and posted as a top-level rebuttal after
operator approval. verify-v1 build/test green on the pre-rebase base.

Lesson recorded: the operator rejected the classifier's consul_pass
bucketing for both findings (project-specific, not general) - they became
project lenses instead, and the lens corpus was consolidated 58->54 (atomics
triplicate dedup, copyright merge, dump-drain+stamp merged into one
effective-feature-flag lens). kb pushed v21.
