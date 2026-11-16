---
id: find-paired-traces-adjudicate-r1-cost-confound
title: cost deltas need paired same-window replays of one prerecorded trace - block-ordered estimates only work under small measured drift
kind: finding
tags: [benchmark, estimator, paired, drift, cost, testing]
applies_to: []
source: native-safety-hypothesis-loop/find-paired-traces-adjudicate-r1-cost-confound
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


Replaying one prerecorded trace identically in every measured mode with matched
bookkeeping and AB/BA pair-order randomization makes per-mode deltas paired
causal estimates: the A-A noise floor stays non-significant even though absolute
medians drift ~30 percent within a single run, so the pairing carries the
signal. Unpaired before/after medians cannot resolve effects at or below
roughly 10 ns/op. A block-ordered unpaired estimate deviates from the paired
estimate by exactly the within-window drift it fails to cancel - the deviation
tracks the measured drift slope (r=+0.902, permutation p=0.0001) and reaches
±13 ns under heavy drift - so block ordering is adequate only when drift is
measured small, never assumed. Report the paired median with a seeded bootstrap
confidence interval, an exact sign test, and the A-A noise floor.
