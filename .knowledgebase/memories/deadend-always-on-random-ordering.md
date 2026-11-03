---
id: deadend-always-on-random-ordering
title: Always-on random test ordering (refuted for the default)
kind: dead-end
tags: [tests, flakiness, ordering]
applies_to: []
source: writing-any-code-thoroughly/deadend-always-on-random-ordering
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Always-on random test ordering (refuted for the default)

Adding `ClassOrderer$Random`/`MethodOrderer$Random` as the default ordering
mechanically works (verified: two identical filtered runs execute classes in
different orders) but is unshippable as a default: the suite's order-dependence
(find-profiler-singleton-order-cascade) makes some random orders detonate a
50+-failure cascade. Random ordering stays available behind
`-PrandomTestOrder` as a deliberate hunt; PROF-16395 tracks driving the suite
to randomized-green before enabling it in a rotation.

## What this rules out
- Shipping random ordering as default until the order-dependence is fixed.
